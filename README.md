*This project has been created as part of the 42 curriculum by migusant, skuhlcke.*

# cub3D

A pseudo-3D maze renderer inspired by **Wolfenstein 3D** (id Software, 1992), built with raycasting and the MiniLibX graphics library. The project explores the math behind early first-person shooters: turning a 2D tile grid into a textured 3D view from the player's perspective using one ray per screen column.

## Description

cub3D parses a `.cub` scene file, builds an internal map representation, and renders a real-time first-person view of that map using the **DDA (Digital Differential Analysis)** raycasting algorithm. The player navigates the maze with keyboard input; walls are drawn with directional textures; the floor and ceiling are filled with configurable solid colors.

### Key Features

- **DDA raycasting** for wall detection — one ray per screen column, perpendicular distance computed against the player's view plane to avoid fisheye distortion
- **Per-direction wall textures** — North, South, East, and West-facing walls each render their own XPM texture, with correct U/V mapping and edge-mirroring per face
- **Configurable floor and ceiling colors** parsed from RGB values in the `.cub` file
- **Smooth movement and rotation** — WASD strafing, arrow-key camera turn, with corner-aware collision detection (radius-based bounding box, slide-on-blocked behavior)
- **Player-centered minimap** with a clamped-viewport camera — player stays centered while in the map interior, drifts toward the visible edge near map boundaries, fills out-of-map area with a neutral background
- **Robust scene parser** that validates element identifiers (NO/SO/WE/EA/F/C), RGB ranges [0–255], texture file paths, and full map enclosure (every walkable cell must be surrounded by walls or other walkable cells; any contact with map padding triggers an error)
- **Clean memory management** — every heap allocation is tracked through a single cleanup path, including the four loaded XPM textures and the framebuffer image
- **MLX leak suppression** via a curated `mlx.supp` file for valgrind, scoped narrowly so any leak in cub3D code itself still surfaces

### Project Structure

```
cub3D/
├── inc/
│   └── cub3d.h                   # Single header: types, defines, prototypes
├── libft/                        # Custom libft (subset used by this project)
├── maps/                         # Example .cub scenes, XPM textures, parser test cases
│   ├── example_1.cub             # Example scenes
│   ├── example_2.cub
│   ├── example_3.cub
│   ├── north.xpm                 # Wall textures (one per cardinal direction)
│   ├── south.xpm
│   ├── east.xpm
│   ├── west.xpm
│   └── test_*.cub                # Crafted malformed inputs for parser robustness
├── src/
│   ├── main.c                    # Entry point and argv handling
│   ├── parse_file.c              # File reading, line splitting, dispatch
│   ├── parse_elements.c          # NO/SO/WE/EA texture identifiers
│   ├── parse_colors.c            # F/C floor and ceiling RGB parsing
│   ├── parse_map.c               # Map grid construction with row padding
│   ├── validate_map.c            # Player spawn, character set, dimensions
│   ├── validate_map_helpers.c    # Direction vector initialization
│   ├── validate_enclosure.c      # Map enclosure check
│   ├── window.c                  # MLX init, texture loading, hooks
│   ├── input.c                   # Keypress / keyrelease handlers
│   ├── game_loop.c               # Per-frame movement and rotation
│   ├── collision.c               # Bounding-box collision detection
│   ├── raycast.c                 # Wall detection and texture selection
│   ├── raycast_helpers.c         # Texture pixel sampling
│   ├── dda.c                     # DDA algorithm: ray init, stepping, hit
│   ├── column.c                  # Wall strip drawing, background fill
│   ├── render.c                  # Frame composition pipeline
│   ├── minimap.c                 # Minimap viewport rendering
│   └── cleanup.c                 # Resource teardown and exit path
├── minilibx-linux.tgz            # Bundled MiniLibX (extracted on first build)
├── mlx.supp                      # Valgrind suppression file for MLX/X11 internals
├── Makefile
└── README.md
```

## Instructions

### Compilation

```bash
make                     # Build the cub3D executable
make v                   # Run valgrind on the default map (example_1.cub)
make v MAP=maps/map.cub  # Run valgrind on a specific map
make clean               # Remove .o files
make fclean              # Remove .o files, executable, and libft/MLX artifacts
make re                  # Recompile from scratch
```

The Makefile builds `libft` and `MiniLibX` via their own Makefiles before linking the main binary. On first build, `minilibx-linux.tgz` is extracted automatically.

### Execution

```bash
./cub3D <map.cub>
```

`<map.cub>` must be a valid scene file. Three example scenes are included under `maps/`:

```bash
./cub3D maps/example_1.cub
./cub3D maps/example_2.cub
./cub3D maps/example_3.cub
```

Additional `test_*.cub` files exist in `maps/` for parser robustness testing — these are intentionally malformed inputs (missing identifiers, bad RGB values, unenclosed maps, CRLF line endings, etc.) that exercise error paths.

### Controls

| Key | Action |
|-----|--------|
| `W` / `S` | Move forward / backward |
| `A` / `D` | Strafe left / right |
| `←` / `→` | Rotate camera |
| `ESC` | Quit |
| Window close button | Quit |

### Memory checking

```
make v                   # Run valgrind on the default map
make v MAP=maps/map.cub  # Run valgrind on a specific map
```

`mlx.supp` filters out leaks that originate inside X11 and MiniLibX internals. Any leak whose call stack includes a cub3D function will still be reported.

## Scene file format (`.cub`)

A scene file declares six elements followed by the map grid. Element order is flexible; the map must come last.

```
NO ./maps/north.xpm    # North-facing wall texture
SO ./maps/south.xpm    # South-facing wall texture
WE ./maps/west.xpm     # West-facing wall texture
EA ./maps/east.xpm     # East-facing wall texture
F  220,100,0           # Floor RGB (0–255 each)
C  225,30,0            # Ceiling RGB (0–255 each)

1111111
1000001
100N001
1000001
1111111
```

**Map character set:**

- `1` — wall
- `0` — empty walkable cell
- `N` `S` `E` `W` — player spawn (exactly one), facing the named direction
- ` ` (space) — out-of-map padding for non-rectangular maps

The map must be fully enclosed by walls. Any walkable cell adjacent to a space character or the map's outer edge is rejected as an open border.

## Technical Implementation

### Raycasting (DDA)

For each screen column `x` ∈ [0, WINDOW_WIDTH), a ray is cast from the player position in the direction `dir + plane × camera_x`, where `camera_x = 2x/WIDTH − 1`. The DDA algorithm walks the ray cell-by-cell along whichever axis crosses the next grid line first, comparing accumulated `side_dist_x` and `side_dist_y` values until the ray hits a wall.

Wall distance is computed as **perpendicular distance** (`side_dist − delta_dist` along the hit axis), not Euclidean — this correction is what eliminates the curved-floor "fisheye" effect.

The wall strip height for column `x` is `WINDOW_HEIGHT / wall_dist`. Texture U comes from the fractional hit position on the wall face, with horizontal mirroring applied for east-facing and north-facing hits to keep textures oriented consistently. Texture V is interpolated linearly across the strip's pixel range.

### Movement and collision

Translation is in the player's local frame: `W`/`S` move along `dir`, `A`/`D` move along the perpendicular `(dir_y, −dir_x)`. Rotation is a 2D rotation matrix applied to both `dir` and `plane` simultaneously so the camera's view plane stays orthogonal to the look direction.

Collision uses a small bounding box (radius `0.15`) around the player. If the proposed move is blocked diagonally, the game tries X-only and Y-only movement separately — this produces the "slide along the wall" feel that prevents the player from getting stuck on corners.

### Minimap

The minimap is a player-centered viewport showing a `5×5` cell window of the map at fixed pixel-per-cell scaling. The viewport origin (top-left map cell visible) is computed as `player.pos − VIEWPORT_CELLS / 2`, then clamped to `[0, map_dim − VIEWPORT_CELLS]`.

The clamping is done in two passes (upper bound first, lower bound second) which incidentally handles maps smaller than the viewport: the upper-bound pass produces a negative value, the lower-bound pass pulls it to zero, and the per-pixel render naturally fills the over-hung region with the out-of-map color.

Rendering is per-pixel rather than per-cell: each minimap pixel computes its corresponding world cell via `origin + pixel_offset / tile_size`. This handles fractional viewport origins (smooth scrolling) without sub-pixel-offset bookkeeping.

### Memory management

A single `t_game` struct, allocated on the stack in `main`, owns all state. Heap allocations are concentrated in three places:

- The map grid (`char **` rows, freed by `free_map_grid`)
- The four texture path strings (freed by `free_textures`)
- The four MLX texture images and the framebuffer image (destroyed by `exit_game` via `mlx_destroy_image`)

`exit_game` is the single exit path. Every error site — argv check, file read failure, parsing error, MLX init failure — routes through it. Cleanup order: textures → framebuffer → window → display → free(mlx) → grid + paths → `exit(code)`. Each step is NULL-guarded so partial-init states clean up without crashing.

## Resources

### Raycasting

- **Lode Vandevenne — *Raycasting tutorial***: https://lodev.org/cgtutor/raycasting.html
  The canonical reference for the DDA algorithm, camera plane model, perpendicular wall distance correction, and texture mapping. Variable names (`sideDistX`, `deltaDistX`, `perpWallDist`) used throughout cub3D implementations across 42 trace back to this source.
- **Permadi — *Ray-Casting Tutorial For Game Development And Other Purposes***: https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/
  Older, more verbose treatment of the same material. Useful for the geometric intuition before diving into Lode's optimized form.
- **3DSage — *Make Your Own Raycaster* (YouTube)**: https://www.youtube.com/watch?v=gYRrGTC7GtA
  Visual walk-through of the algorithm with live drawing — helpful for understanding why DDA works, not just how to implement it.

### MiniLibX

- **42 Docs — MiniLibX**: internal documentation
- `man 3 mlx_*` (limited; most learning is via reading `mlx.h` and the source under `minilibx-linux/`)

### Math reference

- **Vector rotation in 2D** — standard 2×2 rotation matrix, applied to both direction and view plane vectors so they stay orthogonal:

  ```
  new_dir_x   = dir_x * cos(θ) - dir_y * sin(θ)
  new_dir_y   = dir_x * sin(θ) + dir_y * cos(θ)
  ```

### AI usage

AI tools (GitHub Copilot, ChatGPT) were used as a thinking partner and audit assistant to discuss problems and approaches, but all final code, architecture decisions, and bug fixes were produced by the students after understanding the underlying concepts.

- **Static code audit** — read the full source tree and produced a written audit covering architecture, parser robustness, raycasting correctness, memory management, error handling, and Norm compliance. This identified the texture image leak, a CRLF stripping bug in the texture path parser, dead code in the header, and a duplicate dead branch in the keyrelease handler.
- **Runtime audit** — a second pass with execution permissions ran 30 crafted parser test cases (the `test_*.cub` files in `maps/`), validated all error paths against valgrind, and verified each first-pass fix held end-to-end.
- **Suppression file authoring** — helped us create the `mlx.supp` file based on standard X11/MLX leak signatures, with each suppression block documented for what it covers.

## License

This project is part of the 42 Common Core curriculum. See [LICENSE](LICENSE) for details.
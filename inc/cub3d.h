#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"

// Window
# define WINDOW_TITLE "cub3D"
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define TILE_SIZE 32

// Colors (0x00RRGGBB)
# define COLOR_WALL   0x808080
# define COLOR_FLOOR  0x222222
# define COLOR_SPACE  0x000000
# define COLOR_PLAYER 0xFF4500

// Movement
# define MOVE_SPEED 0.1
# define MOVE_TIMER 10
# define PLAYER_RADIUS 0.15

// Map characters
# define CHAR_WALL  '1'
# define CHAR_EMPTY '0'
# define CHAR_SPACE ' '
# define CHAR_NORTH 'N'
# define CHAR_SOUTH 'S'
# define CHAR_EAST  'E'
# define CHAR_WEST  'W'

// Texture index
typedef enum e_tex_id
{
	tex_no = 0,
	tex_so = 1,
	tex_we = 2,
	tex_ea = 3,
	tex_count = 4
}	t_tex_id;

typedef struct s_tex
{
	char	*path;
}	t_tex;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	char	spawn_dir;
}	t_player;

typedef struct s_img
{
	void	*ptr;
	char	*data;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_tex		tex[4];
	t_rgb		floor;
	t_rgb		ceiling;
	t_map		map;
	t_player	player;
	t_img		img;
	t_keys		keys;
}	t_game;

// parse_file.c
int		parse_cub_file(t_game *game, char *path);

// parse_elements.c
int		parse_header(t_game *game, char **lines, int map_start);
int		check_all_elements(t_game *game);

// parse_colors.c
int		parse_floor_color(t_game *game, char *str);
int		parse_ceil_color(t_game *game, char *str);

// parse_map.c
int		parse_map(t_game *game, char **lines, int start, int total);

// validate_map.c
int		validate_map(t_game *game);

// validate_enclosure.c
int		check_enclosure(t_game *game);

// window.c
int		init_window(t_game *game);
int		close_game(t_game *game);

// input.c
int		handle_keypress(int keysym, t_game *game);
int		handle_keyrelease(int keysym, t_game *game);

// game_loop.c
int		game_loop(t_game *game);

// render.c
void	render_frame(t_game *game);

// cleanup.c
void	free_game(t_game *game);
void	exit_game(t_game *game, int code);

#endif

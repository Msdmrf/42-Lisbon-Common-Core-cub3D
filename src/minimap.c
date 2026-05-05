#include "../inc/cub3d.h"

static int	get_tile_color(t_game *game, int tx, int ty)
{
	char	c;

	if (ty < 0 || ty >= game->map.height)
		return (0x111111);
	if (tx < 0 || tx >= game->map.width)
		return (0x111111);
	c = game->map.grid[ty][tx];
	if (c == CHAR_WALL)
		return (0xFFFFFF);
	if (c == CHAR_SPACE)
		return (0x111111);
	return (0x444444);
}

static void	draw_minimap_border(t_game *game)
{
	int	x;
	int	y;

	y = MINIMAP_Y - 2;
	while (y < MINIMAP_Y + MINIMAP_SIZE + 2)
	{
		x = MINIMAP_X - 2;
		while (x < MINIMAP_X + MINIMAP_SIZE + 2)
		{
			put_pixel(game, x, y, 0x222222);
			x++;
		}
		y++;
	}
}

static void	draw_minimap_player(t_game *g, double ts, double ox, double oy)
{
	int	px;
	int	py;
	int	x;
	int	y;
	int	radius;

	radius = 3;
	px = MINIMAP_X + (int)((g->player.pos_x - ox) * ts);
	py = MINIMAP_Y + (int)((g->player.pos_y - oy) * ts);
	y = py - radius;
	while (y <= py + radius)
	{
		x = px - radius;
		while (x <= px + radius)
		{
			if (x >= MINIMAP_X && x < MINIMAP_X + MINIMAP_SIZE
				&& y >= MINIMAP_Y && y < MINIMAP_Y + MINIMAP_SIZE)
				put_pixel(g, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
}

static void	draw_minimap_tiles(t_game *game, double tile_size, double ox,
				double oy)
{
	int	px;
	int	py;

	py = MINIMAP_Y;
	while (py < MINIMAP_Y + MINIMAP_SIZE)
	{
		px = MINIMAP_X;
		while (px < MINIMAP_X + MINIMAP_SIZE)
		{
			put_pixel(game, px, py,
				get_tile_color(game,
					(int)(ox + (double)(px - MINIMAP_X) / tile_size),
					(int)(oy + (double)(py - MINIMAP_Y) / tile_size)));
			px++;
		}
		py++;
	}
}

void	draw_minimap(t_game *game)
{
	double	tile_size;
	double	orig_x;
	double	orig_y;

	tile_size = (double)MINIMAP_SIZE / VIEWPORT_CELLS;
	orig_x = game->player.pos_x - VIEWPORT_CELLS / 2.0;
	orig_y = game->player.pos_y - VIEWPORT_CELLS / 2.0;
	if (orig_x > game->map.width - VIEWPORT_CELLS)
		orig_x = game->map.width - VIEWPORT_CELLS;
	if (orig_x < 0)
		orig_x = 0;
	if (orig_y > game->map.height - VIEWPORT_CELLS)
		orig_y = game->map.height - VIEWPORT_CELLS;
	if (orig_y < 0)
		orig_y = 0;
	draw_minimap_border(game);
	draw_minimap_tiles(game, tile_size, orig_x, orig_y);
	draw_minimap_player(game, tile_size, orig_x, orig_y);
}

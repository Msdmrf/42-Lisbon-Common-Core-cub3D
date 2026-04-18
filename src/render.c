#include "../inc/cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= game->map.width * TILE_SIZE
		|| y >= game->map.height * TILE_SIZE)
		return ;
	dst = game->img.data
		+ (y * game->img.line_len + x * (game->img.bpp / 8));
	*(unsigned int *)dst = color;
}

// static int	get_tile_color(t_game *game, int tx, int ty)
// {
// 	char	c;

// 	if (ty < 0 || ty >= game->map.height)
// 		return (COLOR_SPACE);
// 	if (tx < 0 || tx >= game->map.width)
// 		return (COLOR_SPACE);
// 	c = game->map.grid[ty][tx];
// 	if (c == CHAR_WALL)
// 		return (COLOR_WALL);
// 	if (c == CHAR_SPACE)
// 		return (COLOR_SPACE);
// 	return (COLOR_FLOOR);
// }

// static void	draw_tile(t_game *game, int tx, int ty, int color)
// {
// 	int	px;
// 	int	py;

// 	py = ty * TILE_SIZE;
// 	while (py < (ty + 1) * TILE_SIZE)
// 	{
// 		px = tx * TILE_SIZE;
// 		while (px < (tx + 1) * TILE_SIZE)
// 		{
// 			put_pixel(game, px, py, color);
// 			px++;
// 		}
// 		py++;
// 	}
// }

// static void	draw_player(t_game *game)
// {
// 	int	px;
// 	int	py;
// 	int	x;
// 	int	y;
// 	int	half;

// 	half = TILE_SIZE / 8;
// 	px = (int)(game->player.x * TILE_SIZE);
// 	py = (int)(game->player.y * TILE_SIZE);
// 	y = py - half;
// 	while (y <= py + half)
// 	{
// 		x = px - half;
// 		while (x <= px + half)
// 		{
// 			put_pixel(game, x, y, COLOR_PLAYER);
// 			x++;
// 		}
// 		y++;
// 	}
// }

void	render_frame(t_game *game)
{
	// int	tx;
	// int	ty;

	raycasting(game);

	// ty = 0;
	// while (ty < game->map.height)
	// {
	// 	tx = 0;
	// 	while (tx < game->map.width)
	// 	{
	// 		draw_tile(game, tx, ty, get_tile_color(game, tx, ty));
	// 		tx++;
	// 	}
	// 	ty++;
	// }
	// draw_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
}

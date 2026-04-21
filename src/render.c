/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notjustlaw <notjustlaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:47:19 by notjustlaw        #+#    #+#             */
/*   Updated: 2026/04/21 15:38:04 by notjustlaw       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT)
		return;
	dst = game->img.data
		+ (y * game->img.line_len + x * (game->img.bpp / 8));
	*(unsigned int *)dst = color;
}

static int	get_tile_color(t_game *game, int tx, int ty)
{
	char	c;

	if (ty < 0 || ty >= game->map.height)
		return (0x000000);
	if (tx < 0 || tx >= game->map.width)
		return (0x000000);
	c = game->map.grid[ty][tx];
	if (c == CHAR_WALL)
		return (0xFFFFFF);
	if (c == CHAR_SPACE)
		return (0x000000);
	return (0x444444);
}

static void	draw_minimap_tile(t_game *game, int tx, int ty, int color, double tile_size)
{
	int	px;
	int	py;
	int	screen_x;
	int	screen_y;
	int	tile_size_int;

	tile_size_int = (int)tile_size;
	screen_x = MINIMAP_X + (int)(tx * tile_size);
	screen_y = MINIMAP_Y + (int)(ty * tile_size);
	if (screen_x < MINIMAP_X || screen_x >= MINIMAP_X + MINIMAP_SIZE)
		return;
	if (screen_y < MINIMAP_Y || screen_y >= MINIMAP_Y + MINIMAP_SIZE)
		return;
	py = screen_y;
	while (py < screen_y + tile_size_int && py < MINIMAP_Y + MINIMAP_SIZE)
	{
		px = screen_x;
		while (px < screen_x + tile_size_int && px < MINIMAP_X + MINIMAP_SIZE)
		{
			put_pixel(game, px, py, color);
			px++;
		}
		py++;
	}
}

static void	draw_minimap_player(t_game *game, double tile_size)
{
	int	px;
	int	py;
	int	x;
	int	y;
	int	radius;

	radius = 3;
	px = MINIMAP_X + (int)(game->player.x * tile_size);
	py = MINIMAP_Y + (int)(game->player.y * tile_size);
	
	y = py - radius;
	while (y <= py + radius)
	{
		x = px - radius;
		while (x <= px + radius)
		{
			if (x >= MINIMAP_X && x < MINIMAP_X + MINIMAP_SIZE
				&& y >= MINIMAP_Y && y < MINIMAP_Y + MINIMAP_SIZE)
				put_pixel(game, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
}

static void	draw_minimap(t_game *game)
{
	int		tx;
	int		ty;
	double	tile_size_x;
	double	tile_size_y;
	double	tile_size;

	tile_size_x = (double)MINIMAP_SIZE / game->map.width;
	tile_size_y = (double)MINIMAP_SIZE / game->map.height;
	tile_size = tile_size_x < tile_size_y ? tile_size_x : tile_size_y;
	ty = MINIMAP_Y - 2;
	while (ty < MINIMAP_Y + MINIMAP_SIZE + 2)
	{
		tx = MINIMAP_X - 2;
		while (tx < MINIMAP_X + MINIMAP_SIZE + 2)
		{
			put_pixel(game, tx, ty, 0x222222);
			tx++;
		}
		ty++;
	}
	ty = -1;
	while (++ty < game->map.height)
	{
		tx = 0;
		while (tx < game->map.width)
		{
			draw_minimap_tile(game, tx, ty, get_tile_color(game, tx, ty), tile_size);
			tx++;
		}
	}
	draw_minimap_player(game, tile_size);
}

void	render_frame(t_game *game)
{
	ft_memset(game->img.data, 0, 
		WINDOW_HEIGHT * game->img.line_len);
	raycasting(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
}

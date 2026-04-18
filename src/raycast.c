/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justlaw <justlaw@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */

/*   Created: 2026/04/17 10:44:00 by justlaw           #+#    #+#             */
/*   Updated: 2026/04/17 12:39:42 by justlaw          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	is_wall(t_game *game, double x, double y)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)x;
	grid_y = (int)y;
	if (grid_x < 0 || grid_y >= game->map.width)
		return (1);
	if (grid_y < 0 || grid_x >= game->map.height)
		return (1);
	return (game->map.grid[grid_y][grid_x] == CHAR_WALL);
}

static double	cast_single_ray(t_game *game, double angle)
{
	double	x;
	double	y;
	double	distance;

	x = game->player.x;
	y = game->player.y;
	distance = 0;
	while (!is_wall(game, x, y))
	{
		x += cos(angle) * RAY_STEP;
		y += sin(angle) * RAY_STEP;
		distance += RAY_STEP;
	}
	return (distance);
}

static void	draw_column(t_game *game, int x, double distance)
{
	int	line_height;
	int	y;
	int	top;
	int	color;

	if (distance < 0.1)
		distance = 0.1;
	line_height = (int)(500 / distance);
	if (line_height > WINDOW_HEIGHT)
		line_height = WINDOW_HEIGHT;
	top = (WINDOW_HEIGHT - line_height) / 2;
	
	// Use darker/lighter colors based on distance
	if (distance < 2)
		color = 0xFF0000;  // Red (close)
	else if (distance < 3)
		color = 0x00FF00;  // Green (medium)
	else if (distance < 4)
		color = 0x0000FF;  // Blue (far)
	else
		color = 0xFFFFFF;  // White (very far)
	
	y = top;
	while (y < top + line_height)
	{
		put_pixel(game, x, y, color);
		y++;
	}
}

void	raycasting(t_game *game)
{
	int		x;
	double	ray_angle;
	double	distance;

	// DEBUG
	// printf("Player: x=%.2f, y=%.2f, angle=%.2f\n", 
	// 	game->player.x, game->player.y, game->player.angle);
	// printf("Map: width=%d, height=%d\n", 
	// 	game->map.width, game->map.height);
	
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		ray_angle = calculate_ray_angle(game, x);
		distance = cast_single_ray(game, ray_angle);
		if (x % 100 == 0)  // Print every 100th ray
			printf("Ray at x=%d: angle=%.2f, distance=%.2f\n", 
				x, ray_angle, distance);
		draw_column(game, x, distance);
		x++;
	}
}

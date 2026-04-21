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
	if (grid_x < 0 || grid_y >= game->map.height)
		return (1);
	if (grid_y < 0 || grid_x >= game->map.width)
		return (1);
	return (game->map.grid[grid_y][grid_x] == CHAR_WALL);
}

static t_raycast_result	cast_single_ray(t_game *game, double angle)
{
	double				x;
	double				y;
	double				distance;
	t_raycast_result	result;

	x = game->player.x;
	y = game->player.y;
	distance = 0;
	while (!is_wall(game, x, y))
	{
		x += cos(angle) * RAY_STEP;
		y += sin(angle) * RAY_STEP;
		distance += RAY_STEP;
	}
	x -= cos(angle) * RAY_STEP;
	y -= sin(angle) * RAY_STEP;
	distance -= RAY_STEP;
	while (!is_wall(game, x, y))
	{
		x += cos(angle) * RAY_STEP * 0.1;
		y += sin(angle) * RAY_STEP * 0.1;
		distance += RAY_STEP * 0.1;
	}
	result.distance = distance;
	result.hit_x = x;
	result.hit_y = y;
	return (result);
}

static void	draw_column(t_game *game, int x, double distance, double ray_angle, double hit_x, double hit_y)
{
	int		line_height;
	int		y;
	int		top;
	int		color;
	double	corrected_distance;
	int		wall_dir;
	int		u;
	int		v;
	double	epsilon;
	
	corrected_distance = distance * cos(ray_angle - game->player.angle);
	if (corrected_distance < 0.1)
		corrected_distance = 0.1;
	line_height = (int)(500 / corrected_distance);
	if (line_height > WINDOW_HEIGHT)
		line_height = WINDOW_HEIGHT;
	top = (WINDOW_HEIGHT - line_height) / 2;
	wall_dir = get_wall_direction(hit_x, hit_y);
	epsilon = 0.001;
	y = 0;
	while (y < top)
	{
		put_pixel(game, x, y, (game->ceiling.r << 16) | (game->ceiling.g << 8) | game->ceiling.b);
		y++;
	}
	y = top;
	while (y < top + line_height)
	{
		v = ((y - top) * game->tex[wall_dir].height) / line_height;
		if (v >= game->tex[wall_dir].height)
			v = game->tex[wall_dir].height - 1;
		
		if (wall_dir == tex_no || wall_dir == tex_so)
		{
			u = (int)(((hit_x - (int)hit_x) + epsilon) * game->tex[wall_dir].width);
		}
		else
		{
			u = (int)(((hit_y - (int)hit_y) + epsilon) * game->tex[wall_dir].width);
		}
		
		if (u < 0)
			u = 0;
		if (u >= game->tex[wall_dir].width)
			u = game->tex[wall_dir].width - 1;
		
		color = get_texture_pixel(game, wall_dir, u, v);
		put_pixel(game, x, y, color);
		y++;
	}
	y = top + line_height;
	while (y < WINDOW_HEIGHT)
	{
		put_pixel(game, x, y, (game->floor.r << 16) | (game->floor.g << 8) | game->floor.b);
		y++;
	}
}

void	raycasting(t_game *game)
{
	int					x;
	double				ray_angle;
	t_raycast_result	result;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		ray_angle = calculate_ray_angle(game, x);
		result = cast_single_ray(game, ray_angle);
		draw_column(game, x, result.distance, ray_angle, result.hit_x, result.hit_y);
		x++;
	}
}

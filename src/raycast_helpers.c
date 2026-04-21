/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notjustlaw <notjustlaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 12:42:05 by justlaw           #+#    #+#             */
/*   Updated: 2026/04/21 15:37:08 by notjustlaw       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/// @brief For each pixel column x on the screen, calculate what angle the ray should go
/// @param game 
/// @param x 
/// @return 
double	calculate_ray_angle(t_game *game, double x)
{
	return (game->player.angle - (FOV/2) + (x / WINDOW_WIDTH) * FOV);
}

int	get_texture_pixel(t_game *game, int tex_id, int u, int v)
{
	char	*pixel;
	int		x;
	int		y;

	if (tex_id < 0 || tex_id >= tex_count)
		return (0xFF0000);
	if (!game->tex[tex_id].data)
		return (0xFF0000);
	x = u % game->tex[tex_id].width;
	y = v % game->tex[tex_id].height;
	if (x < 0)
		x += game->tex[tex_id].width;
	if (y < 0)
		y += game->tex[tex_id].height;
	pixel = game->tex[tex_id].data + 
		(y * game->tex[tex_id].line_len + x * (game->tex[tex_id].bpp / 8));
	return (*(unsigned int *)pixel);
}

int	get_wall_direction(double hit_x, double hit_y)
{
	int		grid_x;
	int		grid_y;
	double	frac_x;
	double	frac_y;

	grid_x = (int)hit_x;
	grid_y = (int)hit_y;
	frac_x = hit_x - grid_x;
	frac_y = hit_y - grid_y;
	double dist_left = frac_x;
	double dist_right = 1.0 - frac_x;
	double dist_top = frac_y;
	double dist_bottom = 1.0 - frac_y;
	double min_dist = dist_left;
	int result = tex_we;
	if (dist_right < min_dist)
	{
		min_dist = dist_right;
		result = tex_ea;
	}
	if (dist_top < min_dist)
	{
		min_dist = dist_top;
		result = tex_no;
	}
	if (dist_bottom < min_dist)
		result = tex_so;
	return result;
}

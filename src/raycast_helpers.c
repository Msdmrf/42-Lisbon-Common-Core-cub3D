/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justlaw <justlaw@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 12:42:05 by justlaw           #+#    #+#             */
/*   Updated: 2026/04/17 12:49:52 by justlaw          ###   ########.fr       */
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
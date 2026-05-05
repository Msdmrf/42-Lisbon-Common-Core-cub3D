/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 09:06:01 by migusant          #+#    #+#             */
/*   Updated: 2026/05/05 16:03:16 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_vectors_ew(t_player *player, double mag)
{
	if (player->spawn_dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = mag;
	}
	else if (player->spawn_dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -mag;
	}
}

static void	init_vectors_ns(t_player *player, double mag)
{
	if (player->spawn_dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -mag;
		player->plane_y = 0;
	}
	else if (player->spawn_dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = mag;
		player->plane_y = 0;
	}
}

void	init_player_vectors(t_player *player)
{
	static const double	mag = 0.5773502691896257;

	if (player->spawn_dir == 'E' || player->spawn_dir == 'W')
		init_vectors_ew(player, mag);
	else
		init_vectors_ns(player, mag);
}

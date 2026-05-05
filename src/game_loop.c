/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:16:07 by migusant          #+#    #+#             */
/*   Updated: 2026/05/05 15:47:16 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	compute_move(t_game *game, double *mx, double *my)
{
	*mx = 0;
	*my = 0;
	if (game->keys.w)
	{
		*mx += game->player.dir_x * MOVE_SPEED;
		*my += game->player.dir_y * MOVE_SPEED;
	}
	if (game->keys.s)
	{
		*mx -= game->player.dir_x * MOVE_SPEED;
		*my -= game->player.dir_y * MOVE_SPEED;
	}
	if (game->keys.a)
	{
		*mx += game->player.dir_y * MOVE_SPEED;
		*my -= game->player.dir_x * MOVE_SPEED;
	}
	if (game->keys.d)
	{
		*mx -= game->player.dir_y * MOVE_SPEED;
		*my += game->player.dir_x * MOVE_SPEED;
	}
}

static void	rotate_player(t_game *game)
{
	double	cos_t;
	double	sin_t;
	double	old_x;

	if (!game->keys.right && !game->keys.left)
		return ;
	if (game->keys.right && game->keys.left)
		return ;
	cos_t = cos(ROT_SPEED);
	sin_t = sin(ROT_SPEED);
	if (!game->keys.right)
		sin_t = -sin_t;
	old_x = game->player.dir_x;
	game->player.dir_x = old_x * cos_t - game->player.dir_y * sin_t;
	game->player.dir_y = old_x * sin_t + game->player.dir_y * cos_t;
	old_x = game->player.plane_x;
	game->player.plane_x = old_x * cos_t - game->player.plane_y * sin_t;
	game->player.plane_y = old_x * sin_t + game->player.plane_y * cos_t;
}

static void	move_player(t_game *game)
{
	double	nx;
	double	ny;
	double	move_x;
	double	move_y;

	nx = game->player.pos_x;
	ny = game->player.pos_y;
	compute_move(game, &move_x, &move_y);
	if (can_move(game, nx + move_x, ny + move_y))
	{
		game->player.pos_x += move_x;
		game->player.pos_y += move_y;
	}
	else if (can_move(game, nx + move_x, ny))
		game->player.pos_x += move_x;
	else if (can_move(game, nx, ny + move_y))
		game->player.pos_y += move_y;
}

int	game_loop(t_game *game)
{
	rotate_player(game);
	move_player(game);
	render_frame(game);
	return (0);
}

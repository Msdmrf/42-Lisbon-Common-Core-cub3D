/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:15:06 by migusant          #+#    #+#             */
/*   Updated: 2026/05/05 15:47:36 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	handle_keypress(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		close_game(game);
	if (keysym == XK_w || keysym == XK_W)
		game->keys.w = 1;
	if (keysym == XK_a || keysym == XK_A)
		game->keys.a = 1;
	if (keysym == XK_s || keysym == XK_S)
		game->keys.s = 1;
	if (keysym == XK_d || keysym == XK_D)
		game->keys.d = 1;
	if (keysym == XK_Left)
		game->keys.left = 1;
	if (keysym == XK_Right)
		game->keys.right = 1;
	return (0);
}

int	handle_keyrelease(int keysym, t_game *game)
{
	if (keysym == XK_w || keysym == XK_W)
		game->keys.w = 0;
	if (keysym == XK_a || keysym == XK_A)
		game->keys.a = 0;
	if (keysym == XK_s || keysym == XK_S)
		game->keys.s = 0;
	if (keysym == XK_d || keysym == XK_D)
		game->keys.d = 0;
	if (keysym == XK_Left)
		game->keys.left = 0;
	if (keysym == XK_Right)
		game->keys.right = 0;
	return (0);
}

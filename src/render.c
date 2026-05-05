/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:05:35 by migusant          #+#    #+#             */
/*   Updated: 2026/05/05 15:50:43 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT)
		return ;
	dst = game->img.data
		+ (y * game->img.line_len + x * (game->img.bpp / 8));
	*(unsigned int *)dst = color;
}

void	render_frame(t_game *game)
{
	raycasting(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
}

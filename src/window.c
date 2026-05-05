/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:04:29 by migusant          #+#    #+#             */
/*   Updated: 2026/05/05 15:53:13 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	load_textures(t_game *game, int tex_id)
{
	int	width;
	int	height;

	if (!game->tex[tex_id].path)
		return (1);
	width = 0;
	height = 0;
	game->tex[tex_id].img = mlx_xpm_file_to_image(game->mlx,
			game->tex[tex_id].path, &width, &height);
	if (!game->tex[tex_id].img)
		return (ft_putendl_fd("Error\nFailed to load texture.", 2), 0);
	game->tex[tex_id].data = mlx_get_data_addr(game->tex[tex_id].img,
			&game->tex[tex_id].bpp, &game->tex[tex_id].line_len,
			&game->tex[tex_id].endian);
	game->tex[tex_id].width = width;
	game->tex[tex_id].height = height;
	return (1);
}

static int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_putendl_fd("Error\nMLX init failed.", 2), 0);
	game->win = mlx_new_window(game->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	if (!game->win)
		return (ft_putendl_fd("Error\nWindow creation failed.", 2), 0);
	return (1);
}

static int	init_img(t_game *game)
{
	game->img.ptr = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img.ptr)
		return (ft_putendl_fd("Error\nImage creation failed.", 2), 0);
	game->img.data = mlx_get_data_addr(game->img.ptr, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	return (1);
}

int	init_window(t_game *game)
{
	if (!init_mlx(game))
		return (0);
	if (!init_img(game))
		return (0);
	if (!load_textures(game, tex_NO))
		return (0);
	if (!load_textures(game, tex_SO))
		return (0);
	if (!load_textures(game, tex_WE))
		return (0);
	if (!load_textures(game, tex_EA))
		return (0);
	return (1);
}

int	close_game(t_game *game)
{
	exit_game(game, 0);
	return (0);
}

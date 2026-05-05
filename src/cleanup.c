/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:16:53 by migusant          #+#    #+#             */
/*   Updated: 2026/05/05 15:46:57 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	free_map_grid(t_game *game)
{
	int	i;

	if (!game->map.grid)
		return ;
	i = 0;
	while (i < game->map.height)
	{
		free(game->map.grid[i]);
		i++;
	}
	free(game->map.grid);
	game->map.grid = NULL;
}

static void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < tex_count)
	{
		if (game->tex[i].path)
		{
			free(game->tex[i].path);
			game->tex[i].path = NULL;
		}
		i++;
	}
}

void	free_lines(char **lines, int count)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (i < count && lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

void	free_game(t_game *game)
{
	free_map_grid(game);
	free_textures(game);
}

void	exit_game(t_game *game, int code)
{
	int	i;

	i = 0;
	while (i < tex_count)
	{
		if (game->tex[i].img)
		{
			mlx_destroy_image(game->mlx, game->tex[i].img);
			game->tex[i].img = NULL;
		}
		i++;
	}
	if (game->img.ptr)
		mlx_destroy_image(game->mlx, game->img.ptr);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_game(game);
	exit(code);
}

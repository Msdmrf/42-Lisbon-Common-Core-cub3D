/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_enclosure.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 11:02:49 by migusant          #+#    #+#             */
/*   Updated: 2026/05/05 15:51:10 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	is_walkable(char c)
{
	return (c == CHAR_EMPTY || c == CHAR_NORTH || c == CHAR_SOUTH
		|| c == CHAR_EAST || c == CHAR_WEST);
}

static int	is_valid_neighbor(t_game *game, int x, int y)
{
	int	row_len;

	if (y < 0 || y >= game->map.height)
		return (0);
	row_len = (int)ft_strlen(game->map.grid[y]);
	if (x < 0 || x >= row_len)
		return (0);
	if (game->map.grid[y][x] == CHAR_SPACE)
		return (0);
	return (1);
}

static int	check_cell(t_game *game, int x, int y)
{
	if (!is_valid_neighbor(game, x, y - 1))
		return (0);
	if (!is_valid_neighbor(game, x, y + 1))
		return (0);
	if (!is_valid_neighbor(game, x - 1, y))
		return (0);
	if (!is_valid_neighbor(game, x + 1, y))
		return (0);
	return (1);
}

static int	check_row(t_game *game, int y)
{
	int	x;

	x = 0;
	while (game->map.grid[y][x])
	{
		if (is_walkable(game->map.grid[y][x]) && !check_cell(game, x, y))
		{
			ft_putendl_fd("Error", 2);
			ft_putendl_fd("Map is not properly enclosed by walls.", 2);
			return (0);
		}
		x++;
	}
	return (1);
}

int	check_enclosure(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		if (!check_row(game, y))
			return (0);
		y++;
	}
	return (1);
}

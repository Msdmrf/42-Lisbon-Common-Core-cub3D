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

void	free_game(t_game *game)
{
	free_map_grid(game);
	free_textures(game);
}

void	exit_game(t_game *game, int code)
{
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

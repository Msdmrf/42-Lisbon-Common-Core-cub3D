#include "../inc/cub3d.h"

int	is_wall(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0)
		return (1);
	if (map_y >= game->map.height || map_x >= game->map.width)
		return (1);
	return (game->map.grid[map_y][map_x] == CHAR_WALL
		|| game->map.grid[map_y][map_x] == CHAR_SPACE);
}

int	get_wall_tex(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (tex_EA);
		return (tex_WE);
	}
	if (ray->step_y > 0)
		return (tex_SO);
	return (tex_NO);
}

static void	init_ray(t_ray *ray, t_game *game, int screen_x)
{
	init_ray_dir(ray, game, screen_x);
	init_dda_x(ray, game);
	init_dda_y(ray, game);
}

void	raycasting(t_game *game)
{
	int		x;
	t_ray	ray;

	fill_background(game);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray(&ray, game, x);
		cast_dda_ray(&ray, game);
		finish_ray(&ray, &game->player);
		draw_column(game, x, &ray);
		x++;
	}
}

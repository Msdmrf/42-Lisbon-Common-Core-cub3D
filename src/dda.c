#include "../inc/cub3d.h"

void	init_ray_dir(t_ray *ray, t_game *game, int screen_x)
{
	double	camera_x;

	camera_x = 2.0 * screen_x / WINDOW_WIDTH - 1.0;
	ray->dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
}

void	init_dda_x(t_ray *ray, t_game *game)
{
	if (ray->dir_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (game->player.pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - game->player.pos_x) * ray->delta_x;
	}
}

void	init_dda_y(t_ray *ray, t_game *game)
{
	if (ray->dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1.0 / ray->dir_y);
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (game->player.pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - game->player.pos_y) * ray->delta_y;
	}
}

void	cast_dda_ray(t_ray *ray, t_game *game)
{
	while (!is_wall(game, ray->map_x, ray->map_y))
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
	}
}

void	finish_ray(t_ray *ray, t_player *p)
{
	if (ray->side == 0)
	{
		ray->wall_dist = ray->side_x - ray->delta_x;
		ray->wall_hit = p->pos_y + ray->wall_dist * ray->dir_y;
	}
	else
	{
		ray->wall_dist = ray->side_y - ray->delta_y;
		ray->wall_hit = p->pos_x + ray->wall_dist * ray->dir_x;
	}
	ray->wall_hit -= (int)ray->wall_hit;
}

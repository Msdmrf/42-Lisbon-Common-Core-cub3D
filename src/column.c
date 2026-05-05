#include "../inc/cub3d.h"

static void	fill_row_color(char *dst, int pixel_count, int color)
{
	unsigned int	*ptr;
	unsigned int	*end;

	ptr = (unsigned int *)dst;
	end = ptr + pixel_count;
	while (ptr < end)
	{
		*ptr = (unsigned int)color;
		ptr++;
	}
}

void	fill_background(t_game *game)
{
	int		y;
	int		ceil_c;
	int		floor_c;
	char	*row;

	ceil_c = (game->ceiling.r << 16) | (game->ceiling.g << 8)
		| game->ceiling.b;
	floor_c = (game->floor.r << 16) | (game->floor.g << 8) | game->floor.b;
	y = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		row = game->img.data + y * game->img.line_len;
		fill_row_color(row, WINDOW_WIDTH, ceil_c);
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		row = game->img.data + y * game->img.line_len;
		fill_row_color(row, WINDOW_WIDTH, floor_c);
		y++;
	}
}

static int	get_tex_u(t_ray *ray, t_tex *tex)
{
	int	u;

	u = (int)(ray->wall_hit * tex->width);
	if (u < 0)
		u = 0;
	if (u >= tex->width)
		u = tex->width - 1;
	if ((ray->side == 0 && ray->step_x > 0)
		|| (ray->side == 1 && ray->step_y < 0))
		u = tex->width - 1 - u;
	return (u);
}

void	draw_wall_strip(t_game *game, int x, t_ray *ray, int seg[3])
{
	int	y;
	int	v;
	int	u;
	int	color;
	int	tex_id;

	tex_id = get_wall_tex(ray);
	u = get_tex_u(ray, &game->tex[tex_id]);
	y = seg[0];
	while (y < seg[1])
	{
		v = ((y - (WINDOW_HEIGHT - seg[2]) / 2) * game->tex[tex_id].height)
			/ seg[2];
		if (v >= game->tex[tex_id].height)
			v = game->tex[tex_id].height - 1;
		color = get_texture_pixel(game, tex_id, u, v);
		put_pixel(game, x, y, color);
		y++;
	}
}

void	draw_column(t_game *game, int x, t_ray *ray)
{
	int	line_height;
	int	seg[3];

	if (ray->wall_dist < 0.001)
		ray->wall_dist = 0.001;
	line_height = (int)(WINDOW_HEIGHT / ray->wall_dist);
	seg[0] = (WINDOW_HEIGHT - line_height) / 2;
	seg[1] = seg[0] + line_height;
	seg[2] = line_height;
	if (seg[0] < 0)
		seg[0] = 0;
	if (seg[1] > WINDOW_HEIGHT)
		seg[1] = WINDOW_HEIGHT;
	draw_wall_strip(game, x, ray, seg);
}

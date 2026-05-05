#include "../inc/cub3d.h"

int	get_texture_pixel(t_game *game, int tex_id, int u, int v)
{
	char	*pixel;
	int		x;
	int		y;

	if (tex_id < 0 || tex_id >= tex_count)
		return (0xFF0000);
	if (!game->tex[tex_id].data)
		return (0xFF0000);
	x = u % game->tex[tex_id].width;
	y = v % game->tex[tex_id].height;
	if (x < 0)
		x += game->tex[tex_id].width;
	if (y < 0)
		y += game->tex[tex_id].height;
	pixel = game->tex[tex_id].data
		+ (y * game->tex[tex_id].line_len + x * (game->tex[tex_id].bpp / 8));
	return (*(unsigned int *)pixel);
}

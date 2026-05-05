/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 09:37:17 by migusant          #+#    #+#             */
/*   Updated: 2026/05/05 15:46:26 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"

//Math.h
# define M_PI 3.14159265358979323846

// Window
# define WINDOW_TITLE "cub3D"
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

//Minimap
# define MINIMAP_SIZE 150
# define MINIMAP_PADDING 10
# define MINIMAP_X 1120
# define MINIMAP_Y MINIMAP_PADDING
# define VIEWPORT_CELLS 5

// Movement
# define MOVE_SPEED 0.01
# define PLAYER_RADIUS 0.15
# define ROT_SPEED 0.05

// Map characters
# define CHAR_WALL  '1'
# define CHAR_EMPTY '0'
# define CHAR_SPACE ' '
# define CHAR_NORTH 'N'
# define CHAR_SOUTH 'S'
# define CHAR_EAST  'E'
# define CHAR_WEST  'W'

// Texture index
typedef enum e_tex_id
{
	tex_NO = 0,
	tex_SO = 1,
	tex_WE = 2,
	tex_EA = 3,
	tex_count = 4
}	t_tex_id;

typedef struct s_tex
{
	char	*path;
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_tex;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	spawn_dir;
}	t_player;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	int		step_x;
	int		step_y;
	int		side;
	double	wall_dist;
	double	wall_hit;
}	t_ray;

typedef struct s_img
{
	void	*ptr;
	char	*data;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_tex		tex[4];
	t_rgb		floor;
	t_rgb		ceiling;
	t_map		map;
	t_player	player;
	t_img		img;
	t_keys		keys;
}	t_game;

// parse_file.c
int		parse_cub_file(t_game *game, char *path);

// parse_elements.c
int		parse_header(t_game *game, char **lines, int map_start);
int		check_all_elements(t_game *game);

// parse_colors.c
int		parse_floor_color(t_game *game, char *str);
int		parse_ceil_color(t_game *game, char *str);

// parse_map.c
int		parse_map(t_game *game, char **lines, int start, int total);

// validate_map.c
int		validate_map(t_game *game);

// validate_map_helpers.c
void	init_player_vectors(t_player *player);

// validate_enclosure.c
int		check_enclosure(t_game *game);

// window.c
int		init_window(t_game *game);
int		close_game(t_game *game);

// input.c
int		handle_keypress(int keysym, t_game *game);
int		handle_keyrelease(int keysym, t_game *game);

// game_loop.c
int		game_loop(t_game *game);

// render.c
void	render_frame(t_game *game);

void	put_pixel(t_game *game, int x, int y, int color);

// raycast.c
int		is_wall(t_game *game, int map_x, int map_y);
int		get_wall_tex(t_ray *ray);
void	raycasting(t_game *game);

// dda.c
void	init_ray_dir(t_ray *ray, t_game *game, int screen_x);
void	init_dda_x(t_ray *ray, t_game *game);
void	init_dda_y(t_ray *ray, t_game *game);
void	cast_dda_ray(t_ray *ray, t_game *game);
void	finish_ray(t_ray *ray, t_player *p);

// column.c
void	fill_background(t_game *game);
void	draw_wall_strip(t_game *game, int x, t_ray *ray, int seg[3]);
void	draw_column(t_game *game, int x, t_ray *ray);

// raycast_helpers.c
int		get_texture_pixel(t_game *game, int tex_id, int u, int v);

// cleanup.c
void	free_game(t_game *game);
void	free_lines(char **lines, int count);
void	exit_game(t_game *game, int code);

// collision.c
int		can_move(t_game *game, double nx, double ny);

// minimap.c
void	draw_minimap(t_game *game);

#endif

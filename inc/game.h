/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:57:12 by seunlee2          #+#    #+#             */
/*   Updated: 2023/12/17 04:54:48 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

# include "../libft/libft.h"
# include "../mlx/mlx.h"

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17

# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define SCREENWIDTH 960
# define SCREENHEIGHT 720
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define WALLDIST 1.1

typedef struct s_move
{
	int	key_w;
	int	key_s;
	int	key_a;
	int	key_d;
	int	key_l;
	int	key_r;
}	t_move;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
	t_move	move;
}	t_player;

typedef struct s_ray
{
	double	camera;
	int		map_x;
	int		map_y;
	double	raydir_x;
	double	raydir_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perpwalldist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	wall;
	int		tex_x;
	int		tex_y;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	step;
	double	tex_pos;
}	t_ray;

typedef struct s_img
{
	void		*image;
	int			*data;
	int			bpp;
	int			line_size;
	int			endian;
	int			w;
	int			h;
	int			**texture;
}	t_img;

typedef struct s_mapinfo
{
	int			**matrix;
	char		**info;
	char		dir_ch;
	int			width;
	int			height;
	int			floor;
	int			ceiling;
}	t_mapinfo;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_ray		r;
	t_player	p;
	t_img		img;
	t_mapinfo	map;
}	t_game;

void	error_handler(char *message, int status);

void	init_game(t_game *game, t_img *img);
void	init_player(t_game *game, t_player *p);
void	set_player_dir_plain(t_game *game, t_player *p);
void	init_img(t_img *img);
void	init_img_more(t_img *img);
void	fill_texture(t_img *img, int idx);
void	set_wall_img(t_game *game, t_img *img, t_mapinfo *map, int idx);

int		game_loop(t_game *game);
void	set_floor(t_game *game);
void	raycasting(t_game *game);

void	key_hook_w(t_player *p, t_mapinfo *map);
void	key_hook_s(t_player *p, t_mapinfo *map);
void	key_hook_a(t_player *p, t_mapinfo *map);
void	key_hook_d(t_player *p, t_mapinfo *map);
void	key_hook_l(t_player *p);
void	key_hook_r(t_player *p);
void	key_hook(t_game *game);

int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		key_exit(t_game *game);

void	init_ray( t_ray *r, t_player *p, int x);
void	step_sidedist(t_ray *r, t_player *p);
void	dda(t_game *game);
void	perpwalldist_line_height(t_ray *r, t_player *p);
void	texture(t_ray *r, t_player *p);
void	draw(t_ray *r, t_img *img, int x);
#endif
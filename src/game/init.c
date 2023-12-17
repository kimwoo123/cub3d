/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:42:57 by seunlee2          #+#    #+#             */
/*   Updated: 2023/12/17 08:13:02 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	init_img_more(t_img *img)
{
	int	i;

	img->texture = (int **)malloc(sizeof(int *) * 4);
	if (!(img->texture))
		error_handler("malloc error", 1);
	i = 0;
	while (i < 4)
	{
		img->texture[i] = (int *)malloc(sizeof(int) * TEXHEIGHT * TEXWIDTH);
		if (!img->texture[i])
			return ;
		ft_memset(img->texture[i], 0, (sizeof(int) * TEXHEIGHT * TEXWIDTH));
		i++;
	}
}

void	init_img(t_img *img)
{
	img->image = NULL;
	img->data = NULL;
	img->bpp = 0;
	img->line_size = 0;
	img->endian = 0;
	img->w = 0;
	img->h = 0;
	init_img_more(img);
}

void	set_player_dir_plain(t_game *game, t_player *p)
{
	p->dir_x = 0;
	p->dir_y = 0;
	p->plane_x = 0;
	p->plane_y = 0;
	if (game->map.dir_ch == 'E')
	{
		p->dir_x = 1;
		p->plane_y = 0.66;
	}
	else if (game->map.dir_ch == 'W')
	{
		p->dir_x = -1;
		p->plane_y = -0.66;
	}
	else if (game->map.dir_ch == 'S')
	{
		p->dir_y = 1;
		p->plane_x = -0.66;
	}
	else if (game->map.dir_ch == 'N')
	{
		p->dir_y = -1;
		p->plane_x = 0.66;
	}
}

void	init_player(t_game *game, t_player *p)
{
	p->dir_x = 0;
	p->dir_y = 0;
	p->plane_x = 0;
	p->plane_y = 0;
	set_player_dir_plain(game, &game->p);
	p->move.key_w = 0;
	p->move.key_s = 0;
	p->move.key_a = 0;
	p->move.key_d = 0;
	p->move.key_l = 0;
	p->move.key_r = 0;
	p->move_speed = 0.10;
	p->rot_speed = 0.05;
}

void	init_game(t_game *game, t_img *img)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_handler("mlx init error", 1);
	game->win = mlx_new_window(game->mlx, SCREENWIDTH, SCREENHEIGHT, "cub3D");
	if (!game->win)
		error_handler("make mlx window error", 1);
	init_img(&game->img);
	init_player(game, &game->p);
	set_wall_img(game, &game->img, &game->map, 0);
	img->image = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
	if (!img->image)
		error_handler("make mlx image error", 1);
	img->data = (int *)mlx_get_data_addr \
		(img->image, &img->bpp, &img->line_size, &img->endian);
	if (!img->data)
		error_handler("get mlx data error", 1);
}

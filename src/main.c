/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 16:11:38 by wooseoki          #+#    #+#             */
/*   Updated: 2023/12/10 23:02:14 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int main(int argc, char **argv)
{
	t_map	map;

	ft_bzero(&map, sizeof(map));
	if (argc != 2)
	{
		printf("usage: ./cub3D [map file]\n");
		return (1);
	}
	init_map(&map, argv[1]);
}

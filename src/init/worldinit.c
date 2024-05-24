/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worldinit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:06:35 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/24 17:51:18 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_world	*worldinit(char *file_name)
{
	t_world	*world;

	world = (t_world *)malloc(sizeof(t_world));
	if (!world)
	{
		ft_error(NULL, strerror(errno));
	}
	world->map = NULL;
	world->mlx = NULL;
	world->pics = NULL;
	world->color = NULL;
	world->map = readificator(world, file_name);
	parsingator(world);
	world->mlx = mlxator(world);
	world->pics = texturificator(world, world->mlx, world->map);
	world->color = colorificator(world, world->map);
	if (!world->map || !world->mlx || !world->pics || !world->color)
	{
		ft_error(world, "Initialisation Error");
	}
	return (world);
}

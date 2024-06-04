/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:58:55 by rshay             #+#    #+#             */
/*   Updated: 2024/06/04 14:01:53 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"
#include <sys/types.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->l + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_rays(t_rays *rays, t_world *world)
{
	rays->width = world->map->len;
	rays->height = world->map->lig;
	rays->c_color = world->color->ceiling;
	rays->f_color = world->color->floor;
	rays->pos_x = world->map->player_x;
	rays->pos_y = world->map->player_y;
	rays->dir_x = -1;
	rays->dir_y = 0;
	rays->plane_x = 0;
	rays->plane_y = 0.66;
	rays->move_speed = 0;
	rays->time = 0;
	rays->old_time = 0;
	rays->world_map = world->map->i_map;
}

void	init_alloc(t_rays *rays, t_world *world)
{
	u_int32_t	**buffer;
	int			i;
	size_t		j;

	buffer = malloc(SCREENHEIGHT * sizeof(int *));
	i = 0;
	while (i < SCREENHEIGHT)
	{
		buffer[i] = malloc(SCREENWIDTH * sizeof(int));
		i++;
	}
	rays->buffer = buffer;
	init_rays(rays, world);
	i = 0;
	while (i < world->map->lig)
	{
		j = 0;
		while (j < world->map->len)
		{
			if (rays->world_map[i][j] != 1 && rays->world_map[i][j] != 0)
				rays->world_map[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	loop(t_rays *rays, t_world *world)
{
	rays->texture = world->texture;
	if (world->map->player_p == 'N')
		rotate(-15, rays);
	if (world->map->player_p == 'S')
		rotate(15, rays);
	if (world->map->player_p == 'E')
		rotate(30, rays);
	mlx_loop_hook(rays->vars->mlx, &casting, rays);
	mlx_hook(rays->vars->win, 2, 1L << 0, clavier, rays);
	mlx_hook(rays->vars->win, 17, 1L << 0, close_win, rays->vars->mlx);
	mlx_loop(rays->vars->mlx);
}

int	main(int argc, char **argv)
{
	t_data		img;
	t_rays		rays;
	t_vars		vars;
	t_world		*world;

	if (argc != 2)
	{
		ft_dprintf(2, "Error\nBad Arguments\n");
		return (-1);
	}
	world = worldinit(argv[1]);
	init_alloc(&rays, world);
	vars.img = &img;
	vars.mlx = world->mlx->mlx;
	vars.win = world->mlx->mlx_win;
	rays.vars = &vars;
	rays.vars->mlx = world->mlx->mlx;
	world->rays = &rays;
	init(&rays);
	loop(&rays, world);
	worldend(world);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorificator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:02:07 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/31 16:33:13 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	is_color_valid(char **rgb)
{
	int	color;
	int	i;

	i = 0;
	while (rgb[i])
	{
		color = ft_atoi(rgb[i]);
		if (color < 0 || color > 255)
		{
			return (false);
		}
		i++;
	}
	return (true);
}

bool	put_color(t_world *world, u_int32_t *color, char **c_rgb)
{
	int	*rgb;
	(void)world;
	if (!is_color_valid(c_rgb))
	{
		free_array(c_rgb);
		return (false);
	}
	// rgb = ft_arrtouille(world, c_rgb, -1, 0, 0);
	rgb = malloc(3 * sizeof(int));
	rgb[0] = ft_atoi(c_rgb[0]);
	rgb[1] = ft_atoi(c_rgb[1]);
	rgb[2] = ft_atoi(c_rgb[2]);
	free_array(c_rgb);
	// if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
	// {
	// 	free_int_array(rgb);
	// 	return (false);
	// }
	printf("r = %d, g = %d, b = %d\n", rgb[0], rgb[1], rgb[2]);
	*color = (0 << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	// free_int_array(rgb);
	free(rgb);
	return (true);
}

t_color	*colorificator(t_world *world, t_map *map)
{
	t_color	*color;
	char	**floor;
	char	**ceiling;

	if (!map || !map->map)
		return (NULL);
	if (strncmp("F ", map->map[4], 2) || strncmp("C ", map->map[5], 2))
	{
		ft_error(world, "Invalid Color Format");
	}
	color = (t_color *)malloc(sizeof(t_color) * 2);
	if (!color)
		ft_error(world, strerror(errno));
	floor = ft_split(map->map[4] + 2, ',');
	ceiling = ft_split(map->map[5] + 2, ',');
	if (!put_color(world, &color->floor, floor) \
		|| !put_color(world, &color->ceiling, ceiling))
	{
		ft_error(world, "Invalid Color Format");
	}
	return (color);
}

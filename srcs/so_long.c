/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:59:40 by nde-chab          #+#    #+#             */
/*   Updated: 2024/08/09 20:09:51 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_data	*new_data(t_data **data)
{
	*data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	(*data)->sprite.collectible = NULL;
	(*data)->sprite.exit = NULL;
	(*data)->sprite.floor = NULL;
	(*data)->sprite.player = NULL;
	(*data)->sprite.wall = NULL;
	(*data)->sprite.wall1 = NULL;
	(*data)->sprite.wall2 = NULL;
	(*data)->sprite.wall3 = NULL;
	(*data)->sprite.wall4 = NULL;
	(*data)->sprite.enemie = NULL;
	(*data)->sprite.width = 32;
	(*data)->sprite.height = 32;
	(*data)->vars.mlx = NULL;
	(*data)->so_long.height = 0;
	(*data)->so_long.width = 0;
	(*data)->so_long.bool = 0;
	(*data)->so_long.mouv = 0;
	(*data)->so_long.mouvement = NULL;
	(*data)->so_long.mouvement = str_count(0,(*data)->so_long.mouvement);
	(*data)->frame = 0;
	return (*data);
}

void	ft_printmap(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
	printf("\n\n\n");
}

int	main(int ac, char **av)
{
	int		i;
	t_data	*data;

	i = 0;
	if (ac != 2)
		return (ft_printf("need 1 map\n"), -1);
	else if (error_file_map(av[1]) != 0)
		return (ft_printf("error file map name\n"), -1);
	data = new_data(&data);
	if (!data)
		return (0);
	take_map(av[1], &data->so_long);
	if (!data->so_long.map || !data->so_long.map[0])
		return (ft_free_data(&data), -1);
	if (correct_map(&data->so_long) == 0)
		ft_printf("need a corect map\n");
	else
	{
		ft_printf("map ok c = %d :)\n\n\n", data->so_long.collectible);
		ft_printmap(data->so_long.map);
		ft_visual_part(data);
	}
	ft_free_data(&data);
	return (0);
}

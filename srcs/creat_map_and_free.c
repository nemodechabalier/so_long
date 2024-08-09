/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_map_and_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:23:43 by nde-chab          #+#    #+#             */
/*   Updated: 2024/08/09 20:40:41 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	error_file_map(char *map)
{
	int	i;

	i = ft_strlen(map);
	if (i < 4)
		return (-1);
	return (ft_strncmp(map + i - 4, ".ber", 4));
}

void	ft_free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
}

void	ft_free_data(t_data **data)
{
	ft_free_map((*data)->so_long.map);
	destroy_image(*data);
	free(*data);
	*data = NULL;
}

static char	**ft_realoc_map(char **map, int *size)
{
	char	**new_map;
	int		i;

	i = 0;
	*size *= 2;
	new_map = ft_calloc(sizeof(char *), *size);
	if (!new_map)
		return (ft_free_map(map), NULL);
	while (map[i])
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i] = NULL;
	free(map);
	return (new_map);
}

void	take_map(char *path, t_long *so_long)
{
	char	*line;
	int		size;
	int		fd;
	int		i;

	i = 0;
	size = 8;
	fd = open(path, O_RDONLY);
	so_long->map = ft_calloc(sizeof(char *), size);
	if (!so_long->map)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		if (i >= size - 1)
			so_long->map = ft_realoc_map(so_long->map, &size);
		if (line[ft_strlen(line) - 1] == '\n')
			so_long->map[i] = ft_substr(line, 0, ft_strlen(line) - 1);
		else
			so_long->map[i] = ft_strdup(line);
		free(line);
		i++;
		line = get_next_line(fd);
		so_long->height = i;
	}
}

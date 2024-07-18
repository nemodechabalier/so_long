/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_gestion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:01:56 by nde-chab          #+#    #+#             */
/*   Updated: 2024/07/18 15:30:28 by nde-chab         ###   ########.fr       */
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

char	**ft_realoc_map(char **map, int *size)
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

int	take_map(char *path, t_long *so_long)
{
	char	*line;
	int		size;
	int		fd;
	int		i;

	i = 0;
	size = 8;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	so_long->map = ft_calloc(sizeof(char *), size);
	if (!so_long->map)
		return (0);
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
	}
	return (1);
}

int	correct_wall(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(map[0]) - 1;
	while (map[i])
	{
		if (map[i][0] != '1' || map[i][j] != '1')
			return (0);
		i++;
	}
	i = 0;
	j = 0;
	while (map[i])
		i++;
	i--;
	while (map[i][j])
	{
		if (map[i][j] != '1' || map[0][j] != '1')
			return (0);
		j++;
	}
	return (1);
}
int	unique_part(char **map, int collectible, int exit, int start)
{
	int	i;
	int	j;

	i = 0;
	collectible = 0;
	exit = 0;
	start = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				collectible++;
			if (map[i][j] == 'E')
				exit++;
			if (map[i][j] == 'P')
				start++;
			j++;
		}
		i++;
	}
	if (collectible != 1 || exit != 1 || start != 1)
		return (0);
	return (1);
}
int	unique_letter(t_long *so_long)
{
	int	collectible;
	int	exit;
	int	start;

	collectible = 0;
	start = 0;
	while (so_long->map[start])
	{
		exit = 0;
		while (so_long->map[start][exit])
		{
			if (ft_strchr("01CEP", so_long->map[start][exit]) == NULL)
				return (0);
			exit++;
		}
		start++;
	}
	start = 0;
	exit = 0;
	return (unique_part(so_long->map, collectible, exit, start));
}

void	flood(char **map, int i, int j, char c)
{
	if (map[i][j] == '1' || map[i][j] == c)
		return ;
	map[i][j] = c;
	flood(map, i + 1, j, c);
	flood(map, i, j - 1, c);
	flood(map, i, j + 1, c);
	flood(map, i - 1, j, c);
}

void	find_unique_letter(char **map, int *tab)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'E')
			{
				tab[0] = i;
				tab[1] = j;
			}
			if (map[i][j] == 'P')
			{
				tab[2] = i;
				tab[3] = j;
			}
			if (map[i][j] == 'C')
			{
				tab[4] = i;
				tab[5] = j;
			}
			j++;
		}
		i++;
	}
}
int	correct_cons_exit(char **map)
{
	int	tab[6];

	tab [0] = 0;
	find_unique_letter(map, tab);
	flood(map, tab[0], tab[1], 'T');
	if (map[tab[0]][tab[1]] == 'E' || map[tab[2]][tab[3]] == 'P'
		|| map[tab[4]][tab[5]] == 'C')
		return (0);
	flood(map, tab[0], tab[1], '0');
	map[tab[0]][tab[1]] = 'E';
	map[tab[0]][tab[1]] = 'P';
	map[tab[0]][tab[1]] = 'E';
	return (1);
}

int	correct_map(t_long *so_long)
{
	int		i;
	size_t	size;

	size = ft_strlen(so_long->map[0]);
	i = 1;
	while (so_long->map[i])
	{
		if (strlen(so_long->map[i]) != size)
			return (0);
		i++;
	}
	if (correct_wall(so_long->map) == 0 || unique_letter(so_long) == 0)
		return (0);
	return (correct_cons_exit(so_long->map));
}

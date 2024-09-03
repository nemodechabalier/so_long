/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:22:50 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/03 14:10:41 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**place_ennemie_mouv(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'S')
			{
				if (map[i][j + 1] == '0')
				{
					map[i][j + 1] = 'S';
					j++;
				}
				else if (map[i][j - 1] == '0')
					map[i][j - 1] = 'S';
			}
			j++;
		}
		i++;
	}
	ft_printmap(map);
	return (map);
}

static char	**creat_new_map(char **map)
{
	char	**new_map;
	int		i;

	i = 0;
	while (map[i])
		i++;
	new_map = malloc(sizeof(char *) * (i + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (map[i])
	{
		new_map[i] = ft_strdup(map[i]);
		if (!new_map[i])
			return (ft_free_map(new_map), NULL);
		i++;
	}
	new_map[i] = NULL;
	return (place_ennemie_mouv(new_map));
}

static void	flood(char **map, int i, int j, char c)
{
	if (map[i][j] == '1' || map[i][j] == c || map[i][j] == 'S')
		return ;
	map[i][j] = c;
	flood(map, i + 1, j, c);
	flood(map, i, j - 1, c);
	flood(map, i, j + 1, c);
	flood(map, i - 1, j, c);
}

static int	verrif_new_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("01TS", map[i][j]) == NULL)
				return (ft_free_map(map), 0);
			j++;
		}
		i++;
	}
	return (ft_free_map(map), 1);
}

int	correct_road(char **map, int *x, int *y)
{
	int		i;
	int		j;
	char	**new_map;

	new_map = creat_new_map(map);
	if (!new_map)
		return (0);
	i = 0;
	while (new_map[i])
	{
		j = 0;
		while (new_map[i][j])
		{
			if (new_map[i][j] == 'P')
			{
				*x = j;
				*y = i;
				flood(new_map, i, j, 'T');
				return (verrif_new_map(new_map));
			}
			j++;
		}
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_gestion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:01:56 by nde-chab          #+#    #+#             */
/*   Updated: 2024/07/18 19:30:31 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	correct_wall(char **map)
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

static int	unique_part(char **map, int collectible, int exit, int start)
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
	if (collectible <= 0 || exit != 1 || start != 1)
		return (0);
	return (1);
}

static int	unique_letter(t_long *so_long)
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
	return (correct_road(so_long->map));
}

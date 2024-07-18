/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:59:40 by nde-chab          #+#    #+#             */
/*   Updated: 2024/07/18 15:57:17 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_printmap(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	int i;

	i = 0;
	t_long *so_long;
	if (ac != 2)
		return (ft_printf("need 1 map"), -1);
	else if (error_file_map(av[1]) != 0)
		return (ft_printf("error file map name"), -1);
	so_long = (t_long *)malloc(sizeof(t_long));
	take_map(av[1], so_long);
	if (correct_map(so_long) == 0)
		ft_printf("need a corect map");
	else
		ft_printmap(so_long->map);
	ft_free_map(so_long->map);
	free(so_long);
}
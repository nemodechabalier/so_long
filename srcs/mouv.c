/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:19:27 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/03 14:22:09 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	modif_map(int x, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->so_long.map[i])
	{
		j = 0;
		while (data->so_long.map[i][j])
		{
			if (data->so_long.map[i][j] == 'S')
			{
				if (data->so_long.map[i][j + x] == '0')
				{
					data->so_long.map[i][j] = '0';
					data->so_long.map[i][j + x] = 'S';
					if (x == 1)
						j++;
				}
				else if (data->so_long.map[i][j + x] == 'P')
					close_window(data, 2);
			}
			j++;
		}
		i++;
	}
}

void	ennemie_mouv(t_data *data)
{
	if (data->so_long.bool_ennemie == 0)
	{
		modif_map(1, data);
		data->so_long.bool_ennemie = 1;
	}
	else
	{
		modif_map(-1, data);
		data->so_long.bool_ennemie = 0;
	}
}

void	count_mouv(t_data *data)
{
	mlx_string_put(data->vars.mlx, data->vars.win, 10, data->so_long.height * 32
		+ 20, 0x000000, data->so_long.mouvement);
	data->so_long.mouv++;
	data->so_long.mouvement = str_count(data->so_long.mouv,
			data->so_long.mouvement);
	mlx_string_put(data->vars.mlx, data->vars.win, 10, data->so_long.height * 32
		+ 20, 0xFFFFFF, data->so_long.mouvement);
}

void	mouvement_player(int x, int y, t_data *data)
{
	count_mouv(data);
	if (data->so_long.map[data->so_long.yp + y][data->so_long.xp + x] == '1')
		return (ennemie_mouv(data));
	if (data->so_long.map[data->so_long.yp + y][data->so_long.xp + x] == 'S')
		close_window(data, 2);
	if (data->so_long.map[data->so_long.yp + y][data->so_long.xp + x] == 'C')
		data->so_long.collectible--;
	if (data->so_long.bool == 1)
	{
		data->so_long.map[data->so_long.yp][data->so_long.xp] = 'E';
		data->so_long.bool = 0;
	}
	else
		data->so_long.map[data->so_long.yp][data->so_long.xp] = '0';
	if (data->so_long.map[data->so_long.yp + y][data->so_long.xp + x] == 'E')
	{
		data->so_long.bool = 1;
		if (data->so_long.collectible == 0)
			close_window(data, 1);
	}
	data->so_long.map[data->so_long.yp + y][data->so_long.xp + x] = 'P';
	data->so_long.yp += y;
	data->so_long.xp += x;
	ennemie_mouv(data);
	draw_map(data);
}

int	handle_key(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_window(data, 4);
	if (keycode == 'w' || keycode == 'W')
		mouvement_player(0, -1, data);
	if (keycode == 'a' || keycode == 'A')
		mouvement_player(-1, 0, data);
	if (keycode == 's' || keycode == 'S')
		mouvement_player(0, 1, data);
	if (keycode == 'd' || keycode == 'D')
		mouvement_player(1, 0, data);
	return (0);
}

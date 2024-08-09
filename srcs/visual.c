/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:49:49 by nde-chab          #+#    #+#             */
/*   Updated: 2024/08/09 20:43:37 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_image(t_data *data)
{
	data->sprite.collectible = mlx_xpm_file_to_image(data->vars.mlx,
			"sprite/collectible.xpm", &data->sprite.width,
			&data->sprite.height);
	data->sprite.exit = mlx_xpm_file_to_image(data->vars.mlx, "sprite/exit.xpm",
			&data->sprite.width, &data->sprite.height);
	data->sprite.floor = mlx_xpm_file_to_image(data->vars.mlx,
			"sprite/floor.xpm", &data->sprite.width, &data->sprite.height);
	data->sprite.player = mlx_xpm_file_to_image(data->vars.mlx,
			"sprite/player.xpm", &data->sprite.width, &data->sprite.height);
	data->sprite.wall1 = mlx_xpm_file_to_image(data->vars.mlx,
			"sprite/wall.xpm", &data->sprite.width, &data->sprite.height);
	data->sprite.wall2 = mlx_xpm_file_to_image(data->vars.mlx,
			"sprite/wall2.xpm", &data->sprite.width, &data->sprite.height);
	data->sprite.wall3 = mlx_xpm_file_to_image(data->vars.mlx,
			"sprite/wall3.xpm", &data->sprite.width, &data->sprite.height);
	data->sprite.wall4 = mlx_xpm_file_to_image(data->vars.mlx,
			"sprite/wall4.xpm", &data->sprite.width, &data->sprite.height);
	data->sprite.enemie = mlx_xpm_file_to_image(data->vars.mlx,
			"sprite/enemie.xpm", &data->sprite.width, &data->sprite.height);
	data->sprite.wall = data->sprite.wall1;
	if (!data->sprite.collectible || !data->sprite.enemie || !data->sprite.exit
		|| !data->sprite.floor || !data->sprite.player || !data->sprite.wall1
		|| !data->sprite.wall2 || !data->sprite.wall3 || !data->sprite.wall4)
	close_window(data);
}

void	draw_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	mlx_string_put(data->vars.mlx, data->vars.win, 10, data->so_long.height * 32
		+ 20, 0xFFFFFF, "nb mv = 12");
	while (data->so_long.map[i])
	{
		j = 0;
		while (data->so_long.map[i][j])
		{
			if (data->so_long.map[i][j] == '1')
				mlx_put_image_to_window(data->vars.mlx, data->vars.win,
					data->sprite.wall, j * 32, i * 32);
			if (data->so_long.map[i][j] == '0')
				mlx_put_image_to_window(data->vars.mlx, data->vars.win,
					data->sprite.floor, j * 32, i * 32);
			if (data->so_long.map[i][j] == 'C')
				mlx_put_image_to_window(data->vars.mlx, data->vars.win,
					data->sprite.collectible, j * 32, i * 32);
			if (data->so_long.map[i][j] == 'E')
				mlx_put_image_to_window(data->vars.mlx, data->vars.win,
					data->sprite.exit, j * 32, i * 32);
			if (data->so_long.map[i][j] == 'P')
				mlx_put_image_to_window(data->vars.mlx, data->vars.win,
					data->sprite.player, j * 32, i * 32);
			if (data->so_long.map[i][j] == 'S')
				mlx_put_image_to_window(data->vars.mlx, data->vars.win,
					data->sprite.enemie, j * 32, i * 32);
			j++;
		}
		i++;
	}
}

void	mouvement_player(int x, int y, t_data *data)
{
	data->so_long.mouv++;
	// data->so_long.mouvement = str_count(data->so_long.mouv,
	//		data->so_long.mouvement);
	printf("%s\n", data->so_long.mouvement);
	if (data->so_long.map[data->so_long.yp + y][data->so_long.xp + x] == '1')
		return ;
	if (data->so_long.map[data->so_long.yp + y][data->so_long.xp + x] == 'S')
		exit(0);
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
			exit(0);
	}
	data->so_long.map[data->so_long.yp + y][data->so_long.xp + x] = 'P';
	data->so_long.yp += y;
	data->so_long.xp += x;
	draw_map(data);
}

int	handle_key(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_window(data);
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
int	animate_wall(t_data *data)
{
	data->frame++;
	if (data->frame == INT_MAX)
	{
		data->frame = 0;
		data->sprite.wall = data->sprite.wall1;
	}
	else if (data->frame % 2000 == 0)
		data->sprite.wall = data->sprite.wall1;
	else if (data->frame % 1000 == 0)
		data->sprite.wall = data->sprite.wall4;
	else if (data->frame % 500 == 0)
		data->sprite.wall = data->sprite.wall3;
	else if (data->frame % 250 == 0)
		data->sprite.wall = data->sprite.wall2;
	draw_map(data);
	return (0);
}
void	ft_visual_part(t_data *data)
{
	data->vars.mlx = mlx_init();
	if (data->vars.mlx == NULL)
		return (ft_putstr_fd("Erreur d'initialisation de mlx\n", 2));
	data->vars.win = mlx_new_window(data->vars.mlx, data->so_long.width * 32,
			data->so_long.height * 32 + 40, "so_long");
	if (data->vars.win == NULL)
		return (ft_putstr_fd("Erreur de création de la fenêtre\n", 2),
			mlx_destroy_display(data->vars.mlx), free(data->vars.mlx));
	mlx_key_hook(data->vars.win, handle_key, data);
	mlx_hook(data->vars.win, 17, 0, close_window, data);
	mlx_loop_hook(data->vars.mlx, animate_wall, data);
	load_image(data);
	draw_map(data);
	mlx_loop(data->vars.mlx);
	if (data->vars.win != NULL)
		mlx_destroy_window(data->vars.mlx, data->vars.win);
	mlx_destroy_display(data->vars.mlx);
	free(data->vars.mlx);
}

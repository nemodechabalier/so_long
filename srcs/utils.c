/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:16:20 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/01 21:10:41 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*str_count(int count, char *mouvement)
{
	char	*temp;

	if (mouvement)
		free(mouvement);
	temp = ft_itoa(count);
	if (!temp)
		return (NULL);
	mouvement = ft_strjoin("nb mv = ", temp);
	return (free(temp), mouvement);
}

void	destroy_image(t_data *data)
{
	if (data->sprite.collectible)
		mlx_destroy_image(data->vars.mlx, data->sprite.collectible);
	if (data->sprite.enemie)
		mlx_destroy_image(data->vars.mlx, data->sprite.enemie);
	if (data->sprite.exit)
		mlx_destroy_image(data->vars.mlx, data->sprite.exit);
	if (data->sprite.floor)
		mlx_destroy_image(data->vars.mlx, data->sprite.floor);
	if (data->sprite.player)
		mlx_destroy_image(data->vars.mlx, data->sprite.player);
	if (data->sprite.wall1)
		mlx_destroy_image(data->vars.mlx, data->sprite.wall1);
	if (data->sprite.wall2)
		mlx_destroy_image(data->vars.mlx, data->sprite.wall2);
	if (data->sprite.wall3)
		mlx_destroy_image(data->vars.mlx, data->sprite.wall3);
	if (data->sprite.wall4)
		mlx_destroy_image(data->vars.mlx, data->sprite.wall4);
}

int	close_window(t_data *data, int bool)
{
	mlx_loop_end(data->vars.mlx);
	destroy_image(data);
	mlx_destroy_window(data->vars.mlx, data->vars.win);
	data->vars.win = NULL;
	mlx_destroy_display(data->vars.mlx);
	free(data->vars.mlx);
	ft_free_data(&data);
	if (bool == 1)
		ft_printf("congratulations, you win !!\n");
	else if (bool == 2)
		ft_printf("Oh, no you lost !!\n");
	else if(bool == 0)
		ft_printf("Error\n");
	exit(0);
	return (0);
}

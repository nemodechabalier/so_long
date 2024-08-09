/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:16:20 by nde-chab          #+#    #+#             */
/*   Updated: 2024/08/09 20:46:25 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char *str_count(int count, char *mouvement)
{
	if (mouvement)
		free(mouvement);
	char *temp;

	temp = ft_itoa(count);
	if (!temp)
		return (NULL);
	mouvement = ft_strjoin("nb mv = ", temp);
	return (free(temp), mouvement);
}

void destroy_image(t_data *data)
{
    if (data->sprite.collectible)
    {
        mlx_destroy_image(data->vars.mlx, data->sprite.collectible);
        data->sprite.collectible = NULL;
    }
    if (data->sprite.enemie)
    {
        mlx_destroy_image(data->vars.mlx, data->sprite.enemie);
        data->sprite.enemie = NULL;
    }
    if (data->sprite.exit)
    {
        mlx_destroy_image(data->vars.mlx, data->sprite.exit);
        data->sprite.exit = NULL;
    }
    if (data->sprite.floor)
    {
        mlx_destroy_image(data->vars.mlx, data->sprite.floor);
        data->sprite.floor = NULL;
    }
    if (data->sprite.player)
    {
        mlx_destroy_image(data->vars.mlx, data->sprite.player);
        data->sprite.player = NULL;
    }
    if (data->sprite.wall1)
    {
        mlx_destroy_image(data->vars.mlx, data->sprite.wall1);
        data->sprite.wall1 = NULL;
    }
    if (data->sprite.wall2)
    {
        mlx_destroy_image(data->vars.mlx, data->sprite.wall2);
        data->sprite.wall2 = NULL;
    }
    if (data->sprite.wall3)
    {
        mlx_destroy_image(data->vars.mlx, data->sprite.wall3);
        data->sprite.wall3 = NULL;
    }
    if (data->sprite.wall4)
    {
        mlx_destroy_image(data->vars.mlx, data->sprite.wall4);
        data->sprite.wall4 = NULL;
    }
}


int	close_window(t_data *data)
{
	mlx_loop_end(data->vars.mlx);
	mlx_destroy_window(data->vars.mlx, data->vars.win);
	data->vars.win = NULL;
	mlx_destroy_display(data->vars.mlx);
	free(data->vars.mlx);
	ft_free_data(&data);
	exit(0);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:04:17 by nde-chab          #+#    #+#             */
/*   Updated: 2024/08/09 19:48:19 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct s_vars {
    void    *mlx;
    void    *win;
}               t_vars;

// Fonction pour gérer les événements de clavier
int handle_key(int keycode, t_vars *vars)
{
    if (keycode == 65307) // Touche Échap sur Linux
    {
        mlx_destroy_window(vars->mlx, vars->win);
        vars->win = NULL; // Assurez-vous de ne plus accéder à la fenêtre après destruction
        mlx_loop_end(vars->mlx); // Stoppe la boucle mlx
        return (0);
    }
    return (0);
}

// Fonction pour gérer la fermeture de la fenêtre
int close_window(t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
    vars->win = NULL; // Assurez-vous de ne plus accéder à la fenêtre après destruction
    mlx_loop_end(vars->mlx); // Stoppe la boucle mlx
    return (0);
}

int main()
{
    t_vars vars;

    vars.mlx = mlx_init();
    if (vars.mlx == NULL)
    {
        fprintf(stderr, "Erreur d'initialisation de mlx\n");
        return (1);
    }

    vars.win = mlx_new_window(vars.mlx, 800, 600, "Hello World!");
    if (vars.win == NULL)
    {
        fprintf(stderr, "Erreur de création de la fenêtre\n");
        mlx_destroy_display(vars.mlx); // Détruire le display si la création de la fenêtre échoue
        free(vars.mlx); // Libérer le pointeur mlx
        return (1);
    }
	mlx_hook(vars.win, 17, 1L << 17, close_window, &vars);
    mlx_key_hook(vars.win, handle_key, &vars);
    

    mlx_loop(vars.mlx);
    
    // Après la boucle, libérer les ressources
    if (vars.win != NULL) // Assurez-vous que la fenêtre est détruite
        mlx_destroy_window(vars.mlx, vars.win);
    mlx_destroy_display(vars.mlx);
    free(vars.mlx);

    return (0);
}

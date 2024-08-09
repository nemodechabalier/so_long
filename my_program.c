#include "minilibx-linux/mlx.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct s_vars {
    void    *mlx;
    void    *win;
}               t_vars;

int close(int keycode, t_vars *vars)
{
    if (keycode == 65307) // Touche Échap sur Linux
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
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
        return (1);
    }

    mlx_key_hook(vars.win, close, &vars);
    mlx_loop(vars.mlx);
    return (0);
}

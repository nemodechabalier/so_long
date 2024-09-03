/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:59:44 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/03 14:27:02 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft_all/ft_printf/ft_printf.h"
# include "../libft_all/get_next_line/get_next_line.h"
# include "../libft_all/libtf/libft.h"
# include "../minilibx-linux/mlx.h"
# include <limits.h>

typedef struct s_image
{
	void	*collectible;
	void	*exit;
	void	*player;
	void	*wall;
	void	*floor;
	void	*wall1;
	void	*wall2;
	void	*wall3;
	void	*wall4;
	void	*enemie;
	int		width;
	int		height;
}			t_image;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}			t_vars;

typedef struct s_long
{
	char	**map;
	char	*mouvement;
	int		width;
	int		height;
	int		bool;
	int		xp;
	int		yp;
	int		mouv;
	int		collectible;
	int		bool_ennemie;
}			t_long;

typedef struct s_data
{
	int		frame;
	t_long	so_long;
	t_image	sprite;
	t_vars	vars;
}			t_data;

int			error_file_map(char *map);
int			correct_map(t_long *so_long);
void		take_map(char *path, t_long *so_long);
void		ft_free_data(t_data **data);
void		ft_free_map(char **map);
int			correct_road(char **map, int *x, int *y);
void		ft_visual_part(t_data *data);
void		add_point(int *nb, int i);
char		*str_count(int count, char *mouvenent);
void		destroy_image(t_data *data);
int			close_window(t_data *data, int bool);
int			handle_key(int keycode, t_data *data);
void		draw_map(t_data *data);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:59:44 by nde-chab          #+#    #+#             */
/*   Updated: 2024/07/17 18:04:15 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft_all/ft_printf/ft_printf.h"
# include "../libft_all/get_next_line/get_next_line.h"
# include "../libft_all/libtf/libft.h"

typedef struct s_long
{
	char	**map;
}			t_long;

int			error_file_map(char *map);
int			correct_map(t_long *so_long);
int			take_map(char *path, t_long *so_long);
void		ft_free_map(char **map);

#endif
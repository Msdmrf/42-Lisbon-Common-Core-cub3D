/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notjustlaw <notjustlaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 11:50:06 by justlaw           #+#    #+#             */
/*   Updated: 2026/04/20 11:32:25 by notjustlaw       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double	convert_angle(char spawn_dir)
{
	if (spawn_dir == 'E')
		return (0);
	else if (spawn_dir == 'N')
		return (3 * M_PI / 2);
	else if (spawn_dir == 'W')
		return (M_PI);
	else if (spawn_dir == 'S')
		return (M_PI / 2);
	return (ft_putendl_fd("Error\n Couldn't convert angle.", 2), -1);
}

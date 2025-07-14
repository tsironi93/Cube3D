/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:07:03 by itsiros           #+#    #+#             */
/*   Updated: 2025/07/13 16:05:47 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	store_line(char *line, char *map_buffer[], int *i, size_t *max_len)
{
	char	*new_line;

	new_line = ft_strtrim(line, "\n");
	if (*max_len < ft_strlen(new_line))
		*max_len = ft_strlen(new_line);
	map_buffer[(*i)++] = new_line;
}

static void	finalize_map(t_data *data, char ***map, char *map_buffer[],
					size_t max_len)
{
	int	j;

	j = -1;
	while (++j < data->map_height)
	{
		(*map)[j] = gc_malloc(&data->gc, max_len + 1);
		ft_memset((*map)[j], ' ', max_len);
		ft_memcpy((*map)[j], map_buffer[j], ft_strlen(map_buffer[j]));
		(*map)[j][max_len] = '\0';
	}
	(*map)[j] = NULL;
}

void	fetch_map(t_data *data, char *line, char ***map)
{
	static char		*map_buffer[1024];
	static int		i;
	static size_t	max_len;

	if ((!line && i == 0) || i < 0)
		return ;
	if (!line && i != 0)
	{
		*map = gc_malloc(&data->gc, (i + 1) * sizeof(char *));
		data->map_height = i;
		data->width = max_len;
		finalize_map(data, map, map_buffer, max_len);
		i = -1;
	}
	else
		store_line(line, map_buffer, &i, &max_len);
}

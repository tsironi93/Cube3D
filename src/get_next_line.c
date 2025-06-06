/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:44:40 by itsiros           #+#    #+#             */
/*   Updated: 2025/06/06 18:15:29 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

char	*get_next_line(t_data *data, int fd)
{
	static int	pos;
	int			i;
	static char	buffer[100];
	char		line[516515];
	static int	br;

	i = 0;
	while (1)
	{
		if (pos >= br)
		{
			br = read(fd, buffer, 100);
			pos = 0;
			if (br <= 0)
				break ;
		}
		line[i++] = buffer[pos];
		if (buffer[pos++] == '\n')
			break ;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (gc_strdup(&data->gc, line));
}

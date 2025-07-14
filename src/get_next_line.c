/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:39:50 by pdrettas          #+#    #+#             */
/*   Updated: 2025/07/14 16:44:16 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*strcpy_til_newline(char *buffer)
{
	int		i;
	int		len;
	char	*line;

	len = 0;
	i = 0;
	while (buffer != NULL && buffer[i] != '\0')
	{
		len++;
		if (buffer[i] == '\n')
			break ;
		i++;
	}
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	if (buffer[i] == '\0')
		line = ft_strcpy(line, buffer);
	else
		ft_strlcpy(line, buffer, len + 1);
	return (line);
}

void	moving_buffer_left(char buffer[])
{
	int	i;
	int	j;
	int	h;

	i = 0;
	h = ft_char_in_string(buffer, '\n');
	if (h >= 0)
	{
		j = h + 1;
		while (j < BUFFER_SIZE + 1)
		{
			buffer[i++] = buffer[j++];
		}
		while (i < BUFFER_SIZE + 1)
		{
			buffer[i++] = '\0';
		}
	}
	else
	{
		while (i < BUFFER_SIZE + 1)
		{
			buffer[i++] = '\0';
		}
	}
}

char	*detele_all_after_newline(char *read_line)
{
	int		i;
	size_t	len;
	char	*line;

	if (ft_char_in_string(read_line, '\n') >= 0)
	{
		len = 0;
		i = 0;
		while (read_line != NULL && read_line[i] != '\0')
		{
			len++;
			if (read_line[i] == '\n')
				break ;
			i++;
		}
		line = malloc(sizeof(char) * (len + 1));
		if (!line)
			return (free(read_line), NULL);
		ft_strlcpy(line, read_line, len + 1);
		free(read_line);
	}
	else
		line = read_line;
	return (line);
}

char	*get_buffer(char buffer[], int fd)
{
	int		bytes_read;
	char	*read_line;

	read_line = ft_strjoin_gnl(NULL, buffer);
	if (!read_line)
		return (NULL);
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		if (bytes_read < 0)
		{
			free(read_line);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		read_line = ft_strjoin_gnl(read_line, buffer);
		if (!read_line)
			return (NULL);
		if (ft_char_in_string(buffer, '\n') >= 0)
			break ;
	}
	return (read_line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*read_line;
	static char	buffer[BUFFER_SIZE + 1];

	line = NULL;
	if (fd < 0 || BUFFER_SIZE == 0)
	{
		return (NULL);
	}
	if (ft_char_in_string(buffer, '\n') >= 0)
		line = strcpy_til_newline(buffer);
	else
	{
		read_line = get_buffer(buffer, fd);
		if (read_line != NULL && ft_strlen(read_line) == 0)
		{
			free(read_line);
			return (NULL);
		}
		line = detele_all_after_newline(read_line);
	}
	moving_buffer_left(buffer);
	return (line);
}

// int main ()
// {

//     char * line;
//     int fd = open("./file", O_RDONLY);

//     while(1)
//     {
//         line = get_next_line(fd);
//         if (line == NULL)
//             break;
//         printf("line =%s", line);
// 		free(line);
//     }
//     close(fd);
//     return (0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:40:06 by pdrettas          #+#    #+#             */
/*   Updated: 2025/07/14 14:27:00 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_length;

	i = 0;
	src_length = 0;
	while (src[src_length] != '\0')
	{
		src_length++;
	}
	if (dstsize == 0)
	{
		return (src_length);
	}
	while (src[i] != '\0' && i < (dstsize -1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_length);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strcpy(char *goal, const char *start)
{
	char	*temp;

	temp = goal;
	while (*start != '\0')
		*temp++ = *start++;
	*temp = '\0';
	return (goal);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_len;
	char	*result;

	s1_len = 0;
	s2_len = 0;
	if (s1 == (NULL) && s2 == (NULL))
		return (NULL);
	if (s1 != (NULL))
		s1_len = ft_strlen(s1);
	if (s2 != (NULL))
		s2_len = ft_strlen(s2);
	total_len = (s1_len + s2_len) + 1;
	result = malloc(total_len * sizeof(char));
	if (result == (NULL))
		return (NULL);
	if (s1 != NULL)
		ft_strcpy(result, s1);
	if (s2 != NULL)
		ft_strcpy(result + s1_len, s2);
	return (free(s1), result);
}

int	ft_char_in_string(char *string, char a)
{
	int	i;

	if (string == NULL)
	{
		return (-1);
	}
	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == a)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

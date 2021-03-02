/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 16:06:55 by marvin            #+#    #+#             */
/*   Updated: 2021/03/02 15:11:00 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int				ft_strlen(const char *str)
{
	int			i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char			*ft_strdup(char *src)
{
	int			i;
	char		*dest;

	i = 0;
	while (src[i] != '\0')
		i++;
	if (!(dest = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char			*ft_strchr(const char *s, int c)
{
	char		*str;

	str = (char *)s;
	while (*str != c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return (str);
}

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		j;
	char		*dest;

	i = 0;
	j = 0;
	if (!(dest = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (s[i] != '\0')
	{
		if (i >= start && j < len)
		{
			dest[j] = s[i];
			j++;
		}
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

int				get_next_line(int fd, char **line)
{
	ssize_t		ret;
	char		buff[BUFFER_SIZE + (ret = 1)];
	static char	*str[255];
	char		*temp;

	if (fd < 0 || fd >= 256 || !line || BUFFER_SIZE <= 0)
		return (-1);
	str[fd] == NULL ? str[fd] = ft_memalloc(1 * sizeof(char)) : NULL;
	while (!ft_strchr(str[fd], '\n') && (ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		temp = ft_strjoin(str[fd], buff);
		ft_strfree(&str[fd]);
		str[fd] = temp;
	}
	if (ret == 0)
		*line = ft_strdup(str[fd]);
	else if (ret > 0)
		*line = ft_substr(str[fd], 0, (ft_strchr(str[fd], '\n') - str[fd]));
	else
		return (-1);
	temp = ft_strdup(str[fd] + (ft_strlen(*line) + ((ret > 0) ? +1 : +0)));
	ft_strfree(&str[fd]);
	str[fd] = temp;
	return (ret == 0 ? 0 * ft_strfree(&str[fd]) : 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 10:56:45 by epfennig          #+#    #+#             */
/*   Updated: 2021/02/06 10:25:47 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	int			i;
	int			j;
	char		*str;

	if (s1 == NULL || s2 == NULL || !(str = (char *)malloc(ft_strlen(s1)
		+ ft_strlen(s2) + 1)))
		return (NULL);
	str[0] = '\0';
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char			*ft_strnew(size_t size)
{
	return (ft_memalloc((size + 1) * sizeof(char)));
}

void			*ft_memset(void *b, int c, size_t len)
{
	size_t		i;
	char		*str;

	i = 0;
	str = (char *)b;
	while (i < len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

int				ft_strdel(char **ptr)
{
	if (*ptr)
	{
		ft_memset(*ptr, 0, ft_strlen(*ptr));
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

void			*ft_memalloc(size_t size)
{
	void		*str;

	if (!(str = malloc(size)))
		return (NULL);
	ft_memset(str, 0, size);
	return (str);
}

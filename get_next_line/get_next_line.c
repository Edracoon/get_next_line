/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 16:06:55 by marvin            #+#    #+#             */
/*   Updated: 2021/03/01 16:32:38 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

/*
** Description: Fonction qui retourne
** une ligne lue depuis un file descriptor, sans la nouvelle ligne.
** Parametres:
** 1. file descriptor sur lequel il faut lire
** 2. la valeur qui a ete lue
** Valeur de retour :
** 1 : Une ligne a ete lue
** 0 : EOF a ete atteins
** -1 : Erreur
*/

int				get_next_line(int fd, char **line)
{
	ssize_t		ret;   /* return de read    ssize_t = pour aller dans les negatifs (-1 / 0 / 1) */
	char		buff[BUFFER_SIZE + (ret = 1)]; /* buffer / ligne qu'on lis on va stocker dedans ce qu'on lis puis on rentrera buf dans str qui est static */
	static char	*str = NULL; /* destination de ce que l'on va lire. (static * = stock l'adresse memoire) pour garder en memoir ou on en est */
	char		*temp;

	if (fd < 0 || fd >= 256 || !line || BUFFER_SIZE <= 0)  /* gestion d'erreur */
		return (-1);
	str == NULL ? str = ft_strnew(0) : NULL; /* bzero */
	while (!ft_strchr(str, '\n') && (ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		temp = ft_strjoin(str, buff);
		ft_strdel(&str);
		str = temp;
	}
	if (ret == 0)
		*line = ft_strdup(str);
	else if (ret > 0)
		*line = ft_substr(str, 0, (ft_strchr(str, '\n') - str));  /* strchr - str c'est adresse d'un pointeur - l'adresse de l'autre et ca fait un int */
	else
		return (-1);
	temp = ft_strdup(str + (ft_strlen(*line) + ((ret > 0) ? +1 : +0)));
	ft_strdel(&str);
	str = temp;
	return (ret == 0 ? 0 * ft_strdel(&str) : 1);
}
/*
int			main(int argc, char **argv)
{
	char	*line;
	int		fd;
	int		code;
	int		len;
	int		i;

	i = 1;
	printf("BUFF_SIZE = %d\n", BUFFER_SIZE);
	printf("___Premier FD___ \n\n");
	while (i < argc)
	{
		if ((fd = open(argv[i], O_RDONLY)) == -1)
			write(1, "Erreur, ne peut pas ouvrir le fichier", 25);
		while ((code = get_next_line(fd, &line)) > 0)
		{
			len = ft_strlen(line);
			printf("%d - %d - |%s|\n", code, len, line);
			free(line);
		}
		i++;
		if (i < argc)
			printf("\n___Changement de FD___ \n\n");
	}
	printf("LAST %d - |%s|\n", code, line);
	return (0);
}
*/

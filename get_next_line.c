/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 16:06:55 by marvin            #+#    #+#             */
/*   Updated: 2021/03/02 17:19:00 by epfennig         ###   ########.fr       */
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
	ssize_t		ret;                                                          /* return de read    ssize_t = pour aller dans les negatifs (-1 / 0 / 1) */
	char		buff[BUFFER_SIZE + (ret = 1)];                                /* buffer / ligne qu'on lis on va stocker dedans ce qu'on lis puis on rentrera buf dans str qui est static */
	static char	*str = NULL;                                                  /* destination de ce que l'on va lire. (static * = stock l'adresse memoire) pour garder en memoir ou on en est */
	char		*temp;

	if (fd < 0 || fd >= 256 || !line || BUFFER_SIZE <= 0)                       /* gestion d'erreur */
		return (-1);
	str == NULL ? str = ft_memalloc(1 * sizeof(char)) : NULL;                   /* verification de la static pour savoir si c'est le premier appel de gnl ou non, on alloue 1 bit pour le '\0' */
	while (!ft_strchr(str, '\n') && (ret = read(fd, buff, BUFFER_SIZE)) > 0)    /* Tant que l'on a pas de '\n' et que le read() lis (ret = le return de read, le nombre de bit lus) */
	{
		buff[ret] = '\0';                                                     /* on met le '\0' a la fin de la string buff (notre ligne lue en fonction du buffer_size) pour permettre le ft_strjoin */
		temp = ft_strjoin(str, buff);                                         /* strjoin de la static str avec la ligne lue, qu'on stock dans temp le temps de free l'ancienne adresse de str */
		ft_strfree(&str);                                                     /* on free l'adresse de str pour ensuite lui reassigner temp pour ne pas avoir de leaks et de superposition de string */
		str = temp;                                                           /* assignation de str avec le nouvel strjoin */
	}                                                                           /* on check le ret a la sortie de la boucle, on sort si ret <= 0 ou si l'on a trouvé le '\n' */
	if (ret == 0)                                                               /* si ret = 0 , cela veut dire que il n'y a plus rien a lire car ret = 0*/
		*line = ft_strdup(str);                                               /* on copy + malloc dans *line qui est notre ligne finale de retour, on fait strdup car on a l'EOF donc on a la len qu'il nous faut*/
	else if (ret > 0)                                                           /* si ret > 0 cela veut dire qu'on n'est pas arrivé a l'EOF donc on fait un substr*/
		*line = ft_substr(str, 0, (ft_strchr(str, '\n') - str));              /* strchr - str c'est adresse d'un pointeur - l'adresse de l'autre et ca fait un int : on part de start = 0 et len = la position du '\n' */
	else
		return (-1);                                                          /* else on trouve une erreur dans le ret (ret < 0) */
	temp = ft_strdup(str + (ft_strlen(*line) + ((ret > 0) ? +1 : +0)));       /* partie on l'on stoque le reste pour la suite di programme */
	ft_strfree(&str);                                                         /* on free une derniere fois l'adresse de str */
	str = temp;
	return (ret == 0 ? 0 * ft_strfree(&str) : 1);                             /* valeur de return, on reverifie le ret de read, si on est a l'EOF, on free &str tout en renvoyant 0 */
}                                                                             /* sinon on return 1 == une ligne a été lu */

/*
** Main Tester :
** int			main(int argc, char **argv)
** {
**		char	*line;
**		int		fd;
**		int		code;
**		int		len;
**		int		i;
**
**		i = 1;
**		(void)argc;
**		printf("BUFF_SIZE = %d\n", BUFFER_SIZE);
**		printf("___Premier FD___ \n\n");
**		while (i < argc)
**		{
**			if ((fd = open(argv[i], O_RDONLY)) == -1)
**				write(1, "Erreur, ne peut pas ouvrir le fichier", 25);
**			while ((code = get_next_line(fd, &line)) > 0)
**			{
**				len = ft_strlen(line);
**				printf("%d - %d - |%s|\n", code, len, line);
**				free(line);
**			}
**			i++;
**			if (i < argc)
**				printf("\n___Changement de FD___ \n\n");
**		}
**		printf("LAST %d - |%s|\n", code, line);
**		return (0);
** }
*/

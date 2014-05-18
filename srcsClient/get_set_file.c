/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/17 16:50:27 by jflorimo          #+#    #+#             */
/*   Updated: 2014/05/17 16:50:27 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <libft.h>
#include "script.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

int				put_file(char *file, int sock)
{
	int			fd;
	int			ret;
	struct stat	st[1024];
	int			size;
	char		buff[100000];

	if ((fd = open(file, O_RDONLY)) != -1)
	{
		if ((ret = fstat(fd, st)) == -1)
			ft_putstr("ERROR STAT\n");
		size = (int)st->st_size;
		write(sock, ft_itoa(size), ft_strlen(ft_itoa(size)));
		write(sock, "\0", 1);
		while ((ret = read(fd, buff, (size_t)size)) > 0)
		{
			buff[ret] = '\0';
			write(sock, buff, ret);
		}
	}
	else
	{
		write(sock, "ERROR", 5);
		write(sock, "\0", 1);
	}
	return (1);
}

char			*getname(char *path)
{
	char		*ssc;
	int			l;

	l = 0;
	ssc = ft_strstr(path, "/");
	while (ssc)
	{
		l = ft_strlen(ssc) + 1;
		path = &path[ft_strlen(path) - l + 2];
		ssc = ft_strstr(path, "/");
	}
	return (path);
}

int				get_file(char *file, int sock)
{
	char		size[8];
	char		buff[1];
	char		buffer[100000];
	int			r;
	int			r2;
	int			fd;

	fd = 0;
	ft_bzero(size, 8);
	while ((r = read(sock, buff, 1) > 0) && buff[0] != '\0')
		size[fd++] = buff[0];
	if (!ft_strncmp("ERROR", size, 5))
	{
		ft_putendl("SERVER: ERROR FILE NOT FOUND");
		return (0);
	}
	if ((fd = open(getname(file), O_CREAT | O_WRONLY | O_APPEND, 0666)) == -1)
		ft_putendl("ERROR CREATING FILE\n");
	while ((r2 = read(sock, buffer, ft_atoi(size))) > 0)
	{
		buffer[r2] = '\0';
		write(fd, buffer, ft_atoi(size));
		break ;
	}
	return (1);
}

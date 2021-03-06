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

char			*gen(char *path)
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

void			displayerr(char *s, int fdf)
{
	ft_putstr_fd(s, fdf);
	write(fdf, "\0", 1);
}

void			writefile(int fd, int fdf, int size)
{
	char		buffer[100000];
	int			r2;

	while ((r2 = read(fdf, buffer, size)) > 0)
	{
		buffer[r2] = '\0';
		write(fd, buffer, size);
		break ;
	}
}

void			get_file_serv(char *file, int fdf)
{
	char		size[8];
	char		buff[1];
	int			r;
	int			fd;

	fd = 0;
	ft_bzero(size, 8);
	while ((r = read(fdf, buff, 1) > 0) && buff[0] != '\0')
		size[fd++] = buff[0];
	if (ft_strncmp("ERROR", size, 5))
	{
		if ((fd = open(gen(file), O_CREAT | O_WRONLY | O_APPEND, 0666)) == -1)
			ft_putendl("ERROR CREATING FILE\n");
		writefile(fd, fdf, ft_atoi(size));
		displayerr("SERVER: SUCCESS RECEIVE FILE\n", fdf);
	}
	else
		displayerr("SERVER: ERROR FILE NOT FOUND\n", fdf);
}

void			put_file_serv(char *file, int cs)
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
		write(cs, ft_itoa(size), ft_strlen(ft_itoa(size)));
		write(cs, "\0", 1);
		while ((ret = read(fd, buff, (size_t)size)) > 0)
		{
			buff[ret] = '\0';
			write(cs, buff, ret);
		}
		ft_putstr_fd("SERVER: SUCCESS FILE SEND\n", cs);
	}
	else
		ft_putstr_fd("ERROR", cs);
	write(cs, "\0", 1);
}

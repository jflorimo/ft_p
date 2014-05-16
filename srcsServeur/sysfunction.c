/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sysfunction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 17:43:10 by jflorimo          #+#    #+#             */
/*   Updated: 2014/05/16 17:43:10 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <libft.h>
#include "script.h"

void				ft_ls(int cs)
{
	DIR				*dir;
	struct dirent	*p;
	char			*fic;

	dir = opendir(".");
	while ((p = readdir(dir)))
	{
		fic = p->d_name;
		if (ft_strncmp(".", fic, 1) != 0)
			ft_putendl_fd(fic, cs);
	}
	write(cs, "\0", 1);
	closedir(dir);
}

void				empty(int fd)
{
	write(fd, "\0", 1);
}

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

void				get_pwd(int fd, char *homedir)
{
	char 			cwd[1024];
	char 			*str;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(fd, "~/", 2);
		str = ft_strdup(&cwd[ft_strlen(homedir) + 1]);
		ft_putendl_fd(str, fd);
		write(fd, "\0", 1);
	}
}

void				set_cd(char *s, char *homedir)
{
	char 			saved_cwd[1024];
	char 			cwd[1024];
	if (getcwd(saved_cwd, sizeof(saved_cwd)) != NULL)
		ft_putendl("error in cd");
	chdir(s);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putendl("error in cd");
	if (ft_strcmp(homedir, cwd) > 0)
	{
		ft_putendl("not authorized for query on!");
		chdir(homedir);
	}
}

void				empty(int fd)
{
	write(fd, "\0", 1);
}

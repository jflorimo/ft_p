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

void				empty(int fd)
{
	write(fd, "\0", 1);
}

void				ft_ls(int cs)
{
	DIR				*dir;
	struct dirent	*p;
	char			*fic;
	int				i;

	dir = opendir(".");
	i = 0;
	while ((p = readdir(dir)))
	{
		fic = p->d_name;
		if (ft_strncmp(".", fic, 1) != 0)
			ft_putendl_fd(fic, cs);
		i++;
	}
	if (i > 0)
		ft_putstr_fd("\x1b[32mSUCCESS\x1b[0m\n", cs);
	else
		ft_putstr_fd("\x1b[31mERROR\x1b[0m\n", cs);
	write(cs, "\0", 1);
	closedir(dir);
}

void				get_pwd(int fd, int len)
{
	char			cwd[1024];
	char			*str;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd("\x1b[32mSUCCESS\x1b[0m\n", fd);
		write(fd, "~/", 2);
		if (ft_strlen(&cwd[len]) <= 0)
			str = ft_strdup(&cwd[len]);
		else
			str = ft_strdup(&cwd[len + 1]);
		ft_putendl_fd(str, fd);
		write(fd, "\0", 1);
	}
	else
		ft_putstr_fd("\x1b[31mERROR\x1b[0m\n", fd);
}

void				set_cd(char *s, char *homedir, int fd)
{
	char			saved_cwd[1024];
	char			cwd[1024];

	if (getcwd(saved_cwd, sizeof(saved_cwd)) != NULL)
	{
		chdir(s);
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			if (ft_strcmp(homedir, cwd) > 0)
			{
				chdir(saved_cwd);
				ft_putstr_fd("\x1b[31mERROR\x1b[0m: not authorized\n", fd);
				write(fd, "\0", 1);
			}
			else
			{
				ft_putstr_fd("\x1b[32mSUCCESS\x1b[0m\n", fd);
				write(fd, "\0", 1);
			}
		}
	}
}

char				*get_homedir(void)
{
	char			buff[1024];
	char			*homedir;

	if (getcwd(buff, sizeof(buff)) != NULL)
	{
		homedir = ft_strdup(buff);
	}
	ft_putstr("HOME: ");
	ft_putendl(homedir);
	return (homedir);
}

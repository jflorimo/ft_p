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

void	get_file(char *file, int fd)
{
	int rd;
	char recvBuff[256];
	// int fd_f;
	(void)fd;

	printf("#11#%s##", file);
	// if ((fd_f = open("CACA", O_RDWR | O_CREAT, 0777)) != -1)
	// {
	// 	printf("\x1b[31mFAILED\x1b[0m : file exist\n");
	// 	return ;
	// }
	while ((rd = read(fd, recvBuff, sizeof(recvBuff))) > 0)
	{
		recvBuff[rd] = '\0';
		printf("\x1b[34m%s\x1b[0m", recvBuff);
		// write(fd_f, recvBuff, sizeof(recvBuff));
		// printf("#####%d#####", fd_f);
			// strjoin pour faire une chaine et tenté de le write sur le fichier 
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/22 16:41:36 by jflorimo          #+#    #+#             */
/*   Updated: 2014/04/22 16:41:37 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libft.h>
#include <stdio.h>
#include "script.h"
#include "struct.h"

void					usage(char *str)
{
	printf("Usage: %s <port>\n", str);
	exit(-1);
}

int						create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		printf("Bind error\n");
		exit(-42);
	}
	listen(sock, 42);
	return (sock);
}

int						main(int argc, char *argv[])
{
	t_data				d;

	if (argc != 2)
		usage(argv[0]);
	d.port = ft_atoi(argv[1]);
	d.sock = create_server(port);
	d.count = 0;
	if (getcwd(d.buff, sizeof(d.buff)) != NULL)
	{
		d.homedir = ft_strdup(d.buff);
	}
	ft_putstr("HOME: ");
	ft_putendl(d.homedir);
	while ((d.cs = accept(d.sock, (struct sockaddr *)&(d.csin), &(d.cslen))) > 0)
	{
		if ((d.pid = fork()) == -1)
		{
			close(d.cs);
			continue ;
		}
		else if (d.pid > 0)
		{
			close(d.cs);
			d.count++;
			continue ;
		}
		else if (d.pid == 0)
		{
			d.count++;
		}
		while ((d.r = read(d.cs, d.buff, 1023)) > 0)
		{
			d.buff[d.r - 1] = '\0';
			printf("received %d bytes: [%s] from client N%d\n", d.r, d.buff, d.count);
			if (ft_strncmp("ls", d.buff, 2) == 0)
				ft_ls(d.cs);
			if (ft_strncmp("pwd", d.buff, 3) == 0)
				get_pwd(d.cs, ft_strlen(d.homedir));
			if (ft_strncmp("cd", d.buff, 2) == 0)
				set_cd(&(d.buff[3]), d.homedir);
		}
	}
	return (0);
}

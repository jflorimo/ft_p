/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 14:57:17 by jflorimo          #+#    #+#             */
/*   Updated: 2014/05/13 14:57:18 by jflorimo         ###   ########.fr       */
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
#include <fcntl.h>
#include "client.h"

void					usage(char *str)
{
	ft_putstr("Usage: ");
	ft_putstr(str);
	ft_putstr(" <port>\n");
	exit(-1);
}

int						create_client(char *addr, int port)
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
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putstr("Connect error\n");
		exit(-42);
	}
	return (sock);
}

void					get_result(t_datass d)
{
	while ((d.r2 = read(d.sock, d.buff, 1)) > 0 && d.buff[0] != '\0')
	{
		d.buff[d.r2] = '\0';
		write(1, d.buff, d.r2);
	}
}

void					process(t_datass d)
{
	d.buff[d.r - 1] = '\0';
	write(d.sock, d.buff, d.r);
	if (!ft_strncmp("pwd", d.buff, 3) || !ft_strncmp("ls", d.buff, 2) ||
		!ft_strncmp("cd", d.buff, 2))
	{
		get_result(d);
	}
	if (!ft_strncmp("put", d.buff, 3))
	{
		if (put_file(&(d.buff[4]), d.sock))
			get_result(d);
	}
	if (!ft_strncmp("get", d.buff, 3))
	{
		if (get_file(&(d.buff[4]), d.sock))
			get_result(d);
	}
	if (!ft_strncmp("quit", d.buff, 4))
	{
		close(d.sock);
		printf("leaving server ...\n");
		exit(1);
	}
	ft_putstr("JC% ");
}

int						main(int argc, char *argv[])
{
	t_datass			d;

	if (argc != 3)
		usage(argv[0]);
	d.port = ft_atoi(argv[2]);
	d.sock = create_client(argv[1], d.port);
	ft_putstr("JC% ");
	while ((d.r = read(0, d.buff, 1023)) > 0)
	{
		process(d);
	}
	close(d.sock);
	return (0);
}

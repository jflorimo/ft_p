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

void    usage(char *str)
{
    printf("Usage: %s <port>\n", str);
    exit(-1);
}

int        create_server(int port)
{
    int                    sock;
    struct protoent        *proto;
    struct sockaddr_in    sin;

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

int        main(int argc, char *argv[])
{
    int                    port;
    int                    sock;
    int                    cs;
    unsigned int        cslen;
    struct sockaddr_in    csin;
    int                    r;
    char                buff[1024];
    pid_t               child_pid;

    if (argc != 2)
        usage(argv[0]);
    port = ft_atoi(argv[1]);
    sock = create_server(port);
    child_pid = fork();
	while (42)
	{
		cs = accept(sock, (struct sockaddr *)&csin, &cslen);
		if (child_pid > 0)
		{
			printf("father");
		}
		else
		{
			printf("child");
		}
		while ((r = read(cs, buff, 1023)) > 0)
		{
			buff[r - 1] = '\0';
			printf("received %d bytes: [%s]\n", r, buff);
		}
		close(cs);
		close(sock);

	}
    return (0);
}

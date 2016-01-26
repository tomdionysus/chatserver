#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#include "chatserver.h"

int main() {
	int listen_sock_id, coms_sock_id;

	struct sockaddr_in server_addr;
	
	printf("Chatserver Starting on %d\n",CHATSERVER_PORT);

	memset( &server_addr, 0, sizeof(server_addr));

	listen_sock_id = socket(AF_INET,SOCK_STREAM,0);
	if (listen_sock_id < 0)
	{
		perror("socket:");
		exit(EXIT_FAILURE);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(CHATSERVER_PORT);

	if (bind(listen_sock_id, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("bind:");
		exit(EXIT_FAILURE);
	}
	
	if (listen(listen_sock_id, 1) < 0)
	{
		perror("listen:");
		exit(EXIT_FAILURE);
	}

	printf("Chatserver Listening\n");

	coms_sock_id = accept(listen_sock_id, NULL, NULL);
	if (coms_sock_id < 0)
	{
		fprintf(stderr, "accept failed errno: %d msg: %s\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

	char str[] = "Hello :)\n\x00";
	if (write(coms_sock_id, str, strlen(str)) < 0)
	{
		perror("write:");
		exit(EXIT_FAILURE);
	}

	if (close(listen_sock_id) < 0)
	{
		perror("close:");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}


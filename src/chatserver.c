#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#include "chatserver.h"

int main() {
	int listen_sock_id, coms_sock_id;

	struct sockaddr_in server_addr;
	
	printf("Chatserver Starting on %d\n",CHATSERVER_PORT);

	bzero( &server_addr, sizeof(server_addr));

	listen_sock_id = socket(AF_INET,SOCK_STREAM,0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(CHATSERVER_PORT);

	bind(listen_sock_id, (struct sockaddr*)&server_addr, sizeof(server_addr));
	
	listen(listen_sock_id, 1);

	printf("Chatserver Listening\n");

	coms_sock_id = accept(listen_sock_id, NULL, NULL);
	
	char str[] = "Hello :)\n\x00";
	write(coms_sock_id, str, strlen(str));

	close(listen_sock_id);
}


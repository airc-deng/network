#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>


#include <stdlib.h>
#include <sys/types.h>

#define PORT_NUM	8888

int main()
{
	int sfd,nfd;
	struct sockaddr_in s_add, c_add;
	int sin_size;
	
	/* create an endpoint for communication
	*  int socket(int domain, int type, int protocol);
	*  AF_INET             IPv4 Internet protocols
	*  SOCK_STREAM     Provides sequenced, reliable, two-way, connection-based  byte  streams.
	*/
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if( -1 == sfd){
		printf("create socket fail\n");
		return -1;
	}
	
	/* initialize the s_add with 0
	*  void bzero(void *s, size_t n);
	*  The bzero() function sets the first n bytes of the area starting at s to zero (bytes containing '\0').
	*/
	bzero(&s_add, sizeof(struct sockaddr_in));
	s_add.sin_family = AF_INET;
	//The  htonl()  function  converts  the unsigned integer hostlong from host byte order to network
    // byte order.
	s_add.sin_addr.s_addr = htonl(INADDR_ANY);
	//The htons() function converts the unsigned short integer hostshort from host byte order to net‐
    // work byte order.
	s_add.sin_port = htons(PORT_NUM);
	
	/*  bind a name to a socket
	* int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	*/
	if(-1 == bind(sfd, (struct sockaddr *)(&s_add), sizeof(struct sockaddr))){
		printf("bind fail!\n");
		return -1;
	}
	
	/* listen for connections on a socket
	*  int listen(int sockfd, int backlog);
	*  The backlog argument defines the maximum length to which the queue 
	*  of pending connections for sockfd may grow.
	*/
	if(-1 == listen(sfd, 5)){
		printf("listen fail\n");
		return -1;
	}
	
	while(1)
	{
		sin_size = sizeof(struct sockaddr_in);
		/* accept a connection on a socket
		*  int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
		*/
		nfd = accept(sfd, (struct sockaddr *)(&c_add), &sin_size);
		if(-1 == nfd){
			printf("accept fail!\n");
			return -1;
		}
		
		printf("accept ok! cli_addr:%x, port:%#x\n", ntohl(c_add.sin_addr.s_addr), ntohs(c_add.sin_port));

        //dont't know why always write fail
        /*
        if(-1 == write(nfd, "hello, welcome to server!\n"), 25){
            printf("write client fail\n");
            return -1;
        }
        */
		close(nfd);
	}
	
	close(sfd);
	return 0;
}

#include <Winsock2.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")

#define IP_ADDR		"127.0.0.1"
#define PORT_NUM	8888

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD( 1, 1 );
	
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		printf("WSAStartup fail!\n");
		return -1;
	}
		
	if ( LOBYTE( wsaData.wVersion ) != 1 ||
        HIBYTE( wsaData.wVersion ) != 1 ) {
		printf("wVersion wrong!\n");
		WSACleanup( );
		return -1;
	}

	SOCKET sockCli = socket(AF_INET, SOCK_STREAM, 0);
	
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(IP_ADDR);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(PORT_NUM);
	
	connect(sockCli, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR));
	
	char recvBuf[100];
	recv(sockCli, recvBuf, 100, 0);
	printf("%s \n", recvBuf);
	send(sockCli, "This is Client", strlen("This is Client")+1, 0);

	closesocket(sockCli);
	WSACleanup();

	return 0;
}
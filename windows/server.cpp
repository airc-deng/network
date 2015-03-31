#include <Winsock2.h>
#include <stdio.h>
#include <windows.h>

#pragma comment(lib,"ws2_32.lib")

#define PORT_NUM	8888
#define BUF_LEN		1024

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

	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(PORT_NUM);
	
	bind(sockSrv, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR));

	listen(sockSrv, 5);

	SOCKADDR_IN addrCli;
	int len = sizeof(SOCKADDR);

	while(1)
	{
		SOCKET sockConn = accept(sockSrv, (SOCKADDR *)&addrCli, &len);
		char sendBuf[BUF_LEN];
		sprintf(sendBuf, "Welcome !", addrCli.sin_addr, inet_ntoa(addrCli.sin_addr));
		send(sockConn, sendBuf, strlen(sendBuf)+1, 0);
		
		char recvBuf[BUF_LEN];
		recv(sockConn, recvBuf, BUF_LEN, 0);
		printf("%s \n", recvBuf);
		MessageBox(NULL, TEXT("recv msg!"), TEXT("get msg!"), MB_OK);
		closesocket(sockConn);
	}

	getchar();
	WSACleanup();
	return 0; 

}
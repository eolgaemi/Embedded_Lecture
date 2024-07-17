#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock;
	int clnt_sock;
	int wfd;
	int n_recv;
	char file_buf[100];
	int chunk_size = 100;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	char message[] = "Hello World!";

	wfd = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,0644);

	if(argc!=3){
			printf("Usage: ./server_file <port> <file> \n");
			exit(1);
	}

	serv_sock=socket(PF_INET,SOCK_STREAM,0);

	if(serv_sock <0){
		error_handling("socket () error");
	}
	// 구조체의 메모리를 초기화
	memset(&serv_addr, 0 ,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) <0){
		error_handling("bind() error");
	}
	if(listen(serv_sock,5)<0){
		error_handling("listen() error");
	}
	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);
	if(clnt_sock<0){
		error_handling("accept_error");
	}

	do{
			n_recv = read(clnt_sock,file_buf,chunk_size);
			write(wfd,file_buf,n_recv);
			printf("read : %d\n",n_recv);
	}while(n_recv>0);
	
	if(n_recv <= 0){
		close(clnt_sock);
		close(serv_sock);
		fputs("Done..",stdout);
		fputc('\n',stdout);
	}
	return 0;
}

void error_handling(char *message)
{
		fputs(message,stderr);
		fputc('\n',stderr);
		exit(1);
}

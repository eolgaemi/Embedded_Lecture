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

int main(int argc, char* argv[])
{	
	int serv_sock;
	int rfd;
	struct sockaddr_in serv_addr;
	int n_read,n_send;
	char file_buf[100];
	int chunk_size = 100;
	if(argc!=4){
		printf("Usage: ./client_file <IP> <PORT> <file>\n");
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);

	if(serv_sock <0)
			error_handling("socket () error");

	memset(&serv_addr, 0 , sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));

	if(connect(serv_sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr))<0)
			error_handling("connect() error");
	
	rfd = open(argv[3],O_RDONLY);

	if(rfd<0){
		fputs("<file> file open error",stderr);
		fputc('\n',stderr);
		perror("open");
		exit(1);
	}

	while(1){
		n_read = read(rfd,file_buf,chunk_size);
		if(n_read<=0){
			close(serv_sock);
			fputs("Done..",stdout);
			fputc('\n',stdout);
			break;
		}
		write(serv_sock,file_buf,n_read);
	}
	return 0;
}

void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

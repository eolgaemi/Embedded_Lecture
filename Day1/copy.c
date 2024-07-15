#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	
	if(argc < 3 ){
		write(2,"usage error",11);
		return -1;
	}

	int rfd,wfd,n;
	char buf[1024];

	rfd = open(argv[1],O_RDONLY | O_CREAT,0644);
	if(rfd == -1){
		perror("Open Read");
		exit(-1);
	}

	wfd = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,0644);
	if(wfd == -1){
		perror("Open Write");
		exit(-1);
	}

	while((n = read(rfd,buf,sizeof(buf))) >0)
		write(wfd,buf,n);

	close(rfd);
	close(wfd);

	return 0;
	
}


#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char* argv[]){
	int clnt_sock;
	struct sockaddr_in clnt_addr,your_adr;
	memset(&clnt_addr,0,sizeof(clnt_addr));

	clnt_sock = socket(PF_INET,SOCK_STREAM,0);
	clnt_addr.sin_family = AF_INET;
	clnt_addr.sin_port = htons(atoi(argv[2]));
	clnt_addr.sin_addr.s_addr = inet_addr(argv[1]);
	char input[30];
	int str_len;
	char buf[50];

	connect(clnt_sock,(struct sockaddr*)&clnt_addr,sizeof(clnt_addr));
	socklen_t sock_len;
	sock_len = sizeof(your_adr);
	while(1){
		printf("===========================================================================\n");
		printf("실시간 검색어를 보고 싶은 사이트를 선택하여 주십시오.\n");
		printf("1. 네이버 2. 다음\n");
		
		fgets(input,30,stdin);
		write(clnt_sock,input,30);
		if(input[0] == '1'){
			printf("\n네이버의 현재 검색 순위 .... \n");
			for(int i=0;i<20;i++){
				str_len = read(clnt_sock,buf,50);
				buf[str_len] = '\0';
				printf("%d. %s\n",i+1,buf);
			}

			break;

		}
		else if(input[0] == '2'){
			printf("\n다음의 현재 검색 순위 ....\n");
			for(int i=0;i<10;i++){
				str_len = read(clnt_sock,buf,50);
				buf[str_len] = '\0';
				printf("%d. %s\n",i+1,buf);
			}
			break;
		}
		}
	
}

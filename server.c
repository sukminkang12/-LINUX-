#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define TTL 64


char *buf_temp[20];
char *buf_daum[10];


struct sockaddr_in my_adr,your_adr;

void daum(int clnt_sock){
	system("wget https://www.daum.net");

	FILE *fp = fopen("index.html","r");
	char buf[1024];
	int count=0;
	char *temp;
	int i= 0;
	while(count!=5000){
		fgets(buf,1024,fp);
		if((count>=2181&&count<=2289)){
			if(count%12== 9){
			       temp = strtok(buf,">");
		       		temp = strtok(NULL,">");
		 		temp = strtok(NULL,"<");		
				write(clnt_sock,temp,strlen(temp));
			}
		}		
		count++;
	}

	fclose(fp);
	system("rm index.html");

}

void naver(int clnt_sock){
	system("wget https://datalab.naver.com/keyword/realtimeList.naver");

	FILE *fp = fopen("realtimeList.naver","r");
	char buf[1024];
	fscanf(fp,"%s",buf);

	int count =0;
	char *temp;
	int i=0;
	while(count!=500){
		fgets(buf,1024,fp);
		if((count>=356)&&(count<=470)){
			if(count%6 ==2){
				temp = strtok(buf,">");
				temp = strtok(NULL,">");
				buf_temp[i] = strtok(temp,"<");
				write(clnt_sock,buf_temp[i],strlen(buf_temp[i]));
				i++;
			}
		}
		count++;
	}

	system("rm realtimeList.naver");

}



int main(int argc,char* argv[]){
	 int serv_sock,clnt_sock;
	 
	 char message[30];
	 socklen_t sock_len;
	 
	 serv_sock = socket(PF_INET,SOCK_STREAM,0);

	 memset(&my_adr,0,sizeof(my_adr));

	 my_adr.sin_family = AF_INET;
	 my_adr.sin_port = htons(atoi(argv[1]));
	 my_adr.sin_addr.s_addr = htonl(INADDR_ANY);

	 if(bind(serv_sock,(struct sockaddr*)&my_adr,sizeof(my_adr)) == -1)
		 fputs("ERROR",stderr);
	 sock_len = sizeof(your_adr);
	 listen(serv_sock,5);
	 char input[30];
	 for(int i=0;i<5;i++){
		 clnt_sock = accept(serv_sock,(struct sockaddr*)&your_adr,&sock_len);
		 read(clnt_sock,input,30);
		 if(input[0]=='1'){
			 naver(clnt_sock);
			 puts("네이버 실시간 검색어 전송 완료");
		 }
		 else if(input[0] =='2'){
			 daum(clnt_sock);
			 puts("다음 실시간 검색어 전송 완료");
		 }
	 }



}

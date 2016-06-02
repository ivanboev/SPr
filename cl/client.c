#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>/
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 8000
#define SERVER_IP "127.0.0.1"
#define MAXSZ 100
int main()
{
 int sockfd;

 struct sockaddr_in serverAddress;

 int n;
 char msg1[MAXSZ];
 char msg2[MAXSZ];
 FILE *fp;
 int choice;

 //create socket
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 //initialize the socket addresses
 memset(&serverAddress,0,sizeof(serverAddress));
 serverAddress.sin_family=AF_INET;
 serverAddress.sin_addr.s_addr=inet_addr(SERVER_IP);
 serverAddress.sin_port=htons(PORT);

 connect(sockfd,(struct sockaddr *)&serverAddress,sizeof(serverAddress));

 printf("\nChoose your username:\n");
 fgets(msg1,MAXSZ,stdin);
   if(msg1[0]=='#'){
  	return(-1);
   }
  n=strlen(msg1)+1;
  send(sockfd,msg1,n,0);
  
 while(1)
 {
    {
      printf("Download file: 1:GTAV.txt, 2:WoW.txt, 3:DOTA2.txt\n");
      scanf("%d", &choice);
      char info[1024];
      switch(choice)
	{
	case 1:
	  fp = fopen("GTAV.txt", "r");
	  fgets(info,1024,fp);
	  send(sockfd, "GTAV.txt", 8, 0);
	  n = strlen(info) + 1;
	  send(sockfd,info,n,0);
	  break;
	case 2:
	  fp = fopen("WoW.txt", "r");
	  fgets(info,1024,fp);
	  send(sockfd, "WoW.txt", 7, 0);
	  n = strlen(info) + 1;
	  send(sockfd,info,n,0);
	  break;
	case 3:
	  fp = fopen("DOTA2.txt", "r");
	  fgets(info,1024,fp);
	  send(sockfd, "DOTA2.txt", 9, 0);
	  n = strlen(info) + 1;
	  send(sockfd,info,n,0);
	  break;
	}

  n=recv(sockfd,msg2,MAXSZ,0);

  printf("Received message from  server::%s\n",msg2);
 }
}
 return 0;
}

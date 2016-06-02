#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/sendfile.h>

#define PORT 8000
#define MAXSZ 100
int main()
{
 int sockfd;
 int newsockfd;

 struct sockaddr_in serverAddress;
 struct sockaddr_in clientAddress;

 int n;
 char msg[MAXSZ];
 int clientAddressLength;
 int pid;

 //create socket
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 //initialize the socket addresses
 memset(&serverAddress,0,sizeof(serverAddress));
 serverAddress.sin_family=AF_INET;
 serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
 serverAddress.sin_port=htons(PORT);
 printf("Server waiting for clients\n");

 bind(sockfd,(struct sockaddr *)&serverAddress, sizeof(serverAddress));

 listen(sockfd,5);

 while(1)
 {
  clientAddressLength=sizeof(clientAddress);
  newsockfd=accept(sockfd,(struct sockaddr*)&clientAddress,&clientAddressLength);
  printf("connected to client: %s\n",inet_ntoa(clientAddress.sin_addr));

  
  pid=fork();
  if(pid==0)
  {
	n = recv(newsockfd,msg,MAXSZ,0);
	if(n==0)
    {
     close(newsockfd);
     break;
    }
	FILE *fp;
	fp=fopen("savedRequests.txt", "a");  
	printf("New client connected: %s", msg);
  
   while(1)
   {
        
	fprintf(fp,"%s",msg);
	
	n=recv(newsockfd,msg,MAXSZ,0);
	
	fprintf(fp,"%s",msg);
	printf("File info saved");
    if(n==0)
    {
     close(newsockfd);
     break;
    }
       
   }
  exit(0);
  }
  else
  {
   close(newsockfd);
  }
 }

 return 0;
}



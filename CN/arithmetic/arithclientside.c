#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>
#include<netinet/in.h>

#define PORT 7778

void chatting(int connfd)
{
	int n1,n2,res,ch;
	printf("\t\tMAIN MENU\n");
	printf("1. Add\n2. Subtract\n3. Multiply\n4. Divide\nEnter your choice: ");
	scanf("%d",&ch);
	write(connfd,&ch,sizeof(ch));
	printf("Enter any number: ");
	scanf("%d",&n1);
	write(connfd,&n1,sizeof(n1));
	printf("Enter any number: ");
	scanf("%d",&n2);
	write(connfd,&n2,sizeof(n2));
	read(connfd,&res,sizeof(res));
	printf("Result: %d",res);
}

int main()
{
	int sockfd,len,connfd;
	struct sockaddr_in servaddr,cli;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("\nSocket creation failed");
		exit(0);
	}
	else
	{
		printf("\nSocket created");
	}
	
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=INADDR_ANY;
	servaddr.sin_port=htons(PORT);
	if((connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)))==-1)
	{
		printf("\nConnection failed");
		exit(0);
	}
	else
	{
		printf("\nConnection success");
	}
	
	chatting(sockfd);
	close(sockfd);
	return 0;
}

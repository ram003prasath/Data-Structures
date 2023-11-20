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

void chatting(int connfd,int sockfd)
{
	int n1,n2,res,ch;
	read(connfd,&ch,sizeof(ch));
	printf("Client's choice: %d\n",ch);
	read(connfd,&n1,sizeof(n1));
	printf("From client: %d\n",n1);
	read(connfd,&n2,sizeof(n2));
	printf("From client: %d\n",n2);
	switch(ch)
	{
		case 1:res=n1+n2;break;
		case 2:res=n1-n2;break;
		case 3:res=n1*n2;break;
		case 4:res=n1/n2;break;
	}
	printf("Result: %d\n",res);
	write(connfd,&res,sizeof(res));
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
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(PORT);
	if((bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)))==-1)
	{
		printf("\nBind failed");
		exit(0);
	}
	else
	{
		printf("\nBind success");
	}
	 if (listen(sockfd, 10) == 0)
    	{
        	printf("Listening...\n");
    	}
    	else
    	{
       	printf("Error in listening\n");
        	exit(1);
    	}
	
	len=sizeof(cli);
	connfd=accept(sockfd,(struct sockaddr*)&cli,&len);
	if(connfd==-1)
	{
		printf("\nAccept failed");
		exit(0);
	}
	else
	{
		printf("\nAccept success");
	}
	
	chatting(connfd,sockfd);
	close(sockfd);
	return 0;
}


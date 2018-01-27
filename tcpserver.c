#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#define BUFFER 1024

void send_recv(int s)
{
	char buf[BUFFER];
	int i;
	
	//Receiving data from client
	recv(s,buf,BUFFER,0);
	printf("Message from Client... %s\n", buf);

	//The message is converted into upper case. 
    for(i=0; buf[i]; i++) {
    	buf[i] = toupper(buf[i]);
    }    
    printf("Message send to Client....%s\n",buf);
	send(s,buf,BUFFER,0);
}

int main()
{
 	int socks, cli_s, length;
 	struct sockaddr_in serv,cli;
 	pid_t pid;
 	puts("TCP Server...");
	
	//Creating Socket
 	socks=socket(AF_INET,SOCK_STREAM,0);
 	puts("Socket Created Successfully...");
	
	//Socket Address Structure
 	serv.sin_family=AF_INET;
 	serv.sin_addr.s_addr=INADDR_ANY;
 	serv.sin_port=htons(3500);
	
 	bind(socks,(struct sockaddr*)&serv,sizeof(serv));
 	puts("Binding Done...");
 	listen(socks, 5);
 	puts("Listening for Client...");
 	
 	for(;;)
 	{
		length = sizeof(cli);
		
		//Accepting Client Connection
		cli_s=accept(socks,(struct sockaddr*)&cli,&length);
		puts("\nConnected to Client...");

		//Creating Child Process
		if((pid=fork()) == 0){
			puts("Child process created...");
			close(socks);
			send_recv(cli_s);
			close(cli_s);
			exit(0);
		}
	close(cli_s);
 }
 return 0;
}
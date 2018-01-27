#include<stdio.h>
//#include<string.h>
#include<sys/socket.h>
//#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#define BUFFER 1024
#define TCP_PORT 3500
#define UDP_PORT 3600
#define SERVER "127.0.0.1"

void* tcpclient(void *arg)
{
    char *msg = arg;
    int ls;
    struct sockaddr_in cli;
    //printf("TCP Client...");

    // Creating Socket
    ls = socket(AF_INET,SOCK_STREAM,0);
    //printf("TCP Socket Created Successfully...");
  
    // Socket Address Structure
    cli.sin_family=AF_INET;
    cli.sin_addr.s_addr=inet_addr(SERVER);
    cli.sin_port=htons(TCP_PORT);

    fflush(stdout);
  
    // Connecting to Server
    connect(ls,(struct sockaddr*)&cli,sizeof(cli));
    //printf("\nConnected with TCP Server...");

    char buf[BUFFER];
    send(ls,msg,BUFFER,0); //Sending Data to Server
    recv(ls,buf,BUFFER,0); //Receiving Data from Server
	
    printf("\nUppercase Output from  TCP server:%s",buf); 
    close(ls);
}

void* udpclient(char *buffer[])
{

  int clientSocket, portNum, n;
  
  struct sockaddr_in server;
  socklen_t addr_size;

  //create a TCP socket
  clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

  server.sin_family = AF_INET;
  server.sin_port = htons(UDP_PORT);
  server.sin_addr.s_addr = inet_addr(SERVER);
  memset(server.sin_zero, '\0', sizeof (server.sin_zero));  

  addr_size = sizeof server;

  n = strlen(buffer) + 1;
  printf("\nSending from UDP client=%s",buffer);
    
  //Send to the server
  sendto(clientSocket,buffer,n,0,(struct sockaddr *)&server,addr_size);

  //get from the server
  n= recvfrom(clientSocket,buffer,1024,0,NULL, NULL);

  sleep(3);

  printf("\nReverse Output from  UDP server:%s\n",buffer);
}

int main(void)
{
  char in[BUFFER];
  pthread_t t1,t2;
  while(1)
  {
      printf("\nEnter sentence to send to the servers: ");
      fgets(in, BUFFER, stdin);

      pthread_create(&t1,NULL,&tcpclient,in);
      pthread_create(&t2,NULL,&udpclient,in);

      sleep(5);
  //    pthread_join(t1,NULL);
  //    pthread_join(t2,NULL);
  }
  return 0;
}

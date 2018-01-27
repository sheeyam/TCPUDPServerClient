#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

void reverseArray(char arr[], int start, int end)
{
    char temp;
    while (start < end)
    {
        temp = arr[start];   
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }   
}

int main(){

  int udpsocket, n;
  char buffer[1024];
  struct sockaddr_in serv_addr,cli_addr;
  //struct sockaddr_out cli_addr;
  socklen_t addr_size;
  int i;

  //Creating a UDP socket
  udpsocket = socket(AF_INET, SOCK_DGRAM, 0);

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(3600);
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serv_addr.sin_zero, '\0', sizeof serv_addr.sin_zero);  

  //Bind the local address
  bind(udpsocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

  addr_size = sizeof cli_addr;

  while(1)
{
//Reading data from socket
n = recvfrom(udpsocket,buffer,1024,0,(struct sockaddr *)&cli_addr, &addr_size);

printf("\ninitial value in buffer=%s",buffer); 

//Reversing the data
reverseArray(buffer,0,strlen(buffer)-1);
//reverse(buffer,0,strlen(buffer)-1);

printf("\nValue after reversing=%s",buffer);
//Sending data to Client back
sendto(udpsocket,buffer,n,0,(struct sockaddr *)&cli_addr,addr_size);

 }


}


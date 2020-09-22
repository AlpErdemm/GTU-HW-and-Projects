#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
  
int main(int argc, char const *argv[])
{
    	struct sockaddr_in address;
    	int sock = 0, valread;
    	struct sockaddr_in serv_addr;
    	char *message = "Hileci C 45";
   	char buffer[1024] = "\0";
	sock = socket(AF_INET, SOCK_STREAM, 0);

  
    	memset(&serv_addr,'0', sizeof(serv_addr));
  
    	serv_addr.sin_family = AF_INET;
    	serv_addr.sin_port = htons(5555);
      
  
    	inet_pton(AF_INET,"127.0.0.1", &serv_addr.sin_addr);

	connect(sock,(struct sockaddr *)&serv_addr, sizeof(serv_addr));

    	send(sock ,message ,strlen(message) ,0);
    	return 0;
}


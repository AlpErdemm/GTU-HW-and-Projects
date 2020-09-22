#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <math.h>
#include <signal.h>
#include  <sys/types.h>

#define struct_size 7

pthread_mutex_t	my_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;

int worker;
int x;


struct Providers{
	char name[50];
	int performance;
	int price;
	int duration;
}mami[struct_size];

double factorial(double f);

void choose(char * client_name, char client_process, int client_number);

void *server_function(void *ptr);
void *freer_thread(void *ptr);
void sig_handler();

int main(int argc, char **argv){


   	 struct sigaction my_sig;

    	memset(&my_sig, 0, sizeof(my_sig));
    	my_sig.sa_handler = sig_handler;
    	sigemptyset(&my_sig.sa_mask);
    	sigaddset(&my_sig.sa_mask, SIGINT);
    	sigaction(SIGINT, &my_sig, NULL);

	
	srand(time(NULL));
	
	int i = 0, j = 0;
 	int server_fd, new_socket, valread;
    	struct sockaddr_in address;
    	int opt = 1;
    	int addrlen = sizeof(address);

	char client_name[50];
	char client_process;
	int  client_number;

   	char buffi[1024] = "\0";
    	char *hello = "Hello from server";	
	char buffer[255];
	FILE * f;

	if(argv[1] == NULL){
		printf("No main arguments!\n");
		exit(0);
	}
	f = fopen(argv[1], "r");

	printf("%d provider threads created\n", struct_size);

	while(fgets(buffer, 255, f)){
		printf("%s", buffer);
		if(i != 0){
			sscanf(buffer, "%s %d %d %d", mami[i-1].name, &mami[i-1].performance, &mami[i-1].price, &mami[i-1].duration);
		}
		i++;
	}
    	pthread_t threads[struct_size];
	pthread_t freer;

	for(j = 0; j < struct_size; j++){
		pthread_create(&threads[j], NULL, server_function, (void*) j);	
	}
	
 	server_fd = socket(AF_INET, SOCK_STREAM, 0);
      
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
   	address.sin_family = AF_INET;
   	address.sin_addr.s_addr = INADDR_ANY;
   	address.sin_port = htons(5555);
      
    	bind(server_fd, (struct sockaddr *)&address, sizeof(address));

	listen(server_fd, 3);
	
	printf("Server is waiting for client connections at port 5555\n");

	while(1){
		new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen);
    		read( new_socket , buffi, 1024);
   		printf("Client %s connected,",buffi);
		sscanf(buffi, "%s %c %d", client_name, &client_process, &client_number);
		choose(client_name, client_process, client_number);
		pthread_create(&freer, NULL, freer_thread, NULL);	
	}
   	return 0;
}
void *freer_thread(void *ptr)
{
	pthread_mutex_lock(&my_mutex);
	pthread_cond_broadcast(&cond_var);
	pthread_mutex_unlock(&my_mutex);	

}

void *server_function(void *ptr)
{
	int count = 1, i = 0;
	double result = 0.0, temp, temp2, dude, real_x = x / 180;

   	struct timespec tim, tim2;
  	tim.tv_sec = 5 + (rand() % 10);
   	tim.tv_nsec = 0;

	dude = tim.tv_sec;
	
	int prog = (int) ptr; 
	printf("Provider %s waiting for tasks\n",mami[prog].name);
     	 while(1){
		pthread_mutex_lock(&my_mutex);
      		pthread_cond_wait(&cond_var, &my_mutex);
		if(worker == prog){
			printf("Provider %s is processing task number %d: %d\n", mami[prog].name, count, x);
			result = 0.0;
			for(i = 2; i < 100; i+=4)
			{
				temp = (double)pow(real_x, i)/factorial(i);
				temp2 = (double)pow(real_x,i+2)/factorial(i+2);
				result += temp2 - temp;
			}

			result = 1 - result;

			nanosleep(&tim , &tim2);
			
			printf("Provider %s completed task number %d: cos(%d)= %.1f in %.1f seconds.\n", mami[prog].name, count, x, result, dude);	
			count++;			
		}
		pthread_mutex_unlock(&my_mutex);
	}     
}

void choose(char * client_name, char client_process, int client_number)
{
	int i = 0, cost = mami[0].price, the_thing = 0, qua = mami[0].performance;
	if(client_process == 'C'){
		for(i = 1; i < struct_size; i++){
			if(mami[i].price < cost){
				cost = mami[i].price;
				the_thing = i;
			}
		}
	}	
	else if(client_process == 'Q'){
		for(i = 1; i < struct_size; i++){
			if(mami[i].performance < qua){
				qua = mami[i].price;
				the_thing = i;
			}
		}	
	}
	else if(client_process == 'T'){
		for(i = 1; i < struct_size; i++){
			if(mami[i].performance < qua){
				qua = mami[i].price;
				the_thing = i;
			}
		}		
	}
	else{
		printf("Woops.\n");
		exit(0);
	}
	printf(" forwarded to provider %s\n", mami[the_thing].name);
	worker = the_thing;
	x = client_number;
}
double factorial(double f)
{
    	if (f == 0) 
      	  	return 1;
    	return(f * factorial(f - 1));
}
void sig_handler()
{
	
   	 printf("Termination signal recieved\nTerminating all providers\nTerminating all clients\n", getpid());
   	 while(wait(NULL)!= -1);
    	 exit(1);
}





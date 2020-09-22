#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265
#define F_SIZE 20

void my_handler1(int signum);
void my_handler2(int signum);
void my_handler3(int signum);

int count_line();

int control, N, M;
FILE * filep;
char text[F_SIZE];

pid_t parent_pid;
pid_t child_pid;

int main(int argc, char ** argv){
	pid_t second;
	
	int i, j, k, while_count, main_count, one = 1, count1 = 1, count2 = 1, arr[5], carry;
	double re, im;
	char temp, * dummy = "\0", *str;
	srand(time(NULL));
	
	parent_pid = getpid();	

	if(argc < 6){
		printf("Insufficient arguments, try again. Example: ./exe -N 5 -X file.dat -M 100.\n");
		exit(0);
	}

	for(i = 0; i < argc; i++){
		if(strcmp(argv[i], "-N") == 0){
			N = atoi(argv[i+1]);
		}
		if(strcmp(argv[i], "-M") == 0){
			M = atoi(argv[i+1]);
		}
		if(strcmp(argv[i], "-X") == 0){
			strcpy(text, argv[i+1]);
		} 	
	}
	control = 1;

	second = fork();

	signal(SIGUSR1, my_handler1);
	signal(SIGUSR2, my_handler2);
	signal(SIGINT, my_handler3);
	
	child_pid = second;

	if(second == 0){
		main_count = M;
		while(1){
			if(control == 2){
				printf("Process B:the dft of line %d (", count1);
				filep = fopen(text ,"a+");
				if(filep == NULL){
					printf("Error: opening the file.\n");
					exit(0);
				}
				while_count = N;
				i = 0;
				while(while_count){
					fscanf(filep, "%c", &temp);
					printf("%c ", temp);
					carry = temp - '0';
					arr[i] = carry;
					while_count--;
					i++;
				}
				printf(") is: "); 								
				fclose(filep);
				filep = fopen(text ,"w");
				if(filep == NULL){
					printf("Error: opening the file.\n");
					exit(0);
				}
				fclose(filep);
				filep = NULL;
				for(k = 0; k < N; k++){
					re = 0; im = 0;
					for(j = 0; j < N; j++){
						re += arr[j] * cos((2 * PI * j * k) / N-1);
						im += -(arr[j] * sin((2 * PI * j * k) / N-1));
					}	
					if(im < 0) printf("%.2lf%.2lfi ", re, im);
					else printf("%.2lf+%.2lfi ", re, im);
				}
				printf("\n");
				if(count1 >= M) count1-=2;
				count1++;
				kill(parent_pid, SIGUSR1);
				kill(child_pid, SIGUSR1);
			}
		}
	}
	else{		
		main_count = M;
		while(1){
			if(control == 1){
				printf("Process A: i’m producing a random sequence for line %d: ", count2);				
				filep = fopen(text ,"a");
				if(filep == NULL){
					printf("Error: opening the file.\n");
					exit(0);
				}
				while_count = N;
				while(while_count){
					one = rand() % 10;
					printf("%d ", one);
					fprintf(filep, "%d", one);
					while_count--;
				}
				fprintf(filep, "\n");
				fclose(filep);
				filep = NULL;
				printf("\n");
				if(count2 >= M) count2-=2;
				count2++;
				kill(child_pid, SIGUSR2);
				kill(parent_pid, SIGUSR2);
				
			}

		}
	}
	

	return 0;
}
void my_handler1(int signum)
{
    if (signum == SIGUSR1)
    {
        control = 1;
    }
}
void my_handler2(int signum)
{
    if (signum == SIGUSR2)
    {
        control = 2;
    }
}
void my_handler3(int signum){
    if (signum == SIGINT)
    {
        if(control == 2){
		if(filep != NULL){
			fclose(filep);
		}
		kill(parent_pid, SIGTERM);
		kill(child_pid, SIGTERM);
	}
        if(control == 1){
		if(filep != NULL){
			fclose(filep);
		}
		kill(child_pid, SIGTERM);
		kill(parent_pid, SIGTERM);
	}
    }	
}

int count_line()
{
	FILE * p;
	int count = 0;
	char temp;
	p = fopen(text ,"r");

	if(p == NULL) return 0;

	while(!feof(p))
	{
	  temp = fgetc(p);
	  if(temp == '\n')
	  {
	    count++;
	  }
	}

	fclose(p);

	return count;
}

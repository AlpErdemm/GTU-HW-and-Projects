#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <time.h>
#include <string.h>
#include <signal.h>

int forks;
    //Eggs = 0, Butter = 1, Sugar = 2, Flour = 3
    //Chef 1 lacks eggs, butter
    //Chef 2 lacks eggs, sugar
    //Chef 3 lacks eggs, flour
    //Chef 4 lacks butter, sugar
    //Chef 5 lacks butter, flour
    //Chef 6 lacks sugar, flour
    
struct sembuf ops[2];
static char arr[10];

int wait_chef1();
int wait_chef2();
int wait_chef3();
int wait_chef4();
int wait_chef5();
int wait_chef6();
int post_chef1();
int post_chef2();
int post_chef3();
int post_chef4();
int post_chef5();
int post_chef6();
int seller_wait();
int seller_post(int i, int j);
void name(int a);
void sig_handler();

int main()
{
    struct sigaction my_sig;

    memset(&my_sig, 0, sizeof(my_sig));
    my_sig.sa_handler = sig_handler;
    sigemptyset(&my_sig.sa_mask);
    sigaddset(&my_sig.sa_mask, SIGINT);
    sigaction(SIGINT, &my_sig, NULL);

	srand(time(NULL));
    int intarr[5] = {0,0,0,0,0};
    forks = semget(666, 5, IPC_CREAT|0600);
    semctl(forks, 1, SETALL, intarr);
    int temp, give[2], lack[6][2] = {{0,1},{0,2},{0,3},{1,2},{1,3},{2,3}};
    give[0] = give[1] = rand() % 4;
    while(give[0] == give[1]) give[1] = rand() % 4;
    if(give[0] > give[1]){
        temp = give[0];
        give[0] = give[1];
        give[1] = temp;
    }
    if(fork() == 0){
        while(1){
        	printf("Chef #1 is currently waiting for eggs and butter.\n");
            wait_chef1();
            printf("Chef #1 is preparing the dessert.\n");
            post_chef1();
        }
    }
    if(fork() == 0){
        while(1){
        	printf("Chef #2 is currently waiting for eggs and sugar.\n");
            wait_chef2();
            printf("Chef #2 is preparing the dessert.\n");
            post_chef2();
        }
    }
    if(fork() == 0){
        while(1){
        	printf("Chef #3 is currently waiting for eggs and flour.\n");
            wait_chef3();
            printf("Chef #3 is preparing the dessert.\n");
            post_chef3();
        }
    }
    if(fork() == 0){
        while(1){
        	printf("Chef #4 is currently waiting for butter and sugar.\n");
            wait_chef4();
            printf("Chef #4 is preparing the dessert.\n");
            post_chef4();
        }
    }
    if(fork() == 0){
        while(1){
        	printf("Chef #5 is currently waiting for flour and butter.\n");
            wait_chef5();
            printf("Chef #5 is preparing the dessert.\n");
            post_chef5();
        }
    }
    if(fork() == 0){
        while(1){
        	printf("Chef #6 is currently waiting for sugar and flour.\n");
            wait_chef6();
            printf("Chef #6 is preparing the dessert.\n");
            post_chef6();
        }
    }
    if(fork() == 0){
        while(1){
        	printf("wholesaler delivers ");
            name(give[0]);
            printf("%s", arr);
            name(give[1]);
            printf(" and %s\n", arr);
        	seller_post(give[0], give[1]);
            give[0] = give[1] = rand() % 4;
            while(give[0] == give[1]) give[1] = rand() % 4;
                if(give[0] > give[1]){
                    temp = give[0];
                    give[0] = give[1];
                    give[1] = temp;
                }
            printf("wholesaler is waiting for the dessert\n");
            seller_wait();
            printf("wholesaler has obtained the dessert and left to sell it\n");
        }
    } 
    for(int i = 0; i < 7; i++) wait(NULL);     
}
void name(int a){
	if(a == 0) strcpy(arr, "eggs");
	else if(a == 1) strcpy(arr, "butter");
	else if(a == 2) strcpy(arr, "sugar");
	else if(a == 3) strcpy(arr, "flour");
}
int wait_chef1(){
    ops[0].sem_num = 0;
    ops[1].sem_num = 1;
    ops[0].sem_op = ops[1].sem_op = -1;
    ops[0].sem_flg = ops[1].sem_flg = 0;
    return semop(forks,ops, 2);
}
int wait_chef2(){
    ops[0].sem_num = 0;
    ops[1].sem_num = 2;
    ops[0].sem_op = ops[1].sem_op = -1;
    ops[0].sem_flg = ops[1].sem_flg = 0;
    return semop(forks,ops, 2);
}
int wait_chef3(){
    ops[0].sem_num = 0;
    ops[1].sem_num = 3;
    ops[0].sem_op = ops[1].sem_op = -1;
    ops[0].sem_flg = ops[1].sem_flg = 0;
    return semop(forks,ops, 2);
}
int wait_chef4(){
    ops[0].sem_num = 1;
    ops[1].sem_num = 2;
    ops[0].sem_op = ops[1].sem_op = -1;
    ops[0].sem_flg = ops[1].sem_flg = 0;
    return semop(forks,ops, 2);
}
int wait_chef5(){
    ops[0].sem_num = 1;
    ops[1].sem_num = 3;
    ops[0].sem_op = ops[1].sem_op = -1;
    ops[0].sem_flg = ops[1].sem_flg = 0;
    return semop(forks,ops, 2);
}
int wait_chef6(){
    ops[0].sem_num = 2;
    ops[1].sem_num = 3;
    ops[0].sem_op = ops[1].sem_op = -1;
    ops[0].sem_flg = ops[1].sem_flg = 0;
    return semop(forks,ops, 2);
}

int seller_wait(){
    ops[0].sem_num = 4;
    ops[0].sem_op = -1;
    ops[0].sem_flg = 0;
    return semop(forks,ops, 2);
}

int seller_post(int i, int j){
    ops[0].sem_num = i;
    ops[1].sem_num = j;
    ops[0].sem_op = ops[1].sem_op = 1;
    ops[0].sem_flg = ops[1].sem_flg = 0;
    return semop(forks,ops, 2);
}

int post_chef1(){
    ops[0].sem_num = 4;
    ops[0].sem_op = 1;
    ops[0].sem_flg = 0;
    return semop(forks,ops, 1);
}
int post_chef2(){
    ops[0].sem_num = 4;
    ops[0].sem_op = 1;
    ops[0].sem_flg = 0;
    return semop(forks,ops, 1);
}
int post_chef3(){
    ops[0].sem_num = 4;
    ops[0].sem_op = 1;
    ops[0].sem_flg = 0;
    return semop(forks,ops, 1);
}
int post_chef4(){
    ops[0].sem_num = 4;
    ops[0].sem_op = 1;
    ops[0].sem_flg = 0;
    return semop(forks,ops, 1);
}
int post_chef5(){
    ops[0].sem_num = 4;
    ops[0].sem_op = 1;
    ops[0].sem_flg = 0;
    return semop(forks,ops, 1);
}
int post_chef6(){
    ops[0].sem_num = 4;
    ops[0].sem_op = 1;
    ops[0].sem_flg = 0;
    return semop(forks,ops, 1);
}
void sig_handler()
{
    printf("Process %d terminated.\n", getpid());
    while(wait(NULL)!= -1);
    exit(1);
}

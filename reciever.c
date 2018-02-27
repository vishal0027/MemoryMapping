#include <stdio.h>
#include <memory.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
int trminte = 0;
void printing();
void terminate();
int in = 1;
int main(int argc, char* argv[]){
    //creation of process
   	 printf("The pid is %d\n", getpid());
   	 struct sigaction saction;
	 struct sigaction taction;
  	 sigset_t block_mask;

 	 /* Establish the signal handler. */
  	 sigfillset (&block_mask);

  	 sigdelset(&block_mask, SIGUSR1);
  	 sigdelset(&block_mask, SIGTERM);

 	 saction.sa_handler = printing;
	 taction.sa_handler = terminate;
 	 saction.sa_mask = block_mask;
	 taction.sa_mask = block_mask;
  	 saction.sa_flags = 0;
  	 taction.sa_flags = 0;
	 
 	 sigaction (SIGUSR1, &saction, NULL);
 	 sigaction (SIGTERM, &taction, NULL);

	
   	 while(!(trminte)){
   	 	//printf("waiting for signal\n");
   	 	sigsuspend(&block_mask);
 	   }
  	  printf("Safely Terminated\n");
}

void printing(){ 
		struct stat myst;
   		char *mamP;
   		int fd;
		fd = open("sharedfile",O_RDWR);
		if(fd == -1){
			perror("OPEN FAILED");
			exit(1);
		}
		if(fstat(fd, &myst) < 0){
			perror("fstat error");
			close(fd);
			exit(1);
		}
				//maps the memory
		mamP = mmap(0, myst.st_size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
		if(mamP == MAP_FAILED){
			perror("MAP FAILED");
			close(fd);
			exit(1);
		}
			
		while(mamP[in] != '\0'){
			printf("%c", mamP[in]);
			in++;			
		}
		
	}
	
void terminate(){
	trminte = 1;
}



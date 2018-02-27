#include <stdio.h>
#include <memory.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
int main(int argc, char* argv[]){
	if((argc < 1)){	
	   	printf("USAGE := sender [pid of reciever] ");
		exit(1);
	}
	pid_t pid = atoll(argv[1]);
	// Opens the file 
   	int fd;
   	struct stat myst;
   	char *mamP;
   	fd = open("sharedfile",O_RDWR);
	
	// Error Checking
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
	int count = 1;
	while(count < myst.st_size){
		char c;
		while ((c = getchar()) != '\n'){
		 	if(count != myst.st_size){
		   		 mamP[count] = c;
		  		 count++;
			}
		    }
	 mamP[count] = '\n';
	 count++;
	 kill(pid, SIGUSR1);

	}
	 kill(pid, SIGTERM);
}

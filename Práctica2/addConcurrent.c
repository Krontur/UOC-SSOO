#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
	
	struct stat fileStat;
	int fileSize;
	char fileName[128], buffer1[128];
	int addition;
	off_t offset=0;
		
	if(stat(argv[1], &fileStat) == -1){
		perror("ERROR stat");
		exit(EXIT_FAILURE);
	}
	strcpy(fileName, argv[1]);
	fileSize = fileStat.st_size;
	
	int N = atoi(argv[2]);
	int numBin, res, toAddNumbers, toAddNumbersChild, pid,
		totalAddedNumbers=0, addedNumbers=0;
		
	numBin = open(fileName, O_RDONLY);
	if(numBin == -1){
		perror("ERROR open");
		exit(EXIT_FAILURE);
	}
	
	res = open("res.txt", O_CREAT | O_APPEND | O_RDWR, S_IRUSR | S_IWUSR);
	if(res == -1){
		perror("ERROR open");
		exit(EXIT_FAILURE);
	}	

	toAddNumbers = fileSize/sizeof(int);
	toAddNumbersChild = toAddNumbers/N;
	
	char param[64];
	sprintf(param, "%d", toAddNumbersChild);
	char *paramList[3] = {"./add", param, NULL};
	
	printf("Processing file %s with size %d and total work %d numbers.\n",
			fileName, fileSize, toAddNumbers);
			
	for(int i=0; i<N; i++){
					
		char buffer2[128];
	
		switch(fork()){
			case -1:
				perror("ERROR fork()");
				exit(EXIT_FAILURE);
				break;
			case 0:
				if(lseek(numBin, offset, SEEK_SET)==-1){
					perror("ERROR lseek");
					close(numBin);
					exit(EXIT_FAILURE);
				} else {
					
					close(STDIN_FILENO);
					dup2(numBin, STDIN_FILENO);
					close(numBin);
										
					sprintf(buffer2, "Creating Process %d.\n", i);
					write(1, buffer2, strlen(buffer2));
					
					if(execvp(paramList[0], paramList)<0){
						perror("ERROR exec");
					}
					offset = offset + toAddNumbers*sizeof(int);
					break;
				}
			default:
				pid = wait(&pid);
				addedNumbers = WEXITSTATUS(pid);
				totalAddedNumbers = totalAddedNumbers + addedNumbers;
				sprintf(buffer2, "Process %d finished processing %d numbers\n", pid, addedNumbers);
				write(1, buffer2, strlen(buffer2));
			}
	
	}
	
	sprintf(buffer1, "Total processed %d numbers.\n", totalAddedNumbers);
	write(1, buffer1, strlen(buffer1));
	close(res);
	close(numBin);
	return 0;

}


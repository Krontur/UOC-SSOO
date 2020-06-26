#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

	char output[128];
	int value=0, tmp, err, n=0;
	
	if(argc>1){
		for(int i=0; i< atoi(argv[1]); i++){
			err=read(STDIN_FILENO, &tmp, sizeof(int));
			//printf("%d\n", tmp);
			value = value + tmp;
			n++;
		}
	} else {
		while((err=read(STDIN_FILENO, &tmp, sizeof(int)))>0){
			//printf("%d\n", tmp);
			value = value + tmp;
			n++;
		}
	} 
	if(err==-1)return 0;
	sprintf(output, "%d\n", value);
	write(1, output, strlen(output));
	printf("%d\n", n);
	return n;
}

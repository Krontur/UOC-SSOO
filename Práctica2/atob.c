#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int main(int argc, char *argv[]){

	char c;
	int value=0, err, n=0;
		
	while((err=read(0, &c, 1))>0){
				
		if(isdigit(c)){
			value = 10*value + (c-'0');
		} else {
			write(1, &value, sizeof(int));
			value=0;
			n++;
		}
	} if(err==-1) return 0;
	return n;
	
}

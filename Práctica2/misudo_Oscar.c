#include <unistd.h>

int main(int argc, char *argv[]){

	char *cmd = argv[1];
	char *arguments[argc];
	int index=0;
	for(int i=1; i<=argc; i++){
	
		arguments[index]=argv[i];
		index++;
		
	}
	argv[argc]=NULL;
	
	execvp(cmd, arguments);
	
}

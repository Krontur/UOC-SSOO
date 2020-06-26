#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

char **suffix;

void 
free_memory(char **suffix, int n)
{
/* You must free allocated memory */
	for(int i=n; i>0; i--){
		free(suffix[i]);
	}
	free(suffix);
}

void
panic (char *m)
{
  fprintf (stderr, "%s\n", m);
  exit (0);
}

int
main (int argc, char *argv[])
{
  int n, i;

  if (argc != 2)
    panic ("wrong parameters");

/* Your code starts here */
	n = strlen(argv[1]);

	suffix = (char **) calloc(n, sizeof(char *));
	if(suffix == NULL){
		panic("Memory not allocated");
	}
	int m = n;
	for(i=0; i<n; i++){

		suffix[i] = (char *) malloc(n*sizeof(char));

		if(suffix[i] == NULL){
			panic("Memory not allocated");
		}

		for(int j=0; j<m ; j++){
			suffix[i][j]=argv[1][j+i];
		}
		m--;
	}
/* Your code ends here */

  for (i = 0; i < n; i++)
    {
      printf ("%d %s\n", i, suffix[i]);
    }

  free_memory(suffix, n);

  return 0;
}

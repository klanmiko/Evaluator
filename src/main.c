#include <stdio.h>
#include <unistd.h>
#include <argp.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
static char doc[] = "Evaluates C code, pipes an input file to stdin, and compares stdout of program to an output file";
static char args_doc[] = "valid args: evaluate <executable> <input_file> <output_file> [program arguments]";
int main(int argc, char *argv[]){
	puts(doc);
	int status;
	if(argc<4){
		puts(args_doc);
		return 1;
	}
	for(int i=0;i<argc;i++){
		if(strlen(argv[i])>500){
			printf("argument %d too long\n",i);
			return 1;
		}
	}
	int childtoParentpipe[2];
	pipe(childtoParentpipe);
	pid_t childpid,wait;
	childpid = fork();
	if(childpid==0)
	{
		char **args = malloc((argc-3)*sizeof(char*));
		args[0] = argv[0];
		int i=4;
		//printf("argc: %d\n",argc);
		for(;i<argc;i++){
			args[i-3]=argv[i];
			//printf("arg %d: %s",i,args[i-3]);
		}
		fflush(stdout);
		args[i-3]=NULL;
		FILE *input = fopen(argv[2],"r");
		int fdinput = fileno(input);
		close(childtoParentpipe[0]);
		dup2(fdinput,STDIN_FILENO);
		dup2(childtoParentpipe[1],STDOUT_FILENO);
		execv(argv[1],args);	
	}
	else{
		close(childtoParentpipe[1]);
		dup2(childtoParentpipe[0],STDIN_FILENO);
		FILE *output = fopen(argv[3],"r");
		char prgm_out[500];
		char expected_out[500];
		int line=0;
		wait = waitpid(childpid, &status, WUNTRACED|WCONTINUED);
		if(wait==-1){ perror("wait"); exit(EXIT_FAILURE);}
		if(WIFEXITED(status)){
			printf("program exited status=%d\n",status);
			do{
				line++;
				fgets(prgm_out,500,stdin);
				fgets(expected_out,500,output);
				if(strcmp(prgm_out,expected_out)!=0){
					printf("%d: Actual: %s\n",line,prgm_out);
					printf("%d: Expected: %s\n",line,expected_out);
					kill(childpid,SIGKILL);
					return 0;
				}
			}while (!(feof(output)||feof(stdin)));
			if(!feof(output)){
				printf("program output ends abruptly at line %d\n",line);
			}
			else if(!feof(stdin)){
				printf("extra line of output at line %d\n",line);
			}
			else puts("pass");
		}
	}
	return 0;
}

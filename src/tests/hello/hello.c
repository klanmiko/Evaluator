#include <stdio.h>
int main(int argc, char *argv[]){
	char name[80];
	puts("hello.c");
	fgets(name,80,stdin);
	printf("Hello %s",name);
	return 0;
}

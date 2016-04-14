#include <stdio.h>

void foo(){
	int i;
	printf("In foo function\n");
	for (i = 0; i < 5; i++){
		printf("looping:\t%i\n", i);
	}
}

int main(int argc, char *argv[]){
	int i;
	printf("In main function\n");
	printf("%i program's arguments found\n", argc);
	for (i = 0; i < argc; i++)
		printf("%i\t%s\n", i, argv[i]);

	foo();
	return 1;
}

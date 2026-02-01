#include <stdio.h>
#include <string.h>
#include <unistd.h>

void help(void);
int main(int argc, char *argv[]) {

	int option;

	//checks if no args is given and prints out the help page
	if(argc == 1){
		help();
		return 0;
	}
//need to use optget and redo all of the flag logic manually
	while((option = getopt(argc, argv, "hf:")) != -1){
		switch(option){
			case 'h':
				help();
				break;
			case 'f':
				printf("Given file to process %s\n",optarg);
				break;
			case ':':
				printf("No argument is given\n");
				break;
			case '?':
				printf("Unknown option %c\n",optopt);
				break;
		}
	}
	for(;optind<argc;optind++)
		printf("Given extra arguments %s\n",argv[optind]);

	return 0;
}

void help(){
	printf("usage: ./password_checker password\n");
	printf("  options:\n    -h print this screen\n");
	printf("    -f file.txt Use a file to check if the password already exists eg:rockyou.txt\n");
}

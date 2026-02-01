#include <stdio.h>
#include <string.h>
#include <unistd.h>

void help(void);

int main(int argc, char *argv[]) {

	//for getopt
	int option;

	//checks if no args is given and prints out the help page
	if(argc == 1){
		help();
		return 0;
	}
	//need to use optget and redo all of the flag logic manually
	while((option = getopt(argc, argv, ":hf:")) != -1){
		switch(option){
			case 'h':
				help();
				break;
			case 'f':
				printf("Given file to process %s\n",optarg);
				break;
			case ':':
				fprintf(stderr, "No argument is given\n");
				return 1;
			case '?':
				fprintf(stderr, "Unknown option -%c\n",optopt);
				return 1;	
		}
	}

	//to only count the positional args (password) and check if it is supplied or more than one optional args
	int remaining = argc - optind;

	//check if more that one positional args
	if (remaining > 1) {
	    fprintf(stderr, "Error: too many arguments\n");
	    return 1;
	}

	//the actual password provided by the use
	char *password = argv[optind];
	printf("Password: %s\n",password);

	return 0;
}

void help(){
	printf("usage: ./password_checker password\n");
	printf("  options:\n    -h print this screen\n");
	printf("    -f file.txt Use a file to check if the password already exists eg:rockyou.txt\n");
}

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

##########################@@@@@@@@@@@@@@@@@@@@@@@@@
if -f is empty not able to throw an error
void help(void);
int file(const char *filename,char *password);
int strength(char *password);


int main(int argc, char *argv[]) {

	//for getopt
	int option;
	char *filename;
	int fflag = 0;

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
				return 0;
			case 'f':
				//read file name from -f flag
				filename = optarg;
				fflag = 1;
				break;
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
	//check if no password is provided
	} else if (remaining == 0){
		fprintf(stderr, "Password not provided\n");
		return 1;
	}

	//the actual password provided by the use
	char *password = argv[optind];

	//check if -f flag is used
	if(fflag == 1){
		int errorcode = file(filename,password);
		if(errorcode == 1){
			fprintf(stderr,"Filename must be of .txt extension\n");
		} else if ( errorcode == 2){
			fprintf(stderr,"File not found or not able to open\n");
		} else if (errorcode == 3){
			fprintf(stderr,"Password not found in wordlist\n");
		} else if (errorcode == 0){
			printf("Password found in wordlist!!!!\n");
		} else if(errorcode == 4){
			fprintf(stderr,"File name not specified\n");
		}
	}

	//checking password strength
	int score = strength(password);
	//the max score possible is 7
	if(score>=4){
		printf("Score:%d/7\tVery strong password\n",score);
	}else{
		printf("Score:%d/7\tWeak password\n",score);
	}

	return 0;
}

void help(){
	printf("usage: ./password_checker password\n");
	printf("  options:\n    -h print this screen\n");
	printf("    -f file.txt Use a file to check if the password already exists eg:rockyou.txt\n");
}

int file(const char *s,char *p){
	//checks if a file name was passed
	if(s==NULL){
		return 4;
	}

	size_t plen = strlen(p);
	//pass for password ownership and +2 for newline addition and null terminator
	char pass[plen+2];
	int len = strlen(s);
	char line[512];

	//checks if the file name contains more than 4 characters cause .txt extension needs more than 4 letters
	if (len < 4){
		return 1;
	}
	//checking the extension type
	char *ext = strrchr(s,'.');
	if(!ext){
		return 1;
	} else {
		if(strcmp(ext,".txt") != 0){
			return 1;
		}
	}

	//creating a copy of password with a newline for wordlist checking
	memcpy(pass,p,plen);
	//add newline to password for direct comparisons
	pass[plen] = '\n';
	pass[plen+1] = '\0';

	//opening file
	FILE *f = fopen(s,"r");
	if(f == NULL)
		return 2;

	//take data from file line by line
	while(fgets(line,sizeof(line),f)){
		if(strcmp(line,pass) == 0){
			fclose(f);
			return 0;
		}
	}

	fclose(f);
	return 3;
}

int strength(char *p){
	//final password strength score to be returned
	int score = 0;
	//a coutning variable
	int i = 0;
	int low = 0;

	//check for password length
	size_t plen = strlen(p);
	if(plen >= 8){
		score+=3;
	}

	//check if capital letters is available
	for(i=0;p[i]!='\0';i++){
		if(isupper(p[i])){
			score++;
			break;
		}
	}

	//check if atleast 3 small letter characters
	for(i=0;p[i]!='\0';i++){
		if(islower(p[i])){
			low++;
		}
	}
	if(low>=3){
		score++;
	}

	//checking if special character exists
	for(i=0;p[i]!='\0';i++){
		if(!isalnum(p[i])){
			score++;
			break;
		}
	}

	//check if one digit is present
	for(i=0;p[i]!='\0';i++){
		if(isdigit(p[i])){
			score++;
			break;
		}
	}

	return score;
}

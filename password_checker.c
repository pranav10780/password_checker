#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include "output.h"

void help(void);
int file(const char *filename,const char *password);
int strength(const char *password);

int main(int argc, char *argv[]) {
	//for getopt
	int option;
	char *filename;
	int fflag = 0;
	//0 - normal,1 - json,2 - xml
	int output = 0;

	//checks if no args is given and prints out the help page
	if(argc == 1){
		help();
		return 0;
	}
	//flag parsing
	while((option = getopt(argc, argv, ":hf:o:")) != -1){
		switch(option){
			case 'h':
				help();
				return 0;
			case 'f':
				//read file name from -f flag
				filename = optarg;
				fflag = 1;
				break;
			case 'o':
				//read output format
				if(strcmp(optarg,"json") == 0){
					output = 1;
				}else if (strcmp(optarg,"xml") == 0){
					output = 2;
				}else{
					fprintf(stderr, "Unknown output format\n");
					return 1;
				}
				break;
			case ':':
				fprintf(stderr,"Missing argument for option -%c\n",optopt);
				return 1;
			case '?':
				fprintf(stderr, "Unknown option -%c\n",optopt);
				return 1;	
		}
	}

	//check if more that one positional args
	int remaining = argc - optind;
	if (remaining > 1) {
		fprintf(stderr, "Error: too many arguments\n");
		return 1;
	//check if no password is provided
	} else if (remaining == 0){
		fprintf(stderr, "Password not provided\n");
		return 1;
	}

	//the actual password provided by the user
	const char *password = argv[optind];
	int errorcode = -1;

	//check if -f flag is used
	if(fflag == 1){
		errorcode = file(filename,password);
		if(errorcode == 1){
			fprintf(stderr,"Filename must be of .txt extension\n");
		} else if ( errorcode == 2){
			fprintf(stderr,"File not found or not able to open\n");
		} else if (errorcode == 3 && output == 0){
			printf("Password not found in wordlist\n");
		} else if (errorcode == 0 && output == 0){
			printf("Password found in wordlist!!!!\n");
		}
	}

	//checking password strength
	int score = strength(password);
	//the max score possible is 7
	
	//for normal output execution
	if(output == 0){
		if(score>=4){
			printf("Score:%d/7\tVery strong password\n",score);
		}else{
			printf("Score:%d/7\tWeak password\n",score);
		}
	}else if(output == 1){
		tojson(score,password,errorcode);
	}else if(output == 2){
		toxml(score,password,errorcode);
	}
	return 0;
}

void help(){
	printf("usage: ./password_checker password\n");
	printf("  options:\n    -h print this screen\n");
	printf("    -f file.txt Use a file to check if the password already exists eg:rockyou.txt\n");
	printf("    -o json Output format\n");
}

int file(const char *s,const char *p){

	size_t plen = strlen(p);

	char *ext = strrchr(s,'.');
	if(!ext){
		return 1;
	} else {
		if(strcmp(ext,".txt") != 0){
			return 1;
		}
	}

	//pass for password ownership and +2 for newline addition and null terminator
	//heap instead of vlas
	char *pass = malloc(plen + 2);
	if (!pass) return 2;

	char line[512];

	//creating a copy of password with a newline for wordlist checking
	memcpy(pass,p,plen);
	//add newline to password for direct comparisons
	pass[plen] = '\n';
	pass[plen+1] = '\0';

	//opening file
	FILE *f = fopen(s,"r");
	if(f == NULL){
		free(pass);
		return 2;
	}

	//take data from file line by line
	while(fgets(line,sizeof(line),f)){
		if(strcmp(line,pass) == 0){
			fclose(f);
			free(pass);
			return 0;
		}
	}

	fclose(f);
	free(pass);
	return 3;
}

int strength(const char *p){
	//final password strength score to be returned
	int score = 0;
	//coutning variable
	size_t i = 0;
	int low = 0;

	//check for password length
	size_t plen = strlen(p);
	if(plen >= 8){
		score+=3;
	}

	//check if capital letters is available
	for(i=0;p[i]!='\0';i++){
		if(isupper((unsigned char)p[i])){
			score++;
			break;
		}
	}

	//check if atleast 3 small letter characters
	for(i=0;p[i]!='\0';i++){
		if(islower((unsigned char)p[i])){
			low++;
		}
	}
	if(low>=3){
		score++;
	}

	//checking if special character exists
	for(i=0;p[i]!='\0';i++){
		if(!isalnum((unsigned char)p[i])){
			score++;
			break;
		}
	}

	//check if one digit is present
	for(i=0;p[i]!='\0';i++){
		if(isdigit((unsigned char)p[i])){
			score++;
			break;
		}
	}

	return score;
}

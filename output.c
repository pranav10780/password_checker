#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

//a file for the code to be run inside the -o flag

void tojson(int score,const char *password,int errorcode){
	const char *strength = (score >= 4) ? "strong" : "weak";
	size_t plen = strlen(password);
	char password_in_file[6]; //length of false is 5 + 1 for \0

	if(errorcode == -1){
		strcpy(password_in_file,"null");
	}else if(errorcode == 0){
		strcpy(password_in_file,"true");
	}else{
		strcpy(password_in_file,"false");
	}

	//checking if plen is larger than max size
	if(plen > (SIZE_MAX - 1)/2){
		fprintf(stderr, "Input too large\n");
		return;
	}

	//using heap to avoid vlas
	size_t max =  plen * 2 + 1;
	//new buffer for escaped string
	char *buff = malloc(max);
	if(!buff){
		fprintf(stderr,"Memory allocation failure");
		return;
	}

	//Json escape character parsing
	size_t j = 0;
	for (size_t i = 0; password[i] != '\0'; i++) {
		switch(password[i]){
			case '"':
				buff[j++] = '\\';
				buff[j++] = '"';
				break;
			case '\\':
				buff[j++] = '\\';
				buff[j++] = '\\';
				break;
			case '/':
				buff[j++] = '\\';
				buff[j++] = '/';
				break;
			case '\b':
				buff[j++] = '\\';
				buff[j++] = 'b';
				break;
			case '\f':
				buff[j++] = '\\';
				buff[j++] = 'f';
				break;
			case '\n':
				buff[j++] = '\\';
				buff[j++] = 'n';
				break;
			case '\r':
				buff[j++] = '\\';
				buff[j++] = 'r';
				break;
			case '\t':
				buff[j++] = '\\';
				buff[j++] = 't';
				break;
			default:
				buff[j++] = password[i];
				break;
		}
	}
	buff[j] = '\0';

	//directly printing everyting to stdout
	printf("{\n\t\"password\" : \"%s\",\n\t\"score\" : %d,\n\t\"strength\" : \"%s\",\n\t\"length\" : %zu,\n\t\"password_in_file\" : %s\n}\n",buff,score,strength,plen,password_in_file);

	//freeing memory
	free(buff);
}

void toxml(int score,const char *password,int errorcode){
	const char *strength = (score >= 4) ? "strong" : "weak";
	size_t plen = strlen(password);
	char password_in_file[6]; //length of false is 5 + 1 for \0

	if(errorcode == -1){
		strcpy(password_in_file,"null");
	}else if(errorcode == 0){
		strcpy(password_in_file,"true");
	}else{
		strcpy(password_in_file,"false");
	}

	//checking if plen is larger than max size
	if(plen > (SIZE_MAX - 1)/6){
		fprintf(stderr, "Input too large\n");
		return;
	}
	//using heap instead of vlas
	size_t max = plen * 6 + 1;
	//new buffer for escaped string
	char *buff = malloc(max);
	if(!buff){
		fprintf(stderr,"Memory allocation failed");
		return;
	}

	//Json escape character parsing
	size_t j = 0;
	for (size_t i = 0; password[i] != '\0'; i++) {
		switch(password[i]){
			case '<':
				strcpy(&buff[j],"&lt;");
				j+=4;
				break;
			case '>':
				strcpy(&buff[j],"&gt;");
				j+=4;
				break;
			case '&':
				strcpy(&buff[j],"&amp;");
				j+=5;
				break;
			case '"':
				strcpy(&buff[j],"&quot;");
				j+=6;
				break;
			case '\'':
				strcpy(&buff[j],"&apos;");
				j+=6;
				break;
			default:
				buff[j++] = password[i];
				//this break is not needed but if u r going to expand something below like another case
				//statement below this default then this break is necessary
				break;
		}
	}
	buff[j] = '\0';

	//the actual output printing
	printf("<Password>\n\t<password>%s</password>\n\t<score>%d</score>\n\t<strength>%s</strength>\n\t<length>%zu</length>\n",buff,score,strength,plen);
	if(strcmp(password_in_file,"null") != 0){
		printf("\t<password_in_file>%s</password_in_file>\n",password_in_file);
	}

	printf("</Password>\n");

	//freeing memory
	free(buff);
}

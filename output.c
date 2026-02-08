#include <stdio.h>
#include <string.h>

//a file for the code to be run inside the -o flag


void tojson(int score,const char *password,int errorcode){
	const char *strength = (score >= 4) ? "strong" : "weak";
	int plen = strlen(password);
	char password_in_file[6]; //length of false is 5 + 1 for \0

	if(errorcode == -1){
		strcpy(password_in_file,"null");
	}else if(errorcode == 0){
		strcpy(password_in_file,"true");
	}else{
		strcpy(password_in_file,"false");
	}

	//create a copy of password
	char copy[strlen(password)+1];
	strcpy(copy,password);
	//new buffer for escaped string
	//copy x 2 cus just in case every character is / and causes double // everywhere and +1 for \0
	char buff[strlen(copy)*2+1];

	//input sanitization logic
	int j = 0;
	for (int i = 0; copy[i] != '\0'; i++) {
		if (copy[i] == '"' || copy[i] == '\\') {
			//THIS is very important there is a difference between j++ and ++j if the below statment had ++j the 
			//variable j would have updated first and then written the value one step ahead of the intended
			//index but since it is j++ the below expression/line is processed aka the value is assigned to 
			//buff at the required index and then only it increments the var j
			//This is basic but i had a hard time and if u ever stumble on to this code please keep this in mind
			//before changing the input sanitization of json
			buff[j++] = '\\';
		}
		buff[j++] = copy[i];
	}
	buff[j] = '\0';

	//directly printing everyting to stdout
	printf("{\n\t\"password\" : \"%s\",\n\t\"score\" : %d,\n\t\"strength\" : \"%s\",\n\t\"length\" : %d,\n\t\"password_in_file\" : %s\n}\n",buff,score,strength,plen,password_in_file);
}

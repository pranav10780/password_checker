#include <stdio.h>

int main(int argc, char *argv[]) {
	help_txt();
	return 0;
}

int help_txt(){
	printf("usage: ./password_checker password\n");
	printf("  options:\n    -h/--help print this screen\n");
	printf("    -t/--txt file.txt Use a file to check if the password already exists eg:rockyou.txt\n");
	return 0;
}

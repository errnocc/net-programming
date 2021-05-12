#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE* fd;
	char buff[1024];
	fd = fopen("text_2.txt", "r");
	fgets(buff, 15, fd);
	buff[15]='\0';
	printf("%s\n",buff);
	return 0;
}

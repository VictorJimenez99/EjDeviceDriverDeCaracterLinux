#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>

#define N 1024
char buffer[N],buffer_read[N];

int main()
{
	int fd;
	fd = open("/dev/ESCOM_device", O_RDWR );
	if(fd == -1)
	{
		perror("ERROR al abrir el ddc \n");
		exit(EXIT_FAILURE);
	}

	printf("Mensaje para el módulo:");
	scanf("%s",buffer);
	write(fd,buffer, strlen(buffer)+1 );
	sleep( 5 );
	read(fd, buffer_read, N);
	printf("Mensaje recibido en el DDC: %s\n", buffer_read);
	close(fd);
}


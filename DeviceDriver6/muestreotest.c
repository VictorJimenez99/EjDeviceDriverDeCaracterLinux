#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<math.h>

#define N 1024
#define MUESTRAS 1024

void guardar_array(short int datos[], char* nombre);
void genera_seno( short int seno[] );

int main()
{
	short int seno[MUESTRAS],seno_proc[MUESTRAS];
	int fd, len;
	genera_seno(seno);
	guardar_array( seno, "seno.dat" );
	fd = open("/dev/ESCOM_device", O_RDWR );
	if(fd == -1)
	{
		perror("ERROR al abrir el ddc \n");
		exit(EXIT_FAILURE);
	}



	len = write(fd,seno, sizeof(short int)*MUESTRAS );
	printf("Muestras Enviadas %d\n", len);
	len = read(fd, seno_proc, sizeof(short int)*MUESTRAS);
	printf("Muestras Recibidas %d \n", len);

	guardar_array(seno_proc, "seno_proc.dat" );

	close(fd);
	
	return 0;
}



void genera_seno( short int seno[] )
{
	float f  = 1000; 
	float fs = 45000;
	float muestra;

	register int n;

	for( n = 0; n < MUESTRAS; n++ )
	{
		muestra = sinf(2*n*M_PI*f/fs);

		seno[n] = muestra*2048;
		
	}

}

void guardar_array(short int datos[], char* nombre)
{
	FILE *ap_arch;

	register int n ; 

	ap_arch = fopen(nombre,"w");
	if(!ap_arch)
	{
		perror("Error al abrir arch");
		exit(EXIT_FAILURE);
	}
	for( n = 0; n < MUESTRAS; n++ )
	{
		fprintf(ap_arch, "%d \n",datos[n]);
	}
	fclose(ap_arch);
}



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
void genera_ventana( short int hamming[] );
void procesamiento(short int seno[], short int ventana[], short int seno_proc[]);

int main()
{
	short int seno[MUESTRAS],seno_proc[MUESTRAS], ventana[MUESTRAS];
	int fd, len;
	genera_seno(seno);
	guardar_array( seno, "seno.dat" );

	genera_ventana( ventana );
	guardar_array(ventana, "ventana.dat");
	
	procesamiento(seno, ventana, seno_proc);
	guardar_array(seno_proc, "seno_proc.dat" );

	close(fd);
	
	return 0;
}

void procesamiento(short int seno[], short int ventana[], short int seno_proc[])
{
	register int n;
	int proc;
	for( n = 0; n < MUESTRAS; n++ )
	{
		proc = seno[n] * ventana[n];
		seno_proc[n] = (short int)(proc >> 14);
	}

}

void genera_ventana( short int hamming[] )
{
	float a0 = 0.53863, a1 = 0.46164, v;
	register int n;

	for( n = 0; n < MUESTRAS; n++ )
	{
		v = a0 - (a1*cosf( (2*M_PI*n) / (MUESTRAS-1) ) );
		hamming[n] = (v*(1 << 14));
		
	}

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

		seno[n] = muestra*(1 << 11);
		
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



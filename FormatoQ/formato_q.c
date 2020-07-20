#include<stdio.h>


#define Qn 8
#define M  3

int main(int argc, char**  argv)
{
	float f[M] = {0.5, 9.53125, 4.150625};
	int ce[M], y, x[M] = {23, 7, 11};

	for (int i = 0; i < M; i++)
	{
		ce[i] =(int)( f[i] * ( 1 << Qn ) );
		printf("formato Q: %d, coeficiente: %d\n", i, ce[i]);
	}

	y = 0;

	for(int i = 0; i < M; i++)
	{
		y+=ce[i]* x[i];
	}

	y >>= Qn;
	printf("El resultado es : %d\n",y);

	return 0;
}

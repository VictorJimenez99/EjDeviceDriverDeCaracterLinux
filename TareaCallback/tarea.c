#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/moduleparam.h>//necesaria para el manejo de parámetros
#include<linux/delay.h>
#include<linux/sched.h>
#include<linux/kthread.h>


#define MAX 8

int promedio(int *array);
void burbuja(int *array);
void imp_array(int *array);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("VictorJimenez99");
MODULE_DESCRIPTION("Tarea 31-05-2020");
MODULE_INFO(driver, "Manipulación de array con funciones callback");

MODULE_VERSION("1.0");

/**
 *Puedes pasar argumementos al módulo con sudo insmod param2.ko opcion=x comando="y"
 * */
static int opcion = 0;
static int avrg = 0;
//static char*comando = "derecha";
static int array[MAX] = {7, 6, 5, 4, 3, 2, 1, 0};
static int num_elem = MAX;

int get_param(char *buffer, const struct kernel_param *kp)
{
	int ret;
	ret = param_get_int(buffer, kp);

	//printk(KERN_INFO"Promedio de los datos: %d" ,avrg);
	if ( ret > 1 )
	{
		return avrg;
	}

	return -EPERM;
	
	/*
	char* cadena = (char*)kp->arg;
	int ret;

	ret = param_get_int( buffer, kp );
	if ( ret > 1 )
	{
		return 0;
	}

	return -EPERM;
	*/
}

int set_param(const char *val, const struct kernel_param *kp)
{
	int ret;


	ret = param_set_int(val, kp);
	//printk(KERN_INFO "set_param; parametro: %d\n", opcion);

	switch (opcion)
	{
		case 1:
			//printk(KERN_INFO "Promedio\n");
			avrg = promedio(array);
		break;
		case  2:
			//printk(KERN_INFO "Burbuja\n");
			burbuja(array);
		break;
		default:
			//printk(KERN_INFO "Default\n");
		break;
	}

        opcion = avrg;

	return ret;

}


const struct kernel_param_ops ops_opcion = {
	.set = set_param,
	.get = get_param,
};

module_param_cb(opcion, &ops_opcion, &opcion, 0660);
module_param_array(array, int, &num_elem, 0660);

MODULE_PARM_DESC(opcion, "Qué se hará con el arraglo\n1.-Promedio\n2.-Burbuja");
MODULE_PARM_DESC(datos,"Muestras del array");

void imp_array(int *array)
{
	register int i;
	for( i = 0; i != num_elem; i++)
	{
		printk(KERN_INFO"-->%4d\n",array[i]);
	}
}

void burbuja(int *array)
{
	register int i, j;
	int swap;
	for(i = 0; i < num_elem - 1; i++)
	{
		for(j = 0; j < num_elem - i-1; j++ )
		{
			//printk(KERN_INFO"reading %d,%d",array[j],array[j+1]);
			//return;
			if(array[j] > array[j+1])
			{
				swap = array[j];
				array[j] = array[j+1];
				array[ j+1 ] = swap;
			}
		}
	}
	
	return;
}

int promedio(int *array)
{
	register int i;
	int avrg =  0;

	for(i = 0; i!=num_elem; i++)
	{
		avrg += array[i];
	}
	avrg = avrg/num_elem;
	printk(KERN_INFO "Promedio = %4d\n",avrg);
	return avrg;
}

static int __init funcion_inicio(void)
{
	printk(KERN_INFO "Opción: %03d\n",opcion);
	return  0;
}

static void __exit funcion_exit(void)
{
	register int i;
	printk(KERN_ALERT "Terminando la ejecución del módulo de tarea\n");
	printk(KERN_INFO "Imprimiendo Muestras del Array\n");
	for( i = 0; i != num_elem; i++)
	{
		printk(KERN_INFO"Muestra [%03d]:%4d\n",i,array[i]);
	}
}

module_init(funcion_inicio);
module_exit(funcion_exit);


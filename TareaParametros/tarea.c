#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/moduleparam.h>//necesaria para el manejo de parámetros
#include<linux/delay.h>
#include<linux/sched.h>
#include<linux/kthread.h>


#define MAX 8

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VictorJimenez99");
MODULE_DESCRIPTION("Tarea 18-05-2020");
MODULE_INFO(driver, "Manipulación de array");

MODULE_VERSION("1.0");

/**
 *Puedes pasar argumementos al módulo con sudo insmod param2.ko opcion=x comando="y"
 * */
static int opcion = 0;
//static char*comando = "derecha";
static int array[MAX] = {7, 6, 5, 4, 3, 2, 1, 0};
static int num_elem = MAX;




module_param(opcion, int, 0660);
module_param_array(array, int, &num_elem, 0660);

MODULE_PARM_DESC(opcion, "Qué se hará con el arraglo\n1.-Promedio\n2.-Burbuja");
MODULE_PARM_DESC(datos,"Muestras del array");


struct task_struct *kthread;

int promedio(int *array);
void burbuja(int *array);
void imp_array(int *array);

int hilo_kernel(void *datos)
{
	
	int id = *(int *)datos;
	printk(KERN_INFO "Se ha ingresado al hilo");
	while( ! kthread_should_stop() )
	{
		//printk(KERN_INFO "Option %d\n",opcion);
		if( opcion != 0 )
		{
			switch (opcion)
			{
				case 1:
					printk(KERN_INFO "Promedio\n");
					promedio(array);
				break;
				case  2:
					printk(KERN_INFO "Burbuja\n");
					burbuja(array);
				break;
				case 3:
					printk(KERN_INFO "Imprimiendo Arreglo\n");
					imp_array(array);
				break;
				default:
					printk(KERN_INFO "No se han proporcionado los parametros necesarios\n");
				break;
			}
			opcion = 0;
		}
		//ssleep(2);
		schedule();
	}
	return id;
}

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
	static int id_thread = 10;
	printk(KERN_INFO "Opción: %03d\n",opcion);
	kthread = kthread_run(hilo_kernel,(void*)&id_thread,"kHomeworkThread"); 
	if(IS_ERR(kthread))
	{
		printk(KERN_ERR"Error en la creación del hilo...\n");
		return PTR_ERR(kthread);
	}
	return  0;
}

static void __exit funcion_exit(void)
{
	register int i;
	int ret_thread = kthread_stop(kthread);
	printk(KERN_ALERT "Terminando la ejecución del módulo de tarea\n");
	if(ret_thread == -EINTR)
		printk(KERN_INFO "Terminando la terminación del hilo");
	else
	{
		printk(KERN_INFO "Imprimiendo Muestras del Array\n");
		for( i = 0; i != num_elem; i++)
		{
			printk(KERN_INFO"Muestra [%03d]:%4d\n",i,array[i]);
		}
	}
}

module_init(funcion_inicio);
module_exit(funcion_exit);


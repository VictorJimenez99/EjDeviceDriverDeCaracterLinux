#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/moduleparam.h>//necesaria para el manejo de parámetros

#define MAX 4

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VictorJimenez99");
MODULE_DESCRIPTION("Uso de parámetros");
MODULE_INFO(driver, "TEST_DRIVE");

MODULE_VERSION("1.0");




static int myvar __initdata = 3;
/**
 *Puedes pasar argumementos al módulo con sudo insmod param2.ko irq=x comando="y"
 * */
static int irq = 7;
static char*comando = "derecha";
static int datos[MAX] = {1, 2, 3, 4};
static int num_elem = MAX;

module_param(irq, int, 0660);
module_param(comando, charp, 0660);
module_param_array(datos, int, &num_elem, 0660);

MODULE_PARM_DESC(irq, "Numero de interrupción");
MODULE_PARM_DESC(comando, "Comando del Módulo");
MODULE_PARM_DESC(datos,"Muestras del array");

static int __init funcion_inicio(void)
{
	register int i;
	printk(KERN_ALERT "Hola Mundo con parámetros 1 %d\n", myvar);
	printk(KERN_INFO "INTERRUPCIÓN: %04d\n COMANDO:%s\n",irq,comando);
	printk(KERN_INFO "Imprimiendo Muestras del Array\n");
	for( i = 0; i != num_elem; i++)
	{
		printk(KERN_ALERT "Muestra [%03d]:%4d\n",i,datos[i]);
	}
	return  0;
}

static void __exit funcion_exit(void)
{
	register int i;
	printk(KERN_ALERT "Terminando la ejecución del módulo 4\n");
	printk(KERN_INFO "INTERRUPCIÓN: %04d\n COMANDO:%s\n",irq,comando);
	printk(KERN_INFO "Imprimiendo Muestras del Array\n");
	for( i = 0; i != num_elem; i++)
	{
		printk(KERN_ALERT "Muestra [%03d]:%4d\n",i,datos[i]);
	}
}

module_init(funcion_inicio);
module_exit(funcion_exit);


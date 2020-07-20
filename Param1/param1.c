#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/moduleparam.h>//necesaria para el manejo de parámetros

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VictorJimenez99");
MODULE_DESCRIPTION("Uso de parámetros");
MODULE_INFO(driver, "TEST_DRIVE");

MODULE_VERSION("1.0");

static int myvar __initdata = 3;

static int irq = 7;
module_param(irq, int, 0660);
MODULE_PARM_DESC(irq, "Numero de interrupción");

static int __init funcion_inicio(void)
{
	printk(KERN_ALERT "Hola Mundo con parámetros 1 %d\n", myvar);
	printk(KERN_INFO "INTERRUPCIÓN: %04d\n",irq);
	return  0;
}

static void __exit funcion_exit(void)
{
	printk(KERN_ALERT "Terminando la ejecución del módulo 4\n");
	printk(KERN_INFO "INTERRUPCIÓN: %04d\n",irq);
}

module_init(funcion_inicio);
module_exit(funcion_exit);


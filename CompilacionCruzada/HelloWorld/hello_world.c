
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VictorJimenez99");
MODULE_DESCRIPTION("Compilación cruzada");
MODULE_INFO(intree, "DRIVER");

MODULE_VERSION("1.0");

int init_module(void)
{
	printk(KERN_ALERT "Hola Mundo en el módulo 1");

	return  0;
}

void cleanup_module(void)
{
	printk(KERN_ALERT "Terminando la ejecución del módulo 1");
}


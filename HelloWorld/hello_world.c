
#include<linux/module.h>
#include<linux/kernel.h>

int init_module(void)
{
	printk(KERN_ALERT "Hola Mundo en el módulo 1");

	return  0;
}

void cleanup_module(void)
{
	printk(KERN_ALERT "Terminando la ejecución del módulo 1");
}



#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

static int __init funcion_inicio(void)
{
	printk(KERN_ALERT "Hola Mundo en el módulo 2");
	return  0;
}



static void __exit(void)
{
	printk(KERN_ALERT "Terminando la ejecución del módulo 1");
}

module__init(funcion_inicio);
module_exit(funcion_exit);


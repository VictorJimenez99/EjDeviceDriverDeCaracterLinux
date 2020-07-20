#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VictorJimenez99");
MODULE_DESCRIPTION("Modulo de Prueba");
MODULE_INFO(driver, "TEST_DRIVE");

static int __init funcion_inicio(void)
{
	printk(KERN_ALERT "Hola Mundo en el módulo 3");
	return  0;
}



static void __exit funcion_exit(void)
{
	printk(KERN_ALERT "Terminando la ejecución del módulo 3");
}

module_init(funcion_inicio);
module_exit(funcion_exit);


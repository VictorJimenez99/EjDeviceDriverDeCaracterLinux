#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/moduleparam.h>//necesaria para el manejo de parámetros
#include<linux/fs.h>
#include<linux/kdev_t.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("VictorJimenez99");
MODULE_DESCRIPTION("Asignación de números de DDC");
MODULE_INFO(driver, "Character Device Driver");

MODULE_VERSION("1.0");



dev_t dispositivo;

static int __init funcion_inicio(void)
{
	int ret;
	printk(KERN_INFO "INICIO módulo números estáticos en DDC");
	printk(KERN_INFO "------------------------");
	ret = alloc_chrdev_region( &dispositivo, 0, 1, "ESCOM_DDC" );
	if( ret != 0)
	{
		printk(KERN_ERR "ERROR al asignar el valor mayor y menor del ddc");
		return ret;
	}
	printk(KERN_INFO "Device registrado con MAJOR: %d, MINOR: %d", MAJOR( dispositivo ), MINOR( dispositivo ) );

	return  0;
}

static void __exit funcion_exit(void)
{
	printk(KERN_INFO "FINAL módulo de asignación ");
	printk(KERN_INFO "------------------------");
	unregister_chrdev_region( dispositivo, 1 );
}

module_init(funcion_inicio);
module_exit(funcion_exit);


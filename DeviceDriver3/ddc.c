#include<linux/module.h>	//creación  de modulos
#include<linux/kernel.h>	//printk
#include<linux/moduleparam.h>	//necesaria para el manejo de parámetros
#include<linux/fs.h>		//funciones de registro de numeros
#include<linux/kdev_t.h>	//maco de registro de numeros(MAJOR MINOR)
#include<linux/device.h>	//creación de clase y dispositivo


MODULE_LICENSE("GPL");
MODULE_AUTHOR("VictorJimenez99");
MODULE_DESCRIPTION("Asignación de DDC");
MODULE_INFO(driver, "Character Device Driver");

MODULE_VERSION("1.0");



dev_t dispositivo;
static struct class *dev_class;
static struct device *dev_file;

static int __init funcion_inicio(void)
{
	int ret;
	printk(KERN_INFO "INICIO módulo números estáticos en DDC");
	printk(KERN_INFO "------------------------");
	ret = alloc_chrdev_region( &dispositivo, 0, 1, "ESCOM_dev" );
	if( ret != 0)
	{
		printk( KERN_ERR "ERROR al asignar el valor mayor y menor del ddc" );
		return ret;
	}
	printk(KERN_INFO "Device registrado con MAJOR: %d, MINOR: %d", MAJOR( dispositivo ), MINOR( dispositivo ) );

	dev_class = class_create( THIS_MODULE, "ESCOM_class"  );
	if( IS_ERR(dev_class) )
	{
		printk(KERN_ERR "Error al crear la clase de dispositivo");
		unregister_chrdev_region( dispositivo, 1 );
		return PTR_ERR (dev_class);
	}
	dev_file = device_create( dev_class, NULL, dispositivo,NULL, "ESCOM_device" );
	if( IS_ERR(dev_file) )
	{
		printk(KERN_ERR "Error al crear el archivo del dispositivo");
		unregister_chrdev_region( dispositivo, 1 );
		class_destroy( dev_class );
		return PTR_ERR( dev_file );
	}
	printk( KERN_INFO "Archivo del dispositivo creado exitosamente" );
	return  0;
}

static void __exit funcion_exit(void)
{
	printk(KERN_INFO "FINAL módulo de asignación ");
	printk(KERN_INFO "------------------------");
	device_destroy( dev_class , dispositivo );
	unregister_chrdev_region( dispositivo, 1 );
	class_destroy( dev_class );
}

module_init(funcion_inicio);
module_exit(funcion_exit);


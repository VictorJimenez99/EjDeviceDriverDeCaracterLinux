/**@BRIEF
 * Operaciones del driver
 * */
#include<linux/module.h>	//creación  de modulos
#include<linux/kernel.h>	//printk
#include<linux/moduleparam.h>	//necesaria para el manejo de parámetros
#include<linux/fs.h>		//funciones de registro de numeros
#include<linux/kdev_t.h>	//maco de registro de numeros(MAJOR MINOR)
#include<linux/device.h>	//creación de clase y dispositivo
#include<linux/cdev.h>		//necesaia para registrar  las operaciones del driver

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VictorJimenez99");
MODULE_DESCRIPTION("Asignación de DDC");
MODULE_INFO(driver, "Character Device Driver");

MODULE_VERSION("1.0");



dev_t dispositivo;

static struct class *dev_class;
static struct device *dev_file;
static struct cdev dev_cdev;


static int 	driver_open(struct inode *inode, struct file *file);
static int 	driver_release(struct inode *inode, struct file *file);
static ssize_t 	driver_read( struct file *filp, char __user *buf, size_t len, loff_t *off );
static ssize_t 	driver_write( struct file *filp, const char __user *buf, size_t len, loff_t *off );

static struct file_operations fops = 
{
	.owner	= THIS_MODULE,
	.open	= driver_open,
	.read	= driver_read,
	.write	= driver_write,
	.release= driver_release,
};


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

	/*************************************************/

	cdev_init( &dev_cdev, &fops );
	ret = cdev_add(&dev_cdev, dispositivo, 1);

	if( ret != 0)
	{
		printk( KERN_ERR "ERROR al registrar las operaciones" );
		unregister_chrdev_region( dispositivo, 1 );
		return ret;
	}

	printk( KERN_INFO "Operaciones regstradas correctamente" );

	/************************************************/

	dev_class = class_create( THIS_MODULE, "ESCOM_class"  );
	if( IS_ERR(dev_class) )
	{
		printk(KERN_ERR "Error al crear la clase de dispositivo");
		unregister_chrdev_region( dispositivo, 1 );
		cdev_del( &dev_cdev );
		return PTR_ERR (dev_class);
	}
	dev_file = device_create( dev_class, NULL, dispositivo,NULL, "ESCOM_device" );
	if( IS_ERR(dev_file) )
	{
		printk(KERN_ERR "Error al crear el archivo del dispositivo");
		unregister_chrdev_region( dispositivo, 1 );
		cdev_del( &dev_cdev );
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
	cdev_del( &dev_cdev );
	class_destroy( dev_class );
}

static int driver_open(struct inode *inode, struct file *file)
{
	printk( KERN_INFO "Llamada a OPEN" );
	return  0;
}
static int driver_release(struct inode *inode, struct file *file)
{
	printk( KERN_INFO "Llamada a RELEASE" );
	return  0;
}

static ssize_t 	driver_read( struct file *filp, char __user *buf, size_t len, loff_t *off )
{
	printk( KERN_INFO "Llamada a READ" );
	return  0;
}
static ssize_t 	driver_write( struct file *filp, const char __user *buf, size_t len, loff_t *off )
{
	printk( KERN_INFO "Llamada a WRITE" );
	return  len;
}

module_init(funcion_inicio);
module_exit(funcion_exit);


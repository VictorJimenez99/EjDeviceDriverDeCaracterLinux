#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/moduleparam.h>//necesaria para el manejo de parámetros

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VictorJimenez99");
MODULE_DESCRIPTION("Uso de Callbacks");
MODULE_INFO(driver, "TEST_DRIVE");

MODULE_VERSION("1.0");


//int get_param(char *buffer, const struct kernel_param *kp);
//int set_param(const char *val, const struct kernel_param *kp);

static int irq = 7;

int get_param(char *buffer, const struct kernel_param *kp)
{
	int ret;
	printk(KERN_INFO "------------------------");
	printk(KERN_INFO "Función callback get_param; irq: %04d\n",irq);
	printk(KERN_INFO "------------------------");

	printk(KERN_INFO "buffer antes de conversión %s\n", buffer);

	ret = param_get_int( buffer, kp );
	if( ret > 1 )
	{
		printk(KERN_INFO "buffer después de conversión %s\n", buffer);
		return 0;
	}
	return -EPERM;
}

int set_param(const char *val, const struct kernel_param *kp)
{
	int parametro = *(int *)kp->arg;
	int ret;
	printk(KERN_INFO "------------------------");
	printk(KERN_INFO "Función callback set_param; irq: %04d\n",irq);
	printk(KERN_INFO "Parametro val %s\n",val);
	printk(KERN_INFO "Parametro kp->arg %d\n",parametro);
	printk(KERN_INFO "------------------------");

	ret = param_set_int(val, kp);
	if(ret == 0)
	{
		printk(KERN_INFO "Parametro kp->arg %d\n",parametro);
		printk(KERN_INFO "irq: %4d\n",irq);
		
	}
	return ret;
}
const struct kernel_param_ops mis_param_ops = 
{
	.set = set_param,
	.get = get_param,
};

module_param_cb(irq,&mis_param_ops, &irq, 0660);
MODULE_PARM_DESC(irq, "Número de interrupción");

static int __init funcion_inicio(void)
{
	printk(KERN_INFO "------------------------");
	printk(KERN_INFO "INICIO; irq: %04d\n",irq);
	printk(KERN_INFO "------------------------");
	return  0;
}

static void __exit funcion_exit(void)
{
	printk(KERN_INFO "------------------------");
	printk(KERN_INFO "FINAL;  irq: %04d\n",irq);
	printk(KERN_INFO "------------------------");
}

module_init(funcion_inicio);
module_exit(funcion_exit);


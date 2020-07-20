#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/moduleparam.h>//necesaria para el manejo de parámetros

#define N 10

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VictorJimenez99");
MODULE_DESCRIPTION("Uso de Callbacks");
MODULE_INFO(driver, "TEST_DRIVE");

MODULE_VERSION("1.0");


//int get_param(char *buffer, const struct kernel_param *kp);
//int set_param(const char *val, const struct kernel_param *kp);

//static int irq = 7;

static char comando[N];


int get_param(char *buffer, const struct kernel_param *kp)
{
	char* cadena = (char*)kp->arg;
	int ret;
	printk(KERN_INFO "------------------------");
	printk(KERN_INFO "Función callback get_param; ");
	printk(KERN_INFO "------------------------");

	strcpy(buffer, cadena);
	ret = strlen(buffer);
	printk(KERN_INFO "Valor de retorno: %s; long %d...\n", buffer,ret );
	return ret;
}

int set_param(const char *val, const struct kernel_param *kp)
{
	char *parametro = (char *)kp->arg;

	int lon = strlen(val);

	printk(KERN_INFO "------------------------");
	printk(KERN_INFO "Función callback set_param; comando: %s\n",  comando);
	printk(KERN_INFO "Parametro val %s\n",val);
	printk(KERN_INFO "Parametro kp->arg %s\n",parametro);
	printk(KERN_INFO "------------------------");

	if(lon > N)
	{
		printk(KERN_ERR "Error de longitud, en el parametro (%s)\n", val);
		return -ENOSPC;
	}
	else if( lon == 1 )
	{
		printk(KERN_ERR "Error de longitud, en el parametro (%s)\n", val);
		return -EINVAL;
	
	}

	strcpy(parametro, val);
	return 0;
}
const struct kernel_param_ops mis_param_ops = 
{
	.set = set_param,
	.get = get_param,
};

module_param_cb( comando,&mis_param_ops, comando, 0660 );
MODULE_PARM_DESC(comando, "Cadena - parametro");

static int __init funcion_inicio(void)
{
	strcpy( comando, "atrás" );
	printk(KERN_INFO "------------------------");
	printk(KERN_INFO "INICIO; comando: %s\n",comando);
	printk(KERN_INFO "------------------------");
	return  0;
}

static void __exit funcion_exit(void)
{
	printk(KERN_INFO "------------------------");
	printk(KERN_INFO "FINAL;  comando: %s\n",comando);
	printk(KERN_INFO "------------------------");
}

module_init(funcion_inicio);
module_exit(funcion_exit);


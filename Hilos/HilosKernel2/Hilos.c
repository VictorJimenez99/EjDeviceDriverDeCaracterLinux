#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/moduleparam.h>//necesaria para el manejo de parámetros
#include<linux/delay.h>
#include<linux/sched.h>
#include<linux/kthread.h>

#define MAX 4

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VictorJimenez99");
MODULE_DESCRIPTION("Uso de parámetros");
MODULE_INFO(driver, "HILOS DEL KERNEL");

MODULE_VERSION("1.0");


struct task_struct *khilo;


int hilo_kernel(void *data)
{
	int id=*(int*)data;
	register int contador = 0;
	printk(KERN_INFO"Hilo en ejecución con id: %5d",id);

	while(!kthread_should_stop() )
	{
		printk(KERN_INFO "Contador %3d",contador++);
		//schedule();
		ssleep(2);		//seg
		//msleep(500);		//miliseg
		//udelay(1000);		//microseg
	
	}
	return id;
}

/**
 *Puedes pasar argumementos al módulo con sudo insmod param2.ko irq=x comando="y"
 * */

static int __init funcion_inicio(void)
{
	static int id_thread = 10;
	printk(KERN_INFO "-------------------------------------\n");
	khilo = kthread_create(hilo_kernel,(void*)&id_thread,"k_hilo");

	if(IS_ERR(khilo))
	{
		printk("KERN_ERR Error en acreación del hilo...\n");
		return PTR_ERR(khilo);
	}
	wake_up_process(khilo);
	printk(KERN_INFO"Hilo de kernel creado : %s con PID %d \n",khilo->comm,khilo->pid);
	return 0;
}

static void __exit funcion_exit(void)
{
	int ret_hilo_kernel= kthread_stop(khilo);
	printk(KERN_INFO "Terminando la ejecución del módulo de hilos");
	if( ret_hilo_kernel == -EINTR)
		printk(KERN_INFO "Error en la tarmincación  del Hilo");
	else
		printk(KERN_INFO"Hilo de kernel terminado : %d \n",ret_hilo_kernel);
}

static int __init kernel_init(void)
{
	static int id_thread = 10;
	printk(KERN_INFO "-------------------------------------\n");
	khilo = kthread_run(hilo_kernel,(void*)&id_thread,"k_hilo");

	if(IS_ERR(khilo))
	{
		printk("KERN_ERR Error en acreación del hilo...\n");
		return PTR_ERR(khilo);
	}
	printk(KERN_INFO"Hilo de kernel creado : %s con PID %d \n",khilo->comm,khilo->pid);
	return 0;
}


module_init(kernel_init);
module_exit(funcion_exit);



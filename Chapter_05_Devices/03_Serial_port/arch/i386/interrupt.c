/*! Interrupt handling - 'arch' layer(only basic operations) */

#define _ARCH_INTERRUPTS_C_
#include "interrupt.h"

#include <arch/processor.h>
#include <kernel/errno.h>
#include <lib/list.h>
#include <kernel/memory.h>

/*! Interrupt controller device */
extern arch_ic_t IC_DEV;
static arch_ic_t *icdev = &IC_DEV;

/*! interrupt handlers */
static list_t ihandlers[INTERRUPTS];
static int size_l; //broj zahtjeva
static list_t zahtjevi;
static int i=0;

struct zahtjev
{
	uint8 tru;
	void *device; //struct ihndlr
	int irq_num;
	int prio;
	int (*ihandler) (unsigned int, void *device);
};

struct ihndlr
{
	int prio;
	void *device;
	int (*ihandler)(unsigned int, void *device);
	int irq_num;
	list_h list;
};

/*! Initialize interrupt subsystem(in 'arch' layer) */
void arch_init_interrupts()
{
	size_l=0;	
	int i;

	icdev->init();

	for (i = 0; i < INTERRUPTS; i++)
		list_init(&ihandlers[i]);
}

/*!
 * enable and disable interrupts generated outside processor, controller by
 * interrupt controller(PIC or APIC or ...)
 */
void arch_irq_enable(unsigned int irq)
{
	icdev->enable_irq(irq);
}
void arch_irq_disable(unsigned int irq)
{
	icdev->disable_irq(irq);
}

/*! Register handler function for particular interrupt number */
 void arch_register_interrupt_handler(unsigned int inum, void *handler, void *device, int prio) 
{
	struct ihndlr *ih;

	if (inum < INTERRUPTS)
	{
		ih = kmalloc(sizeof(struct ihndlr));
		ASSERT(ih);

		ih->device = device;
		ih->ihandler = handler;
		ih->prio=prio;

		list_append(&ihandlers[inum], ih, &ih->list);
	
	}
	else {
		LOG(ERROR, "Interrupt %d can't be used!\n", inum);
		halt();
	}
	size_l=size_l+1;
}

/*! Unregister handler function for particular interrupt number */
void arch_unregister_interrupt_handler(unsigned int irq_num, void *handler,
					 void *device)
{
	struct ihndlr *ih, *next;

	ASSERT(irq_num >= 0 && irq_num < INTERRUPTS);

	ih = list_get(&ihandlers[irq_num], FIRST);

	while (ih)
	{
		next = list_get_next(&ih->list);

		if (ih->ihandler == handler && ih->device == device)
			list_remove(&ihandlers[irq_num], FIRST, &ih->list);

		ih = next;
	}
}

/*!
 * "Forward" interrupt handling to registered handler
 * (called from interrupts.S)
 */

int cmpa(void *a, void *b){
	struct zahtjev *a1 = kmalloc(sizeof(struct zahtjev));
	struct zahtjev *b1 = kmalloc(sizeof(struct zahtjev));
	a1 = (struct zahtjev *)a;
	b1 = (struct zahtjev *)b;
	if ((a1->prio) >= (b1->prio))
		return 1;
	else return -1;
}
void arch_interrupt_handler(int irq_num)
{
	struct ihndlr *ih;
	list_init(&zahtjevi);

	if (irq_num < INTERRUPTS && (ih = list_get(&ihandlers[irq_num], FIRST)))
	{
		/* enable interrupts on PIC immediately since program may not
		 * return here immediately */
		if (icdev->at_exit)
			icdev->at_exit(irq_num);
		if(i==0) size_l-=5;
		/* Call registered handlers */
		while (ih)
		{
			//ih->ihandler(irq_num, ih->device);
			struct zahtjev *req = kmalloc(sizeof(struct zahtjev));
			req->device = ih->device;
			req->irq_num = irq_num;
			req->prio = ih->prio;
			req->ihandler = ih->ihandler;
			req->tru=1;
			list_h *tmp = kmalloc(sizeof(list_h));
			tmp->object = req;
	
				list_sort_add(&zahtjevi, req, tmp, cmpa);
			ih->irq_num=irq_num;
			ih = list_get_next(&ih->list);
		}
		printf("called interrupt, size of requests  %d \n", size_l);

		if(size_l >= 5){;
			if (i==0) i++;
			struct zahtjev *iter = kmalloc(sizeof(struct zahtjev));
			iter = list_get(&zahtjevi,FIRST);
			struct ihndlr *ihd;
			ih = list_get(&ihandlers[irq_num], FIRST);

			while (iter && iter->tru)
			{
				iter->tru = 0;
				enable_interrupts();
				iter->ihandler(iter->prio, iter->device);
				list_remove(&ihandlers[ihd->irq_num], FIRST, &ihd->list);
				disable_interrupts();
				list_remove(&zahtjevi, FIRST, NULL);
				kfree(iter);
				iter = list_get(&zahtjevi, FIRST);
				ihd = list_get_next(&ih->list);
			}
			size_l=0;
		}

	}

	else if (irq_num < INTERRUPTS)
	{
		LOG(ERROR, "Unregistered interrupt: %d - %s!\n",
		      irq_num, icdev->int_descr(irq_num));
		halt();
	}
	else {
		LOG(ERROR, "Unregistered interrupt: %d !\n", irq_num);
		halt();
	}
}

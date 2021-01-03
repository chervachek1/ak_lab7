#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <hello1.h>
#include <linux/slab.h>
#define DEBUG

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("AK-1 Lab7");
MODULE_AUTHOR("Kuzmich IV-82");

EXPORT_SYMBOL(print_hello);

static struct my_list_head *head;

void clear_my_list(void)
{
    struct my_list_head* temp_first;
    struct my_list_head* temp_second;

    temp_first = head;

    while(temp_first != NULL) {
        temp_second = temp_first->next;
        kfree(temp_first);
        temp_first = temp_second;
    }
}

int print_hello(uint count)
{
    int i;
    struct my_list_head *temp_head1;
    struct my_list_head *temp_head2;

    BUG_ON(count > 10);

    head = kmalloc(sizeof(struct my_list_head*), GFP_KERNEL);

    temp_head1 = head;

    if (count == 0)
    {
        pr_warn("WARNING\nvalue = 0\n");
        return 0;
    }
    else if (count >= 5)// && count <= 10)
    {
        pr_warn("WARNING\nvalue is in betwen 5 and 10\n");
    }
    // else if (count > 10)
    // {
    //     pr_err("ERROR\n value > 10");
    //     return -EINVAL;
    // }
    for (i = 0; i < count; i++)
    {
        temp_head1->next = kmalloc(sizeof(struct my_list_head*), GFP_KERNEL);
        if (i == 9){
            temp_head1 = NULL;
        }

        // BUG_ON(temp_head1 == NULL);

        // if (!temp_head1) {
        //     clear_my_list();
        //     pr_err("ERROR\n out of memory");
        //     return -ENOMEM;
        // }
        temp_head1->time = ktime_get();
        pr_info("Hello, world\n");
        temp_head1->post_time = ktime_get();
        temp_head2 = temp_head1;
        temp_head1 = temp_head1->next;
    }
    kfree(temp_head2->next);
    temp_head2->next = NULL;
    //pr_info("%d", sizeof(struct my_list_head) * count / 1024 / 1024);


    return 0;
}



static int __init hello1_init(void)
{
    pr_info("hello1 init");
    return 0;
}

static void __exit hello1_exit(void)
{
    struct my_list_head* temp_first = head;
    struct my_list_head* temp_second = temp_first;
    pr_debug("Print list start");
    while(temp_first != NULL)
    {
        pr_debug("Time spent %lld", temp_first->post_time - temp_first->time);
        temp_second = temp_first;
        temp_first=temp_second->next;
        kfree(temp_second);
    }
    pr_debug("Print list end");
    pr_info("hello1 exit");
}

module_init(hello1_init);
module_exit(hello1_exit);

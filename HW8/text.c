/*CSAPP第八章作业*/
# include <stdio.h>

/*
8.11
    4行

8.15
    5行

8.19
    2^n

8.23
    未处理信号是不排队的，子进程发送SIGUSR2给父进程，
    父进程调用handler开始处理第一个信号，此时阻塞了SIGUSR2信号的接收，
    第二次产生的信号就添加到了待处理的信号的集合中，这就导致之后陆续产生的SIGUSR2信号被丢弃。
    handler结束后，全局变量counter为1，之后内核检查到队列中有一个未处理的SIGUSR2，便会让父进程接收，
    之后counter++，所以最终打印的数字为2。
*/
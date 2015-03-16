###1.中断和异常的差别？
中断是CPU暂停当前工作，有计划地去处理其他的事情。中断的发生一般是可以预知的，处理的过程也是事先制定好的。处理中断时程序是正常运行的。而异常是CPU遇到了无法响应的工作，而后进入一种非正常状态。异常的出现表明程序有缺陷。

###2.什么是中断向量？Linux怎么分配的？
为每种中断赋予一个中断类型码n,8位无符号整数叫一个向量，在Linux下这样分配：
0  ~ 31    异常和非屏蔽中断
32 ~ 47    屏蔽中断
48 ~ 255   软中断(Linux只用了0x80实现系统调用

###3.什么是中断描述符表？什么是门描述符?
中断描述符表是每个向量对应的门描述符。存入IDTR
>门描述符: ![p1](segment.png)

###4.门描述符有几种？有什么区别？
有三种：1.中断门(会关中断) 2.陷阱门(不会关中断) 3.系统门(DPL=3)

###5.Call和INT指令区别？
CALL指令段内调用将指令指针IP入栈，段间调用先入栈段基址Cs，再入栈IP。CALL调用RET返回再讲地址弹出，相关变量值改变。而INT指令要先将FLAGS（状态标志位）入栈，再将CS入栈，再将Ip入栈，然后还要将相关寄存器值入栈，IRET返回后，相关寄存器的值不发生变化。

###6.如何对中断描述符表进行初始化？

    setup_idt:
    lea ignore_int,%edx /*计算ignore_int地址的偏移量,并将其装入%edx*/
    movl $(__KERNEL_CS &lt;&lt; 16),%eax /* selector = 0x0010 = cs */
    movw %dx,%ax
    movw $0x8E00,%dx /* interrupt gate - dpl=0, present */
    lea SYMBOL_NAME(idt_table),%edi 
    mov $256,%ecx 
    rp_sidt: 
    movl %eax,(%edi) 
    movl %edx,4(%edi) 
    addl $8,%edi
    dec %ecx 
    jne rp_sidt 
    ret

###7.如何插入一个中断门、陷阱门和系统门？
中断门: 

    static void set_intr_gate(unsigned int n, void *addr){
        _set_gate(idt_table+n, 14, 0, addr);    //DPL = 0, 1110 = 14 32位类型码110
    }
陷阱门:

    static void set_trap_gate(unsigned int n, void *addr){
        _set_gate(idt_table+n, 15, 0, addr);    //DPL = 0, 1111 = 14 32位类型码111
    }
系统门:

    static void set_trap_gate(unsigned int n, void *addr){
        _set_gate(idt_table+n, 15, 3, addr);    //DPL = 3, 1111 = 14 32位类型码111
    }
    
###8.内核如何处理异常？

#只是我自己回答 题目不一定打全 简述大意

###1. INTEL微处理器从4位。。。。到32位，什么起了决定性作用？继承了什么？突破了什么？
我觉得地址总线起主要作用，继承了一开始的段机制 突破了数据总线和地址总线不匹配的情况，并且可以直接寻址4G空间

###2. 在80x86寄存器中，哪些寄存器提供一般用户使用？哪些只能被操作系统是使用？
用户可用：EAX EBX ECX EDX ESI EDI SS DS ES CS GS FLAG IP EBP ESP CR0-CR3 DR0-DR3 DR6-DR7 只能系统用:LDTR GDTR TSS

###3. 什么是物理地址？什么是虚拟地址？什么是线性地址？
物理地址：真正存储在物理上的地址 虚拟地址：段+偏移形式的地址 线性地址：经过分页机制转换后的地址

###4. MMU如何把一个虚拟地址转换为物理地址？
通过CR3寄存器获得页目录基址（查询高速缓存，如果命中会跳过翻译过程），通过3级分页找到物理地址

###5.请用C语言描述段描述符表
  struct segment_descriptor{
    short limit1;
    short base1;
    char base2;
    char flag_limit2;
    char base3;
  };

###6.为什么把80x86下段寄存器叫段选择子
因为在保护模式下段已经失去了寻址的作用，而作为一个GDT或者LDT索引，找到该段的基址 界限 标志等

###7.保护模式主要保护什么？通过什么保护？
通过RPL CPL DPL可以进行特权保护，通过分页可以提供内存保护

###8.Linux如何巧妙的绕过段机制？
把段基址置为0，且只有内核态2个段和用户态2个段（INTEL规定GDT第一项应该全0）

###9.页的大小由什么决定？过大过小会有什么问题？
硬件提供可选的页大小，OS可以设置，4KB 4MB 2种可选，Linux采用4KB页。过大的页会造成内存浪费，过小的页大小会是管理变得麻烦，额外浪费更多的内存。

###10.为什么对32位线性地址采用2级页表？
如果采用一级页表需要2^32/2^12 = 2^22 * 4 = 4MB的空间，而2级可以有效减少空间占用4KB + 4KB = 8KB

###12.为什么设计二级页表，页目录和页表各分配10位？如果不是这样会产生什么结果？
平均分才能最大化利用内存

###13.页表项各个位由硬件还是操作系统决定？
由硬件决定，但留给操作系统了一些位 P R/W U/S都可以起到保护作用

###16.TLB起什么作用，什么时候替换
起到加速地址翻译的作用，采用LRU策略

###17.Linux为什么采用三级分页
为了兼容多平台

###18.Intel语法和AT&T语法差别
源操作数和目的操作数位置，表明操作大小，寻址格式等

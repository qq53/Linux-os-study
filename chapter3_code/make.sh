#  File : make.sh
#  ------------------------------------
#  Create date : 2015-03-11 23:41
#  Modified date: 2015-03-17 17:00
#  Author : Sen1993
#  Email : gsen1993@gmail.com
#  ------------------------------------
 
#!/bin/bash
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

[ "$#" -lt 1 ] && echo "need param" && exit

sb_addr="0x"$(cat /proc/kallsyms | egrep "super_blocks$" | awk -F ' ' '{print $1}')
sb_lock="0x"$(cat /proc/kallsyms | egrep "sb_lock$" | awk -F ' ' '{print $1}')
sed "s/SB_ADDRESS/$sb_addr/g" $1".c" > tmp
sed "s/SB_LOCK/$sb_lock/g" tmp > $1".c"
sed "s/TARGET_OBJECT/$1/g" Makefile > tmp
mv Makefile bak
mv tmp Makefile
make
mv bak Makefile

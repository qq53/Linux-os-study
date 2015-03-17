#  File : make.sh
#  ------------------------------------
#  Create date : 2015-03-11 23:41
#  Modified date: 2015-03-11 23:58
#  Author : Sen1993
#  Email : gsen1993@gmail.com
#  ------------------------------------
 
#!/bin/bash
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

[ "$#" -lt 1 ] && echo "need param" && exit

sed "s/TARGET_OBJECT/$1/g" Makefile > tmp
mv Makefile bak
mv tmp Makefile
make
mv bak Makefile

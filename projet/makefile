#----------------------------------------------
all : node
#----------------------------------------------
.c.o :
	gcc -g -I/usr/include/win32 -Wall -c $<
#----------------------------------------------
node : blocknode.o xdr_struct.o
	gcc -g -o node xdr_struct.o blocknode.o -lrpcsvc -lnsl -pthread

#----------------------------------------------
clean :
	/bin/rm -f *.o node *~  *.ps

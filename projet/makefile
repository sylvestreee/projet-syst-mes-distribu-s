#----------------------------------------------
all : node
#----------------------------------------------
.c.o :
	gcc -I/usr/include/win32 -Wall -c $<
#----------------------------------------------
node : blocknode.o xdr_struct.o
	gcc -o node xdr_struct.o blocknode.o -lrpcsvc -lnsl -pthread

#----------------------------------------------
clean :
	/bin/rm -f *.o node *~  *.ps

#----------------------------------------------
all : node
#----------------------------------------------
.c.o :
	gcc -I/usr/include/win32 -Wall -c $<
#----------------------------------------------
node : client.o xdr_matrice.o
	gcc -o client xdr_matrice.o client.o -lrpcsvc -lnsl

#----------------------------------------------
clean :
	/bin/rm -f *.o server client *~  *.ps

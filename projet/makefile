#----------------------------------------------
all : node participant
#----------------------------------------------
.c.o :
	gcc -g -I/usr/include/win32 -Wall -c $<
#----------------------------------------------
node : blocknode.o xdr_struct.o
	gcc -g -Wall -o node xdr_struct.o blocknode.o -lrpcsvc -lnsl -lpthread

participant: participant_node.o xdr_struct.o
	gcc -g -Wall -o participant xdr_struct.o blocknode.o -lrpcsvc -lnsl -lpthread

#----------------------------------------------
clean :
	/bin/rm -f *.o node participant *~  *.ps

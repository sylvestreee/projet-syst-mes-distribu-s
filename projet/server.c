#include "stdio.h"
#include "rpc/types.h"
#include "rpc/xdr.h"
#include "rpc/rpc.h"

/** Appel les fonctions de créations de noeudblock et de noeud particpant transfert les informations et demande à chaque noeudblock ou noeud participant **/
#define PROGNUM 0x20000100
#define VERSNUM 1
#define PROCNUM 1

struct block 
{

};

struct block_node
{

};

struct part_node
{

};

struct server
{
	
};


int * proc_dist(int *n)
{ 
  	static int res = 1 ;
  	printf("server: variable n (debut) : %d,\n",*n) ;
  	res = (*n) + 1 ;
  	*n = *n + 1 ;
  	printf("server: variable n (fin) : %d,\n",*n) ;
  	printf("server: variable res : %d\n",res) ;
  	return &res ;
}

int create_block(int * nb, int * p)
{
	
	
	return 1;	
}



int main (void)
{
  registerrpc(/* prognum */ PROGNUM,
	     /* versnum */ VERSNUM,
	     /* procnum */ PROCNUM,
	     /* pointer on function */ create_block,
	     /* argument decoding */ (xdrproc_t)xdr_int,
	     /* function result encoding */ (xdrproc_t)xdr_int) ;


  svc_run() ; /* server ready for clients */

  return 0;
}

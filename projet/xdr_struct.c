#include "include.h"

/*block * malloc_block(void)
{
	block * b;
	b = (block *) malloc(sizeof(block));
	return b;
}

block_node * malloc_block_node(void)
{
	block_node * bn;
	bn = (block_node *) malloc(sizeof(block_node));
	return bn;
}

void xdr_freep(void *p)
{
  fprintf(stdout, "Zone désallouée : %x\n", (unsigned)p);
  free(p);
}*/

bool_t xdr_block(XDR *xdrs, block * block)
{
	/*block * b;
	int n,c;
	switch (xdrs->x_op)
	{
		case XDR_ENCODE : 
			fprintf(stderr,"xdr_mat  : ENCODE(%d)\n", xdrs->x_op);   
			break; 
	    case XDR_DECODE : 
			fprintf(stderr,"xdr_mat  : DECODE(%d)\n", xdrs->x_op);
			break; 
	    case XDR_FREE :
			fprintf(stderr,"xdr_mat  : FREE(%d)\n", xdrs->x_op);
			xdr_freep(b);
			break; 
	    default :
			fprintf(stderr,"xdr_mat  : default(%d)\n", xdrs->x_op);
			break; 
	}

	if(xdrs->op == XDR_ENCODE)
	{
		b = *block;
		n = block -> num;
		if(!xdr_int(xdrs, &n))
      		return FALSE;
		c = block -> creator;
		if(!xdr_u_int(xdrs, &c))
		    return FALSE;
	}
	else if(xdrs->op == XDR_DECODE)
	{
		if(!xdr_int(xdrs, &n))
			return FALSE;
		if(!xdr_int(xdrs, &c))
			return FALSE;
		b = malloc_block(void);
		*block = b;
	}
	return TRUE;
	*/
	return (xdr_int(xdrs, &block->depth) && 
			xdr_int(xdrs, &block->creator);
}

bool_t xdr_request(XDR * xdrs, char * request)
{
	return (xdr_string(xdrs, &request, LGTH));
}

bool_t xdr_block_node(XDR * xdrs, block_node * bn)
{
	return (xdr_int(xdrs, &bn->num) &&
			xdr_vector(xdrs, &bn->block_node_connect, NB, sizeof(int), xdr_int) &&
			xdr_vector(xdrs, &bn->b, NB, sizeof(block), xdr_block) &&
			xdr_vector(xdrs, &bn->requests, sizeof(request), xdr_request)
}


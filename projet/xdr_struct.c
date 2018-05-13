#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/rpc.h>

#include "include.h"

bool_t xdr_request(XDR * xdrs, char * request)
{
	return (xdr_string(xdrs, &request, LGTH));
}

bool_t xdr_block(XDR *xdrs, block * block)
{
	if(!(xdr_int(xdrs, &block->depth)))
		return (FALSE);
	if(!(xdr_int(xdrs, &block->creator)))
		return (FALSE);
	if(!(xdr_vector(xdrs, &block->requests, NB, sizeof(request), xdr_request)))
		return (FALSE);
	return (TRUE);
}

bool_t xdr_block_node(XDR * xdrs, block_node * bn)
{
	return (xdr_int(xdrs, &bn->num) &&
			xdr_vector(xdrs,(char *) &bn->block_node_connect, NB, sizeof(int), xdr_int) &&
			xdr_vector(xdrs, &bn->b, NB, sizeof(block), xdr_block) &&
			xdr_vector(xdrs, &bn->requests, NB, sizeof(request), xdr_request));
}


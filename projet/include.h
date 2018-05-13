#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#define NB 10
#define LGTH 250

struct block {
	int depth;
	int creator;	
};

typedef struct block block;

typedef char request[LGTH];

struct block_node {
	int num;
	int block_node_connect[NB];
	block b[NB];
	request requests[NB];
};

typedef struct node_block node_block;

block * malloc_block(void);

block_node * malloc_block_node(void);

bool_t xdr_block(XDR *xdrs, block * block);

bool_t xdr_block_node(XDR * xdrs, block_node * bn);

#endif /* __INCLUDE_H__ */

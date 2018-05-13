struct block {
	int depth;
	int creator;	
};

struct block_node {
	int num;
	int block_node_connect[10];
	struct block b[10];
	char * requests[10];
};

typedef struct block block;
typedef struct node_block node_block;

block * malloc_block(void);

block_node * malloc_block_node(void);

bool_t xdr_block(XDR *xdrs, block * b);

bool_t xdr_block_node(XDR * xdrs, block_node * bn);

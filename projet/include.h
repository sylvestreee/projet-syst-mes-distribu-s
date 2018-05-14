#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include <rpc/rpc.h>

#ifdef __cplusplus
extern "C" {
#endif

struct request {
	int sender;
	int entitle;
	int receiver;
};

typedef struct request request;

struct block {
	int depth;
	int creator;
	// hash
	request requests[10];
};

typedef struct block block;

struct participant_node {
	int num;
	int value;
	int block_node_connect[10];
};

typedef struct participant_node participant_node;

struct block_node {
	int num;
	int block_node_connect[10];
	block b[10];
	request requests[10];
	int pn[10];
};

typedef struct block_node block_node;

struct transmission {
	block_node *bn;
	int q;
};
typedef struct transmission transmission;
	
/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_request (XDR *, request*);
extern  bool_t xdr_request (XDR *, request*);
extern  bool_t xdr_block (XDR *, block*);
extern  bool_t xdr_block (XDR *, block*);
extern  bool_t xdr_participant_node (XDR *, participant_node*);
extern  bool_t xdr_participant_node (XDR *, participant_node*);
extern  bool_t xdr_block_node (XDR *, block_node*);
extern  bool_t xdr_block_node (XDR *, block_node*);
extern  bool_t xdr_transmission (XDR *, transmission*);
extern  bool_t xdr_transmission (XDR *, transmission*);

#else /* K&R C */
extern bool_t xdr_request ();
extern bool_t xdr_request ();
extern bool_t xdr_block ();
extern bool_t xdr_block ();
extern bool_t xdr_participant_node ();
extern bool_t xdr_participant_node ();
extern bool_t xdr_block_node ();
extern bool_t xdr_block_node ();
extern bool_t xdr_transmission ();
extern bool_t xdr_transmission ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* __INCLUDE_H__ */

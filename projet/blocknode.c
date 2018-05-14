#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/rpc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include "include.h"

/* on utilise les thread pour lancer à la fois un serveur et un client pour un seul noeud*/

int array(block * b)
{
    int i = 0;
    while(b[i].creator != -1)
    {
        i++;
    }
    return i;
}

int *hello(void)
{
    static int r = 0;
    printf("Hello world\n");
    fflush(stdout);
    return &r;
}

int *create_block(block_node *bn)
{	
	static int r = 0;
	printf("create block %d\n", bn->b[0].depth);
	fflush(stdout);
	int i = 0, length = array(bn->b);
	block bl;
    
	// empty blockchain
	if(bn->b[0].creator == -1)
	{
		bl.depth = 0;
		bl.creator = bn->num;
		// hash
		while(bn->requests[i].sender != -1) // remplir le tableau du bloc / vider le tableau du noeud
		{
			bl.requests[i].sender = bn->requests[i].sender;
            bl.requests[i].entitle = bn->requests[i].entitle;
            bl.requests[i].receiver = bn->requests[i].receiver;
            bn->requests[i].sender = -1;
            bn->requests[i].entitle = "nothing";
            bn->requests[i].receiver = -1;
			i++;
		}
		bn->b[0] = bl;
	}
	// blockchain's not full
	if(length < 10)
	{
		bl.depth = length;
		bl.creator = bn->num;
		// hash
		while(bn->requests[i].sender != -1)
		{
			bl.requests[i].sender = bn->requests[i].sender;
            bl.requests[i].entitle = bn->requests[i].entitle;
            bl.requests[i].receiver = bn->requests[i].receiver;
            bn->requests[i].sender = -1;
            bn->requests[i].entitle = "nothing";
            bn->requests[i].receiver = -1;
			i++;
		}
		bn->b[length] = bl;
	}

	// blockchain's full
	else if(length == 10)
	{
		r = -1;
		return &r;
	}

	// transmit_blockchain_points function
	printf("create block in %d\n", bn->num);
	return &r;	
}

/*
int * ask_for_blocks(void)
{
    return 0;
}

int * transmit_blocks(void)
{
    return 0;
}

int * transmit_requests(void)
{
    return 0;
}

    int * transmit_blockchain_points(void)
    {

    }

int participant_number(block_node *bn)
{
    int i = 0, j = 0, n;
    while(bn->b[i] != NULL) // parcours de la blockchain
    {
        while(bn->b[i].cleared_requests[j] != NULL) // parcours de la liste des requêtes 
        {
            if(bn->b[i].cleared_requests[j].receiver == bn->num &&
               strcmp(bn->b[i].cleared_requests[j].entitle, "participant_inscription") == 0) 
            {
                n++;
            }
            j++;
        }
        i++;
    }
    return n;
}

// when a participant node asked for an inscription
int *ask_for_inscription()
{
    block_node *bn; // shouldn't exist
    if(participant_number(bn) < NB)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
*/

void *node(void *arg)
{
    printf("launching server\n");

    block_node * bn = (block_node *) arg;
	
    int stop = 0;
    int ask,i;
    enum clnt_stat stat;
    static int res;
	for(i = 0; i < 10; i++)
	{
		printf("%d\n",bn->b[i].depth);	
	} 
	printf("%d\n",bn->num);

    while(stop != 1)
    {
        printf(">");
        scanf("%d",&ask);
        switch(ask)
        {
            case 0:
				scanf("%d",&ask);
                stat = callrpc("localhost",
                   	ask,ask,1,
                    (xdrproc_t)xdr_void, (void *)0,
                    (xdrproc_t)xdr_int, (char *)&res);

                if (stat != RPC_SUCCESS)
                {
                    fprintf(stderr, "Echec de l'appel distant\n");
                    clnt_perrno(stat);
                    fprintf(stderr, "\n");
					pthread_exit(NULL);
                }
                break;
            case 1:
				stat = callrpc("localhost",
                   	ask,ask,2,
                    (xdrproc_t)xdr_block_node,(char *)bn,
                    (xdrproc_t)xdr_char, (char *)&res) ;

                if (stat != RPC_SUCCESS)
                {
                    fprintf(stderr, "Echec de l'appel distant\n");
                    clnt_perrno(stat);
                    fprintf(stderr, "\n");
					pthread_exit(NULL);
                }
                break;
            case 2:
				break;
			case 3:
				break;
			case 4:
				stop = 1;
				pthread_exit(NULL);
                break;
            default:
                break;
        }
        printf("\n");
    }
    
    pthread_exit(NULL);
}

int main(int argc, char ** argv)
{
    pthread_t thread_client;
	int i = 0;
	int PROGNUM;
	int VERSNUM;
    block b;

	if(argc < 3 || argc >= 12)
	{
		printf("Too few argument\n");
		return 0;
	}
	
	block_node * bn = (block_node *) malloc(sizeof(block_node));
	bn->num = atoi(argv[1]);
	
	PROGNUM = bn->num;
	VERSNUM = bn->num;

	for(i = 2; i < argc; i++)
	{
		bn->block_node_connect[i-2] = atoi(argv[i]);
	}

	for(i = 0; i<10; i++)
	{
		bn->b[i] = b;
		bn->b[i].depth = -1;
		bn->b[i].creator = -1;
	}
    
    if(pthread_create(&thread_client, NULL, node, (void *)bn) == -1){
        perror("pthread_create");
        return EXIT_FAILURE;
    }

    if(registerrpc(PROGNUM, VERSNUM, 1, hello, (xdrproc_t)xdr_void, 
		(xdrproc_t)xdr_char) == -1){
        fprintf(stderr, "unable to register 'hello' !\n");
        return EXIT_FAILURE;
    }

	if(registerrpc(PROGNUM, VERSNUM, 2, create_block, 	
		(xdrproc_t)xdr_block_node, 
		(xdrproc_t)xdr_char) == -1){
        fprintf(stderr, "unable to register 'create_block' !\n");
        return EXIT_FAILURE;
    }

    printf("thread launched\n");

    svc_run();

    if(pthread_join(thread_client,NULL)==-1){
        perror("pthread_join");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/** Peut se connecter à un ou plusieurs blocknode à travers le serveur principale **/
#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/rpc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "include.h"

participant_node * participant_n = NULL;

/* on utilise les thread pour lancer à la fois un serveur et un client pour un seul noeud*/

void *transmit_blockchain_points(float value)
{
	participant_node *pn = participant_n;
	pn->value += value;
}

void *ask_for_block_fraction()
{
	participant_node *pn = participant_n;
	return pn->value;
}


void *node_particpant(void *arg)
{
    printf("launching server\n");

    enum clnt_stat stat;
	static int res;	

    while(1)
    {
        printf(">");
        scanf("%d",&ask);
        switch(ask)
        {
            case 0:
		stat = callrpc("localhost",bn->num,bn->num,1,
                    	(xdrproc_t)xdr_block_node,(char *)bn,
                    	(xdrproc_t)xdr_block_node,(char *)bn_res) ;

                if (stat != RPC_SUCCESS)
                {
                    	fprintf(stderr, "Echec de l'appel distant\n");
                    	clnt_perrno(stat);
			fprintf(stderr, "\n");
			pthread_exit(NULL);
                }
                break;
            case 1:
		stat = callrpc("localhost",b_neigboorh,b_neigboorh,2,
                    (xdrproc_t)xdr_block_pointer,(char *)b,
                    (xdrproc_t)xdr_int,(char *)&res) ;
		
		if (stat != RPC_SUCCESS)
                {
                    	fprintf(stderr, "Echec de l'appel distant\n");
                    	clnt_perrno(stat);
                    	fprintf(stderr, "\n");
			pthread_exit(NULL);
                }
		
		break;
            default:
		printf_block_node(block_n);
                break;
        }
        printf("\n");
    }
    
    pthread_exit(NULL);
}

int main(int argc, char ** argv)
{
    pthread_t thread_client;
	int i = 0, j = 0;
	int PROGNUM;
	int VERSNUM;
    	//block_pointer bl = initialize_block(bl);

	if(argc < 3 || argc >= 12)
	{
		printf("Too few argument\n");
		return 0;
	}

    
	if(pthread_create(&thread_client, NULL, node, (void *)block_n) == -1)
	{
		perror("pthread_create");
		return EXIT_FAILURE;
	}

	if(registerrpc(PROGNUM, VERSNUM, 1, create_block, 	
		(xdrproc_t)xdr_block_node, 
		(xdrproc_t)xdr_block_node) == -1)
	{
	        fprintf(stderr, "unable to register 'create_block' !\n");
	        return EXIT_FAILURE;
	}
	if(registerrpc(PROGNUM,VERSNUM, 2, transmit_blocks,
		(xdrproc_t)xdr_block_pointer, (xdrproc_t)xdr_int) == -1)
	{
		fprintf(stderr, "unable to register 'transmit_block' !\n");
	        return EXIT_FAILURE;
	}

	printf("thread launched\n");
	svc_run();

	if(pthread_join(thread_client,NULL)==-1)
	{
		perror("pthread_join");
	        return EXIT_FAILURE;
	}

    	return EXIT_SUCCESS;
}

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

int *transmit_blockchain_points(float value)
{
	static int res;
	participant_node *pn = participant_n;
	pn->value += value;
	return &res;
}

int * ask_for_block_fraction(void * v)
{
	participant_node *pn = participant_n;
	return &pn->value;
}

void *node_participant(void *arg)
{
    printf("launching server\n");

    enum clnt_stat stat;
    static int res;	
    int ask;
    float test = 1;

    while(1)
    {
        printf(">");
        scanf("%d",&ask);
        switch(ask)
        {
            case 0:
		stat = callrpc("localhost",participant_n->num,
			participant_n->num,1,
                    	(xdrproc_t)xdr_float,(char *)&test,
                    	(xdrproc_t)xdr_int,(char *)&res) ;

                if (stat != RPC_SUCCESS)
                {
                    	fprintf(stderr, "Echec de l'appel distant\n");
                    	clnt_perrno(stat);
			fprintf(stderr, "\n");
			pthread_exit(NULL);
                }
                break;
            case 1:
		stat = callrpc("localhost",participant_n->num,
		     participant_n->num,2,
                    (xdrproc_t)xdr_void,(char *)0,
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

	if(argc < 3 || argc >= 12)
	{
		printf("Too few/many argument\n");
		return 0;
	}
	
	participant_n = (participant_node *)malloc(sizeof(participant_node));

	participant_n->num = atoi(argv[1]);
	participant_n->value = 0;
	for(i = 2; i < argc; i++)
	{
		participant_n->block_node_connect[i] = atoi(argv[i]);
	}
	
	PROGNUM = participant_n->num;
	VERSNUM = participant_n->num;

	if(pthread_create(&thread_client, NULL, node_participant, NULL) == -1)
	{
		perror("pthread_create");
		return EXIT_FAILURE;
	}

	if(registerrpc(PROGNUM, VERSNUM, 1, transmit_blockchain_points, 	
		(xdrproc_t)xdr_float, 
		(xdrproc_t)xdr_int) == -1)
	{
	        fprintf(stderr, "unable to register 'transmit_blockchain_point' !\n");
	        return EXIT_FAILURE;
	}
	if(registerrpc(PROGNUM,VERSNUM, 2, ask_for_block_fraction,
		(xdrproc_t)xdr_void, (xdrproc_t)xdr_int) == -1)
	{
		fprintf(stderr, "unable to register 'ask_for_block_fraction' !\n");
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

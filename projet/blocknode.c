#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/rpc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "include.h"

/* on utilise les thread pour lancer à la fois un server et un client pour un seul noeud*/

int * hello(void)
{
    static int r = 0;
    printf("Hello world\n");
    fflush(stdout);
    return &r;
}

int * create_block(block_node * bn)
{
	printf("create block %d\n",bn->num);
	return &bn->num;
}

int * ask_for_blocks(void)
{

}

int * transmit_blocks(void)
{

}

int * transmit_requests(void)
{

}

int * transmit_blockchain_points(void)
{

} 

void *node(void *arg)
{
    printf("launching server\n");

    block_node * bn = (block_node *) arg;
	
    int stop = 0;
    int ask;
    enum clnt_stat stat ;
    static int res;

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
                    (xdrproc_t)xdr_char, (char *)&res) ;

                if (stat != RPC_SUCCESS)
                {
                    fprintf(stderr, "Echec de l'appel distant\n") ;
                    clnt_perrno(stat) ;
                    fprintf(stderr, "\n") ;
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
                    fprintf(stderr, "Echec de l'appel distant\n") ;
                    clnt_perrno(stat) ;
                    fprintf(stderr, "\n") ;
					pthread_exit(NULL);
                }
				printf("%d\n",res);
                break;
            case 2:
			case 3:
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
	int PROCNUM;

	if(argc < 3 || argc >= 12)
	{
		printf("To few argument\n");
		return 0;
	}
	
	block_node * bn = (block_node *) malloc(sizeof(block_node));
	bn->num = atoi(argv[1]);

	PROGNUM = bn->num;
	VERSNUM = bn->num;
	PROCNUM = bn->num;

	for(i = 2; i < argc; i++)
	{
		bn->block_node_connect[i-2] = atoi(argv[i]);
	}
	printf("%d, %d, %d\n",PROGNUM,VERSNUM,PROCNUM);
    
    if(pthread_create(&thread_client, NULL, node, (void *)bn) == -1){
        perror("pthread_create");
        return EXIT_FAILURE;
    }

    if(registerrpc(PROGNUM, VERSNUM, PROCNUM, hello, (xdrproc_t)xdr_void, 
		(xdrproc_t)xdr_char) == -1){
        fprintf(stderr, "unable to register 'hello' !\n");
        return EXIT_FAILURE;
    }

	if(registerrpc(PROGNUM, VERSNUM, PROCNUM+1, create_block, 	
		xdr_block_node, 
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

#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/rpc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define PROGNUM 0x20000135
#define VERSNUM 1
#define PROCNUM 1

/* on utilise les thread pour lancer à la fois un server et un client pour un seul noeud*/

int * hello(void)
{
    static int r = 0;
    printf("Hello world\n");
    fflush(stdout);
    return &r;
}

void *node(void *arg)
{
    printf("launching server\n");

    int stop = 0;
    int ask;
    enum clnt_stat stat ;
    static int res;

    while(stop != 1)
    {
        printf(">");
        scanf("%d",&ask);
        switch(ask)
        {
            case 0:
                stat = callrpc("localhost",
                    PROGNUM, VERSNUM, PROCNUM,
                    (xdrproc_t)xdr_void, (void *)0,
                    (xdrproc_t)xdr_int, (char *)&res) ;

                if (stat != RPC_SUCCESS)
                {
                    fprintf(stderr, "Echec de l'appel distant\n") ;
                    clnt_perrno(stat) ;
                    fprintf(stderr, "\n") ;
                    //return 1 ;
                }
                break;
            case 1:
                stop = 1;
                break;
            default:
                break;
        }
        printf("\n");
    }
    
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t thread_client;
    
    if(pthread_create(&thread_client, NULL, node, NULL) == -1){
        perror("pthread_create");
        return EXIT_FAILURE;
    }

    if(registerrpc(PROGNUM, VERSNUM, PROCNUM, hello, (xdrproc_t)xdr_void, (xdrproc_t)xdr_int) == -1){
        fprintf(stderr, "unable to register 'hello' !\n");
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

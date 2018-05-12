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

int res, n;
enum clnt_stat stat;

void hello()
{
    printf("Hello world");
}

void *node_server(void *arg)
{
    printf("launching server\n");
    
    stat = callrpc(/* host */ "turing",
         /* prognum */ PROGNUM,
         /* versnum */ VERSNUM,
         /* procnum */ PROCNUM,
         /* argument encoding filter */ (xdrproc_t) xdr_void,
         /* argument */ (char *)&n,
         /* return value decoding filter */ (xdrproc_t) xdr_void,
         /* retour value */ (char *)&res);

   if (stat != RPC_SUCCESS)
   {
     fprintf(stderr, "Echec de l'appel distant\n");
     clnt_perrno(stat);
     fprintf(stderr, "\n");
     pthread_exit(NULL);
   }
 
   //printf("n : %s\n",n);
   //printf("res : %s\n", res);

    pthread_exit(NULL);
}

int main(void)
{
    pthread_t thread_client;
    
    if(pthread_create(&thread_client, NULL, node_server, NULL) == -1){
        perror("pthread_create");
        return EXIT_FAILURE;
    }

    if(registerrpc(PROGNUM, VERSNUM, PROCNUM, hello, (xdrproc_t)xdr_void, (xdrproc_t)xdr_void) == -1){
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

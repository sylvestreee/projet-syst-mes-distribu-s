/** Peut se connecter à un ou plusieurs blocknode à travers le serveur principale **/
#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/rpc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "include.h"

/* on utilise les thread pour lancer à la fois un serveur et un client pour un seul noeud*/

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

void *earn_points(float value)
{
	participant_node *pn; // shouldn't exist
	pn->value += value;
}

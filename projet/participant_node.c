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

void *transmit_blockchain_points(float value)
{
	participant_node *pn = (participant_node *) malloc(sizeof(participant_node)); // shouldn't exist
	pn->value += value;
}

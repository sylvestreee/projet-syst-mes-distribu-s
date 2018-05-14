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
	pn->value += value;
}

void *get_block_fraction()
{
	return pn->value;
}

void ask_for_block_fraction()
{
	participant_node * pn = participant_n;
	block * participants = (block_node*) malloc(sizeof(block_node));
	int res = -1, res2 = -1, n;
	while(res == -1) // choix d'une noeud bloc au hasard
	{
		n = rand() % 10;
		res = pn->block_node_connect[n];
	}

	/* callrpc de get_participant sur le noeud bloc de numéro res
	 * retour de la fonction à mettre dans participants
	 */

	while(res2 == -1) // choix d'un noeud participant au hasard
	{
		n = rand() % 10;
		res2 = participant[n];
	}

	/* callrpc de get_block_fraction sur le noeud participant de numéro res2
	 * retour de la fonction à mettre dans n
	 */

	printf("Participant node %d has a block fraction of %d\n", res2, n);
}
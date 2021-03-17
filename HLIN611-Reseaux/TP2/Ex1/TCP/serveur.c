#include <stdio.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

/* Rôle du serveur (attention, se serveur ne traite qu'un client !) :
 -  accepter la demande de connexion d'un client ;

 - en boucle (infinie) : 1) recevoir un message de type "long int" ;
   2) comparer sa valeur avec la précédente reçue ; 3) si la valeur
   reçue est inférieure à la précédente, afficher une trace notifiant
   ce cas; 4) dans tous les cas, afficher le nombre total d'octets
   reçus depuis le début et le nombre d'appels à la fonction recv(...)

 - termine apres départ du client.

*/

/* Réutiliser les fonctions de l'exercice 3 du TP précédent */
/* les deux derniers parametres sont les compteurs, auxquels doit s'ajouter le nombre d'octets
   lus depuis le buffer de réception et le nombre d'appels reussis à recv(..)
   (ils sont initialisés par l'appelant.*/
/* Si vous avez utilisé des variables globales, pas de souci. */
int recvTCP(int socket, char *buffer, size_t length, unsigned int *nbBytesReceved, unsigned int *nbCallRecv){
	long int valeur = -1;
	int received = 1;
	while (received != 0){
		received = recv(socket, buffer, length, 0);
		if (received <= 0){
			return received;
		}

		char *eptr;
		long int result = strtol(buffer, &eptr, 10);
		if (valeur < result){
			printf("La valeur reçue est inférieure à la précédente\n");
		}
		valeur = result;

		(*nbBytesReceved) += received;
		(*nbCallRecv)++;
	}
	return 1;
}

int main(int argc, char *argv[]){
	if (argc < 2){
		printf("utilisation: %s numero_port\n", argv[0]);
		exit(1);
	}

	/*  Création de la socket d'écoute, nomage et mise en écoute.*/
	int ds = socket(PF_INET, SOCK_STREAM, 0);
	if (ds == -1){
		perror("Problème à la création de la socket: ");
		exit(1);
	}

	// Penser à tester votre code progressivement.
	// Rappel un seul client est à traiter.
	printf("Serveur : j'attends la demande du client (accept) \n");

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(atoi(argv[1]));

	if (bind(ds, (struct sockaddr *)&server, sizeof(server)) < 0){
		perror("Serveur : erreur bind");
		close(ds);
		exit(1);
	}
	printf("Serveur: nommage : ok\n");
	int ecoute = listen(ds, 10);
	if (ecoute < 0)	{
		printf("Serveur : je suis sourd(e)\n");
		close(ds);
		exit(1);
	}
	printf("Serveur: mise en écoute : ok\n");

	struct sockaddr_in adCv;
	socklen_t lgCv = sizeof(struct sockaddr_in);

	for (int i = 0; i < 3; ++i) {

		int dsCv = accept(ds, (struct sockaddr *)&adCv, &lgCv);
		if (dsCv < 0){
			perror("Serveur, probleme accept :");
			close(ds);
			exit(1);
		}

		printf("Serveur: le client %s:%d est connecté  \n", inet_ntoa(adCv.sin_addr), ntohs(adCv.sin_port));

		/* Réception de messages, chaque message est un long int */

		long int messagesRecus[2]; // je defini ce tableau pour garder le
								   // message précédent (voir plus bas)

		unsigned int nbTotalOctetsRecus = 0;
		unsigned int nbAppelRecv = 0;

		// recevoir un premier message puis mettre en place la boucle de
		// réception de la suite.
		int k = sizeof(long int);

		int rcv = recvTCP(dsCv, (char *)messagesRecus, k, &nbTotalOctetsRecus, &nbAppelRecv);

		/* Traiter TOUTES les valeurs de retour (voir le cours ou la documentation). */
		if (rcv < 0){
			perror("Erreur de réception");
			close(dsCv);
			close(ds);
			exit(1);
		}

		printf("Serveur : j'ai reçu au total %d octets avec %d appels à recv \n", nbTotalOctetsRecus, nbAppelRecv);

	    printf("Serveur : saisir un caractère avant de poursuivre \n");
	    fgetc(stdin);
	    
		while (1){	
			// le serveur n'a pas connaissance du nombre de messages
			// qu'il recevra, donc, il boucle et la gestion des
			// valeurs de retours de fonctions permettra de sortir
			// de la boucle pour arrêter le serveur.

			rcv = recvTCP(dsCv, (char *)(messagesRecus + 1), k, &nbTotalOctetsRecus, &nbAppelRecv);

			/* Traiter TOUTES les valeurs de retour (voir le cours ou la documentation). */
			if (rcv < 0){
				perror("Erreur de réception");
				close(dsCv);
				close(ds);
				exit(1);
			}
			else if (rcv == 0){	break;}

			if (messagesRecus[1] < messagesRecus[0]) // si la valeur reçue est inférieure à la précédente, alors désordre.
				printf("Serveur : reception dans le désordre : %ld reçu après %ld \n", messagesRecus[1], messagesRecus[0]);

			/* garder la valeur précédente pour la prochaine comparaison*/
			messagesRecus[0] = messagesRecus[1];

			printf("Serveur : j'ai reçu au total %d octets avec %d appels à recv \n", nbTotalOctetsRecus, nbAppelRecv);
		}

		// terminer proprement votre programme
		close(dsCv);
		printf("Serveur : fin du dialogue avec le client\n");
	}

	close(ds);
	printf("Serveur : je termine\n");
}
#include <stdio.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/select.h>

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
	size_t received ;
	size_t totalRCV = 0;
	unsigned int cptrRCV = 0;

	while (totalRCV < length){
		received = recv(socket, buffer + totalRCV, length - totalRCV, 0);
		cptrRCV++;

		if (received <= 0){
			(*nbBytesReceved) += totalRCV;
			(*nbCallRecv) += cptrRCV;

			printf("%ld\n", received);
			return received;
		}

		totalRCV += received;
	}

	(*nbBytesReceved) += totalRCV;
	(*nbCallRecv) += cptrRCV;
	return 1;
}

/*int sendTCP(int socket, char *buffer, size_t length, unsigned int *nbBytesSent, unsigned int *nbCallSend){
	size_t rcv;
	size_t totalSent = 0;
	unsigned int cptrSend = 0;

	while (totalSent < length)	{
		sent = send(socket, buffer + totalSent, length - totalSent, 0);
		cptrSend++;
		if (sent <= 0)		{
			(*nbBytesSent) += totalSent;
			(*nbCallSend) += cptrSend;
			return sent;
		}
		totalSent += sent;
	}
	(*nbBytesSent) += totalSent;
	(*nbCallSend) += cptrSend;

	return 1;
}*/

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


	// DEBUT DU MULTIPLEXAGE
	fd_set set ;
	fd_set settmp ;

	FD_ZERO(&set);
	FD_SET(ds, &set);

	int max = ds;

	while(1) {
		printf("Serveur : Tour de while\n");

		settmp = set;
		select(max+1, &settmp, NULL, NULL, NULL);

		for (int df = 2; df <= max; df++){
			printf("Serveur : Tour de for\n");

			if (!FD_ISSET(df, &settmp)) {
				printf("Serveur : !ISSET\n"); 
				continue;
			}

			if(df == ds) {
				struct sockaddr_in adCv;
				socklen_t lgCv = sizeof(struct sockaddr_in);

				int dSC = accept(ds, (struct sockaddr *)&adCv, &lgCv);
				if (dSC < 0) {
					perror("Accept error : ") ;
					continue; 
				}
				printf("Serveur : le client %s:%d est connecté  \n", inet_ntoa(adCv.sin_addr), ntohs(adCv.sin_port));

				FD_SET(dSC, &set) ;
				if (max < dSC) max = dSC;
				continue;
			} 


			printf("Serveur : Debut MULTIPLEXAGE\n");
			long int messagesRecus[2]; 

			unsigned int nbTotalOctetsRecus = 0;
			unsigned int nbAppelRecv = 0;

			int k = sizeof(long int);
			int rcv = recvTCP(df, (char *)messagesRecus, k, &nbTotalOctetsRecus, &nbAppelRecv);
			if (rcv < 0){
				perror("Erreur de réception");
				FD_CLR(df, &set);
				close(df);
				continue;
			}

			if (rcv == 0) {
				printf("Fin lecture\n");
				FD_CLR(df, &set);
				close(df);
				continue;
			}

			
			rcv = recvTCP(df, (char *)(messagesRecus + 1), k, &nbTotalOctetsRecus, &nbAppelRecv);
			if (rcv < 0){
				perror("Erreur de réception");
				FD_CLR(df, &set);
				close(df);
				continue;
			}

			if (rcv == 0) {
				printf("Fin lecture\n");
				FD_CLR(df, &set);
				close(df);
				continue;
			}

			printf("%ld > %ld ???\n", messagesRecus[0], messagesRecus[1]);

			if (messagesRecus[1] < messagesRecus[0]){
				printf("Serveur : reception dans le désordre : %ld reçu après %ld \n", messagesRecus[1], messagesRecus[0]);
			}

			messagesRecus[0] = messagesRecus[1];

			printf("Serveur : j'ai reçu au total %d octets avec %d appels à recv \n", nbTotalOctetsRecus, nbAppelRecv);

		
		}
	}


	close(ds);
	printf("Serveur : je termine\n");
}
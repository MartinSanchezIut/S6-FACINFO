#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>


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

int sendTCP(int socket, const char *buffer, size_t length, unsigned int *nbBytesSent, unsigned int *nbCallSend){
	size_t sent;
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
}


int main(int argc, char *argv[]){
	if (argc != 4)	{
		printf("utilisation : %s <ip_serveur> <port_serveur> <username>\n", argv[0]);
		exit(0);
	}
	int ds = socket(AF_INET, SOCK_STREAM, 0);
	if (ds == -1)	{ printf("Client : pb creation socket\n");exit(1);}

	struct sockaddr_in adrServ;
	adrServ.sin_family = AF_INET;
	adrServ.sin_port = htons(atoi(argv[2]));
	if (inet_pton(AF_INET, argv[1], &(adrServ.sin_addr)) < 1){perror("client: inet_pton() error ->");exit(1);}
	int conn = connect(ds, (struct sockaddr *)&adrServ, sizeof(adrServ));
	if (conn < 0)	{perror("Client: pb au connect :");close(ds);exit(1);}

	int snd;
	char* name = argv[3];
	unsigned int nbTotalOctetsEnvoyes = 0;
	unsigned int nbAppelSend = 0;

/*
	long nameSize = strlen(name);
	int snd = sendTCP(ds, (char *)&nameSize, sizeof(nameSize), &nbTotalOctetsEnvoyes, &nbAppelSend);
	if (snd < 0){perror("Probleme d'emission taille");close(ds);exit(1);}

	snd = sendTCP(ds, (char *)&name, nameSize, &nbTotalOctetsEnvoyes, &nbAppelSend);
	if (snd < 0){perror("Probleme d'emission taille");close(ds);exit(1);}
	printf("DEBUG: %s : %ld  \n", name, nameSize);
*/

	printf("Chat > Connexion a %s:%s reussie \n", argv[1], argv[2]);
	printf("Chat > Bienvenue %s ! \n", name);


	switch (fork()){
		case -1: // Erreur
			perror("Erreur de Fork \n");
			close(ds);
			exit(1);
			break;
		case 0 : // Fils reçoit
			exit(1);
			break;
				
		default:  ;// Pere envoit
			char buf[2048];
			do {
				printf(" <   ");
				fgets(buf, sizeof(buf), stdin);
				buf[strcspn(buf, "\n")] = 0;
				buf[2048-1] = '\0';

				//printf("DEBUG: %s : %ld  ", buf, strlen(buf));
				//printf("  : %d \n", strncmp(buf, "/quit\n", 6));

				long size = strlen(buf);
				snd = sendTCP(ds, (char *)&size, sizeof(size), &nbTotalOctetsEnvoyes, &nbAppelSend);
				if (snd < 0){perror("Probleme d'emission taille");close(ds);exit(1);}

				snd = sendTCP(ds, (char *)&buf, size, &nbTotalOctetsEnvoyes, &nbAppelSend);
				if (snd < 0){perror("Probleme d'emission taille");close(ds);exit(1);}


			}while (strncmp(buf, "/quit\n", 6) > 0) ;
			break;
	}

	close(ds);
	printf("Chat > Aurevoir %s ! \n", name);
	printf("\n Chat > Fin de connexion a %s:%s\n - %d^  %dv \n", argv[1], argv[2], nbTotalOctetsEnvoyes, nbAppelSend);
	exit(0);
}

#include <stdio.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

// taille du buffer qui me permet de récupérer le contenu du fichier à recevoir bloc par bloc. Vous pouvez changer cette valeur.
#define MAX_BUFFER_SIZE 500

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

int main(int argc, char *argv[]){
	if (argc < 2)	{
		printf("utilisation: %s numero_port\n", argv[0]);
		exit(1);
	}
	int ds = socket(PF_INET, SOCK_STREAM, 0);
	if (ds == -1)	{
		perror("Problème à la création de la socket: ");
		exit(1);
	}
	printf("Serveur : j'attends la demande du client (accept) \n");

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(atoi(argv[1]));

	if (bind(ds, (struct sockaddr *)&server, sizeof(server)) < 0)	{
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


	/* boucle pour le traitement itératif des clients */   //	while (1){
	for (int i = 0; i < 5; ++i) {
		int dsCv = accept(ds, (struct sockaddr *)&adCv, &lgCv);
		if (dsCv < 0){
			perror("Serveur, probleme accept :");
			close(ds);
			continue;
		}
		printf("-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=- \n");
		printf("Serveur: le client %s:%d est connecté  \n\n", inet_ntoa(adCv.sin_addr), ntohs(adCv.sin_port));


		switch (fork())		{
			case -1: // Erreur
				perror("Erreur de Fork \n");
				close(dsCv);
				continue;
				break;
			case 0 : // Fils
				close(ds);

				unsigned int nbTotalOctetsRecus = 0;
				unsigned int nbAppelRecv = 0;

				// je doit recevoir des données me permettant d'obtenur le nom d'un fichier

				int name_size;
				int rcv = recvTCP(dsCv, (char *)&name_size, sizeof(name_size), &nbTotalOctetsRecus, &nbAppelRecv);
				if (rcv < 0){
					perror("Erreur de réception");
					close(dsCv);
					close(ds);
					exit(1);  //continue;
				}
				printf("Taille du nom reçu : %d \n", name_size);
				printf("Serveur : j'ai reçu au total %d octets avec %d appels à recv \n\n", nbTotalOctetsRecus, nbAppelRecv);

				char *file_name = malloc(name_size);
				rcv = recvTCP(dsCv, (char *)file_name, name_size, &nbTotalOctetsRecus, &nbAppelRecv);
				if (rcv < 0){
					perror("Erreur de réception");
					close(dsCv);
					close(ds);
					exit(1);  //continue;
				}
				printf("Nom du fichier reçu : %s \n", file_name);
				printf("Serveur : j'ai reçu au total %d octets avec %d appels à recv \n\n", nbTotalOctetsRecus, nbAppelRecv);
				//printf("Serveur, je vais recevoir le fichier %s\n", file_name);





				// je construis le chemin vers le fichier à créer.
				char *filepath = malloc(name_size + 16); // ./reception/+nom fichier
				filepath[0] = '\0';
				strcat(filepath, "./reception/");
				strcat(filepath, file_name);
				free(file_name);

				// j'ouvre le fichier dans lequel je vais écrire
				FILE *file = fopen(filepath, "wb");
				if (file == NULL)	{ // servez vous de cet exemple pour le traitement des erreurs.
					perror("Serveur : erreur ouverture fichier: \n");
					free(filepath);
					close(dsCv);
					exit(1);  //continue; // passer au client suivant
				}
				free(filepath); // je n'en ia plus besoin.


				//reception des données me permettant de recevoir correctement le contenu du fichier.
				int file_size;
				rcv = recvTCP(dsCv, (char *)&file_size, sizeof(file_size), &nbTotalOctetsRecus, &nbAppelRecv);
				if (rcv < 0){
					perror("Erreur de réception");
					close(dsCv);
					close(ds);
					exit(1);  //continue;
				}
				printf("Taille du fichier reçu : %d \n", file_size);
				printf("Serveur : j'ai reçu au total %d octets avec %d appels à recv \n\n", nbTotalOctetsRecus, nbAppelRecv);

				
				int contentReceived = 0; // Compte le nombre d'octets du fichier reçu
				while (contentReceived < file_size)		{
					char buffer[MAX_BUFFER_SIZE];
					int nbOctectsARecevoir = (file_size - contentReceived < MAX_BUFFER_SIZE) ? file_size - contentReceived : MAX_BUFFER_SIZE;
					rcv = recvTCP(dsCv, (char *)&buffer, nbOctectsARecevoir, &nbTotalOctetsRecus, &nbAppelRecv);

					//rcv = recv(dsCv, buffer, MAX_BUFFER_SIZE, 0); // /!\ ici appel
																// direct de recv
																// car recvTCP
																// n'est pas
																// adapté. Pourquoi ?
					if (rcv < 0){
						perror("Erreur de réception");
						close(dsCv);
						break;
					}			
					printf("Reçu : %s \n", buffer);
					printf("Serveur : j'ai reçu au total %d octets avec %d appels à recv \n\n", nbTotalOctetsRecus, nbAppelRecv);


						// si pas d'erreurs, j'ai reçu rcv octets. Je dois les écire dans le fichier.
					size_t written = fwrite(buffer, sizeof(char), nbOctectsARecevoir, file);
					if (written < nbOctectsARecevoir){
						printf("Written : %ld  NbRecev: %d", written, nbOctectsARecevoir);
						printf("Serveur : Erreur a l'ecriture du fichier ->");
						//close(dsCv);
						break; // je sors de la boucle d'écrture/réception.
					}

					contentReceived += nbOctectsARecevoir;
				}
				// fermeture du fichier à la fin de son écriture ou si erreur s'est produite.
				fclose(file);
				if (contentReceived != file_size) {
					printf("Probablement une erreur s'est produite \n") ;
					close(dsCv);
					exit(1);  //continue;
				}
				printf("Serveur : fin du dialogue avec le client, nombre total d'octets recus : %d,  recus en %d appels a recv \n\n", nbTotalOctetsRecus, nbAppelRecv);
				close(dsCv);
				//je passe au client suivant.

				exit(0);
				break;
					
			default:  // Pere
				close(dsCv);
				break;
		}
	}

	close(ds); // atteignable si on sort de la boucle infinie.
	printf("Serveur : je termine\n");
}

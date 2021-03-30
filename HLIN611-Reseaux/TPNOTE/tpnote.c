#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include<arpa/inet.h>
#include<string.h>


// ce programme est à compléter en fonction des instructions à
// recevoir depuis un processus serveur TCP distant. L'IP et le numéro de
// port du serveur sont fournis en début d'épreuve par les enseignants
// et sont à passer en paramètres de votre programme.

// Une instruction est sous forme de chaine de caractères (caractère
// de fin de chaine inclus) dont la taille (de type int) est à
// recevoir juste avant le texte de l'instruction. Donc, une
// instruction implique deux messages : un premier message qui est la
// taille (en nombre d'octets) du texte de l'instruction et un second
// message qui est le texte de l'instruction.

// Après execution d'une instruction, votre programme recoit un
// feedback avec l'instruction suivante. Là aussi, deux messages sont
// à recevoir : le premier qui est la taille (de type int) en nombre
// d'octets du second mesage qui est une chaine de caractères
// (caractère de fin inclus).

// Remarque 1 : un message de type chaine de caractères ne depassera jamais 6000 octets.


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





int main(int argc, char *argv[]) {
	if (argc != 4){
	    printf("Utilisation : %s ip_serveur port_serveur param3 \n param3 est un entier dont la signification sera fournie par une instruction. En attendant cette instruction, passer n'importe quelle valeur\n", argv[0]);
	    exit(1);
	}


	int ds = socket(AF_INET, SOCK_STREAM, 0);
	if (ds == -1)	{
		printf("Client : pb creation socket\n");
		exit(1);
	}

	struct sockaddr_in adrServ;
	adrServ.sin_family = AF_INET;
	adrServ.sin_port = htons(atoi(argv[2]));
	if (inet_pton(AF_INET, argv[1], &(adrServ.sin_addr)) < 1)	{
		perror("client: inet_pton() error ->");
		exit(1);
	}

	int conn = connect(ds, (struct sockaddr *)&adrServ, sizeof(adrServ));
	if (conn < 0)	{
		perror("Client: pb au connect :");
		close(ds);
		exit(1);
	}

	printf("Client : demande de connexion reussie \n");




	unsigned int nbTotalOctetsEnvoyes = 0;
	unsigned int nbAppelSend = 0;
	unsigned int nbTotalOctetsRecus = 0;
	unsigned int nbAppelRecv = 0;

	int name_size;
	int rcv = recvTCP(ds, (char *)&name_size, sizeof(name_size), &nbTotalOctetsRecus, &nbAppelRecv);
	if (rcv < 0){
		perror("Erreur de réception");
		close(ds);
		exit(1);
	}
	printf("Taille : %d \n", name_size);

	char *file_name = malloc(name_size);
	rcv = recvTCP(ds, (char *)file_name, name_size, &nbTotalOctetsRecus, &nbAppelRecv);
	if (rcv < 0){
		perror("Erreur de réception");
		close(ds);
		exit(1); 
	}
	printf("reçu : %s \n", file_name);


  // instruction (lire commentaire plus haut). Bien évidement, il est
  // necessaire d'afficher le message reçu pour prendre connaissance
  // des instructions à suivre pour compléter votre programme.
  

	printf("\nJe r'envoie le premier message (taille : %d) \n\n\n", name_size);
	int snd = sendTCP(ds, file_name, name_size, &nbTotalOctetsEnvoyes, &nbAppelSend);
	if (snd < 0)		{
		perror("Probleme d'emission taille");
		close(ds);
		exit(1);
	}
	free(file_name);

 

	//name_size;
	rcv = recvTCP(ds, (char *)&name_size, sizeof(name_size), &nbTotalOctetsRecus, &nbAppelRecv);
	if (rcv < 0){
		perror("Erreur de réception");
		close(ds);
		exit(1);
	}
	printf("Taille : %d \n", name_size);

	char *file_name2 = malloc(name_size);
	rcv = recvTCP(ds, (char *)file_name2, name_size, &nbTotalOctetsRecus, &nbAppelRecv);
	if (rcv < 0){
		perror("Erreur de réception");
		close(ds);
		exit(1); 
	}
	printf("reçu : %s \n", file_name2);
	free(file_name2);

	printf("\n\n\n");




	// Début de la partie serveur

	int dsS = socket(PF_INET, SOCK_STREAM, 0);
	if (dsS == -1)	{
		perror("Problème à la création de la socket: ");
		exit(1);
	}

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(atoi(argv[3]));
	printf("Port : %s  | Taille d'un short:%ld\n", argv[3], sizeof(short));

	if (bind(dsS, (struct sockaddr *)&server, sizeof(server)) < 0)	{
		perror("Serveur : erreur bind");
		close(dsS);
		exit(1);
	}
	printf("Serveur: nommage : ok\n");
	int ecoute = listen(dsS, 10);
	if (ecoute < 0)	{
		printf("Serveur : je suis sourd(e)\n");
		close(dsS);
		exit(1);
	}
	printf("Serveur: mise en écoute : ok\n");

	struct sockaddr_in adCv;
	socklen_t lgCv = sizeof(struct sockaddr_in);



	short port = atoi(argv[3]);
	printf("\n\nJ'envoie le port\n\n\n\n");
	snd = sendTCP(ds, (char *)&port, sizeof(short), &nbTotalOctetsEnvoyes, &nbAppelSend);
	if (snd < 0)		{
		perror("Probleme d'emission");
		close(ds);
		exit(1);
	}

	printf("Serveur : j'attends la demande des client (accept) \n");


	// Partie serveur
	for (int i = 0; i < 4; ++i){
		printf("\n\n\n\n\n");

		int dsCv = accept(dsS, (struct sockaddr *)&adCv, &lgCv);
		if (dsCv < 0){
			perror("Serveur, probleme accept :");
			close(dsCv);
			//close(dsS);
			continue; //exit(1);
		}
		printf("-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=- \n");
		printf("Serveur: le client %s:%d est connecté  \n\n", inet_ntoa(adCv.sin_addr), ntohs(adCv.sin_port));




		//name_size;
		rcv = recvTCP(dsCv, (char *)&name_size, sizeof(name_size), &nbTotalOctetsRecus, &nbAppelRecv);
		if (rcv < 0){
			perror("Erreur de réception");
			close(dsCv);
			//close(dsS);
			//close(ds);		
			continue; //exit(1);
		}
		printf("Taille : %d \n", name_size);

		char *file_name3 = malloc(name_size);
		rcv = recvTCP(dsCv, (char *)file_name3, name_size, &nbTotalOctetsRecus, &nbAppelRecv);
		if (rcv < 0){
			perror("Erreur de réception");
			close(dsCv);
			//close(dsS);
			//close(ds);		
			continue; //exit(1);
		}
		printf("reçu : %s \n", file_name3);
		free(file_name3);
		

		printf("\n\n\n");



		//name_size;
		rcv = recvTCP(dsCv, (char *)&name_size, sizeof(name_size), &nbTotalOctetsRecus, &nbAppelRecv);
		if (rcv < 0){
			perror("Erreur de réception");
			close(dsCv);
			//close(dsS);
			//close(ds);		
			continue; //exit(1);
		}
		printf("Taille : %d \n", name_size);

		char *file_name4 = malloc(name_size);
		rcv = recvTCP(dsCv, (char *)file_name4, name_size, &nbTotalOctetsRecus, &nbAppelRecv);
		if (rcv < 0){
			perror("Erreur de réception");
			close(dsCv);
			//close(dsS);
			//close(ds);		
			continue; //exit(1);
		}
		printf("reçu : %s\n", file_name4);





		printf("\n Je r'envoie le deuxieme message\n\n\n");
		snd = sendTCP(dsCv, file_name4, name_size, &nbTotalOctetsEnvoyes, &nbAppelSend);
		if (snd < 0)		{
			perror("Probleme d'emission taille");
			close(ds);
			exit(1);
		}
		free(file_name4);




		//name_size;
		rcv = recvTCP(dsCv, (char *)&name_size, sizeof(name_size), &nbTotalOctetsRecus, &nbAppelRecv);
		if (rcv < 0){
			perror("Erreur de réception");
			close(dsCv);
			//close(dsS);
			//close(ds);		
			continue; //exit(1);
		}
		printf("Taille : %d \n", name_size);

		char *file_name5 = malloc(name_size);
		rcv = recvTCP(dsCv, (char *)file_name5, name_size, &nbTotalOctetsRecus, &nbAppelRecv);
		if (rcv < 0){
			perror("Erreur de réception");
			close(dsCv);
			//close(dsS);
			//close(ds);		
			continue; //exit(1);
		}
		printf("reçu : %s\n", file_name5);

		free(file_name5);	




		printf("\nBien reçu, je termine le client\n");
		close(dsCv);
	}





	printf("\n-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-\n\n");

	printf("Je termine le serveur\n");
	close(dsS);
	close(ds);
}



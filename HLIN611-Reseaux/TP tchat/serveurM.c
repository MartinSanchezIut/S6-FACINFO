#include <stdio.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>


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


struct userInfo {
 char ip_adress[40];
 int ip_port;
 char user_name[40];
};



int main(int argc, char *argv[]){
	if (argc < 2){printf("utilisation: %s numero_port\n", argv[0]);	exit(1);}
	int ds = socket(PF_INET, SOCK_STREAM, 0);
	if (ds == -1){perror("Problème à la création de la socket: ");exit(1);}
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(atoi(argv[1]));
	if (bind(ds, (struct sockaddr *)&server, sizeof(server)) < 0){perror("Serveur : erreur bind");close(ds);exit(1);}
	int ecoute = listen(ds, 10);
	if (ecoute < 0)	{printf("Serveur : je suis sourd(e)\n");close(ds);exit(1);}


	// DEBUT DU MULTIPLEXAGE
	fd_set set ;
	fd_set settmp ;
	FD_ZERO(&set);
	FD_SET(ds, &set);

	int nbUser = 1;
	struct userInfo list[1000] ;

	unsigned int nbTotalOctetsRecus = 0;
	unsigned int nbAppelRecv = 0;

	int max = ds;
	while(1) {
		settmp = set;
		select(max+1, &settmp, NULL, NULL, NULL);

		for (int df = 2; df <= max; df++){
			if (!FD_ISSET(df, &settmp)) {continue;}

			if(df == ds) {
				struct sockaddr_in adCv;
				socklen_t lgCv = sizeof(struct sockaddr_in);

				int dSC = accept(ds, (struct sockaddr *)&adCv, &lgCv);
				if (dSC < 0) {perror("Accept error : ") ;continue;}
				FD_SET(dSC, &set) ;
				if (max < dSC) max = dSC;

				printf("DEBUG: %d  ->   %d \n", ds, dSC);
				printf("Serveur : le client %s:%d est connecté  (%d)\n", inet_ntoa(adCv.sin_addr), ntohs(adCv.sin_port), nbUser);
				nbUser++;
				continue;
			} 

			char buf[2048];
			buf[2048-1] = '\0';
			int taille;


			int rcv = recvTCP(df, (char *)&taille, sizeof(long), &nbTotalOctetsRecus, &nbAppelRecv);
			if (rcv < 0){perror("Erreur de réception");FD_CLR(df, &set);close(df);nbUser--;continue;}
			if (rcv == 0) {	   						   FD_CLR(df, &set);close(df);continue;}

			
			rcv = recvTCP(df, (char *)&buf, taille, &nbTotalOctetsRecus, &nbAppelRecv);
			if (rcv < 0){perror("Erreur de réception");FD_CLR(df, &set);close(df);nbUser--;continue;}
			if (rcv == 0) {	   						   FD_CLR(df, &set);close(df);continue;}
		
			buf[taille] = '\0';

			if (strncmp(buf, "/quit\n", 5) == 0) {FD_CLR(df, &set);close(df);nbUser--;continue;}
			printf("%s : %d  : %d  \n", buf, taille, strncmp(buf, "/quit", 5) > 0);		
			
		}
	}


	close(ds);
	printf("Serveur : je termine\n");
}
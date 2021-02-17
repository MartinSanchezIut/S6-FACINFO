// Code d'un client comme à la fin du cours
#include <netdb.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define SERV "127.0.0.1"
#define PORT 12345

int main() { 
  int port,sock;
  struct  sockaddr_in     serv_addr;
  struct  hostent         *serveur;

  sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sock == -1) {
    perror("Problème création socket");exit(1);
  }

  port = PORT;
  serveur = gethostbyname(SERV);
  if (serveur == NULL) { //gethostbyname renvoie NULL en cas d'erreur
    fprintf(stderr, "Problème d'adresse du serveur \"%s\"\n",SERV);exit(1);
  }

  // Initialisation de serv_addr
  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy(serveur->h_addr, &serv_addr.sin_addr.s_addr,serveur->h_length);
  serv_addr.sin_port = htons(port);

  if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
  	perror("Connexion impossible");exit(1);
  }
  // Nous sommes connectés et nous pouvons dialoguer ici avec le serveur
  char nom[1000] = {0};
  listen(sock,3);
  char mess[1000] = {0};

  while(strncmp(nom,"fin",3)!=0){
    printf("Quel est votre message ? ");
    scanf("%s", nom);
    // si on écrit un message
    if (write(sock,nom,1000)>0){ 
      //on lit le message
      read(sock,nom,1000);
      printf("Le serveur me répond %s\n", nom);
    }
  }
  close(sock);
  // Fermeture de la communication
}

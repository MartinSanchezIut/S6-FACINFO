#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <strings.h>
#include <unistd.h>
#define PORT 12345
int sock, socket2, lg;
char mess[1000];
struct sockaddr_in local; // champs d entete local
struct sockaddr_in distant; // champs d entete distant

void creer_socket()
{
    // preparation des champs d entete
    bzero(&local, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(PORT);
    local.sin_addr.s_addr = INADDR_ANY;
    bzero(&(local.sin_zero),8);
    // mise a zero de la zone adresse
    // famille d adresse internet
    // numero de port
    // types d adresses prises en charge
    // fin de remplissage
    lg = sizeof(struct sockaddr_in);
    if((sock = socket(AF_INET,SOCK_STREAM,0)) == -1){ // creation socket du serveur mode TCP/IP
        perror("Erreur socket");
        exit(1);
    }

    if((bind(sock,(struct sockaddr*)& local,sizeof(struct sockaddr)) == -1 ))// nommage de la socket
    {
        perror("Erreur bind");
        exit(1);
        close(sock);
    }
}

main(){
    // creation socket
    creer_socket();
    listen(sock,3);
    // mise a l ecoute
    char nom[1000] = {0};
    // boucle sans fin pour la gestion des connexions
    while(1) { 
        // attente connexion client
        printf ("En attente d un client\n");
        socket2 = accept(sock, (struct sockaddr*)&distant, &lg);
        printf ("client connecte \n");
        strcpy(mess,"");

        while (strncmp(mess,"fin",3)!=0){
            // si le client envoie un message
	        if((read(socket2,mess,1000)>=0)){
                printf ("le client me dit %s \n",mess);
            }  
            printf ("Quel est votre message ?\n");
            //on lit le message
            scanf("%s", mess);
            write(socket2, mess,1000);
        }

        close(socket2);
        close(sock);
        // on lui ferme la socket}
    }
}
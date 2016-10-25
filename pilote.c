#include "struct.h"

int main() {
    system("clear");

    printf("================================================");
    printf("\n            Pilote \n");
    printf("================================================");

    Requete demande, reponse;
    int sortieTube, entreeTube;
    demande.pid = getpid();

    printf("\nIdentifiant pilote : %d\n", demande.pid);
    printf("================================================");
    printf("\n");
    printf("\n -----  Envoie de la demande... -----  \n");


    // PARTIE CLIENT => SERVEUR -- initialisation de la demande
    sleep(1);
    ouvrirTubeEcriture(&entreeTube,TRANSFERT);
    strcpy(demande.type,"SYN");
    ecritureTube(entreeTube,demande);

    // PARTIE SERVEUR => CLIENT
    sleep(1);
    ouvrirTubeLecture(&sortieTube,TRANSFERT);
    lireTube(sortieTube,&reponse);

    printf("\n===============================================");
    printf("\n        Reponse du Serveur \n");
    printf("================================================");
    printf("\n %s \n", reponse.type);
    printf("================================================\n");


     // PARTIE CLIENT => SERVEUR -- cloture de la demande
    sleep(1);
    ouvrirTubeEcriture(&entreeTube,TRANSFERT);
    if(strcasecmp(reponse.type,"") == 0) strcpy(demande.type,"ACK KO");
    else strcpy(demande.type,"ACK OK");
    ecritureTube(entreeTube,demande);

    exit(EXIT_SUCCESS);
}

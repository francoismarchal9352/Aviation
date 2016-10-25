#include "struct.h"

int main(){
    system("clear");

    printf("================================================");
    printf("\n   Gestionnaire de messages ATIS \n");
    printf("================================================");
    printf("\n");
    printf("\n -----  Attente de la meteo... -----  \n");

    int i;
    int sortieTubeMeteo;
    int entreeTube, sortieTube;
    Requete demande, reponse, meteo;

    creerTube(METEO);
    creerTube(TRANSFERT);

for(i=0;i<2;i++){

    // PARTIE METEO
    sleep(1);
    ouvrirTubeLecture(&sortieTubeMeteo,METEO);
    lireTube(sortieTubeMeteo,&meteo);


    printf("\n===============================================");
    printf("\n       Donnees ATIS ( meteo )\n");
    printf("================================================");
    printf("\n %s \n", meteo.type);
    printf("================================================");
    printf("\n");

    printf("\n -----  Attente de client... -----  \n");

    // PARTIE CLIENT => SERVEUR
    sleep(1);
    ouvrirTubeLecture(&sortieTube,TRANSFERT);
    lireTube(sortieTube,&demande);

    printf("\n===============================================");
    printf("\n       Donnees recu du pilote\n");
    printf("================================================");
    printf("\nIdentifiant pilote : %d", demande.pid);
    printf("\nMessage : %s\n", demande.type);
    printf("================================================");
    // PARTIE SERVEUR => CLIENT
    sleep(1);
    ouvrirTubeEcriture(&entreeTube,TRANSFERT);
    reponse.pid = demande.pid;
    strcpy(reponse.type,meteo.type);
    ecritureTube(entreeTube,reponse);

    printf("\n -----  Envoie des donnees au pilote... -----  \n");

    // PARTIE CLIENT => SERVEUR
    sleep(1);
    ouvrirTubeLecture(&sortieTube,TRANSFERT);
    lireTube(sortieTube,&demande);

    printf("\n==============================================");
    printf("\n        Reponse du pilote \n");
    printf("================================================");
    printf("\nIdentifiant pilote : %d", demande.pid);
    printf("\nMessage : %s\n", demande.type);
    printf("================================================");

    i--;
}
    unlink(TRANSFERT);
    exit(EXIT_SUCCESS);
}

#include "struct.h"

int main(){
    system("clear");

    printf("================================================");
    printf("\n   Gestionnaire Meteo \n");
    printf("================================================");
    printf("\n");

    char ATIS[TAILLE_MESSAGE][10];
    int i, nombreInfo;
    int entreeTubeMeteo;
    Requete meteo;

    strcpy(ATIS[0],"EBBR 0615 20015KT 8000 RA SCT010 OVC015 TEMPO 0608 5000 RA BKN005 BECMG 0810 9999 NSW BKN025");
    strcpy(ATIS[1],"EBBR 0712 15020KT 6200 FG SCT010 OVC015 TEMPO 1450 6000 RA BKN005 BECMG 0810 5000 NSW BKN025");
    strcpy(ATIS[2],"EBBR 0620 20015KT 8000 SA SCT010 OVC015 TEMPO 0780 4000 RA BKN005 BECMG 0810 4000 NSW BKN025");
    strcpy(ATIS[3],"EBBR 0607 20015KT 8000 RA SCT010 OVC015 TEMPO 0608 3000 RA BKN005 BECMG 0810 9999 NSW BKN025");

    nombreInfo = 4;


    for(i=0;i<nombreInfo;i++){
        strcpy(meteo.type,ATIS[i]);

        printf("\n===============================================");
        printf("\n          Message Actuel\n");
        printf("================================================");
        printf("\n %s \n", meteo.type);

        ouvrirTubeEcriture(&entreeTubeMeteo,METEO);
        ecritureTube(entreeTubeMeteo,meteo);
        if(i == nombreInfo - 1) i = -1;
        sleep(5);
    }

    unlink(METEO);
    exit(EXIT_SUCCESS);
}

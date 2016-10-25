#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <fcntl.h>
#include <time.h>

#define TAILLE_MESSAGE	256
#define METEO "meteo.fifo"
#define TRANSFERT "tranfert.fifo"

typedef struct{
    int pid;
    char type[TAILLE_MESSAGE];
} Requete;

void creerTube(char *nom){
    unlink(nom);
    int tube;
    tube = mkfifo(nom, 0666);
    if(tube < 0){
        if(tube == -1){
            printf("\nTube existant => reinitialisation.\n");
            unlink(nom);
            mkfifo(nom, 0666);
        } else {
            printf("\nImpossible de creer le tube.\n");
            printf("\nCode erreur : %d\n", tube);
            exit(EXIT_FAILURE);
        }
    }
}

void ouvrirTubeLecture(int *sortieTube, char *nom){
    *sortieTube = open(nom, O_RDONLY);
    if(*sortieTube == -1) {
		printf("\nImpossible d'ouvrir la sortie du tube.\n");
		exit(EXIT_FAILURE);
	}
}

void ouvrirTubeEcriture(int *entreeTube, char *nom){
    *entreeTube = open(nom, O_WRONLY);
    if(*entreeTube == -1) {
		printf("\nOuverture Impossible de l entree du tube.\n");
		exit(EXIT_FAILURE);
	}
}

void lireTube(int sortieTube, Requete *message){
    int lectureTube;
    lectureTube = read(sortieTube, message, TAILLE_MESSAGE);
	close(sortieTube);
    if(lectureTube < 0) {
        printf("\nImpossible de lire sur la sortie du tube.\n");
	}
}

void ecritureTube(int entreeTube, Requete message){
    int ecritureTube;
    ecritureTube = write(entreeTube, &message, TAILLE_MESSAGE);
	close(entreeTube);
	if(ecritureTube < 0) {
		printf("\nEcriture Impossible de l entree du tube.\n");
	}
}

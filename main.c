#include<stdlib.h>
#include"util.h"


int main(void){
    srand(time(NULL));
    FILE* fichier = fopen("plan.pln","r");
    salle_t** tab = malloc(26 * sizeof(salle_t*));
    construire_lab(tab,fichier);
    salle_t* salle_actu = tab[0];

    inventaire_t* inventaire = malloc(sizeof *inventaire);
    inventaire->liste_objets = NULL;

    int end_game = 0;
    int cle1 = intro();
    if (cle1 == 1){
        prendre_objet(inventaire,all_objet("key R"));
    }

    while(end_game != 1){
        salle_actu = config_salle(salle_actu,inventaire);

    }
    return 0;
}



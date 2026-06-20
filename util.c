#include"util.h"

salle_t* all_salle(int n, salle_t* N, salle_t* S, salle_t* E, salle_t* O){
    salle_t* res = malloc(sizeof *res);
    res->n = n;
    res->N = N;
    res->S = S;
    res->E = E;
    res->O = O;
    res->liste_objets = NULL;
    return res;
}

objet_t* all_objet(char* nom_obj){
    objet_t* res = malloc(sizeof *res);
    res->nom = strdup(nom_obj);
    res->suivant = NULL;
    return res;
}

void ajouter_objet_salle(salle_t* s, objet_t* o){
    if (s->liste_objets == NULL) s->liste_objets = o;
    else{
        objet_t* actu = s->liste_objets;
        while (actu->suivant != NULL) actu = actu->suivant;
        actu->suivant = o;
        // on ajoute l'objet a la fin de la liste.
    }

}

void show_objet(salle_t* s){
    objet_t* actu = s->liste_objets;
    while (actu != NULL){
        print_slow("- ");
        print_slow(actu->nom);
        print_slow("\n");
        actu = actu->suivant;
    }
}

void show_inventaire(inventaire_t* i){
    objet_t* actu = i->liste_objets;
    while (actu != NULL){
        print_slow("- ");
        print_slow(actu->nom);
        print_slow("\n");
        actu = actu->suivant;
    }
}

int contient_objet_salle(salle_t* s, char* nom_obj){
    objet_t* actu = s->liste_objets;
    while (actu != NULL){
        if (strcmp(actu->nom,nom_obj) == 0){
            return 1;
        }
        actu = actu->suivant;
    }
    return 0;

}

void supprimer_objet_salle(salle_t* s, char* nom_obj){
    if (s->liste_objets == NULL) return;
    if (strcmp(s->liste_objets->nom, nom_obj) == 0) {
            objet_t* a_supprimer = s->liste_objets;
            s->liste_objets = s->liste_objets->suivant;
            free(a_supprimer->nom);
            free(a_supprimer);
            return;
        }
    objet_t* actu = s->liste_objets;
    while (actu->suivant != NULL){
        if (strcmp(actu->suivant->nom,nom_obj) == 0){
            objet_t* a_supprimer = actu->suivant;
            actu->suivant = actu->suivant->suivant;
            free(a_supprimer->nom);
            free(a_supprimer);
            return;
        }
        actu = actu->suivant;
    }
}

void prendre_objet(inventaire_t* inventaire, objet_t* o){
    if (inventaire->liste_objets == NULL) inventaire->liste_objets = o;
    else{
        objet_t* actu = inventaire->liste_objets;
        while (actu->suivant != NULL) actu = actu->suivant;
        actu->suivant = o;
        // on ajoute l'objet a la fin de la liste.
    }
}

int possede_objet(inventaire_t* inventaire, char* nom_obj){
    objet_t* actu = inventaire->liste_objets;
    while (actu != NULL){
        if (strcmp(actu->nom,nom_obj) == 0){
            return 1;
        }
        actu = actu->suivant;
    }
    return 0;

}

void print_slow(const char *txt){
    for (int i=0; txt[i] != '\0'; i++){
        printf("%c", txt[i]);
        fflush(stdout);
        usleep(50000);
    }
}

int intro(void){
    int choix1 = 0;
    print_slow("Vous arrivez à l'entrée de ce fameux château d'Azatoth, un passant vous demande :\n- Mais... que faites vous ici ?\n");
    print_slow("\n");
    print_slow(" 1. Je suis passé par hasard, je continue ma promenade ! \n 2. J'ai décidé d'affronter Azatoth.\n");
    do {
        print_slow("Choisissez : ");
        scanf("%d",&choix1);
    } while (choix1 < 1 || choix1 > 2);

    if (choix1 == 1){
        print_slow("- D'accord, méfiez-vous la prochaine fois, bonne journée !\n");
        exit(1);
    }
    else if (choix1 == 2){
        int choix2 = 0;
        print_slow("- Q..quoi ?? vous êtes malade ! Savez-vous ce qui vous attends à l'interieur ? Personne n'a réussi à s'en sortir vivant !\n");
        print_slow("\n");
        print_slow(" 1. Je suis venu rendre l'âme à tous ces pauvres victimes. Il faut que ça cesse !\n 2. I don't care, je suis l'homme le plus intelligent et le plus fort au monde ! MOUAHAHA !!\n");
        do {
            print_slow("Choisissez : ");
            scanf("%d",&choix2);
        } while (choix2 < 1 || choix2 > 2);
        if (choix2 == 1){
            print_slow("- Je vois que vous êtes extrêmement motivé et courageux. Dans ce cas, je vous apporte tout mon soutien. A vrai dire, je travaillais ici auparavant, j'ai gardé précieusement une clé qui pourrait vous être utile. Tenez. Parvenez à le retrouver et l'arrêter ;) Bon courage !\n");
            print_slow("\nSur la clé est gravé la lettre \"R\". Vous la rangez dans votre poche, puis entrez au sein du chateau.\n");
            return 1;
        }
        else if(choix2 == 2){
            print_slow("- Vous allez le regretter !\n");
            print_slow("\nVous entrez au sein du chateau.\n");
            return 0;
        }
    }
    return 0;

}

void construire_lab(salle_t** tab, FILE* f){
    char buffer[1000];
    int s1,s2;
    char d1,d2;
    fscanf(f,"%s",buffer);
    while (fscanf(f,"%s %d.%c-%d.%c;",buffer,&s1,&d1,&s2,&d2) == 5){
        if (tab[s1] == NULL){
            tab[s1] = all_salle(s1,NULL,NULL,NULL,NULL);
        }
        if (tab[s2] == NULL){
            tab[s2] = all_salle(s2,NULL,NULL,NULL,NULL);
        }
        if (d1=='N') tab[s1]->N = tab[s2];
        else if (d1=='S') tab[s1]->S = tab[s2];
        else if (d1=='E') tab[s1]->E = tab[s2];
        else if (d1=='O') tab[s1]->O = tab[s2];
        if (d2=='N') tab[s2]->N = tab[s1];
        else if (d2=='S') tab[s2]->S = tab[s1];
        else if (d2=='E') tab[s2]->E = tab[s1];
        else if (d2=='O') tab[s2]->O = tab[s1];
    }
    fscanf(f,"%s",buffer);
    while (fscanf(f,"%d:%[^;];",&s1,buffer) == 2){
        objet_t* o1 = all_objet(buffer);
        ajouter_objet_salle(tab[s1],o1);
    }
}



void deplacer_azatoth(salle_t* s){
    salle_t* voisins[4];
    int nb = 0;
    if (s->N){
        voisins[nb] = s->N;
        nb++;
    }
    if (s->S){
        voisins[nb] = s->S;
        nb++;
    }
    if (s->E){
        voisins[nb] = s->E;
        nb++;
    }
    if (s->O){
        voisins[nb] = s->O;
        nb++;
    }
    if (nb > 0){
        int r = rand() % nb;
        ajouter_objet_salle(voisins[r], all_objet("Azatoth"));
        supprimer_objet_salle(s,"Azatoth");
        print_slow("\n*** Azatoth s'enfuit vers une autre salle ! ***\n\n");
    }
}




salle_t* config_salle(salle_t* salle_actu, inventaire_t* inventaire){
    int choix = 0;
    int cpt = 0;
    salle_t* d[5];
    int id_cle = -1;
    int id_azatoth = -1;
    int id_coffre_locked = -1;
    int id_coffre_unlocked = -1;
    int id_inv = -1;

    printf("╪══════════════════════════╪\n");
    print_slow("Vous entrez dans une pièce.\n");

    if (salle_actu->liste_objets != NULL || salle_actu->N != NULL || salle_actu->S != NULL || salle_actu->E != NULL || salle_actu->O != NULL){
        print_slow("Il y a :\n");
        show_objet(salle_actu);
        if (salle_actu->N != NULL) print_slow("- Une porte devant\n");
        if (salle_actu->S != NULL) print_slow("- Une porte derrière\n");
        if (salle_actu->E != NULL) print_slow("- Une porte à droite\n");
        if (salle_actu->O != NULL) print_slow("- Une porte à gauche\n");
    }
    else print_slow("Il n'y a rien ici.\n");

    print_slow("\nVous pouvez :\n");
    if (salle_actu->N != NULL){
        cpt++;
        printf(" %d",cpt);
        print_slow(". Aller tout droit\n");
        d[cpt] = salle_actu->N;
    }
    if (salle_actu->S != NULL){
        cpt++;
        printf(" %d",cpt);
        print_slow(". Aller derrière\n");
        d[cpt] = salle_actu->S;
    }
    if (salle_actu->E != NULL){
        cpt++;
        printf(" %d",cpt);
        print_slow(". Aller à droite\n");
        d[cpt] = salle_actu->E;
    }
    if (salle_actu->O != NULL){
        cpt++;
        printf(" %d",cpt);
        print_slow(". Aller à gauche\n");
        d[cpt] = salle_actu->O;
    }

    //presence d'une clé
    if (contient_objet_salle(salle_actu,"Une clé")){
        cpt++;
        printf(" %d",cpt);
        print_slow(". Prendre la clé\n");
        id_cle = cpt;
    }

    //presence de coffre verouillé
    if (contient_objet_salle(salle_actu,"Un grand coffre noir vérouillé")){
        cpt++;
        printf(" %d",cpt);
        print_slow(". Ouvrir le coffre\n");
        id_coffre_locked = cpt;
    }

    //presence coffre ouvert
    if (contient_objet_salle(salle_actu,"Un coffre ouvert avec une épée à l'intérieur")){
        cpt++;
        printf(" %d",cpt);
        print_slow(". Prendre l'épée du coffre\n");
        id_coffre_unlocked = cpt;
    }
    
    //presence Azatoth
    if (contient_objet_salle(salle_actu,"Azatoth")){
        cpt++;
        printf(" %d",cpt);
        print_slow(". Tuer Azatoth\n");
        id_azatoth = cpt;
    }

    //option pour voir inventaire
    cpt++;
    printf(" %d",cpt);
    print_slow(". Voir mon inventaire\n");
    id_inv = cpt;

    //choix joueur
    do {
        print_slow("Choisissez : ");
        scanf("%d",&choix);
    } while (choix < 1 || choix > cpt);

    //tuer Azatoth
    if (id_azatoth != -1 && choix == id_azatoth){
        if (possede_objet(inventaire,"Une épée")){
            print_slow("Vous avez tué Azatoth !\n");
            exit(1);
        }
        else{
            print_slow("Vous ne pouvez pas tuer Azatoth.\n");
            if (contient_objet_salle(salle_actu,"Azatoth")) deplacer_azatoth(salle_actu);
            return salle_actu;
        }
    }
    //prendre l'épée
    if (id_coffre_unlocked != -1 && choix == id_coffre_unlocked){
        print_slow("Vous avez pris l'épée.\n");
        supprimer_objet_salle(salle_actu,"Un coffre ouvert avec une épée à l'intérieur");
        ajouter_objet_salle(salle_actu,all_objet("Un coffre vide"));
        prendre_objet(inventaire,all_objet("Une épée"));
        if (contient_objet_salle(salle_actu,"Azatoth")) deplacer_azatoth(salle_actu);
        return salle_actu;
    }

    //prendre une clé
    if (id_cle != -1 && choix == id_cle){
        print_slow("Vous avez pris la clé.\n");
        supprimer_objet_salle(salle_actu,"Une clé");
        if (possede_objet(inventaire,"key R") == 0){
            prendre_objet(inventaire,all_objet("key R"));
            print_slow("La lettre \"R\" est gravée dessus.\n");
        }
        else if (possede_objet(inventaire,"key G") == 0){
            prendre_objet(inventaire,all_objet("key G"));
            print_slow("La lettre \"G\" est gravée dessus.\n");
        }
        else{
            prendre_objet(inventaire,all_objet("key B"));
            print_slow("La lettre \"B\" est gravée dessus.\n");
        }
        if (contient_objet_salle(salle_actu,"Azatoth")) deplacer_azatoth(salle_actu);
        return salle_actu;
    }

    //ouvrir le coffre
    if (id_coffre_locked != -1 && choix == id_coffre_locked){
        if (possede_objet(inventaire,"key R") && possede_objet(inventaire,"key G") && possede_objet(inventaire,"key B")){
            supprimer_objet_salle(salle_actu,"Un grand coffre noir vérouillé");
            print_slow("Le coffre est ouvert. Une épée se trouve à l'intérieur.\n");
            ajouter_objet_salle(salle_actu,all_objet("Un coffre ouvert avec une épée à l'intérieur"));
            if (contient_objet_salle(salle_actu,"Azatoth")) deplacer_azatoth(salle_actu);
            return salle_actu;
        }
        else{
            print_slow("Il vous manque des clés pour ouvrir ce coffre.\n");
            if (contient_objet_salle(salle_actu,"Azatoth")) deplacer_azatoth(salle_actu);
            return salle_actu;
        }
    }

    //voir inventaire
    if (id_inv != -1 && choix == id_inv){
        print_slow("Vous avez :\n");
        show_inventaire(inventaire);
        if (contient_objet_salle(salle_actu,"Azatoth")) deplacer_azatoth(salle_actu);
        return salle_actu;
    }

    //deplacer azatoth si present
    if (contient_objet_salle(salle_actu,"Azatoth")){
        deplacer_azatoth(salle_actu);
    }
    return d[choix];
}
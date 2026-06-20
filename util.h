#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>

#ifndef UTIL_H
#define UTIL_H


typedef struct s_objet_t{
    char* nom;
    struct s_objet_t* suivant;
} objet_t;

typedef struct s_salle_t{
    int n;
    struct s_salle_t* N;
    struct s_salle_t* S;
    struct s_salle_t* E;
    struct s_salle_t* O;
    objet_t* liste_objets;
    
} salle_t;


typedef struct s_inventaire_t{
    objet_t* liste_objets;
} inventaire_t;



salle_t* all_salle(int n, salle_t* N, salle_t* S, salle_t* E, salle_t* O);
objet_t* all_objet(char* nom_obj);
void ajouter_objet_salle(salle_t* s, objet_t* o);
void show_objet(salle_t* s);
void show_inventaire(inventaire_t* i);
int contient_objet_salle(salle_t* s, char* nom_obj);
void supprimer_objet_salle(salle_t* s, char* nom_obj);
void prendre_objet(inventaire_t* inventaire, objet_t* o);
int possede_objet(inventaire_t* inventaire, char* nom_obj);
void print_slow(const char *txt);
int intro(void);
void construire_lab(salle_t** tab, FILE* f);
void deplacer_azatoth(salle_t* s);
salle_t* config_salle(salle_t* salle_actu, inventaire_t* inventaire);

#endif
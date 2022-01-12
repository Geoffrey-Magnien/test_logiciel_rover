#ifndef LOGICIEL_H
#define LOGICIEL_H
#include <stdbool.h>

typedef struct Capteur_telemetrique{
    bool capt_devant;
    bool capt_derriere;
    bool capt_gauche;
    bool capt_droite;
    bool capt_toit;
}capteur_t;

capteur_t telemetrique;

typedef struct capteur_pression{
    int valeur;
}capteur_p;

capteur_p pression;

typedef struct capteur_temperature{
    int valeur;
}capteur_temp;

capteur_temp temperature;

typedef struct quantite_batterie{
    int valeur;
}batterie_q;

batterie_q batterie;

typedef struct btn_emergency{
    bool valeur;
}emergency_b;

emergency_b bouton;

typedef struct moteur_roues{
    int roues_dg;
    int roues_dd;
    int roues_mg;
    int roues_md;
    int roues_ag;
    int roues_ad;
}moteur_r;

moteur_r moteur;

typedef struct frequence_echantillonage{
    int valeur;
}freq_e;

freq_e freq;

typedef struct incident_apparu{
    int nombre;
}incident_t;

typedef struct site_web{
    float vitesse;
    int pourcentage;
    incident_t incidents;
}site_w;

site_w site;

int compteur;

bool rover_base;

void depart(bool capteur_tele, int capteur_press, int capteur_temperature);
bool avance();
void gestion_deplacement();
void gestion_echantillonage();
void retour_base();
void gestion_site_web();
void fonctionnement();

void sleep(int secondes);

#endif
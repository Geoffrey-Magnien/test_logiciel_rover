#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

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

void depart(bool capteur_tele, int capteur_press, int capteur_temperature){
    moteur.roues_ad = 1;
    moteur.roues_ag = 1;
    moteur.roues_dd = 1;
    moteur.roues_dg = 1;
    moteur.roues_md = 1;
    moteur.roues_mg = 1;
    rover_base = false;
    freq.valeur = 100;
    site.incidents.nombre = 0;

    temperature.valeur = capteur_temperature;
    pression.valeur = capteur_tele;
    telemetrique.capt_devant = capteur_tele ;
    

}

bool avance(){
    if (moteur.roues_ad == moteur.roues_ag && moteur.roues_md == moteur.roues_ag && moteur.roues_dd == moteur.roues_dg){
        return true; //avance
    }   
    return false;
    
}

void gestion_deplacement(){
    if (telemetrique.capt_devant || avance()){
        if( (float) (rand()/RAND_MAX) > 0.5 ){
            moteur.roues_ad = 1;
            moteur.roues_ag = -1;
            moteur.roues_dd = 1;
            moteur.roues_dg = -1;
            moteur.roues_md = 1;
            moteur.roues_mg = -1;

            sleep(5);

            moteur.roues_ad = 1;
            moteur.roues_ag = 1;
            moteur.roues_dd = 1;
            moteur.roues_dg = 1;
            moteur.roues_md = 1;
            moteur.roues_mg = 1;
        }
        else{
             moteur.roues_ad = -1;
            moteur.roues_ag = 1;
            moteur.roues_dd = -1;
            moteur.roues_dg = 1;
            moteur.roues_md = -1;
            moteur.roues_mg = 1;

            sleep(5);

            moteur.roues_ad = 1;
            moteur.roues_ag = 1;
            moteur.roues_dd = 1;
            moteur.roues_dg = 1;
            moteur.roues_md = 1;
            moteur.roues_mg = 1;
        }
    }   
}

void gestion_echantillonage(){
        if(temperature.valeur > 32 && pression.valeur > 1025 && freq.valeur == 100 ){
            freq.valeur -= 40;
        } 
        else if(temperature.valeur > 32 && pression.valeur < 1025 && freq.valeur == 100 ){
            freq.valeur -= 20;
        } 
        else if(temperature.valeur < 10 && pression.valeur > 1025 && freq.valeur == 100){
            freq.valeur = 100;
        }   
        else if( temperature.valeur < 10 && pression.valeur < 1025 && freq.valeur == 100){
            freq.valeur += 20;
        }    
        else if( temperature.valeur >= 10 && temperature.valeur <= 32  && pression.valeur < 1025 && freq.valeur == 100){
            freq.valeur = 100;
        }         
        else if( temperature.valeur >= 10 && temperature.valeur <= 32  && pression.valeur > 1025){
            freq.valeur += 20;
        }  
}


void retour_base(){
    if(bouton.valeur || batterie.valeur < 55 ){
        printf("le vehicule retourne a la base\n");
        rover_base = true;
    }
}


void gestion_site_web(){
    site.vitesse = (moteur.roues_ad + moteur.roues_ag ) / 2;
    site.pourcentage = compteur;
    if (moteur.roues_ad == 0 && moteur.roues_ag == 0)
    {
         site.incidents.nombre += 1;
    }
}

int test_rover() {
    // MES TESTS ROVER

    if (telemetrique.capt_devant == 1){
        assert(moteur.roues_ad == -1 || moteur.roues_ag == -1);
    }
    if(pression.valeur > 1025 && temperature.valeur > 32){
        assert(freq.valeur == 60);
    } 
    else if(pression.valeur < 1025 && temperature.valeur > 32){
        assert(freq.valeur == 80);
    } 
    else if(pression.valeur > 1025 && temperature.valeur < 10){
        assert(freq.valeur == 100);
    }
    else if(pression.valeur < 1025 && temperature.valeur < 10){
        assert(freq.valeur == 120);
    }    
    else if(pression.valeur < 1025 && temperature.valeur >= 10 && temperature.valeur <= 32 ){
        assert(freq.valeur == 100);
    }         
    else if(pression.valeur > 1025 && temperature.valeur >= 10 && temperature.valeur <= 32){
        assert(freq.valeur == 120);
    }
    if(bouton.valeur){
        assert(rover_base = true);
    }
    if(batterie.valeur < 55){
        assert(rover_base = true);
    }
    assert(site.vitesse < 2);
    assert(site.pourcentage == compteur);
    printf( "Le programme peut se poursuivre normalement" );

    return 0;
}

void fonctionnement(){
    while (20){
        batterie.valeur -= 2;
        compteur += 4;
        gestion_deplacement();
        gestion_echantillonage();
        retour_base();
        gestion_site_web();
    }
}

int main(){
    depart(false,1015,20);
    foncionement();
    depart(false,1030,20);
    foncionement();
    depart(true,1015,20);
    foncionement();
    depart(false,1015,33);
    foncionement();
    depart(false,1015,9);
    foncionement();
    depart(false,1035,9);
    foncionement();
    depart(true,1035,33);
    foncionement();
    depart(true,1015,9);
    foncionement();
    depart(true,1035,9);
    foncionement();
    depart(true,1035,33);
    foncionement();
    return 0;
}

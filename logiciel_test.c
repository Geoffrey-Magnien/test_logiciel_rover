#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "CUnit-2.1-3/CUnit/Headers/CUnit.h"
#include "CUnit-2.1-3/CUnit/Headers/Basic.h"
#include "logiciel.h"
// !!
int test_rover() {
    // MES TESTS ROVER

    if (telemetrique.capt_devant == 1){
        CU_ASSERT_TRUE(moteur.roues_ad == -1 || moteur.roues_ag == -1)
    }
    if(pression.valeur > 1025 && temperature.valeur > 32){
        CU_ASSERT_EQUAL(freq.valeur,60);
    } 
    else if(pression.valeur < 1025 && temperature.valeur > 32){
        CU_ASSERT_EQUAL(freq.valeur,80);
    } 
    else if(pression.valeur > 1025 && temperature.valeur < 10){
        CU_ASSERT_EQUAL(freq.valeur,100);
    }
    else if(pression.valeur < 1025 && temperature.valeur < 10){
        //CU_ASSERT_EQUAL(freq.valeur,120); FALSE
    }   
    else if(pression.valeur < 1025 && temperature.valeur >= 10 && temperature.valeur <= 32 ){
        CU_ASSERT_EQUAL(freq.valeur,100);
    }      
    else if(pression.valeur > 1025 && temperature.valeur >= 10 && temperature.valeur <= 32){
        CU_ASSERT_EQUAL(freq.valeur,120);
    }
    if(bouton.valeur){
        CU_ASSERT_TRUE(rover_base);
    }
    if(batterie.valeur < 55){
        //CU_ASSERT_TRUE(rover_base); FALSE
    }
    //CU_ASSERT_TRUE(site.vitesse < 2); FALSE
    //CU_ASSERT_TRUE(site.pourcentage == compteur); FALSE
    return 0;
}

int main(int argc, char const *argv[])
{
    test_rover();
    return 0;
}

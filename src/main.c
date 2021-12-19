// Librairies Projet
#include <genesis.h>
#include <dma.h>
#include <main.h>
#include <init.h>
#include <variables.h>
#include <palettes.h>
#include <routines.h>
#include <GestionPAD.h>
#include <sprites_JEU.h>

// Procédure principale

int main(u16 hardreset)
{

    if (!hardreset) SYS_hardReset();

	// Init HW
	InitSystem();

    // Ecran Titre
    StartMain();

    return 0;
}


void StartMain()
{
    // Init Ecran Titre
    InitTitre();

    // Init Ecran sélection
    InitSelection();

    // Init Niveaux
    InitNiveaux();

    // Boucle du jeu
    MainLoop();

    return;  
}

void MainLoop()
{
    switch (num_Niveau)
    {
        case 1:
        while(TRUE)
        {
            // Manette
            Pause_Jeu();



            // Jeu en Pause ?
            if(PauseJeu==0)
            {
                //Phases_Joueur();
                //collision_Decor(Joueur);

                updateScrolling_Niveau1();

                creaEnnemis_Niveau1();
                mvtEnnemis_Niveau1();
            }



            // MAJ sprites
            SPR_update();

            // MAJ tiles BG
            updateTiles_Niveau1();

            // Vblank
            SYS_doVBlankProcess();

        }
        
        break;


    }

    //updateCamera();
    //SYS_doVBlankProcess();
}
// Librairies Projet
#include <genesis.h>
#include <dma.h>
#include <main.h>
#include "init.h"
#include "variables.h"
#include "palettes.h"
#include "routines.h"
#include "sprites_JEU.h"
#include "musique.h"

void joyEventCallback(u16 joy, u16 changed, u16 state)
{
    SpriteJoueur_ *ptrJoueur=&Joueur;
    SpriteDragon_ *ptrDragon=&Dragon;
    SpriteAura_ *ptrAura=&Aura;

    // START //
    if (changed & state & BUTTON_START)
    {
        // Mettre en mode Pause //
        if (PauseJeu==0)
        {
            PauseJeu=1;
            StatutJoy=0;

            SPR_setPosition(sprite_Pause[0], 140, 116);
            SPR_setPosition(sprite_Pause[1], 172, 116);

            XGM_pausePlay(Niveau1_Remix);

        }
        // Sortir du mode Pause //
        else if (PauseJeu==1)
        {
            PauseJeu=0;
            StatutJoy=0;

            SPR_setPosition(sprite_Pause[0], -40, 0);
            SPR_setPosition(sprite_Pause[1], -32, 0);

           XGM_resumePlay(Niveau1_Remix);
        }
    }

    // can't do more in paused state
    if (PauseJeu==1) return;



    // SAUT //
    if (changed & state & BUTTON_C)
    {
        if(ptrJoueur->Phase==ARRET || ptrJoueur->Phase==MARCHE)
        {
            ptrJoueur->Phase=SAUT;
        }

        // LARGAGE APRES RÉAPPARITION //
        else if(ptrJoueur->Phase==APPARITION)
        {
            if(ptrJoueur->CompteurApparition>55 && ptrJoueur->CompteurApparition<255)
            {
                ptrDragon->Phase=SORTIE_DRAGON;

                ptrJoueur->Phase=CHUTE;
                ptrJoueur->CompteurApparition=0;
                ptrJoueur->Invincible=1;

                // REINIT BARRE D'ENERGIE //
                Energie=ENERGIE_DEPART;
                CompteurEnergie=0;
                Init_BarreEnergie();
            }
        }
    }

    // TIR //
    if (changed & state & BUTTON_B)
    {
        // SI LE JOUEUR SAUTE //
        if(ptrJoueur->Phase==SAUT)
        {
            // SAUT + TIR
            ptrJoueur->Phase=SAUT_TIR;

            // L'AURA SE DECLENCHE
            if(ptrAura->Init==0)
            {
                ptrAura->Init=1;
            }
        }

        // SI JOUEUR ARRET OU MARCHE //
        else if(ptrJoueur->Phase==ARRET || ptrJoueur->Phase==MARCHE)
        {
            // MARCHE + TIR
            ptrJoueur->Phase=TIR;

            // L'AURA SE DECLENCHE
            if(ptrAura->Init==0)
            {
                ptrAura->Init=1;
            }
        }
    }

}

// Procédure principale //
int main(u16 hardreset)
{

    if (!hardreset) SYS_hardReset();

	// Init HW
	InitSystem();

    // Ecran Titre
    StartMain();

    return 0;
}

// Titre + Selection joueur //
void StartMain()
{
    // Init Ecran Titre
    InitTitre();

    // Init Ecran sélection
    InitSelection();

    // Init Niveaux
    //InitNiveaux();

    // Boucle du jeu
    MainLoop();

    return;  
}

// Boucle Niveaux //
void MainLoop()
{
    InitNiveaux();
    
    //SYS_showFrameLoad(TRUE);

    // Manette
    JOY_setEventHandler(joyEventCallback);
    
    switch (num_Niveau)
    {
        case 1:

        XGM_startPlay(Niveau1_Remix);

        while(TRUE)
        {

            // Jeu en Pause ?
            if(PauseJeu==0)
            {
                Phases_Joueur();

                Scrolling_Niveau1();

                CreaSprites_Niveau1();
                MvtSprites_Niveau1();

                MvtJoueur();
                TilesJoueur();

                //Maj_CompteurEnergie();
                //Maj_BarreEnergie(CompteurEnergie, Energie);

            }

            // MAJ sprites
            SPR_update();

            // MAJ tiles BG
            Tiles_Niveau1();

            //u16 décalage;


            // DEBUG
            //VDP_drawInt( ID_Plateforme , 1 , 12 , 6);

            // Vblank
            SYS_doVBlankProcess();

            // CHANGEMENT DES PALETTES
            ChgtPalette_Niveau1();
        }       
        //break;
    }
}
// Librairies Projet
#include <genesis.h>
#include <dma.h>
#include <main.h>
#include <init.h>
#include <variables.h>
#include <palettes.h>
#include <routines.h>
#include <sprites_JEU.h>

void joyEventCallback(u16 joy, u16 changed, u16 state)
{
    SpriteJoueur_ *ptrJoueur=&Joueur;

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

            //break;
        }
        // Sortir du mode Pause //
        else if (PauseJeu==1)
        {
            PauseJeu=0;
            StatutJoy=0;

            SPR_setPosition(sprite_Pause[0], -40, 0);
            SPR_setPosition(sprite_Pause[1], -32, 0);
        }
    }

    // can't do more in paused state
    if (PauseJeu==1) return;

    // SAUT //
    if (changed & state & BUTTON_C)
    {
        if(ptrJoueur->Phase==0 || ptrJoueur->Phase==1)
        {
            ptrJoueur->Phase=2;
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
    
    SYS_showFrameLoad(TRUE);

    // Manette
    JOY_setEventHandler(joyEventCallback);
    
    switch (num_Niveau)
    {
        case 1:
        while(TRUE)
        {

            //u16 value=JOY_readJoypad(JOY_1);

            // Jeu en Pause ?
            if(PauseJeu==0)
            {
                Phases_Joueur();

                Scrolling_Niveau1();

                CreaSprites_Niveau1();
                MvtSprites_Niveau1();

                MvtJoueur();
                TilesJoueur();

            }


            // MAJ sprites
            SPR_update();

            // MAJ tiles BG
            Tiles_Niveau1();

            // DEBUG
            //VDP_drawInt( Plateforme[0].pt_Coll1_X ,  3 , 12 , 8);
            //VDP_drawInt( contactPlt_OK ,  3 , 17 , 8);

            //VDP_drawInt( Joueur.pt_Coll1_X+64 ,  3 , 22 , 6);

            // Vblank
            SYS_doVBlankProcess();

            // CHANGEMENT DES PALETTES
            ChgtPalette_Niveau1();

        }
        
        break;


    }

    //updateCamera();
    //SYS_doVBlankProcess();
}
// Librairies Projet
#include <genesis.h>
#include <main.h>
#include <init.h>
#include <variables.h>
#include <palettes.h>
#include <routines.h>
#include <sprites_JEU.h>

///////////////////////////////
//         GESTION PAD       //
///////////////////////////////

void Pause_Jeu()
{
    // Déclaration manette
    u16 value=JOY_readJoypad(JOY_1);

    // Désactivation auto-fire
    if (!value) StatutJoy++;
    if (StatutJoy>4) StatutJoy=4;

    if (StatutJoy>2)
    {
        // Mettre en mode Pause
        if (value & BUTTON_START && PauseJeu==0)
        {
            PauseJeu=1;
            StatutJoy=0;

            SPR_setPosition(sprite_Pause[0], 140, 116);
            SPR_setPosition(sprite_Pause[1], 172, 116);

            return;
        }

        // Sortir du mode Pause
        if (value & BUTTON_START && PauseJeu==1)
        {
            PauseJeu=0;
            StatutJoy=0;

            SPR_setPosition(sprite_Pause[0], -40, 0);
            SPR_setPosition(sprite_Pause[1], -32, 0);

            return;
        }
    }


    // Si en mode Pause, on n'exécute pas le reste
    if(PauseJeu) return;

}



void Phases_Joueur()
{
    // Gestion manette
	u16 value=JOY_readJoypad(JOY_1);

    ///////////////
    //   ARRET   //
    /////////////// 
    if(value==0)
    {
        // Si le joueur ne tombe pas
        if(ptrJoueur->Phase!=2)
        {
            ptrJoueur->Phase=0;
        }
        return;
    }

    ////////////////
    //   DROITE   //
    ////////////////
    if(value & BUTTON_RIGHT)
    {
        // Si joueur à l'arrêt
        if(ptrJoueur->Phase==0)
        {
            ptrJoueur->Axe=0;
            ptrJoueur->Phase=1;
        }
        // Si le joueur marche vers la gauche
        else if(ptrJoueur->Phase==1 && ptrJoueur->Axe==1)
        {
            ptrJoueur->Axe=0;
            SPR_setVFlip(ptrJoueur->SpriteJ, FALSE);
        }
        return;
    }

    ////////////////
    //   GAUCHE   //
    ////////////////
    if(value & BUTTON_LEFT)
    {
        // Si joueur à l'arrêt
        if(ptrJoueur->Phase==0)
        {
            ptrJoueur->Axe=1;
            ptrJoueur->Phase=1;
        }
        // Si le joueur marche vers la droite
        else if(ptrJoueur->Phase==1 && ptrJoueur->Axe==0)
        {
            ptrJoueur->Axe=1;
            SPR_setVFlip(ptrJoueur->SpriteJ, TRUE);
        }
        return;
    }
}
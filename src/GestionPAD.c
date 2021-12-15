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


void Phases_Joueur(SpriteJoueur_ *spr)
{
    // Déclaration manette
    u16 value=JOY_readJoypad(JOY_1);

    // Désactivation auto-fire
    if (!value) StatutJoy++;
    if (StatutJoy>4) StatutJoy=4;


    // PHASE ARRET //
    if(spr->phase==0)
    {
        //
    }






}
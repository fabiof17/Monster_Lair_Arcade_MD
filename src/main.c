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

// Gestion manette pour les séquences de Plateforme //
void Game_PF_Callback(u16 joy, u16 changed, u16 state)
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

            SPR_setPosition(sprite_Pause, 140, 116);

            XGM_pausePlay(Niveau1);

        }
        // Sortir du mode Pause //
        else if (PauseJeu==1)
        {
            PauseJeu=0;
            StatutJoy=0;

            SPR_setPosition(sprite_Pause, -40, 0);

           XGM_resumePlay(Niveau1);
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

            Tir_OK=1;

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

            Tir_OK=1;

            // L'AURA SE DECLENCHE
            if(ptrAura->Init==0)
            {
                ptrAura->Init=1;
            }
        }
 
         // SI JOUEUR ARRET OU MARCHE //
        else if(ptrJoueur->Phase==CHUTE)
        {
            // MARCHE + TIR
            ptrJoueur->Phase=CHUTE_TIR;

            Tir_OK=1;

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

    // init VDP
    VDP_init();

    // set all palette to black
    //PAL_setPaletteColors(0, &palette_NOIR, DMA);

    // Attente VBLANK //
    SYS_doVBlankProcess();

    //******************************************************************************************//
    //******************************************************************************************//
    //                                                                                          //
    //                                   BOUCLE PRINCIPALE                                      //
    //                                                                                          //
    //******************************************************************************************//
    //******************************************************************************************//
    while(TRUE)
    {
        //**************************************************************************************//
        //                                  ECRAN TITRE                                         //
        //**************************************************************************************//       
        if(Scene==0)
        {
            //////////////////////////////////////////////////////////////////////////////////////
            //                            CHARGEMENT ECRAN TITRE                                //
            //////////////////////////////////////////////////////////////////////////////////////           
            if(Titre_OK==0)
            {
                // Init ECRAN TITRE //
                InitTitre();
            }

            //////////////////////////////////////////////////////////////////////////////////////
            //                             ANIMATION ECRAN TITRE                                //
            //////////////////////////////////////////////////////////////////////////////////////
            else if(Titre_OK==1)
            {
                // Anim ECRAN TITRE //
                AnimTitre();
            }
        }

        //**************************************************************************************//
        //                                ECRAN SELECTION                                       //
        //**************************************************************************************// 
        else if(Scene==1)
        {
            ///////////////////////////////////////////////////////////////////////////////////////
            //                              CHARGEMENT SELECTION                                 //
            ///////////////////////////////////////////////////////////////////////////////////////
            if(Selection_OK==0)
            {
                // Init ECRAN SELECTION //
                InitSelection();
            }

            //////////////////////////////////////////////////////////////////////////////////////
            //                           ANIMATION ECRAN SELECTION                              //
            //////////////////////////////////////////////////////////////////////////////////////
            else if(Selection_OK==1)
            {
                // Anim ECRAN SELECTION //
                AnimSelection();
            }
        }

        //**************************************************************************************//
        //                                    NIVEAUX                                           //
        //**************************************************************************************// 
        else if(Scene==2)
        {
            ///////////////////////////////////////////////////////////////////////////////////////
            //                                CHARGEMENT NIVEAU                                  //
            ///////////////////////////////////////////////////////////////////////////////////////
            if(Niveau_OK==0)
            {
                // Init NIVEAU //
                InitNiveaux();
            }

            ///////////////////////////////////////////////////////////////////////////////////////
            //                                       JEU                                         //
            ///////////////////////////////////////////////////////////////////////////////////////
            else if(Niveau_OK==1)
            {
                SYS_showFrameLoad(TRUE);
                
                switch (Num_Niveau)
                {
                    case 1:

                    XGM_startPlay(Niveau1);

                    while(TRUE)
                    {

                        JOY_setEventHandler(Game_PF_Callback);

                        // En attente Continue ? //
                        if(Continue==0)
                        {
                            // Jeu en Pause ? //
                            if(PauseJeu==0)
                            {
                                Phases_Joueur();

                                Scrolling_Niveau1();

                                CreaSprites_Niveau1();
                                MvtEnnemis_Niveau1();
                                
                                MvtPlateformes_Niveau1();

                                MvtJoueur();
                                //GestionTirs();
                                
                                TilesJoueur();

                                Maj_CompteurEnergie();
                                Maj_BarreEnergie(CompteurEnergie, Energie);                               
                            }

                            // DEBUG
                            //VDP_drawInt( Joueur.Phase , 2 , 10 , 6);

                        }
                        else
                        {
                            Maj_Continue();
                        }

                        // MAJ sprites
                        SPR_update();

                        // MAJ tiles BG
                        Tiles_Niveau1();

                        // Vblank
                        SYS_doVBlankProcess();

                        // CHANGEMENT DES PALETTES
                        ChgtPalette_Niveau1();
                    }       
                }
            }
        }
    }

    return 0;
}

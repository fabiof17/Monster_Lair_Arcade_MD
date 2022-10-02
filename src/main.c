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


// Procédure principale //
int main(bool resetType)
{
    if (!resetType) SYS_hardReset();

	// Init HW //
	InitSystem();

    // Reset variables //
    InitVariablesGeneral();

    // Init joypad //
    JOY_init();

    DEBUG_COLLISIONS_ENNEMIS=0;


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
            else
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
            else
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
            else
            {
                //SYS_showFrameLoad(TRUE);
                
                switch (Num_Niveau)
                {
                    case 1:

                    XGM_startPlay(musique_Niveau1);

                    while(SWITCH_GAMEOVER == 0)
                    {

                        JOY_setEventHandler(Game_PF_Callback);

                        // NOT in CONTINUE phase //
                        if(SWITCH_CONTINUE==0)
                        {
                            // Jeu en Pause ? //
                            if(PauseJeu == 0)
                            {
                                Phases_Joueur();

                                Scrolling_Niveau1();

                                Crea_Sprites_Niveau1();
                                Mvt_Ennemis_Niveau1();
                                
                                MvtPlateformes_Niveau1();

                                Mvt_Joueur();
                                Mvt_TirJoueur();
                                
                                TilesJoueur();

                                //Maj_CompteurEnergie();
                                //Maj_BarreEnergie(CompteurEnergie, Energie);                               
                            }

                            //** DEBUG **//
                            /*
                            SpriteBalle_ *ptrTOTO=&Balles[0];
                            SpriteBalle_ *ptrTATA=&Balles[1];
                            SpriteBalle_ *ptrTUTU=&Balles[2];

                            VDP_drawInt( ptrTOTO->Init , 1 , 20 , 5 );
                            VDP_drawInt( ptrTATA->Init , 1 , 21 , 5 );
                            VDP_drawInt( ptrTUTU->Init , 1 , 22 , 5 );

                            VDP_drawInt( Nb_Balles , 1 , 24 , 5 );
                            */
                        }

                        // In CONTINUE phase //
                        else
                        {
                            Maj_Continue();
                        }

                        //** DEBUG **//
                        //VDP_drawInt( SWITCH_GAMEOVER , 1 , 12 , 5);

                        // MAJ sprites
                        SPR_update();

                        // MAJ tiles BG
                        Tiles_Niveau1();

                        // Vblank
                        SYS_doVBlankProcess();

                        // CHANGEMENT DES PALETTES
                        ChgtPalette_Niveau1();
                    }

                    Effacer_BarreEnergie();
                    Afficher_GameOver();
                    SPR_update();

                    waitMs(5000);

                    XGM_pausePlay();
                    XGM_stopPlay();

                    Clear_Niveau1();

                    InitVariablesGeneral();
                    SPR_end();

                    SYS_doVBlankProcess();
                }
            }
        }
    }
    
    return 0;
}

#include <genesis.h>
#include "main.h"
#include "init.h"
#include "variables.h"
#include "palettes.h"
#include "maps_GLOBALES.h"
#include "maps_NIVEAU1.h"
#include "tilemaps_ennemis.h"
#include "palettes_ennemis.h"
#include "tilemaps_plateformes.h"
#include "animation_sprites.h"
#include "sprites_JEU.h"
#include "musique.h"
#include "sons.h"


void VDP_drawInt(u16 valeur,u8 zeros,u8 x, u8 y)
{
	intToStr(valeur,texteSortie,zeros); //MIN -500.000.000 - MAX 500.000.000
	VDP_drawTextBG(WINDOW,texteSortie,x,y);
}



//----------------------------------------------------//
//                      GAMEOVER                      //
//----------------------------------------------------//
void Afficher_GameOver()
{
    // Effacer CONTINUE ? //
    VDP_setTileMapEx(WINDOW, image_BARRE_VIERGE.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, AdresseVram_BarreVerte), 3, 3, 0, 0, 1, 2, DMA);
    //VDP_setTileMapEx(WINDOW, image_BARRE_VIERGE.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, AdresseVram_BarreVerte), 4, 3, 0, 0, 1, 2, DMA);
    VDP_setTileMapEx(WINDOW, image_BARRE_VIERGE.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, AdresseVram_BarreVerte), 17, 3, 0, 0, 1, 2, DMA);
    VDP_setTileMapEx(WINDOW, image_BARRE_VIERGE.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, AdresseVram_BarreVerte), 18, 3, 0, 0, 1, 2, DMA);        
    
    // Chargement tiles GAMEOVER à la place des tiles CONTINUE ? //
    VDP_loadTileSet(image_GAMEOVER_WINDOW.tileset, AdresseVram_Continue, DMA);

    // Affichage GAMEOVER //
    // getting tilemap data from IMAGE structure declared in maps_GLOBALES.res
    VDP_setTileMapEx(WINDOW, image_GAMEOVER_WINDOW.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, AdresseVram_Continue), 4, 3, 0, 0, 12, 2, DMA);

    // Sprite GAMEOVER //
    SPR_setPosition(sprite_GameOver, 80, 88);
}

//----------------------------------------------------//
//                      CONTINUE                      //
//----------------------------------------------------//
void Maj_Continue()
{
    // Pointeur vers la tilemap à charger pour la barre d'énergie //
    const TileSet *ptrBARRE;

    if(Compteur_Continue==0)
    {
        // On pointe sur le tileset de la barre noire //
        ptrBARRE=&tileset_BARRE_NOIRE;

        // EFFACEMENT BARRE ENERGIE //
        // Chargement de la barre noire en Vram //
        VDP_loadTileSet(ptrBARRE, AdresseVram_BarreVerte, DMA);
        VDP_loadTileSet(ptrBARRE, AdresseVram_BarreVierge, DMA);

        // CHIFFRE 9 //
        VDP_loadTileSet(image_CHIFFRE_9.tileset, AdresseVram_ChiffresContinue, DMA);

        // AFFICHAGE CONTINUE ? //
        // getting tilemap data from IMAGE structure declared in maps_GLOBALES.res
        VDP_setTileMapEx(WINDOW, image_CONTINUE.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, AdresseVram_Continue), 4, 3, 0, 0, 12, 2, DMA);


        // AFFICHAGE CHIFFRE 9 //
        // getting tilemap data from IMAGE structure declared in maps_GLOBALES.res
        VDP_setTileMapEx(WINDOW, image_CHIFFRE_9.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, AdresseVram_ChiffresContinue), 17, 3, 0, 0, 2, 2, DMA);

        /***********/
        /* CREDITS */
        /***********/
        SPR_setPosition(sprite_Credits, 124, 116);
        SPR_setPosition(sprite_Nb_Credits, 188, 116);
    }
    
    else if(Compteur_Continue==60)
    {
        // CHIFFRE 8 //
        VDP_loadTileSet(image_CHIFFRE_8.tileset, AdresseVram_ChiffresContinue, DMA);
    }

    else if(Compteur_Continue==120)
    {
        // CHIFFRE 7 //
        VDP_loadTileSet(image_CHIFFRE_7.tileset, AdresseVram_ChiffresContinue, DMA);
    }

    else if(Compteur_Continue==180)
    {
        // CHIFFRE 6 //
        VDP_loadTileSet(image_CHIFFRE_6.tileset, AdresseVram_ChiffresContinue, DMA);
    }

    else if(Compteur_Continue==240)
    {
        // CHIFFRE 5 //
        VDP_loadTileSet(image_CHIFFRE_5.tileset, AdresseVram_ChiffresContinue, DMA);
    }

    else if(Compteur_Continue==300)
    {
        // CHIFFRE 4 //
        VDP_loadTileSet(image_CHIFFRE_4.tileset, AdresseVram_ChiffresContinue, DMA);
    }

    else if(Compteur_Continue==360)
    {
        // CHIFFRE 3 //
        VDP_loadTileSet(image_CHIFFRE_3.tileset, AdresseVram_ChiffresContinue, DMA);
    }

    else if(Compteur_Continue==420)
    {
        // CHIFFRE 2 //
        VDP_loadTileSet(image_CHIFFRE_2.tileset, AdresseVram_ChiffresContinue, DMA);
    }

    else if(Compteur_Continue==480)
    {
        // CHIFFRE 1 //
        VDP_loadTileSet(image_CHIFFRE_1.tileset, AdresseVram_ChiffresContinue, DMA);
    }

    else if(Compteur_Continue==540)
    {
        // CHIFFRE 0 //
        VDP_loadTileSet(image_CHIFFRE_0.tileset, AdresseVram_ChiffresContinue, DMA);
    }

    else if(Compteur_Continue==600)
    {
        SPR_setPosition(sprite_Credits, 0, -8);
        SPR_setPosition(sprite_Nb_Credits, 0, -8);
        SWITCH_GAMEOVER = 1;
    }



    Compteur_Continue++;



    if(Compteur_Continue>601)
    {
        Compteur_Continue=601;
    }

}

void Maj_Vies()
{  
    // If player runs out of life //
    if(Nb_Vies==0)
    {
        // If there are remaining credits //
        //if(Nb_Credits != 0)
        //{
            // Switch to CONTINUE phase //
            SWITCH_CONTINUE = 1;

            // Reset CONTINUE counter //
            Compteur_Continue = 0;
        //}
    }

    // If player still has life //
    else
    {
        // Clear Life sprite //
        SPR_releaseSprite(sprite_Vie[Nb_Vies-1]);

        // Substract 1 life //
        Nb_Vies-=1;
    }
}

void Clear_Niveau1()
{
    // Disable interruptions //
    //SYS_disableInts();

    SYS_doVBlankProcess();

    // set all palettes to black
    PAL_setPaletteColors(0, &palette_NOIR, DMA);
   


    VDP_setWindowHPos(0, 0);
    VDP_setWindowVPos(0, 0);
    VDP_resetScreen();

    // Clear collision MAP //
    MEM_free(tilemapCollision);


    // Clear all sprites //
    SPR_reset();

    // Disable Sprite Engine //
    SPR_end();

}



//----------------------------------------------------//
//                    BARRE ENERGIE                   //
//----------------------------------------------------//
void Effacer_BarreEnergie()
{
     VDP_loadTileSet(&tileset_BARRE_NOIRE, AdresseVram_BarreVerte, DMA);
     VDP_loadTileSet(&tileset_BARRE_NOIRE, AdresseVram_BarreVierge, DMA);
}

void Init_BarreEnergie()
{
    Energie=ENERGIE_DEPART;
    CompteurEnergie=0;

    ///////////////////
    //  TETE JOUEUR  //
    ///////////////////
    if(selectJoueur==0)
    {
        VDP_loadTileSet(&tileset_TETE_H, AdresseVram_Tete, DMA);
    }
    else
    {
        VDP_loadTileSet(&tileset_TETE_F, AdresseVram_Tete, DMA);
    }

    VDP_loadTileSet(&tileset_BARRE_VERTE1, AdresseVram_BarreVerte, DMA);
    VDP_loadTileSet(&tileset_BARRE_VIERGE, AdresseVram_BarreVierge, DMA);
    


    u8 i;
    
    for (i=0; i<ENERGIE_DEPART; i++)
    {
        VDP_setTileMapEx(WINDOW, image_BARRE_VERTE1.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, AdresseVram_BarreVerte), 4+i, 3, 0, 0, 1, 2, DMA);
    }

    for (i=ENERGIE_DEPART; i<ENERGIE_DEPART+7; i++)
    {
        VDP_setTileMapEx(WINDOW, image_BARRE_VIERGE.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, AdresseVram_BarreVierge), 4+i, 3, 0, 0, 1, 2, DMA);
    }

    VDP_setTileMapEx(WINDOW, image_BARRE_VIERGE.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, AdresseVram_BarreNoire), ENERGIE_DEPART+11, 3, 0, 0, 1, 2, DMA);
}

void Maj_CompteurEnergie()
{
    // LA BARRE SE BLOQUE A LA FIN DU NIVEAU
    if(CamPosX>-4336)
    {
        SpriteJoueur_ *ptrJoueur=&Joueur;
        
        // LA BARRE SE BLOQUE SI JOUEUR TOUCHE OU EN COURS D'APPARITION //
        if(ptrJoueur->Phase!=TOUCHE && ptrJoueur->Phase!=APPARITION)
        {            
            CompteurEnergie++;

            if(CompteurEnergie>DELAI_MAJ_ENERGIE)
            {
                // COMPTEUR REMIS A 0 //
                CompteurEnergie=0;

                // ON ENLEVE 1 BARRE D'ENERGIE //
                Energie-=1;

                // SI L'ENERGIE TOMBE A 0 //
                if(Energie==0)
                {
                    ptrJoueur->Phase=TOUCHE;
                    ptrJoueur->ptrPosition=&anim_TOUCHE[0];
                    Energie=ENERGIE_DEPART;
                }
            }
        }
    }
}

void Maj_BarreEnergie(u8 valeurCompteur, u8 valeurEnergie)
{
    SpriteJoueur_ *ptrJoueur=&Joueur;

    if(ptrJoueur->Phase!=TOUCHE && ptrJoueur->Phase!=APPARITION)
    {
        // SI LE COMPTEUR EST A 0 //
        if(valeurCompteur==0)
        {
            // Pointeur vers la tilemap à charger pour la barre d'énergie //
            const TileSet *ptrBARRE;

            if(valeurEnergie<5)
            {
                ptrBARRE=&tileset_BARRE_ORANGE;
                //break;
            }
            else if(valeurEnergie>4 && valeurEnergie<7)
            {
                ptrBARRE=&tileset_BARRE_JAUNE;
                //break;
            }
            else if(valeurEnergie>6 && valeurEnergie<8)
            {
                ptrBARRE=&tileset_BARRE_VERTE1;
                //break;
            }
            else if(valeurEnergie>7)
            {
                ptrBARRE=&tileset_BARRE_VERTE2;
                //break;
            }

            VDP_loadTileSet(ptrBARRE, AdresseVram_BarreVerte, DMA);
            VDP_setTileMapEx(WINDOW, image_BARRE_VIERGE.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, AdresseVram_BarreVierge), 4 + (u16)valeurEnergie, 3, 0, 0, 1, 2, DMA);
    
        }
    }
}

inline static void Vider_BarreEnergie()
{
    VDP_loadTileSet(&tileset_BARRE_VIERGE, AdresseVram_BarreVerte, DMA);
}



//----------------------------------------------------//
//                      SCROLLING                     //
//----------------------------------------------------//
void Scrolling_Niveau1()
{
    u16 i;

    s16 scrollOffset_TILE_NIVEAU1_BGA[28];
    s16 scrollOffset_TILE_NIVEAU1_BGB[28];

    // MOUVEMENT CAMERA //
    CamPosX-=vitesseScrolling;

    if(CamPosX<-4336)
    {
        CamPosX=-4336;
    }

    tilemapOffset=-(CamPosX>>3);




    // MISE A JOUR TILEMAP //
    if(CamPosX>-4336)
    {

        compteurTile+=vitesseScrolling;

        // DEPLACEMENT CAMERA //
        // BG_A
        for (i=0; i<28; i++)
        {
            scrollOffset_TILE_NIVEAU1_BGA[i]=CamPosX;
        }

        // scrolling par tile
        VDP_setHorizontalScrollTile(BG_A, 7, scrollOffset_TILE_NIVEAU1_BGA, 21, DMA_QUEUE);



        // BG_B
        // NUAGES
        for (i=0; i<17; i++)
        {
            scrollOffset_TILE_NIVEAU1_BGB[i]=CamPosX>>1;
        }
        // EAU
        for (i=17; i<21; i++)
        {
            scrollOffset_TILE_NIVEAU1_BGB[i]=CamPosX;
        }

        VDP_setHorizontalScrollTile(BG_B, 7, scrollOffset_TILE_NIVEAU1_BGB, 24, DMA_QUEUE);
    }
}

void Tiles_Niveau1()
{
    // MISE A JOUR TILEMAP //
    if(CamPosX>-4336)
    {
        if (tilemapOffset>0 && tilemapOffset<520)
        {
            // BG_B //
            VDP_setTileMapColumnEx(BG_B, image_NIVEAU1_BGB.tilemap, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, 16), (tilemapOffset>>1)-2, 62+(tilemapOffset>>1), 7, 20, DMA_QUEUE);
            VDP_setTileMapColumnEx(BG_B, image_NIVEAU1_BGB.tilemap, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 16), (tilemapOffset>>1)-2, 62+(tilemapOffset>>1), 27, 4, DMA_QUEUE);

            // BG_A //
            // TETE DE DRAGON DE FIN DE NIVEAU EN PRIORITE 1 //
            if(tilemapOffset>482)
            {
                VDP_setTileMapColumnEx(BG_A, image_NIVEAU1_BGA.tilemap, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, AdresseVram_BG_A), tilemapOffset-2, 62+tilemapOffset, 7, 21, DMA_QUEUE);
            }
            else
            {
                VDP_setTileMapColumnEx(BG_A, image_NIVEAU1_BGA.tilemap, TILE_ATTR_FULL(PAL3, FALSE, FALSE, FALSE, AdresseVram_BG_A), tilemapOffset-2, 62+tilemapOffset, 7, 21, DMA_QUEUE);
            }

        }
    }
}

void ChgtPalette_Niveau1()
{
    // CHANGEMENTS PALETTE

     if(CamPosX<-700 && CamPosX>-704)
    {
        const u16* NouvellePalette = palette_NIVEAU1_BULOT.data;
        PAL_setPalette(PAL1, NouvellePalette, DMA);
    }

    else if(CamPosX<-1110 && CamPosX>-1114)
    {
        const u16* NouvellePalette = palette_NIVEAU1_ESCARGOT.data;
        PAL_setPalette(PAL1, NouvellePalette, DMA);
    }

    else if(CamPosX<-2600 && CamPosX>-2604)
    {
        const u16* NouvellePalette = palette_NIVEAU1_PELICAN.data;
        PAL_setPalette(PAL1, NouvellePalette, DMA);
    }

    else if(CamPosX<-3700 && CamPosX>-3704)
    {
        const u16* NouvellePalette = palette_NIVEAU1_BULOT.data;
        PAL_setPalette(PAL1, NouvellePalette, DMA);
    }

    else if(CamPosX<-4016 && CamPosX>-4020)
    {
        const u16* NouvellePalette = palette_NIVEAU1_BGA2.data;
        PAL_setPalette(PAL3, NouvellePalette, DMA);
    }
}



//----------------------------------------------------//
//                      COLLISIONS                    //
//----------------------------------------------------//
inline static void MAJ_PtsCollision_Joueur()
{
    SpriteJoueur_ *ptrJoueur=&Joueur;

    // POINTS GAUCHE //
    if(ptrJoueur->PosX>=0)
    {
        ptrJoueur->pt_Coll_BG_X=fix32ToInt(positionX)+8;
        ptrJoueur->pt_Coll_CG_X=ptrJoueur->pt_Coll_BG_X;
    }
    else
    {
        ptrJoueur->pt_Coll_BG_X=fix32ToInt(positionX)+11;
        ptrJoueur->pt_Coll_CG_X=ptrJoueur->pt_Coll_BG_X;
    }
    ptrJoueur->pt_Coll_BG_Y=fix32ToInt(positionY)+10;
    ptrJoueur->pt_Coll_CG_Y=fix32ToInt(positionY)+7;


    // POINTS DROITE //
    ptrJoueur->pt_Coll_BD_X=fix32ToInt(positionX)+21;
    ptrJoueur->pt_Coll_CD_X=ptrJoueur->pt_Coll_BD_X;

    ptrJoueur->pt_Coll_BD_Y=ptrJoueur->pt_Coll_BG_Y;
    ptrJoueur->pt_Coll_CD_Y=ptrJoueur->pt_Coll_CG_Y;


    posTileY=ptrJoueur->pt_Coll_BG_Y>>3;
}

inline static void Collision_Decor_Bas()
{
    u16 *ptrtileID_BG=&tileID_BG;
    u16 *ptrtileID_BD=&tileID_BD;

    SpriteJoueur_ *ptrJoueur=&Joueur;

    *ptrtileID_BG=MAP_getTile( tilemapCollision , ((ptrJoueur->pt_Coll_BG_X - CamPosX) >> 3) , posTileY ) & TILE_INDEX_MASK;
    *ptrtileID_BD=MAP_getTile( tilemapCollision , ((ptrJoueur->pt_Coll_BD_X - CamPosX) >> 3) , posTileY ) & TILE_INDEX_MASK;
}

inline static void Collision_Decor_Cotes()
{
    u16 *ptrtileID_CG=&tileID_CG;
    u16 *ptrtileID_CD=&tileID_CD;

    SpriteJoueur_ *ptrJoueur=&Joueur;

    *ptrtileID_CG=MAP_getTile( tilemapCollision , ((ptrJoueur->pt_Coll_CG_X - CamPosX) >> 3) , ((ptrJoueur->pt_Coll_CG_Y - CamPosX) >> 3) ) & TILE_INDEX_MASK;
    *ptrtileID_CD=MAP_getTile( tilemapCollision , ((ptrJoueur->pt_Coll_CD_X - CamPosX) >> 3) , ((ptrJoueur->pt_Coll_CD_Y - CamPosX) >> 3) ) & TILE_INDEX_MASK;
}

inline static void Collision_Decor_Haut()
{
    u16 *ptrtileID_H=&tileID_H;

    SpriteJoueur_ *ptrJoueur=&Joueur;

    *ptrtileID_H=MAP_getTile( tilemapCollision , ((ptrJoueur->PosX + 16 - CamPosX) >> 3) , posTileY + 5 ) & TILE_INDEX_MASK;     
}

inline static void Collision_Joueur_Ennemis()
{
    if(DEBUG_COLLISIONS_ENNEMIS==0)
    {    
        // SI IL Y A DES ENNEMIS
        if(nb_Ennemis != 0)
        {
            u16 i;

            SpriteJoueur_ *ptrJoueur=&Joueur;

            // SI LE JOUEUR PAS TOUCHÉ NI MORT
            if(ptrJoueur->Phase != 99 && ptrJoueur->Phase != 100)
            {
                // ON CYCLE DANS LE TABLEAU DES ENNEMIS
                for( i=0 ; i<MAX_ENNEMIS ; i++ )
                {
                    SpriteEnnemi_ *ptrEnnemi=&Ennemi[i];

                    // Si le sprite a été créé
                    if(ptrEnnemi->Init==1)
                    {
                        //----------------------------//
                        //      SI ENNEMI VIVANT      //
                        //----------------------------//
                        if(ptrEnnemi->Etat == 1)
                        {
                            // *---*---*---*---*
                            // |   |   |   |   |
                            // *---*---*---*---*
                            // |   |   |   |   |
                            // *---*--[X]--*---*
                            // |   |   |   |   |
                            // *---*---*---*---*
                            // |   |   |   |   |
                            // *---*---*---*---*

                            // LIMITE GAUCHE DU SPRITE ENNEMI (ptrEnnemi->PosX)
                            if(ptrJoueur->PosX+16 >= ptrEnnemi->PosX)
                            {
                                // LIMITE DROITE DU SPRITE ENNEMI (ptrEnnemi->PosX+24)
                                if(ptrJoueur->PosX+16 <= ptrEnnemi->PosX+ptrEnnemi->Largeur)
                                {
                                    // LIMITE HAUT DU SPRITE ENNEMI
                                    if(ptrJoueur->PosY-8 >= ptrEnnemi->PosY)
                                    {
                                        //
                                        if(ptrJoueur->PosY-24 <= ptrEnnemi->PosY+ptrEnnemi->Largeur)
                                        {
                                            ptrJoueur->Phase=TOUCHE;
                                            ptrJoueur->ptrPosition=&anim_SAUT[0];
                                            ptrJoueur->ptrPosition=&anim_TOUCHE[0];
                                            return;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

inline static void Collision_Joueur_Plateformes()
{
    u8 i;
    u16 value=JOY_readJoypad(JOY_1);
    SpriteJoueur_ *ptrJoueur=&Joueur;

    // SI DES PLATEFORMES ONT ÉTÉ CRÉÉES //
    if(nb_Plateformes>0)
    {
        contactPlt_OK=0;

        // On scanne les emplacements vides
        for(i=0;i<MAX_PLATEFORMES;i++)
        {
            SpritePlateforme_ *ptrPlateforme=&Plateforme[i];

            // Si le sprite a été créé
            if(ptrPlateforme->Init==1)
            {
                //----------------------------------------//
                //       COIN BAS GAUCHE DU JOUEUR        //
                //----------------------------------------//
                // Si pt collision X G joueur >= pt collision X G plateforme
                if(ptrJoueur->pt_Coll_BG_X >= ptrPlateforme->pt_Coll1_X)
                {
                    // Si pt collision X G joueur <= pt collision X D plateforme
                    if((ptrJoueur->pt_Coll_BG_X <= ptrPlateforme->pt_Coll2_X))
                    {
                        // Si pt collision Y G joueur >= pt collision Y G plateforme
                        if(ptrJoueur->pt_Coll_BG_Y >= ptrPlateforme->pt_Coll1_Y)
                        {
                            // Si pt collision Y G joueur >= pt collision Y G plateforme +7
                            if(ptrJoueur->pt_Coll_BG_Y <= ptrPlateforme->pt_Coll1_Y+15)
                            {
                                // Il y a contact
                                contactPlt_OK=1;

                                // Déclenchement des plateformes mouvantes
                                if(ptrPlateforme->Mouvante==1)
                                {
                                    ptrPlateforme->Declencheur=1;
                                }


                                // Plateformes mouvantes horizontales
                                if(ptrPlateforme->ID==2 || ptrPlateforme->ID==7)
                                {
                                    positionX += intToFix32(*(ptrPlateforme->ptrPosition));
                                }


                                // Position du joueur = position de la plateforme-hauteur du sprite (8px)
                                ptrJoueur->PosY = ptrPlateforme->PosY-8;
                                // MAJ de la variable positionY
                                positionY=intToFix32(ptrJoueur->PosY);
                                // réinit de l'accélération verticale
                                movY=0;


                                // réinit de l'anim de saut
                                ptrJoueur->ptrPosition=&anim_SAUT[0];



                                if((value & BUTTON_DIR) == 0)
                                {
                                    if(ptrJoueur->Phase!=TIR)
                                    {
                                        ptrJoueur->Phase=ARRET;
                                    }
                                }
                                else if(value & BUTTON_RIGHT || value & BUTTON_LEFT)
                                {
                                    if(ptrJoueur->Phase!=TIR)
                                    {
                                        ptrJoueur->Phase=MARCHE;
                                    }
                                }
                                return;
                            }
                        }
                    }
                }
                //----------------------------------------//
                //       COIN BAS DROITE DU JOUEUR        //
                //----------------------------------------//
                // Si pt collision X D joueur >= pt collision X G plateforme
                else if(ptrJoueur->pt_Coll_BD_X >= ptrPlateforme->pt_Coll1_X)
                {
                    // Si pt collision X D joueur <= pt collision X D plateforme
                    if((ptrJoueur->pt_Coll_BD_X <= ptrPlateforme->pt_Coll2_X))
                    {
                        // Si pt collision Y D joueur >= pt collision Y G plateforme
                        if(ptrJoueur->pt_Coll_BD_Y >= ptrPlateforme->pt_Coll1_Y)
                        {
                            // Si pt collision Y D joueur >= pt collision Y G plateforme +7
                            if(ptrJoueur->pt_Coll_BD_Y <= ptrPlateforme->pt_Coll1_Y+15)
                            {
                                // Il y a contact
                                contactPlt_OK=1;

                                // Déclenchement des plateformes mouvantes
                                if(ptrPlateforme->Mouvante==1)
                                {
                                    ptrPlateforme->Declencheur=1;
                                }

                                
                                // Plateformes mouvantes horizontales
                                if(ptrPlateforme->ID==2 || ptrPlateforme->ID==7)
                                {
                                    positionX += intToFix32(*(ptrPlateforme->ptrPosition));
                                }


                                // Position du joueur = position de la plateforme-hauteur du sprite (8px)
                                ptrJoueur->PosY = ptrPlateforme->PosY-8;
                                // MAJ de la variable positionY
                                positionY=intToFix32(ptrJoueur->PosY);
                                // réinit de l'accélération verticale
                                movY=0;


                                // réinit de l'anim de saut
                                ptrJoueur->ptrPosition=&anim_SAUT[0];



                                if((value & BUTTON_DIR) == 0)
                                {
                                    if(ptrJoueur->Phase!=TIR)
                                    {
                                        ptrJoueur->Phase=ARRET;
                                    }
                                }
                                else if(value & BUTTON_RIGHT || value & BUTTON_LEFT)
                                {
                                    if(ptrJoueur->Phase!=TIR)
                                    {
                                        ptrJoueur->Phase=MARCHE;
                                    }
                                }
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
}



inline static void Crea_Impact( SpriteEnnemi_ *ptrEnnemi )
{
    u8 i;

    for( i=0 ; i<MAX_IMPACTS ; i++)
    {
        SpriteImpact_ *ptrImpact=&Impacts[i];
        
        if( ptrImpact->Init == 0 )
        {
            ptrImpact->Init = 1;

            ptrImpact->SpriteI = SPR_addSprite(&tiles_Sprite_IMPACT, ptrEnnemi->PosX, ptrEnnemi->PosY, TILE_ATTR (PAL0, FALSE, FALSE, FALSE) );
            SPR_setDepth(ptrImpact->SpriteI,15);
            ptrImpact->CompteurFrame = 0;
            ptrImpact->IndexFrame = 0;
            SPR_setFrame(ptrImpact->SpriteI,(s16)ptrImpact->IndexFrame);

            break;
        }
    }
}

inline static void Crea_Explo_Ennemi( SpriteEnnemi_ *ptrEnnemi )
{
    u8 i;

    for( i=0 ; i<MAX_IMPACTS ; i++)
    {
        SpriteExploEnnemi_ *ptrExploEnnemi=&ExploEnnemis[i];
        
        if( ptrExploEnnemi->Init == 0 )
        {
            ptrExploEnnemi->Init = 1;

            ptrExploEnnemi->SpriteEE = SPR_addSprite(&tiles_Sprite_EXPLOSION_ENNEMI, ptrEnnemi->PosX - ( (32-ptrEnnemi->Largeur) >>1 ), ptrEnnemi->PosY, TILE_ATTR (PAL0, FALSE, FALSE, FALSE) );
            SPR_setDepth(ptrExploEnnemi->SpriteEE,16);
            ptrExploEnnemi->CompteurFrame = 0;
            ptrExploEnnemi->IndexFrame = 0;
            SPR_setFrame(ptrExploEnnemi->SpriteEE,(s16)ptrExploEnnemi->IndexFrame);

            break;
        }
    }
}



inline static void Collision_Tir_Joueur_Ennemis( SpriteBalle_ *ptrProjectile , u8 largeur )
{
    u8 e;

    for(e=0 ; e<MAX_ENNEMIS ; e++)
    {
        SpriteEnnemi_ *ptrEnnemi=&Ennemi[e];

        //--------------------------//
        //      SI SPRITE CREE      //
        //--------------------------//
        if( ptrEnnemi->Init == 1 )
        {
            //----------------------------//
            //      SI ENNEMI VIVANT      //
            //----------------------------//
            if( ptrEnnemi->Etat == 1)
            {
                // ON VERIFIE LES COLLISIONS QUAND LE SPRITE EST RENTRE DE 16 PIXELS DANS L'ECRAN // 
                if( ptrEnnemi->PosX < 304 )
                {
                    if( ptrProjectile->PosX+ptrProjectile->Largeur > ptrEnnemi->PosX+ptrEnnemi->Marge)
                    {
                        if( ptrProjectile->PosX < ptrEnnemi->PosX+ptrEnnemi->Largeur-ptrEnnemi->Marge )
                        {
                            if( ptrProjectile->PosY+ptrProjectile->Hauteur > ptrEnnemi->PosY )
                            {
                                if( ptrProjectile->PosY < ptrEnnemi->PosY+ptrEnnemi->Hauteur )
                                {
                                    // On enlève 1 point de vie //
                                    ptrEnnemi->PointsVie -= 1;

                                    // On supprime le projectile //
                                    ptrProjectile->Init = 0;
                                    SPR_releaseSprite( ptrProjectile->SpriteB );

                                    Nb_Projectiles -= 1;
                                    Nb_Balles -= 1;

                                    // Création de  l'impact //
                                    Nb_Impacts += 1;
                                    Crea_Impact( ptrEnnemi );

                                    if( ptrEnnemi->PointsVie == 0 )
                                    {
                                        // Ennemi MORT //
                                        ptrEnnemi->Etat = 0;

                                        // Tile ENNEMI mort //
                                        SPR_setAnimAndFrame( ptrEnnemi->SpriteE , 1 , 0 );

                                        // On commence l'anim de chute //
                                        ptrEnnemi->ptrPosition=&anim_CHUTE_ENNEMIS[0];

                                        //  Création de l'explosion //
                                        if( ptrEnnemi->ID == 4 || ptrEnnemi->ID == 5 || ptrEnnemi->ID == 6 || ptrEnnemi->ID == 7 )
                                        {
                                            Nb_ExploEnnemis += 1;
                                            Crea_Explo_Ennemi( ptrEnnemi );
                                        }                                          
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
}

//----------------------------------------------------//
//                   SPRITES NIVEAU 1                 //
//----------------------------------------------------//
void Crea_Sprites_Niveau1()
{
    u16 i;

    // Si compteurTile est supérieur à 7
    if(compteurTile>7)
    {
        u8 delta = compteurTile-8;

        /////////////////
        //   ENNEMIS   //
        /////////////////

        // tilemapCreaEnnemis_Niveau1[0][indexCreaEnnemis] : PosX
        if (-CamPosX>>3 == tilemapCreaEnnemis_Niveau1[0][indexCreaEnnemis])
        {
            // On scanne les emplacements vides
            for(i=0;i<MAX_ENNEMIS;i++)
            {
                SpriteEnnemi_ *ptrEnnemi=&Ennemi[i];

                // Si on trouve un emplacement vide
                if(ptrEnnemi->Init==0)
                {
                    ptrEnnemi->Init=1;          // ENNEMI CREE
                    ptrEnnemi->Etat=1;          // ENNEMI VIVANT
                    //ptrEnnemi->PointsVie=1;

                    ptrEnnemi->CompteurPosition=0;
                    ptrEnnemi->CompteurFrame=i;
                    ptrEnnemi->IndexFrame=0;

                    ptrEnnemi->Axe=0;

                    //---------------------------//
                    //             ID            //
                    //---------------------------//
                    ptrEnnemi->ID=tilemapCreaEnnemis_Niveau1[2][indexCreaEnnemis];

                    //-----------------------------------//
                    //             POSITION X            //
                    //-----------------------------------//
                    ptrEnnemi->PosX=tilemapCreaEnnemis_Niveau1[3][indexCreaEnnemis]-delta;

                    //-----------------------------------//
                    //             POSITION Y            //
                    //-----------------------------------//
                    ptrEnnemi->PosY=tilemapCreaEnnemis_Niveau1[4][indexCreaEnnemis];

                    //------------------------------//
                    //             BONUS            //
                    //------------------------------//
                    ptrEnnemi->Bonus=tilemapCreaEnnemis_Niveau1[5][indexCreaEnnemis];

                    //------------------------------//
                    //         POINTS DE VIE        //
                    //------------------------------//
                    
                    //--------------------------------//
                    //             LARGEUR            //
                    //--------------------------------//

                    //--------------------------------//
                    //             HAUTEUR            //
                    //--------------------------------//                    

                    //--------------------------------//
                    //              MARGE             //
                    //--------------------------------//

                    // MORSE
                    if(ptrEnnemi->ID==4)
                    {
                        ptrEnnemi->Largeur = 40;
                        ptrEnnemi->Hauteur = 40;
                        ptrEnnemi->PointsVie=8;
                        ptrEnnemi->Marge = 8;
                    }
                    // LES AUTRES ENNEMIS
                    else
                    {                        
                        ptrEnnemi->Largeur = 24;
                        ptrEnnemi->Hauteur = 24;
                        ptrEnnemi->PointsVie=1;
                        ptrEnnemi->Marge = 4;
                    }



                    ptrEnnemi->SpriteE = SPR_addSprite(AdrTilesEnnemi[ptrEnnemi->ID-1], ptrEnnemi->PosX, ptrEnnemi->PosY, TILE_ATTR(paletteEnnemis_Niveau1[(ptrEnnemi->ID)-1], FALSE, FALSE, FALSE));


                    // POULPE 1
                    if(ptrEnnemi->ID==5)
                    {
                        //ptrEnnemi->Hauteur = 32;
                        ptrEnnemi->ptrPosition=&anim_POULPE1[0];
                    }
                    // POULPE 2
                    else if(ptrEnnemi->ID==6)
                    {
                        //ptrEnnemi->Hauteur = 32;
                        ptrEnnemi->ptrPosition=&anim_POULPE2[0];
                    }

                    indexCreaEnnemis++;
                    nb_Ennemis+=1;

                    break;
                }
            }
        }

        /////////////////////
        //   PLATEFORMES   //
        /////////////////////

        // tilemapCreaPlateformes_Niveau[0][indexCreaPlateformes] : PosX
        if (-CamPosX>>3 == tilemapCreaPlateformes_Niveau1[0][IndexCreaPlateformes])
        {
            // On scanne les emplacements vides
            for(i=0;i<MAX_PLATEFORMES;i++)
            {
                SpritePlateforme_ *ptrPlateforme=&Plateforme[i];

                // Si on trouve un emplacement vide
                if(ptrPlateforme->Init==0)
                {
                    // tilemapCreaPlateformes_Niveau1[2][indexCreaPlateformes] : ID
                    ptrPlateforme->ID=tilemapCreaPlateformes_Niveau1[2][IndexCreaPlateformes];

                     // tilemapCreaPlateformes_Niveau1[3][indexCreaPlateformes] : MOUVANTE OU NON
                    ptrPlateforme->Mouvante=tilemapCreaPlateformes_Niveau1[3][IndexCreaPlateformes];

                    ptrPlateforme->Init=1;
                    ptrPlateforme->Declencheur=0;

                    // POSITION X
                    ptrPlateforme->PosX=321-delta;

                    // POSITION Y
                    // tilemapCreaPlateformes_Niveau1[1][indexCreaPlateformes] : PosY
                    ptrPlateforme->PosY=(u16)tilemapCreaPlateformes_Niveau1[1][IndexCreaPlateformes]<<3;



                    ptrPlateforme->SpriteP = SPR_addSprite(&tiles_Sprite_PLATEFORME, ptrPlateforme->PosX, ptrPlateforme->PosY, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));


                    // PLATEFORME VERTICALE 1 //
                    if(ptrPlateforme->ID==1 || ptrPlateforme->ID==3 || ptrPlateforme->ID==4 || ptrPlateforme->ID==6)
                    {
                        ptrPlateforme->ptrPosition=&anim_PLATEFORME_V1[0];
                    }
                    else if(ptrPlateforme->ID==5)
                    {
                        ptrPlateforme->ptrPosition=&anim_PLATEFORME_V2[0];
                    }
                    else if(ptrPlateforme->ID==2)
                    {
                        ptrPlateforme->ptrPosition=&anim_PLATEFORME_H1[0];
                    }
                    else if(ptrPlateforme->ID==7)
                    {
                        ptrPlateforme->ptrPosition=&anim_PLATEFORME_H2[0];
                    }


                    IndexCreaPlateformes++;
                    nb_Plateformes+=1;
                    break;
                }

            }
        }

        // On remet le compteur entre 0 et 7
        compteurTile = delta;
    }
}

void Mvt_Ennemis_Niveau1()
{
    if(CamPosX>-4336)
    {
        u8 i;

        /////////////////
        //   ENNEMIS   //
        /////////////////

        for(i=0;i<MAX_ENNEMIS;i++)
        {
            SpriteEnnemi_ *ptrEnnemi=&Ennemi[i];

            //--------------------------//
            //      SI SPRITE CREE      //
            //--------------------------//
            if(ptrEnnemi->Init==1)
            {
                // TYPE D'ENNEMI //
                switch(ptrEnnemi->ID)
                {
                    
                    //////////////////////////////////////
                    //                                  //
                    //           ESCARGOTS H            //
                    //                                  //
                    //////////////////////////////////////
                    case 1:

                        //----------------------//
                        //      POSITION X      //
                        //----------------------//
                        ptrEnnemi->PosX-=vitesseScrolling;
                        
                        //----------------------------//
                        //      SI ENNEMI VIVANT      //
                        //----------------------------//
                        if(ptrEnnemi->Etat == 1)
                        {
                            //--------------------------//
                            //      ANIM DES TILES      //
                            //--------------------------//
                            ptrEnnemi->CompteurFrame+=1;

                            // MAJ des tiles toutes les 8 images (0 à 7)
                            if(ptrEnnemi->CompteurFrame>7)
                            {
                                ptrEnnemi->CompteurFrame-=8;
                                ptrEnnemi->IndexFrame+=1;

                                // Cycle de FRAME de 0 à 12 (13 étapes)
                                if(ptrEnnemi->IndexFrame>12)
                                {
                                    ptrEnnemi->IndexFrame=0;
                                }

                                SPR_setFrame(ptrEnnemi->SpriteE,(s16)ptrEnnemi->IndexFrame);
                            }
                        }

                        //--------------------------//
                        //      SI ENNEMI MORT      //
                        //--------------------------//
                        else
                        {
                            //----------------------//
                            //      POSITION Y      //
                            //----------------------//
                            ptrEnnemi->PosY += *(ptrEnnemi->ptrPosition);
                            ptrEnnemi->ptrPosition++;

                            if(ptrEnnemi->ptrPosition > &anim_CHUTE_ENNEMIS[MAX_ETAPES_CHUTE_ENNEMI])
                            {
                                ptrEnnemi->ptrPosition = &anim_CHUTE_ENNEMIS[MAX_ETAPES_CHUTE_ENNEMI];
                            }
                        }

                        SPR_setPosition(ptrEnnemi->SpriteE, ptrEnnemi->PosX, ptrEnnemi->PosY);

                        // Si l'ennemi sort de l'écran
                        // 3 tiles (24 px) de large
                        if(ptrEnnemi->PosX < -ptrEnnemi->Largeur || ptrEnnemi->PosY > 224 )
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                            nb_Ennemis-=1;
                        }
                        break;

                    //////////////////////////////////////
                    //                                  //
                    //              BULOTS              //
                    //                                  //
                    //////////////////////////////////////
                    case 2:

                        //----------------------//
                        //      POSITION X      //
                        //----------------------//
                        if(ptrEnnemi->CompteurPosition==0)
                        {
                            ptrEnnemi->PosX-=(vitesseScrolling);
                        }
                        else if(ptrEnnemi->CompteurPosition==1)
                        {
                            ptrEnnemi->PosX-=(vitesseScrolling+1);
                        }

                        ptrEnnemi->CompteurPosition++;

                        if(ptrEnnemi->CompteurPosition==2)
                        {
                            ptrEnnemi->CompteurPosition=0;
                        }

                        //----------------------------//
                        //      SI ENNEMI VIVANT      //
                        //----------------------------//
                        if(ptrEnnemi->Etat == 1)
                        {
                            //--------------------------//
                            //      ANIM DES TILES      //
                            //--------------------------//
                            ptrEnnemi->CompteurFrame+=1;

                            // MAJ des tiles toutes les 6 images (0 à 5)
                            if(ptrEnnemi->CompteurFrame>5)
                            {
                                ptrEnnemi->CompteurFrame-=6;
                                ptrEnnemi->IndexFrame+=1;

                                // Cycle de FRAME de 0 à 11 (12 étapes)
                                if(ptrEnnemi->IndexFrame>11)
                                {
                                    ptrEnnemi->IndexFrame=0;
                                }

                                SPR_setFrame(ptrEnnemi->SpriteE,(s16)ptrEnnemi->IndexFrame);
                            }
                        }

                        //--------------------------//
                        //      SI ENNEMI MORT      //
                        //--------------------------//
                        else
                        {
                            //----------------------//
                            //      POSITION Y      //
                            //----------------------//
                            ptrEnnemi->PosY += *(ptrEnnemi->ptrPosition);
                            ptrEnnemi->ptrPosition++;

                            if(ptrEnnemi->ptrPosition > &anim_CHUTE_ENNEMIS[MAX_ETAPES_CHUTE_ENNEMI])
                            {
                                ptrEnnemi->ptrPosition = &anim_CHUTE_ENNEMIS[MAX_ETAPES_CHUTE_ENNEMI];
                            }
                        }

                        SPR_setPosition(ptrEnnemi->SpriteE, ptrEnnemi->PosX, ptrEnnemi->PosY);

                        // Si l'ennemi sort de l'écran
                        // 3 tiles (24 px) de large
                        if(ptrEnnemi->PosX < -ptrEnnemi->Largeur || ptrEnnemi->PosY > 224 )
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                            nb_Ennemis-=1;
                        }
                        break;

                    //////////////////////////////////////
                    //                                  //
                    //           ESCARGOTS V            //
                    //                                  //
                    //////////////////////////////////////
                    case 3:

                        //----------------------//
                        //      POSITION X      //
                        //----------------------//
                        ptrEnnemi->PosX-=vitesseScrolling;

                        //----------------------------//
                        //      SI ENNEMI VIVANT      //
                        //----------------------------//
                        if(ptrEnnemi->Etat == 1)
                        {
                            ptrEnnemi->CompteurPosition+=1;

                            //----------------------//
                            //      POSITION X      //
                            //----------------------//
                            // Orienté vers le bas
                            if(ptrEnnemi->Axe==0)
                            {
                                if(ptrEnnemi->CompteurPosition>79)
                                {
                                    ptrEnnemi->CompteurPosition=0;
                                    ptrEnnemi->Axe=1;
                                    SPR_setVFlip(ptrEnnemi->SpriteE, TRUE);
                                }
                                else
                                {
                                    if(ptrEnnemi->CompteurPosition%2==0)
                                    {
                                        ptrEnnemi->PosY+=1;
                                    }
                                }
                            }
                            // Orienté vers le haut
                            else if(ptrEnnemi->Axe==1)
                            {
                                if(ptrEnnemi->CompteurPosition>79)
                                {
                                    ptrEnnemi->CompteurPosition=0;
                                    ptrEnnemi->Axe=0;
                                    SPR_setVFlip(ptrEnnemi->SpriteE, FALSE);
                                }
                                else
                                {
                                    if(ptrEnnemi->CompteurPosition%2==0)
                                    {
                                        ptrEnnemi->PosY-=1;
                                    }
                                }
                            }

                            //--------------------------//
                            //      ANIM DES TILES      //
                            //--------------------------//
                            ptrEnnemi->CompteurFrame+=1;

                            // MAJ des tiles toutes les 8 images (0 à 7)
                            if(ptrEnnemi->CompteurFrame>7)
                            {
                                ptrEnnemi->CompteurFrame-=8;
                                ptrEnnemi->IndexFrame+=1;

                                // Cycle de FRAME de 0 à 12 (13 étapes)
                                if(ptrEnnemi->IndexFrame>12)
                                {
                                    ptrEnnemi->IndexFrame=0;
                                }

                                SPR_setFrame(ptrEnnemi->SpriteE,(s16)ptrEnnemi->IndexFrame);
                            }
                        }

                        //--------------------------//
                        //      SI ENNEMI MORT      //
                        //--------------------------//
                        else
                        {
                            //----------------------//
                            //      POSITION Y      //
                            //----------------------//
                            ptrEnnemi->PosY += *(ptrEnnemi->ptrPosition);
                            ptrEnnemi->ptrPosition++;

                            if(ptrEnnemi->ptrPosition > &anim_CHUTE_ENNEMIS[MAX_ETAPES_CHUTE_ENNEMI])
                            {
                                ptrEnnemi->ptrPosition = &anim_CHUTE_ENNEMIS[MAX_ETAPES_CHUTE_ENNEMI];
                            }
                        }

                        SPR_setPosition(ptrEnnemi->SpriteE, ptrEnnemi->PosX, ptrEnnemi->PosY);

                        // Si l'ennemi sort de l'écran
                        // 3 tiles (24 px) de large
                        if(ptrEnnemi->PosX < -ptrEnnemi->Largeur || ptrEnnemi->PosY > 224 )
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                            nb_Ennemis-=1;
                        }
                        break;

                    //////////////////////////////////////
                    //                                  //
                    //              MORSE               //
                    //                                  //
                    //////////////////////////////////////
                    case 4:

                        //----------------------//
                        //      POSITION X      //
                        //----------------------//
                        ptrEnnemi->PosX -= vitesseScrolling;

                        //----------------------------//
                        //      SI ENNEMI VIVANT      //
                        //----------------------------//
                        if(ptrEnnemi->Etat == 1)
                        {
                            /*
                            //--------------------------//
                            //      ANIM DES TILES      //
                            //--------------------------//
                            ptrEnnemi->CompteurFrame+=1;

                            // MAJ des tiles toutes les 8 images (0 à 7)
                            if(ptrEnnemi->CompteurFrame==8)
                            {
                                ptrEnnemi->CompteurFrame=0;
                                ptrEnnemi->IndexFrame+=1;

                                // Cycle de FRAME de 0 à 12 (13 étapes)
                                if(ptrEnnemi->IndexFrame==13)
                                {
                                    ptrEnnemi->IndexFrame=0;
                                }

                                SPR_setFrame(ptrEnnemi->SpriteE,(s16)ptrEnnemi->IndexFrame);
                            }*/
                        }

                        //--------------------------//
                        //      SI ENNEMI MORT      //
                        //--------------------------//
                        else
                        {
                            //----------------------//
                            //      POSITION Y      //
                            //----------------------//
                            ptrEnnemi->PosY += *(ptrEnnemi->ptrPosition);
                            ptrEnnemi->ptrPosition++;

                            if(ptrEnnemi->ptrPosition > &anim_CHUTE_ENNEMIS[MAX_ETAPES_CHUTE_ENNEMI])
                            {
                                ptrEnnemi->ptrPosition = &anim_CHUTE_ENNEMIS[MAX_ETAPES_CHUTE_ENNEMI];
                            }
                        }

                        SPR_setPosition(ptrEnnemi->SpriteE, ptrEnnemi->PosX, ptrEnnemi->PosY);

                        // Si l'ennemi sort de l'écran
                        // 6 tiles (48 px) de large
                        if(ptrEnnemi->PosX < -ptrEnnemi->Largeur || ptrEnnemi->PosY > 224)
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                            nb_Ennemis-=1;
                        }
                        break;

                    //////////////////////////////////////
                    //                                  //
                    //             POULPE 1             //
                    //                                  //
                    //////////////////////////////////////
                    case 5:

                        //----------------------------//
                        //      SI ENNEMI VIVANT      //
                        //----------------------------//
                        if(ptrEnnemi->Etat == 1)
                        {
                            //----------------------//
                            //      POSITION X      //
                            //----------------------//
                            ptrEnnemi->PosX -= vitesseScrolling;

                            //----------------------//
                            //      POSITION Y      //
                            //----------------------//                            
                            ptrEnnemi->PosY += *(ptrEnnemi->ptrPosition);

                            ptrEnnemi->ptrPosition++;

                            if(ptrEnnemi->ptrPosition >= &anim_POULPE1[MAX_ETAPES_POULPE1])
                            {
                                ptrEnnemi->ptrPosition=&anim_POULPE1[0];
                            }

                            SPR_setPosition(ptrEnnemi->SpriteE, ptrEnnemi->PosX, ptrEnnemi->PosY);
                            /*
                            //--------------------------//
                            //      ANIM DES TILES      //
                            //--------------------------//
                            ptrEnnemi->CompteurFrame+=1;

                            // MAJ des tiles toutes les 8 images (0 à 7)
                            if(ptrEnnemi->CompteurFrame==8)
                            {
                                ptrEnnemi->CompteurFrame=0;
                                ptrEnnemi->IndexFrame+=1;

                                // Cycle de FRAME de 0 à 12 (13 étapes)
                                if(ptrEnnemi->IndexFrame==13)
                                {
                                    ptrEnnemi->IndexFrame=0;
                                }

                                SPR_setFrame(ptrEnnemi->SpriteE,(s16)ptrEnnemi->IndexFrame);
                            }*/
                        }

                        //--------------------------//
                        //      SI ENNEMI MORT      //
                        //--------------------------//
                        else
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                            nb_Ennemis-=1;
                        }

                        // Si l'ennemi sort de l'écran
                        // 4 tiles (32 px) de large
                        if(ptrEnnemi->PosX < -ptrEnnemi->Largeur || ptrEnnemi->PosY > 224)
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                            nb_Ennemis-=1;
                        }
                        break;


                    //////////////////////////////////////
                    //                                  //
                    //             POULPE 2             //
                    //                                  //
                    //////////////////////////////////////
                    case 6:

                        //----------------------//
                        //      POSITION X      //
                        //----------------------//
                        ptrEnnemi->PosX -= vitesseScrolling;

                        //----------------------------//
                        //      SI ENNEMI VIVANT      //
                        //----------------------------//
                        if(ptrEnnemi->Etat == 1)
                        {
                            //----------------------//
                            //      POSITION Y      //
                            //----------------------//
                            ptrEnnemi->PosY += *(ptrEnnemi->ptrPosition);

                            ptrEnnemi->ptrPosition++;

                            if(ptrEnnemi->ptrPosition >= &anim_POULPE2[MAX_ETAPES_POULPE2])
                            {
                                ptrEnnemi->ptrPosition=&anim_POULPE2[0];
                            }

                            SPR_setPosition(ptrEnnemi->SpriteE, ptrEnnemi->PosX, ptrEnnemi->PosY);
                            /*
                            //--------------------------//
                            //      ANIM DES TILES      //
                            //--------------------------//
                            ptrEnnemi->CompteurFrame+=1;

                            // MAJ des tiles toutes les 8 images (0 à 7)
                            if(ptrEnnemi->CompteurFrame==8)
                            {
                                ptrEnnemi->CompteurFrame=0;
                                ptrEnnemi->IndexFrame+=1;

                                // Cycle de FRAME de 0 à 12 (13 étapes)
                                if(ptrEnnemi->IndexFrame==13)
                                {
                                    ptrEnnemi->IndexFrame=0;
                                }

                                SPR_setFrame(ptrEnnemi->SpriteE,(s16)ptrEnnemi->IndexFrame);
                            }*/
                        }

                        //--------------------------//
                        //      SI ENNEMI MORT      //
                        //--------------------------//
                        else
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                            nb_Ennemis-=1;
                        }

                        // Si l'ennemi sort de l'écran
                        // 4 tiles (32 px) de large
                        if(ptrEnnemi->PosX < -ptrEnnemi->Largeur || ptrEnnemi->PosY > 224)
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                            nb_Ennemis-=1;
                        }
                        break;


                    //////////////////////////////////////
                    //                                  //
                    //              PELICANS            //
                    //                                  //
                    //////////////////////////////////////
                    case 7:

                        //----------------------------//
                        //      SI ENNEMI VIVANT      //
                        //----------------------------//
                        if(ptrEnnemi->Etat == 1)
                        {

                            //----------------------//
                            //      POSITION X      //
                            //----------------------//
                            if(ptrEnnemi->CompteurPosition==0)
                            {
                                ptrEnnemi->PosX-=(vitesseScrolling);
                            }
                            else if(ptrEnnemi->CompteurPosition==1)
                            {
                                ptrEnnemi->PosX-=(vitesseScrolling+1);
                            }

                            ptrEnnemi->CompteurPosition++;

                            if(ptrEnnemi->CompteurPosition==2)
                            {
                                ptrEnnemi->CompteurPosition=0;
                            }

                            SPR_setPosition(ptrEnnemi->SpriteE, ptrEnnemi->PosX, ptrEnnemi->PosY);
                            
                            //--------------------------//
                            //      ANIM DES TILES      //
                            //--------------------------//
                            ptrEnnemi->CompteurFrame+=1;

                            // MAJ des tiles toutes les 8 images (0 à 7)
                            if(ptrEnnemi->CompteurFrame>7)
                            {
                                ptrEnnemi->CompteurFrame-=8;
                                ptrEnnemi->IndexFrame+=1;

                                // Cycle de FRAME de 0 à 11 (12 étapes)
                                if(ptrEnnemi->IndexFrame>11)
                                {
                                    ptrEnnemi->IndexFrame=0;
                                }

                                SPR_setFrame(ptrEnnemi->SpriteE,(s16)ptrEnnemi->IndexFrame);
                            }
                        }

                        //--------------------------//
                        //      SI ENNEMI MORT      //
                        //--------------------------//
                        else
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                            nb_Ennemis-=1;
                        }

                        // Si l'ennemi sort de l'écran
                        // 3 tiles (24 px) de large
                        if( ptrEnnemi->PosX < -ptrEnnemi->Largeur || ptrEnnemi->PosY > 224 )
                        {
                            SPR_releaseSprite( ptrEnnemi->SpriteE );
                            ptrEnnemi->Init = 0;
                            nb_Ennemis -= 1;
                        }
                        break;
                    
                }

            }
        }
    }
 
    //////////////////
    //    DRAGON    //
    //////////////////
    SpriteDragon_ *ptrDragon=&Dragon;

    if(ptrDragon->Phase==SORTIE_DRAGON)
    {
        ptrDragon->PosY-=1;

        if(ptrDragon->PosY==0)
        {
            ptrDragon->Phase=ATTENTE_DRAGON;
            ptrDragon->CompteurFrameVol=0;
            ptrDragon->IndexFrameVol=0;
            ptrDragon->PosX=10;
            ptrDragon->PosY=-32;

            // CHANGEMENT PALETTE JOUEUR //
            PAL_setColor( 10 , 0x000C );
            PAL_setColor( 13 , 0x06CC );
        }
    }

    ///////////////////
    //    IMPACTS    //
    ///////////////////
    if( Nb_Impacts != 0 )
    {
        u8 i;
        
        for( i=0 ; i<MAX_IMPACTS ; i++)
        {
            SpriteImpact_ *ptrImpact=&Impacts[i];

            if( ptrImpact->Init == 1 )
            {
                //--------------------------//
                //      ANIM DES TILES      //
                //--------------------------//
                ptrImpact->CompteurFrame+=1;

                // MAJ des tiles toutes les 4 images (0 à 3)
                if(ptrImpact->CompteurFrame>3)
                {
                    ptrImpact->CompteurFrame-=0;
                    ptrImpact->IndexFrame+=1;

                    SPR_setFrame(ptrImpact->SpriteI,(s16)ptrImpact->IndexFrame);

                    // Cycle de FRAME de 0 à 2 (3 étapes)
                    if(ptrImpact->IndexFrame>2)
                    {
                        ptrImpact->IndexFrame=0;
                        ptrImpact->Init=0;

                        SPR_releaseSprite(ptrImpact->SpriteI);
                    }
                }
            }
        }
    }

    //////////////////////////////
    //    EXPLOSIONS ENNEMIS    //
    //////////////////////////////
    if( Nb_ExploEnnemis != 0 )
    {
        u8 i;
        
        for( i=0 ; i<MAX_IMPACTS ; i++)
        {
            SpriteExploEnnemi_ *ptrExploEnnemi=&ExploEnnemis[i];

            if( ptrExploEnnemi->Init == 1 )
            {
                //--------------------------//
                //      ANIM DES TILES      //
                //--------------------------//
                ptrExploEnnemi->CompteurFrame+=1;

                // MAJ des tiles toutes les 2 images (0 à 1)
                if(ptrExploEnnemi->CompteurFrame>1)
                {
                    ptrExploEnnemi->CompteurFrame-=0;
                    ptrExploEnnemi->IndexFrame+=1;

                    SPR_setFrame(ptrExploEnnemi->SpriteEE,(s16)ptrExploEnnemi->IndexFrame);

                    // Cycle de FRAME de 0 à 7 (8 étapes)
                    if(ptrExploEnnemi->IndexFrame>7)
                    {
                        ptrExploEnnemi->IndexFrame=0;
                        ptrExploEnnemi->Init=0;

                        SPR_releaseSprite(ptrExploEnnemi->SpriteEE);
                    }
                }
            }
        }
    }
}

void MvtPlateformes_Niveau1()
{
    if(CamPosX>-4336)
    {
        u8 i;

        /////////////////////
        //   PLATEFORMES   //
        /////////////////////

        for(i=0;i<MAX_PLATEFORMES;i++)
        {
            SpritePlateforme_ *ptrPlateforme=&Plateforme[i];

            // Si le sprite a été créé
            if(ptrPlateforme->Init==1)
            {
                // On vérifie le type de plateforme
                switch(ptrPlateforme->ID)
                {
                    ///////////////////////////////////////
                    // PLATEFORME VERTICALE VERS LE HAUT //
                    ///////////////////////////////////////
                    case 1:
                        // Position X //
                        ptrPlateforme->PosX-=vitesseScrolling;

                        // POSITION Y //
                        ptrPlateforme->PosY += *(ptrPlateforme->ptrPosition);
                        ptrPlateforme->ptrPosition++;

                        if(ptrPlateforme->ptrPosition >= &anim_PLATEFORME_V1[MAX_ETAPES_PF_V1])
                        {
                            ptrPlateforme->ptrPosition=&anim_PLATEFORME_V1[0];
                        }

                        SPR_setPosition(ptrPlateforme->SpriteP, ptrPlateforme->PosX, ptrPlateforme->PosY);

                        ptrPlateforme->pt_Coll1_X=ptrPlateforme->PosX;
                        ptrPlateforme->pt_Coll1_Y=ptrPlateforme->PosY;
                        ptrPlateforme->pt_Coll2_X=ptrPlateforme->PosX+63;
                        ptrPlateforme->pt_Coll2_Y=ptrPlateforme->pt_Coll1_Y;

                        // Si la plateforme sort de l'écran
                        // 8 tiles (64 px) de large
                        if(ptrPlateforme->PosX<-64)
                        {
                            SPR_releaseSprite(ptrPlateforme->SpriteP);
                            ptrPlateforme->Init=0;
                            nb_Plateformes-=1;
                        }
                        break;

                    ////////////////////////////
                    // PLATEFORME HORIZONTALE //
                    ////////////////////////////
                    case 2:
                        // POSITION X //
                        ptrPlateforme->PosX-=vitesseScrolling;

                        // POSITION Y //                       
                        ptrPlateforme->ptrPosition++;

                        if(ptrPlateforme->ptrPosition >= &anim_PLATEFORME_H1[MAX_ETAPES_PF_H1])
                        {
                            ptrPlateforme->ptrPosition=&anim_PLATEFORME_H1[0];
                        }

                        ptrPlateforme->PosX += *(ptrPlateforme->ptrPosition);


                        SPR_setPosition(ptrPlateforme->SpriteP, ptrPlateforme->PosX, ptrPlateforme->PosY);

                        ptrPlateforme->pt_Coll1_X=ptrPlateforme->PosX;
                        ptrPlateforme->pt_Coll1_Y=ptrPlateforme->PosY;
                        ptrPlateforme->pt_Coll2_X=ptrPlateforme->PosX+63;
                        ptrPlateforme->pt_Coll2_Y=ptrPlateforme->pt_Coll1_Y;

                        // Si la plateforme sort de l'écran
                        // 8 tiles (64 px) de large
                        if(ptrPlateforme->PosX<-64)
                        {
                            SPR_releaseSprite(ptrPlateforme->SpriteP);
                            ptrPlateforme->Init=0;
                            nb_Plateformes-=1;
                        }
                        break;

                    //////////////////////////////////////////////////////
                    // PLATEFORME VERTICALE VERS LE BAS (DECLENCHEMENT) //
                    //////////////////////////////////////////////////////
                    case 3:
                        // Position X
                        ptrPlateforme->PosX-=vitesseScrolling;

                        // POSITION Y
                        // SI LA PLATEFORME S'EST DECLENCHEE //
                        if(ptrPlateforme->Declencheur==1)
                        {
                            // POSITION Y
                            ptrPlateforme->PosY -= *(ptrPlateforme->ptrPosition);

                            ptrPlateforme->ptrPosition++;

                            if(ptrPlateforme->ptrPosition >= &anim_PLATEFORME_V1[MAX_ETAPES_PF_V1])
                            {
                                ptrPlateforme->ptrPosition=&anim_PLATEFORME_V1[0];
                            }
                        }

                        SPR_setPosition(ptrPlateforme->SpriteP, ptrPlateforme->PosX, ptrPlateforme->PosY);

                        ptrPlateforme->pt_Coll1_X=ptrPlateforme->PosX;
                        ptrPlateforme->pt_Coll1_Y=ptrPlateforme->PosY;
                        ptrPlateforme->pt_Coll2_X=ptrPlateforme->PosX+63;
                        ptrPlateforme->pt_Coll2_Y=ptrPlateforme->pt_Coll1_Y;

                        // Si la plateforme sort de l'écran
                        // 8 tiles (64 px) de large
                        if(ptrPlateforme->PosX<-64)
                        {
                            SPR_releaseSprite(ptrPlateforme->SpriteP);
                            ptrPlateforme->Init=0;
                            nb_Plateformes-=1;
                        }
                        break;

                    ///////////////////////////////////////////////////////
                    // PLATEFORME VERTICALE VERS LE HAUT (DECLENCHEMENT) //
                    ///////////////////////////////////////////////////////
                    case 4:
                        // POSITION X //
                        ptrPlateforme->PosX-=vitesseScrolling;

                        // POSITION Y //
                        // SI LA PLATEFORME S'EST DECLENCHEE //
                        if(ptrPlateforme->Declencheur==1)
                        {
                            // POSITION Y
                            ptrPlateforme->PosY += *(ptrPlateforme->ptrPosition);

                            ptrPlateforme->ptrPosition++;

                            if(ptrPlateforme->ptrPosition >= &anim_PLATEFORME_V1[MAX_ETAPES_PF_V1])
                            {
                                ptrPlateforme->ptrPosition=&anim_PLATEFORME_V1[0];
                            }
                        }

                        SPR_setPosition(ptrPlateforme->SpriteP, ptrPlateforme->PosX, ptrPlateforme->PosY);

                        ptrPlateforme->pt_Coll1_X=ptrPlateforme->PosX;
                        ptrPlateforme->pt_Coll1_Y=ptrPlateforme->PosY;
                        ptrPlateforme->pt_Coll2_X=ptrPlateforme->PosX+63;
                        ptrPlateforme->pt_Coll2_Y=ptrPlateforme->pt_Coll1_Y;

                        // Si la plateforme sort de l'écran
                        // 8 tiles (64 px) de large
                        if(ptrPlateforme->PosX<-64)
                        {
                            SPR_releaseSprite(ptrPlateforme->SpriteP);
                            ptrPlateforme->Init=0;
                            nb_Plateformes-=1;
                        }
                        break;

                    /////////////////////////////////
                    // PLATEFORME VERTICALE RAPIDE //
                    /////////////////////////////////
                    case 5:
                        // POSITION X //
                        ptrPlateforme->PosX-=vitesseScrolling;

                        // POSITION Y //
                        ptrPlateforme->PosY += *(ptrPlateforme->ptrPosition);

                        ptrPlateforme->ptrPosition++;

                        if(ptrPlateforme->ptrPosition >= &anim_PLATEFORME_V2[MAX_ETAPES_PF_V2])
                        {
                            ptrPlateforme->ptrPosition=&anim_PLATEFORME_V2[0];
                        }

                        SPR_setPosition(ptrPlateforme->SpriteP, ptrPlateforme->PosX, ptrPlateforme->PosY);

                        ptrPlateforme->pt_Coll1_X=ptrPlateforme->PosX;
                        ptrPlateforme->pt_Coll1_Y=ptrPlateforme->PosY;
                        ptrPlateforme->pt_Coll2_X=ptrPlateforme->PosX+63;
                        ptrPlateforme->pt_Coll2_Y=ptrPlateforme->pt_Coll1_Y;

                        // Si la plateforme sort de l'écran
                        // 8 tiles (64 px) de large
                        if(ptrPlateforme->PosX<-64)
                        {
                            SPR_releaseSprite(ptrPlateforme->SpriteP);
                            ptrPlateforme->Init=0;
                            nb_Plateformes-=1;
                        }
                        break;

                    /////////////////////////////////////
                    // PLATEFORME VERTICAL VERS LE BAS //
                    /////////////////////////////////////
                    case 6:
                        // Position X //
                        ptrPlateforme->PosX-=vitesseScrolling;

                        // POSITION Y //
                        ptrPlateforme->PosY -= *(ptrPlateforme->ptrPosition);

                        ptrPlateforme->ptrPosition++;

                        if(ptrPlateforme->ptrPosition >= &anim_PLATEFORME_V1[MAX_ETAPES_PF_V1])
                        {
                            ptrPlateforme->ptrPosition=&anim_PLATEFORME_V1[0];
                        }

                        SPR_setPosition(ptrPlateforme->SpriteP, ptrPlateforme->PosX, ptrPlateforme->PosY);

                        ptrPlateforme->pt_Coll1_X=ptrPlateforme->PosX;
                        ptrPlateforme->pt_Coll1_Y=ptrPlateforme->PosY;
                        ptrPlateforme->pt_Coll2_X=ptrPlateforme->PosX+63;
                        ptrPlateforme->pt_Coll2_Y=ptrPlateforme->pt_Coll1_Y;

                        // Si la plateforme sort de l'écran
                        // 8 tiles (64 px) de large
                        if(ptrPlateforme->PosX<-64)
                        {
                            SPR_releaseSprite(ptrPlateforme->SpriteP);
                            ptrPlateforme->Init=0;
                            nb_Plateformes-=1;
                        }
                        break;

                    ////////////////////////////////////////////
                    // PLATEFORME HORIZONTALE (DECLENCHEMENT) //
                    ////////////////////////////////////////////
                    case 7:
                        // POSITION X //
                        ptrPlateforme->PosX-=vitesseScrolling;

                        // SI LA PLATEFORME S'EST DECLENCHEE //
                        if(ptrPlateforme->Declencheur==1)
                        {
                            // POSITION Y //                       
                            ptrPlateforme->ptrPosition++;

                            if(ptrPlateforme->ptrPosition >= &anim_PLATEFORME_H2[MAX_ETAPES_PF_H2])
                            {
                                ptrPlateforme->ptrPosition=&anim_PLATEFORME_H2[0];
                            }
                        }

                        ptrPlateforme->PosX += *(ptrPlateforme->ptrPosition);

                        SPR_setPosition(ptrPlateforme->SpriteP, ptrPlateforme->PosX, ptrPlateforme->PosY);

                        ptrPlateforme->pt_Coll1_X=ptrPlateforme->PosX;
                        ptrPlateforme->pt_Coll1_Y=ptrPlateforme->PosY;
                        ptrPlateforme->pt_Coll2_X=ptrPlateforme->PosX+63;
                        ptrPlateforme->pt_Coll2_Y=ptrPlateforme->pt_Coll1_Y;

                        // Si la plateforme sort de l'écran
                        // 8 tiles (64 px) de large
                        if(ptrPlateforme->PosX<-64)
                        {
                            SPR_releaseSprite(ptrPlateforme->SpriteP);
                            ptrPlateforme->Init=0;
                            nb_Plateformes-=1;
                        }
                        break;

                }
            }
        }
    }

    //////////////////
    //    DRAGON    //
    //////////////////
    SpriteDragon_ *ptrDragon=&Dragon;

    if(ptrDragon->Phase==SORTIE_DRAGON)
    {
        ptrDragon->PosY-=1;

        if(ptrDragon->PosY==0)
        {
            ptrDragon->Phase=ATTENTE_DRAGON;
            ptrDragon->CompteurFrameVol=0;
            ptrDragon->IndexFrameVol=0;
            ptrDragon->PosX=10;
            ptrDragon->PosY=-32;

            // CHANGEMENT PALETTE JOUEUR //
            PAL_setColor( 10 , 0x000C );
            PAL_setColor( 13 , 0x06CC );
        }
    }

}


//-----------------------------------------------//
//                      TIRS                     //
//-----------------------------------------------//
void CreaTirBalle()
{
    u8 i;

    if( Nb_Balles < MAX_BALLES )
    {       
        for( i=0 ; i<Nb_Balles+1 ; i++ )
        {
            SpriteBalle_ *ptrBalle=&Balles[i];
            SpriteJoueur_ *ptrJoueur=&Joueur;
            
            if( ptrBalle->Init == 0 )
            {
                ptrBalle->Init = 1;
                ptrBalle->Axe = ptrJoueur->Axe;

                ptrBalle->Largeur = 8;
                ptrBalle->Hauteur = 8;

                ptrBalle->PosX = ptrJoueur->PosX + 24;
                ptrBalle->PosY = ptrJoueur->PosY - 12;

                ptrBalle->SpriteB = SPR_addSprite( &tiles_Sprite_BALLE , ptrBalle->PosX, ptrBalle->PosY , TILE_ATTR ( PAL0 , FALSE , FALSE , FALSE ) );
                SPR_setDepth(ptrBalle->SpriteB,14);

                Nb_Balles += 1;
                Nb_Projectiles += 1;

                break;
            }   
        }
    }
    /*
    else if( Nb_Balles == MAX_BALLES )
    {
        //
    }*/
}

void CreaTirShuriken()
{
    //
}

void CreaTirBoule()
{
    //
}

void CreaTirBouleFeu()
{
    //
}

void CreaTirLaser()
{
    //
}



void TirJoueur()
{
    switch (ID_Arme)
    {
        case 0:

        CreaTirBalle();
        return;
    }
}

//void (*TabCreaTir[5])()={CreaTirBalle,CreaTirShuriken,CreaTirBoule,CreaTirBouleFeu,CreaTirLaser};



/*
void MvtTirBase()
{
    //
}

void MvtTirShuriken()
{
    //
}

void MvtTirBoule()
{
    //
}

void MvtTirBouleFeu()
{
    //
}

void MvtTirLaser()
{
    //
}
*/
//void (*TabMvtTir[5])()={MvtTirBase,MvtTirShuriken,MvtTirBoule,MvtTirBouleFeu,MvtTirLaser};


void Mvt_TirJoueur()
{
    // Si au moins 1 projectile existe //
    if( Nb_Projectiles != 0 )
    {
        u8 i;
        //u8 e;
        
        // Si au moins 1 balle existe //
        if( Nb_Balles != 0 )
        {
            for( i=0 ; i<MAX_BALLES ; i++)
            {
                // Pointeur sur le tableau de balles //
                SpriteBalle_ *ptrBalle=&Balles[i];

                // Si balle créée //
                if( ptrBalle->Init == 1)
                {
                    // Vers la droite //
                    if( ptrBalle->Axe == 0 )
                    {
                        ptrBalle->PosX += 6;                       
                    }

                    // Vers la gauche //
                    else
                    {
                        ptrBalle->PosX -= 6;
                    }

                    SPR_setPosition(ptrBalle->SpriteB, ptrBalle->PosX, ptrBalle->PosY);
                
                    //----------------------------------------------------------//
                    //          TEST COLLISION PROJECTILE --> ENNEMI            //
                    //----------------------------------------------------------// 
                    if( nb_Ennemis != 0 )
                    {
                        Collision_Tir_Joueur_Ennemis(ptrBalle , ptrBalle->Largeur);
                    }

                    // Sortie écran //
                    if( ptrBalle->PosX > 320 || ptrBalle->PosX < -8 )
                    {
                        //------------------------------//
                        //          SECURITE            //
                        //------------------------------// 

                        // SI LE SPRITE N'A PAS ETE SUPPRIME DANS LA COLLISION AVEC UN ENNEMI //                       
                        if( ptrBalle->Init == 1 )
                        {
                            ptrBalle->Init = 0;
                            SPR_releaseSprite(ptrBalle->SpriteB);

                            Nb_Projectiles -= 1;
                            Nb_Balles -= 1;
                        }
                    }
                }
            }
        }
    }
}


//-----------------------------------------------//
//                     JOUEUR                    //
//-----------------------------------------------//
void Phases_Joueur()
{
    // Gestion manette
	u16 value=JOY_readJoypad(JOY_1);

    SpriteJoueur_ *ptrJoueur=&Joueur;
    //SpriteDragon_ *ptrDragon=&Dragon;

    // If player reaches the end of the level, he goes to the right //
    if(CamPosX <= -4336)
    {
        value |= BUTTON_RIGHT;

        ////////////////
        //   DROITE   //
        ////////////////
        // Si joueur à l'arrêt
        if(ptrJoueur->Phase==ARRET)
        {
            ptrJoueur->Axe=0;
            ptrJoueur->Phase=MARCHE;
        }
        // Si le joueur marche vers la gauche
        else if(ptrJoueur->Phase==MARCHE && ptrJoueur->Axe==1)
        {
            ptrJoueur->Axe=0;
        }
    }

    // Else, the joypad drives the player //
    else
    {
        ///////////////
        //   ARRET   //
        ///////////////
        if((value & BUTTON_DIR)==0)
        {
            if(ptrJoueur->Phase!=SAUT && ptrJoueur->Phase!=TIR && ptrJoueur->Phase!=SAUT_TIR && ptrJoueur->Phase!=CHUTE && ptrJoueur->Phase!=CHUTE_TIR && ptrJoueur->Phase!=TOUCHE && ptrJoueur->Phase!=APPARITION)
            {
                ptrJoueur->Phase=ARRET;
            }
        }

        ////////////////
        //   DROITE   //
        ////////////////
        else if(value & BUTTON_RIGHT)
        {
            // Si joueur à l'arrêt
            if(ptrJoueur->Phase==ARRET)
            {
                ptrJoueur->Axe=0;
                ptrJoueur->Phase=MARCHE;
            }
            // Si le joueur marche vers la gauche
            else if(ptrJoueur->Phase==MARCHE && ptrJoueur->Axe==1)
            {
                ptrJoueur->Axe=0;
            }
        }

        ////////////////
        //   GAUCHE   //
        ////////////////
        else if(value & BUTTON_LEFT)
        {
            // Si joueur à l'arrêt
            if(ptrJoueur->Phase==ARRET)
            {
                ptrJoueur->Axe=1;
                ptrJoueur->Phase=MARCHE;
            }
            // Si le joueur marche vers la droite
            else if(ptrJoueur->Phase==MARCHE && ptrJoueur->Axe==0)
            {
                ptrJoueur->Axe=1;
            }
        }

        ///////////////////////
        //    HAUT OU BAS    //
        ///////////////////////
        else if(value & (BUTTON_UP | BUTTON_DOWN))
        {
            // Si joueur marche
            if(ptrJoueur->Phase==MARCHE)
            {
                ptrJoueur->Phase=ARRET;
            }
        }
    }  
}

void MvtJoueur()
{
    // Gestion manette
	u16 value=JOY_readJoypad(JOY_1);

    SpriteJoueur_ *ptrJoueur=&Joueur;
    SpriteDragon_ *ptrDragon=&Dragon;
    SpriteSplash_ *ptrSplash=&Splash;
    SpriteAura_ *ptrAura=&Aura;


    //----------------------------------------------------//
    //----------------------------------------------------//
    //                        ARRET                       //
    //----------------------------------------------------//
    //----------------------------------------------------//
    if(ptrJoueur->Phase==ARRET)
    {
        //--------------------------//
        //         POSITION X       //
        //--------------------------//

        // SI ON N'EST PAS A LA FIN DU NIVEAU
        if(CamPosX!=-4336)
        {
            if(movX>= FIX32(-1L))
            {
                positionX -= GLISSEMENT;
            }
        }

        // JOUEUR ORIENTÉ VERS LA DROITE
        if(ptrJoueur->Axe==0)
        {
            movX -= ACCEL_D;
            if(movX < FIX32(0))
            {
                movX=0;
            }
        }

        // JOUEUR ORIENTÉ VERS LA GAUCHE
        else if(ptrJoueur->Axe==1)
        {
            movX += ACCEL_G;
            if(movX > FIX32(0))
            {
                movX=0;
            }
        }

        // ON AJOUTE 'movX' A L'ACCUMULATEUR 'positionX'
        positionX += movX;


        //--------------------------------//
        //            POSITION Y          //
        //--------------------------------//

        positionY = intToFix32(ptrJoueur->PosY);

        // MAJ POINTS DE COLLISION DU JOUEUR //
        MAJ_PtsCollision_Joueur();


        //--------------------------------//
        //     COLLISIONS PLATEFORMES     //
        //--------------------------------//

        Collision_Joueur_Plateformes();

        // SI PAS DE CONTACT AVEC PLATEFORME
        if(contactPlt_OK == 0)
        {
            //--------------------------//
            //     COLLISIONS DECOR     //
            //--------------------------//

            // TEST COLLISION DECOR //
            Collision_Decor_Bas();


            // SI LE JOUEUR CHUTE
            if(tileID_BG==0 && tileID_BD==0)
            {
                // PHASE CHUTE
                ptrJoueur->Phase=CHUTE;
            }

            // SI LE JOUEUR NE CHUTE PAS
            else
            {
                ptrJoueur->PosY = (posTileY<<3)-8;
                positionY=intToFix32(ptrJoueur->PosY);
            }
        }

        ptrJoueur->ptrPosition=&anim_SAUT[0];


        if(ptrJoueur->Invincible==0)
        {
            Collision_Joueur_Ennemis();
        }
    }


    //----------------------------------------------------//
    //----------------------------------------------------//
    //                       MARCHE                       //
    //----------------------------------------------------//
    //----------------------------------------------------//
    else if(ptrJoueur->Phase==MARCHE)
    {
        //--------------------------//
        //         POSITION X       //
        //--------------------------//

        /////////////////////////////
        //         DROITE          //
        /////////////////////////////
        if(ptrJoueur->Axe==0)
        {
            if(CamPosX!=-4336)
            {
                // ON AJOUTE 'ACCEL_D' A 'movX'
                movX += ACCEL_D;
            }
            else
            {
                // ON AJOUTE 'ACCEL_G' A 'movX'
                movX += ACCEL_G;
            }

            // ON BLOQUE LA VITESSE A 'maxSpeed_D (1)'
            if (movX >= maxSpeed_D)
            {
                movX = maxSpeed_D;
            }
        }

        /////////////////////////////
        //         GAUCHE          //
        /////////////////////////////
        else if(ptrJoueur->Axe==1)
        {
            movX -= ACCEL_G;

            if(CamPosX!=-4336)
            {
                if(movX >= FIX32(-1L))
                {
                    positionX -= GLISSEMENT;
                }

                // ON BLOQUE LA VITESSE A 'maxSpeed_G (2)'
                if(movX <= -maxSpeed_G)
                {
                    movX = -maxSpeed_G;
                }

            }

            // ON BLOQUE LA VITESSE A 'maxSpeed_D (1)'
            else
            {
                if(movX <= -maxSpeed_D)
                {
                    movX = -maxSpeed_D;
                }
            }
        }

        // ON AJOUTE 'movX' A L'ACCUMULATEUR 'positionX'
        positionX += movX;

        //--------------------------------//
        //            POSITION Y          //
        //--------------------------------//

        positionY = intToFix32(ptrJoueur->PosY);

        // MAJ POINTS DE COLLISION DU JOUEUR //
        MAJ_PtsCollision_Joueur();


        //--------------------------------//
        //     COLLISIONS PLATEFORMES     //
        //--------------------------------//

        Collision_Joueur_Plateformes();


        // SI PAS DE CONTACT AVEC PLATEFORME
        if(contactPlt_OK == 0)
        {
            //--------------------------//
            //     COLLISIONS DECOR     //
            //--------------------------//

            // TEST COLLISION DECOR //
            Collision_Decor_Bas();


            // SI LE JOUEUR CHUTE
            if(tileID_BG==0 && tileID_BD==0)
            {
                // PHASE CHUTE
                ptrJoueur->Phase=CHUTE;
                return;
            }

            // SI LE JOUEUR NE CHUTE PAS
            else if(tileID_BG==1 || tileID_BD==1)
            {
                ptrJoueur->PosY = (posTileY<<3)-8;
                positionY=intToFix32(ptrJoueur->PosY);
                MAJ_PtsCollision_Joueur();
            }
        }

        ptrJoueur->ptrPosition=&anim_SAUT[0];


        if(ptrJoueur->Invincible==0)
        {
            Collision_Joueur_Ennemis();
        }
    }


    //----------------------------------------------------//
    //----------------------------------------------------//
    //                        SAUT                        //
    //----------------------------------------------------//
    //----------------------------------------------------//
    else if(ptrJoueur->Phase==SAUT)
    {
        //--------------------------//
        //         POSITION X       //
        //--------------------------//

        /////////////////////////////
        //      BOUTON DROITE      //
        /////////////////////////////
        if(value & BUTTON_RIGHT)
        {
            ptrJoueur->Axe=0;

            // ON AJOUTE 'ACCEL_D' A 'movX'
            movX += ACCEL_D;

            // ON BLOQUE LA VITESSE A 'maxSpeed_D (1)'
            if (movX >= maxSpeed_D)
            {
                movX = maxSpeed_D;
            }
        }

        /////////////////////////////
        //      BOUTON GAUCHE      //
        /////////////////////////////
        else if(value & BUTTON_LEFT)
        {
            ptrJoueur->Axe=1;

            movX -= ACCEL_G;

            if(CamPosX!=-4336)
            {
                if(movX >= FIX32(-1L))
                {
                    positionX -= GLISSEMENT;
                }

                // ON BLOQUE LA VITESSE A 'maxSpeed_D (1)'
                if(movX <= -maxSpeed_G)
                {
                    movX = -maxSpeed_G;
                }
            }

            // ON BLOQUE LA VITESSE A 'maxSpeed_D (1)'
            else if(movX <= -maxSpeed_D)
            {
                movX = -maxSpeed_D;
            }
        }

        //////////////////////////////////////////
        //       AUCUN BOUTON DE DIRECTION      //
        //////////////////////////////////////////

        else if((value & BUTTON_DIR) == 0 || value & (BUTTON_UP | BUTTON_DOWN) )
        {
            //--------------------------//
            //         POSITION X       //
            //--------------------------//

            // SI ON N'EST PAS A LA FIN DU NIVEAU
            if(CamPosX!=-4336)
            {
                if(movX>= FIX32(-1L))
                {
                    positionX -= GLISSEMENT;
                }
            }

            // JOUEUR ORIENTÉ VERS LA DROITE
            if(ptrJoueur->Axe==0)
            {
                movX -= ACCEL_D;
                if(movX < FIX32(0))
                {
                    movX=0;
                }
            }

            // JOUEUR ORIENTÉ VERS LA GAUCHE
            else if(ptrJoueur->Axe==1)
            {
                movX += ACCEL_G;
                if(movX > FIX32(0))
                {
                    movX=0;
                }
            }
        }

        // ON AJOUTE 'movX' A L'ACCUMULATEUR 'positionX'
        positionX += movX;


        //--------------------------//
        //         POSITION Y       //
        //--------------------------//

        //--------------------------------//
        //          ANIM DE SAUT          //
        //--------------------------------//

        ptrJoueur->PosY += *(ptrJoueur->ptrPosition);
        ptrJoueur->ptrPosition++;

        if(ptrJoueur->ptrPosition > &anim_SAUT[MAX_ETAPES_SAUT])
        {
            ptrJoueur->ptrPosition = &anim_SAUT[MAX_ETAPES_SAUT];
        }

        positionY = intToFix32(ptrJoueur->PosY);

        // MAJ POINTS DE COLLISION DU JOUEUR //
        MAJ_PtsCollision_Joueur();

        //--------------------------------//
        //     COLLISIONS PLATEFORMES     //
        //--------------------------------//

        Collision_Joueur_Plateformes();

        

        // SI PAS DE CONTACT AVEC PLATEFORME //
        if(contactPlt_OK == 0)
        {
            // SI LE JOUEUR EST EN PHASE DESCENDANTE DU SAUT //
            if(ptrJoueur->ptrPosition > &anim_SAUT[21])
            {
                //--------------------------//
                //     COLLISIONS DECOR     //
                //--------------------------//

                // TEST COLLISION DECOR //
                Collision_Decor_Bas();


                // SI LE JOUEUR CHUTE //
                if(tileID_BG==1 || tileID_BD==1)
                {
                    // PHASE ARRET //
                    ptrJoueur->Phase=ARRET;
                    ptrJoueur->PosY = (posTileY<<3)-8;
                    ptrJoueur->ptrPosition=&anim_SAUT[0];
                    positionY = intToFix32(ptrJoueur->PosY);
                    MAJ_PtsCollision_Joueur();

                    //return;
                }
            }
        }

        if(ptrJoueur->Invincible==0)
        {
            Collision_Joueur_Ennemis();
        }

        // JOUEUR TOUCHE BAS DE L'ÉCRAN //
        if(ptrJoueur->PosY>192)
        {
            // SPLASH //
            ptrSplash->Init=1;
            ptrSplash->PosX=ptrJoueur->PosX;
            ptrSplash->PosY=168;
            SPR_setPosition(ptrSplash->SpriteS, ptrSplash->PosX, ptrSplash->PosY);

            VDP_loadTileSet(&tileset_TETE_MORT, AdresseVram_Tete, DMA);

            // LA BARRE D'ENERGIE SE VIDE //
            Vider_BarreEnergie();
            CompteurEnergie=0;
            Energie=0;

            ptrJoueur->CompteurInvincible=0;
            ptrJoueur->Invincible=0;
            ptrJoueur->HorsChamp=0;
            PosYinvincible=0;

            // JOUEUR //
            ptrJoueur->Phase=APPARITION;
            //ptrJoueur->Invincible=1;
            ptrJoueur->Axe=0;
            ptrJoueur->PosX=63;
            ptrJoueur->PosY=40;
            positionX=intToFix32(63);
            positionY=intToFix32(40);
            movX=0;
            SPR_setHFlip(ptrJoueur->SpriteJ_BAS, FALSE);
            SPR_setHFlip(ptrJoueur->SpriteJ_HAUT, FALSE);
        }
    }


    //----------------------------------------------------//
    //----------------------------------------------------//
    //                         TIR                        //
    //----------------------------------------------------//
    //----------------------------------------------------//
    else if(ptrJoueur->Phase==TIR)
    {
        //--------------------------//
        //         POSITION X       //
        //--------------------------//

        /////////////////////////////
        //      BOUTON DROITE      //
        /////////////////////////////
        if(value & BUTTON_RIGHT)
        {
            ptrJoueur->Axe=0;

            // ON AJOUTE 'ACCEL_D' A 'movX'
            movX += ACCEL_D;

            // ON BLOQUE LA VITESSE A 'maxSpeed_D (1)'
            if (movX >= maxSpeed_D)
            {
                movX = maxSpeed_D;
            }
        }

        /////////////////////////////
        //      BOUTON GAUCHE      //
        /////////////////////////////
        else if(value & BUTTON_LEFT)
        {
            ptrJoueur->Axe=1;

            movX -= ACCEL_G;

            if(CamPosX!=-4336)
            {
                if(movX >= FIX32(-1L))
                {
                    positionX -= GLISSEMENT;
                }

                // ON BLOQUE LA VITESSE A 'maxSpeed_D (1)'
                if(movX <= -maxSpeed_G)
                {
                    movX = -maxSpeed_G;
                }
            }

            // ON BLOQUE LA VITESSE A 'maxSpeed_D (1)'
            else if(movX <= -maxSpeed_D)
            {
                movX = -maxSpeed_D;
            }
        }

        //////////////////////////////////////////
        //       AUCUN BOUTON DE DIRECTION      //
        //////////////////////////////////////////

        else if((value & BUTTON_DIR) == 0 || value & (BUTTON_UP | BUTTON_DOWN) )
        {
            //--------------------------//
            //         POSITION X       //
            //--------------------------//

            // SI ON N'EST PAS A LA FIN DU NIVEAU
            if(CamPosX!=-4336)
            {
                if(movX>= FIX32(-1L))
                {
                    positionX -= GLISSEMENT;
                }
            }

            // JOUEUR ORIENTÉ VERS LA DROITE
            if(ptrJoueur->Axe==0)
            {
                movX -= ACCEL_D;
                if(movX < FIX32(0))
                {
                    movX=0;
                }
            }

            // JOUEUR ORIENTÉ VERS LA GAUCHE
            else if(ptrJoueur->Axe==1)
            {
                movX += ACCEL_G;
                if(movX > FIX32(0))
                {
                    movX=0;
                }
            }
        }

        // ON AJOUTE 'movX' A L'ACCUMULATEUR 'positionX'
        positionX += movX;


        //--------------------------//
        //         POSITION Y       //
        //--------------------------//

        positionY = intToFix32(ptrJoueur->PosY);


        // MAJ POINTS DE COLLISION DU JOUEUR //
        MAJ_PtsCollision_Joueur();


        //--------------------------------//
        //     COLLISIONS PLATEFORMES     //
        //--------------------------------//

        Collision_Joueur_Plateformes();


        // SI PAS DE CONTACT AVEC PLATEFORME
        if(contactPlt_OK == 0)
        {
            //--------------------------//
            //     COLLISIONS DECOR     //
            //--------------------------//

            // TEST COLLISION DECOR //
            Collision_Decor_Bas();


            // SI LE JOUEUR CHUTE
            if(tileID_BG==0 && tileID_BD==0)
            {
                // PHASE CHUTE
                ptrJoueur->Phase=CHUTE;
                return;
            }

            // SI LE JOUEUR NE CHUTE PAS
            else if(tileID_BG==1 || tileID_BD==1)
            {
                ptrJoueur->PosY = (posTileY<<3)-8;
                positionY=intToFix32(ptrJoueur->PosY);
                MAJ_PtsCollision_Joueur();
            }
        }

        if(ptrJoueur->Invincible==0)
        {
            Collision_Joueur_Ennemis();
        }
    }


    //----------------------------------------------------//
    //----------------------------------------------------//
    //                    SAUT + TIR                      //
    //----------------------------------------------------//
    //----------------------------------------------------//
    else if(ptrJoueur->Phase==SAUT_TIR)
    {
        //--------------------------//
        //         POSITION X       //
        //--------------------------//

        /////////////////////////////
        //      BOUTON DROITE      //
        /////////////////////////////
        if(value & BUTTON_RIGHT)
        {
            ptrJoueur->Axe=0;

            // ON AJOUTE 'ACCEL_D' A 'movX'
            movX += ACCEL_D;

            // ON BLOQUE LA VITESSE A 'maxSpeed_D (1)'
            if (movX >= maxSpeed_D)
            {
                movX = maxSpeed_D;
            }
        }

        /////////////////////////////
        //      BOUTON GAUCHE      //
        /////////////////////////////
        else if(value & BUTTON_LEFT)
        {
            ptrJoueur->Axe=1;

            movX -= ACCEL_G;

            if(CamPosX!=-4336)
            {
                if(movX >= FIX32(-1L))
                {
                    positionX -= GLISSEMENT;
                }

                // ON BLOQUE LA VITESSE A 'maxSpeed_D (1)'
                if(movX <= -maxSpeed_G)
                {
                    movX = -maxSpeed_G;
                }
            }

            // ON BLOQUE LA VITESSE A 'maxSpeed_D (1)'
            else if(movX <= -maxSpeed_D)
            {
                movX = -maxSpeed_D;
            }
        }

        //////////////////////////////////////////
        //       AUCUN BOUTON DE DIRECTION      //
        //////////////////////////////////////////

        else if((value & BUTTON_DIR) == 0 || value & (BUTTON_UP | BUTTON_DOWN) )
        {
            //--------------------------//
            //         POSITION X       //
            //--------------------------//

            // SI ON N'EST PAS A LA FIN DU NIVEAU
            if(CamPosX!=-4336)
            {
                if(movX>= FIX32(-1L))
                {
                    positionX -= GLISSEMENT;
                }
            }

            // JOUEUR ORIENTÉ VERS LA DROITE
            if(ptrJoueur->Axe==0)
            {
                movX -= ACCEL_D;
                if(movX < FIX32(0))
                {
                    movX=0;
                }
            }

            // JOUEUR ORIENTÉ VERS LA GAUCHE
            else if(ptrJoueur->Axe==1)
            {
                movX += ACCEL_G;
                if(movX > FIX32(0))
                {
                    movX=0;
                }
            }
        }

        // ON AJOUTE 'movX' A L'ACCUMULATEUR 'positionX'
        positionX += movX;


        //--------------------------//
        //         POSITION Y       //
        //--------------------------//

        //--------------------------------//
        //          ANIM DE SAUT          //
        //--------------------------------//

        ptrJoueur->PosY += *(ptrJoueur->ptrPosition);
        ptrJoueur->ptrPosition++;

        if(ptrJoueur->ptrPosition > &anim_SAUT[MAX_ETAPES_SAUT])
        {
            ptrJoueur->ptrPosition = &anim_SAUT[MAX_ETAPES_SAUT];
        }

        positionY = intToFix32(ptrJoueur->PosY);


        // MAJ POINTS DE COLLISION DU JOUEUR //
        MAJ_PtsCollision_Joueur();

        //--------------------------------//
        //     COLLISIONS PLATEFORMES     //
        //--------------------------------//

        Collision_Joueur_Plateformes();

        positionY = intToFix32(ptrJoueur->PosY);

        // SI PAS DE CONTACT AVEC PLATEFORME //
        if(contactPlt_OK == 0)
        {
            // SI LE JOUEUR EST EN PHASE DESCENDANTE DU SAUT //
            if(ptrJoueur->ptrPosition > &anim_SAUT[21])
            {
                //--------------------------//
                //     COLLISIONS DECOR     //
                //--------------------------//

                // TEST COLLISION DECOR //
                Collision_Decor_Bas();


                // SI LE JOUEUR TOUCHE LE SOL //
                if(tileID_BG==1 || tileID_BD==1)
                {
                    // PHASE ARRET //
                    if(ptrJoueur->Phase==SAUT_TIR)
                    {
                        ptrJoueur->Phase=TIR;
                    }
                    else
                    {
                        ptrJoueur->Phase=ARRET;
                    }

                    ptrJoueur->PosY=(posTileY<<3)-8;
                    ptrJoueur->ptrPosition=&anim_SAUT[0];
                    positionY=intToFix32(ptrJoueur->PosY);
                    MAJ_PtsCollision_Joueur();
                }
            }
        }

        if(ptrJoueur->Invincible==0)
        {
            Collision_Joueur_Ennemis();
        }

        // JOUEUR TOUCHE BAS DE L'ÉCRAN //
        if(ptrJoueur->PosY>192)
        {
            // SPLASH //
            ptrSplash->Init=1;
            ptrSplash->PosX=ptrJoueur->PosX;
            ptrSplash->PosY=168;
            SPR_setPosition(ptrSplash->SpriteS, ptrSplash->PosX, ptrSplash->PosY);

            VDP_loadTileSet(&tileset_TETE_MORT, AdresseVram_Tete, DMA);

            // LA BARRE D'ENERGIE SE VIDE //
            Vider_BarreEnergie();
            CompteurEnergie=0;
            Energie=0;

            ptrJoueur->CompteurInvincible=0;
            ptrJoueur->Invincible=0;
            ptrJoueur->HorsChamp=0;
            PosYinvincible=0;

            // JOUEUR //
            ptrJoueur->Phase=APPARITION;
            //ptrJoueur->Invincible=1;
            ptrJoueur->Axe=0;
            ptrJoueur->PosX=63;
            ptrJoueur->PosY=40;
            positionX=intToFix32(63);
            positionY=intToFix32(40);
            movX=0;
            SPR_setHFlip(ptrJoueur->SpriteJ_BAS, FALSE);
            SPR_setHFlip(ptrJoueur->SpriteJ_HAUT, FALSE);
        }
    }


    //----------------------------------------------------//
    //----------------------------------------------------//
    //                       CHUTE                        //
    //----------------------------------------------------//
    //----------------------------------------------------//
    else if(ptrJoueur->Phase==CHUTE)
    {
        //--------------------------//
        //         POSITION X       //
        //--------------------------//

        /////////////////////////////
        //      BOUTON DROITE      //
        /////////////////////////////
        if(value & BUTTON_RIGHT)
        {
            ptrJoueur->Axe=0;

            // ON AJOUTE 'ACCEL_D' A 'movX'
            movX += ACCEL_C;

            // ON BLOQUE LA VITESSE A 'maxSpeed_D (1)'
            if (movX >= maxSpeed_D)
            {
                movX = maxSpeed_D;
            }
        }

        /////////////////////////////
        //      BOUTON GAUCHE      //
        /////////////////////////////
        else if(value & BUTTON_LEFT)
        {
            ptrJoueur->Axe=1;

            // ON SOUSTRAIT 'ACCEL_D' A 'movX'
            movX -= ACCEL_C;

        // ON BLOQUE LA VITESSE A 'maxSpeed_D (1)'
            if(movX <= -maxSpeed_D)
            {
                movX = -maxSpeed_D;
            }
        }

        /////////////////////////////
        //       AUCUN BOUTON      //
        /////////////////////////////
        else if(value == 0)
        {
            // JOUEUR ORIENTÉ VERS LA DROITE
            if(ptrJoueur->Axe==0)
            {
                movX -= ACCEL_C;
                if(movX < FIX32(0))
                {
                    movX=0;
                }
            }

            // JOUEUR ORIENTÉ VERS LA GAUCHE
            else if(ptrJoueur->Axe==1)
            {
                movX += ACCEL_C;
                if(movX > FIX32(0))
                {
                    movX=0;
                }
            }
        }

        // SI ON N'EST PAS A LA FIN DU NIVEAU
        if(CamPosX!=-4336)
        {
            positionX -= GLISSEMENT;
        }

        // ON AJOUTE 'movX' A L'ACCUMULATEUR 'positionX'
        positionX += movX;


        //--------------------------//
        //         POSITION Y       //
        //--------------------------//

        movY += ACCEL_B;

        // ON BLOQUE LA VITESSE A 'maxSpeed_V (3)'
        if (movY >= maxSpeed_V)
        {
            movY = maxSpeed_V;
        }

        // ON AJOUTE 'movY' A L'ACCUMULATEUR 'positionY'
        positionY += movY;



        // MAJ POINTS DE COLLISION DU JOUEUR //
        MAJ_PtsCollision_Joueur();


        //--------------------------------//
        //     COLLISIONS PLATEFORMES     //
        //--------------------------------//

        Collision_Joueur_Plateformes();


        // SI PAS DE CONTACT AVEC PLATEFORME
        if(contactPlt_OK == 0)
        {
            //--------------------------//
            //     COLLISIONS DECOR     //
            //--------------------------//

            // TEST COLLISION DECOR //
            Collision_Decor_Bas();


            // SI LE JOUEUR TOUCHE LE SOL
            if(tileID_BG==1 || tileID_BD==1)
            {
                // PHASE CHUTE
                ptrJoueur->PosY = (posTileY<<3)-8;
                positionY=intToFix32(ptrJoueur->PosY);
                MAJ_PtsCollision_Joueur();
                ptrJoueur->Phase=ARRET;
                ptrJoueur->ptrPosition=&anim_SAUT[0];
            }

            // SI LE JOUEUR NE TOUCHE PAS LE SOL
            else
            {
                ptrJoueur->PosY=fix32ToInt(positionY);
            }

            // JOUEUR TOUCHE BAS DE L'ÉCRAN //
            if(ptrJoueur->PosY>192)
            {
                // SPLASH //
                ptrSplash->Init=1;
                ptrSplash->PosX=ptrJoueur->PosX;
                ptrSplash->PosY=168;
                SPR_setPosition(ptrSplash->SpriteS, ptrSplash->PosX, ptrSplash->PosY);

                VDP_loadTileSet(&tileset_TETE_MORT, AdresseVram_Tete, DMA);

                // LA BARRE D'ENERGIE SE VIDE //
                Vider_BarreEnergie();
                CompteurEnergie=0;
                Energie=0;

                ptrJoueur->CompteurInvincible=0;
                ptrJoueur->Invincible=0;
                ptrJoueur->HorsChamp=0;
                PosYinvincible=0;

                // JOUEUR //
                ptrJoueur->Phase=APPARITION;
                //ptrJoueur->Invincible=1;
                ptrJoueur->Axe=0;
                ptrJoueur->PosX=63;
                ptrJoueur->PosY=40;
                positionX=intToFix32(63);
                positionY=intToFix32(16);
                movX=0;
                SPR_setHFlip(ptrJoueur->SpriteJ_BAS, FALSE);
                SPR_setHFlip(ptrJoueur->SpriteJ_HAUT, FALSE);
            }
        }

        if(ptrJoueur->Invincible==0)
        {
            Collision_Joueur_Ennemis();
        }
    }


    //----------------------------------------------------//
    //----------------------------------------------------//
    //                     CHUTE_TIR                      //
    //----------------------------------------------------//
    //----------------------------------------------------//
    else if(ptrJoueur->Phase==CHUTE_TIR)
    {
        //--------------------------//
        //         POSITION X       //
        //--------------------------//

        /////////////////////////////
        //      BOUTON DROITE      //
        /////////////////////////////
        if(value & BUTTON_RIGHT)
        {
            ptrJoueur->Axe=0;

            // ON AJOUTE 'ACCEL_D' A 'movX'
            movX += ACCEL_C;

            // ON BLOQUE LA VITESSE A 'maxSpeed_D (1)'
            if (movX >= maxSpeed_D)
            {
                movX = maxSpeed_D;
            }
        }

        /////////////////////////////
        //      BOUTON GAUCHE      //
        /////////////////////////////
        else if(value & BUTTON_LEFT)
        {
            ptrJoueur->Axe=1;

            // ON SOUSTRAIT 'ACCEL_D' A 'movX'
            movX -= ACCEL_C;

        // ON BLOQUE LA VITESSE A 'maxSpeed_D (1)'
            if(movX <= -maxSpeed_D)
            {
                movX = -maxSpeed_D;
            }
        }

        /////////////////////////////
        //       AUCUN BOUTON      //
        /////////////////////////////
        else if(value == 0)
        {
            // JOUEUR ORIENTÉ VERS LA DROITE
            if(ptrJoueur->Axe==0)
            {
                movX -= ACCEL_C;
                if(movX < FIX32(0))
                {
                    movX=0;
                }
            }

            // JOUEUR ORIENTÉ VERS LA GAUCHE
            else if(ptrJoueur->Axe==1)
            {
                movX += ACCEL_C;
                if(movX > FIX32(0))
                {
                    movX=0;
                }
            }
        }

        // SI ON N'EST PAS A LA FIN DU NIVEAU
        if(CamPosX!=-4336)
        {
            positionX -= GLISSEMENT;
        }

        // ON AJOUTE 'movX' A L'ACCUMULATEUR 'positionX'
        positionX += movX;


        //--------------------------//
        //         POSITION Y       //
        //--------------------------//

        movY += ACCEL_B;

        // ON BLOQUE LA VITESSE A 'maxSpeed_V (3)'
        if (movY >= maxSpeed_V)
        {
            movY = maxSpeed_V;
        }

        // ON AJOUTE 'movY' A L'ACCUMULATEUR 'positionY'
        positionY += movY;



        // MAJ POINTS DE COLLISION DU JOUEUR //
        MAJ_PtsCollision_Joueur();


        //--------------------------------//
        //     COLLISIONS PLATEFORMES     //
        //--------------------------------//

        Collision_Joueur_Plateformes();


        // SI PAS DE CONTACT AVEC PLATEFORME
        if(contactPlt_OK == 0)
        {
            //--------------------------//
            //     COLLISIONS DECOR     //
            //--------------------------//

            // TEST COLLISION DECOR //
            Collision_Decor_Bas();


                // SI LE JOUEUR TOUCHE LE SOL //
                if(tileID_BG==1 || tileID_BD==1)
                {
                    // PHASE ARRET //
                    if(ptrJoueur->Phase==CHUTE_TIR)
                    {
                        ptrJoueur->Phase=TIR;
                    }
                    else
                    {
                        ptrJoueur->Phase=ARRET;
                    }

                    ptrJoueur->PosY = (posTileY<<3)-8;
                    positionY=intToFix32(ptrJoueur->PosY);
                    MAJ_PtsCollision_Joueur();
                }


            // SI LE JOUEUR NE TOUCHE PAS LE SOL
            else
            {
                ptrJoueur->PosY=fix32ToInt(positionY);
            }

            // JOUEUR TOUCHE BAS DE L'ÉCRAN //
            if(ptrJoueur->PosY>192)
            {
                // SPLASH //
                ptrSplash->Init=1;
                ptrSplash->PosX=ptrJoueur->PosX;
                ptrSplash->PosY=168;
                SPR_setPosition(ptrSplash->SpriteS, ptrSplash->PosX, ptrSplash->PosY);

                VDP_loadTileSet(&tileset_TETE_MORT, AdresseVram_Tete, DMA);

                // LA BARRE D'ENERGIE SE VIDE //
                Vider_BarreEnergie();
                CompteurEnergie=0;
                Energie=0;

                ptrJoueur->CompteurInvincible=0;
                ptrJoueur->Invincible=0;
                ptrJoueur->HorsChamp=0;
                PosYinvincible=0;

                // JOUEUR //
                ptrJoueur->Phase=APPARITION;
                //ptrJoueur->Invincible=1;
                ptrJoueur->Axe=0;
                ptrJoueur->PosX=63;
                ptrJoueur->PosY=40;
                positionX=intToFix32(63);
                positionY=intToFix32(16);
                movX=0;
                SPR_setHFlip(ptrJoueur->SpriteJ_BAS, FALSE);
                SPR_setHFlip(ptrJoueur->SpriteJ_HAUT, FALSE);
            }
        }

        if(ptrJoueur->Invincible==0)
        {
            Collision_Joueur_Ennemis();
        }
    }


    //----------------------------------------------------//
    //----------------------------------------------------//
    //                       TOUCHÉ                       //
    //----------------------------------------------------//
    //----------------------------------------------------//
    else if(ptrJoueur->Phase==TOUCHE)
    {
        VDP_loadTileSet(&tileset_TETE_MORT, AdresseVram_Tete, DMA);
        //VDP_setTileMapEx(WINDOW, image_TETE_F.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, AdresseVram_Tete), 1, 1, 0, 0, 2, 2, DMA);

        
        // LA BARRE D'ENERGIE SE VIDE //
        Vider_BarreEnergie();
        CompteurEnergie=0;
        Energie=0;
        
        //--------------------------//
        //         POSITION X       //
        //--------------------------//

        // SI ON N'EST PAS A LA FIN DU NIVEAU
        if(CamPosX!=-4336)
        {
            positionX -= GLISSEMENT;
        }

        movX=0;


        //--------------------------//
        //         POSITION Y       //
        //--------------------------//

        //--------------------------------//
        //          ANIM DE SAUT          //
        //--------------------------------//

        ptrJoueur->PosY += *(ptrJoueur->ptrPosition);
        ptrJoueur->ptrPosition++;

        if(ptrJoueur->ptrPosition > &anim_TOUCHE[MAX_ETAPES_TOUCHE])
        {
            ptrJoueur->ptrPosition = &anim_TOUCHE[MAX_ETAPES_TOUCHE];
        }

        positionY = intToFix32(ptrJoueur->PosY);


        // JOUEUR TOUCHE BAS DE L'ÉCRAN //
        if(ptrJoueur->PosY>192)
        {
            Collision_Decor_Haut();

            // SI IL N'Y A PAS DE ROCHER AU-DESSUS DE L'EAU //
            if(tileID_H == 2)
            {
                // SPLASH //
                ptrSplash->Init=1;
                ptrSplash->PosX=ptrJoueur->PosX;
                ptrSplash->PosY=168;
                SPR_setPosition(ptrSplash->SpriteS, ptrSplash->PosX, ptrSplash->PosY);
            }
            else
            {
                // Le décompte de vies ne se fait qu'à la fin du splash //
                // Dans le cas où il n'y a pas de splash, on fait le décompte tout de suite //
                // CHANGEMENT PALETTE DRAGON //
                PAL_setColor( 10 , 0x0A4C );
                PAL_setColor( 13 , 0x0C6C );
                Maj_Vies();
            }

            // LA BARRE D'ENERGIE SE VIDE //
            Vider_BarreEnergie();
            CompteurEnergie=0;
            Energie=0;

            ptrJoueur->CompteurInvincible=0;
            ptrJoueur->Invincible=0;
            ptrJoueur->HorsChamp=0;
            PosYinvincible=0;

            // JOUEUR //
            ptrJoueur->Phase=APPARITION;
            //ptrJoueur->Invincible=1;
            ptrJoueur->Axe=0;
            ptrJoueur->PosX=63;
            ptrJoueur->PosY=40;
            positionX=intToFix32(63);
            positionY=intToFix32(40);
            movX=0;
            SPR_setHFlip(ptrJoueur->SpriteJ_BAS, FALSE);
            SPR_setHFlip(ptrJoueur->SpriteJ_HAUT, FALSE);
        }

    }


    //----------------------------------------------------//
    //----------------------------------------------------//
    //                     APPARITION                     //
    //----------------------------------------------------//
    //----------------------------------------------------//
    else if(ptrJoueur->Phase==APPARITION)
    {
        //--------------------------//
        //           SPLASH         //
        //--------------------------//

        // Quand le splash est en cours, son anim se déroule //
        if(ptrSplash->Init==1)
        {
            // SI LE SCROLLING EST EN COURS, LE SPLASH SE DEPLACE //
            if(CamPosX!=-4336)
            {
                ptrSplash->PosX-=vitesseScrolling;
            }

            // QUAND L'ANIM DU SPLASH EST FINE, IL DEVIENT HORS CHAMP //
            if(ptrSplash->CompteurFrameSplash==0 && ptrSplash->IndexFrameSplash==7)
            {
                ptrSplash->PosY-=8;
                // CHANGEMENT PALETTE DRAGON //
                PAL_setColor( 10 , 0x0A4C );
                PAL_setColor( 13 , 0x0C6C );
            }
        }

        //--------------------------//
        //           DRAGON         //
        //--------------------------//

        // Quand le splash est fini, le dragon apparait //
        else
        {
            //-------------------------------------//
            //           APPARITION DRAGON         //
            //-------------------------------------//
            if(ptrJoueur->CompteurApparition>20 && ptrJoueur->CompteurApparition<76)
            {
                ptrJoueur->PosY+=1;
                positionY=intToFix32(ptrJoueur->PosY);

                ptrDragon->PosX=ptrJoueur->PosX;
                ptrDragon->PosY=ptrJoueur->PosY-49;
            }
//**//
            //-------------------------------------//
            //            ATTENTE LARGAGE          //
            //-------------------------------------//
            else if(ptrJoueur->CompteurApparition>75 && ptrJoueur->CompteurApparition<275)
            {
                //--------------------------//
                //         POSITION X       //
                //--------------------------//

                /////////////////////////////
                //      BOUTON DROITE      //
                /////////////////////////////
                if(value & BUTTON_RIGHT)
                {
                    ptrJoueur->PosX+=1;

                    // LIMITE DROITE ECRAN //
                    if(ptrJoueur->PosX>159)
                    {
                        ptrJoueur->PosX=159;
                    }

                    positionX=intToFix32(ptrJoueur->PosX);
                    ptrDragon->PosX=ptrJoueur->PosX;
                }

                /////////////////////////////
                //      BOUTON GAUCHE      //
                /////////////////////////////
                else if(value & BUTTON_LEFT)
                {
                    ptrJoueur->PosX-=1;

                    // LIMITE GAUCHE ECRAN //
                    if(ptrJoueur->PosX<31)
                    {
                        ptrJoueur->PosX=31;
                    }

                    positionX=intToFix32(ptrJoueur->PosX);
                    ptrDragon->PosX=ptrJoueur->PosX;
                }
            }

            //-------------------------------------//
            //              ENVOL DRAGON           //
            //-------------------------------------//
            else if(ptrJoueur->CompteurApparition>274)
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


            // SI LE DRAGON NE S'ENVOLE PAS, ON INCREMENTE LE COMPTEUR //
            if(ptrDragon->Phase!=SORTIE_DRAGON)
            {
                ptrJoueur->CompteurApparition++;
            }
        }
    }


    // SPECIAL CASE : IF PLAYER SPAWNS AGAIN AT THE END OF THE LEVEL //
    if(CamPosX == -4336)
    {
        if(ptrJoueur->Phase==APPARITION)
        {
            if(ptrJoueur->CompteurApparition>55)
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


    //----------------------------------------------------//
    //             NOUVELLE POSITION DU SPRITE            //
    //----------------------------------------------------//
    vitesseScrolling=1;

    // SI LE JOUEUR ATTEINT LA GAUCHE DE L'ECRAN
    if(positionX < -MAX_POS_G)
    {
        // IL EST BLOQUÉ
        positionX = -MAX_POS_G;
        movX=0;
    }
    
    // SI LE JOUEUR A ATTEINT LA FIN DU NIVEAU //
    if(CamPosX <= -4336)
    {
        // SI LE JOUEUR ATTEINT LA DROITE DE L'ECRAN
        if(positionX > MAX_POS_FIN)
        {
            // IL EST BLOQUÉ
            positionX = MAX_POS_FIN;

            SWITCH_GAMEOVER = 1;

            vitesseScrolling=2;
        }
    }

    else
    {
        // SI LE JOUEUR ATTEINT LA DROITE DE L'ECRAN
        if(positionX > MAX_POS_D)
        {
            // IL EST BLOQUÉ
            positionX = MAX_POS_D;

            vitesseScrolling=2;
        }
    }

    // ON CONVERTIT 'positionX' en int
    // 'positionX' EST LA NOUVELLE POSITION X DU SPRITE
    ptrJoueur->PosX=fix32ToInt(positionX);


    //----------------------------------------------------//
    //                    ETAT INVINCIBLE                 //
    //----------------------------------------------------//
    if(ptrJoueur->Invincible==1)
    {
        ptrJoueur->CompteurInvincible++;

        if(ptrJoueur->CompteurInvincible%2==0)
        {
            ptrJoueur->HorsChamp=!(ptrJoueur->HorsChamp);

            if(ptrJoueur->HorsChamp==0)
            {
                PosYinvincible=0;
            }
            else
            {
                PosYinvincible=256;
            }
        }

        // Invincible PENDANT 60 IMAGES //
        if(ptrJoueur->CompteurInvincible>DUREE_INVINCIBLE)
        {
            ptrJoueur->CompteurInvincible=0;
            ptrJoueur->Invincible=0;
            ptrJoueur->HorsChamp=0;
            PosYinvincible=0;
        }
    }


    //-----------------------------//
    //             AURA            //
    //-----------------------------//
    if(ptrAura->Init==1)
    {
        // JOUEUR VERS LA DROITE
        if(ptrJoueur->Axe==0)
        {
            SPR_setHFlip(ptrAura->SpriteA, FALSE);
            ptrAura->PosX=ptrJoueur->PosX+19;
            ptrAura->PosY=ptrJoueur->PosY-19;
        }
        // JOUEUR VERS LA GAUCHE
        else
        {
            SPR_setHFlip(ptrAura->SpriteA, TRUE);
            ptrAura->PosX=ptrJoueur->PosX-11;
            ptrAura->PosY=ptrJoueur->PosY-19;
        }
    }
    
    else
    {
        ptrAura->PosX=0;
        ptrAura->PosY=-24;
    }



    // JOUEUR //
    SPR_setPosition(ptrJoueur->SpriteJ_BAS, ptrJoueur->PosX, ptrJoueur->PosY-PosYinvincible);
    SPR_setPosition(ptrJoueur->SpriteJ_HAUT, ptrJoueur->PosX, ptrJoueur->PosY-PosYinvincible-24);

    // REPERES //
    //SPR_setPosition(sprite_repere_BG, ptrJoueur->pt_Coll_BG_X, ptrJoueur->pt_Coll_BG_Y-PosYinvincible-7);
    //SPR_setPosition(sprite_repere_BD, ptrJoueur->pt_Coll_BD_X-7, ptrJoueur->pt_Coll_BG_Y-PosYinvincible-7);

    // DRAGON //
    SPR_setPosition(ptrDragon->SpriteD, ptrDragon->PosX, ptrDragon->PosY);
    // SPLASH //
    SPR_setPosition(ptrSplash->SpriteS, ptrSplash->PosX, ptrSplash->PosY);
    // AURA //
    SPR_setPosition(ptrAura->SpriteA, ptrAura->PosX, ptrAura->PosY);
}


//-----------------------------------------------//
//                      TILES                    //
//-----------------------------------------------//
inline static void TilesBloque()
{
    SpriteJoueur_ *ptrJoueur=&Joueur;

    SPR_setAnim(ptrJoueur->SpriteJ_BAS,1);
    SPR_setAnim(ptrJoueur->SpriteJ_HAUT,1);

    ptrJoueur->CompteurFrameArret=0;
    ptrJoueur->IndexFrameArret=0;

    ptrJoueur->CompteurFrameMarche=0;
    ptrJoueur->IndexFrameMarche=0;

    ptrJoueur->CompteurFrameTir=0;
    ptrJoueur->IndexFrameTir=0;

    SPR_setHFlip(ptrJoueur->SpriteJ_BAS, FALSE);
    SPR_setHFlip(ptrJoueur->SpriteJ_HAUT, FALSE);

    SPR_setFrame(ptrJoueur->SpriteJ_BAS,(s16)ptrJoueur->IndexFrameBloque);
    SPR_setFrame(ptrJoueur->SpriteJ_HAUT,(s16)ptrJoueur->IndexFrameBloque);

    // Anim des tiles
    ptrJoueur->CompteurFrameBloque+=1;

    // MAJ des tiles toutes les 5 images (0 à 4)
    if(ptrJoueur->CompteurFrameBloque>4)
    {
        ptrJoueur->CompteurFrameBloque=0;
        ptrJoueur->IndexFrameBloque+=1;

        // Cycle de FRAME de 0 à 2 (3 étapes)
        if(ptrJoueur->IndexFrameBloque>2)
        {
            ptrJoueur->IndexFrameBloque=0;
        }
    }
}

inline static void TilesArret()
{
    SpriteJoueur_ *ptrJoueur=&Joueur;

    SPR_setAnim(ptrJoueur->SpriteJ_BAS,0);
    SPR_setAnim(ptrJoueur->SpriteJ_HAUT,0);

    ptrJoueur->CompteurFrameBloque=0;
    ptrJoueur->IndexFrameBloque=0;

    ptrJoueur->CompteurFrameMarche=0;
    ptrJoueur->IndexFrameMarche=0;

    ptrJoueur->CompteurFrameTir=0;
    ptrJoueur->IndexFrameTir=0;

    SPR_setFrame(ptrJoueur->SpriteJ_BAS,(s16)ptrJoueur->IndexFrameArret);
    SPR_setFrame(ptrJoueur->SpriteJ_HAUT,(s16)ptrJoueur->IndexFrameArret);

    // Anim des tiles
    ptrJoueur->CompteurFrameArret+=1;

    // MAJ des tiles toutes les 10 images (0 à 9)
    if(ptrJoueur->CompteurFrameArret>9)
    {
        ptrJoueur->CompteurFrameArret=0;
        ptrJoueur->IndexFrameArret+=1;

        // Cycle de FRAME de 0 à 2 (3 étapes)
        if(ptrJoueur->IndexFrameArret>2)
        {
            ptrJoueur->IndexFrameArret=0;
        }
    }
}

inline static void TilesMarche()
{
    SpriteJoueur_ *ptrJoueur=&Joueur;

    SPR_setAnim(ptrJoueur->SpriteJ_BAS,2);
    SPR_setAnim(ptrJoueur->SpriteJ_HAUT,2);

    ptrJoueur->CompteurFrameBloque=0;
    ptrJoueur->IndexFrameBloque=0;

    ptrJoueur->CompteurFrameArret=0;
    ptrJoueur->IndexFrameArret=0;

    ptrJoueur->CompteurFrameTir=0;
    ptrJoueur->IndexFrameTir=0;

    SPR_setFrame(ptrJoueur->SpriteJ_BAS,(s16)ptrJoueur->IndexFrameMarche);
    SPR_setFrame(ptrJoueur->SpriteJ_HAUT,(s16)ptrJoueur->IndexFrameMarche);

    if(ptrJoueur->Axe==0)
    {
        SPR_setHFlip(ptrJoueur->SpriteJ_BAS, FALSE);
        SPR_setHFlip(ptrJoueur->SpriteJ_HAUT, FALSE);
    }
    else
    {
        SPR_setHFlip(ptrJoueur->SpriteJ_BAS, TRUE);
        SPR_setHFlip(ptrJoueur->SpriteJ_HAUT, TRUE);
    }

    // Anim des tiles
    ptrJoueur->CompteurFrameMarche+=1;

    // MAJ des tiles toutes les 6 images (0 à 5)
    if(ptrJoueur->CompteurFrameMarche>5)
    {
        ptrJoueur->CompteurFrameMarche=0;
        ptrJoueur->IndexFrameMarche+=1;

        // Cycle de FRAME de 0 à 3 (4 étapes)
        if(ptrJoueur->IndexFrameMarche>3)
        {
            ptrJoueur->IndexFrameMarche=0;
        }
    }
}

inline static void TilesDerapage()
{
    SpriteJoueur_ *ptrJoueur=&Joueur;

    SPR_setAnim(ptrJoueur->SpriteJ_BAS,5);
    SPR_setAnim(ptrJoueur->SpriteJ_HAUT,5);

    ptrJoueur->CompteurFrameBloque=0;
    ptrJoueur->IndexFrameBloque=0;

    ptrJoueur->CompteurFrameArret=0;
    ptrJoueur->IndexFrameArret=0;

    ptrJoueur->CompteurFrameMarche=0;
    ptrJoueur->IndexFrameMarche=0;

    ptrJoueur->CompteurFrameTir=0;
    ptrJoueur->IndexFrameTir=0;
}

inline static void TilesSaut()
{
    SpriteJoueur_ *ptrJoueur=&Joueur;

    SPR_setAnim(ptrJoueur->SpriteJ_BAS,3);
    SPR_setAnim(ptrJoueur->SpriteJ_HAUT,3);

    ptrJoueur->CompteurFrameBloque=0;
    ptrJoueur->IndexFrameBloque=0;

    ptrJoueur->CompteurFrameArret=0;
    ptrJoueur->IndexFrameArret=0;

    ptrJoueur->CompteurFrameMarche=0;
    ptrJoueur->IndexFrameMarche=0;

    ptrJoueur->CompteurFrameTir=0;
    ptrJoueur->IndexFrameTir=0;

    if(ptrJoueur->Axe==0)
    {
        SPR_setHFlip(ptrJoueur->SpriteJ_BAS, FALSE);
        SPR_setHFlip(ptrJoueur->SpriteJ_HAUT, FALSE);
    }
    else
    {
        SPR_setHFlip(ptrJoueur->SpriteJ_BAS, TRUE);
        SPR_setHFlip(ptrJoueur->SpriteJ_HAUT, TRUE);
    }
}

inline static void TilesTir()
{
    // Gestion manette
	u16 value=JOY_readJoypad(JOY_1);
    
    SpriteJoueur_ *ptrJoueur=&Joueur;

    
    SPR_setAnim(ptrJoueur->SpriteJ_HAUT,4);

    if((value & BUTTON_DIR)==0)
    {
        SPR_setAnim(ptrJoueur->SpriteJ_BAS,4);
        SPR_setFrame(ptrJoueur->SpriteJ_BAS,1);
    }
    else if(value & (BUTTON_RIGHT | BUTTON_LEFT))
    {
        SPR_setAnim(ptrJoueur->SpriteJ_BAS,2);
        SPR_setFrame(ptrJoueur->SpriteJ_BAS,(s16)ptrJoueur->IndexFrameMarche);
    }
    
    SPR_setFrame(ptrJoueur->SpriteJ_HAUT,1);

    ptrJoueur->CompteurFrameBloque=0;
    ptrJoueur->IndexFrameBloque=0;

    ptrJoueur->CompteurFrameArret=0;
    ptrJoueur->IndexFrameArret=0;

    //ptrJoueur->CompteurFrameMarche=0;
    //ptrJoueur->IndexFrameMarche=0;

    if(ptrJoueur->Axe==0)
    {
        SPR_setHFlip(ptrJoueur->SpriteJ_BAS, FALSE);
        SPR_setHFlip(ptrJoueur->SpriteJ_HAUT, FALSE);
    }
    else
    {
        SPR_setHFlip(ptrJoueur->SpriteJ_BAS, TRUE);
        SPR_setHFlip(ptrJoueur->SpriteJ_HAUT, TRUE);
    }

    // Anim des tiles
    ptrJoueur->CompteurFrameMarche+=1;

    // MAJ des tiles toutes les 6 images (0 à 5)
    if(ptrJoueur->CompteurFrameMarche>5)
    {
        ptrJoueur->CompteurFrameMarche=0;
        ptrJoueur->IndexFrameMarche+=1;

        // Cycle de FRAME de 0 à 3 (4 étapes)
        if(ptrJoueur->IndexFrameMarche>3)
        {
            ptrJoueur->IndexFrameMarche=0;
        }
    }

    // Anim des tiles
    ptrJoueur->CompteurFrameTir+=1;

    // MAJ des tiles toutes les 8 images (0 à 7)
    if(ptrJoueur->CompteurFrameTir>7)
    {
        ptrJoueur->CompteurFrameTir=0;
        ptrJoueur->Phase=ARRET;
        return;
    }
}

inline static void TilesSautTir()
{
    SpriteJoueur_ *ptrJoueur=&Joueur;

    SPR_setAnim(ptrJoueur->SpriteJ_BAS,4);
    SPR_setAnim(ptrJoueur->SpriteJ_HAUT,4);

    SPR_setFrame(ptrJoueur->SpriteJ_BAS,(s16)ptrJoueur->IndexFrameTir);
    SPR_setFrame(ptrJoueur->SpriteJ_HAUT,(s16)ptrJoueur->IndexFrameTir);


    if(ptrJoueur->Axe==0)
    {
        SPR_setHFlip(ptrJoueur->SpriteJ_BAS, FALSE);
        SPR_setHFlip(ptrJoueur->SpriteJ_HAUT, FALSE);
    }
    else
    {
        SPR_setHFlip(ptrJoueur->SpriteJ_BAS, TRUE);
        SPR_setHFlip(ptrJoueur->SpriteJ_HAUT, TRUE);
    }


    // Anim des tiles
    ptrJoueur->CompteurFrameTir+=1;

    // MAJ des tiles toutes les 8 images (0 à 7)
    if(ptrJoueur->CompteurFrameTir>7)
    {
        ptrJoueur->CompteurFrameTir=0;
        ptrJoueur->IndexFrameTir++;

        // Cycle de FRAME de 0 à 1 (2 étapes)
        if(ptrJoueur->IndexFrameTir>1)
        {
            ptrJoueur->IndexFrameTir=0;
            ptrJoueur->Phase=SAUT;
        }
    }
}

inline static void TilesChuteTir()
{
    SpriteJoueur_ *ptrJoueur=&Joueur;

    SPR_setAnim(ptrJoueur->SpriteJ_BAS,4);
    SPR_setAnim(ptrJoueur->SpriteJ_HAUT,4);

    SPR_setFrame(ptrJoueur->SpriteJ_BAS,(s16)ptrJoueur->IndexFrameTir);
    SPR_setFrame(ptrJoueur->SpriteJ_HAUT,(s16)ptrJoueur->IndexFrameTir);


    if(ptrJoueur->Axe==0)
    {
        SPR_setHFlip(ptrJoueur->SpriteJ_BAS, FALSE);
        SPR_setHFlip(ptrJoueur->SpriteJ_HAUT, FALSE);
    }
    else
    {
        SPR_setHFlip(ptrJoueur->SpriteJ_BAS, TRUE);
        SPR_setHFlip(ptrJoueur->SpriteJ_HAUT, TRUE);
    }


    // Anim des tiles
    ptrJoueur->CompteurFrameTir+=1;

    // MAJ des tiles toutes les 8 images (0 à 7)
    if(ptrJoueur->CompteurFrameTir>7)
    {
        ptrJoueur->CompteurFrameTir=0;
        ptrJoueur->IndexFrameTir++;

        // Cycle de FRAME de 0 à 1 (2 étapes)
        if(ptrJoueur->IndexFrameTir>1)
        {
            ptrJoueur->IndexFrameTir=0;
            ptrJoueur->Phase=CHUTE;
        }
    }
}

inline static void TilesTouche()
{
    SpriteJoueur_ *ptrJoueur=&Joueur;

    SPR_setAnim(ptrJoueur->SpriteJ_BAS,6);
    SPR_setAnim(ptrJoueur->SpriteJ_HAUT,6);

    SPR_setFrame(ptrJoueur->SpriteJ_BAS,(s16)ptrJoueur->IndexFrameTouche);
    SPR_setFrame(ptrJoueur->SpriteJ_HAUT,(s16)ptrJoueur->IndexFrameTouche);

    ptrJoueur->CompteurFrameBloque=0;
    ptrJoueur->IndexFrameBloque=0;

    ptrJoueur->CompteurFrameArret=0;
    ptrJoueur->IndexFrameArret=0;

    ptrJoueur->CompteurFrameMarche=0;
    ptrJoueur->IndexFrameMarche=0;

    ptrJoueur->CompteurFrameTir=0;
    ptrJoueur->IndexFrameTir=0;

    // Anim des tiles
    ptrJoueur->CompteurFrameTouche+=1;

    // MAJ des tiles toutes les 8 images (0 à 7)
    if(ptrJoueur->CompteurFrameTouche>7)
    {
        ptrJoueur->CompteurFrameTouche=0;
        ptrJoueur->IndexFrameTouche++;

        // Cycle de FRAME de 0 à 3 (4 étapes)
        if(ptrJoueur->IndexFrameTouche>3)
        {
            ptrJoueur->IndexFrameTouche=0;
        }
    }
}

inline static void TilesApparition()
{
    SpriteJoueur_ *ptrJoueur=&Joueur;

    SPR_setAnim(ptrJoueur->SpriteJ_BAS,7);
    SPR_setAnim(ptrJoueur->SpriteJ_HAUT,7);

    // TILES DU DRAGON //
    ptrJoueur->CompteurFrameTouche=0;
    ptrJoueur->IndexFrameTouche=0;

    //
}

inline static void TilesDragon()
{
    SpriteDragon_ *ptrDragon=&Dragon;

    SPR_setFrame(ptrDragon->SpriteD,(s16)ptrDragon->IndexFrameVol);

    // Anim des tiles
    ptrDragon->CompteurFrameVol+=1;

    // MAJ des tiles toutes les 6 images (0 à 5)
    if(ptrDragon->CompteurFrameVol>5)
    {
        ptrDragon->CompteurFrameVol=0;
        ptrDragon->IndexFrameVol+=1;

        // Cycle de FRAME de 0 à 1 (2 étapes)
        if(ptrDragon->IndexFrameVol>1)
        {
            ptrDragon->IndexFrameVol=0;
        }
    }
}

inline static void TilesSplash()
{
    SpriteDragon_ *ptrDragon=&Dragon;
    SpriteSplash_ *ptrSplash=&Splash;

    SPR_setFrame(ptrSplash->SpriteS,(s16)ptrSplash->IndexFrameSplash);

    ptrSplash->CompteurFrameSplash+=1;

    // MAJ des tiles toutes les 3 images (0 à 2)
    if(ptrSplash->CompteurFrameSplash>2)
    {
        ptrSplash->CompteurFrameSplash=0;
        ptrSplash->IndexFrameSplash+=1;

        // Cycle de FRAME de 0 à 7 (8 étapes)
        if(ptrSplash->IndexFrameSplash>7)
        {
            ptrSplash->IndexFrameSplash=0;
            ptrSplash->Init=0;

            ptrSplash->PosX=48;
            ptrSplash->PosY=-32;

            SPR_setPosition(ptrSplash->SpriteS, ptrSplash->PosX, ptrSplash->PosY);

            ptrDragon->Phase=VOL_DRAGON;

            Maj_Vies();
        }
    }
}

inline static void TilesAura()
{
    SpriteAura_ *ptrAura=&Aura;

    SPR_setFrame(ptrAura->SpriteA,(s16)ptrAura->IndexFrameAura);

    ptrAura->CompteurFrameAura+=1;

    // MAJ des tiles toutes les 2 images (0 à 1)
    if(ptrAura->CompteurFrameAura>1)
    {
        ptrAura->CompteurFrameAura=0;
        ptrAura->IndexFrameAura+=1;

        // Cycle de FRAME de 0 à 3 (4 étapes)
        if(ptrAura->IndexFrameAura>3)
        {
            ptrAura->IndexFrameAura=0;
            ptrAura->Init=0;

            ptrAura->PosX=0;
            ptrAura->PosY=-24;

        }
    }

}

void TilesJoueur()
{
    SpriteJoueur_ *ptrJoueur=&Joueur;
    SpriteDragon_ *ptrDragon=&Dragon;
    SpriteSplash_ *ptrSplash=&Splash;
    SpriteAura_ *ptrAura=&Aura;

    //--------------//
    //    DRAGON    //
    //--------------//
    if(ptrDragon->Phase!=ATTENTE_DRAGON)
    {
        TilesDragon();
    }


     //--------------//
    //    SPLASH    //
    //--------------//
    if(ptrSplash->Init==1)
    {
        TilesSplash();
    }



    //--------------//
    //     AURA     //
    //--------------//
    if(ptrAura->Init==1)
    {
        TilesAura();
    }


    //--------------//
    //    JOUEUR    //
    //--------------//

    ///////////////
    //   ARRET   //
    ///////////////
    if(ptrJoueur->Phase==ARRET)
    {
        // BLOQUE
        if(ptrJoueur->PosX==-11)
        {
            if(CamPosX!=-4336)
            {
                TilesBloque();
                return;
            }
            else
            {
                TilesArret();
                return;
            }
        }

        // ARRET
        else
        {
            if(movX==0)
            {
                TilesArret();
                return;
            }
            else
            {
                TilesMarche();
                return;
            }
        }
    }

    ////////////////
    //   MARCHE   //
    ////////////////
    else if(ptrJoueur->Phase==MARCHE)
    {
        // SI JOUEUR VA VERS LA DROITE
        if(ptrJoueur->Axe==0)
        {
            if(movX < FIX32(0))
            {
                TilesDerapage();
                return;
            }
            else
            {
                TilesMarche();
                return;
            }
        }

        // SI JOUEUR VA VERS LA GAUCHE
        else if(ptrJoueur->Axe==1)
        {
            if(movX > FIX32(0))
            {
                TilesDerapage();
                return;
            }
            else
            {
                TilesMarche();
                return;
            }
        }
    }

    ////////////////
    //     SAUT   //
    ////////////////
    else if(ptrJoueur->Phase==SAUT)
    {
        TilesSaut();
        return;
    }

    //////////////////////
    //        TIR       //
    //////////////////////
    else if(ptrJoueur->Phase==TIR)
    {
        TilesTir();
        return;
    }

    ///////////////////////
    //     SAUT + TIR    //
    ///////////////////////
    else if(ptrJoueur->Phase==SAUT_TIR)
    {
        TilesSautTir();
        return;
    }

    ////////////////
    //    CHUTE   //
    ////////////////
    else if(ptrJoueur->Phase==CHUTE)
    {
        TilesSaut();
        return;
    }

    ////////////////////////
    //     CHUTE + TIR    //
    ////////////////////////
    else if(ptrJoueur->Phase==CHUTE_TIR)
    {
        TilesChuteTir();
        return;
    }

    /////////////////
    //    TOUCHE   //
    /////////////////
    else if(ptrJoueur->Phase==TOUCHE)
    {
        TilesTouche();
        return;
    }

    /////////////////////
    //    APPARITION   //
    /////////////////////
    else if(ptrJoueur->Phase==APPARITION)
    {
        SpriteSplash_ *ptrSplash=&Splash;

        // SI LE SPLASH EST TERMINE //
        if(ptrSplash->Init==0)
        {
            TilesApparition();
            return;
        }
    }
}


//----------------------------------------------------//
//                       MANETTE                      //
//----------------------------------------------------//
// Gestion manette écran titre //
void Titre_Callback(u16 joy, u16 changed, u16 state)
{
    if(joy == JOY_1)
    {

        // BOUTONS //
        if(Menu_Titre == 1)
        {
            // BOUTON BAS //
            if( changed & state & BUTTON_DOWN )
            {
                if(Pos_Menu_Titre == 0)
                {
                    Pos_Menu_Titre = 1;
                    SPR_setPosition(sprite_Bouton_Options,112,104);
                }

                else if(Pos_Menu_Titre == 1)
                {
                    Pos_Menu_Titre = 2;
                    SPR_setPosition(sprite_Bouton_Options,112,120);
                }
            }

            // BOUTON HAUT //
            else if( changed & state & BUTTON_UP )
            {
                if(Pos_Menu_Titre == 1)
                {
                    Pos_Menu_Titre = 0;
                    SPR_setPosition(sprite_Bouton_Options,112,88);
                }

                else if(Pos_Menu_Titre == 2)
                {
                    Pos_Menu_Titre = 1;
                    SPR_setPosition(sprite_Bouton_Options,112,104);
                }
            }

            // BOUTON DROITE //
            else if( changed & state & (BUTTON_RIGHT | BUTTON_C) )
            {
                if(Pos_Menu_Titre == 0)
                {
                    if( Nb_Vies_Options < 5 )
                    {
                        Nb_Vies_Options += 1;
                        Nb_Vies = Nb_Vies_Options;
                        SPR_setFrame( sprite_Nb_Player_Options , Nb_Vies_Options );
                    }
                }

                else if(Pos_Menu_Titre == 1)
                {
                    if( Nb_Credits < 5 )
                    {
                        Nb_Credits += 1;
                        SPR_setFrame( sprite_Nb_Credits_Options , Nb_Credits );
                    } 
                }
            }

            // BOUTON GAUCHE //
            else if( changed & state & ( BUTTON_LEFT | BUTTON_B ) )
            {
                if(Pos_Menu_Titre == 0)
                {
                    if( Nb_Vies_Options > 3 )
                    {
                        Nb_Vies_Options -= 1;
                        Nb_Vies = Nb_Vies_Options;
                        SPR_setFrame( sprite_Nb_Player_Options , Nb_Vies_Options );
                    }
                }

                else if(Pos_Menu_Titre == 1)
                {
                    if( Nb_Credits > 3 )
                    {
                        Nb_Credits -= 1;
                        SPR_setFrame( sprite_Nb_Credits_Options , Nb_Credits );
                    } 
                }
            }

        }



        // START //
        if (changed & state & BUTTON_START)
        {        
            // on quitte BOUCLE ECRAN TITRE //
            if(Menu_Titre == 1)
            {
                if(Pos_Menu_Titre == 2)
                {
                    CamPosX=0;
                    Exit_Titre=1;
                }
            }
            
            // on rentre dans le menu OPTIONS //
            else
            {
                Menu_Titre = 1;
               
                SPR_setPosition(sprite_Bouton_Options,112,88);

                SPR_setPosition(sprite_Player_Options,128,88);
                SPR_setPosition(sprite_Credits_Options,128,104);
                SPR_setPosition(sprite_Start_Options,128,120);

                SPR_setPosition(sprite_Nb_Player_Options,200,88);
                SPR_setPosition(sprite_Nb_Credits_Options,200,104);               

                SPR_setPosition(sprite_Menu_Titre,104,80);
            }
        }


        
    }
}

// Gestion manette écran sélection //
void Selection_Callback(u16 joy, u16 changed, u16 state)
{
    u16 i;

    if(joy == JOY_1)
    {
        if(Exit_Selection==0)
        {
            // Si DROITE //
            if ( changed & state & BUTTON_RIGHT && selectJoueur == 0 )
            {
                // scrolling par tile
                VDP_setHorizontalScrollTile(BG_A, 13, scrollOffset_TILE_SELECTION, 10, CPU);

                for (i=0; i<10; i++)
                {
                    scrollOffset_TILE_SELECTION[i]=0;
                }

                selectJoueur=1;
                //StatutJoy=0;
            }

            // Si GAUCHE //
            if (changed & state & BUTTON_LEFT && selectJoueur == 1 )
            {
                // scrolling par tile
                VDP_setHorizontalScrollTile(BG_A, 13, scrollOffset_TILE_SELECTION, 10, CPU);

                for (i=0; i<10; i++)
                {
                    scrollOffset_TILE_SELECTION[i]=128;
                }

                selectJoueur=0;
            }


            if (changed & state & (BUTTON_A | BUTTON_B | BUTTON_C | BUTTON_START))
            {
                Exit_Selection=1;
            }
        }
    }    
}

// Gestion manette séquences de Plateforme //
void Game_PF_Callback(u16 joy, u16 changed, u16 state)
{
    SpriteJoueur_ *ptrJoueur=&Joueur;
    SpriteDragon_ *ptrDragon=&Dragon;
    SpriteAura_ *ptrAura=&Aura;

    if(joy == JOY_1)
    {
        // If not in CONTINUE phase nor GAMEOVER //
        if(SWITCH_CONTINUE == 0 && SWITCH_GAMEOVER == 0)
        {
            // If player hasn't reached the end of the level, the joypad drives the player //
            if(CamPosX != -4336)
            {
                // START //
                if (changed & state & BUTTON_START)
                {
                    // Enter PAUSE mode //
                    if (PauseJeu==0)
                    {
                        PauseJeu=1;

                        SPR_setPosition(sprite_Pause, 140, 116);

                        XGM_pausePlay();

                    }
                    // Exit PAUSE mode //
                    else if (PauseJeu==1)
                    {
                        PauseJeu=0;

                        SPR_setPosition(sprite_Pause, -40, 0);

                        XGM_resumePlay();
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
                        XGM_startPlayPCM(AUDIO_SAUT, 15, SOUND_PCM_CH4);
                    }

                    //**//
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
                        //**//
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

                        //Tir_OK=1;

                        // L'AURA SE DECLENCHE
                        if(ptrAura->Init==0)
                        {
                            ptrAura->Init=1;
                        }

                        TirJoueur();
                    }

                    // SI JOUEUR ARRET OU MARCHE //
                    else if(ptrJoueur->Phase==ARRET || ptrJoueur->Phase==MARCHE)
                    {
                        // MARCHE + TIR
                        ptrJoueur->Phase=TIR;

                        //Tir_OK=1;

                        // L'AURA SE DECLENCHE
                        if(ptrAura->Init==0)
                        {
                            ptrAura->Init=1;
                        }

                        TirJoueur();
                    }
            
                    // SI JOUEUR ARRET OU MARCHE //
                    else if(ptrJoueur->Phase==CHUTE)
                    {
                        // MARCHE + TIR
                        ptrJoueur->Phase=CHUTE_TIR;

                        //Tir_OK=1;

                        // L'AURA SE DECLENCHE
                        if(ptrAura->Init==0)
                        {
                            ptrAura->Init=1;
                        }

                        TirJoueur();
                    }
                }
            }
        }

        // If in CONTINUE phase //
        else if(SWITCH_CONTINUE == 1)
        {
            // If there are remaining CONTINUE //
            if(Nb_Credits != 0)
            {
                // If the CONTINUE counter hasn't reached the end (600) //
                if(Compteur_Continue < 600)
                {
                    // If A B C START buttons are pressed //
                    if (changed & state & (BUTTON_A | BUTTON_B | BUTTON_C | BUTTON_START))
                    {
                        // Player loses 1 CONTINUE //
                        Nb_Credits -= 1;

                        Nb_Vies = Nb_Vies_Options;

                        // Clears credits sprites //
                        SPR_setPosition(sprite_Credits, 0, -8);
                        SPR_setPosition(sprite_Nb_Credits, 0, -8);

                        // Refill lives //
                        InitVies();

                        // Refill energy bar //
                        Init_BarreEnergie();

                        // Exit CONTINUE Phase //
                        SWITCH_CONTINUE = 0;

                        //SYS_doVBlankProcess();
                    }
                }
            }

            /*else
            {
                SPR_releaseSprite(sprite_Credits);
                SPR_releaseSprite(sprite_Nb_Credits);
                Afficher_GameOver();
            }*/
        }      
    }    
}



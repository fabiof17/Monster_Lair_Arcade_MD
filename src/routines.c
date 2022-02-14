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


void VDP_drawInt(u16 valeur,u8 zeros,u8 x, u8 y)
{
	intToStr(valeur,texteSortie,zeros); //MIN -500.000.000 - MAX 500.000.000
	VDP_drawText(texteSortie,x,y);
}



// BARRE ENERGIE //
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

            VDP_loadTileSet(ptrBARRE, AdresseVram_BarreEnergie, DMA);
            VDP_setTileMapEx(WINDOW, image_BARRE_VIERGE.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, AdresseVram_BarreVierge), 4 + (u16)valeurEnergie, 3, 0, 0, 1, 2, DMA);
    
        }
    }
}

void Init_BarreEnergie()
{
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

    VDP_loadTileSet(&tileset_BARRE_VERTE1, AdresseVram_BarreEnergie, DMA);
    


    u8 i;
    
    for (i=0; i<ENERGIE_DEPART; i++)
    {
        VDP_setTileMapEx(WINDOW, image_BARRE_VERTE1.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, AdresseVram_BarreEnergie), 4+i, 3, 0, 0, 1, 2, DMA);
    }

    for (i=ENERGIE_DEPART; i<ENERGIE_DEPART+7; i++)
    {
        VDP_setTileMapEx(WINDOW, image_BARRE_VIERGE.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, AdresseVram_BarreVierge), 4+i, 3, 0, 0, 1, 2, DMA);
    }
}

void Vider_BarreEnergie()
{
    VDP_loadTileSet(&tileset_BARRE_VIERGE, AdresseVram_BarreEnergie, DMA);
}



// SCROLLING //
void Scrolling_Niveau1()
{
    u16 i;

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
            // BG_B
            VDP_setTileMapColumnEx(BG_B, image_NIVEAU1_BGB.tilemap, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, 16), (tilemapOffset>>1)-2, 62+(tilemapOffset>>1), 7, 20, DMA_QUEUE);
            VDP_setTileMapColumnEx(BG_B, image_NIVEAU1_BGB.tilemap, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 16), (tilemapOffset>>1)-2, 62+(tilemapOffset>>1), 27, 4, DMA_QUEUE);

            // BG_A
            // TETE DE DRAGON EN PRIORITE 1
            if(tilemapOffset>482)
            {
                VDP_setTileMapColumnEx(BG_A, image_NIVEAU1_BGA.tilemap, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, 191), tilemapOffset-2, 62+tilemapOffset, 7, 21, DMA_QUEUE);
                //VDP_setTileMapColumnEx(BG_A, image_NIVEAU1_BGA.tilemap, TILE_ATTR_FULL(PAL3, FALSE, FALSE, FALSE, 191), tilemapOffset-2, 62+tilemapOffset, 20, 8, DMA_QUEUE);
            }
            else
            {
                VDP_setTileMapColumnEx(BG_A, image_NIVEAU1_BGA.tilemap, TILE_ATTR_FULL(PAL3, FALSE, FALSE, FALSE, 191), tilemapOffset-2, 62+tilemapOffset, 7, 21, DMA_QUEUE);
            }

        }
    }
}

void ChgtPalette_Niveau1()
{
    // CHANGEMENTS PALETTE

     if(CamPosX<-700 && CamPosX>-704)
    {
        PAL_setPaletteColors(16, &palette_NIVEAU1_BULOT, DMA);
    }

    else if(CamPosX<-1110 && CamPosX>-1114)
    {
        PAL_setPaletteColors(16, &palette_NIVEAU1_ESCARGOT, DMA);
    }

    else if(CamPosX<-2600 && CamPosX>-2604)
    {
        PAL_setPaletteColors(16, &palette_NIVEAU1_PELICAN, DMA);
    }

    else if(CamPosX<-3700 && CamPosX>-3704)
    {
        PAL_setPaletteColors(16, &palette_NIVEAU1_BULOT, DMA);
    }

    else if(CamPosX<-4016 && CamPosX>-4020)
    {
        PAL_setPaletteColors(48, &palette_NIVEAU1_BGA2, DMA);
    }
}



// COLLISIONS //
void MAJ_PtsCollision_Joueur()
{
    SpriteJoueur_ *ptrJoueur=&Joueur;

    // POINT BAS GAUCHE //
    if(ptrJoueur->PosX>=0)
    {
        ptrJoueur->pt_Coll1_X=fix32ToInt(positionX)+8;
    }
    else
    {
        ptrJoueur->pt_Coll1_X=fix32ToInt(positionX)+11;
    }
    ptrJoueur->pt_Coll1_Y=fix32ToInt(positionY)+10;


    // POINT BAS DROITE //
    ptrJoueur->pt_Coll2_X=fix32ToInt(positionX)+21;
    ptrJoueur->pt_Coll2_Y=ptrJoueur->pt_Coll1_Y;


    posTileY=ptrJoueur->pt_Coll1_Y>>3;
}

void Collision_Decor()
{
    u16 *ptrtileID_G=&tileID_G;
    u16 *ptrtileID_D=&tileID_D;
    //u8 offsetTilemap;

    SpriteJoueur_ *ptrJoueur=&Joueur;

    // Récuperation ID de tile de collision
    /*if(CamPosX%8==0)
    {
        offsetTilemap=0;
    }
    else
    {
        offsetTilemap=1;
    }*/

    *ptrtileID_G=MAP_getTile( tilemapCollision , ((ptrJoueur->pt_Coll1_X - CamPosX) >> 3) , posTileY ) & TILE_INDEX_MASK;
    *ptrtileID_D=MAP_getTile( tilemapCollision , ((ptrJoueur->pt_Coll2_X - CamPosX) >> 3) , posTileY ) & TILE_INDEX_MASK;
}

void Collision_Ennemis()
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
            for(i=0;i<MAX_ENNEMIS;i++)
            {
                SpriteEnnemi_ *ptrEnnemi=&Ennemi[i];

                // Si le sprite a été créé
                if(ptrEnnemi->Init==1)
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
                        if(ptrJoueur->PosX+16 <= ptrEnnemi->PosX+24)
                        {
                            // LIMITE HAUT DU SPRITE ENNEMI
                            if(ptrJoueur->PosY-8 >= ptrEnnemi->PosY)
                            {
                                //
                                if(ptrJoueur->PosY-24 <= ptrEnnemi->PosY+24)
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

void Collision_Plateformes()
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
                if(ptrJoueur->pt_Coll1_X >= ptrPlateforme->pt_Coll1_X)
                {
                    // Si pt collision X G joueur <= pt collision X D plateforme
                    if((ptrJoueur->pt_Coll1_X <= ptrPlateforme->pt_Coll2_X))
                    {
                        // Si pt collision Y G joueur >= pt collision Y G plateforme
                        if(ptrJoueur->pt_Coll1_Y >= ptrPlateforme->pt_Coll1_Y)
                        {
                            // Si pt collision Y G joueur >= pt collision Y G plateforme +7
                            if(ptrJoueur->pt_Coll1_Y <= ptrPlateforme->pt_Coll1_Y+15)
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
                else if(ptrJoueur->pt_Coll2_X >= ptrPlateforme->pt_Coll1_X)
                {
                    // Si pt collision X D joueur <= pt collision X D plateforme
                    if((ptrJoueur->pt_Coll2_X <= ptrPlateforme->pt_Coll2_X))
                    {
                        // Si pt collision Y D joueur >= pt collision Y G plateforme
                        if(ptrJoueur->pt_Coll2_Y >= ptrPlateforme->pt_Coll1_Y)
                        {
                            // Si pt collision Y D joueur >= pt collision Y G plateforme +7
                            if(ptrJoueur->pt_Coll2_Y <= ptrPlateforme->pt_Coll1_Y+15)
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



// SPRITES NIVEAU 1 //
void CreaSprites_Niveau1()
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
                    ptrEnnemi->Init=1;
                    ptrEnnemi->Etat=0;
                    ptrEnnemi->PointsVie=1;

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


                    ptrEnnemi->SpriteE = SPR_addSprite(AdrTilesEnnemi[ptrEnnemi->ID-1], ptrEnnemi->PosX, ptrEnnemi->PosY, TILE_ATTR(paletteEnnemis_Niveau1[(ptrEnnemi->ID)-1], FALSE, FALSE, FALSE));


                    // POULPE 1
                    if(ptrEnnemi->ID==5)
                    {
                        ptrEnnemi->ptrPosition=&anim_POULPE1[0];
                    }
                    // POULPE 2
                    else if(ptrEnnemi->ID==6)
                    {
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

void MvtEnnemis_Niveau1()
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

            // Si le sprite a été créé
            if(ptrEnnemi->Init==1)
            {
                // On vérifie le type d'ennemi
                switch(ptrEnnemi->ID)
                {
                    /////////////////
                    // ESCARGOTS H //
                    /////////////////
                    case 1:

                        // Position X
                        ptrEnnemi->PosX-=vitesseScrolling;
                        SPR_setPosition(ptrEnnemi->SpriteE, ptrEnnemi->PosX, ptrEnnemi->PosY);

                        // Anim des tiles
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

                        // Si l'ennemi sort de l'écran
                        // 3 tiles (24 px) de large
                        if(ptrEnnemi->PosX<-24 || ptrEnnemi->PosY>224 )
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                            nb_Ennemis-=1;
                        }
                        break;

                    ////////////
                    // BULOTS //
                    ////////////
                    case 2:

                        // Position X
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

                        // Anim des tiles
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

                        // Si l'ennemi sort de l'écran
                        // 3 tiles (24 px) de large
                        if(ptrEnnemi->PosX<-24 || ptrEnnemi->PosY>224 )
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                            nb_Ennemis-=1;
                        }
                        break;

                    /////////////////
                    // ESCARGOTS V //
                    /////////////////
                    case 3:

                        // Position X
                        ptrEnnemi->PosX-=vitesseScrolling;

                        ptrEnnemi->CompteurPosition+=1;

                        // Position Y
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

                        SPR_setPosition(ptrEnnemi->SpriteE, ptrEnnemi->PosX, ptrEnnemi->PosY);

                        // Anim des tiles
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

                        // Si l'ennemi sort de l'écran
                        // 3 tiles (24 px) de large
                        if(ptrEnnemi->PosX<-24 || ptrEnnemi->PosY>224 )
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                            nb_Ennemis-=1;
                        }
                        break;

                    ///////////
                    // MORSE //
                    ///////////
                    case 4:

                        // Position X
                        ptrEnnemi->PosX -= vitesseScrolling;

                        SPR_setPosition(ptrEnnemi->SpriteE, ptrEnnemi->PosX, ptrEnnemi->PosY);
                        /*
                        // Anim des tiles
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

                        // Si l'ennemi sort de l'écran
                        // 6 tiles (48 px) de large
                        if(ptrEnnemi->PosX<-48 || ptrEnnemi->PosY>224)
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                            nb_Ennemis-=1;
                        }
                        break;

                    //////////////
                    // POULPE 1 //
                    //////////////
                    case 5:

                        ptrEnnemi->PosX -= vitesseScrolling;
                        ptrEnnemi->PosY += *(ptrEnnemi->ptrPosition);

                        SPR_setPosition(ptrEnnemi->SpriteE, ptrEnnemi->PosX, ptrEnnemi->PosY);



                        ptrEnnemi->ptrPosition++;

                        if(ptrEnnemi->ptrPosition >= &anim_POULPE1[MAX_ETAPES_POULPE1])
                        {
                            ptrEnnemi->ptrPosition=&anim_POULPE1[0];
                        }



                        // Si l'ennemi sort de l'écran
                        // 4 tiles (32 px) de large
                        if(ptrEnnemi->PosX<-32 || ptrEnnemi->PosY>224)
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                            nb_Ennemis-=1;
                            //break;
                        }



                        /*
                        // Anim des tiles
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
                        break;


                    //////////////
                    // POULPE 2 //
                    //////////////
                    case 6:

                        // Position X
                        ptrEnnemi->PosX -= vitesseScrolling;

                        // Position Y
                        ptrEnnemi->PosY += *(ptrEnnemi->ptrPosition);

                        SPR_setPosition(ptrEnnemi->SpriteE, ptrEnnemi->PosX, ptrEnnemi->PosY);



                        ptrEnnemi->ptrPosition++;

                        if(ptrEnnemi->ptrPosition >= &anim_POULPE2[MAX_ETAPES_POULPE2])
                        {
                            ptrEnnemi->ptrPosition=&anim_POULPE2[0];
                        }



                        // Si l'ennemi sort de l'écran
                        // 4 tiles (32 px) de large
                        if(ptrEnnemi->PosX<-32 || ptrEnnemi->PosY>224)
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                            nb_Ennemis-=1;
                        }



                        /*
                        // Anim des tiles
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
                        break;

                    /////////////
                    // PELICAN //
                    /////////////
                    case 7:

                        // Position X
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

                        // Anim des tiles
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

                        // Si l'ennemi sort de l'écran
                        // 3 tiles (24 px) de large
                        if(ptrEnnemi->PosX<-24 || ptrEnnemi->PosY>224)
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                            nb_Ennemis-=1;
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

            PAL_setColor( 10 , 0x000C );
            PAL_setColor( 13 , 0x06CC );
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

            PAL_setColor( 10 , 0x000C );
            PAL_setColor( 13 , 0x06CC );
        }
    }

}



// TIRS //
void MvtTirs()
{
    //
}



// JOUEUR //
void Phases_Joueur()
{
    // Gestion manette
	u16 value=JOY_readJoypad(JOY_1);

    SpriteJoueur_ *ptrJoueur=&Joueur;

    ///////////////
    //   ARRET   //
    ///////////////
    if((value & BUTTON_DIR)==0)
    {
        if(ptrJoueur->Phase!=SAUT && ptrJoueur->Phase!=TIR && ptrJoueur->Phase!=SAUT_TIR && ptrJoueur->Phase!=CHUTE && ptrJoueur->Phase!=TOUCHE && ptrJoueur->Phase!=APPARITION)
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

        Collision_Plateformes();

        // SI PAS DE CONTACT AVEC PLATEFORME
        if(contactPlt_OK == 0)
        {
            //--------------------------//
            //     COLLISIONS DECOR     //
            //--------------------------//

            // TEST COLLISION DECOR //
            Collision_Decor();


            // SI LE JOUEUR CHUTE
            if(tileID_G==0 && tileID_D==0)
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
            Collision_Ennemis();
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

        Collision_Plateformes();


        // SI PAS DE CONTACT AVEC PLATEFORME
        if(contactPlt_OK == 0)
        {
            //--------------------------//
            //     COLLISIONS DECOR     //
            //--------------------------//

            // TEST COLLISION DECOR //
            Collision_Decor();


            // SI LE JOUEUR CHUTE
            if(tileID_G==0 && tileID_D==0)
            {
                // PHASE CHUTE
                ptrJoueur->Phase=CHUTE;
                return;
            }

            // SI LE JOUEUR NE CHUTE PAS
            else if(tileID_G==1 || tileID_D==1)
            {
                ptrJoueur->PosY = (posTileY<<3)-8;
                positionY=intToFix32(ptrJoueur->PosY);
                MAJ_PtsCollision_Joueur();
            }
        }

        ptrJoueur->ptrPosition=&anim_SAUT[0];


        if(ptrJoueur->Invincible==0)
        {
            Collision_Ennemis();
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

        Collision_Plateformes();

        

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
                Collision_Decor();


                // SI LE JOUEUR CHUTE //
                if(tileID_G==1 || tileID_D==1)
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
            Collision_Ennemis();
        }

        // JOUEUR TOUCHE BAS DE L'ÉCRAN //
        if(ptrJoueur->PosY>192)
        {
            // SPLASH //
            ptrSplash->Init=1;
            ptrSplash->PosX=ptrJoueur->PosX;
            ptrSplash->PosY=168;
            SPR_setPosition(ptrSplash->SpriteS, ptrSplash->PosX, ptrSplash->PosY);

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

            // CHANGEMENT PALETTE //
            //PAL_setColor( 10 , 0x0A4C );
            //PAL_setColor( 13 , 0x0C6C );
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

        Collision_Plateformes();


        // SI PAS DE CONTACT AVEC PLATEFORME
        if(contactPlt_OK == 0)
        {
            //--------------------------//
            //     COLLISIONS DECOR     //
            //--------------------------//

            // TEST COLLISION DECOR //
            Collision_Decor();


            // SI LE JOUEUR CHUTE
            if(tileID_G==0 && tileID_D==0)
            {
                // PHASE CHUTE
                ptrJoueur->Phase=CHUTE;
                return;
            }

            // SI LE JOUEUR NE CHUTE PAS
            else if(tileID_G==1 || tileID_D==1)
            {
                ptrJoueur->PosY = (posTileY<<3)-8;
                positionY=intToFix32(ptrJoueur->PosY);
                MAJ_PtsCollision_Joueur();
            }
        }

        if(ptrJoueur->Invincible==0)
        {
            Collision_Ennemis();
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

        Collision_Plateformes();

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
                Collision_Decor();


                // SI LE JOUEUR CHUTE //
                if(tileID_G==1 || tileID_D==1)
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
            Collision_Ennemis();
        }

        // JOUEUR TOUCHE BAS DE L'ÉCRAN //
        if(ptrJoueur->PosY>192)
        {
            // SPLASH //
            ptrSplash->Init=1;
            ptrSplash->PosX=ptrJoueur->PosX;
            ptrSplash->PosY=168;
            SPR_setPosition(ptrSplash->SpriteS, ptrSplash->PosX, ptrSplash->PosY);

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

            // CHANGEMENT PALETTE //
            //PAL_setColor( 10 , 0x0A4C );
            //PAL_setColor( 13 , 0x0C6C );
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

            // ON SOUSTRAIT 'ACCEL_D' A 'movX'
            movX -= ACCEL_D;

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

        Collision_Plateformes();


        // SI PAS DE CONTACT AVEC PLATEFORME
        if(contactPlt_OK == 0)
        {
            //--------------------------//
            //     COLLISIONS DECOR     //
            //--------------------------//

            // TEST COLLISION DECOR //
            Collision_Decor();


            // SI LE JOUEUR TOUCHE LE SOL
            if(tileID_G==1 || tileID_D==1)
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

                // CHANGEMENT PALETTE //
                //PAL_setColor( 10 , 0x0A4C );
                //PAL_setColor( 13 , 0x0C6C );
            }
        }

        if(ptrJoueur->Invincible==0)
        {
            Collision_Ennemis();
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
            // SPLASH //
            ptrSplash->Init=1;
            ptrSplash->PosX=ptrJoueur->PosX;
            ptrSplash->PosY=168;
            SPR_setPosition(ptrSplash->SpriteS, ptrSplash->PosX, ptrSplash->PosY);

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

            // CHANGEMENT PALETTE //
            //PAL_setColor( 10 , 0x0A4C );
            //PAL_setColor( 13 , 0x0C6C );
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
                // CHANGEMENT PALETTE //
                PAL_setColor( 10 , 0x0A4C );
                PAL_setColor( 13 , 0x0C6C );
            }
        }

        //--------------------------//
        //           DRAGON         //
        //--------------------------//
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
    // SI LE JOUEUR ATTEINT LA DROITE DE L'ECRAN
    else if(positionX > MAX_POS_D)
    {
        // IL EST BLOQUÉ
        positionX = MAX_POS_D;

        vitesseScrolling=2;
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
    //SPR_setPosition(sprite_repere_BG, ptrJoueur->pt_Coll1_X, ptrJoueur->pt_Coll1_Y-PosYinvincible-7);
    //SPR_setPosition(sprite_repere_BD, ptrJoueur->pt_Coll2_X-7, ptrJoueur->pt_Coll1_Y-PosYinvincible-7);

    // DRAGON //
    SPR_setPosition(ptrDragon->SpriteD, ptrDragon->PosX, ptrDragon->PosY);
    // SPLASH //
    SPR_setPosition(ptrSplash->SpriteS, ptrSplash->PosX, ptrSplash->PosY);
    // AURA //
    SPR_setPosition(ptrAura->SpriteA, ptrAura->PosX, ptrAura->PosY);
}



// TILES //
void TilesBloque()
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

void TilesArret()
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

void TilesMarche()
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

void TilesDerapage()
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

void TilesSaut()
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

void TilesTir()
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

void TilesSautTir()
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

void TilesTouche()
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

void TilesApparition()
{
    SpriteJoueur_ *ptrJoueur=&Joueur;

    SPR_setAnim(ptrJoueur->SpriteJ_BAS,7);
    SPR_setAnim(ptrJoueur->SpriteJ_HAUT,7);

    // TILES DU DRAGON //
    ptrJoueur->CompteurFrameTouche=0;
    ptrJoueur->IndexFrameTouche=0;

    //
}

void TilesDragon()
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

void TilesSplash()
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

            ptrDragon->Phase=VOL_DRAGON;
        }
    }
}

void TilesAura()
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

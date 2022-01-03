#include <genesis.h>
#include "main.h"
#include "init.h"
#include "variables.h"
#include "palettes.h"
#include "maps_NIVEAU1.h"
#include "tilemaps_ennemis.h"
#include "animation_ennemis.h"
#include "sprites_JEU.h"
//#include <GestionPAD.h>


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

    tilemapOffset=(CamPosX>>3)*-1;




    // MISE A JOUR TILEMAP //
    if(CamPosX>-4336)
    {

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
        //if (CamPosX%8==0)
        //{
            if (tilemapOffset>0 && tilemapOffset<520)
            {
                // BG_B
                VDP_setTileMapColumnEx(BG_B, image_NIVEAU1_BGB.tilemap, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, 16), (tilemapOffset>>1)-2, 62+(tilemapOffset>>1), 7, 20, DMA_QUEUE);
                VDP_setTileMapColumnEx(BG_B, image_NIVEAU1_BGB.tilemap, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 16), (tilemapOffset>>1)-2, 62+(tilemapOffset>>1), 27, 4, DMA_QUEUE);

                // BG_A
                // TETE DE DRAGON EN PRIORITE 1
                if(tilemapOffset>499)
                {
                    VDP_setTileMapColumnEx(BG_A, image_NIVEAU1_BGA.tilemap, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, 191), tilemapOffset-2, 62+tilemapOffset, 7, 13, DMA_QUEUE);
                    VDP_setTileMapColumnEx(BG_A, image_NIVEAU1_BGA.tilemap, TILE_ATTR_FULL(PAL3, FALSE, FALSE, FALSE, 191), tilemapOffset-2, 62+tilemapOffset, 20, 8, DMA_QUEUE);
                }               
                else
                {
                    VDP_setTileMapColumnEx(BG_A, image_NIVEAU1_BGA.tilemap, TILE_ATTR_FULL(PAL3, FALSE, FALSE, FALSE, 191), tilemapOffset-2, 62+tilemapOffset, 7, 21, DMA_QUEUE);
                }
                
            }
        //}
    }


    // CHANGEMENTS PALETTE

     if(CamPosX<-700 && CamPosX>-702)
    {
        PAL_setPaletteColors(16, &palette_NIVEAU1_BULOT, DMA);
    }

    else if(CamPosX<-1110 && CamPosX>-1112)
    {
        PAL_setPaletteColors(16, &palette_NIVEAU1_ESCARGOT, DMA);
    }

    else if(CamPosX<-2600 && CamPosX>-2602)
    {
        PAL_setPaletteColors(16, &palette_NIVEAU1_PELICAN, DMA);
    }
    
    else if(CamPosX<-3700 && CamPosX>-3702)
    {
        PAL_setPaletteColors(16, &palette_NIVEAU1_BULOT, DMA);
    }

    else if(CamPosX<-4016 && CamPosX>-4018)
    {
        PAL_setPaletteColors(48, &palette_NIVEAU1_BGA2, DMA);
    }


}


//
void collision_Decor()
{
    u16 *ptrtileID_G=&tileID_G;
    u16 *ptrtileID_D=&tileID_D;
    
    // Point collision bas gauche
    ptrJoueur->pt_Coll1_X=SPR_getPositionX(ptrJoueur->SpriteJ)+8;
    ptrJoueur->pt_Coll1_Y=SPR_getPositionY(ptrJoueur->SpriteJ)+32;

    // Point collision bas droite
    ptrJoueur->pt_Coll2_X=SPR_getPositionX(ptrJoueur->SpriteJ)+23;
    //spr->pt_Coll2_Y=spr->pt_Coll1_Y;


    // Récuperation ID de tile de collision
    if(CamPosX>=7)
    {
        *ptrtileID_G=MAP_getTile( tilemapCollision, (ptrJoueur->pt_Coll1_X>>3) - (CamPosX>>3)+1, ptrJoueur->pt_Coll1_Y>>3 ) & TILE_INDEX_MASK;
        *ptrtileID_D=MAP_getTile( tilemapCollision, (ptrJoueur->pt_Coll2_X>>3) - (CamPosX>>3)+1, ptrJoueur->pt_Coll1_Y>>3 ) & TILE_INDEX_MASK;
    }
    else
    {
        *ptrtileID_G=MAP_getTile( tilemapCollision, (ptrJoueur->pt_Coll1_X>>3) - (CamPosX>>3), ptrJoueur->pt_Coll1_Y>>3 ) & TILE_INDEX_MASK;
        *ptrtileID_D=MAP_getTile( tilemapCollision, (ptrJoueur->pt_Coll2_X>>3) - (CamPosX>>3), ptrJoueur->pt_Coll1_Y>>3 ) & TILE_INDEX_MASK;
    }
}


// ENNEMIS NIVEAU 1 //
void CreaEnnemis_Niveau1()
{
    u16 i;

    if(CamPosX>-4336)
    {
        compteurTile+=vitesseScrolling;
    }
    

    // Si compteurTile est supérieur à 7
    if(compteurTile>7)
    {
        // tilemapCreaEnnemis_Niveau1[0][indexCreaEnnemis] : PosX
        if (-CamPosX>>3 == tilemapCreaEnnemis_Niveau1[0][indexCreaEnnemis])
        {          
            // On scanne les emplacements vides
            for(i=0;i<11;i++)
            {
                SpriteEnnemi_ *ptrEnnemi=&Ennemi[i];

                // Si on trouve un emplacement vide
                if(ptrEnnemi->Init==0)
                {                    
                    // tilemapCreaEnnemis_Niveau1[2][indexCreaEnnemis] : ID
                    ptrEnnemi->ID=tilemapCreaEnnemis_Niveau1[2][indexCreaEnnemis];

                    ptrEnnemi->Init=1;
                    ptrEnnemi->Phase=1;
                    ptrEnnemi->PointsVie=1;

                    ptrEnnemi->CompteurPosition=0;
                    ptrEnnemi->CompteurFrame=i;
                    ptrEnnemi->IndexFrame=0;

                    ptrEnnemi->Axe=0;

                    // Les escargots V ont une position en X à part
                    if(ptrEnnemi->ID==4)
                    {
                        ptrEnnemi->PosX=323;
                    }
                    else
                    {
                        // Tous les autres ennemis
                        ptrEnnemi->PosX=325;
                    }
                    
                    // tilemapCreaEnnemis_Niveau1[1][indexCreaEnnemis] : PosY
                    ptrEnnemi->PosY=(u16)tilemapCreaEnnemis_Niveau1[1][indexCreaEnnemis]<<3;


                    // Différentes palettes pour les ennemis
                    // MORSE
                    if(ptrEnnemi->ID==7)
                    {
                        ptrEnnemi->SpriteE = SPR_addSprite(adrResEnnemi[ptrEnnemi->ID], ptrEnnemi->PosX, ptrEnnemi->PosY, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));
                    }
                    // POULPE 1
                    else if(ptrEnnemi->ID==8)
                    {
                        ptrEnnemi->SpriteE = SPR_addSprite(adrResEnnemi[ptrEnnemi->ID], ptrEnnemi->PosX, ptrEnnemi->PosY, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
                        ptrEnnemi->ptrPosition=&anim_POULPE1[0];
                    }
                    // POULPE 2
                    else if(ptrEnnemi->ID==9)
                    {
                        ptrEnnemi->SpriteE = SPR_addSprite(adrResEnnemi[ptrEnnemi->ID], ptrEnnemi->PosX, ptrEnnemi->PosY, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
                        ptrEnnemi->ptrPosition=&anim_POULPE2[0];
                    }
                    // Tous les autres ennemis
                    else
                    {
                        ptrEnnemi->SpriteE = SPR_addSprite(adrResEnnemi[ptrEnnemi->ID], ptrEnnemi->PosX, ptrEnnemi->PosY, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
                    }

                    indexCreaEnnemis++;
                    break;
                }
            }
        }

        // On remet le compteur entre 0 et 7
        compteurTile-=8;  
    }
}

void MvtEnnemis_Niveau1()
{    
    if(CamPosX>-4336)
    {       
        u16 i;
        
        for(i=0;i<11;i++)
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
                                ptrEnnemi->IndexFrame-=13;
                            }

                            SPR_setFrame(ptrEnnemi->SpriteE,(u16)ptrEnnemi->IndexFrame);
                        }

                        // Si l'ennemi sort de l'écran
                        // 3 tiles (24 px) de large  
                        if(ptrEnnemi->PosX<-24 || ptrEnnemi->PosY>224 )
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                        }
                        break;

                    /////////////////////
                    // BULOTS SHURIKEN //
                    /////////////////////
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
                                ptrEnnemi->IndexFrame-=12;
                            }

                            SPR_setFrame(ptrEnnemi->SpriteE,(u16)ptrEnnemi->IndexFrame);
                        }

                        // Si l'ennemi sort de l'écran
                        // 3 tiles (24 px) de large  
                        if(ptrEnnemi->PosX<-24 || ptrEnnemi->PosY>224 )
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                        }
                        break;
 
                    ////////////
                    // BULOTS //
                    ////////////
                    case 3:

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
                                ptrEnnemi->IndexFrame-=12;
                            }

                            SPR_setFrame(ptrEnnemi->SpriteE,(u16)ptrEnnemi->IndexFrame);
                        }

                        // Si l'ennemi sort de l'écran
                        // 3 tiles (24 px) de large  
                        if(ptrEnnemi->PosX<-24 || ptrEnnemi->PosY>224 )
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                        }
                        break;

                    /////////////////
                    // ESCARGOTS V //
                    /////////////////
                    case 4:
                        
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
                                ptrEnnemi->IndexFrame-=13;
                            }

                            SPR_setFrame(ptrEnnemi->SpriteE,(u16)ptrEnnemi->IndexFrame);
                        }

                        // Si l'ennemi sort de l'écran
                        // 3 tiles (24 px) de large  
                        if(ptrEnnemi->PosX<-24 || ptrEnnemi->PosY>224 )
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                        }
                        break;

                    /////////////////////////
                    // BULOTS DOUBLE BOULE //
                    /////////////////////////
                    case 5:

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
                                ptrEnnemi->IndexFrame-=12;
                            }

                            SPR_setFrame(ptrEnnemi->SpriteE,(u16)ptrEnnemi->IndexFrame);
                        }

                        // Si l'ennemi sort de l'écran
                        // 3 tiles (24 px) de large  
                        if(ptrEnnemi->PosX<-24 || ptrEnnemi->PosY>224 )
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                        }
                        break;

                    //////////////////////////////
                    // ESCARGOTS H BOULE DE FEU //
                    //////////////////////////////
                    case 6:

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
                                ptrEnnemi->IndexFrame-=13;
                            }

                            SPR_setFrame(ptrEnnemi->SpriteE,(u16)ptrEnnemi->IndexFrame);
                        }

                        // Si l'ennemi sort de l'écran
                        // 3 tiles (24 px) de large  
                        if(ptrEnnemi->PosX<-24 || ptrEnnemi->PosY>224 )
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                        }
                        break;

                    ///////////
                    // MORSE //
                    ///////////
                    case 7:

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

                            SPR_setFrame(ptrEnnemi->SpriteE,(u16)ptrEnnemi->IndexFrame);
                        }*/

                        // Si l'ennemi sort de l'écran
                        // 6 tiles (48 px) de large  
                        if(ptrEnnemi->PosX<-48 || ptrEnnemi->PosY>224)
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                        }
                        break;

                    //////////////
                    // POULPE 1 //
                    //////////////
                    case 8:

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

                            SPR_setFrame(ptrEnnemi->SpriteE,(u16)ptrEnnemi->IndexFrame);
                        }*/
                        break;
                  

                    //////////////
                    // POULPE 2 //
                    //////////////
                    case 9:

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

                            SPR_setFrame(ptrEnnemi->SpriteE,(u16)ptrEnnemi->IndexFrame);
                        }*/
                        break; 

                    /////////////
                    // PELICAN //
                    /////////////
                    case 11:

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
                                ptrEnnemi->IndexFrame-=12;
                            }

                            SPR_setFrame(ptrEnnemi->SpriteE,(u16)ptrEnnemi->IndexFrame);
                        }

                        // Si l'ennemi sort de l'écran
                        // 3 tiles (24 px) de large  
                        if(ptrEnnemi->PosX<-24 || ptrEnnemi->PosY>224)
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                        }
                        break;


                    //////////////////////
                    // PELICAN SHURIKEN //
                    //////////////////////
                    case 10:

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
                                ptrEnnemi->IndexFrame-=12;
                            }

                            SPR_setFrame(ptrEnnemi->SpriteE,(u16)ptrEnnemi->IndexFrame);
                        }
                        
                        // Si l'ennemi sort de l'écran
                        // 3 tiles (24 px) de large  
                        if(ptrEnnemi->PosX<-24 || ptrEnnemi->PosY>224)
                        {
                            SPR_releaseSprite(ptrEnnemi->SpriteE);
                            ptrEnnemi->Init=0;
                        }
                        break;

                }

            }
        }
    }
}


// JOUEUR //
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
    else if(value & BUTTON_RIGHT)
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
        }
        return;
    }

    ////////////////
    //   GAUCHE   //
    ////////////////
    else if(value & BUTTON_LEFT)
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
        }
        return;
    }
}

void MvtJoueur()
{
    ///////////////
    //   ARRET   //
    /////////////// 
    if(ptrJoueur->Phase==0)
    { 
        // SI ON N'EST PAS A LA FIN DU NIVEAU
        if(CamPosX!=-4336)
        {
            positionX -= GLISSEMENT;
        }

        // JOUEUR ORIENTÉ VERS LA DROITE            
        if(ptrJoueur->Axe==0)
        {
            movX -= ACCEL;
            //movX -= glissement;
            if(movX < FIX32(0))
            {
                movX=0;
            }
        }

        // JOUEUR ORIENTÉ VERS LA GAUCHE
        else if(ptrJoueur->Axe==1)
        {
            movX += ACCEL;
            if(movX > FIX32(0))
            {
                movX=0;
            }
        }            
    }

    ////////////////
    //   MARCHE   //
    ////////////////
    else if(ptrJoueur->Phase==1)
    {
        /////////////////////////////
        //         DROITE          //
        /////////////////////////////
        if(ptrJoueur->Axe==0)
        {
            // ON AJOUTE 'ACCEL' A 'movX'
            movX += ACCEL;

            // ON BLOQUE LA VITESSE A 'maxSpeed (1)'
            if (movX >= maxSpeed)
            {
                movX = maxSpeed;
            } 
        }

        /////////////////////////////
        //         GAUCHE          //
        /////////////////////////////
        else if(ptrJoueur->Axe==1)
        {  
            // SI ON N'EST PAS A LA FIN DU NIVEAU
            if(CamPosX!=-4336)
            {
                positionX -= GLISSEMENT;
            }

            // ON SOUSTRAIT 'ACCEL' A 'movX'
            movX -= ACCEL;

           // ON BLOQUE LA VITESSE A 'maxSpeed (1)'
            if(movX <= -maxSpeed)
            {
                movX = -maxSpeed;
            }
        }
    }

    vitesseScrolling=1;

     // ON AJOUTE 'movX' A L'ACCUMULATEUR 'positionX'
    positionX += movX;

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
    // 'positionX' EST LA POSITION DU SPRITE
    ptrJoueur->PosX=fix32ToInt(positionX);
    SPR_setPosition(ptrJoueur->SpriteJ, ptrJoueur->PosX, ptrJoueur->PosY);
}

void TilesBloque()
{
    SPR_setAnim(ptrJoueur->SpriteJ,1);

    ptrJoueur->CompteurFrameArret=0;
    ptrJoueur->IndexFrameArret=0;

    ptrJoueur->CompteurFrameMarche=0;
    ptrJoueur->IndexFrameMarche=0;

    SPR_setHFlip(ptrJoueur->SpriteJ, FALSE);

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

    SPR_setFrame(ptrJoueur->SpriteJ,(u16)ptrJoueur->IndexFrameBloque);
}

void TilesArret()
{
    SPR_setAnim(ptrJoueur->SpriteJ,0);

    ptrJoueur->CompteurFrameBloque=0;
    ptrJoueur->IndexFrameBloque=0;

    ptrJoueur->CompteurFrameMarche=0;
    ptrJoueur->IndexFrameMarche=0;

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

    SPR_setFrame(ptrJoueur->SpriteJ,(u16)ptrJoueur->IndexFrameArret);
}

void TilesMarche()
{
    SPR_setAnim(ptrJoueur->SpriteJ,2);
    
    ptrJoueur->CompteurFrameBloque=0;
    ptrJoueur->IndexFrameBloque=0;
    
    ptrJoueur->CompteurFrameArret=0;
    ptrJoueur->IndexFrameArret=0;


    if(ptrJoueur->Axe==0)
    {
        SPR_setHFlip(ptrJoueur->SpriteJ, FALSE);
    }
    else
    {
        SPR_setHFlip(ptrJoueur->SpriteJ, TRUE);
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

    SPR_setFrame(ptrJoueur->SpriteJ,(u16)ptrJoueur->IndexFrameMarche);
}

void TilesDerapage()
{
    SPR_setAnim(ptrJoueur->SpriteJ,5);

    ptrJoueur->CompteurFrameBloque=0;
    ptrJoueur->IndexFrameBloque=0;

    ptrJoueur->CompteurFrameArret=0;
    ptrJoueur->IndexFrameArret=0;

    ptrJoueur->CompteurFrameMarche=0;
    ptrJoueur->IndexFrameMarche=0;   
}

void TilesJoueur()
{
    ///////////////
    //   ARRET   //
    /////////////// 
    if(ptrJoueur->Phase==0)
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
    else if(ptrJoueur->Phase==1)
    {
        // SI JOUEUR VA VERS LA DROITE
        if(ptrJoueur->Axe==0)
        {
            if(movX < FIX32(0))
            {
                TilesDerapage();
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
            }
            else
            {
                TilesMarche();
                return;
            }
        }    
    }
}
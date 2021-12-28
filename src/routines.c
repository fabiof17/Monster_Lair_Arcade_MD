#include <genesis.h>
#include <main.h>
#include <init.h>
#include <variables.h>
#include <palettes.h>
#include <maps_NIVEAU1.h>
#include <tilemaps_ennemis.h>
#include <animation_ennemis.h>
#include <GestionPAD.h>
#include <sprites_JEU.h>

void updateScrolling_Niveau1()
{
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

void updateTiles_Niveau1()
{
    // MISE A JOUR TILEMAP //
    if(CamPosX>-4336)
    {
        if (CamPosX%8==0)
        {
            if (tilemapOffset>0 && tilemapOffset<520)
            {
                VDP_setTileMapColumnEx(BG_B, image_NIVEAU1_BGB.tilemap, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, 16), (tilemapOffset>>1)-2, 62+(tilemapOffset>>1), 7, 20, DMA_QUEUE);
                VDP_setTileMapColumnEx(BG_B, image_NIVEAU1_BGB.tilemap, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 16), (tilemapOffset>>1)-2, 62+(tilemapOffset>>1), 27, 4, DMA_QUEUE);


                VDP_setTileMapColumnEx(BG_A, image_NIVEAU1_BGA.tilemap, TILE_ATTR_FULL(PAL3, FALSE, FALSE, FALSE, 191), tilemapOffset-2, 62+tilemapOffset, 7, 21, DMA_QUEUE);
            }
        }
    }


    // CHANGEMENTS PALETTE
    
    if(CamPosX<-2600 && CamPosX>-2602)
    {
        PAL_setPaletteColors(16, &palette_NIVEAU1_PELICAN, DMA);
    }
    
    else if(CamPosX<-3702 && CamPosX>-3704)
    {
        PAL_setPaletteColors(16, &palette_NIVEAU1_BULOT, DMA);
    }

    else if(CamPosX<-4016 && CamPosX>-4018)
    {
        PAL_setPaletteColors(48, &palette_NIVEAU1_BGA2, DMA);
    }


}

void collision_Decor(SpriteJoueur_ *ptrJoueur)
{
    // Point collision bas gauche
    ptrJoueur->pt_Coll1_X=SPR_getPositionX(ptrJoueur->SpriteJ)+8;
    ptrJoueur->pt_Coll1_Y=SPR_getPositionY(ptrJoueur->SpriteJ)+32;

    // Point collision bas droite
    ptrJoueur->pt_Coll2_X=SPR_getPositionX(ptrJoueur->SpriteJ)+23;
    //spr->pt_Coll2_Y=spr->pt_Coll1_Y;


    // Récuperation ID de tile de collision
    if(CamPosX>=7)
    {
        tileID_G=MAP_getTile( tilemapCollision, (ptrJoueur->pt_Coll1_X>>3) - (CamPosX>>3), ptrJoueur->pt_Coll1_Y>>3 ) & TILE_INDEX_MASK;
        tileID_D=MAP_getTile( tilemapCollision, (ptrJoueur->pt_Coll2_X>>3) - (CamPosX>>3), ptrJoueur->pt_Coll1_Y>>3 ) & TILE_INDEX_MASK;
    }
    else
    {
        tileID_G=MAP_getTile( tilemapCollision, (ptrJoueur->pt_Coll1_X>>3) - (CamPosX>>3)+1, ptrJoueur->pt_Coll1_Y>>3 ) & TILE_INDEX_MASK;
        tileID_D=MAP_getTile( tilemapCollision, (ptrJoueur->pt_Coll2_X>>3) - (CamPosX>>3)+1, ptrJoueur->pt_Coll1_Y>>3 ) & TILE_INDEX_MASK;
    }
}

void creaEnnemis_Niveau1()
{
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
                    ptrEnnemi->CompteurFrame=i;
                    ptrEnnemi->IndexFrame=0;

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
                    if(ptrEnnemi->ID==7)
                    {
                        ptrEnnemi->SpriteE = SPR_addSprite(adrResEnnemi[ptrEnnemi->ID], ptrEnnemi->PosX, ptrEnnemi->PosY, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));
                    }
                    else if(ptrEnnemi->ID==8)
                    {
                        ptrEnnemi->SpriteE = SPR_addSprite(adrResEnnemi[ptrEnnemi->ID], ptrEnnemi->PosX, ptrEnnemi->PosY, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
                        ptrEnnemi->ptrPosition=&anim_POULPE1[0];
                    }
                     else if(ptrEnnemi->ID==9)
                    {
                        ptrEnnemi->SpriteE = SPR_addSprite(adrResEnnemi[ptrEnnemi->ID], ptrEnnemi->PosX, ptrEnnemi->PosY, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
                        ptrEnnemi->ptrPosition=&anim_POULPE2[0];
                    }
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

void mvtEnnemis_Niveau1()
{    
    if(CamPosX>-4336)
    {       
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

                    /////////////////////////
                    // BULOTS DOUBLE BOULE //
                    /////////////////////////
                    case 5:

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

                        ptrEnnemi->PosX -= vitesseScrolling;
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

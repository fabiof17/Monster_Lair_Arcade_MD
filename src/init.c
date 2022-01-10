// Librairies Projet
#include <genesis.h>
#include <main.h>
#include "init.h"
#include "variables.h"
#include "maps_TITRE.h"
#include "maps_SELECTION.h"
#include "maps_NIVEAU1.h"
#include "sprites_JEU.h"
#include "palettes.h"
#include "routines.h"
#include "GestionPAD.h"

///////////////////////////////
//        INIT SYSTEME       //
///////////////////////////////
void InitSystem()
{
    // disable interrupt when accessing VDP
    SYS_disableInts();

	// init resolution
    VDP_setScreenWidth320();
    VDP_setScreenHeight224();

    // set all palette to black
    PAL_setPaletteColors(0, &palette_NOIR, DMA);

    SYS_doVBlankProcess();
}




///////////////////////////////
//      INIT ECRAN TITRE     //
///////////////////////////////

void InitTitre()
{
    // init VDP
    VDP_init();

    SYS_doVBlankProcess();

    // set all palette to black
    PAL_setPaletteColors(0, &palette_NOIR, DMA);

    //SYS_doVBlankProcess();

    //////////////////////////////////////////////
    //                CREATION BG               //
    //////////////////////////////////////////////

    // safe starting VRAM adress (16)
    u16 ind = TILE_USERINDEX;

    // BGB tileset loading in VRAM
    // getting tileset data from IMAGE structure declared in maps_TITRE.res
    VDP_loadTileSet(image_TITRE_BGB.tileset, ind, DMA);

    // BGB CREATION
    // getting dtilemap data from IMAGE structure declared in maps_TITRE.res
    VDP_setTileMapEx(BG_B, image_TITRE_BGB.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, 0, 0, 64, 32, CPU);

    // we offset tile index by the number of tiles previously loaded in VRAM
    ind += image_TITRE_BGB.tileset->numTile;

    // safe VBlank wait between 2 BG creations
    SYS_doVBlankProcess();




    // BGA tileset loading in VRAM
    // getting tileset data from IMAGE structure declared in maps_TITRE.res
    VDP_loadTileSet(image_TITRE_BGA.tileset, ind, DMA);

    // BGA CREATION
    // getting tilemap data from IMAGE structure declared in maps_TITRE.res
    VDP_setTileMapEx(BG_A, image_TITRE_BGA.tilemap, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), 0, 0, 0, 0, 64, 32, CPU);

    // we offset tile index by the number of tiles previously loaded in VRAM
    ind += image_TITRE_BGA.tileset->numTile;

    // safe VBlank wait between 2 BG creations
    SYS_doVBlankProcess();




    // scroll mode
    VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_PLANE);




    //////////////////////////////////////////////
    //                   SPRITES                //
    ////////////////////////////////////////////// 
 
    // init Sprite Engine
    SPR_init();

    // création des sprites du titre
    Sprite *sprite_Titre[6];

    u16 i;

    for (i=0; i<6; i++)
    {
        sprite_Titre[i]=SPR_addSprite(&tiles_Sprite_TITRE, 64+(i<<5), 16, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
        SPR_setAnimAndFrame(sprite_Titre[i], 0, i);
    }
    
    SPR_update();

    //KLog_U1("Hello Gens KMod - ", 1010);

    //////////////////////////////////////////////
    //               PALETTES LOADING           //
    //////////////////////////////////////////////

    SYS_doVBlankProcess();

    PAL_setPalette(PAL0, palette_TITRE_BGB.data, DMA);
    PAL_setPalette(PAL1, palette_TITRE_BGA.data, DMA);
    PAL_setPalette(PAL2, palette_TITRE.data ,DMA);

    SYS_enableInts();

    //SYS_doVBlankProcess();




    while(TRUE)
	{
        CamPosX-=1;

        for (i=0; i<9; i++)
        {
            scrollOffset_TILE_TITRE[i]=CamPosX>>1;
        }

        // scrolling par tile
        VDP_setHorizontalScrollTile(BG_B, 9, scrollOffset_TILE_TITRE, 9, DMA_QUEUE);



        // Gestion manette
		u16 value=JOY_readJoypad(JOY_1);

        // Désactivation auto-fire
        if (!value) StatutJoy++;
        if (StatutJoy>4) StatutJoy=4;

        if (StatutJoy>2)
        {
            // Si A ou B ou C ou START : on quitte
            if (value & (BUTTON_A | BUTTON_B | BUTTON_C | BUTTON_START))
            {
                CamPosX=0;
                StatutJoy=0;
                break;
            }
        }

        // Vblank
		SYS_doVBlankProcess();
    }


    // set all palette to black
    VDP_setPaletteColors(0, (u16*) palette_black, 64);


    for (i=0; i<9; i++)
    {
        scrollOffset_TILE_TITRE[i]=0;
    }

    // réinit scrolling par tile
    VDP_setHorizontalScrollTile(BG_B, 9, scrollOffset_TILE_TITRE, 9, DMA_QUEUE);


    // Si on quitte
    // On efface les BG
    VDP_clearPlane(BG_B,TRUE);
    VDP_clearPlane(BG_A,TRUE);


    for (i=0; i<6; i++)
    {
        SPR_releaseSprite(sprite_Titre[i]);
    }

    // réinitialise le Sprite Engine
    SPR_reset();
    // désactive le Sprite Engine
    SPR_end();


    SYS_doVBlankProcess();
}




///////////////////////////////////
//      INIT ECRAN SELECTION     //
///////////////////////////////////

void InitSelection()
{

    //////////////////////////////////////////////
    //                BG CREATION               //
    //////////////////////////////////////////////

    // safe starting VRAM adress (16)
    u16 ind = TILE_USERINDEX;

    // BGB tileset loading in VRAM
    // getting tileset data from IMAGE structure declared in maps_SELECTION.res
    VDP_loadTileSet(image_SELECTION_BGB.tileset, ind, DMA);

    // BGB CREATION
    // getting dtilemap data from IMAGE structure declared in maps_SELECTION.res
    VDP_setTileMapEx(BG_B, image_SELECTION_BGB.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, 0, 0, 40, 28, CPU);
    VDP_setTileMapEx(BG_B, image_SELECTION_BGB.tilemap, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, ind), 25, 14, 25, 14, 6, 8, CPU);

    // we offset tile index by the number of tiles previously loaded in VRAM
    ind += image_SELECTION_BGB.tileset->numTile;

    // safe VBlank wait between 2 BG creations
    SYS_doVBlankProcess();




    // BGA tileset loading in VRAM
    // getting tileset data from IMAGE structure declared in maps_SELECTION.res
    VDP_loadTileSet(image_SELECTION_BGA.tileset, ind, DMA);

    // BGA CREATION
    // getting tilemap data from IMAGE structure declared in maps_SELECTION.res
    VDP_setTileMapEx(BG_A, image_SELECTION_BGA.tilemap, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), 0, 0, 0, 0, 64, 28, CPU);

    // we offset tile index by the number of tiles previously loaded in VRAM
    ind += image_SELECTION_BGA.tileset->numTile;

    // safe VBlank wait between 2 BG creations
    SYS_doVBlankProcess();




    // scroll mode
    VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_PLANE);


    //////////////////////////////////////////////
    //                  SPRITES                 //
    //////////////////////////////////////////////

    /*********/
    /*  VIES */
    /*********/

    u16 i;

    SPR_init();

    for (i=0; i<2; i++)
    {
        sprite_Vie[i]=SPR_addSprite(&tiles_Sprite_VIE_H, 16+(i<<4), 200, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    }

    for (i=0; i<2; i++)
    {    
        sprite_Vie[i]=SPR_addSprite(&tiles_Sprite_VIE_F, 272+(i<<4), 200, TILE_ATTR(PAL2, TRUE, FALSE, FALSE));
    }
    
    SPR_update();

    //////////////////////////////////////////////
    //               CHARGEMENT PALETTES        //
    //////////////////////////////////////////////


    PAL_setPalette(PAL0, palette_SELECTION_BGB.data, DMA);
    PAL_setPalette(PAL1, palette_SELECTION_BGA.data, DMA);
    PAL_setPalette(PAL2, palette_02_SELECTION.data, DMA);

    SYS_doVBlankProcess();

    for (i=0; i<10; i++)
    {
        scrollOffset_TILE_TITRE[i]=128;
    }


    while(TRUE)
	{

        // Gestion manette
		u16 value=JOY_readJoypad(JOY_1);

        // Désactivation auto-fire
        if (!value) StatutJoy++;
        if (StatutJoy>4) StatutJoy=4;

        if (StatutJoy>2)
        {
            // Si A ou B ou C ou START : on quitte
            if (value & BUTTON_RIGHT && selectJoueur == 0 )
            {
                // scrolling par tile
                VDP_setHorizontalScrollTile(BG_A, 13, scrollOffset_TILE_TITRE, 10, CPU);
    
                for (i=0; i<10; i++)
                {
                    scrollOffset_TILE_TITRE[i]=0;
                }
        
                selectJoueur=1;
                StatutJoy=0;
            }

            if (value & BUTTON_LEFT && selectJoueur == 1 )
            {
                // scrolling par tile
                VDP_setHorizontalScrollTile(BG_A, 13, scrollOffset_TILE_TITRE, 10, CPU);
    
                for (i=0; i<10; i++)
                {
                    scrollOffset_TILE_TITRE[i]=128;
                }
        
                selectJoueur=0;
                StatutJoy=0;
            }

            if (value & BUTTON_START)
            {
                // set all palette to black
                VDP_setPaletteColors(0, (u16*) palette_black, 64);


                for (i=0; i<10; i++)
                {
                    scrollOffset_TILE_TITRE[i]=0;
                }

                // réinit scrolling par tile
                VDP_setHorizontalScrollTile(BG_A, 13, scrollOffset_TILE_TITRE, 10, CPU);


                // Si on quitte
                // On efface les BG
                VDP_clearPlane(BG_B,TRUE);
                VDP_clearPlane(BG_A,TRUE);

                StatutJoy=0;

                break;
            }
        }


        // Vblank
		SYS_doVBlankProcess();
    }
}




//////////////////////////////////
//        INIT DES NIVEAUX      //
//////////////////////////////////

void InitNiveaux()
{
    switch (num_Niveau)
    {
        case 1:
        waitMs(500);
        InitNiveau1();
        break;

        case 2:
        break;
    }   
}




///////////////////////////////
//        INIT NIVEAU 1      //
///////////////////////////////

void InitNiveau1()
{
    nb_Vie=2;
    
    vitesseScrolling=1;
    compteurTile=0;

    nb_Ennemis=0;
    indexCreaEnnemis=0;

    nb_Plateformes=0;
    indexCreaPlateformes=0;
       
    // Position initiale du sprite : 64 pixels
    positionX=FIX32(64L);
    movX = FIX32(0);
    maxSpeed = MAX_SPEED;
    
    //////////////////////////////////////////////
    //                CREATION  BG              //
    //////////////////////////////////////////////

    /********************************************/
    /*                     BGB                  */
    /********************************************/

    // safe starting VRAM adress (16)
    u16 ind = TILE_USERINDEX;

    // BGB tileset loading in VRAM
    // getting tileset data from IMAGE structure declared in maps_NIVEAU1.res
    VDP_loadTileSet(&tileset_NIVEAU1_BGB, ind, DMA);   

    // BGB CREATION
    // getting tilemap data from IMAGE structure declared in maps_NIVEAU1.res
    VDP_setTileMapEx(BG_B, image_NIVEAU1_BGB.tilemap, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, ind), 0, 0, 0, 0, 64, 27, CPU);
    VDP_setTileMapEx(BG_B, image_NIVEAU1_BGB.tilemap, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, ind), 0, 27, 0, 27, 64, 4, CPU);
    //VDP_setTileMap(BG_B, image_NIVEAU1_BGB.tilemap, 0, 0, 64, 28, CPU);

    // we offset tile index by the number of tiles previously loaded in VRAM
    ind += tileset_NIVEAU1_BGB.numTile;

    // Vblank
    SYS_doVBlankProcess();




    /********************************************/
    /*                     BGA                  */
    /********************************************/

    // BGB tileset loading in VRAM
    // getting tileset data from IMAGE structure declared in maps_NIVEAU1.res
    VDP_loadTileSet(&tileset_NIVEAU1_BGA, ind, DMA);   

    // BGA CREATION
    // getting tilemap data from IMAGE structure declared in maps_NIVEAU1.res
    VDP_setTileMapEx(BG_A, image_NIVEAU1_BGA.tilemap, TILE_ATTR_FULL(PAL3, FALSE, FALSE, FALSE, ind), 0, 0, 0, 0, 64, 28, CPU);
    //VDP_setTileMap(BG_A, image_NIVEAU1_BGA.tilemap, 0, 0, 64, 28, CPU);

    // we offset tile index by the number of tiles previously loaded in VRAM
    ind += tileset_NIVEAU1_BGA.numTile;   

    // Vblank
    SYS_doVBlankProcess();




    /********************************************/
    /*                  WINDOW                  */
    /********************************************/

    VDP_setWindowHPos(0, 0);
    VDP_setWindowVPos(0, 6);

    // WINDOW tileset loading in VRAM
    // getting tileset data from IMAGE structure declared in maps_NIVEAU1.res
    VDP_loadTileSet(&tileset_NIVEAU1_WINDOW, ind, DMA);
    

    // WINDOW CREATION
    // getting tilemap data from IMAGE structure declared in maps_NIVEAU1.res
    VDP_setTileMapEx(WINDOW, image_NIVEAU1_WINDOW.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, ind), 0, 0, 0, 0, 40, 6, DMA);

    // we offset tile index by the number of tiles previously loaded in VRAM
    ind += tileset_NIVEAU1_WINDOW.numTile;

    // SI JOUEUR FEMME
    // TETE FEMME DANS LE LAYER WINDOW
    if(selectJoueur==1)
    {
        VDP_loadTileSet(&tileset_TETE_F, ind, DMA);
        VDP_setTileMapEx(WINDOW, image_TETE_F.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, ind), 1, 1, 0, 0, 2, 2, DMA);
    }

    // we offset tile index by the number of tiles previously loaded in VRAM
    ind += tileset_NIVEAU1_WINDOW.numTile;

    // Vblank
    SYS_doVBlankProcess();


    VDP_setVerticalScroll(BG_B, 24);


    //////////////////////////////////////////////
    //                  SPRITES                 //
    //////////////////////////////////////////////

    SPR_init();

    /*********/
    /* PAUSE */
    /*********/
    sprite_Pause[0]=SPR_addSprite(&tiles_Sprite_PAUSE1, -40, 0, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    sprite_Pause[1]=SPR_addSprite(&tiles_Sprite_PAUSE2, -32, 0, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));

    /*********/
    /*  VIES */
    /*********/

    u16 i;

    for (i=0; i<nb_Vie; i++)
    {
        if(selectJoueur==0)
        {
            sprite_Vie[i]=SPR_addSprite(&tiles_Sprite_VIE_H, 16+(i<<4), 200, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
        }
        else
        {
            sprite_Vie[i]=SPR_addSprite(&tiles_Sprite_VIE_F, 16+(i<<4), 200, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
        
        }
    }

    /**********/
    /* JOUEUR */
    /**********/
    // Création d'un pointeur de type "SpritePerso_" contenant la variable "Joueur".
    SpriteJoueur_ *ptrJoueur=&Joueur;

    if(selectJoueur==0)
    {
        ptrJoueur->SpriteJ = SPR_addSprite(&tiles_Sprite_JOUEUR_H, 0, 128, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    }
    else
    {
        ptrJoueur->SpriteJ = SPR_addSprite(&tiles_Sprite_JOUEUR_F, 0, 128, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    
    }
    
    // PHASE CHUTE DEBUT //
    ptrJoueur->Phase=50;

    // ORIENTE DROITE //
    ptrJoueur->Axe=0;

    // POSITION //
    ptrJoueur->PosX=fix32ToInt(positionX);
    ptrJoueur->PosY=128;

    SPR_setPosition(ptrJoueur->SpriteJ, ptrJoueur->PosX, ptrJoueur->PosY);

    ptrJoueur->CompteurFrameBloque=0;
    ptrJoueur->IndexFrameBloque=0;

    ptrJoueur->CompteurFrameArret=0;
    ptrJoueur->IndexFrameArret=0;

    /***********/
    /* ENNEMIS */
    /***********/
    // Init de la structure des sprites ennemis.
    // Init=0 car les ennemis n'ont pas encore été créés.
    // Aucune assignation de sprite dans SpriteE.
    for(i=0;i<10;i++)
    {
        Ennemi[i].Init=0;
    }

    // Init adresse sreesources sprites ennemis
    adrResEnnemi[1]=&tiles_Sprite_ESCARGOT_H;
    adrResEnnemi[2]=&tiles_Sprite_BULOT;
    adrResEnnemi[3]=&tiles_Sprite_BULOT;
    adrResEnnemi[4]=&tiles_Sprite_ESCARGOT_V;
    adrResEnnemi[5]=&tiles_Sprite_BULOT;
    adrResEnnemi[6]=&tiles_Sprite_ESCARGOT_H;
    adrResEnnemi[7]=&tiles_Sprite_MORSE;
    adrResEnnemi[8]=&tiles_Sprite_POULPE;
    adrResEnnemi[9]=&tiles_Sprite_POULPE;
    adrResEnnemi[10]=&tiles_Sprite_PELICAN;
    adrResEnnemi[11]=&tiles_Sprite_PELICAN;

    SPR_update();

    /////////////////////////////
    // TILEMAP COLLISION DECOR //
    /////////////////////////////
    // Pointeur *tilemapCollision de type Map déclaré dans variables.h
    // MAP tilemap_COLLISION_NIVEAU1 déclarée dans maps_NIVEAU1.res
    tilemapCollision=MAP_create(&tilemap_COLLISION_NIVEAU1, BG_A, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX));


    //////////////////////////////////////////////
    //                  PALETTES                //
    //////////////////////////////////////////////

    VDP_setBackgroundColor(32);

    if(selectJoueur==0)
    {
        PAL_setPalette(PAL0, palette_JOUEUR_H.data, DMA); // PALETTE PERSO H
    }
    else
    {
        PAL_setPalette(PAL0, palette_JOUEUR_F.data, DMA); // PALETTE PERSO F
    }
    
    PAL_setPalette(PAL1, palette_NIVEAU1_ESCARGOT.data, DMA);   // PALETTE ENNEMIS
    PAL_setPalette(PAL2, palette_NIVEAU1_BGB.data, DMA);        // PALETTE BG_B
    PAL_setPalette(PAL3, palette_NIVEAU1_BGA.data, DMA);        // PALETTE BG_A

    // scroll mode
    VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_PLANE);
 
    // Vblank
    SYS_doVBlankProcess();
}
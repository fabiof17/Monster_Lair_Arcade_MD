// Librairies Projet
#include <genesis.h>
#include <main.h>
#include "init.h"
#include "variables.h"
#include "maps_TITRE.h"
#include "maps_SELECTION.h"
#include "maps_GLOBALES.h"
#include "maps_NIVEAU1.h"
#include "sprites_JEU.h"
#include "palettes.h"
#include "routines.h"

///////////////////////////////
//        INIT SYSTEME       //
///////////////////////////////
void InitSystem()
{  
    // Init game resolution //
    VDP_setScreenWidth320();
    VDP_setScreenHeight224();
}

void InitVariablesGeneral()
{
   // We start on the title secrren //
    Scene = 0;

    // Title screen not loaded yet //
    Titre_OK = 0;

    // Selection screen not loaded yet //
    Selection_OK = 0;

    // No level loaded yet //
    Niveau_OK = 0;

    // We start the game at level 1 //
    Num_Niveau = 1;

    // Counter for the Continue ? numbers //
    Compteur_Continue = 0;

    AdresseVram_BG_A = 0;

    // Game is not in Continue ? mode // //
    SWITCH_CONTINUE = 0;

    // Game is not over //
    SWITCH_GAMEOVER = 0;

    // Game is not in pause mode //
    PauseJeu = 0;

    // Life number //
    Nb_Vies_Options = 3;
    Nb_Vies = Nb_Vies_Options;

    // Number of credits //
    Nb_Credits = 3;

    Exit_Titre = 0;

    Exit_Selection = 0;
}


///////////////////////////////
//         ECRAN TITRE       //
///////////////////////////////

void InitTitre()
{
    Exit_Titre = 0;
    Menu_Titre = 0;
    Pos_Menu_Titre = 0;
    

    VDP_setHilightShadow(TRUE);

    // set all palette to black
    PAL_setColors(0, (u16*) palette_black, 64, CPU);

    // set all palettes to black
    //PAL_setPaletteColors(0, &palette_NOIR, DMA);

    // scroll mode
    VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_PLANE);


    //////////////////////////////////////////////
    //                CREATION BG               //
    //////////////////////////////////////////////

    /********************************************/
    /*                     BGB                  */
    /********************************************/

    // safe starting VRAM adress (16)
    u16 ind = TILE_USER_INDEX;

    // BGB tileset loading in VRAM
    // getting tileset data from IMAGE structure declared in maps_TITRE.res
    VDP_loadTileSet(image_TITRE_BGB.tileset, ind, DMA);

    // BGB CREATION
    // getting dtilemap data from IMAGE structure declared in maps_TITRE.res
    VDP_setTileMapEx(BG_B, image_TITRE_BGB.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, ind), 0, 0, 0, 0, 64, 32, CPU);

    // we offset tile index by the number of tiles previously loaded in VRAM
    ind += image_TITRE_BGB.tileset->numTile;

    // safe VBlank wait between 2 BG creations
    SYS_doVBlankProcess();



    /********************************************/
    /*                     BGA                  */
    /********************************************/

    // BGA tileset loading in VRAM
    // getting tileset data from IMAGE structure declared in maps_TITRE.res
    VDP_loadTileSet(image_TITRE_BGA.tileset, ind, DMA);

    // BGA CREATION
    // getting tilemap data from IMAGE structure declared in maps_TITRE.res
    VDP_setTileMapEx(BG_A, image_TITRE_BGA.tilemap, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, ind), 0, 0, 0, 0, 64, 32, CPU);

    // we offset tile index by the number of tiles previously loaded in VRAM
    ind += image_TITRE_BGA.tileset->numTile;

    // safe VBlank wait between 2 BG creations
    SYS_doVBlankProcess();




    // scroll mode
    //VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_PLANE);

    VDP_setVerticalScroll(BG_B, 0);
    VDP_setVerticalScroll(BG_A, 0);



    //////////////////////////////////////////////
    //                   SPRITES                //
    //////////////////////////////////////////////

    // init Sprite Engine
    SPR_init();

    sprite_Bouton_Options=SPR_addSprite(&tiles_Sprite_BOUTON_OPTIONS, 0, -8, TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
    sprite_Player_Options=SPR_addSprite(&tiles_Sprite_PLAYER_OPTIONS, 0, -8, TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
    sprite_Credits_Options=SPR_addSprite(&tiles_Sprite_CREDITS_OPTIONS, 0, -8, TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
    sprite_Start_Options=SPR_addSprite(&tiles_Sprite_START_OPTIONS, 0, -8, TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

    sprite_Nb_Player_Options=SPR_addSprite(&tiles_Sprite_CHIFFRES_OPTIONS, 0, -8, TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
    SPR_setFrame( sprite_Nb_Player_Options , Nb_Vies_Options );
    sprite_Nb_Credits_Options=SPR_addSprite(&tiles_Sprite_CHIFFRES_OPTIONS, 0, -8, TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
    SPR_setFrame( sprite_Nb_Credits_Options , Nb_Credits );

    sprite_Menu_Titre=SPR_addSprite(&tiles_Sprite_MENU_TITRE, 0, -56, TILE_ATTR(PAL3, TRUE, FALSE, FALSE));



    u16 i;

    for (i=0; i<6; i++)
    {
        sprite_Titre[i]=SPR_addSprite(&tiles_Sprite_TITRE, 64+(i<<5), 16, TILE_ATTR(PAL2, TRUE, FALSE, FALSE));
        SPR_setAnimAndFrame(sprite_Titre[i], 0, i);
    }

    // création du sprite PRESS START //
    sprite_Press_Start=SPR_addSprite(&tiles_Sprite_PRESS_START, 116, 48, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));




    SPR_update();

    //KLog_U1("Hello Gens KMod - ", 1010);

    //////////////////////////////////////////////
    //               PALETTES LOADING           //
    //////////////////////////////////////////////


    SYS_doVBlankProcess();

    PAL_setPalette(PAL0, palette_TITRE_BGB.data, DMA);
    PAL_setPalette(PAL1, palette_TITRE_BGA.data, DMA);
    PAL_setPalette(PAL2, palette_TITRE.data ,DMA);
    PAL_setPalette(PAL3, palette_MENU.data ,DMA);


    SYS_doVBlankProcess();

    // ECRAN TITRE chargé //
    Titre_OK=1;

}

void AnimTitre()
{
    u8 CompteurPressStart=1;
    s16 scrollOffset_TILE_TITRE[10]={1,1,1,1,1,1,1,1,1,0};

    /********************************************/
    /*            BOUCLE ECRAN TITRE            */
    /********************************************/
    while(Exit_Titre==0)
	{
        if(Menu_Titre == 0)
        {
            /********************************************/
            /*                CLIGNOTEMENT              */
            /********************************************/
            if(CompteurPressStart==0)
            {
                SPR_setPosition(sprite_Press_Start,116,48);
            }
            else if(CompteurPressStart==6)
            {
                SPR_setPosition(sprite_Press_Start,0,-8);
            }        

            CompteurPressStart++;

            if(CompteurPressStart>11)
            {
                CompteurPressStart=0;
            }
        }
        else
        {
            SPR_setPosition(sprite_Press_Start,0,-8);
            CompteurPressStart=0;
        }


        /********************************************/
        /*                 SCROLLING                */
        /********************************************/ 
        CamPosX-=1;

        u16 i=0;

        for (i=0; i<9; i++)
        {
            scrollOffset_TILE_TITRE[i]=CamPosX>>1;
        }

        // scrolling par tile
        VDP_setHorizontalScrollTile(BG_B, 9, scrollOffset_TILE_TITRE, 9, DMA_QUEUE);

        // Update sprites //
        SPR_update();

        // Vblank //
		SYS_doVBlankProcess();

        /********************************************/
        /*                  MANETTE                 */
        /********************************************/ 
        JOY_setEventHandler(Titre_Callback);

    }


    /********************************************/
    /*             SORTIE ECRAN TITRE           */
    /********************************************/

    // Set all palettes to black //
    PAL_setColors(0, (u16*) palette_black, 64 , DMA_QUEUE);



    u16 i=0;

    // Set all tiles offset to 0 //
    for (i=0; i<9; i++)
    {
        scrollOffset_TILE_TITRE[i]=0;
    }

    // Reset tile scrolling //
    VDP_setHorizontalScrollTile(BG_B, 9, scrollOffset_TILE_TITRE, 9, DMA_QUEUE);

     // Clear all BG //
    VDP_clearPlane(BG_B,TRUE);
    VDP_clearPlane(BG_A,TRUE);

    // Clear all sprites //
    SPR_reset();

    // Disable Sprite Engine //
    SPR_end();



    // On passe à l'ECRAN DE SELECTION //
    Scene=1;

    Titre_OK=0;



    // Vblank //
    SYS_doVBlankProcess();
}




///////////////////////////////////
//         ECRAN SELECTION       //
///////////////////////////////////

void InitSelection()
{
    VDP_setHilightShadow(FALSE);
    
    Exit_Selection=0;
    selectJoueur=0;

    //////////////////////////////////////////////
    //                BG CREATION               //
    //////////////////////////////////////////////

    /********************************************/
    /*                     BGB                  */
    /********************************************/

    // safe starting VRAM adress (16)
    u16 ind = TILE_USER_INDEX;

    // BGB tileset loading in VRAM
    // getting tileset data from IMAGE structure declared in maps_SELECTION.res
    VDP_loadTileSet(image_SELECTION_BGB.tileset, ind, DMA);

    // BGB CREATION
    // getting dtilemap data from IMAGE structure declared in maps_SELECTION.res
    VDP_setTileMapEx(BG_B, image_SELECTION_BGB.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, 0, 0, 40, 28, CPU);
    VDP_setTileMapEx(BG_B, image_SELECTION_BGB.tilemap, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, ind), 25, 14, 25, 14, 6, 8, CPU);

    // we offset tile index by the number of tiles previously loaded in VRAM
    ind += image_SELECTION_BGB.tileset->numTile;

    AdresseVram_BG_A=ind;

    // safe VBlank wait between 2 BG creations
    SYS_doVBlankProcess();




    /********************************************/
    /*                     BGA                  */
    /********************************************/

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



    /********************************************/
    /*                  WINDOW                  */
    /********************************************/

    VDP_setWindowHPos(0, 0);
    VDP_setWindowVPos(0, 6);

    // WINDOW tileset loading in VRAM
    // getting tileset data from IMAGE structure declared in maps_NIVEAU1.res
    VDP_loadTileSet(&tileset_WINDOW, ind, DMA);


    // WINDOW CREATION
    // getting tilemap data from IMAGE structure declared in maps_NIVEAU1.res
    VDP_setTileMapEx(WINDOW, image_WINDOW.tilemap, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, ind), 0, 0, 0, 0, 40, 6, DMA);

    // we offset tile index by the number of tiles previously loaded in VRAM
    ind += tileset_WINDOW.numTile;


    ///////////////////
    //  TETE JOUEUR  //
    ///////////////////

    VDP_loadTileSet(&tileset_TETE_H_SELECTION, ind, DMA);
    VDP_setTileMapEx(WINDOW, image_TETE_H_SELECTION.tilemap, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, ind), 1, 1, 0, 0, 2, 2, DMA);

    // we offset tile index by the number of tiles previously loaded in VRAM
    ind += tileset_TETE_H_SELECTION.numTile;

    VDP_loadTileSet(&tileset_TETE_F_SELECTION, ind, DMA);
    VDP_setTileMapEx(WINDOW, image_TETE_F_SELECTION.tilemap, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, ind), 21, 1, 0, 0, 2, 2, DMA);

    // we offset tile index by the number of tiles previously loaded in VRAM
    ind += tileset_TETE_F_SELECTION.numTile;



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

    for (i=0; i<Nb_Vies_Options; i++)
    {
        sprite_Vie[i]=SPR_addSprite(&tiles_Sprite_VIE_H, 16+(i<<4), 200, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    }

    for (i=0; i<Nb_Vies_Options; i++)
    {
        sprite_Vie[i+Nb_Vies_Options]=SPR_addSprite(&tiles_Sprite_VIE_F, 288-(i<<4), 200, TILE_ATTR(PAL2, TRUE, FALSE, FALSE));
    }

    SPR_update();

    SYS_doVBlankProcess();

    //////////////////////////////////////////////
    //               CHARGEMENT PALETTES        //
    //////////////////////////////////////////////

    PAL_setPalette(PAL3, palette_JOUEUR_H.data, DMA);
    PAL_setPalette(PAL0, palette_SELECTION_BGB.data, DMA);
    PAL_setPalette(PAL1, palette_SELECTION_BGA.data, DMA);
    PAL_setPalette(PAL2, palette_02_SELECTION.data, DMA);

    SYS_doVBlankProcess();

    
    for (i=0; i<10; i++)
    {
        scrollOffset_TILE_SELECTION[i]=128;
    }


    // ECRAN SELECTION chargé //
    Selection_OK=1;

}    

void AnimSelection()
{
    u16 i=0;
    u8 CompteurClignotement=1;

    while(Exit_Selection==0)
	{
        /********************************************/
        /*                CLIGNOTEMENT              */
        /********************************************/       
        if(CompteurClignotement==0)
        {
            VDP_setTileMapEx(BG_A,image_SELECTION_BGA.tilemap,TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, AdresseVram_BG_A),8, 9, 0, 0, 26, 2, CPU);
        }
        else if(CompteurClignotement==4)
        {
            VDP_setTileMapEx(BG_A,image_SELECTION_BGA.tilemap,TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, AdresseVram_BG_A),8, 9, 8, 9, 26, 2, CPU);
        }        

        CompteurClignotement++;

        if(CompteurClignotement>8)
        {
            CompteurClignotement=0;
        }

        /********************************************/
        /*                  MANETTE                 */
        /********************************************/ 
        JOY_setEventHandler(Selection_Callback);       

        // Update sprites //
        SPR_update();

        // Vblank //
		SYS_doVBlankProcess();
    }



    /********************************************/
    /*           SORTIE ECRAN SELECTION         */
    /********************************************/
    
    // set all palette to black
    PAL_setColors(0, (u16*) palette_black, 64, DMA_QUEUE);


    for (i=0; i<10; i++)
    {
        scrollOffset_TILE_SELECTION[i]=0;
    }

    // réinit scrolling par tile
    VDP_setHorizontalScrollTile(BG_A, 13, scrollOffset_TILE_SELECTION, 10, CPU);


    // Clear all BG //
    VDP_clearPlane(BG_B,TRUE);
    VDP_clearPlane(BG_A,TRUE);
    VDP_clearPlane(WINDOW,TRUE);

    // Clear all sprites //
    SPR_reset();

    //Selection_OK=0;

    // On passe au NIVEAU 1 //
    Scene=2;

    // Vblank
    SYS_doVBlankProcess();
}




//////////////////////////////////
//        INIT DES NIVEAUX      //
//////////////////////////////////

void InitNiveaux()
{
    switch (Num_Niveau)
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
void InitVies()
{
    u8 i;
    
    for (i=0; i<Nb_Vies; i++)
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
}


void InitNiveau1()
{
    u16 i;

    ID_Arme=0;
    Nb_Projectiles=0;
    Nb_Balles=0;   
    CompteurTir=0;

    CompteurEnergie=1;
    Energie=ENERGIE_DEPART;

    AdresseVram_Tete=0;
    AdresseVram_BarreVerte=0;
    AdresseVram_BarreVierge=0;
    AdresseVram_BarreNoire=0;
    AdresseVram_Continue=0;
    AdresseVram_ChiffresContinue=0;

    vitesseScrolling=1;
    compteurTile=0;

    tilemapOffset=0;

    nb_Ennemis=0;
    indexCreaEnnemis=0;

    nb_Plateformes=0;
    IndexCreaPlateformes=0;
    contactPlt_OK=0;

    PosYinvincible=0;



    // Position X initiale du sprite : 64 pixels
    positionX=FIX32(64L);
    // Position Y initiale du sprite : 56 pixels
    positionY=FIX32(56L);

    movX = FIX32(0);
    movY = FIX32(0);

    maxSpeed_D = MAX_SPEED_D;
    maxSpeed_G = MAX_SPEED_G;
    maxSpeed_V = MAX_SPEED_V;

    CamPosX=0;
    CamPosY=0;

    tileID_BG=0;
    tileID_BD=0;
    posTileY=0;

    tileID_CG=0;
    tileID_CD=0;

    tileID_H=0;

    //////////////////////////////////////////////
    //                CREATION  BG              //
    //////////////////////////////////////////////

    /********************************************/
    /*                     BGB                  */
    /********************************************/

    // safe starting VRAM adress (16)
    u16 ind = TILE_USER_INDEX;

    // BGB tileset loading in VRAM
    // getting tileset data from IMAGE structure declared in maps_NIVEAU1.res
    VDP_loadTileSet(image_NIVEAU1_BGB.tileset, ind, DMA);

    // BGB CREATION
    // getting tilemap data from IMAGE structure declared in maps_NIVEAU1.res
    VDP_setTileMapEx(BG_B, image_NIVEAU1_BGB.tilemap, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, ind), 0, 0, 0, 0, 64, 27, CPU);
    VDP_setTileMapEx(BG_B, image_NIVEAU1_BGB.tilemap, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, ind), 0, 27, 0, 27, 64, 4, CPU);
    //VDP_setTileMap(BG_B, image_NIVEAU1_BGB.tilemap, 0, 0, 64, 28, CPU);

    // we offset tile index by the number of tiles previously loaded in VRAM
    ind += image_NIVEAU1_BGB.tileset->numTile;

    AdresseVram_BG_A=ind;

    // Vblank
    SYS_doVBlankProcess();




    /********************************************/
    /*                     BGA                  */
    /********************************************/

    // BGB tileset loading in VRAM
    // getting tileset data from IMAGE structure declared in maps_NIVEAU1.res
    VDP_loadTileSet(image_NIVEAU1_BGA.tileset, ind, DMA);

    // Vblank
    SYS_doVBlankProcess();

    // BGA CREATION
    // getting tilemap data from IMAGE structure declared in maps_NIVEAU1.res
    VDP_setTileMapEx(BG_A, image_NIVEAU1_BGA.tilemap, TILE_ATTR_FULL(PAL3, FALSE, FALSE, FALSE, ind), 0, 0, 0, 0, 64, 28, CPU);
    //VDP_setTileMap(BG_A, image_NIVEAU1_BGA.tilemap, 0, 0, 64, 28, CPU);

    // we offset tile index by the number of tiles previously loaded in VRAM
    ind += image_NIVEAU1_BGA.tileset->numTile;

    // Vblank
    SYS_doVBlankProcess();




    /********************************************/
    /*                  WINDOW                  */
    /********************************************/

    VDP_setWindowHPos(0, 0);
    VDP_setWindowVPos(0, 6);

    // WINDOW tileset loading in VRAM
    // getting tileset data from IMAGE structure declared in maps_GLOBALES.res
    VDP_loadTileSet(image_WINDOW.tileset, ind, DMA);


    // WINDOW CREATION
    // getting tilemap data from IMAGE structure declared in maps_GLOBALES.res
    VDP_setTileMapEx(WINDOW, image_WINDOW.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, ind), 0, 0, 0, 0, 40, 6, DMA);

    // we offset tile index by the number of tiles previously loaded in VRAM
    ind += image_WINDOW.tileset->numTile;

    // Vblank
    SYS_doVBlankProcess();



    //////////////////////////////////////
    //          TILES CONTINUE ?        //
    //////////////////////////////////////

    AdresseVram_Continue=ind;

    // getting tileset data from IMAGE structure declared in maps_GLOBALES.res
    VDP_loadTileSet(image_CONTINUE.tileset, ind, DMA);

    // we offset tile index by the number of tiles previously loaded in VRAM
    ind += image_CONTINUE.tileset->numTile;


    //////////////////////////////////////
    //           TILES CHIFFRES         //
    //////////////////////////////////////

    AdresseVram_ChiffresContinue=ind;

    // getting tileset data from IMAGE structure declared in maps_GLOBALES.res
    VDP_loadTileSet(image_CHIFFRE_9.tileset, ind, DMA);

    // we offset tile index by the number of tiles previously loaded in VRAM
    ind += image_CHIFFRE_9.tileset->numTile;



    ///////////////////
    //  TETE JOUEUR  //
    ///////////////////

    // On récupère l'adresse en Vram des tiles de la tête
    AdresseVram_Tete=ind;


    if(selectJoueur==0)
    {
        VDP_loadTileSet(&tileset_TETE_H, ind, DMA);
        VDP_setTileMapEx(WINDOW, image_TETE_H.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, ind), 1, 1, 0, 0, 2, 2, DMA);

        // we offset tile index by the number of tiles previously loaded in VRAM
        ind += tileset_TETE_H.numTile;
    }
    else
    {
        VDP_loadTileSet(&tileset_TETE_F, ind, DMA);
        VDP_setTileMapEx(WINDOW, image_TETE_F.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, ind), 1, 1, 0, 0, 2, 2, DMA);

        // we offset tile index by the number of tiles previously loaded in VRAM
        ind += tileset_TETE_F.numTile;
    }

    // Vblank
    SYS_doVBlankProcess();


    VDP_setVerticalScroll(BG_B, 24);


    ////////////////////////////////////////////////////
    //                  BARRES DE VIE                 //
    ////////////////////////////////////////////////////

    // On récupère l'adresse en Vram des tiles de la barre d'énergie
    AdresseVram_BarreVerte=ind;

    // WINDOW tileset loading in VRAM
    // getting tileset data from IMAGE structure declared in maps_GLOBAL.res
    VDP_loadTileSet(&tileset_BARRE_VERTE1, ind, DMA);

    for (i=0; i<ENERGIE_DEPART; i++)
    {
        VDP_setTileMapEx(WINDOW, image_BARRE_VERTE1.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, ind), 4+i, 3, 0, 0, 1, 2, DMA);
    }

    // we offset tile index by the number of tiles previously loaded in VRAM
    ind += tileset_BARRE_VERTE1.numTile;



    // On récupère l'adresse en Vram des tiles de la barre vierge
    AdresseVram_BarreVierge=ind;

    // WINDOW tileset loading in VRAM
    // getting tileset data from IMAGE structure declared in maps_GLOBAL.res
    VDP_loadTileSet(&tileset_BARRE_VIERGE, ind, DMA);

    for (i=ENERGIE_DEPART; i<ENERGIE_DEPART+7; i++)
    {
        VDP_setTileMapEx(WINDOW, image_BARRE_VIERGE.tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, ind), 4+i, 3, 0, 0, 1, 2, DMA);
    }

    // we offset tile index by the number of tiles previously loaded in VRAM
    ind += tileset_BARRE_VIERGE.numTile;


    
    // On récupère l'adresse en Vram des tiles de la barre noire
    AdresseVram_BarreNoire=ind;

    // WINDOW tileset loading in VRAM
    // getting tileset data from IMAGE structure declared in maps_GLOBAL.res
    VDP_loadTileSet(&tileset_BARRE_NOIRE, ind, DMA);

    // we offset tile index by the number of tiles previously loaded in VRAM
    ind += tileset_BARRE_NOIRE.numTile;

    // Vblank
    SYS_doVBlankProcess();





    //////////////////////////////////////////////
    //                  SPRITES                 //
    //////////////////////////////////////////////

    SPR_init();

    /*************/
    /* GAME OVER */
    /*************/
    sprite_GameOver=SPR_addSprite(&tiles_Sprite_GAMEOVER, 0, -32, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));

    /*********/
    /* ROUND */
    /*********/
    sprite_Round=SPR_addSprite(&tiles_Sprite_ROUND, 132, 200, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));

    if(Num_Niveau==1)
    {
        sprite_NumRound=SPR_addSprite(&tiles_Sprite_1, 180, 200, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    }

    /***********/
    /* CREDITS */
    /***********/
    sprite_Credits=SPR_addSprite(&tiles_Sprite_CREDITS, 0, -8, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    sprite_Nb_Credits=SPR_addSprite(&tiles_Sprite_CHIFFRES, 0, -8, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    SPR_setFrame(sprite_Nb_Credits,Nb_Credits);

    /*********/
    /* PAUSE */
    /*********/
    sprite_Pause=SPR_addSprite(&tiles_Sprite_PAUSE, -40, 0, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));

    /*********/
    /*  VIES */
    /*********/
    InitVies();

    /**********/
    /* SPLASH */
    /**********/
    SpriteSplash_ *ptrSplash=&Splash;

    ptrSplash->Init=0;
    ptrSplash->PosX=48;
    ptrSplash->PosY=-32;
    ptrSplash->CompteurFrameSplash=0;
    ptrSplash->IndexFrameSplash=0;

    ptrSplash->SpriteS=SPR_addSprite(&tiles_Sprite_SPLASH, ptrSplash->PosX, ptrSplash->PosY, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
    SPR_setAnim(ptrSplash->SpriteS,0);
    SPR_setFrame(ptrSplash->SpriteS,0);


    /**********/
    /* DRAGON */
    /**********/
    SpriteDragon_ *ptrDragon=&Dragon;

    ptrDragon->Phase=ATTENTE_DRAGON;

    ptrDragon->PosX=0;
    ptrDragon->PosY=-32;

    ptrDragon->CompteurFrameVol=0;
    ptrDragon->IndexFrameVol=0;

    ptrDragon->SpriteD=SPR_addSprite(&tiles_Sprite_DRAGON, ptrDragon->PosX, ptrDragon->PosY, TILE_ATTR(PAL0, FALSE, FALSE, FALSE));
    SPR_setAnim(ptrDragon->SpriteD,0);
    SPR_setFrame(ptrDragon->SpriteD,0);

    /**********/
    /* JOUEUR */
    /**********/
    // Création d'un pointeur de type "SpritePerso_" contenant la variable "Joueur".
    SpriteJoueur_ *ptrJoueur=&Joueur;

    if(selectJoueur==0)
    {
        ptrJoueur->SpriteJ_BAS = SPR_addSprite(&tiles_Sprite_JOUEUR_H_BAS, 64, 56, TILE_ATTR(PAL0, FALSE, FALSE, FALSE));
        ptrJoueur->SpriteJ_HAUT = SPR_addSprite(&tiles_Sprite_JOUEUR_H_HAUT, 64, 32, TILE_ATTR(PAL0, FALSE, FALSE, FALSE));
    }
    else
    {
        ptrJoueur->SpriteJ_BAS = SPR_addSprite(&tiles_Sprite_JOUEUR_F_BAS, 64, 56, TILE_ATTR(PAL0, FALSE, FALSE, FALSE));
        ptrJoueur->SpriteJ_HAUT = SPR_addSprite(&tiles_Sprite_JOUEUR_F_HAUT, 64, 32, TILE_ATTR(PAL0, FALSE, FALSE, FALSE));
    }

    // PHASE CHUTE DEBUT //
    ptrJoueur->Phase=CHUTE;

    // ORIENTE DROITE //
    ptrJoueur->Axe=0;
    ptrJoueur->Arme=0;

    ptrJoueur->Invincible=0;
    ptrJoueur->HorsChamp=0;

    // POSITION //
    ptrJoueur->PosX=fix32ToInt(positionX);
    ptrJoueur->PosY=fix32ToInt(positionY);

    //SPR_setPosition(ptrJoueur->SpriteJ_BAS, ptrJoueur->PosX, ptrJoueur->PosY);

    // INIT DES COMPTEURS //
    ptrJoueur->CompteurFrameBloque=0;
    ptrJoueur->IndexFrameBloque=0;

    ptrJoueur->CompteurFrameArret=0;
    ptrJoueur->IndexFrameArret=0;

    ptrJoueur->CompteurFrameTir=0;
    ptrJoueur->IndexFrameTir=0;

    ptrJoueur->CompteurFrameTouche=0;
    ptrJoueur->IndexFrameTouche=0;

    ptrJoueur->CompteurApparition=0;

    ptrJoueur->pt_Coll_BG_X=ptrJoueur->PosX+8;
    ptrJoueur->pt_Coll_BG_Y=ptrJoueur->PosY+10;
    ptrJoueur->pt_Coll_BD_X=ptrJoueur->PosX+21;
    ptrJoueur->pt_Coll_BD_Y=ptrJoueur->pt_Coll_BG_Y;

    posTileY=ptrJoueur->pt_Coll_BG_Y>>3;

    SPR_setAnim(ptrJoueur->SpriteJ_BAS,4);
    SPR_setFrame(ptrJoueur->SpriteJ_BAS,0);

    /***********/
    /* REPERES */
    /***********/

    //sprite_repere_BG=SPR_addSprite(&tiles_repere_BG, ptrJoueur->pt_Coll1_X, ptrJoueur->pt_Coll1_Y-7, TILE_ATTR(PAL0, FALSE, FALSE, FALSE));
    //sprite_repere_BD=SPR_addSprite(&tiles_repere_BD, ptrJoueur->pt_Coll2_X-7, ptrJoueur->pt_Coll1_Y-7, TILE_ATTR(PAL0, FALSE, FALSE, FALSE));



    /**********/
    /*  AURA  */
    /**********/
    SpriteAura_ *ptrAura=&Aura;

    ptrAura->Init=0;
    ptrAura->PosX=0;
    ptrAura->PosY=-24;
    ptrAura->CompteurFrameAura=0;
    ptrAura->IndexFrameAura=0;


    if(selectJoueur==0)
    {
        ptrAura->SpriteA=SPR_addSprite(&tiles_Sprite_AURA_H, ptrAura->PosX, ptrAura->PosY, TILE_ATTR(PAL0, FALSE, FALSE, FALSE));
    }
    else
    {
        ptrAura->SpriteA=SPR_addSprite(&tiles_Sprite_AURA_F, ptrAura->PosX, ptrAura->PosY, TILE_ATTR(PAL0, FALSE, FALSE, FALSE));

    }



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

    // Init adresse reesources sprites ennemis
    AdrTilesEnnemi[0]=&tiles_Sprite_ESCARGOT_H;
    AdrTilesEnnemi[1]=&tiles_Sprite_BULOT;
    AdrTilesEnnemi[2]=&tiles_Sprite_ESCARGOT_V;
    AdrTilesEnnemi[3]=&tiles_Sprite_MORSE;
    AdrTilesEnnemi[4]=&tiles_Sprite_POULPE;
    AdrTilesEnnemi[5]=&tiles_Sprite_POULPE;
    AdrTilesEnnemi[6]=&tiles_Sprite_PELICAN;



    /***************/
    /* PLATEFORMES */
    /***************/
    // Init de la structure des sprites des plateformes.
    // Init=0 car les plateformes n'ont pas encore été créés.
    // Aucune assignation de sprite dans SpriteP.
    for(i=0;i<MAX_PLATEFORMES;i++)
    {
        Plateforme[i].Init=0;
        Plateforme[i].ptrPosition=0;
    }


    /***************/
    /*   BALLES    */
    /***************/
    for(i=0;i<MAX_BALLES;i++)
    {
        Balles[i].Init=0;
    }


    SPR_update();

    /////////////////////////////
    // TILEMAP COLLISION DECOR //
    /////////////////////////////
    // Pointeur *tilemapCollision de type Map déclaré dans variables.h
    // MAP tilemap_COLLISION_NIVEAU1 déclarée dans maps_NIVEAU1.res
    tilemapCollision=MAP_create(&tilemap_COLLISION_NIVEAU1, BG_A, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USER_INDEX));


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

    Niveau_OK=1;
}
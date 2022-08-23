#include <genesis.h>
#include "variables.h"

///////////////////////////////////
//		Variables principales    //
///////////////////////////////////

u16 StatutJoy=0;

u8 Scene=0;

bool Titre_OK=0;
bool Selection_OK=0;
bool Niveau_OK=0;

u8 Nb_Vie=2;
u8 Nb_Tirs=0;
u8 Nb_Balles=0;

u8 CompteurTir=0;

u16 GameOver=0;
bool PauseJeu=0;

u8 Num_Niveau=1;
u8 selectJoueur=0;

u8 CompteurEnergie;
u8 Energie;

u16 AdresseVram_Tete=0;
u16 AdresseVram_BarreEnergie=0;
u16 AdresseVram_BarreVierge=0;

bool Tir_OK=0;

char texteSortie[3];

///////////////////////////////////
//		Variables scrolling      //
///////////////////////////////////
u16 AdresseVram_BG_A=0;
s16 scrollOffset_TILE_SELECTION[10]={0,0,0,0,0,0,0,0,0,0};

u8 vitesseScrolling=1;

s16 CamPosX=0;
s16 CamPosY=0;

//s16 scrollOffset_TILE_TITRE[10]={1,1,1,1,1,1,1,1,1,0};
s16 scrollOffset_TILE_NIVEAU1_BGA[28]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
s16 scrollOffset_TILE_NIVEAU1_BGB[28]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

///////////////////////////////////
//		Variables Sprites        //
///////////////////////////////////
Sprite *sprite_Vie[3];
Sprite *sprite_Titre[6];
Sprite *sprite_Pause;
Sprite *sprite_Round;
Sprite *sprite_NumRound;

Sprite *sprite_Press_Start;

Sprite *sprite_repere_BG;
Sprite *sprite_repere_BD;


//----------------------------------------------------//
//                       JOUEUR                       //
//----------------------------------------------------//
SpriteJoueur_ Joueur;

///////////////////////////////////
//		 Variables Joueur        //
///////////////////////////////////
fix32 maxSpeed_D;
fix32 maxSpeed_G;
fix32 maxSpeed_V;

fix32 positionX;
fix32 positionY;
fix32 movX;
fix32 movY;

u16 PosYinvincible;


//----------------------------------------------------//
//                       DRAGON                       //
//----------------------------------------------------//
SpriteDragon_ Dragon;


//----------------------------------------------------//
//                       SPLASH                       //
//----------------------------------------------------//

SpriteSplash_ Splash;


//----------------------------------------------------//
//                      ENNEMIS                       //
//----------------------------------------------------//
SpriteEnnemi_ Ennemi[MAX_ENNEMIS];
const SpriteDefinition *AdrTilesEnnemi[7];


//----------------------------------------------------//
//                    PLATEFORMES                     //
//----------------------------------------------------//
SpritePlateforme_ Plateforme[MAX_PLATEFORMES];
u8 IndexCreaPlateformes;
u8 nb_Plateformes=0;
bool contactPlt_OK=0;


//----------------------------------------------------//
//                        AURA                        //
//----------------------------------------------------//

SpriteAura_ Aura;


//----------------------------------------------------//
//                      TILEMAPS                      //
//----------------------------------------------------//
Map *tilemapCollision;

u16 tileID_BG=0;
u16 tileID_BD=0;
u16 posTileY;

u16 tileID_CG=0;
u16 tileID_CD=0;

u8 compteurTile=0; // 0 -> 7 //
u16 tilemapOffset=0;

u8 nb_Ennemis;
u8 indexCreaEnnemis;

//bool contactSol_OK=0;

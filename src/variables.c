#include <genesis.h>
#include <variables.h>


///////////////////////////////////
//		Variables principales    //
///////////////////////////////////

u16 StatutJoy=0;

u8 nb_Vie=2;
u16 GameOver=0;
bool PauseJeu=0;

u8 num_Niveau=1;
u8 selectJoueur=0;

char texteSortie[2];

///////////////////////////////////
//		Variables scrolling      //
///////////////////////////////////
u8 vitesseScrolling=1;

s16 CamPosX=0;
s16 CamPosY=0;

s16 scrollOffset_TILE_TITRE[10]={1,1,1,1,1,1,1,1,1,0};
s16 scrollOffset_TILE_NIVEAU1_BGA[28]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
s16 scrollOffset_TILE_NIVEAU1_BGB[28]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

///////////////////////////////////
//		Variables Sprites        //
///////////////////////////////////
Sprite *sprite_Vie[3];
Sprite *sprite_Pause[2];


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


//----------------------------------------------------//
//                      ENNEMIS                       //
//----------------------------------------------------//
SpriteEnnemi_ Ennemi[10];
const SpriteDefinition *adrResEnnemi[12];


//----------------------------------------------------//
//                    PLATEFORMES                     //
//----------------------------------------------------//
SpritePlateforme_ Plateforme[5];
u8 indexCreaPlateformes;
u8 nb_Plateformes;

//----------------------------------------------------//
//                      TILEMAPS                      //
//----------------------------------------------------//
Map *tilemapCollision;

u16 tileID_G=0;
u16 tileID_D=0;
u16 posTileY;

u8 compteurTile=0; // 0 -> 7 //
u16 tilemapOffset=0;

u8 nb_Ennemis;
u8 indexCreaEnnemis;

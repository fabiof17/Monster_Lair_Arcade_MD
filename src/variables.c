#include <genesis.h>
#include <variables.h>


///////////////////////////////////
//		Variables principales
///////////////////////////////////

//u16 ind=0;

u16 StatutJoy=0;

u8 nb_Vie=2;
u16 GameOver=0;
u16 PauseJeu=0;

u8 num_Niveau=1;
u8 selectJoueur=0;

// CAMERA
u8 vitesseScrolling=1;

s16 CamPosX=0;
s16 CamPosY=0;

s16 scrollOffset_TILE_TITRE[10]={1,1,1,1,1,1,1,1,1,0};
s16 scrollOffset_TILE_NIVEAU1_BGA[28]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
s16 scrollOffset_TILE_NIVEAU1_BGB[28]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

u16 tilemapOffset=0;

u16 tileID_G=0;
u16 tileID_D=0;

u8 compteurTile=0; // 0 -> 7 //

char texteSortie[2];

// SPRITES
Sprite *sprite_Vie[3];
Sprite *sprite_Pause[2];

SpriteJoueur_ Joueur;
SpriteEnnemi_ Ennemi[10];
SpritePlateforme_ Plateforme[5];

SpriteJoueur_ *ptrJoueur;

const SpriteDefinition *adrResEnnemi[12];

// TILEMAPS
Map *tilemapCollision;
//Map *tilemapEnnemis;

u8 indexCreaEnnemis;
u8 indexCreaPlateformes;

// VARIABLES //
fix32 maxSpeed;
fix32 jumpSpeed;
fix32 gravity;

fix32 positionX;
fix32 positionY;
fix32 movX;
fix32 movY;
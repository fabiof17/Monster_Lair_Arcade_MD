#include <genesis.h>
#include <variables.h>

///////////////////////////////////
//		Variables principales
///////////////////////////////////

s16 i=0;
u16 ind=0;

u16 StatutJoy=0;

u16 palette[64];

u8 nb_Vie=2;
u16 GameOver=0;
u16 PauseJeu=0;

u8 num_Niveau=1;

//Map *bga;
//Map *bgb;

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

u16 tileID_ENNEMI=0;

u8 compteurTile=0; // 0 -> 7 //

// SPRITES
Sprite *sprite_Vie[3];
Sprite *sprite_Pause[2];

SpriteJoueur_ *Joueur;
SpriteEnnemi_ Ennemi[10];

// TILEMAPS
Map *tilemapCollision;
Map *tilemapEnnemis;
u8 indexCreaEnnemis=0;

char monTexte[2];
char *texte;
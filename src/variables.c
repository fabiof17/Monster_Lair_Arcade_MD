#include <genesis.h>
#include "variables.h"

///////////////////////////////////
//		       DEBUG            //
///////////////////////////////////

bool DEBUG_COLLISIONS_ENNEMIS;

///////////////////////////////////
//		Variables principales    //
///////////////////////////////////

u8 Scene=0;                                                 // init ---> InitVariablesGeneral() //

bool Titre_OK;                                              // init ---> InitVariablesGeneral() //
bool Selection_OK;                                          // init ---> InitVariablesGeneral() //
bool Niveau_OK;                                             // init ---> InitVariablesGeneral() //

u16 Score;                                                  // init ---> InitVariablesGeneral() //

bool SWITCH_CONTINUE;                                       // init ---> InitVariablesGeneral() //
bool SWITCH_GAMEOVER;                                       // init ---> InitVariablesGeneral() //
bool PauseJeu;                                              // init ---> InitVariablesGeneral() //

u8 Num_Niveau;                                              // init ---> InitVariablesGeneral() //

u16 Compteur_Continue;                                      // init ---> InitVariablesGeneral() //

u16 AdresseVram_BG_A;                                       // init ---> InitVariablesGeneral() //

u8 Nb_Vies;                                                 // init ---> InitVariablesGeneral() //
u8 Nb_Vies_Options;                                         // init ---> InitVariablesGeneral() //
u8 Nb_Credits;                                              // init ---> InitVariablesGeneral() //
u8 Nb_Impacts;                                              // init ---> InitVariablesGeneral() //
u8 Nb_ExploEnnemis;                                         // init ---> InitVariablesGeneral() //
u8 Nb_Chiffres;                                             // init ---> InitVariablesGeneral() //

char texteSortie[3];


///////////////////////////////////
//		  Variables titre        //
///////////////////////////////////

bool Exit_Titre;                                            // init ---> InitTitre() //
bool Menu_Titre;                                            // init ---> InitTitre() //
u8 Pos_Menu_Titre;

///////////////////////////////////
//		Variables sélection      //
///////////////////////////////////

u8 selectJoueur;                                            // init ---> InitSelection() //
bool Exit_Selection;                                        // init ---> InitSelection() //
s16 scrollOffset_TILE_SELECTION[10];                        // init ---> InitSelection() //


///////////////////////////////////
//		 Variables niveaux       //
///////////////////////////////////

u8 Nb_Projectiles;                                          // init ---> InitNiveau1() //
u8 Nb_Balles;                                               // init ---> InitNiveau1() //

u8 CompteurTir=0;                                           // init ---> InitNiveau1() //
//bool Tir_OK=0;                                            // init ---> InitNiveau1() //

u8 CompteurEnergie;                                         // init ---> InitNiveau1() //
u8 Energie;                                                 // init ---> InitNiveau1() //

u16 AdresseVram_Tete=0;                                     // init ---> InitNiveau1() //

u16 AdresseVram_BarreVerte=0;                               // init ---> InitNiveau1() //
u16 AdresseVram_BarreVierge=0;                              // init ---> InitNiveau1() //
u16 AdresseVram_BarreNoire=0;                               // init ---> InitNiveau1() //

u16 AdresseVram_Continue=0;                                 // init ---> InitNiveau1() //
u16 AdresseVram_ChiffresContinue=0;                         // init ---> InitNiveau1() //
u16 AdresseVram_ChiffresScore;                              // init ---> InitNiveau1() //

///////////////////////////////////
//		Variables scrolling      //
///////////////////////////////////


u8 vitesseScrolling;                                        // init ---> InitNiveau1() //

s16 CamPosX=0;                                              // init ---> InitNiveau1() //
s16 CamPosY=0;                                              // init ---> InitNiveau1() //


///////////////////////////////////
//		Variables Sprites        //
///////////////////////////////////
Sprite *sprite_Vie[10];
Sprite *sprite_Titre[6];

Sprite *sprite_Menu_Titre;

Sprite *sprite_Bouton_Options;
Sprite *sprite_Player_Options;
Sprite *sprite_Credits_Options;
Sprite *sprite_Start_Options;
Sprite *sprite_Nb_Player_Options;
Sprite *sprite_Nb_Credits_Options;


Sprite *sprite_Pause;
Sprite *sprite_Round;
Sprite *sprite_NumRound;
Sprite *sprite_Credits;
Sprite *sprite_Nb_Credits;

Sprite *sprite_Press_Start;
Sprite *sprite_GameOver;

Sprite *sprite_repere_BG;
Sprite *sprite_repere_BD;


//----------------------------------------------------//
//                       JOUEUR                       //
//----------------------------------------------------//
SpriteJoueur_ Joueur;

///////////////////////////////////
//		 Variables Joueur        //
///////////////////////////////////
fix32 maxSpeed_D;                                           // init ---> InitNiveau1() //
fix32 maxSpeed_G;                                           // init ---> InitNiveau1() //
fix32 maxSpeed_V;                                           // init ---> InitNiveau1() //

fix32 positionX;                                            // init ---> InitNiveau1() //
fix32 positionY;                                            // init ---> InitNiveau1() //

fix32 movX;                                                 // init ---> InitNiveau1() //
fix32 movY;                                                 // init ---> InitNiveau1() //

u16 PosYinvincible;                                         // init ---> InitNiveau1() //


//----------------------------------------------------//
//----------------------------------------------------//
//                       ARMES                        //
//----------------------------------------------------//
//----------------------------------------------------//

u8 ID_Arme;

//----------------------------------------------------//
//                       IMPACT                       //
//----------------------------------------------------//
SpriteImpact_ Impacts[MAX_IMPACTS];

//----------------------------------------------------//
//                   EXPLOSION ENNEMI                 //
//----------------------------------------------------//
SpriteExploEnnemi_ ExploEnnemis[MAX_IMPACTS];

//----------------------------------------------------//
//                       BALLES                       //
//----------------------------------------------------//
SpriteBalle_ Balles[MAX_BALLES];

//----------------------------------------------------//
//                       ANNEAU                       //
//----------------------------------------------------//
SpriteAnneau_ Anneaux[MAX_ANNEAUX];





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
//const u8 LargeurEnnemis[7];

//----------------------------------------------------//
//                    PLATEFORMES                     //
//----------------------------------------------------//
SpritePlateforme_ Plateforme[MAX_PLATEFORMES];

u8 IndexCreaPlateformes;                                    // init ---> InitNiveau1() //
u8 nb_Plateformes;                                          // init ---> InitNiveau1() //
bool contactPlt_OK;                                         // init ---> InitNiveau1() //

//----------------------------------------------------//
//                        AURA                        //
//----------------------------------------------------//

SpriteAura_ Aura;

//----------------------------------------------------//
//                       SCORE                        //
//----------------------------------------------------//
u8 tableau_Score[9];



//----------------------------------------------------//
//                      TILEMAPS                      //
//----------------------------------------------------//
Map *tilemapCollision;

u16 tileID_BG;                                              // init ---> InitNiveau1() //
u16 tileID_BD;                                              // init ---> InitNiveau1() //
u16 posTileY;                                               // init ---> InitNiveau1() //

u16 tileID_CG;                                              // init ---> InitNiveau1() //
u16 tileID_CD;                                              // init ---> InitNiveau1() //

u16 tileID_H;

u8 compteurTile;                                            // init ---> InitNiveau1() //
u16 tilemapOffset;                                          // init ---> InitNiveau1() //

u8 nb_Ennemis;                                              // init ---> InitNiveau1() //
u8 indexCreaEnnemis;                                        // init ---> InitNiveau1() //

#ifndef _VARIABLES_H
#define _VARIABLES_H

// CONSTANTES //
#define MAX_SPEED_D     FIX32(1L) // VITESSE MAX HORIZONTALE DROITE
#define MAX_SPEED_G     FIX32(2L) // VITESSE MAX HORIZONTALE GAUCHE
#define MAX_SPEED_V     FIX32(3L) // VITESSE MAX VERTICALE
//#define MAX_SPEED_S     FIX32(1L) // VITESSE MAX SAUT

#define ACCEL_D         FIX32(0.08)
#define ACCEL_G         FIX32(0.16)
#define ACCEL_B         FIX32(0.1)
//#define ACCEL_S         FIX32(0.1)
#define GLISSEMENT      FIX32(1L)

#define MAX_POS_D       FIX32(228L)
#define MAX_POS_G       FIX32(11L)

#define MAX_ETAPES_SAUT    40
#define MAX_ETAPES_POULPE1 50
#define MAX_ETAPES_POULPE2 55
#define MAX_ETAPES_PF_V1   69

///////////////////////////////////
//		Variables principales    //
///////////////////////////////////

extern u16 StatutJoy;

extern u8 nb_Vie;
extern u16 GameOver;
extern bool PauseJeu;

extern u8 num_Niveau;
extern u8 selectJoueur;

extern char texteSortie[2];

///////////////////////////////////
//		Variables scrolling      //
///////////////////////////////////

extern u8 vitesseScrolling;

extern s16 CamPosX;
extern s16 CamPosY;

extern s16 scrollOffset_TILE_TITRE[10];
extern s16 scrollOffset_TILE_NIVEAU1_BGA[28];
extern s16 scrollOffset_TILE_NIVEAU1_BGB[28];

///////////////////////////////////
//		Variables Sprites        //
///////////////////////////////////

extern Sprite *sprite_Vie[3];
extern Sprite *sprite_Pause[2];



//----------------------------------------------------//
//                       JOUEUR                       //
//----------------------------------------------------//
typedef struct
{
    Sprite* SpriteJ;
    u8 Phase; // 0=ARRET - 1=MARCHE - 2=SAUT - 3=TIR - 4=SAUT+TIR - 98=CHUTE - 99=TOUCHÉ - 100=MORT
    u8 Axe; // 0=DROITE - 1=GAUCHE
    s16 PosX;
    s16 PosY;
    u16 pt_Coll1_X;
    u16 pt_Coll1_Y;
    u16 pt_Coll2_X;
    u8 CompteurFrameArret;      // Compteur pour passer à la prochaine FRAME ARRET
    u8 IndexFrameArret;         // Index de FRAME ARRET
    u8 CompteurFrameBloque;     // Compteur pour passer à la prochaine FRAME BLOQUÉ
    u8 IndexFrameBloque;        // Index de FRAME BLOQUÉ
    u8 CompteurFrameMarche;     // Compteur pour passer à la prochaine FRAME MARCHE
    u8 IndexFrameMarche;        // Index de FRAME MARCHE
    const s16 *ptrPosition;     // Pointeur dans le tableau de position
} SpriteJoueur_;

extern SpriteJoueur_ Joueur;


///////////////////////////////////
//		 Variables Joueur        //
///////////////////////////////////
extern fix32 maxSpeed_D;
extern fix32 maxSpeed_G;
extern fix32 maxSpeed_V;

extern fix32 positionX;
extern fix32 positionY;
extern fix32 movX;
extern fix32 movY;



//----------------------------------------------------//
//                      ENNEMIS                       //
//----------------------------------------------------//
typedef struct
{
    Sprite* SpriteE;
    u8 Phase;                   // 0 = ARRET / 1 = MARCHE
    bool Axe;                   // 0 = Bas / 1 = Haut
    u8 Init;                    // Sprite créé ou non
    u8 ID;                      // Type d'ennemi
    u8 PointsVie;               // Nb points de vie
    s16 PosX;                   // Position X
    s16 PosY;                   // Position Y
    u16 pt_Coll1_X;
    u16 pt_Coll1_Y;
    u16 pt_Coll2_X;
    u16 pt_Coll2_Y;
    u8 CompteurPosition;        // Compteur pour déclencher le déplacement du sprite
    u8 CompteurFrame;           // Compteur pour passer à la prochaine FRAME
    u8 IndexFrame;              // Index de FRAME
    const s16 *ptrPosition;     // Pointeur dans le tableau de position
} SpriteEnnemi_;

extern SpriteEnnemi_ Ennemi[10];
extern const SpriteDefinition *adrResEnnemi[12];
extern u8 indexCreaEnnemis;
extern u8 nb_Ennemis;



//----------------------------------------------------//
//                    PLATEFORMES                     //
//----------------------------------------------------//
typedef struct
{
    Sprite* SpriteP;
    u8 Init;                    // Sprite créé ou non
    u8 ID;                      // Type de plateforme
    u8 mouvante;                // Plateforme qui se déclenche ou non
    u8 declencheur;             // Déclencheur d'animation
    s16 PosX;                   // Position X
    s16 PosY;                   // Position Y
    const s16 *ptrPosition;     // Pointeur dans le tableau de position
} SpritePlateforme_;

extern SpritePlateforme_ Plateforme[5];
extern u8 indexCreaPlateformes;
extern u8 nb_Plateformes;



//----------------------------------------------------//
//                      TILEMAPS                      //
//----------------------------------------------------//
extern Map *tilemapCollision;

extern u16 tileID_G;
extern u16 tileID_D;
extern u16 posTileY;

extern u8 compteurTile; // 0 -> 7 //
extern u16 tilemapOffset;

#endif // _MAIN
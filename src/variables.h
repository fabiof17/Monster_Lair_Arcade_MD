#ifndef _VARIABLES_H
#define _VARIABLES_H

// CONSTANTES //
#define MAX_SPEED_D     FIX32(1L)   // VITESSE MAX HORIZONTALE DROITE
#define MAX_SPEED_G     FIX32(2L)   // VITESSE MAX HORIZONTALE GAUCHE
#define MAX_SPEED_V     FIX32(3L)   // VITESSE MAX VERTICALE

#define ACCEL_D         FIX32(0.08)  // ACCELERATION DROITE
#define ACCEL_G         FIX32(0.16)  // ACCELERATION GAUCHE
#define ACCEL_B         FIX32(0.5)   // ACCELERATION BAS (GRAVITE)
#define ACCEL_C         FIX32(0.1)   // ACCELERATION DROITE/GAUCHE LORS DE LA CHUTE
#define GLISSEMENT      FIX32(1L)

#define MAX_POS_D       FIX32(228L) // LIMITE DROITE ECRAN
#define MAX_POS_G       FIX32(11L)  // LIMITE GAUCHE ECRAN

#define MAX_ETAPES_SAUT         40
#define MAX_ETAPES_TOUCHE       37
#define MAX_ETAPES_POULPE1      50
#define MAX_ETAPES_POULPE2      55
#define MAX_ETAPES_PF_V1        69
#define MAX_ETAPES_PF_V2        28
#define MAX_ETAPES_PF_H1        50
#define MAX_ETAPES_PF_H2        65

#define MAX_ENNEMIS             11
#define MAX_PLATEFORMES         7

#define ARRET                   0
#define MARCHE                  1
#define TIR                     2
#define SAUT                    3
#define SAUT_TIR                4
#define CHUTE                   5
#define CHUTE_TIR               6
#define TOUCHE                  7
#define APPARITION              8


#define ATTENTE_DRAGON          0
#define VOL_DRAGON              1
#define SORTIE_DRAGON           2
#define DUREE_INVINCIBLE        119

#define ENERGIE_DEPART          7
#define DELAI_MAJ_ENERGIE       239
#define TAILLE_BARRE            14


///////////////////////////////////
//		Variables principales    //
///////////////////////////////////

extern u16 StatutJoy;

extern u8 Nb_Vie;
extern u8 Nb_Tirs;
extern u16 GameOver;
extern bool PauseJeu;

extern u8 Num_Niveau;
extern u8 selectJoueur;

extern u8 CompteurEnergie;
extern u8 Energie;

extern u16 AdresseVram_Tete;
extern u16 AdresseVram_BarreEnergie;
extern u16 AdresseVram_BarreVierge;
extern u16 AdresseVram_BG_A;

extern bool Tir_OK;

extern char texteSortie[3];

///////////////////////////////////
//		Variables scrolling      //
///////////////////////////////////

extern u8 vitesseScrolling;

extern s16 CamPosX;
extern s16 CamPosY;

//extern s16 scrollOffset_TILE_TITRE[10];
extern s16 scrollOffset_TILE_NIVEAU1_BGA[28];
extern s16 scrollOffset_TILE_NIVEAU1_BGB[28];

///////////////////////////////////
//		Variables Sprites        //
///////////////////////////////////

extern Sprite *sprite_Vie[3];
extern Sprite *sprite_Pause[2];

extern Sprite *sprite_repere_BG;
extern Sprite *sprite_repere_BD;

//----------------------------------------------------//
//                       JOUEUR                       //
//----------------------------------------------------//
typedef struct
{
    Sprite* SpriteJ_BAS;
    Sprite* SpriteJ_HAUT;
    u8 Phase;                   // 0=ARRET - 1=MARCHE - 2=SAUT - 3=TIR - 4=SAUT+TIR - 98=CHUTE - 99=TOUCH?? - 100=MORT
    u8 Axe;                     // 0=DROITE - 1=GAUCHE
    u8 Arme;                    // 0=TIR DE BASE - 1=SHURIKEN - 2=DOUBLE BOULE - 

    s16 PosX;
    s16 PosY;
    s16 pt_Coll_BG_X;           // Points de collision BAS
    s16 pt_Coll_BG_Y;
    s16 pt_Coll_BD_X;
    s16 pt_Coll_BD_Y;

    s16 pt_Coll_CG_X;           // Points de collision C??T??
    s16 pt_Coll_CG_Y;
    s16 pt_Coll_CD_X;
    s16 pt_Coll_CD_Y;

    u16 CompteurApparition;
    bool Invincible;
    u8 CompteurInvincible;
    bool HorsChamp;
    
    u8 CompteurFrameArret;      // Compteur pour passer ?? la prochaine FRAME ARRET
    u8 IndexFrameArret;         // Index de FRAME ARRET
    u8 CompteurFrameBloque;     // Compteur pour passer ?? la prochaine FRAME BLOQU??
    u8 IndexFrameBloque;        // Index de FRAME BLOQU??
    u8 CompteurFrameMarche;     // Compteur pour passer ?? la prochaine FRAME MARCHE
    u8 IndexFrameMarche;        // Index de FRAME MARCHE
    u8 CompteurFrameTir;        // Compteur pour passer ?? la prochaine FRAME TIR
    u8 IndexFrameTir;           // Index de FRAME TIR
    u8 CompteurFrameTouche;     // Compteur pour passer ?? la prochaine FRAME TIR
    u8 IndexFrameTouche;        // Index de FRAME TIR

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

extern u16 PosYinvincible;


//----------------------------------------------------//
//                      ENNEMIS                       //
//----------------------------------------------------//
typedef struct
{
    Sprite* SpriteE;
    u8 Etat;                    // 0 = VIVANT / 1 = MORT
    bool Axe;                   // 0 = BAS / 1 = HAUT
    u8 Init;                    // Sprite cr???? ou non
    u8 ID;                      // Type d'ennemi
    u8 Bonus;                   // Arme ?
    u16 Points;                 // Points obtenus lorsque ennemi tu??
    u8 PointsVie;               // Nb points de vie
    s16 PosX;                   // Position X
    s16 PosY;                   // Position Y
    s16 pt_Coll1_X;
    s16 pt_Coll1_Y;
    s16 pt_Coll2_X;
    s16 pt_Coll2_Y;
    u8 CompteurPosition;        // Compteur pour d??clencher le d??placement du sprite
    u8 CompteurFrame;           // Compteur pour passer ?? la prochaine FRAME
    u8 IndexFrame;              // Index de FRAME
    const s16 *ptrPosition;     // Pointeur dans le tableau de position
} SpriteEnnemi_;

extern SpriteEnnemi_ Ennemi[MAX_ENNEMIS];
extern const SpriteDefinition *AdrTilesEnnemi[7];
extern u8 indexCreaEnnemis;
extern u8 nb_Ennemis;



//----------------------------------------------------//
//                    PLATEFORMES                     //
//----------------------------------------------------//
typedef struct
{
    Sprite* SpriteP;
    u8 Init;                    // Sprite cr???? ou non
    u8 ID;                      // Type de plateforme
    u8 Mouvante;                // Plateforme qui se d??clenche ou non
    u8 Declencheur;             // D??clencheur d'animation
    s16 PosX;                   // Position X
    s16 PosY;                   // Position Y
    s16 pt_Coll1_X;
    s16 pt_Coll1_Y;
    s16 pt_Coll2_X;
    s16 pt_Coll2_Y;
    const s16 *ptrPosition;     // Pointeur dans le tableau de position
} SpritePlateforme_;

extern SpritePlateforme_ Plateforme[MAX_PLATEFORMES];
extern u8 IndexCreaPlateformes;
extern u8 nb_Plateformes;
extern bool contactPlt_OK;



//----------------------------------------------------//
//                       DRAGON                       //
//----------------------------------------------------//
typedef struct
{
    Sprite* SpriteD;
    u8 Phase;
    s16 PosX;                   // Position X
    s16 PosY;                   // Position Y
    u8 CompteurFrameVol;        // Compteur pour passer ?? la prochaine FRAME VOL
    u8 IndexFrameVol;           // Index de FRAME VOL
} SpriteDragon_;

extern SpriteDragon_ Dragon;



//----------------------------------------------------//
//                       SPLASH                       //
//----------------------------------------------------//
typedef struct
{
    Sprite* SpriteS;
    bool Init;
    s16 PosX;                   // Position X
    s16 PosY;                   // Position Y
    u8 CompteurFrameSplash;     // Compteur pour passer ?? la prochaine FRAME SPLASH
    u8 IndexFrameSplash;        // Index de FRAME SPLASH
} SpriteSplash_;

extern SpriteSplash_ Splash;


//----------------------------------------------------//
//                        AURA                        //
//----------------------------------------------------//
typedef struct
{
    Sprite* SpriteA;
    bool Init;
    s16 PosX;                   // Position X
    s16 PosY;                   // Position Y
    u8 CompteurFrameAura;       // Compteur pour passer ?? la prochaine FRAME AURA
    u8 IndexFrameAura;          // Index de FRAME AURA
} SpriteAura_;

extern SpriteAura_ Aura;


//----------------------------------------------------//
//                       FRUIT                        //
//----------------------------------------------------//
typedef struct
{
    Sprite* SpriteF;
    bool Init;
    s16 PosX;                   // Position X
    s16 PosY;                   // Position Y
    u8 CompteurFrameFruit;      // Compteur pour passer ?? la prochaine FRAME FRUIT
    u8 IndexFrameFruit;         // Index de FRAME FRUIT
} SpriteFruit_;


//----------------------------------------------------//
//                      TILEMAPS                      //
//----------------------------------------------------//
extern Map *tilemapCollision;

extern u16 tileID_BG;
extern u16 tileID_BD;
extern u16 posTileY;

extern u16 tileID_CG;
extern u16 tileID_CD;


extern u8 compteurTile; // 0 -> 7 //
extern u16 tilemapOffset;

#endif // _MAIN
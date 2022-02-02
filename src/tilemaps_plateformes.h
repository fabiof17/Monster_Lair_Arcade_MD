#ifndef _TILEMAPS_PLATEFORMES_H
#define _TILEMAPS_PLATEFORMES_H

// [0] : POS X (EN TILES)
// [1] : POS Y(EN TILES)
// [2] : ID
// [3] : DECLENCHEMENT

// TILEMAP CREATION PLATEFORMES NIVEAU 1 //
// 1 : VERTICAL VERS LE HAUT
// 2 : HORIZONTAL
// 3 : VERTICAL VERS LE BAS  (DECLENCHEMENT)
// 4 : VERTICAL VERS LE HAUT (DECLENCHEMENT)
// 5 : VERTICAL RAPIDE
// 6 : VERTICAL VERS LE BAS
// 7 : HORIZONTAL (DECLENCHEMENT)
const u16 tilemapCreaPlateformes_Niveau1[4][14] = { {58,122,248,282,318,358,370,379,389,401,438,446,466,486},
                                                    {20,20,17,16,18,18,24,24,24,22,16,22,22,22},
                                                    {1,1,2,3,4,3,5,5,5,4,6,7,7,7},
                                                    {0,0,0,1,1,1,0,0,0,1,0,1,1,1}
                                                  };


#endif // _MAIN
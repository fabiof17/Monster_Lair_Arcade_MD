#ifndef _ROUTINES_H
#define _ROUTINES_H

extern void Maj_CompteurEnergie();
extern void Maj_BarreEnergie();
extern void Init_BarreEnergie();

extern void Scrolling_Niveau1();
extern void Tiles_Niveau1();
extern void ChgtPalette_Niveau1();

extern void Collision_Decor();
extern void Collision_Ennemis();

extern void Phases_Joueur();
extern void MvtJoueur();
extern void TilesJoueur();

extern void CreaSprites_Niveau1();
extern void MvtEnnemis_Niveau1();
extern void MvtPlateformes_Niveau1();

extern void VDP_drawInt();

#endif // _MAIN
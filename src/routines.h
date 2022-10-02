#ifndef _ROUTINES_H
#define _ROUTINES_H

extern void Phases_Joueur();
extern void Scrolling_Niveau1();
extern void Crea_Sprites_Niveau1();

extern void Mvt_Ennemis_Niveau1();
extern void MvtPlateformes_Niveau1();
extern void Mvt_Joueur();

extern void TirJoueur();
extern void CreaTirBase();

extern void Mvt_TirJoueur();

extern void TilesJoueur();
extern void Tiles_Niveau1();

extern void Maj_CompteurEnergie();
extern void Effacer_BarreEnergie();
extern void Maj_BarreEnergie();
extern void Init_BarreEnergie();

extern void Maj_Continue();
extern void Maj_Vies();
extern void Maj_Continue();
extern void Clear_Niveau1();
extern void Afficher_GameOver();

extern void Titre_Callback(u16 joy, u16 changed, u16 state);
extern void Selection_Callback(u16 joy, u16 changed, u16 state);
extern void Game_PF_Callback(u16 joy, u16 changed, u16 state);

extern void ChgtPalette_Niveau1();

extern void VDP_drawInt(u16 valeur,u8 zeros,u8 x, u8 y);

#endif // _MAIN
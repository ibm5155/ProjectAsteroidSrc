#include <stdlib.h>
#include <MT2D/ObjectCore/Object.h>
//#include <MT2D/ObjectCore/Cscript.h>
#include <MT2D/ObjectCore/STDFunctions.h>
//#include <MT2D/ObjectCore/Vars.h>
//#include <MT2D/ObjectCore/State.h>
//#include <MT2D/ObjectCore/Sprites.h>

/*
main
move
moveU1
moveU2
moveD1
moveD2
Fire

*/

ObjectState **Projectile1States;
Sprite *Projectile1Sprites;

extern MT2D_VAR *Pointer_Health;
MT2D_VAR *Pointer_PosX = MT2D_Object_Create_Var_Pointer("Pos_X");
extern MT2D_VAR *State_Main;
extern MT2D_VAR *State_Dead;
MT2D_VAR *State_Explode = MT2D_Object_Create_Var_Char("explode", 0);


MT2D_VAR *Const320 = MT2D_Object_Create_Var_Int("320", 320);
extern MT2D_VAR *Const5;
extern MT2D_VAR *Const0;

Object *Create_Projectile01_Object(int X, int Y) {
	Projectile1States = (ObjectState**)malloc(2 * sizeof(ObjectState*));
	Projectile1States[0] = MT2D_OBJECT_CREATE_STATE("main");
	Projectile1States[1] = MT2D_OBJECT_CREATE_STATE("explode");
	Projectile1Sprites = (Sprite*)malloc(2 * sizeof(Sprite));
	Projectile1Sprites[0] = *Load_Sprite_Image("Projectiles/Proj01.png", 16, 14);
	//MAIN
	MT2D_OBJECT_ADD_STATE(Projectile1States[0], &Projectile1Sprites[0], 1, Cscript_New2( &Cscript_Move) );

	MT2D_OBJECT_ADD_STATE(Projectile1States[0], &Projectile1Sprites[0], 0,
		Cscript_New3(MT2D_VAR_Create_Matrix3(State_Explode, Pointer_PosX, Const320), &Cscript_JumpToStateIfVarHigherEq));
	MT2D_OBJECT_ADD_STATE(Projectile1States[0], &Projectile1Sprites[0], 0,
		Cscript_New3(MT2D_VAR_Create_Matrix3(State_Explode, Const5, Pointer_Health), &Object_GotoState_IfHit));

	// to be continued
	//EXPLODE
	MT2D_OBJECT_ADD_STATE(Projectile1States[1], &Projectile1Sprites[0], 1,
		Cscript_New2(&Cscript_RemoveObject));

	Object *Projectile = Object_Create(false, false, 16, 8, X, Y, Projectile1States, 2);
	Projectile->Aceleration.X = 8;
	return Projectile;
}
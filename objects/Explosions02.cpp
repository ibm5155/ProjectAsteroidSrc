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

ObjectState **Explosion2States;
Sprite *Explosion2Sprites;

extern MT2D_VAR *State_Dead;
extern MT2D_VAR *Pointer_Timeout;
extern MT2D_VAR *Const0;
extern MT2D_VAR *Const1;


void ReplicateExplosion02(Object *Caller) {
	MT2D_VAR *Timeout = MT2D_Object_Create_Var_Int("Timeout", 0);
	Object *O = Object_Create(false, false, Caller->Size.X, Caller->Size.Y, Caller->SpacePosition.X, Caller->SpacePosition.Y, Explosion2States, 1);
	O->User_Vars_Count = 1;
	O->User_Vars = Timeout;
	ObjectScene_Add(Caller->MyScene,O);

}

void Explosion02_Init() {
	int i;
	char Spath[] = "Explosion/02/FrameXX.png";
	Explosion2States = (ObjectState**)malloc(1 * sizeof(ObjectState*));
	Explosion2States[0] = MT2D_OBJECT_CREATE_STATE("main");
	Explosion2Sprites = (Sprite*)malloc(13 * sizeof(Sprite));
	for (i = 0; i < 13; i++) {
		Spath[18] = '0' + (i+1) / 10;
		Spath[19] = '0' + (i+1) % 10;
		Explosion2Sprites[i] = *Load_Sprite_Image(Spath, 21, 21);
	}

	//MAIN
	for (i = 0; i < 13; i++) {
		MT2D_OBJECT_ADD_STATE(Explosion2States[0], &Explosion2Sprites[i], 0,
			Cscript_New3(MT2D_VAR_Create_Matrix2(Pointer_Timeout, Const0), Cscript_JumpNextFrameIfVarHigherEq));
		MT2D_OBJECT_ADD_STATE(Explosion2States[0], &Explosion2Sprites[i], 1, Cscript_Empty());

		MT2D_OBJECT_ADD_STATE(Explosion2States[0], &Explosion2Sprites[i], 0, 
			Cscript_New3(MT2D_VAR_Create_Matrix2(Pointer_Timeout, Const1),Cscript_JumpNextFrameIfVarEq));
		MT2D_OBJECT_ADD_STATE(Explosion2States[0], &Explosion2Sprites[i], 1, Cscript_New2(Cscript_Move));

		MT2D_OBJECT_ADD_STATE(Explosion2States[0], &Explosion2Sprites[i], 0,
			Cscript_New3(MT2D_VAR_Create_Matrix2(Pointer_Timeout, Const0), Cscript_JumpNextFrameIfVarEq));
		MT2D_OBJECT_ADD_STATE(Explosion2States[0], &Explosion2Sprites[i], 0, Cscript_New2(ReplicateExplosion02));

		MT2D_OBJECT_ADD_STATE(Explosion2States[0], &Explosion2Sprites[i], 0,
			Cscript_New3(MT2D_VAR_Create_Matrix2(Pointer_Timeout, Const0), Cscript_JumpNextFrameIfVarEq));
		MT2D_OBJECT_ADD_STATE(Explosion2States[0], &Explosion2Sprites[i], 0,
			Cscript_New3(MT2D_VAR_Create_Matrix1(Pointer_Timeout), Cscript_VAR_DEC));
	}
	MT2D_OBJECT_ADD_STATE(Explosion2States[0], &Explosion2Sprites[0], 0,
		Cscript_New2(&Cscript_RemoveObject));
	MT2D_ObjectState_ADD(Explosion2States[0], &Explosion2Sprites[12], 1, Cscript_Empty());
}

Object *Create_Explosion02_Object(int pX, int pY) {
	MT2D_VAR *Timeout = MT2D_Object_Create_Var_Int("Timeout", 13);

	Object *Enemy = Object_Create(false, false, 1, 1, pX, pY, Explosion2States, 2);
	Enemy->Aceleration.X = 3 - rand() % 6;
	Enemy->Aceleration.Y = 3 - rand() % 6;
	Enemy->User_Vars_Count = 1;
	Enemy->User_Vars = Timeout;
	return Enemy;
}
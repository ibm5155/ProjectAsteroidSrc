#include <stdlib.h>
#include <MT2D/ObjectCore/Object.h>
#include "objects\enemy\Enemy1.h"
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

ObjectState **Enemy3States=0;
Sprite *Enemy3Sprites;

extern MT2D_VAR *Pointer_PosX;
extern MT2D_VAR *Pointer_Health;
extern MT2D_VAR *State_Dead;
extern MT2D_VAR *ConstMinus40;
extern MT2D_VAR *ConstMinus10;
extern MT2D_VAR *Const0;
MT2D_VAR *ConstMinus1 = MT2D_Object_Create_Var_Int("-1",-1);
extern MT2D_VAR *Const10;

extern void SpawnExplosions(Object *Caller);

extern void IncreaseScore(Object *caller, MT2D_VAR**ToIncrease);


Object *Create_Enemy03_Object(int pX, int pY, int sX, int sY) {
	int i;
	char Spath[] = "Enemies/03/Frame0X.png";
	if (Enemy3States == 0) {
		Enemy3States = (ObjectState**)malloc(2 * sizeof(ObjectState*));
		Enemy3States[0] = MT2D_OBJECT_CREATE_STATE("main");
		Enemy3States[1] = MT2D_OBJECT_CREATE_STATE("Dead");
		Enemy3Sprites = (Sprite*)malloc(6 * sizeof(Sprite));
		for (i = 0; i < 6; i++) {
			Spath[17] = '1' + i;
			Enemy3Sprites[i] = *Load_Sprite_Image(Spath, 18, 12);
		}

		//MAIN
		for (i = 0; i < 6; i++) {
			MT2D_OBJECT_ADD_STATE(Enemy3States[0], &Enemy3Sprites[i], 2, Cscript_New2(&Cscript_Move));
			MT2D_OBJECT_ADD_STATE(Enemy3States[0], &Enemy3Sprites[i], 0,
				Cscript_New3(MT2D_VAR_Create_Matrix3(State_Dead, Pointer_Health, Const0), &Cscript_JumpToStateIfVarLowerEq));
			MT2D_OBJECT_ADD_STATE(Enemy3States[0], &Enemy3Sprites[i], 0,
				Cscript_New3(MT2D_VAR_Create_Matrix3(State_Dead, Pointer_PosX, ConstMinus40), &Cscript_JumpToStateIfVarLowerEq));
		}
		// to be continued
		//DEAD
		MT2D_OBJECT_ADD_STATE(Enemy3States[1], &Enemy3Sprites[0], 0,
			Cscript_New3(MT2D_VAR_Create_Matrix2(Pointer_PosX, ConstMinus40), &Cscript_JumpNextFrameIfVarLowerEq));
		MT2D_OBJECT_ADD_STATE(Enemy3States[1], &Enemy3Sprites[0], 0,
			Cscript_New3(MT2D_VAR_Create_Matrix1(Const0), &IncreaseScore));
		MT2D_OBJECT_ADD_STATE(Enemy3States[1], &Enemy3Sprites[0], 0,
			Cscript_New3(MT2D_VAR_Create_Matrix2(Pointer_PosX, Const0), &Cscript_JumpNextFrameIfVarHigherEq));
		MT2D_OBJECT_ADD_STATE(Enemy3States[1], &Enemy3Sprites[0], 0,
			Cscript_New3(MT2D_VAR_Create_Matrix1(ConstMinus1), &IncreaseScore));
		MT2D_OBJECT_ADD_STATE(Enemy3States[1], &Enemy3Sprites[0], 0,
			Cscript_New3(MT2D_VAR_Create_Matrix2(Pointer_PosX, Const0), &Cscript_JumpNextFrameIfVarHigherEq));
		MT2D_OBJECT_ADD_STATE(Enemy3States[1], &Enemy3Sprites[0], 1,
			Cscript_New2(&Cscript_RemoveObject));


		MT2D_OBJECT_ADD_STATE(Enemy3States[1], &Enemy3Sprites[0], 1,
			Cscript_New2(&SpawnSmallExplosion));
		MT2D_OBJECT_ADD_STATE(Enemy3States[1], &Enemy3Sprites[0], 1,
			Cscript_New2(&Cscript_RemoveObject));

	}
	MT2D_VAR *UserVars = (MT2D_VAR*)malloc(sizeof(MT2D_VAR));
	UserVars[0] = *MT2D_Object_Create_Var_Int("Health", 5);

	Object *Enemy = Object_Create(true, false, 32, 32, pX, pY, Enemy3States, 2);
	Enemy->Aceleration.X = sX;
	Enemy->Aceleration.Y = sY;
	Enemy->User_Vars_Count = 1;
	Enemy->User_Vars = UserVars;
	return Enemy;
}
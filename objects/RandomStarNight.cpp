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

ObjectState **RandomStarsStates;
Sprite *Rstars1Sprites;

extern MT2D_VAR *Pointer_PosX;
MT2D_VAR *State_main1 = MT2D_Object_Create_Var_Char("main1", 0);
MT2D_VAR *State_main2 = MT2D_Object_Create_Var_Char("main2", 0);
MT2D_VAR *State_main3 = MT2D_Object_Create_Var_Char("main3", 0);
MT2D_VAR *State_main4 = MT2D_Object_Create_Var_Char("main4", 0);


extern MT2D_VAR *ConstMinus40;
extern MT2D_VAR *Const0;
extern MT2D_VAR *ConstMinus40;

void ResetRandomStars(Object *Caller) {
	if (Caller->SpacePosition.X < 0) {
		Caller->SpacePosition.X = 310 + rand() % 20;
	}
}
void RandomStarts_Init() {
	int i;
	char Spath[] = "Sky/Stars/st0X.png";
	RandomStarsStates = (ObjectState**)malloc(5 * sizeof(ObjectState*));
	RandomStarsStates[0] = MT2D_OBJECT_CREATE_STATE("main1");
	RandomStarsStates[1] = MT2D_OBJECT_CREATE_STATE("main2");
	RandomStarsStates[2] = MT2D_OBJECT_CREATE_STATE("main3");
	RandomStarsStates[3] = MT2D_OBJECT_CREATE_STATE("main4");
	Rstars1Sprites = (Sprite*)malloc(4 * sizeof(Sprite));
	for (i = 0; i < 3; i++) {
		Spath[13] = '2' + i;
		Rstars1Sprites[i] = *Load_Sprite_Image(Spath, 1, 1);
	}
	Spath[13] = '1';
	Rstars1Sprites[3] = *Load_Sprite_Image(Spath, 4, 4);

	//MAINs
		MT2D_OBJECT_ADD_STATE(RandomStarsStates[0], &Rstars1Sprites[0], 1, Cscript_New2(&Cscript_Move));
		MT2D_OBJECT_ADD_STATE(RandomStarsStates[0], &Rstars1Sprites[0], 0,
			Cscript_New2(&ResetRandomStars));

		MT2D_OBJECT_ADD_STATE(RandomStarsStates[1], &Rstars1Sprites[1], 3, Cscript_New2(&Cscript_Move));
		MT2D_OBJECT_ADD_STATE(RandomStarsStates[1], &Rstars1Sprites[1], 0,
			Cscript_New2(&ResetRandomStars));
	
		MT2D_OBJECT_ADD_STATE(RandomStarsStates[2], &Rstars1Sprites[2], 2, Cscript_New2(&Cscript_Move));
		MT2D_OBJECT_ADD_STATE(RandomStarsStates[2], &Rstars1Sprites[2], 0,
			Cscript_New2(&ResetRandomStars));
	
		MT2D_OBJECT_ADD_STATE(RandomStarsStates[3], &Rstars1Sprites[3], 2, Cscript_New2(&Cscript_Move));
		MT2D_OBJECT_ADD_STATE(RandomStarsStates[3], &Rstars1Sprites[3], 0,
			Cscript_New2(&ResetRandomStars));


}


Object *Create_RandomStar_Object(int pX, int pY) {
	Object *Enemy = Object_Create(false, false, 1, 1, pX, pY, &RandomStarsStates[rand()%4], 1);
	Enemy->Aceleration.X = -1;
	return Enemy;
}
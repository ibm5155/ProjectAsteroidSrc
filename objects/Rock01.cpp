#include <stdlib.h>
#include <MT2D/ObjectCore/Object.h>
//#include <MT2D/ObjectCore/Cscript.h>
#include <MT2D/ObjectCore/STDFunctions.h>
#include <MT2D/Audio/MT2D_Audio_core.h>

#include "objects/Explosions01.h"
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

ObjectState **Rock1States;
Sprite *Rock1Sprites;

void Rock01_Init() {
	char Spath[] = "Rock/01/Frame1.png";
	Rock1States = (ObjectState**)malloc(1 * sizeof(ObjectState*));
	Rock1States[0] = MT2D_OBJECT_CREATE_STATE("main");
	Rock1Sprites = (Sprite*)malloc(1 * sizeof(Sprite));
	Rock1Sprites[0] = *Load_Sprite_Image(Spath, 50, 62);
	//MAIN
	MT2D_OBJECT_ADD_STATE(Rock1States[0], &Rock1Sprites[0], 4, Cscript_New2(&Cscript_Move));

}

Object *Create_Rock01_Object(int sX, int sY) {

	MT2D_VAR *UserVars = (MT2D_VAR*)malloc(sizeof(MT2D_VAR));
	UserVars[0] = *MT2D_Object_Create_Var_Int("Health", 1000);

	Object *Enemy = Object_Create(true, false, 50, 62, sX, sY, Rock1States, 2);
	Enemy->Aceleration.X = -1;
	Enemy->User_Vars_Count = 1;
	Enemy->User_Vars = UserVars;
	return Enemy;
}
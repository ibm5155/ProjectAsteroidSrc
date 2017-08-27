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

ObjectState **Explosion1States;
Sprite *Explosion1Sprites;

extern MT2D_VAR *State_Dead;

void Explosion01_Init() {
	int i;
	char Spath[] = "Explosion/01/FrameXX.png";
	Explosion1States = (ObjectState**)malloc(1 * sizeof(ObjectState*));
	Explosion1States[0] = MT2D_OBJECT_CREATE_STATE("main");
	Explosion1Sprites = (Sprite*)malloc(13 * sizeof(Sprite));
	for (i = 0; i < 13; i++) {
		Spath[18] = '0' + i / 10;
		Spath[19] = '0' + i % 10;
		Explosion1Sprites[i] = *Load_Sprite_Image(Spath, 33, 32);
	}

	//MAIN
	for (i = 0; i < 13; i++) {
		MT2D_OBJECT_ADD_STATE(Explosion1States[0], &Explosion1Sprites[i], 1, Cscript_Empty());
	}
	MT2D_OBJECT_ADD_STATE(Explosion1States[0], &Explosion1Sprites[0], 0,
		Cscript_New2(&Cscript_RemoveObject));
}

Object *Create_Explosion01_Object(int pX, int pY) {
	Object *Enemy = Object_Create(false, false, 1, 1, pX, pY, Explosion1States, 2);
	return Enemy;
}
#include <stdlib.h>
#include <MT2D/ObjectCore/Object.h>
//#include <MT2D/ObjectCore/Cscript.h>
#include <MT2D/ObjectCore/STDFunctions.h>
#include <MT2D/Audio/MT2D_Audio_core.h>
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

ObjectState **PlayerStates;
Sprite *PlayerSprites;
extern MT2D_VAR *Pointer_PosX;
MT2D_VAR *Pointer_PosY = MT2D_Object_Create_Var_Pointer("Pos_Y");
MT2D_VAR *Pointer_AcelY = MT2D_Object_Create_Var_Pointer("Acel_Y");
MT2D_VAR *Pointer_AcelX = MT2D_Object_Create_Var_Pointer("Acel_X");
MT2D_VAR *Pointer_Timeout = MT2D_Object_Create_Var_Pointer("Timeout");
MT2D_VAR *Pointer_RequestFire = MT2D_Object_Create_Var_Pointer("RequestFire");

MT2D_VAR *State_Main = MT2D_Object_Create_Var_Char("main", 0);
MT2D_VAR *State_Move = MT2D_Object_Create_Var_Char("move", 0);
MT2D_VAR *State_MoveU1 = MT2D_Object_Create_Var_Char("moveU1", 0);
MT2D_VAR *State_MoveU2 = MT2D_Object_Create_Var_Char("moveU2", 0);
MT2D_VAR *State_MoveD1 = MT2D_Object_Create_Var_Char("moveD1", 0);
MT2D_VAR *State_MoveD2 = MT2D_Object_Create_Var_Char("moveD2", 0);


MT2D_VAR *Const5 = MT2D_Object_Create_Var_Int("5", 5);
MT2D_VAR *Const10 = MT2D_Object_Create_Var_Int("10", 10);
MT2D_VAR *Const0 = MT2D_Object_Create_Var_Int("0", 0);
MT2D_VAR *ConstMinus5 = MT2D_Object_Create_Var_Int("-5", -5);
MT2D_VAR *ConstMinus10 = MT2D_Object_Create_Var_Int("-10", -10);


extern Object *Projectile1;

void TryFire(Object *Caller) {
	MT2D_VAR **Tmp;
	if (*(int*)Caller->User_Vars[0].Data > 0) {
		*(int*)Caller->User_Vars[0].Data = *(int*)Caller->User_Vars[0].Data - 1;
	}
	if (*(int*)Caller->User_Vars[1].Data == 1) {
		if (*(int*)Caller->User_Vars[0].Data == 0) {
			MT2D_VAR *NewPosX = MT2D_Object_Create_Var_Int("NewX", Caller->SpacePosition.X + Caller->Size.X + 3);
			Tmp = MT2D_VAR_Create_Matrix4(NewPosX, Pointer_PosY, Const10, Const0);
			Cscript_CreateObject(Caller, Projectile1, Tmp);
			MT2D_Play_Audio("Projectiles/Proj.ogg");
			free(Tmp);
			*(int*)Caller->User_Vars[0].Data = 5;
		}
	}
}



Object *Create_Player_Object(int X, int Y) {
	char SpritesPATH[] = "Player/Ship0X.png";
	PlayerStates = (ObjectState**)malloc(7 * sizeof(ObjectState*));
	PlayerStates[0] = MT2D_OBJECT_CREATE_STATE("main");
	PlayerStates[1] = MT2D_OBJECT_CREATE_STATE("move");
	PlayerStates[2] = MT2D_OBJECT_CREATE_STATE("moveU1");
	PlayerStates[3] = MT2D_OBJECT_CREATE_STATE("moveU2");
	PlayerStates[4] = MT2D_OBJECT_CREATE_STATE("moveD1");
	PlayerStates[5] = MT2D_OBJECT_CREATE_STATE("moveD2");
	PlayerStates[6] = MT2D_OBJECT_CREATE_STATE("Fire");
	PlayerSprites = (Sprite*)malloc(5 * sizeof(Sprite));
	for (int i = 0; i < 5; i++) {
		SpritesPATH[12] = '0' + i + 1;
		PlayerSprites[i] = *Load_Sprite_Image(SpritesPATH, 32, 24);
	}
	//MAIN
	MT2D_OBJECT_ADD_STATE(PlayerStates[0], &PlayerSprites[0], 0, 
		Cscript_New3(MT2D_VAR_Create_Matrix3(State_Move, Pointer_AcelY,Const0),&Cscript_JumpToStateIfVarEq));
	MT2D_OBJECT_ADD_STATE(PlayerStates[0], &PlayerSprites[0], 0,
		Cscript_New3(MT2D_VAR_Create_Matrix3(State_MoveU2, Pointer_AcelY, Const5), &Cscript_JumpToStateIfVarHigherEq));
	MT2D_OBJECT_ADD_STATE(PlayerStates[0], &PlayerSprites[0], 0,
		Cscript_New3(MT2D_VAR_Create_Matrix3(State_MoveU1, Pointer_AcelY, Const0), &Cscript_JumpToStateIfVarHigherEq));
	MT2D_OBJECT_ADD_STATE(PlayerStates[0], &PlayerSprites[0], 0,
		Cscript_New3(MT2D_VAR_Create_Matrix3(State_MoveD2, Pointer_AcelY, ConstMinus5), &Cscript_JumpToStateIfVarLowerEq));
	MT2D_OBJECT_ADD_STATE(PlayerStates[0], &PlayerSprites[0], 0,
		Cscript_New3(MT2D_VAR_Create_Matrix3(State_MoveD1, Pointer_AcelY, Const0), &Cscript_JumpToStateIfVarLowerEq));
	// to be continued
	//MOVE 
	MT2D_OBJECT_ADD_STATE(PlayerStates[1], &PlayerSprites[0], 1,
		Cscript_New2(&Cscript_Move));
	MT2D_OBJECT_ADD_STATE(PlayerStates[1], &PlayerSprites[0], 0,
		Cscript_New2(&TryFire));
	MT2D_OBJECT_ADD_STATE(PlayerStates[1], &PlayerSprites[0], 0,
		Cscript_New3(MT2D_VAR_Create_Matrix1(State_Main), &Cscript_Object_SetState));
	//MOVE D1
	MT2D_OBJECT_ADD_STATE(PlayerStates[2], &PlayerSprites[1], 1,
		Cscript_New2(&Cscript_Move));
	MT2D_OBJECT_ADD_STATE(PlayerStates[2], &PlayerSprites[1], 0,
		Cscript_New2(&TryFire));
	MT2D_OBJECT_ADD_STATE(PlayerStates[2], &PlayerSprites[1], 0,
		Cscript_New3(MT2D_VAR_Create_Matrix1(State_Main), &Cscript_Object_SetState));
	//MOVE D2
	MT2D_OBJECT_ADD_STATE(PlayerStates[3], &PlayerSprites[2], 1,
		Cscript_New2(&Cscript_Move));
	MT2D_OBJECT_ADD_STATE(PlayerStates[3], &PlayerSprites[2], 0,
		Cscript_New2(&TryFire));
	MT2D_OBJECT_ADD_STATE(PlayerStates[3], &PlayerSprites[2], 0,
		Cscript_New3(MT2D_VAR_Create_Matrix1(State_Main), &Cscript_Object_SetState));
	//MOVE U1
	MT2D_OBJECT_ADD_STATE(PlayerStates[4], &PlayerSprites[3], 1,
		Cscript_New2(&Cscript_Move));
	MT2D_OBJECT_ADD_STATE(PlayerStates[4], &PlayerSprites[3], 0,
		Cscript_New2(&TryFire));
	MT2D_OBJECT_ADD_STATE(PlayerStates[4], &PlayerSprites[3], 0,
		Cscript_New3(MT2D_VAR_Create_Matrix1(State_Main), &Cscript_Object_SetState));
	//MOVE U2
	MT2D_OBJECT_ADD_STATE(PlayerStates[5], &PlayerSprites[4], 1,
		Cscript_New2(&Cscript_Move));
	MT2D_OBJECT_ADD_STATE(PlayerStates[5], &PlayerSprites[4], 0,
		Cscript_New2(&TryFire));
	MT2D_OBJECT_ADD_STATE(PlayerStates[5], &PlayerSprites[4], 0,
		Cscript_New3(MT2D_VAR_Create_Matrix1(State_Main), &Cscript_Object_SetState));
	//FIRE
	MT2D_OBJECT_ADD_STATE(PlayerStates[6], &PlayerSprites[0], 0,
		Cscript_New3(MT2D_VAR_Create_Matrix1(State_Main), &Cscript_Object_SetState));

	MT2D_VAR *Myvars = (MT2D_VAR*)malloc(2*sizeof(MT2D_VAR));
	Myvars[0] = *MT2D_Object_Create_Var_Int("Timeout", 5);
	Myvars[1] = *MT2D_Object_Create_Var_Int("RequestFire", 0);

	Object *Player = Object_Create(false, false, 32, 24, X, Y, PlayerStates, 7);
	Player->User_Vars = Myvars;
	Player->User_Vars_Count = 2;
	return Player;
}

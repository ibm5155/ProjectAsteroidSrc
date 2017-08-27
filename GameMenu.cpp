#include <MT2D/Audio/MT2D_Audio_core.h>
#include <MT2D/ObjectCore/Sprites.h>
#include <MT2D/ObjectCore/State.h>
#include <MT2D/ObjectCore/Object.h>
#include <MT2D/ObjectCore/STDFunctions.h>
#include <MT2D/MT2D.h>
#include <MT2D/MT2D_Display.h>
#include <MT2D/MT2D_System_Calls.h>
#include <MT2D/MT2D_Keyboard.h>
#include <cstdlib>

int Selected = 0;
bool Enter_pressed = false;

Sprite **TitleImage;
Sprite **NewGImage;
Sprite **OptionsImage;
Sprite **ExitImage;
Sprite **_Selected;


ObjectState **NewGameStates;
ObjectState **OptionsStates;
ObjectState **ExitStates;
ObjectState **LoadTitleStates;
ObjectState **SelecteditleStates;

MT2D_VAR *LoopState = MT2D_Object_Create_Var_Char("Loop", 0);
MT2D_VAR *Const60 = MT2D_Object_Create_Var_Int("60", 60);
MT2D_VAR *Const80 = MT2D_Object_Create_Var_Int("80", 80);

void TryMove(Object *Caller) {
	int Key = 0;
	if (MT2D_Keyboard_touched()) {
		Key = MT2D_Keyboard_keytouched();
		if (Key == arrow_key_pressed) {
			Key = MT2D_Keyboard_keytouched();
			if (Key == arrow_up_pressed) {
				Selected = (Selected == 0 ? 2 : Selected - 1);
				Caller->SpacePosition.Y = 90 + 30 * Selected;
			}
			else if (Key == arrow_down_pressed) {
				Selected = (Selected == 2 ? 0 : Selected + 1);
				Caller->SpacePosition.Y = 90 + 30 * Selected;
			}
		}
		else if (Key == enter_pressed || Key == ' ') {
			Enter_pressed = true;
		}
	}
}

Object *SelectedButton(int x, int y) {

	_Selected = (Sprite**)malloc(2 * sizeof(Sprite*));
	_Selected[0] = Load_Sprite_Image("Title01.png", 16, 16);
	_Selected[1] = Load_Sprite_Image("Selected.png", 16, 16);
	SelecteditleStates = (ObjectState**)malloc(2 * sizeof(ObjectState*));
	SelecteditleStates[0] = MT2D_OBJECT_CREATE_STATE("Spawn");
	SelecteditleStates[1] = MT2D_OBJECT_CREATE_STATE("Loop");
	//Spawn
	MT2D_ObjectState_ADD(SelecteditleStates[0], _Selected[0], 150, Cscript_New3(
		MT2D_VAR_Create_Matrix1(LoopState), &Cscript_Object_SetState));
	//Loop
	MT2D_ObjectState_ADD(SelecteditleStates[1], _Selected[1], 5, Cscript_New2(&TryMove));
	Object *New = Object_Create(false, false, 1, 1, x, y, SelecteditleStates, 2);
	return New;

}

Object *ExitButton(int x, int y) {
	int i = 0;
	char SpriteName[] = "ExitX.png";
	ExitImage = (Sprite**)malloc(4 * sizeof(Sprite*));
	for (; i < 4; i++) {
		SpriteName[4] = '0' + (i + 1) % 10;
		ExitImage[i] = Load_Sprite_Image(SpriteName, 64, 25);
	}
	ExitStates = (ObjectState**)malloc(2 * sizeof(ObjectState*));
	ExitStates[0] = MT2D_OBJECT_CREATE_STATE("Spawn");
	ExitStates[1] = MT2D_OBJECT_CREATE_STATE("Loop");

	//Spawn
	MT2D_ObjectState_ADD(ExitStates[0], ExitImage[0], 150, Cscript_New3(
		MT2D_VAR_Create_Matrix1(LoopState), &Cscript_Object_SetState));
	//Loop
	for (i = 0; i < 3; i++) {
		MT2D_ObjectState_ADD(ExitStates[1], ExitImage[i+1], 30, Cscript_Empty());
	}
	Object *New = Object_Create(false, false, 1, 1, x, y, ExitStates, 2);
	return New;
}

Object *OptionsButton(int x, int y) {
	int i = 0;
	char SpriteName[] = "OptionsX.png";
	OptionsImage = (Sprite**)malloc(4 * sizeof(Sprite*));
	for (; i < 4; i++) {
		SpriteName[7] = '0' + (i + 1) % 10;
		OptionsImage[i] = Load_Sprite_Image(SpriteName, 64, 25);
	}
	OptionsStates = (ObjectState**)malloc(2 * sizeof(ObjectState*));
	OptionsStates[0] = MT2D_OBJECT_CREATE_STATE("Spawn");
	OptionsStates[1] = MT2D_OBJECT_CREATE_STATE("Loop");

	//Spawn
	MT2D_ObjectState_ADD(OptionsStates[0], OptionsImage[0], 150, Cscript_New3(
		MT2D_VAR_Create_Matrix1(LoopState), &Cscript_Object_SetState));
	//Loop
	for (i = 0; i < 3; i++) {
		MT2D_ObjectState_ADD(OptionsStates[1], OptionsImage[i + 1], 30, Cscript_Empty());
	}
	Object *New = Object_Create(false, false, 1, 1, x, y, OptionsStates, 2);
	return New;
}


Object *LoadNewGameButton(int x, int y) {
	int i = 0;
	char SpriteName[] = "NgameX.png";
	NewGImage = (Sprite**)malloc(4 * sizeof(Sprite*));
	for (; i < 4; i++) {
		SpriteName[5] = '0' + (i + 1) % 10;
		NewGImage[i] = Load_Sprite_Image(SpriteName, 64, 25);
	}
	NewGameStates = (ObjectState**)malloc(2 * sizeof(ObjectState*));
	NewGameStates[0] = MT2D_OBJECT_CREATE_STATE("Spawn");
	NewGameStates[1] = MT2D_OBJECT_CREATE_STATE("Loop");

	//Spawn
	MT2D_ObjectState_ADD(NewGameStates[0], NewGImage[0], 150, Cscript_New3(
		MT2D_VAR_Create_Matrix1(LoopState), &Cscript_Object_SetState));
	//Loop
	for (i = 0; i < 3; i++) {
		MT2D_ObjectState_ADD(NewGameStates[1], NewGImage[i + 1], 30, Cscript_Empty());
	}
	Object *New = Object_Create(false, false, 1, 1, x, y, NewGameStates, 2);
	return New;
}

Object * LoadTitle() {
	int i = 0;
	char SpriteName[] = "TitleXX.png";
	TitleImage = (Sprite**)malloc(15 * sizeof(Sprite*));
	for (; i < 15; i++) {
		SpriteName[5] = '0' + (i+1) / 10;
		SpriteName[6] = '0' + (i + 1)% 10;
		TitleImage[i] = Load_Sprite_Image(SpriteName, 200, 64);
	}
	LoadTitleStates = (ObjectState**)malloc(2 * sizeof(ObjectState*));
	LoadTitleStates[0] = MT2D_OBJECT_CREATE_STATE("Spawn");
	LoadTitleStates[1] = MT2D_OBJECT_CREATE_STATE("Loop");
	
	MT2D_ObjectState_ADD(LoadTitleStates[0], TitleImage[0], 90, Cscript_Empty());
	//spawn state
	for (i = 1; i < 10; i++) {
		MT2D_ObjectState_ADD(LoadTitleStates[0], TitleImage[i], 3, Cscript_Empty());
	}
	MT2D_ObjectState_ADD(LoadTitleStates[0], TitleImage[i], 3, Cscript_New3(
		MT2D_VAR_Create_Matrix1(LoopState),&Cscript_Object_SetState));
	//loop state
	MT2D_ObjectState_ADD(LoadTitleStates[1], TitleImage[11], 500, Cscript_New3(
		MT2D_VAR_Create_Matrix3(LoopState, Const60, Const80),&Cscript_JumpToStateIfRandom));
	//spawn state
	for (i = 12; i < 15; i++) {
		MT2D_ObjectState_ADD(LoadTitleStates[1], TitleImage[i], 6, Cscript_Empty());
	}

	Object *Title = Object_Create(false, false, 1, 1, 50, 0, LoadTitleStates, 2);
	return Title;
}

int GameMenu() {
	Sprite *MenuBackground = Load_Sprite_Image("menu.png", 320, 240);
	Object *Title = LoadTitle();
	Object *SelectedOption = SelectedButton(105, 90);
	Object *NewGame = LoadNewGameButton(120, 90);
	Object *Options = OptionsButton(120, 120);
	Object *Exit = ExitButton(120, 150);


	ObjectScene *Scene = ObjectScene_CreateEmpty();
	ObjectScene_Add(Scene, Title);
	ObjectScene_Add(Scene, NewGame);
	ObjectScene_Add(Scene, Options);
	ObjectScene_Add(Scene, Exit);
	ObjectScene_Add(Scene, SelectedOption);
	MT2D_Play_Music("Menu.ogg");
	while (Enter_pressed == false) {
		MT2D_Clear_Main_Window();
		Sprite_Render_on_Window(MenuBackground, DISPLAY_WINDOW1, 0, 0);
		ObjectScene_Goto_NextSteps(Scene);
		ObjectScene_Render(Scene);
		MT2D_Draw_Window(DISPLAY_WINDOW1);
		MT2D_System_Delay(10);
	}
	//MT2D_Clear_Main_Window();
	MT2D_ObjectState_Delete(NewGameStates[0]);
	MT2D_ObjectState_Delete(NewGameStates[1]);
	free(NewGameStates);

	MT2D_ObjectState_Delete(OptionsStates[0]);
	MT2D_ObjectState_Delete(OptionsStates[1]);
	free(OptionsStates);

	MT2D_ObjectState_Delete(ExitStates[0]);
	MT2D_ObjectState_Delete(ExitStates[1]);
	free(ExitStates);

	MT2D_ObjectState_Delete(LoadTitleStates[0]);
	MT2D_ObjectState_Delete(LoadTitleStates[1]);
	free(LoadTitleStates);

	MT2D_ObjectState_Delete(SelecteditleStates[0]);
	MT2D_ObjectState_Delete(SelecteditleStates[1]);
	free(SelecteditleStates);

	Object_Delete(Title);
	Object_Delete(SelectedOption);
	Object_Delete(NewGame);
	Object_Delete(Options);
	Object_Delete(Exit);
	Sprite_Delete(MenuBackground);

	return Selected + 1;
}
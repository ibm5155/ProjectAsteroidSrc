#include <MT2D/Audio/MT2D_Audio_core.h>
#include <MT2D/ObjectCore/Sprites.h>
#include <MT2D/ObjectCore/State.h>
#include <MT2D/ObjectCore/Object.h>
#include <MT2D/ObjectCore/STDFunctions.h>
#include <MT2D/MT2D.h>
#include <MT2D/MT2D_Display.h>
#include <MT2D/MT2D_System_Calls.h>
#include <MT2D/MT2D_Keyboard.h>
#include <MT2D/Joystick/MT2D_Joystick.h>
#include <cstdlib>
#include "objects/PlayerShip.h"
#include "objects/projectile/Projectile01.h"
#include "objects/enemy/Enemy1.h"
#include "objects/enemy/Enemy2.h"
#include "objects/enemy/Enemy3.h"
#include "objects/Rock01.h"
#include "objects/Explosions01.h"
#include "objects/Explosions02.h"
#include "objects/RandomStarNight.h"
#include <time.h>

Object *Projectile1;

int __PLAYER_SCORE__ = 0;

void RunGame() {
	time_t time2;
	time_t time3;
	int timer = 0;
	time_t t = time(NULL), t2 = time(NULL);

	int FPS_Delay = 0;
	double fps = 0;

	MT2D_Joystick_Init();
	RandomStarts_Init();
	Explosion01_Init();
	Explosion02_Init();
	Rock01_Init();
	MT2D_Joystick_Map_Button01(' ');
	MT2D_Play_Music("music.ogg");
	Object *Player = Create_Player_Object(12, 120);
	Projectile1 = Create_Projectile01_Object(0, 0);
	int *AcelY = &Player->Aceleration.Y;
	int *AcelX = &Player->Aceleration.X;
	float RAcelX = 0, RAcelY = 0;
	int Key = 0;
	char Slowdown = 1;
	int Cnt = 0;
	ObjectScene *Layer3Scene = ObjectScene_CreateEmpty();
	ObjectScene *Layer2Scene = ObjectScene_CreateEmpty();
	ObjectScene_Add(Layer3Scene, Player);
	for (int x = 0; x < 320; x += 30) {
		for (int y = 0; y < 240; y += 10) {
			ObjectScene_Add(Layer2Scene, Create_RandomStar_Object(x + 6 - rand() % 12, y + 3 - rand() % 6));
		}
	}
	while (true) {
		time3 = clock();
		if (Cnt % 50 == 0 + 3 - rand() % 6) {
			if (rand() % 100 < 20) {
				ObjectScene_Add(Layer3Scene, Create_Enemy02_Object(320, rand() % 200, -4, 0));
			}
			else if (rand() % 100 < 8) {
				ObjectScene_Add(Layer3Scene, Create_Rock01_Object(320, rand() % 200));
			}
			else {
				ObjectScene_Add(Layer3Scene, Create_Enemy01_Object(320, rand() % 200, -4, 0));
			}
			if (rand() % 100 >= 85 && rand()%100 <= 15) {
				for (int i = 0, j = rand()%60; i < 10 + j; i++) {
					ObjectScene_Add(Layer3Scene, Create_Enemy03_Object(320 + i * 20, rand() % 200, -6 - rand()%2, 1 - rand() % 2));
				}
			}
		}
		Cnt++;
		MT2D_Clear_Main_Window();
		ObjectScene_Goto_NextSteps(Layer2Scene);
		ObjectScene_Goto_NextSteps(Layer3Scene);
		ObjectScene_Render(Layer2Scene);
		ObjectScene_Render(Layer3Scene);

		insert_string_on_display("FPS:", 0, 0, DISPLAY_WINDOW1);
		insert_number_on_display(fps, 0, 4, DISPLAY_WINDOW1);
		insert_string_on_display("SCORE:", 0, 40, DISPLAY_WINDOW1);
		insert_number_on_display(__PLAYER_SCORE__, 0, 46, DISPLAY_WINDOW1);
		MT2D_Draw_Window(DISPLAY_WINDOW1);
		Slowdown = 1;
		MT2D_Joystick_Update();
		if (MT2D_Joystick_Touched()) {
			if (MT2D_Joystick_ArrowKey_Touched()) {
				RAcelY += (MT2D_Joystick_Get_LeftAxisY() >> 13) / 2.5;
				RAcelX += (MT2D_Joystick_Get_LeftAxisX() >> 13) / 2.5;
				Slowdown = 0;
				if (RAcelY < -5) {
					RAcelY = -5;
				}
				else if (RAcelY > 5) {
					RAcelY = 5;
				}
				if (RAcelX < -3) {
					RAcelX = -3;
				}
				else if (RAcelX > 3) {
					RAcelX = 3;
				}
			}
			if (MT2D_Joystick_Button_Touched(1)) {
				*(int*)Player->User_Vars[1].Data = 1;
			}
			else {
				*(int*)Player->User_Vars[1].Data = 0;
			}
		}
		else {
			*(int*)Player->User_Vars[1].Data = 0;
		}
		if (Slowdown == 1) {
			if (RAcelX > 0) {
				RAcelX -= 0.15;
			}
			else if (RAcelX < 0) {
				RAcelX += 0.15;
			}
			if (RAcelY > 0) {
				RAcelY -= 0.1;
			}
			else if (RAcelY < 0) {
				RAcelY += 0.1;
			}
		}
		AcelX[0] = RAcelX;
		AcelY[0] = RAcelY;
		MT2D_Joystick_Update();

		timer++;
		t2 = time(NULL);
		if (difftime(t2, t) >= 1.0) {

			fps = timer;
			timer = 0;
			t = time(NULL);
		}
		time2 = clock();
		if (fps >= 55 && fps <= 65);
		else if (timer != 0);
		else if (fps < 40) {
			FPS_Delay=12;
		}
		else if (fps < 53) {
			FPS_Delay+=3;
		}
		else if (fps < 58) {
			FPS_Delay ++;
		}
		else if (fps > 65) {
			FPS_Delay = 0;
		}
		else if (fps > 64) {
			FPS_Delay--;
		}
		printf("%d\n", FPS_Delay);
		if (FPS_Delay <= 16 && difftime(time2,time3) < 16) {
			MT2D_System_Delay(16 - difftime(time2,time3));//60fps lock, the clock - time is in case the render takes too many time to render that it'll go below 60fps
		}
	}
	MT2D_Joystick_Close();
}
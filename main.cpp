#include "GameMenu.h"
#include "GameMap.h"
#include <MT2D/MT2D.h>
#include <MT2D/Audio/MT2D_Audio_core.h>
#include <SDL.h>

int main(int argc, char *argv[]) {
	MT2D_Init();
	MT2D_Audio_Init();
	int whatshouldIdo = 0;
	whatshouldIdo = GameMenu();
	while (whatshouldIdo != 3) {
		if (whatshouldIdo == 1) {
			//play game
			RunGame();
		}

	}
	MT2D_Audio_Close();
	return 0;
}
#pragma once
typedef struct Object;
Object *Create_Enemy01_Object(int pX, int pY, int sX, int sY);
void SpawnSmallExplosion(Object *Caller);
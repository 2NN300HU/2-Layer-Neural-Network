#include "nnlearning.h"
#pragma once

#define col GetStdHandle(STD_OUTPUT_HANDLE) // 콘솔창의 핸들정보 받아오기.
#define WHITE SetConsoleTextAttribute( col,0x000f); // 흰색
#define GRAY SetConsoleTextAttribute( col,0x0008); // 회색

void gotoxy(int x, int y);

int be_input();

int get_input(WORD* vkey, COORD* pos);

int drawing(struct readfile* r, struct NeuralNetwork* nn, int nnsize[]);

void usertest();
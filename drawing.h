#include "nnlearning.h"
#pragma once

#define col GetStdHandle(STD_OUTPUT_HANDLE) // �ܼ�â�� �ڵ����� �޾ƿ���.
#define WHITE SetConsoleTextAttribute( col,0x000f); // ���
#define GRAY SetConsoleTextAttribute( col,0x0008); // ȸ��

void gotoxy(int x, int y);

int be_input();

int get_input(WORD* vkey, COORD* pos);

int drawing(struct readfile* r, struct NeuralNetwork* nn, int nnsize[]);

void usertest();
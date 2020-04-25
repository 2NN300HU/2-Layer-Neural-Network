#include "nnfunc.h"
#pragma once
FILE* imgfileopen(char* s);

FILE* lbfileopen(char* s);

void fileheaderread(FILE* fp);

void set(struct NeuralNetwork* nn, int ini, int nnsize[]);

void setsave(struct NeuralNetwork* nn, int nnsize[]);

void caseread(FILE* img, FILE* lb, struct readfile* r);
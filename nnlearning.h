#include "nnfile.h"
#pragma once
void foward(struct readfile* r, struct NeuralNetwork* nn, int nnsize[]);

void backward(struct readfile* r, struct NeuralNetwork* nn, int nnsize[]);

void neuralnetwork(int ini);
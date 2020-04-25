#include "nndata.h"
#pragma once
double gaussianRandom(double average, double stdev);

double xavier(int input, int output);

double initialize(int method, int input, int output);

double normalize(unsigned char val);

double standardize(double val);

double sigmoid(double val);

double softmax(double val, double sum);

double outputgrad(double input, double target);

double othergrad(struct NeuralNetwork* nn, double input, int a, int nnsize[]);

void savegrad(struct NeuralNetwork* nn, int nnsize[], int batch);

int outputmax(struct NeuralNetwork* nn, int nnsize[]);

double relu(double val);
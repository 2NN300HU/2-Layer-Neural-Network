#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <Windows.h>

#pragma once
#define INPUT 784
#define HIDDEN1 300
#define OUTPUT 10
#define BATCH 32
#define TRNSIZE 60000
#define TESTSIZE 10000
#define TRNIMG "./data/train-images.idx3-ubyte"
#define TRNLB "./data/train-labels.idx1-ubyte"
#define TSTIMG "./data/t10k-images.idx3-ubyte"
#define TSTLB "./data/t10k-labels.idx1-ubyte"
#define INIVAL "./data/InitializationValue.dat"
#define LRNRATE 0.1

struct readfile
{
	unsigned char input[INPUT];
	unsigned char tag;
};

struct layer1
{
	double in[INPUT];
};

struct synapse1
{
	double weight[HIDDEN1][INPUT];
	double bias[HIDDEN1];
	double calcweight[HIDDEN1][INPUT];
	double calcbias[HIDDEN1];
};
struct layer2
{
	double hid[HIDDEN1];
	double atf[HIDDEN1];
	double grad[HIDDEN1];
};
struct synapse2
{
	double weight[OUTPUT][HIDDEN1];
	double bias[OUTPUT];
	double calcweight[OUTPUT][HIDDEN1];
	double calcbias[OUTPUT];
};

struct layer3
{
	double out[OUTPUT];
	double atf[OUTPUT];
	double grad[OUTPUT];
	double target[OUTPUT];
};

struct NeuralNetwork
{
	struct layer1 ly1;
	struct synapse1 sy1;
	struct layer2 ly2;
	struct synapse2 sy2;
	struct layer3 ly3;
};
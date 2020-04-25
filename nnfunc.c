#include "nnfunc.h"

double gaussianRandom(double average, double stdev)
{
	double v1, v2, s, temp;
	do {

		v1 = 2 * ((double)rand() / RAND_MAX) - 1;

		v2 = 2 * ((double)rand() / RAND_MAX) - 1;

		s = v1 * v1 + v2 * v2;

	} while (s >= 1 || s == 0);

	s = (double)sqrt((-2 * log(s)) / s);
	temp = v1 * s;
	temp = (stdev * temp) + average;
	return temp;
}

double xavier(int input, int output)
{
	double temp;
	double variance = (double)2 / ((double)input + output);
	double stdev = sqrt(variance);
	temp = gaussianRandom(0, stdev);
	return temp;
}

double he(int input, int output)
{
	double temp;
	double variance = (double)4 / ((double)input + output);
	double stdev = sqrt(variance);
	temp = gaussianRandom(0, stdev);
	return temp;
}

double initialize(int method, int input, int output)
{
	double temp = 0;
	if (method == 0)
	{
		temp = xavier(input, output);
	}
	else
	{
		printf("Error: undefined initialize function value.\n");
	}
	return temp;
}

double normalize(unsigned char val)
{
	double temp;
	if (val > 150)
	{
		temp = 1.0;
	}
	else
	{
		temp = 0.0;
	}
	return temp;
}

double standardize(double val)
{
	double temp = (val-0.5)*2.0;
	return temp;
}

double relu(double val)
{
	double temp;
	if (val > 0.0)
	{
		temp = val;
	}
	else
	{
		temp = 0.01*val;
	}
	return temp;
}

double sigmoid(double val)
{
	double temp = (double)exp((double)-val);
	temp = (double)1 / (1 + temp);
	return temp;
}

double softmax(double val, double sum)
{
	double temp;
	temp = (double)exp((double)val) / sum;
	return temp;
}

double outputgrad(double input, double target)
{
	//Activation function : softmax

	//Cost function : MSE
	double temp = ((input)-target) * input * (1 - input);

	////Cost function : CE
	//double temp = ((input)-target);
	return temp;
}

double othergrad(struct NeuralNetwork* nn, double input, int a, int nnsize[])
{
	double sum = 0;
	for (int x = 0; x < nnsize[2]; x++)
	{
		sum += nn->ly3.grad[x] * nn->sy2.weight[x][a];
	}

	//Activation function : sigmoid
	double temp = sum * input * (1 - input);
	
	////Activation function : ReLu
	//double temp;
	//if (input > 0.0)
	//{
	//	temp = 1.0;
	//}
	//else
	//{
	//	temp = 0.01;
	//}
	//return temp;
	//temp = sum * temp ;

	return temp;
}

void savegrad(struct NeuralNetwork* nn, int nnsize[], int batch)
{
	for (int a = 0; a < nnsize[2]; a++)
	{
		for (int b = 0; b < nnsize[1]; b++)
		{
			nn->sy2.weight[a][b] -= (double)LRNRATE * nn->sy2.calcweight[a][b] / batch;
			nn->sy2.calcweight[a][b] = 0;
		}
		nn->sy2.bias[a] -= (double)LRNRATE * nn->sy2.calcbias[a] / batch;
		nn->sy2.calcbias[a] = 0;
	}

	for (int a = 0; a < nnsize[1]; a++)
	{
		for (int b = 0; b < nnsize[0]; b++)
		{
			nn->sy1.weight[a][b] -= (double)LRNRATE * nn->sy1.calcweight[a][b] / batch;
			nn->sy1.calcweight[a][b] = 0;
		}
		nn->sy1.bias[a] -= (double)LRNRATE * nn->sy1.calcbias[a] / batch;
		nn->sy1.calcbias[a] = 0;
	}
}

int outputmax(struct NeuralNetwork* nn, int nnsize[])
{
	int tempval = 0;
	for (int b = 0; b < nnsize[2]; b++)
	{
		tempval = nn->ly3.atf[b] >= nn->ly3.atf[tempval] ? b : tempval;
	}
	return tempval;
}
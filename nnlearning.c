#include "nnlearning.h"

void foward(struct readfile* r, struct NeuralNetwork* nn, int nnsize[])
{
	//layer 1
	for (int a = 0; a < nnsize[0]; a++)
	{
		nn->ly1.in[a] = standardize(normalize(r->input[a]));
	}

	//synapse 1
	for (int b = 0; b < nnsize[1]; b++)
	{
		double temp = 0;
		for (int a = 0; a < nnsize[0]; a++)
		{
			temp += nn->sy1.weight[b][a] * nn->ly1.in[a];

		}
		temp += nn->sy1.bias[b];

		nn->ly2.hid[b] = temp;

	}

	//layer 2
	for (int b = 0; b < nnsize[1]; b++)
	{
		nn->ly2.atf[b] = sigmoid(nn->ly2.hid[b]);
	}

	//synapse 2
	for (int b = 0; b < nnsize[2]; b++)
	{
		double temp = 0;
		for (int a = 0; a < nnsize[1]; a++)
		{
			temp += nn->sy2.weight[b][a] * nn->ly2.atf[a];

		}
		temp += nn->sy2.bias[b];
		nn->ly3.out[b] = temp;
	}

	//layer 3
	double sum = 0;
	for (int b = 0; b < nnsize[2]; b++)
	{
		sum += (double)exp((double)nn->ly3.out[b]);
	}

	for (int b = 0; b < nnsize[2]; b++)
	{
		nn->ly3.atf[b] = softmax(nn->ly3.out[b], sum);
	}
}

void backward(struct readfile* r, struct NeuralNetwork* nn, int nnsize[])
{
	for (int b = 0; b < nnsize[2]; b++)
	{
		nn->ly3.target[b] = (int)r->tag == b ? (double)1 : (double)0;
	}

	for (int a = 0; a < nnsize[2]; a++)
	{
		nn->ly3.grad[a] = outputgrad(nn->ly3.atf[a], nn->ly3.target[a]);
		for (int b = 0; b < nnsize[1]; b++)
		{
			nn->sy2.calcweight[a][b] += nn->ly3.grad[a] * nn->ly2.atf[b];
		}
		nn->sy2.calcbias[a] += nn->ly3.grad[a];
	}

	for (int a = 0; a < nnsize[1]; a++)
	{
		nn->ly2.grad[a] = othergrad(nn, nn->ly2.atf[a], a, nnsize);
		for (int b = 0; b < nnsize[0]; b++)
		{
			nn->sy1.calcweight[a][b] += nn->ly2.grad[a] * nn->ly1.in[b];
		}
		nn->sy1.calcbias[a] += nn->ly2.grad[a];
	}
}

void neuralnetwork(int ini)
{
	//난수준비
	srand((unsigned int)GetTickCount64());

	//memoization
	struct readfile* r = malloc(sizeof(struct readfile));
	if (r == NULL)
	{
		exit(0);
	}
	struct NeuralNetwork* nn = malloc(sizeof(struct NeuralNetwork));
	if (nn == NULL)
	{
		exit(0);
	}
	memset(r, 0, sizeof(struct readfile));
	memset(nn, 0, sizeof(struct NeuralNetwork));
	int nnsize[3] = { INPUT,HIDDEN1,OUTPUT };

	//초기화
	set(nn, ini, nnsize);

	//Train

	// mnist 파일 읽어오기
	FILE* trnimg, * trnlb;
	trnimg = imgfileopen(TRNIMG);
	fileheaderread(trnimg);
	trnlb = lbfileopen(TRNLB);
	fileheaderread(trnlb);

	//Learning
	for (int p = 1; p < (TRNSIZE / BATCH); p++)
	{
		for (int i = 0; i < BATCH; i++)
		{
			printf("\rTraining... batch ( %d / %d ) mini batch ( %02d / %d )", p + 1, TRNSIZE / BATCH, i + 1, BATCH);
			caseread(trnimg, trnlb, r);
			foward(r, nn, nnsize);
			backward(r, nn, nnsize);
		}
		savegrad(nn, nnsize, BATCH);
	}
	//저장
	setsave(nn, nnsize);
	printf("\n");

	//Test

	// mnist 파일 읽어오기
	FILE* tstimg, * tstlb;
	tstimg = imgfileopen(TSTIMG);
	fileheaderread(tstimg);
	tstlb = lbfileopen(TSTLB);
	fileheaderread(tstlb);

	//테스트
	int correct = 0, wrong = 0;
	for (int p = 0; p < TESTSIZE; p++)
	{
		caseread(tstimg, tstlb, r);
		foward(r, nn, nnsize);
		if ((int)r->tag == outputmax(nn, nnsize))
		{
			correct++;
		}
		else
		{
			wrong++;
		}
		//printf("real : %d expect : %d", (int)r->tag, outputmax(nn, nnsize));
		printf("\rTesting... ( %d / %d )", correct + wrong, TESTSIZE);
	}
	printf("Error rate : %.2f%%\n", (double)100 * wrong / ((double)correct + wrong));

	//종료
	fclose(tstimg);
	fclose(tstlb);
	fclose(trnlb);
	fclose(trnimg);
	free(r);
	free(nn);
}


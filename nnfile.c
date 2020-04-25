#include "nnfile.h"

FILE* imgfileopen(char* s)
{
	FILE* fp;
	fp = fopen(s, "rb");
	if (fp == NULL)
	{
		printf("Error : No image to train\n");
		exit(1);
	}
	return fp;
}

FILE* lbfileopen(char* s)
{
	FILE* fp;
	fp = fopen(s, "rb");
	if (fp == NULL)
	{
		printf("Error : No label to train\n");
		exit(1);
	}
	return fp;
}

void fileheaderread(FILE* fp)
{
	unsigned long magicnumber = 0, casesize = 0, col = 0, row = 0;
	fread(&magicnumber, sizeof(unsigned long), 1, fp);
	magicnumber = ntohl(magicnumber);
	if (magicnumber == 2051)
	{
		printf("Reading Image file...\nmagic number: 0x%08X\n", magicnumber);
		fread(&casesize, sizeof(unsigned long), 1, fp);
		casesize = ntohl(casesize);
		printf("case size: %lu\n", casesize);

		fread(&row, sizeof(unsigned long), 1, fp);
		row = ntohl(row);
		fread(&col, sizeof(unsigned long), 1, fp);
		col = ntohl(col);
		printf("img size: %lu * %lu\n\n", col, row);
	}
	else if (magicnumber == 2049)
	{
		printf("Reading Label file...\nmagic number: 0x%08X\n", magicnumber);
		fread(&casesize, sizeof(unsigned long), 1, fp);
		casesize = ntohl(casesize);
		printf("case size: %lu\n\n", casesize);
	}
	else
	{
		printf("Error : Undefined magic number\n");
		exit(0);
	}
}

void set(struct NeuralNetwork* nn, int ini, int nnsize[])
{
	if (ini == 0)
	{
		FILE* fp;
		fp = fopen(INIVAL, "rb");
		if (fp == NULL)
		{
			printf("Error : No initialize value file\n");
			exit(1);
		}
		printf("Loading initialize value file...");
		for (int a = 0; a < nnsize[1]; a++)
		{
			for (int b = 0; b < nnsize[0]; b++)
			{
				fread(&nn->sy1.weight[a][b], sizeof(double), 1, fp);
			}
			fread(&nn->sy1.bias[a], sizeof(double), 1, fp);
		}

		for (int a = 0; a < nnsize[2]; a++)
		{
			for (int b = 0; b < nnsize[1]; b++)
			{
				fread(&nn->sy2.weight[a][b], sizeof(double), 1, fp);
			}
			fread(&nn->sy2.bias[a], sizeof(double), 1, fp);
		}
	}
	else if (ini == 1)
	{
		printf("initializing...");
		for (int a = 0; a < nnsize[1]; a++)
		{
			for (int b = 0; b < nnsize[0]; b++)
			{
				nn->sy1.weight[a][b] = initialize(0, nnsize[0], nnsize[1]);
			}
			nn->sy1.bias[a] = initialize(0, nnsize[0], nnsize[1]);
		}

		for (int a = 0; a < nnsize[2]; a++)
		{
			for (int b = 0; b < nnsize[1]; b++)
			{
				nn->sy2.weight[a][b] = initialize(0, nnsize[1], nnsize[2]);
			}
			nn->sy2.bias[a] = initialize(0, nnsize[1], nnsize[2]);
		}
	}
	else
	{
		printf("Error: undefined initialize method value.\n");
	}
}

void setsave(struct NeuralNetwork* nn, int nnsize[])
{
	FILE* fp;
	fp = fopen(INIVAL, "wb");

	for (int a = 0; a < nnsize[1]; a++)
	{
		for (int b = 0; b < nnsize[0]; b++)
		{
			fwrite(&nn->sy1.weight[a][b], sizeof(double), 1, fp);
		}
		fwrite(&nn->sy1.bias[a], sizeof(double), 1, fp);
	}

	for (int a = 0; a < nnsize[2]; a++)
	{
		for (int b = 0; b < nnsize[1]; b++)
		{
			fwrite(&nn->sy2.weight[a][b], sizeof(double), 1, fp);
		}
		fwrite(&nn->sy2.bias[a], sizeof(double), 1, fp);
	}
}

void caseread(FILE* img, FILE* lb, struct readfile* r)
{
	for (int a = 0; a < INPUT; a++)
	{
		fread(&r->input[a], sizeof(unsigned char), 1, img);
	}
	fread(&r->tag, sizeof(unsigned char), 1, lb);
}
#include "drawing.h"

int main()
{
	printf("Welcome to machine learning system\nstyle: 2NN 300HU MSE\ndata set: MNIST\n");
	while (1)
	{
		int a;
		printf("\n1. Auto train and test 2. Test by user 0. Exit\nSelect mode:");
		int temp = scanf("%d", &a);
		if (a == 1)
		{
			int b;
			printf("Auto train and test mode...\n1. Initialize 2. Load initialize value file\nSelect initialize method: ");
			temp = scanf("%d", &b);
			if (b == 1)
			{
				int sure;
				printf("Initialize mode...\nThis mode will overwrite initialize value file. Are you sure? 0. Ok 1. No :");
				temp = scanf("%d", &sure);
				if (sure == 0)
				{
					printf("Initialize mode...\n");
					neuralnetwork(1);
					printf("\n");
				}
				else
				{
					printf("Initialize mode canceled\n");
				}
				
			}
			else if (b == 2)
			{
				printf("Load initialize value file mode...\n");
				neuralnetwork(0);
				printf("\n");
			}
			else
			{
				printf("Undefined method...\n");
			}
		}
		else if(a==2)
		{
			printf("User test mode... Loading...\n");
			Sleep(2000);
			usertest();
		}
		else if (a == 0)
		{
			printf("exiting...\n");
			break;
		}
		else
		{
			printf("Undefined mode...\n");
		}
	}
	return 0;
}
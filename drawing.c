#include "drawing.h"

HANDLE COUT = 0;
HANDLE CIN = 0;

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

int be_input()
{
	INPUT_RECORD input_record;
	DWORD input_count;

	PeekConsoleInput(CIN, &input_record, 1, &input_count);
	return input_count;
}

int get_input(WORD* vkey, COORD* pos)
{
	INPUT_RECORD input_record;
	DWORD input_count;
	static int check_pen = 0;

	ReadConsoleInput(CIN, &input_record, 1, &input_count);
	switch (input_record.EventType) {
	case MOUSE_EVENT:
		if (pos && (input_record.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED))
		{
			CONSOLE_SCREEN_BUFFER_INFO csbi;

			GetConsoleScreenBufferInfo(COUT, &csbi);

			*pos = input_record.Event.MouseEvent.dwMousePosition;
			pos->X -= csbi.srWindow.Left;
			pos->Y -= csbi.srWindow.Top;

			if (pos->Y <= 3)
			{/*그릴수 없음*/
			}
			else if (pos->Y >= 31)
			{/*그릴수 없음*/
			}
			else if (pos->X >= 28)
			{/*그릴수 없음*/
			}
			else if (pos->X <=0)
			{/*그릴수 없음*/
			}
			else
			{
				gotoxy(pos->X, pos->Y);
				printf("*");
				gotoxy(pos->X, pos->Y+1);
				printf("*");
				gotoxy(pos->X+1, pos->Y);
				printf("*");
				gotoxy(pos->X+1, pos->Y+1);
				printf("*");

			}
			return MOUSE_EVENT;
		}
		break;
	}
	return 0;
}

int drawing(struct readfile* r, struct NeuralNetwork* nn, int nnsize[])
{
	DWORD mode;
	WORD key;
	COORD pos;
	int x;
	int y;
	int make_frame = 0;	// 테두리 작성 변수
	int clear_width = 8, clear_length = 3;
	int check_help = 0;

	system("mode con: cols=30 lines=33"); // 화면 고정

	CIN = GetStdHandle(STD_INPUT_HANDLE);
	COUT = GetStdHandle(STD_OUTPUT_HANDLE);

	// 마우스 활성화
	GetConsoleMode(CIN, &mode);
	SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT);

	GRAY;
	while (make_frame != 30) // 가로줄 채우기
	{
		gotoxy(make_frame, 1); printf("*");
		gotoxy(make_frame, 3); printf("*");
		gotoxy(make_frame, 32); printf("*");
		make_frame++;
	}
	make_frame = 4;
	while (make_frame != 33) // 세로줄 채우기
	{
		gotoxy(0, make_frame); printf("*");
		gotoxy(29, make_frame); printf("*");
		make_frame++;
	}
	gotoxy(10, 2); printf("*"); gotoxy(20, 2); printf("*");

	WHITE;
	gotoxy(7, 0); printf("Neuralnetwork");
	gotoxy(13, 2); printf("reset");
	gotoxy(23, 2); printf("exit");


	while (1)															
	{
		if (be_input())
		{
			if (get_input(&key, &pos) != 0)								
			{

				MOUSE_EVENT;
				x = pos.X;												
				y = pos.Y;

				if (x >= 1 && x <= 27)
				{
					if (y >= 4 && y <= 30)
					{
						r->input[x - 1 + 28 * (y - 4)] = 255;
						r->input[x  + 28 * (y - 4)] = 255;
						r->input[x  + 28 * (y - 3)] = 255;
						r->input[x - 1 + 28 * (y - 3)] = 255;
						foward(r, nn, nnsize);
						gotoxy(0, 2); printf("expect: %d", outputmax(nn, nnsize));
					}

					if (y >= 1 && y <= 2) // 도구상자 범위
					{
						if (x >= 10 && x <= 19) // RESET
						{
							memset(r, 0, sizeof(struct readfile));
							clear_length = 4;
							clear_width = 1;
							while (clear_length <= 31)
							{
								while (clear_width <= 28)
								{
									gotoxy(clear_width, clear_length); printf(" ");
									clear_width++;
								}
								clear_width = 1;
								clear_length++;
							}
						}

						else if (x >= 20 && x <= 29) // EXIT
						{
							system("mode con: cols=152 lines=35"); // 화면 고정
							return 0;
						}
					}
				}
			}
		}
		
	}
}

void usertest()
{
	//Dynamic Programing 위한 공간
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

	//test
	set(nn, 0, nnsize);
	drawing(r,nn,nnsize);
	system("cls");

	//종료
	free(r);
	free(nn);
}
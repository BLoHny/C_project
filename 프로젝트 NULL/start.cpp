#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

void gotoxy(float x, int y);
void stage();
void home_main();
void home_map_draw();

void home_start() {
	int j = 0;
	int choose_number = 1, cy = 35;
	char choose = NULL;

	home_map_draw();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	gotoxy(44, cy);
	printf("▶");

	gotoxy(45.5, 35);
	printf("게임 시작");

	gotoxy(45.5, 38);
	printf("최고 점수");

	gotoxy(45.5, 41);
	printf("게임 종료");

	for (;;)
	{

		if (_kbhit())
			choose = _getch();

		if (choose == 72 && cy != 35)
		{
			gotoxy(44, cy);
			printf("  ");
			cy -= 3;
			gotoxy(44, cy);
			printf("▶");
			choose_number--;
			choose = NULL;
		}
		
		if (choose == 80 && cy != 41)
		{
			gotoxy(44, cy);
			printf("  ");
			cy += 3;
			gotoxy(44, cy);
			printf("▶");
			choose_number++;
			choose = NULL;
		}

		if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			if (choose_number == 1) {
				system("cls");
				Sleep(200);
				home_main();
			}
			else if (choose_number == 2) {

			}
			else {
				system("cls");
				gotoxy(44, 25);
				printf("게임을 종료합니다.");
				Sleep(1000);
				exit(0);
			}
		}

	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	system("cls");
	stage();

}

void home_map_draw()
{
	int colors[2] = { 8, 5 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			gotoxy(0, 0);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors[j]);
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("                                                                   \n");
			printf("                                                                      ####      ##  ##          ##  ###         ###                     \n");
			printf("                                                                      #####     ##  ##          ##  ###         ###                     \n");
			printf("                                                                      ## ###    ##  ##          ##  ###         ###                     \n");
			printf("                                                                      ##  ###   ##  ##          ##  ###         ###                     \n");
			printf("                                                                      ##   ###  ##  ##          ##  ###         ###                     \n");
			printf("                                                                      ##    ### ##  ###        ###  ###         ###                     \n");
			printf("                                                                      ##     #####   ###      ###   ###         ###                     \n");
			printf("                                                                      ##      ####     ########     ##########  ###########             \n");
			if (i == 0 && j == 0)
				Sleep(1000);
			else if (i == 0 && j == 1)
				Sleep(1000);
			else if (i == 1 && j == 0)
				Sleep(1000);
			else if (i == 1 && j == 1)
				Sleep(800);
			else if (i == 2 && j == 0)
				Sleep(500);
			else if (i == 2 && j == 1)
				Sleep(300);
			else if (i == 3)
				Sleep(100);
		}
	}
	Sleep(1200);
	for (int z = 0; z < 14; z++) {
		system("cls");
		gotoxy(0, z);
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("                                                                   \n");
		printf("                                                                      ####      ##  ##          ##  ###         ###                     \n");
		printf("                                                                      #####     ##  ##          ##  ###         ###                     \n");
		printf("                                                                      ## ###    ##  ##          ##  ###         ###                     \n");
		printf("                                                                      ##  ###   ##  ##          ##  ###         ###                     \n");
		printf("                                                                      ##   ###  ##  ##          ##  ###         ###                     \n");
		printf("                                                                      ##    ### ##  ###        ###  ###         ###                     \n");
		printf("                                                                      ##     #####   ###      ###   ###         ###                     \n");
		printf("                                                                      ##      ####     ########     ##########  ###########             \n");
		Sleep(120);
		if (z == 13) {
			Sleep(1500);
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	gotoxy(47.5, 17);
	printf("★");
	Sleep(500);
	gotoxy(30, 19);
	printf("★");
	Sleep(500);
	gotoxy(65, 19);
	printf("★");
	Sleep(500);
	gotoxy(47.5, 33);
	printf("★");
	Sleep(1000);

	gotoxy(0, 0);
	printf("                                                                                                              \n");
	printf("                                                                                                                             \n");
	printf("                                                                                                                             \n");
	printf("                                                                                                                             \n");
	printf("                                                                                                                             \n");
	printf("                                                                                                                             \n");
	printf("                                                                                                                             \n");
	printf("                                                                                                                             \n");
	printf("                                                                                                                             \n");
	printf("                                                                                                                             \n");
	printf("                                                                                                                             \n");
	printf("                                                                                                                             \n");
	printf("                                                                                                                             \n");
	printf("                                                                                                                             \n");
	printf("                              ▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲                                                                     ▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼       \n");
	printf("                                  ▼▲                ▲▼▲▼▲                                                                 ▲▼▲▼▲                ▲▼         \n");
	printf("                                      ▼▲▼▲▼▲▼▲▼▲▼▲▼▲                                                             ▲▼▲▼▲▼▲▼▲▼▲▼▲▼              \n");
	printf("                                        ▼▲             ▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼*▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼             ▲▼            \n");
	printf("                                           ▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼                       ▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼                    \n");
	printf("                                             ▼              ▼▲▼▲▼▲▼                                           ▼▲▼▲▼▲▼              ▼      \n");
	printf("                                               ▼▲▼▲▼▲▼▲▼▲▼                                                       ▼▲▼▲▼▲▼▲▼▲▼                   \n");
	printf("                                                 ▼          ▼▲                                                               ▲▼          ▼          \n");
	printf("                                                   ▼▲▼▲▼▲▼     ####      ##  ##          ##  ###         ###             ▼▲▼▲▼▲▼                      \n");
	printf("                                                    ▼      ▲▼      #####     ##  ##          ##  ###         ###              ▲▼      ▼                    \n");
	printf("                                                      ▼▲▼▲▼      ## ###    ##  ##          ##  ###         ###              ▼▲▼▲▼                           \n");
	printf("                                                        ▼▲▼▲      ##  ###   ##  ##          ##  ###         ###              ▲▼▲▼                         \n");
	printf("                                                        ▲▼▲▼      ##   ###  ##  ##          ##  ###         ###              ▼▲▼▲                          \n");
	printf("                                                        ▼▲▼▲      ##    ### ##  ###        ###  ###         ###              ▲▼▲▼                          \n");
	printf("                                                          ▼▲▼      ##     #####   ###      ###   ###         ###              ▼▲▼                         \n");
	printf("                                                           ▲▼▲     ##      ####     ########     ##########  ###########     ▲▼▲                          \n");
	printf("                                                           ▼▲▼                                                               ▼▲▼                     \n");
	printf("                                                             ▼▲▼▲                                                       ▲▼▲▼                     \n");
	printf("                                                               ▼▲▼▲▼▲                                           ▲▼▲▼▲▼                     \n");
	printf("                                                                 ▼▲▼▲▼▲▼▲▼                          ▼▲▼▲▼▲▼▲▼                     \n");
	printf("                                                                   ▼▲▼▲▼▲▼                              ▼▲▼▲▼▲▼                \n");
}
#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

void gotoxy(float x, int y);
void stage();
void home_draw();
void home_start();
void shop_main();
void inf_main();

int mx = 30, my = 15;

char choose;

void home_main()
{
	home_draw();

	while (1)
	{
		if (_kbhit)
			choose = _getch();

		if (choose == '1') {
			system("cls");
			choose = NULL;
			stage();
		}
		if (choose == '2') {
			system("cls");
			choose = NULL;
			shop_main();
		}
		if (choose == '3') {
			system("cls");
			choose = NULL;
			inf_main();
		}
		if (choose == '4') {
			system("cls");
			gotoxy(44, 25);
			printf("게임을 종료합니다.");
			Sleep(1000);
			exit(0);
		}
	}
}

void home_draw()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

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
	printf("                                                   ▼▲▼▲▼▲▼                                                               ▼▲▼▲▼▲▼                      \n");
	printf("                                                    ▼      ▲▼                                                                 ▲▼      ▼                    \n");
	printf("                                                      ▼▲▼▲▼                                                                 ▼▲▼▲▼                           \n");
	printf("                                                        ▼▲▼▲                                                                 ▲▼▲▼                         \n");
	printf("                                                        ▲▼▲▼                                                                 ▼▲▼▲                          \n");
	printf("                                                        ▼▲▼▲                                                                 ▲▼▲▼                          \n");
	printf("                                                          ▼▲▼                                                                 ▼▲▼                         \n");
	printf("                                                           ▲▼▲                                                               ▲▼▲                          \n");
	printf("                                                           ▼▲▼                                                               ▼▲▼                     \n");
	printf("                                                             ▼▲▼▲                                                       ▲▼▲▼                     \n");
	printf("                                                               ▼▲▼▲▼▲                                           ▲▼▲▼▲▼                     \n");
	printf("                                                                 ▼▲▼▲▼▲▼▲▼                          ▼▲▼▲▼▲▼▲▼                     \n");
	printf("                                                                   ▼▲▼▲▼▲▼                              ▼▲▼▲▼▲▼                \n");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	gotoxy(38, 21); printf("게임 시작");
	gotoxy(38, 23); printf("   (1)");
	gotoxy(52, 21); printf("업그레이드");
	gotoxy(52, 23); printf("   (2)");
	gotoxy(39, 28); printf("정보");
	gotoxy(39, 30); printf(" (3)");
	gotoxy(52, 28); printf("게임 종료");
	gotoxy(52, 30); printf("   (4)");
}

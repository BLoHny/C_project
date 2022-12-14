#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAP_X 200
#define MAP_Y 50
#define MON 11
#define MON1 12
#define MON2 13
#define MAX_MOB 60

void map_change();
void player();
void stage_map_main();
void gotoxy(float x, int y);
void home_main();
void shop_main();
void shop_draw();
void inf_main();
void inf_draw();

//게임 메인 변수들
//------------------------------------------------------------
int map[MAP_Y][MAP_X];
int bull = 0;
int stop = 0, game_stop = FALSE;
int py = 25;
int score = 0, bullet_num = 1;
double mob_damage1 = 2, mob_damage2 = 1, mob_damage3 = 3, hp1 = 3, hp2 = 2, hp3 = 5;
double player_attack = 1, tower_hp = 100, tower_hp1;
double delay1, delay, delay_time = 0.3;
int monster_ran = 200, random_monster_type;
double monster_delay = 0.4;
//------------------------------------------------------------


//상점 메인 변수들
//------------------------------------------------------------
int money = 0, upgrade_attak_money = 500, upgrade_bullet_money = 2000, upgrade_bullet_speed_money = 200, upgrade_tower_money = 500;
double upgrade_attak_damage = 1, upgrade_tower_hp = 50;
int attack_upgrade_cnt = 1, bullet_upgrade_cnt = 0, speed_upgrade_cnt = 1, tower_upgrade_cnt = 0;
//------------------------------------------------------------


//정보 메인 변수들
//------------------------------------------------------------
int monster_cnt = 0, all_score_save = 0;
//------------------------------------------------------------


struct monster {
	int x, y;
	int type;
	double damage;
	double hp;
	bool active = FALSE;
}mob[MAX_MOB] = { NULL }; //최대 몬스터 수

struct bullet {
	int x, y;
	bool active;
}shoot[100];

void stage()
{
	srand(time(NULL));

	gotoxy(2, py);
	printf("옷");

	gotoxy(44, 2);
	printf(" time :");

	gotoxy(44, 4);
	printf("score :");

	gotoxy(48, 4);
	printf("%6d", score);

	gotoxy(7, 3);
	printf("저지선 내구도 : %3.1lf", tower_hp);

	stage_map_main();

	delay = (double)clock() / CLOCKS_PER_SEC;

	double delay2 = delay + 0.6, play_time = 0.1, p_t_s = delay + 0.1;
	int monster_ran_time = delay + 20;

	tower_hp1 = tower_hp;

	while (1)
	{
		delay = (double)clock() / CLOCKS_PER_SEC;

		map_change();
		player();

		if (game_stop == FALSE)
		{
			if (delay >= p_t_s) {
				gotoxy(48, 2);
				printf("%7.1lf", play_time - 0.1);
				play_time += 0.1;
				p_t_s = delay + 0.1;
			}

			for (int i = 0; i < MAX_MOB; i++) {
				if (mob[i].active == FALSE) {
					random_monster_type = rand() % 100 + 1;

					mob[i].x = rand() % monster_ran + 99;
					mob[i].y = rand() % 35 + 9;

					if (random_monster_type >= 1 && random_monster_type <= 10) {
						mob[i].hp = hp3;
						mob[i].type = 3;
						mob[i].damage = mob_damage3;
					}
					else if (random_monster_type >= 20 && random_monster_type <= 40) {
						mob[i].hp = hp2;
						mob[i].type = 2;
						mob[i].damage = mob_damage2;
					}
					else {
						mob[i].hp = hp1;
						mob[i].type = 1;
						mob[i].damage = mob_damage1;
					}
					mob[i].active = TRUE;
				}

				if (mob[i].x < 94) {
					if (mob[i].type == 1)
						map[mob[i].y][mob[i].x] = MON;
					else if (mob[i].type == 2)
						map[mob[i].y][mob[i].x] = MON1;
					else if (mob[i].type == 3)
						map[mob[i].y][mob[i].x] = MON2;
				}

				if (delay >= delay2) {
					for (int j = 0; j < MAX_MOB; j++) {
						if (mob[j].x > 8)
							mob[j].x--;
						else {
							mob[j].active = FALSE;
							tower_hp1 -= mob[j].damage;

							gotoxy(7, 3);
							printf("                       ");
							gotoxy(7, 3);
							printf("저지선 내구도 : %3.1lf", tower_hp1);
						}
					}
					delay2 = delay + monster_delay;
				}
			}

			if (tower_hp1 <= 0) // 게임 오버시 초기화 및 보상 획득
			{
				Sleep(300);
				system("cls");
				Sleep(500);
				money += score / 10;
				score = 0;
				hp1 = 3; hp2 = 2; hp3 = 5;
				mob_damage1 = 2; mob_damage2 = 1; mob_damage3 = 3;
				monster_ran = 200;
				monster_delay = 0.4;
				for (int i = 0; i < MAX_MOB; i++) {
					mob[i].active = FALSE;
				}
				home_main();
			}

			if (stop == TRUE) {
				if (delay >= delay1) {
					stop = FALSE;
				}
			}

			if (delay >= monster_ran_time) {
				if (monster_ran > 100)
					monster_ran -= 5;
				if (monster_delay > 0.35)
					monster_delay -= 0.03;
				if (play_time <= 150) {
					hp1 += 1;
					hp2 += 0.7;
					hp3 += 1.8;
					mob_damage1 += 0.5;
					mob_damage2 += 0.2;
					mob_damage3 += 0.8;
				}
				else if (play_time > 150 && play_time <= 300) {
					hp1 += 3;
					hp2 += 2.1;
					hp3 += 5.4;
					mob_damage1 += 1.5;
					mob_damage2 += 0.6;
					mob_damage3 += 2.4;
				}
				else {
					hp1 += 5;
					hp2 += 3.3;
					hp3 += 7.6;
					mob_damage1 += 2.1;
					mob_damage2 += 1.5;
					mob_damage3 += 5;
				}
				monster_ran_time = delay + 20;
			}

		}
		Sleep(10);
	}
}

void map_change()
{
	for (int i = 8; i < MAP_Y - 5; i++) {
		for (int j = 0; j < MAP_X; j++) {
			if (map[i][j] == 2) { //지우기
				gotoxy(j, i);
				printf("  ");
				map[i][j] = 0;
			}
			if (map[i][j] == 4) { //몹 지우기 - 1
				gotoxy(j, i);
				printf("  ");
				gotoxy(j, i + 1);
				printf("    ");
				map[i][j] = 5;
			}
			if (map[i][j] == 5) { //몹 지우기 - 2
				gotoxy(j, i);
				printf("  ");
				gotoxy(j, i + 1);
				printf("    ");
				map[i][j] = 0;
			}
			if (map[i][j] == 1) { //총알 그리기
				gotoxy(j, i);
				printf("->");
				map[i][j] = 2;
			}
			if (map[i][j] == MON) { //몹 그리기 - 1
				gotoxy(j, i);
				printf("○");
				gotoxy(j, i + 1);
				printf("/＼");
				map[i][j] = 4;
			}
			if (map[i][j] == MON1) { //몹 그리기 - 2
				gotoxy(j, i);
				printf("◆");
				gotoxy(j, i + 1);
				printf("/＼");
				map[i][j] = 4;
			}
			if (map[i][j] == MON2) { //몹 그리기 - 3
				gotoxy(j, i);
				printf("□");
				gotoxy(j, i + 1);
				printf("/＼");
				map[i][j] = 4;
			}
		}
	}
	return;
}

void player()
{
	char exit = NULL;

	if (_kbhit())
		exit = _getch();

	if (exit == 27) {
		game_stop = TRUE;
		gotoxy(41.5, 22); printf("                             ");
		gotoxy(41.5, 23); printf("                             ");
		gotoxy(41.5, 24); printf("                             ");
		gotoxy(41.5, 25); printf("                             ");
	}

	if (game_stop == TRUE) {
		gotoxy(41.5, 22); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
		gotoxy(41.5, 23); printf("┃                           ┃");
		gotoxy(41.5, 24); printf("┃                           ┃");
		gotoxy(41.5, 25); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

		gotoxy(43, 23);
		printf("게임을 종료하시겠습니까?");
		gotoxy(44, 24);
		printf("예(1)      아니오(2)");

		if (exit == '1') {
			Sleep(300);
			system("cls");
			Sleep(500);
			for (int i = 0; i < 100; i++) {
				shoot[i].active = FALSE;
			}
			money += score / 10;
			score = 0;
			hp1 = 3; hp2 = 2; hp3 = 5;
			mob_damage1 = 2; mob_damage2 = 1; mob_damage3 = 3;
			monster_ran = 200;
			monster_delay = 0.4;
			for (int i = 0; i < MAX_MOB; i++) {
				mob[i].active = FALSE;
			}
			game_stop = FALSE;
			home_main();
		}
		if (exit == '2') {
			gotoxy(41.5, 22); printf("                             ");
			gotoxy(41.5, 23); printf("                             ");
			gotoxy(41.5, 24); printf("                             ");
			gotoxy(41.5, 25); printf("                             ");
			game_stop = FALSE;
		}
	}
	else {
		if (GetAsyncKeyState(VK_UP) & 0x8000 && py > 8) //위
		{
			gotoxy(2, py);
			printf("  ");
			py--;
			gotoxy(2, py);
			printf("옷");

		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000 && py < 44) //아래
		{
			gotoxy(2, py);
			printf("  ");
			py++;
			gotoxy(2, py);
			printf("옷");
		}

		if (GetAsyncKeyState(VK_CONTROL) & 0x8000) //총알 발사
		{
			if (stop == FALSE) {
				shoot[bull].x = 7;
				shoot[bull].y = py; //플레이어 y좌표
				shoot[bull].active = TRUE; //총알 TRUE로 변경
				bull++;
				if (bull == 100) //초기화
					bull = 0;
				stop = 1;
				delay1 = delay + delay_time;
			}
		}
		for (int i = 0; i < 100; i++) {
			if (shoot[i].active) { //총알이 TRUE면 실행

				shoot[i].x++;
				if (bullet_upgrade_cnt == 2) {
					if (shoot[i].x < 94)
						shoot[i].x++;
				}

				if (bullet_upgrade_cnt == 0)
					map[shoot[i].y][shoot[i].x] = 1;
				else if (bullet_upgrade_cnt == 1) {
					map[shoot[i].y - 1][shoot[i].x] = 1;
					map[shoot[i].y + 1][shoot[i].x] = 1;
				}
				else {
					map[shoot[i].y - 1][shoot[i].x] = 1;
					map[shoot[i].y][shoot[i].x + 1] = 1;
					map[shoot[i].y + 1][shoot[i].x] = 1;
				}

				for (int j = 0; j < MAX_MOB; j++) {
					if (bullet_upgrade_cnt == 0) {
						if (mob[j].active && shoot[i].x == mob[j].x && shoot[i].y == mob[j].y || shoot[i].x == mob[j].x && shoot[i].y == mob[j].y + 1) {
							mob[j].hp -= player_attack;

							if (mob[j].hp <= 0) {
								if (mob[j].type == 1) {
									score += 100;
									all_score_save += 100;
								}
								else if (mob[j].type == 2) {
									score += 75;
									all_score_save += 75;
								}
								else {
									score += 150;
									all_score_save += 150;
								}
								monster_cnt++;
								gotoxy(48, 4);
								printf("         ");
								gotoxy(48, 4);
								printf("%6d", score);
								map[mob[j].y][mob[j].x] = 4;
								mob[j].active = FALSE;
							}

							shoot[i].active = FALSE; //총알 FALSE로 변경

						}
					}
					else if (bullet_upgrade_cnt == 1) {
						if (mob[j].active && shoot[i].x == mob[j].x && shoot[i].y - 1 == mob[j].y || shoot[i].x == mob[j].x && shoot[i].y - 1 == mob[j].y + 1 || mob[j].active && shoot[i].x == mob[j].x && shoot[i].y + 1 == mob[j].y || shoot[i].x == mob[j].x && shoot[i].y + 1 == mob[j].y + 1) {
							mob[j].hp -= player_attack * 1.5;

							if (mob[j].hp <= 0) {
								if (mob[j].type == 1) {
									score += 100;
									all_score_save += 100;
								}
								else if (mob[j].type == 2) {
									score += 75;
									all_score_save += 75;
								}
								else {
									score += 150;
									all_score_save += 150;
								}
								monster_cnt++;
								gotoxy(48, 4);
								printf("         ");
								gotoxy(48, 4);
								printf("%6d", score);
								map[mob[j].y][mob[j].x] = 4;
								mob[j].active = FALSE;
							}

							shoot[i].active = FALSE; //총알 FALSE로 변경

						}
					}
					else {
						if (mob[j].active && shoot[i].x == mob[j].x && shoot[i].y - 1 == mob[j].y || shoot[i].x == mob[j].x && shoot[i].y - 1 == mob[j].y + 1 || mob[j].active && shoot[i].x == mob[j].x && shoot[i].y + 1 == mob[j].y || shoot[i].x == mob[j].x && shoot[i].y + 1 == mob[j].y + 1 || mob[j].active && shoot[i].x + 1 == mob[j].x && shoot[i].y == mob[j].y || shoot[i].x + 1 == mob[j].x && shoot[i].y == mob[j].y + 1) {
							mob[j].hp -= player_attack * 2;

							if (mob[j].hp <= 0) {
								if (mob[j].type == 1) {
									score += 100;
									all_score_save += 100;
								}
								else if (mob[j].type == 2) {
									score += 75;
									all_score_save += 75;
								}
								else {
									score += 150;
									all_score_save += 150;
								}
								monster_cnt++;
								gotoxy(48, 4);
								printf("         ");
								gotoxy(48, 4);
								printf("%6d", score);
								map[mob[j].y][mob[j].x] = 4;
								mob[j].active = FALSE;
							}

							shoot[i].active = FALSE; //총알 FALSE로 변경

						}
					}
				}
				if (shoot[i].x > 93)
					shoot[i].active = FALSE; //총알 FALSE로 변경
			}
		}
	}
	return;
}

void shop_main()
{
	shop_draw();
	char upgrade = NULL;
	int U_N = 0;

	while (1)
	{
		if (_kbhit())
			upgrade = _getch();

		if (upgrade == '1') {
		RE1:
			gotoxy(36.5, 37);  printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
			gotoxy(36.5, 38);  printf("┃                                            ┃");
			if (attack_upgrade_cnt < 4) {
				gotoxy(36.5, 39);  printf("┃      공격력   %.0lf  ->  %.0lf      -    ◆  %4d  ┃", player_attack, player_attack + upgrade_attak_damage, upgrade_attak_money);
			}
			else {
				gotoxy(36.5, 39);  printf("┃      공격력   %.0lf  ->  MAX    -    ◆   MAX  ┃", player_attack);
			}
			gotoxy(36.5, 40);  printf("┃                                            ┃");
			gotoxy(36.5, 41);  printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
			U_N = 1;
		}
		if (upgrade == '2') {
		RE2:
			gotoxy(36.5, 37);  printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
			gotoxy(36.5, 38);  printf("┃                                            ┃");
			if (speed_upgrade_cnt < 6) {
				gotoxy(36.5, 39);  printf("┃  공격 속도 %.2lf  -> %.2lf    -    ◆  %4d  ┃", delay_time, delay_time - 0.05, upgrade_bullet_speed_money);
			}
			else {
				gotoxy(36.5, 39);  printf("┃  공격 속도 %.2lf  ->  MAX    -    ◆   MAX  ┃", delay_time);
			}
			gotoxy(36.5, 40);  printf("┃                                            ┃");
			gotoxy(36.5, 41);  printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
			U_N = 2;
		}
		if (upgrade == '3') {
		RE3:
			gotoxy(36.5, 37);  printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
			gotoxy(36.5, 38);  printf("┃                                            ┃");
			if (bullet_upgrade_cnt < 2) {
				gotoxy(36.5, 39);  printf("┃     총알 수   %d  ->  %d      -    ◆  %4d  ┃", bullet_num, bullet_num + 1, upgrade_bullet_money);
			}
			else {
				gotoxy(36.5, 39);  printf("┃     총알 수   %d  ->  MAX    -    ◆   MAX  ┃", bullet_num);
			}
			gotoxy(36.5, 40);  printf("┃                                            ┃");
			gotoxy(36.5, 41);  printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
			U_N = 3;
		}
		if (upgrade == '4') {
		RE4:
			gotoxy(36.5, 37);  printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
			gotoxy(36.5, 38);  printf("┃                                            ┃");
			if (tower_upgrade_cnt < 4) {
				gotoxy(36.5, 39);  printf("┃  성벽 체력  %.0lf  ->  %.0lf    -    ◆  %4d  ┃", tower_hp, tower_hp + upgrade_tower_hp, upgrade_tower_money);
			}
			else {
				gotoxy(36.5, 39);  printf("┃  성벽 체력  %.0lf  ->  MAX    -    ◆   MAX  ┃", tower_hp);
			}
			gotoxy(36.5, 40);  printf("┃                                            ┃");
			gotoxy(36.5, 41);  printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
			U_N = 4;
		}
		if (upgrade == ' ') {
			if (U_N == 1) { //데미지 업그레이드
				if (attack_upgrade_cnt < 4) {
					if (money >= upgrade_attak_money) {
						money -= upgrade_attak_money;
						player_attack += upgrade_attak_damage;
						upgrade_attak_damage += attack_upgrade_cnt;
						upgrade_attak_money += 500;
						gotoxy(47, 8);
						printf(" %5d", money);
						attack_upgrade_cnt++;
						upgrade = NULL;
						goto RE1;
					}
				}
			}
			if (U_N == 2) { //공격속도 업그레이드
				if (speed_upgrade_cnt < 6) {
					if (money >= upgrade_bullet_speed_money) {
						money -= upgrade_bullet_speed_money;
						delay_time -= 0.05;
						upgrade_bullet_speed_money += 200 * speed_upgrade_cnt;
						gotoxy(47, 8);
						printf(" %5d", money);
						speed_upgrade_cnt++;
						upgrade = NULL;
						goto RE2;
					}
				}
			}
			if (U_N == 3) { //총알 개수 업그레이드
				if (bullet_upgrade_cnt < 2) {
					if (money >= upgrade_bullet_money) {
						money -= upgrade_bullet_money;
						bullet_num++;
						upgrade_bullet_money = 5000;
						gotoxy(47, 8);
						printf(" %5d", money);
						bullet_upgrade_cnt++;
						upgrade = NULL;
						goto RE3;
					}
				}
			}
			if (U_N == 4) { //성벽 업그레이드
				if (tower_upgrade_cnt < 4) {
					if (money >= upgrade_tower_money) {
						money -= upgrade_tower_money;
						tower_hp += upgrade_tower_hp;
						upgrade_tower_hp += 50 * tower_upgrade_cnt;
						upgrade_tower_money += 500;
						gotoxy(47, 8);
						printf(" %5d", money);
						tower_upgrade_cnt++;
						upgrade = NULL;
						goto RE4;
					}
				}
			}
		}
		if (upgrade == 'a') {
			money += 10000;
			gotoxy(47, 8);
			printf(" %5d", money);
			upgrade = NULL;
		}
		if (upgrade == 27) {
			system("cls");
			home_main();
		}
	}
}

void shop_draw()
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

	gotoxy(38, 21); printf("  공격력");
	gotoxy(38, 23); printf("   (1)");
	gotoxy(52, 21); printf("공격 속도");
	gotoxy(52, 23); printf("   (2)");
	gotoxy(38, 28); printf("총알 강화");
	gotoxy(39, 30); printf(" (3)");
	gotoxy(52, 28); printf("성벽 강화");
	gotoxy(52, 30); printf("   (4)");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);

	gotoxy(44, 1);  printf("        ▲");
	gotoxy(44, 2);  printf("       ▲▲");
	gotoxy(44, 3);  printf("      ▲▼▲");
	gotoxy(44, 4);  printf("    ▲▼  ▼▲");
	gotoxy(44, 5);  printf("   ▲        ▲");
	gotoxy(44, 6);  printf(" ▲▼        ▼▲");
	gotoxy(44, 7);  printf(" ▼            ▼");
	gotoxy(44, 9);  printf(" ▲            ▲");
	gotoxy(44, 10); printf(" ▼▲        ▲▼");
	gotoxy(44, 11); printf("   ▼        ▼");
	gotoxy(44, 12); printf("    ▼▲  ▲▼");
	gotoxy(44, 13); printf("      ▼▲▼");
	gotoxy(44, 14); printf("       ▼▼");
	gotoxy(44, 15); printf("        ▼");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);

	gotoxy(38, 5);  printf("    ▲");
	gotoxy(38, 6);  printf("   ▲▲");
	gotoxy(38, 7);  printf("  ▲▼▲");
	gotoxy(38, 8);  printf("  ▼▲▼");
	gotoxy(38, 9);  printf("   ▼▼");
	gotoxy(38, 10);  printf("    ▼");

	gotoxy(54, 5);  printf("    ▲");
	gotoxy(54, 6);  printf("   ▲▲");
	gotoxy(54, 7);  printf("  ▲▼▲");
	gotoxy(54, 8);  printf("  ▼▲▼");
	gotoxy(54, 9);  printf("   ▼▼");
	gotoxy(54, 10);  printf("    ▼");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

	gotoxy(47, 8);
	printf(" %5d", money);
}

void inf_main()
{
	inf_draw();

	delay = (double)clock() / CLOCKS_PER_SEC;

	while (1)
	{
		char exit = NULL;
		if (_kbhit)
			exit = _getch();

		if (exit == 27) {
			system("cls");
			home_main();
		}
	}
}

void inf_draw()
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

	gotoxy(44, 21); printf("플레이 타임 - %.1lf", delay);
	gotoxy(44, 25); printf(" 몹 처치 수 - %d", monster_cnt);
	gotoxy(44, 29); printf("  총 점수  -  %d", all_score_save);
}
//히히 망했다
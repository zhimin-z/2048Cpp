#include <time.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>

//游戏主界面是一个4*4的16宫格，使用二人维数组表示，用0代表空格。
int a[4][4] = {0};
//宫格中的空格个数
int empty;

//用于绘制游戏界面
void draw();
//游戏运行的逻辑主体
void play();
//初始化
void init();
//绘制单个数字
void draw_one(int y, int x);
//确定新数字出现位置
void cnt_value(int *new_y, int *new_x);
//结束游戏
void game_over();
//统计(y,x)对应的格子周围一圈空格的个数
int cnt_one(int y, int x);

int main()
{
	init();
	play();
	endwin();
	return 0;
}

void init()
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);

	empty = 15;
	srand(time(0));
	int x = rand() % 4;
	int y = rand() % 4;
	a[y][x] = 2;
	draw();
}

void draw()
{
	clear();
	
	//绘制横线，n代表行，m代表列
	for(int n = 0; n < 9; n += 2)
		for(int m = 0; m < 21; m++)
		{
			move(n, m);
			addch('-');
			refresh();
		}
	
	//绘制竖线
	for(int m = 0; m < 22; m +=5)
		for(int n = 1; n < 8; n++)
		{
			move(n, m);
			addch('|');
			refresh();
		}

	//绘制数字
	for(int y = 0; y < 4; y++)
		for(int x = 0; x < 4; x++)
		{
			draw_one(y, x);
		}
}

void draw_one(int y, int x)
{
    char c[5] = {0x00}; 
    int i = a[y][x];
    int m = 0;

    while(i > 0)
    {
        int j = i % 10;
        c[m++] = j + '0';
        i = i / 10;
    }

    m = 0;
    int k = (x + 1) * 5 - 1;

    while(c[m] != 0x00)
    {
        move(2*y+1, k);
        addch(c[m++]);
        k--;
    }
}

void play()
{
	while(1) 
	{
		int i;
		int move = 0;
		int old_empty = empty;
		char ch = getch(); 

		switch(ch) {
			//左移
			case 97:
			case 104:
			case 68:
				for(int y = 0; y < 4; y++)
					for(int x = 0; x < 4; ) 
					{
						if(a[y][x] == 0) 
						{
							x++;
							continue;
						} 
						else 
						{
							for(i = x + 1; i < 4; i++) 
							{
								if(a[y][i] == 0) 
								{
									continue;
								}
								else 
								{
									if(a[y][x] == a[y][i]) 
									{
										a[y][x] += a[y][i];
										a[y][i] = 0;
										empty++;
										break;
									}
									else 
									{
										break;
									}
								}
							}
							x = i;
						}
					}
				for(int y = 0; y < 4; y++)
					for(int x = 0; x < 4; x++) 
					{
						if(a[y][x] == 0) 
						{
							continue;
						} 
						else 
						{
							for(i = x; (i > 0) && (a[y][i-1] == 0); i--) 
							{
								a[y][i-1] = a[y][i];
								a[y][i] = 0;
							    move = 1;
							}
						}
					}
				break;
			//右移
			case 100:
			case 108:
			case 67:
				for(int y = 0; y < 4; y++)
					for(int x = 3; x >= 0; ) 
					{
						if(a[y][x] == 0) 
						{
							x--;
							continue;
						} 
						else 
						{
							for(i = x - 1; i >= 0; i--)
							{
								if(a[y][i] == 0)
								{
									continue;
								} 
								else if(a[y][x] == a[y][i]) 
								{
									a[y][x] += a[y][i];
									a[y][i] = 0;
									empty++;
									break;
								} 
								else 
								{
									break;
								}
							}
							x = i;
						}
					}
				for(int y = 0; y < 4; y++)
					for(int x = 3; x >= 0; x--) 
					{
						if(a[y][x] == 0) 
						{
							continue;
						} else 
						{
							for(i = x; (i < 3) && (a[y][i+1] == 0); i++) 
							{
								a[y][i+1] = a[y][i];
								a[y][i] = 0;
							    move = 1;
							}
						}
					}
				break;
			//上移
			case 119:
			case 107:
			case 65:
				for(int x = 0; x < 4; x++)
					for(int y = 0; y < 4; ) 
					{
						if(a[y][x] == 0)
						{
							y++;
							continue;
						} 
						else 
						{
							for(i = y + 1; i < 4; i++) 
							{
								if(a[i][x] == 0) 
								{
									continue;
								} 
								else if(a[y][x] == a[i][x]) 
								{
									a[y][x] += a[i][x];
									a[i][x] = 0;
									empty++;
									break;
								} else 
								{
									break;
								}
							}
							y = i;
						}
					}
				for(int x = 0; x < 4; x++)
					for(int y = 0; y < 4; y++) 
					{
						if(a[y][x] == 0) 
						{
							continue;
						} 
						else
						{
							for(i = y; (i > 0) && (a[i-1][x] == 0); i--) 
							{
								a[i-1][x] = a[i][x];
								a[i][x] = 0;
							    move = 1;
							}
						}
					}
				break;
			//下移
			case 115:
			case 106:
			case 66:
				for(int x = 0; x < 4; x++)
					for(int y = 3; y >= 0; ) 
					{
						if(a[y][x] == 0) 
						{
							y--;
							continue;
						} 
						else 
						{
							for(i = y - 1; i >= 0; i--) 
							{
								if(a[i][x] == 0) 
								{
									continue;
								} 
								else if(a[y][x] == a[i][x])
								{
									a[y][x] += a[i][x];
									a[i][x] = 0;
									empty++;
									break;
								} 
								else
								{
									break;
								}
							}
							y = i;
						}
					}
				for(int x = 0; x < 4; x++)
					for(int y = 3; y >= 0; y--) 
					{
						if(a[y][x] == 0) 
						{
							continue;
						} 
						else 
						{
							for(i = y; (i < 3) && (a[i+1][x] == 0); i++) 
							{
								a[i+1][x] = a[i][x];
								a[i][x] = 0;
							    move = 1;
							}
						}
					}
				break;
			//退出
			case 'Q':
			case 'q':
				game_over();
				break;
			default:
				continue;
				break;
		}

		if(empty <= 0)
			game_over();

		if((empty != old_empty) || (move == 1)) 
		{ 
			int new_x, new_y;
			do{
				new_x = rand() % 4;
				new_y = rand() % 4;
			}while(a[new_y][new_x] != 0);

			cnt_value(&new_y, &new_x);
			
			int temp;
			do {
				temp = rand() % 4;
			}while(temp == 0 || temp == 2);

			a[new_y][new_x] = temp + 1;
			empty--;
		}

		draw();
	}
}

int cnt_one(int y, int x)
{
	int value = 0;

	if(y - 1 > 0)  
		a[y-1][x] ? 0 : ++value;
	if(y + 1 < 4)
		a[y+1][x] ? 0 : ++value;
	if(x - 1 >= 0)
		a[y][x-1] ? 0 : ++value;
	if(x + 1 < 4)
		a[y][x+1] ? 0 : ++value;
	if(y - 1 >= 0 && x - 1 >= 0)
		a[y-1][x-1] ? 0 : ++value;
	if(y - 1 >= 0 && x + 1 < 4)
		a[y-1][x+1] ? 0 : ++value;
	if(y + 1 < 4 && x - 1 >= 0)
		a[y+1][x-1] ? 0 : ++value;
	if(y + 1 < 4 && x + 1 < 4)
		a[y+1][x+1] ? 0 : ++value;

	return value;
}

void cnt_value(int *new_y, int *new_x)
{
	static int old_y, old_x;
	int max = cnt_one(*new_y, *new_x);

	for(int y = 0; y < 4; y++)
		for(int x = 0; x < 4; x++) 
		{
			if(!a[y][x]) 
			{
				int value = cnt_one(y, x);
				//优先选取周围空格最多的空格填充新数字，并避免在同一位置反复出现新数字
				if(value > max && old_y != y && old_x != x) 
				{
					*new_y = y;
					*new_x = x;
					old_x = x;
					old_y = y;
					break;
				}
			}
		}
}

void game_over()
{
	sleep(1);
	endwin();
	exit(0);
}

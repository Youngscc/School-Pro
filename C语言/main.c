/*Made By Youngsc*/

# include <windows.h>
# include <conio.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <windows.h>
# include <mmsystem.h>

int n, mid = 100, dif, opt, flag, score ,Eatsum ,mapID;
int bx[] = { 0,-1,1,0,0 }, by[] = { 0,0,0,-1,1 };
char s[55];

struct hh{
	int x,y,p,end;
	struct hh *pre,*next;
}che[110][110],*head;

void HideCursor(){
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor);
}

void gotoxy(int y, int x) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	HideCursor();
}

void music()
{
    PlaySound(TEXT(".\\aa.wav"),NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void color(int a) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
	/*
	字
	1 	深蓝色
	2 	深绿色
	3 	深青色
	4 	深红色
	5 	深粉色
	6	深黄色
	7 	深白色
	8 	灰色
	9 	浅蓝色
	10 	浅绿色
	11 	浅青色
	12	浅红色
	13	浅粉色
	14	浅黄色
	15	浅白色


	背景
	1~15		黑色
	16~31		深蓝色
	32~47		深绿色
	48~63		深青色
	64~79		深红色
	80~95		深粉色
	96~111		深黄色
	112~127 	深白色
	128~143 	灰色
	144~159 	浅蓝色
	160~175 	浅绿色
	176~191 	浅青色
	192~207 	浅红色
	208~223 	浅粉色
	224~239 	浅黄色
	240~255 	浅白色
	*/
}

int Get() {
	int res = 0;
	char ch;
	do {
		ch = _getch();
		switch (ch) {
		case 72: res = 1; break;
		case 80: res = 2; break;
		case 75: res = 3; break;
		case 77: res = 4; break;
		default: break;
		}
	} while (!res);
	return res;
}

void Out() {
	system("cls");
	for (int i = 0; i <= n+1; i++)
	{
		color(10);
		for (int j = 0; j <= n+1; j++)
		{

			switch(che[i][j].p)
			{
				case 1: color(10); printf("■"); break;
				case 2: color(4);  printf("●"); break;
				case 3: color(12); printf("◆"); break;
				case 4: color(4);  printf("○"); break;
				case 5: color(10); printf("□"); break;
			}
		}

		puts("");
	}
	puts("");
	printf("Your score : %d\n", score);
}

void Food() {
	int x, y;
	do {
		x = rand() % 13 + 1;
		y = rand() % 13 + 1;
	} while (che[x][y].p != 1);
	che[x][y].p = 3;
	gotoxy(x,y*2);
	color(12);
	printf("◆");
	return;
}

void make1(){
	puts("请输入地图的边长:");
	puts("（不要超过40，你的屏幕放不下）");
	scanf("%d", &n);
	system("cls");

	puts("输入一个数字(1~10)来设定游戏难度.");
	puts("数字越大，速度越慢");
	scanf("%d", &dif);
	while (dif<1||dif>10) printf("请输入范围内的难度值\n"),scanf("%d",&dif);
	system("cls");
	mid *= dif;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			che[i][j].p=1;
			che[i][j].x=i;
			che[i][j].y=j;
		}

	for (int i=0; i<=n+1; ++i) che[0][i].p = che[i][0].p = che[n+1][i].p = che[i][n+1].p = 5;
}

void make2(){
	n = 13;
	char mapname[15]={0};
	puts("我这儿里有8张地图，请问你想要第几张:");
	scanf("%d",&mapID);
	while (mapID<1||mapID>8) printf("请输入范围内的地图序号\n"),scanf("%d",&mapID);
	system("cls");

	puts("输入一个数字(1~10)来设定游戏难度.");
	puts("数字越大，速度越慢");
	scanf("%d", &dif);
	while (dif<1||dif>10) printf("请输入范围内的难度值\n"),scanf("%d",&dif);
	system("cls");
	mid *= dif;

	sprintf(mapname,"map%d.txt",mapID);
	freopen(mapname,"r",stdin);
	for (int i=0; i<=14; ++i)
		for (int j=0; j<=14; ++j)
			scanf("%d",&che[i][j].p),
			che[i][j].x = i,
			che[i][j].y = j;
	fclose(stdin);
}

void Be() {
	if (opt == 1) make1();
	else make2();

	int x,y;
	do {
		x = rand() % n + 1,
		y = rand() % n + 1;
	} while(che[x][y].p != 1);
	che[x][y].p = 2;
	che[x][y].end = 1;
	head = &che[x][y];
	flag = rand() % 4 + 1;
	do {
		x = head->x + bx[flag];
		y = head->y + by[flag];
		if (che[x][y].p == 1||che[x][y].p == 3) break;
		flag = (flag + 1) % 4;
		if (!flag) flag = 1;
	} while (1);

	Food();
	Out();
}

int Hashlist[1000010];

struct playersdata{
	int map[10];
	int relax;
	char name[55];
}playersmark[60];

unsigned int BKDRHash(char *str){
    unsigned int seed = 131;
    unsigned int hash = 0;

    while (*str)
    {
        hash = hash * seed + (*str++);
    }

    return (hash%1000007);
}

struct playersdata a[60];

void mysort1(int l,int r){
	if(l == r) return ;
	int m = (l+r)/2;
	mysort1(l,m), mysort1(m+1,r);
	int fa = l,fb = m+1,t = l-1;

	while(fa <= m&&fb <= r)
		if(playersmark[fa].relax > playersmark[fb].relax) a[++t] = playersmark[fa++];
		else a[++t] = playersmark[fb++];

	while(fa <= m) a[++t] = playersmark[fa++];
	while(fb <= r) a[++t] = playersmark[fb++];

	for(int i = l;i <= r;++i) playersmark[i] = a[i];
}

void mysort2(int l,int r,int mapID){
	if(l == r) return ;
	int m = (l+r)/2;
	mysort2(l,m,mapID), mysort2(m+1,r,mapID);
	int fa = l,fb = m+1,t = l-1;

	while(fa <= m&&fb <= r)
		if(playersmark[fa].map[mapID] > playersmark[fb].map[mapID]) a[++t] = playersmark[fa++];
		else a[++t] = playersmark[fb++];

	while(fa <= m) a[++t] = playersmark[fa++];
	while(fb <= r) a[++t] = playersmark[fb++];

	for(int i = l;i <= r;++i) playersmark[i] = a[i];
}

void print_rank(){
	int playersum,hashnum = BKDRHash(s);
	char playername[55]={0};
	freopen("players.txt","r",stdin);
	scanf("%d",&playersum);
	for (int i=1; i<=playersum; ++i)
	{
		scanf("%s",playername);
		int Hashn = BKDRHash(playername);
		Hashlist[Hashn] = i;
		memcpy(playersmark[i].name,playername,sizeof(playername));
		scanf("%d",&playersmark[i].relax);
		for (int j=1; j<=8; ++j) scanf("%d",&playersmark[i].map[j]);
	}
	fclose(stdin);
	int Hashn = BKDRHash(s), ID;
	if (!Hashlist[Hashn]) Hashlist[Hashn] = ++playersum;
	ID = Hashlist[Hashn];
	if (opt == 1) playersmark[ID].relax = score>playersmark[ID].relax? score:playersmark[ID].relax;
	else playersmark[ID].map[mapID] = score>playersmark[ID].map[mapID]? score:playersmark[ID].map[mapID];
	memcpy(playersmark[ID].name,s,sizeof(s));
	if (opt == 1) mysort1(1,playersum);
	else mysort2(1,playersum,mapID);
	printf("以下为该模式下该地图的所有玩家最高得分排行榜\n");
	printf("------战绩榜------\n");
	printf("       score    ID\n");
	for (int i=1; i<=playersum; ++i)
		printf("NO.%2d   %3d     %s\n",i, opt == 1? playersmark[i].relax:playersmark[i].map[mapID],playersmark[i].name);

	freopen("players.txt","w",stdout);
	printf("%d\n",playersum);
	for (int i=1; i<=playersum; ++i)
	{
		printf("%s\n%d ",playersmark[i].name,playersmark[i].relax);
		for (int j=1; j<=8; ++j) printf("%d ",playersmark[i].map[j]);
		printf("\n");
	}
	fclose(stdout);
}

void is_fail(int x, int y) {
	if (che[x][y].p != 1 && che[x][y].p != 3) {
		gotoxy(n+4,0);
		color(15);
		puts("Emnnnnnn......");
		puts("不好意思，你挂了。。。");
		print_rank();
		char c;
		while (c = getchar() && c != 'q');
		exit(0);
	}
	return;
}

void Eat(int x, int y) {
	score += 10 - dif + 1;
	Eatsum++;
	gotoxy(n+3,13);
	printf("%d         \n",score);
	che[x][y].p = 2;
	gotoxy(x,y*2);
	color(4);
	printf("●");
	head->p = 4;
	gotoxy(head->x,head->y*2);
	color(4);
	printf("○");
	head->next = &che[x][y];
	che[x][y].pre = head;
	head = &che[x][y];
	Food();
}

void Go(int x) {
	struct hh *to;
	to = &che[head->x+bx[x]][head->y+by[x]];
	is_fail(to->x,to->y);
	if (to->p == 3) Eat(to->x, to->y);
	else {
		head->next = to;
		to->pre = head;
		head->p = 4;
		gotoxy(head->x,head->y*2);
		color(4);
		printf("○");
		to->p = 2;
		gotoxy(to->x,to->y*2);
		color(4);
		printf("●");
		head = to;
		while (!to->end) {
			struct hh *now = to->pre;
			if (now->end) {
				now->p = 1;
				gotoxy(now->x,now->y*2);
				color(10);
				printf("■");
				now->end = 0;
				to->end = 1;
				break;
			}
			to = now;
		}
	}
	return;
}

void Move() {
	double l = clock();
	int tim = 1;
	while ((tim = (clock() - l < mid)) && !_kbhit());
	if (!tim) {
		Go(flag);
		return;
	}

	int want = Get();
	if (want == 1 && flag == 2) return;
	if (want == 2 && flag == 1) return;
	if (want == 3 && flag == 4) return;
	if (want == 4 && flag == 3) return;
	flag = want;
	Go(flag);
	return;
}

int main(){
	music();
	srand(time(0));

	printf("请创建你的ID，如已创建，请输入已有ID\n长度不超过50\n");
	scanf("%s",s);
	system("cls");
	printf("请选择游戏模式\n 1、休闲模式\n 2、街机模式\n(输入1或2点击回车即可)\n");
	scanf("%d",&opt);
	while (opt != 1&&opt != 2) printf("请输入1或2\n"),scanf("%d",&opt);
	system("cls");

	Be();

	while (1) Move();

	return 0;
}



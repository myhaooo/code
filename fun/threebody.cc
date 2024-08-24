#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;
int b,c;
int toint(float a){return ((int)(a*10+5))/10;}
void Setpos(float x,float y){COORD pos;pos.X=toint(y*2),pos.Y=toint(x);SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);}
void Color(int a)
{
	if(a%11==1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
    if(a%11==2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
    if(a%11==3) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
    if(a%11==4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);
	if(a%11==5) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);
    if(a%11==6) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
    if(a%11==7) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    if(a%11==7) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE);
    if(a%11==8) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
    if(a%11==9) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN);
    if(a%11==10) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);
    if(a==c) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
}
struct node
{
    float x,y,z;
    float vx,vy,vz;
    float r,m;
    bool life;
}Sun[1000001];
void Push(int a,int b)
{
    float Ax=Sun[a].x-Sun[b].x,Ay=Sun[a].y-Sun[b].y,Dis=sqrt(Ax*Ax+Ay*Ay)*1.0;
    if(Dis<=1) return;//??: Dis>=Sun[a].r||Dis>=Sun[b].r||

    float ac=Sun[a].m*Sun[b].m/(Dis*Dis)*1.0,afx,afy;
    if(abs(Ax)<=1) return;//afy=ac;
    else if(abs(Ay)<=1) return;//afx=ac;
    else
    {
        float d=abs(Ax/Ay*1.0);
        afy=sqrt(ac/(1+d*d))*1.0,afx=sqrt(ac/(1+d*d))*d*1.0;
    }
    if(Ax>0) afx*=-1;if(Ay>0) afy*=-1;
    Sun[a].vx+=afx/Sun[a].m*5.0;Sun[a].vy+=afy/Sun[a].m*5.0;
    Sun[b].vx-=afx/Sun[b].m*5.0;Sun[b].vy-=afy/Sun[b].m*5.0;
}
int T,More=10,Speed=50;
void Move()
{
    for(int i=1;i<=b;i++)
    {
        Setpos(Sun[i].x/More*1.0,Sun[i].y/More*1.0);printf(" ");
        Sun[i].x+=Sun[i].vx*More/10.0;Sun[i].y+=Sun[i].vy*More/10.0;
        if(Sun[i].x>=40*More) Sun[i].x=40*More,Sun[i].vx*=-0.5;
        if(Sun[i].x<=1) Sun[i].x=1,Sun[i].vx*=-0.5;
        if(Sun[i].y>=40*More) Sun[i].y=40*More,Sun[i].vy*=-0.5;
        if(Sun[i].y<=1) Sun[i].y=1,Sun[i].vy*=-0.5;
        Setpos(Sun[i].x/More*1.0,Sun[i].y/More*1.0);Color(i);
        if(i<=c) {
        	printf("O");
		}else {
			printf(".");
		}
    }
    for(int i=1;i<=b;i++)
    for(int j=i+1;j<=b;j++) Push(i,j);
}

float dist(float x1,float y1,float x2,float y2) {
	return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

int cooldown;

void planetState() {
	bool f=1;
	for(int i=1;i<=c-1;i++) {
		if(dist(Sun[i].x,Sun[i].y,Sun[c].x,Sun[c].y)<200) {
			f=0;
			break;
		}
	}
	if(f) {
		printf("极寒  ");
		return;
	}
	f=0;
	for(int i=1;i<=c-1;i++) {
		if(dist(Sun[i].x,Sun[i].y,Sun[c].x,Sun[c].y)<20) {
			f=1;
			break;
		}
	}
	if(f) {
		printf("大撕裂");
		if(cooldown>0) {
			return;
		}
		cooldown=10;
		if(Sun[b-1].m<0.01) {
			Sun[b-1].m*=0.8;
			return;
		}
		b++;
		Sun[b].x=Sun[b-1].x+rand()%2-0.5;
		Sun[b].y=Sun[b-1].y+rand()%2-0.5;
		Sun[b].vx=Sun[b-1].vx+rand()%2-0.5;
		Sun[b].vy=Sun[b-1].vy+rand()%2-0.5;
		Sun[b].m=Sun[b-1].m*0.2;
		Sun[b-1].m*=0.8;
		return;
	}
	f=1;
	float mind=1e9;
	int id=0;
	for(int i=1;i<=c-1;i++) {
		if(dist(Sun[i].x,Sun[i].y,Sun[c].x,Sun[c].y)<mind) {
			mind=dist(Sun[i].x,Sun[i].y,Sun[c].x,Sun[c].y);
			id=i;
		}
	}
	for(int i=1;i<=c-1;i++) {
		if(i==id) {
			continue;
		}
		if(dist(Sun[i].x,Sun[i].y,Sun[c].x,Sun[c].y)<mind*2.0) {
			f=0;
			break;
		}
	}
	if(f) {
		printf("恒纪元");
		return;
	}
	printf("乱纪元");
}

int main()
{
    system("mode con cols=82 lines=42");
    CONSOLE_CURSOR_INFO cursor_info={1,0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
    srand((unsigned)time(NULL));

//  ??????????(???????),???????,??????? 

    c=b=4;
    Sun[0].m=5000*pow(2,b);
    for(int i=1;i<=b-1;i++) {
    	Sun[i].x=rand()%400,Sun[i].y=rand()%400,Sun[i].vx=rand()%20-9.5,Sun[i].vy=rand()%20-9.5,Sun[i].m=Sun[i-1].m*0.8;
	}
	Sun[b].x=rand()%400,Sun[b].vx=rand()%20-9.5,Sun[b].vy=rand()%20-9.5,Sun[b].m=1;
    while(1)
    {
    	Setpos(3,5);
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    	printf("行星运行状态：");
    	planetState();
        T++;
        cooldown--;
        if(cooldown<0) {
        	cooldown=0;
		}
        Move();
        Sleep(Speed);
    }
}
#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>

using namespace std;

typedef struct Frame
{
    COORD position[2];
}Frame;

void Color(int a)
{
    //白 
    if(a==0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    //绿 
    if(a==1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
    //红 
    if(a==2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
    //蓝 
    if(a==3) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
    //粉
    if(a==4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE); 
    //黄
    if(a==5) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN); 
    //灰 
    if(a==6) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    //棕
    if(a==7) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN); 
    //随机
    if(a == -1) Color(rand() % 8); 
}

void SetPos(COORD a)// set cursor 
{
    HANDLE out=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(out, a);
}

void SetPos(int i, int j)// set cursor
{
    COORD pos={short(i), short(j)};
    SetPos(pos);
}

void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

char input()
{
    while(1)
    {
        if(_kbhit())
        {
            return _getch();
        }
    }
}

char input(int i, int j)
{
    while(1)
    {
        char x = input();
        if(x >= i && x <= j) return x;
    }
}

//在[a, b)之间产生一个随机整数
int random(int a, int b)
{
    int c=(rand() % (a-b))+ a;
    return c;
}

struct BLOCK
{
    int id;
    string txt;
    int color;
    int hard;
    int level; //挖掘等级(0=徒手 1=木 2=石 3=铁 4=钻石 5=合金) 
    string name;
    bool fluid; //是否为流体(可以穿越 能够替换成方块) 
};

BLOCK block[] = //方块 
{
{0, "□", 0, 2000000000, 100, "基岩", false}, 
{1, "■", 6, 250, 1, "石头", false}, 
{2, "▓ ", 7, 75, 0, "泥土", false}, 
{3, "▓ ", 6, 75, 0, "砂砾", false}, 
{4, "■", 5, 80, 0, "木头", false},
{5, "※", 0, 500, 2, "铁矿石", false}, 
{6, "∷", 0, 500, 2, "铁块", false}, 
{7, "※", 5, 600, 3, "金矿石", false}, 
{8, "∷", 5, 600, 3, "金块", false},
{9, "※", 3, 900, 3, "钻石矿石", false},
{10, "∷", 3, 900, 3, "钻石块", false}, 
{11, "▓ ", 1, 20, 0, "树叶", false},
{12, "■", 3, 2000000000, 100, "水", true},
{13, "□", 2, 2000000000, 100, "岩浆", true},
{14, "□", 0, 2000, 4, "真正的基岩", false},
{15, "■", 4, 45, 0, "地狱岩", false},
{16, "□", 4, 3000, 4, "远古残骸", false},
{17, "∷", 4, 3000, 4, "下界合金块", false},
{18, "■", 2, 2000000000, 100, "地幔", true},
{19, "  ", 0, 2000000000, 100, "空气", true},
{20, "●", 4, 3000, 3, "海洋之星", false},
{21, "□", 3, 2500, 3, "海能石", false},
{22, "※", 1, 1200, 3, "绿宝石矿石", false},
{23, "∷", 1, 1200, 3, "绿宝石块", false},
{24, "■", 7, 2400, 1, "神殿方块", false},
{25, "<>", 2, 6000, 2, "神殿核心", false},
{26, "于", 2, 10000, 1, "于苗晶体A", false},
{27, "苗", 2, 10000, 1, "于苗晶体B", false},
{28, "{}", 3, 7500, 1, "宝藏锚点", false},
{29, "■", 2, 1000, 0, "TNT", false},
{30, "■", 5, 1000, 0, "TNT", false},
{31, "■", 2, 1000, 0, "TNT", false},
{32, "■", 2, 1000, 0, "TNT", false},
{33, "■", 3, 80000, 2, "地牢石", false},
{34, "※", 3, 150000, 4, "魂石", false},
{35, "▓ ", 3, 2000000000, 100, "死水", true},
{36, "■", 5, 440, 2, "下界砖", false}
};

int block_max = 36;

struct ITEM
{
    int id;
    int hurt;
    int speed; //每个短刻的挖掘进度 
    int level;
    string name;
    int rare; //稀有度 白0<绿1<蓝2<紫3<幻4 
};

ITEM item[] = //物品 
{
{0, 0, 0, 0, "空气", 0},
{1, 2, 20, 1, "木镐", 0},
{2, 5, 0, 1, "木剑", 0},
{3, 3, 40, 2, "石镐", 0},
{4, 6, 0, 2, "石剑", 0}, 
{5, 0, 0, 0, "铁锭", 0},
{6, 4, 80, 3, "铁镐", 0},
{7, 9, 0, 3, "铁剑", 0},
{8, 0, 0, 0, "金锭", 1},
{9, 3, 30, 3, "金镐", 1},
{10, 6, 0, 3, "金剑", 1},
{11, 0, 0, 0, "钻石", 2},
{12, 5, 200, 4, "钻石镐", 2},
{13, 12, 0, 4, "钻石剑", 2},
{14, 0, 0, 0, "下界合金碎片", 3},
{15, 0, 0, 0, "下界合金锭", 3},
{16, 6, 900, 5, "下界合金镐", 3},
{17, 15, 0, 5, "下界合金剑", 3},
{18, 0, 0, 0, "桶", 0},
{19, 0, 0, 0, "水桶", 0},
{20, 0, 0, 0, "岩浆桶", 0},
{21, 0, 0, 0, "药水量子", 3},
{22, 0, 0, 0, "强化量子", 3},
{23, 0, 0, 0, "绿宝石", 2},
{24, 6, 150, 4, "绿宝石镐", 2},
{25, 11, 0, 4, "绿宝石剑", 2},
{26, 0, 100, 0, "海洋创造锤", 3},
{27, 0, 0, 0, "无尽核心", 4},
{28, 0, 0, 0, "宝藏探测器", 4},
{29, 0, 0, 0, "死水桶", 0},
{30, 0, 0, 0, "灵魂之星", 3},
{31, 6, 1600, 5, "灵魂镐", 3},
{32, 17, 0, 5, "灵魂剑", 3}
};

int item_max = 32;

struct ARMOR
{
    int id;
    int defease; //最高为20 可抵御(defease*4)%伤害
    string name;
};

ARMOR armor[] = //盔甲
{
{0, 0, "空"},
{1, 4, "木盔甲"},
{2, 8, "石盔甲"},
{3, 12, "铁盔甲"},
{4, 16, "钻石盔甲"},
{5, 20, "下界合金盔甲"}
};

struct BUFF
{
    int id;
    string name;
    int level; //等级 默认为0 1级以上显示在玩家属性页面中 
    int time; //单位: short_tick 降至0后等级降至0级 
};

BUFF buff[] = //效果
{
{0, "空", 0, 0},
{1, "生命提升", 0, 0},
{2, "急迫", 0, 0},
{3, "生命吸收", 0, 0},
{4, "中毒", 0, 0}
};

const int buff_max = 4;

string buff_str[] = //效果简介
{
"空效果",
"能够提升生命值 每级提升4点生命值",
"能够加快挖掘速度 每级提升25%挖掘速度",
"获得护盾 每级提升1点免伤值",
"负面效果 每级每个构造刻受到1点伤害"
};

int gamemode = 0; //0=生存 1=创造 2=极限 
int short_tick = 0, tick = 0; //短刻(每秒10次)和构造刻(每秒1次)
BLOCK world[2400][1200]; //地图 x0~2399 y0~1199
BLOCK fkl[5]; //方块栏
ITEM wpl[5]; //物品栏
ARMOR kjl = armor[0]; //盔甲栏 做出盔甲立即替换 
const int xgmax = 5; //可获得的效果总数 
BUFF xgl[xgmax]; //效果栏 
int xgnum; //已拥有BUFF 
int fknum[5], wpnum[5]; //数量(max:64) 
int now = 0; //目前手持方块/物品 0~4方块 5~9物品
int playerx = 1200, playery = 700; //冒险者 坐标
double health = 20; //生命 
double max_health = 20; //生命值上限 
int oxygen = 20; //氧气 
int energy = 0; //跳跃能量 
int wjjd = 0; //挖掘进度 
int zhuiluo = 0; //连续坠落格数 
int level = 0, xp = 0; //等级、经验 
bool tick_attack = false; //本tick是否受伤 

void print_data();
void input_data();

//地牢结构
int dilao_jiegou[27][29] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2},
{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 2, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 2},
{2, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 1, 1, 2, 3, 3, 2, 5, 5, 5, 5, 5, 5, 2, 3, 3, 3, 3, 2},
{2, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 1, 1, 2, 3, 3, 2, 5, 5, 5, 5, 5, 5, 2, 3, 3, 3, 3, 2},
{2, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 1, 1, 2, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 2},
{2, 3, 3, 3, 2, 2, 3, 3, 3, 2, 1, 1, 1, 2, 3, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2},
{2, 3, 3, 2, 3, 3, 2, 3, 3, 2, 1, 1, 1, 2, 3, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2},
{2, 3, 3, 2, 3, 3, 2, 3, 3, 2, 1, 1, 1, 2, 3, 3, 2, 3, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 2},
{2, 3, 3, 3, 2, 2, 3, 3, 3, 2, 1, 1, 1, 2, 2, 2, 2, 3, 2, 2, 3, 3, 3, 2, 2, 2, 2, 2, 2},
{2, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 1, 1, 1, 2, 2, 3, 3, 2, 2, 3, 3, 3, 2, 1, 1, 1, 1, 1},
{2, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 1, 1, 1, 1, 1},
{2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 3, 3, 2, 3, 3, 2, 3, 3, 2, 2, 2, 2, 2, 2},
{2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 2},
{1, 1, 2, 3, 3, 2, 1, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 2, 4, 4, 2, 3, 3, 3, 3, 3, 3, 3, 2},
{1, 1, 2, 3, 3, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2},
{1, 1, 2, 3, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 3, 3, 3, 3, 3, 2, 1, 1, 1, 1, 1, 1},
{1, 1, 2, 3, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1},
{1, 1, 2, 3, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 2, 3, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3, 2, 2, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3, 2, 2, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1}
};

//下界城市
//核心
int nc_core[9][9] = 
{
{0, 0, 0, 1, 2, 1, 0, 0, 0},
{0, 0, 1, 1, 2, 1, 1, 0, 0},
{0, 1, 1, 2, 2, 2, 1, 1, 0},
{1, 1, 2, 2, 2, 2, 2, 1, 1},
{2, 2, 2, 2, 2, 2, 2, 2, 2},
{1, 1, 2, 2, 2, 2, 2, 1, 1},
{0, 1, 1, 2, 2, 2, 1, 1, 0},
{0, 0, 1, 1, 2, 1, 1, 0, 0},
{0, 0, 0, 1, 2, 1, 0, 0, 0}
};
//水平廊道
int nc_cz_ld[9][9] = 
{
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 1, 1, 1},
{2, 2, 2, 2, 2, 2, 2, 2, 2},
{1, 1, 1, 1, 1, 1, 1, 1, 1},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0}
};
//垂直廊道
int nc_sp_ld[9][9] = 
{
{0, 0, 0, 1, 2, 1, 0, 0, 0},
{0, 0, 0, 1, 2, 1, 0, 0, 0},
{0, 0, 0, 1, 2, 1, 0, 0, 0},
{0, 0, 0, 1, 2, 1, 0, 0, 0},
{0, 0, 0, 1, 2, 1, 0, 0, 0},
{0, 0, 0, 1, 2, 1, 0, 0, 0},
{0, 0, 0, 1, 2, 1, 0, 0, 0},
{0, 0, 0, 1, 2, 1, 0, 0, 0},
{0, 0, 0, 1, 2, 1, 0, 0, 0}
};

void block_copy(int x, int y, int id) //将一个方块放置到某个坐标
{
    world[x][y].id = id;
    world[x][y].txt = block[id].txt;
    world[x][y].color = block[id].color;
    world[x][y].hard = block[id].hard;
    world[x][y].name = block[id].name;
    world[x][y].level = block[id].level;
    world[x][y].fluid = block[id].fluid;
}

void chengshi(int x, int y) //下界城市的生成
{
    queue<pair<pair<int, int>, int> > q;
    int size = 5;
    x /= 9;
    y /= 9;
    int nt = 1;
    q.push({{x, y}, 1});
    for(int i = 0;i < 9;i++)
            {
                for(int j = 0;j < 9;j++)
                {
                    if(nt == 1)
                    {
                        if(nc_core[i][j] == 2)
                        {
                            block_copy(x * 9 + i, y * 9 + j, 19);
                        }
                        else if(nc_core[i][j] == 0) ;
                        else block_copy(x * 9 + i, y * 9 + j, 36);
                    }
                    else if(nt == 2)
                    {
                        if(nc_sp_ld[i][j] == 2)
                        {
                            block_copy(x * 9 + i, y * 9 + j, 19);
                        }
                        else if(nc_sp_ld[i][j] == 0);
                        else block_copy(x * 9 + i, y * 9 + j, 36);
                    }
                    else if(nt == 3)
                    {
                        if(nc_cz_ld[i][j] == 2)
                        {
                            block_copy(x * 9 + i, y * 9 + j, 19);
                        }
                        else if(nc_cz_ld[i][j] == 0) ;
                        else block_copy(x * 9 + i, y * 9 + j, 36);
                    }

                }
            }
            nt = 2;
    q.push({{x - 1, y}, 2});
    for(int i = 0;i < 9;i++)
            {
                for(int j = 0;j < 9;j++)
                {
                    if(nt == 1)
                    {
                        if(nc_core[i][j] == 2)
                        {
                            block_copy(x * 9 - 9 + i, y * 9 + j, 19);
                        }
                        else if(nc_core[i][j] == 0);
                        else block_copy(x * 9 - 9 + i, y * 9 + j, 36);
                    }
                    else if(nt == 2)
                    {
                        if(nc_sp_ld[i][j] == 2)
                        {
                            block_copy(x * 9 - 9 + i, y * 9 + j, 19);
                        }
                        else if(nc_sp_ld[i][j] == 0);
                        else block_copy(x * 9 - 9 + i, y * 9 + j, 36);
                    }
                    else if(nt == 3)
                    {
                        if(nc_cz_ld[i][j] == 2)
                        {
                            block_copy(x * 9 - 9 + i, y * 9 + j, 19);
                        }
                        else if(nc_cz_ld[i][j] == 0) ;
                        else block_copy(x * 9 - 9 + i, y * 9 + j, 36);
                    }

                }
            }
    q.push({{x + 1, y}, 2});
    for(int i = 0;i < 9;i++)
            {
                for(int j = 0;j < 9;j++)
                {
                    if(nt == 1)
                    {
                        if(nc_core[i][j] == 2)
                        {
                            block_copy(x * 9 + 9 + i, y * 9 + j, 19);
                        }
                        else if(nc_core[i][j] == 0) ;
                        else block_copy(x * 9 + 9 + i, y * 9 + j, 36);
                    }
                    else if(nt == 2)
                    {
                        if(nc_sp_ld[i][j] == 2)
                        {
                            block_copy(x * 9 + 9 + i, y * 9 + j, 19);
                        }
                        else if(nc_sp_ld[i][j] == 0) ;
                        else block_copy(x * 9 + 9 + i, y * 9 + j, 36);
                    }
                    else if(nt == 3)
                    {
                        if(nc_cz_ld[i][j] == 2)
                        {
                            block_copy(x * 9 + 9 + i, y * 9 + j, 19);
                        }
                        else if(nc_cz_ld[i][j] == 0) ;
                        else block_copy(x * 9 + 9 + i, y * 9 + j, 36);
                    }

                }
            }
            nt = 3;
    q.push({{x, y - 1}, 3});
    for(int i = 0;i < 9;i++)
            {
                for(int j = 0;j < 9;j++)
                {
                    if(nt == 1)
                    {
                        if(nc_core[i][j] == 2)
                        {
                            block_copy(x * 9 + i, y * 9 - 9 + j, 19);
                        }
                        else if(nc_core[i][j] == 0) ;
                        else block_copy(x * 9 + i, y * 9 - 9 + j, 36);
                    }
                    else if(nt == 2)
                    {
                        if(nc_sp_ld[i][j] == 2)
                        {
                            block_copy(x * 9 + i, y * 9 - 9 + j, 19);
                        }
                        else if(nc_sp_ld[i][j] == 0) ;
                        else block_copy(x * 9 + i, y * 9 - 9 + j, 36);
                    }
                    else if(nt == 3)
                    {
                        if(nc_cz_ld[i][j] == 2)
                        {
                            block_copy(x * 9 + i, y * 9 - 9 + j, 19);
                        }
                        else if(nc_cz_ld[i][j] == 0) ;
                        else block_copy(x * 9 + i, y * 9 - 9 + j, 36);
                    }
                }
            }
    q.push({{x, y + 1}, 3});
    for(int i = 0;i < 9;i++)
            {
                for(int j = 0;j < 9;j++)
                {
                    if(nt == 1)
                    {
                        if(nc_core[i][j] == 2)
                        {
                            block_copy(x * 9 + i, y * 9 + 9 + j, 19);
                        }
                        else if(nc_core[i][j] == 0);
                        else block_copy(x * 9 + i, y * 9 + 9 + j, 36);
                    }
                    else if(nt == 2)
                    {
                        if(nc_sp_ld[i][j] == 2)
                        {
                            block_copy(x * 9 + i, y * 9 + 9 + j, 19);
                        }
                        else if(nc_sp_ld[i][j] == 0) ;
                        else block_copy(x * 9 + i, y * 9 + 9 + j, 36);
                    }
                    else if(nt == 3)
                    {
                        if(nc_cz_ld[i][j] == 2)
                        {
                            block_copy(x * 9 + i, y * 9 + 9 + j, 19);
                        }
                        else if(nc_cz_ld[i][j] == 0) ;
                        else block_copy(x * 9 + i, y * 9 + 9 + j, 36);
                    }

                }
            }
    while(!q.empty() && size < 24)
    {
        int nx = q.front().first.first;
        int ny = q.front().first.second;
        int nt = q.front().second;
        q.pop();
        if(rand() % 3 <= 1 && nt != 3)
        {
            q.push({{nx - 1, ny}, 2});
            size++;
            for(int i = 0;i < 9;i++)
            {
                for(int j = 0;j < 9;j++)
                {
                    if(nt == 1)
                    {
                        if(nc_core[i][j] == 2)
                        {
                            block_copy(nx * 9 + i, ny * 9 + j, 19);
                        }
                        else if(nc_core[i][j] == 0) continue;
                        else block_copy(nx * 9 + i, ny * 9 + j, 36);
                    }
                    else if(nt == 2)
                    {
                        if(nc_sp_ld[i][j] == 2)
                        {
                            block_copy(nx * 9 + i, ny * 9 + j, 19);
                        }
                        else if(nc_sp_ld[i][j] == 0) continue;
                        else block_copy(nx * 9 + i, ny * 9 + j, 36);
                    }
                    else if(nt == 3)
                    {
                        if(nc_cz_ld[i][j] == 2)
                        {
                            block_copy(nx * 9 + i, ny * 9 + j, 19);
                        }
                        else if(nc_cz_ld[i][j] == 0) continue;
                        else block_copy(nx * 9 + i, ny * 9 + j, 36);
                    }

                }
            }
        }
        if(rand() % 3 <= 1 && nt != 3)
        {
            q.push({{nx + 1, ny}, 2});
            size++;
            for(int i = 0;i < 9;i++)
            {
                for(int j = 0;j < 9;j++)
                {
                    if(nt == 1)
                    {
                        if(nc_core[i][j] == 2)
                        {
                            block_copy(nx * 9 + i, ny * 9 + j, 19);
                        }
                        else if(nc_core[i][j] == 0) continue;
                        else block_copy(nx * 9 + i, ny * 9 + j, 36);
                    }
                    else if(nt == 2)
                    {
                        if(nc_sp_ld[i][j] == 2)
                        {
                            block_copy(nx * 9 + i, ny * 9 + j, 19);
                        }
                        else if(nc_sp_ld[i][j] == 0) continue;
                        else block_copy(nx * 9 + i, ny * 9 + j, 36);
                    }
                    else if(nt == 3)
                    {
                        if(nc_cz_ld[i][j] == 2)
                        {
                            block_copy(nx * 9 + i, ny * 9 + j, 19);
                        }
                        else if(nc_cz_ld[i][j] == 0) continue;
                        else block_copy(nx * 9 + i, ny * 9 + j, 36);
                    }

                }
            }
        }
        if(rand() % 3 <= 1 && nt != 2)
        {
            q.push({{nx, ny - 1}, 3});
            size++;
            for(int i = 0;i < 9;i++)
            {
                for(int j = 0;j < 9;j++)
                {
                    if(nt == 1)
                    {
                        if(nc_core[i][j] == 2)
                        {
                            block_copy(nx * 9 + i, ny * 9 + j, 19);
                        }
                        else if(nc_core[i][j] == 0) continue;
                        else block_copy(nx * 9 + i, ny * 9 + j, 36);
                    }
                    else if(nt == 2)
                    {
                        if(nc_sp_ld[i][j] == 2)
                        {
                            block_copy(nx * 9 + i, ny * 9 + j, 19);
                        }
                        else if(nc_sp_ld[i][j] == 0) continue;
                        else block_copy(nx * 9 + i, ny * 9 + j, 36);
                    }
                    else if(nt == 3)
                    {
                        if(nc_cz_ld[i][j] == 2)
                        {
                            block_copy(nx * 9 + i, ny * 9 + j, 19);
                        }
                        else if(nc_cz_ld[i][j] == 0) continue;
                        else block_copy(nx * 9 + i, ny * 9 + j, 36);
                    }

                }
            }
        }
        if(rand() % 3 <= 1 && nt != 2)
        {
            q.push({{nx, ny + 1}, 3});
            size++;
            for(int i = 0;i < 9;i++)
            {
                for(int j = 0;j < 9;j++)
                {
                    if(nt == 1)
                    {
                        if(nc_core[i][j] == 2)
                        {
                            block_copy(nx * 9 + i, ny * 9 + j, 19);
                        }
                        else if(nc_core[i][j] == 0) continue;
                        else block_copy(nx * 9 + i, ny * 9 + j, 36);
                    }
                    else if(nt == 2)
                    {
                        if(nc_sp_ld[i][j] == 2)
                        {
                            block_copy(nx * 9 + i, ny * 9 + j, 19);
                        }
                        else if(nc_sp_ld[i][j] == 0) continue;
                        else block_copy(nx * 9 + i, ny * 9 + j, 36);
                    }
                    else if(nt == 3)
                    {
                        if(nc_cz_ld[i][j] == 2)
                        {
                            block_copy(nx * 9 + i, ny * 9 + j, 19);
                        }
                        else if(nc_cz_ld[i][j] == 0) continue;
                        else block_copy(nx * 9 + i, ny * 9 + j, 36);
                    }

                }
            }
        }
        if(rand() % 3 <= 1 && nt != 1)
        {
            q.push({{nx + random(-1, 2), ny + random(-1, 2)}, 1});
            size++;
            for(int i = 0;i < 9;i++)
            {
                for(int j = 0;j < 9;j++)
                {
                    if(nt == 1)
                    {
                        if(nc_core[i][j] == 2)
                        {
                            block_copy(nx * 9 + i, ny * 9 + j, 19);
                        }
                        else if(nc_core[i][j] == 0) continue;
                        else block_copy(nx * 9 + i, ny * 9 + j, 36);
                    }
                    else if(nt == 2)
                    {
                        if(nc_sp_ld[i][j] == 2)
                        {
                            block_copy(nx * 9 + i, ny * 9 + j, 19);
                        }
                        else if(nc_sp_ld[i][j] == 0) continue;
                        else block_copy(nx * 9 + i, ny * 9 + j, 36);
                    }
                    else if(nt == 3)
                    {
                        if(nc_cz_ld[i][j] == 2)
                        {
                            block_copy(nx * 9 + i, ny * 9 + j, 19);
                        }
                        else if(nc_cz_ld[i][j] == 0) continue;
                        else block_copy(nx * 9 + i, ny * 9 + j, 36);
                    }

                }
            }
        }
    }
}

void init() //生成世界 
{
    cout << "2%" << endl;
    for(int x = 0;x < 2400;x++) //填充空气 
    {
        for(int y = 0;y < 1200;y++) block_copy(x, y, 19);
    }
    cout << "4%" << endl;
    for(int y = 1;y < 1200;y++) //边界 
    {
        for(int x = 0;x <= 198;x++) block_copy(x, y, 18);
        for(int x = 2301;x <= 2399;x++) block_copy(x, y, 18);
        block_copy(199, y, 0);
        block_copy(2300, y, 0);
    }
    cout << "6%" << endl;
    int stgd[2400]; //石头高度(海平面700) 
    //生成主世界构造
    //确认x坐标下石头高度 (第一次构造)
    stgd[1200] = 200; //默认值 
    for(int x = 1199;x >= 200;x--)
    {
        if(random(0, 1000) <= 500)
        {
            stgd[x] = stgd[x + 1] - random(0, 2) + random(0, 2); //小变动 
        }
        else if(random(0, 1000) <= 100)
        {
            int add = random(0, 20);
            add -= 10;
            stgd[x] = stgd[x + 1] + add; //断崖式变动 
        }
        else
        {
            stgd[x] = stgd[x + 1]; //无变动 
        }
        if(stgd[x] > 210) stgd[x] = 210; 
        if(stgd[x] < 160) stgd[x] = 160;
    }
    cout << "12%" << endl;
    for(int x = 1201;x < 2300;x++)
    {
        if(random(0, 1000) <= 500)
        {
            stgd[x] = stgd[x - 1] - random(0, 2) + random(0, 2);
        }
        else if(random(0, 1000) <= 100)
        {
            int add = random(0, 20);
            add -= 10;
            stgd[x] = stgd[x - 1] + add; 
        }
        else
        {
            stgd[x] = stgd[x - 1];
        }
        if(stgd[x] > 220) stgd[x] = 220;
        if(stgd[x] < 160) stgd[x] = 160;
    }
    cout << "15%" << endl;
    //拷贝石头(主世界下边界:y=501)
    for(int x = 200;x < 2300;x++)
    {
        for(int y = 501;y <= 501 + stgd[x];y++)
        {
            block_copy(x, y, 1);
            //生成铁矿和金矿 
            if(random(1, 10000) <= 100)
            {
                block_copy(x, y, 5);
            }
            else if(random(1, 10000) <= 300)
            {
                block_copy(x, y, 7);
            }

            //生成钻石 
            if(y <= 515 && random(1, 10000) <= 50)
            {
                block_copy(x, y, 9);
            }

            //生成绿宝石
            if(y <= 600 && random(1, 10000) <= 75)
            {
                block_copy(x, y, 22);
            }

            //生成岩浆
            if(y <= 580 && random(1, 10000) <= 100)
            {
                block_copy(x, y, 13);
            }
        }
    }
    cout << "20%" << endl;
    //增加海水(第二次构造)
    for(int x = 200;x < 2300;x++)
    {
        for(int y = 501 + stgd[x] + 1;y <= 700;y++)
        {
            block_copy(x, y, 12);
        }
    }
    cout << "23%" << endl;
    for(int x = 200;x < 2300;x++)
    {
        for(int y = 501 + stgd[x] + 1;y <= 700;y++)
        {
            if(world[x][y].id != 12) continue;
            //海之环生成 
            bool flag = true;
            for(int xx = x - 3;xx <= x + 5;xx++)
            {
                for(int yy = y - 3;yy <= y + 5;yy++)
                {
                    if(world[xx][yy].id != 12) flag = false;
                }
            }
            if(flag && random(1, 10000) < 6) //符合条件
            {
                bool haizhihuan[9][9] = 
                {
                {0, 0, 1, 1, 1, 1, 1, 0, 0},
                {0, 1, 1, 0, 0, 0, 1, 1, 0},
                {1, 1, 0, 0, 1, 0, 0, 1, 1},
                {1, 0, 0, 1, 0, 1, 0, 0, 1},
                {1, 0, 1, 0, 1, 0, 1, 0, 1},
                {1, 0, 0, 1, 0, 1, 0, 0, 1},
                {1, 1, 0, 0, 1, 0, 0, 1, 1},
                {0, 1, 1, 0, 0, 0, 1, 1, 0},
                {0, 0, 1, 1, 1, 1, 1, 0, 0}};
                for(int i = x - 5;i <= x + 5;i++)
                {
                    for(int j = y - 5;j <= y + 5;j++)
                    {
                        if(haizhihuan[i - (x - 5)][j - (y - 5)] == 1)
                        {
                            block_copy(i, j, 21);
                        }
                    }
                }
                block_copy(x, y, 20);
            }
        }
    }
    cout << "27%" << endl;
    //最上3层为泥土 
    for(int x = 200;x < 2300;x++)
    {
        int dian = random(1, 10000);
        int tree = random(1, 10000);
        block_copy(x, 501 + stgd[x], 2);
        block_copy(x, 501 + stgd[x] + 1, 2);
        block_copy(x, 501 + stgd[x] + 2, 2);
        //生成树
        if(tree <= 250)
        {
            block_copy(x, 501 + stgd[x] + 2, 4);
            block_copy(x, 501 + stgd[x] + 3, 4);
            block_copy(x, 501 + stgd[x] + 4, 4);
            block_copy(x - 1, 501 + stgd[x] + 4, 11);
            block_copy(x + 1, 501 + stgd[x] + 4, 11);
            block_copy(x, 501 + stgd[x] + 5, 11);
            block_copy(x - 1, 501 + stgd[x] + 5, 11);
            block_copy(x + 1, 501 + stgd[x] + 5, 11);
            block_copy(x, 501 + stgd[x] + 6, 11);
         } 
        //生成高树
        else if(tree <= 310)
        {
            block_copy(x, 501 + stgd[x] + 2, 4);
            block_copy(x, 501 + stgd[x] + 3, 4);
            block_copy(x, 501 + stgd[x] + 4, 4);
            block_copy(x, 501 + stgd[x] + 5, 4);
            block_copy(x - 1, 501 + stgd[x] + 4, 4);
            block_copy(x + 1, 501 + stgd[x] + 4, 4);
            block_copy(x - 2, 501 + stgd[x] + 5, 4);
            block_copy(x + 2, 501 + stgd[x] + 5, 4);
            block_copy(x - 2, 501 + stgd[x] + 6, 11);
            block_copy(x + 2, 501 + stgd[x] + 6, 11);
            block_copy(x - 2, 501 + stgd[x] + 4, 11);
            block_copy(x + 2, 501 + stgd[x] + 4, 11);
            block_copy(x, 501 + stgd[x] + 6, 11);
            block_copy(x - 1, 501 + stgd[x] + 5, 11);
            block_copy(x + 1, 501 + stgd[x] + 5, 11);
            block_copy(x - 1, 501 + stgd[x] + 6, 11);
            block_copy(x + 1, 501 + stgd[x] + 6, 11);
            block_copy(x, 501 + stgd[x] + 6, 11);
            block_copy(x, 501 + stgd[x] + 7, 11);
            block_copy(x - 1, 501 + stgd[x] + 7, 11);
            block_copy(x + 1, 501 + stgd[x] + 7, 11);
        }
        //生成入云树
        else if(tree <= 340)
        {
            for(int i = 501 + stgd[x] + 2;i <= 501 + stgd[x] + (rand()%10) + 6;i++)
            {
                block_copy(x, i, 4);
                if(i >= 501 + stgd[x] + 4)
                {
                    block_copy(x - 1, i, 11);
                    block_copy(x + 1, i, 11);
                }
                block_copy(x, i + 1, 11);
            }
        }
        //生成巨树
        else if(tree <= 370)
        {
            block_copy(x, 501 + stgd[x] + 2, 4);
            block_copy(x - 1, 501 + stgd[x] + 2, 4);
            block_copy(x + 1, 501 + stgd[x] + 2, 4);
            block_copy(x, 501 + stgd[x] + 3, 4);
            block_copy(x - 1, 501 + stgd[x] + 3, 4);
            block_copy(x + 1, 501 + stgd[x] + 3, 4);
            block_copy(x, 501 + stgd[x] + 4, 4);
            block_copy(x - 1, 501 + stgd[x] + 4, 4);
            block_copy(x + 1, 501 + stgd[x] + 4, 4);
            block_copy(x, 501 + stgd[x] + 5, 4);
            block_copy(x - 1, 501 + stgd[x] + 5, 4);
            block_copy(x + 1, 501 + stgd[x] + 5, 4);
            block_copy(x - 2, 501 + stgd[x] + 4, 11);
            block_copy(x + 2, 501 + stgd[x] + 4, 11);
            block_copy(x - 2, 501 + stgd[x] + 5, 11);
            block_copy(x + 2, 501 + stgd[x] + 5, 11);
            block_copy(x - 2, 501 + stgd[x] + 6, 11);
            block_copy(x + 2, 501 + stgd[x] + 6, 11);
            block_copy(x - 1, 501 + stgd[x] + 6, 11);
            block_copy(x + 1, 501 + stgd[x] + 6, 11);
            block_copy(x, 501 + stgd[x] + 6, 11);
            block_copy(x, 501 + stgd[x] + 7, 11);
            block_copy(x - 1, 501 + stgd[x] + 7, 11);
            block_copy(x + 1, 501 + stgd[x] + 7, 11);
        }

        //生成于苗神殿
        else if(tree <= 405)
        {
            int y = 501 + stgd[x] + 3;

            block_copy(x, y, 24);
            block_copy(x - 1, y, 24);
            block_copy(x + 1, y, 24);
            block_copy(x - 2, y, 24);
            block_copy(x + 2, y, 24);
            block_copy(x - 3, y, 24);
            block_copy(x + 3, y, 24);
            block_copy(x - 3, y + 1, 24);
            block_copy(x + 3, y + 1, 24);
            block_copy(x - 3, y + 2, 24);
            block_copy(x + 3, y + 2, 24);
            block_copy(x - 3, y + 3, 24);
            block_copy(x + 3, y + 3, 24);
            block_copy(x - 3, y + 4, 24);
            block_copy(x + 3, y + 4, 24);
            block_copy(x - 3, y + 5, 24);
            block_copy(x + 3, y + 5, 24);
            block_copy(x - 3, y + 6, 24);
            block_copy(x + 3, y + 6, 24);
            block_copy(x - 2, y + 6, 24);
            block_copy(x + 2, y + 6, 24);
            block_copy(x - 1, y + 6, 24);
            block_copy(x + 1, y + 6, 24);
            block_copy(x, y + 6, 24);
            block_copy(x - 2, y + 6, 24);
            block_copy(x + 2, y + 6, 24);
            block_copy(x - 2, y + 7, 24);
            block_copy(x + 2, y + 7, 24);
            block_copy(x - 1, y + 7, 26);
            block_copy(x + 1, y + 7, 27);
            block_copy(x - 2, y + 8, 24);
            block_copy(x + 2, y + 8, 24);
            block_copy(x - 1, y + 9, 24);
            block_copy(x + 1, y + 9, 24);
            block_copy(x, y + 9, 25);
            block_copy(x - 1, y + 10, 24);
            block_copy(x + 1, y + 10, 24);
            block_copy(x, y + 10, 24);
        }
        //生成地牢 
        else if(tree <= 415 || x == 1200)
        {
            int t_high = rand() % 20 + 60;
            for(int i = 0;i < 27;i++)
            {
                for(int j = 0;j < 29;j++)
                {
                    int fangkuaiid = 0;
                    if(dilao_jiegou[i][j] == 1) continue;
                    else if(dilao_jiegou[i][j] == 2) fangkuaiid = 33;
                    else if(dilao_jiegou[i][j] == 3) fangkuaiid = 19;
                    else if(dilao_jiegou[i][j] == 5) fangkuaiid = 35;
                    else fangkuaiid = 34;
                    block_copy( x - 14 + j, 501 + stgd[x] + 3 - (t_high) + i, fangkuaiid);
                }
            }
        }
    }
    cout << "30%" << endl;
    for(int x = 200;x < 2300;x++)
    {
        int gaodu = max(741, 501 + stgd[x]);
        for(int y = gaodu + 15;y <= gaodu + 20;y++)
        {
            if(rand() % 20000 < 1)
            {
                //生成宝藏岛
                block_copy(x, y, 1);
                for(int z = x - 2;z <= x + 2;z++) block_copy(z, y + 1, 1);
                for(int z = x - 3;z <= x + 3;z++) block_copy(z, y + 2, 1);
                for(int z = x - 4;z <= x + 4;z++) block_copy(z, y + 3, 1);
                for(int z = x - 5;z <= x + 5;z++) block_copy(z, y + 4, 1);
                block_copy(x - 2, y + 5, 9);
                block_copy(x + 2, y + 5, 9);
                block_copy(x - 2, y + 6, 7);
                block_copy(x + 2, y + 6, 7);
                block_copy(x - 2, y + 7, 5);
                block_copy(x + 2, y + 7, 5);
                block_copy(x - 1, y + 8, 22);
                block_copy(x + 1, y + 8, 22);
                block_copy(x, y + 6, 16);
                block_copy(x, y + 10, 28); 
                break;
            }
        }
    }
    cout << "34%" << endl;
    for(int x = 200;x < 2300;x++)
    {
        block_copy(x, 500, 14);
        block_copy(x, 499, 14);
        block_copy(x, 498, 14);
        block_copy(x, 497, 14);
    }
    cout << "36%" << endl;
    for(int x = 200;x < 2300;x++)
    {
        for(int y = 496;y >= 100;y--)
        {
            block_copy(x, y, 15);
            if(random(0, 10000) <= 60)
            {
                bool flag = false;
                if(random(0, 10000) <= 1000) flag = true;
                int r = random(2, 4);
                for(int xx = x - r;xx <= x + r;xx++)
                {
                    for(int yy = y - r;yy <= y + r;yy++)
                    {
                        block_copy(xx, yy, 19);
                        if(yy == y - r)
                        {
                            if(flag) block_copy(xx, yy, 13);
                        }
                    }
                }
            }
            //添加岩浆
            if(random(0, 10000) <= 1000) block_copy(x, y, 13);
            //远古残骸
            if(random(0, 10000) <= 10) block_copy(x, y, 16);
        }
    }
    cout << "42%" << endl;
    for(int x = 200;x < 2300;x++)
    {
        for(int y = 496;y >= 100;y--)
        {
            //下界城市
            if(random(1, 10000) == 1 || (x == 1200 && y == 400))
            {
                if(random(1, 100) == 1 || (x == 1200 && y == 400))
                {
                    chengshi(x, y);
                }
             } 
        }
    }
    playery = 501 + stgd[1200] + 3;
}

void block_pick(BLOCK blk)
{
    for(int i = 0;i < 5;i++)
    {
        if(fkl[i].id == blk.id && blk.id != 0 && fknum[i] < 64)
        {
            fkl[i].id = blk.id;
            fkl[i].name = blk.name;
            fkl[i].txt = blk.txt;
            fkl[i].hard = blk.hard;
            fkl[i].level = blk.level;
            fkl[i].fluid = blk.fluid;
            fkl[i].color = blk.color;
            fknum[i]++;
            return;
        }
    }
    for(int i = 0;i < 5;i++)
    {
        if(fknum[i] <= 0)
        {
            fkl[i].id = blk.id;
            fkl[i].name = blk.name;
            fkl[i].txt = blk.txt;
            fkl[i].hard = blk.hard;
            fkl[i].level = blk.level;
            fkl[i].fluid = blk.fluid;
            fkl[i].color = blk.color;
            fknum[i] = 1;
            return;
        }
    }
}

void block_delete(BLOCK blk)
{
    for(int i = 0;i < 5;i++)
    {
        if(fkl[i].id == blk.id && fkl[i].txt == blk.txt)
        {
            fknum[i]--;
            if(fknum[i] == 0)
            {
                fkl[i].id = 0;
                fkl[i].name = "";
                fkl[i].txt = "";
                fkl[i].hard = 0;
                fkl[i].level = 0;
                fkl[i].fluid = 0;
                fkl[i].color = 0;
            }
            return;
        }
    }
}

int block_num(BLOCK blk)
{
    int num = 0;
    for(int i = 0;i < 5;i++)
    {
        if(fkl[i].id == blk.id && fkl[i].txt == blk.txt)
        {
            num += fknum[i];
        }
    }
    return num;
}

void item_pick(ITEM itm)
{
    for(int i = 0;i < 5;i++)
    {
        if(wpl[i].id == itm.id && itm.id != 0 && wpnum[i] < 64)
        {
            wpl[i].id = itm.id;
            wpl[i].hurt = itm.hurt;
            wpl[i].level = itm.level;
            wpl[i].name = itm.name;
            wpl[i].speed = itm.speed;
            wpl[i].rare = itm.rare;
            wpnum[i]++;
            return;
        }
    }
    for(int i = 0;i < 5;i++)
    {
        if(wpnum[i] <= 0)
        {
            wpl[i].id = itm.id;
            wpl[i].hurt = itm.hurt;
            wpl[i].level = itm.level;
            wpl[i].name = itm.name;
            wpl[i].speed = itm.speed;
            wpl[i].rare = itm.rare;
            wpnum[i] = 1;
            return;
        }
    }
}

void item_delete(ITEM itm)
{
    for(int i = 0;i < 5;i++)
    {
        if(wpl[i].id == itm.id && wpl[i].name == itm.name)
        {
            wpnum[i]--;
            if(wpnum[i] == 0)
            {
                wpl[i].id = 0;
                wpl[i].hurt = 0;
                wpl[i].speed = 0;
                wpl[i].level = 0;
                wpl[i].name = "";
                wpl[i].rare = 0;
            }
            return;
        }
    }
}

int item_num(ITEM itm)
{
    int num = 0;
    for(int i = 0;i < 5;i++)
    {
        if(wpl[i].id == itm.id && wpl[i].name == itm.name)
        {
            num += wpnum[i];
        }
    }
    return num;
}

void armor_delete()
{
    kjl.id = 0;
    kjl.defease = 0;
    kjl.name = "空";
}

void armor_pick(ARMOR arm)
{
    kjl.id = arm.id;
    kjl.defease = arm.defease;
    kjl.name = arm.name;
}

void buff_give(BUFF bff, int level, int time)
{
    if(bff.id == 0) return;
    if(xgnum == xgmax) return;
    xgl[xgnum].id = bff.id;
    xgl[xgnum].level = level;
    xgl[xgnum].name = bff.name;
    xgl[xgnum++].time = time;
}

void buff_delete(BUFF bff)
{
    if(bff.id == 0) return;
    for(int i = 0;i < xgnum;i++)
    {
        if(xgl[i].id == bff.id)
        {
            xgl[i].id = 0;
            xgl[i].level = 0;
            xgl[i].name = "空";
            xgl[i].time = 0;
        }
    }
}

int get_buff_level(BUFF bff)
{
    int mx = 0;
    if(bff.id == 0) return 0;
    for(int i = 0;i < xgnum;i++)
    {
        if(xgl[i].id == bff.id) mx = max(mx, xgl[i].level);
    }
    return mx;
}

void buff_merge() //效果合并(每短刻进行)
{
    for(int i = 0;i < xgnum;i++)
    {
        for(int j = i + 1;j < xgnum;j++)
        {
            if(xgl[i].id == xgl[j].id && xgl[i].id != 0)
            {
                xgl[i].level = max(xgl[i].level, xgl[j].level);
                xgl[i].time = xgl[i].time + xgl[j].time;
                xgl[j].id = 0;
                xgl[j].level = 0;
                xgl[j].name = "空";
                xgl[j].time = 0;
                xgnum--;
                //迁移效果
                for(int k = j + 1;k < xgnum + 1;k++)
                {
                    xgl[k - 1].level = xgl[k].level;
                    xgl[k - 1].id = xgl[k].id;
                    xgl[k - 1].time = xgl[k].time;
                    xgl[k - 1].name = xgl[k].name;
                    xgl[k].id = 0;
                    xgl[k].level = 0;
                    xgl[k].name = "空";
                    xgl[k].time = 0;
                }
            }
        }
    }
}

void buff_live()
{
    for(int i = 0;i < xgnum;i++)
    {
        if(xgl[i].id != 0)
        {
            xgl[i].time--;
            if(xgl[i].time <= 0)
            {
                xgl[i].id = 0;
                xgl[i].level = 0;
                xgl[i].name = "空";
                xgl[i].time = 0;
            }
        }
    }
}

void attack(int hurt_num, string die_str) //造成伤害 
{
    if(gamemode == 1) return;
    double hurt;
    hurt = hurt_num * (1.0 - (kjl.defease) * 0.04);
    //对高伤害进行削弱 
    int i = 0;
    double shjm = 0.0;
    for(int xxx = 0;xxx <= kjl.defease;xxx++)
    {
        shjm += 0.012 * (1.0 - (xxx * 0.04));
    }
    if(hurt >= 150)
    {   
        hurt = 150 + sqrt(hurt - 150);
    }
    hurt -= hurt * 0.1 + shjm;
    if(get_buff_level(buff[3]) > 0) hurt -= get_buff_level(buff[3]); //生命吸收 
    health -= hurt;
    tick_attack = true;
    if(health < 0 && gamemode == 2) //玩家死亡 极限模式=删除存档 
    {
        system("cls");
        SetPos(2, 2);
        cout << "GAME OVER";
        SetPos(2, 4);
        cout << die_str;
        SetPos(2, 6);
        cout << "极限模式下 你必须删除存档";
        init();
        print_data();
        SetPos(2, 8);
        system("pause");
        exit(0);
    }
    else if(health < 0 && gamemode == 0) //玩家死亡 生存模式=复活
    {
        system("cls");
        SetPos(2, 2);
        cout << "GAME OVER";
        SetPos(2, 4);
        cout << die_str;
        SetPos(2, 6);
        cout << "重生";
        SetPos(2, 8);
        system("pause");
        playerx = 1200;
        playery = 700;
        block_copy(playerx, playery, 19);
        health = max_health + get_buff_level(buff[1]) * 4;
        return;
    }
}

void input_data() //输入数据
{
    ifstream fin("data.txt", ios::in); 
    for(int i = 0;i < 2400;i++)
    {
        for(int j = 0;j < 1200;j++)
        {
            int ijid;
            fin >> ijid;
            block_copy(i, j, ijid);
        }
    }
    fin >> playerx >> playery;
    for(int i = 0;i < 5;i++) fin >> fknum[i] >> wpnum[i];
    for(int i = 0;i < 5;i++)
    {
        int fkid, wpid;
        fin >> fkid >> wpid;
        if(fkid != 0)
        {
            fkl[i].id = fkid;
            fkl[i].fluid = block[fkid].fluid;
            fkl[i].color = block[fkid].color;
            fkl[i].hard = block[fkid].hard;
            fkl[i].level = block[fkid].level;
            fkl[i].txt = block[fkid].txt;
            fkl[i].name = block[fkid].name;
        }
        else fknum[i] = 0;
        if(wpid != 0)
        {
            wpl[i].id = wpid;
            wpl[i].name = item[wpid].name;
            wpl[i].speed = item[wpid].speed;
            wpl[i].hurt = item[wpid].hurt;
            wpl[i].level = item[wpid].level;
            wpl[i].rare = item[wpid].rare;
        }
        else wpnum[i] = 0;
    }
    int zbid;
    fin >> zbid;
    armor_pick(armor[zbid]);
    fin >> xgnum;
    for(int i = 0;i < xgnum;i++)
    {
        int xgid, xgtm, xglv;
        fin >> xgid >> xgtm >> xglv;
        xgl[i].id = xgid;
        xgl[i].time = xgtm;
        xgl[i].name = buff[xgid].name;
        xgl[i].level = xglv;
    }
    fin >> health >> oxygen;
    fin >> gamemode;
    fin >> level >> xp >> max_health;
}

void print_data() //输出数据 
{
    ofstream fout("data.txt", ios::out); 
    for(int i = 0;i < 2400;i++)
    {
        for(int j = 0;j < 1200;j++)
        {
            int id = world[i][j].id;
            fout << id;
            fout << ' ';
        }
        fout << endl;
    }
    fout << playerx << endl << playery << endl;
    for(int i = 0;i < 5;i++) fout << fknum[i] << ' ' << wpnum[i] << endl;
    for(int i = 0;i < 5;i++)
    {
        fout << fkl[i].id << ' ' << wpl[i].id << endl; 
    }
    fout << kjl.id << endl;
    fout << xgnum << endl;
    for(int i = 0;i < xgnum;i++)
    {
        fout << xgl[i].id << ' ' << xgl[i].time << ' ' << xgl[i].level;
        fout << endl;
    }
    fout << health << endl << oxygen << endl;
    fout << gamemode << endl;
    fout << level << endl << xp << endl << max_health << endl;
}

void item_choose() //创造物品选择器 
{
    system("cls");
    SetPos(10, 1);
    cout << "创造模式物品选择器:";
    SetPos(10, 3);
    cout << "a d 迭代手中物品 S 堆叠手中物品";
    SetPos(10, 5);
    cout << "K 确认";
    while(1)
    {
        SetPos(10, 7);
        cout << "手中物品:";
        if(now <= 4) //显示方块 
        {
            Color(fkl[now].color), cout << fkl[now].txt << ' ' << fkl[now].name;
            cout << "        ";
            Color(0);
        }
        else //显示物品 
        {
            if(wpl[now - 5].rare == 0) Color(0);
            else if(wpl[now - 5].rare == 1) Color(1);
            else if(wpl[now - 5].rare == 2) Color(3);
            else if(wpl[now - 5].rare == 3) Color(4);
            else Color(2);
            cout << wpl[now - 5].name;
            cout << "        ";
            Color(0);
        }
        Color(0);
        if(_kbhit())
        {
            char f = _getch();
            if(f == 'a')
            {
                if(now <= 4 && fkl[now].id > 0)
                {
                    if(!fknum[now]) fknum[now]++;
                    fkl[now].id--;
                    fkl[now].color = block[fkl[now].id].color;
                    fkl[now].fluid = block[fkl[now].id].fluid;
                    fkl[now].hard = block[fkl[now].id].hard;
                    fkl[now].level = block[fkl[now].id].level;
                    fkl[now].name = block[fkl[now].id].name;
                    fkl[now].txt = block[fkl[now].id].txt;
                }
                else if(now >= 5 && wpl[now - 5].id > 0)
                {
                    if(!wpnum[now - 5]) wpnum[now - 5]++;
                    wpl[now - 5].id--;
                    wpl[now - 5].hurt = item[wpl[now - 5].id].hurt;
                    wpl[now - 5].level = item[wpl[now - 5].id].level;
                    wpl[now - 5].name = item[wpl[now - 5].id].name;
                    wpl[now - 5].rare = item[wpl[now - 5].id].rare;
                    wpl[now - 5].speed = item[wpl[now - 5].id].speed;
                }
            }
            else if(f == 'd')
            {
                if(now <= 4 && fkl[now].id < block_max)
                {
                    if(!fknum[now]) fknum[now]++;
                    fkl[now].id++;
                    fkl[now].color = block[fkl[now].id].color;
                    fkl[now].fluid = block[fkl[now].id].fluid;
                    fkl[now].hard = block[fkl[now].id].hard;
                    fkl[now].level = block[fkl[now].id].level;
                    fkl[now].name = block[fkl[now].id].name;
                    fkl[now].txt = block[fkl[now].id].txt;
                }
                else if(now >= 5 && wpl[now - 5].id < item_max)
                {
                    if(!wpnum[now - 5]) wpnum[now - 5]++;
                    wpl[now - 5].id++;
                    wpl[now - 5].hurt = item[wpl[now - 5].id].hurt;
                    wpl[now - 5].level = item[wpl[now - 5].id].level;
                    wpl[now - 5].name = item[wpl[now - 5].id].name;
                    wpl[now - 5].rare = item[wpl[now - 5].id].rare;
                    wpl[now - 5].speed = item[wpl[now - 5].id].speed;
                }
            }
            else if(f == 's')
            {
                if(now <= 4) fknum[now] = 64;
                else wpnum[now - 5] = 64;
            }
            else if(f == 'k')
            {
                system("cls");
                return;
            }
        }
    }
}

void crafting()
{
    //合成
    system("cls");
    SetPos(10, 1);
    cout << "合成";
    SetPos(10, 3);
    cout << "1 工具类";
    SetPos(10, 5);
    cout << "2 熔炼类";
    SetPos(10, 7);
    cout << "3 盔甲类";
    SetPos(10, 9);
    cout << "4 杂项";
    SetPos(10, 11);
    cout << "5 离开";
    char cft0 = input('1', '5');
    system("cls");
    if(cft0 == '1')
    {
        SetPos(10, 1);
        cout << "合成 - 工具类";
        SetPos(10, 3);
        cout << "1 木质";
        SetPos(10, 5);
        cout << "2 石质";
        SetPos(10, 7);
        cout << "3 铁质";
        SetPos(10, 9);
        cout << "4 金质";
        SetPos(10, 11);
        cout << "5 钻石/绿宝石质";
        SetPos(10, 13);
        cout << "6 合金质";
        SetPos(10, 15);
        cout << "7 灵魂物质";
        SetPos(10, 17);
        cout << "8 药水";
        SetPos(10, 19);
        cout << "9 离开";
        char cft1 = input('1', '9');
        system("cls");
        if(cft1 == '1')
        {
            SetPos(10, 1);
            cout << "合成 - 工具类 - 木质";
            SetPos(10, 3);
            cout << "1 木镐";
            SetPos(10, 5);
            cout << "2 木剑";
            SetPos(10, 7);
            cout << "3 离开";
            char cft11 = input('1', '3');
            if(cft11 == '1')
            {
                SetPos(10, 7);
                cout << "需要 木头x4";
                SetPos(10, 9);
                cout << "1 确认";
                SetPos(10, 11);
                cout << "2 离开";
                char cft111 = input('1', '2');
                if(cft111 == '1')
                {
                    if(block_num(block[4]) < 4) return;
                    block_delete(block[4]);
                    block_delete(block[4]);
                    block_delete(block[4]);
                    block_delete(block[4]);
                    item_pick(item[1]);
                    xp += 3;
                }
                else if(cft111 == '2')
                {
                    return;
                }
            }
            else if(cft11 == '2')
            {
                SetPos(10, 7);
                cout << "需要 木头x4";
                SetPos(10, 9);
                cout << "1 确认";
                SetPos(10, 11);
                cout << "2 离开";
                char cft112 = input('1', '2');
                if(cft112 == '1')
                {
                    if(block_num(block[4]) < 4) return;
                    block_delete(block[4]);
                    block_delete(block[4]);
                    block_delete(block[4]);
                    block_delete(block[4]);
                    item_pick(item[2]);
                    xp += 3;
                }
                else if(cft112 == '2')
                {
                    return;
                }
            }
            else if(cft11 == '3')
            {
                return;
            }
        }
        else if(cft1 == '2')
        {
            SetPos(10, 1);
            cout << "合成 - 工具类 - 石质";
            SetPos(10, 3);
            cout << "1 石镐";
            SetPos(10, 5);
            cout << "2 石剑";
            SetPos(10, 7);
            cout << "3 离开";
            char cft12 = input('1', '3');
            if(cft12 == '1')
            {
                SetPos(10, 9);
                cout << "需要 石头x6";
                SetPos(10, 11);
                cout << "1 确认";
                SetPos(10, 13);
                cout << "2 离开";
                char cft121 = input('1', '2');
                if(cft121 == '1')
                {
                    if(block_num(block[1]) < 6) return;
                    block_delete(block[1]);
                    block_delete(block[1]);
                    block_delete(block[1]);
                    block_delete(block[1]);
                    block_delete(block[1]);
                    block_delete(block[1]);
                    item_pick(item[3]);
                    xp += 3;
                }
                else if(cft121 == '2')
                {
                    return;
                }
            }
            else if(cft12 == '2')
            {
                SetPos(10, 9);
                cout << "需要 石头x6";
                SetPos(10, 11);
                cout << "1 确认";
                SetPos(10, 13);
                cout << "2 离开";
                char cft122 = input('1', '2');
                if(cft122 == '1')
                {
                    if(block_num(block[1]) < 6) return;
                    block_delete(block[1]);
                    block_delete(block[1]);
                    block_delete(block[1]);
                    block_delete(block[1]);
                    block_delete(block[1]);
                    block_delete(block[1]);
                    item_pick(item[4]);
                    xp += 3;
                }
                else if(cft122 == '2')
                {
                    return;
                }
            }
            else if(cft12 == '3')
            {
                return;
            }
        }
        else if(cft1 == '3')
        {
            SetPos(10, 1);
            cout << "合成 - 工具类 - 铁质";
            SetPos(10, 3);
            cout << "1 铁镐";
            SetPos(10, 5);
            cout << "2 铁剑";
            SetPos(10, 7);
            cout << "3 铁块";
            SetPos(10, 9);
            cout << "4 离开";
            char cft13 = input('1', '4');
            if(cft13 == '1')
            {
                SetPos(10, 11);
                cout << "需要 铁锭x3";
                SetPos(10, 13);
                cout << "1 确认";
                SetPos(10, 15);
                cout << "2 离开";
                char cft131 = input('1', '2');
                if(cft131 == '1')
                {
                    if(item_num(item[5]) < 3) return;
                    item_delete(item[5]);
                    item_delete(item[5]);
                    item_delete(item[5]);
                    item_pick(item[6]);
                    xp += 3;
                }
                else if(cft131 == '2')
                {
                    return;
                }
            }
            else if(cft13 == '2')
            {
                SetPos(10, 11);
                cout << "需要 铁锭x3";
                SetPos(10, 13);
                cout << "1 确认";
                SetPos(10, 15);
                cout << "2 离开";
                char cft132 = input('1', '2');
                if(cft132 == '1')
                {
                    if(item_num(item[5]) < 3) return;
                    item_delete(item[5]);
                    item_delete(item[5]);
                    item_delete(item[5]);
                    item_pick(item[7]);
                    xp += 3;
                }
                else if(cft132 == '2')
                {
                    return;
                }
            }
            else if(cft13 == '3')
            {
                SetPos(10, 11);
                cout << "需要 铁锭x9";
                SetPos(10, 13);
                cout << "1 确认";
                SetPos(10, 15);
                cout << "2 离开";
                char cft133 = input('1', '2');
                if(cft133 == '1')
                {
                    if(item_num(item[5]) < 9) return;
                    item_delete(item[5]);
                    item_delete(item[5]);
                    item_delete(item[5]);
                    item_delete(item[5]);
                    item_delete(item[5]);
                    item_delete(item[5]);
                    item_delete(item[5]);
                    item_delete(item[5]);
                    item_delete(item[5]);
                    block_pick(block[6]);
                    xp += 3;
                }
                else if(cft133 == '2')
                {
                    return;
                }
            }
            else if(cft13 == '4')
            {
                return;
            }
        }
        else if(cft1 == '5')
        {
            SetPos(10, 1);
            cout << "合成 - 工具类 - 钻石/绿宝石质";
            SetPos(10, 3);
            cout << "1 钻石镐";
            SetPos(10, 5);
            cout << "2 钻石剑";
            SetPos(10, 7);
            cout << "3 钻石块";
            SetPos(10, 9);
            cout << "4 绿宝石镐";
            SetPos(10, 11);
            cout << "5 绿宝石剑";
            SetPos(10, 13);
            cout << "6 绿宝石块";
            SetPos(10, 9);
            cout << "7 离开";
            char cft15 = input('1', '7');
            if(cft15 == '1')
            {
                SetPos(10, 11);
                cout << "需要 钻石x6";
                SetPos(10, 13);
                cout << "1 确认";
                SetPos(10, 15);
                cout << "2 离开";
                char cft151 = input('1', '2');
                if(cft151 == '1')
                {
                    if(item_num(item[11]) < 6) return;
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_pick(item[12]);
                    xp += 3;
                }
                else if(cft151 == '2')
                {
                    return;
                }
            }
            else if(cft15 == '2')
            {
                SetPos(10, 11);
                cout << "需要 钻石x6";
                SetPos(10, 13);
                cout << "1 确认";
                SetPos(10, 15);
                cout << "2 离开";
                char cft152 = input('1', '2');
                if(cft152 == '1')
                {
                    if(item_num(item[11]) < 6) return;
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_pick(item[13]);
                    xp += 3;
                }
                else if(cft152 == '2')
                {
                    return;
                }
            }
            else if(cft15 == '3')
            {
                SetPos(10, 11);
                cout << "需要 钻石x9";
                SetPos(10, 13);
                cout << "1 确认";
                SetPos(10, 15);
                cout << "2 离开";
                char cft153 = input('1', '2');
                if(cft153 == '1')
                {
                    if(item_num(item[11]) < 9) return;
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    block_pick(block[10]);
                    xp += 3;
                }
                else if(cft153 == '2')
                {
                    return;
                }
            }
            else if(cft15 == '4')
            {
                SetPos(10, 11);
                cout << "需要 绿宝石x6";
                SetPos(10, 13);
                cout << "1 确认";
                SetPos(10, 15);
                cout << "2 离开";
                char cft154 = input('1', '2');
                if(cft154 == '1')
                {
                    if(item_num(item[23]) < 6) return;
                    item_delete(item[23]);
                    item_delete(item[23]);
                    item_delete(item[23]);
                    item_delete(item[23]);
                    item_delete(item[23]);
                    item_delete(item[23]);
                    item_pick(item[24]);
                    xp += 3;
                }
                else if(cft154 == '2')
                {
                    return;
                }
            }
            else if(cft15 == '5')
            {
                SetPos(10, 11);
                cout << "需要 绿宝石x6";
                SetPos(10, 13);
                cout << "1 确认";
                SetPos(10, 15);
                cout << "2 离开";
                char cft155 = input('1', '2');
                if(cft155 == '1')
                {
                    if(item_num(item[23]) < 6) return;
                    item_delete(item[23]);
                    item_delete(item[23]);
                    item_delete(item[23]);
                    item_delete(item[23]);
                    item_delete(item[23]);
                    item_delete(item[23]);
                    item_pick(item[25]);
                    xp += 3;
                }
                else if(cft155 == '2')
                {
                    return;
                }
            }
            else if(cft15 == '6')
            {
                SetPos(10, 11);
                cout << "需要 绿宝石x9";
                SetPos(10, 13);
                cout << "1 确认";
                SetPos(10, 15);
                cout << "2 离开";
                char cft156 = input('1', '2');
                if(cft156 == '1')
                {
                    if(item_num(item[23]) < 9) return;
                    item_delete(item[23]);
                    item_delete(item[23]);
                    item_delete(item[23]);
                    item_delete(item[23]);
                    item_delete(item[23]);
                    item_delete(item[23]);
                    item_delete(item[23]);
                    item_delete(item[23]);
                    item_delete(item[23]);
                    block_pick(block[23]);
                    xp += 3;
                }
                else if(cft156 == '2')
                {
                    return;
                }
            }
            else if(cft15 == '7')
            {
                return;
            }
        }
        else if(cft1 == '6')
        {
            SetPos(10, 1);
            cout << "合成 - 工具类 - 下界合金质";
            SetPos(10, 3);
            cout << "1 下界合金镐";
            SetPos(10, 5);
            cout << "2 下界合金剑";
            SetPos(10, 7);
            cout << "3 下界合金块";
            SetPos(10, 9);
            cout << "4 离开";
            char cft16 = input('1', '4');
            if(cft16 == '1')
            {
                SetPos(10, 11);
                cout << "需要 钻石x12 下界合金块x1";
                SetPos(10, 13);
                cout << "1 确认";
                SetPos(10, 15);
                cout << "2 离开";
                char cft161 = input('1', '2');
                if(cft161 == '1')
                {
                    if(item_num(item[11]) < 12) return;
                    if(block_num(block[17]) < 1) return;
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    block_delete(block[17]);
                    item_pick(item[16]);
                    xp += 3;
                }
                else if(cft161 == '2')
                {
                    return;
                }
            }
            else if(cft16 == '2')
            {
                SetPos(10, 11);
                cout << "需要 钻石x12 下界合金块x1";
                SetPos(10, 13);
                cout << "1 确认";
                SetPos(10, 15);
                cout << "2 离开";
                char cft162 = input('1', '2');
                if(cft162 == '1')
                {
                    if(item_num(item[11]) < 12) return;
                    if(block_num(block[17]) < 1) return;
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    item_delete(item[11]);
                    block_delete(block[17]);
                    item_pick(item[17]);
                    xp += 3;
                }
                else if(cft162 == '2')
                {
                    return;
                }
            }
            else if(cft16 == '3')
            {
                SetPos(10, 11);
                cout << "需要 钻石块x1 下界合金锭x9";
                SetPos(10, 13);
                cout << "1 确认";
                SetPos(10, 15);
                cout << "2 离开";
                char cft163 = input('1', '2');
                if(cft163 == '1')
                {
                    if(block_num(block[10]) < 1) return;
                    if(item_num(item[15]) < 9)
                    block_delete(block[10]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    block_pick(block[17]);
                    xp += 3;
                }
                else if(cft163 == '2')
                {
                    return;
                }
            }
            else if(cft16 == '4')
            {
                return;
            }
        }
        else if(cft1 == '7')
        {
            SetPos(10, 1);
            cout << "合成 - 工具类 - 灵魂物质";
            SetPos(10, 3);
            cout << "1 灵魂镐";
            SetPos(10, 5);
            cout << "2 灵魂剑";
            SetPos(10, 7);
            cout << "3 灵魂之星"; 
            SetPos(10, 9);
            cout << "3 离开";
            char cft16 = input('1', '4');
            if(cft16 == '1')
            {
                SetPos(10, 11);
                cout << "需要 下界合金锭x12 灵魂之星x1";
                SetPos(10, 13);
                cout << "1 确认";
                SetPos(10, 15);
                cout << "2 离开";
                char cft161 = input('1', '2');
                if(cft161 == '1')
                {
                    if(item_num(item[15]) < 12) return;
                    if(item_num(item[30]) < 1) return;
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[30]);
                    item_pick(item[31]);
                    xp += 3;
                }
                else if(cft161 == '2')
                {
                    return;
                }
            }
            else if(cft16 == '2')
            {
                SetPos(10, 11);
                cout << "需要 下界合金锭x12 灵魂之星x1";
                SetPos(10, 13);
                cout << "1 确认";
                SetPos(10, 15);
                cout << "2 离开";
                char cft162 = input('1', '2');
                if(cft162 == '1')
                {
                    if(item_num(item[15]) < 12) return;
                    if(item_num(item[30]) < 1) return;
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[15]);
                    item_delete(item[30]);
                    item_pick(item[32]);
                    xp += 3;
                }
                else if(cft162 == '2')
                {
                    return;
                }
            }
            else if(cft16 == '3')
            {
                SetPos(10, 11);
                cout << "需要 下界合金块x2 魂石x1";
                SetPos(10, 13);
                cout << "1 确认";
                SetPos(10, 15);
                cout << "2 离开";
                char cft163 = input('1', '2');
                if(cft163 == '1')
                {
                    if(block_num(block[17]) < 2) return;
                    if(block_num(block[34]) < 1) return;
                    block_delete(block[17]);
                    block_delete(block[17]);
                    block_delete(block[34]);
                    item_pick(item[30]);
                    xp += 3;
                }
                else if(cft163 == '2')
                {
                    return;
                }
            }
            else if(cft16 == '4')
            {
                return;
            }
        }
        else if(cft1 == '8')
        {
            SetPos(10, 1);
            cout << "合成 - 工具类 - 药水";
            SetPos(10, 3);
            cout << "1 生命提升药水";
            SetPos(10, 5);
            cout << "2 急迫药水";
            SetPos(10, 7);
            cout << "3 生命吸收药水";
            SetPos(10, 9);
            cout << "4 中毒药水";
            SetPos(10, 11);
            cout << "5 离开";
            char cft17 = input('1', '5');
            if(cft17 == '1')
            {
                SetPos(10, 13);
                cout << "需要 水桶x1 药水量子x1";
                SetPos(10, 15);
                cout << "1 确认";
                SetPos(10, 17);
                cout << "2 离开";
                char cft171 = input('1', '2');
                if(cft171 == '1')
                {
                    if(item_num(item[19]) < 1) return;
                    if(item_num(item[21]) < 1) return;
                    item_delete(item[19]);
                    item_delete(item[21]);
                    buff_give(buff[1], 2, 1200);
                    xp += 3;
                }
            }
            else if(cft17 == '2')
            {
                SetPos(10, 13);
                cout << "需要 水桶x1 药水量子x1";
                SetPos(10, 15);
                cout << "1 确认";
                SetPos(10, 17);
                cout << "2 离开";
                char cft172 = input('1', '2');
                if(cft172 == '1')
                {
                    if(item_num(item[19]) < 1) return;
                    if(item_num(item[21]) < 1) return;
                    item_delete(item[19]);
                    item_delete(item[21]);
                    buff_give(buff[2], 2, 1200);
                    xp += 3;
                }
            }
            else if(cft17 == '3')
            {
                SetPos(10, 13);
                cout << "需要 水桶x1 药水量子x1";
                SetPos(10, 15);
                cout << "1 确认";
                SetPos(10, 17);
                cout << "2 离开";
                char cft173 = input('1', '2');
                if(cft173 == '1')
                {
                    if(item_num(item[19]) < 1) return;
                    if(item_num(item[21]) < 1) return;
                    item_delete(item[19]);
                    item_delete(item[21]);
                    buff_give(buff[3], 2, 1200);
                    xp += 3;
                }
            }
            else if(cft17 == '4')
            {
                SetPos(10, 13);
                cout << "需要 水桶x1 药水量子x1";
                SetPos(10, 15);
                cout << "1 确认";
                SetPos(10, 17);
                cout << "2 离开";
                char cft174 = input('1', '2');
                if(cft174 == '1')
                {
                    if(item_num(item[19]) < 1) return;
                    if(item_num(item[21]) < 1) return;
                    item_delete(item[19]);
                    item_delete(item[21]);
                    buff_give(buff[4], 2, 1200);
                    xp += 3;
                }
            }
        }
    }
    else if(cft0 == '2')
    {
        SetPos(10, 1);
        cout << "合成 - 熔炼类";
        SetPos(10, 3);
        cout << "1 锭熔炼";
        SetPos(10, 5);
        cout << "2 远古残骸熔炼";
        SetPos(10, 7);
        cout << "3 离开";
        char cft2 = input('1', '3');
        system("cls");
        if(cft2 == '1')
        {
            SetPos(10, 1);
            cout << "合成 - 熔炼类 - 锭熔炼";
            SetPos(10, 3);
            cout << "1 铁锭";
            SetPos(10, 5);
            cout << "2 金锭";
            SetPos(10, 7);
            cout << "3 钻石";
            SetPos(10, 9);
            cout << "4 下界合金锭";
            SetPos(10, 11);
            cout << "5 离开";
            char cft21 = input('1', '5');
            if(cft21 == '1')
            {
                SetPos(10, 13);
                cout << "需要 铁矿石x1";
                SetPos(10, 15);
                cout << "1 确认";
                SetPos(10, 17);
                cout << "2 离开";
                char cft211 = input('1', '2');
                if(cft211 == '1')
                {
                    if(block_num(block[5]) < 1) return;
                    block_delete(block[5]);
                    item_pick(item[5]);
                    xp += 3;
                }
                else
                {
                    return;
                }
            }
            else if(cft21 == '2')
            {
                SetPos(10, 13);
                cout << "需要 金矿石x1";
                SetPos(10, 15);
                cout << "1 确认";
                SetPos(10, 17);
                cout << "2 离开";
                char cft212 = input('1', '2');
                if(cft212 == '1')
                {
                    if(block_num(block[7]) < 1) return;
                    block_delete(block[7]);
                    item_pick(item[8]);
                    xp += 3;
                }
                else
                {
                    return;
                }
            }
            else if(cft21 == '3')
            {
                SetPos(10, 13);
                cout << "需要 钻石矿石x1";
                SetPos(10, 15);
                cout << "1 确认";
                SetPos(10, 17);
                cout << "2 离开";
                char cft213 = input('1', '2');
                if(cft213 == '1')
                {
                    if(block_num(block[9]) < 1) return;
                    block_delete(block[9]);
                    item_pick(item[11]);
                    xp += 3;
                }
                else
                {
                    return;
                }
            }
            else if(cft21 == '4')
            {
                SetPos(10, 13);
                cout << "需要 下界合金碎片x4 金锭x4";
                SetPos(10, 15);
                cout << "1 确认";
                SetPos(10, 17);
                cout << "2 离开";
                char cft211 = input('1', '2');
                if(cft211 == '1')
                {
                    if(item_num(item[14]) < 4) return;
                    if(item_num(item[8]) < 4) return;
                    item_delete(item[14]);
                    item_delete(item[14]);
                    item_delete(item[14]);
                    item_delete(item[14]);
                    item_delete(item[8]);
                    item_delete(item[8]);
                    item_delete(item[8]);
                    item_delete(item[8]);
                    item_pick(item[15]);
                    xp += 3;
                }
                else
                {
                    return;
                }
            }
            else if(cft21 == '5')
            {
                return; 
            }
        }
        else if(cft2 == '2')
        {
            SetPos(10, 1);
            cout << "合成 - 熔炼类 - 远古残骸熔炼";
            SetPos(10, 3);
            cout << "1 下界合金碎片";
            SetPos(10, 5);
            cout << "2 离开";
            char cft22 = input('1', '2');
            if(cft22 == '1')
            {
                SetPos(10, 7);
                cout << "需要 远古残骸x1";
                SetPos(10, 9);
                cout << "1 确认";
                SetPos(10, 11);
                cout << "2 离开";
                char cft221 = input('1', '2');
                if(cft221 == '1')
                {
                    if(block_num(block[16]) < 1) return;
                    block_delete(block[16]);
                    item_pick(item[14]);
                    xp += 3;
                }
            }
        }
    }
    else if(cft0 == '3')
    {
        SetPos(10, 1);
        cout << "合成 - 盔甲类";
        SetPos(10, 3);
        cout << "1 木盔甲";
        SetPos(10, 5);
        cout << "2 石盔甲";
        SetPos(10, 7);
        cout << "3 铁盔甲";
        SetPos(10, 9);
        cout << "4 钻石盔甲";
        SetPos(10, 11);
        cout << "5 下界合金盔甲";
        SetPos(10, 13);
        cout << "6 离开";
        SetPos(10, 15);
        Color(2), cout << "Tips:盔甲制造后立即替换当前盔甲!!", Color(0);
        char cft3 = input('1', '6');
        if(cft3 == '1')
        {
            SetPos(10, 17);
            cout << "需要 木头x4";
            SetPos(10, 19);
            cout << "1 确认";
            SetPos(10, 21);
            cout << "2 离开";
            char cft31 = input('1', '2');
            if(cft31 == '1')
            {
                if(block_num(block[4]) < 4) return;
                block_delete(block[4]);
                block_delete(block[4]);
                block_delete(block[4]);
                block_delete(block[4]);
                armor_pick(armor[1]);
                xp += 3;
            }
        }
        else if(cft3 == '2')
        {
            SetPos(10, 17);
            cout << "需要 石头x6";
            SetPos(10, 19);
            cout << "1 确认";
            SetPos(10, 21);
            cout << "2 离开";
            char cft32 = input('1', '2');
            if(cft32 == '1')
            {
                if(block_num(block[1]) < 6) return;
                block_delete(block[1]);
                block_delete(block[1]);
                block_delete(block[1]);
                block_delete(block[1]);
                block_delete(block[1]);
                block_delete(block[1]);
                armor_pick(armor[2]);
                xp += 3;
            }
        }
        else if(cft3 == '3')
        {
            SetPos(10, 17);
            cout << "需要 铁锭x3";
            SetPos(10, 19);
            cout << "1 确认";
            SetPos(10, 21);
            cout << "2 离开";
            char cft33 = input('1', '2');
            if(cft33 == '1')
            {
                if(item_num(item[5]) < 3) return;
                item_delete(item[5]);
                item_delete(item[5]);
                item_delete(item[5]);
                armor_pick(armor[3]);
                xp += 3;
            }
        }
        else if(cft3 == '4')
        {
            SetPos(10, 17);
            cout << "需要 钻石x12";
            SetPos(10, 19);
            cout << "1 确认";
            SetPos(10, 21);
            cout << "2 离开";
            char cft34 = input('1', '2');
            if(cft34 == '1')
            {
                if(item_num(item[11]) < 12) return;
                item_delete(item[11]);
                item_delete(item[11]);
                item_delete(item[11]);
                item_delete(item[11]);
                item_delete(item[11]);
                item_delete(item[11]);
                item_delete(item[11]);
                item_delete(item[11]);
                item_delete(item[11]);
                item_delete(item[11]);
                item_delete(item[11]);
                item_delete(item[11]);
                armor_pick(armor[4]);
                xp += 3;
            }
        }
        else if(cft3 == '5')
        {
            SetPos(10, 17);
            cout << "需要 钻石x12 下界合金块x1";
            SetPos(10, 19);
            cout << "1 确认";
            SetPos(10, 21);
            cout << "2 离开";
            char cft35 = input('1', '2');
            if(cft35 == '1')
            {
                if(item_num(item[11]) < 12) return;
                if(block_num(block[17]) < 1) return;
                item_delete(item[11]);
                item_delete(item[11]);
                item_delete(item[11]);
                item_delete(item[11]);
                item_delete(item[11]);
                item_delete(item[11]);
                item_delete(item[11]);
                item_delete(item[11]);
                item_delete(item[11]);
                item_delete(item[11]);
                item_delete(item[11]);
                item_delete(item[11]);
                block_delete(block[17]);
                armor_pick(armor[5]);
                xp += 3;
            }
        }
        else if(cft3 == '6')
        {
            return;
        }
    }
    else if(cft0 == '4')
    {
        SetPos(10, 1);
        cout << "合成 - 杂项";
        int page = 1, pagemax = 1;
        while(1)
        {
            system("cls");
            SetPos(10, 1);
            cout << "合成 - 杂项";
            SetPos(10, 3);
            cout << "A 上一页 D 下一页 E 离开";
            SetPos(10, 5);
            cout << page << '/' << pagemax << "页";
            if(page == 1)
            {
                SetPos(10, 7);
                cout << "1 桶";
                SetPos(10, 9);
                cout << "2 药水量子";
                SetPos(10, 11);
                cout << "3 强化量子";
                SetPos(10, 13);
                cout << "4 海洋创造锤";
            }
            char cft4 = input();
            if(cft4 == 'a' && page != 1) page--;
            else if(cft4 == 'd' && page != pagemax) page++;
            else if(cft4 == 'e')
            {
                return;
            }
            else if(cft4 >= '1' && cft4 <= '5')
            {
                char choose;
                if(page == 1)
                {
                    switch(cft4)
                    {
                        case '1':
                            SetPos(10, 15);
                            cout << "需要 铁锭x3";
                            SetPos(10, 17);
                            cout << "1 确认";
                            SetPos(10, 19);
                            cout << "2 离开";
                            choose = input('1', '2');
                            if(choose == '1')
                            {
                                if(item_num(item[5]) < 3) return;
                                item_delete(item[5]);
                                item_delete(item[5]);
                                item_delete(item[5]);
                                item_pick(item[18]);
                                xp += 3;
                            }
                            break;
                        case '2':
                            SetPos(10, 15);
                            cout << "需要 下界合金锭x1";
                            SetPos(10, 17);
                            cout << "1 确认";
                            SetPos(10, 19);
                            cout << "2 离开";
                            choose = input('1', '2');
                            if(choose == '1')
                            {
                                if(item_num(item[15]) < 1) return;
                                item_delete(item[15]);
                                item_pick(item[21]);
                                xp += 3;
                            }
                            break;
                        case '3':
                            SetPos(10, 15);
                            cout << "需要 海洋之星x1 药水量子x1";
                            SetPos(10, 17);
                            cout << "1 确认";
                            SetPos(10, 19);
                            cout << "2 离开";
                            choose = input('1', '2');
                            if(choose == '1')
                            {
                                if(item_num(item[21]) < 1) return;
                                if(block_num(block[20]) < 1) return;
                                item_delete(item[21]);
                                block_delete(block[20]);
                                item_pick(item[22]);
                                xp += 3;
                            }
                            break;
                        case '4':
                            SetPos(10, 15);
                            cout << "需要 海洋之星x1";
                            SetPos(10, 17);
                            cout << "1 确认";
                            SetPos(10, 19);
                            cout << "2 离开";
                            choose = input('1', '2');
                            if(choose == '1')
                            {
                                if(block_num(block[20]) < 1) return;
                                block_delete(block[20]);
                                item_pick(item[26]);
                                xp += 3;
                            }
                        default:
                            break;
                    }
                }
            }
        }
    }
    else if(cft0 == '5')
    {
        return;
    }
}

void sea_crafting()
{
    SetPos(10, 1);
    cout << "海洋合成";
    SetPos(10, 3);
    cout << "1 强化型药水";
    SetPos(10, 5);
    cout << "2 离开";
    char sft0 = input('1', '2');
    system("cls");
    if(sft0 == '1')
    {
        SetPos(10, 1);
        cout << "海洋合成 - 强化型药水";
        SetPos(10, 3);
        cout << "1 强化急迫药水";
        SetPos(10, 5);
        cout << "2 强化中毒药水";
        SetPos(10, 7);
        cout << "3 离开";
        char sft1 = input('1', '3');
        if(sft1 == '1')
        {
            SetPos(10, 9);
            cout << "需要 岩浆桶x1 强化量子x1";
            SetPos(10, 11);
            cout << "1 确认";
            SetPos(10, 13);
            cout << "2 离开";
            char sft11 = input('1', '2');
            if(sft11 == '1')
            {
                if(item_num(item[20]) < 1) return;
                if(item_num(item[22]) < 1) return;
                item_delete(item[20]);
                item_delete(item[22]);
                buff_give(buff[2], 4, 1200);
                xp += 3;
            }
        }
        else if(sft1 == '2')
        {
            SetPos(10, 9);
            cout << "需要 岩浆桶x1 强化量子x1";
            SetPos(10, 11);
            cout << "1 确认";
            SetPos(10, 13);
            cout << "2 离开";
            char sft12 = input('1', '2');
            if(sft12 == '1')
            {
                if(item_num(item[20]) < 1) return;
                if(item_num(item[22]) < 1) return;
                item_delete(item[20]);
                item_delete(item[22]);
                buff_give(buff[4], 4, 1200);
                xp += 3;
            }
        }
    }
}

void bomb(int x, int y, int lvl)
{
    for(int i = x - lvl * 5;i <= x + lvl * 5;i++)
    {
        for(int j = y - lvl * 5;j <= y + lvl * 5;j++)
        {
            if(sqrt(abs(i - x) * abs(i - x) + abs(j - y) * abs(j - y)) <= lvl * 2)
            {
                block_copy(i, j, 19);
            }
        }
    }
    if(sqrt(abs(playerx - x) * abs(playerx - x) + abs(playery - y) * abs(playery - y)) <= lvl * 2)
    {
        attack(lvl * 4, "玩家被炸成了灰烬");
    }
}

void other()
{
    while(1)
    {
        SetPos(0, 0);
        cout << "属性";
        SetPos(0, 2);
        cout << "Z键开启合成界面";
        if(now >= 5 && wpl[now - 5].id == 26)
        {
            Color(3), cout << "   手持海洋创造锤 可进入专项合成区";
            Color(0);
        }
        SetPos(0, 4);
        cout << "药水效果:";
        if(xgnum < 5)
        {
            for(int i = 0;i < xgnum;i++)
            {
                SetPos(0, 6 + 4 * i);
                cout << xgl[i].name << "[" << xgl[i].level << "级]";
                SetPos(0, 7 + 4 * i);
                cout << xgl[i].time / 600 << ":" << xgl[i].time % 600 / 10;
                SetPos(0, 8 + 4 * i);
                cout << buff_str[xgl[i].id];
            }
        }
        else if(xgnum < 12)
        {
            for(int i = 0;i < xgnum;i++)
            {
                SetPos(0, 6 + 2 * i);
                cout << xgl[i].name << "[" << xgl[i].level << "级]";
            }
        }
        else
        {
            for(int i = 0;i < 12;i++)
            {
                SetPos(0, 6 + 2 * i);
                cout << xgl[i].name << "[" << xgl[i].level << "级]";
            }
        }

        SetPos(40, 4);
        cout << "基本属性:";
        SetPos(40, 6);
        cout << "生命值:" << health;
        SetPos(40, 8);
        cout << "生命值上限:" << max_health + get_buff_level(buff[1]) * 4 << endl;
        SetPos(40, 10);
        cout << "挖掘速度:";
        if(now <= 4) cout << "0";
        else cout << (10 + wpl[now - 5].speed) * (1 + get_buff_level(buff[2]) * 0.25) * (sqrt(level * 2.5 + 1) * 0.2) << "每短刻";

        SetPos(40, 13);
        cout << "等级：" << level;
        SetPos(60, 13);
        cout << "经验：" << xp << "/" << 100 + (level + 1) * 10;
        int xp_of_level = 100 + (level + 1) * 10;
        int xp_ge = xp * 30 / xp_of_level;
        for(int i = 0;i < min(xp_ge, 30);i++) SetPos(40 + i, 15), Color(2), cout << "█";
        for(int i = xp_ge;i < 30;i++) SetPos(40 + 1, 15), Color(0), cout << "█";

        SetPos(40, 14);
        cout << "X键返回主页面";
        if(_kbhit())
        {
            char x = _getch();
            if(x == 'z')
            {
                system("cls");
                if(now >= 5 && wpl[now - 5].id == 26) sea_crafting();
                else crafting();
                system("cls");
            }
            else if(x == 'x')
            {
                system("cls");
                return;
            }
        }
    }
}

void minecraft()
{
    int jianweitishi = 20, wajuetishi = 0;
    system("cls");
    while(1)
    {
        Sleep(100);
        //时刻流逝 
        short_tick++;
        if(short_tick == 10)
        {
            short_tick = 0;
            tick++;
            tick_attack = false;
            int zhongdulevel = get_buff_level(buff[4]);
            if(zhongdulevel > 0) attack(zhongdulevel, "玩家中毒而死");
        }
        if(jianweitishi) jianweitishi--;
        if(wajuetishi) wajuetishi--;
        //处理药水效果 
        buff_merge();
        buff_live();

        //处理生命溢出
        if(health >= max_health + get_buff_level(buff[1]) * 4)
        {
            health = max_health + get_buff_level(buff[1]) * 4;
        }

        //处理等级提升
        int i = 0;
        while(xp >= 100 + (level + 1) * 10)
        {
            i++;
            xp -= 100 + (level + 1) * 10;
            level++;
            if(level % 2 == 0) max_health++; //每两级加一滴血 
        }

        SetPos(0, 0);
        cout << "世界与我  Craft And My";
        SetPos(0, 1); 
        if(get_buff_level(buff[4])) Color(5);
        else Color(2);
        double the_mx = max_health + get_buff_level(buff[1]) * 4; //生命上限
        int h = health;
        int heart = h / the_mx * 10;
        for(int i = 0;i < heart;i++) cout << "◆"; //生命值 
        int y = h / (the_mx / 10);
        for(int z = heart;z < 10;z++) cout << "◇";
        cout << ' ' << fixed << setprecision(1) << health << "    ";
        Color(0);
        SetPos(0, 2);
        Color(3);
        for(int i = 2;i <= oxygen;i += 2) cout << "●"; //氧气值 
        int u = oxygen / 2;
        for(int v = u + 1;v <= 10;v++) cout << "○";
        cout << ' ' << fixed << setprecision(1) << oxygen << "    ";
        Color(0);
        SetPos(0, 3);
        for(int i = 2;i <= kjl.defease;i += 2) cout << "▼"; //盔甲 
        SetPos(69, 2); //输出玩家坐标 
        cout << "X:" << playerx;
        SetPos(69, 4);
        cout << "Y:" << playery;
        for(int i = 0;i < 5;i++) //打印物品栏 方块栏 
        {
            SetPos(69, 6 + i * 2);
            if(now == i) Color(5);
            else if(wajuetishi) Color(2);
            cout << i << " ";
            Color(0);
            if(fknum[i] > 0)
            {
                Color(fkl[i].color);
                cout << fkl[i].txt << " " << fkl[i].name;
                Color(0);
                cout << " " << fknum[i] << "x      ";
            }
            else
            {
                cout << "            ";
            }
            SetPos(69, 6 + (i + 5) * 2);
            if(now == i + 5) Color(5);
            else if(wajuetishi) Color(1);
            cout << i + 5 << " ";
            Color(0);
            if(wpnum[i] > 0)
            {
                if(wpl[i].rare == 0) Color(0);
                else if(wpl[i].rare == 1) Color(1);
                else if(wpl[i].rare == 2) Color(3);
                else if(wpl[i].rare == 3) Color(4);
                else Color(-1);

                if(wpl[i].rare == 4)
                {
                    string s = wpl[i].name;
                    for(int i = 0;i < s.size();i++)
                    {
                        Color(-1), cout << s[i];
                    }
                }
                else cout << wpl[i].name;

                if(wpl[i].rare == 4) Color(2);
                cout << " " << wpnum[i] << "x       ";
                Color(0);
            }
            else
            {
                cout << "             ";
            }
        }
        SetPos(69, 26);
        cout << "盔甲:" << kjl.name;
        SetPos(0, 24);
        cout << "                         ";
        SetPos(0, 25);
        cout << "             ";
        SetPos(0, 26);
        cout << "E键开启属性界面";
        SetPos(0, 27);
        cout << "S键保存当前存档";
        if(gamemode == 0 || gamemode == 2)
        {
            SetPos(0, 28);
            cout << "Q键摧毁手持物品"; 
        }
        else
        {
            SetPos(0, 28);
            cout << "Q键选择手持物品";
        }
        SetPos(0, 5);
        //输出地图
        int j = 4;
        for(int i = playery + 13;i >= playery - 3;i--)
        {
            j++;
            SetPos(0, j);
            for(int j = playerx - 12;j <= playerx + 12;j++)
            {
                if(i == playery && j == playerx)
                {
                    cout << "[]";
                    continue;
                }

                //进入游戏后一秒键位提示
                if(jianweitishi)
                {
                    if(world[j][i].fluid)
                    {
                        if(j == playerx && i == playery + 1)
                        {
                            Color(5), cout << "W^";
                            Color(0);
                            continue;
                        }
                        else if(j == playerx - 1 && i == playery)
                        {
                            Color(5), cout << "A<";
                            Color(0);
                            continue; 
                        }
                        else if(j == playerx + 1 && i == playery)
                        {
                            Color(5), cout << "D>";
                            Color(0);
                            continue;
                        }
                    }
                    else
                    {
                        if(j == playerx && i == playery + 1)
                        {
                            Color(2), cout << "I^";
                            Color(0);
                            continue;
                        }
                        else if(j == playerx && i == playery - 1)
                        {
                            Color(2), cout << "Kv";
                            Color(0);
                            continue;
                        }
                        else if(j == playerx - 1 && i == playery)
                        {
                            Color(2), cout << "J<";
                            Color(0);
                            continue;
                        }
                        else if(j == playerx + 1 && i == playery)
                        {
                            Color(2), cout << "L>";
                            Color(0);
                            continue;
                        }
                    }
                }

                Color(world[j][i].color), cout << world[j][i].txt;
                Color(0);
            }
        }
        //流体下降
        for(int i = playery + 12;i >= playery - 3;i--)
        {
            for(int j = playerx - 12;j <= playerx + 12;j++)
            {
                if(world[j][i].fluid && world[j][i - 1].id == 19)
                {
                    block_copy(j, i - 1, world[j][i].id);
                }
            }
        }
        //生命恢复
        if(short_tick == 9 && tick % 2 == 0 && health < the_mx && !tick_attack)
        {
            health++;
            if(health > the_mx) health = the_mx;
        }
        //重力下落 
        if(zhuiluo < 4 && (tick * 10 + short_tick) % 3 == 0)
        {
            if(world[playerx][playery - 1].fluid)
            {
                playery--;
                zhuiluo++;
            }
            else //落地 
            {
                if(zhuiluo > 9) attack((zhuiluo - 9), "玩家摔死了");//摔落伤害
                zhuiluo = 0; 
            }
        }
        //快速下落 
        else if(zhuiluo >= 4 && zhuiluo < 8 && short_tick % 2 == 0)
        {
            if(world[playerx][playery - 1].fluid)
            {
                playery--;
                zhuiluo++;
            }
            else //落地 
            {
                if(zhuiluo > 9) attack((zhuiluo - 9), "玩家摔死了"); //摔落伤害 
                zhuiluo = 0;
            }
        }
        //危险下落 
        else if(zhuiluo >= 8 && short_tick % 3 <= 1)
        {
            if(world[playerx][playery - 1].fluid)
            {
                playery--;
                zhuiluo++;
            }
            else //落地 
            {
                if(zhuiluo > 9) attack(sqrt(zhuiluo - 9), "玩家摔死了"); //摔落伤害 
                zhuiluo = 0;
            }
        }
        //岩浆
        if(world[playerx][playery].id == 13 && short_tick % 2 == 1)
        {
            attack(2, "玩家在熔岩里游泳");
        }
        //地幔
        if(world[playerx][playery].id == 18)
        {
            attack(5, "玩家在地幔里游泳");
        }
        //死水
        if(world[playerx][playery].id == 35)
        {
            attack(5, "玩家在死水中化为飞灰");
        }
        //氧气值下降 
        if(short_tick == 0)
        {
            if(world[playerx][playery].fluid && !(world[playerx][playery].name == "空气"))
            {
                oxygen--;
                if(oxygen < 0)
                {
                    //氧气耗尽 
                    oxygen = 0;
                    attack(1, "玩家窒息而死");
                }
            }
            else if(oxygen < 20)
            {
                oxygen++; //若玩家不在流体中则恢复氧气 
            }
        }
        if(energy > 0) //跳跃 
        {
            if(world[playerx][playery + 1].fluid)
            {
                playery++;
                energy -= 500;
            }
            else energy = 0;
            if(energy < 0) energy = 0;
        }
        char x;
        if(_kbhit()) //按键点击 
        {
            x = _getch();
            if(x == 'a')
            {
                if(world[playerx - 1][playery].fluid)
                {
                    playerx--;
                }
                wjjd = 0;
            }
            else if(x == 'd')
            {
                if(world[playerx + 1][playery].fluid)
                {
                    playerx++;
                }
                wjjd = 0;
            }
            else if(x == 'w')
            {
                energy += 1000;
                wjjd = 0;
            }
            else if(x >= '0' && x <= '9')
            {
                now = x - '0';
                wjjd = 0;
            }
            else if(x == 'i') //挖掘上方方块/放置方块在上方 
            {
                //桶的收集判定
                if(now >= 5 && wpl[now - 5].id == 18)
                {
                    if(world[playerx][playery + 1].id == 12)
                    {
                        item_delete(item[18]);
                        item_pick(item[19]);
                        block_copy(playerx, playery + 1, 19);
                    }
                    else if(world[playerx][playery + 1].id == 13)
                    {
                        item_delete(item[18]);
                        item_pick(item[20]);
                        block_copy(playerx, playery + 1, 19);
                    }
                    else if(world[playerx][playery + 1].id == 35)
                    {
                        item_delete(item[18]);
                        item_pick(item[29]);
                        block_copy(playerx, playery + 1, 19);
                    }
                }
                //宝藏探测器判定
                if(now >= 5 && wpl[now - 5].id == 28)
                {
                    int mindis = 100000000, mx, my;
                    for(int x = 101;x <= 2300;x++)
                    {
                        for(int y = 1; y <= 1100;y++)
                        {
                            if(world[x][y].id == 28)
                            {
                                if(mindis > abs(x - playerx) + abs(y - playery)) mx = x, my = y;
                                mindis = min(mindis, abs(x - playerx) + abs(y - playery));
                            }
                        }
                    }
                    if(mindis != 100000000)
                    {
                        playerx = mx;
                        playery = my;
                    }
                }
                //TNT判定
                if(world[playerx][playery + 1].id == 29)
                {
                    block_copy(playerx, playery + 1, 30);
                    Sleep(1000);
                    block_copy(playerx, playery + 1, 31);
                    Sleep(1000);
                    block_copy(playerx, playery + 1, 32);
                    Sleep(1000);
                    bomb(playerx, playery + 1, 4);
                }
                //其它判定 
                if(world[playerx][playery + 1].fluid && now <= 4)
                {
                    wajuetishi = 20;
                    if(fknum[now] > 0 && fkl[now].id != 0)
                    { 
                        block_copy(playerx, playery + 1, fkl[now].id);
                        block_delete(fkl[now]);
                    }
                }
                else if(!world[playerx][playery + 1].fluid && now >= 5)
                {
                    wajuetishi = 20;
                    if(gamemode == 1)
                    {
                        block_copy(playerx, playery + 1, 19);
                        continue;
                    }
                    wjjd += (10 + wpl[now - 5].speed) * (1 + get_buff_level(buff[2]) * 0.25) * (sqrt(level * 2.5 + 1) * 0.2);
                    if(wjjd >= world[playerx][playery + 1].hard)
                    {
                        wjjd = 0;
                        if(max(0, wpl[now - 5].level) >= world[playerx][playery + 1].level)
                        {
                            block_pick(world[playerx][playery + 1]);
                        }
                        block_copy(playerx, playery + 1, 19);
                        xp++;
                    }
                    else
                    {
                        SetPos(0, 24);
                        cout << "正在挖掘: " << world[playerx][playery + 1].name;
                        SetPos(0, 25);
                        cout << "进度: ";
                        cout << 1.0 * wjjd / world[playerx][playery + 1].hard * 100;
                        cout << "%";
                    }
                }
            }
            else if(x == 'k')
            {
                //桶的收集判定
                if(now >= 5 && wpl[now - 5].id == 18)
                {
                    if(world[playerx][playery - 1].id == 12)
                    {
                        item_delete(item[18]);
                        item_pick(item[19]);
                        block_copy(playerx, playery - 1, 19);
                    }
                    else if(world[playerx][playery - 1].id == 13)
                    {
                        item_delete(item[18]);
                        item_pick(item[20]);
                        block_copy(playerx, playery - 1, 19);
                    }
                    else if(world[playerx][playery - 1].id == 35)
                    {
                        item_delete(item[18]);
                        item_pick(item[29]);
                        block_copy(playerx, playery - 1, 19);
                    }
                }
                //宝藏探测器判定
                if(now >= 5 && wpl[now - 5].id == 28)
                {
                    int mindis = 100000000, mx, my;
                    for(int x = 101;x <= 2300;x++)
                    {
                        for(int y = 1; y <= 1100;y++)
                        {
                            if(world[x][y].id == 28)
                            {
                                if(mindis > abs(x - playerx) + abs(y - playery)) mx = x, my = y;
                                mindis = min(mindis, abs(x - playerx) + abs(y - playery));
                            }
                        }
                    }
                    if(mindis != 100000000)
                    {
                        playerx = mx;
                        playery = my;
                    }
                }
                //TNT判定
                if(world[playerx][playery - 1].id == 29)
                {
                    block_copy(playerx, playery - 1, 30);
                    Sleep(1000);
                    block_copy(playerx, playery - 1, 31);
                    Sleep(1000);
                    block_copy(playerx, playery - 1, 32);
                    Sleep(1000);
                    bomb(playerx, playery - 1, 4);
                }
                //其它判定 
                if(world[playerx][playery - 1].fluid && now <= 4)
                {
                    wajuetishi = 20;
                    if(fknum[now] > 0 && fkl[now].id != 0)
                    {
                        block_copy(playerx, playery - 1, fkl[now].id);
                        block_delete(fkl[now]);
                    }
                }
                else if(!world[playerx][playery - 1].fluid && now >= 5)
                {
                    wajuetishi = 20;
                    if(gamemode == 1)
                    {
                        block_copy(playerx, playery - 1, 19);
                        continue;
                    }
                    wjjd += (10 + wpl[now - 5].speed) * (1 + get_buff_level(buff[2]) * 0.25) * (sqrt(level * 2.5 + 1) * 0.2);
                    if(wjjd >= world[playerx][playery - 1].hard)
                    {
                        wjjd = 0;
                        if(max(0, wpl[now - 5].level) >= world[playerx][playery - 1].level)
                        {
                            block_pick(world[playerx][playery - 1]);
                        }
                        block_copy(playerx, playery - 1, 19);
                        xp++;
                    }
                    else
                    {
                        SetPos(0, 24);
                        cout << "正在挖掘: " << world[playerx][playery - 1].name;
                        SetPos(0, 25);
                        cout << "进度: ";
                        cout << 1.0 * wjjd / world[playerx][playery - 1].hard * 100;
                        cout << "%";
                    }
                }
            }
            else if(x == 'j')
            {
                //桶的收集判定
                if(now >= 5 && wpl[now - 5].id == 18)
                {
                    if(world[playerx - 1][playery].id == 12)
                    {
                        item_delete(item[18]);
                        item_pick(item[19]);
                        block_copy(playerx - 1, playery, 19);
                    }
                    else if(world[playerx - 1][playery].id == 13)
                    {
                        item_delete(item[18]);
                        item_pick(item[20]);
                        block_copy(playerx - 1, playery, 19);
                    }
                    else if(world[playerx - 1][playery].id == 35)
                    {
                        item_delete(item[18]);
                        item_pick(item[29]);
                        block_copy(playerx - 1, playery, 19);
                    }
                }
                //宝藏探测器判定
                if(now >= 5 && wpl[now - 5].id == 28)
                {
                    int mindis = 100000000, mx, my;
                    for(int x = 101;x <= 2300;x++)
                    {
                        for(int y = 1; y <= 1100;y++)
                        {
                            if(world[x][y].id == 28)
                            {
                                if(mindis > abs(x - playerx) + abs(y - playery)) mx = x, my = y;
                                mindis = min(mindis, abs(x - playerx) + abs(y - playery));
                            }
                        }
                    }
                    if(mindis != 100000000)
                    {
                        playerx = mx;
                        playery = my;
                    }
                }
                //TNT判定
                if(world[playerx - 1][playery].id == 29)
                {
                    block_copy(playerx - 1, playery, 30);
                    Sleep(1000);
                    block_copy(playerx - 1, playery, 31);
                    Sleep(1000);
                    block_copy(playerx - 1, playery, 32);
                    Sleep(1000);
                    bomb(playerx - 1, playery, 4);
                }
                //其它判定 
                if(world[playerx - 1][playery].fluid && now <= 4)
                {
                    wajuetishi = 20;
                    if(fknum[now] > 0 && fkl[now].id != 0)
                    {
                        block_copy(playerx - 1, playery, fkl[now].id);
                        block_delete(fkl[now]);
                    }
                }
                else if(!world[playerx - 1][playery].fluid && now >= 5)
                {
                    wajuetishi = 20;
                    if(gamemode == 1)
                    {
                        block_copy(playerx - 1, playery, 19);
                        continue;
                    }
                    wjjd += (10 + wpl[now - 5].speed) * (1 + get_buff_level(buff[2]) * 0.25) * (sqrt(level * 2.5 + 1) * 0.2);
                    if(wjjd >= world[playerx - 1][playery].hard)
                    {
                        wjjd = 0;
                        if(max(0, wpl[now - 5].level) >= world[playerx - 1][playery].level)
                        {
                            block_pick(world[playerx - 1][playery]);
                        }
                        block_copy(playerx - 1, playery, 19);
                        xp++;
                    }
                    else
                    {
                        SetPos(0, 24);
                        cout << "正在挖掘: " << world[playerx - 1][playery].name;
                        SetPos(0, 25);
                        cout << "进度: ";
                        cout << 1.0 * wjjd / world[playerx - 1][playery].hard * 100;
                        cout << "%";
                    }
                }
            }
            else if(x == 'l')
            {
                //桶的收集判定
                if(now >= 5 && wpl[now - 5].id == 18)
                {
                    if(world[playerx + 1][playery].id == 12)
                    {
                        item_delete(item[18]);
                        item_pick(item[19]);
                        block_copy(playerx + 1, playery, 19);
                    }
                    else if(world[playerx + 1][playery].id == 13)
                    {
                        item_delete(item[18]);
                        item_pick(item[20]);
                        block_copy(playerx + 1, playery, 19);
                    }
                    else if(world[playerx - 1][playery].id == 35)
                    {
                        item_delete(item[18]);
                        item_pick(item[29]);
                        block_copy(playerx - 1, playery, 19);
                    }
                }
                //宝藏探测器判定
                if(now >= 5 && wpl[now - 5].id == 28)
                {
                    int mindis = 100000000, mx, my;
                    for(int x = 101;x <= 2300;x++)
                    {
                        for(int y = 1; y <= 1100;y++)
                        {
                            if(world[x][y].id == 28)
                            {
                                if(mindis > abs(x - playerx) + abs(y - playery)) mx = x, my = y;
                                mindis = min(mindis, abs(x - playerx) + abs(y - playery));
                            }
                        }
                    }
                    if(mindis != 100000000)
                    {
                        playerx = mx;
                        playery = my;
                    }
                }
                //TNT判定
                if(world[playerx + 1][playery].id == 29)
                {
                    block_copy(playerx + 1, playery, 30);
                    Sleep(1000);
                    block_copy(playerx + 1, playery, 31);
                    Sleep(1000);
                    block_copy(playerx + 1, playery, 32);
                    Sleep(1000);
                    bomb(playerx + 1, playery, 4);
                }
                //其它判定 
                if(world[playerx + 1][playery].fluid && now <= 4)
                {
                    wajuetishi = 20;
                    if(fknum[now] > 0 && fkl[now].id != 0)
                    {
                        block_copy(playerx + 1, playery, fkl[now].id);
                        block_delete(fkl[now]);
                    }
                }
                else if(!world[playerx + 1][playery].fluid && now >= 5)
                {
                    wajuetishi = 20;
                    if(gamemode == 1)
                    {
                        block_copy(playerx + 1, playery, 19);
                        continue;
                    }
                    wjjd += (10 + wpl[now - 5].speed) * (1 + get_buff_level(buff[2]) * 0.25) * (sqrt(level * 2.5 + 1) * 0.2);
                    if(wjjd >= world[playerx + 1][playery].hard)
                    {
                        wjjd = 0;
                        if(max(0, wpl[now - 5].level) >= world[playerx + 1][playery].level)
                        {
                            block_pick(world[playerx + 1][playery]);
                        }
                        block_copy(playerx + 1, playery, 19);
                        xp++;
                    }
                    else
                    {
                        SetPos(0, 24);
                        cout << "正在挖掘: " << world[playerx + 1][playery].name;
                        SetPos(0, 25);
                        cout << "进度: ";
                        cout << 1.0 * wjjd / world[playerx + 1][playery].hard * 100;
                        cout << "%";
                    }
                }
            }
            else if(x == 'e')
            {
                system("cls");
                other();
                system("cls");
            }
            else if(x == 's')
            {
                print_data();
            }
            else if(x == 'q')
            {
                if(gamemode == 1) item_choose(); //创造物品选择器 
                else if(now >= 4) wpnum[now - 5]--;
            }
            else if(x == 'z')
            {
                jianweitishi += 20;
            }
            else if(x == '/')
            {
                //命令
                SetPos(0, 30);
                cout << "/";
                SetPos(0, 31);
                cout << "输入命令";
                SetPos(0, 33);
                cout << "请勿随意换行 否则后果自负";
                SetPos(1, 30);
                string main_com;
                cin >> main_com; //关键字
                if(main_com == "gamemode")
                {
                    int mode;
                    cin >> mode;
                    if(mode < 0 || mode > 2)
                    {
                        SetPos(0, 32);
                        cout << "错误:游戏模式错误";
                    }
                    else
                    {
                        gamemode = mode;
                        SetPos(0, 32);
                        cout << "游戏模式已更新:";
                        if(gamemode == 0) cout << "生存模式";
                        else if(gamemode == 1) cout << "创造模式";
                        else if(gamemode == 2) cout << "极限模式";
                    }
                }
                else if(main_com == "give")
                {
                    string type;
                    cin >> type;
                    if(type == "block")
                    {
                        int id, num;
                        cin >> id >> num;
                        if(id < 0 || id > block_max)
                        {
                            SetPos(0, 32);
                            cout << "错误:方块ID越界";
                        }
                        else
                        {
                            fkl[now].id = id;
                            fkl[now].fluid = block[fkl[now].id].fluid;
                            fkl[now].hard = block[fkl[now].id].hard;
                            fkl[now].color = block[fkl[now].id].color;
                            fkl[now].level = block[fkl[now].id].level;
                            fkl[now].name = block[fkl[now].id].name;
                            fkl[now].txt = block[fkl[now].id].txt;
                            fknum[now] = num;
                            SetPos(0, 32);
                            cout << "已将方块栏第" << now << "处";
                            cout << "设为" << block[id].name;
                        }
                    }
                    else if(type == "item")
                    {
                        int id, num;
                        cin >> id >> num;
                        if(id < 0 || id > item_max)
                        {
                            SetPos(0, 32);
                            cout << "错误:物品ID越界";
                        }
                        else
                        {
                            wpl[now - 5].id = id;
                            wpl[now - 5].hurt = item[wpl[now - 5].id].hurt;
                            wpl[now - 5].level = item[wpl[now - 5].id].level;
                            wpl[now - 5].rare = item[wpl[now - 5].id].rare;
                            wpl[now - 5].speed = item[wpl[now - 5].id].speed;
                            wpl[now - 5].name = item[wpl[now - 5].id].name;
                            wpnum[now - 5] = num;
                            SetPos(0, 32);
                            cout << "已将物品栏第" << now - 5 << "处";
                            cout << "设为" << item[id].name;
                        }
                    }
                    else if(type == "effect")
                    {
                        int id, time, level;
                        cin >> id >> time >> level;
                        if(id < 0 || id > buff_max)
                        {
                            SetPos(0, 32);
                            cout << "错误:效果ID越界";
                        }
                        else
                        {
                            buff_give(buff[id], level, time);
                            buff_merge();
                            SetPos(0, 32);
                            cout << "已给予" << level << "级" << buff[id].name;
                        }
                    }
                    else
                    {
                        SetPos(0, 32);
                        cout << "错误:没有该类型";
                    }
                }
                else if(main_com == "delete")
                {
                    string type;
                    cin >> type;
                    if(type == "block")
                    {
                        int id;
                        cin >> id;
                        if(id < 0 || id > block_max)
                        {
                            SetPos(0, 32);
                            cout << "错误:方块ID越界";
                        }
                        else
                        {
                            block_delete(block[id]);
                            SetPos(0, 32);
                            cout << "已删除 " << block[id].name;
                        }
                    }
                    else if(type == "item")
                    {
                        int id;
                        cin >> id;
                        if(id < 0 || id > item_max)
                        {
                            SetPos(0, 32);
                            cout << "错误:物品ID越界";
                        }
                        else
                        {
                            item_delete(item[id]);
                            SetPos(0, 32);
                            cout << "已删除 " << item[id].name;
                        }
                    }
                    else
                    {
                        SetPos(0, 32);
                        cout << "错误:没有该类型";
                    }
                }
                else if(main_com == "add_xp")
                {
                    int ax;
                    cin >> ax;
                    if(ax < 0)
                    {
                        SetPos(0, 32);
                        cout << "错误:不能降低xp" << endl;
                    }
                    else
                    {
                        xp += ax;
                    }
                }
                else if(main_com == "bomb")
                {
                    int lvl;
                    cin >> lvl;
                    if(lvl < 0)
                    {
                        SetPos(0, 32);
                        cout << "错误:爆炸等级不能为负数" << endl;
                    }
                    else if(lvl > 20)
                    {
                        SetPos(0, 32);
                        cout << "错误:爆炸等级不能高于20" << endl;
                    }
                    else
                    {
                        bomb(playerx, playery, lvl);
                    }
                }
                else if(main_com == "tp")
                {
                    int x, y;
                    cin >> x >> y;
                    playerx = x;
                    playery = y;
                    block_copy(playerx, playery, 19);
                }
                else if(main_com == "kill")
                {
                    attack(1e9, "玩家被一种奇怪的力量抹杀");
                }
                else if(main_com == "attack")
                {
                    int num;
                    cin >> num;
                    attack(num, "玩家被一种奇怪的力量抹杀");
                }
                else if(main_com == "health")
                {
                    int num;
                    cin >> num;
                    health += num;
                }
                else if(main_com == "set_health")
                {
                    int new_health;
                    cin >> new_health;
                    health = new_health;
                    attack(0, "玩家被一种奇怪的力量抹杀");
                }
                else if(main_com == "set_oxygen")
                {
                    int new_oxygen;
                    cin >> new_oxygen;
                    if(new_oxygen >= 20 || new_oxygen < 0)
                    {
                        SetPos(0, 32);
                        cout << "错误:氧气值不在正常范围内" << endl;
                    }
                    else
                    {
                        oxygen = new_oxygen;
                    }
                }
                else
                {
                    SetPos(0, 32);
                    cout << "错误:未知命令";
                }
                SetPos(0, 33);
                cout << "                             ";
                SetPos(0, 33);
                system("pause");
                SetPos(0, 30);
                cout << "                                                  ";
                SetPos(0, 31);
                cout << "                                                  ";
                SetPos(0, 32);
                cout << "                                                  ";
                SetPos(0, 33);
                cout << "                                                  ";
            }
        }
        else wjjd = 0;
    }
}

void jiaocheng()
{
    SetPos(2, 2);
    Color(5), cout << "世界与我 Craft And My 新手教程" << endl;
    Sleep(400);
    SetPos(2, 4);
    Color(1), cout << "这款游戏是2D版的";
    Color(6), cout << "我的世界(Minecraft)";
    Sleep(400);
    SetPos(2, 6);
    Color(0), cout << "游戏的第一项基本操作是移动" << endl;
    Sleep(400);
    SetPos(42, 4);
    Color(5), cout << "w";
    SetPos(2, 8);
    cout << "现在跳跃    ";
    char x = input('w', 'w');
    SetPos(40, 6);
    Color(5), cout << "a";
    SetPos(2, 8);
    cout << "现在向左移动";
    x = input('a', 'a');
    SetPos(44, 6);
    Color(5), cout << "d"; 
    SetPos(2, 8);
    cout << "现在向右移动";
    x = input('d', 'd');
    SetPos(2, 8);
    cout << "做的好！    ";
    Sleep(400);
    SetPos(2, 10);
    Color(0), cout << "你可以使用另一套按键挖掘或放置方块" << endl;
    Sleep(400);
    int cnt[4] = {5, 5, 5, 5};
    int rank = 0, now = 0;
    SetPos(2, 14);
    cout << "持续点击方块直到它变成白色";
    while(cnt[0] || cnt[1] || cnt[2] || cnt[3])
    {
        Sleep(50);
        rank++;
        if(rank % 10 == 0)
        {
            Color(0);
            if(now == 0)
            {
                now++;
                SetPos(2, 12);
                cout << "使用 i 挖掘上面方块";
            }
            else if(now == 1)
            {
                now++;
                SetPos(2, 12);
                cout << "使用 j 挖掘左面方块";
            }
            else if(now == 2)
            {
                now++;
                SetPos(2, 12);
                cout << "使用 l 挖掘右面方块";
            }
            else if(now == 3)
            {
                now = 0;
                SetPos(2, 12);
                cout << "使用 k 挖掘下面方块";
            }
        }
        SetPos(62, 4);
        Color(cnt[0]), cout << "i";
        SetPos(60, 6);
        Color(cnt[1]), cout << "j";
        SetPos(64, 6);
        Color(cnt[2]), cout << "l";
        SetPos(62, 8);
        Color(cnt[3]), cout << "k";
        char y = ' ';
        if(_kbhit()) y = input(); 
        if(y == 'i') cnt[0] = max(cnt[0] - 1, 0);
        if(y == 'j') cnt[1] = max(cnt[1] - 1, 0);
        if(y == 'l') cnt[2] = max(cnt[2] - 1, 0);
        if(y == 'k') cnt[3] = max(cnt[3] - 1, 0);
    }
    Color(0);
    SetPos(2, 12);
    cout << "你完成了这项任务！ " << endl;
    Sleep(400);
    SetPos(2, 16);
    Color(7), cout << "注意，只有手中拿物品的时候才能挖掘" << endl;
    Sleep(800);
    SetPos(2, 18);
    Color(0), cout << "在你的物品栏中，0~4为方块 5~9为物品" << endl;
    SetPos(2, 20);
    Color(2), cout << "0 1 2 3 4 ";
    Color(1), cout << "5 6 7 8 9";
    SetPos(2, 22);
    Color(0), cout << "地图中会生成许多结构 等待着你去探索" << endl;
    Sleep(1000);
    SetPos(2, 24);
    cout << "新手教程到此结束，现在，生成你的第一张地图！" << endl;
    Sleep(1000);
    SetPos(2, 26);
    system("pause");
    system("cls");
    cout << "你的第一张地图正在生成中 0%" << endl;
    init();
    cout << "50%";
    print_data();
    cout << "100%";
}

int main()
{
    //世界准备 
    system("mode con cols=130 lines=35");
    srand(time(0));
    HideCursor();
    SetConsoleTitle("世界与我 0.8_v2.3"); 
cundang:
    cout << "Craft and My: 世界与我" << endl;
    cout << "1 使用原先存档" << endl;
    cout << "2 重置新的世界" << endl;
    cout << "3 查看更新日志" << endl;
    cout << "4 新手教程(";
    Color(5), cout << "新人必看";
    Color(0), cout << ")" << endl;
    cout << "版本: 测试版0.8_v2.3" << endl; 
    char n = input('1', '4');
    if(n == '1') input_data();
    else if(n == '2')
    {
        cout << "世界种子:(数字 输入0以随机选择)" << endl;
        int zhongzi;
        cin >> zhongzi;
        if(zhongzi != 0) srand(zhongzi);
        cout << "选择模式:" << endl;
        cout << "1 生存:" << endl;
        cout << "  挖掘 战斗 成为英雄!" << endl;
        cout << "2 创造:" << endl;
        cout << "  建造 规划 成为上帝!" << endl;
        cout << "3 极限:" << endl;
        cout << "  求生 变强 成为王者!" << endl;
        char m = input('1', '3');
        if(m == '1') gamemode = 0;
        else if(m == '2') gamemode = 1;
        else gamemode = 2;
        system("cls");
        SetPos(0, 0);
        cout << "Map 地图生成中 0%" << endl;
        init();
        cout << "50%" << endl;
        print_data();
        cout << "100%" << endl;
        system("cls");
        srand(time(0));
    }
    else if(n == '3')
    {
        system("cls");
        cout << "更新日志" << endl;
        int page = 1, pagemax = 3;
        while(1)
        {
            Color(0);
            system("cls");
            cout << "A 上一页 D 下一页 E退出" << endl;
            cout << page << '/' << pagemax << "页" << endl;
            if(page == 1)
            {
                Color(6), cout << "(1) 0.6pre1" << endl;
                Color(6), cout << "(2) 0.6pre2" << endl;
                Color(5), cout << "(3) 0.6" << endl;
                Color(6), cout << "(4) 0.7pre1" << endl;
                Color(6), cout << "(5) 0.7pre2" << endl;
                Color(6), cout << "(6) 0.7pre3" << endl;
                Color(6), cout << "(7) 0.7pre4" << endl;
                Color(5), cout << "(8) 0.7" << endl;
                Color(5), cout << "(9) 0.7a" << endl;
            }
            else if(page == 2)
            {
                Color(5), cout << "(1) 0.7b" << endl;
                Color(5), cout << "(2) 0.7c" << endl;
                Color(6), cout << "(3) 0.8pre1" << endl;
                Color(6), cout << "(4) 0.8pre1.1" << endl;
                Color(6), cout << "(5) 0.8pre1.2" << endl;
                Color(6), cout << "(6) 0.8pre2" << endl;
                Color(6), cout << "(7) 0.8pre2.1" << endl;
                Color(5), cout << "(8) 0.8_v1" << endl;
                Color(5), cout << "(9) 0.8_v2" << endl;
            }
            else if(page == 3)
            {
                Color(5), cout << "(1) 0.8_v2.1" << endl;
                Color(5), cout << "(2) 0.8_v2.2" << endl;
                Color(5), cout << "(3) 0.8_v2.3" << endl;
                Color(0), cout << "(4)" << endl;
                Color(0), cout << "(5)" << endl;
                Color(0), cout << "(6)" << endl;
                Color(0), cout << "(7)" << endl;
                Color(0), cout << "(8)" << endl;
                Color(0), cout << "(9)" << endl;
            }
            char n = input();
            if(n == 'a')
            {
                if(page != 1) page--;
            }
            else if(n == 'd')
            {
                if(page != pagemax) page++;
            }
            else if(n >= '1' && n <= '9')
            {
                if(page == 1)
                {
                    switch(n)
                    {
                        case '1':
                            Color(6), cout << "内部版0.6pre1" << endl, Color(0);
                            cout << "- 更新2种新的效果" << endl;
                            cout << "- 更新4种新的方块" << endl;
                            cout << "- 新增更新日志栏" << endl;
                            cout << "- 更新血量栏的颜色" << endl;
                            system("pause");
                            system("cls");
                            break;
                        case '2':
                            Color(6), cout << "内部版0.6pre2" << endl, Color(0);
                            cout << "- 更新1个新的配方栏" << endl;
                            cout << "- 使药水配方能够合成" << endl;
                            cout << "- 修改属性界面" << endl;
                            cout << "- 修改日志界面" << endl;
                            cout << "- 使桶能够收集流体" << endl;
                            cout << "- 修复一些漏洞" << endl;
                            system("pause");
                            system("cls");
                            break;
                        case '3':
                            Color(5), cout << "测试版0.6" << endl, Color(0);
                            cout << "- 更新2个新的命令" << endl;
                            cout << "- 新增命令系统" << endl;
                            cout << "- 修复一些漏洞" << endl;
                            system("pause");
                            system("cls");
                            break;
                        case '4':
                            Color(6), cout << "内部版0.7pre1" << endl, Color(0);
                            cout << "- 更新4个方块 5个物品" << endl;
                            cout << "- 增加结构 海之环" << endl;
                            cout << "- 扩大地图(与之前存档不兼容)" << endl;
                            system("pause");
                            system("cls");
                            break;
                        case '5':
                            Color(6), cout << "内部版0.7pre2" << endl, Color(0);
                            cout << "- 更新海洋合成专区" << endl;
                            cout << "- 新增Z键键位提示" << endl;
                            cout << "- 修复一些漏洞" << endl;
                            system("pause");
                            system("cls");
                            break;
                        case '6':
                            Color(6), cout << "内部版0.7pre3" << endl, Color(0);
                            cout << "- 修改游戏名称" << endl;
                            system("pause");
                            system("cls");
                            break; 
                        case '7':
                            Color(6), cout << "内部版0.7pre4" << endl, Color(0);
                            cout << "- 修复一些漏洞" << endl;
                            system("pause");
                            system("cls");
                            break; 
                        case '8':
                            Color(5), cout << "测试版0.7" << endl, Color(0);
                            cout << "- 修改give命令" << endl;
                            cout << "- 新增1个命令" << endl;
                            cout << "- 修改主界面" << endl;
                            cout << "- 重置存档时允许输入种子" << endl;
                            cout << "- 修复一些漏洞" << endl;
                            system("pause");
                            system("cls");
                            break; 
                        case '9':
                            Color(5), cout << "测试版0.7a" << endl, Color(0);
                            cout << "- 修改提升了程序的兼容性" << endl;
                            system("pause");
                            system("cls");
                            break;
                        default:
                            break;
                    }
                }
                else if(page == 2)
                {
                    switch(n)
                    {
                        case '1':
                            Color(5), cout << "测试版0.7b" << endl, Color(0);
                            cout << "- 修复了0.7pre1以来致命的错误(错误发现者 武意程先生)" << endl;
                            system("pause");
                            system("cls");
                            break;
                        case '2':
                            Color(5), cout << "测试版0.7c" << endl, Color(0);
                            cout << "- 增加了几种新的树" << endl;
                            system("pause");
                            system("cls");
                            break;
                        case '3':
                            Color(6), cout << "内部版0.8pre1" << endl, Color(0);
                            cout << "- 全新结构：于苗神殿登场！" << endl;
                            cout << "- 全新结构：宝藏岛登场！" << endl;
                            cout << "- 下界地形优化：不再填满方块！" << endl;
                            cout << "- 新增多个物品、方块" << endl;
                            cout << "- 新增等级系统" << endl;
                            cout << "- 其它一些小改动or小优化" << endl; 
                            system("pause");
                            system("cls"); 
                            break;
                        case '4':
                            Color(6), cout << "内部版0.8pre1.1" << endl, Color(0);
                            cout << "- 宝藏探测器的一点小更改" << endl;
                            cout << "- 补上了0.8pre1漏掉的一个小改动" << endl;
                            cout << "- 等级系统BUG修复" << endl;
                            system("pause");
                            system("cls"); 
                            break;
                        case '5':
                            Color(6), cout << "内部版0.8pre1.2" << endl, Color(0);
                            cout << "- 大整改！！！" << endl; 
                            cout << "- 爆炸更新：添加了巨大的爆炸系统！" << endl;
                            cout << "- 指令更新：增加了许多种指令！" << endl;
                            cout << "- 伤害更新：大幅提升了高伤害时的减免！" << endl;
                            cout << "- 经验更新：经验等级现在与生命值和挖掘速度挂钩！" << endl;
                            cout << "- BUG 修改：修改了许多BUG ！" << endl;
                            system("pause");
                            system("cls");
                            break;
                        case '6':
                            Color(6), cout << "内部版0.8pre2" << endl, Color(0);
                            cout << "- 修改代码结构" << endl;
                            system("pause");
                            system("cls");
                            break;
                        case '7':
                            Color(6), cout << "内部版0.8pre2.1" << endl, Color(0);
                            cout << "- 灵魂套前导预告：灵魂地牢" << endl;
                            cout << "- 灵魂地牢：大型地牢结构（好吧没多大），内部含有珍贵魂石" << endl;
                            system("pause");
                            system("cls");
                            break;
                        case '8':
                            Color(5), cout << "测试版0.8_v1" << endl, Color(0);
                            cout << "- 灵魂地牢更新：" << endl;
                            cout << "- 地牢扩大，增加死水池" << endl;
                            cout << "- 预计地牢在接下来几个版本里将会持续扩张" << endl;
                            cout << "- 修复了死亡后重生在地底的BUG" << endl;
                            cout << "- 新增一个修改氧气值的指令" << endl;
                            cout << "- 更改伤害指令的死亡信息" << endl;
                            system("pause");
                            system("cls"); 
                            break;
                        case '9':
                            Color(5), cout << "测试版0.8_v2" << endl, Color(0);
                            cout << "- 灵魂地牢更新：" << endl;
                            cout << "- 地牢再一次扩大 增加了几个目前没用的房间" << endl;
                            cout << "- 地牢石和魂石的硬度大幅提升 成为目前可以破坏的最坚硬的物质" << endl;
                            cout << "- 新增灵魂装备 目前灵魂装备是全游戏最强的装备" << endl;
                            cout << "- 修改了合成中的一些BUG" << endl;
                            cout << "- BETA测试专属功能：x=1200格下方必生成灵魂地牢" << endl;
                            cout << "- 修复了日志栏一直跳转不显示目录的BUG" << endl;
                            system("pause");
                            system("cls");
                            break;
                        default:
                            break;
                    }
                }
                else if(page == 3)
                {
                    switch(n)
                    {
                        case '1':
                            Color(5), cout << "测试版0.8_v2.1" << endl, Color(0);
                            cout << "- 改了一下生成 现在不会卡崩了" << endl;
                            cout << "- 船新新手教程 基础操作手把手指引！" << endl;
                            system("pause");
                            system("cls");
                            break;
                        case '2':
                            Color(5), cout << "测试版0.8_v2.2" << endl, Color(0);
                            cout << "- 改摔伤 降低了摔落伤害 同时修复了单次坠落格数过高时无法再跳跃的问题" << endl;
                            cout << "- 修改了硬度系统 增高降低了某些方块的硬度 调高了一些镐子的挖掘速度" << endl;
                            cout << "- 增大了海之环" << endl;
                            system("pause");
                            system("cls"); 
                        case '3':
                            Color(5), cout << "测试版0.8_v2.3" << endl, Color(0);
                            cout << "- 修改宝藏岛 让它的生成变得更难" << endl;
                            cout << "- 增加了未完成的下界要塞：生成机制重做中" << endl;
                            system("pause");
                            system("cls");
                        default:
                            break;
                    }
                }
            }
            else if(n == 'e')
            {
                system("cls");
                goto cundang;
            }
        }
    }
    else if(n == '4')
    {
        system("cls");
        jiaocheng();
    }
    minecraft();
    return 0;
} 
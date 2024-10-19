#include<algorithm>
#include<cmath>
#include<vector>
#include<stdio.h>
#include<iostream>
#include<string>
#include<cstring>
#include<windows.h>
#include<conio.h>
#include<cstdlib>
#include<ctime>
#include<fstream>
using namespace std;
/*********全局变量声明*********/
long long kaishi;//开始时间 
const int cjnum=64;
string cj[100]=//成就名称 
{"",
//  1      		2			3				4			5
  "旅程的起点","2^11","逃跑专家","长命百岁","学习狂魔",
//	6				7			8			9			10
  "艺术就是爆炸!","富甲一方","电脑高手","学霸再现江湖","登山游记",
//	11			12			13				14			15
  "天上的城市","钻石!","挖矿时间到","可怕的影子","这就是作者",
//	16		17		18				19			20
  "老赌徒","富二代","真是个肉盾","出击时间到!","光头强",
//	21				22			23			24			25
  "是时候继续挖矿了","怪物猎人","用钻石包裹我","超级英雄","虚空来客",
//	26			27			28				29				30
  "附魔师","量子幽灵在手","大悲咒","长线挂机","现在没空",
//	31			   32				33		34			35			36
  "黑漆漆的树林","鸭蛋还是鸡蛋","结束了？","旅途的终点","梦境回魂","获得升级",
// 37			38		   39		40		41			42			43 
  "赌博高手","甜蜜的梦","斗牛士","扫雷战士","妙手回春","时间恶魔","再一次到达终点",
//44		45			46 			47			48				49			50
  "弹无虚发","主宰全场","恶魔终结者","游戏高手","怪物狩猎完成","资深游戏专家","人生赢家",
  
  //隐藏成就
//51			52			53		54				55			56
 "天谴之人","交友达人","闹事达人","就是这么任性","写作高手","赌神",
//57		58			59			60			61		62
 "败家子儿","赚钱达人","食神助我","大预言家","复读机","急先锋",
//63			64
 "一时失手","失手成习惯",
};
string what_do[100]=//完成成就的要求 
{"",
  "进入游戏","玩2048成功一次","在神殿逃跑50次","活到100岁","看过所有的学习提示（共27条）",
  "用【春节礼炮】炸死166只怪物","拥有的零花钱超过100000","某次打字游戏速度超过250字/分钟","考一次100分","某一次登山成功",
  "去到天空之境","获得一颗钻石","获得一把铁镐","遇见一次游魂","遇见一次作者",
  "去赌场进行一次“赌大小”","在小学阶段零花钱数量达到1000000","血量超过1000","拥有一把铁剑","砍一次树",
  "打造一把钻石镐","击杀一次僵尸或骷髅","拥有一套钻石套装（注：最后做鞋子）","拥有一套英雄套装（注：最后做鞋子）","拥有一套虚空套装（注：最后做鞋子）",
  "拥有一个附魔台","拥有一把量子剑","默读《大悲咒》一次","获取一次至少8小时的挂机收益","连续48小时不上线，再次领取挂机收益即可获得",
  "去一次小树林","考一次0分","进入第六章","通过第六章","？？？","升一次级",
  "猜大小连中5次","在家睡一次觉","猎杀一头牛","某次“扫雷”成功","请“神医”为你治疗一次", "用“恶魔沙漏”修改一次时间轨迹", 
  "第二次击败MCYH","连续打猎打中20次","在竞技场连胜15局","终结恶魔领主","在创建游戏后的10分钟之内通关","累计击杀50只怪物",
  "使用过游戏中所有功能（除了隐藏功能一共74个）", "完成所有成就（隐藏成就除外）并且等级达到50级以上",
  //隐藏成就
  "被闪电劈死一次","让全班同学都成为你的好友","打架50次","开局时连点4个“否”","日记长度达到20K","中20张彩票",
  "累计开销/损失达到500G","累计赚取500G钱","饱食度达到50K","在被算命先生预言期间死亡一次","在寺庙里反复重复一句话5次",
  "在帮派战役中杀死50人","杀死一名自己帮派成员","杀死十名自己帮派成员",
};
bool gn[200];//功能使用flag 
unsigned long long gotmoney;//收入的钱数 
long long things[2000];//基本数据储存 
/*
0章节 1XP 2HP 3hungry 4water 5attack 6run 7money 8level 9等级 10age 
11棒棒糖 12面包 13矿泉水 14小瓶子 15玩具枪 16天数 17朋友数量 18次数 
19学号 20最高成绩 21难度 22存档是否存在 23打架次数 24和作者打架 
25回家次数 26剧情 27打猎资格 28大学 29挂机收益 30挂机上限 31沙漏
32附魔台 33附魔石 34更新 35管理员模式 36最高等级 37~57兑换码 
58~68活动是否参与过 69连中次数 70~79技能书 80隐藏进度条 81连中打猎
82竞技场连胜 83累计杀怪 84累计使用功能 85银行卡号 89密码 93余额
98维度 99传送符 100~184成就 185存档编号 186颜色 187今日事件 188形式 
189成就5完成进度 190死亡次数 191Pet数量 192是否已读取存档 193去神殿次数 
194通关神殿次数 195成就完成数量 196在神殿被炸死次数 197艺术就是爆炸记录 
198中彩票次数 199受限 200帮派加入申请人数（随机） 201~205修仙条件 
206~255各种丹药数量 256红水晶 257紫水晶 258蓝水晶 259黑水晶 260仙丹石
261奥玄石 262玄彩石 263白虎石 264朱雀石 265青龙石 266玄武石 267麒麟内丹
268麒麟石 269彩陶石 270炼丹炉 301上次领取魔金丹的时间 202上次领取材料的时间 
303修炼进度 304身份 305复读机进度 306急先锋进度 307失手进度 308生日礼物领取 
*/ 
 
//1当日运势（1~8:大凶，半凶，中平，小吉，中吉，大吉） 
void use(int n)
{
	if (gn[n]==false)
	  gn[n]=true,things[84]++;
}
long long fost[200];//小森林背包储存 
/*******/
string fsn[200]=//小森林背包物品名称 
{"原木 ","木板 ","木棍 ","石头 ","铁锭 ","金锭 ","钻石 ",
 "木镐 ","石镐 ","铁镐 ","金镐 ","钻石镐 ",
 "木剑 ","石剑 ","铁剑 ","金剑 ","钻石剑 ",
 "木斧 ","石斧 ","铁斧 ","金斧 ","钻石斧 ",
 "春节礼炮","火药","铁块","金块","钻石块",
 /*27*/"铁头盔","铁胸甲","铁护腿","铁靴子",
 "金头盔","金胸甲","金护腿","金靴子",
 "钻石头盔","钻石胸甲","钻石护腿","钻石靴子",
 /*39*/"英雄头盔","英雄战甲","英雄护腿","英雄战靴","英雄剑","英雄镐","英雄战斧",
 /*46*/"虚空头盔","虚空战甲","虚空护腿","虚空战靴","虚空剑","虚空镐","虚空斧",
 /*53*/"量子剑", "石头精华","CPU","工业钻石", 
};
string studentname[40]=//同学名称 
{"APEAPC","CIRCECLE","PAOE","FICE","CLEA","JACK","YZC","CODE","CPERA","FODAP","DIA","DOACKER",
"AOEE","ROD","RAUDJE","FIC","CZKD","AIDE","AKTI","MCAO","WAL","YZR","DEFASE","WKD","RKDOAE",
"FPEO","LCOE","LCOEOO","WAH","OCID","CIE","WYQ","PACOE","CDEFK","CKDO","CIDEP","MCYH",
"IDA","FIAOEP","FODA",
};
struct Time
{
	int year,month,day,hour,minute,second;
};
struct Player
{
	int y,m,d,age;
	int play,gang;
};
Player me;
string student[40];//存档同学名称 
const unsigned long long sj[]=//升级所需经验值 
{
//0 1  2   3   4   5    6   7     8    9   10    11   12    13     14   15    16    17      18    19      20    21      22    22                                                                                                                                                                                                                                                                                                                                            
  0,0,100,300,500,800,1500,2122,4500,6821,8933,13382,20091,38392,59183,70003,89312,100033,110344,130953,150099,169821,193831,229183,
//  24      25     26      27       28     29     30       31     32       33     34       35     36        37       38       39       40      41        42                                                                                                                                  
  500000,867132,1102933,1491839,1783021,2092103,2819382,3857192,4561738,5637139,7003928,8563729,10000000,10092819,11928372,12837291,14838279,16738291,18973820,
//   43         44      45      46       47     48      49      50     51       52     53        54     55      56     57       58      59      60      61                                                                                                
  20093819,23849577,25860392,28039281,3003920,3120392,3302910,3939201,4029102,4392018,4592018,4672103,4800928,5028102,5193029,5392010,5503921,5872810,6839201,
//    62     63      64      65      66      67       68         69    70       71       72          73      74         75      76      77      78       79                                                         
  7293829,7495820,7888930,8139002,8873029,9567291,10093829,11293029,13930295,15930281,169302810,18392910,22839020,28739201,38392819,50009329,74892396,99837281,
//    80         81        82        83         84     85      86            87      88        89         90        91       92        93        94        95                                                                                                                         
  103958372,113837293,136573829,157683920,175837292,183726195,200999887,218376859,239837261,254637289,267392019,289383910,309201839,339281039,358372918,381039283,
//     96        97        98       99      100        101         102      103       104      105       106        107     108        109     110          111                                                                                                 
  457362821,478392018,500938271,536839201,556738291,598372918,620999382,647382019,667382010,683920133,708310999,738291839,756372819,778837261,819382910,837291038,
//      112    113        114           115     116          117        118       119      120          121     122      123          124       125       126      127                                                           
  1000000000,1093729183,1128372919,1273829102,1303928193,13283920193,135869302,142637291,144738291,145637289,149392019,151839201,1553291333,156839201,158382919,160993029,
//    128        129        130      131         132          133      134         135       136          137       138        139        140        141         142       143                                                                                    
  1618392918,1638392819,1657382918,1689392819,1700900300,17100000000,1728393820,1759382910,1783929182,1800392022,1819310393,1827392913,1858392918,1889380130,1918038286,1938028284,
//    144        145       146         147       148         149         150       151      152       153       154        155         156        157      158          159                                                                                         
  1958302882,1978928388,2009380291,2039209288,2048983828,20673802838,2083920788,210989382,212980838,214008000,2147483647,225903988,2500993021,2930993822,3259586666,3693829100,
//    160         161       162        163       164         165         166       167        168         169         170          171        172          173        174                                                                                          
  4193857766,4894827188,5693028188,6839281999,7503929188,79302918383,9603929183,1059837772,12968392005,15382993005,16392159388,18396198382,21325938292,24593203928,26832392012,
 //下面为程序自动生成 385
 30052279053,33358029748,39696055400,43665660940,51962136518,59236835630,66937624261,77647644142,91624220087,106284095300,122226709595,139338448938,160239216278,177865530068,199209393676,227098708790,249808579669,294774124009,338990242610,376279169297,440246628077,488673757165,566861558311,657559407640,762768912862,884811938919,1008685610367,1129727883611,1276592508480,1493613234921,1642974558413,1840131505422,2189756491452,2408732140597,2745954640280,3267686021933,3855869505880,4357132541644,4967131097474,5712200762095,6797518906893,7885121931995,8673634125194,9887942902721,11173375480074,12514180537682,14891874839841,16827818569020,19015434982992,21867750230440,24054525253484,27181613536436,30715223296172,35936811256521,40967964832433,45474440964000,51386118289320,61149480764290,71544892494219,85138422068120,99611953819700,110569268739867,122731888301252,139914352663427,166498079669478,183147887636425,206957113029160,229722395462367,261883530827098,298547225142891,349300253417182,415667301566446,461390704738755,539827124544343,642394278207768,706633706028544,833827773113681,967240216811870,1092981444997413,1256928661747025,1420329387774138,1590768914307034,1877107318882300,2121131270336999,2481723586294289,2903616595964318,3223014421520393,3642006296318044,4079047051876209,4731694580176402,5441448767202862,6094422619267206,7130474464542631,8413959868160304,9423635052339540,11025653011237262,12679500962922852,15088606145878194,16899238883383578,19772109493558788,22540204822657020,26146637594282144,30330099609367288,33666410566397688,37033051623037456,42588009366493072,49827970958796896,57302166602616432,65897491593008896,74464165500100048,84144507015113056,95083292927077760,110296619795410208,125738146566767632,139569342689112064,157713357238696640,187678895114048992,213953940430015840,254605189111718848,295342019369593856,336689902081336960,370358892289470656,429616315055785984,506947251765827456,562711449460068480,669626624857481472,770070618586103680,847077680444713984,948727002098079616,1110010592454753152,1243211863549323520,1404829405810735616,1431086375945250560,1446971027840490240,1494018951557873152,1518714164038880000,1592428131188393984,1630900628817673728,1810299697987617792,1824965224029160192,1877743262415855616,1974937311041138432,2007712974518568192,2104325350214072320,2277593219013369088,2389212896748011520,2402552078753502208,2442051050667406336,2526209225503725568,2644886891827077120,2752031650881759744,2925328324759292928,3082952541741774848,3114801490694014464,3272962213933260800,3448520616728823808,3562378621596667904,3614580665056815104,3715541270040010240,3829626753671020544,3881950815100641792,4066119147758477312,4100812022884206080,4264982704384962048,4393977614875269632,4552320047186110976,4729663571374253056,4748539979845751808,4817922013471148032,4978958553478782976,5037722159087005696,5105887941592544256,5153669446809650176,5158992743549910016,5216864161138915328,5313692663972759552,5476127048895844352,5614437613770797056,5790912181349713920,5874510199086896128,6009584831237059584,6108877048861882368,6286137713971544064,6369582544521513984,6402682722514263040,6504774754431067136,6666897655207197696,6846854075068702720,6883076441892843520,6971175851971602432,7024803267562148864,7173881272107077632,7225138449090473984,7346607341013281792,7490330458986493952,7651300351116490752,7800145196587322368,7863362331652847616,8014695660294729728,8134268892447566848,8247604581892128768,8334495277132959744,8394519971509001216,8462948123097688064,8525747737633649664,8598595290495365120,8756588869792719872,8788140778443200512,8902971217834443776,8934328782589128704,9084111032814346240, 
};
int much[200]=//商品卖出价钱 
{
	0,0,0,0,0,0,0,0,0,0,
	15,100,100,60,3000,
};
int mu[200]=//商品买入价钱 
{
	0,0,0,0,0,0,0,0,0,0,0, 
	50,200,200,100,10000,
};
struct Pet//宠物结构体 
{
	string name;//宠物名称 
	string LX;//宠物名称（cat/dog） 
	int hp;//血量 
	int attack;//攻击 
	int run;//防御 
};
struct people
{
	string name;
	int hp,attack,defence;
	int gang;//所属组织 
};
struct Gang
{
	string name;//名称 
	int pnum;//↑50 
	people peo[50];//各人信息 
	int leader;//首领 
}gang[50];
Pet pet[50];//定义50只宠物 
string name;//玩家名称 
int sudu=80;//字出现速度
int week;//星期几 
string gangth;//帮派日志 
/*
 0 = 黑色       8 = 灰色
    1 = 蓝色       9 = 淡蓝色
    2 = 绿色       A = 淡绿色
    3 = 浅绿色     B = 淡浅绿色
    4 = 红色       C = 淡红色
    5 = 紫色       D = 淡紫色
    6 = 黄色       E = 淡黄色
    7 = 白色       F = 亮白色*/
 
enum Colour{black,blue,green,palegreen,red,purple,yellow,white,gray,light_blue,light_palegreen,light_red,light_purple,light_yellow,light_white};//注：有些是词生造出来的，可能与实际不符，仅供参数使用，切勿实际使用，否则后果自负
const Colour Const[16]={black,blue,green,palegreen,red,purple,yellow,white,gray,light_blue,light_palegreen,light_red,light_purple,light_yellow,light_white};
 
//函数声明
 
/*********存档函数*********/ 
void w1();
void w2();
void w3();
void w4();
void w5();//一堆输出点
void w6();
void w7();
void w8();
void w9(); 
void r1();
void r2();
void r3();
void r4();
void r5();//一堆读入点 
void mrf();//save.txt的读取 
void mwf();//save.txt的存档 
void Write_File();//负责调用子存档函数 
void Read_File();//负责调用子读取函数 
 
/*********剧情函数*********/ 
void show();//开头剧情 
 
/*********游戏页面函数*********/ 
void mainmenu();//主页面 
void game();//第一章小学时代 
void home();//家 
void school();//学校 
void shop();//超市 
void park();//公园 
void carnie();//游乐场 
float kaoshi();//考试 
void about();//关于游戏 
void Die();//死亡判定 
void Mid_School();//第三章中学时代 
void Birthday(); //生日
void Duchang();//赌场 
void Bank();//银行 
void Bookstore();//书店
void chengjiu();//查看成就
void City();//市中心
bool dalie();//打猎
int dazi();//打字游戏
void delp();//帮助（神界）
void Divinity();//神界
/*贪吃蛇部分省略*/
int Exa();//高考
void forest();//小森林
void Getmap();//输出异界地图
void hdcj(int i);//获得成就
void Hell();//地狱
void help();//帮助（地狱）
void hole();//星墓（地狱）
void Jingji();//竞技场
void market();//人力市场
int pingjia();//评价游戏
void poem();//结尾
int psss();//石头剪刀布 
int quest();//小升初
bool saolei();//扫雷游戏
void shuoming();//游戏说明
void Soc();//第五章进入社会
void use(int n);//功能使用（标记） 
int WAR();//星墓之战 
void War();//第六章决斗 
void welcome();//欢迎界面
bool zhandou(int m);//竞技场之战 
 
/*********核心功能函数*********/ 
bool baohu(); //未成年保护模式 
void jdt(int n);//进度条 
void gotoxy(int y,int x);//移动光标 
void coutwhat(int a,int b,int c,int d,string n);//输出something 
void setcolor(Colour x,Colour y);
void color(int x);//调节颜色 
int random(int n,int m);//产生随机数 
void Sout(string n);//减缓输出速度并输出 
void cls();//清屏system("cls")的简写 
void hidden();//清除光标 
void clear();//清屏的快捷版 
void g();//_getch()的简写 
void gs(); //_getch()并且cls() 
int gongji(int attack);//攻击返回数值 
void tepan();//特殊判定 
void sheng();//升级 
void init();//全局初始化 
char* randstr(int n,int m);//生成随机字符串 
/**********帮派部分**********/
void join(int x,int y,people imft);
void dead(int x,int y);
people born(int x); 
 
 
 
 
 
 
 
long long min(long long x,long long y)
{
	return x<y?x:y;
}
long long max(long long x,long long y)
{
	return x>y?x:y;
} 
void coutwhat(int a,int b,int c,int d,string n)//输出一些东西，从坐标(a,b)到(c,d)输出n 
{
	int i,j;
	for(i=a;i<=c;i++)
	 {
	  gotoxy(i,b);
	  for(j=b;j<=d;j++)
	    {
	    	cout<<n;
		}
	 }
}
void gotoxy(int y,int x) //移动光标 
{
	Write_File();
    COORD  coord;     
    coord.X=x;         
    coord.Y=y;
    HANDLE a=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,coord);    
}
void setcolor(Colour x,Colour y)
{
	int i,j;
	for(i=0;i<16;i++)
	  if (x==Const[i])
	    break;
	for(j=0;j<16;j++)
	  if (y==Const[j])
	    break;
	color(i+y*16);
}
void color(int x)//调颜色 
{
//	Write_File();//随时存档 
	int typeface=x/16,background=x%16; 
	char command_typeface[2],command_background[2];
	string command="color ";
	string change="0123456789abcdef";
	command=command+change[typeface]+change[background];
	char cmd[9];
	for(int i=0;i<9;i++)
	  cmd[i]=command[i];
	system(cmd);
}
int random(int n,int m)//产生一个随机数n~m 
{
	return rand()%(m-n+1)+n; 
}
void Sout(string n)//减速输出，挺有用的 
{
	for(int i=0;i<n.size();i++)
	  {
	  	cout<<n[i];
	  	Sleep(sudu);
	  	if (kbhit())
	  	  if (getch()=='\n')
		    {
		  	  cout<<n.substr(i+1,n.size()-i);
		  	  return;
		    }
	  }
}
void cls()
{
	system("cls");
}
 
void hidden()
{
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO CursorInfo;GetConsoleCursorInfo(handle, &CursorInfo);
CursorInfo.bVisible = false;
SetConsoleCursorInfo(handle, &CursorInfo);
}
void g()
{
	_getch();
} 
void gs()
{
	hidden();
	gotoxy(45,80);
	cout<<"按下任意键继续_";
	_getch();
	system("cls");
}
void jdt(int n)//进度条 
{
	Write_File();
	if (things[80]==32768)
	  return;
	if (n<=0)
	  n=1;
	time_t t1,t2;
	time(&t1);
	system("cls");
	int i,j=0,k=n;
	gotoxy(0,0);
	cout<<"Loading...\n";
	cout<<"剩余时间：       s";
	for(i=1;i<=100;i++)
	  {
	  	gotoxy(2,i);
	  	cout<<'-';
	  	gotoxy(5,i);
	  	cout<<'-';
	  }
	gotoxy(3,101);
	cout<<"|";
	gotoxy(4,101);
	cout<<"|";
	gotoxy(3,0);
	cout<<"|\n|";
	for(i=1;i<100;i++)
	  {
	  	gotoxy(1,30);
	  	cout<<i<<'%';
	  	gotoxy(1,12);
	  	cout<<n<<' ';
	  	gotoxy(2,i);
	  	cout<<"-";
	  	gotoxy(3,i);
	  	cout<<"#";
	  	gotoxy(4,i);
	  	cout<<"#";
	  	gotoxy(5,i);
	  	cout<<"-";
	  	gotoxy(3,i+1);
	  	cout<<"|";
	  	gotoxy(4,i+1);
	  	cout<<"|";
	  	Sleep(float(k/100.0)*60);
	  	time(&t2);
	  	if (t2-t1>=1)
	  	  {
	  	  	n--;
	  	  	time(&t1);
		  }
	  }
	cls();
} 
Time gottime()//获取当前时间 
{
	Time TIME;
	time_t now=time(0);
	tm*ltm=localtime(&now);
	TIME.year=1900+ltm->tm_year;
	TIME.month=1+ltm->tm_mon;
	TIME.day=ltm->tm_mday;
	TIME.hour=ltm->tm_hour;
	TIME.minute=ltm->tm_min;
	TIME.second=ltm->tm_sec;
	return TIME;
} 
Time Exit,now;
bool judge_num(string num)
{
	int i,k=0;
	int xs[18]={7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
	char x[11]={'1','0','X','9','8','7','6','5','4','3','2'};
	for(i=0;i<17;i++)
	  k+=(num[i]-'0')*xs[i];
	k%=11;
	return (x[k]==num[17]);
}
void namek()//实名注册系统 
{
	cls();
	printf("根据国家要求，你需要经过实名注册才能创建该存档!\n");
	printf("请输入姓名：");
	string num;
	cin>>num;
	do
	  {
		printf("请输入身份证号码：");
		cin>>num;
		things[199]=judge_num(num);
		if (things[199]==0)
		  printf("输入有误，请重新输入!\n");
	  }
	while(things[199]==0);
	int y,m,d;
	y=(num[7]-'0')*1000+(num[8]-'0')*100+(num[9]-'0')*10+(num[10]-'0');
	m=(num[11]-'0')*10+(num[12]-'0');
	d=(num[13]-'0')*10+(num[14]-'0');
	Time now=gottime();
	me.y=y;
	me.m=m;
	me.d=d;
	me.age=(now.year-me.y)+(now.month>me.m||now.month==me.m&&now.day>me.d);
	things[199]=(me.age>=18);
} 
int getwday()
{
	int y,m,d;
	const int monthS[2][13]=
	{
	{0,31,28,31,30,31,30,31,31,30,31,30,31},
	{0,31,29,31,30,31,30,31,31,30,31,30,31},
	};
	int i;
	scanf("%d%d%d",&y,&m,&d);
	//以2021.09.01星期三开始算起
	int y1,m1,d1;
	for(y1=2021;y1<=y;y1++) 
	  for(m1=9;m1<=m||y1<y&&m1<=12;m1++)
	   {
	   	  printf("%d.%d has %d days\n",y1,m1,y1==y&&m1==m?d:monthS[y1%400==0||y1%100!=0&&y%4==0][m1]);
	     if (y1==y&&m1==m)
		   i+=d;
		 else
		   i+=monthS[y1%400==0||y1%100!=0&&y%4==0][m1];
	   }
	return (i+1)%7+1;
} 
bool baohu()
{
	if (things[199]==1||things[35]==1)
	  return 0;
	Time jk=gottime();
	int m=jk.hour;
	if (m<=8||m>=22)
	{
	  cout<<"你好，根据国家政策，保护模式限定8点~22点才能登录游戏，请退出！\n";
	  gotoxy(45,80);
	  cout<<"按下任意键继续_";
	  char l=_getch();
	  if (l=='\\')
	    {
	    	cout<<"你居然按对了，那么输入密码吧：";
	    	string mima;
	    	cin>>mima;
	    	if (mima=="Minecraft_MC_YH")
	    	  return 0;
	    	else
	    	  cout<<"密码错了，退出吧~";
		}
	  if (m<=7)
	  cout<<"现在才"<<m<<"点呢！";
		if (m>=22)
		cout<<"都"<<m<<"点了，洗洗睡吧！";
	  return 1;
	}
	return 0;
}
bool friends[40];
bool renwu[20];
int xiaoguo[100][10]=//商店给自身带来的效果(xg[i][j],i表示第i个物品，j表示things[j]的加成） 
{
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,5,10,10,5,0,0,0,0,0,
	0,5,20,25,1,0,0,0,0,0,
	0,5,5,1,30,0,0,0,0,0,
	0,50,0,0,0,0,0,0,0,0,
	0,30,0,0,0,30,0,0,0,0,
};
time_t start,end;
string goodname[300]=//旧版的名字库，等随机起名完善后再删掉 
{
	"耶，","DA",
	"fda","DFADE,","DEA",
	"DAE","CKA","PEQWI","FDOAKEL",
	"OIASHDDE","SAOJVISD","IEFW",
	"UHJTR","WU","YUJ","TGRV","TRHY",
	"UBH","WETU","WDU","WDQCU56","HU54","5HU4",
	"5HUJ4","TY","G4T5","GT5R","TGE","H6","B4T","EGTB",
	"ETBG","TEBG","5UJ7Y","RSE","TG53","B4Y5NU","ECFRHYNJUMK",
	"FRVGTBHY","FRGTHY","DEFCRGT","FRGVT","FRG","FRGTY","UYTGR","TY",
	"JHG","T4HB","UI5","B%39201","YD1930sS","HY46","JU5NY","暴o十安妮","McyH","DE",
	"CEAD","FEDAOD","FEAD","HKDFS","HTR","RGFW","GRE","TRGE","HYGTRE","uj6HYGTRE", 
};
string filename[10]={"空存档","空存档","空存档","空存档","空存档","空存档","空存档","空存档","空存档","空存档"};//存档名，如果没有改变则为“空存档” 
string nn[4]={"物品","装备","矿物","其它"};//物品类型 
int leibie[201]={0,0,0,0,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3};
string fumoname[4][5]=//附魔名称 
{
	{"耐久","锋利","抢夺","雷电之力","落雷术"},
	{"耐久","效率","洪荒之力","木之克星","时运"},
	{"耐久","效率","急迫","精准采集","时运"},
	{"耐久","保护","血量提升","荆棘","雷电附身"},
}; 
int has_fumo[4][5]={0};//装备附魔情况 
int playthis;//玩游戏时间（还在完善） 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
string happened;//日记 
void hdcj(int i)//完成某个成就，i为成就编号 
{
	use(1);
	if (things[i+99])//如果已经完成就不重复了 
	  return;
	things[195]++;
	gotoxy(48,0);
	if (i<=50)
	  printf("%s获得了成就：【%s】",name.c_str(),cj[i].c_str());
	if (i>50)
	  printf("%s获得了隐藏成就：【%s】",name.c_str(),cj[i].c_str());
	printf("  %s",what_do[i].c_str());
	things[i+99]=1;
	if (i<=50)
	  happened+=(name+"获得了成就【"+cj[i]+"】/"); 
	if (i>50)
	  happened+=(name+"获得了隐藏成就【"+cj[i]+"】/"); 
	Write_File();//这么重大的事肯定得存档啊 
	Sleep(3000);
} 
void chengjiu()//查看成就 
{
	use(2);
	gs();
	int i,j,k,n,m;
	char l;
	i=1;
	bool flag=true;
	cout<<"按a查看上一个，按d查看下一个，按e退出\n";//采用ad翻页式 
	while(flag)
	  {
	  	l=_getch();
	  	cls();
	  	switch(l)
	  	  {
	  	  	case 'a':if (i>1)i--;break;
	  	  	case 'd':if (i<=cjnum)i++;break;
	  	  	case 'e':flag=false;break;
		  }
		gotoxy(3,0);
		if (i<=50||things[100+i-1])//这个需要特判一下 
		  printf("%d.[%s]\n",i,cj[i].c_str());
		else//如果是未完成的隐藏成就 
		  printf("%d.[隐藏成就]\n",i);
		if (things[i+99])
		  {
		  cout<<"（已完成）";
		  }
		else
		 {
		  cout<<"（未完成）";
		}
		if (i==5)
		  cout<<"完成进度："<<things[189]<<'/'<<27; 
		if (i==49)
		  cout<<"完成进度："<<things[84]<<'/'<<74;//某些成就需要给点进展提示 
		gotoxy(6,0);
		if (i<=50||things[100+i-1])
		  cout<<what_do[i];
		gotoxy(0,0);
		cout<<"按a查看上一个，按d查看下一个，按e退出\n";
	  }
}
int pingjia()//评价游戏 
{
	use(3);
	int star=0;
	bool lda=true;
	while(lda)
	  {
	  	int i;
	  	gotoxy(2,0);
	  	char nm;
	  	nm=_getch();
	  	for(i=1;i<=5-star;i++)
	  	  cout<<"★";
	  	for(;i<=5;i++)
	  	  cout<<"☆";
	  	gotoxy(3,0);
	  	cout<<"你给了"<<5-star<<"星";
	  	switch(nm)
	  	{
	  		case 'a':star++;break;
	  		case 'd':star--;break;
	  		case 'k':lda=false;break;
		}
		if (star<=0)
		  star=0;
		if (star>=5)
		  star=5;
	   } 
	   star=5-star; 
	if (star==0||star==1)
	  MessageBox(NULL,TEXT("你个没良心的，信不信我删你存档"),TEXT("诅咒"),0);
	if (star==2||star==3)
	  MessageBox(NULL,TEXT("建议给作者提点建议，以上是我的QQ号"),TEXT("3491576605"),0);
	if (star==4)
	  MessageBox(NULL,TEXT("就差一分就满星了，干嘛不给了呢？"),TEXT("。"),0);
	if (star==5)
	  MessageBox(NULL,TEXT("谢谢支持！"),TEXT("感谢"),0);
	if (star==0)
	  Sout("MCYH:******（口吐芬芳）"),system("shutdown -H");//恶作剧 
	return star;
} 
void welcome()//欢迎界面（水） 
{
	hidden();
	setcolor(blue,light_white);
	gotoxy(20,40);
	cout<<"人  生  之  路";
	gotoxy(21,40);
	cout<<"ren sheng zhi lu";
	Sleep(2000);
	cls();
	gotoxy(20,40);
	cout<<"ＧＣＺＸＸＸＢＣＤ";
	Sleep(200);
	gotoxy(21,40);
	Sout("  　　R i c h a r d");
	Sleep(1000);
	setcolor(blue,light_white);
	int i,j,k;
	for(k=1;i<=10;k++)
	{
	for(i=1;i<=47;i++)
	  for(j=1;j<=110;j++)
	    {
	    	gotoxy(i,j);
	    	cout<<char(random(2,120));//装模做样一下 
		}
	Sleep(90);
	}
	cls();
	gotoxy(20,45);
	cout<<"Richard出品，必是精品！\n";
	Sleep(2000);
	cls();
	setcolor(blue,light_white);
	hidden();
	i=0,j=0;
	while(i<=800&&j<=1500)
	  {
	  	i+=random(4,8)*10;
	  	j+=random(8,16)*10;
	  	gotoxy(0,0);
	  	cout<<"解析文件"<<i<<" of "<<j;//装模做样一下 
	  	Sleep(random(50,180));
	  }
	gotoxy(0,60);
	cout<<"\t\t\t\t\t\tｖ１．２０．０１．３２９５８５"; 
	gotoxy(0,0);
	printf("    ＷＥＬＣＯＭＥ            \n");
	printf("------------------------------------\n");
	printf("|                                  |\n");
	printf("|                                  |\n");
	printf("|                                  |\n");
	printf("|                                  |\n");
	printf("|                                  |\n");
	printf("|                                  |\n");
	printf("|                                  |\n");
	printf("|                                  |\n");
	printf("|__________________________________|\n");
	gotoxy(2,2);
	hidden();
	Sout("欢迎来到《人生之路》");
	gotoxy(3,2);
	Sout("作者：Richard\n");
	gotoxy(4,2);
	Sout("祝你游戏愉快\n");
	gotoxy(5,2);
	Sout("(*^_^*)\n");
	gs();
}
void Birthday()//庆生 
{
	use(4);
	cls();
	Sout("mtr:宝贝，生日‘快乐’！\n");
	Sout("ftr:生日‘快乐’！\n");
	things[10]++;
	if (things[10]==12)
	  things[0]++;
	gs();
}
int main()//主函数 
{
	ShellExecute(NULL,"open","cmd.exe /c attrib file1.txt +h",NULL,NULL,SW_SHOWNORMAL);
	mrf();
	cout<<"正在加载...请稍等...";
	int  cx   =   GetSystemMetrics(   SM_CXSCREEN   );   
	int  cy   =   GetSystemMetrics(   SM_CYSCREEN   );  //这些好像没啥用... 
	cout<<"屏幕大小:"<<cx<<"x"<<cy<<"\n"; 
	cout<<"正在调整为全屏模式~Loading...\n";
	system("mode con cols=300 lines=114"); 
	setcolor(light_blue,light_white);
	MessageBox(NULL,TEXT("点击右上角□即可调为全屏~"),TEXT("请调整为全屏模式"),MB_OK);
	MessageBox(NULL,TEXT("根据国家要求，未成年人只能在8点~22点获取游戏服务!"),TEXT("提示"),MB_OK);
	gs();
	srand(time(0));
	welcome();
	gs();
	hidden();
	if (baohu())
	  {
	  	gs();
	  	me.play=clock();
	  }
	cout<<"游戏基本规则：当选项左边出现数字（比如1. 2. 3.之类的）就需要按下序号进行移动，输入时请注意（数值禁止输入字符，否则直接卡退或存档混乱！）\n";
	cout<<"请选择：\n";
	cout<<"1.新建用户（覆盖或新建存档）\n";
	cout<<"2.继续游戏（读取存档）\n";
	char m=_getch();
	if (m=='1')//新建存档 
	  {
	  	namek();
	  	string number[10]={"0","1","2","3","4","5","6","7","8","9"};
	  	cout<<"覆盖哪个存档？\n";
	  	for(int i=1;i<=9;i++)
	  	  cout<<"存档"<<i<<"："<<filename[i]<<'\n';
	  	cin>>things[185];
	  	filename[things[185]]="新存档"+number[things[185]]; 
	  	cout<<"是否改存档名？（当前存档名："<<filename[things[185]]<<"）\n(Y/N)";
		char s;
		cin>>s;
		if (s=='Y')
		  {
		  	cout<<"改成什么？";
		  	cin>>filename[things[185]];
		  } 
		things[192]=1;//已读取，开始运行 
	  	show();//开始剧情 
	  }
	else
	  {
	  	cout<<"读取哪个存档？\n";
	  	for(int i=1;i<=9;i++)
	  	  if (filename[i]!="空存档")
	  	    cout<<"存档"<<i<<"："<<filename[i]<<'\n';
	  	cin>>things[185];
	  	int i=things[185];
	  	Read_File();
	  	things[185]=i;//防止存档被恶意毁坏 
 
	  	Time now=gottime();
	  	if (now.day!=Exit.day)
	  	  {
	  	  	Exit=gottime();
	  	  	cls();
	  		
		  }
	  	things[192]=1;
	  	jdt(10);
	  	mainmenu();//这是第二主函数，相当于剧情主干 
	  }
	
	return 0;
}
void Die()
{
	use(4);
	cls();
	sudu=500;
	setcolor(light_white,red);
	color(7);
	Sout("你	死	了	！\n");
	cout<<"┏┛墓┗┓...(((m -__-)m";
	things[190]++;
	sudu=100;
	if (things[187]==3)
	  hdcj(60);
	if (things[31])//emo沙漏 
	  {
	  	gs();
	  	gotoxy(15,50);
	  	cout<<"_____\n";
	  	gotoxy(16,50);
	  	cout<<" \\|/\n";
	  	gotoxy(17,50);
	  	cout<<" /|\\\n";
	  	gotoxy(18,50);
	  	cout<<"-----\n";
	  	Sleep(2000);
	  	gotoxy(40,35);
	  	cout<<name<<"使用了技能【时间回溯】将时间回溯至1分钟前，但是灵魂被恶魔沙漏反噬，仅剩150滴血";
	  	use(5);
	  	hdcj(42);
	  	happened+=(name+"死亡后复活了！/");
	  	things[31]--;
	  	things[2]=150;
	  	gs();
	  	return;
	   } 
	if (things[21]==4)//炼狱模式，删除存档（将22设为150后永远无法读取存档） 
	  	things[22]=150,Write_File(); 
	if (things[21]==3)//困难模式 
	  {
	  	cout<<"（你丢失了所有东西（精力，水分，饥饿。水分，攻击，血量，防御，成就除外）";
	  	for(int i=1;i<81;i++)
	  	if (i!=21&&i!=10)
	  	  things[i]=1;
	  	for(int i=0;i<100;i++)
	  	  fost[i]=0;
	  	things[3]=things[4]=100;
	  	things[8]=100;
	  	things[2]=100;
	  	things[5]=50;
	  	things[6]=20;
	  	things[30]=360;
	  }
	if (things[21]==2)//普通模式 
	  {
	  	cout<<"你的钱全丢了！";
	  	things[7]=0;
	  }
	if (things[21]==1)//简单模式 
	  cout<<"真幸运，什么都没丢";
	gs();
	cout<<"血量恢复至250,按1键继续，按e关机，或按其他退出";
	things[2]=250;
	Write_File(); 
	char l=_getch();
	if (l=='e')
	  system("Shutdown -H");// :)
	if (l!='1') 
	  me.play+=clock(),exit(0);
}
void mrf()//储存存档名称的存档 
{
	ifstream fin("save.MCYH");
	for(int i=1;i<=9;i++)
	  fin>>filename[i];
	fin.close();
}
void mwf()
{
	ofstream fout("save.MCYH");
	for(int i=1;i<=9;i++)
	  fout<<filename[i]<<'\n';
	fout.close();
}
void w1()
{
	ofstream fout("file1.a");
	use(6);
	fout<<name<<endl;
	for(int i=0;i<2000;i++)
	  fout<<things[i]<<' ';
	fout<<sudu<<'\n';
	for(int i=0;i<40;i++)
	  fout<<friends[i]<<' ';
	fout<<endl;
	for(int i=0;i<40;i++)
	  fout<<student[i]<<' ';
	for(int i=0;i<20;i++)
	  fout<<renwu[i]<<' ';
	fout<<endl;
	for(int i=0;i<200;i++)
	  fout<<fost[i]<<' ';
	fout<<endl<<start<<endl;
	for(int i=0;i<4;i++)
	  for(int j=0;j<5;j++)
	    fout<<has_fumo[i][j]<<' '; 
	fout<<endl<<kaishi<<endl;
	fout<<happened<<endl;
	for(int i=0;i<200;i++)
	  fout<<gn[i]<<' ';
	for(int i=0;i<50;i++)
	  fout<<pet[i].name<<' '<<pet[i].LX<<' '<<pet[i].attack<<' '<<pet[i].hp<<' '<<pet[i].run<<'\n';
	fout<<gotmoney<<'\n';
	fout<<me.y<<' '<<me.m<<' '<<me.d<<' '<<me.play<<' '<<me.age<<' '<<me.gang<<'\n';
	fout<<Exit.year<<' '<<Exit.month<<' '<<Exit.day<<' '<<Exit.hour<<' '<<Exit.minute<<' '<<Exit.second<<'\n';
	for(int i=1;i<31;i++)
	  {
	  	fout<<gang[i].pnum<<' '<<gang[i].name<<'\n';
	  	for(int j=1;j<50;j++)
	  	  fout<<gang[i].peo[j].name<<' '<<gang[i].peo[j].hp<<' '<<gang[i].peo[j].attack<<' '<<gang[i].peo[j].defence<<' '<<gang[i].peo[j].gang<<'\n';
		fout<<gang[i].leader<<'\n';
	  }
	fout<<gangth<<endl;
	fout.close();
}
void w2()
{
	ofstream fout("file2.b");
	use(6);
	fout<<name<<endl;
	for(int i=0;i<2000;i++)
	  fout<<things[i]<<' ';
	fout<<sudu<<'\n';
	for(int i=0;i<40;i++)
	  fout<<friends[i]<<' ';
	fout<<endl;
	for(int i=0;i<40;i++)
	  fout<<student[i]<<' ';
	for(int i=0;i<20;i++)
	  fout<<renwu[i]<<' ';
	fout<<endl;
	for(int i=0;i<200;i++)
	  fout<<fost[i]<<' ';
	fout<<endl<<start<<endl;
	for(int i=0;i<4;i++)
	  for(int j=0;j<5;j++)
	    fout<<has_fumo[i][j]<<' '; 
	fout<<endl<<kaishi<<endl;
	fout<<happened<<endl;
	for(int i=0;i<200;i++)
	  fout<<gn[i]<<' ';
	for(int i=0;i<50;i++)
	  fout<<pet[i].name<<' '<<pet[i].LX<<' '<<pet[i].attack<<' '<<pet[i].hp<<' '<<pet[i].run<<'\n';
	fout<<gotmoney<<'\n';
	fout<<me.y<<' '<<me.m<<' '<<me.d<<' '<<me.play<<' '<<me.age<<' '<<me.gang<<'\n';
	fout<<Exit.year<<' '<<Exit.month<<' '<<Exit.day<<' '<<Exit.hour<<' '<<Exit.minute<<' '<<Exit.second<<'\n';
	for(int i=1;i<31;i++)
	  {
	  	fout<<gang[i].pnum<<' '<<gang[i].name<<'\n';
	  	for(int j=1;j<50;j++)
	  	  fout<<gang[i].peo[j].name<<' '<<gang[i].peo[j].hp<<' '<<gang[i].peo[j].attack<<' '<<gang[i].peo[j].defence<<' '<<gang[i].peo[j].gang<<'\n';
		fout<<gang[i].leader<<'\n';
	  }
	fout<<gangth<<endl;
	fout.close();
}
void w3()
{
	ofstream fout("file3.c++");
	use(6);
	fout<<name<<endl;
	for(int i=0;i<2000;i++)
	  fout<<things[i]<<' ';
	fout<<sudu<<'\n';
	for(int i=0;i<40;i++)
	  fout<<friends[i]<<' ';
	fout<<endl;
	for(int i=0;i<40;i++)
	  fout<<student[i]<<' ';
	for(int i=0;i<20;i++)
	  fout<<renwu[i]<<' ';
	fout<<endl;
	for(int i=0;i<200;i++)
	  fout<<fost[i]<<' ';
	fout<<endl<<start<<endl;
	for(int i=0;i<4;i++)
	  for(int j=0;j<5;j++)
	    fout<<has_fumo[i][j]<<' '; 
	fout<<endl<<kaishi<<endl;
	fout<<happened<<endl;
	for(int i=0;i<200;i++)
	  fout<<gn[i]<<' ';
	for(int i=0;i<50;i++)
	  fout<<pet[i].name<<' '<<pet[i].LX<<' '<<pet[i].attack<<' '<<pet[i].hp<<' '<<pet[i].run<<'\n';
	fout<<gotmoney<<'\n';
	fout<<me.y<<' '<<me.m<<' '<<me.d<<' '<<me.play<<' '<<me.age<<' '<<me.gang<<'\n';
	fout<<Exit.year<<' '<<Exit.month<<' '<<Exit.day<<' '<<Exit.hour<<' '<<Exit.minute<<' '<<Exit.second<<'\n';
	for(int i=1;i<31;i++)
	  {
	  	fout<<gang[i].pnum<<' '<<gang[i].name<<'\n';
	  	for(int j=1;j<50;j++)
	  	  fout<<gang[i].peo[j].name<<' '<<gang[i].peo[j].hp<<' '<<gang[i].peo[j].attack<<' '<<gang[i].peo[j].defence<<' '<<gang[i].peo[j].gang<<'\n';
		fout<<gang[i].leader<<'\n';
	  }
	fout<<gangth<<endl;
	fout.close();
}
void w4()
{
	ofstream fout("file4.d");
	use(6);
	fout<<name<<endl;
	for(int i=0;i<2000;i++)
	  fout<<things[i]<<' ';
	fout<<sudu<<'\n';
	for(int i=0;i<40;i++)
	  fout<<friends[i]<<' ';
	fout<<endl;
	for(int i=0;i<40;i++)
	  fout<<student[i]<<' ';
	for(int i=0;i<20;i++)
	  fout<<renwu[i]<<' ';
	fout<<endl;
	for(int i=0;i<200;i++)
	  fout<<fost[i]<<' ';
	fout<<endl<<start<<endl;
	for(int i=0;i<4;i++)
	  for(int j=0;j<5;j++)
	    fout<<has_fumo[i][j]<<' '; 
	fout<<endl<<kaishi<<endl;
	fout<<happened<<endl;
	for(int i=0;i<200;i++)
	  fout<<gn[i]<<' ';
	for(int i=0;i<50;i++)
	  fout<<pet[i].name<<' '<<pet[i].LX<<' '<<pet[i].attack<<' '<<pet[i].hp<<' '<<pet[i].run<<'\n';
	fout<<gotmoney<<'\n';
	fout<<me.y<<' '<<me.m<<' '<<me.d<<' '<<me.play<<' '<<me.age<<' '<<me.gang<<'\n';
	fout<<Exit.year<<' '<<Exit.month<<' '<<Exit.day<<' '<<Exit.hour<<' '<<Exit.minute<<' '<<Exit.second<<'\n';
	for(int i=1;i<31;i++)
	  {
	  	fout<<gang[i].pnum<<' '<<gang[i].name<<'\n';
	  	for(int j=1;j<50;j++)
	  	  fout<<gang[i].peo[j].name<<' '<<gang[i].peo[j].hp<<' '<<gang[i].peo[j].attack<<' '<<gang[i].peo[j].defence<<' '<<gang[i].peo[j].gang<<'\n';
		fout<<gang[i].leader<<'\n';
	  }
	fout<<gangth<<endl;
	fout.close();
}
void w5()
{
	ofstream fout("file5.e");
	use(6);
	fout<<name<<endl;
	for(int i=0;i<2000;i++)
	  fout<<things[i]<<' ';
	fout<<sudu<<'\n';
	for(int i=0;i<40;i++)
	  fout<<friends[i]<<' ';
	fout<<endl;
	for(int i=0;i<40;i++)
	  fout<<student[i]<<' ';
	for(int i=0;i<20;i++)
	  fout<<renwu[i]<<' ';
	fout<<endl;
	for(int i=0;i<200;i++)
	  fout<<fost[i]<<' ';
	fout<<endl<<start<<endl;
	for(int i=0;i<4;i++)
	  for(int j=0;j<5;j++)
	    fout<<has_fumo[i][j]<<' '; 
	fout<<endl<<kaishi<<endl;
	fout<<happened<<endl;
	for(int i=0;i<200;i++)
	  fout<<gn[i]<<' ';
	for(int i=0;i<50;i++)
	  fout<<pet[i].name<<' '<<pet[i].LX<<' '<<pet[i].attack<<' '<<pet[i].hp<<' '<<pet[i].run<<'\n';
	fout<<gotmoney<<'\n';
	fout<<me.y<<' '<<me.m<<' '<<me.d<<' '<<me.play<<' '<<me.age<<' '<<me.gang<<'\n';
	fout<<Exit.year<<' '<<Exit.month<<' '<<Exit.day<<' '<<Exit.hour<<' '<<Exit.minute<<' '<<Exit.second<<'\n';
	for(int i=1;i<31;i++)
	  {
	  	fout<<gang[i].pnum<<' '<<gang[i].name<<'\n';
	  	for(int j=1;j<50;j++)
	  	  fout<<gang[i].peo[j].name<<' '<<gang[i].peo[j].hp<<' '<<gang[i].peo[j].attack<<' '<<gang[i].peo[j].defence<<' '<<gang[i].peo[j].gang<<'\n';
		fout<<gang[i].leader<<'\n';
	  }
	fout<<gangth<<endl;
	fout.close();
}
void w6()
{
	ofstream fout("file6.f");
	use(6);
	fout<<name<<endl;
	for(int i=0;i<2000;i++)
	  fout<<things[i]<<' ';
	fout<<sudu<<'\n';
	for(int i=0;i<40;i++)
	  fout<<friends[i]<<' ';
	fout<<endl;
	for(int i=0;i<40;i++)
	  fout<<student[i]<<' ';
	for(int i=0;i<20;i++)
	  fout<<renwu[i]<<' ';
	fout<<endl;
	for(int i=0;i<200;i++)
	  fout<<fost[i]<<' ';
	fout<<endl<<start<<endl;
	for(int i=0;i<4;i++)
	  for(int j=0;j<5;j++)
	    fout<<has_fumo[i][j]<<' '; 
	fout<<endl<<kaishi<<endl;
	fout<<happened<<endl;
	for(int i=0;i<200;i++)
	  fout<<gn[i]<<' ';
	for(int i=0;i<50;i++)
	  fout<<pet[i].name<<' '<<pet[i].LX<<' '<<pet[i].attack<<' '<<pet[i].hp<<' '<<pet[i].run<<'\n';
	fout<<gotmoney<<'\n';
	fout<<me.y<<' '<<me.m<<' '<<me.d<<' '<<me.play<<' '<<me.age<<' '<<me.gang<<'\n';
	fout<<Exit.year<<' '<<Exit.month<<' '<<Exit.day<<' '<<Exit.hour<<' '<<Exit.minute<<' '<<Exit.second<<'\n';
	for(int i=1;i<31;i++)
	  {
	  	fout<<gang[i].pnum<<' '<<gang[i].name<<'\n';
	  	for(int j=1;j<50;j++)
	  	  fout<<gang[i].peo[j].name<<' '<<gang[i].peo[j].hp<<' '<<gang[i].peo[j].attack<<' '<<gang[i].peo[j].defence<<' '<<gang[i].peo[j].gang<<'\n';
		fout<<gang[i].leader<<'\n';
	  }
	fout<<gangth<<endl;
	fout.close();
}
void w7()
{
	ofstream fout("file7.gxc");
	use(6);
	fout<<name<<endl;
	for(int i=0;i<2000;i++)
	  fout<<things[i]<<' ';
	fout<<sudu<<'\n';
	for(int i=0;i<40;i++)
	  fout<<friends[i]<<' ';
	fout<<endl;
	for(int i=0;i<40;i++)
	  fout<<student[i]<<' ';
	for(int i=0;i<20;i++)
	  fout<<renwu[i]<<' ';
	fout<<endl;
	for(int i=0;i<200;i++)
	  fout<<fost[i]<<' ';
	fout<<endl<<start<<endl;
	for(int i=0;i<4;i++)
	  for(int j=0;j<5;j++)
	    fout<<has_fumo[i][j]<<' '; 
	fout<<endl<<kaishi<<endl;
	fout<<happened<<endl;
	for(int i=0;i<200;i++)
	  fout<<gn[i]<<' ';
	for(int i=0;i<50;i++)
	  fout<<pet[i].name<<' '<<pet[i].LX<<' '<<pet[i].attack<<' '<<pet[i].hp<<' '<<pet[i].run<<'\n';
	fout<<gotmoney<<'\n';
	fout<<me.y<<' '<<me.m<<' '<<me.d<<' '<<me.play<<' '<<me.age<<' '<<me.gang<<'\n';
	fout<<Exit.year<<' '<<Exit.month<<' '<<Exit.day<<' '<<Exit.hour<<' '<<Exit.minute<<' '<<Exit.second<<'\n';
	for(int i=1;i<31;i++)
	  {
	  	fout<<gang[i].pnum<<' '<<gang[i].name<<'\n';
	  	for(int j=1;j<50;j++)
	  	  fout<<gang[i].peo[j].name<<' '<<gang[i].peo[j].hp<<' '<<gang[i].peo[j].attack<<' '<<gang[i].peo[j].defence<<' '<<gang[i].peo[j].gang<<'\n';
		fout<<gang[i].leader<<'\n';
	  }
	fout<<gangth<<endl;
	fout.close();
}
void w8()
{
	ofstream fout("file8.hec");
	use(6);
	fout<<name<<endl;
	for(int i=0;i<2000;i++)
	  fout<<things[i]<<' ';
	fout<<sudu<<'\n';
	for(int i=0;i<40;i++)
	  fout<<friends[i]<<' ';
	fout<<endl;
	for(int i=0;i<40;i++)
	  fout<<student[i]<<' ';
	for(int i=0;i<20;i++)
	  fout<<renwu[i]<<' ';
	fout<<endl;
	for(int i=0;i<200;i++)
	  fout<<fost[i]<<' ';
	fout<<endl<<start<<endl;
	for(int i=0;i<4;i++)
	  for(int j=0;j<5;j++)
	    fout<<has_fumo[i][j]<<' '; 
	fout<<endl<<kaishi<<endl;
	fout<<happened<<endl;
	for(int i=0;i<200;i++)
	  fout<<gn[i]<<' ';
	for(int i=0;i<50;i++)
	  fout<<pet[i].name<<' '<<pet[i].LX<<' '<<pet[i].attack<<' '<<pet[i].hp<<' '<<pet[i].run<<'\n';
	fout<<gotmoney<<'\n';
	fout<<me.y<<' '<<me.m<<' '<<me.d<<' '<<me.play<<' '<<me.age<<' '<<me.gang<<'\n';
	fout<<Exit.year<<' '<<Exit.month<<' '<<Exit.day<<' '<<Exit.hour<<' '<<Exit.minute<<' '<<Exit.second<<'\n';
	for(int i=1;i<31;i++)
	  {
	  	fout<<gang[i].pnum<<' '<<gang[i].name<<'\n';
	  	for(int j=1;j<50;j++)
	  	  fout<<gang[i].peo[j].name<<' '<<gang[i].peo[j].hp<<' '<<gang[i].peo[j].attack<<' '<<gang[i].peo[j].defence<<' '<<gang[i].peo[j].gang<<'\n';
		fout<<gang[i].leader<<'\n';
	  }
	fout<<gangth<<endl;
	fout.close();
}
void w9()
{
	ofstream fout("file9.init");
	use(6);
	fout<<name<<endl;
	for(int i=0;i<2000;i++)
	  fout<<things[i]<<' ';
	fout<<sudu<<'\n';
	for(int i=0;i<40;i++)
	  fout<<friends[i]<<' ';
	fout<<endl;
	for(int i=0;i<40;i++)
	  fout<<student[i]<<' ';
	for(int i=0;i<20;i++)
	  fout<<renwu[i]<<' ';
	fout<<endl;
	for(int i=0;i<200;i++)
	  fout<<fost[i]<<' ';
	fout<<endl<<start<<endl;
	for(int i=0;i<4;i++)
	  for(int j=0;j<5;j++)
	    fout<<has_fumo[i][j]<<' '; 
	fout<<endl<<kaishi<<endl;
	fout<<happened<<endl;
	for(int i=0;i<200;i++)
	  fout<<gn[i]<<' ';
	for(int i=0;i<50;i++)
	  fout<<pet[i].name<<' '<<pet[i].LX<<' '<<pet[i].attack<<' '<<pet[i].hp<<' '<<pet[i].run<<'\n';
	fout<<gotmoney<<'\n';
	fout<<me.y<<' '<<me.m<<' '<<me.d<<' '<<me.play<<' '<<me.age<<' '<<me.gang<<'\n';
	fout<<Exit.year<<' '<<Exit.month<<' '<<Exit.day<<' '<<Exit.hour<<' '<<Exit.minute<<' '<<Exit.second<<'\n';
	for(int i=1;i<31;i++)
	  {
	  	fout<<gang[i].pnum<<' '<<gang[i].name<<'\n';
	  	for(int j=1;j<50;j++)
	  	  fout<<gang[i].peo[j].name<<' '<<gang[i].peo[j].hp<<' '<<gang[i].peo[j].attack<<' '<<gang[i].peo[j].defence<<' '<<gang[i].peo[j].gang<<'\n';
		fout<<gang[i].leader<<'\n';
	  }
	fout<<gangth<<endl;
	fout.close();
}
void Write_File()
{
	Exit=gottime();
	if (things[192]==0)
	  return;
	switch(things[185])
	  { 
	  	case 1:w1();break;
	  	case 2:w2();break;
	  	case 3:w3();break;
	  	case 4:w4();break;
	  	case 5:w5();break;
	  	case 6:w6();break;
	  	case 7:w7();break;
	  	case 8:w8();break;
	  	case 9:w9();break;
	  	default:cout<<things[185]<<"[error] 404";Sleep(5000);me.play+=clock(),exit(0);
	  }
}
void r1()
{
	ifstream fin("file1.a");
	fin>>name;
	for(int i=0;i<2000;i++)
	  fin>>things[i];
	fin>>sudu;
	for(int i=0;i<40;i++)
	  fin>>friends[i];
	for(int i=0;i<40;i++)
	  fin>>student[i];
	for(int i=0;i<20;i++)
	  fin>>renwu[i];
	for(int i=0;i<200;i++)
	  fin>>fost[i];
	long long temp;
	fin>>temp;
	if (temp!=0) 
	  start=temp;
	else
	  {
	  	time_t guodu;
	  	time(&guodu);
	  	start=guodu;
	  }
	for(int i=0;i<4;i++)
	  for(int j=0;j<5;j++)
	    fin>>has_fumo[i][j];
	fin>>kaishi;
	fin>>happened;
	for(int i=0;i<200;i++)
	  fin>>gn[i];
	for(int i=0;i<50;i++)
	  fin>>pet[i].name>>pet[i].LX>>pet[i].attack>>pet[i].hp>>pet[i].run;
	fin>>gotmoney;
	fin>>me.y>>me.m>>me.d>>me.play>>me.age>>me.gang;
	fin>>Exit.year>>Exit.month>>Exit.day>>Exit.hour>>Exit.minute>>Exit.second;
	for(int i=1;i<31;i++)
	  {
	  	fin>>gang[i].pnum>>gang[i].name;
	  	for(int j=1;j<50;j++)
	  	  fin>>gang[i].peo[j].name>>gang[i].peo[j].hp>>gang[i].peo[j].attack>>gang[i].peo[j].defence>>gang[i].peo[j].gang;
		fin>>gang[i].leader;
	  }
	fin>>gangth;
	fin.close();
}
void r2()
{
	ifstream fin("file2.b");
	fin>>name;
	for(int i=0;i<2000;i++)
	  fin>>things[i];
	fin>>sudu;
	for(int i=0;i<40;i++)
	  fin>>friends[i];
	for(int i=0;i<40;i++)
	  fin>>student[i];
	for(int i=0;i<20;i++)
	  fin>>renwu[i];
	for(int i=0;i<200;i++)
	  fin>>fost[i];
	long long temp;
	fin>>temp;
	if (temp!=0) 
	  start=temp;
	else
	  {
	  	time_t guodu;
	  	time(&guodu);
	  	start=guodu;
	  }
	for(int i=0;i<4;i++)
	  for(int j=0;j<5;j++)
	    fin>>has_fumo[i][j];
	fin>>kaishi;
	fin>>happened;
	for(int i=0;i<2000;i++)
	  fin>>gn[i];
	for(int i=0;i<50;i++)
	  fin>>pet[i].name>>pet[i].LX>>pet[i].attack>>pet[i].hp>>pet[i].run;
	fin>>gotmoney;
	fin>>me.y>>me.m>>me.d>>me.play>>me.age>>me.gang;
	fin>>Exit.year>>Exit.month>>Exit.day>>Exit.hour>>Exit.minute>>Exit.second;
	for(int i=1;i<31;i++)
	  {
	  	fin>>gang[i].pnum>>gang[i].name;
	  	for(int j=1;j<50;j++)
	  	  fin>>gang[i].peo[j].name>>gang[i].peo[j].hp>>gang[i].peo[j].attack>>gang[i].peo[j].defence>>gang[i].peo[j].gang;
		fin>>gang[i].leader;
	  }
	fin>>gangth;
	fin.close();
}
void r3()
{
	ifstream fin("file3.c++");
	fin>>name;
	for(int i=0;i<2000;i++)
	  fin>>things[i];
	fin>>sudu;
	for(int i=0;i<40;i++)
	  fin>>friends[i];
	for(int i=0;i<40;i++)
	  fin>>student[i];
	for(int i=0;i<20;i++)
	  fin>>renwu[i];
	for(int i=0;i<200;i++)
	  fin>>fost[i];
	long long temp;
	fin>>temp;
	if (temp!=0) 
	  start=temp;
	else
	  {
	  	time_t guodu;
	  	time(&guodu);
	  	start=guodu;
	  }
	for(int i=0;i<4;i++)
	  for(int j=0;j<5;j++)
	    fin>>has_fumo[i][j];
	fin>>kaishi;
	fin>>happened;
	for(int i=0;i<2000;i++)
	  fin>>gn[i];
	for(int i=0;i<50;i++)
	  fin>>pet[i].name>>pet[i].LX>>pet[i].attack>>pet[i].hp>>pet[i].run;
	fin>>gotmoney;
	fin>>me.y>>me.m>>me.d>>me.play>>me.age>>me.gang;
	fin>>Exit.year>>Exit.month>>Exit.day>>Exit.hour>>Exit.minute>>Exit.second;
	for(int i=1;i<31;i++)
	  {
	  	fin>>gang[i].pnum>>gang[i].name;
	  	for(int j=1;j<50;j++)
	  	  fin>>gang[i].peo[j].name>>gang[i].peo[j].hp>>gang[i].peo[j].attack>>gang[i].peo[j].defence>>gang[i].peo[j].gang;
		fin>>gang[i].leader;
	  }
	fin>>gangth;
	fin.close();
}
void r4()
{
	ifstream fin("file4.d");
	fin>>name;
	for(int i=0;i<2000;i++)
	  fin>>things[i];
	fin>>sudu;
	for(int i=0;i<40;i++)
	  fin>>friends[i];
	for(int i=0;i<40;i++)
	  fin>>student[i];
	for(int i=0;i<20;i++)
	  fin>>renwu[i];
	for(int i=0;i<200;i++)
	  fin>>fost[i];
	long long temp;
	fin>>temp;
	if (temp!=0) 
	  start=temp;
	else
	  {
	  	time_t guodu;
	  	time(&guodu);
	  	start=guodu;
	  }
	for(int i=0;i<4;i++)
	  for(int j=0;j<5;j++)
	    fin>>has_fumo[i][j];
	fin>>kaishi;
	fin>>happened;
	for(int i=0;i<200;i++)
	  fin>>gn[i];
	for(int i=0;i<50;i++)
	  fin>>pet[i].name>>pet[i].LX>>pet[i].attack>>pet[i].hp>>pet[i].run;
	fin>>gotmoney;
	fin>>me.y>>me.m>>me.d>>me.play>>me.age>>me.gang;
	fin>>Exit.year>>Exit.month>>Exit.day>>Exit.hour>>Exit.minute>>Exit.second;
	for(int i=1;i<31;i++)
	  {
	  	fin>>gang[i].pnum>>gang[i].name;
	  	for(int j=1;j<50;j++)
	  	  fin>>gang[i].peo[j].name>>gang[i].peo[j].hp>>gang[i].peo[j].attack>>gang[i].peo[j].defence>>gang[i].peo[j].gang;
		fin>>gang[i].leader;
	  }
	fin>>gangth;
	fin.close();
}
void r5()
{
	ifstream fin("file5.e");
	fin>>name;
	for(int i=0;i<2000;i++)
	  fin>>things[i];
	fin>>sudu;
	for(int i=0;i<40;i++)
	  fin>>friends[i];
	for(int i=0;i<40;i++)
	  fin>>student[i];
	for(int i=0;i<20;i++)
	  fin>>renwu[i];
	for(int i=0;i<200;i++)
	  fin>>fost[i];
	long long temp;
	fin>>temp;
	if (temp!=0) 
	  start=temp;
	else
	  {
	  	time_t guodu;
	  	time(&guodu);
	  	start=guodu;
	  }
	for(int i=0;i<4;i++)
	  for(int j=0;j<5;j++)
	    fin>>has_fumo[i][j];
	fin>>kaishi;
	fin>>happened;
	for(int i=0;i<200;i++)
	  fin>>gn[i];
	for(int i=0;i<50;i++)
	  fin>>pet[i].name>>pet[i].LX>>pet[i].attack>>pet[i].hp>>pet[i].run;
	fin>>gotmoney;
	fin>>me.y>>me.m>>me.d>>me.play>>me.age>>me.gang;
	fin>>Exit.year>>Exit.month>>Exit.day>>Exit.hour>>Exit.minute>>Exit.second;
	for(int i=1;i<31;i++)
	  {
	  	fin>>gang[i].pnum>>gang[i].name;
	  	for(int j=1;j<50;j++)
	  	  fin>>gang[i].peo[j].name>>gang[i].peo[j].hp>>gang[i].peo[j].attack>>gang[i].peo[j].defence>>gang[i].peo[j].gang;
		fin>>gang[i].leader;
	  }
	fin>>gangth;
	fin.close();
}
void r6()
{
	ifstream fin("file6.f");
	fin>>name;
	for(int i=0;i<2000;i++)
	  fin>>things[i];
	fin>>sudu;
	for(int i=0;i<40;i++)
	  fin>>friends[i];
	for(int i=0;i<40;i++)
	  fin>>student[i];
	for(int i=0;i<20;i++)
	  fin>>renwu[i];
	for(int i=0;i<200;i++)
	  fin>>fost[i];
	long long temp;
	fin>>temp;
	if (temp!=0) 
	  start=temp;
	else
	  {
	  	time_t guodu;
	  	time(&guodu);
	  	start=guodu;
	  }
	for(int i=0;i<4;i++)
	  for(int j=0;j<5;j++)
	    fin>>has_fumo[i][j];
	fin>>kaishi;
	fin>>happened;
	for(int i=0;i<200;i++)
	  fin>>gn[i];
	for(int i=0;i<50;i++)
	  fin>>pet[i].name>>pet[i].LX>>pet[i].attack>>pet[i].hp>>pet[i].run;
	fin>>gotmoney;
	fin>>me.y>>me.m>>me.d>>me.play>>me.age>>me.gang;
	fin>>Exit.year>>Exit.month>>Exit.day>>Exit.hour>>Exit.minute>>Exit.second;
	for(int i=1;i<31;i++)
	  {
	  	fin>>gang[i].pnum>>gang[i].name;
	  	for(int j=1;j<50;j++)
	  	  fin>>gang[i].peo[j].name>>gang[i].peo[j].hp>>gang[i].peo[j].attack>>gang[i].peo[j].defence>>gang[i].peo[j].gang;
		fin>>gang[i].leader;
	  }
	fin>>gangth;
	fin.close();
}
void r7()
{
	ifstream fin("file7.gxc");
	fin>>name;
	for(int i=0;i<2000;i++)
	  fin>>things[i];
	fin>>sudu;
	for(int i=0;i<40;i++)
	  fin>>friends[i];
	for(int i=0;i<40;i++)
	  fin>>student[i];
	for(int i=0;i<20;i++)
	  fin>>renwu[i];
	for(int i=0;i<200;i++)
	  fin>>fost[i];
	long long temp;
	fin>>temp;
	if (temp!=0) 
	  start=temp;
	else
	  {
	  	time_t guodu;
	  	time(&guodu);
	  	start=guodu;
	  }
	for(int i=0;i<4;i++)
	  for(int j=0;j<5;j++)
	    fin>>has_fumo[i][j];
	fin>>kaishi;
	fin>>happened;
	for(int i=0;i<200;i++)
	  fin>>gn[i];
	for(int i=0;i<50;i++)
	  fin>>pet[i].name>>pet[i].LX>>pet[i].attack>>pet[i].hp>>pet[i].run;
	fin>>gotmoney;
	fin>>me.y>>me.m>>me.d>>me.play>>me.age>>me.gang;
	fin>>Exit.year>>Exit.month>>Exit.day>>Exit.hour>>Exit.minute>>Exit.second;
	for(int i=1;i<31;i++)
	  {
	  	fin>>gang[i].pnum>>gang[i].name;
	  	for(int j=1;j<50;j++)
	  	  fin>>gang[i].peo[j].name>>gang[i].peo[j].hp>>gang[i].peo[j].attack>>gang[i].peo[j].defence>>gang[i].peo[j].gang;
		fin>>gang[i].leader;
	  }
	fin>>gangth;
	fin.close();
}
void r8()
{
	ifstream fin("file8.hec");
	fin>>name;
	for(int i=0;i<2000;i++)
	  fin>>things[i];
	fin>>sudu;
	for(int i=0;i<40;i++)
	  fin>>friends[i];
	for(int i=0;i<40;i++)
	  fin>>student[i];
	for(int i=0;i<20;i++)
	  fin>>renwu[i];
	for(int i=0;i<200;i++)
	  fin>>fost[i];
	long long temp;
	fin>>temp;
	if (temp!=0) 
	  start=temp;
	else
	  {
	  	time_t guodu;
	  	time(&guodu);
	  	start=guodu;
	  }
	for(int i=0;i<4;i++)
	  for(int j=0;j<5;j++)
	    fin>>has_fumo[i][j];
	fin>>kaishi;
	fin>>happened;
	for(int i=0;i<200;i++)
	  fin>>gn[i];
	for(int i=0;i<50;i++)
	  fin>>pet[i].name>>pet[i].LX>>pet[i].attack>>pet[i].hp>>pet[i].run;
	fin>>gotmoney;
	fin>>me.y>>me.m>>me.d>>me.play>>me.age>>me.gang;
	fin>>Exit.year>>Exit.month>>Exit.day>>Exit.hour>>Exit.minute>>Exit.second;
	for(int i=1;i<31;i++)
	  {
	  	fin>>gang[i].pnum>>gang[i].name;
	  	for(int j=1;j<50;j++)
	  	  fin>>gang[i].peo[j].name>>gang[i].peo[j].hp>>gang[i].peo[j].attack>>gang[i].peo[j].defence>>gang[i].peo[j].gang;
		fin>>gang[i].leader;
	  }
	fin>>gangth;
	fin.close();
}
void r9()
{
	ifstream fin("file9.init");
	fin>>name;
	for(int i=0;i<2000;i++)
	  fin>>things[i];
	fin>>sudu;
	for(int i=0;i<40;i++)
	  fin>>friends[i];
	for(int i=0;i<40;i++)
	  fin>>student[i];
	for(int i=0;i<20;i++)
	  fin>>renwu[i];
	for(int i=0;i<200;i++)
	  fin>>fost[i];
	long long temp;
	fin>>temp;
	if (temp!=0) 
	  start=temp;
	else
	  {
	  	time_t guodu;
	  	time(&guodu);
	  	start=guodu;
	  }
	for(int i=0;i<4;i++)
	  for(int j=0;j<5;j++)
	    fin>>has_fumo[i][j];
	fin>>kaishi;
	fin>>happened;
	for(int i=0;i<200;i++)
	  fin>>gn[i];
	for(int i=0;i<50;i++)
	  fin>>pet[i].name>>pet[i].LX>>pet[i].attack>>pet[i].hp>>pet[i].run;
	fin>>gotmoney;
	fin>>me.y>>me.m>>me.d>>me.play>>me.age>>me.gang;
	fin>>Exit.year>>Exit.month>>Exit.day>>Exit.hour>>Exit.minute>>Exit.second;
	for(int i=1;i<31;i++)
	  {
	  	fin>>gang[i].pnum>>gang[i].name;
	  	for(int j=1;j<50;j++)
	  	  fin>>gang[i].peo[j].name>>gang[i].peo[j].hp>>gang[i].peo[j].attack>>gang[i].peo[j].defence>>gang[i].peo[j].gang;
		fin>>gang[i].leader;
	  }
	fin>>gangth;
	fin.close();
}
void Read_File()
{
	switch(things[185])
	  {
	  	case 1:r1();break;
	  	case 2:r2();break;
	  	case 3:r3();break;
	  	case 4:r4();break;
	  	case 5:r5();break;
	  	case 6:r6();break;
	  	case 7:r7();break;
	  	case 8:r8();break;
	  	case 9:r9();break;
	  	default:cout<<"[error] 找不到存档";Sleep(5000);me.play+=clock();exit(0);
	  }
	if (things[34]!=12001)//1.20的更新，更新旧版本不兼容的存档 
	  {
	  	for(int i=1;i<30;i++)
	  {
	  	gang[i].pnum=random(2,40);
	  	gang[i].name=randstr(5,21);
	  	for(int j=1;j<=gang[i].pnum;j++)
	  	  {
	  	  	gang[i].peo[j]=born(i);
		  }
		gang[i].leader=random(1,gang[i].pnum);
	  }
	  things[34]=12001,things[117]=0,things[127]=0;
	  Write_File(); 
	  }
}
void about()
{
	cls();
	use(7);
	Sout("游戏作者：沉迷学习的MCYH\n\n");
	Sout("游戏版本：v1.20.01.334778\n\n");
	Sout("作者QQ：3491576605\n\n");
	Sout("祝你玩得愉快！\n\n");
	Sout("按任意键返回\n\n");
	gs();
	return;
}
void shuoming()
{
	;//废 
}
char* randstr(int n,int m)//随机字符串 
{
	int i,j;
	char abc[50];
	for(i=0;i<random(n,m);i++)
	  abc[i]=rand()%4?random('a','z'):random('A','Z');
	return abc;
}
void show()
{
	things[270]=0;
	shuoming();
	time_t ld;
	time(&ld);
	kaishi=ld;
	cout<<"当前时间刻："<<kaishi;
	gs();
	Write_File(); 
	string sm="";
	things[30]=720; 
	srand(time(0));
	memset(friends,0,sizeof(friends));
	things[19]=rand()%40;
	color(6);
	gs();
	srand(time(0));
	for(int i=0;i<40;i++)
	  {
	  	student[i]=studentname[i];
	  }
	string sn;
	memset(gn,false,sizeof(gn));
	cout<<"enter your name↙:__________(输入.加enter自动起名)";
	gotoxy(0,20);
	cin>>sn;
	happened+=(sn+"出生了/");
	int m;
	if (sn==".")
	  {
	  	char a,b,c;
	  	do
	  	  {
	  	  sn=randstr(3,12);
		  gotoxy(6,20);
		  printf("Your name:%s            ",sn.c_str());
		  gotoxy(7,20);
		  cout<<"按h重新起名，其他退出";
		  a=_getch();
		  }
		while(a=='h');
	  }
	student[things[19]]=sn;
	name=sn;
	cout<<"请选择游戏难度：\n";
	cout<<"1.简单模式（非常简单，死了什么都不会丢，适合新手）\n";
	cout<<"2.中等模式（运气比较差，怪物比较强（包括你同学），死亡后会丢失所有金钱，适合第二次玩的同学）\n";
	cout<<"3.困难模式（运气特别差，怪物特别强（包括你同学），死亡后会丢失所有东西，重置你的等级和血量，章节进度和挂机收益不会改变，适合玩过4次以上的老玩家））\n";
	cout<<"4.炼狱模式（运气极差，怪物极强（包括你同学），死亡后存档会丢失，适合勇敢的挑战者（大师））\n";
	cin>>things[21];
	student[things[19]]=name;
	if ((name[0]=='M'||name[0]=='m')&&(name[1]=='C'||name[1]=='c')&&(name[2]=='Y'||name[2]=='y')&&(name[3]=='H'||name[3]=='h')||name=="MC夜丶痕"||name=="zjl"||name=="夜丶痕"||name=="作者"||name=="我是作者")
	  {
	  	Sout("嘿，伙计！你不能用这个名字！这是作者的名字，按0键退出游戏！（你敢按其他键吗？）");
	  	char m=_getch();
	  	if (m=='0')
	  	  me.play+=clock(),exit(0);
	  	cls();
	  	Sout("调皮，接受诅咒吧！");
	  	MessageBox(NULL,TEXT("吗尼吗尼哄！"),TEXT("关机咒"),0);//...
	  	system("shutdown -H");
	  	while(1)//这两行代码， 
	  	  Sleep(100);//永远也不会运行 
	  }
	hdcj(1);
	cls();
	sudu=15;
	//无聊的剧情 
	Sout("人生就是一条路，但它不是一条平坦的路。");
	gs();
	Sout("你叫"+name+"，是一个学生。");
	gs();
	Sout("你以为自己很聪明，但是实际上。。。");
	gs();
	Sout("你就是个学灰。你经常逃课去网吧，有一次...");
	gs();
	Sout("你又习惯性的打开了http:www.4399.com/的网页。");
	gs(); 
	int nn=0;
	while(MessageBox(NULL,TEXT("你认为自己是一个很有才能的人吗？"),TEXT("未知错误！"),MB_YESNO)==IDNO)
	  {
	  	cls();
	  cout<<"调皮，别闹！"; 
	  nn++;
	  }
	if (nn>=4)
	  hdcj(4);
	while(MessageBox(NULL,TEXT("如果给你一个机会，你愿意让这一切重新开始吗？"),TEXT("未知错误！"),MB_YESNO)==IDNO)
	  {
	  	nn++;
	  	cls();
	  	cout<<"调皮，别闹！";
	  }
	if (nn>=4)
	  hdcj(54);
	cls();
	Sout("那好，马上就带你回去。。。\n");
	gs();
	Sout("是否跳过开头剧情及引导帮助？Y/N");
	char l=_getch(); 
	if (l!='y'&&l!='Y')
	{
	sudu=10;
	gotoxy(48,0);
	hdcj(1);
	cls();
	gotoxy(0,0); 
	Sout("随着一声啼哭，你不小心降临到这个吵吵嚷嚷的世界上");
	gs();
	Sout("Ftr:嗯。。。给孩子起个什么名字呢？\n");
	Sout("mtr:就叫");
	Sout(name);
	Sout("吧.\n"); 
	gs();
	Sout("Ftr:是个好名字。\n");
	gs();
	Sout("MCYH:在这个竞争激烈的社会上，没有本事的人只能被淘汰掉。\n");
	gs();
	Sout("MCYH:‘朋友’，让我告诉你游戏怎么玩");
	gs();
	Sout("MCYH:你要学会怎么和我们说话，按下任意键就可以了。。。");
	gs();
	Sout("MCYH:嗯。。。学的真快");
	gs();
	Sout("MCYH:那么开始吧");
	gs();
	Sout("MCYH:在游戏中，你有很多属性，例如name,age,xp,level,hp,water,hungry等等");
	gs();
	Sout("MCYH:你可以通过上学增加XP，或者去商店买一些东西增强自己，当XP达到一定之后会升级，当年龄达到一定后会升学\n");
	gs();
	Sout("MCYH:当你大学毕业之后就可以进入社会，寻找工作，生存下去\n");
	gs();
	Sout("MCYH：在这个异世界里，每隔30天就是一年，只要睡上一觉就能到第二天了。\n");
	gs();
	Sout("MCYH：当然，也有很多奇怪的道具可以帮助你跨越时间或者回溯时间，有些是很好用的道具\n");
	gs();
	Sout("MCYH:嗯。。。开始吧。\n");
	shuoming();
	gs();
	Sout("时光飞逝，转眼你已经上了小学。。。\n");
	gs();}
	//初始化 
	printf("Loading init...");
	things[7]=800;
	things[2]=100;
	things[3]=50;
	things[4]=50;
	things[5]=30;
	things[6]=5;
	things[8]=100;
	things[9]=1;
	things[10]=6;
	things[18]=1;
	things[30]=720;
	things[34]=12001;
	for(int i=1;i<30;i++)
	  {
	  	gang[i].pnum=random(2,40);
	  	gang[i].name=randstr(5,21);
	  	for(int j=1;j<=gang[i].pnum;j++)
	  	  {
	  	  	gang[i].peo[j]=born(i);
		  }
		gang[i].leader=random(1,gang[i].pnum);
	  }
	time_t dl;
	time(&dl);
	start=dl; 
	things[0]=1;
	memset(renwu,0,sizeof(renwu));
	Write_File(); 
	mainmenu();
}
int gongji(int attack)//攻击，采用该方法计算造成伤害 
{
	int i=0,j=1;
	gotoxy(10,0);
	cout<<"按空格攻击\n";
	cout<<"Low                         High                         Low\n";
	cout<<"------------------------------------------------------------\n\n";
	cout<<"------------------------------------------------------------";
	float shang[60]=
	{0.1,0.1,0.1,0.2,0.2,0.2,0.2,0.3,0.3,0.3,0.3,0.5,0.5,0.5,0.6,0.6,0.6,0.7,0.7,0.7,0.7,0.7,0.8,0.8,0.9,0.9,1.0,1.1,1.5,1.1,1.0,0.9,0.9,0.8,0.8,
	 0.7,0.7,0.7,0.7,0.6,0.6,0.6,0.5,0.5,0.5,0.4,0.4,0.4,0.3,0.2,0.2,0.2,0.2,0.1,0.1,0.1,0.6,0.4,0.4,0.1};
	while(1)
	  {
	  	gotoxy(13,i-j);
	  	cout<<"     ";
	  	gotoxy(13,i);
	  	cout<<"|#|";
	  	char m;
	  	if (kbhit())
	  	  {
	  	  	m=getch();
	  	  	if (m==' ')
	  	  	  return attack*(shang[i])+attack*0.3;
			}
	  	i+=j;
	  	if (i>=60)
	  	  j=-j;
	  	if (i<=0)
	  	  j=-j;
	  //	Sleep(1);
	  }
}
long long llgongji(long long attack)//攻击，采用该方法计算造成伤害 
{
	int i=0,j=1;
	gotoxy(10,0);
	cout<<"按空格攻击\n";
	cout<<"Low                         High                         Low\n";
	cout<<"------------------------------------------------------------\n\n";
	cout<<"------------------------------------------------------------";
	float shang[60]=
	{0.1,0.1,0.1,0.2,0.2,0.2,0.2,0.3,0.3,0.3,0.3,0.5,0.5,0.5,0.6,0.6,0.6,0.7,0.7,0.7,0.7,0.7,0.8,0.8,0.9,0.9,1.0,1.1,1.5,1.1,1.0,0.9,0.9,0.8,0.8,
	 0.7,0.7,0.7,0.7,0.6,0.6,0.6,0.5,0.5,0.5,0.4,0.4,0.4,0.3,0.2,0.2,0.2,0.2,0.1,0.1,0.1,0.6,0.4,0.4,0.1};
	while(1)
	  {
	  	gotoxy(13,i-j);
	  	cout<<"     ";
	  	gotoxy(13,i);
	  	cout<<"|#|";
	  	char m;
	  	if (kbhit())
	  	  {
	  	  	m=getch();
	  	  	if (m==' ')
	  	  	  return attack*(shang[i])+attack*0.3;
			}
	  	i+=j;
	  	if (i>=60)
	  	  j=-j;
	  	if (i<=0)
	  	  j=-j;
	  //	Sleep(1);
	  }
}
void tepan()//特殊判断，比如减饥饿值、生病什么的 （此函数格式较乱，强迫症者可以免看） 
{
	things[8]-=random(2,4)*(things[21]);
	things[3]-=random(2,5)*(things[21]-1); 
	things[4]-=random(2,5)*(things[21]-1);
	things[1]+=random(1,5)*(5-things[21]); 
	if (rand()%73==6||random(1,350)>things[2]&&rand()%16==2)
	  {
	  	int rdg=random(7,45),rdf=random(230,1598);
	  	Sout("你生病了");
	  	if (rdg>35)
	  	  Sout("，十分严重，挺住!\n");
	  	printf("(hp-%d money-%d)",rdg,rdf);
	  	things[2]-=rdg,things[7]-=rdf;
	  	if (things[2]<0)
	  	  Die();
	  }
	if (rand()%(3000/things[21])==9)
	  {
	  	int deadway=random(1,10);
		switch(deadway)
		  {
		  	case 1:Sout("你出了车祸，你挂了...\n");break;
		  	case 2:Sout("你重重地摔了一跤，脑部严重损伤，你挂了...\n");break;
		  	case 3:Sout("你得了不治之症，你挂了...\n");break;
		  	case 4:Sout("你掉进水里淹死了...\n");break;
		  	case 5:Sout("你开车时连人带车翻进了水里，你挂了...\n");break;
		  	case 6:Sout("你得了抑郁症，你挂了...\n");break;
			case 7:Sout("你被几个帮派的人谋害了，你挂了...\n");break;
			case 8:Sout("你家着火了，你挂了...\n");break;
			case 9:Sout("你死了...\n");break;//敷衍
			case 10:Sout("参观动物园时掉进老虎笼子，你挂了...\n");break; //离谱 
		  }
		  Sleep(1000);
		  Die();
	  }
	if (happened.length()>=20000)
	  hdcj(54); 
	if (double(gotmoney-things[93]-things[7])>=double(500000000000*1))
	  hdcj(57);
	if (gotmoney>=double(500000000000))
	  hdcj(58);
	if (things[16]>=96*30)
	  hdcj(4);
	int i,m=0,j,k;
	if (rand()%50==6&&gang[me.gang].peo[gang[me.gang].leader].name==name)
	  things[200]++;
	while (rand()%250==7&&me.gang!=0)//中途要Break 
	  {
						  do j=random(1,49); while(j!=me.gang);
						Sout(gang[j].name+"向你发起了帮派战役，是否接受(Y/N)\n");
						char l=_getch();
						if (l=='N'||l=='n')
						  {
						  	gangth+=gang[me.gang].name+"拒绝了"+gang[j].name+"发起的战斗，损失惨重/";
						  	Sout("你没有接受，因此损失了");
						  	int lost=random(2335,50000);
						  	printf("%d",lost);
						  	Sout("元钱\n");
						  	things[7]-=lost;
						  	gs();
						  	break;
						  }
						while(1)
						  {
							cls();
							printf("Num\t\tName\t\tatk\t\thp\t\tdfc\n");
							for(i=1;i<=gang[me.gang].pnum;i++)
						  	  printf("%3d\t\t%s\t\t%d\t\t%d\t\t%d\t\t%d\n",i,gang[me.gang].peo[i].name.c_str(), gang[me.gang].peo[i].attack, gang[me.gang].peo[i].hp, gang[me.gang].peo[i].defence);
							printf("Please choose one to fight with your enemy:(enter -1 to quit)");
							int us,enemy;
							cin>>us;
							if (us==-1)
							  break;
							enemy=random(1,gang[j].pnum);
							cls();
							printf("%s VS %s\n",gang[me.gang].peo[us].name.c_str(),gang[j].peo[enemy].name.c_str());
							people a=gang[me.gang].peo[us];
							people b=gang[j].peo[enemy];
							int round=0;
							while(a.hp>0&&b.hp>0)
							  {
							  	Sout("Round ");
							  	printf("%d\n",++round);
							  	int sh;
							  	sh=max(int(a.attack*random(8,12)/10.0-b.defence*random(8,12)/10.0),1);//打出负数就回血了，所以至少造成1点伤害, 
							  	Sout(a.name);													 //攻击和防御随机取0.8~1.2倍好玩一些 
							  	Sout("发起了攻击，对");
							  	Sout(b.name);
							  	Sout("造成了");
							  	cout<<sh;
							  	Sout("点伤害。\n");//以上这些可以合并 
							  	b.hp-=sh;
							  	sh=max(int(b.attack*random(8,12)/10.0-a.defence*random(8,12)/10.0),1);
							  	Sout(b.name);
							  	Sout("发起了攻击，对");
							  	Sout(a.name);
							  	Sout("造成了");
							  	cout<<sh;
							  	Sout("点伤害。\n");
							  	a.hp-=sh;
							  }
							Sout("战斗结束。");
							gang[me.gang].peo[us]=a;
							gang[j].peo[enemy]=b;
							if (a.hp<=0)
							  {
							  	gangth+=gang[me.gang].peo[us].name+"在帮派战役中被"+gang[j].name+"的"+gang[j].peo[enemy].name+"杀死了/";
							  	printf("失败！%s死亡",a.name.c_str());
							  	dead(me.gang,us);//死后需清除其数据 
							  	if (a.name==name)
							  	  Die();
							  	int lost=random(359932,5083921);
							  	printf("损失%d元",lost);
							  	things[7]-=lost;
							  }
							if (b.hp<=0)
							  {
							  	gangth+=gang[me.gang].peo[us].name+"在帮派战役中杀死了"+gang[j].name+"的"+gang[j].peo[enemy].name+"/";
							  	int got=random(187903,3829183);
							  	printf("胜利！获得%d元",got);
							  	things[7]+=got,gotmoney+=got;
								dead(j,enemy);
							  }
							gs();
							if (gang[me.gang].pnum==0)
							  {
							  	gangth+=gang[me.gang].name+"在帮派战役中被"+gang[j].name+"灭了/";
							  	Sout("你的帮派被灭掉了!\n");
							  	Sleep(1000);
								Sout("你损失了所有钱财!");
								things[7]=0; 
								me.gang=0;
							  }
							if (gang[j].pnum==0)
							  {
							  	gangth+=gang[me.gang].name+"在帮派战役中被灭掉了"+gang[j].name+"/";
							  	Sout(gang[j].name);
							  	Sout("从此覆灭...");
							  	Sleep(1000);
							  	Sout("你获得大量金钱!\n");
							  	int got=random(509835,8898372);
							  	things[7]+=got,gotmoney+=got;
							  	break;
							  }
							}
							break;
	  }
	for(i=1;i<=50;i++)//帮派变化
	  if (i!=me.gang||gang[me.gang].peo[gang[me.gang].leader].name!=name)
	    {
	  	  if (!rand()%4)
	  	    {
	  	    	k=1;
	  	    	j=random(1,3);
	  	    	if (!rand()%4)
	  	    	  k=0;
	  	    	int a[3];
	  	    	if (k)
	  	    	  {
	  	    	  	j=min(50-gang[i].pnum,j);
	  	    	  	for(int ij=1;ij<=j;ij++)
	  	    	  	  {
	  	    	  	  	people newjoy=born(i);
	  	    	  	    join(i,gang[i].pnum,newjoy);
	  	    	  	    gangth+=newjoy.name+"加入了"+gang[i].name+"/";
	  	    	  	  }
	  	    	  	break;
				  }
	  	    	for(int ij=0;ij<j;ij++)
	  	    	  do
	  	    	    a[ij]=random(1,gang[i].pnum);
	  	    	  while(a[ij]==gang[i].leader);
	  	    	if (i==me.gang)
	  	    	  for(int ij=0;ij<j;ij++)
	  	    	    if (gang[me.gang].peo[a[ij]].name==name)
	  	    	      {
	  	    	      	Sout("你被帮主驱逐出了帮派...");
	  	    	      	gs();
					  }
	  	    	for(int ij=0;ij<j;ij++)
	  	    	  {
	  	    	  	gangth+=gang[i].name+"的"+gang[i].peo[a[ij]].name+"被驱逐了/";
	  	    	    dead(i,a[ij]);
	  	    	  }
			}
	    } 
	for(i=100;i<129;i++)
	   m+=(fost[i]==1);
	things[189]=m;
	if (things[189]>=27)
	  hdcj(5);
	if (rand()%56==9)
	switch(things[187])
	  {
	  	case 1:Sout("一道闪电从天上劈了下来，");
	  	if (rand()%2)
	  	  {
	  	  Sout("正好劈到你的脑袋上，你不明不白地去世了。");happened+=(name+"被闪电劈死了");hdcj(51);Die();//惨遭五雷轰顶 
	  	 }
	  	else
	  	  Sout("正好劈在你的面前，差点就命中你了。");
		break;
	  	
	  }
	color(things[186]);
	hidden();
	if (things[7]>=100000)
	  hdcj(7);
	if (things[84]>=70)
	  hdcj(49);
	bool wancheng=true;
	if (things[9]<50)
	  wancheng=false;
	if (wancheng)
	  for(int i=1;i<=49;i++)
	  	if (things[i+99]==false)
	  	  wancheng=false;
	if (wancheng)
	  hdcj(50);
	sheng();
	Write_File();
	mwf(); 
	if (things[2]>=1000)
	  hdcj(18);
	if (baohu())
	  {
	  	gs();
	  	Write_File();
	  	me.play+=clock(),exit(0);
	   } 
	cls();
	if (things[8]<5)//强制睡觉 
	    		  {
	    		  	Sout("你没有精力了，按1强制睡觉");
	    		  	char n;
	    		  	do
	    		  	  {
	    		  	  	n=_getch();
						}
					while(n!='1');
					Sout("一个临时的坏觉，你的精力回了一半（水分-10 饱食度-10）");
					things[8]=50;
					things[3]-=10,things[4]-=10;
					things[16]++;
					things[97]=rand()%400+100;
					things[93]+=things[93]*float(things[97]/100000.0);
					gs();
					things[187]=random(1,10);
					switch(things[187])
					  {
						case 1:Sout("天气预报：今日雷暴天气，不宜出行");break;//详见上方被雷劈 
						case 2:Sout("新闻：小森林传来不明怪叫声，专家称可能是一种叫树妖的生物发出的。树妖是一种由枯死的树木变成的怪物，异常凶猛");break;//确有其事 
						case 3:Sout("娱乐新闻：今日有一算命先生称我市市民"+name+"会事事不顺，该算命先生已被逮捕");break;//没准就成真了 
						case 4:Sout("你的眼前好像出现了一个黑影，你正想仔细看，他却不见了，你发现你还是在睡觉的位置");break;//这个... 
						case 5:Sout("特大新闻，特大新闻：我市银行遭犯罪分子抢劫，损失惨重。据银行人员说他们会尽力减少广大市民们的损失");break;//银行的钱会减少 
						default:Sout("天亮了，又是美好的一天");break;//理想状态 
					  }
					Sleep(3000);
					gs();
				  }
				if (things[3]<=0)
				  {
				  	cout<<"你在挨饿!!!";
				  	things[2]-=20;
				  }
				if (things[4]<=0)
				  {
				  	cout<<"你口干舌燥!!!";
				  	things[2]-=20;
				  }
				if (things[2]<=0)
				  Die();
				if (things[16]>=30)
				  Birthday(),things[16]-=30;
}
//const string where[]={"做作业（+XP）","看书（+XP）","睡觉（回满精力）","冥想（+IQ）","吃饭（+饱食度，+水分）","查看状态","查看背包","存档","设置","返回"}; 
//{"学习（+XP）","考试（+XP，考得好+零花钱，考不好-hp）","查看同学资料","玩耍","交朋友","任务","背包","回家","打架（emmmmm...）"};//5
const char tbh[][15]=//图例 
{
  {' ','#','h','s','S','p','c','e','a','k'},
  {' ','#','w','b','s','t','e','l','B','f','E','r'},
  {' ','#','s','t','l','p','f','T','b','r','w'},
  {' ','#','r','p','c','f','b','t','P','h','d','s'},
  {' ','#','e','s','l','t','g','b'},
  {' ','#','b','w','r','b','f','g'},
  {' ','#','g','s','w','t','l','b','f','b','s','S','m'},
  {' ','#','h','d','m','c','f','s','b','p','e','C'},
};
/*if (things[188]==1)
	      l=choose(3)+'0';*///这是代码模板，用于复制粘贴 
const string jieshi[][15]=//图例解释 
{
  {" ","墙","家","学校","超市","公园","游乐场","保存退出","关于游戏","KILL YOURSELF"},
  {" ","墙","做作业","看书","睡觉","冥想","吃饭","查看状态","查看背包","存档","设置","返回"}, 
  {" ","墙","学习","考试","查看同学资料","玩耍","交朋友","任务","背包","回家","打架（这个...）"},
  {" ","墙","跑步","踢足球","登山","钓鱼","返回","公告","活动中心","给游戏评价","兑换码","查看成就"},
  {" ","墙","贪吃蛇","石头剪刀布","扫雷","打字游戏","2048","返回"},
  {" ","墙","搬砖","抄作业","文字录入","离开","找工作","领取挂机收益"},
  {" ","墙","打猎","砍树","工作台","探索","查看合成表","离开","附魔","森林背包","查看当前附魔属性","看看森林中各物品说明","神秘人"},
  {" ","墙","家","赌场","人力市场","游乐场","小森林","超市","背包","公园","存档并退出","市中心"},
};
const int area[][2]=//范围 
{
	{46,110},
	{10,17},
};
 
 
//尽量别看，刺眼 
const int mainmap[][110]=
{
	{1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,1,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,9,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,1,0,0,13,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,2,0,0,0,1,0,6,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,1,0,3,0,0,0,1,0,0,4,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,12,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,13,0,0,0,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,12,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
void PrintfMap(int m)//输出图像式地图 
{
	gotoxy(0,0);
	int i,j;
	for(i=0;i<46;i++)
	  {
	    for(j=0;j<110;j++)
	      printf("%c",tbh[m][mainmap[i][j]]);
	    printf("\n");
	  }
	for(i=25;i<=38;i++)
	  {
	  	gotoxy(i,80);
	    printf("%c - %s\n",tbh[m][i-25],jieshi[m][i-25].c_str());
	  }
	gotoxy(40,80);
	cout<<" Day "<<things[16]+((things[10]-6)*30)<<'\n';
	gotoxy(41,80);
	cout<<"WASD移动,空格确定去此处";
} 
int choose(int m)//图像式专用选择函数 
{
	PrintfMap(m);
	int x,y,i,j,k;
	x=1,y=1;
	char n;
	while(1)
	{
		gotoxy(x,y);
		cout<<"o";
		n=_getch();
		gotoxy(x,y);
		cout<<tbh[m][mainmap[x][y]]; 
		switch(n)
		{
			case 'w':if (x-1>=1&&mainmap[x-1][y]!=1) x--;break;
			case 's':if (x+1<=46&&mainmap[x+1][y]!=1) x++;break;
			case 'a':if (y-1>=1&&mainmap[x][y-1]!=1) y--;break;
			case 'd':if (y+1<=110&&mainmap[x][y+1]!=1) y++;break;
			case ' ':
				if (mainmap[x][y]>=2)
				  return mainmap[x][y]-2;
		 } 
	}
}
void sheng()//升级 
{
	use(8);
	while(things[1]>=sj[things[9]])
	  {
	  	if (things[9]==200)
	  	  {
	  	  	Sout("在不断地悟道后，你明白了自己的本源道，知道了你是谁，从哪里来，到哪里去。（P H D）\n");
		  }
	  	hdcj(36);
	  	things[9]++;
	  	if (things[9]<things[36])
	  	  continue;
	  	things[36]=things[9];
	  	if (things[0]>=7)
		  {
		  	if (rand()%8==3)
		  	  {
		  	  	cout<<"你升级了！ 由于修道走火入魔，元神大损\n";
		  	  	things[2]-=800000*things[9];
		  	  	things[1]-=150000000*things[9];
			  }
		  	cout<<"你升级了！攻击+ 防御+ hp+\n";
	  		things[5]+=50000*things[9];
	  		things[6]+=random(20000,30000)*things[9];
	  		things[2]+=400000*things[9];
		  }
	  	cout<<"你升级了！攻击+5，防御+2，生命恢复40点\n";
	  	things[5]+=5;
	  	things[6]+=random(2,3);
	  	things[2]+=40;
	  	happened+=name+"升级了/";
	  }
}
void game()//第一章主页面，函数名从1.04开始一直没改 
{
	if (things[22]==150)
	  {
	  	Sout("嘿，‘伙计’，你的存档被删除了~");
	  	me.play+=clock(),exit(0);
	  }
	things[18]++;
	const string where[]={"家（存档的地方）","学校（学习的地方）","小超市（购物的地方）","公园（运动）","游乐场（玩耍，赚点零花钱）","保存并退出","关于游戏","自杀"};
	int i,j,k,n,m,l;
	while(1)
	  {
	  	cls();
	  	if (things[0]>=2)
	  	  return;
	  	if(things[10]>=12){
		   things[0]++; 
		   return;}
		char s;
		if (things[188]==1)
		  s=choose(0)+'0';
		else
		  {
		  	for(i=0;i<8;i++)
		  	  printf("%d.%s\n",i,where[i].c_str());
		  	s=_getch();
		  }
	    switch(s)
	      {
	      	case '0':home();break;
	      	case '1':school();break;
	      	case '2':shop();break;
	      	case '3':park();break;
	      	case '4':carnie();break;
	      	case '5':Write_File();me.play+=clock(),exit(0);
	      	case '6':about();break;
	      	case '7':Sout("Ftr:？？？？");Die();break;
	      	case 'h':
	      		{
	      			cls();
	      			cout<<"家：住所，可以存档，睡觉，学习，吃饭，设置以及查看状态\n";
	      			cout<<"学校：学习、交友、玩耍、考试的地方，是你知识的源泉\n";
	      			cout<<"小超市：购买在游戏中生存的必需品（比如食物什么的）\n";
	      			cout<<"公园：运动放松、钓鱼休闲的地方，当然还有一些隐藏功能\n";
	      			cout<<"游乐场：玩一些好玩的游戏，轻松地赚一点小钱\n";
	      			cout<<"存档并退出：这个好像没什么解释的\n";
	      			cout<<"关于游戏：点开看看就知道了\n";
	      			cout<<"？？？？？？\n";
	      			gs();
				}
		  }
	  }
}
void home()//家 
{
	const string where[]={"做作业（+XP）","看书（+XP）","睡觉（回满精力）","冥想（+IQ）","吃饭（+饱食度，+水分）","查看状态","查看背包","存档","设置","返回"}; 
	int i,j,k,n,m;
	things[25]++;
	while(1)
	{
	  if (things[7]>=1000000)
	    hdcj(17);
	  system("cls");
	  char l;
	  if (things[188]==1)//图像式选择 
	    l=choose(1)+'0';
	else
	  {
	  cout<<"这里是你的家，充满着温馨和你珍贵的回忆\n";
	  cout<<"按下序号，实现功能\n";
	  for(i=0;i<10;i++)
	    printf("%d.%s\n",i,where[i].c_str());
	  l=_getch();
	  }
	  cls();
	  switch(l)
	    {
	    	case '0':
	    		cls();
	    		use(9);
	    		tepan();
	    		things[8]-=5;
	    		system("cls");
	    		Sout("1+1==2");
	    		jdt(7);
	    		gs();
	    		Sout("你的XP增加了！");
	    		things[1]+=5;
	    		sheng();break;
	    	case '1':cls();
	    		use(10);
	    		tepan();
	    		things[8]-=5;
	    		system("cls");
	    		Sout("苟利国家生死以，岂因祸福避趋之~");
	    		jdt(6);
	    		gs();
	    		Sout("你的XP增加了！");
	    		things[1]+=10;
	    		if (things[1]>=sj[things[9]])
	    		  things[9]++,cout<<"你升级了！";break;
	    	case '2':cls();
	    		hdcj(38);
	    		use(11);
	    		Sout("多么一个舒适的好觉啊！你的精力已经回满！（水分-10 饱食-10）");
	    		things[16]++;
	    		things[97]=rand()%400+100;
					things[93]+=things[93]*float(things[97]/100000.0);
	    		things[3]-=10,things[4]-=10,things[8]=100;
	    		gs();
					things[187]=random(1,10);
					switch(things[187])
					  {//虽然很离谱但是很准 
						case 1:Sout("天气预报：今日雷暴天气，不宜出行");break;
						case 2:Sout("新闻：小森林传来不明怪叫声，专家称可能是一种叫树妖的生物发出的。树妖是一种由枯死的树木变成的怪物，异常凶猛");break;
						case 3:Sout("娱乐新闻：今日有一算命先生称我市市民"+name+"会事事不顺，该算命先生已被逮捕");break;
						case 4:Sout("你的眼前好像出现了一个黑影，你正想仔细看，他却不见了，你发现你还是在睡觉的位置");break;
						case 5:Sout("特大新闻，特大新闻：我市银行遭犯罪分子抢劫，损失惨重。据银行人员说他们会尽力减少广大市民们的损失");things[93]*=(random(72,100)/100.0);break;
						default:Sout("天亮了，又是美好的一天");break;
					  }
					Sleep(3000);
					gs();
				break;
	    	case '3':cls();
	    		use(12);
	    		tepan();
	    		things[8]-=5;
	    		things[1]+=10;
	    		jdt(6);
	    		sheng();break;
	    	case '4':
			{cls();
	    		use(13);
	    		tepan();
	    		things[8]-=5;
	    		string vname[10]=
	    		{
	    			"可乐+汉堡+炸鸡", 
	    			"薯条",
	    			"鸭血粉丝汤", 
	    			"稀饭", 
	    			"米饭+青菜", 
	    			"白开水",
	    			"番茄炒鸡蛋",
	    			"土豆炖排骨",
	    			"压缩饼干",
	    			"神药",//作弊级神器了 
				};
	    		int AdD[10][3]=
	    		{
	    			46,40,15,
	    			15,20,-5,
	    			40,30,30,
	    			10,-5,20,
	    			20,30,10,
	    			5,1,40,
	    			20,20,20,
	    			48,50,10,
	    			30,50,10,
	    			2000000,2000000,2000000,
				};
				for(i=0;i<10;i++)
				  printf("%d.%s  价钱：%d 饱食度：%d 水分：%d\n",i,vname[i].c_str(),AdD[i][0],AdD[i][1],AdD[i][2]);
				j=_getch()-'0';
				if (things[7]<AdD[j][0])
				  {
				  	cout<<"钱不够！";
				  	gs();
				  	break;
				  }
				things[7]-=AdD[j][0];
				things[3]+=AdD[j][1];
				things[4]+=AdD[j][2];
				if (things[3]>=50000)
				  hdcj(59);
	    		Sout(name+"：嗯。。。真香！");
	    		jdt(6);
	    		Sout("饱食度，水分已恢复！");
	    		break;}
	    	case '5':
	    		{
				cls();
	    		use(14);
	    		const string w[]=
	    		{"关卡进度：",
	    		"经验值：",
	    		"健康值：",
	    		"水分：",
	    		"饱食度：",
	    		"攻击力：",
	    		"防御力：",
	    		"零花钱：",
	    		"精力：",
	    		"等级：",
	    		"年龄：",
				};
				string nan[5]={"","简单模式","中等模式","困难模式","炼狱模式"};
				string xs[2]={"文字","图像"};
				printf("姓名：%s\n",name.c_str()); 
	    		for(i=0;i<=10;i++)
	    		if (i==1)
	    		  printf("%s%lld/%lld\n",w[i].c_str(),things[i],sj[things[9]+1]);
	    		else
	    		  printf("%s%lld\n",w[i].c_str(),things[i]);
	    		printf("挂机上限：%d小时\n",things[30]/60);
				printf("挂机收益：%d元/分钟\n",things[29]); 
				printf("达到过的最高等级：%d\n",things[36]);
				printf("死亡次数：%d\n",things[190]);
				printf("杀怪次数：%d\n",things[83]);
				printf("竞技场连胜次数：%d\n",things[82]);
				printf("银行卡余额：%d\n",things[93]);
				printf("等级：");
				switch(things[304])
				  {
				  	case 0:if (things[0]==7)printf("Opration");else printf("Human");break;
				  	case 1:printf("Demon");break;
				  	case 2:printf("God");break;
				  }
				printf("\n");
				printf("修炼进度：%d/41\n",things[303]);
				printf("总收入：%lld\n",gotmoney);
				printf("总开销/损失：%lld\n",gotmoney-things[93]-things[7]);
				printf("显示形式：%s\n",xs[things[188]].c_str()); 
	    		cout<<"考试最高分："<<things[20]<<'\n';
	    		cout<<"游戏难度："<<nan[things[21]]<<'\n';
	    		cout<<"去神殿次数："<<things[193]<<'\n';
	    		cout<<"在神殿被炸死次数："<<things[196]<<'\n';
	    		cout<<"找到神殿宝藏次数："<<things[194]<<'\n';
	    		cout<<"在神殿逃跑次数："<<things[193]-things[194]-things[196]<<'\n';
	    		cout<<"被你炸死的怪物数量："<<things[197]<<'\n'; 
	    		cout<<"成就完成数量："<<things[195]<<'/'<<cjnum<<'\n';
	    		cout<<"游戏开始时间："<<kaishi<<'\n';
	    		cout<<"今日游戏时间："<<me.play<<'\n';
	    		cout<<"所属帮派："<<gang[me.gang].name<<'\n';
	    		time_t now;
	    		time(&now);
	    		cout<<"现在时间："<<now<<'\n';
	    		cout<<"存档累计时间："<<(now-kaishi)/86400<<"天"<<(now-kaishi)%86400/3600<<"小时"<<(now-kaishi)%3600/60<<"分钟"<<(now-kaishi)%60<<"秒"<<"（"<<now-kaishi<<"）"<<'\n';
	    		cout<<"存档号："<<things[185]<<'\n';
	    		cout<<"存档名："<<filename[things[185]]<<'\n';
				printf("按任意键返回");
	    		gs();
				break;
			}
	    	case '6':{cls();
	    	tepan();
	    		things[8]-=5;
	    	  const string w[]={"棒棒糖","面包","矿泉水","小瓶子","玩具枪"};
	    	  for(i=11;i<16;i++)
	    	    printf("%d.%s*%d\n",i,w[i-11].c_str(),things[i]);
	    	  printf("u.使用\n");
	    	  printf("e.出售\n");
	    	  printf("x.退出\n");
	    	  char m;
	    	  m=_getch();
	    	if (m=='u')
	    	  {
	    	  	printf("用哪个？");
	    	  	cin>>j;
	    	  	printf("用几个？");
	    	  	cin>>k;
	    	  	if (things[j]>=k)
	    	  	  {
	    	  	  	things[j]-=k;
	    	  	  	for(int jj=1;jj<=k;jj++)
	    	  	  	for(int ii=0;ii<10;ii++)
	    	  	  	  things[ii]+=xiaoguo[j][ii];//直接加上 
					}
				break;
			  }
			if (m=='x')
			  break;
			printf("你想卖掉哪个？输入序号和数量");
			int ll,ss;
			cin>>ll>>ss;
			if (things[ll]>=ss)
			  ll-=ss,things[7]+=much[ss],gotmoney+=much[ss];
			else
			  cout<<"不存在的";
			break;}
	    	case '7':Write_File();break;
	    	case '8':
	    		{
	    		use(15);
	    		cout<<"1.改速度：当前文字出现速度："<<sudu<<" \n2.改颜色"<<" \n3.重新读取存档（读取错误时使用）"<<"\n4.查看日记 \n5.隐藏/显示进度条 \n6.改存档名 \n7.显示形式（0.数字形式 1.图像形式）\n8.查看宠物\n9.切换存档";
	    		char l=_getch();
	    		if (l=='1')
	    		{
	    		cout<<"  你想改为多少（>=1）\n";
	    		cin>>sudu;
	    		cout<<"更改成功！";
	    		}
	    		if (l=='2')
	    		{
	    		cout<<"当前颜色："<<things[186];
	    		int typeside,background;
	    		cout<<"输入前景和背景景编号（空格隔开）"; 
				printf("0.黑色 1.蓝色 2.绿色 3.浅绿色 4.红色 5.紫色 6.黄色 7.白色 8.灰色 9.淡蓝色 10.浅绿色 11.淡浅绿色 12.淡红色 13.淡紫色 14.淡黄色 15.亮白色\n");
	    		cin>>typeside>>background;
	    		things[186]=typeside+background*16;
	    		color(things[186]);
	    		}
	    		if (l=='3')
	    		  Read_File();
	    		if (l=='4')
	    		  {
	    		  	cls();
	    		  	int i;
	    		  	for(i=0;i<happened.size();i++)
	    		  	  if (happened[i]=='/')
	    		  	    cout<<"\n";
	    		  	  else
	    		  	    cout<<happened[i];
	    		  	gs();
				  }
				if (l=='5')
				  {
				  	cls();
					if (things[80]!=32768)
					  things[80]=32768;
					else
					  things[80]=0;
				  }
				if (l=='6')
				  {
				  	cls();
				  	int i;
				  	cout<<"存档号："<<things[185]<<endl;
				  	cout<<"存档名："<<filename[things[185]]<<endl;
				  	cout<<"改成什么？";
				  	cin>>filename[things[185]];
				  	mwf();
				  }
				if (l=='7')
				  {
				  	cls();
				  	cout<<"当前形式："<<things[188];
				  	cout<<"\n是否更改？Y/N";
				  	l=_getch();
					if (l=='Y'||l=='y')
					  things[188]=1-things[188];
				  }
				if (l=='8')//宠物（快没用了） 
				  {
				  	cls();
				  	for(i=1;i<=things[191];i++)
				  	  cout<<i<<".\n"<<"名字"<<pet[i].name<<"\n类型："<<pet[i].LX<<"\n血量："<<pet[i].hp<<"\n攻击："<<pet[i].attack<<"\n防御："<<pet[i].run<<"\n--------------------\n";
				  	cout<<"1.治疗 2.放生\n";
				  	cin>>n;
				  	if (n==1)
				  	  {
				  	  	cout<<"输入编号，-1结束";
				  	  	m=100;
				  	  	while(m!=-1)
				  	  	  {
				  	  	  	cin>>m;
				  	  	  	if (things[7]>500)
				  	  	  	  things[7]-=500,pet[m].hp+=150;
				  	  	  	else
				  	  	  	  {
				  	  	  	  	cout<<"钱不够！";
				  	  	  	  	break;
							  }
						  }
					  }
					if (n==2)
					  {
					  	cout<<"输入编号，-1结束";
				  	  	m=100;
				  	  	while(m!=-1)
				  	  	  {
				  	  	  	cin>>m;
				  	  	  	happened+=(name+"放走了"+pet[i].name+"/"); 
				  	  	  	pet[i].name.clear();
				  	  	  	pet[i].hp=0;
				  	  	  	pet[i].attack=0;
				  	  	  	pet[i].run=0;
				  	  	  	pet[i].LX.clear();
						  }
					  }
				  } 
				  if (l=='9')
				    {
				    	printf("确定切换？（功能尚未开发完全，可能会卡退），请输入编号（0放弃）\n");
				    	for(i=1;i<=9;i++)
				    	  printf("%d.%s\n",i,filename[i].c_str());
				    	cin>>things[185];
				    	Read_File();
					}
	    		break;
	    		}
	    	case '9':return;
	    	case 'a'://扫地 
	    		{
	    			use(16);
	    			things[8]-=5;
	    			 tepan();
	    			jdt(5);
	    			srand(time(0));
	    			if (rand()%3)
	    			  {
	    			  	cls();
	    			  	Sout("mtr:真干净！奖励800元钱！\n");
	    			  	gs();
	    			  	things[7]+=800;
					  }
					else
					  {
					  	cls();
					  	Sout("mtr:怎么扫成这个样子？\n");
					  	gs();
					  }
					break;
				}
			case 'h':
				{
					cls();
					cout<<"做作业：+XP\n";
					cout<<"读书：+XP\n";
					cout<<"睡觉：睡个好觉回满精力，明天好好工作学习\n";
					cout<<"冥想：静下心来思考人生，+IQ\n";
					cout<<"吃饭：吃一顿饱饭，再睡个好觉吧\n"; 
					cout<<"查看状态：及时了解一下自己的状态\n";
					cout<<"背包：使用或出售自己身上的东西\n";
					cout<<"存档：记录你当前的状态及游戏进度\n";
					cout<<"设置：根据你自己的喜好调整游戏界面，使整个游戏符合你的使用癖好\n";
					cout<<"返回：回到主界面\n";
					gs(); 
				}
		}
	}
}
string study[27]=//学校的教学内容 
{
 "游戏的作者是创世神MCYH，他是我们班的36号同学，没事不要惹他，不然他会把你的电脑打到关机",
 "遇到困难不要怕，勇敢的面对它","骸骨之地是个危险的地方",
 "郊区的小森林以前是个矿井","做题一定要仔细审题","考不上好大学就没有好工作","魔法吟唱者Ainz的特点是吟唱时间长，但是伤害高",
 "去公园爬山会有惊喜","同学们，请算出(5!)!","民办中学收费很贵哦","游戏的1.21版本正在更新哦（2022/01/20）","这个游戏的最快通关记录是2分29秒",
 "小森林里面有很多不为人知的生物","公元1989年，矿井爆炸了，从此矿井毁掉了，上面变成了一片树林",
 "矿井爆炸的原因是一群Creeper同时爆炸，然后有很多怪物从中涌了出来","小森林的怪物很厉害，同学们不要去那里玩",
 "同学们，2+2=10，你们要记住（你把计算器调成4进制档试试），这个以后考试要考","长大以后一定要去小森林一趟（没有解释）",
 "赌场老板很坑人的，以后不要去那里玩","雷暴天气不要出门，在家睡觉，不然会被雷劈的","遇到MCYH不要害怕，他是个很善良的人（-_-）",
 "饿了一定要吃饭，不然会饿死的。渴了一定要喝水，不然会渴死的。","不要乱买玩具枪，那东西有问题","小森林有很多动(怪)物", 
 "没事不要去废弃矿井玩，那里虽然有宝藏，但是有鬼，36号同学可以随便去",
 "量子之剑需要CPU核心、石头精华（晶体管）、钻石块（高攻击）合成，一刀999",
};
void school()
{
	cls();
	const string where[]=
	{"学习（+XP）","考试（+XP，考得好+零花钱，考不好-hp...）","查看同学资料","玩耍","交朋友","任务","背包","回家","打架（emmmmm...）"};//5
	int i,j,k,n,m;
	while(1)
	  {
	  	cls();
	  	char l;
	  	for(i=0;i<1000;i++)
	  	  if (kbhit())
	  	    l=getch();//垃圾收集器 
	  	if (things[188]==0)
	  	  {
	  	  	for(i=0;i<=8;i++)
	  	  printf("%d.%s\n",i,where[i].c_str());
	  	  l=_getch();
			}
		else
		  l=choose(2)+'0';
	  	cls();
	  	switch(l)
	  	  {
	  	  	case '0':
	  	  		use(17); 
	  	  		tepan();
	  	  		things[8]-=5;
	  	  		m=random(0,26);
	  	  		Sout(study[m]);
	  	  		fost[m+100]=1;
	  	  		jdt(5);
	  	  		things[1]+=5;
	  	  		sheng();
	  	  		gs();
	  	  		break;
	  	  	case '1':{
				use(18);
	  	  		tepan();
	  	  		things[1]+=10;
	  	  		things[8]-=5;
	  	  		float ad=kaoshi();
	  	  		if (ad>things[20])
	  	  		  things[20]=ad;
	  	  		if (ad>=100)
	  	  		  hdcj(9);
	  	  		if (ad<=0)
	  	  		  hdcj(32);
	  	  		if (ad>=80)
	  	  		  {
	  	  		  	Sout("Ftr:嗯。。。考得不错，奖励1500块钱！");
	  	  		  	happened+=(name+"获得了1500元钱/");
	  	  		  	things[7]+=1500;gs();
	  	  		  	gotmoney+=1500;
					break;
					  }
					
				else
				  {
				  	Sout("Ftr:考成这样还敢回家？！");
				  	gs();
				  	Sout("“啪，啪！”hp-30!!!");
				  	happened+=(name+"被父亲打得失去了30滴血量/"); 
				  	things[2]-=30;
				  	gs();
				  	break;
				   }sheng();
			}
				case '2':cls();
					use(19);
					for(i=0;i<40;i++)
					  {
					  	printf("%d号:%s\n",i,student[i].c_str()); 
					  }
					gs();
					break;
				case '3':cls(); 
					use(20);
					tepan();
					things[8]-=5;
					cout<<"你想和谁玩？输入学号，输入-1退出\n";
					for(i=0;i<40;i++)
					  if (friends[i])
					    printf("%d.%s\n",i,student[i].c_str());
					cin>>j;
					if (friends[j])
					  {
					  	cls();
					  	Sout(name);
					  	Sout("：我们一起玩游戏吧，");
					  	Sout(student[j]);
					  	Sout("！\n");
					  	if (rand()%2)
					  	  Sout(student[j]+"：好呀！"),jdt(5),things[1]+=100;
					  	else
					  	  Sout(student[j]+"：不好意思，现在没空~");
					  }
					else
					  Sout(student[j]+"：走开，不要来烦我~");sheng();gs();break;
				case '4':cls();
				tepan();
	    		things[8]-=5;
					use(21);
					for(i=0;i<40;i++)
					  {
					  	printf("%d号:%s\n",i,student[i].c_str()); 
					  }
					Sout("你想和谁做朋友？");
					cin>>n;
					if (friends[n]==true)
					  {
					  	Sout("你们已经是朋友啦！");
					  	gs();
					  	break;
					  }
					if (rand()%2)
					  Sout("交友成功！"),friends[n]=true,things[17]++;
					else
					  Sout("对方不想理你。");
					if (things[17]>=40)
					  hdcj(52);
					break;
				case '5'://以后弄成帮派任务或者修仙任务 
					use(22);
					cls();
					cout<<"你现在的任务：\n";
					cout<<"0.交5个朋友\n";
					cout<<"任务介绍：找啊找啊找朋友，找到一个好朋友~\n";
					cout<<"任务奖励：XP*10000 money*5000\n";
					printf("完成进度：(%d/5)",things[17]);
					if (things[17]>=5&&renwu[0]==false)
					  renwu[0]=true,things[1]+=10000,things[7]+=5000,gotmoney+=5000;
					if (things[17]>=5)
					  cout<<"（已完成）";
					cout<<"\n\n1.某次考试达到一百分\n";
					cout<<"任务介绍：我是班里的学霸~\n";
					cout<<"任务奖励：money*50000\n";
					cout<<"完成进度"<<things[20]<<'/'<<100<<endl;
					if (things[20]>=100&&renwu[1]==false)
					  renwu[1]=true,things[7]+=50000,gotmoney+=5000;
					if (renwu[1])
					  cout<<"（任务已完成）\n";
					cout<<"\n\n2.获得100000元零花钱\n";
					cout<<"任务介绍：我是一个小富翁~\n";
					cout<<"任务奖励：XP*50000 棒棒糖*5\n";
					cout<<"完成进度："<<things[7]<<'/'<<100000<<endl;
					if (things[7]>=100000&&renwu[2]==false)
					  renwu[2]=true,things[1]+=50000,things[11]+=5;
					if (renwu[2])
					  cout<<"（已完成）";
					if (renwu[2])
					  {
					  	hdcj(7);
					  }
					cout<<"\n\n";
					cout<<"3.升至15级\n";
					cout<<"任务介绍：小霸王\n";
					cout<<"任务奖励：面包*5\n";
					cout<<"完成进度："<<things[9]<<'/'<<15<<endl;
					if (things[9]>=15&&renwu[3]==false)
					  renwu[3]=true,things[12]+=5;
					if (renwu[3])
					  cout<<"（已完成）";
					cout<<"\n\n";
					cout<<"4.打开游戏50次\n";
					cout<<"任务介绍：游戏狂热爱好者\n";
					cout<<"任务奖励：XP+200000 money+600000\n";
					cout<<"完成进度："<<things[18]<<'/'<<50<<endl;
					if (things[18]>=50&&renwu[4]==false)
					  renwu[4]=true,things[1]+200000,things[7]+=600000,gotmoney+=600000;
					if (renwu[4])
					  cout<<"（已完成）";
					cout<<"\n\n";
					cout<<"5.打架10次\n";
					cout<<"任务介绍：从小就是个刺儿头(emmmmm)\n";
					cout<<"任务奖励：money*100000\n";
					cout<<"完成进度："<<things[23]<<'/'<<10<<endl;
					if (things[23]>=10&&renwu[5]==false)
					  renwu[5]=true,things[7]+=100000,gotmoney+=100000;
					if (renwu[5])
					  cout<<"（已完成）";
					cout<<"\n\n";
					cout<<"6.回家100次\n";
					cout<<"任务介绍:常回家看看，回家看看~\n";
					cout<<"任务奖励:money*200000\n";
					cout<<"完成进度："<<things[25]<<'/'<<100<<endl;
					if (things[25]>=100&&renwu[5]==false)
					  renwu[6]=true,things[7]+=200000,gotmoney+=200000;
					if (renwu[6])
					  cout<<"（已完成）";
					cout<<"\n\n";
					gs();sheng();
					break;
				case '6':{
					tepan();
	    		things[8]-=5;
					use(23);
					cls();
			const string w[]={"棒棒糖","面包","矿泉水","小瓶子","玩具枪"};
	    	  for(i=11;i<16;i++)
	    	    printf("%d. %s x%d\n",i,w[i-11].c_str(),things[i]);
	    	  printf("u.使用\n");
	    	  printf("e.出售\n");
	    	  printf("x.退出\n");
	    	  char m;
	    	  m=_getch();
	    	if (m=='u')
	    	  {
	    	  	printf("用哪个？");
	    	  	cin>>j;
	    	  	printf("用几个？");
	    	  	cin>>k;
	    	  	if (things[j]>=k)
	    	  	  {
	    	  	  	things[j]-=k;
	    	  	  	for(int jj=1;jj<=k;jj++)
	    	  	  	for(int ii=0;ii<10;ii++)
	    	  	  	  things[ii]+=xiaoguo[j][ii];
					}
					break;
			  }
			if (m=='x')
			  break;
			printf("你想卖掉哪个？输入序号和数量");
			int ll,ss;
			cin>>ll>>ss;
			if (things[ll]>=ss)
			  ll-=ss,things[7]+=much[ss],gotmoney+=much[ss];
			else
			  cout<<"不存在的";}sheng();
			break;
			case '7':return;
			case '8':
				{
				use(24);
				cls();
				cout<<"你要和谁打架？（学号）\n";
				cin>>n;
				int hp,attack,run;
				tepan();
	    		things[8]-=5;
				switch(things[21])
				  {
				  	case 1:hp=random(things[9]*8,things[9]*13),attack=random(things[9]*4,things[9]*5),run=random(things[9]*1,things[9]*2);break;
				  	case 2:hp=random(things[9]*10,things[9]*16),attack=random(things[9]*5,things[9]*6),run=random(things[9]*2,things[9]*3);break;
				  	case 3:hp=random(things[9]*12,things[9]*18),attack=random(things[9]*6,things[9]*7),run=random(things[9]*3,things[9]*4);break;
				  	case 4:hp=random(things[9]*16,things[9]*23),attack=random(things[9]*8,things[9]*9),run=random(things[9]*5,things[9]*6);break;
				  }
				if (n==36){
				  cout<<"竟敢和作者打架，8嘎压路！";
				  things[24]++;
				  Write_File();
				}
				if (things[24]==8)
				  {
				  	sudu=100;
				  	system("color 74");
				  	system("cls");
					Sout("MCYH:又是你？\n");
					gs();
					Sout("MCYH:真有意思\n");
					gs();
					Sout("MCYH:来吧！！\n"); 
					n=36;
				  }
				if (things[24]>=9)
				  {
				  	sudu=30;
				  	system("color 74");
				  	system("cls");
				  	Sout("MCYH:又是你！");
				  	gs();
				  	Sout("MCYH:还没死够？");
				  	gs();
				  	Sout("MCYH:那你关机吧！");
				  	things[22]=150;
				  	Write_File();
				  	system("shutdown -H");
				   } 
				gs();
				hp*=things[0],attack*=things[0],run*=things[0];
				int sm=things[2];
				while(1)
				  {
				  	if(n==36)
				  	  hp=random(things[9]*40,things[9]*66),attack=random(things[9]*21,things[9]*29),run=random(things[9]*8,things[9]*15);
				  	cls();
				  	cout<<"你的hp:"<<things[2]<<endl;
				  	printf("你的攻击：%d\n",things[5]);
				  	printf("你的防御：%d\n",things[6]);
				  	printf("对手：%s\n",student[n].c_str());
				  	if (n==36)
				  	  printf("注：不死之身\n");
				  	printf("对手的hp:%d\n",hp);
				  	printf("对手的attack:%d\n",attack);
				  	printf("对手的防御:%d\n\n",run);
				  	m=gongji(things[5]);
				  	cls();
				  	cout<<"你发动了攻击，对手受到了"<<m-run<<"点伤害\n";
				  	hp-=m-run;
				  	int sh=attack*(float(random(6,9)/10.0))-things[6];
				  	if (sh<=0)
				  	  sh=1;
				  	cout<<"对手发动了攻击，你受到了"<<sh<<"点伤害\n";
				  	things[2]-=sh;
				  	if (things[2]<=0||hp<=0)
				  	  break;
				  	gs();
				  }
				gs();
				if (hp<=0)
				  {
				  	Sout("胜利");
				  	happened+=(name+"将"+studentname[n]+"打得头破血流/");
				  	things[1]+=5000;
				  	things[7]+=5000;
				  	gotmoney+=5000;
				  	if (n==36)
				  	  things[1]+=40000,things[7]+=40000,gotmoney+=40000;
				  	sheng();
				  	gs();
				  }
				else // :) 
				  {
				  	if (things[24]>=8&&n==36)
				  	  {
				  	  	system("cls");
				  	  	Sout("这只是一场噩梦，祝愿你永远不会醒来！"+name+"\n");
				  	  	sudu=1000;
				  	  	Sout("再	见	！\n");
				  	  	if (things[21]==4)
				  	  	  {
				  	  	  	things[22]=150;
				  	  	  	Write_File();
							  }
						system("Shutdown -H");
				  	  	me.play+=clock(),exit(0);
					  }
					if (n==36)
					  Sout("MCYH：。。。\n");
					if (n==36)
					  happened+=(name+"在与MCYH打架时不慎被打死，还被抢走所有钱财/");
					things[7]=0;
					happened+=(name+"被"+studentname[n]+"打得头破血流/");
				  	Sout("你被打死了。。。");
				  	Write_File();
				  	things[1]=0;
				  	Die();
				  	sheng();
				  }
				things[23]++;
				if (things[23]>=50)
				  hdcj(53);
				break;
				}
				case 'h':
				  {
					cls();
					cout<<"学习：好好学习，天天向上。积累经验\n";
					cout<<"考试：看看你的学习成果吧，考得好还有奖金哦\n";
					cout<<"查看同学资料：不光是自己，同学也要了解哦\n";
					cout<<"玩耍：学习之余和朋友玩耍放松一下，可以增长点经验\n";
					cout<<"任务：按时完成任务可以获得丰厚奖励\n";
					cout<<"背包：使用或出售身上的东西\n";
					cout<<"回家：这个好像不用解释\n";
					cout<<"打架：不良行为\n";
					gs();
				  } 
		}
	  }
}
void shop()
{
	tepan();
	things[8]-=5;
	use(25); 
	const string what[]={"棒棒糖","面包","矿泉水","小瓶子","玩具枪","离开"};
	int i,j,k,n,m;
	while(1)
	  {
	  	cls();
	  	cout<<"你有"<<things[7]<<"元钱\n";
	  	for(i=0;i<6;i++)
	  	  printf("%d.%s %d$\n",i,what[i].c_str(),mu[i+11]);
	  	cout<<"32767.虫洞 100000$\n";
		cout<<"1500.血瓶（现买现用）1500$\n"; 
		cout<<"7.兴奋剂（用5点血量的代价换取20点精力，不亏） 8888$\n";
		  if (things[0]>=5)
		    cout<<"19.猎枪 30000$\n";
	  	cout<<"你想买哪个？输入序号\n";
	  	cin>>j;
	  	if (j==19&&things[0]>=5)
	  	  things[27]=1,things[7]-=30000;
	  	if (j==7)
	  	  {
	  	  	cout<<"买几个？";
	  	  	cin>>i;
	  	  	if (i*8888>things[7])
	  	  	  {
	  	  	  	cout<<"钱不够！";
	  	  	  	break;
			  }
	  	  	things[2]-=i*5;
	  	  	things[8]+=i*20;
	  	  	things[7]-=i*8888;
	  	  	if (things[2]<=0)
	  	  	  Die();
	  	  	break;
		  }
	  	if (j==5)
	  	  return;
	  	if (j==32767)
	  	  {
	  	  	if (things[7]>=100000)
	  	  	  {
	  	  	  	things[7]-=100000,things[10]++;break;
				  }
			}
		if (j==1500)
		  {
		  	cout<<"买几个？";
		  	cin>>k;
		  	k*=1500;
		  	if (things[7]>=k)
		  	  things[7]-=k,things[2]+=20*k/1500;
			break; 
		  }
	  	cout<<"买几个?\n";
	  	cin>>k;
	  	j+=11;
	  	n=mu[j]*k;
	  	if (things[7]>=n)
	  	  {
	  	  	printf("购买成功！\n");
	  	  	things[7]-=n;
	  	  	things[j]+=k;
			}
		else
		  printf("你的钱不够！\n");
	  }
}
void park()
{
	srand(time(0));
	const string where[]=
	{"跑步（+hp，有一定概率摔倒）","踢足球（+hp，有一定概率被球砸中）","登山（+XP和hp（海量）不过需要15点精力，有10/25/33/50%概率从山上摔下来掉hp）","钓鱼（+money）","返回","公告","活动中心","给游戏评价","兑换码","查看成就"};
	int n,m,i,j,k;
	bool hurt=false;
	while(1)
	  {
	  	char l;
	  	for(i=0;i<1000;i++)
	  	  if (kbhit())
	  	    l=getch();//垃圾收集器 
	  	cls();
	  	for(i=0;i<10;i++)
	  	  printf("%d.%s\n",i,where[i].c_str());
	  	if (things[188]==1)
	      l=choose(3)+'0';
	    else 
	  	  l=_getch();
	  	switch(l)
	  	  {
	  	  	case '0':
	  	  		use(26);
	  	  		cls();
	  	  		things[1]+=10;
	  	  		tepan();
	  	  		things[8]-=5;
	  	  		Sout("一，一，一二一！");
	  	  		jdt(5);
	  	  		if (things[21]==1&&rand()%33==9)
	  	  		  hurt=true;
	  	  		if (things[21]==2&&rand()%20==15)
	  	  		  hurt=true;
	  	  		if (things[21]==3&&rand()%12==7)
	  	  		  hurt=true;
	  	  		if (things[21]==4&&rand()%10==5)
	  	  		  hurt=true;
	  	  		if (hurt)
	  	  		  {
	  	  		  	Sout("你不小心摔倒了！hp-15~");
	  	  		  	happened+=(name+"在爬山时摔倒了/");
	  	  		  	things[2]-=5;
				  }
				else
				  {
				  	Sout("通过运动，你的hp增加了！");
				  	happened+=(name+"通过运动，增加了5点血量/");
				  	things[2]+=5;
				  }
				break;
			case '1':
				use(27);
				cls();
				things[1]+=10;
				tepan();
				things[8]-=5;
				Sout("射门，射门！球进了~");
				jdt(5);
				if (things[21]==1&&rand()%33==9)
	  	  		  hurt=true;
	  	  		if (things[21]==2&&rand()%20==15)
	  	  		  hurt=true;
	  	  		if (things[21]==3&&rand()%12==7)
	  	  		  hurt=true;
	  	  		if (things[21]==4&&rand()%10==5)
	  	  		  hurt=true;
	  	  		if (hurt)
	  	  		  {
	  	  		  	Sout("你被球砸中了脑壳！hp-15 IQ-5(不存在的)~");
	  	  		  	happened+=(name+"踢球时脑壳受伤，hp-15，智力严重受损/");
	  	  		  	things[2]-=5;
				  }
				else
				  {
				  	Sout("通过运动，你的hp增加了！");
				  	happened+=(name+"通过运动，恢复了5点血量/");
				  	things[2]+=5;
				  }break;
			case '2':
				use(28);
				cls();
				things[1]+=10;
				tepan();
				things[8]-=15;
				hurt=false;
				Sout("加油，马上就到顶了！~");
				jdt(10);
				if (things[21]==1&&rand()%10==9)
	  	  		  hurt=true;
	  	  		if (things[21]==2&&rand()%4==2)
	  	  		  hurt=true;
	  	  		if (things[21]==3&&rand()%3==2)
	  	  		  hurt=true;
	  	  		if (things[21]==4&&rand()%2)
	  	  		  hurt=true;
	  	  		if (hurt)
	  	  		  {
	  	  		  	Sout("你失足滚了下来！hp-15~");
	  	  		  	happened+=(name+"在爬山途中滚了下来/");
	  	  		  	things[2]-=15;
				  }
				else
				  {
				  	use(29);
				  	Sout("通过运动，你的hp增加了！");
				  	happened+=(name+"爬山增加了15点血量/");
				  	hdcj(10);
				  	if (rand()%5>=3)
				  	  {
				  	  	happened+=(name+"来到了天空之境/");
				  	  	gs();
				  	  	cout<<"运气真好，你来到了天空之境。";
				  	  	hdcj(11);
				  	  	gs();
				  	  	cout<<"\n";
				  	  	cout<<"你想干什么呢？\n";
				  	  	cout<<"1.去天空医院\n";
				  	  	cout<<"2.去天空集市\n";
				  	  	cout<<"3.找耀光之盾\n";
				  	  	cout<<"4.许愿池\n";
				  	  	cout<<"5.交易市场\n";
				  	  	char l=_getch();
				  	  	cls();
				  	  	switch(l)
				  	  	  {
				  	  	  	case '1':
				  	  	  		{
				  	  	  			use(30);
				  	  	  			Sout("神医：哎呦，你这伤不轻啊，要");
				  	  	  			m=rand()%10000+100000;
				  	  	  			cout<<m;
				  	  	  			Sout("元才能治好！");
				  	  	  			cout<<"\n是否接受治疗？Y/N\n";
									char l=_getch();
									if (l=='y'||l=='Y')
									  if (things[7]>=m)
									    {
									    	things[7]-=m;
									    	n=rand()%300+200;
									    	cout<<"真不愧是神医，你回复了"<<n<<"点血量！";
									    	things[2]+=n;
									    	hdcj(41);
									    	happened+=("神医治好了"+name+"的重伤/");
										 } 
									  else
									    cout<<"你的钱不够！";
									else
									  Sout("神医：哼。");
									 break;
								}
							case '2':
								{
									use(31);
									cout<<"你想购买什么？\n";
									cout<<"1.黄昏流星锤（攻击+30）200000$\n";
									cout<<"2.传送神符 300000$\n";
									cout<<"3.圣光盾牌（防御+25）300000$\n";
									cout<<"4.治疗药水（hp+200）15000$\n";
									cout<<"5.恶魔沙漏 （在你死亡时将你救回，但是灵魂会遭到恶魔反噬...） 666666$\n";
									cout<<"6.附魔之瓶 （XP+3000）500$\n";
									cout<<"7.附魔台（可用于附魔装备）100000$\n";
									cout<<"8.附魔石（附魔的必备物品）30000$\n";
									cout<<"9.改名神符（改名） 500000$\n";
									cout<<"0.Secret Case 15000000$\n";
									int how[10]={15000000,200000,30000,300000,15000,666666,500,100000,30000,500000};
									char l=_getch();
									n=l-'0';
									k=n;
									cout<<"买几个呀？\n";
									cin>>m;
									n=how[n]*m;
									if (things[7]>=n)
									  things[7]-=n;
									else
									  {
									  	cout<<"你的钱不够！\n";
									  	Sout("店主：穷B！没钱就出去！！！");
									  	happened+=(name+"来天空集市抢东西被老板赶出店门/");
									  	gs();
									  	break;
									  }
									switch(k)
									  {
									  	case 0:things[201]=1;break;
									  	case 1:things[5]+=m*30;break;
									  	case 2:things[99]+=m;break;
									  	case 3:things[6]+=m*25;break;
									  	case 4:things[2]+=m*200;break;
									  	case 5:things[31]+=m;break;
									  	case 6:things[1]+=m*3000;break;
									  	case 7:things[32]+=m;hdcj(26);break;
									  	case 8:things[33]+=m;break;
									  	case 9:
									  		{
									  			cls();
									  			cout<<"你想把名字改成什么：";
									  			cin>>name;
									  			break;
											}
									  	default:cout<<"没有这个商品！";break;
									  }
									break;
								}
							case '3':
								{
									use(32);
									Sout("耀光之盾：来找我？想变得更强吗？\n");
									cout<<"Y/N";
									char l=_getch();
									if (l=='Y'||l=='y')
									  {
									  	Sout("耀光之盾：那好，成全你！\n");
									  	gs();
									  	Sout("耀光之盾发动了技能【圣光庇护】，为你增加了一个500点血量的护盾，但是降低了20点攻击");
									  	things[2]+=500,things[5]-=20;
									  	break;
									  }
									else
									  Sout("耀光之盾：你耍老子呢！...");
									break;
								}
							case '4':
								{
									use(33);
									const string sh[]={"","钻石*3","春节礼炮*1","钱*300000","XP*500000","挂机上限+1小时","挂机收益+10元/分钟","钱*150000","钻石剑*1","钱*2000"};
									cls();
									cout<<"抽奖\n";
									cout<<"1.钻石*3（4%）\n";
									cout<<"2.春节礼炮*1（1%）\n";
									cout<<"3.钱*300000（6%）\n";
									cout<<"4.XP*500000（10%）\n";
									cout<<"5.挂机上限+1小时（5%）\n";
									cout<<"6.挂机收益+10元/分钟（10%）\n";
									cout<<"7.钱*150000（20%）\n";
									cout<<"8.钻石剑*1（14%）\n";
									cout<<"9.钱*2000（30%）\n";
									int kl[10][2]=
									{
										0,0,
										1,4,
										5,5,
										6,11,
										12,21,
										22,27,
										28,37,
										37,56,
										57,70,
										71,100
									};
									n=rand()%100+1;
									for(i=1;i<=9;i++)
									  if (n>=kl[i][0]&&n<=kl[i][1])
									    break;
									m=i;
									k=rand()%4+5;
									j=9*k+m;
									k=1;
									for(i=1;i<=j;i++)
									  {
									  	gotoxy(k,30);
									  	cout<<"<---";
									  	Sleep(100);
									  	gotoxy(k,30);
									  	cout<<"     ";
									  	k++;
									  	if (k>=10)
									  	  k=1;
									  }
									cout<<"获得"<<sh[m];
									gs();
									if (m==1)
									  hdcj(12);
									switch(m)
									  {
									  	case 1:fost[6]+=3;break;
									  	case 2:fost[22]++;break;
									  	case 3:things[7]+=300000;gotmoney+=300000;break;
									  	case 4:things[1]+=500000;break;
									  	case 5:things[30]+=60;break;
									  	case 6:things[29]+=15;break;
									  	case 7:things[7]+=1500;gotmoney+=1500;break;
									  	case 8:fost[15]++;break;
									  	case 9:things[7]+=2000;gotmoney+=2000;break;
									  }
									happened+=(name+"在许愿树大显身手，抽中了"+sh[m]+"/");
									break;
								}
							case '5':
								{
									cls();
									cout<<"你想卖掉什么，这里收购以下物品\n";
									cout<<"1.火药       1000$  *1\n";
									cout<<"2.金锭       5000$  *1\n";
									cout<<"3.石头精华  20000$  *1\n";
									cout<<"4.木板         50$  *1\n";
									cout<<"5.工业钻石 300000$  *1\n";
									cout<<"6.铁头盔    10000$  *1\n";
									cout<<"7.铁胸甲    16000$  *1\n";
									cout<<"8.铁护腿    14000$  *1\n";
									cout<<"9.铁靴子     8000$  *1\b";
									char l=_getch();
									int _xb[10]={0,23,5,54,1,56,27,28,29,30};
									int money[10]={0,1000,5000,20000,50,300000,10000,16000,14000,8000};
									int i,j;
									j=l-'0';
									int before=things[7];
									printf("你拥有%d个，卖掉多少个？\n",fost[_xb[j]]); 
									cin>>i;
									if (i<=fost[_xb[j]])
									  {
									    fost[_xb[j]]-=i;
									  	i=money[j]*i;
									  	things[7]+=i;
									  	printf("获得%d元!",i);
									  }
									else
									  Sout("店主：穷B，没钱就出去！");
									gotmoney+=things[7]-before;
									gs();
									break;
								}
							case 'h':
								{
									cls();
									cout<<"天空医院：让神医为你治疗，恢复些许血量，当然收费也不低\n";
									cout<<"天空集市：购买一些平时买不到的东西，很稀有哦\n";
									cout<<"耀光之盾：给你套个盾，回点血，但是有副作用\n";
									cout<<"许愿池：快来试试你的手气如何吧\n";
								}
						  }
						}
				  	things[2]+=15;
				  }break;
			case '3':{
				use(34);
				cls();
				const string fish[]=
				{"罗非鱼","草鱼","鲤鱼","太阳鱼","石斑鱼","鲫鱼","鲨鱼（emmmmm...）"};
				const int fm[]=
				{15,100,300,800,2500,7500,100000};
				bool fishing[7]=
				{0,0,0,0,0,0,0};
				tepan();
				things[8]-=5;
				jdt(10);
				if (rand()%2==1)
				  fishing[0]=1;
				if (rand()%5==3)
				  fishing[1]=1;
				if (rand()%8==5)
				  fishing[2]=1;
				if (rand()%15==3)
				  fishing[3]=1;
				if (rand()%20==4)
				  fishing[4]=1;
				if (rand()%25==9)
				  fishing[5]=1;
				if (rand()%50==6)
				  fishing[6]=1;
				bool diao=false;
				string shouhuo="";
				int getn=0;
				for(i=0;i<7;i++)
				  if (fishing[i])
				    shouhuo+=fish[i]+',',things[7]+=fm[i],gotmoney+=fm[i],getn+=fm[i],diao=true;
				if (diao)
				  cout<<"你钓到了"<<shouhuo<<"\b。卖了"<<getn<<"元钱\n";
				else
				  cout<<"毛都没钓到！";
				gs(); 
				happened+=(name+"钓鱼，钓的可开心了/");
				break;}
			case '4':return;
			case '5':
				{
					use(35);
					cls();
					cout<<"				人生之路公告\n";
					cout<<"	版本：v1.20.01.334778\n";
					cout<<"更新内容：新增活动“修仙之路”\n";
					cout<<"修复已知BUG，增强了游戏的稳定性\n";
					cout<<"开学了，更新的速度可能会慢些，请谅解（放心，不会影响学习）\n"; 
					cout<<"祝各位同学在新学期学业进！!";
					cout<<"										沉迷学习的MCYH\n";
					cout<<"											2022/1/8 23:25\n"; 
					gs();
					break;
				}
			case '6':
				{
					use(36);
					cls();
					cout<<"修仙之路\n";
					cout<<"2月1日14:00~2月27日14:00\n";
					cout<<"活动简介：\n";
					cout<<"随着human的science技术不断提高，他们在sky无意中发现了opration的踪迹\n";
					cout<<"某日，一个名叫Copra的sicentist利用cueip技术追随一只opration来到了oprat\n";
					cout<<"这时，human才意识到sky中早已存在了oprat\n";
					cout<<"只有拥有强大soul的human才可能进入oprat，并成为一个opration。\n";
					cout<<"Copra发现oprat世界与forest中的secret man有着联系，并在oprat中发现了secret man的足迹\n";
					cout<<"oprat世界欢迎你...\n";
					cout<<"在2.1~2.27这段时间，oprat世界将举行活动。参与活动的神免费赠送价值200神币的紫金丹一盒\n";
					cout<<"最后送大家一句话（法语）：Stupide, je savais que tu avais besoin d'un traducteur.\n";
					time_t BD;
					cout<<"本活动还有";
					time(&BD);
					cout<<(1642396366+14*86400-BD)/86400<<"天结束\n";
					gs();
					break; 
				}
			case '.':
				{
					cls();
					cout<<"密码:";
					string s;
					cin>>s;
					if (s=="ZoNgJiAlE")
					  {
					  	if (things[35])
					  	  {
					  	    cout<<"是否退出管理员模式？1/0";
					  	    cin>>n;
					  	    if (n==1)
					  	      things[35]=0;
					  	    happened+=(name+"退出了管理员模式/");
					  	  }
					  	if (things[35]==0)
					  	  {
					  	  	cout<<"是否进入管理员模式？1/0";
					  	  	cin>>n;
					  	  	if (n==1)
					  	  	  things[35]=1;
					  	  	happened+=(name+"进入了管理员模式/");
							}
					  }
				}
			  case '7':
			  	{
			  		cls();
			  		int star=pingjia();
			  		if (star==5)
			  		  cout<<"惊喜！：兑换码:minecraft91#c93_49dj9lxp9q32n";
			  		gs();
			  		break;
				}
				/*
0章节 1XP 2HP 3hungry 4water 5attack 6run 7money 8level 9等级 10age 
11棒棒糖 12面包 13矿泉水 14小瓶子 15玩具枪 16天数 17朋友数量 18次数 
19学号 20最高成绩 21难度 22存档是否存在 23打架次数 24和作者打架 
25回家次数 26剧情 27打猎资格 28大学 29挂机收益 30挂机上限 31沙漏
32附魔台 33附魔石 34更新 35管理员模式 36最高等级 37~57兑换码 
58~68活动参加过没有  100~199成就 
*/ 
/*string fsn[200]=
	0       1       2      3        4      5        6
{"原木 ","木板 ","木棍 ","石头 ","铁锭 ","金锭 ","钻石 ",
   7       8       9           10   11
 "木镐 ","石镐 ","铁镐 ","金镐 ","钻石镐 ",
    12     13		14		15		16
 "木剑 ","石剑 ","铁剑 ","金剑 ","钻石剑 ",
	17		18		19		20		21
 "木斧 ","石斧 ","铁斧 ","金斧 ","钻石斧 ",
 	22		  23	 24		25		26
 "春节礼炮","火药","铁块","金块","钻石块",
 		27		28		29			30
 /*27"铁头盔","铁胸甲","铁护腿","铁靴子",
 	31		32			33		34
 "金头盔","金胸甲","金护腿","金靴子",
 	35			36			37		38
 "钻石头盔","钻石胸甲","钻石护腿","钻石靴子",
 		39			40			41			42		43		44		45
 /*39"英雄头盔","英雄战甲","英雄护腿","英雄战靴","英雄剑","英雄镐","英雄战斧",
 		46			47			48			49		50		51		52
 /*46"虚空头盔","虚空战甲","虚空护腿","虚空战靴","虚空剑","虚空镐","虚空斧",
 		53			54		55		56
 /*53"量子剑", "石头精华", "CPU","工业钻石" 
};*/
			  case '8'://37~57
			  	{
			  		use(37);
			  		cls();
			  		cout<<"输入兑换码：";
			  		string ma;
			  		cin>>ma;
			  		if (ma=="minecraft91#c93_49dj9lxp9q32n"&&things[37]==0)
			  		  {
			  		  	cout<<"获得：钱*50000 钻石*15";
			  		  	gs();
			  		  	things[7]+=50000,fost[6]+=15,things[37]=1;
			  		  	gotmoney+=50000;
					  }
					else if (ma=="MCYH_IS_VERY_HANDSOME"&&things[38]==0)
					  {
					  	cout<<"获得：附魔台*1 附魔石*100";
					  	things[32]++,things[33]+=100;things[38]=1;
					  	hdcj(26);
					  	gs();
					  }
					else if (ma=="RSZL666"&&things[39]==0)
					  {
					  	cout<<"获得：铁块*8 CPU*1";
					  	fost[24]+=8,fost[55]++;
					  	things[39]=1;
					  	gs();
					  }
					else if (ma=="WAH&MCYH&WYQ"&&things[40]==0)
					  {
					  	cout<<"获得：金块*10 虚空剑*1 经验*200000";
					  	things[1]+=200000;
					  	fost[25]+=10,fost[50]++;
					  	things[40]=1;
					  	gs();
					  }
					break;
				}
			  case '9':
			  	{
			  		chengjiu();
			  		break;
				}
			  case 'h':
			  	{
			  		//{"跑步（+hp，有一定概率摔倒）","踢足球（+hp，有一定概率被球砸中）","登山（+XP和hp（海量）不过需要15点精力，有10/25/33/50%概率从山上摔下来掉hp）","钓鱼（+money）","返回","公告","活动中心","给游戏评价","兑换码","查看成就"};
 
			  		cls();
			  		printf("跑步：做运动，提高体力和免疫力\n");
			  		printf("踢足球：做运动，提高体力和免疫力\n");
			  		printf("登山：做运动，提高体力和免疫力（有彩蛋）\n");
			  		
				  }
			gs();
		}
	  }
}
int quest()
{
	use(38); 
	system("cls");
	string question[100],ans[100];
	int count=1,wincount=0;
	cout<<"输入字母全大写(输入只有字母或数字，汉字一律输入大写首字母)"<<endl; 
	question[1]="这个程序的作者叫什么名字？"; 
	ans[1]="MCYH";
	question[2]="Birds的原唱是Imagine Dragons和谁？";
	ans[2]="Eisa";
	question[3]="MC旧版本中，一个附魔金苹果需要8个金块和一个苹果合成。一个附魔金苹果重约20t，苹果的重量忽略不计，如此计算，一个金粒重多少kg（保留整数）？"; 
	ans[3]="31";
	question[4]="利用向后推1位的凯撒加密术，密码bzs解密后的中文意思是什么（汉字回答）";
	ans[4]="猫";
	question[5]="9月3日网易云音乐Taylor Swift的歌单中第2首是什么";
	ans[5]="Lover";
	question[6]="OneRepublic乐队的中文意思？";
	ans[6]="GHSD";
	question[7]="Beep函数的第二个参数的单位？";
	ans[7]="ms";
	question[8]="Beep函数的第一个参数的单位？";
	ans[8]="db";
	question[9]="123456789个汉字占多少MB空间？（保留一位小数）";
	ans[9]="235.5";
	question[10]="本游戏是作者在7月几号发在C站的？";
	ans[10]="3";
	question[11]="一个月多少天？";
	ans[11]="2.5";
	question[12]="地狱是不是有个地方叫做神店？（YES/NO（大写））";
	ans[12]="NO";
	question[13]="史塔克是哪部动漫里的人物？";
	ans[13]="SS";
	question[14]="如果1+1=3，那么3+3=几？"; 
	ans[14]="4";
	question[15]="求BVN3.5鼬的连招adj+jjj+wj+j+wu+i的最高伤害是多少（没有任何buff加身时）";
	ans[15]="780";
	question[16]="这题的编号是16，请问上一题的编号是多少？";
	ans[16]="15";
	question[17]="((1+5==6||3+3==7)&&!((5+3!=7&&(!(100*3==300&&200*4==700)))*0)||(1*5==3))&&(5+5==10))的值是true还是false？";
	ans[17]="false";
	question[18]="ABCDEFG___";
	ans[18]="HIJ";
	question[19]="2^(2^(2^(2^(2^0))))=";
	ans[19]="65536";
	question[20]="作者的QQ号是多少？";
	ans[20]="3491576605"; 
	question[21]="耀光之盾(光盾)是谁的称号？";
	ans[21]="LXS";
	question[22]="____的终极技能可以将时间回溯？";
	ans[22]="ZLS";
	question[23]="电脑可以使用红黄蓝作为三原色组合出多少种不同的颜色？";
	ans[23]="16777216";
	question[24]="82,50,26,下一个数?";
	ans[24]="10";
	question[25]="MC中的混凝土粉末是由染料，沙子和____合成的";
	ans[25]="SL";
	question[26]="末地城的英文是什么？";
	ans[26]="ENDCITY";
	question[27]="假设MC中一格水可以灌溉其周围半径6格正方形的农田（假设，不是真的），那么一格水最多可以灌溉几格农田?我们假设不考虑高度，只有水源才能灌溉";
	ans[27]="168"; 
	question[28]="Ignite的作者是Alan Walker和谁？";
	ans[28]="K-391";
	question[29]="假设游戏中一把斧头的暴击率为30%，暴击时造成3倍伤害，基础攻击为9点，能攻击1500次，求至少可以打出多少伤害?";
	ans[29]="13500";
	question[30]="戴蒙2技能叫什么？";
	ans[30]="LHJQ";
	question[31]="这是人生之路哪个版本？(前三个即可，格式为X.XX.XX)";
	ans[31]="1.19.01";
	question[32]="MCYH的生日是哪天（格式：例如5月7号为0507）";
	ans[32]="0206";
	question[33]="前序遍历的顺序？（注：父节点为F，左节点为L，右节点为R）";
	ans[33]="FLR"; 
	question[34]="假设甘瑟尔扔出了直线飞行的手里剑，每2ms造成65点真实伤害，飞行距离为50m，速度为10m/s，经过每名敌人时不减速，敌人分别站在离初始甘瑟尔7m,17m,35m的位置，设敌人有10cm宽度。求甘瑟尔造成了多少伤害?";
	ans[34]="975";
	question[35]="甘瑟尔的必杀技叫什么";
	ans[35]="YRZW";
	question[36]="火线精英中AK47-逆鳞在黑市被抽到的概率是百分之几？";
	ans[36]="3";
	question[37]="火线精英中变羊枪的原名？";
	ans[37]="KNMDY";
	question[38]="哪个变异体大招期间无敌？";
	ans[38]="MFS";
	question[39]="飞鼠在进入游戏后改名为什么";
	ans[39]="AZWEG";
	question[40]="Grammar是什么意思 A.语法 B.表达";
	ans[40]="A";
	question[41]="有一个U盘生产时，标记内存为16GB，求实际内存（单位：GB）？(四舍五入保留两位小数)";
	ans[41]="15.28";
	question[42]="给岁月以文明，给时光以__";
	ans[42]="SM";
	question[43]="FADED的纯音乐版叫什么？";
	ans[43]="FADE";
	question[44]="MC是不是好游戏？（YES/NO）";
	ans[44]="YES";
	question[45]="求35,89,75,132,65,69,38,69,50,15,7,20,5,13,11,3,150,80的最长不上升子序列长度";
	ans[45]="8";
	question[46]="《十亿年后的来客》中的病毒是几进制基因";
	ans[46]="8";
	question[47]="BVN3.5带土二段的WU后是否可接WI?（YES/NO）";
	ans[47]="YES";
	question[48]="迷你世界好玩吗？（YES/NO）";
	ans[48]="NO";
	question[49]="儿童节是哪天";
	ans[49]="0601"; 
	question[50]="求35,89,75,132,65,69,38,69,50,15,7,20,5,13,11,3,150,80的最长连续不上升子序列长度";
	ans[50]="4";
	int num=50;
	bool quested[100];
	memset(quested,0,sizeof(quested));
	while(count<=num)
	{
		system("cls");
		int number=rand()%num+1;;
		while(quested[number])number=rand()%num+1;
		cout<<"第";cout<<count;cout<<"轮"<<endl; 
		Sout(""),Sout(question[number]);
		cout<<endl<<"请回答:";
		string yourans;
		cin>>yourans;
		if(yourans==ans[number])
		{
			Sout("恭喜你，你答对了！"); 
			wincount++;
			Sout("你已经累计答对"),cout<<wincount<<"次!";
			cout<<endl; 
			_getch();
		}
		else
		{
			Sout("很抱歉，你答错了");
			Sout("正确答案是:"),cout<<ans[number]<<endl;
			_getch(); 
		}
		quested[number]=1;
		count++;
	}
	happened+=(name+"参加了小升初考，考了个好成绩/");
	Sout("你已经答完了题库中现有的所有题！你的正确率是");
	printf("%llf",(wincount*1.0)/(num*1.0)*100);
	cout<<"%"<<endl;
	Sout("\n你的得分是：");
	cout<<wincount*2;
	_getch();
	return wincount*2;
} 
const string que[]=
{
	"游戏的名字叫什么?（考试时的答案请输入拼音开头首字母，例如新华字典写为XHZD，标点符号省略）",
	"作者是谁？",
	"6层的完全二叉树有几个叶子节点？",
	"万能头怎么写？",
	"本游戏是不是好游戏？(YES/NO)",
	"作者的QQ号是多少？",
	"你记得自己吃过多少块巧克力吗？（提示：某著名小数的循环节）",
	"圆周率第50位是几？",
	"根号10约等于多少（6位小数）?",
	"“查看属性”中第三个是什么？" ,
	"截至2020/11/21，作者的闹钟升级为哪个版本（格式: vX.X）",
	"你们班的7号叫什么名字？",
	"作者的《CNLDJ》第100关在哪一版？",
	"看书时弹出的信息是什么？",
	"“我洗海带哟~”是那首歌？",
	"枚举法中，想要减少循环次数，需要用到的方法是______",
	"单词接龙：如果BEAST和ASTONISH接成一条龙，那么结果为BEASTONISH，请问AT,TOUCH,CHEAT,CHOOSE,TACT以A开头的最长的“龙”是什么？",
	"53!的结果中含有几个2的因子？",
	"15668392710381900147392的乘积根是多少?",
	"1!+2!+3!+4!+5!+6!+7!+8!+9!+10+11!+12!+13!+14!+15!+16!=__________",
};
string answe[20]=
{
	"RSZL",
	"MCYH",
	"32",
	"#include<bits/stdc++.h>",
	"YES",
	"3491576605",
	"142857",
	"7",
	"3.162277",
	"HP",
	"v3.0",
	"",
	"4",
	"GLGJSSYQYHFBQZ",
	"UNRAVEL",
	"JZ",
	"ATOUCHEATACTACTOUCHOOSE",
	"49",
	"6",
	"22324392524313",
};
 
float kaoshi()
{
	use(39);
	answe[11]=student[7];
	float n=0.0;
	int i,j,k;
	string answ;
	for(i=0;i<20;i++)
	  {
	  	gs();
	  	Sout(que[i]);
	  	cin>>answ;
	  	if (answ==answe[i])
	  	  Sout("答对了！"),n+=5.0;
	  	else{ 
	  	  Sout("很遗憾答错了，正确答案是");Sout(answe[i]);
			} 
	  }
	gs();
	printf("你的最终得分是：");
	printf("%f",n);
	return n;
}
#define framex 5
#define framey 5
#define wide 20
#define high 20
int i,j,a[2];	
//游戏封面
void Gotoxy(HANDLE hout,int x,int y){
    //COORD是WindowsAPI中定义的一种结构，表示一个字符在控制台屏幕上的坐标
    COORD pos;
    pos.X=x;
    pos.Y=y;
    //SetConsoleCursorPosition是API中定位光标位置的函数。
    SetConsoleCursorPosition(hout,pos);
}
void cover (HANDLE hout){
    char a;
    a=getchar();
    system("cls");
} 
//定义蛇的结构体 
struct  Snake{
    int x[100];
    int y[100];
    int speed;
    int length;
    int count;
};
//定义食物的结构体 
struct Food{
    int x;
    int y;
};
//制作框架 
void makeframe(struct Snake snake){
    //定义显示器变量句柄 
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
   // color(7);
    Gotoxy(hout,framex+wide*2+5,framey);
    printf( "   贪吃蛇"); 
    Gotoxy(hout,framex+wide*2+5,framey+3);
    printf("使用方向键或wasd移动");
    Gotoxy(hout,framex+wide*2+5,framey+5);
    printf("长按方向键可加速");
    Gotoxy(hout,framex+wide*2+5,framey+7);
    printf("按任意键暂停,方向键继续");
    //打印上边框 
    for(i=0;i<wide*2+1;i++){
        Gotoxy(hout,framex+i,framey);
        printf("*");
    }
    //打印下边框 
    for(i=0;i<wide*2+2;i++){
        Gotoxy(hout,framex+i,framey+high);
        printf("*");
    }
    //打印左边框 
    for(i=0;i<high;i++){
        Gotoxy(hout,framex,framey+i);
        printf("■");
    }
    //打印右边框 
    for(i=0;i<high;i++){
        Gotoxy(hout,framex+wide*2+1,framey+i);
        printf("■");
    }
}
//游戏信息
void infor(HANDLE hout,struct Snake* snake){
    Gotoxy(hout,framex+wide*2+5,framey+15);
 //   color(6);
    printf("当前速度:%d",-snake->speed+500);
    Gotoxy(hout,framex+wide*2+5,framey+17);
//    color(8);
    printf("当前得分:%d",snake->count);
    Gotoxy(hout,framex+wide*2+5,framey+19);
   // color(4);
    printf("当前长度:%d",snake->length);
} 
//初始化蛇 
void initsnake(struct Snake *snake){
    snake->x[0]=framex+2;
    snake->y[0]=framey+high/2;
    snake->count=0;
    snake->length=3;
    snake->speed=400;
    //初始化由蛇尾至蛇头的坐标 
    for(i=1;i<snake->length;i++){
        snake->x[i]=snake->x[i-1]+1;
        snake->y[i]=snake->y[i-1];
    }
}
//打印蛇 
void printsnake(HANDLE hout ,struct Snake *snake){
    for(i=0;i<snake->length;i++){
        Gotoxy(hout,snake->x[i],snake->y[i]);
        if(i==snake->length-1) 
          { 
         //   color(6);
            printf("·");
          }
        else if(i==0)
          {
          //	color(8);
            printf("０");
          }
        else 
          {
          //	color(4);
            printf("■"); 
          }
    }
}
//移动蛇 
void movesnake(HANDLE hout,struct Snake *snake){
    Gotoxy(hout,snake->x[0],snake->y[0]);
    //清除蛇尾 
    printf("  ");
    //蛇的后一节坐标变成前一节的坐标 
    for(i=1;i<snake->length;i++){
        snake->x[i-1]=snake->x[i];
        snake->y[i-1]=snake->y[i];
    }
}
//打印食物 
void printfood (HANDLE hout,struct Snake *snake,struct Food* food){
    //用计算机时间获取随机值 
    srand((unsigned)time(NULL));
    while(1){
        //将食物的横纵坐标的大小限定在窗口大小内 
        food->x=rand()%(wide-2)+1;
        food->y=rand()%(high-2)+1;
        //避免食物出现在边框上 
        if(food->x==0&&food->y==0)
            continue;
        //将食物的坐标放置在窗口内 
        food->x=2*food->x+framex;
        food->y+=framey;
        //如果食物出现在蛇上，重新产生食物 
        for(i=0;i<snake->length;i++){
            if(food->x==snake->x[i]&&food->y==snake->y[i])
                break;
        }
        //食物不在蛇上，打印食物，结束循环 
        if(i==snake->length){
            Gotoxy(hout,food->x,food->y);
           // color(7);
            printf("Ｑ");
            break;  
        }
    }
 
}
//吃食物 
void eatfood(HANDLE hout,struct Snake * snake,struct Food *food){
    //如果蛇头的坐标等于食物的坐标 
    if(snake->x[snake->length-1]==food->x&&snake->y[snake->length-1]==food->y){
        //蛇长加一 
        snake->length++;
        //蛇身（不包括蛇尾）整体像前移动一格 
        for(i=snake->length-1;i>0;i--){
            snake->x[i]=snake->x[i-1];
            snake->y[i]=snake->y[i-1];
        }
        //得到蛇尾的坐标（即蛇移动前的蛇尾坐标） 
        snake->x[0]=a[0];      
        snake->y[0]=a[1];
        printfood(hout,snake,food);
        snake->count++;
        if(snake->count%3==0)
            snake->speed-=50;
    }
}
//死亡判断 
int ifdead(struct Snake* snake){
    //如果碰到左边界 返回0；
    if(snake->x[snake->length-1]==framex)
        return 0;
    //如果碰到右边界 返回0；
    if(snake->x[snake->length-1]==framex+wide*2)
        return 0;
    //如果碰到上边界 返回0；
    if(snake->y[snake->length-1]==framey)
        return 0;
    //如果碰到下边界 返回0；
    if(snake->y[snake->length-1]==framey+high)
        return 0;
    //如果碰到自己身体 返回0； 
    for(i=0; i<snake->length-1; i++) 
        if( snake->x[snake->length-1]==snake->x[i] && snake->y[snake->length-1]==snake->y[i] ) 
            return 0;
    //否则返回1； 
    return 1;
}
//开始游戏 
int Snake(){
    unsigned char ch =77;
    //定义显示器句柄 
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    cover(hout);
    struct Snake s, *snake=&s;
    struct Food  f,  *food=&f;
    makeframe(*snake);
    initsnake(snake);
    printfood(hout,snake,food);
    Sleep(500);
    while(1){
        infor(hout,snake);
        //保存蛇尾横纵坐标 
        a[0]=snake->x[0];
        a[1]=snake->y[0];
        j=0;
        //如果用户敲击键盘
        if(kbhit()){ 
            //用ch接收输入 ，注意是getch()，不需敲击回车
            ch=getch();
            if(kbhit()){
            //长按时间
                Sleep(20);
                j=1;
            }
        }
        switch(ch){
            //向上移动 
            case'W':
            case 'w' :
            case 72:{
                movesnake(hout,snake);
                //蛇头纵坐标减一 
                snake->y[snake->length-1]-=1;
                break;
            }
            //向下移动 
            case'S':
            case 's':
            case 80:{
                movesnake(hout,snake);
                //蛇头纵坐标加一 
                snake->y[snake->length-1]+=1;
                break;
            }
            //向左移动 
            case'A':
            case 'a':
            case 75:{
                movesnake(hout,snake);
                //蛇头横坐标减二 
                snake->x[snake->length-1]-=2;
                break;
            }
            //向右移动 
            case'D':
            case 'd':
            case 77:{
                movesnake(hout,snake);
                //蛇头横坐标加二 
                snake->x[snake->length-1]+=2;
                break;
            }
        }
 
        eatfood(hout,snake,food);
        printsnake(hout,snake);
        //如果判断蛇死亡，跳出循环 
        if(ifdead(snake)==0||ch==27||snake->speed==0){
            Gotoxy(hout,framex+wide/2,framey-2);
            if(snake->speed==0)
                printf("恭喜你通关了！！!");
            else
                printf("糟糕 T_T");
            break;
        }
 
        if(j==0)
        //如果没有长按，蛇滞留的时间为 
            Sleep(snake->speed);
        //如果长按，蛇滞留的时间为 20ms，即加速 
        else 
            Sleep(20);
    }
    //跳出循环时 ，滞留死亡场景一段时间
    Sleep(3000);
    //清屏 
    system("cls");
    //显示结束界面 
    if(snake->speed==0) {
	
        printf("\n\n\n\n\n\t\t\t哈哈，你赢了\n\n\t\t\t你得到了满分：24\n\n\n");return 24;}
    else {
        printf("\n\n\n\n\n\t\t\t哈哈，你输了\n\n\t\t\t你的最终得分是：%d\n\n\n",snake->count);return snake->count; }
    Sleep(3000);
    return 0; 
}
 
int psss()
{
	string what[3]={"石头","剪刀","布"};
	int n,m,i,j,k;
	for(i=0;i<=2;i++)
	  printf("%d.%s\n",i,what[i].c_str());
	cout<<"你出什么？";
	cin>>n;
	srand(time(0));
	m=random(0,2);
	cout<<"你出的是"<<what[n]<<"，老板出了"<<what[m];
	switch(n-m)
	  {
	  	case -1:
	  	case 2:cout<<"你赢了！";return 2;
	  	case 0:cout<<"平局！";return 1;
	  	default:cout<<"你输了！";return 0;
	  }
}
bool saolei(){
int delta[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
int row =0,col = 0,num = 0;
char map[10][10] = {0};
char show[10][10] = {0};
srand(time(0));
for(row = 0;row <= 9;row++){
for(col = 0;col <= 9;col++){
map[row][col] = '0';
}
}
do{
row = rand() % 10;
col = rand() % 10;
if(map[row][col] == '0'){
map[row][col] = 'x';
num++;
}
}while(num < 10);
for (row = 0;row <= 9;row++){
for (col = 0;col <= 9;col++){
if(map[row][col] != 'x'){
int cnt = 0;
for (num = 0;num <= 7;num++){
if(row + delta[num][0] < 0){
continue;
}
if(row + delta[num][0] > 9){
continue;
}
if(col + delta[num][1] < 0){
continue;
}
if(col + delta[num][1] > 9){
continue;
}
if(map[row + delta[num][0]][col + delta[num][1]]== 'x'){
cnt++;
}
}
map[row][col] = '0' + cnt;
}
}
}
for (row = 0;row < 10;row++){
for(col = 0;col < 10;col ++){
printf("* ");
}
printf("\n");
}
num = 0;
int x,y;
do{
printf("please enter the coordinate of array:");
scanf("%d%d",&x,&y);
show[x-1][y-1] = 1;
if(map[x-1][y-1] == '0'){
for (num = 0;num <= 7;num++){
if(x-1 + delta[num][0] < 0){
continue;
}
if(x-1 + delta[num][0] > 9){
continue;
}
if(y -1+ delta[num][1] < 0){
continue;
}
if(y-1 + delta[num][1] > 9){
continue;
}
show[x-1+delta[num][0]][y-1+delta[num][1]] = 1;
}
}
if (map[x-1][y-1]!= 'x'&&map[x-1][y-1] != '0'){
for (num = 0;num <= 7;num++){
int cnt = 0;
if(x-1 + delta[num][0] < 0){
continue;
}
if(x-1 + delta[num][0] > 9){
continue;
}
if(y-1 + delta[num][1] < 0){
continue;
}
if(y-1 + delta[num][1] > 9){
continue;
}
if( map[x -1 + delta[num][0]][y -1+ delta[num][1]] != 'x'){
show[x-1  + delta[num][0]][y -1+ delta[num][1]] = 1 ;
}
}
 
}
if(map[x-1][y-1] == 'x') {
printf("game over!\n");
for (row = 0;row < 10;row++){
for(col = 0;col < 10;col ++){
printf("%c ",map[row][col]);
}
printf("\n");
}
return 0;
}
system("cls");
printf("mine sweeping:\n");
for (row = 0;row < 10;row++){
for(col = 0;col < 10;col ++){
if (show[row][col] == 1)
{
printf("%c ", map[row][col]);
}
else
{
printf("* ");
}
}
printf("\n");
}
num = 0;
for (row = 0;row < 10;row++){
for(col = 0;col < 10;col ++){
if (show[row][col] == 1 )
{
num++;
}
}
}
printf("num:%d\n",num);
}while(num < 90);
printf("you win!");
return 1;
}
int dazi()
{
	string Right="tyduafidooduaepepeidiaeofpdiaepdd\nincldiepapdpeedfidncfidkdledeidd\njdicndleiicneldiapapppeodmcmcadfad\naofdahldkfiehalfdfhoea\n$#$#$!$#@><$dfa>#?!$32>$!#@?\n>$!#@?$#314321FSAD?$@!\nFAdfadl.3$!@#>afdsk4ml132>adfadsl\njflasdfiawehochodackodhiossdjafoisjoifudhalfdlsfhwe8hlfefafjeiajfls\nhfadshioewclzxkdjhfldshadsujcndalheicdjalfsd\nhfdshioqwefawiew#$#!ndafslkdwifdsalhuwoiefdsaiufhuefohoeiafdsa\nfqwelcdxnzleuwiqrwiofadsjflsdfjldsaj\nhfkdlsffhklashflwiuehcnczksiewaolkdsahifls\nhflaidshiohafusehriokndasfjihlueo\nfhakdsfhwei#$!#@$kadhf#R9ofa#$dsf89ewq#$sdfihf3#R;sdfEWQ#RFDSFEAqliru9dss\n";
   char c;
	printf("在屏幕上打出这段话，随时按`加enter结束（随时可以按回车，不算错字）\n\n%s\n",Right.c_str());
    char ch;
    int n=0,right=0;
    time_t t1,t2;
    time(&t1);
    while(1)
      { 
      ch=_getch();
      cout<<ch;
          if (ch==Right[n])
            right++;
        if (ch=='`')
          break;
          n++;
      } 
    time(&t2);
    printf("\n总的输入字符数;%d",n);
    printf("\n对的字符数：%d",right);
    printf("\n总时长：%d秒",t2-t1); 
    printf("\n平均录入速度;%.2f/s",1.0*right/(t2-t1));
    printf("\n平均每分钟速度：%.2f/s",1.0*right/(t2-t1)*60);
    int S=1;
    printf("\n段位：");
    int s=1.0*right/(t2-t1)*60;
    if (s>=0&&s<50)
      printf("LV.1初学者");
    if (s>=50&&s<100)
      printf("LV.2有点水平");
    if (s>=100&&s<150)
      printf("LV.3超越正常人");
    if (s>=150&&s<220)
      printf("LV.4编程队员的水平");
    if (s>=220&&s<300)
      printf("LV.5程序猿");
    if (s>=300&&s<400)
      printf("LV.6速度不是盖的");
    if (s>=400&&s<480)
      printf("LV.7打字能手");
    if (s>=480&&s<550)
      printf("LV.8超级程序员");
    if (s>=550&&s<650)
      printf("LV.9电脑大师");
    if (s>=650&&s<850)
      printf("LV.10计算机大佬");
    if (s>=850)
	  printf("LV.11世界冠军"); 
    return s;
}
int const ROW = 4;
int const COL = 4;
int gamemap[ROW][COL] = {0};
 
//上下左右
int const UP = 1;
int const DOWN = 2;
int const LEFT = 3;
int const RIGHT = 4;
 
//游戏所处的状态
int const GAME_OVER = 1;
int const GAME_WIN = 2;
int const GAME_CONTINUE = 3;
 
enum GameNum
{
	Game_2 = 2,
	Game_4 = 4,
	Game_8 = 8,
	Game_16 = 16,
	Game_32 = 32,
	Game_64 = 64,
	Game_128 = 128,
	Game_256 = 256,
	Game_512 = 512,
	Game_1024 = 1024,
	Game_2048 = 2048,
};
 
//打印所得的数组
void Print()
{
	system("cls");
	cout << "*****************  2048 小 游 戏  ******************" << endl;
	cout << "*****************  ＧＡＭＥ 2048  ******************" << endl << endl;
	for (int i = 0; i < ROW; ++i)
	{
		cout << "---------------------------------"<< endl;
		for (int j = 0; j < COL; ++j)
		{
			if (gamemap[i][j] == 0)
			{
				cout <<"|   \t";
			}
			else 
			{
				cout <<"|   " << gamemap[i][j] << "\t";
			}
		}
		cout << "|" << endl;
	}
	cout << "---------------------------------"<< endl;
}
 
 
bool CreateNumber()
{
	int x = -1;
	int y = -1;
	int times = 0;
	int maxTimes = ROW * COL;
	//三分之二的概率生成2，三分之一的概率生成4
	int whitch = rand() % 3;
	do 
	{
		x = rand() % ROW;
		y = rand() % COL;
		++times;
	} while (gamemap[x][y] != 0 && times <= maxTimes);
 
	//说明格子已经满了
	if(times >= maxTimes)
	{
		return false;
	}
	else
	{
		GameNum num;
		if(whitch == 0)
		{
			num = Game_4;
		}
		else if(whitch)
		{
			num = Game_2;
		}
		gamemap[x][y] = num;
	}
 
	return true;
}
 
void Process(int direction)
{
	switch (direction)
	{
	case UP:
		//最上面一行不动
		for(int row = 1; row < ROW; ++row)
		{
			for(int crow = row; crow >= 1; --crow)
			{
				for(int col = 0; col < COL; ++col)
				{
					//上一个格子为空
					if(gamemap[crow-1][col] == 0)
					{
						gamemap[crow-1][col] = gamemap[crow][col];
						gamemap[crow][col] = 0;
					}
					else 
					{
						//合并
						if(gamemap[crow-1][col] == gamemap[crow][col])
						{
							gamemap[crow - 1][col] *= 2;
							gamemap[crow][col] = 0;
						}
 
					}
				}
			}
		}
		break;
	case DOWN:
		//最下面一行不动
		for(int row = ROW - 2; row >= 0; --row)
		{
			for(int crow = row; crow < ROW - 1; ++crow)
			{
				for(int col = 0; col < COL; ++col)
				{
					//上一个格子为空
					if(gamemap[crow + 1][col] == 0)
					{
						gamemap[crow + 1][col] = gamemap[crow][col];
						gamemap[crow][col] = 0;
					}
					else 
					{
						//合并
						if(gamemap[crow + 1][col] == gamemap[crow][col])
						{
							gamemap[crow + 1][col] *= 2;
							gamemap[crow][col] = 0;
						}
 
					}
				}
			}
		}
		break;
	case LEFT:
		//最左边一列不动
		for(int  col = 1; col < COL; ++col)
		{
			for(int ccol = col; ccol >= 1; --ccol)
			{
				for(int row = 0; row < ROW; ++row)
				{
					//上一个格子为空
					if(gamemap[row][ccol-1] == 0)
					{
						gamemap[row][ccol - 1] = gamemap[row][ccol];
						gamemap[row][ccol] = 0;
					}
					else 
					{
						//合并
						if(gamemap[row][ccol - 1] == gamemap[row][ccol])
						{
							gamemap[row][ccol - 1] *= 2;
							gamemap[row][ccol] = 0;
						}
 
					}
				}
			}
		}
		break;
	case RIGHT:
		//最右边一列不动
		for(int  col = COL - 2; col >= 0; --col)
		{
			for(int ccol = col; ccol <= COL - 2; ++ccol)
			{
				for(int row = 0; row < ROW; ++row)
				{
					//上一个格子为空
					if(gamemap[row][ccol + 1] == 0)
					{
						gamemap[row][ccol + 1] = gamemap[row][ccol];
						gamemap[row][ccol] = 0;
					}
					else 
					{
						//合并
						if(gamemap[row][ccol + 1] == gamemap[row][ccol])
						{
							gamemap[row][ccol + 1] *= 2;
							gamemap[row][ccol] = 0;
						}
 
					}
				}
			}
		}
		break;
	}
 
}
 
//处理输入输出，返回上下左右
int Input()
{
	//读取上下左右四个方向键
	int upArrow = 0;
	int downArrow = 0;
	int leftArrow = 0;
	int rightArrow = 0;
	int direction = 0;
	while (true)
	{
		upArrow = GetAsyncKeyState(VK_UP);
		downArrow = GetAsyncKeyState(VK_DOWN);
		leftArrow = GetAsyncKeyState(VK_LEFT);
		rightArrow = GetAsyncKeyState(VK_RIGHT);
 
		if(upArrow)
		{
			direction = UP;
			break;
		}
		else if(downArrow)
		{
			direction = DOWN;
			break;
		}
		else if(leftArrow)
		{
			direction = LEFT;
			break;
		}
		else if(rightArrow)
		{
			direction = RIGHT;
			break;
		} 
 
	}
 
	return direction;
}
 
//判断游戏状态
int Judge()
{
	//赢得游戏
	for(int i = 0; i < ROW; ++i)
	{
		for(int j = 0; j < COL; ++j)
		{
			if(gamemap[i][j] == 2048)
			{
				return GAME_WIN;
				break;
			}
		}
	}
 
	//横向检查
	for(int i = 0 ; i < ROW; ++i)
	{
		for(int j = 0; j < COL - 1; ++j)
		{
			if(!gamemap[i][j] || (gamemap[i][j] == gamemap[i][j+1]))
			{
				return GAME_CONTINUE;
			}
		}
	}
	//纵向检查
	for(int j = 0; j< COL; ++j)
	{
		for(int i = 0; i < ROW -1; ++i)
		{
			if(!gamemap[i][j] || (gamemap[i][j] == gamemap[i+1][j]))
			{
				return GAME_CONTINUE;
				break;
			}
		}
	}
 
	//不符合上述两种状况，游戏结束
	return GAME_OVER;
}
 
bool game2048()
{
	CreateNumber();
	CreateNumber();
	//数组初始化
	for(int i=0;i<4;i++)
	  for(int j=0;j<4;j++)
	    gamemap[i][j]=0; 
	Print();
	int direction = 0;
	int gameState = -1;
	while(true)
	{
		direction = Input();
		gameState = Judge();
		if(direction && gameState == GAME_CONTINUE)
		{
			Process(direction);
			CreateNumber();
			Print();
		}
		else if(gameState == GAME_WIN)
		{
			Print();
			cout << "You Win！" << endl;
			hdcj(2);
			return 1;
		}
		else if(gameState == GAME_OVER)
		{
			Print();
			cout <<"You lose!" << endl;
			return 0;
		}
	}
}
void carnie()
{
	cls();
	while(1)
	  {
	  	cout<<"欢迎来到游乐场~按下序号即可玩相应的游戏~\n";
	  	const string where[]=
	  	{"贪吃蛇","石头剪刀布","扫雷","打字游戏","2048","离开","有奖问答"};
	  	int i,j,k,n,m;
	  	char l;
	  	for(i=0;i<1000;i++)
	  	  if (kbhit())
	  	    l=getch();//垃圾收集器 
	  	for(i=0;i<=6;i++)
	  	  printf("%d.%s\n",i,where[i].c_str());
	  	if (things[188]==1)
	      l=choose(4)+'0';
	    else
	  	    l=_getch();
	  	switch(l)
	  	  {
	  	  	case '0':{
	  	  		use(39);
	  	  		happened+=(name+"在游乐场畅玩贪吃蛇/");
	  	  		tepan();
	  	  		things[8]-=5;
	  	  	cls();
	  	  	cout<<"你要押多少钱？（注：9分以下血本无归，10分获得50%押钱，11~13获得70%押钱，14获得90%，15获得100%，以后每分增加5%\n";
	  	  	cin>>k;
	  	  	if (things[7]<k)
                                          	  	  	  {
	  	  	  	cout<<"钱不够！";
	  	  	  	break;
				  }
	  	  	things[7]-=k;
				float cl[25]=
	  	  	{0,0,0,0,0,0,0,0,0,0,0.5,0.7,0.7,0.7,0.9,1,1.05,1.1,1.15,1.2,1.25,1.3,1.35,1.4,1.45};
			n=Snake();
	  	  	cls();
	  	  	m=k*cl[n];
	  	  	printf("你获得了：%d元",m);
	  	  	things[7]+=m;
	  	  	gotmoney+=m;
	  	  	break;}
	  	  	case '1':
	  	  		{
	  	  			use(40);
	  	  			happened+=(name+"在游乐场和老板玩石头剪刀布/");
	  	  			tepan();
	  	  			things[8]-=5;
	  	  		cls();
	  	  		cout<<"你要押多少钱？（注：输了血本无归，平局回本，赢了双倍收获\n";
	  	  		cin>>k;
	  	  		if (things[7]<k)
	  	  		  {
	  	  		  	cout<<"钱不够！";
	  	  		  	break;
					  }
	  	  		cls();
	  			things[7]-=k;
	  			n=psss();
	  			if (n==1)
	  			  things[7]+=k,gotmoney+=k;
	  			if (n==2)
	  			  things[7]+=k*2,gotmoney+=k*2;
	  			break;
	  		}
	  		case '2':
	  			{tepan();
	  			use(41);
	  	  			things[8]-=5;
	  			cls();
	  			cout<<"你要押多少钱？（注:输了血本无归，赢了双倍收获）\n";
	  			cin>>k;
	  			if (things[7]<k)
	  			  {
	  			  	cout<<"钱不够！";
	  			  	break;
					}
				cls();
				things[7]-=k;
				n=saolei();
				if (n)
				  {
				  	happened+=(name+"玩扫雷游戏，还成功了/");
				  	cout<<"你赢了!";
				  	things[7]+=k*2;
				  	gotmoney+=k*2;
				  	hdcj(40);
				  }
				else
				  {
				    cout<<"你输了！";
				    happened+=(name+"在玩扫雷游戏时被雷炸飞了/");
				  }
				break;
			}
			case '3':{tepan();
			use(42);
	  	  			things[8]-=5;
			cout<<"你要押多少钱？（注：60每分钟以下没钱，60回本，以后每50增加10%）"; 
			cin>>n;
			if (things[7]<n)
				{
					cout<<"钱不够！";
					break;
				}
			things[7]-=n;
			j=dazi();
			if (j>=250)
			  hdcj(8);
			m=0;
			if (j==60)
			  m=n;
			 if (j>60)
			   {
			   	m=n*(1+(float(j/50)*0.1));
				} 
			cout<<"你赚到了："<<m<<"元！\n";
			gs();
			things[7]+=m;
			gotmoney+=m;
			break;}
			case '4':
				{
					tepan();
	    		things[8]-=5;
					printf("你要押多少钱？（输了无钱，赢了双倍收获）\n");
					cin>>m;
					if (m>things[7])
					  {
					  	cout<<"钱不够！";
					  	break;
					  }
					things[7]-=m;
					if (game2048())
					  m*=2;
					else
					  m=0;
					things[7]+=m;
					cout<<"你赚到了"<<m<<"元";
					gotmoney+=m;
					happened+=(name+"在游乐场玩2048/");
					break;
				}
			case '5':tepan();
	  	  			things[8]-=5;return;
	  	  	case '6':
	  	  		{
	  	  			cls();
	  	  			gotoxy(1,45);
	  	  			printf("有奖问答");
	  	  			coutwhat(2,20,2,70,"=");
	  	  			gotoxy(5,25);
	  	  			printf("规则：");
	  	  			gotoxy(7,29);
	  	  			printf("1.每轮共有20道问题需要回答\n");
	  	  			gotoxy(9,29);
	  	  			printf("2.答对一题+5分，答错-5分\n");
	  	  			gotoxy(11,29);
	  	  			printf("3.");
				}
	  	  	case '/'://作弊，没事别用 
				{
					int num;
					string dm;
					string one,two,three,four;
					cin>>dm>>one>>two>>three>>four;
					cin>>num;
					if (dm!="/")
					  break;
					//gamemode
					if (one=="gamemode"&&three=="*"&&four=="*")
					  things[21]=two[0]-'0';
					//things
					if (one=="gamethings"&&three=="of"&&four=="*")
					  {
					  	int a,b;
					  	a=(two[0]-'0')*100+(two[1]-'0')*10+(two[2]-'0')*1;
					  	things[a]+=num;
					  }
					//fost
					if (one=="fost"&&three=="of"&&four=="*")
					  {
					  	int a,b;
					  	a=(two[0]-'0')*100+(two[1]-'0')*10+(two[2]-'0')*1;
					  	fost[a]+=num;
					  }
					break;
				} 
		}
			gs();
	  }
}
void market()
{
	cout<<"WAH：小子，又来打工了啊，你这样的小身板还敢来人力市场！\n";
	const string where[]=
	{"搬砖（60%概率成功，得500块）(临工)","抄作业（100%概率成功，可以批量接受，但是要密码，100块）","文字录入（40%概率成功，1000）（临时工）","离开","找工作","领取挂机收益"};
	int i,j,k,n,m;
	while(1)
	  {cls();
	  char l;
	     for(i=0;i<6;i++)
		   printf("%d.%s\n",i,where[i].c_str());
		 if (things[188]==1)
	      l=choose(5)+'0';
	     else
		  l=_getch();
		  tepan();
		  things[8]-=15;
		  switch(l)
		    {
		    	case '0':
		    		
		    		use(43);tepan();
	    		things[8]-=5;
		    		happened+=(name+"在工地上搬砖/");
		    		Sout("你费力地搬起一堆堆沉重的砖头，砖头却纹丝不动，你又使出了吃奶的劲儿。");
		    		jdt(10);
		    		if (rand()%5<=2)
		    		  {
		    		  	cout<<"获得:500元";
		    		  	things[7]+=500;
		    		  	gotmoney+=500;
					  }
					else
					  cout<<"WAH：你才搬了几块砖头？！没有工资！！";
					gs();
					break;
				case '1':
					{
					cout<<"密码：";
					bool Right=true;
					string MM="ZJL20090206";
					for(j=0;j<11;j++)
					  {
					  	char m=_getch();
					  	cout<<'*';
					  	if (m!=MM[j])
					  	  Right=false;
					  }
					if (Right)
					  {
					  	happened+=(name+"窃取了抄作业的密码，疯狂抄作业/");
					  	cout<<"抄几次？";
					  	cin>>m;
					  	jdt(10);
						  things[7]+=100*m,gotmoney+=100*m; 
					  }
					else
					  {
					    cout<<"没有密码就别逞强！";
					    happened+=(name+"竟然没有密码也想抄作业赚钱/");
					  }
					gs();
					break;
				}
				case '2':
					use(44);
					tepan();
	    		things[8]-=5;
					Sout("你费力地看着一行行文字，感觉眼睛生疼，但是为了赚到钱，你拼了！");
					jdt(10);
					if (rand()%5<=1)
					  {
					  	cout<<"获得1000元！";
					  	things[7]+=1000,gotmoney+=1000;
					  }
					else
					  cout<<"WAH：打错了好几个字，没有工资！！";
					gs();
					break;
				case '3':return;
				case '4':
					{
						use(45);
						tepan();
	    		things[8]-=5;
						switch(things[28])
						  {
						  	case 4:
						  		cls();
						  		Sout("老板：这位可是白云大学的呢！来这里！工资高!");
						  		gs();
						  		cout<<"你被SORT_TIS公司录取了，（挂机收益：70元/分钟）";
						  		things[29]=70;
						  		happened+=(name+"被SORT_TIS公司录取为高级程序员/");
						  		break;
						  	case 3:
						  		cls();
						  		Sout("老板：你是白云大学的啊。还不错哦~");
						  		gs();
						  		cout<<"你被WAMVA公司录取了，（挂机收益：55元/分钟）";
						  		things[29]=55;
						  		happened+=(name+"被WAMVA公司录取为经理/");
						  		break;
						  	case 2:
						  		cls();
						  		Sout("老板：emmmmm...白云大学，没听说过呢。");
						  		gs();
						  		cout<<"你被WMC公司录取了，（挂机收益：35元/分钟）";
						  		happened+=(name+"被WMC公司录取为科长/");
						  		things[29]=35;break;
						  	case 1:
						  		cls();
						  		Sout("老板：（很为难的样子）白云大学，不怎么样啊，公司缺人，你还是来上班吧。。。");
						  		gs();
						  		cout<<"你被NOTSH公司录取了，（挂机收益10元/分钟）";
						  		happened+=(name+"被NOTSH公司录取为一名普通职员/");
						  		things[29]=10;break;
						  	case 0:
						  		cls();
						  		Sout("老板：你连大学都没上啊，你去办公室扫地吧。。。");
						  		gs();
						  		cout<<"你被CLEAN_FLOOR公司录取了，（挂机收益3元/分钟）";
						  		happened+=(name+"被CLEAN_FLOOR公司录取为清洁工/");
						  		things[29]=3;
						  		break;
						  }
						break;
					}
				case '5':
					{
						tepan();
	    		things[8]-=5;
						use(46);
						time_t temp;
						time(&temp);
						m=temp-start;
						cout<<"挂机开始时间："<<start<<'\n';
						cout<<"挂机结束时间："<<temp<<'\n';
						cout<<"你挂机了"<<m<<"秒\n"; 
						m/=60;
						if (m>=480)
						  hdcj(29);
						if (m>=2880)
						  hdcj(30);
						cout<<"你已经挂机了"<<m<<"分钟\n";
						if (m>=things[30])
						  m=things[30];
						cout<<"收益："<<things[29]<<"元/分钟\n";
						cout<<"获得："<<m*things[29]<<"元钱！\n";
						things[7]+=things[29]*m,gotmoney+=things[29]*m;
						time_t te;
						time(&te);
						start=te;
						gs();
						break;
					}
				}	
	   } 
}
void Duchang()
{
	cls();
	srand(time(0));
	cout<<"WYQ：小子，又来赌场了啊，还想把裤子都输掉吗？哈哈哈...";
	const string where[]=
	{"赌大小","猜数","彩票","取数游戏","离开","老虎机"};
	int i,j,k,n,m;
	while(1)
	  {
	  	char l;
	  	for(i=0;i<1000;i++)
	  	  if (kbhit())
	  	    l=getch();//垃圾收集器 
	  	cls();
	  	for(i=0;i<6;i++)
	  	  {
	  	  	printf("%d.%s\n",i,where[i].c_str());
			}
		l=_getch();
		tepan();
		things[8]-=10;
		switch(l)
		  {
		  	case '0':
		  		{
		  			use(47);
		  			hdcj(16);
		  			tepan();
	    		things[8]-=5;
		  			system("cls");
		  			cout<<"1-大 2-小\n";
		  			cin>>m;
		  			cout<<"赌多少钱？";
		  			cin>>i;
		  			k=0;
		  			if (things[7]<i)
		  			  {
		  			  	cout<<"钱不够!";
		  			  	break;
						}
		  			things[7]-=i;
		  			for(j=1;j<=6;j++)
		  			  {
		  			  	n=rand()%6+1;
		  			  	printf("%d\n",n);
		  			  	k+=n;
						}
					if (k>21)
					  j=1;
					else
					  j=0;
					if (m==j)
					  {
					  	cout<<"赚到了!";
					  	things[7]+=i*2;
					  	gotmoney+=i*2;
					  	happened+=(name+"在赌场大赚一笔/");
					  }
					else
					  {
					    cout<<"血本无归!";
					    happened+=(name+"在赌场血亏/");
					  }
					break;
				  }
				case '1':
					{
					use(48);
					cout<<"赌多少钱？";
		  			cin>>i;
		  			tepan();
	    		things[8]-=5;
		  			k=0;
		  			if (things[7]<i)
		  			  {
		  			  	cout<<"钱不够!";
		  			  	break;
						}
		  			things[7]-=i;
						n=random(1,50);
						for(j=1;j<=6;j++)
						  {
						  	system("cls");
						  	cout<<"猜一个数，1~50之间，你还有"<<7-j<<"次机会\n";
						  	cin>>m; 
						  	if (m>n)
						  	  cout<<"Too big!";
						  	if (m<n)
						  	  cout<<"Too small!";
						  	if (m==n)
						  	  {
						  	  	things[69]++;
						  	  	cout<<"猜中了！你赚到了"<<i*2<<"元!";
						  	  	happened+=(name+"在猜数游戏中赚了很多钱/");
						  	  	things[7]+=i*2;
						  	  	gotmoney+=i*2;
						  	  	break;
							  }
							gs();
						  }
						if (j==7)
						  {
						    cout<<"血本无归！";
						    happened+=(name+"竟然连猜数游戏都猜不中/");
						    things[69]=0;
						  }
						if (things[69]>=5)
						  hdcj(37);
						break;
					}
					case '2':
						{
							use(49);
							tepan();
	    		things[8]-=5;
							int a[6]={0,1,100,10000,500000,1000},b[6]={0,100,10000,500000,10000000,1000000};
							int c[6]={0,20,10,5,4,1};
							cout<<"你要买什么彩票？\n";
							cout<<"1.1-->100 20%概率中\n";
							cout<<"2.100-->10000 10%\n";
							cout<<"3.10000-->500000 5%\n";
							cout<<"4.500000-->10000000 4%\n";
							cout<<"5.1000 --> 1000000 1%\n";
							cin>>m;
							if (things[7]<a[m]){
							  cout<<"钱不够！";break;}
							if (rand()%100+1<=c[m])
							  {
							  	cout<<"中奖了！简直是好运附体！";
							  	happened+=(name+"买彩票中奖了！/");
							  	things[7]+=b[m];
							  	gotmoney+=b[m];
							  	if (++things[198]>=20)
								   hdcj(55); 
							  }
							else
							  {
							    cout<<"毛都没抽到!";
							    happened+=(name+"早上没洗脸，买彩票遭血亏/");
							  }
							break;
						}
					case '3':
						{
							cls();
							tepan();
	    		things[8]-=5;
							cout<<"赌多少钱？\n";
							cin>>m;
							if (things[7]>=m)
							  things[7]-=m;
							else
							  {
							  	cout<<"钱不够";
							  	break;
							  }
							int a[21];
							cls();
							for(i=1;i<=20;i++)
							  a[i]=random(1,10000);
							for(i=1;i<=20;i++)
							  {
							  	gotoxy(0,0);
							  	cout<<a[i]<<' ';
							  	gotoxy(1,0);
							  	cout<<"1.选择 2.下一个";
							  	char l=_getch();
							  	switch(l)
							  	  {
							  	  	case '1':k=a[i];i=5555;
							  	  	case '2':break;
								  }
							  }
							j=0;
							for(i=1;i<=20;i++)
							  j+=(a[i]>k);
							cls();
							cout<<"得分:"<<20-j;
							switch(j)
							  {
							  	case 0:k=400;break;
							  	case 1:k=330;break;
							  	case 2:k=260;break;
							  	case 3:k=185;break;
							  	case 4:k=115;break;
							  	case 5:k=84;break;
							  	default:k=0;break;
							  }
							m*=(k/100.0);
							cout<<"\n赚了"<<m<<"元\n";
							cout<<"序列为：";
							for(i=1;i<=20;i++)
							  cout<<a[i]<<' ';
							things[7]+=m;
							gotmoney+=m;
							gs();
							break;
						}
					case '4':return;
					case '5':
						{
							tepan();
	    		things[8]-=5;
							char o[3]={'O','X','K'};//3,3 3,6 3,9
							int line[4]={0,3,6,9};
							cls();
							int i,j,k,last;
							cout<<"赌多少钱？";
							cin>>j;
							if (j>things[7])
							  {
							  	Sout("老虎机：钱，不够，出去！");
							  	break;
							  }
							else
							  things[7]-=j;
							coutwhat(1,1,1,12,"#");
							coutwhat(1,1,6,1,"#");
							coutwhat(1,12,6,12,"#");
							coutwhat(6,1,6,12,"#");
							coutwhat(2,5,5,5,"#");
							coutwhat(2,8,5,8,"#");
							bool win=true;
							for(i=1;i<=3;i++)
							  {
							  	for(int nbi=1;nbi<=random(40,50);nbi++)
							  	  {
							  		gotoxy(3,line[i]);
							  		k=rand()%3;
							  		cout<<o[k];
							  		if (i==1)
							  		  last=k;
							  		Sleep(50); 
							  	  }
							  	if (last!=k)
							  	  win=false;
							  }
							if (win)
							  {
							  	gotoxy(12,0);
							  	Sout("手气不错，你赢了！");
							  	j*=5;
							  	things[7]+=j,gotmoney+=j;
							  }
							else
							  {
							  	gotoxy(5,0);
							  	Sout("血本无归。");
							  }
							gs();
							break;
						}
		  }
		  gs();
	   } 
}
void Mid_School()
{
	const string where[]={"家（存档的地方）","学校（学习的地方）","小超市（购物的地方）","公园（运动）","游乐场（玩耍，赚点零花钱）","保存并退出","关于游戏","自杀","人力市场","赌场"};
	int i,j,k,n,m,l;
	while(1)
	  {
	  	for(i=0;i<1000;i++)
	  	  if (kbhit())
	  	    l=getch();//垃圾收集器 
	  	tepan();
	    things[8]-=5;
	  	cls();
	  	if (things[0]>=4)
	  	  return;
	  	if (things[10]>=18)
	  	  things[0]++;
	  	cout<<" Day "<<things[16]+((things[10]-6)*30)<<'\n';
	    cout<<"你想去哪里，按下序号\n";
	    for(i=0;i<10;i++)
	      printf("%d.%s\n",i,where[i].c_str());
	    char s=_getch();
	    switch(s)
	      {
	      	case '0':home();break;
	      	case '1':school();break;
	      	case '2':shop();break;
	      	case '3':park();break;
	      	case '4':carnie();break;
	      	case '5':Write_File();me.play+=clock(),exit(0);
	      	case '6':about();break;
	      	case '7':Sout("Ftr:？？？？");Die();break;
	      	case '8':market();break;
	      	case '9':Duchang();break;
		  }
	  }
}
int Exa()
{
	use(50);
	string q[100],a[100],b;
	int i,j,k;
	int n,m;
	n=50;
	q[1]="赌场老板叫什么名字？";
	a[1]="WYQ";
	q[2]="作者的生日你打算送什么？（Tips:水题）";
	a[2]="GIFT";
	q[3]="作者生活在哪个城市？（格式：例如广东广州为GDGZ）";
	a[3]="GDDG";
	q[4]="中序遍历的顺序？（父节点F，左节点L，右节点R）";
	a[4]="LFR";
	q[5]="1.01的12次方？（精确结果）";
	a[5]="1.126825030131969720661201";
	q[6]="360分解质因数的结果是：（Tips：格式，假如数据是35，那么输入结果为5*7";
	a[6]="2*2*2*3*3*5";
	q[7]="雪米拉的儿子叫什么？";
	a[7]="DM";
	q[8]="布鲁特斯是谁的老师？";
	a[8]="KASS";
	q[9]="克艾索斯和百夫长的决斗中谁赢了？";
	a[9]="KASS";
	q[10]="沙暴天气是谁释放的？（称号）";
	a[10]="QZ";
	q[11]="冰雪世界是谁的必杀技？";
	a[11]="KZD";
	q[12]="MC创作于哪一年？";
	a[12]="2009";
	q[13]="作者的出生日期？";
	a[13]="20090206";
	q[14]="MC的吉祥物是JS,KL和_____";
	a[14]="PXZ";
	q[15]="凋零的血量是：";
	a[15]="600";
	q[16]="MC最强的附魔属性是：";
	a[16]="JYXB";
	q[17]="用锋利V的木剑打人造成的伤害是多少？";
	a[17]="12";
	q[18]="娑丽丝的外号？";
	a[18]="HL";
	q[19]="扎普拉尔的克星？";
	
	a[19]="LKLDY";
	q[20]="三体星系就是______";
	a[20]="BRMZ";
	int num=19;
	int wincount=0;
	bool quested[100];
	memset(quested,0,sizeof(quested));
	string yourans;
	int count=0;
	while(count<=19)
	{
		system("cls");
		int number=rand()%num+1;
		while(quested[number])number=rand()%num+1;
		for(i=0;i<19;i++)
		  if (quested[i]==0)
		    break;
		if (i>=19)
		  break;
		cout<<"第";cout<<count;cout<<"轮"<<endl; 
		Sout(""),Sout(q[number]);
		cout<<endl<<"请回答:";
		string yourans;
		cin>>yourans;
		if(yourans==a[number])
		{
			Sout("恭喜你，你答对了！"); 
			wincount++;
			Sout("你已经累计答对"),cout<<wincount<<"次!";
			cout<<endl; 
			_getch();
		}
		else
		{
			Sout("很抱歉，你答错了");
			Sout("正确答案是:"),cout<<a[number]<<endl;
			_getch(); 
		}
		quested[number]=1;
		count++;
		if (count>=19)
		  break;
	}
	happened+=(name+"参加了高考/");
	Sout("你已经答完了题库中现有的所有题！你的正确率是");
	printf("%llf",(wincount*1.0)/(num*1.0)*100);
	cout<<"%"<<endl;
	Sout("\n你的得分是：");
	cout<<wincount*38;
	_getch();
	return wincount*38;
}
//0 可通行格子 1.挡墙 2.返回点 3.出生点 4.宝藏洞窟 5. 帮助 6.secret
const int dm[][110]=
{
	{1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,3,0,5,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,4,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,5,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,1,6,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,1,1,7,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,6,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,1,1,0,1,1,0,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,1,1,1,0,1,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,1,1,1,0,0,0,1,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,1,1,0,0,1,1,0,1,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,0,1,0,0,1,1,1,1,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
int High[500]; 
int mhigh[100];
//0可通行 1墙 2宝藏 3陷阱 
int mm[40][102];
const char sd[]={' ','#','B','X'};
const char ch[]={' ','#','B','F','S','H','R','s'};
int teea;
void Getrmap(float a,int k)
{
	cls();
	for(int i=1;i<=90;i++)
	  {
	  	gotoxy((101-mhigh[i]),i);
	  	cout<<"-";
	  }
}
void run()
{
	tepan();
	things[8]-=5;
	float mh=0.0;
	int i,j,k=1,l=1,r=90,time=0;
	for(i=5;i<=450;i++)
	  if (rand()%((High[i-1]/15+1))||High[i-1]>=50)
	    High[i]=random(0,High[i-1])%100;
	  else
	    High[i]=High[i-1]+1;
	for(i=l,j=1;i<=r;i++,j++)
	  mhigh[j]=High[i];
	Getrmap(0.0,1);
	while(k<=450)
	  {
	  	char a='?';
	  	if (kbhit())
	  	  a=getch();
	  	gotoxy(60,50);
	  	cout<<(k/450.0)*100.0<<"%\t\t\t"<<(float)time/20.0<<"s\t\t\tH:"<<mh<<"\t\t\t";
	  	time++;
	  	switch(a)
	  	  {
	  	  	case 'a':if (k>1&&mhigh[(k+1)%90-2]<=mh)k--;break;
	  	  	case 'd':if (k<450&&mhigh[(k+1)%90]<=mh)k++;break;
	  	  	case ' ':if (abs(mh)==mhigh[(k+1)%90-1])mh+=1.5;break;
	  	  	case 'e':return;
		  }
		if (k%90==0)
		  {
		  	k++; 
		  	l=k+1;
		  	r=l+90;
		  	for(i=l,j=1;i<=r;i++,j++)
	  		  mhigh[j]=High[i];
	  		Getrmap(mh,(k+1)%90-1);
		  }
		if (mh-0.4>mhigh[(k+1)%90-1])
		  mh-=0.4;
		else
		  mh=mhigh[(k+1)%90-1];
		gotoxy(100-mh,(k+1)%90-1);
		cout<<"O";
		Sleep(50);
		gotoxy(100-mh,(k+1)%90-1);
		cout<<" ";
		if (k>=450)
		  break;
	  }
	gotoxy(0,50);
	cout<<"恭喜你到达了终点！";
	Sleep(2000);
	gs();
	cout<<"奖品：";
	k=random(4,6);
	j=random(2,30);
	cout<<fsn[k]<<'*'<<j;
	fost[k]+=j;
	k=random(10000,500000);
	j=random(5000,80000);
	cout<<' '<<"XP*"<<k<<" money*"<<j;
	things[1]+=k;
	things[7]+=j;
	gotmoney+=j;
	gs();
	Getmap();
}
void SD()
{
	tepan();
	things[8]-=5;
	things[193]++; 
	use(75);
	int i,j,k,n,m,a,b;
	cout<<"生成地图中...";
	while(1)
	{
	for(i=0;i<40;i++)
	  for(j=0;j<101;j++)
	    mm[i][j]=0;
	switch(things[21])
	  {
	  	case 1:m=random(260,320);break;
	  	case 2:m=random(311,360);break;
	  	case 3:m=random(355,389);break;
	  	case 4:m=random(371,460);break;
	  }
	for(i=1;i<=m;i++)
	  {
	    do
	      {
	    	j=random(1,39);
	    	k=random(1,99);
		  }
		while(mm[j][k]!=0);
		mm[j][k]=3;
	  }
	int q=random(700,1300);
	for(i=1;i<=q;i++)
	  {
	  	do
	  	  {
	  	  	j=random(1,39);
	  	  	k=random(1,99);
		  }
		while(mm[j][k]!=0);
		mm[j][k]=1;
	  }
	do
	  {
	  	j=random(1,39);
	  	k=random(1,99);
	  }
	while(mm[j][k]!=0||(j==1||k==1));
	mm[j][k]=2;
	a=j,b=k;
	teea=1;
	  break;
	}
	cls(); 
	coutwhat(0,0,40,0,"#");
	coutwhat(0,0,0,100,"#");
	coutwhat(40,0,40,100,"#");
	coutwhat(0,100,40,100,"#");
//	color(7);
	for(i=1;i<40;i++)
	  {
	  	gotoxy(i,1);
	    for(j=1;j<100;j++)
	      {
	      	if (mm[i][j]==2)
	      	{
	      	//  color(1);
	        printf("%c",sd[mm[i][j]]);
	        color(7);
	        }
	        else printf("%c",sd[mm[i][j]]);
	      }
	    printf("\n");
	  }
	int x=1,y=1,zd=5,sy=3;
	int _3=1;
	bool find=1;
	while(find)
	{
		gotoxy(x,y);
	//	color(3);
		cout<<"o";
		gotoxy(43,0);
		cout<<"B 宝藏 o你 #墙 X陷阱\n";
		cout<<"WASD移动，E退出，Q使用炸弹 V使用瞬移（下次移动时朝那个方向移动3格）\n";
		cout<<"炸弹剩余："<<zd<<"瞬移技能剩余："<<sy<<endl;
		printf("你(%d,%d) 宝藏(%d,%d)",x,y,a,b); 
	  	char l=_getch();
	  	if (l=='w'||l=='s'||l=='a'||l=='d')
	  	  {
	  	    gotoxy(x,y);
	  	    cout<<" "; 
	  	  }
	  	switch(l)
	  	  {
	  	  	case 'w':if (x-_3>0&&mm[x-_3][y]!=1) x-=_3,_3=1;break;
	  	  	case 's':if (x+_3<=40&&mm[x+_3][y]!=1)x+=_3,_3=1;break;
	  	  	case 'a':if (y-_3>0&&mm[x][y-_3]!=1)y-=_3,_3=1;break;
	  	  	case 'd':if (y+_3<=100&&mm[x][y+_3]!=1)y+=_3,_3=1;break;
	  	  	case 'q':
	  	  	  {
				if (zd)
	  	  	  		  {
	  	  	  		  	for(i=x-1;i<=x+1;i++)
	  	  	  		  	  for(j=y-1;j<=y+1;j++)
	  	  	  		  	    if (mm[i][j]==1||mm[i][j]==3)
	  	  	  		  	      {
	  	  	  		  	        mm[i][j]=0;
	  	  	  		  	        cout<<" ";
	  	  	  		  	        gotoxy(i,j);
	  	  	  		  	      }
	  	  	  		  	zd--;
					  }
					break;
			  }
			case 'v':if (sy) sy--,_3=3;break;
			case 'e':if (things[193]-things[194]-things[196]>=50)hdcj(3);Getmap();cls();return;
		  }
		switch(mm[x][y])
		  {
		  	case 2:
		  		{
		  			int c,d;
		  			c=rand()%3+4;
		  			d=rand()%15+5;
		  			++things[194]; 
		  			printf("恭喜你找到了宝藏！获得：%s*%d",fsn[c].c_str(),d);
		  			fost[c]+=d;
		  			c=rand()%10000+1000;
		  			d=rand()%8000+500;
		  			cout<<' '<<"XP*"<<c<<" money*"<<d;
		  			things[1]+=c;
		  			things[7]+=d;
		  			gotmoney+=d;
		  			find=false;
		  			things[203]=1;
		  			break;
				}
			case 3:
				{
					happened+=(name+"在探索神殿时踩中陷阱/");
					++things[196];
					Die();
					return;
				}
		  }
	}
	gs();
	Getmap();
}
void Divinity()
{
	tepan();
	things[8]-=5;
	use(76);
	int a,b;
	int i,j,k;
	int n,m;
	int x=1,y=1;
	Getmap();
	while(1)
	  {
	  	gotoxy(x,y);
		cout<<"o";
	  	char l=_getch();
	  	if (l=='w'||l=='s'||l=='a'||l=='d')
	  	  {
	  	    gotoxy(x,y);
	  	    cout<<" "; 
	  	  }
	  	switch(l)
	  	  {
	  	  	case 'w':if (x>1&&dm[x-1][y]!=1) x--;break;
	  	  	case 's':if (x<44&&dm[x+1][y]!=1)x++;break;
	  	  	case 'a':if (y>1&&dm[x][y-1]!=1)y--;break;
	  	  	case 'd':if (y<110&&dm[x][y+1]!=1)y++;break;
		  }
		switch(dm[x][y])
		  {
		  	case 2:if ((MessageBox(NULL,TEXT("确定返回主世界吗？"),TEXT("传送NPC"),MB_YESNO)==IDYES))return;break;
		  	case 4:if ((MessageBox(NULL,TEXT("确定前往星墓吗？"),TEXT("传送NPC"),MB_YESNO)==IDYES))hole();Getmap();break;
		  	case 5:if ((MessageBox(NULL,TEXT("是否获取帮助？"),TEXT("HELP"),MB_YESNO)==IDYES))help();Getmap();break;
		  }
	  }
}
void Getmap()
{
	use(77);
	gotoxy(0,0);
	int i,j;
	for(i=0;i<44;i++)
	  {
	  	for(j=0;j<110;j++)
	  	  {
	  		printf("%c",ch[dm[i][j]]);
	  	  }
	  	printf("\n");
	  }
}
int WAR()
{
	tepan();
	things[8]-=5;
	use(78);
	int mh=things[5]*random(16,30),ma=things[5],mc=things[6];
	int sah=0,aa=things[9]*random(2,4),ac=things[9]*random(1,2),bn=0;
	int time=0,sh;
	int x,y,x1,y1;
	x=1,y=1;
	x1=1,y1=5;
	int cs=0;
	int ae=0,aad=0;
	while(mh>0&&time<=90)
	  {
	  	cls(); 
	  	int X=aa,Y=ac;
	  	aa*=(1+bn*5);
	  	ac*=(1+bn*3);
	  	cs++;
	  	gotoxy(0,0);
	  	cout<<"伤害："<<sah<<"\t狂暴层数："<<bn<<"\t剩余时间："<<90-time<<"s\t剩余血量："<<mh<<"AIENERGY:"<<ae<<"\n";
	  	cout<<"＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝\n";
	  	char l='l';
	  	if (kbhit())
	  	  l=getch();
	  	gotoxy(x,y);
	  	cout<<"♀";
	  	gotoxy(x1,y1);
	  	cout<<"♀";
	  	switch(l)
	  	  {
	  	  	case 'w':if (x>2)x--;break;
	  	  	case 'a':if (y>2)y--;break;
	  	  	case 's':if (x<40)x++;break;
	  	  	case 'd':if (y<80)y++;break;
			case ' ':
			if (x-x1<=5&&x1-x<=5&&y-y1<=5&&y1-y<=5) 
			  {
			  	sh=ma-ac;
			  	gotoxy(x1-2,y1);
			  	cout<<'-'<<sh;
			  	sah+=sh;
			  	gotoxy(x-1,y);
			  	cout<<'+'<<sh*0.2;
			  	sh*=0.2;
			  	mh+=sh;
			  	int dc=random(15,32);
				ae+=dc,aad+=dc;
			  }
			}
		if (rand()%2)
		x1+=(x>x1);
		else
		y1+=(y>y1);
		if (rand()%2)
		{
			if (x-x1<=5&&x1-x<=5&&y-y1<=5&&y1-y<=5) 
			  {
			  	sh=aa-mc;
			  	gotoxy(x-2,y);
			  	cout<<'-'<<sh;
			  	mh-=sh;
			  }
		}
		if (sah/10000>bn)
		  bn++;
		if (ae>=1000)
		  {
		  	gotoxy(40,35);
		  	cout<<"湮灭枷锁";
		  	sh=aa*2;
		  	float ls=random(30,70)/100.0;
		  	if (aad<300)
		  	sh*=(1+ls);
		  	else
		  	sh*=(1+ls*5);
		  	ae*=(1-ls);
		  	gotoxy(x-2,y);
		  	cout<<'-'<<sh;
		  	Sleep(500);
		  	mh-=sh;
		  	ae=0;
		  }
		if (cs%10==0)
		  {
		  	time++;
		  	if (time%8==0)
		  	  {
		  	  	gotoxy(40,35);
		  	  	cout<<"黑域之旅";
		  	  	gotoxy(x-1,y-2);
		  	 // 	color(3);
		  	  	cout<<"（）";
				gotoxy(x,y);
				cout<<"  "; 
			//	color(4);
				Sleep(1000);
				x=random(x-4,x+4);
				y=random(y-4,y+4);
				gotoxy(x,y);
				cout<<"♀";
				sh=aa*2;
				if (aad>=1000)
				  sh*=1.5;
				gotoxy(x-2,y);
				cout<<'-'<<sh;
				mh-=sh; 
			//	color(4);
			  }
			if (time%10==0)
			  {
			  	gotoxy(40,35);
			  	cout<<"异界怒雷";
			  	gotoxy(x-5,y-2);
			  	cout<<"（）";
			  	gotoxy(x-4,y);
			  	cout<<"｜";
			  	gotoxy(x-3,y);
			  	cout<<"｜";
			  	gotoxy(x-2,y);
			  	cout<<"｜";
			  	gotoxy(x-1,y);
			  	cout<<"｜";
			  	gotoxy(x,y);
			  	cout<<"｜";
			  	gotoxy(x+1,y);
			  	cout<<"｜";
			  	gotoxy(x+2,y);
			  	cout<<"｜";
			  	gotoxy(x+3,y);
			  	cout<<"｜";
			  	gotoxy(x+4,y);
			  	cout<<"｜";
			  	gotoxy(x+5,y-2);
			  	cout<<"（）";
			  	gotoxy(x,y-7);
			  	cout<<"（）";
			  	gotoxy(x,y-2);
			  	cout<<"－";
			  	gotoxy(x,y-1);
			  	cout<<"－";
			  	gotoxy(x,y);
			  	cout<<"－";
			  	gotoxy(x,y+1);
			  	cout<<"－";
			  	gotoxy(x,y+2);
			  	cout<<"－";
			  	gotoxy(x,y+3);
			  	cout<<"（）";
			  	sh=aa*2.4;
			  	Sleep(450);
			  	gotoxy(x-2,y);
			  	cout<<"-"<<sh;
			  	if (aad>=2000)
			  	  ma*=0.96;
			  	mh-=sh;
			  }
		  }
		aa=X,ac=Y;
	  }
	return sah;
}
void hole()
{
	use(79);
	cls();
	cout<<"星墓守门人技能(根据伤害发放奖励)\n";
	cout<<"湮灭枷锁：用湮灭能量对敌人造成200%攻击伤害并损失30~70%能量，自身每损失1%能量，伤害提高1%\n";
	cout<<"黑域之旅：打开亚空间之门将敌人传送至星墓，一秒后从空中落下造成160%攻击伤害并短暂眩晕\n";
	cout<<"异界怒雷：从多道亚空间之门中召唤怒雷，造成220%攻击水平伤害\n";
	cout<<"邪神之眼：当能量累计恢复300/1000/2000时睁开一只邪神之眼，第一只眼使“湮灭枷锁”的伤害提高改为5%，第二只眼使“黑域之旅”的伤害提高50%，第三只眼使被“异界怒雷”命中的敌人降低4%攻击\n\n";
	cout<<"狂暴：每受到一定伤害，叠加一层能力效果\n";
	cout<<"复制之躯：开场时自身的血量无限，等级同敌人一样\n";
	cout<<"异界控制：敌人的技能全部无效（吸血鬼之牙除外）\n\n\n";
	cout<<"你：吸血鬼之牙：吸血+20%\n";
	gs();
	long long n=WAR();
	int money=n*0.008;
	int XP=n*0.009;
	int kw=n*0.0001,kW=random(4,6);
	cout<<"获得："<<fsn[kW]<<'*'<<kw<<' '<<"钱*"<<money<<" 经验*"<<XP;
	Sleep(3000);
	things[7]+=money,gotmoney+=money,things[1]+=XP; 
	fost[kW]+=kw;
	gs();
	Getmap();
	return;
}
void help()
{
	use(80);
	cls(); 
	cout<<"wasd移动（你是'o'），以下为各种符号代表的东西\n";
	cout<<"# 墙，不可以通过\n";
	cout<<"B 返回点\n";
	cout<<"F 出生点\n";
	cout<<"S 星墓\n";
	cout<<"H 帮助\n";
	gs();
	Getmap();
}
void delp()
{
	use(81);
	cls(); 
	cout<<"wasd移动（你是'o'），以下为各种符号代表的东西\n";
	cout<<"# 墙，不可以通过\n";
	cout<<"B 返回点\n";
	cout<<"F 出生点\n";
	cout<<"S 神殿\n";
	cout<<"R 登山跑酷\n";
	cout<<"H 帮助\n";
	cout<<"s 神秘\n";
	gs();
	Getmap();
}
void Hell()
{
	tepan();
	things[8]-=5;
	use(82);
	int a,b;
	int i,j,k;
	int n,m;
	int x=1,y=1;
	Getmap();
	while(1)
	  {
	  	gotoxy(x,y);
		cout<<"o";
	  	char l=_getch();
	  	if (l=='w'||l=='s'||l=='a'||l=='d')
	  	  {
	  	    gotoxy(x,y);
	  	    cout<<" "; 
	  	  }
	  	switch(l)
	  	  {
	  	  	case 'w':if (x>1&&dm[x-1][y]!=1) x--;break;
	  	  	case 's':if (x<44&&dm[x+1][y]!=1)x++;break;
	  	  	case 'a':if (y>1&&dm[x][y-1]!=1)y--;break;
	  	  	case 'd':if (y<110&&dm[x][y+1]!=1)y++;break;
		  }
		switch(dm[x][y])
		  {
		  	case 2:if ((MessageBox(NULL,TEXT("确定返回主世界吗？"),TEXT("传送NPC"),MB_YESNO)==IDYES))return;break;
		  	case 4:if ((MessageBox(NULL,TEXT("确定前往神殿吗？"),TEXT("传送NPC"),MB_YESNO)==IDYES))SD();Getmap();break;
		  	case 5:if ((MessageBox(NULL,TEXT("是否获取帮助？"),TEXT("HELP"),MB_YESNO)==IDYES))help();Getmap();break;
		  	case 6:if ((MessageBox(NULL,TEXT("确定前往登山跑酷吗？"),TEXT("传送NPC"),MB_YESNO)==IDYES))run();Getmap();break;
		  	case 7:if ((MessageBox(NULL,TEXT("确定前往    吗？"),TEXT("传送ＮＰＣ"),MB_YESNO)==IDYES)&&things[10]>=100&&things[201]==1&&things[202]==1&&things[203]==1)things[0]=7;things[213]=1,things[220]=1;tepan();return;
		  }
	  }
}
bool dalie()
{
	tepan();
	    things[8]-=5;
	use(51);
	cls();
	int n,i,j,k,m=6;
	int x=25,y=25,x1=5,y1=5;
	while(1)
	{
		cout<<"按k键射击，wasd控制\n";
		cout<<"你还有"<<m<<"发子弹\n";
		char l=' ';
		if (kbhit())
		  l=getch();
		switch(l)
		  {
		  	case 'w':x-=random(2,5);break;
		  	case 's':x+=random(2,5);break;
		  	case 'a':y-=random(2,5);break;
		  	case 'd':y+=random(2,5);break;
		  	case 'k':m--;if (x==x1&&y==y1||x-2<=x1&&y1==y||x+2>=x1&&y==y)return 1;
		  	default:break;
		  }
		if (m<=0)
		  return 0;
		srand(time(0));
		if (m!=3||(m==3&&rand()%10==7))
		n=rand()%4+1;
		  	switch(n)
		  	  {
		  	  	case 1:x1-=random(1,3);break;
		  	  	case 2:x1+=random(2,4);break;
		  	  	case 3:y1-=random(1,3);break;
		  	  	case 4:y1+=random(2,4);break;
				}
		gotoxy(x,y-3);
		cout<<"-- ·--";
		gotoxy(x-1,y);
		cout<<"|";
		gotoxy(x-2,y);
		cout<<"|";
		gotoxy(x+1,y);
		cout<<"|";
		gotoxy(x+2,y);
		cout<<"|";
		gotoxy(x1-1,y1);
		cout<<"---";
		gotoxy(x1,y1);
		cout<<"| |";
		gotoxy(x1+1,y1);
		cout<<"---";
		if (x>40)
		  x=40;
		if (y>50)
		  y=50;
		if (x1>40)
		  x1=40;
		if (y1>40)
		  y1=40;
		if (x<5)
		  x=5;
		if (y<5)
		  y=5;
		if (x1<5)
		  x1=5;
		if (y1<5)
		  y1=5;
	//	Sleep(20);
		cls();
	}
	return 1;
}
const int map[][3][3]=
					{
					  {
					  	1,1,1,
					  	1,1,1,
						1,1,1,
					  },
					  {
					  	0,-1,-1,
					  	-1,-1,-1,
					  	-1,-1,-1,
					  },
					  {
					  	1,-1,-1,
					  	1,-1,-1,
					  	-1,-1,-1,
					  },
					  {
					  	-2,-2,-2,
					  	-2,-2,-2,
					  	-2,-2,-2,
					  },
					  {
						24,-1,-1,
						-1,-1,-1,
						-1,-1,-1,
					  },
					  {
					  	25,-1,-1,
						-1,-1,-1,
						-1,-1,-1,
					  },
					  {
					  	26,-1,-1,
						-1,-1,-1,
						-1,-1,-1,
					  },
					  {
					  	1,1,1,
					  	-1,2,-1,
					  	-1,2,-1,
					  },
					  {
					  	3,3,3,
					  	-1,2,-1,
					  	-1,2,-1,
					  },
					  {
					  	4,4,4,
					  	-1,2,-1,
					  	-1,2,-1,
					  },
					  {
					  	5,5,5,
					  	-1,2,-1,
					  	-1,2,-1,
					  },
					  {
					  	6,6,6,
					  	-1,2,-1,
					  	-1,2,-1,
					  },
					  {
					  	-1,1,-1,
					  	-1,1,-1,
					  	-1,2,-1,
					  },
					  {
					  	-1,3,-1,
					  	-1,3,-1,
					  	-1,2,-1,
					  },
					  {
					  	-1,4,-1,
					  	-1,4,-1,
					  	-1,2,-1,
					  },
					  {
					  	-1,5,-1,
					  	-1,5,-1,
					  	-1,2,-1,
					  },
					  {
					  	-1,6,-1,
					  	-1,6,-1,
					  	-1,2,-1,
					  },
					  {
					  	1,1,-1,
					  	1,2,-1,
					  	-1,2,-1,
					  },
					  {
					  	3,3,-1,
					  	3,2,-1,
					  	-1,2,-1,
					  },
					  {
					  	4,4,-1,
					  	4,2,-1,
					  	-1,2,-1,
					  },
					  {
					  	5,5,-1,
					  	5,2,-1,
					  	-1,2,-1,
					  },
					  {
					  	6,6,-1,
					  	6,2,-1,
					  	-1,2,-1,
					  },
					  {
						23,26,23,
						26,23,26,
						23,26,23,
					  },
					  {
					  	-2,-1,-1,
					  	-1,-1,-1,
					  	-1,-1,-1, 
					  },
					  {
					  	4,4,4,
					  	4,4,4,
					  	4,4,4,
					  },
					  {
					  	5,5,5,
					  	5,5,5,
					  	5,5,5,
					  },
					  {
					  	6,6,6,
					  	6,6,6,
					  	6,6,6,
					  },
					  {
					  	4,4,4,
					  	4,-1,4,
					  	-1,-1,-1,
					  },
					  {
					  	4,-1,4,
					  	4,4,4,
					  	4,4,4,
					  },
					  {
					  	4,4,4,
					  	4,-1,4,
					  	4,-1,4,
					  },
					  {
					  	-1,-1,-1,
					  	4,-1,4,
					  	4,-1,4,
					  },
					  {
					  	5,5,5,
					  	5,-1,5,
					  	-1,-1,-1,
					  },
					  {
					  	5,-1,5,
					  	5,5,5,
					  	5,5,5,
					  },
					  {
					  	5,5,5,
					  	5,-1,5,
					  	5,-1,5,
					  },
					  {
					  	-1,-1,-1,
					  	5,-1,5,
					  	5,-1,5,
					  },
					  {
					  	6,6,6,
					  	6,-1,6,
					  	-1,-1,-1,
					  },
					  {
					  	6,-1,6,
					  	6,6,6,
					  	6,6,6,
					  },
					  {
					  	6,6,6,
					  	6,-1,6,
					  	6,-1,6,
					  },
					  {
					  	-1,-1,-1,
					  	6,-1,6,
					  	6,-1,6,
					  },
					  {
					  	25,25,25,
					  	25,-1,25,
					  	-1,-1,-1,
					  },
					  {
					  	24,-1,24,
					  	24,24,24,
					  	24,24,24,
					  },
					  {
					  	24,24,24,
					  	24,-1,24,
					  	24,-1,24,
					  },
					  {
					  	-1,-1,-1,
					  	26,-1,26,
					  	26,-1,26,
					  },
					  {
					  	-1,26,-1,
					  	-1,25,-1,
					  	-1,2,-1,
					  },
					  {
					  	24,25,26,
					  	-1,2,-1,
					  	-1,2,-1,
					  },
					  {
					  	26,25,-1,
					  	24,2,-1,
					  	-1,2,-1,
					  },
					  {
					  	31,31,31,
					  	31,-1,31,
					  	-1,-1,-1,
					  },
					  {
					  	28,-1,28,
					  	28,28,28,
					  	28,28,28,
					  },
					  {
					  	29,29,29,
					  	29,-1,29,
					  	29,-1,29,
					  },
					  {
					  	-1,-1,-1,
					  	38,-1,38,
					  	38,-1,38,
					  },
					  {
					  	-1,43,-1,
					  	-1,43,-1,
					  	-1,2,-1,
					  },
					  {
					  	44,44,44,
					  	-1,2,-1,
					  	-1,2,-1,
					  },
					  {
					  	45,45,-1,
					  	45,2,-1,
					  	-1,2,-1,
					  },
					  {
					  	-1,56,-1,
					  	26,55,26,
					  	-1,54,-1,
					  },
					  {
					  	3,3,3,
					  	3,3,3,
					  	3,3,3,
					  },
					  {
					  	24,24,24,
					  	26,56,26,
					  	56,54,56,
					  },
					  {
						-1,-1,-1,
						6,6,4,
						-1,-1,-1,
					  },
};
void forest()
{
	hdcj(31);
	srand(time(0));
	const string where[]=
	{"打猎","砍树","工作台","探索","查看合成表","离开","附魔","森林背包","查看当前附魔属性","看看森林中各物品说明"};
	int i,j,k,n,m;
	char l;
	while(1)
	  {
	  	for(i=0;i<1000;i++)
	  	  if (kbhit())
	  	    l=getch();//垃圾收集器 
	  	things[8]-=5;
	  	tepan();
	  	cls();
	  	printf("树林茂密的森林中，不时传来的尖叫声给人一种不安的气氛\n");
	  	for(i=0;i<10;i++)
	  	  printf("%d.%s\n",i,where[i].c_str());
	  	cout<<"` （ESC下面）神秘人\n";
	  	if (things[188]==1)
	      l=choose(6)+'0';
	    else
	  	  l=_getch();
	  	switch(l)
	  	  {
	  	  	case '0':
	  	  		{
	  	  		cls();
	  	  		if (rand()%4==1)
	  	  		  {
	  	  		  	cout<<"运气不巧，什么都没碰到";
	  	  		  	gs();
	  	  		  	break;
					  }
				cout<<"你遇到了一只野";
				string animal[6]={"","牛","羊","猪","鸡","兔"};
				srand(time(0));
				n=random(1,5);
				cout<<animal[n];
				gs();
				if (dalie())
				  {
				  	happened+=(name+"在小森林打猎，收获猎物一只/");
				  if (n==1)
				    hdcj(39);
				  things[81]++;
				  if (things[81]>=20)
				    hdcj(44);
				  cout<<"打中了！";
				  cout<<"卖了";
				  n=random(800,8000);
				  cout<<n;
				  cout<<"元";
				  things[7]+=n;
				  gotmoney+=n;
				  gs();
				  }
				else
				  {
				  	things[84]=0;
				  	happened+=(name+"打猎时手滑走火导致猎物逃走/");
				  	cout<<"没打中！";
				  	gs();
				  }break;
			}
			case '1':
				{
					use(52);
					gs();
					hdcj(20);
					Sout("你费力地挥舞着斧头，树木吱吱的发出不祥的叫声。");
					happened+=(name+"在森林乱砍乱伐/");
					gs();
					for(i=1;i<=random(4,7);i++)
					  {
					  	m=60000;
					  	n=0;
					  	n+=fost[17]*1593;
					  	n+=fost[18]*3983;
					  	n+=fost[19]*6927;
					  	n+=fost[20]*6281;
					  	n+=fost[21]*12817;
					  	n+=fost[45]*18693;
					  	n+=fost[53]*23100;
					  	n*=random(1,has_fumo[1][1]+1);
					  	m-=n;
					  	jdt(float(m/10000.0));
					  	n=random(2,4);
					  	n*=random(1,has_fumo[2][4]+1);
					  	cout<<"原木*"<<n;
					  	fost[0]+=n;
					  }
					break;
				}
			case '2':
				{
					use(53);
					gs();
					cout<<"______________________________\n";
					cout<<"|         |         |         |\n";
					cout<<"|         |         |         |\n";
					cout<<"|_________|_________|_________|\n";
					cout<<"|         |         |         |\n";
					cout<<"|         |         |         |\n";
					cout<<"|_________|_________|_________|\n";
					cout<<"|         |         |         |\n";
					cout<<"|         |         |         |\n";
					cout<<"|_________|_________|_________|\n";
					cout<<"输入你有的东西的编号，放进对应的格子";
					int f[3][3];
					int grid[3][3][2]=
					{
						{
							2,2,
							2,14,
							2,26,
						},
						{
							5,2,
							5,14,
							5,26,
						},
						{
							8,2,
							8,14,
							8,26,
						},
					};
					  for(i=0;i<3;i++)
					    for(j=0;j<3;j++)
					      {
					      	gotoxy(16,3);
					      	cout<<"第"<<i*3+j+1<<"格放什么？输入编号（什么都不放输入-1）           \n";
					      	int g=0;
					      	for(k=0;k<=56;k++)
					      	  if (fost[k])
					      	    {
					      	      printf("%d.%s * %d\t",k,fsn[k].c_str(),fost[k]);
					      	      if ((++g)%3==0)
					      	        printf("\n");
					      	    }
					      	cin>>f[i][j];
					      	gotoxy(grid[i][j][0],grid[i][j][1]);
					      	if (f[i][j]==-1)
					      	  cout<<"空";
					      	else
					      	  cout<<fsn[f[i][j]];
						  }
					  cls();
					  n=-1;
					  for(i=0;i<=56;i++)
					    {
					    	bool flag=true;
					    	for(j=0;j<3;j++)
					    	  for(k=0;k<3;k++)
					    	    if (f[j][k]!=map[i][j][k])
					    	      flag=false;
					    	if (flag)
					    	  {
					    	  	n=i;
					    	  	break;
							  }
						}
					  if (n==-1)
						{
							cout<<"不存在该合成表！";
							gs();
							break;
						}
					cout<<"做几个 "<<fsn[n]<<" ？";
					int l1;
					cin>>l1;
					int getn[201];
					memset(getn,0,sizeof(getn));
					for(i=0;i<200;i++)
					  getn[i]=fost[i]; 
					bool can=true;
					for(i=0;i<3;i++)
					  for(j=0;j<3;j++)
					    if (map[n][i][j]>=0)
					    if (getn[map[n][i][j]]<l1)
					      {
					      	can=false;
					      	break;
						  }
						else
						  getn[map[n][i][j]]-=l1;
					cout<<can<<endl;
					if (can==0)
					  {
					  	cout<<"材料不足!，缺少"<<i<<','<<j<<'\n';
					  	gs();
						break; 
					  }
					  for(i=0;i<3;i++)
					    for(j=0;j<3;j++)
					      {
					      	if (map[n][i][j]!=-1)
					      	{
					      	  fost[map[n][i][j]]-=l1;
					        }
						  }
					if (i!=500&&j!=600)
					{
					cout<<"获得："<<fsn[n]<<'*'<<l1;
					if (n==9)
					  hdcj(13);
					if (n==14)
					  hdcj(19);
					if (n==11)
					  hdcj(21);
					if (n==12)
					  things[5]+=l1;
					if (n==13)
					  things[5]+=2*l1;
					if (n==14)
					  things[5]+=3*l1;
					if (n==15)
					  things[5]+=5*l1;
					if (n==22)
					  things[5]+=17*l1;
					happened+=(name+"合成了"+fsn[n]+"/");
					if (i<=5&&j<=5)
					  fost[n]+=l1;
					if (n==1)
					  fost[n]+=3*l1;
					if (n==2)
					  fost[n]+=3*l1;
					if (n==4)
					  fost[n]+=8*l1;
					if (n==5)
					  fost[n]+=8*l1;
					if (n==6)
					  fost[n]+=8*l1;
					if (n>=35&&n<=38)
					  {
					  	bool diamond=true;
					  	for(int ji=35;ji<=38;ji++)
					  	  if (fost[ji]<=0)
					  	    diamond=false;
					  	if (diamond)
					  	  hdcj(23);
					  }
					if (n>=39&&n<=42)
					  {
					  	bool diamond=true;
					  	for(int ji=39;ji<=42;ji++)
					  	  if (fost[ji]<=0)
					  	    diamond=false;
					  	if (diamond)
					  	  hdcj(24);
					  }
					if (n>=46&&n<=49)
					  {
					  	bool diamond=true;
					  	for(int ji=46;ji<=49;ji++)
					  	  if (fost[ji]<=0)
					  	    diamond=false;
					  	if (diamond)
					  	  hdcj(25);
					  }
					/*iron golden diamond hero sky
				head   4    3         6		9	15
				clothes 6    4        8		14	23
				tussle  5    4        7		12	19
				shoes	3    2        5 	8	13
					*/
					if (n==27)
					  things[6]+=4;
					if (n==28)
					  things[6]+=6;
					if (n==29)
					  things[6]+=5;
					if (n==30)
					  things[6]+=3;
					if (n==31)
					  things[6]+=3;
					if (n==32)
					  things[6]+=4;
					if (n==33)
					  things[6]+=4;
					if (n==34)
					  things[6]+=2;
					if (n==35)
					  things[6]+=6;
					if (n==36)
					  things[6]+=8;
					if (n==37)
					  things[6]+=7;
					if (n==38)
					  things[6]+=5;
					if (n==39)
					  things[6]+=9;
					if (n==40)
					  things[6]+=14;
					if (n==41)
					  things[6]+=12;
					if (n==42)
					  things[6]+=8;
					if (n==43)
					  things[5]+=16;
					if (n==46)
					  things[6]+=15;
					if (n==47)
					  things[6]+=23;
					if (n==48)
					  things[6]+=19;
					if (n==49)
					  things[6]+=13;
					if (n==50)
					  things[5]+=35;
					if (n==53)
					  {
					    things[5]+=46;
					    hdcj(27);
					  }
					}
					break;
					}
					case '3':
						{
							/*	string fumoname[4][5]=
{
	{"耐久","锋利","抢夺","雷电之力","落雷术"},
	{"耐久","效率","洪荒之力","木之克星","时运"},
	{"耐久","效率","急迫","精准采集","时运"}
	{"耐久","保护","血量提升","荆棘","雷电附身"},
}; */
							n=random(1,6);
							if (things[187]==2&&rand()%3<=1)
							  n=7;
							cls();
							switch(n)
							  {
							  	case 1:
							  		{
							  			use(54);
							  			Sout("你遇到了一只僵尸！");
							  			m=random(things[9]-10,things[9]+15);
							  			int hp,attack,run;
							  			hp=m*(random(17,29));
							  			attack=m*(random(4,13));
							  			run=m;
							  			while(1)
							  			{
							  			  cls();
							  			  cout<<"Your hp:"<<things[2]<<'\n';
							  			  cout<<"JS's hp:"<<hp<<'\n';
							  			  cout<<"1.attack 2.run away\n";
							  			  char l=_getch();
							  			  cout<<l;
							  			  if (l=='2')
							  			    {
							  			    	if (rand()%4==1)
							  			    	  {
							  			    	  	cout<<"逃跑成功，运气不错！";
							  			    	  	break;
													}
												else
												  cout<<"逃跑失败！\n";
											  }
										  else
										  {
										  if (fost[22]==0&&fost[43]==0&&fost[50]==0&&fost[53]==0)
										  {
							  			  n=gongji(things[5]);
							  			  gotoxy(12,0);
							  			  n-=run;
							  			  Sout("你发动了攻击,僵尸受到了");
							  			  }
							  			else
										  {
										  if (fost[22]>=1)
										    {cout<<"你发动了技能【火炮轰炸】\n";n=1.2*things[5];}
										  if (fost[43]>=1)//43,50,53
										    {cout<<"你发动了技能【横扫】\n";n+=1.1*things[5];}
										  if (fost[50]>=1)
										    {cout<<"你发动了技能【坠入虚空】\n";n+=hp*0.5;}
										  if (fost[53]>=1)
										    {cout<<"你发动了技能【量子充能】\n";n+=0.4*things[2];}
										  }
										if (has_fumo[3][4])
										  if (rand()%(70/(70/has_fumo[3][4])))
										    cout<<"你发动了技能【雷电之力】\n",n+=has_fumo[3][4]*0.01*things[2];
							  			Sout("造成了");
							  			  cout<<n;
							  			  Sout("点伤害\n");
							  			  hp-=n;
							  			  }
							  			  Sout("僵尸发动了攻击，你受到了");
							  			  n=attack*0.87-things[6];
							  			  if (n<1)
							  			    n=1;
							  			  cout<<n;
							  			  Sout("点伤害\n");
							  			  Sout("反伤：");
							  			  m=0;
							  			  if (has_fumo[3][3])
							  			    m=n*(has_fumo[3][3])*0.03;
							  			  cout<<m<<"点\n";
							  			  things[2]-=n;
							  			  hp-=m;
							  			  if (things[2]<=0)
							  			    {
							  			      happened+=(name+"被僵尸杀死了/");
							  			      Die();
							  			    }
							  			if (hp<=0)
							  			  {
							  			  	hdcj(22);
							  			  	break;
											}
							  			}
							  		  Sout("胜利！战利品：");
							  		  things[83]++;
							  		  if (fost[22]>=1)
										things[197]++;
									  if (things[197]>=166)
									    hdcj(6);
							  		  happened+=(name+"杀死了一只僵尸/");
							  		  n=random(2,4);
							  		  m=random(0,2);
							  		  cout<<fsn[m]<<"*"<<n;
							  		  n*=random(1,has_fumo[0][2]+1);
							  		  fost[m]+=n;
							  		  gs();
							  		  break;
									}
								case 2:
									{
										use(55);
										cls();
							  			Sout("你遇到了一只骷髅！");
							  			m=random(things[9]-10,things[9]+15);
							  			int hp,attack,run;
							  			hp=m*(random(7,23));
							  			attack=m*(random(5,8));
							  			run=m;
							  			while(1)
							  			{
							  			  cout<<"Your hp:"<<things[2]<<'\n';
							  			  cout<<"KL's hp:"<<hp<<'\n';
							  			  cout<<"1.attack 2.run away\n";
							  			  char l=_getch();
							  			  cout<<l;
							  			  if (l=='2')
							  			    {
							  			    	if (rand()%4==1)
							  			    	  {
							  			    	  	cout<<"逃跑成功，运气不错！";
							  			    	  	break;
													}
												else
												  cout<<"逃跑失败！\n";
											  }
										  else
										  {
							  			  n=gongji(things[5]);
							  			  gotoxy(12,0);
							  			  n-=run;
							  			  Sout("你发动了攻击,KL受到了");
							  			  cout<<n;
							  			  Sout("点伤害\n");
							  			  hp-=n;
							  			  }
							  			  Sout("骷髅发动了攻击，你受到了");
							  			  n=attack*0.87-things[6];
							  			  if (n<1)
							  			    n=1;
							  			  cout<<n;
							  			  Sout("点伤害\n");
							  			  Sout("反伤：");
							  			  m=0;
							  			  if (has_fumo[3][3])
							  			    m=n*(has_fumo[3][3])*0.03;
							  			  cout<<m<<"点\n";
							  			  things[2]-=n;
							  			  hp-=m;
							  			  if (things[2]<=0)
							  			    {
							  			      happened+=(name+"被骷髅杀死了/");
							  			      Die();
							  			    }
							  			if (hp<=0)
							  			  {
							  			  	hdcj(22);
							  			  	break;
							  			  }
							  			}
							  		  happened+=(name+"杀死了一只骷髅/");
							  		  Sout("胜利！战利品：");
							  		  things[83]++;
							  		  n=random(2,4);
							  		  m=random(0,2);
							  		  n*=random(1,has_fumo[0][2]+1);
							  		  cout<<fsn[m]<<"*"<<n;
							  		  fost[m]+=n;
							  		  gs();
							  		  break;
									}
								case 3:
								 {
								 	use(56);
							  			Sout("你遇到了一只爬行者！");
							  			m=random(things[9]-10,things[9]+15);
							  			int hp,attack,run;
							  			hp=m*(random(17,23));
							  			attack=m*(random(6,8));
							  			run=m;
							  			while(1)
							  			{
							  			  cls();
							  			  cout<<"Your hp:"<<things[2]<<'\n';
							  			  cout<<"PXZ's hp:"<<hp<<'\n';
							  			  cout<<"1.attack 2.run away\n";
							  			  char l=_getch();
							  			  if (l=='2')
							  			    {
							  			    	if (rand()%4==1)
							  			    	  {
							  			    	  	cout<<"逃跑成功，运气不错！";
							  			    	  	break;
													}
												else
												  cout<<"逃跑失败！\n";
											  }
										  if (fost[22]==0&&fost[43]==0&&fost[50]==0&&fost[53]==0)
										  {
							  			  n=gongji(things[5]);
							  			  gotoxy(12,0);
							  			  n-=run;
							  			  Sout("你发动了攻击,爬行者受到了");
							  			  cout<<n;
							  			  Sout("点伤害\n");
							  			  hp-=n;
							  			  }
							  			  Sout("爬行者自爆了，你受到了");
							  			  n=attack*1.4-things[6];
							  			  cout<<n;
							  			  Sout("点伤害") ;
							  			  things[2]-=n;
							  			  hp=0;
							  			  if (things[2]<=0)
							  			    {
							  			      happened+=(name+"被creeper炸飞了/");
							  			      Die();
							  			    }
							  			if (hp<=0)
							  			  break;
							  			}
							  		  Sout("胜利！战利品：");
							  		  n=random(2,5);
							  		  m=23;
							  		  n*=random(1,has_fumo[0][2]+1);
							  		  cout<<fsn[m]<<"*"<<n;
							  		  fost[23]+=n;
							  		  gs();
							  		  break;
									}
								  case 4:
								  	{
								  		use(57);
								  	  Sout("你找到了一个矿洞.");
								  	  Sout("\n是否挖矿？1.是 2.否");
								  	  char l=_getch();
								  	  if (l=='2')
								  	    break;
								  	  n=60000;
								  	  n-=fost[7]*2838;
								  	  n-=fost[8]*5092;
								  	  n-=fost[9]*7928;
								  	  n-=fost[10]*9203;
								  	  n-=fost[11]*13029;
								  	  n-=fost[44]*17832;
								  	  n-=fost[51]*30091;
								  	  n*=1-has_fumo[2][1]*0.04;
								  	  n*=1-has_fumo[2][2]*0.05;
								  	  if (n<10000)
								  	    n=10000;
								  	  for(i=1;i<=6;i++)
								  	  {
								  	  	m=random(3,6);
								  	  	if (has_fumo[2][3])
								  	  	  {
								  	  	  	cout<<"你想要什么？\n";
								  	  	  	cout<<"1.石头\n";
								  	  	  	cout<<"2.铁锭\n";
								  	  	  	cout<<"3.金锭\n";
								  	  	  	cout<<"4.钻石\n";
								  	  	  	int a;
								  	  	  	cin>>a;
								  	  	  	if (a>4)
								  	  	  	  a=random(1,4);
								  	  	  	m=a+2;
										  }
										if (m==6)
										  hdcj(12);
								  	    jdt(n/10000+(m-3));
								  	    k=random(1,3);
								  	    k*=random(1,has_fumo[2][4]+1);
								  	    fost[m]+=k;
								  	    cout<<fsn[m]<<'*'<<k;
								  	    happened+=(name+"在矿洞淘钻/");
								  	    gs();
								  	  }
								  	  break;
									}
									case 5:
										{
											use(58);
											srand(time(0));
											Sout("你遇到了一个废弃矿道");
											cout<<"是否探索？1.是 2.否 3.查看故事";
											char l=_getch();
											if (l=='3')
											  {
											  	cls();
											  	cout<<"    这是一条灵异矿道，以前的矿工常常在里面离奇失踪，\n";
											  	cout<<"数日后便会有几个影子在矿道里游荡。有人说这是矿工的亡\n";
											  	cout<<"魂，也有人说这是恶魔的影子。\n";
											  	cout<<"    唯一一个或者从矿道里走出来的是WYQ，他在下矿之前被\n";
											  	cout<<"MCYH施加了BUFF，所以没事。但是他亲口说自己看到了地上躺\n";
											  	cout<<"着无数没有生命的躯体，眼里冒着绿光。忽然他们全都站了起\n";
											  	cout<<"来向WYQ扑过来，但是他们看到MCYH的BUFF时立刻魂飞魄散了。\n";
											  	cout<<"    从此以后，只有游戏主宰者MCYH和好友WYQ能在矿道和地上\n";
												cout<<"世界中自由的穿梭，只有他能为地面上的人类带来矿道里丰富的宝藏。\n";
											  	cout<<"    所以，这位看故事的玩家，你敢进去吗？\n";
											  	cout<<"是否探索？1.是 2.否";
											  	l=_getch();
											  	if (l=='2'){
											  	  Sout("MCYH：胆小鬼，我编个故事吓吓你而已...");break;}
											  }
											n=rand()%4+1;
											switch(n)
											  {
											  	case 1:
											  	case 2:
											  	case 3:
											  		{
											  			Sout("你发现了一个箱子，是否打开？1.YES 2.NO");
											  			l=_getch();
											  			if (l=='2')
											  			  break;
											  			if (l=='1')
											  			  {
											  			  	srand(time(0));
											  			  	if (rand()%2)
											  			  	  {
											  			  	  	happened+=(name+"在废弃矿道找到了很多宝藏/");
											  			  	  	cout<<"你找到了一堆宝藏！\n";
											  			  	  	cout<<"获得:";
																n=random(3,6);
																m=random(3,5);
																cout<<fsn[n]<<'*'<<m;
																fost[n]+=m;
																cout<<"，";
																n=random(3,6);
																m=random(3,5);
																cout<<fsn[n]<<'*'<<m;
																fost[n]+=m;
																break; 
																  }
															{
							  			Sout("你遇到了一只游魂！");
							  			hdcj(14);
							  			m=random(things[9]-10,things[9]+15);
							  			int hp,attack,run;
							  			hp=m*(random(23,28));
							  			attack=m*(random(7,9));
							  			run=m;
							  			while(1)
							  			{
							  			  cls();
							  			  cout<<"Your hp:"<<things[2]<<'\n';
							  			  cout<<"YH's hp:"<<hp<<'\n';
							  			  cout<<"敌军等级："<<m<<"\n"; 
							  			  cout<<"1.attack 2.run away\n";
							  			  char l=_getch();
							  			  if (l=='2')
							  			    {
							  			    	if (rand()%2)
							  			    	  {
							  			    	  	cout<<"逃跑成功，运气不错！";
							  			    	  	break;
													}
												else
												  cout<<"逃跑失败！\n";
											  }
										  else
										  {
										  if (fost[22])
										    cout<<"你发动了技能【火炮轰炸】\n",n=1.2*things[5];
										  if (fost[43])//43,50,53
										    cout<<"你发动了技能【横扫】\n",n+=1.1*things[5];
										  if (fost[50])
										    cout<<"你发动了技能【坠入虚空】\n",n+=hp*0.5;
										  if (fost[53])
										    cout<<"你发动了技能【量子充能】\n",n+=0.4*things[2];
										if (fost[22]==0&&fost[43]==0&&fost[50]==0&&fost[53]==0){
							  			  n=gongji(things[5]);
							  			  n-=run;
							  			  Sout("你发动了攻击,游魂受到了");
							  			}
							  			  cout<<n;
							  			  Sout("点伤害\n");
							  			  hp-=n;
							  			  }
							  			  if (rand()%4)
							  			  {
							  			  Sout("游魂发动了攻击，你受到了");
							  			  n=attack*0.87-things[6];
							  			  if (n<1)
							  			    n=1;
							  			  cout<<n;
							  			  Sout("点伤害") ;
							  			  things[2]-=n;
							  			  }
							  			  else
							  			  {
							  			  	cout<<"游魂发动技能“灵魂威慑”，对你造成了"<<attack*1.5<<"点伤害\n";
							  			  	things[2]-=attack*1.5;
											}
							  			  if (things[2]<=0)
							  			    {
							  			      happened+=(name+"被游魂杀死了/");
							  			      Die();
							  			    }
							  			if (hp<=0)
							  			  break;
							  			cls();
							  			}
							  		  Sout("胜利！战利品：");
							  		  if (fost[22]>=1)
										things[197]++;
									  if (things[197]>=166)
									    hdcj(6);
							  		  things[83]++;
							  		  n=random(2,6);
							  		  m=random(0,6);
							  		  n*=random(1,has_fumo[0][2]+1);
							  		  cout<<fsn[m]<<"*"<<n;
							  		  fost[m]+=n;
							  		  gs();
							  		  break;
									}	
															}
													  }
									case 4:
										{
											if (rand()%2)
											{
												use(59);
											  cout<<"你遇到了MCYH！\n";
											  cout<<"1.attack 2.run away";
											  char l=_getch();
											  switch(l)
											    {
											    	case '2':break;
											    	default:
											    		{
											    		  Sout("\nMCYH：和作者打架。。。");
											    		  hdcj(15);
											    		  Sout("\nMCYH（拿起纳米剑）：来吧！准备好了没有？Y/N");
											    		  char g=_getch();
											    		  if (g!='Y'&&g!='y')
											    		  {
											    		    Sout("MCYH：胆小鬼！");break;
											    		  }
											    		  gs();
											    		  things[0]++;
											    		  return;
											    		  break;
											    		}
												}
											  break;
											}
											else
											{
												use(60);
												cout<<"你遇到了WYQ！\n";
												cout<<"1.attack 2.run away\n";
												char l=_getch();
												switch(l)
												{
													case '2':break;
													default:
														Sout("MCYH：竟敢和作者的好兄弟WYQ打架？！关机吧！！！");
														system("Shutdown -H");
														break;
												}
												break;
											}
										}
											  }
										break;
										}
									case 6:
										{
											use(61);
											cout<<"你遇到了SLS（索罗斯）！";
											int a,b,c,d=random(things[9]-3,things[9]+5);
											int huanying=0;
											a=d*(random(21,30));
							  				b=d*(random(6,11));
							  				c=d;
											gs();
											while(1)
											  {
											  	cls();
											  	Sout("YOUR HP:");
											  	cout<<things[2]<<'\n';
											  	Sout("SLS HP:");
											  	cout<<a<<'\n';
											  	Sout("SLS ATTACK:");
											  	cout<<b<<'\n';
											  	Sout("SLS DEFENCE:");
											  	cout<<c<<'\n';
											  	Sout("SLS XP:");
											  	cout<<d<<'\n';
											  	Sout("SLS幻影层数：");
											  	cout<<huanying<<'\n';
											  	cout<<"1.attack 2.run away\n";
											  	char l=_getch();
											  	if (l=='2')
											  	  {
											  	  	if (rand()%4==1)
											  	  	  {
											  	  	  	Sout("逃跑成功，运气不错");
											  	  	  	break;
													  }
													else
													  Sout("逃跑失败！\n");
												  }
												else
												  {
												  	if (fost[22])
										    		  cout<<"你发动了技能【火炮轰炸】\n",n=1.2*things[5];
										  			if (fost[43])//43,50,53
                                          										    		  cout<<"你发动了技能【横扫】\n",n+=1.1*things[5];
										  			if (fost[50])
										    		  cout<<"你发动了技能【坠入虚空】\n",n+=a*0.5;
										  			if (fost[53])
										    		  cout<<"你发动了技能【量子充能】\n",n+=0.4*things[2];
													if (fost[22]==0&&fost[43]==0&&fost[50]==0&&fost[53]==0){
							  			  			  n=gongji(things[5]);
							  			  			n-=c;
							  			  			Sout("你发动了攻击,SLS受到了");
							  						}
							  						else
							  						  cout<<"造成了";
							  						cout<<n<<"点伤害\n";
							  						a-=n;
												  }
												if (a<=0)
												  {
												  	cout<<"胜利！战利品：XP5000";
												  	int jiangli=random(0,56);
													cout<<" "<<fsn[jiangli];
													cout<<" *1";
													fost[jiangli]++; 
													things[83]++;
													if (fost[22]>=1)
													  things[197]++;
												  	gs();
												  	break;
												  }
												if (rand()%2)
												{
													n=float((random(6,9))/10)*b-things[6];
													Sout("索罗斯发动了攻击，你受到了");
													cout<<n;
													Sout("点伤害，索罗斯叠加了一层幻影\n");
													huanying++;
													things[2]-=n;
													if (things[197]>=166)
									    			  hdcj(6);
												}
												else
												{
													int jin=random(1,3);
													if (jin==1)
													  {
													  	Sout("索罗斯发动了技能【幻枪连击】，对你造成");
													  	n=1.6*b;
													  	cout<<n;
													  	Sout("点伤害\n");
													  	things[2]-=n;
													  }
													if (jin==2)
													  {
													  	Sout("索罗斯发动技能【结合】，将幻影层数清空，并且每失去一个幻影，自身恢复30点血量，增加4点攻击");
													  	a+=huanying*30;
													  	b+=huanying*4;
													  	huanying=0;
													  }
													if (jin==3)
													  {
													  	Sout("索罗斯发动技能【总攻击】，让所有幻影对敌人造成攻击（每个幻影拥有自身60%属性），对你造成了");
													  	n=a*0.6*huanying;
													  	cout<<n;
													  	Sout("点伤害，并失去2个幻影");
													  	huanying-=2;
													  	things[2]-=n;
													  }
												}
												if (things[2]<=0)
												  Die();
											  }
											break;
										  }
										case 7:
											{
												cls();
												int a=things[5]*0.6,b=things[6]*0.5;
												int c=things[9]*3,d=things[9],e=things[9]*11;
												Sout("你遇到了一只树妖（树妖特性：只能攻击，无法逃跑，你的攻击和防御大幅下降，无法用技能）\n");
												while(e>0&&things[2]>0)
												  {
												  	int A,B;
												  	A=gongji(a);
												  	A-=d;
												  	Sout("你发动了攻击，树妖受到了");
												  	cout<<A;
												  	e-=A;
												  	Sout("点伤害\n");
												  	B=c*0.875-b;
												  	Sout("树妖发动了攻击，你受到了");
												  	cout<<B;
												  	Sout("点伤害\n");
												  	things[2]-=B;
												  	if (things[2]<=0)
												  	  {
												  	  	happened+=(name+"被树妖杀死了");
												  	  	Die();
														}
												  	gs();
												  }
												cout<<"胜利！";
												happened+=(name+"杀死了一只树妖/");
							  		 			 Sout("胜利！战利品：");
							  		  			things[83]++;
							  		  			n=random(2,4);
							  		  			m=random(0,2);
							  		 			 n*=random(1,has_fumo[0][2]+1);
							  		 			 cout<<fsn[m]<<"*"<<n;
							  		  			fost[m]+=n;
											}
										}
									break;
							  }
					case '4':
						{
							cls();
							while(1)
							  {
							  	use(62);
							  	cls();
							  	cout<<"想查看什么的合成表？输入编号，输入-1退出\n";
							  	for(i=0;i<=56;i++)
							  	  {
							  	  	cout<<i<<" "<<fsn[i]<<'\n';
									}
								cin>>n;
								if (n==-1)
								  break;
								cls();
								for(i=0;i<3;i++)
								{
								  for(j=0;j<3;j++)
								    {
								    	if (map[n][i][j]==-2)
								    	{
								    	  cout<<"不可合成物";
								    	  gs();
								    	  i=10,j=10;
								    	  break;
								    	}
								    	if (map[n][i][j]==-1)
								    	  {
								    	  	cout<<"空";
										  }
										else
										  cout<<fsn[map[n][i][j]];
										cout<<' ';
									}
									cout<<endl;
								}
								gs();
							  }
							break;
						}
				case '5':return;
				case '6':
				{
					use(63);
					if (things[32]==0)
					  {
					  	cout<<"没有附魔台！\n";
					  	cout<<"获得方式:公园-->登山-->天空之境-->天空集市购买\n";
					  	gs();
					  	break;
					  }
					cls();
					cout<<"你要给哪个装备附魔？";
					cout<<"1.剑\n";
					cout<<"2.斧子\n";
					cout<<"3.镐子\n";
					cout<<"4.头盔\n";
					cout<<"5.胸甲\n";
					cout<<"6.护腿\n";
					cout<<"7.靴子\n"; 
					cin>>n;
					if (n>4)
					  n=4;
					i=n-1;
						srand(time(0));
						cout<<"\n\n";
						cout<<"你有"<<things[9]<<"级经验\n";
						cout<<"你有"<<things[33]<<"块附魔石\n";
						cout<<"你想附哪一种魔？（附魔等级上限：6级）\n";
						int a,b,c;
						a=rand()%5;
						cout<<"0.不附魔\n";
						cout<<"1.1级经验，1块附魔石："<<fumoname[i][a]<<has_fumo[i][a]+1<<"  经验等级限制：7"<<'\n';
						do
						  b=rand()%5;
						while(a==b);
						cout<<"2.2级经验，2块附魔石："<<fumoname[i][a]<<has_fumo[i][a]+1<<'+'<<fumoname[i][b]<<has_fumo[i][b]+1<<"  等级限制：15"<<'\n';
						do
						  c=rand()%5;
						while(c==a||c==b);
						cout<<"3.3级经验，3块附魔石："<<fumoname[i][a]<<has_fumo[i][a]+1<<'+'<<fumoname[i][b]<<'+'<<has_fumo[i][b]+1<<fumoname[i][c]<<has_fumo[i][c]+1<<"等级限制：30"<<'\n';
						cin>>m;
						int s[4]={0,7,15,30};
						if (m==0)
						  break;
						if (things[9]<s[m]||things[33]<m)
						  {
						  	cout<<"材料（经验或附魔石）不足！";
						  	gs();
						  	break;
						  }
						has_fumo[i][a]++;
						if (m>=2)
						  has_fumo[i][b]++;
						if (m>=3)
						  has_fumo[i][c]++;
						things[9]-=m;
						things[1]=sj[things[9]-1];
						things[33]-=m;
					/*	string fumoname[4][5]=
{
	{"耐久","锋利","抢夺","雷电之力","落雷术"},
	{"耐久","效率","洪荒之力","木之克星","时运"},
	{"耐久","效率","急迫","速率提升","时运"}
	{"耐久","保护","血量提升","荆棘","雷电附身"},
}; */
					if (i==0)
					  {
					  	if (a==1||b==1||c==1)
					  	  things[5]+=5;
					  }
					if (i==3)
					  {
					  	if (a==1||b==1||c==1)
					  	  things[6]+=2;
					  	if (a==2||b==2||c==2)
					  	  things[2]+=30;
					  }
					for(i=0;i<4;i++)
					  for(j=0;j<5;j++)
					    if (has_fumo[i][j]>6)
					      has_fumo[i][j]=6;
					break;
					  }
				case '7':
					{
						use(64);
						for(i=0;i<=56;i++)
						  if (fost[i])
						    printf("%s *%d  -%s\n",fsn[i].c_str(),fost[i],nn[leibie[i]].c_str());
						gs();
						break;
					}
				case '8':
					{
						use(65);
						string wupin[4]={"剑","斧头","镐子","盔甲"};
						cls();
						for(i=0;i<4;i++)
						  for(j=0;j<5;j++)
						    {
						    	printf("%s:【%s】%d级\n",wupin[i].c_str(),fumoname[i][j].c_str(),has_fumo[i][j]);
							}
						break;
					}
				case '9':
					{
						use(74);
						/*string fsn[200]=
	0       1       2      3        4      5        6
{"原木 ","木板 ","木棍 ","石头 ","铁锭 ","金锭 ","钻石 ",
   7       8       9           10   11
 "木镐 ","石镐 ","铁镐 ","金镐 ","钻石镐 ",
    12     13		14		15		16
 "木剑 ","石剑 ","铁剑 ","金剑 ","钻石剑 ",
	17		18		19		20		21
 "木斧 ","石斧 ","铁斧 ","金斧 ","钻石斧 ",
 	22		  23	 24		25		26
 "春节礼炮","火药","铁块","金块","钻石块",
 		27		28		29			30
 /*27"铁头盔","铁胸甲","铁护腿","铁靴子",
 	31		32			33		34
 "金头盔","金胸甲","金护腿","金靴子",
 	35			36			37		38
 "钻石头盔","钻石胸甲","钻石护腿","钻石靴子",
 		39			40			41			42		43		44		45
 /*39"英雄头盔","英雄战甲","英雄护腿","英雄战靴","英雄剑","英雄镐","英雄战斧",
 		46			47			48			49		50		51		52
 /*46"虚空头盔","虚空战甲","虚空护腿","虚空战靴","虚空剑","虚空镐","虚空斧",
 		53			54		55		56
 /*53"量子剑", "石头精华", "CPU","工业钻石" 
};*/
					/*iron golden diamond hero sky
				head   4    3         6		9	15
				clothes 6    4        8		14	23
				tussle  5    4        7		12	19
				shoes	3    2        5 	8	13*/ 
					string ab[200]=
					{
						"来自于一棵大树身上的木头","由一块原木分解后得到的东西，可以用于制作基础装备","装备的握把，由木板分解而成",
						"一块普通的石头，蕴含着不普通的能量，可以用于制造石器装备","矿洞里的一种普通矿石，很常见，可用于合成武器与防具",
						"矿洞里的一种普通矿石，很常见，可用于合成武器与防具","一种稀有矿石，可以通过挖矿或购买获得","普通的基础挖矿工具",
						"升级后的挖矿工具","一把挖矿利器，开采效率较高","挖矿能手，附魔时属性会更好哦","奢侈豪华的挖矿神器，速度超快",
						"普通的防身武器","升级后的防身武器","一把打怪利器","打怪能手，附魔时属性会更好哦","奢侈豪华的打怪神器，伤害很高",
						"普通的伐木工具","升级后的伐木工具","一把伐木利器","伐木能手，附魔时属性会更好哦","奢侈豪华的伐木神器，速度超快",
						"炸怪神器，伤害超高","PXZ的掉落物，用于合成春节礼炮","铁锭的块状，可以分解回铁锭，也可以合成英雄装备",
						"金锭的块状，可以分解回金锭，也可以合成英雄装备","钻石的块状，可以分解回钻石，也可以合成英雄装备",
						"铁制的头盔，增加4点防御","铁制的胸甲，增加6点防御","铁制的护腿，增加5点防御","铁制的靴子，增加3点防御",
						"金制的头盔，增加3点防御","金制的胸甲，增加4点防御","金制的护腿，增加4点防御","金制的靴子，增加2点防御",
						"钻石制的头盔，增加6点防御","钻石制的胸甲，增加8点防御","钻石制的护腿，增加7点防御","钻石制的靴子，增加5点防御",
						"金块合成的头盔，增加9点防御","铁块合成的胸甲，增加14点防御","铁块合成的护腿，增加12点防御","钻石块合成的靴子，增加8点防御",
						"英雄使用的宝剑","英雄采矿用的镐子","英雄手中的战斧",
						"金头盔压缩制成的头盔，增加15点防御，好像还有其它作用","铁胸甲压缩制成的胸甲，增加23点防御，好像还有其它作用",
						"铁护腿压缩制成的护腿，增加19点防御，好像还有其它作用","钻石靴子压缩制成的靴子，增加13点防御，好像还有其它作用",
						"虚空来客防身的剑","虚空来客采矿用的镐子","虚空来客手中的战斧",
						"用稀有材料制成的剑，114514年被科学家在MCYH留下的时间印记中发现","石头中能量的精华","14514年ACOPer.th13计算机的CPU，好像还有其他作用",
						"加工后的钻石，闪闪发光",
					};
					int i,j,k;
					char l;
					i=1;
					bool flag=true;
					while(flag)
						{
							cls();
							cout<<"a上一个 d下一个 e退出\n";
							cout<<"["<<fsn[i]<<"]\n";
							cout<<ab[i]<<"\n";
							l=_getch();
							switch(l)
							  {
							  	case 'a':if (i>1)i--;break;
							  	case 'd':if (i<56)i++;break;
							  	case 'e':flag=false;break;
							  }
						}
					break;
					} 
				case '`':
					{
						cls();
						if (things[9]<100)
						 {
						  Sout("神秘人：小伙子不错嘛，居然看得到我。啧啧，你的修行还不够呢，等你升到100级再来找我吧。");
						  gs();
						  break;
					     }
						Sout("神秘人：只要给我传送符，我马上就带你去另一个维度。\n");
						cout<<"1.传送至地狱 2.传送至神界 3.离开\n";
						char l=_getch();
						switch(l)
						  {
						  	case '1':
						  		{
						  			if (things[99])
						  			  {
						  			    things[98]=1;
						  			    things[99]--; 
						  			    Divinity();
						  			  }
						  			else
						  			  cout<<"传送符不足！";
									break;
								}
							case '2':
								{
									if (things[99])
									  {
									    things[98]=2;
									    things[99]--;
									    Hell(); 
									  }
									else
									  cout<<"传送符不足！";
									break;
								}
							case '3':break;
						  }
					}
			}
			if (things[83]>=50)
			  hdcj(48);
			gs();
	  }
}
void poem()
{
	use(66);
	sudu=40;
	color(6);
	cout<<"MCYH  ";
	color(0);
	cout<<"WYQ   ";
	color(7);
	cout<<"WAH\n";
	color(6);
	Sout("看到了吧，这就是");
	Sout(name);
	Sout("，那个强大的玩家。\n\n");
	color(0);
	Sout("是，他强大到连创世之神都可以击败。\n\n");
	color(7);
	Sout("创世之神竟然对一个小小的玩家放水。\n\n");
	color(0);
	Sout("嘘。。。\n");
	Sout("他可能真的十分强大，他获取了世上仅有一把的量子之剑。\n\n");
	color(6);
	Sout("我喜欢这个玩家，他玩的很好，从未间断。\n");
	time_t the_end;
	time(&the_end);
	long long cha=the_end-kaishi;
	int d,h,m,s;
	d=cha/86400;
	h=cha%86400/3600;
	m=cha%3600/60;
	s=cha%60;
	Sout(name);
	Sout("从出生的那一刻起到现在，已经过去了");
	printf("%d天%d小时%d分钟%d秒",d,h,m,s);
	if (h==0&&(m==10&&s==0)||m<10)
	  hdcj(47);
	Sout("。当然，以我们为参照系。\n\n");
	color(7);
	Sout("。。。");
	color(6);
	Sout("这位玩家玩游戏真的很厉害，在整个存档中，一共完成了");
	d=0;
	for(int i=1;i<=70;i++)
	  {
	  	if (things[i+99])
	  	  {
	  	  	d++;
	  		printf("【%s】、",cj[i].c_str());
		  }
	  }
	cout<<d;
	Sout("个成就，在结束之前，还有");
	cout<<fost[6]<<"颗钻石、";
	cout<<things[7]<<"元钱。\n";
	color(0);
	Sout("MCYH，以后把你的主宰者之位让给这位玩家吧。\n\n");
	color(6);
	Sout("WYQ，叫他的名字。\n\n");
	color(0);
	Sout(name);
	Sout("。祝你在另一个时间线过的顺利。\n\n");
	color(7);
	Sout("走了，我们也应该去另一个时间线玩玩了。\n\n");
	color(6);
	Sout("嗯，我们一起走吧。\n\n");
	gs();
	cout<<"是否查看“战绩”（由于生成错误，只能查看森林的背包和附魔）\n";
	cout<<"Y/N";
	char l=_getch();
	if (l=='n'||l=='N')
	  return;
	for(int i=1;i<=200;i++)
	  if (fost[i])
	    printf("[%s] %d\n",fsn[i].c_str(),fost[i]);
	for(int i=0;i<4;i++)
	  for(int j=0;j<5;j++)
	    printf("[%s] %d级\n",fumoname[i][j].c_str(),has_fumo[i][j]);
	gs();
	return;
}
void clearzhandou(int x,int y,int x1,int y1)
{
	gotoxy(40,35);
	printf("          "); 
	gotoxy(x-2,y);
	if (x-2>2)
	  printf("          ");
	gotoxy(x-1,y);
	if (x-1>2)
	  printf("          ");
	gotoxy(x1-2,y);
	if (x1-2>2)
	  printf("          ");
	gotoxy(x1-1,y);
	if (x1-1>2)
	  printf("          ");
}
bool zhandou(int m)
{
	time_t BC;
	time(&BC);
	bool juexing=false;
	int nvG=0,W214=0,W126=0;
	int ada=random(6,9);
	int bomb=-1505,bx,by;
	int cishum=0,cishua=0;
	int wl=0;
	int azweg=1; 
	int time=0;
	int hurt=0;
	int ztm[20],zta[20];
	int yh=0;
	//0持续伤害 1禁锢 2持续回血（兴奋药剂） 3特殊 4炸弹 5无敌 6浴火 7范围提升 8诅咒 9骨王减伤 10骨王反伤 11禁止回能 
	memset(ztm,0,sizeof(ztm));
	memset(zta,0,sizeof(zta));
	int A,B,ai;
	int mh=things[2]*16,ma=things[5],mc=things[6];
	A=mh;
	int ah,aa,ac;
	int a,b,c,d,e,f;
	a=b=c=d=e=f=0;
	d=random(things[9]-3,things[9]+5);
	ah=d*(random(21,28))*16;
	aa=d*(random(6,10));
	ac=d;
	B=ah;
	int i,j,k;
	int sh;
	char g;
	int x,y,x1,y1;
	x=5,x1=5;
	x1=5,y1=30;
	int energy=500,ea=500;
	//战前准备
	if (m==3)
	  ma*=1.3;
	if (m==1)
	  ma*=1.15;
	if (m==9)
	  mh+=B*0.8,e+=B*0.8,zta[0]=30;
	if (m==10)
	  ztm[0]=2147483641;
	if (m==12)
	  zta[2]=2147483641;
	if (m==15)
	  zta[10]=8;
	int jitan=0;
	juexing=false;
	yh=0;
	while(mh>0&&ah>0)
	  {
	  	cls();
	  	time+=3;
	  	color(0);
	  	//界面输出 
	  	gotoxy(0,0);
	  	cout<<"YOUR_HP:"<<mh<<'/'<<A<<"\t\t\t X_HP:"<<ah<<'/'<<B<<'\n';
	  	cout<<"YOUR ENERGY:"<<energy<<"\t\t\t AI_ENERGY"<<ea<<"\n";
	  	cout<<"___________________________________________________THE_TIME:"<<time/10<<"\n";
	  	gotoxy(x,y);
	  //	color(6);
	  	cout<<"♀";
	  	gotoxy(x1,y1);
	  //	color(7);
	  	cout<<"♀";
	  //	color(0);
	  	gotoxy(45,60);
	  	cout<<"YOURATTACK:"<<ma<<"\tAIATTACK:"<<aa;
	  	gotoxy(46,60);
	  	cout<<"YOURDEFENCE:"<<mc<<"\tAIDEFENCE:"<<ac;
	  	gotoxy(0,70);
	  	cout<<"YOUROUT\tAIOUT";
	  	gotoxy(1,70);
	  	cout<<a<<"\t"<<d;
	  	gotoxy(2,70);
	  	cout<<"YOURTREAT\tAITREAT";
	  	gotoxy(3,70);
	  	cout<<b<<"\t"<<e;
	  	gotoxy(4,70);
	  	cout<<"YOUR“BTW”\tAI“BTW”";
	  	gotoxy(5,70);
	  	cout<<c<<"\t"<<f;
	  	//状态输出
		gotoxy(10,70);
		cout<<"\t己方\t敌方\n";
		gotoxy(11,70);
		printf("持续伤害\t%ds\t%ds",ztm[0],zta[0]);
		gotoxy(12,70);
		printf("生命恢复\t%ds\t%ds",ztm[2],zta[2]);
		gotoxy(13,70);
		printf("禁锢\t%ds\t%ds",ztm[1],zta[1]);
		gotoxy(14,70);
		printf("其他1\t%ds\t%ds",ztm[3],zta[3]);
		gotoxy(15,70);
		printf("其他2\t%ds\t%ds",ztm[4],zta[4]);
		gotoxy(16,70);
		printf("其他3\t%ds\t%ds",ztm[5],zta[5]);
		gotoxy(17,70);
		printf("其他4\t%ds\t%ds",ztm[6],zta[6]);
		gotoxy(18,70);
		printf("其他5\t%ds\t%ds",ztm[7],zta[7]);
		gotoxy(19,70);
		printf("其他6\t%ds\t%ds",ztm[8],zta[8]);
		gotoxy(20,70);
		printf("其他7\t%ds\t%ds",ztm[9],zta[9]);
		gotoxy(21,70);
		printf("其他8\t%ds\t%ds",ztm[10],zta[10]);
		if (m==12)
		  {
		  	gotoxy(18,70);
		  	cout<<"祭坛血量："<<jitan;
		  }
		if (m==14)
		  {
		  	gotoxy(18,70);
		  	cout<<"亡魂数量："<<wl;
		  }
	  	g='m';
	  	if (ztm[1]<=0)
	  	  if (kbhit())
	  	    g=getch();
	  	if (zta[5]&&g!='a'&&g!='s'&&g!='d'&&g!='w')
		    g=';'; 
	  	//我方操作 
	  	switch(g)
	  	  {
	  	  	//移动 
	  	  	case 'a':y--;break;
	  	  	case 'd':y++;break;
	  	  	case 'w':x--;break;
	  	  	case 's':x++;break;
	  	  	//攻击 
	  	  	case ' ':
	  	  		{
	  	  			if (m==6&&juexing)
	  	  			  {
	  	  			  	gotoxy(x1-2,y1);
	  	  			  	cout<<"免疫";
	  	  			  	break;
					  }
	  	  			if (x-x1<=5&&x1-x<=5&&y-y1<=5&&y1-y<=5)
	  	  			  {
	  	  			  	sh=ma-ac;
	  	  			  	if (zta[9]&&m==15)
	  	  			  	  sh*=0.3,hurt+=sh;
	  	  			  	if (wl>12&&m==14)
	  	  			  	  sh*=0.4;
	  	  			  	else if (wl>0&&m==14)
	  	  			  	  sh*=1-wl*0.05;
	  	  			  	if (m==1&&rand()%10==7)
	  	  			  	  {
	  	  			  	  	gotoxy(x-2,y);
	  	  			  	  	cout<<"反伤-"<<sh;
	  	  			  	  	mh-=sh,c+=sh,d+=sh;
	  	  			  	  	break;
						  }
						if (m==15&&zta[10])
						  {
						  	gotoxy(x-2,y);
						  	cout<<'-'<<sh*0.75;
						  	mh-=sh*0.75,c+=sh*0.75,d+=sh*0.75;
						  }
	  	  			  	if (m==1&&rand()%5==3)
	  	  			  	  {
	  	  			  	  	gotoxy(x1-2,y1);
	  	  			  	  	cout<<"免疫";
	  	  			  	  	sh=0;
						  }
						//闪避判定
				if (m==6&&juexing==false)
				  {
				  	if (rand()%20==16)
				  	  {
				  	  	gotoxy(40,35);
				  	  	cout<<"反击直觉";
				  	  	x1=x,y1=y+2;
				  	  	sh=aa*1.65;
						gotoxy(x-2,y);
						cout<<"-"<<sh;
						mh-=sh,c+=sh,d+=sh;
						sh=0;
					  }
				  } 
	  	  			  	gotoxy(x1-2,y1);
	  	  			  	cout<<"-"<<sh;
	  	  			  	ah-=sh;
	  	  			  	a+=sh;
	  	  			  	f+=sh;
	  	  			  	energy+=random(20,45);
	  	  			  	ea+=random(5,25);
	  	  			  	if (ztm[6]&&m!=9)
	  	  			  	  zta[0]=6;
					  }
					cishum++;
					break;
				}
			//主动技 
			case '1':
				{
					if (things[70]&&energy>=500)
					  {
					  	gotoxy(40,35);
					  	cout<<"二连击刺";
					  	sh=(ma*1.6-ac);
					  	gotoxy(x-2,y);
					  	cout<<"-"<<sh<<'\n';
					  	gotoxy(x1-1,y1);
					  	cout<<"-"<<sh;
					  	ah-=sh*2;
					  	a+=sh*2;
					  	f+=sh*2;
					  	Sleep(500);
					  	energy-=500;
					  	ea+=random(10,60);
					  }
					cishum++;
					break;
				}
			case '2':
				{
					if (things[71]&&energy>=500)
					  {
					  	gotoxy(40,35);
					  	cout<<"自然滋养";
					  	sh=A*0.25;
					  	gotoxy(x-1,y);
					  	cout<<"+"<<sh;
					  	mh+=sh;
					  	b+=sh;
					  	Sleep(500);
					  	energy-=500;
					  }
					break;
				}
			case '3':
				{
					if (things[72]&&energy>=500)
					  {
					  	gotoxy(40,35);
					  	cout<<"影刃之斩";
					  	sh=B*0.2;
					  	if (sh>mh)
					  	  sh=mh-1;
					  	gotoxy(x1-2,y1);
					  	cout<<"-"<<sh;
					  	a+=sh;
					  	f+=sh;
					  	ah-=sh;
					  	Sleep(500);
					  	energy-=500;
					  	ea+=random(10,60);
					  }
					cishum++;
					break;
				}
			case '5':
				{
					if (things[74]&&energy>=500)
					  {
					  	gotoxy(40,35);
					  	cout<<"定时炸弹";
					  	bomb=time;
					  	energy-=500;
					  	bx=x,by=y;
					  	ztm[4]=4;
					  	Sleep(500);
					  }
					break;
				}
			case '6':
				{
					if (things[75]&&energy>=500)
					  {
					  	gotoxy(40,35);
					  	cout<<"兴奋药剂";
					  	ztm[1]=4;
					  	energy-=500;
					  	ma*=1.036;
					  	Sleep(500);
					  }
					break;
			 	} 
			case '7':
				{
					if (things[76]&&energy>=500)
					  {
					  	gotoxy(40,35);
					  	cout<<"虫洞";
					  	gotoxy(x,y);
					  	cout<<"  ";
					  	x=x1,y=y1+2;
					  	gotoxy(x,y);
					 // 	color(4);
					  	energy-=500;
					  	cout<<"♀";
					 // 	color(0);
					  	Sleep(500);
					  }
					break;
				}
			case '8':
				{
					if (things[77]&&energy>=500)
					  {
					  	gotoxy(40,35);
					  	cout<<"回旋飞刀";
					  	sh=ma*0.75;
					  	energy-=500;
					  	bool xx=false;
					  	for(i=1;i<=4;i++)
					  	  {
					  	  	if (rand()%5==3)
					  	  	  xx=true;
					  	  	gotoxy(x-2,y);
					  	  	cout<<'-'<<sh;
					  	  	ah-=sh,a+=sh,f+=sh;
						  }
						if (xx=true)
						  {
						  	zta[0]=2;
						  	sh=a*0.3;
						  	gotoxy(x-1,y);
						  	cout<<'+'<<sh;
						  	mh+=sh,b+=sh;
						  }
						Sleep(500);
					  }
					break;
				}
			case '9':
				{
					if (things[78]&&energy>=500)
					  {
					  	gotoxy(40,35);
					  	cout<<"浴火";
					  	sh=mh*0.8;
					  	energy-=500;
					  	gotoxy(x-2,y);
					  	cout<<'-'<<sh;
					  	mh-=sh,c+=sh;
					  	yh=sh+A*0.25;
					  	ztm[6]=5;
					  	Sleep(300); 
					  }
					break;
				}
		  }
		//我方被动技
		if (things[73]&&(time/10)%5==0)
		  {
		  	gotoxy(40,35);
		  	cout<<"暗影盾";
		  	sh=ma*0.4;
		  	gotoxy(x-1,y);
		  	cout<<'+'<<sh;
		  	mh+=sh;
			b+=sh; 
		  }
		
		
		//敌方
		//敌方移动（随机） 
		 ai=random(1,4);
		 if (rand()%3==1)//（1/3的概率向玩家冲来） 
		   {
		   	if (x>x1)
		   	  ai=1;
		   	if (x<x1)
		   	  ai=2;
		   	if (y>y1)
		   	  ai=3;
		   	if (y<y1)
		   	  ai=4;
		   }
		//敌方移动 
		switch(ai)
		  {
		  	case 1:x1++;break;
		  	case 2:x1--;break;
		  	case 3:y1++;break;
		  	case 4:y1--;break;
		  }
		//敌军攻击 
		if (rand()%2)//攻击率：1/2 
		  {
		  	if (x-x1<=5&&x1-x<=5&&y-y1<=5&&y1-y<=5||m==10&&zta[5]>0)
	  	  	  {
	  	  	  	if (m==2)
	  	  	  	  {
	  	  	  	  	int jn=cishua%3+1;
	  	  	  	  	switch(jn)
	  	  	  	  	  {
	  	  	  	  	  	case 1:
	  	  	  	  	  		{
	  	  	  	  	  		    sh=aa*1.05;
	  	  	  	  	  			mh-=sh;
	  	  	  	  	  			c+=sh,d+=sh;
	  	  	  	  	  			break;
							}
						case 2:
							{
								sh=aa*1.3;
								mh-=sh;
								c+=sh,d+=sh;
								break;
							}
						case 3:
							{
								x=random(x-5,x+5);
								y=random(y-5,y+5);
								break;
							}
					  }
				  }
	  	  		sh=aa-mc;
	  	  		if (m==12)
	  	  		  sh+=jitan*0.05;
	  	  		if (m==4&&things[21]>=2)
	  	  	  	  sh+=mh*0.04;
	  	  	  	if (m==13)
	  	  	  	  {
	  	  	  	  	if (time/10>=18&&time/10<=45)
	  	  	  	  	  sh=aa*2.2;
	  	  	  	  	if (time/10>45)
	  	  	  	  	  sh=aa*2.7,x--;
				  }
	  	  		gotoxy(x-2,y);
	  	  		cout<<"-"<<sh;
	  	  		mh-=sh;
	  	  		d+=sh;
	  	  		c+=sh;
	  	  		energy+=random(5,25);
	  	  		ea+=random(20,45);
	  	  		cishua++;
	  	  		if (cishua%4==0&&m==3)
	  	  		  {
	  	  		  	gotoxy(40,35);
	  	  		  	cout<<"魅惑射击";
	  	  		  	sh=mh*0.06;
	  	  		  	gotoxy(x-2,y);
	  	  		  	cout<<"-"<<sh;
	  	  		  	c+=sh,d+=sh,mh-=sh;
				  }
				//吸血判定
				if (m==5)
				  {
				  	sh*=0.3;
				  	gotoxy(x1-1,y1);
				  	cout<<"+"<<sh;
				  	ah+=sh,e+=sh;
				  } 
				if (m==6&&juexing)
				  {
				  	sh*=0.4;
				  	gotoxy(x1-1,y1);
				  	cout<<"+"<<sh;
				  	ah+=sh,e+=sh;
				  }
				if (m==12)
				  {
				  	sh*=0.2;
				  	jitan+=sh;
				  }
			  }
		  }
		//边界判定 
		if (x>40)
		  x=40;
		if (x<5)
		  x=5;
		if (y>70)
		  y=70;
		if (y<5)
		  y=5;
		if (x1>40)
		  x1=40;
		if (x1<5)
		  x1=5;
		if (y1>70)
		  y1=70;
		if (y1<5)
		  y1=5;
		//敌方energy>1000时触发必杀技 
		if (ea>=1000)
		  {
		  	if (m==1)
		  	  {
		  	  	sh=aa*1.95;
		  	  	gotoxy(40,35);
		  	  	cout<<"双剑合璧";
		  	  	gotoxy(x-2,y);
		  	  	cout<<"-"<<sh;
		  	  	mh-=sh;
		  	  	d+=sh;
		  	  	c+=sh;
		  	  	ztm[0]=4;
			  }
			if (m==2)
			  {
			  	gotoxy(45,30);
			  	cout<<"天空坠落";
			  	gotoxy(x,y+2);
			  	cout<<"#^@&#!#@……";
			  	Sleep(3000);
			  	gotoxy(x,y+2);
			  	cout<<"            ";
			  	sh=aa*5.4;
			  	gotoxy(x-2,y);
			  	cout<<"-"<<sh;
			  	mh-=sh;
			  	d+=sh;
			  	c+=sh;
			  	Sleep(500);
			  }//21难度 
			if (m==3)
			  {
			  	gotoxy(40,35);
			  	cout<<"马哈耶加翁";
			  	sh=aa*2.6;
			  	gotoxy(x-2,y);
			  	cout<<"-"<<sh;
			  	mh-=sh;
			  	d+=sh;
			  	c+=sh;
			  	Sleep(500);
			  	if (things[21]>=3)
			  	  {
			  	  	gotoxy(40,35);//总攻击 
			  	  	cout<<"总攻击";
			  	  	sh=aa*4;
			  	  	gotoxy(x-2,y);
			  	  	cout<<"-"<<sh;
					mh-=sh; 
					d+=sh;
					c+=sh;
					Sleep(500);
				  }
			  }
			if (m==4)
			  {
			  	gotoxy(40,35);
			  	cout<<"漩涡";
			  	gotoxy(x,y);
			  	cout<<"  ";
			  //	color(6);
			  	gotoxy(x1,y1+4);
			  	cout<<"♀";
			  //	color(0);
			  	ztm[0]=ztm[1]=2;
			  	Sleep(500);
			  }
			if (m==5)
			  {
			  	if (ztm[0]>0)
			  	  {
			  		if (things[21]>=3)
			  	  	  nvG*=2;
			  		gotoxy(x1+1,y1);
			  		cout<<"+"<<nvG;
			  		ah+=nvG,e+=nvG;
			  		nvG=0;
			  		Sleep(200);
			  	  }
			  	gotoxy(40,35);
			  	cout<<"灵魂环绕";
			  	ztm[0]=12;
			  	Sleep(500);
			  }
			if (m==6)
			  {
			  	gotoxy(40,35);
			  	cout<<"影刃之舞";
			  	gotoxy(x1,y1);
			  	cout<<"  ";
			  //	color(7);
			  	gotoxy(x,y+2);
			  	cout<<"＊";
			  	for(i=1;i<=5;i++)
			  	  {
			  	  //	color(0);
			  	  	sh=aa*0.36;
			  	  	c+=sh,d+=ah;
			  		mh-=sh;
			  		gotoxy(x-2,y);
			  		cout<<"-"<<sh;
			  		Sleep(100); 
				  }
			//	color(7);
				gotoxy(x,y+2);
				cout<<"♀";
				sh=a*2.62;
			//	color(0);
				gotoxy(x-2,y);
				cout<<"-"<<sh;
				mh-=sh;
				c+=sh,d+=sh;
				sh*=0.3;
				gotoxy(x1-1,y1);
				cout<<"+"<<sh;
				e+=sh;
				ah+=sh;
				Sleep(500);
			  }
			if (m==7)
			  {
			  	gotoxy(40,35);
			  	cout<<"狂风席卷";
			  	sh=A*0.2;
				gotoxy(x-2,y);
				cout<<"-"<<sh;
				c+=sh,d+=sh,mh-=sh;
				sh=aa*0.35;
				gotoxy(x-2,y);
				cout<<"-"<<sh;
				c+=sh,d+=sh,mh-=sh;
				Sleep(500);
			  }
			if (m==8)
			  {
			  	gotoxy(40,35);
			  	cout<<"控制者";
			  	ea-=200;
			  	while(ea>0)
			  	  {
			  	  	gotoxy(40,50);
			  	  	cout<<"剩余能量："<<ea;
			  	  	ea-=100;
			  	  	sh=aa*0.7;
			  	  	gotoxy(x-2,y);
			  	  	cout<<"-"<<sh;
			  	  	mh-=sh,c+=sh,d+=sh;
			  	  	gotoxy(x1-1,y1);
			  	  	sh*=0.5;
			  	  	cout<<"+"<<sh;
			  	  	ah+=sh,e+=sh;
			  	  	Sleep(300);
				  }
			  }
			if (m==9)
			  {
			  	gotoxy(40,35);
			  	cout<<"灵魂借取";
			  	sh=A*0.25;
			  	gotoxy(x-2,y);
			  	cout<<"-"<<sh;
			  	mh-=sh,c+=sh,d+=sh;
			  	W126=ah;
			  	gotoxy(x1-1,y1);
			  	cout<<"+"<<sh;
			  	ah+=sh,e+=sh;
			  	zta[3]=5;
			  	Sleep(500);
			  }
			if (m==10)
			  {
			  	gotoxy(40,35);
			  	cout<<"精神支配";
			  	sh=aa*2.9;
			  	x=random(1,40);
			  	y=random(1,50);
			  	gotoxy(x-2,y);
			  	cout<<'-'<<sh;
			  	mh-=sh,c+=sh,d+=sh;
			  	mc*=0.2;
			  	ztm[1]=2;
			  	zta[5]=5; 
			  	Sleep(500);
			   } 
			if (m==11)
			  {
			  	gotoxy(40,35);
			  	cout<<"化学风暴";
			  	sh=(B-ah)*0.5;
			  	ah+=sh,e+=sh;
			  	gotoxy(x1-1,y1);
			  	cout<<'+'<<sh;
			  	aa*=1.1;
			  	Sleep(500);
			  }
			if (m==12)
			  {
			  	gotoxy(40,35);
			  	cout<<"鲜血献祭";
			  	sh=ah*0.2;
			  	jitan+=sh;
			  	ah-=sh;
			  	f+=sh;
			  	Sleep(500);
			  }
			if (m==13)
			  {
			  	gotoxy(40,35);
			  	cout<<"时间跳跃";
			  	sh=B*0.055;
			  	ea-=200;
			  	while(ea>=0)
			  	  {
			  	  	gotoxy(x1-1,y1); 
			  	  	cout<<"+"<<sh;
			  	  	ea-=160;
			  	  	ah+=sh,e+=sh;
					Sleep(500);
				  }
				sh=aa*2.2;
				gotoxy(x-2,y);
				cout<<'-'<<sh;
				mh-=sh,d+=sh,c+=sh;
			  } 
			if (m==14)
			  {
			  	gotoxy(40,35);
			  	cout<<"埋骨之地";
			  	sh=aa*1.5;
			  	gotoxy(x-2,y);
			  	cout<<"-"<<sh;
			  	c+=sh,d+=sh;
			  	mh-=sh;
			  	wl++; 
			  	Sleep(500);
			  }
			if (m==15)
			  {
			  	gotoxy(40,35);
			  	cout<<"复仇反击";
			  	zta[9]=5;
			  	Sleep(350);
			  	zta[1]=5; 
			  }
			ea=0;
			if (m==10)
			  {
			  	ea+=energy*0.3;
			  	energy*=0.7;
			  }
			 
		  }
		//特殊输出
		//5技能炸弹
		if (ztm[4])
		  {
		  	gotoxy(bx,by);
		  	cout<<"#";
		  }
		if (m==9&&ah<=B)
		  zta[0]=0;
		//持续输出 
		if (time%9==0)
		  {
		  	if (wl>0)
		  	  {
		  	  	gotoxy(x-2,y);
		  	  	sh=aa*0.35*wl;
		  	  	cout<<'-'<<sh;
		  	  	mh-=sh;
		  	  	c+=sh,d+=sh;
		  	  	gotoxy(x1-1,y1);
		  	  	sh*=0.8;
		  	  	cout<<'+'<<sh;
		  	  	ah+=sh;
		  	  	e+=sh;
		  	  	energy-=wl*10,ea+=wl*10;
			  }
		  	if (m==13)
		  	  aa*=1.009;
		  	if (time%180==0&&m==11)
		  	  {
		  	  	gotoxy(40,35);
		  	  	cout<<"超肾上腺素";
		  	    zta[2]=8;
		  	    Sleep(500);
		  	  }
		  	if (m==11&&B*0.3<=ah)
		  	  {
		  	  	sh=B*0.01;
		  	  	f+=sh,ah-=sh;
		  	  	gotoxy(x1-2,y1);
		  	  	cout<<'-'<<sh;
		  	  	if (x-x1<=3&&x1-x<=3&&y-y1<=3&&y1-y<=3)
		  	  	  {
		  	  	  	sh*=3;
					gotoxy(x-2,y);
					cout<<'-'<<sh;
					c+=sh,d+=sh,mh-=sh; 
				  }
			  }
		  	for(i=0;i<=19;i++)
		  	  {
		  	   if (zta[i]>0)
		  	    zta[i]--;
			   if (ztm[i]>0)
			    ztm[i]--;
			  }
		  	if (zta[3]==1)//灵魂归还 
		  	  {
		  	  	W126=ah-W126;
		  	  	if (W126)
		  	  	  ah-=W126,mh+=W126,b+=W126,f+=W126;
			  }
			if (ztm[0])
			  {
			  	switch(m)
			  	  {
			  	  	case 1:sh=aa*0.5;break;
			  	  	case 4:sh=aa*1.75;break;
			  	  	case 5:sh=aa*1.3,nvG+=sh;break;
			  	  	case 9:sh=B*0.027;break;
			  	  	case 10:sh=aa*0.6;break;
				  }
				mh-=sh;
				gotoxy(x-2,y);
				cout<<"-"<<sh;
				c+=sh,d+=sh;
			  }
			if (zta[0])
			  {
			  	switch(m)
			  	  {
			  	  	case 6:sh=B*0.05;break;
			  	  	default:sh=ma*0.35;break;
				  }
				ah-=sh;
				gotoxy(x1-2,y1);
				cout<<'-'<<sh;
				c+=sh,d+=sh;
			  }
			if (ztm[1])
			  {
				sh=(A-mh)*0.16;
				if (sh<0)
				  sh=0;
				gotoxy(x-1,y);
				cout<<'+'<<sh;
				mh+=sh;
				b+=sh;
			  }
			if (zta[2])
			  {
			  	switch(m)
				  {
				  	case 11:sh=(B-ah)*0.16;break;
				  	case 12:sh=jitan*0.1;break;
				  } 
				ah+=sh;
				gotoxy(x1-1,y1);
				cout<<'+'<<sh;
				e+=sh,ah+=sh;
			  }
			if (ztm[0]<=1&&m==5)
			  {
			  	if (things[21]>=3)
			  	  nvG*=2;
			  	gotoxy(x1+1,y1);
			  	cout<<"+"<<nvG;
			  	ah+=nvG,e+=nvG;
			  	nvG=0;
			  	Sleep(200);
			  }
			if (ztm[6])
			  {
			  	sh=yh*0.2;
			  	gotoxy(x-1,y);
			  	cout<<'+'<<sh;
			  	mh+=sh,b+=sh;
			  }
			if (zta[9]<=1&&zta[9]!=0)
			  {
			  	ah-=aa*random(4,9)*0.3;
			  	f+=aa*random(4,9)*0.3;
			  	sh+=aa*random(4,9)*0.3;
			  	gotoxy(x,y-1);
			  	cout<<"）";
			  	y+=random(2,4);
			  	gotoxy(x,y);
			  //	color(4);
			  	cout<<"♀";
			 // 	color(0);
			  	gotoxy(x-2,y);
			  	sh=hurt*2+aa*1.5;
			  	cout<<'-'<<sh;
			  	mh-=sh;
			  	c+=sh,d+=sh;
			  	ah+=sh*0.8;
			  	e+=sh*0.8;
			  	hurt=0;
			  }
			if (ztm[4]==1)
			  {
			  	ztm[4]=0;
			  	gotoxy(bx-5,by-5);
			  	cout<<"～～～～～\n";
			  	gotoxy(bx-4,by-5);
			  	cout<<"～～～～～\n";
			  	gotoxy(bx-3,by-5);
			  	cout<<"～～～～～\n";
			  	gotoxy(bx-2,by-5);
			  	cout<<"～～～～～\n";
			  	gotoxy(bx-1,by-5);
			  	cout<<"～～～～～\n";
			  	gotoxy(bx,by-5);
			  	cout<<"～～～～～\n";
			  	gotoxy(bx+1,by-5);
			  	cout<<"～～～～～\n";
			  	gotoxy(bx+2,by-5);
			  	cout<<"～～～～～\n";
			  	gotoxy(bx+3,by-5);
			  	cout<<"～～～～～\n";
			  	gotoxy(bx+4,by-5);
			  	cout<<"～～～～～\n";
			  	gotoxy(bx+5,by-5);
			  	cout<<"～～～～～\n";
			  	sh=a*0.45;
			  	if (x>=bx-5&&x<=bx+5&&y>=by-5&&y<=by+5)
			  	  {
			  	  	gotoxy(x-2,y);
			  	  	cout<<"-"<<sh;
			  	  	mh-=sh;
			  	  	a+=sh,c+=sh;
				  }
				if (x1>=bx-5&&x1<=bx+5&&y1>=by-5&&y1<=by+5&&m!=6||(m==6&&juexing==false))
			  	  {
			  	  	gotoxy(x1-2,y1);
			  	  	cout<<"-"<<sh;
			  	  	ah-=sh;
			  	  	a+=sh,f+=sh;
				  }
				gotoxy(bx,by);
				cout<<" ";
			  }
		  }
		if (ztm[5]>0)
		  x++,y--;
		//2技能
		if ((time/10)%ada==0)
		  {
		  	if (m==1)
		  	  {
		  	  	gotoxy(40,35);
		  	  	cout<<"魔剑技";
		  	  	sh=mh*0.12+aa;
		  	  	gotoxy(x-2,y);
		  	  	cout<<"-"<<sh;
		  	  	mh-=sh,c+=sh,d+=sh;
		  	  	x-=5,y-=8;
			  }
			if (m==5)
			  {
			  	gotoxy(40,35);
			  	cout<<"灵魂吸取";
			  	sh=aa*0.5;
			  	for(i=1;i<=6;i++)
			  	  {
			  	  	gotoxy(x-2,y);
			  	  	cout<<"-"<<sh;
			  	  	gotoxy(x1-1,y1);
			  	  	cout<<"+"<<sh;
			  	  	mh-=sh,ah+=sh;
			  	  	a+=sh,c+=sh,d+=sh,e+=sh;
			  	  	sh*=0.05;
				  }
			  }
			if (m==7)
			  {
			  	gotoxy(40,35);
			  	cout<<"原始嚎叫";
			    ztm[3]=3;
			  }
			if (m==8)
			  {
			  	gotoxy(x-2,y);
			  	cout<<"肢解";
			  	for(i=1;i<=random(4,8);i++)
			  	  {
			  	  	sh=aa*0.4;
			  	  	gotoxy(x-2,y);
			  	  	cout<<"-"<<sh;
			  	  	ztm[1]=3;
				  }
			  }
			if (m==10)
			  {
			  	gotoxy(40,35);
			  	cout<<"恐惧威慑";
			  	Sleep(400);
			  	ea+=energy*0.3;
			  	energy*=0.7;
			  }
			if (m==11)
			  {
			  	gotoxy(40,35);
			  	cout<<"横冲直撞";
			  	sh=aa*0.7;
			  	mh-=sh,c+=sh,d+=sh;
			  	gotoxy(x-2,y);
			  	cout<<'-'<<sh;
			  	x-=3,y-=7;
			  	Sleep(500);
			  }
			if (m==13)
			  {
			  	gotoxy(40,35);
			  	cout<<"穿梭";
			  	sh=aa*0.5;
			  	for(i=1;i<=random(4,7);i++)
			  	  {
			  	  	gotoxy(x-2,y);
			  	  	cout<<'-'<<sh;
			  	  	mh-=sh,d+=sh,c+=sh;
				  }
				sh=2*0.4*aa;
				gotoxy(x-2,y);
				cout<<'-'<<sh;
				mh-=sh,c+=sh,d+=sh;
				Sleep(500);
			  }
			if (m==14)
			  {
			  	gotoxy(40,35);
			  	cout<<"噬魂斩击";
			  	sh=aa*0.25;
			  	gotoxy(x-2,y);
			  	cout<<'-'<<sh;
			  	mh-=sh,d+=sh,c+=sh;
			  	aa+=(ma*0.02),ac+=(mc*0.02);
			  	ma*=0.98,mc*=0.98;
			  	Sleep(500);
			  }
			if (m==15)
			  {
			  	gotoxy(40,35);
			  	cout<<"强制遵从";
			  	sh=aa*0.65;
			  	ztm[1]=1;
			  	gotoxy(x-2,y);
			  	cout<<'-'<<sh;
			  	mh-=sh,c+=sh,d+=sh;
			  	Sleep(300);
			  }
			ada=random(6,9);
		  }
		//特殊判定
		if (m==3&&mh<A*0.5&&juexing==false)
		  {
		  	gotoxy(40,35);
		  	cout<<"总攻击";
		  	juexing=true;
		  	sh=aa*4;
		  	gotoxy(x-2,y);
		  	cout<<"-"<<sh;
			mh-=sh;
			c+=sh,d+=sh;
			Sleep(500);
		  }
		if (m==4&&mh<A*0.2&&juexing==false)
		  {
		  	gotoxy(40,35);
		  	cout<<"决杀";
		  	sh=aa*4;
		  	gotoxy(x-2,y);
		  	cout<<"-"<<sh;
		  	mh-=sh;
		  	c+=sh,d+=sh;
		  	juexing=true;
		  	Sleep(500);
		  }
		if (m==6&&ah<=0&&juexing==false)
		  {
		  	gotoxy(40,35);
		  	cout<<"复仇执念";
		  	ah=B;
		  	juexing=true;
		  	zta[5]=2147483647,zta[0]=2147483647;
		  }
		if (m==8&&mh<A*0.2&&juexing==false)
		  {
		  	gotoxy(40,35);
		  	cout<<"最后一击";
		  	sh=aa*2;
		  	gotoxy(x-2,y);
		  	cout<<"-"<<sh;
		  	mh-=sh,c+=sh,d+=sh;
		  	ztm[1]=5;
		  	juexing=true;
		  }
		if (m==12&&ah<=0)
		  {
		  	gotoxy(x1-1,y1);
		  	cout<<'+'<<jitan;
		  	ah+=jitan;
		  	e+=jitan;
		  	jitan=0;
		  }
		if (m==13&&ah<=0&&juexing==false)
		  {
		  	gotoxy(40,35);
		  	cout<<"轮回";
		  	Sleep(2000);
		  	a=b=c=d=e=f=0;
			d=random(things[9]-3,things[9]+5);
			mh=things[2]*16,ma=things[5],mc=things[6];
			ah=B;
			A=mh;
			x=5,x1=5;
			x1=5,y1=30;
			energy=500,ea=500;
			juexing=true;
			
		  }
		if (m==15&&ah<=0&&juexing==false)
		  {
		  	gotoxy(40,35);
		  	cout<<"";
		  	Sleep(1500);
		  	ah=B;
		  	e+=B;
		  	ztm[0]=3;
		  	juexing=true;
		  }
		if (mh<=0&&things[78]&&ztm[6])
		  {
		  	sh=ztm[6]*yh;
		  	b+=sh;
		  	mh+=sh;
		  	gotoxy(x-1,y);
		  	cout<<'+'<<sh;
		  	ztm[6]=0;
		  	Sleep(300);
		  }
	  }
	gs();
	if (mh<0)
	  {
	  	cout<<"你输了！";
	  	things[82]=0;
	  	Sleep(2000);
	  }
	else
	  {
	  	cout<<"你赢了！";
	  	cout<<"获得战利品：";
	  	int h[5];
	  	for(i=1;i<=4;i++)
	  	  {
	  	    h[i]=random(1,50);
	  	    cout<<fsn[h[i]]<<"*1、";
	  	    if (1615383954+86400*145-BC>0&&m==10)
	  	      {cout<<"\b\b\b2";fost[h[i]]++;}
	  	    fost[h[i]]++;
	  	  }
	  	  if (rand()%8==4)
	  	    {
	  	      cout<<"恶魔沙漏*1、"; 
	  	      things[31]++;
	  	    }
	  	things[82]++;
	  	if (things[82]>=15)
	  	  hdcj(45);
	  	if (m==10)
	  	  hdcj(46);
	  	cout<<"\b\b。";
	  	Sleep(2000);
	  }
	gs();
	char mn='3';
	char q=' ',w=' ',u=' ',r=' ',t=' ',Y=' ';
	float _1,_2,_3,_4,_5,_6;
	if (a>=10000&&a<=999999)
	  q='K',_1=a/1000.0;
	if (a>=1000000&&a<=999999999)
	  q='M',_1=a/1000000.0;
	if (a>=1000000000)
	  q='B',_1=a/100000000.0;
	if (b>=10000&&b<=999999)
	  w='K',_2=b/1000.0;
	if (b>=1000000&&b<=999999999)
	  w='M',_2=b/1000000.0;
	if (b>=1000000000)
	  w='B',_2=b/100000000.0;
	if (c>=10000&&c<=999999)
	  u='K',_3=c/1000.0;
	if (a>=1000000&&a<=999999999)
	  u='M',_3=c/1000000.0;
	if (c>=1000000000)
	  u='B',_3=c/100000000.0;
	if (d>=10000&&d<=999999)
	  r='K',_4=d/1000.0;
	if (d>=1000000&&d<=999999999)
	  r='M',_4=d/1000000.0;
	if (d>=1000000000)
	  r='B',_4=d/100000000.0;
	if (e>=10000&&e<=999999)
	  t='K',_5=e/1000.0;
	if (e>=1000000&&e<=999999999)
	  t='M',_5=e/1000000.0;
	if (e>=1000000000)
	  t='B',_5=e/100000000.0;
	if (f>=10000&&f<=999999)
	  Y='K',_6=f/1000.0;
	if (f>=1000000&&f<=999999999)
	  Y='M',_6=f/1000000.0;
	if (f>=1000000000)
	  Y='B',_6=f/100000000.0;
	cout<<"\t你\t\t\tA.I.\n\n";
	cout<<"输出\t"<<_1<<q<<"\t\t\t"<<_4<<r<<"\n\n";
	cout<<"治疗\t"<<_2<<w<<"\t\t\t"<<_5<<t<<"\n\n";
	cout<<"承伤\t"<<_3<<u<<"\t\t\t"<<_6<<Y<<"\n\n";
	cout<<"按下'm'键退出\n\n";
	while(mn!='m')
	  {
		if (kbhit())
		  mn=getch();
	  }
}
void Jingji()
{
	use(67);
	cls();
	cout<<"这里是热闹的血戮竞技场，周围的人群不时发出的欢呼声令你感到不安。\n";
	cout<<"JOKER:又来竞技场了啊，还嫌被揍得不够惨吗？\n";
	cout<<"（众人大笑）\n";
	cout<<"请选择你想挑战的人：\n";
	cout<<"1.Elon（游侠，擅长打持续输出，人称“凛风之刃”）\n";
	cout<<"2.Ainz Ooal Gown（法师，擅长爆发输出，大招可以瞬间带走你，人称“魔法吟唱者”）\n";
	cout<<"3.JOKER（游侠、刺客，他的“persona”可以将你瞬间打成半血。人称“寡言的绝对领袖”）\n";
	cout<<"4.QUEEN（战士，JOKER的好助手，人称“果敢的战术参谋”）\n";
	cout<<"5.Shemira（法师，具有强大的治疗能力，人称“哀怮女妖”\n";
	cout<<"6.Z206（创世神MCYH的跟随者，擅长爆发输出，代号“Z206”，真名不为人所知，据说是MCYH的分身）\n";
	cout<<"7.Tidus（强大的战士，可以化作刀刃席卷战场，具有强大的吸血等级）\n";
	cout<<"8.W126（创世神MCYH的追随者WYQ的追随者，擅长控制，代号“W126”，真名不为人所知，据说是WYQ的分身）\n";
	cout<<"9.W214（创世神MCYH的追随者WAH的追随者，具有强大的回血能力，代号“W214”，真名不为人所知，据说是WAH的分身）\n";
	cout<<"a.凯恩（夺走了强互作用引力之剑的恶魔，这把剑使他变得异常强大）\n";
	cout<<"b.Isolde（一个被XLS改造的人，拥有超强的续航能力）\n";
	cout<<"c.ENGY（恶魔的信仰者，会将自身以及敌人的血量存入祭坛，在死亡时取出作为自身生命）\n"; 
	cout<<"d.Zollars（篡改时间的恶魔，自由穿梭在时间线中，拥有持续输出和超强自愈能力，死后可以让战斗重新开始\n";
	cout<<"e.Grizerle（骸骨之地的守墓人，可以召唤亡灵附身在敌人身上，给自己带来增益效果，是Toan的忠实护卫）\n";
	cout<<"f.Toan（骸骨之地的国王，一刀流的代表人物）\n";
	cout<<"0.查看说明\n";
	char l=_getch();
	if (l=='0')
	  {
	  	cls();
	  	cout<<"竞技场\n";
	  	cout<<"1.12.9版本的产物，在这里即使被击败也不会死亡。并且会掉落许多强大的物品供你升级、变强！\n";
	  	cout<<"血戮竞技场是一个比武的地方，在这里你要和各位角斗士进行竞赛！\n";
	  	cout<<"如果没有技能书，你将没有资格与角斗士竞技，会刚进场就被秒杀！\n";
	  	cout<<"以下是守卫者的技能：\n\n";
	  	cout<<"凛风之刃·Elon\n";
	  	cout<<"双剑合璧：将两把剑合为一把发动致命一击，造成195%attack伤害，并令敌人在此后的每秒内受到50%attack伤害持续4秒\n";
	  	cout<<"魔法剑技：释放以下两个技能：冰之剑：对敌人造成120%attack伤害并减速；风之剑：造成25%敌人生命值的生命并击飞\n";
	  	cout<<"魔剑（被动）：对敌人造成的伤害始终增加15%,受到伤害时有20%概率免疫此伤害（困难/炼狱模式下，有10%概率反伤100%）,仅限普攻\n\n";
	  	
	  	cout<<"魔法吟唱者·Ainz Ooal Gown\n";
	  	cout<<"天空坠落：吟唱3秒后对敌人造成540%attack伤害\n";
	  	cout<<"魔法吟唱：普通攻击改为轮流释放以下三个技能\n";
	  	cout<<"闪电：召唤闪电对敌人造成多次35%attack伤害\n";
	  	cout<<"黑洞：向敌人扔出黑洞造成130%attack伤害\n";
	  	cout<<"控制：将敌人传送至随机位置\n\n";
	  	
	  	cout<<"寡言的绝对领袖·JOKER\n";
	  	cout<<"马哈耶加翁：召唤亚森对敌人造成一次260%attack伤害，当难度在困难以上时发动“总攻击”(persona!)\n";
	  	cout<<"随机应变：开场时，JOKER会标记敌人。对标记的敌人额外造成30%attack伤害，如果被标记的敌人生命低于50%则会发动一次“总攻击”（困难模式以上时伤害提高1倍）\n";
	  	cout<<"魅惑射击：每当攻击4次后会使用手枪进行一次攻击，造成敌人当前生命6%的伤害\n";
	  	cout<<"总攻击：不会主动发动，对敌人造成400%attack伤害\n\n";
	  	
	  	cout<<"果敢的战术参谋·QUEEN\n";
	  	cout<<"漩涡：骑乘琼安制造一个漩涡，将敌人吸入漩涡每秒受到175%attack伤害持续2秒\n";
	  	cout<<"世纪末霸者前辈（被动）：普通攻击时额外造成其当前生命4%的伤害，简单模式下不会触发\n";
	  	cout<<"决杀：敌人生命低于20%时会发动，造成400%attack伤害\n\n";
	  	
	  	cout<<"哀怮女妖·Shemira\n";
	  	cout<<"灵魂环绕：释放大量灵魂，每秒对敌人造成130%attack伤害，持续6秒，并在释放结束以后恢复总伤害的100/200%(困难模式为200%)，如果期间能量蓄满则立即恢复血量结束伤害，然后再次释放\n";
	  	cout<<"灵魂吸取：吸取敌人的生命，每0.15秒造成50%attack伤害持续1秒，伤害每次增加5%\n";
	  	cout<<"灵魂枷锁：令敌人在8秒之内无法使用技能\n";
	  	cout<<"吸血灵体（被动）：吸血+20%\n\n";
	  	
	  	cout<<"MCYH追随者·Z206\n";
	  	cout<<"影刃之舞：扔出战刀并遁地，战刀会飞到敌人身边每0.1秒造成36%attack伤害。战刀飞到敌人身旁0.5秒后会瞬移至敌人身旁，造成262%Attack伤害，并恢复伤害30%等量生命\n";
	  	cout<<"反击直觉：受到伤害时有5%概率免疫伤害并反击，造成165%attack伤害\n";
	  	cout<<"复仇执念（被动）：死亡后以灵魂的形态继续在场上战斗，期间无敌但是每秒受到5%最大生命值的伤害。期间提高30%吸血等级\n\n";
	  	
	  	cout<<"血戮之刃·Tidus\n";
	  	cout<<"狂风席卷：化作刀刃席卷战场，对敌人造成20%最大生命值的伤害，然后从空中坠落，令敌人受到30%attack伤害\n";
	  	cout<<"原始嚎叫：发出嚎叫令敌人逃离自己（放逐）持续4秒\n";
	  	cout<<"追杀印记：对敌人加上追杀印记。攻击有追杀印记的敌人时带有35点吸血\n\n";
	  	
	  	cout<<"WYQ追随者·W126\n";
	  	cout<<"控制者：消耗200点能量将敌人禁锢在原地，此后每0.3秒消耗100点能量对敌人造成70%attack伤害并恢复50%伤害等量生命，直至能量耗尽\n";
	  	cout<<"肢解处理：将敌人拉至面前肢解，造成多次70%attack伤害并原地禁锢3秒\n";
	  	cout<<"最后一击：当敌人生命低于30%时造成一次200%attack伤害并禁锢5秒\n\n";
	  	
	  	cout<<"WAH追随者·W214\n";
	  	cout<<"灵魂借取：向敌人借取25%最大生命值的血量作为自己的护盾持续5秒，之后将剩余护盾转为生命还给该敌人\n";
	  	cout<<"灵魂盛宴：开场时额外获得80%最大生命值的等量血量，这些血量在开场后30秒之内缓慢失去。如果生命低于最大生命值则停止掉血\n";
	  	cout<<"生命体：每秒增加2.5%最大生命值，保持生命百分比不变\n";
	  	cout<<"免控机制（被动）：W214免疫所有敌人造成的持续伤害\n\n";
	  	
	  	cout<<"恶魔领主·凯恩\n";
	  	cout<<"精神支配：对敌人造成230%attack伤害并进行“恐惧威慑”，令其禁锢2秒，然后将攻击范围提升至全战场持续3秒\n";
	  	cout<<"恐惧威慑：发出怪叫永久降低敌人80%防御，然后偷取敌人30%能量\n";
	  	cout<<"强互作用引力保护屏障：当敌人发动技能或自身生命低于30%时生成一个护盾（期间无敌）持续3秒，最多抵消∞的伤害\n";
	  	cout<<"恶魔助手：开场时令3个恶魔附身敌人，恶魔无法被攻击且每秒对敌人造成20%attack伤害直至敌人死亡\n\n";
	  	
	  	cout<<"恐虐尸傀·Isolde\n";
	  	cout<<"化学风暴：为自身注入大量化学药剂，立刻恢复已损失生命值的50%生命，然后增加10%攻击力\n";
	  	cout<<"致命酸雾：开场时在自身周围释放酸雾，自身3格以内的敌人每秒受到3%YSED最大生命值的伤害，YSED每秒受到1%最大生命值的伤害，当YSED生命低于35%时会停止释放\n";
	  	cout<<"横冲直撞：冲向敌人造成210%攻击力伤害并撞飞\n";
	  	cout<<"超肾上腺素：使用后，每秒恢复16%已损失生命持续8秒，该技能每20秒触发一次\n\n";
	  	
	  	cout<<"狂热信仰者·ENGY\n";
		cout<<"鲜血献祭：将自身20%当前生命值注入祭坛\n";
		cout<<"恶魔祭坛：每秒恢复祭坛中10%的等量生命，攻击时额外造成祭坛中血量的5%伤害\n";
		cout<<"狂热信仰：攻击时将伤害的20%注入祭坛\n";
		cout<<"治疗神符（被动）：当生命降至0的时候触发（可以无限触发），将祭坛中所有生命转为自身生命恢复\n\n";
		
		cout<<"时之魇·Zollars\n";
		cout<<"时间跳跃：消耗200点能量进入时间裂隙，期间每秒消耗160点能量恢复自身5.5%最大生命值并禁锢敌人，直到生命回满、能量耗尽或再次使用该技能时，Zollars返回战场，对敌人造成220%攻击伤害。\n";
		cout<<"穿梭：与未来的自己配合多次攻击敌人，多次造成50%攻击力伤害，最后一击对敌人造成两段120%攻击伤害并短暂眩晕，但是两个Zollars受到伤害时，Zollars都会受伤\n";
		cout<<"永劫：战斗第18秒，Zollars的攻击方式改为对敌人造成2次120%攻击伤害并击退，第45秒，Zollars的攻击方式改为对敌人造成3次90%攻击伤害无视防御。困难模式下，Zollars每秒增加1%攻击力，持续80秒\n";
		cout<<"轮回（被动）：当自身即将死亡时，将时间回溯至战斗刚开始的状态，并保留“永劫”的持续时间，仅触发一次。\n\n";
		
		cout<<"骸骨禁卫·Grizerle\n";
		cout<<"埋骨之地：在敌人背后召唤墓碑造成180%attack伤害并眩晕2秒，并且令一个亡灵附身敌人，亡灵每秒偷取10点能量给自身，造成35%attack伤害，且不会消失，可叠加\n";
		cout<<"噬魂斩击：对敌人造成75%attack伤害并永久偷取15%防御和攻击\n";
		cout<<"亡魂守护（被动）：每当有一个亡灵附身在敌人身上时，自己受到的普攻伤害降低5%，最多降低60%\n";
		cout<<"嗜血之魂（被动）：每当有一个亡灵攻击敌人时，自己恢复伤害量的100%生命\n\n";
		
		cout<<"骸骨之王·Toan\n";
		cout<<"复仇反击：将敌人拉至面前，原地蓄力一段时间，期间降低70%所受伤害并强制敌人攻击自己每秒1~2次（也可以主动攻击），蓄力结束后对敌人造成160%attack伤害+170%蓄力期间所受伤害总和，此技能带有80%吸血\n";
		cout<<"强制遵从：将敌人劈倒造成130%attack伤害\n";
		cout<<"黄泉归来（被动）：死亡1秒后复活，只能触发一次，并令敌人眩晕3秒\n";
		cout<<"死亡诅咒（被动）：开场时诅咒敌人8秒，当Toan受到伤害时敌人也受到伤害的75%\n";
	  	cout<<"静待更新......\n";
	  	cout<<"如果屏幕太小没有全部看完可以拉动右侧滚轮进行上下调整喔~"; 
	  	gs();
	  	return; 
	  }
	int n=l-'0';
	if (l=='a')
	  n=10;
	if (l=='b')
	  n=11;
	if (l=='c')
	  n=12;
	if (l=='d')
	  n=13; 
	if (l=='e')
	  n=14;
	if (l=='f')
	  n=15; 
	zhandou(n); 
	happened+=(name+"在竞技场和人打架/");
}
int q[11][2]=
{
	0,0,
	152323,189203,
	202913,353921,
	293021,495022,
	100592,302919,
	315265,509392,
	495213,673829,
	493139,892029,
	903882,1392012,
	1500928,3728102,
};
void Bookstore()
{
	use(68);
	const string bookname[]={"","两连击刺","自然滋养","影刃之斩","暗影盾","定时炸弹","兴奋药剂","虫洞","回旋飞刀","浴火"};
	const string xiaoguo[]=
	{
	"",
	"对敌人造成两次160%攻击力伤害",
	"恢复自身最大生命值25%等量",
	"对敌人造成其最大生命值20%的伤害",
	"被动的，每5秒获得1个200%攻击力的永久护盾",
	"在脚下布置一个定时炸弹，4秒后爆炸对10格以内的人造成45%自身总输出的伤害（可能炸到自己）",
	"使用后每秒恢复16%已损失生命值持续4秒，并永久提高3.6%攻击",
	"瞬移至敌人右侧2格",
	"扔出回旋飞刀令敌人受到4次75%attack伤害。每次有20%概率造成2秒眩晕，成功眩晕则瞬移至敌人面前并恢复自身总输出的30%生命",
	"失去70%当前血量并进入浴火状态持续5秒，期间降低80%所受伤害，且攻击时附带35%的燃烧伤害持续6秒，并每秒恢复刚才失去生命的20%+最大生命值的5%，如果致死则立刻结束浴火状态并恢复剩余血量",
	};
 	time_t t1;
	time(&t1);
	cls();
	cout<<"图书管理员：来看看吧，都是精品！\n";
	bool xuan[11];
	memset(xuan,0,sizeof(xuan));
	int huo[3];
	int money[3];
	int n,m,i,j,k;
	for(i=0;i<3;i++)
	  {
	  	while(1)
	  	  {
	  	  	time_t t2;
			time(&t2);
			if (t2-t1>=3)
			  {
			  	cout<<"连接超时！";
			  	Write_File();
			  	break;
			  }
	  		huo[i]=random(1,9);
	  		bool exit=true;
	  		for(j=0;j<i;j++)
	  		  if (huo[i]==huo[j])
	  		    exit=false;
	  		if (exit)
	  		  break;
	  	  }
	  	cout<<i<<'.'<<bookname[huo[i]];
	  	money[i]=random(q[huo[i]][0],q[huo[i]][1]);
	  	cout<<"  "<<money[i]<<'\n';
	  }
	cout<<"16.帮助\n";
	cout<<"-1.什么都不买\n";
	cin>>m;
	if (m==-1)
	  return;
	if (m==16)
	  {
	  	cls();
	  	cout<<"本书店出售的都是可以在竞技场发动技能的“技能书”\n";
		cout<<"以下是每个技能以及触发编号。按下对应编号即可触发\n";
		cout<<"价钱公道，童叟无欺！\n\n"; 
	  	for(i=1;i<=9;i++)
	  	  {
	  	  	cout<<bookname[i]<<':'<<xiaoguo[i]<<'\n';
		  }
		gs();
		return;
	  }
	if (things[7]>=money[m])
	  {
	  	things[7]-=money[m];
	  	things[huo[m]+69]++;
	  	cout<<"购买成功！";
	  }
	else
	  cout<<"钱不够！";
}
void Bank()//85~88,89~92,93~96,97
{
	gs();
	int i,j,k,n,m;
	char l;
	if (things[85]==0)
	  {
	  	cout<<"请注册银行卡号：";
	  	cin>>things[85];
	  	cout<<"输入密码：";
	  	cin>>things[89];
	  }
	else
	  {
	  	cout<<"输入银行卡号：";
	  	cin>>j;
	  	cout<<"输入密码：";
	  	cin>>k;
	  	if (things[85]!=j||things[89]!=k)
	  	  {
	  	  	cout<<"密码错误！";
	  	  	gs();
	  	  	return;
		  }
	  }
	while(1)
	  {
	  	gs(); 
	  	cout<<"1.存款 2.取款 3.查看信息 4.离开\n";
	  	l=_getch();
	  	switch(l)
	  	  {
	  	  	case '1':
	  	  		{
	  	  			use(71);
	  	  			cout<<"存多少钱？（你有："<<things[7]<<"元钱）";
	  	  			cin>>k;
	  	  			if (k<=things[7])
	  	  			  {
	  	  			  	things[93]+=k;
	  	  			  	things[7]-=k;
	  	  			  	cout<<"存款成功！";
					  }
					else
					  cout<<"钱不够！";
					break;
				}
			case '2':
				{
					use(72);
					cout<<"取多少钱？（银行卡里有："<<things[93]<<"元钱）";
	  	  			cin>>k;
	  	  			if (k<=things[93])
	  	  			  {
	  	  			  	things[93]-=k;
	  	  			  	things[7]+=k;
	  	  			  	cout<<"取款成功！";
					  }
					else
					  cout<<"钱不够！";
					break;
				}
			case '3':
				{
					use(73);
					cout<<"余额："<<things[93]<<"元\n";
					cout<<"今日利率："<<things[97]/1000.0<<"%";
					gs();
					break;
				}
			case '4':return;
		  }
	  }
}
void PetShop()
{
	int money[2][9][2]=
	{
		{
			0,0,
			15000,30000,
			22500,37500,
			39813,50839,
			46392,55683,
			49302,60839,
			57839,70093,
			68392,80039,
			15000000,38000000,
		},
		{
			0,0,
			15000,30000,
			22500,37500,
			39813,50839,
			46392,55683,
			49302,60839,
			57839,70093,
			68392,80039,
			15000000,38000000,
		}
	};
	int sm[2][9][2]=
	{
		{
			0,0,
			300,500,
			600,900,
			1100,1300,
			1300,1500,
			1500,1700,
			1700,2000,
			2000,2300,
			150000,350000,
		},
		{
			0,0,
			300,500,
			600,900,
			1100,1300,
			1300,1500,
			1500,1700,
			1700,2000,
			2000,2300,
			150000,350000,
		},
	};
	int gj[2][9][2]=
	{
		{
			0,0,
			5,15,
			15,25,
			25,35,
			35,45,
			45,55,
			55,60,
			60,70,
			500,2000,
		},
		{
			0,0,
			3,10,
			12,20,
			21,27,
			29,38,
			39,50,
			51,59,
			62,75,
			500,2000,
		},
	};
	int fy[2][9][2]=
	{
		{
			0,0,
			1,2,
			3,4,
			7,10,
			8,13,
			11,15,
			12,18,
			15,20,
			100,300,
		},
		{
			0,0,
			1,2,
			3,4,
			7,10,
			8,13,
			11,15,
			12,18,
			15,20,
			100,300,
		}
	};
	int a[2][9],b[2][9],c[2][9],d[2][9];
	cls();
	printf("欢迎光临宠物店\n");
	string dn[9]={"","OXE07","PEOX7","P1L08","EX73K","KM81D","EG1J3","A8P32","P92OE"};
	string cn[9]={"","L3S13","S8IOP","MV3CL","IEPEO","DLPE4","DLAE0","CLEP1","LA09D"};
	int i,j;
	for(i=0;i<2;i++)
	  for(j=1;j<=8;j++)
	    a[i][j]=random(sm[i][j][0],sm[i][j][1]);
	for(i=0;i<2;i++)
	  for(j=1;j<=8;j++)
	    b[i][j]=random(gj[i][j][0],gj[i][j][1]);
	for(i=0;i<2;i++)
	  for(j=1;j<=8;j++)
	    c[i][j]=random(fy[i][j][0],fy[i][j][1]);
	for(i=0;i<2;i++)
	  for(j=1;j<=8;j++)
	    d[i][j]=random(money[i][j][0],money[i][j][1]);
	printf("1.DOG\n");
	for(i=1;i<=8;i++)
	  printf("1%d.%s HP%d ATTACK%d RUN%d money%d\n",i,dn[i].c_str(),a[0][i],b[0][i],c[0][i],d[0][i]);
	printf("2.CAT\n");
	for(i=1;i<=8;i++)
	  printf("2%d.%s HP%d ATTACK%d RUN%d money%d\n",i,cn[i].c_str(),a[1][i],b[1][i],c[1][i],d[1][i]);
	int n,m,k;
	printf("请输入你想购买的编号，无需隔开\n");
	cin>>m;
	n=m/10;
	m%=10;
	if (things[7]>=d[n][m])
	   {
	   	string lxx[3]={"","DOG","CAT"};
	   	cout<<"购买成功！给它起个名吧！\n";
	   	++things[191];
	   	string WWW;
	   	cin>>WWW;
	   	pet[things[191]].name=WWW;
	   	pet[things[191]].hp=a[n][m];
	   	pet[things[191]].attack=b[n][m];
	   	pet[things[191]].run=c[n][m];
	   	pet[things[191]].LX=lxx[n];
	   	things[7]-=d[n][m];
	   	happened+=(name+"买了一只"+lxx[n]+"，取名为"+WWW+"/");
	   	Write_File();
	   }
	else
	  cout<<"钱不够！";
}
/*
  帮派成员管理函数
  驱逐 dead(x,y)
  加入 join(x,y,imft) 
  生成 born(x)
*/ 
void dead(int x,int y)//帮派成员死亡或被驱逐(x为其所在帮派，y为编号)
{
	if (gang[x].leader>y)
	  gang[x].leader--;
	gang[x].pnum--;
	gang[x].peo[y].name=".";
	gang[x].peo[y].hp=0;
	gang[x].peo[y].attack=0;
	gang[x].peo[y].defence=0;
	for(int ii=y+1;ii<=gang[x].pnum+1;ii++)//名单前移 
	  gang[x].peo[ii-1].name=gang[x].peo[ii].name,gang[x].peo[ii-1].hp=gang[x].peo[ii].hp,gang[x].peo[ii-1].attack=gang[x].peo[ii].attack,gang[x].peo[ii-1].defence=gang[x].peo[ii].defence;
} 
void join(int x,int y,people imft/*imformation的缩写*/)//新成员加入帮派(x为其所在帮派，y为编号)
{
	gang[x].pnum++;
	y=gang[x].pnum;//双重保险 
	gang[x].peo[y].name=imft.name;
	gang[x].peo[y].hp=imft.hp;
	gang[x].peo[y].attack=imft.attack;
	gang[x].peo[y].defence=imft.defence;
} 
people born(int x)//生成一个新成员 
{
	people fx;
	fx.hp=random(1500,20000);
	fx.attack=random(650,4300);
	fx.defence=random(280,1230);
	fx.name=randstr(6,16);
	fx.gang=x;
	return fx;
}
 
void fac()
{
	cls();
	if (me.gang==0)
	  {
	  	printf("1.加入帮派\n2.创建帮派\n3.查看帮派情况\n4.退出");
	  	char l;
	  	int n,i,j,k;
	  	l=_getch();
	  	switch(l)
	  	  {
	  		case '1':
	  			{
	  				cls();
	  				printf("名称\t\t\t\t成员数量\t\t\t\t帮主\n");
	  				for(i=1;gang[i].pnum;i++)
	  				  printf("%s\t\t\t%2d\t\t\t\t%s\n",gang[i].name.c_str(),gang[i].pnum,gang[i].peo[gang[i].leader].name.c_str());
	  				printf("请输入你想加入的编号:");
	  				do
	  				{
					  cin>>j;
					if (gang[j].pnum>=50)
					  {
					  	printf("已满员");
					  } 
				    }
					while(gang[j].pnum>=50);
					printf("加入成功");
					gang[j].pnum++;
					me.gang=j;
					gang[j].peo[gang[j].pnum].name=name;
					gang[j].peo[gang[j].pnum].hp=things[2];
					gang[j].peo[gang[j].pnum].attack=things[5];
					gang[j].peo[gang[j].pnum].defence=things[6];
					cls();
					break;
				}
			case '2':
				{
					cls();
					printf("创建帮派需要：钱*5000000 等级>=100 确定创建?Y/N\n");
					l=_getch();
					if (l!='Y'&&l!='y')
					  break;
					if (things[7]<5000000||things[9]<=99)
					  {
					  	printf("钱或等级不够!");
					  	break; 
					  }
					things[7]-=5000000;
					printf("创建成功!");
					Sleep(800);
					cls(); 
					printf("给它起个名字吧:");
					cin>>gang[30].name;
					gang[30].leader=1;
					gang[30].peo[1].hp=things[2];
					gang[30].peo[1].attack=things[5];
					gang[30].peo[1].defence=things[6];
					gang[30].peo[1].name=name;
					gang[30].pnum=1;
					me.gang=30;
				}
			case '3':
				{
					j=1;
					while(1)
					{
					  system("cls");
					  printf("%d-----%s------ case a to the last. case d to the next. case q to quit\n",j,gang[j].name.c_str());
					  for(i=1;i<=gang[j].pnum;i++)
					    {
					    	if (gang[j].leader==i)
					    	  printf("★Leader\n");
					    	printf("%d:%s\thp:%d\tattack:%d\tdefence:%d\n--------------------\n",i,gang[j].peo[i].name.c_str(),gang[j].peo[i].hp,gang[j].peo[i].attack,gang[j].peo[i].defence);
						}
					  l=_getch();
					  if (l=='a'&&j>1)
					    j--;
					  if (l=='d'&&j<30)
					    j++;
					  if (l=='q')
					    break;
					}
				    break;
				}
			case '4':return;
		  }
	  }
	else
	  {
	  	while(1)
	  	{
	  	cls(); 
	  	bool imler=false;
	  	if (rand()%15==6&&gang[me.gang].peo[gang[me.gang].leader].name!=name)
	  	  {
	  	  	int ii;
	  	  	Sout("帮主"+gang[me.gang].peo[gang[me.gang].leader].name+"看你骨骼精奇天赋异禀，将帮主之位让与你。");
	  	  	for(ii=1;ii<=50;ii++)
	  	  	  if (gang[me.gang].peo[ii].name==name)
	  	  	    break;
	  	  	gang[me.gang].leader=ii;//每次变量都要打这么长，好烦啊... =.= 
		  }
	  	printf("1.查看帮派情况\n2.情报书\n3.退出/解散帮派\n");
	  	if (gang[me.gang].peo[gang[me.gang].leader].name==name)
	  	  imler=true;
	  	if (imler)
	  	  printf("4.帮派管理\n5.帮派战役\n6.管理申请");
	  	printf("7.离开\n");
	  	char l=_getch();
	  	cls();
	  	switch(l)
	  	  {
	  	  	case '1':
	  	  		{
					j=1;
					while(1)
					{
					  system("cls");
					  printf("%d-----%s------ case a to the last. case d to the next. case q to quit\n",j,gang[j].name.c_str());
					  for(i=1;i<=gang[j].pnum;i++)
					    {
					    	if (gang[j].leader==i)
					    	  printf("★Leader\n");
					    	printf("%d:%s\thp:%d\tattack:%d\tdefence:%d\n--------------------\n",i,gang[j].peo[i].name.c_str(),gang[j].peo[i].hp,gang[j].peo[i].attack,gang[j].peo[i].defence);
						}
					  l=_getch();
					  if (l=='a'&&j>1)
					    j--;
					  if (l=='d'&&j<30)
					    j++;
					  if (l=='q')
					    break;
					}
				    break;
				}
			case '2':
				{
			  	    int i;
	    		  	for(i=0;i<gangth.size();i++)
	    		  	  if (gangth[i]=='/')
	    		  	    cout<<"\n";
	    		  	  else
	    		  	    cout<<gangth[i];
	    		  	gs();
				  break;
				}
			case '3':
				{
					for(j=0;j<=gang[me.gang].pnum;j++)
					  if (gang[me.gang].peo[j].name==name)
					    break;
					gang[me.gang].pnum--;
					gang[me.gang].peo[j].name=".";
					gang[me.gang].peo[j].hp=0;
					gang[me.gang].peo[j].attack=0;
					gang[me.gang].peo[j].defence=0;
					me.gang=0;
					break;
				}
			case '4':
				{
					int k;
					if (imler==false)
					  break;
					for(i=1;i<=gang[me.gang].pnum;i++)
					    {
					    	if (gang[me.gang].leader==i)
					    	  printf("★Leader\n");
					    	printf("%d:%s\tHp:%d\tAtk:%d\tDfc:%d\n--------------------\n",i,gang[me.gang].peo[i].name.c_str(),gang[me.gang].peo[i].hp,gang[me.gang].peo[i].attack,gang[me.gang].peo[i].defence);
						}
					printf("请输入目标的编号：");
					cin>>j;
					if (j>gang[me.gang].pnum)
					  break;
					printf("请选择一个选项：\n1.驱逐 2.设为帮主 3.宰杀 4.取消操作\n");
					char x=_getch();
					for(k=0;k<=gang[me.gang].pnum;k++)
					  if (gang[me.gang].peo[k].name==name)
					   	break;
					switch(x)
					  {
					  	case '1':
					  		{
							  gangth+=gang[me.gang].name+"的"+gang[me.gang].peo[j].name+"被驱逐了/";
					  		  if (j==k)
					  		    {
					  		  	  Sout("你把自己赶出了帮派。");
								  dead(me.gang,j);
								  me.gang=0; 
								  break;
							    }
							   dead(me.gang,j);
							   break;
						    }
						case '2':
							{
								gangth+=gang[me.gang].name+"的"+gang[i].peo[j].name+"被立为帮主/";
								gang[me.gang].leader=j;
								break;
							}
						case '3':
							{
								gangth+=gang[me.gang].name+"的"+gang[i].peo[j].name+"被杀了/";
								things[307]++;
								hdcj(63);
								if (things[307]>=10)
								  hdcj(64);
								if (j==k)
					  		      {
					  		  	    Sout("你把自己杀了。");
								    gang[me.gang].pnum--;
								    gang[me.gang].peo[j].name=".";
								    gang[me.gang].peo[j].hp=0;
								    gang[me.gang].peo[j].attack=0;
								    gang[me.gang].peo[j].defence=0;
								    me.gang=0;//众所周知，死人不能加入帮派 
								    Die();
								    break;
							      }
							    system("color 4f");
							    Sout(gang[me.gang].peo[j].name);
								Sout("被你杀了。");
								dead(me.gang,j);
								cls();
								break;
							}
						case '4':break;
					  }
					break;
				}
				case '5':
					{
						if (imler==false)
						  break;
						bool flag=0;//判断是我方发起还是对方发起 
						if (rand()%6==3)
						  flag=1;
						if (flag)
						{
						  do j=random(1,49); while(j!=me.gang);
						Sout(gang[j].name+"向你发起了帮派战役，是否接受(Y/N)\n");
						char l=_getch();
						if (l=='N'||l=='n')
						  {
						  	gangth+=gang[me.gang].name+"拒绝了"+gang[j].name+"发起的战斗，损失惨重/";
						  	Sout("你没有接受，因此损失了");
						  	int lost=random(2335,50000);
						  	printf("%d",lost);
						  	Sout("元钱\n");
						  	things[7]-=lost;
						  	gs();
						  	break;
						  }
						  }
						if (!flag)
						  {
							printf("Num\t\tName\t\tLeader\n");
							for(i=0;i<=49;i++)
						  	  printf("%d\t\t%s\t\t%s\n",i,gang[i].name.c_str(),gang[i].peo[gang[i].leader].name.c_str());
							printf("Enter which one do you want to fight with______↙(number)\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
							cin>>j;
							if (j==me.gang)
						  	  {
						  		printf("You can't fight with yourself...");
						  		Sleep(1000);
						  		break;
						 	   }
							printf("Are you sure to fight with %s?(Y/N)\n",gang[j].name.c_str());
							l=_getch();
							if (l=='N'||l=='n')
						 	   break;
						 }
						while(1)
						  {
							cls();
							printf("Num\t\tName\t\tatk\t\thp\t\tdfc\n");
							for(i=1;i<=gang[me.gang].pnum;i++)
						  	  printf("%3d\t\t%s\t\t%d\t\t%d\t\t%d\t\t%d\n",i,gang[me.gang].peo[i].name.c_str(), gang[me.gang].peo[i].attack, gang[me.gang].peo[i].hp, gang[me.gang].peo[i].defence);
							printf("Please choose one to fight with your enemy:(enter -1 to quit)");
							int us,enemy;
							cin>>us;
							if (us==-1)
							  break;
							enemy=random(1,gang[j].pnum);
							cls();
							printf("%s VS %s\n",gang[me.gang].peo[us].name.c_str(),gang[j].peo[enemy].name.c_str());
							people a=gang[me.gang].peo[us];
							people b=gang[j].peo[enemy];
							int round=0;
							while(a.hp>0&&b.hp>0)
							  {
							  	Sout("Round ");
							  	printf("%d\n",++round);
							  	int sh;
							  	sh=max(int(a.attack*random(8,12)/10.0-b.defence*random(8,12)/10.0),1);//打出负数就回血了，所以至少造成1点伤害, 
							  	Sout(a.name);													 //攻击和防御随机取0.8~1.2倍好玩一些 
							  	Sout("发起了攻击，对");
							  	Sout(b.name);
							  	Sout("造成了");
							  	cout<<sh;
							  	Sout("点伤害。\n");//以上这些可以合并 
							  	b.hp-=sh;
							  	sh=max(int(b.attack*random(8,12)/10.0-a.defence*random(8,12)/10.0),1);
							  	Sout(b.name);
							  	Sout("发起了攻击，对");
							  	Sout(a.name);
							  	Sout("造成了");
							  	cout<<sh;
							  	Sout("点伤害。\n");
							  	a.hp-=sh;
							  }
							Sout("战斗结束。");
							gang[me.gang].peo[us]=a;
							gang[j].peo[enemy]=b;
							if (a.hp<=0)
							  {
							  	gangth+=gang[me.gang].peo[us].name+"在帮派战役中被"+gang[j].name+"的"+gang[j].peo[enemy].name+"杀死了/";
                                          							  	printf("失败！%s死亡",a.name.c_str());
							  	dead(me.gang,us);//死后需清除其数据 
							  	if (a.name==name)
							  	  Die();
							  	int lost=random(359932,5083921);
							  	printf("损失%d元",lost);
							  	things[7]-=lost;
							  }
							if (b.hp<=0)
							  {
							  	if (gang[me.gang].peo[us].name==name)
							  	  things[306]++;
							  	if (things[306]>=50)
							  	  hdcj(62);
							  	gangth+=gang[me.gang].peo[us].name+"在帮派战役中杀死了"+gang[j].name+"的"+gang[j].peo[enemy].name+"/";
							  	int got=random(187903,3829183);
							  	printf("胜利！获得%d元",got);
							  	things[7]+=got,gotmoney+=got;
								dead(j,enemy);
							  }
							gs();
							if (gang[me.gang].pnum==0)
							  {
							  	gangth+=gang[me.gang].name+"在帮派战役中被"+gang[j].name+"灭了/";
							  	Sout("你的帮派被灭掉了!\n");
							  	Sleep(1000);
								Sout("你损失了所有钱财!");
								things[7]=0; 
								me.gang=0;
							  }
							if (gang[j].pnum==0)
							  {
							  	gangth+=gang[me.gang].name+"在帮派战役中被灭掉了"+gang[j].name+"/";
							  	Sout(gang[j].name);
							  	Sout("从此覆灭...");
							  	Sleep(1000);
							  	Sout("你获得大量金钱!\n");
							  	int got=random(509835,8898372);
							  	things[7]+=got,gotmoney+=got;
							  	break;
							  }
						  }
						break;
					}
				case '6':
					{
						if (things[200]==0)
						  {
						  	printf("还未收到申请呢...");
						  	gs();
						  }
						int i,j;
						people ask[31];//上限30
						things[200]=min(int(things[200]),30); 
						for(i=1;i<=things[200];i++)
						  ask[i]=born(me.gang);
						printf("Num\t\tName\t\t Hp \t\tAtk\t\tDfc\n");
						for(i=1;i<=things[200];i++)
						  printf("%3d\t\t%s\t\t%4d\t\t%3d\t\t%3d\n",i,ask[i].name.c_str(),ask[i].hp,ask[i].attack,ask[i].defence);
						printf("输入序号即可，以-1结束\n");
						do
						  {
						  	cin>>j;
						  	gangth+=ask[j].name+"加入了帮派/";
						  	if (j>=1&&j<=things[200])
						  	  join(me.gang,1,ask[j]);
						  }
						while(j!=-1&&gang[me.gang].pnum<50);
						things[200]=0;
						break;
					}
				case '7':return;
		  }
		  }
	  }
}
void City()
{
	use(69);
	cls();
	const string where[]={"竞技场","书店","银行","宠物店","离开","帮派"};
	int i,j,k,n,m;
	char l;
	while(1)
	  {
	  	cls();
	  	char l;
	  	for(i=0;i<1000;i++)
	  	  if (kbhit())
	  	    l=getch();//垃圾收集器 
	  	printf("你想去哪里，按下序号\n");
	  	for(i=0;i<6;i++)
	  	  printf("%d.%s\n",i,where[i].c_str());
	  	l=_getch();
	  	switch(l)
	  	  {
	  	  	case '0':Jingji();break;
	  	  	case '1':Bookstore();break;
	  	  	case '2':Bank();break; 
	  	  	case '3':PetShop();break;
	  	  	case '4':return;
	  	  	case '5':fac();break;
		  }
	  }
}
void Soc()
{
	const string where[]={"家","赌场（“财源滚滚”）","人力市场（打工，找工作，挂机收益等等）","游乐场（休闲娱乐+赚点小钱）","小森林（阴森诡异）","超市（购物）","背包","公园(公告什么的)","存档并退出","市中心（建设中）"};
	int i,j,k,n,m;
	while(1)
	  {
	  	cls();
	  	char l;
	  	for(i=0;i<1000;i++)
	  	  if (kbhit())
	  	    l=getch();//垃圾收集器 
	  	cout<<" Day "<<things[16]+((things[10]-6)*30)<<'\n';
	  	printf("你想去哪里，按下序号\n");
	  	for(i=0;i<10;i++)
	  	  printf("%d.%s\n",i,where[i].c_str());
	  	if (things[188]==1)
	      l=choose(7)+'0';
	    else
	  	  l=_getch();
	  	switch(l)
	  	  {
	  	  	case '0':home();break;
	  	  	case '1':Duchang();break;
	  	  	case '2':market();break;
	  	  	case '3':carnie();break;
	  	  	case '4':forest();break;
	  	  	case '5':shop();break;
	  	  	case '6':
	  	  		{cls();
				
	    	  const string w[]={"棒棒糖","面包","矿泉水","小瓶子","玩具枪"};
	    	  for(i=11;i<16;i++)
	    	    printf("%d.%s*%d\n",i,w[i-11].c_str(),things[i]);
	    	  printf("u.使用\n");
	    	  printf("e.出售\n");
	    	  printf("x.退出\n");
	    	  char m;
	    	  m=_getch();
	    	if (m=='u')
	    	  {
	    	  	printf("用哪个？");
	    	  	cin>>j;
	    	  	printf("用几个？");
	    	  	cin>>k;
	    	  	if (things[j]>=k)
	    	  	  {
	    	  	  	things[j]-=k;
	    	  	  	for(int jj=1;jj<=k;jj++)
	    	  	  	for(int ii=0;ii<10;ii++)
	    	  	  	  things[ii]+=xiaoguo[j][ii];
					}
				break;
			  }
			if (m=='x')
			  break;
			printf("你想卖掉哪个？输入序号和数量");
			int ll,ss;
			cin>>ll>>ss;
			if (things[ll]>=ss)
			  ll-=ss,things[7]+=much[ss],gotmoney+=much[ss];
			else
			  cout<<"不存在的";
			break;}
			case '7':park();break;
			case '8':Write_File();me.play+=clock(),exit(0);
			case '9':City();break;
			case 'r':if (things[0]==7) return;break;
			}
			if (things[0]>5)
			  return;
			gs();
	  }
}
void War()
{
	use(70);
	happened+=(name+"在某地和Richard决斗/");
	hdcj(33);
	//2,5,6
	int hp,attack,run;
	int H,A,R;
	hp=things[9]*random(46,67);
	attack=things[9]*random(11,18);
	run=things[9]*random(4,6);
	H=hp,A=attack,R=run;
	cout<<"你的信息：你拾取了Richard给你的量子剑\n";
	cout<<"血量："<<things[2]<<"\t攻击："<<things[5]<<"\t防御："<<things[6]<<'\n';
	cout<<"技能：量子充能：对敌人造成自身最大生命40%伤害。增强：并恢复伤害的80%\n\n\n";
	cout<<"敌人：创世之神·MCYH\n";
	cout<<"职业：程序员 主要职责：编写代码\n";
	cout<<"血量："<<hp<<"\t攻击："<<attack<<"\t防御："<<run;
	cout<<"\n";
	cout<<"技能：\n";
	cout<<"纳米剑蓄力：Richard挥动纳米剑对敌人造成450%攻击的伤害，如果敌人生命值低于50%则伤害提高5倍\n";
	cout<<"时间裂隙：Richard消耗敌人最大生命值的25%生命（如果使用后生命值低于1则将血量恢复至1点），开启时间裂隙。在时间裂隙中每秒恢复最大生命值生命的15%持续3秒，从裂隙出来时会伏击敌人造成200%攻击伤害\n";
	cout<<"嗜血魔剑：挥动魔剑造成敌人最大生命15%的伤害，该次攻击带有300%吸血效果\n";
	cout<<"强互作用引力盾：开场时用强互作用引力剑召唤一个持续70秒的护盾，此护盾不能抵挡伤害，但是护盾存在期间不会受到附魔以及除了量子剑以外所有武器的伤害\n" ;
	cout<<"速战速决：当战斗时间超过15秒时发动，用纳米细丝将敌人切碎，无视免疫和闪避。\n";
	cout<<"欺诈盟约：攻击时有15%概率触发，用自身10%当前生命治疗敌人，然后偷取敌人15%攻击\n";
	cout<<"轮回：当自身死亡时使用，将时间回溯至一伀倀儀刀匀吀唀嘀圀堀夀娀嬀尀崀嬀帀开怀堀愀戀挀搀攀昀最栀椀樀欀氀洀?渀（此处为字迹不清的资料）\n";
	cout<<"组合双剑：被动的，战斗中Richard只会使用嗜血魔剑，每次攻击造成120%~180%攻击力伤害，纳米剑以及强互作用引力之剑在空中飞行，纳米剑会找机会对敌人造成23%已损失生命，强互作用引力之剑会找准机会挡下你的攻击\n";
	cout<<"被动：被动的，吸血+80%，荆棘30%\n";
	cout<<"按下任意键开始决斗！\n";
	gs();
	int a=things[2],b=things[5],c=things[6];
	int x,y,x1,y1;
	x=15,y=27;
	x1=15,y1=40;
	int energy=1,time1=1,time3=1,time4=1;
	long long last;
	time_t t12;
	time(&t12);
	last=t12;
	while(a>0&&hp>0)
	  {
	  	time_t t13;
	  	time(&t13);
	  	if (t13!=last)
	  	  {
	  	  	time1++,time3++,time4++,energy++;
	  	  	hp+=H*0.02;
		  }
		last=t13;
	  	gotoxy(0,0);
	  	cout<<"YOUR_HP:"<<a<<"\t\t\t"<<"MCYH_HP:"<<hp<<'\n';
	  	cout<<"操作提示：WASD移动，空格攻击，按Q使用技能（还差"<<10-energy<<"点能量就可以释放了!）\n";
	  	char l='.';
	  	int n,m,i,j,k;
	  	n=random(1,4);
	  	if (x<5)
	  	  x=5;
	  	if (y<5)
	  	  y=5;
	  	if (x>35)
	  	  x=35;
	  	if (y>60)
	  	  y=60;
	  	if (x1<5)
	  	  x1=5;
	  	if (y1<5)
	  	  y1=5;
	  	if (x1>35)
	  	  x1=35;
	  	if (y1>60)
	  	  y1=60;
	  	gotoxy(x,y);
	 // 	color(6);
	  	cout<<"♀";
	  	gotoxy(x1,y1);
	  //	color(7);
	  	cout<<"♀";
	  //	color(0);
	  	if (kbhit())
		   l=_getch();
		if (rand()%13==7)//纳米之剑攻击
		  {
		  	int hurt=(A-a)*0.23;
			gotoxy(x-2,y);
			cout<<'-'<<hurt;
			a-=hurt; 
		   } 
		 //判断我方
		switch(l)
		  {
		  	case 'w':x--;break;
		  	case 'a':y--;break;
		  	case 'd':y++;break;
		  	case 's':x++;break;
		  	case ' ':if (x-x1<=5&&x1-x<=5&&y1-y<=5&&y-y1<=5&&rand()%9!=5){hp-=(b-run);gotoxy(x1-1,y1);cout<<"-"<<b-run;energy++;a-=(b-run)*0.4;}break;
		  	case 'q':gotoxy(40,35);cout<<"量子充能！";if (x-x1<=10&&x1-x<=10&&y1-y<=10&&y-y1<=10){hp-=(things[2]*0.4-run);gotoxy(x1-1,y1);cout<<"-"<<(things[2]*0.4-run);a+=(things[2]*0.4-run)*0.8;energy=0;}break;
		  }
		//判断敌方
		switch(n)
		  {
		  	case 1:x1--;break;
		  	case 2:y1--;break;
		  	case 3:y1++;break;
		  	case 4:x1++;break;
		   } 
		if (rand()%2)
		  {
		  	if (x-x1<=5&&x1-x<=5&&y1-y<=5&&y-y1<=5)
		  	  {
		  	  	int hurt=(attack-c)*(random(120,180)/100.0);
		  	  	a-=hurt;
		  	  	hp+=hurt*0.8;
		  	  	gotoxy(x-1,y);
				cout<<"-"<<hurt;
				time1++,time3++,time4++;
				if (rand()%6==3)
				  attack+=b*0.15,b*=0.85,a+=hp*0.1,hp*=0.9; 
				//  10    11      7
			  }
		  }
		//敌方技能 
		if (time1>=10)
		  {
		  	gotoxy(40,35);
		  	cout<<"纳米剑蓄力";
		  	n=attack*4.5-c;
		  	if (a<=things[2]*0.5)
		  	  n*=5;
		  	gotoxy(x-1,y);
		  	cout<<"-"<<n;
		  	if (a<=things[2]*0.5)
		  	  cout<<" 终结！";
		  	a-=n;
		  	time1=0;
		  }
		if (time3>=11)
		  {
		  	a-=H*0.25;
		  	if (a<1)
		  	  a=1;
		  	for(i=1;i<=3;i++)
		  	  {
		  	  	gotoxy(x1-1,y1);
		  	  	cout<<"+"<<H*0.15;
		  	  	hp+=H*0.15;
		  	  	Sleep(1000);
			  }
			gotoxy(x-1,y);
			cout<<"-"<<attack*2-c;
			a-=attack*2-c;
			time3=0;
		  }
		if (time4>=9)
		  {
		  	gotoxy(40,35);
			  cout<<"嗜血魔剑"; 
		  	n=A*0.15;
		  	a-=n;
		  	gotoxy(x-1,y);
		  	cout<<'-'<<n;
		  	n*=3;
		  	hp+=n;
		  	gotoxy(x1-1,y1);
		  	cout<<"+"<<n;
		  	time4=0;
		  }
		if (hp<=0)
		  {
		  	gotoxy(40,35);
		  	cout<<"轮回";
		  	Sleep(2000);
		  	cls();
		  	hdcj(34);
		  	Sout("MCYH：仔细看过资料了吧。");
		  	gs();
		  	Sout("MCYH：【轮回】那一栏是字迹不清的。");
		  	gs();
		  	Sout("MCYH：给你重新看看完整的：");
		  	gs();
		  	Sout("MCYH：轮回：当自身死亡时使用，将时间回溯至游戏刚开始时的状态。");
		  	gs();
		  	Sout("MCYH：那么，再见啦~");
		  	poem();
			things[10]=6;
			if (things[34+99]&&things[35+99])
			  hdcj(43);
	  		happened+=(name+"击败了创世神/");
	  		happened+=(name+"被Richard传送回了6岁那年/");
	  		things[202]=1;
	  		return;
		  }
		if (a<=0)
		  {
		  	Sout("MCYH:你不行啊。。。回去多练练再来。。。");
		  	gs();
		  	War();
		  	happened+=(name+"MCYH获得1杀/");
		  	things[0]--;
		  	Soc();
		  }
		cls();
	  }
}
string pellect[80]=
{
//占位符 
"",
//    206          207		  	  208				209			210				211				212
"丹药（普通）","丹药（精良）","仙丹（稀有）","仙丹（罕见）","神丹（传说）","神丹（神话）","神丹（神话+）",
//	213				214				215					216					217					218					219
"紫金丹（普通）","紫金丹（精良）","紫金仙丹（稀有）","紫金仙丹（罕见）","紫金神丹（传说）","紫金神丹（神话）","紫金神丹（神话+）",//红+蓝=紫，常识。吃完成仙 
// 220					221						222					223						224						225					226
"黑暗紫金丹（普通）","黑暗紫金丹（精良）","黑暗紫金仙丹（稀有）","黑暗紫金仙丹（罕见）","黑暗紫金神丹（传说）","黑暗紫金神丹（神话）","黑暗紫金神丹（神话+）",//黑+紫=暗紫，常识。吃完成魔 
"","","","","","","","","","","","","","","","","","","",
//246		247		248		249
"红水晶      ","紫水晶      ","蓝水晶      ","黑水晶      ",
//250		251		252		253			254		255		256
"仙丹石      ","奥玄石      ","白虎石","朱雀石","青龙石","玄武石","麒麟内丹",
//257		258		259		260    261
"麒麟石","彩陶石","元神","","" 
};
//                 0  1     2    3     4      5       6       7          8     9     10   11     12       13          14     15   16     17     18     19        20     21                                                                                                                                                                                                                                                                                                                                                                       
const int addxp[]={0,2500,8000,50000,300000,1500000,10200000,105000000,8000,50000,348790,883739,5599883,45938212,327683920,8000,50000,483922,1293821,7839200,47382990,319382995};
int maketb[30][3][3]=//-205 (41)
{
	{//占位符 
		-2,-2,-2,
		-2,-2,-2,
		-2,-2,-2,
	},
	{//普通丹 
		45,45,45,
		45,45,45,
		45,45,45,
	},
	{//二级丹 
		45,1,45,
		1,1,1,
		45,1,45,
	},
	{//三级丹 
		-2,-2,-2,
		-2,-2,-2,
		-2,-2,-2,
	},
	{//四级丹 
		3,1,2,
		1,1,2,
		3,1,2, 
	},
	{//五级丹 
		4,2,3,
		2,2,3,
		4,2,3,
	},
	{//六级丹 
		5,3,4,
		3,3,4,
		5,3,4,
	},
	{//七级丹 
		6,4,5,
		4,46,5,
		6,4,5,
	},
	{//一级仙丹 
		-2,-2,-2,
		-2,-2,-2,
		-2,-2,-2,
	},
	{//二级仙丹 
		-2,-2,-2,
		-2,-2,-2,
		-2,-2,-2,
	},
	{//三级仙丹 
		-2,-2,-2,
		-2,-2,-2,
		-2,-2,-2,
	},
	{//四级仙丹 
		8,41,7,
		42,41,42,
		8,41,7,
	},
	{//五级仙丹 
		9,42,8,
		41,42,41,
		9,41,8,
	},
	{//六级仙丹 
		10,41,9,
		 42,46,41,
		10,42,9,
	},
	{//七级仙丹 
		46,41,10,
		 42,41,42,
		11,42,46,
	},
	{//一级魔丹 
		-2,-2,-2,
		-2,-2,-2,
		-2,-2,-2,
	},
	{//二级魔丹 
		-2,-2,-2,
		-2,-2,-2,
		-2,-2,-2,
	},
	{//三级魔丹 
		-2,-2,-2,
		-2,-2,-2,
		-2,-2,-2,
	},
	{//四级魔丹 
		17,44,16,
		43,43,43,
		17,44,16,
	},
	{//五级魔丹
		18,44,17,
		46,43,46,
		18,44,17, 
	},
	{//六级魔丹 
		19,43,18,
		46,44,46,
		19,44,18,
	},
	{//七级魔丹
		20,43,19,
		45,46,44,
		20,46,19, 
	},
};
void make_pills()
{
	int a,b,c,d;
	for(a=1;a<=21;a++)
	  for(b=0;b<3;b++)
	    for(c=0;c<3;c++)
	      if (maketb[a][b][c]>=1&&maketb[a][b][c]<=30)
	        maketb[a][b][c]+=205;
	if (things[270]==0)
	  {
	  	printf("没有炼丹炉！\n");
	  	printf("是否合成一个？\n");
	  	printf("合成方式：\n");
	  	printf("铁块  空  铁块\n");
	  	printf("铁块  空  铁块\n");
	  	printf("铁块 铁块 铁块\n");
	  	if (_getch()!='N'&&_getch()!='n')
		  if (fost[24]>=7)
		    things[270]=1,fost[24]-=7;
		  else
		    printf("铁块不足！");
		else
		  return; 
	  }
	if (things[270]>=1)
	  {
	  	bool breAk=1;
	  	while(breAk)
	  	  {
	  	  	printf("1.查看合成表 2.炼丹 3.使用丹药 4.离开\n");
	  	  	char l;
	  	  	l=_getch();
	  	  	switch(l)
	  	  	  {
	  	  	  	case '1':
	  	  	  		{
	  	  	  			int i,j=1,k=1;
	  	  	  			char g;
	  	  	  			while(j)
	  	  	  			  {system("cls");
	  	  	  			  	printf("a,d切换 q退出\n");
	  	  	  			  	printf("%s\n",pellect[k].c_str());
	  	  	  			  	if (maketb[k][0][0]==-2)
	  	  	  			  	  printf("不可合成");
	  	  	  			  	else
	  	  	  			  	  printf(" %s \t %s \t %s\n %s \t %s \t %s\n %s \t %s \t %s\n",pellect[maketb[k][0][0]].c_str(),pellect[maketb[k][0][1]].c_str(),pellect[maketb[k][0][2]].c_str(),pellect[maketb[k][1][0]].c_str(),pellect[maketb[k][1][1]].c_str(),pellect[maketb[k][1][2]].c_str(),pellect[maketb[k][2][0]].c_str(),pellect[maketb[k][2][1]].c_str(),pellect[maketb[k][2][2]].c_str());
						    g=_getch();
						    switch(g)
						      {
						      	case 'a':if (k>1)k--;break;
						      	case 'd':if (k<21)k++;break;
						      	case 'q':j=0;break;
							  }
						  }
						break;
					}
				case '2':
					{
						for(i=1;i<=47;i++)
						  if (things[i+205]>0)
						    printf("%d.%s*%d\n",i,pellect[i].c_str(),things[i+205]);
						printf("输入合成表（3*3）\n");
						int i,j,k,flag=1;
						int making[3][3];
						for(i=0;i<3;i++)
						  for(j=0;j<3;j++)
						    scanf("%d",&making[i][j]);
						for(i=1;i<=21;i++)
						  {
						  for(j=0;j<3;j++)
						    for(k=0;k<3;k++)
						      if (making[j][k]!=maketb[i][j][k])
						        {
						        	flag=0;break;
								}
							if (j>2&&k>2)
							  break;
							}
						if (i>21)
						  {
						  	printf("找不到此合成表");
						  	gs();
						  	break;
						  }
					int n=i;
					cout<<"做几个 "<<pellect[n]<<" ？";
					int l1;
					cin>>l1;
					int getn[2001];
					memset(getn,0,sizeof(getn));
					for(i=0;i<2000;i++)//仿制森林工作台，不过数据开多了点... 
					  getn[i]=things[i]; 
					bool can=true;
					for(i=0;i<3;i++)
					  for(j=0;j<3;j++)
					    if (maketb[n][i][j]>=0)
					    if (getn[maketb[n][i][j]]<l1)
					      {
					      	can=false;
					      	break;
						  }
						else
						  getn[maketb[n][i][j]]-=l1;
					if (can==0)
					  {
					  	cout<<"材料不足!，缺少"<<i<<','<<j<<'\n';
					  	gs();
						break; 
					  }
					  for(i=0;i<3;i++)
					    for(j=0;j<3;j++)
					      {
					      	if (maketb[n][i][j]!=-1)
					      	{
					      	  things[maketb[n][i][j]]-=l1;
					        }
						  }
						things[n+205]+=l1;
						break;
					}
				case '3':
					{
						int i,j,k;
						for(i=206;i<=226;i++)
						  if (things[i]>0)
						    printf("%d.%s*%d\n",i-205,pellect[i-205].c_str(),things[i]);
						printf("Enter what do you want to use?\n");
						scanf("%d",&j);
						printf("Enter how much do you want to use?\n");
						scanf("%d",&k);
						if (things[304]==0)
						  {
						    if (j>=8&&j<=14)
						      {
						        printf("吃完紫金丹后，你变成了神...");
						        gs();
								things[270]=2;
						      }
						    if (j>=15&&j<=22)
						      {
						      	printf("吃完黑暗紫金丹后，你变成了魔...");
						      	gs();
						      	things[270]=1;
							  }
						  }
						if (things[304]==1&&j>=8&&j<=14)
						  {
						  	printf("你是魔，不能吃神的东西...");
						  	gs();
						  	break;
						  }
						if (things[304]==2&&j>=15&&j<=21)
						  {
						  	printf("你是神，不能吃魔的东西...");
						  	gs();
						  	break;
						  }
						if (things[j+205]>=k)
						  {
						  	if (rand()%15==7)
						  	  {
						  	  	Sout("You feel disgust after you eat it... hp-50 xp-3000");
						  	  	things[1]-=3000,things[2]-=50;
						  	  	if (things[2]<=0)
						  	  	  Die();
						  	  	break;
							  }
						  	printf("Successful use!  ");
							printf("XP+%lld\n",addxp[j]*(things[9]/100+(things[9]%100/10)*5)+things[9]%10*5000*k*1000);
						  	things[j+205]-=k;
						  	//经验=提供经验*(等级百位+等级十位*5)+个位*5000
							things[1]+=addxp[j]*(things[9]/100+(things[9]%100/10)*5)+things[9]%10*5000*k*1000;
							sheng(); 
						  } 
						else
						  printf("The data is not enough.");
						gs();
						break;
					}
				case '4':breAk=0;break;
			  }
		  }
	  }
}
const string ques[]=
//				1								2						3									4
{"","你好啊，小伙子。是来找我谈opra的事的吧","不谈就走开!","你知道oprat世界是哪个scientist发现的吗?","不是吧，你没看过公告吗？是Copra啊。不过后来他被一种viru感染了，因为他不是opration",
//		5															6											7
"不错，你对oprat的历史还是挺了解的，那你肯定知道Richard吧","那是创世神啊，怎么会是human的scientist呢？","不用担心，你已经150级了，算是个弱X的opration了，不会感染的，Richard会保护你的",
// 8														9						10
"既然谈到Richard了，那你知道吗，曾经有个人击败过他呢!","是吗？那你用的什么武器？","敢骗我？就那种破剑怎么破得了他的盾？快出去！",
//		11															12										13
"你看就知道你在骗我，opration的记忆力没这么差，快出去！","哇，那你一定是那位转世重修者吧！（欣喜若狂）","我还没见过Richard呢，他长什么样啊？",
// 14
"...（外面轰隆一声，你的魂魄被震出了肉体，元神大损，Richard操纵了对你施展了九重雷劫，你的修行不够，魂魄分裂了。有一小部分重新转世了）",
// 15														16										17
"是吗？果然如传言所说啊。你可能会成为新的创世神呢!","那肯定啊，Richard打个响指（口误）...都能干掉你","你还是可能成为新创世神的，毕竟Richard很快要去另一个平行世界了",
// 18																			19											20
"不会了。Richard在每个世界都会安排一个创世神，你就是他从另一个世界带来的。","如果你当创世神，就不用继续轮回下去了。","只要你修行足够，Richard会来找你的",
//21																			22						23
"好了，我们讨论一下修仙的事吧。你知道你是谁，从哪来，到哪去了吗？", "不错，你已经开始悟到了你的本源道","你的修行还不够呢，这只是肤浅的理解而已",
//24								25
"当你升到200级的时候会理解的","据说，要成为创世神，需要历经本源大劫、九重雷劫及五行之中任意一劫。需要极高的修行，否则可能要重新轮回转世重修（很麻烦）",
//26				27												28			29															  
"你炼过仙丹吗？","炼丹是一件神圣庄严的事情，你一定要庄严对待","你会炼丹吗？","我们寺庙的后院可以烧香，只要心诚，则可心想事成，还能获得大量XP",
//30																31								32
"所谓炼丹，不仅仅是XP的获取，还有对道的领悟，对Heart的修养。","你平时可以来后院买点香纸","那太好了（又可以赚钱了），我们随时欢迎你",
//33								34								  	35
"能不能好好说话啊。。。","既然施主如此吝啬，那我只好扣除一些XP了","你是想修雷电大法、五行之术还是本源大道呢？",
//36
"好啊，学了这个你可以轻松度过九重雷劫，可以互相抵消，而且杀伤力也极高，一直是MCYH攻击的主要招式，当年的恶魔领主就是被此术击碎的",
//37
"好啊，学了这个你可以轻松控制世间万物，并轻松度过五行之劫，比雷电大法更加实用（和平年代用不着雷电大法）",
//38
"好啊，悟道本源大道之后，你可以知生死、预测未来，是成为上神的必修课程",
//39													40
"好啊，既然你这么好学，成为创世神有希望了（哈哈）", "好了，今日陪你叙述到此，下次有缘再谈。",
};
const string answ[]=
//	 	   1	2		3		4		5		6  		  7					8			9			10					11
{"别选我","是","不是","Ropca","Pocra","Copra","MCYH","我会感染那种viru吗?","继续吧","就是我啊","是吗，我不认识那人哦","开玩笑",
// 12        13		14		 15	    	16		17			18						19				 20
 "英雄剑","虚空剑","量子剑","忘了","没错就是我","帅爆了","丑爆了（轮回警告）","他戴了个面具，没看清","哪里，MCYH根本没认真和我打",
//21			22		23				24		25					26					27						28
  "可能会呢","那必须的","我可没那么弱","确实","他还回来吗？","我明白了，继续吧","那我要怎样才能成为创世神呢？","继续吧",
//29		30		31		32		33			34			35		36			37		   38	  39
 "P H D","E D C","G E F","P A C","请老师傅赐教","当然炼过","没有","一定一定","我才不要","当然会","不会",
//40			41			42		43		44			45
"下次一定","下次丕定","雷电大法","五行之术","本源大道","我全都要",
};
const int choosen[][13]=//0表示选项的数量 1~4表示选项对应答案编号，5~8为1~4答案的经验数量 9~12为1~4答案通向的下一个问题 0为无 
{
	0, 0,0,0,0, 0,0,0,0, 0,0,0,0,//0			//0占位符 
	2, 1,2,0,0, 1500,-1000,0,0, 3,2,0,0,//1			//表示2个选项，问完问题后，如果选择“是”则通往问题2，否则返回 
	1, -1,0,0,0, 0,0,0,0, -1,0,0,0,//2
	4, 3,4,5,6, 200,200,80000,40000, 4,4,5,6,//3
	1, 7,0,0,0, 500,0,0,0, 7,0,0,0,//4
	1, 8,0,0,0, 80000,0,0,0, 8,0,0,0,//5
	1, 8,0,0,0, 4000,0,0,0, 8,0,0,0,//6
	1, 8,0,0,0, 5000,0,0,0, 8,0,0,0,//7
	3, 9,10,11,0, 100000,200000,5000,0, 9,16,16,0,//8
	4, 12,13,14,15, -100000,-100000,5000000,-2000, 10,10,12,11, //9
	1, -1,0,0,0, -10000,0,0,0, -1,0,0,0,//10
	1, -1,0,0,0, -10000,0,0,0, -1,0,0,0,//11
	1, 16,0,0,0, 80000000,0,0,0, 13,0,0,0,//12
	3, 17,18,19,0, 666666666,-666666666,50000000,0, 15,14,15,0,//13
	0, 0,0,0,0, 0,0,0,0, 0,0,0,0,//14 		写什么都无所谓啦 
	3, 20,21,22,0, 10000000,5000000,8000000,0, 16,17,17,0,//15
	2, 23,24,0,0, 50000000,50000000,0,0, 17,18,0,0,//16
	1, 25,0,0,0, 100,0,0,0, 18,0,0,0,//17
	1, 26,0,0,0, 100,0,0,0, 19,0,0,0,//18
	1, 27,0,0,0, 100,0,0,0, 20,0,0,0,//19
	1, 28,0,0,0, 1000,0,0,0, 21,0,0,0,//20
	4, 29,30,31,32, 800000000,5,5,5, 22,23,23,23,//21
	1, 28,0,0,0, 1000,0,0,0, 25,0,0,0,//22
	1, 33,0,0,0, 100,0,0,0,  24,0,0,0,//23
	1, 28,0,0,0, 100,0,0,0,  25,0,0,0,//24
	1, 28,0,0,0, 1000,0,0,0, 26,0,0,0,//25
	2, 34,35,0,0, 10000000,1000000,0,0, 27,28,0,0,//26
	2, 36,37,0,0, 250000000,-100000000,0,0, 29,27,0,0,//27 (选项2就无限循环了） 
	2, 38,39,0,0, 320000000,130000000,0,0, 30,30,0,0,//28  懒得写那么多了
	3, 40,41,37,0, 560000000,-320000000,-800000000,0, 32,33,34,0,//29
	1, 26,0,0,0, 10000,0,0,0, 31,0,0,0,  //30
	1, 28,0,0,0, 1,0,0,0, 29,0,0,0,  //31 
	1, 28,0,0,0, 0,0,0,0, 35,0,0,0, //32
	1, 28,0,0,0, 0,0,0,0, 35,0,0,0, //33
	1, 28,0,0,0, 0,0,0,0, 35,0,0,0, //34
	4, 42,43,44,45, 50000000,80000000,150000000,100000000, 36,37,38,39,  //35
	1, 28,0,0,0, 1,0,0,0, 40,0,0,0,//36
	1, 28,0,0,0, 1,0,0,0, 40,0,0,0,//37
	1, 28,0,0,0, 1,0,0,0, 40,0,0,0,//38
	1, 28,0,0,0, 1,0,0,0, 40,0,0,0,//39
	1, -1,0,0,0, 0,0,0,0, -1,0,0,0,//40
	
};
void talk(int x,long long &gxp)//问题，gxp为getxp的缩写，表示获取的经验数量 
{
	if (x==27)
	  things[305]++;
	if (things[305]>4)
	  hdcj(61);
	int i,j,k;
	printf("获得XP:%lld\n",gxp);
	Sout("主侍："+ques[x]+'\n');
	if (x==14)
	  {//是不是很眼熟（初始化代码） 
	  	things[7]=800;
		things[2]=100;
		things[3]=50;
		things[4]=50;
		things[5]=30;
		things[6]=5;
		things[8]=100;
		things[9]=1;
		things[10]=6;
		things[18]=1;
		things[30]=720;
		things[34]=11901;
		for(int i=1;i<30;i++)
	 	  {
	  		gang[i].pnum=random(2,40);
	  		gang[i].name=randstr(5,21);
	  		for(int j=1;j<=gang[i].pnum;j++)
	  	  	  {
	  	  		gang[i].peo[j]=born(i);
		  	  }
			gang[i].leader=random(1,gang[i].pnum);
	  	  }
		time_t dl;
		time(&dl);
		start=dl; 
		things[0]=1;
		memset(renwu,0,sizeof(renwu));
		Write_File(); //想杜绝存档回复，及时存档很重要 
	    show();
	  }
	for(i=1;i<=choosen[x][0];i++)
	  if (choosen[x][i]==-1)
	    printf("%d.离开\t");
	  else
	    printf("%d.%s\t",i,answ[choosen[x][i]].c_str());
	char l=_getch();
	j=l-'0';
	gxp+=choosen[x][j+4];
	if (choosen[x][j+8]==-1||choosen[x][j]==-1)
	  return;
	talk(choosen[x][j+8],gxp);
} 
void fane()
{
	int i,j,k;
	char l;
	const string place[]={"主侍（Level>=150）","Secret Room（Level>=250）","烧香（money-50000）","后山（魔不能来）","离开"};
	while(1)
	  {
	  	for(i=0;i<5;i++)
	  	  printf("%d.%s\n",i,place[i].c_str());
	  	l=_getch();
	  	switch(l)
	  	  {
	  	  	case '0':
				{
				  if (things[9]<150) 
				    {
				      Sout("主侍：你的修行还不够呢，等升到150级再来找我吧。");
					  break;
					}
				  cls();
				  long long gxp=1000;
				  things[305]=0;
				  talk(1,gxp);
				  gxp*=(things[9]/100+(things[9]%100/10)*5)+things[9]%10*5000;
				  float c=random(80,650);
				  c/=100.0;
				  cls();
				  printf("翻倍：%d%%\n",int(c*100));
				  gxp*=c;
				  printf("XP+%lld",gxp);
				  things[1]+=gxp;
				  if (gxp>100000000)
				    if (rand()%15==6)
				      things[260]++;//默默赠送 
				  sheng();
				  gs();
				  break;
				}
			case '1':
				{
					time_t t1;
					time(&t1); 
					if (t1<things[301]+7200)
					  {
					  	printf("请在%d秒后再来。",things[271]+7200-t1);
					  	gs();
					  	break;
					  }
					if (things[9]<250) 
				      {
				      Sout("你的修行还不够呢，等升到250级再进来吧。");
					  break;
					  }
					cls();
					Sout("嘎吱——（开门声）");
					Sout("吼...吼...\n");
					Sout("你顺着叫声往里面走去\n");
					Sout("砰的一声，门关上了...\n");
					Sout("怪声：嘿嘿");
					if (things[304]==0)
					  {
					    Sout("，原来是个普通的opration啊，嘿嘿...\n");
					    Sout("逃跑");
					    int m=gongji(1000);
					    if (m>1000)
					      {
					      	Sout("逃跑成功！\n");
					      	break;
						  }
						else
						  {
						  	Sout("你受到了重伤！元神大损\n");
						  	int x,y;
						  	x=random(5000,20000),y=random(200000000,500000000);
						  	printf("hp-%d xp-%d",x,y);
						  	things[2]-=x,things[1]-=y;
						  }
					  }
					if (things[304]==1)
					  {
					  	time(&t1);
					  	things[301]=t1;
					  	Sout("，原来你是个小鬼啊...嘿嘿...\n");
					  	Sout("你是来要黑暗金丹的吧，诺，这是赏你的... 获得黑暗紫金丹（罕见）*1");
					  	things[223]++;
					  	break;
					  }
					if (things[304]==2)
					  {
					  	Sout("，原来是个神啊，嘿嘿\n");
					  	Sout("限你三秒出去，不然，嘿嘿嘿...（按任意键离开）\n");
					  	int i=clock();
					  	while(!kbhit())
					  	  printf("%d.%d",clock()/1000,clock()%1000);
					  	if (clock()-i>3000)
					  	  {
					  	  	Sout("你被一重木劫打中了。");
					  	  	int x,y;
					  	  	x=random(550,88880),y=random(77800000,1500000000);
					  	  	printf("hp-%d xp-%d");
					  	  	things[2]-=x,things[1]-=y;
					  	  	if (things[2]<=0)
					  	  	  Die();
						  }
						break;
					  }
					break;
				}
			case '2':
				{
					cls();
					if (things[7]<50000)
					  {
					  	printf("钱不够！");
					  	break;
					  }
					things[7]-=50000;
					Sout("南无喝啰怛那哆啰夜耶南无阿唎耶婆卢羯帝烁钵啰耶菩提萨埵婆耶摩诃萨埵婆耶摩诃迦卢尼迦耶唵萨皤啰罚曳数怛那怛写南无悉吉利埵伊蒙阿唎耶婆卢吉帝室佛啰楞驮婆南无那啰谨墀醯唎摩诃皤哆沙咩萨婆阿他豆输朋阿逝孕......\n");
					Sout("你的XP增加了");
					hdcj(28);
					things[1]+=random(100000000,2000000000);
					break; 
				}
			case '3':
				{
					time_t t1;
					time(&t1); 
					if (t1<things[302]+7200)
					  {
					  	printf("请在%d秒后再来。",things[272]+7200-t1);
					  	gs();
					  	break;
					  }
					cls();
					if (things[304]==1)
					  {
					  	Sout("Oprations：啊——有个Demon啊！\n");
					  	Sout("Gods：赶出去，赶出去！\n");
					  	Sout("你被赶走了，还好没有受伤\n");
					  	break;
					  }
					time(&t1);
					things[302]=t1;
					int a,b,c,d,e,f;
					a=random(255,262);
					b=random(255,262);
					c=random(255,262);
					d=random(1,3);
					e=random(1,3);
					f=random(1,3);
					if (a==255&&b==255&&c==255)
					  a=random(255,262);
					printf("获得：");
					if (a>255)
					  {
					    printf("%s*%d、",pellect[a-205].c_str(),d);
					    things[a]+=d;
					  }
					if (b>255)
					  {
					    printf("%s*%d、",pellect[b-205].c_str(),e);
					    things[b]+=e;
					  }
					if (c>255)
					  {
					    printf("%s*%d",pellect[c-205].c_str(),f);
					    things[c]+=f;
					  }
					break;
				}
			case '4':return;
		  }
	  }
}
//                            1     2    3      4     5       6     7        8        9     10     11         12     13     14    15       16       17         18     19         20     21       22       23       24        25      26        27       28        29        30       31        32          33      34          35        36       37       38          39       40                   BOSS41                                                                                                                                             
const long long  hper[]={0,80000,150000,200000,300000,500000,800000,1300000,1800000,2500000,3400000,4500000,5800000,7000000,8500000,10500000,13000000,14800000,17500000,20000000,25000000,32000000,43000000,52000000,59000000,70000000,85000000,102000000,110000000,123000000,135810000,148590000,173840000,201930000,248570000,290000000,350000000,480099332,710000000,890000000,1000000000,50000000000000};
const long long atker[]={0,10000,50000,100000,120000,200000,350000,500000,700000,1200000,1500000,2200000,2900000,3400000,4000000,4500000,5000000,5600000,6500000,7200000,9000000,11200000,15000000,21000000,25000000,32000000,35000000,410000000,45000000,49000000,56000000,63000000,71000000,79000000,86000000,98000000,120000000,170000000,230000000,410000000,500000000,       	   		 800000000000};
const long long dfcer[]={0,4500,22000,35000,45000,80000,120000,200000,300000,500000,600000,1000000,1300000,1500000,1600000,1800000,2300000,2600000,2900000,3400000,4000000,5500000,5600000,6300000,7300000,15000000,17200000,19000000,21000000,23000000,26000000,31000000,34000000,38000000,42000000,45000000,53000000,68000000,80000000,120000000,200000000,230000000  ,         			 200000000000};
const int         getn[]={0,246,246,247,247,248,248,249,249,250,250,251,252,253,254,255,256,257,258,259,206,213,220,207,214,221,208,215,222,209,216,223,210,217,224,211,218,225,212,219,226,259};
void trainning()
{
	if (things[303]<1)
	  things[303]=1;
	cls();
	printf("1.闯关模式（可选择1~%d关）\n",min(things[303],41));
	printf("2.自定义模式（自定义敌人，只掉落经验）\n掉落物：\n"); 
	int i,j,k;
	char l;
	l=_getch();
	switch(l)
	  {
	  	case '1':
	  		{
	  			while(1)
				  {
			  	cls();
	  			printf("请选择关卡（1~%d，0退出）\n",min(things[303],41));
	  			for(i=1;i<=40;i++)
	  			  printf("第%d关：%s\n",i,pellect[getn[i]-205].c_str());
	  			scanf("%d",&k);
	  			if (k==0)
	  			  break;
	  			if (k>min(things[303],41))
	  			  break;
	  			cls();
	  			long long hp=things[2],atk=things[5],dfc=things[6];
	  			long long ehp=hper[k],eak=atker[k],edc=dfcer[k];
	  			int Round=0;
	  			while(hp>0&&ehp>0)
	  			  {
	  			  	cls();
	  			  	long long hurt;
	  			  	printf("Round %d\n",++Round);
	  			  	printf("Your hp:%lld  Enemy's hp:%lld\n",hp,ehp);
	  			  	printf("Your atk:%lld Enemy's atk:%lld\n",atk,eak);
	  			  	printf("Your dfc:%lld Enemy's dfc:%lld\n",dfc,edc);
	  			  	hurt=llgongji(atk)-edc;
	  			  	printf("You attacked! Your enemy took %lld damage.\n",hurt);
	  			  	ehp-=hurt;
	  			  	hurt=eak*(random(8,12)/10.0)-dfc;
	  			  	printf("Enemy attacked! You took %lld damage.\n",hurt);
	  			  	hp-=hurt;
	  			  	printf("－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－\n");
	  			  	if (Round>=15)
	  			  	  break;
				  }
				if (hp<=0||Round>=15)
				  {
				  	printf("You lose!");
				  	gs();
				  	break;
				  }
				else
				  {
				  	int num=random(1,10);
				  	if (rand()%40==6)
				  	  num=random(15,50);
				  	if (getn[k]==259)
				  	  num=1;
				  	printf("You win! Got:XP*%lld %s*%d",(hper[k]*200+eak*300+edc*500)*things[9]*100,pellect[getn[k]-205].c_str(),num);
				  	things[getn[k]]+=num;
				  	things[1]+=(hper[k]*200+eak*300+edc*500)*things[9]*100;
				  	if (things[303]==k)
				  	  things[303]++;
				  	gs();
				  	break;
				  }
				  }
				break;
			}
		case '2':
			{
				long long a,b,c,d,e,f;
				cls();
				printf("Enemy's hp? (x~y) Enter x and y:");
				scanf("%d%d",&a,&b);
				printf("Enemy's atk? (x~y) Enter x and y:");
				scanf("%d%d",&c,&d);
				printf("Enemy's dfc? (x~y) Enter x and y:");
				scanf("%d%d",&e,&f);
				long long hp=things[2],atk=things[5],dfc=things[6];
	  			long long ehp=random(a,b),eak=random(c,d),edc=random(e,f),Hp=ehp;
	  			int Round=0;
	  			while(hp>0&&ehp>0)
	  			  {
	  			  	cls();
	  			  	long long hurt;
	  			  	printf("Round %d\n",++Round);
	  			  	printf("Your hp:%lld  Enemy's hp:%lld\n",hp,ehp);
	  			  	printf("Your atk:%lld Enemy's atk:%lld\n",atk,eak);
	  			  	printf("Your dfc:%lld Enemy's dfc:%lld\n",dfc,edc);
	  			  	hurt=llgongji(atk)-edc;
	  			  	printf("You attacked! Your enemy took %lld damage.\n",hurt);
	  			  	ehp-=hurt;
	  			  	hurt=eak*(random(8,12)/10.0)-dfc;
	  			  	hp-=hurt;
	  			  	printf("Enemy attacked! You took %lld damage.\n",hurt);
	  			  	printf("－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－\n");
	  			  	if (Round>=15)
	  			  	  break;
				  }
				if (hp<=0||Round>=15)
				  {
				  	printf("You lose!");
				  	gs();
				  	break;
				  }
				else
				  {
				  	printf("You win! Got:XP*%lld",(Hp*200+eak*300+edc*500)*things[9]*100);//还不是为了让你们快点升级 
				  	things[1]+=(Hp*20+eak*30+edc*50)*things[9]*100;
				  	gs();
				  	break;
				  }
			}
	  }
}
void secretman()
{
	if (things[9]<200)
	  {
	  	Sout("Secretman:不错嘛小伙子，居然能看见我...啧啧，你的修行还不够呢，升到200级再来找我吧！\n");
	  	return;
	  }
	printf("只要给我元神，我就帮你打造奇珍异宝！\n");
	printf("     朱雀盔      白虎甲      青龙腕      玄武靴      麒麟扇\n");
	printf("hp    1e+8        5e+12       3e+8          4e+8      5e+12\n");
	printf("atk   5e+7        3e+7        1e+7          0         8e+10\n");
	printf("dfc   2e+7        3e+7        4e+6          8e+6      4e+9\n");
	printf("Need\n");
	printf("   朱雀石*50   白虎石*80    青龙石*70   玄武石*40    麒麟石*100\n");
	printf("   彩陶石*50   彩陶石*80    彩陶石*70   彩陶石*40    麒麟内丹*120\n");
	printf("   元神*5       元神*5       元神*5      元神*5       元神*5\n");
	printf("1.朱雀盔 2.白虎甲 3.青龙腕 4.玄武靴 5.麒麟扇 6.离开\n");
	for(i=47;i<=54;i++)
	  printf("%s*%d\t",pellect[i].c_str(),things[i+205]);
	printf("\n");
	int k;
	cin>>k;
/*	206~245各种丹药数量 246红水晶 247紫水晶 248蓝水晶 249黑水晶 250仙丹石
251奥玄石 252白虎石 253朱雀石 254青龙石 255玄武石 256麒麟内丹
257麒麟石 258彩陶石 259元神 270炼丹炉*/
	switch(k)
	  {
	  	case 1:if (things[253]>=50&&things[258]>=50&&things[259]>=5)
	  			{
	  				printf("制作成功！\n");
	  				things[253]-=50,things[258]-=50,things[259]-=5;
	  				things[2]+=100000000,things[5]+=50000000,things[6]+=20000000;
				}
			   else
			   	printf("材料不够！\n");
			   	gs();
				break;
		case 2:if (things[252]>=80&&things[258]>=80&&things[259]>=5)
	  			{
	  				printf("制作成功！\n");
	  				things[252]-=80,things[258]-=80,things[259]-=5;
	  				things[2]+=500000000000,things[5]+=3000000,things[6]+=3000000;
				}
			   else
			   	printf("材料不够！\n");
			   	gs();
				break;
		case 3:if (things[254]>=70&&things[258]>=70&&things[259]>=5)
	  			{
	  				printf("制作成功！\n");
	  				things[254]-=70,things[258]-=70,things[259]-=5;
	  				things[2]+=30000000,things[5]+=1000000,things[6]+=400000;
				}
			   else
			   	printf("材料不够！\n");
			   	gs();
				break;
		case 4:if (things[255]>=40&&things[258]>=40&&things[259]>=5)
	  			{
	  				printf("制作成功！\n");
	  				things[253]-=40,things[258]-=40,things[259]-=5;
	  				things[2]+=40000000,things[6]+=800000;
				}
			   else
			   	printf("材料不够！\n");
			   	gs();
				break;
		case 5:if (things[256]>=120&&things[257]>=100&&things[259]>=5)
	  			{
	  				printf("制作成功！\n");
	  				things[256]-=120,things[257]-=100,things[259]-=5;
	  				things[2]+=500000000000,things[5]+=8000000000,things[6]+=400000000;
				}
			   else
			   	printf("材料不够！\n");
			   	gs();
				break;
	  }
	
} 
bool hijacking()
{
	long long hurt,xp;
	cls();
	printf("hp:%lld xp:%lld\n",things[2],things[1]);
	Sout("第一重雷劫落下\n");
	hurt=random(100000000,500000000)*10;
	xp=random(100000000,500000000)*10;
	hurt-=things[6];
	xp-=things[6];
	hurt=max(1,hurt);
	xp=max(1,xp);
	printf("hp-%lld xp-%lld\n",hurt,xp);
	things[2]-=hurt,things[1]-=xp;
	if (things[2]<=0||things[1]<0)
	  return 0;
	printf("hp:%lld xp:%lld\n",things[2],things[1]);
	Sout("第二重雷劫落下。\n");
	hurt=random(100000000,500000000)*100;
	xp=random(100000000,500000000)*100;
	hurt-=things[6];
	xp-=things[6];
	hurt=max(1,hurt);
	xp=max(1,xp);
	printf("hp-%d xp-%d\n",hurt,xp);
	things[2]-=hurt,things[1]-=xp;
	if (things[2]<=0||things[1]<0)
	  return 0;
	printf("hp:%lld xp:%lld\n",things[2],things[1]);
	Sout("第三重雷劫落下。\n");
	hurt=random(100000000,500000000)*1000;
	xp=random(100000000,500000000)*1000;
	hurt-=things[6];
	xp-=things[6];
	hurt=max(1,hurt);
	xp=max(1,xp);
	printf("hp-%lld xp-%lld\n",hurt,xp);
	things[2]-=hurt,things[1]-=xp;
	if (things[2]<=0||things[1]<0)
	  return 0;
	printf("hp:%lld xp:%lld\n",things[2],things[1]);
	Sout("第四重雷劫落下。\n");
	hurt=random(100000000,500000000)*10000;
	xp=random(100000000,500000000)*10000;
	hurt-=things[6];
	xp-=things[6];
	hurt=max(1,hurt);
	xp=max(1,xp);
	printf("hp-%lld xp-%lld\n",hurt,xp);
	things[2]-=hurt,things[1]-=xp;
	if (things[2]<=0||things[1]<0)
	  return 0;
	printf("hp:%lld xp:%lld\n",things[2],things[1]);
	Sout("第五重雷劫落下。\n");
	hurt=random(100000000,500000000)*100000;
	xp=random(100000000,500000000)*100000;
	hurt-=things[6];
	xp-=things[6];
	hurt=max(1,hurt);
	xp=max(1,xp);
	printf("hp-%lld xp-%lld\n",hurt,xp);
	things[2]-=hurt,things[1]-=xp;
	if (things[2]<=0||things[1]<0)
	  return 0;
	printf("hp:%lld xp:%lld\n",things[2],things[1]);
	Sout("第六重雷劫落下。\n");
	hurt=random(100000000,500000000)*1000000;
	xp=random(100000000,500000000)*1000;
	hurt-=things[6];
	xp-=things[6];
	hurt=max(1,hurt);
	xp=max(1,xp);
	printf("hp-%lld xp-%lld\n",hurt,xp);
	things[2]-=hurt,things[1]-=xp;
	if (things[2]<=0||things[1]<0)
	  return 0;
	printf("hp:%lld xp:%lld\n",things[2],things[1]);
	Sout("第七重雷劫落下。\n");
	hurt=random(100000000,500000000)*10000000;
	xp=random(100000000,500000000)*100000;
	hurt-=things[6];
	xp-=things[6];
	hurt=max(1,hurt);
	xp=max(1,xp);
	printf("hp-%lld xp-%lld\n",hurt,xp);
	things[2]-=hurt,things[1]-=xp;
	if (things[2]<=0||things[1]<0)
	  return 0;
	printf("hp:%lld xp:%lld\n",things[2],things[1]);
	Sout("第八重雷劫落下。\n");
	hurt=random(100000000,500000000)*100000000;
	xp=random(100000000,500000000)*1000000;
	hurt-=things[6];
	xp-=things[6];
	hurt=max(1,hurt);
	xp=max(1,xp);
	printf("hp-%lld xp-%lld\n",hurt,xp);
	things[2]-=hurt,things[1]-=xp;
	if (things[2]<=0||things[1]<0)
	  return 0;
	printf("hp:%lld xp:%lld\n",things[2],things[1]);
	Sout("第九重雷劫落下。\n");
	hurt=random(100000000,500000000)*1000000000;
	xp=random(100000000,500000000)*100000000;
	hurt-=things[6];
	xp-=things[6];
	hurt=max(1,hurt);
	xp=max(1,xp);
	printf("hp-%lld xp-%lld\n",hurt,xp);
	things[2]-=hurt,things[1]-=xp;
	if (things[2]<=0||things[1]<0)
	  return 0;
	Sout("雷劫结束，五行劫开始\n");
	string je[6]={"","金","木","水","火","土"};
	int nm=random(1,5);
	Sout(je[nm]+"劫落下。\n");
	hurt=random(10000000,50000000),xp=random(100000000,500000000);
	hurt-=things[6];
	xp-=things[6];
	hurt=max(1,hurt);
	xp=max(1,xp);
	if (things[2]<=0||things[1]<0)
	  return 0;
	Sout("本源劫落下。\n");//算了不落了 
	return 1;
}
void xiux()
{
	const string place[]={"炼丹房（炼丹）","寺院（可能有一些世外高人）","仙居（住的地方）","修行之地（修行）","神秘人（???）","小森林","下凡（主页面按q返回）","保存并退出","背包"};
	int i,j,k;
	char l;
	string level[3]={"OPRATION","DEMON","GOD"};//0 opration 1魔 2神 
	while(1)
	  {
	  	cls();
	  	if (things[9]>=384&&things[303]>=42)
	  	  {
	  	  	Sout("你渡劫的时候到了...\n");
	  	  	if (hijacking()==0)
				{
					Sout("你渡劫失败了，你的一部分灵魂重新转世了。\n");
	  				things[7]=800;
					things[2]=100;
					things[3]=50;
					things[4]=50;
					things[5]=30;
					things[6]=5;
					things[8]=100;
					things[9]=1;
					things[10]=6;
					things[18]=1;
					things[30]=720;
					things[34]=11901;
					for(int i=1;i<30;i++)
	 				  {
	  					gang[i].pnum=random(2,40);
	  					gang[i].name=randstr(5,21);
	  					for(int j=1;j<=gang[i].pnum;j++)
	  	  				  {
	  	  					gang[i].peo[j]=born(i);
		  	 			 }
						gang[i].leader=random(1,gang[i].pnum);
	  	  			}
					time_t dl;
					time(&dl);
					start=dl; 
					things[0]=1;
					memset(renwu,0,sizeof(renwu));
					Write_File();
	  			 	 show();
				}
	  	  	things[0]=8;
	  	  	return;
		  }
	  	for(i=0;i<1000;i++)
	  	  if (kbhit())
	  	    l=getch();//垃圾收集器 
	  	printf("%s Lv.%lld (%lld/%lld)\n",name.c_str(),things[9],things[1],sj[things[9]+1]);
	  	printf("%s\n",level[things[304]].c_str());
	  	printf("Day %d\n",things[16]);
	  	for(i=0;i<8;i++)
	  	  printf("%d.%s\n",i,place[i].c_str());
	  	l=_getch();
	  	switch(l)
	  	  {
	  	  	case '0':make_pills();break;
	  	  	case '1':fane();break;
	  	  	case '2':home();break;
	  	  	case '3':trainning();break; 
	  	  	case '4':secretman();break;
	  	  	case '5':forest();break;
	  	  	case '6':Soc();break;
	  	  	case '7':Write_File();exit(0);
	  	  	case '8':
	  	  		{
	  	  			for(i=1;i<=55;i++)
					  if (things[i+205]>0)
					    printf("%d.%s*%d\n",i,pellect[i].c_str(),things[i+205]);
					gs();
					break;
				}
		  }
	  }
}
void mainmenu()
{
	Time now=gottime();
	if (now.year==2022&&now.month==2&&now.day==6&&things[308]!=20220206)
	  {
	  	Sout("今天是MCYH的生日，你有什么想对他说的吗？\n");
	  	Sout("1.生日快乐 2.天天开心 3.平安幸福 4.All Of The Options\n");
	  	char a;
	  	a=_getch();
		switch(a)
	  	  {
	  	  	case '1':
	  	  	case '2':
	  	  	case '3':Sout("MCYH：谢谢祝福，新的一年我会继续努力。");printf("获得：XP*%lld money*%lld 春节礼炮*1 英雄战甲*1",50000*things[9],500000*things[9]);things[1]+=50000*things[9],things[7]+=500000*things[9],fost[22]++,fost[40]++;break;
	  	  	case '4':Sout("MCYH：感谢三连，新的一年我会继续努力。");printf("获得：XP*%lld money*%lld 春节礼炮*1 英雄礼包（内含：英雄头盔、英雄战甲、英雄护腿、英雄战靴、英雄剑、英雄斧、英雄镐）*1",500000*things[9],5000000*things[9]);things[1]+=500000*things[9],things[7]+=5000000*things[9],fost[22]++,fost[39]++,fost[40]++,fost[41]++,fost[42]++,fost[43]++,fost[44]++,fost[45]++;break;//送礼物当然得一件件送 
		  }
		things[308]=20220206;
		cls(); 
	  } 
	things[26]=0;
	if (things[0]==1)
	{
		if (things[26]==0)
		{
		sudu=300;
		gotoxy(30,70);
		Sout("第\t一\t章");
		gotoxy(32,70);
		Sout("我\t的\t童\t年");
		gotoxy(31,70);
		Sout("Episode 1\n");
		gotoxy(33,70);
		Sout("My Childhood");
		sudu=5;
		Sout("剧情：\n");
		Sout("人生之中最快乐最幸福的时光大概就是童年了，同时，童年的生活也是非常短暂的。\n");
		Sout("在学校里，你是想做一个学霸，还是一个默默无闻的学渣？\n");
		Sout("你是想做一个老师的好帮手，还是一个打架的刺儿头？\n");
		Sout("在本章里尽可揭晓!");
		things[26]=1;
		gs();
		}
	game();
	things[26]=0;
	}
	
	if (things[0]==2){
	Sout("时间过得真快呀，你已经12岁了，准备上初中了。");
	gs();
	Sout("只是不知，你能否顺利通过升学考试呢？");
	gs();
	gotoxy(40,60);
	sudu=300;
	Sout("第二章\n");
	gotoxy(42,60);
	Sout("入学考试\n");
	gotoxy(41,60);
	Sout("Episode 2\n");
	gotoxy(43,60);
	Sout("entrance examination\n");
	gs();
	sudu=5;
	if (things[26]==0)
	{
	Sout("剧情\n");
	Sout("我说的没错吧，很快，你的童年生活（小学时代）结束了，你面临着\n");
	Sout("人生中的第一道坎：小升初，也不知你能否如愿考上你心中最好的初\n");
	Sout("中呢？我们一起看看吧！");
	things[26]=1;
	Write_File();
	}	
	int fen=quest();
	gs();
	if (fen>=90)
	  {
	  	printf("	录	取	通	知	书\n");
	  	Sout("    恭喜你被蓝天中学录取！\n");
	  	Sout("Ftr:考得不错！蓝天中学可是这里最好的中学呢！");
	   }
	if (fen>=75&&fen<90)
	  {
	  	printf("	录	取	通	知	书\n");
	  	Sout("    恭喜你被蓝天中学录取！\n");
	  	Sout("Ftr:emmmmm...还行吧，蓝天中学也不错。");
	  }
	if (fen>=50&&fen<75)
	  {
	  	printf("	录	取	通	知	书\n");
	  	Sout("    恭喜你被蓝天中学录取！\n");
	  	Sout("Ftr:emmmmm...啊这，怎么考这么差？平时成绩不是挺好的嘛？蓝天中学是我们这儿比较差的中学哦\n"); 
	  }
	if (fen>=25&&fen<50)
	  {
	  	printf("	录	取	通	知	书\n");
	  	Sout("    恭喜你被蓝天中学录取！\n");
	  	Sout("Ftr:欠打？考成这样还敢回家？！\n");
	  	Sout("mtr:别打，再怎么也是个中学。。。\n");
	  }
	if (fen<25)
	  {
	  	Sout("Ftr:怎么考成这样，居然还敢回家？！\n");
	  	Sout("mtr:只能让你去上民办中学了，不过学费你自己出。\n");
	  	int school=30000;
	  	if (school>things[7])
	  	  school=things[7];
	  	Sout("Ftr:诶。。。学费需要");
	  	cout<<school;
	  	Sout("块钱诶，你正好付得起。");
	  	things[7]-=school;
	  	Write_File();
	  	gs();
	  	printf("	录	取	通	知	书\n");
	  	Sout("    恭喜你被蓝天中学录取！\n");
	  	gs(); 
	  }
	  things[0]++;
	  things[26]=0; 
	Write_File();}
	if (things[0]==3)
	{
		if (things[26]==0)
	  {
		sudu=400;
		gotoxy(40,60);
	  Sout("第三章\n");
	  gotoxy(42,60);
	  Sout("中学时光\n");
	  gotoxy(41,60);
	  Sout("Episode 3\n");
	  gotoxy(43,60);
	  Sout("High school time");
	  gs();
	  sudu=5;
	  Sout("时光匆匆而去，转眼你已是一个12岁的初中生了。\n");
	  Sout("你能否抵挡住赌场的诱惑，专心致志地学习，成\n");
	  Sout("为老师和同学们心目中的好学生呢？\n");
	  Sout("幸运的是，你的小学同学都和你分到了同一个班（现实中不可能的），\n");
	  Sout("一切尽在本章揭晓！");
	  things[26]=1;
	}
	  Mid_School();
	  things[26]=0;
	   }
	if (things[0]==4)
	  {
	  	if (things[26]==0)
	  	{
	  	sudu=400;
	  	cls();
	  	gotoxy(40,60);
	  	Sout("第四章");
	  	gotoxy(42,60);
	  	Sout("高考");
	  	gotoxy(41,60);
	  	Sout("Episode 4");
	  	sudu=100;
	  	gotoxy(43,60);
	  	Sout("National College Entrance Examination");
	  	gs();
	  	sudu=5;
	  	things[26]=1;
	  	}
	  	things[26]=0;
		int fen=Exa();
		gs();
	if (fen>=640)
	  {
	  	printf("	录	取	通	知	书\n");
	  	Sout("    恭喜你被白云大学录取！\n");
	  	Sout("Ftr:考得不错！白云大学可是这里最好的大学呢！");
	  	things[28]=4;
	   }
	if (fen>=545&&fen<640)
	  {
	  	printf("	录	取	通	知	书\n");
	  	Sout("    恭喜你被白云大学录取！\n");
	  	Sout("Ftr:emmmmm...还行吧，白云大学也不错。");
	  	things[28]=3;
	  }
	if (fen>=435&&fen<545)
	  {
	  	printf("	录	取	通	知	书\n");
	  	Sout("    恭喜你被白云大学录取！\n");
	  	Sout("Ftr:emmmmm...啊这，怎么考这么差？平时成绩不是挺好的嘛？白云大学是我们这儿比较差的大学哦\n"); 
	  	things[28]=2;
	  }
	if (fen>=380&&fen<435)
	  {
	  	printf("	录	取	通	知	书\n");
	  	Sout("    恭喜你被白云大学录取！\n");
	  	Sout("Ftr:欠打？考成这样还敢回家？！\n");
	  	Sout("mtr:别打，再怎么也是个大学。。。\n");
	  	things[28]=1;
	  }
	if (fen<380)
	  {
	  	Sout("Ftr:怎么考成这样，居然还敢回家？！\n");
	  	Sout("mtr:上不了大学咯~\n");
	  	gs(); 
	  }
	  things[26]=0,things[0]++;
	  }
	  if (things[0]==5)
	  {
	  	if (things[26]==0)
	  	{
	  	sudu=5;
	  	Sout("很快，四年过去了。\n");
	  	Sout("你开始小心翼翼地进入这个充满竞争的社会\n");
	  	Sout("异世界的社会不仅充满竞争，还充满怪物\n");
	  	Sout("这已经不是普通的生活了，这叫生存！");
	  	gs();
	  	things[26]=1;
	  	}
	  	things[10]+=4;
	  	sudu=400;
	  	gotoxy(40,60);
	  	Sout("第五章");
	  	gotoxy(42,60);
	  	Sout("进入社会");
	  	gotoxy(41,60);
	  	Sout("Episode 5");
	  	gotoxy(43,60);
	  	sudu=200;
	  	Sout("Step into the society");
	  	sudu=5;
	  	things[26]=1;
	  	Soc();
	  	gs();
	  	things[26]=0;
	  	}
	  	if (things[0]==6&&things[26]==0)
	  	  {
	  		sudu=400;
	  		gotoxy(40,60);
	  		Sout("第六章");
	  		gotoxy(42,60);
	  		Sout("决战");
	  		gotoxy(41,60);
	  		Sout("Episode 6");
	  		gotoxy(43,60);
	  		sudu=200;
	  		Sout("Decisive battle");
	  		sudu=5;
	  		Write_File();
	  		gs();
	  		War();
	  		things[16]=1;
	  		gs();
	  		Write_File(); 
	  		gotoxy(15,50);
	  		cout<<"_____\n";
	  		gotoxy(16,50);
	  		cout<<" \\|/\n";
	  		gotoxy(17,50);
	  		cout<<" /|\\\n";
	  		gotoxy(18,50);
	  		cout<<"-----\n";
	  		Sleep(3000);
	  		gs();
	  		Sout("你（睁开眼）：怎么了？发生甚魔事了？\n");
	  		Sout("Ftr：孩子，你醒了！今天是你6岁生日！\n");
	  		Sout("你（用手抓抓脑壳）：？？？我才6岁？我不是已经长大成人了吗？我还打败了创世神Richard！\n");
	  		Sout("Ftr（想给你一巴掌）：别乱说话！能打败MCYH的人还没出生呢！Richard，孩子不懂事，瞎说！千万不要天降神罚啊！\n");
	  		Sout("你：我还记得。。。记得。。。我用量子剑打败的他！\n");
	  		Sout("mtr：你是不是生病了？量子剑需要不少稀有材料合成，你是不是去偷隔壁WYQ的东西了？\n");
	  		Sout("你（吓了一跳）：没有没有，可能只是个梦罢了。。。\n");
	  		Sout("MCYH：过去的事情已成为过去，新的生活终将开始！");
	  		hdcj(35);
	  		gs();
	  		things[0]=1;
	  		mainmenu();
	  	  }
	  	if (things[0]==7)
	  	  {
	  	  	sudu=400;
	  		gotoxy(40,60);
	  		Sout("第\t七\t章");
	  		gotoxy(42,60);
	  		Sout("修\t仙\t之\t路");
	  		gotoxy(41,60);
	  		Sout("Episode 7");
	  		gotoxy(43,60);
	  		sudu=200;
	  		Sout("The Road Of XiuXian");//不是本人英语不行，是真的没这个词 
	  		sudu=5;
	  		Sout("剧情\n");
	  		Sout("    你早已厌倦了人间的生活，当你年满期颐、击败了创世神、闯过神殿之后，你\n");
	  		Sout("打开了当年在天空之境买的Secret Case...\n");
	  		Sout("    Case中装的是一本仙法秘籍、几件破布衣和一张地图...\n");
	  		Sout("    你顺着地图，走到了你要去的地方。从此以后，你离开了人世间，来到了神界修\n");
	  		Sout("炼。一心想着修成仙法、度过九重天劫，成为上仙...\n");
	  		Sout("    当然，这一切都被MCYH看在眼里...\n");
	  		gs(); 
	  		xiux();
		  }
		if (things[0]==8)
		  {
		  	cls();
		  	Sout("时间过得真快，你已经384级了，也通过了修炼，度过劫，RichardH即将启程前往新的平行世界了...\n");
		  	string level[3]={"仙""神","魔"};
		  	Sout("你是一个"+level[things[304]]+"，可以成为新的创世神，Richard决定让你来接替他做这个世界的创世神了...\n");
		  	Sout(name+"，你愿意做创世神吗？(Y/N)选择不愿意可以重新轮回转世成为凡人。");
		  	char l=_getch();
		  	cls();
		  	if (l=='n'||l=='N')
		  	{
		  	gotoxy(15,50);
	  		cout<<"_____\n";
	  		gotoxy(16,50);
	  		cout<<" \\|/\n";
	  		gotoxy(17,50);
	  		cout<<" /|\\\n";
	  		gotoxy(18,50);
	  		cout<<"-----\n";
	  		Sleep(3000);
	  		gs();
	  		Sout("你（睁开眼）：怎么了？发生甚魔事了？\n");
	  		Sout("Ftr：孩子，你醒了！今天是你6岁生日！\n");
	  		Sout("你（用手抓抓脑壳）：？？？我才6岁？我不是已经长大成人了吗？我还打败了创世神MCYH！我还差点成为创世神呢！\n");
	  		Sout("Ftr（想给你一巴掌）：别乱说话！能打败MCYH的人还没出生呢！MCYH，孩子不懂事，瞎说！千万不要天降神罚啊！\n");
	  		Sout("你：我还记得。。。记得。。。我度过了九重雷劫，悟得本源大道，才...\n");
	  		Sout("mtr：你是不是生病了？看样子精神出了问题\n");
	  		Sout("你（吓了一跳）：没有没有，可能只是个梦罢了。。。\n");
	  		Sout("MCYH：过去的事情已成为过去，新的生活终将开始！");
	  		hdcj(35);
	  		gs();
	  		things[0]=1,things[10]=6;
	  		mainmenu();
	  		}
	  		else
	  		{
	  			Sout("你成为了新的创世神，你作为人的一生结束了。\n");
	  			Sout("请等待Richard的人生之路1.21创世之神 \n");
	  			Sout("终");
	  			gs();
	  			things[22]=150;//眼熟吧，看看学校那一章 
	  			Write_File();
	  			exit(0);
			}
		  }
}
/*
  the end
*/ 


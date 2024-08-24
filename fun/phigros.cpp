#include <bits/stdc++.h>
#include <windows.h>
using namespace std;  // 这是为设置颜色工作的，别改，除非你知道这个的原理
struct ConsoleColor {
    WORD Value;
    ConsoleColor(WORD value) { Value = value; }
    ConsoleColor operator|(const ConsoleColor &Other) const {
        ConsoleColor result = Value;
        result.Value |= Other.Value;
        return result;
    }
    ConsoleColor operator|(const WORD &Other) const {
        ConsoleColor result = Value;
        result.Value |= Other;
        return result;
    }
};

// 支持设置的颜色（目前只有这几种，够用了）
namespace Color {
const ConsoleColor Red = FOREGROUND_RED;               // 红色
const ConsoleColor Green = FOREGROUND_GREEN;           // 绿色
const ConsoleColor Blue = FOREGROUND_BLUE;             // 蓝色
const ConsoleColor Gray = FOREGROUND_INTENSITY;        // 灰色
const ConsoleColor Yellow = Red | Green;               // 黄色
const ConsoleColor Purple = Red | Blue;                // 紫色
const ConsoleColor Aqua = Green | Blue;                // 浅蓝色
const ConsoleColor DefaultColor = Red | Green | Blue;  // 默认颜色（白色）
}  // namespace Color

// 设置颜色
// 用法1：SetColor(Color::Aqua); 这个将颜色设置为了浅蓝色，设置后打印的内容可以变色
// 用法2：cout << SetColor(Color::Green) << 内容; 同“用法1”效果但是更简便
string SetColor(const ConsoleColor &Color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color.Value);
    return "";
}

// 移动光标
// 用法1: Cur(X坐标, Y坐标); 将鼠标移动到指定位置
// 用法2: cout << Cur(X坐标, Y坐标) << 内容; 同上但是更简便。详情请看 Launch() 函数
// 注意：X 指横坐标，Y 指纵坐标
string Cur(const short &x, const short &y) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x, y });
    return "";
}

// 设置窗口标题
// 用法：SetTitle("我是标题");
void SetTitle(const LPCSTR &Name) { SetConsoleTitleA(Name); }
void SetTitle(const string &Name) { SetTitle(Name.c_str()); }

// 清屏
string Cls() {
    system("cls");
    Cur(0, 0);
    return "";
}

ConsoleColor JudgeLineColor = Color::Yellow;  // 判定线颜色

// Tips（最多两行）
vector<pair<string, string>> Tips = { { "这是一条没用的 Tip", "" },
                                      { "字体大小建议调为 14，如果屏幕太小，也可以适当调小",
                                        "* 建议的尺寸 - 1920*1080 大小 14；1600*900 大小 11；" },
                                      { "这不是控制台吗？", "" },
                                      { "这是一个普通中学的 Phigros 实验室", "过一小会，控制台突然发生崩溃" },
                                      { "PhigrOS 已崩溃", "模拟结束，感谢你的参与。愿我们在塔中重聚 [确认]" },
                                      { "florr.io", "Connecting..." },
                                      { "florr.io", "Logging in..." },
                                      { "florr.io", "Loading..." },
                                      { "florr.io", "Guest [Ready >]" },
                                      { "break over", "IN.LV14 AT.LV14" },
                                      { "狂喜蘭舞", "IN LV.14 Score 937425" } };

int jz, MaxCombo = 0, bj, HideJudgeLine = 0, NowTime, zbw[111111], pandingxianweizhi[111111];

bool IsPressed(int count, ...) {
    va_list nVirtKey;
    va_start(nVirtKey, count);
    for (int i = 0; i < count; i++) {
        if (!(GetKeyState(va_arg(nVirtKey, int)) & 0x8000)) {
            return 0;
        }
    }
    return 1;
}
struct Note {
    int wz, zt, dq = 0, startTime, lx, endTime;
    bool fuc = 0;
    char ldx, ldy;
    

} JudgeLine[101][5002];
bool ok[27];
void gd() {
    //	system("start Phigros Introduction.m4a");<--不用这种方法
    while (1) {
        Sleep(10);
        //len++;
        for (int i = 0; i < 26; i++) {
            if (!IsPressed(1, 'A' + i)) {
                ok[i] = 1;
            }
        }
    }
}

bool pd(bool ty) { return ok[ty]; }

void Introduction();

void zt() {
    while (1) {
        Sleep(50);
        Cls();
        Cur(113, 25);
        cout << "暂停中";
        Cur(113, 26);
        cout << "< c> |>";
        Cur(113, 27);
        cout << "1 2  3";
        if (IsPressed(1, '1')) {
            Cls();
            exit(0);
        }
        if (IsPressed(1, '2')) {
            Introduction();
        }
        if (IsPressed(1, '3')) {
            break;
        }
    }
}

void pand(int y, int gq, int dq, int j) {
    for (int k = 1; k <= 234; k++) {
        for (int i = dq; i <= min(dq + 60, gq); i++) {
            if ((JudgeLine[y][i].startTime - NowTime <= j && JudgeLine[y][i].endTime - NowTime >= j) &&
                JudgeLine[y][i].wz == k && JudgeLine[y][i].zt == 0) {
                if (j == JudgeLine[y][i].startTime - NowTime) {
                    if (JudgeLine[y][i].lx == 1) {
                        cout << SetColor(Color::Yellow) << Cur(k, 52 - j)
                             << "-----------------------------------" << SetColor(Color::DefaultColor);
                    }
                    if (JudgeLine[y][i].lx == 0) {
                        cout << SetColor(Color::Aqua) << Cur(k, 52 - j)
                             << "<=================================>" << SetColor(Color::DefaultColor);
                    }
                    if (JudgeLine[y][i].lx == 2) {
                        cout << SetColor(Color::Red) << Cur(k, 52 - j)
                             << "<================/\\/================>" << SetColor(Color::DefaultColor);
                    }
                    if (j >= 0 && JudgeLine[y][i].lx == 3) {
                        cout << SetColor(Color::Aqua) << Cur(k, 52 - j)
                             << "\\------------------------------------/" << SetColor(Color::DefaultColor);
                    }
                } else if (j >= 0 && j == JudgeLine[y][i].endTime - NowTime) {
                    cout << SetColor(Color::Aqua) << Cur(k, 52 - j)
                         << "/------------------------------------\\" << SetColor(Color::DefaultColor);
                } else if (j >= 0) {
                    cout << SetColor(Color::Aqua) << Cur(k, 52 - j)
                         << "|                                    |" << SetColor(Color::DefaultColor);
                }
                k += 35;
            }
            if ((JudgeLine[y][i].startTime - NowTime == j && j == 1) && JudgeLine[y][i].wz == k &&
                JudgeLine[y][i].zt == 3) {
                Cur(k, 52 - j);
                cout << "Perfect";
            }
            if ((JudgeLine[y][i].startTime - NowTime == j && j == 1) && JudgeLine[y][i].wz == k &&
                JudgeLine[y][i].zt == 2) {
                Cur(k, 52 - j);
                cout << "Good";
            }
        }
    }
}

void Introduction() {
    thread tims(gd);
    NowTime = 0;
    int Perfect = 0, Good = 0, Miss = 0, dq = 0, ComboCount = 0;
    while (1) {
        Cur(0, 0);
        Sleep(20);
        NowTime++;
        Cls();
        for (int i = 0; i < 100; i++) {
            if (JudgeLine[0][i].lx == 3 &&
                JudgeLine[0][i].endTime <= NowTime + pandingxianweizhi[JudgeLine[0][i].startTime]) {
                if (JudgeLine[0][i].fuc == 0) {
                    if (JudgeLine[0][i].dq == 3) {
                        Perfect++;
                    }
                    if (JudgeLine[0][i].dq == 2) {
                        if (JudgeLineColor.Value != Color::DefaultColor.Value) {
                            JudgeLineColor = Color::Aqua;
                        }
                        Good++;
                    }
                    JudgeLine[0][i].zt = JudgeLine[0][i].dq;
                    JudgeLine[0][i].fuc = 1;
                    ComboCount++;
                }
            }
            if (JudgeLine[0][i].endTime <= NowTime - 9 + pandingxianweizhi[JudgeLine[0][i].startTime] &&
                JudgeLine[0][i].zt == 0) {
                JudgeLineColor = Color::DefaultColor;
                Miss++;
                ComboCount = 0;
                JudgeLine[0][i].zt = 1;
            } else if (JudgeLine[0][i].zt == 2 || JudgeLine[0][i].zt == 3) {
                JudgeLine[0][i].zt = 1;
            } else if (JudgeLine[0][i].zt == 1) {
                continue;
            } else {
                dq = i;
                break;
            }
        }
        //		int yl = dq;
        bool biaoji = 0, tongpaipand = 0;
        for (int j = 0; j < 100; j++) {
            for (int i = 0; i < 26; i++) {
                jz = i;
                if (IsPressed(1, i + 'A')) {
                    if (i + 'A' == 'Z') {
                        if (bj == 30) {
                            zt();
                        }
                        bj++;
                    }
                    if (JudgeLine[0][j].startTime != JudgeLine[0][j - 1].startTime && tongpaipand == 1) {
                        biaoji = 1;
                        break;
                    }
                    if ((JudgeLine[0][j].ldx == i + 'A' || JudgeLine[0][j].ldy == i + 'A') &&
                        JudgeLine[0][j].zt == 0) {
                        if (JudgeLine[0][j].lx == 1) {
                            if (JudgeLine[0][j].startTime <=
                                    NowTime + 2 + pandingxianweizhi[JudgeLine[0][i].startTime] &&
                                JudgeLine[0][j].startTime >=
                                    NowTime - 2 + pandingxianweizhi[JudgeLine[0][i].startTime]) {
                                Perfect++;
                                tongpaipand = 1;
                                ComboCount++;
                                JudgeLine[0][j].zt = 3;
                                break;
                            }
                        }
                        if (JudgeLine[0][j].lx == 2) {
                            if (JudgeLine[0][j].startTime <=
                                    NowTime + 2 + pandingxianweizhi[JudgeLine[0][i].startTime] &&
                                JudgeLine[0][j].startTime >=
                                    NowTime - 2 + pandingxianweizhi[JudgeLine[0][i].startTime] &&
                                (IsPressed(1, 'Q') || IsPressed(1, 'W') || IsPressed(1, 'E') ||
                                 IsPressed(1, 'R') || IsPressed(1, 'T') || IsPressed(1, 'Y') ||
                                 IsPressed(1, 'U') || IsPressed(1, 'I') || IsPressed(1, 'O') ||
                                 IsPressed(1, 'P'))) {
                                Perfect++;
                                tongpaipand = 1;
                                ComboCount++;
                                JudgeLine[0][j].zt = 3;
                                break;
                            }
                        }
                        if (JudgeLine[0][j].lx == 0 && pd(i)) {
                            if (JudgeLine[0][j].startTime <=
                                    NowTime + 3 + pandingxianweizhi[JudgeLine[0][i].startTime] &&
                                JudgeLine[0][j].startTime >=
                                    NowTime - 2 + pandingxianweizhi[JudgeLine[0][i].startTime]) {
                                Perfect++;
                                tongpaipand = 1;
                                ComboCount++;
                                JudgeLine[0][j].zt = 3;
                                break;
                            } else if (JudgeLine[0][j].startTime <=
                                           NowTime + 5 + pandingxianweizhi[JudgeLine[0][i].startTime] &&
                                       JudgeLine[0][j].startTime >=
                                           NowTime - 4 + pandingxianweizhi[JudgeLine[0][i].startTime]) {
                                if (JudgeLineColor.Value != Color::DefaultColor.Value) {
                                    JudgeLineColor = Color::Aqua;
                                }
                                Good++;
                                tongpaipand = 1;
                                ComboCount++;
                                JudgeLine[0][j].zt = 2;
                                break;
                            }
                        }
                        if (JudgeLine[0][j].lx == 3) {
                            if (JudgeLine[0][j].dq == 0) {
                                if (JudgeLine[0][j].startTime <=
                                        NowTime + 2 + pandingxianweizhi[JudgeLine[0][i].startTime] &&
                                    JudgeLine[0][j].startTime >=
                                        NowTime - 2 + pandingxianweizhi[JudgeLine[0][i].startTime]) {
                                    JudgeLine[0][j].dq = 3;
                                } else if (JudgeLine[0][j].startTime <=
                                               pandingxianweizhi[JudgeLine[0][i].startTime] + 4 &&
                                           JudgeLine[0][j].startTime >=
                                               pandingxianweizhi[JudgeLine[0][i].startTime] - 4) {
                                    JudgeLine[0][j].dq = 2;
                                } else if (JudgeLine[0][j].startTime <=
                                           pandingxianweizhi[JudgeLine[0][i].startTime] - 8) {
                                    JudgeLine[0][j].zt = 1;
                                    JudgeLine[0][j].fuc = 1;
                                    JudgeLine[0][j].dq = 1;
                                    JudgeLineColor = Color::DefaultColor;
                                    Miss++;
                                }
                            }
                        }
                    }
                } else if ((JudgeLine[0][j].ldx == i + 'A' || JudgeLine[0][j].ldy == i + 'A') &&
                           JudgeLine[0][j].lx == 3) {
                    if (JudgeLine[0][j].endTime <= pandingxianweizhi[JudgeLine[0][i].startTime] + 4 &&
                        JudgeLine[0][j].fuc == 0) {
                        JudgeLineColor = Color::DefaultColor;
                        Miss++;
                        JudgeLine[0][j].fuc = 1;
                    }
                } else if (i + 'A' == 'Z') {
                    bj = 0;
                }
            }
            if (biaoji) {
                break;
            }
        }
        for (int j = 51; j >= -9; j--) {
            MaxCombo = max(MaxCombo, ComboCount);
            if (j == 51) {
                cout << SetColor(Color::DefaultColor) << "| |";
                Cur(0, 60);
                cout << SetColor(Color::DefaultColor) << "Introduction";
                Cur(227, 60);
                cout << SetColor(Color::DefaultColor) << "EZ LV.3";
                HideJudgeLine = 0;
            }
            if (NowTime <= 70) {
                Cur(77, max(71 - NowTime * NowTime / 5, 31));
                cout << SetColor(Color::Aqua)
                     << "欢迎来到 Phigros！此教程会带你了解 Phigros 的玩法与 Phigros 和 控制台版 的差异"
                     << SetColor(Color::DefaultColor);
            }
            if (NowTime <= 100) {
                Cur(0, 1);
                cout << SetColor(Color::DefaultColor) << "长按 Z 即可暂停";
                Cur(222, 1);
                cout << SetColor(Color::DefaultColor) << "这是你的得分";
                Cur(0, 59);
                cout << SetColor(Color::DefaultColor) << "左下角是歌曲名称";
                Cur(218, 59);
                cout << SetColor(Color::DefaultColor) << "右下角是歌曲等级";
                HideJudgeLine = 1;
            }
            if (NowTime >= 70 && NowTime <= 150) {
                Cur(77, 31);
                cout << SetColor(Color::Aqua) << "<=================================>  "
                     << SetColor(Color::DefaultColor) << "这是 Tap，在它到达判定线时点击它对应的键。"
                     << SetColor(Color::DefaultColor);
                HideJudgeLine = 1;
            }
            if (NowTime >= 360 && NowTime <= 570) {
                Cur(48, 31);
                cout << SetColor(Color::Yellow) << "-----------------------------------  "
                     << SetColor(Color::DefaultColor)
                     << "这是 Drag，与判定线接触时按下对应的键以接住它，Drag "
                        "通常会大量出现，只需按住对应键即可"
                     << SetColor(Color::DefaultColor);
                HideJudgeLine = 1;
            }
            if (NowTime >= 880 && NowTime <= 1130) {
                Cur(61, 31);
                cout << SetColor(Color::Red) << "<================/\\/==============>  "
                     << SetColor(Color::DefaultColor)
                     << "这是 Flick，在它到判定线时保持按下它对应的键及保持按下键盘第一行的任意键。"
                     << SetColor(Color::DefaultColor);
                HideJudgeLine = 1;
            }
            if (NowTime >= 1280 && NowTime <= 1360) {
                cout << SetColor(Color::Aqua) << Cur(75, 31) << "/------------------------------------\\  "
                     << SetColor(Color::DefaultColor) << "这是Hold,在他到判定线时点击它直到它消失。"
                     << SetColor(Color::DefaultColor) << endl;
                cout << SetColor(Color::Aqua) << Cur(75, 32) << "|                                    |"
                     << endl
                     << SetColor(Color::DefaultColor);
                cout << SetColor(Color::Aqua) << Cur(75, 33) << "|                                    |"
                     << endl
                     << SetColor(Color::DefaultColor);
                cout << SetColor(Color::Aqua) << Cur(75, 34) << "|                                    |"
                     << endl
                     << SetColor(Color::DefaultColor);
                cout << SetColor(Color::Aqua) << Cur(75, 35) << "\\------------------------------------/"
                     << endl
                     << SetColor(Color::DefaultColor);
                HideJudgeLine = 1;
            }
            if (NowTime >= 1530 && NowTime <= 1730) {
                cout << Cur(75, 31) << SetColor(Color::Green) << "现在让我们把这些结合起来"
                     << SetColor(Color::DefaultColor) << endl;
                HideJudgeLine = 1;
            }
            if (j == 51 && ComboCount >= 3) {
                int ls = ComboCount, len = 0;
                while (ls >= 1) {
                    ls /= 10;
                    len++;
                }
                Cur(118 - (len - 1) / 2, 1);
                cout << ComboCount;
            }
            if (j == 51) {
                Cur(228, 0);
                int df = Perfect * 9 * pow(10, 5) * 1.0 / 100 + Good * 9 * pow(10, 5) * 1.0 / 100 * 0.65 +
                         MaxCombo * pow(10, 5) * 1.0 / 100;
                int ls = df, len = 6;
                if (df == 0) {
                    len--;
                }
                while (ls >= 1) {
                    ls /= 10;
                    len--;
                }
                for (int k = 1; k <= len; k++) {
                    cout << " ";
                }
                cout << df;
            }
            if (j == 50 && ComboCount >= 3) {
                Cur(114, 2);
                cout << "C O M B O";
            }
            if (HideJudgeLine) {
                continue;
            }
            if (j == 0) {
                Cur(0, 52 - pandingxianweizhi[NowTime]);
                cout << SetColor(JudgeLineColor)
                     << "-------------------------a-------------------------s-------------------------d------"
                        "-------------------f-------------------------g-------------------------h------------"
                        "-------------j-------------------------k--------------------------"
                     << SetColor(Color::DefaultColor) << endl;
                continue;
            }
            pand(0, 100, dq - 10, j);
        }
    }
}

void Launch() {
    srand(time(NULL));
    SetColor(Color::DefaultColor);
    cout << Cur(70, 25) << "■■■■■■    ■             ■    ■■■■■■   ■     ■   ■■■■■■     ■■■■■■" << endl;
    cout << Cur(70, 26) << "■        ■    ■                   ■        ■   ■   ■     ■        ■     ■"
         << endl;
    cout << Cur(70, 27) << "■        ■    ■             ■    ■        ■   ■ ■       ■        ■     ■" << endl;
    cout << Cur(70, 28) << "■        ■    ■             ■    ■        ■   ■■        ■        ■     ■" << endl;
    cout << Cur(70, 29) << "■■■■■■    ■■■■■■   ■    ■■■■■■   ■          ■        ■     ■■■■■■" << endl;
    cout << Cur(70, 30)
         << "■              ■        ■   ■              ■   ■          ■        ■               ■" << endl;
    cout << Cur(70, 31)
         << "■              ■        ■   ■              ■   ■          ■        ■               ■" << endl;
    cout << Cur(70, 32)
         << "■              ■        ■   ■              ■   ■          ■        ■               ■" << endl;
    cout << Cur(70, 33) << "■              ■        ■   ■    ■■■■■■   ■          ■■■■■■     ■■■■■■" << endl;
    int TipIndex = rand() % Tips.size();
    cout << Cur(70, 35) << "Tip: " << SetColor(Color::Yellow) << Tips[TipIndex].first;
    cout << Cur(70, 36) << SetColor(Color::Yellow) << Tips[TipIndex].second;
    cout << Cur(107, 38) << SetColor(Color::Aqua) << ">>> 单击 " << SetColor(Color::Green) << "Q"
         << SetColor(Color::Aqua) << " 开始 <<<" << SetColor(Color::DefaultColor);
    while (1) {
        if (IsPressed(1, 'Q')) {
            Cls();
            Introduction();
            break;
        }
    }
}

double fzt[1145] = {
    10,   14,   18,   18,   32,   32.5, 33,   33.5, 34, 37, 37.5, 38,   38.5, 39,   42, 42.5,
    42,   42.5, 60,   62,   64,   72,   74,   76,   76, 90, 90.2, 90.4, 90.6, 90.8, 92, 92.2,
    92.4, 92.6, 92.8, 93.2, 93.6, 94,   94.6, 95,   96, 96, 96.3, 96.3, 96.6, 96.6
};  //碰到判定线起始时间
double zzt[1145] = { 10,   14, 18,   18,   32,   32.5, 33,   33.5, 34,   37,   37.5, 38,
                     38.5, 39, 42,   42.5, 42,   42.5, 60,   62,   64,   73,   75,   76.5,
                     76.5, 90, 90.2, 90.4, 90.6, 90.8, 92,   92.2, 92.4, 92.6, 92.8, 93.2,
                     93.6, 94, 94.6, 95.5, 96,   96,   96.3, 96.3, 96.6, 96.6 };
int lxt[1145] = { 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3,
                  3, 3, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0 };
char ldw[1145] = { 'F', 'F', 'D', 'H', 'F', 'F', 'F', 'F', 'F', 'H', 'H', 'H', 'H', 'H', 'D', 'D',
                   'H', 'H', 'F', 'F', 'F', 'F', 'F', 'D', 'H', 'D', 'D', 'D', 'F', 'F', 'H', 'H',
                   'H', 'G', 'G', 'G', 'D', 'G', 'D', 'F', 'D', 'G', 'D', 'G', 'D', 'G' };
char ldk[1145] = { 'F', 'F', 'D', 'H', 'F', 'F', 'G', 'G', 'G', 'H', 'H', 'H', 'H', 'G', 'D', 'D',
                   'H', 'H', 'F', 'F', 'F', 'F', 'F', 'D', 'H', 'D', 'D', 'F', 'F', 'G', 'H', 'H',
                   'G', 'G', 'F', 'G', 'D', 'G', 'D', 'F', 'D', 'G', 'D', 'G', 'D', 'G' };
int wzx[1145] = { 89,  89,  63,  139, 87, 91,  95, 99, 103, 141, 137, 133, 129, 125, 63,  62,
                  139, 139, 89,  89,  89, 89,  89, 63, 139, 63,  72,  81,  90,  99,  141, 132,
                  123, 114, 105, 105, 72, 105, 72, 89, 63,  115, 63,  115, 63,  115 };
double pdxqs[1145] = { 90,   90.1, 90.2, 90.3, 90.4, 90.5, 90.6, 90.7, 90.8,
                       90.9, 91.1, 91.2, 91.3, 91.4, 91.5, 91.6, 91.7, 91.8 };
double pdxzj[1145] = { 90.1, 90.2, 90.3, 90.4, 90.5, 90.6, 90.7, 90.8, 90.9,
                       91.1, 91.2, 91.3, 91.4, 91.5, 91.6, 91.7, 91.8, 91.9 };
double pdxwz[1145] = { 1, 2, 3, 2, 1, 2, 3, 2, 1, 1, 2, 3, 2, 1, 2, 3, 2, 1 };
int main() {
    system("mode con cols=234 lines=63");
    SetTitle("Phigros");
    for (int i = 0; i < 100; i++) {
        JudgeLine[0][i].startTime = fzt[i] * 20;
        JudgeLine[0][i].endTime = zzt[i] * 20;
        JudgeLine[0][i].zt = 0;
        JudgeLine[0][i].lx = lxt[i];
        JudgeLine[0][i].wz = wzx[i];
        JudgeLine[0][i].ldx = ldw[i];
        JudgeLine[0][i].ldy = ldk[i];
    }
    int len = 0;
    for (int i = 0; i < 100000; i++) {
        if (i >= pdxqs[len] * 20 && i <= pdxzj[len] * 20) {
            pandingxianweizhi[i] = pdxwz[len];
        } else {
            if (i > pdxzj[len] * 20) {
                len++;
                i--;
                continue;
            }
            pandingxianweizhi[i] = 0;

        }
    }
    Launch();
    return 0;
}
#define 我开始审视这个妹子，心中想到 how_sad = false;
#define 那真是个悲伤的故事 how_sad = true;
#define 拿下这个妹子就多个妹子陪 (dp[j][k] < dp[j - money_cost[i]][k - rp_cost[i]] + 1)
#define 这个妹子比前面那个省事 (dp[j][k] == dp[j - money_cost[i]][k - rp_cost[i]] \
                    && tme[j][k] > tme[j - money_cost[i]][k - rp_cost[i]] + time_cost[i]) 
#define 如果 if
#define 而且 &&
#define 或者 ||
#define 我 (
#define 的话 )
#define 没钱没人品  j < money_cost[i] || k < rp_cost[i]
#define 有钱而且有人品 (!how_sad)
#define 那我就 ){
#define 推倒她 dp[j][k] = dp[j - money_cost[i]][k - rp_cost[i]] + 1; \
                        tme[j][k] = tme[j - money_cost[i]][k - rp_cost[i]] + time_cost[i];
#define 的说 }
#define 如果推倒她并没有什么用 else
#define 那我管她呢 dp[j][k] = dp[j][k], tme[j][k] = tme[j][k];

#include<iostream>
using namespace std;
#define MAX_GIRLS 101
int money_cost[MAX_GIRLS], rp_cost[MAX_GIRLS], time_cost[MAX_GIRLS];
int my_money, my_rp;
int dp[MAX_GIRLS][MAX_GIRLS],tme[MAX_GIRLS][MAX_GIRLS];

int main() {
    int girls; cin >> girls;
    for (int i = 1; i <= girls; i++)
        cin
        >> money_cost[i]
        >> rp_cost[i]
        >> time_cost[i];
    cin >> my_money >> my_rp;
    bool how_sad;
    for (int i = 1; i <= girls; i++)
        for (int j = my_money; j>0; j--)
            for (int k = my_rp; k > 0; k--) {
                我开始审视这个妹子，心中想到
                如果 我 没钱没人品 的话
                那真是个悲伤的故事
                如果 我 有钱而且有人品 而且 我 
                拿下这个妹子就多个妹子陪 
                或者 这个妹子比前面那个省事 的话
                那我就 推倒她 的说
                如果推倒她并没有什么用
                那我管她呢
            }
    cout << tme[my_money][my_rp];
}
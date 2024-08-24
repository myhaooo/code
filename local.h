#ifdef getchar() getchar_unlocked()
#undef getchar()
#define getchar() _getchar_nolock()
#endif
#ifdef getchar getchar_unlocked
#undef getchar
#define getchar _getchar_nolock
#endif
#ifdef putchar() putchar_unlocked()
#undef putchar()
#define putchar() _putchar_nolock()
#endif
#ifdef putchar putchar_unlocked
#undef putchar
#define putchar _putchar_nolock
#endif


//席嘉佳想要变得可可爱爱~

#include <iostream>
#include <cmath>
#include <string>
#include <random>

#define 整数类型的 int //席嘉佳不喜欢#typedef呢~
#define 比较短的整数类型的 short
#define 比较长的整数类型的 long
#define 比较不好用的浮点类型的 float //总之就是席嘉佳不喜欢啦！哼！
#define 浮点类型的 double //席嘉佳想要用这个呢~
#define 逻辑类型的 bool
#define 真 true
#define 假 false
#define 席嘉佳想要先执行一下这段代码呢 do {
#define 这段代码要在 } while (
#define 的时候一直循环呢 );
#define 席嘉佳想要让下面这段代码在 while (
#define 时一直循环呢，这段代码是这样的 ){
#define 这个程序将从这里开始哟 int main(){
#define 返回 return
#define 这个程序将在这里结束哟 return 0 ; }
#define 输出 std::cout <<
#define 输入 std::cin >>
#define 了 << std::endl
#define 了哟 << std::endl;
#define ，以及 <<
#define 的值为 =
#define 被声明好了，先让它的初始值为 =
#define 加 +
#define 减 -
#define 乘 *
#define 除以 /
#define 余 %
#define 席嘉佳想要手动关闭这个程序 std::cin.get()
#define 呀 ;
#define 吧 ;
#define 单精度浮点类型的 float
#define 如果 if (
#define ，那么 ){
#define ，否则 } else {
#define ，或者如果 } else if (
#define 搞定了呢！ }
#define 就这样说好了哟！ } 
#define 检查一下 switch (
#define 的值 ){
#define 当被检查的对象是 case
#define 的时候 :
#define 好的，就这样吧 break;
#define 要是还是不行的话，我觉得可以 default :
#define 这个地址的指针指向了 &
#define 指针形态的 *
#define 没有负数的 unsigned
#define 量测对象大小 sizeof
#define 的格式为固定小数位数 fixed
#define 让 for(
#define 并且当 ;
#define 时执行循环，此外还应该在每次循环重复时，通过不断  ;
#define 自增变量 ++
#define 自减变量 --
#define 来使循环发生变化，循环的内容为 ){
#define 字符类型的 char
#define 字符串类型的 string
#define 宽字符类型的 wchar_t
#define 并且 &&
#define 不是 !
#define 或者 ||
#define 被声明好啦 ;
#define 小于 <
#define 大于 >
#define 等于 ==
#define 小于等于 <=
#define 大于等于 >=
#define 不等于 !=
#define 使用std命名空间 using namespace std;
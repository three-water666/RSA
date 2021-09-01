#include "Bigint.h"


Bigint BigRand(int bytes); //生成位数为 8*bytes 的随机数
Bigint BigRandOdd(int bytes); //生成位数为 8*bytes 的随机奇数
Bigint BigRand(Bigint n); //生成[0, n)内的随机数
Bigint2 BigRand(Bigint2 n); //生成[0, n)内的随机数
bool MillerRabinKnl(Bigint &n); //单次 Miller-Rabin 检测，通过返回 1，否则返回 0
bool MillerRabin(Bigint & n, int loop); //多次 Miller-Rabin 检测，通过返回 1，否则返回 0
Bigint GenPrime(int bytes); //生成位数为 8*bytes 的素数
void Print10(Bigint a);
void Print10(Bigint2 a);





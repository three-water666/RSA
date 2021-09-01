#include<stdio.h>
#include<time.h>
#include<iostream>

#include "Bigprime.h"

using namespace std;

Bigint BigRand(int bytes) //生成位数为 8*bytes 的随机数
{
	Bigint res = { 0 };
	for (int i = 0; i < bytes - 1; i++)
	{
		res.num[i] = rand() % 256; //每个字节都取成[0, 255]内随机数
	}
	res.num[bytes - 1] = 128 + rand() % 128; //最高位取成 1
	return res;
}

//生成位数为 8*bytes 的随机奇数
Bigint BigRandOdd(int bytes)
{
	//初始化一个零大数
	Bigint res = { 0 };
	//随机一个大数
	for (int i = 0; i < bytes - 1; i++)
	{
		res.num[i] = rand() % 256;
	}

	res.num[bytes - 1] = 128 + rand() % 128; //最高位取成 1
	//奇数化
	if (!(res.num[0] & 0x01)) res.num[0] = res.num[0] + 1; //若为偶数，则加 1 成为奇数
	return res;
}

Bigint BigRand(Bigint n) //生成[0, n)内的随机数
{
	Bigint res = { 0 };
	for (int i = 0; i < SIZE; i++)
	{
		res.num[i] = rand() % 256; //每个字节都取成[0, 255]内随机数
	}
	res = Mod(res, n); //利用求模函数使其落到[0, n)中
	return res;
}

Bigint2 BigRand(Bigint2 n) //生成[0, n)内的随机数
{
	Bigint2 res = { 0 };
	for (int i = 0; i < SIZE*2; i++)
	{
		res.num[i] = rand() % 256; //每个字节都取成[0, 255]内随机数
	}
	res = Mod(res, n); //利用求模函数使其落到[0, n)中
	return res;
}

//单次 Miller-Rabin 检测，通过返回 1，否则返回 0
// 米勒-拉宾素性检验
bool MillerRabinKnl(Bigint &n)
{
	Bigint b, m, v, temp;
	Bigint j = { 0 };
	Bigint one = { 1 };
	Bigint two = { 2 };
	Bigint three = { 3 };
	//m=n-1
	m = Sub(n, one);
	//Print(m);
	//1.首先将n-1分解为m*(2^j)
	while (!(m.num[0] & 0x01)) //计算 m,j,使得 n-1 = m*(2^j)
	{
		//Print(m);
		//j从0开始加
		j = Add(j, one);
		BitMoveRight(m);
		//Print(m);
		//cout << Length(m);
	}
	//m是奇数，随机选取 b 属于[2, N-1]
	b = Add(two, BigRand(Sub(n, three)));
	//2.b^m mod n == 1
	v = PowMod(b, m, n); //计算 v=b^m mod n
	if (Compare(v, one) == 0) return 1; //若 v=1，通过测试
	Bigint i = { 1 };
	temp = Sub(n, one);
	//3. b^((2^i)*m) mod n == -1
	while (Compare(v, temp) < 0) //若 v < n - 1,不通过
	{
		if (Compare(i, j) == 0) return 0; //若 i = j, 是合数，不通过
		v = MulMod(v, v, n); //v = v^2 mod n, i = i + 1
		i = Add(i, one);
	}
	return 1; //若 v = n - 1,通过检测
}

// 多次 Miller-Rabin 检测
bool MillerRabin(Bigint & n, int loop) //多次 Miller-Rabin 检测，通过返回 1，否则返回 0
{
	for (int i = 0; i < loop; i++)
	{
		//单次Miller-Rabin 检测 
		if (!MillerRabinKnl(n)) return 0;
	}
	return 1;
}

Bigint GenPrime(int bytes) //生成位数为 8*bytes 的素数
{
	//随机种子
	srand((unsigned int)time(0));
	//先获得一个随机大奇数
	Bigint res = BigRandOdd(bytes);
	int loop = 20;
	//多次Miller-Rabin 检测，如果没过，重生成一个大奇数
	while (!MillerRabin(res, loop))
	{
		res = BigRandOdd(bytes);
	}
	//返回大素数
	return res;
}

void Print10(Bigint a)
{
	char num[60];
	Bigint ten = { 10 };
	Bigint b = a;
	int i = 0;
	while (Length(b))
	{
		num[i] = Mod(b, ten).num[0];
		b = Div(b, ten);
		i++;
	}

	for(i--;i>=0;i--)
	{
		printf("%d", num[i]);
	}

	printf("\n");
}

void Print10(Bigint2 a)
{
	char num[150];
	Bigint2 ten = { 10 };
	Bigint2 b = a;
	int i = 0;
	while (Length(b))
	{
		num[i] = Mod(b, ten).num[0];
		b = Div(b, ten);
		i++;
	}

	for(i--;i>=0;i--)
	{
		printf("%d", num[i]);
	}

	printf("\n");
}

// int main()
// {
// 	Print10(GenPrime(16));
// }



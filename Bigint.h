#pragma once
#define SIZE 33
typedef struct Bigint
{
	//数组大小为17bytes，1bytes为8bits
	unsigned char num[SIZE];
}Bigint;

typedef struct Bigint2
{
	unsigned char num[SIZE * 2];
}Bigint2;

typedef struct Bigint4
{
	unsigned char num[SIZE * 4];
}Bigint4;

Bigint Init(unsigned char a[], int length); //初始化
void Print(Bigint a); //打印输出
void Copy(Bigint &a, Bigint b); //拷贝
void Copy(Bigint2 &a, Bigint2 b); //拷贝
int Length(Bigint a); //计算数组长度
int Length(Bigint2 a);
int Compare(Bigint a, Bigint b); //比较大小
int Compare(Bigint2 a, Bigint2 b);
Bigint ByteMoveLeft(Bigint a, int loop); //左移 loop 个字节
Bigint2 ByteMoveLeft(Bigint2 a, int loop);
void BitMoveRight(Bigint &a); //右移一个比特
void BitMoveRight(Bigint2 &a); //右移一个比特
Bigint2 Extend(Bigint a); //扩充数组
Bigint Narrow(Bigint2 a); //截断数组
Bigint Add(Bigint a, Bigint b); //加法
Bigint2 Add(Bigint2 a, Bigint2 b); //加法
Bigint Sub(Bigint a, Bigint b); //减法
Bigint2 Sub(Bigint2 a, Bigint2 b);//乘法
Bigint2 Mul(Bigint a, Bigint b);
Bigint4 Mul(Bigint2 a, Bigint2 b);
Bigint Div(Bigint a, Bigint b); //除法
Bigint2 Div(Bigint2 a, Bigint2 b); //除法
Bigint Mod(Bigint a, Bigint b); //求余
Bigint2 Mod(Bigint2 a, Bigint2 b);
Bigint AddMod(Bigint a, Bigint b, Bigint n); //模加
Bigint SubMod(Bigint a, Bigint b, Bigint n); //模减
Bigint Sub2Mod(Bigint a, Bigint b, Bigint n);
Bigint2 Sub2Mod(Bigint2 a, Bigint2 b, Bigint2 n);
Bigint MulMod(Bigint a, Bigint b, Bigint n); //模乘
Bigint2 MulMod(Bigint2 a, Bigint2 b, Bigint2 n); //模乘
Bigint PowMod(Bigint a, Bigint b, Bigint n); //模幂
Bigint2 PowMod(Bigint2 a, Bigint2 b, Bigint2 n); //模幂
bool Inverse(Bigint e, Bigint N, Bigint &d);
bool Inverse(Bigint2 e, Bigint2 N, Bigint2 &d);
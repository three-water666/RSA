#include<stdio.h>
#include<string>
#include<iostream>

#include "Bigint.h"

using namespace std;

int Length(Bigint a)
{
	for (int i = SIZE - 1; i >= 0; i--)
	{
		if (a.num[i] != 0)
		{
			return i + 1;
		}
	}
	return 0;
}

int Length(Bigint2 a)
{
	for (int i = 2 * SIZE - 1; i >= 0; i--)
	{
		if (a.num[i] != 0)
		{
			return i + 1;
		}
	}
	return 0;
}

Bigint Narrow(Bigint2 a)
{
	Bigint temp;
	for (int i = 0; i < SIZE; i++)
	{
		temp.num[i] = a.num[i];
	}
	return temp;
}

Bigint Add(Bigint a, Bigint b)
{
	Bigint c;
	unsigned short temp;
	unsigned char carry = 0;
	for (int i = 0; i < SIZE; i++)
	{
		temp = a.num[i] + b.num[i] + carry;
		c.num[i] = temp & 0x00ff;;
		carry = (temp >> 8) & 0xff;
	}
	return c;
}

Bigint2 Add(Bigint2 a, Bigint2 b)
{
	Bigint2 c;
	unsigned short temp;
	unsigned char carry = 0;
	for (int i = 0; i < SIZE*2; i++)
	{
		temp = a.num[i] + b.num[i] + carry;
		c.num[i] = temp & 0x00ff;;
		carry = (temp >> 8) & 0xff;
	}
	return c;
}

int Compare(Bigint a, Bigint b)
{
	int a_len = Length(a);
	int b_len = Length(b);
	int max;
	if (a_len > b_len) max = a_len;
	else max = b_len;
	if (max == 0) return 0;
	else
	{
		for (int i = max - 1; i >= 0; i--)
		{
			if (a.num[i] > b.num[i]) return 1;
			if (a.num[i] < b.num[i]) return -1;
		}
	}
	return 0;
}


int Compare(Bigint2 a, Bigint2 b)
{
	int a_len = Length(a);
	int b_len = Length(b);
	int max;
	if (a_len > b_len) max = a_len;
	else max = b_len;
	if (max == 0) return 0;
	else
	{
		for (int i = max - 1; i >= 0; i--)
		{
			if (a.num[i] > b.num[i]) return 1;
			if (a.num[i] < b.num[i]) return -1;
		}
	}
	return 0;
}


Bigint Sub(Bigint a, Bigint b)
{
	if (Compare(a, b)== -1)
	{
		cout << "subtract error" << endl;
		return a;
	}
	Bigint c;
	short temp; //定义临时差
	unsigned char carry = 0; //定义借位
	for (int i = 0; i < SIZE; i++)
	{
		temp = (a.num[i] - b.num[i]) - carry;
		c.num[i] = temp & 0x00ff; //每字节减法结果
		carry = (temp >> 15) & 0x01; // 记录借位
	}
	return c;
}

Bigint2 Sub(Bigint2 a, Bigint2 b)
{
	if (Compare(a, b) == -1)
	{
		cout << "subtract error" << endl;
		return a;
	}
	Bigint2 c;
	short temp; //定义临时差
	unsigned char carry = 0; //定义借位
	for (int i = 0; i < 2*SIZE; i++)
	{
		temp = (a.num[i] - b.num[i]) - carry;
		c.num[i] = temp & 0x00ff; //每字节减法结果
		carry = (temp >> 15) & 0x01; // 记录借位
	}
	return c;
}

Bigint2 Mul(Bigint a, Bigint b)
{
	Bigint2 c = { 0 };
	unsigned short temp;
	unsigned char carry;
	for (int i = 0; i < SIZE; i++)
	{
		carry = 0;
		for (int j = 0; j < SIZE; j++)
		{
			temp = a.num[i] * b.num[j] + c.num[i + j] + carry;
			c.num[i + j] = temp & 0x00ff;
			carry = (temp >> 8) & 0xff;
		}
	}
	c.num[2 * SIZE - 1] = carry;
	return c;
}


Bigint ByteMoveLeft(Bigint a, int loop)
{
	for (int i = Length(a) - 1; i >= 0; i--)
	{
		if (i + loop >= SIZE) continue;
		a.num[i + loop] = a.num[i];
	}
	for (int i = loop - 1; i >= 0; i--) a.num[i] = 0;
	return a;
}

Bigint2 ByteMoveLeft(Bigint2 a, int loop)
{
	for (int i = Length(a) - 1; i >= 0; i--)
	{
		if (i + loop >= 2*SIZE) continue;
		a.num[i + loop] = a.num[i];
	}
	for (int i = loop - 1; i >= 0; i--) a.num[i] = 0;
	return a;
}

void BitMoveRight(Bigint &a)
{//右移一个比特
	Bigint temp1 = { 2 };
	Bigint temp2=a;
	a = Div(temp2, temp1);
}

void BitMoveRight(Bigint2 &a)
{//右移一个比特
	Bigint2 temp1 = { 2 };
	Bigint2 temp2=a;
	a = Div(temp2, temp1);
}

Bigint Div(Bigint a, Bigint b)
{
	Bigint B = { 0 };
	Bigint c = { 0 };
	int len = Length(a) - Length(b);
	while (len >= 0)
	{
		B = ByteMoveLeft(b, len);
		
		while (1)
		{	
			if (Compare(a, B) < 0)
			{
				break;
			}
			a = Sub(a, B);
			c.num[len]++;
		}
		len--;
	}
	return c;
}

Bigint2 Div(Bigint2 a, Bigint2 b)
{
	Bigint2 B = { 0 };
	Bigint2 c = { 0 };
	int len = Length(a) - Length(b);
	while (len >= 0)
	{
		B = ByteMoveLeft(b, len);
		
		while (1)
		{	
			if (Compare(a, B) < 0)
			{
				break;
			}
			a = Sub(a, B);
			c.num[len]++;
		}
		len--;
	}
	return c;
}

Bigint Mod(Bigint a, Bigint b) //大数求模 a mod b
{
	if (Compare(a, b) < 0)
	{
		return a;
	}
	else
	{
		Bigint B = { 0 };
		int len = Length(a) - Length(b);
		while (len >= 0)
		{
			B = ByteMoveLeft(b, len);//除数 b 左移 len 个字节，作为临时除数 B
			while (Compare(a, B) >= 0) a = Sub(a, B);//当 a>=B 时，不断减去 B
			len--;
		}
		return a; //减到最后，a 就是结果
	}
}

void Copy(Bigint &a, Bigint b)
{
	for (int i = 0; i < SIZE; i++)
	{
		a.num[i] = b.num[i];
	}
}

void Copy(Bigint2 &a, Bigint2 b)
{
	for (int i = 0; i < SIZE*2; i++)
	{
		a.num[i] = b.num[i];
	}
}

Bigint2 Extend(Bigint a)
{
	Bigint2 temp;
	for (int i = 0; i < SIZE; i++)
	{
		temp.num[i] = a.num[i];
	}

	for (int i = SIZE; i < 2 * SIZE; i++)
	{
		temp.num[i] = 0;
	}
	return temp;
}

Bigint2 Mod(Bigint2 a, Bigint2 b)
{
	if (Compare(a, b) < 0)
	{
		return a;
	}
	else
	{
		Bigint2 B = { 0 };
		int len = Length(a) - Length(b);
		while (len >= 0)
		{
			B = ByteMoveLeft(b, len);//除数 b 左移 len 个字节，作为临时除数 B
			while (Compare(a, B) >= 0) a = Sub(a,B);//当 a>=B 时，不断减去 B
			len--;
		}
		return a; //减到最后，a 就是结果
	}
}


bool Inverse(Bigint e, Bigint N, Bigint &d)
{
	Bigint r1 = { 0 };
	Bigint r2 = { 0 };
	Copy(r1, e);
	Copy(r2, N); //设初始值 r1=e, r2= N
	Bigint s1 = { 1 }; //设洗漱初始值 s1 = 1,s2 = 0
	Bigint s2 = { 0 };
	Bigint s = { 0 };
	Bigint r = { 0 };
	Bigint q;
	while (1)
	{
		if (Length(r1) == 0) return 0; //若 r1= 0,求模逆失败
		if (Length(r1) == 1 && r1.num[0] == 1)
		{
			Copy(d, s1); //若 r1=1, 求模逆成功，将结果 s1 存入 d
			return 1;
		}
		q = Div(r1, r2); //商 q=r1/r2
		s = Sub2Mod(s1, MulMod(q, s2, N), N);//s=s1 - q*s2,为了结果非负，使用模 N 运算
		r = Sub(r1, Narrow(Mul(q, r2)));//r= r-q*r2
		Copy(r1, r2);
		Copy(s1, s2);
		Copy(s2, s);
		Copy(r2, r);
		
	}
}

bool Inverse(Bigint2 e, Bigint2 N, Bigint2 &d)
{
	Bigint2 r1 = { 0 };
	Bigint2 r2 = { 0 };
	Copy(r1, e);
	Copy(r2, N); //设初始值 r1=e, r2= N
	Bigint2 s1 = { 1 }; //设洗漱初始值 s1 = 1,s2 = 0
	Bigint2 s2 = { 0 };
	Bigint2 s = { 0 };
	Bigint2 r = { 0 };
	Bigint2 q;
	while (1)
	{
		if (Length(r1) == 0) return 0; //若 r1= 0,求模逆失败
		if (Length(r1) == 1 && r1.num[0] == 1)
		{
			Copy(d, s1); //若 r1=1, 求模逆成功，将结果 s1 存入 d
			return 1;
		}
		q = Div(r1, r2); //商 q=r1/r2
		s = Sub2Mod(s1, MulMod(q, s2, N), N);//s=s1 - q*s2,为了结果非负，使用模 N 运算
		r = Sub(r1, Mul(Narrow(q), Narrow(r2)));//r= r-q*r2
		Copy(r1, r2);
		Copy(s1, s2);
		Copy(s2, s);
		Copy(r2, r);
		
	}
}

Bigint AddMod(Bigint a, Bigint b, Bigint n)
{ //模加：计算 a+b mod n
	Bigint res;
	res = Add(a, b);
	return Mod(res, n);
}

Bigint SubMod(Bigint a, Bigint b, Bigint n)
{ //模减：计算 a-b mod n(要求 a >= b)
	Bigint res;
	/*
	if (Compare(a, b) == -1)
	{
		Bigint temp;
		temp = a;
		a = b;
		b = temp;
	}
	*/
	res = Sub(a, b);
	return Mod(res, n);
}

Bigint Sub2Mod(Bigint a, Bigint b, Bigint n)
{ //模减：计算 a-b mod n
	while (Compare(a, b) < 0) a = Add(a, n);
	return Sub(a, b);
}

Bigint2 Sub2Mod(Bigint2 a, Bigint2 b, Bigint2 n)
{ //模减：计算 a-b mod n
	while (Compare(a, b) < 0) a = Add(a, n);
	return Sub(a, b);
}

Bigint MulMod(Bigint a, Bigint b, Bigint n)
{ //模乘：计算 a*b mod n
	Bigint2 res;
	res = Mul(a, b);
	return Narrow(Mod(res, Extend(n)));
}

Bigint2 MulMod(Bigint2 a, Bigint2 b, Bigint2 n)
{ //模乘：计算 a*b mod n
	Bigint2 res;
	res = Mul(Narrow(a), Narrow(b));
	return Mod(res, n);
}

Bigint PowMod(Bigint a, Bigint b, Bigint n)
{ //模幂：计算（a^b）mod n
	Bigint c = { 1 };
	Bigint temp = { 1 };
	while (Length(b) > 0)
	{
		while (!(b.num[0] & 1))
		{
			BitMoveRight(b);
			a = MulMod(a, a, n);
		}
		b = Sub(b, temp);
		c = MulMod(a, c, n);
	}
	return c;
}

Bigint2 PowMod(Bigint2 a, Bigint2 b, Bigint2 n)
{ //模幂：计算（a^b）mod n
	Bigint2 c = { 1 };
	Bigint2 temp = { 1 };
	while (Length(b) > 0)
	{
		while (!(b.num[0] & 1))
		{
			BitMoveRight(b);
			a = MulMod(a, a, n);
		}
		b = Sub(b, temp);
		c = MulMod(a, c, n);
	}
	return c;
}

Bigint Init(unsigned char a[], int length) 
{
	Bigint temp;
	for (int i = 0; i < length; i++)
	{
		temp.num[i] = a[length - 1 - i];
	}
	for (int i = length; i < SIZE; i++)
	{
		temp.num[i] = 0;
	}
	return temp;
}

void Print(Bigint a) //打印输出
{
	int i;
	for ( i = SIZE-1; i >= 0; i--)
	{
		if (a.num[i] != 0)
		{
			break;
		}
	}

	for (; i >= 0; i--)
	{
		printf("%d ", a.num[i]);
	}
	printf("\n");
}


// int main()
// {
// 	unsigned char a[] = {3,212,123,212,121,12,12,1}; 
// 	unsigned char b[] = {2};
// 	unsigned char n[] = { 2,31,231,31,2,3,2,2,23,2,23 };
// 	Bigint A, B, N;
// 	A = Init( a,1);
// 	B = Init( b,1);
// 	N = Init( n,11);

// 	printf("A=");
// 	Print(A);

// 	printf("B=");
// 	Print(B);

// 	printf("N=");
// 	Print(N);
	
// 	printf("(A+B)modN=");
// 	Print(AddMod(A, B, N));

// 	printf("(A-B)modN=");
// 	Print(SubMod(A, B, N));

// 	printf("(A*B)modN=");
// 	Print(MulMod(A, B, N));
	
	
// 	printf("A模N的逆=");
// 	Bigint temp;
// 	Inverse(A, N, temp);
// 	Print(temp);
	
	
// 	printf("(A/B)=");
// 	Print(Div(A, B));
	
	
// 	printf("(A^B)modN=");
// 	Print(PowMod(A, B, N));
	

// 	return 0;
// }




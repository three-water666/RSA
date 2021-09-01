#include<stdio.h>

#include "Bigint.h"
#include "Bigprime.h"
#include "RSA.h"

Bigint GCD(Bigint a, Bigint b) //计算 a 和 b 的最大公因数（a, b）
{
    Bigint c = {0};
    while (Length(a) > 0)
    {
        Copy(c, Mod(b, a));
        Copy(b, a);
        Copy(a, c);
    }
    return b;
}

Bigint2 GCD(Bigint2 a, Bigint2 b) //计算 a 和 b 的最大公因数（a, b）
{
    Bigint2 c = {0};
    while (Length(a) > 0)
    {
        Copy(c, Mod(b, a));
        Copy(b, a);
        Copy(a, c);
    }
    return b;
}

Bigint GenE(Bigint PhiN)
{
    Bigint e = BigRand(PhiN);
    Bigint g = GCD(PhiN, e);
    while (Length(g) != 1 || g.num[0] != 1)
    {
        e = BigRand(PhiN);
        g = GCD(PhiN, e);
    }
    return e;
}

Bigint2 GenE(Bigint2 PhiN)
{
    Bigint2 e = BigRand(PhiN);
    Bigint2 g = GCD(PhiN, e);
    while (Length(g) != 1 || g.num[0] != 1)
    {
        e = BigRand(PhiN);
        g = GCD(PhiN, e);
    }
    return e;
}

bool GenD(Bigint e, Bigint PhiN, Bigint &d) //生成私钥 d
{
    if (Inverse(e, PhiN, d))
        return 1;
    else
        return 0;
}

bool GenD(Bigint2 e, Bigint2 PhiN, Bigint2 &d) //生成私钥 d
{
    if (Inverse(e, PhiN, d))
        return 1;
    else
        return 0;
}

Bigint Encrypt(Bigint m, Bigint e, Bigint n) //加密函数，c = m^e(mod N)
{
    return PowMod(m, e, n);
}

Bigint2 Encrypt(Bigint2 m, Bigint2 e, Bigint2 n) //加密函数，c = m^e(mod N)
{
    return PowMod(m, e, n);
}

Bigint Decrypt(Bigint c, Bigint d, Bigint n) //解密函数，m` = c^d(mod N)
{
    return PowMod(c, d, n);
}

Bigint2 Decrypt(Bigint2 c, Bigint2 d, Bigint2 n) //解密函数，m` = c^d(mod N)
{
    return PowMod(c, d, n);
}


int main(){

    //1.选取大素数p,q 均为BIT=128比特素数
    Bigint p = GenPrime(BYTE);
    printf("大素数p:");
    Print10(p);
    Bigint q = GenPrime(BYTE);
    printf("大素数q:");
    Print10(q);
    //2.计算乘积N=pq 约为2*len比特
    Bigint2 N = Mul(p,q);
    printf("N=pq:");
    Print10(N);
    //3.计算N的欧拉函数值$(N)=(p-1)(q-1)
    Bigint one = { 1 };
    Bigint2 PhiN = Mul(Sub(p,one),Sub(q,one)); 
    printf("PhiN=(p-1)(q-1):");
    Print10(PhiN);
    //4.生成公钥e gcd(e,$(N))=1
    Bigint2 e = GenE(PhiN);
    printf("公钥e:");
    Print10(e);
    //5.生成私钥d,d=e^-1 mod $(N)
    Bigint2 d;
    GenD(e,PhiN,d);
    printf("私钥d:");
    Print10(d);
    //6.加密 c=m^e(mod N)
    // char str[]="Hi,this is RSA!";
    // Bigint m=Init((unsigned char *)str,BYTE);
    Bigint2 m = Extend(BigRand(BYTE));
    printf("加密前明文m:");
    Print10(m);
    //加密
    Bigint2 c=Encrypt(m,e,N);
    printf("加密后密文c:");
    Print10(c);
    //7.解密 m'=c^d(mod N)
    Bigint2 m_=Decrypt(c,d,N);
    printf("解密后明文m_:");
    Print10(m_);

}
// 大素数位数
#define BIT 128
#define BYTE BIT/8

Bigint GCD(Bigint a, Bigint b); //计算 a 和 b 的最大公因数（a, b）

Bigint GenE(Bigint PhiN);

bool GenD(Bigint e, Bigint PhiN, Bigint &d); //生成私钥 d


Bigint Encrypt(Bigint m, Bigint e, Bigint n); //加密函数，c = m^e(mod N)


Bigint Decrypt(Bigint c, Bigint d, Bigint n); //解密函数，m` = c^d(mod N)
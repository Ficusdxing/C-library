#include <stdio.h>
#include "Ficusxx_strings.h"

/*======================================================
* @ brief :	将BCD码串转换为字符串，BCD格式：123 -> 321<EOF>
* @ example:	1234<EOF> -> "1234"
* @ parama:	X -> 待转换BCD码串的指针
* @ retval: X -> 处理后返回原指针
=======================================================*/
char* BCD2str(char* X)
{
	for (int i = 0;; i++)
	{
		if (X[i] != EOF)
			X[i] += '0';
		else
		{
			X[i] = 0;
			return X;
		}
	}

}
/*======================================================
* @ brief :	将字符串转换为BCD码串，BCD格式：123 -> "321<EOF>"
* @ example:	"1234" -> 1234<EOF>
* @ parama:	X -> 待转换的串X
* @ retval:	X -> 处理后返回原指针
======================================================*/
char* str2BCD(char* X)
{
	for (int i = 0;; i++)
	{
		if (X[i] != '\0')
			X[i] -= '0';
		else
		{
			X[i] = EOF;
			return X;
		}
	}
}
/*======================================================
	@ brief: 整形变为倒序的字符串
	@ example: 123 -> "321"
	@ parama: n -> 待转换的整数
	@ retval: X -> 处理后返回字符串指针
=======================================================*/
char* int2Rstr(char* X,int n)
{
	int i = 0;
	while (n)
	{
		X[i++] = '0' + n % 10;
		n /= 10;
	}
	X[i] = '\0';
	return X;
}
/*======================================================
	@ brief: ascii字符串倒置
	@ example: "abcd123" -> "321dcba"
	@ parama: char* X -> 待处理串的指针
	@ retval: char* X -> 处理后返回原指针
=======================================================*/
char* reverse_str(char* X)
{
	unsigned char count = 0;
	char tmp;
	char* p = X;
	while (p[++count] != '\0');
	count--;
	while (p - X < count)
	{
		tmp = X[count];
		X[count--] = *p;
		*p++ = tmp;
	}
	return X;
}

/*======================================================
	@ brief :	以小端字符串的形式进行乘法运算，串X空间必须大于等于
	串X长度+串Y长度。
		CAUTION: 小端排序
	@ example：	("8888","88") -> "441287"
	@ parama:	X -> 被加串的指针
				Y -> 加数串的指针
				len -> 处理的最大长度，X的最大长度
	@ retval:	X -> 处理后返回被加串指针
=======================================================*/
char* RstrMul(char* X, const char* Y,const int len)
{
	str2BCD(X), str2BCD(Y);//转为BCD编码
	//X[len - 1] = EOF;
	int Y_len = 0;
	int X_len = 0;
	for (Y_len = 0; Y[Y_len] != EOF; Y_len++);
	for (X_len = 0; X[X_len] != EOF; X_len++);
	if ((Y_len + X_len) >= len)return NULL;
	char bit = 0;
	for (int i = X_len; i < len; i++)
	{
		X[i] = 0;
	}
	for (int i = 0; i < Y_len; i++)
	{
		X[len - 1 - i] += X[0] * Y[i];
		X[len - 2 - i] += X[len - 1 - i]/10;
		X[len - 1 - i] = X[len - 1 - i] % 10;
	}
	for(bit = 1;; bit++)
	{
		
		X[bit - 1] = X[len - 1];
		if (bit < X_len)
		{
			for (int i = 0; i < Y_len+1; i++)
			{
				X[len - 1 - i] = X[len - 1 - i - 1];
			}
			X[len - Y_len - 2] = 0;
			for (int i = 0; i < Y_len; i++)
			{
				X[len - 1 - i] += X[bit] * Y[i];
				X[len - 2 - i] += X[len - 1 - i] / 10;
				X[len - 1 - i] = X[len - 1 - i] % 10;
			}
		}
		else
		{
			for (int i = 0; i < Y_len + 1; i++)
			{
				X[len - 1 - i] = X[len - 1 - i - 1];
			}
			X[len - Y_len - 2] = 0;
			X_len++;
			Y_len--;
		}
		if (Y_len <= 0)
		{
			X[bit] = EOF;
			break;
		}
	}
	
	return X;
}

/*======================================================
	@ brief :	进行(小端)字符串加法，串X必须大于串Y，
		CAUTION: 小端排序
	@ example：	"321","4321" -> "7531"
	@ parama:	X -> 被加串的指针
				Y -> 加数串的指针
				len -> 处理的最大长度，X的最大长度
	@ retval:	X -> 处理后返回被加串指针
=======================================================*/
char* RstrAdd(char* X, const char* Y,const int len)
{
	char* px = X;
	const char* py = Y;
	unsigned char flag = 0;//进位标记
	str2BCD(X), str2BCD(Y);//转为BCD编码
	do
	{
		if (*px == EOF)
			*px = 0;
		if (*py != EOF )
			*px += *py++;
		else if (!flag)break;//串py运算结束
		//进位标记运算
		if (flag) 
		{
			*px += 1;
			flag = 0;
		}
		//进位标记打开
		if (*px > 9) 
		{
			*px -= 10;
			flag = 1;
		}
		px++;
	} while (px - X < len);
	*px = EOF;
	BCD2str(X);
	return X;
}


/*======================================================
* @ brief :	将两个整形相加并转化为字符串，保存至串X中。
* @ example:(1234,123,X,64) -> "1357"
* @ parama:	Var1 -> 被加数
*			Var2 -> 加数
*			X -> 于之保存的目标串X
*			len -> 串的最大长度		
* @ retval:	char* X -> 处理后返回原指针
======================================================*/
//char* intAdd2str( int Var1, int Var2,char* X, int len)
//{
//	char Y[11] = {0};
//	int2str(X, Var1);
//	int2str(Y, Var2);
//	reverse_str(RstrAdd(X,Y,len));
//	return X;
//}
int main()
{
	char X[20] = "123456789";
	char Y[20] =   "23233";
	int a = 55;
	int b = 66;
	//printf(reverse_str( BCD2str( BCD_Add( str2BCD(int2str(X, a)), str2BCD(int2str(Y, b))))));
	printf(reverse_str(BCD2str(RstrMul(reverse_str(X), reverse_str(Y), 20))));
}


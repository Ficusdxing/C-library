#include <stdio.h>
#include "Ficusxx_strings.h"

/*======================================================
* @ brief :	��BCD�봮ת��Ϊ�ַ�����BCD��ʽ��123 -> 321<EOF>
* @ example:	1234<EOF> -> "1234"
* @ parama:	X -> ��ת��BCD�봮��ָ��
* @ retval: X -> ����󷵻�ԭָ��
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
* @ brief :	���ַ���ת��ΪBCD�봮��BCD��ʽ��123 -> "321<EOF>"
* @ example:	"1234" -> 1234<EOF>
* @ parama:	X -> ��ת���Ĵ�X
* @ retval:	X -> ����󷵻�ԭָ��
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
	@ brief: ���α�Ϊ������ַ���
	@ example: 123 -> "321"
	@ parama: n -> ��ת��������
	@ retval: X -> ����󷵻��ַ���ָ��
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
	@ brief: ascii�ַ�������
	@ example: "abcd123" -> "321dcba"
	@ parama: char* X -> ��������ָ��
	@ retval: char* X -> ����󷵻�ԭָ��
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
	@ brief :	��С���ַ�������ʽ���г˷����㣬��X�ռ������ڵ���
	��X����+��Y���ȡ�
		CAUTION: С������
	@ example��	("8888","88") -> "441287"
	@ parama:	X -> ���Ӵ���ָ��
				Y -> ��������ָ��
				len -> �������󳤶ȣ�X����󳤶�
	@ retval:	X -> ����󷵻ر��Ӵ�ָ��
=======================================================*/
char* RstrMul(char* X, const char* Y,const int len)
{
	str2BCD(X), str2BCD(Y);//תΪBCD����
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
	@ brief :	����(С��)�ַ����ӷ�����X������ڴ�Y��
		CAUTION: С������
	@ example��	"321","4321" -> "7531"
	@ parama:	X -> ���Ӵ���ָ��
				Y -> ��������ָ��
				len -> �������󳤶ȣ�X����󳤶�
	@ retval:	X -> ����󷵻ر��Ӵ�ָ��
=======================================================*/
char* RstrAdd(char* X, const char* Y,const int len)
{
	char* px = X;
	const char* py = Y;
	unsigned char flag = 0;//��λ���
	str2BCD(X), str2BCD(Y);//תΪBCD����
	do
	{
		if (*px == EOF)
			*px = 0;
		if (*py != EOF )
			*px += *py++;
		else if (!flag)break;//��py�������
		//��λ�������
		if (flag) 
		{
			*px += 1;
			flag = 0;
		}
		//��λ��Ǵ�
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
* @ brief :	������������Ӳ�ת��Ϊ�ַ�������������X�С�
* @ example:(1234,123,X,64) -> "1357"
* @ parama:	Var1 -> ������
*			Var2 -> ����
*			X -> ��֮�����Ŀ�괮X
*			len -> ������󳤶�		
* @ retval:	char* X -> ����󷵻�ԭָ��
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


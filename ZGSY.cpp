extern"C" {
#include"miracl.h"
#include"mirdef.h"
}
#include<stdio.h>
#include<math.h>
#include<stdlib.h>


int main()
{
	FILE* fp;
	int j = 0;
	miracl* mip = mirsys(5000, 10);
	big aj[3], mj[3], Mj[3], Mj_inverse[3], m, x, temp ;

	//大数初始化
	m = mirvar(1);
	x = mirvar(0);
	temp = mirvar(0);
	for (j = 0; j < 3; j++) {
		aj[j] = mirvar(0);
		mj[j] = mirvar(0);
		Mj[j] = mirvar(0);
		Mj_inverse[j] = mirvar(0);
	}
	//打开文件并赋值
	if ((fp = fopen("4.txt", "r+")) == NULL) {
		printf("文件打开失败！\n");
		system("pause");
		return 1;
	}
	printf("你输入的aj序列为：\n");
	for (j = 0; j < 3; j++) {
		cinnum(aj[j], fp);
		cotnum(aj[j], stdout);
		printf("\n");
	}
	printf("你输入的mj序列为：\n");
	for (j = 0; j < 3; j++) {
		cinnum(mj[j], fp);
		cotnum(mj[j], stdout);
		printf("\n");
	}
	//1.判断大数mj是否两两互素
	for (j = 0; j < 3; j++)
		for (int i = j + 1; i < 3; i++) {
			egcd(mj[j], mj[i], temp);
			if (mr_compare(temp, mirvar(1))) {
				printf("不能直接利用中国剩余定理\n");
				system("pause");
				return 1;
			}
		}
	for (j = 0; j < 3; j++)
		multiply(m, mj[j], m);//m=m*mj[j]
	for (j = 0; j < 3; j++) {
		fdiv(m, mj[j], Mj[j]);
		xgcd(Mj[j], mj[j], Mj_inverse[j], Mj_inverse[j], Mj_inverse[j]);//计算模逆
		multiply(Mj[j], Mj_inverse[j],Mj[j]);
		multiply(Mj[j], aj[j], temp);
		add(x, temp, x);
	}
	powmod(x, mirvar(1), m, x);
	printf("x=");
	cotnum(x, stdout);

	mirkill(x);
	mirkill(m);
	mirkill(temp);
	fclose(fp);

	system("pause");
	return 0;
}


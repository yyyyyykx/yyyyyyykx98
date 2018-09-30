#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int n[10000][3];   //0为自然数，1为分母，2为分子
int m[3];
int result[1][3]; 
char sign[4];

//通过随机的方法确定运算符个数
int SignOfOperatorNum() {
	int num;
	int choice[3] = {1, 2, 3};
	//srand ((unsigned)time(NULL));
	num = rand()%3;
 	return choice[num];
}


//通过随机的方法选择运算符及确定加入括号的数组
char SignOfOperator(int no) {
	int num;
	int i;
	for( i=0; i<no; i++) {
            num = rand()%5;
		switch(num) {
			case 1:
				sign[i] = '+';
				break;
			case 2:
				sign[i] = '-';
				break;
			case 3:
				sign[i] = '*';
				break;
			case 4:
				sign[i] = '%';
				break;
		}
		sign[no]='=';
	}
}

//在给出的范围内通过随机的方法确定数字及其数组
void RandomNum(int range, int no) {
	int i, j, t;
	//srand ((unsigned)time(NULL));
	int choice[2] = {0, 1};
	for( i=0; i<=no; i++) {//生成数字个数
		j = rand()%2;
		switch(choice[j]) {   //判断随机选择的数字是自然数还是分数
		case 0:
			n[i][1] = 1;
			n[i][2] = 0;
			n[i][0] = rand()%(range+1);
			/*printf("%d\n", n[i][0]);
			printf("自然数\n");*/
			break;
		case 1:
			n[i][1] = rand()%(range+1);
			while(n[i][1]==0) {   //分母不能为0
				n[i][1] = rand()%(range+1);
			}
			n[i][2] = rand()%n[i][1];
			while(n[i][2]==0) {   //分子不能为0
				n[i][2] = rand()%(n[i][1]);
			}
			n[i][0] = rand()%range;
			while(n[i][0]==0) {   //分母不能为0
				n[i][0] = rand()%(range);
			}
			/*printf("%d'%d/%d\n",n[i][0],n[i][2],n[i][1]);
			printf("分数\n");*/
			break;
		default:
			printf("error\n");
		}
	}
}

//生成一个算术式并输出
char Formula(int range, int no,FILE *fp) {
	int i,j=1;
	RandomNum(range,no);
	SignOfOperator(no);
	for( i=0;i<=no; i++) {
		if(n[i][1]==1) {   //若分母为1则可以确定数字为自然数
			fprintf(fp,"%d",n[i][0]);
			printf("%d",n[i][0]);
		}
		else {   //若为分数
			fprintf(fp,"%d'%d/%d",n[i][0],n[i][2],n[i][1]);
            printf("%d'%d/%d",n[i][0],n[i][2],n[i][1]);
		}
		fprintf(fp,"%c",sign[i]);
		printf("%c",sign[i]);
	}
	fprintf(fp,"\n");
	printf("\n");
}

//求最大公因数
int Max(int n, int m) {
	int temp, r;
	if(n<m) {
		temp = n;
		n = m;
		m = temp;
	}
	while(m!=0) {
		r = n % m;
		n = m;
		m = r;
	}
	return n;
}

//求最小公倍数
int Min(int m, int n) {
	int temp, r, p;
	if(n<m) {
		temp = n;
		n = m;
		m = temp;
	}
	p = n * m;
	while(m!=0) {
		r = n % m;
		n = m;
		m = r;
	}
	return p/n;
}

//相加
int Add(int n1[], int n2[]) {
	m[0] = n1[0] + n2[0];
	m[1] = Min(n1[1], n2[1]);
	m[2] = m[1] / n1[1] * n1[2] + m[1] / n2[1] * n2[2];
	if(m[2]>m[1]) {
		m[2] -= m[1];
		m[0] += 1;
	}
}

//相减
int Sub(int n1[], int n2[]) {
	m[0] = n1[0] - n2[0];
	m[1] = Min(n1[1], n2[1]);
	m[2] = m[1] / n1[1] * n1[2] - m[1] / n2[1] * n2[2];
	if(m[2]<0) {
		m[0] -= 1;
		m[2] += m[1];
	}
}

//相乘
int Multiply(int n1[], int n2[]) {
	int max;
	m[0] = n1[0] * n2[0];
	m[1] = n1[1] * n2[2];
	m[2] = n1[2] * n2[1];
	max = Max(m[1], m[2]);
	if(max!=1) {
		m[1] /= max;
		m[2] /= max;
	}
}

//相除
int Division(int n1[], int n2[]) {
	int max;
	n1[2] += n1[1] * n1[0];
	n2[2] += n2[1] * n2[0];
	m[1] = n1[1] * n2[2];
	m[2] = n1[2] * n2[1];
	max = Max(m[1], m[2]);
	if(max!=1) {
		m[1] /= max;
		m[2] /= max;
	}
	if(m[2]>m[1]) {
		m[0] = m[2] / m[1];
		m[2] -= m[0] * m[1];
	}
}

//计算算术式结果   未完 
int Result() {
	int i, j, f, point[3], length, result=0;
	length = strlen(sign);
	for( i=0, j=0; i<length; i++) {   //记录乘除号的个数和位置 
		if(sign[i]=='*' || sign[i]=='%') {
			point[j] = i;
			j++;
		}
	}
	if(j=1) {   //若只有一个乘除号 
		f = point[0];
		if(sign[f]=='*') {
			result[0][] += Multiply(n[f][], n[f+1][]);
		} else {
			result[0][] += Division(n[f][], n[f+1][]);
		}
	} else if(j=2) {   //若有两个乘除号
	 	
	} else {   //若均为乘除号 
		
	} 
}

//主函数
int main() {
	int num, range, no, i=0;
	FILE *fp;
	char filename[]="Exercises.txt";
	printf("请输入生成题目的个数： \n");
	scanf("%d", &num);
	while(num>10000 || num<=0) {
		printf("请输入生成题目的个数： \n");
		scanf("%d", &num);
	}
	printf("请输入题目中数值的范围： \n");
	scanf("%d", &range);
	while(range<=0) {
		printf("请输入题目中数值的范围： \n");
		scanf("%d", &range);
	}
	if((fp=fopen(filename,"w"))==NULL) {
        printf("无法打开文件\n");
       exit(EXIT_FAILURE);
    }
    while(i<num) {
        no = SignOfOperatorNum();
        SignOfOperator(no);
        fprintf(fp,"%d.",i+1);
        printf("%d.",i+1);
        Formula(range, no,fp);
        i++;
     }
     fclose(fp);
	 return 0;
}

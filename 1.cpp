#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int n[10000][3];   //0Ϊ��Ȼ����1Ϊ��ĸ��2Ϊ����
int m[3];
int result[1][3]; 
char sign[4];

//ͨ������ķ���ȷ�����������
int SignOfOperatorNum() {
	int num;
	int choice[3] = {1, 2, 3};
	//srand ((unsigned)time(NULL));
	num = rand()%3;
 	return choice[num];
}


//ͨ������ķ���ѡ���������ȷ���������ŵ�����
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

//�ڸ����ķ�Χ��ͨ������ķ���ȷ�����ּ�������
void RandomNum(int range, int no) {
	int i, j, t;
	//srand ((unsigned)time(NULL));
	int choice[2] = {0, 1};
	for( i=0; i<=no; i++) {//�������ָ���
		j = rand()%2;
		switch(choice[j]) {   //�ж����ѡ�����������Ȼ�����Ƿ���
		case 0:
			n[i][1] = 1;
			n[i][2] = 0;
			n[i][0] = rand()%(range+1);
			/*printf("%d\n", n[i][0]);
			printf("��Ȼ��\n");*/
			break;
		case 1:
			n[i][1] = rand()%(range+1);
			while(n[i][1]==0) {   //��ĸ����Ϊ0
				n[i][1] = rand()%(range+1);
			}
			n[i][2] = rand()%n[i][1];
			while(n[i][2]==0) {   //���Ӳ���Ϊ0
				n[i][2] = rand()%(n[i][1]);
			}
			n[i][0] = rand()%range;
			while(n[i][0]==0) {   //��ĸ����Ϊ0
				n[i][0] = rand()%(range);
			}
			/*printf("%d'%d/%d\n",n[i][0],n[i][2],n[i][1]);
			printf("����\n");*/
			break;
		default:
			printf("error\n");
		}
	}
}

//����һ������ʽ�����
char Formula(int range, int no,FILE *fp) {
	int i,j=1;
	RandomNum(range,no);
	SignOfOperator(no);
	for( i=0;i<=no; i++) {
		if(n[i][1]==1) {   //����ĸΪ1�����ȷ������Ϊ��Ȼ��
			fprintf(fp,"%d",n[i][0]);
			printf("%d",n[i][0]);
		}
		else {   //��Ϊ����
			fprintf(fp,"%d'%d/%d",n[i][0],n[i][2],n[i][1]);
            printf("%d'%d/%d",n[i][0],n[i][2],n[i][1]);
		}
		fprintf(fp,"%c",sign[i]);
		printf("%c",sign[i]);
	}
	fprintf(fp,"\n");
	printf("\n");
}

//���������
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

//����С������
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

//���
int Add(int n1[], int n2[]) {
	m[0] = n1[0] + n2[0];
	m[1] = Min(n1[1], n2[1]);
	m[2] = m[1] / n1[1] * n1[2] + m[1] / n2[1] * n2[2];
	if(m[2]>m[1]) {
		m[2] -= m[1];
		m[0] += 1;
	}
}

//���
int Sub(int n1[], int n2[]) {
	m[0] = n1[0] - n2[0];
	m[1] = Min(n1[1], n2[1]);
	m[2] = m[1] / n1[1] * n1[2] - m[1] / n2[1] * n2[2];
	if(m[2]<0) {
		m[0] -= 1;
		m[2] += m[1];
	}
}

//���
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

//���
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

//��������ʽ���   δ�� 
int Result() {
	int i, j, f, point[3], length, result=0;
	length = strlen(sign);
	for( i=0, j=0; i<length; i++) {   //��¼�˳��ŵĸ�����λ�� 
		if(sign[i]=='*' || sign[i]=='%') {
			point[j] = i;
			j++;
		}
	}
	if(j=1) {   //��ֻ��һ���˳��� 
		f = point[0];
		if(sign[f]=='*') {
			result[0][] += Multiply(n[f][], n[f+1][]);
		} else {
			result[0][] += Division(n[f][], n[f+1][]);
		}
	} else if(j=2) {   //���������˳���
	 	
	} else {   //����Ϊ�˳��� 
		
	} 
}

//������
int main() {
	int num, range, no, i=0;
	FILE *fp;
	char filename[]="Exercises.txt";
	printf("������������Ŀ�ĸ����� \n");
	scanf("%d", &num);
	while(num>10000 || num<=0) {
		printf("������������Ŀ�ĸ����� \n");
		scanf("%d", &num);
	}
	printf("��������Ŀ����ֵ�ķ�Χ�� \n");
	scanf("%d", &range);
	while(range<=0) {
		printf("��������Ŀ����ֵ�ķ�Χ�� \n");
		scanf("%d", &range);
	}
	if((fp=fopen(filename,"w"))==NULL) {
        printf("�޷����ļ�\n");
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

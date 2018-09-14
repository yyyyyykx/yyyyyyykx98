#include<stdio.h>
#include<stdlib.h>
//#include<string.h>
#include<ctype.h>
 
//�ַ��� 
int Character(char *filename) {
	FILE *fp;
	int num = 0;
	char ch[100];
	char m;
	if((fp=fopen(filename,"r")) == NULL) {   //�ж��ļ��Ƿ������� 
		printf("�ļ��޷�������\n");
		exit(0);
	}
	while(!feof(fp)) {   //fp��ָ����ļ�δ������һֱѭ�� 
		m = fgetc(fp);
		if(isalnum(m) || ispunct(m)) {
			num++;
		}
	}
	printf("�ļ����ַ�����%d\n",num);
	fclose(fp);
	return num;
} 

//������
int Word(char *filename) {
	FILE *fp;
	int num = 0, point=0;
	char str[100];
	char m;
	if((fp=fopen(filename,"r")) == NULL) {   //�ж��ļ��Ƿ�������
		printf("�ļ��޷�������\n");
		exit(0);
	}
	while(!feof(fp)) {   //fp��ָ����ļ�δ������һֱѭ��
		m = fgetc(fp);
		if(!((m>='a' && m<='z') || (m>='A' && m<='Z'))) {
			point = 0;
		} else if(((m>='a' && m<='z') || (m>='A' && m<='Z')) && point==0) {
			point = 1;
			num++;
		}
	}
	printf("�ļ��ĵ�������%d\n",num);
	fclose(fp);
	return num;
} 

//����
int Line(char *filename) {
	FILE *fp;
	int num = 0;
	char m;
	if((fp=fopen(filename,"r")) == NULL) {   //�ж��ļ��Ƿ�������
		printf("�ļ��޷�������\n");
		exit(0);
	}
	m = fgetc(fp);
	while(!feof(fp)) {   //fp��ָ����ļ�δ������һֱѭ��
		if(m=='\n') {
			num++;
		}
		m = fgetc(fp);
	}
	printf("�ļ���������\n%d\n",num);
	fclose(fp);
	return num;
} 

/*���� ������ ע���� 
void EmptyCodeComment(char *filename) {
	FILE *fp;
	int emptyline = 0, codeline = 0, commentline = 0;
	char str[100];
	if((fp=fopen(filename,"r")) == NULL) {
		printf("�ļ��޷�������\n");
		exit(0);
	}
	while(!feof(fp)) {
		fscanf(fp,"%s",str);
		if(fgetc(fp)=='{' || fgetc(fp)=='}') {
			emptyline++;
		}  else if((str[0]=='/'&&str[1]=='/') || (str[0]=='/'&&str[1]=='*') || str[0]=='}'&&str[1]=='/'&&str[2]=='/') {
			commentline++;
		} else {
			codeline++;
		}
	}
	fclose(fp);
	printf("��������%d\n�����У�%d\nע���У�%d\n", emptyline, codeline, commentline);
} */

// ����ԭ�˵�
void back() {
	printf("\n\n");
	system("PAUSE"); 
	printf("\n");
}

//������
int main() {
	char filename[100], ch[2];
	while(true) {
		printf("****************************************\n");
		printf("*                                      *\n");
		printf("*                 W  C                 *\n");
		printf("*                                      *\n");
		printf("*                                      *\n");
		printf("*          -c �����ļ��ַ���           *\n"); 
		printf("*          -w �����ļ�������           *\n");
		printf("*          -l �����ļ�������           *\n");
		printf("*          -a ���ش����п���ע����     *\n");
		printf("*                                      *\n");
		printf("****************************************\n\n");
 		printf("�������ļ���λ�ã�\n");
		scanf("%s",filename);
		printf("��������Ҫ�����\n");
		scanf("%s",ch);
		switch(ch[1]) {
			case 'c':
				Character(filename);
				back();
				break;
			case 'w':
				Word(filename);
				back();
				break;
			case 'l':
				Line(filename);
				back();
				break;
			case 'a':
				EmptyCodeComment(filename);
				back();
				break;
			default:
				printf("error\n");
		}
	}
	return 0;
} 





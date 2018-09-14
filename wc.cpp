#include<stdio.h>
#include<stdlib.h>
//#include<string.h>
#include<ctype.h>
 
//字符数 
int Character(char *filename) {
	FILE *fp;
	int num = 0;
	char ch[100];
	char m;
	if((fp=fopen(filename,"r")) == NULL) {   //判断文件是否正常打开 
		printf("文件无法正常打开\n");
		exit(0);
	}
	while(!feof(fp)) {   //fp所指向的文件未结束便一直循环 
		m = fgetc(fp);
		if(isalnum(m) || ispunct(m)) {
			num++;
		}
	}
	printf("文件的字符数：%d\n",num);
	fclose(fp);
	return num;
} 

//单词数
int Word(char *filename) {
	FILE *fp;
	int num = 0, point=0;
	char str[100];
	char m;
	if((fp=fopen(filename,"r")) == NULL) {   //判断文件是否正常打开
		printf("文件无法正常打开\n");
		exit(0);
	}
	while(!feof(fp)) {   //fp所指向的文件未结束便一直循环
		m = fgetc(fp);
		if(!((m>='a' && m<='z') || (m>='A' && m<='Z'))) {
			point = 0;
		} else if(((m>='a' && m<='z') || (m>='A' && m<='Z')) && point==0) {
			point = 1;
			num++;
		}
	}
	printf("文件的单词数：%d\n",num);
	fclose(fp);
	return num;
} 

//行数
int Line(char *filename) {
	FILE *fp;
	int num = 0;
	char m;
	if((fp=fopen(filename,"r")) == NULL) {   //判断文件是否正常打开
		printf("文件无法正常打开\n");
		exit(0);
	}
	m = fgetc(fp);
	while(!feof(fp)) {   //fp所指向的文件未结束便一直循环
		if(m=='\n') {
			num++;
		}
		m = fgetc(fp);
	}
	printf("文件的行数：\n%d\n",num);
	fclose(fp);
	return num;
} 

/*空行 代码行 注释行 
void EmptyCodeComment(char *filename) {
	FILE *fp;
	int emptyline = 0, codeline = 0, commentline = 0;
	char str[100];
	if((fp=fopen(filename,"r")) == NULL) {
		printf("文件无法正常打开\n");
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
	printf("空行数：%d\n代码行：%d\n注释行：%d\n", emptyline, codeline, commentline);
} */

// 返回原菜单
void back() {
	printf("\n\n");
	system("PAUSE"); 
	printf("\n");
}

//主函数
int main() {
	char filename[100], ch[2];
	while(true) {
		printf("****************************************\n");
		printf("*                                      *\n");
		printf("*                 W  C                 *\n");
		printf("*                                      *\n");
		printf("*                                      *\n");
		printf("*          -c 返回文件字符数           *\n"); 
		printf("*          -w 返回文件单词数           *\n");
		printf("*          -l 返回文件的行数           *\n");
		printf("*          -a 返回代码行空行注释行     *\n");
		printf("*                                      *\n");
		printf("****************************************\n\n");
 		printf("请输入文件的位置：\n");
		scanf("%s",filename);
		printf("请输入需要的命令：\n");
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





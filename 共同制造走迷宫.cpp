//��Ȩ������ꡢ����Զ�������˲�������ʹ�� 
#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;

//�����б� 
char space(int n);			//���n���ո�(cout) OK 
void wait(double a);		//OK 
void gotoxy(int,int);//�ƶ���� ��x�е�y�� OK 
void change_chose(int& );	//ȫ��ͳһ��ʽ���������Ϊwasd��ѡ���Ϊ�ո� OK 
void readmap();	//�����ͼ OK 
void init();	//��ʼ�� OK 
void game();	//menuval=1 OK  
void setmap();	//menuval=2 �л���ͼ OK  
void setting();	//menuval=3
void guide();	//menuval=4 ��Ϸ˵�� OK 
void printmenu(int);	//����˵� OK 
void setcolor(int,int);	//������ɫ ����ɫ-����ɫ OK 

//���� 
int num_map;	//����ô���ŵ�ͼ 
int maps[25][55][55];	//��x��ͼ  0Ϊ�գ�1Ϊǽ��2Ϊ��Ҵ���3Ϊ�յ� 
struct pos{
	int x,y;	//��¼λ�� 
	bool isthis(int i,int j){
		return i==x&&j==y;
	}
	void set(int i,int j){
		x=i,y=j;
	}
};
pos perpos;	//����λ�� 
pos midpos;	//��ͼ������ʱ���Ͻ����� 
int maph[25]={12};		//ÿ�ŵ�ͼ�ĸ� 
int mapw[25]={15};		//ÿ�ŵ�ͼ�Ŀ� 
int mapx = 1;			//������ڼ��ŵ�ͼ 
HANDLE hdle ;			//������ڵľ�� 
const string menus[6]={"","��ʼ��Ϸ","���õ�ͼ","  ����  ","��Ϸ˵��","�˳���Ϸ"};
//��Ϸ��ʼ 
void game(){
	midpos.set( (35-maph[mapx])/2-1 , (100-mapw[mapx]*2)/2-1 );//��ͼ��������ʱ
	for(int i=1;i<=maph[mapx];i++){
		gotoxy(midpos.y,midpos.x+i-1);//�������� 
		for(int j=1;j<=mapw[mapx];j++){
			if(maps[mapx][i][j]==2)
				perpos.set(i,j);//���ó�ʼ������� 
			//����ʼ�ĵ�ͼ 
			if(maps[mapx][i][j]==1){
				setcolor(15,3);
				cout << "��"; //ǽ 
			}else if(maps[mapx][i][j]==0){
				setcolor(15,3);
				cout << "  "; //· 
			}else if(perpos.isthis(i,j)){
				setcolor(1,3);
				cout << "��"; //�� 
			}else if(maps[mapx][i][j]==3){
				setcolor(4,3);
				cout << "��"; //���� 
			}
		}
	}
	
	while(1){//һ����Ϸ 
		int xd,yd,xc,yc;
		while(1){//һ���ƶ� 
			//���뷽�� 
			int way=getch();
			change_chose(way);
			if(way=='w')way=1;
			else if(way=='a')way=2;
			else if(way=='s')way=3;
			else if(way=='d')way=4;
			else continue;
			const int xx[5]={0,-1,0,1,0};
			const int yy[5]={0,0,-1,0,1};
			xc=perpos.x+xx[way],
			yc=perpos.y+yy[way];	//�ƶ���λ�� 
			xd=perpos.x,yd=perpos.y;//�ƶ�ǰλ�� 
			if(maps[mapx][xc][yc]==0){
				perpos.set(xc,yc);
				break;
			}else if(maps[mapx][xc][yc]==3){
				system("cls");
				gotoxy(42,14);
				setcolor(4,3);
				cout << "�㵽�����յ㣡";
				setcolor(15,3);
				wait(1500);
				return;
			}
		}
		gotoxy(midpos.y+(yd-1)*2,midpos.x+xd-1);
		setcolor(15,3);
		cout<<"  ";
		gotoxy(midpos.y+(yc-1)*2,midpos.x+xc-1);
		setcolor(1,3);
		cout<<"��";		//ֻ��������Ҫ���ĵĵط���������ȫ������������Ͳ����� 
	}
}

void setmap(){
	int x=1,y=1;
	while(1){
		gotoxy(46,5);
		cout<<"��ͼѡ��";
		int maxx=num_map/5+bool(num_map%5);
		for(int i=1;i<=maxx;i++){
			for(int j=1;j<=5;j++){
				int mapi=i*5+j-5;
				if(mapi>num_map)break;
				if(x*5+y-5!=mapi){
					gotoxy(15+(j-1)*14+4,9+(i-1)*3);
					printf("��%d��",mapi);
				}
				else{
					gotoxy(15+(j-1)*14+2,9+(i-1)*3-1);
					int lg=log10(mapi);
					if(lg)printf("----------");
					else  printf("---------");
					gotoxy(15+(j-1)*14+2,9+(i-1)*3);
					printf("# ��%d�� #",mapi);
					gotoxy(15+(j-1)*14+2,9+(i-1)*3+1);
					if(lg)printf("----------");
					else  printf("---------");
				}
			}
		}
		while(1){
			int chose=getch();
			change_chose(chose);
			if(chose=='w'&&x>1){
				x--;
				break;
			}
			else if(chose=='a'&&y>1){
				y--;
				break;
			}
			else if( chose=='s' && (x<maxx-1||(x==maxx-1&&(num_map%5==0||y<=num_map%5))) ){
				x++;
				break;
				//����������е㳤�������˼�����ж�����������ǲ��ǿ�  
			}
			else if( chose=='d' && ((y<5&&x!=maxx)||(x==maxx&&y<num_map%5)) ){
				y++;
				break;
			}
			else if(chose==' '){
				mapx=x*5+y-5;
				gotoxy(46,9+(x-1)*3+5);
				cout<<"ѡ��ɹ�";
				wait(1000);
				return;
			}
		}
		system("cls"); 
	}
}

void setting(){
	
}

void guide(){
	gotoxy(42,4);
	cout << "��Ϸ˵��";
	gotoxy(0,7);
	cout << space(39) << "��Ϸ�������Թ�"<<endl;
	cout << endl;
	cout << space(42) << "��Ϸ�淨��" <<endl ;
	cout << endl;
	cout << space(31) << "��WASD��������ݽ�ɫ�����յ�" <<endl;
	cout << endl;
	cout << space(44) << "ͼʾ��" <<endl;
	cout << endl;
	cout << space(42) << "������ǽ" <<endl;
	cout << endl;
	cout << space(42) << "�������" <<endl;
	cout << endl;
	cout << space(42) << "��Ϊ�յ�" <<endl;
	cout << endl; 
	cout << space(33) << "�ĵ��е�mapeditor�ǵ�ͼ�༭��" <<endl;
	cout << endl;
	cout << space(31) << "���к�mapss�е����ݿ�����maps��" <<endl; 
	cout << endl;
	cout << space(39) << "����24������Ϊ15" <<endl;
	cout << endl;
	cout << space(40) << "���ɻ���µ�ͼ" <<endl;
	cout << endl;
	cout << space(40) << "���������˳�" <<endl;
	getch();
}

char space(int n){
	for(int i=1;i<n;i++)putchar(' ');//���n-1�� 
	return ' '; //ʣ��һ����cout��� 
}

void printmenu(int menuval){
	gotoxy(42,7);
	cout<<"���Թ�С��Ϸ";
	gotoxy(0,12);
	for(int i=1;i<=5;i++){
		if(menuval==i){
			cout<<space(42)<<"------------"<<endl;
			cout<<space(42)<<"# "<<menus[i]<<" #"<<endl;
			cout<<space(42)<<"------------"<<endl;
		}
		else{
			cout<<endl;
			cout<<space(42)<<"  "<<menus[i]<<endl;
			cout<<endl;
		}
	}
}

int main(){
	int menuval=1;
	init();
	while(1){
		printmenu(menuval);
		while(1){
			int chose=getch();
			change_chose(chose);
			if(chose==' '){
				system("cls");
				if(menuval==1){
					game();
				}
				else if(menuval==2){
					setmap();
				}
				else if(menuval==3){
					setting();
				}
				else if(menuval==4){
					guide();
				}
				else if(menuval==5){
					gotoxy(45,15);
					cout<<"��лʹ�ã�";
					wait(1000);
					return 0;
				}
				break;
			}
			else if(chose=='s'&&menuval<5){
				menuval++;
				break;
			}
			else if(chose=='w'&&menuval>1){
				menuval--;
				break;
			}
		}
		system("cls");
	}
	return 0;
}

void readmap(){
	FILE* fin;
	fin=fopen("maps.txt","r");
	fscanf(fin,"%d",&num_map);
	for(int a=1;a<=num_map;a++){
		fscanf(fin,"%d%d",&maph[a],&mapw[a]);
		for(int i=1;i<=maph[a];i++){
			for(int j=1;j<=mapw[a];j++){
				fscanf(fin,"%1d",&maps[a][i][j]);
			}
		}
	}
	fclose(fin);
}

void init(){
	printf("��ʼ����..."); 
	system("title ���Թ�  �����ߣ�����ꡢ����Զ");
	system("color 3f");
	system("mode con cols=100 lines=35");
	hdle=GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ�˴��ھ�� 
	CONSOLE_CURSOR_INFO CurSor;//������ڵĹ�� 
	GetConsoleCursorInfo(hdle, &CurSor);//��ȡ��� 
	CurSor.bVisible = false;//ʹ��겻�ɼ� 
	SetConsoleCursorInfo(hdle, &CurSor);//���ù�� 
	readmap();
	system("cls");
}

void change_chose(int &n){
	if(n==224) n=getch();//��windows�£���������������ַ����ɣ��ֱ���224������������˺��� 
	if(n=='\r')n=' ';//��windows�£����س���\r
	if(n==72)n='w';
	if(n==75)n='a';
	if(n==80)n='s';
	if(n==77)n='d';
	if(n>='A'&&n<='Z')n+=32;//��д��ĸתСд��ĸ 
}

void gotoxy(int x,int y){
	SetConsoleCursorPosition(hdle, COORD{SHORT(x),SHORT(y)});
}

void wait(double a){
	double t=clock();
	while(clock()-t<a);
}

void setcolor(int a,int b){
	SetConsoleTextAttribute(hdle,a+b*0x10);
}

//版权：beanadorkabledragon、liningyuan19，其他人不能随意使用 
#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;

//函数列表 
char space(int n);		//输出n个空格(cout) OK 
void wait(double a);	//OK 
void gotoxy(int,int);	//移动光标 第x列第y行 OK 
void change_chose(int&);//全部统一格式，方向键改为wasd，选择改为空格 OK 
void readmap();	//读入地图 OK 
void init();	//初始化 OK 
void game();	//menuval=1 OK  
void setmap();	//menuval=2 切换地图 OK  
void setacolor(int,string);	//OK
void setcolor();//menuval=3 OK
void guide();	//menuval=4 游戏说明 OK 
void printmenu(int);	//输出菜单 OK 
void setcolor(int,int);	//设置颜色 字体色-背景色 OK 
char to16(int);	//OK

//变量 
int num_map;	//共这么多张地图 
int maps[25][55][55];	//第x张图  0为空，1为墙，2为玩家处，3为终点 
struct pos{
	int x,y;	//记录位置 
	bool isthis(int i,int j){
		return i==x&&j==y;
	}
	void set(int i,int j){
		x=i,y=j;
	}
};
pos perpos;	//主角位置 
pos midpos;	//地图在中央时左上角坐标 
int maph[25]={12};	//每张地图的高 
int mapw[25]={15};	//每张地图的宽 
int mapx = 1;		//正在玩第几张地图 
HANDLE hdle ;		//这个窗口的句柄 
const string menus[6]={"","开始游戏","设置地图","设置颜色","游戏说明","退出游戏"};
int colors[6]={0,3,15,15,4,1};//空-背景-字体-墙体-终点-人物 
//游戏开始 
void game(){
	midpos.set( (35-maph[mapx])/2-1 , (100-mapw[mapx]*2)/2-1 );//地图在最中心时
	for(int i=1;i<=maph[mapx];i++){
		gotoxy(midpos.y,midpos.x+i-1);//设置行列 
		for(int j=1;j<=mapw[mapx];j++){
			if(maps[mapx][i][j]==2)
				perpos.set(i,j);//设置初始玩家坐标 
			//画初始的地图 
			if(maps[mapx][i][j]==1){
				setcolor(colors[3],colors[1]);
				cout << "■"; //墙 
			}else if(maps[mapx][i][j]==0){
				setcolor(15,colors[1]);
				cout << "  "; //路 
			}else if(perpos.isthis(i,j)){
				setcolor(colors[5],colors[1]);
				cout << "●"; //人 
			}else if(maps[mapx][i][j]==3){
				setcolor(colors[4],colors[1]);
				cout << "★"; //出口 
			}
		}
	}
	
	while(1){//一局游戏 
		int xd,yd,xc,yc;
		while(1){//一次移动 
			//输入方向 
			int way=getch();
			change_chose(way);
			if(way=='w')way=1;
			else if(way=='a')way=2;
			else if(way=='s')way=3;
			else if(way=='d')way=4;
			else if(way=='b'){
				system("cls");
				return;
			}
			else continue;
			const int xx[5]={0,-1,0,1,0};
			const int yy[5]={0,0,-1,0,1};
			xc=perpos.x+xx[way],
			yc=perpos.y+yy[way];	//移动后位置 
			xd=perpos.x,yd=perpos.y;//移动前位置 
			if(maps[mapx][xc][yc]==0){
				perpos.set(xc,yc);
				break;
			}else if(maps[mapx][xc][yc]==3){
				system("cls");
				gotoxy(42,14);
				setcolor(colors[2],colors[1]);
				cout << "你到达了终点！";
				wait(1500);
				return;
			}
		}
		gotoxy(midpos.y+(yd-1)*2,midpos.x+xd-1);
		setcolor(15,colors[1]);
		cout<<"  ";
		gotoxy(midpos.y+(yc-1)*2,midpos.x+xc-1);
		setcolor(colors[5],colors[1]);
		cout<<"●";		//只更改有需要更改的地方，而不是全部输出出来，就不会闪 
	}
}

void setmap(){
	int x=mapx/5+1,y=mapx%5;
	while(1){
		setcolor(colors[2],colors[1]);
		gotoxy(46,5);
		cout<<"地图选择";
		int maxx=num_map/5+bool(num_map%5);
		for(int i=1;i<=maxx;i++){
			for(int j=1;j<=5;j++){
				int mapi=i*5+j-5;
				if(mapi>num_map)break;
				if(x*5+y-5!=mapi){
					gotoxy(15+(j-1)*14+4,9+(i-1)*3);
					printf("第%d张",mapi);
				}
				else{
					gotoxy(15+(j-1)*14+2,9+(i-1)*3-1);
					int lg=log10(mapi);
					if(lg)printf("----------");
					else  printf("---------");
					gotoxy(15+(j-1)*14+2,9+(i-1)*3);
					printf("# 第%d张 #",mapi);
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
				//这两条语句有点长，大概意思就是判断下面或右面是不是空  
			}
			else if( chose=='d' && ((y<5&&x!=maxx)||(x==maxx&&y<num_map%5)) ){
				y++;
				break;
			}
			else if(chose==' '){
				mapx=x*5+y-5;
				gotoxy(46,9+(x-1)*3+5);
				cout<<"选择成功";
				wait(1000);
				return;
			}
			else if(chose=='b'){
				return;
			} 
		}
		system("cls"); 
	}
}
void setacolor(int colorx,string colormenu){
	const string colors2[5][5]=
	{
	  {"黑色","深蓝","深绿","蓝色"},
	  {"深红","紫色","黄色","白色"},
	  {"灰色","淡蓝","淡绿","蓝绿"},
	  {"红色","淡紫","淡黄","亮白"}
	};
	int x=colors[colorx]/4,y=colors[colorx]%4;
	system("cls");
	while(1){
		gotoxy(44,9);
		cout<<colormenu;
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				if(i==x&&j==y){
					gotoxy(26+12*i+2,11+j*3);
					cout<<"--------";
					gotoxy(26+12*i+2,11+j*3+1);
					cout<<"# "<<colors2[i][j]<<" #";
					gotoxy(26+12*i+2,11+j*3+2);
					cout<<"--------";
				}else{
					gotoxy(26+12*i+2,11+j*3+1);
					cout<<"  "<<colors2[i][j];
				}
			}
		}
		while(1){
			int chose=getch();
			change_chose(chose);
			if(chose=='w'&&y>0){
				y--;
				break;
			}else if(chose=='s'&&y<3){
				y++;
				break;
			}else if(chose=='a'&&x>0){
				x--;
				break;
			}else if(chose=='d'&&x<3){
				x++;
				break;
			}else if(chose==' '){
				colors[colorx]=x*4+y;
				return;
			}else if(chose=='b'){
				return;
			}
		}
		system("cls");
	}
}
void setcolor(){
	const string colormenus[7]={"","背景颜色设置","字体颜色设置","墙体颜色设置","终点颜色设置","人物颜色设置","退出颜色设置"};
	int colorx=1;
	while(1){
		setcolor(colors[2],colors[1]);
		gotoxy(46,9);
		cout<<"颜色设置";
		gotoxy(0,12);
		for(int i=1;i<=6;i++){
			if(colorx==i){
				cout<<space(42)<<"----------------"<<endl;
				cout<<space(42)<<"# "<<colormenus[i]<<" #"<<endl;
				cout<<space(42)<<"----------------"<<endl;
			}else{
				cout<<endl;
				cout<<space(42)<<"  "<<colormenus[i]<<"  "<<endl;
				cout<<endl;
			}
		}
		while(1){
			int chose=getch();
			change_chose(chose);
			if(chose=='s'&&colorx<6){
				colorx++;
				break;
			}else if(chose=='w'&&colorx>1){
				colorx--;
				break;
			}else if(chose==' '){
				if(colorx==6)return;
				setacolor(colorx,colormenus[colorx]);
				if(colorx==1){
					string a="color ";
					a+=to16(colors[1]);
					if( to16(colors[1]) != '0' ) a+='0';
					else a+='1';
					system(a.c_str());//设置全部背景色 
				}
				break;
			}else if(chose=='b'){
				return;
			}
		}
		system("cls"); 
	}
}

void guide(){
	setcolor(colors[2],colors[1]);
	gotoxy(42,4);
	cout << "游戏说明";
	gotoxy(0,7);
	cout << space(39) << "游戏名：走迷宫"<<endl;
	cout << endl;
	cout << space(42) << "游戏玩法：" <<endl ;
	cout << endl;
	cout << space(31) << "用WASD或方向键操纵角色到达终点" <<endl;
	cout << endl;
	cout << space(43) << "b键返回" <<endl;
	cout << endl;
	cout << space(44) << "图示：" <<endl;
	cout << endl;
	cout << space(42) << "■代表墙" <<endl;
	cout << endl;
	cout << space(42) << "●代表人" <<endl;
	cout << endl;
	cout << space(42) << "★为终点" <<endl;
	cout << endl; 
	cout << space(33) << "文档中的mapeditor是地图编辑器" <<endl;
	cout << endl;
	cout << space(31) << "运行后将mapss中的内容拷贝到maps里" <<endl; 
	cout << endl;
	cout << space(40) << "点击任意键退出" <<endl;
	getch();
}

char space(int n){
	for(int i=1;i<n;i++)putchar(' ');//输出n-1个 
	return ' '; //剩下一个用cout输出 
}

void printmenu(int menuval){
	gotoxy(42,7);
	setcolor(colors[2],colors[1]);
	cout<<"走迷宫小游戏";
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
					setcolor();
				}
				else if(menuval==4){
					guide();
				}
				else if(menuval==5){
					gotoxy(45,15);
					setcolor(colors[2],colors[1]);
					cout<<"感谢使用！";
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
	printf("初始化中..."); 
	system("title 走迷宫  制造者：beanadorkabledragon、liningyuan19");
	system("color 3f");
	system("mode con cols=100 lines=35");
	hdle=GetStdHandle(STD_OUTPUT_HANDLE);//获取此窗口句柄 
	CONSOLE_CURSOR_INFO CurSor;//这个窗口的光标 
	GetConsoleCursorInfo(hdle, &CurSor);//获取光标 
	CurSor.bVisible = false;//使光标不可见 
	SetConsoleCursorInfo(hdle, &CurSor);//设置光标 
	readmap();
	system("cls");
}

void change_chose(int &n){
	if(n==224){
		n=getch();//在windows下，方向键是由两个字符构成，分别是224和其他，详见此函数 
		if(n==72)n='w';
		if(n==75)n='a';
		if(n==80)n='s';
		if(n==77)n='d';
	}
	if(n=='\r')n=' ';//在windows下，按回车是\r
	if(n>='A'&&n<='Z')n+=32;//大写字母转小写字母 
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

char to16(int a){
	if(a<10)return a+'0';
	else return a-10+'a';
}

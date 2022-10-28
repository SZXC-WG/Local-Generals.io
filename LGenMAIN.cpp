#include <bits/stdc++.h>
#include "windows.h"
#include "conio.h"
#define SetColor(x) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x)
using namespace std;
int N=26;
const int P=10;
const int d=150;
const int T=15;
const int mountain=90;
const int tower=15;
string col[15]= {"","red","yellow","cyan","green","purple","blue","brown","lblue","white","grey"},
                name[20]= {"","ZLY","LXY","KTQ","XCX","CHR","FTX","SZX","XTK","JYL","LiS"};
mt19937 mt_rand(GetTickCount());
string ts(int x) {
	string s="";
	while(x) {
		s=(char)((x%10)^48)+s;
		x/=10;
	}
	return s;
}
void gotoxy(int x,int y) {
	COORD pos= {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void HideCursor() {
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle,&CursorInfo);
	CursorInfo.bVisible=false;
	SetConsoleCursorInfo(handle,&CursorInfo);
}
void ShowCursor() {
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle,&CursorInfo);
	CursorInfo.bVisible=true;
	SetConsoleCursorInfo(handle,&CursorInfo);
}
void setcolor(string col) {
	if(col=="red") cout<<"\033[1;31m";
	else if(col=="green") cout<<"\033[1;32m";
	else if(col=="blue") cout<<"\033[34m";
	else if(col=="yellow") cout<<"\033[1;33m";
	else if(col=="purple") cout<<"\033[1;35m";
	else if(col=="cyan") cout<<"\033[1;36m";
	else if(col=="white") cout<<"\033[1m";
	else if(col=="grey") cout<<"\033[1;30m";
	else if(col=="brown") cout<<"\033[33m";
	else if(col=="lblue") cout<<"\033[1;34m";
	else cout<<"\033[0m";
}
void SETCOLOR(string col) {
	if(col=="red") cout<<"\033[0m\033[1;31;41m";
	else if(col=="green") cout<<"\033[0m\033[1;32;41m";
	else if(col=="blue") cout<<"\033[0m\033[34;41m";
	else if(col=="yellow") cout<<"\033[0m\033[1;33;41m";
	else if(col=="purple") cout<<"\033[0m\033[1;35;41m";
	else if(col=="cyan") cout<<"\033[0m\033[1;36;41m";
	else if(col=="white") cout<<"\033[0m\033[1;41m";
	else if(col=="grey") cout<<"\033[0m\033[1;30;41m";
	else if(col=="brown") cout<<"\033[0m\033[33;41m";
	else if(col=="lblue") cout<<"\033[0m\033[1;34;41m";
	else cout<<"\033[0m\033[;;41m";
}
void resetcolor() {cout<<"\033[0m";}
struct block {int type,x;};
int cnt,cnt2,dx[4] {-1,0,1,0},dy[4] {0,-1,0,1},nowx,nowy,
    d2x[8] {-1,-1,-1,0,0,1,1,1},d2y[8] {-1,0,1,-1,1,-1,0,1},
    hx[P+1],hy[P+1],army[P+1],land[P+1],
    px[P+1],py[P+1],lx[P+1],ly[P+1],alivecnt=P;
bool vis[505][505],alive=1,seen[P+1],s[505][505],cheat,K,c[505][505],light[505][505];
block mp[505][505];
void win() {MessageBox(nullptr,"��Ӯ��","",MB_OK);}
void lose(int x) {MessageBox(nullptr,("Player "+name[x]+"Ӯ��").c_str(),"",MB_OK);}
void killed(int x) {MessageBox(nullptr,("Player "+name[x]+"����ɱ��").c_str(),"",MB_OK);}
void dfs(int x,int y) {
	vis[x][y]=1;
	for(int i=0; i<4; ++i) {
		int nx=x+dx[i],ny=y+dy[i];
		if(nx<1||ny<1||nx>N||ny>N) continue;
		if(mp[nx][ny].type!=-1) continue;
		if(vis[nx][ny]) continue;
		dfs(nx,ny);
	}
}
bool check1() {
	memset(vis,0,sizeof(vis));
	for(int i=1; i<=N; ++i)
		for(int j=1; j<=N; ++j) {
			if(mp[i][j].type==-1) {
				dfs(i,j);
				break;
			}
		}
	for(int i=1; i<=N; ++i)
		for(int j=1; j<=N; ++j)
			if(vis[i][j]==0&&mp[i][j].type==-1) return 0;
	return 1;
}
bool see(int p,int x,int y) {
	for(int i=0; i<8; ++i) {
		int nx=x+d2x[i],ny=y+d2y[i];
		if(nx<1||ny<1||nx>N||ny>N) continue;
		if(mp[nx][ny].type==p||mp[nx][ny].type==p+P||mp[nx][ny].type==p+P+P) return 1;
	}
	return 0;
}
void print(bool f,string color,char left,char right,int x) {
	if(f==1) SETCOLOR(color);
	else setcolor(color);
	if(x<=9) cout<<" "<<left<<x<<right;
	else if(x<=99) cout<<left<<x<<right;
	else if(x<=999) cout<<left<<x/100<<"H"<<right;
	else if(x<=9999) cout<<left<<x/1000<<"K"<<right;
	else cout<<left<<min(x/10000,9)<<"W"<<right;
	resetcolor();
	cout<<"|";
}
void print_all() {
	gotoxy(0,0);
	cout<<"+";
	for(int i=1; i<=N; ++i) cout<<"----+";
	cout<<'\n';
	for(int i=1; i<=N; ++i) {
		cout<<"|";
		for(int j=1; j<=N; ++j) {
			int f=0,tp=mp[i][j].type,x=mp[i][j].x;
			if(i==nowx&&j==nowy) f=1;
			if(f) SETCOLOR("black");
			switch(tp) {
				case -1:if(c[i][j]) cout<<"===="; else cout<<"    "; resetcolor(); cout<<"|"; break;
				case -2:cout<<"####|"; break;
				case -3:print(f,"white",'[',']',x); break;
				case 1:print(f,col[1],'$','$',x); break;
				case 2 ... P:print(f,col[tp],'{','}',x); break;
				case P+1 ... P+P:print(f,col[tp-P],'[',']',x); break;
				case P+P+1 ... P+P+P:print(f,col[tp-P-P],c[i][j]?'=':' ',c[i][j]?'=':' ',x); break;
			}
		}
		cout<<'\n';
		cout<<"+";
		for(int i=1; i<=N; ++i) cout<<"----+";
		cout<<'\n';
	}
	cout<<'\n';
	memset(army,0,sizeof(army));
	memset(land,0,sizeof(land));
	for(int i=1; i<=N; ++i)
		for(int j=1; j<=N; ++j) {
			int tp=mp[i][j].type,x=mp[i][j].x;
			if(tp<=0) continue;
			for(int k=1; k<=P; ++k)
				if((tp-1)%P==k-1) army[k]+=x,++land[k];
		}
	cout<<"----------- Ranklist ----------"<<'\n';
	cout<<" Rank | Player |  Army  | Land"<<'\n';
	int s[P+1],p[P+1];
	string nm[P+1];
	memset(p,0,sizeof(p));
	memset(s,0,sizeof(s));
	for(int i=1; i<=P; ++i) nm[i]=name[i].c_str(),p[i]=i,s[i]=army[i];
	for(int i=1; i<P; ++i) for(int j=i+1; j<=P; ++j)
			if(s[i]<s[j]) swap(s[i],s[j]),swap(p[i],p[j]),swap(nm[i],nm[j]);
	for(int i=1; i<=P; ++i) {
		setcolor(col[p[i]]);
		cout<<" ";
		cout<<setw(4)<<i<<" | "<<setw(6)<<nm[i].c_str()<<" | ";
		if(army[p[i]]<=999999) cout<<setw(6)<<army[p[i]]<<" | ";
		else if(army[p[i]]<=9999999) cout<<setw(5)<<round(1.0*army[p[i]]/10000.0)/100.0<<"M | ";
		else cout<<setw(6)<<" 10M+"<<" | ";
		cout<<setw(4)<<land[p[i]]<<"    ";
		cout<<'\n';
		resetcolor();
	}
	cout<<flush;
}
void print() {
	gotoxy(0,0);
	cout<<"+";
	for(int i=1; i<=N; ++i) cout<<"----+";
	cout<<'\n';
	for(int i=1; i<=N; ++i) {
		cout<<"|";
		for(int j=1; j<=N; ++j) {
			int f=0,tp=mp[i][j].type,x=mp[i][j].x;
			if(i==nowx&&j==nowy) f=1;
			if(f) SETCOLOR("black");
			switch(tp) {
				case -1:if(c[i][j]) cout<<"===="; else cout<<"    "; resetcolor(); cout<<"|"; break;
				case -2:if(light[i][j]||see(1,i,j)) cout<<"####|"; else cout<<"####|"; break;
				case -3:if(light[i][j]||see(1,i,j)) print(f,"white",'[',']',x); else cout<<"####|"; break;
				case 1:print(f,col[1],'$','$',x); break;
				case P+1:print(f,col[1],'[',']',x); break;
				case P+P+1:print(f,col[1],' ',' ',x); break;
				case 2 ... P:if(light[i][j]||see(1,i,j)) print(f,col[tp],'{','}',x); else cout<<"    |"; break;
				case P+2 ... P+P:if(light[i][j]||see(1,i,j)) print(f,col[tp-P],'[',']',x); else if(s[i][j]) cout<<"####|"; else cout<<"####|"; break;
				case P+P+2 ... P+P+P:if(light[i][j]||see(1,i,j)) print(f,col[tp-P-P],c[i][j]?'=':' ',c[i][j]?'=':' ',x); else cout<<"    |"; break;
			}
		}
		cout<<"\n+";
		for(int i=1; i<=N; ++i) cout<<"----+";
		cout<<'\n';
	}
	cout<<'\n';
	memset(army,0,sizeof(army));
	memset(land,0,sizeof(land));
	for(int i=1; i<=N; ++i)
		for(int j=1; j<=N; ++j) {
			int tp=mp[i][j].type,x=mp[i][j].x;
			if(tp<=0) continue;
			for(int k=1; k<=P; ++k)
				if((tp-1)%P==k-1) army[k]+=x,++land[k];
		}
	cout<<"----------- Ranklist ----------"<<'\n';
	cout<<" Rank | Player |  Army  | Land"<<'\n';
	int s[P+1],p[P+1];
	string nm[P+1];
	memset(p,0,sizeof(p));
	memset(s,0,sizeof(s));
	for(int i=1; i<=P; ++i) nm[i]=name[i].c_str(),p[i]=i,s[i]=army[i];
	for(int i=1; i<P; ++i) for(int j=i+1; j<=P; ++j)
			if(s[i]<s[j]) swap(s[i],s[j]),swap(p[i],p[j]),swap(nm[i],nm[j]);
	for(int i=1; i<=P; ++i) {
		setcolor(col[p[i]]);
		cout<<" ";
		cout<<setw(4)<<i<<" | "<<setw(6)<<nm[i].c_str()<<" | ";
		if(army[p[i]]<=999999) cout<<setw(6)<<army[p[i]]<<" | ";
		else if(army[p[i]]<=9999999) cout<<setw(5)<<round(1.0*army[p[i]]/10000.0)/100.0<<"M | ";
		else cout<<setw(6)<<" 10M+"<<" | ";
		cout<<setw(4)<<land[p[i]]<<"    ";
		cout<<'\n';
		resetcolor();
	}
	cout<<flush;
}
int getmove(int p) {
	int x=px[p],y=py[p],val[5]= {0},ok=0;
	for(int i=0; i<4; ++i) {
		int nx=x+dx[i],ny=y+dy[i];
		if(nx<1||ny<1||nx>N||ny>N||mp[nx][ny].type==-2) {
			val[i]=-1;
			continue;
		}
		++ok;
		if(nx==lx[p]&&ny==ly[p]) {
			val[i]=-1;
			continue;
		}
		if(mp[nx][ny].type==p)
			val[i]=-1;
		else if(mp[nx][ny].type==p+P) val[i]=999970+mp[nx][ny].x;
		else if(mp[nx][ny].type==p+P+P) val[i]=10+mp[nx][ny].x;
		else if(mp[nx][ny].type==-3) {
			if(mp[nx][ny].x<mp[x][y].x) val[i]=1000001+mp[x][y].x-mp[nx][ny].x;
			else val[i]=-1;
		} else if(mp[nx][ny].type==-1) {
			if(mp[x][y].x>=2) {
				if(!c[x][y]) val[i]=1000009;
				else val[i]=12;
			} else val[i]=-1;
		} else if(mp[nx][ny].type<=P) val[i]=110000000;
		else if(mp[nx][ny].type<=P+P) {
			if(mp[nx][ny].x<mp[x][y].x-1) val[i]=1000050+mp[x][y].x-mp[nx][ny].x;
			else val[i]=20;
		} else {
			if(mp[nx][ny].x<mp[x][y].x-1) val[i]=999900+mp[x][y].x-mp[nx][ny].x;
			else val[i]=-1;
		}
	}
	if(ok<=1)
		for(int i=0; i<4; ++i) {
			int nx=x+dx[i],ny=y+dy[i];
			if(nx==lx[p]&&ny==ly[p]) return i;
		}
	int pos=0,mx=-1;
	for(int I=0; I<=15; ++I) {
		int i=mt_rand()%5;
		if(val[i]>mx) mx=val[i],pos=i;
	}
	return pos;
}
void getseen() {
	for(int p=1; p<=P; ++p) {
		seen[p]=0;
		for(int i=1; i<=N; ++i)
			for(int j=1; j<=N; ++j) {
				int t=mp[i][j].type;
				if(t==p||t==p+P||t==p+P+P)
					for(int d=0; d<4; ++d) {
						int nx=i+dx[d],ny=j+dy[d];
						if(nx<1||ny<1||nx>N||ny>N) continue;
						int nt=mp[nx][ny].type;
						if(nt>=1&&nt!=p&&nt!=p+P&&nt!=p+P) seen[p]=1;
					}
			}
	}
}
void kill(int p1,int p2) {
	if(p2==1) killed(p1),alive=0;
	--alivecnt;
	if(alivecnt<=1) {
		if(alive) win();
		else lose(p1);
		print_all();
		//	exit(0);
	}
	for(int i=1; i<=N; ++i)
		for(int j=1; j<=N; ++j) {
			int t=mp[i][j].type,x=mp[i][j].x;
			if(t==p2) mp[i][j].type=p1+P;
			else if(t==p2+P) mp[i][j].type=p1+P,(++mp[i][j].x)>>=1;
			else if(t==p2+P+P) mp[i][j].type=p1+P+P,(++mp[i][j].x)>>=1;
		}
}
bool cmp(pair<int,pair<int,int>> x,pair<int,pair<int,int>> y) {
	if(x.first!=y.first) return x.first<y.first;
	return mt_rand()&1;
}
void readmap(string name) {
	freopen(name.c_str(),"r",stdin);
	int n;
	cin>>n;
	vector<pair<int,pair<int,int>>> home;
	n=min(n,N);
	for(int i=1; i<=N; ++i)
		for(int j=1; j<=N; ++j) mp[i][j]= {-1,0};
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j) {
			int tp;
			cin>>tp;
			if(tp==-4) c[i][j]=1;
			else if(tp<0) mp[i][j].type=tp;
			else home.push_back({tp,{i,j}});
		}
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j) cin>>mp[i][j].x;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j) cin>>light[i][j];
	for(int i=1; i<home.size(); ++i) {
		int r=mt_rand()%(i+1);
		swap(home[i],home[r]);
	}
	// sort(home.begin(),home.end());
	for(int i=1; i<=P; ++i) {
		px[i]=hx[i]=home[i-1].second.first,py[i]=hy[i]=home[i-1].second.second;
		mp[hx[i]][hy[i]]=(block) {i,1};
		if(i==1) nowx=hx[i],nowy=hy[i];
		s[hx[i]][hy[i]]=1;
	}
	print_all();
	system("pause");
	fclose(stdin);
}
void getmap(string name) {
	if(name=="9 Squares") {
		for(int i=1; i<=N; ++i)
			for(int j=1; j<=N; ++j) mp[i][j]=(block) {-1,0};
		for(int i=1; i<=13; ++i) mp[1][i]=mp[i][1]=mp[13][i]=mp[i][13]=(block) {-2,0};
		for(int i=1; i<=13; ++i) mp[5][i]=mp[9][i]=mp[i][5]=mp[i][9]=(block) {-2,0};
		for(int i=0; i<3; ++i)
			for(int j=0; j<3; ++j) mp[i*4+2][j*4+2]=mp[i*4+4][j*4+4]=(block) {-3,1};
		for(int i=0; i<3; ++i)
			for(int j=0; j<2; ++j) mp[i*4+3][j*4+5]=(block) {-3,370};
		for(int i=0; i<2; ++i)
			for(int j=0; j<3; ++j) mp[i*4+5][j*4+3]=(block) {-3,370};
		for(int i=1; i<=P; ++i) {
			int x=mt_rand()%3,y=mt_rand()%3;
			x=x*4+3;
			y=y*4+3;
			while(mp[x][y].type!=-1) {
				x=mt_rand()%3;
				y=mt_rand()%3;
				x=x*4+3;
				y=y*4+3;
			}
			hx[i]=x;
			hy[i]=y;
			mp[x][y]=(block) {i,1};
			if(i==1) nowx=x,nowy=y;
			s[x][y]=1;
		}
	} else if(name=="25 Squares") {
		for(int i=1; i<=N; ++i)
			for(int j=1; j<=N; ++j) mp[i][j]=(block) {-1,0};
		for(int i=1; i<=21; ++i) mp[1][i]=mp[i][1]=mp[21][i]=mp[i][21]=(block) {-2,0};
		for(int i=1; i<=21; ++i) mp[5][i]=mp[9][i]=mp[13][i]=mp[17][i]=mp[i][5]=mp[i][9]=mp[i][13]=mp[i][17]=(block) {-2,0};
		for(int i=0; i<5; ++i)
			for(int j=0; j<5; ++j) mp[i*4+2][j*4+2]=mp[i*4+4][j*4+4]=(block) {-3,1};
		for(int i=0; i<5; ++i)
			for(int j=0; j<4; ++j) mp[i*4+3][j*4+5]=(block) {-3,370};
		for(int i=0; i<4; ++i)
			for(int j=0; j<5; ++j) mp[i*4+5][j*4+3]=(block) {-3,370};
		for(int i=1; i<=P; ++i) {
			int x=mt_rand()%5,y=mt_rand()%5;
			x=x*4+3;
			y=y*4+3;
			while(mp[x][y].type!=-1) {
				x=mt_rand()%5;
				y=mt_rand()%5;
				x=x*4+3;
				y=y*4+3;
			}
			hx[i]=x;
			hy[i]=y;
			mp[x][y]=(block) {i,1};
			if(i==1) nowx=x,nowy=y;
			s[x][y]=1;
		}
	} else if(name=="random") {
		for(int i=1; i<=N; ++i)
			for(int j=1; j<=N; ++j) {
				mp[i][j]= {-1,0};
				if(mt_rand()%(N*N-(i-1)*N-(j-1))<mountain-cnt) {
					mp[i][j]= {-2,0};
					if(!check1()) mp[i][j]=(block) {-1,0};
					else {
						if(mt_rand()%(mountain-cnt)<tower-cnt2) mp[i][j]=(block) {-3,mt_rand()%11+40},++cnt2;
						++cnt;
					}
				}
			}
		for(int i=1; i<=P; ++i) {
			px[i]=hx[i]=mt_rand()%N+1,py[i]=hy[i]=mt_rand()%N+1;
			mp[hx[i]][hy[i]]=(block) {i,1};
			if(i==1) nowx=hx[i],nowy=hy[i];
			s[hx[i]][hy[i]]=1;
		}
	} else readmap(name);
}
deque<int> movement;

void getN() { cout<<"�������ͼ��С��"; cin>>N; }
int __citypower;
void getCity() { cout<<"������ǳس�ʼ������"; cin>>__citypower; }
const int dlk_sz[55]= {0,25,40,40,40,49,35,45,50/*40*50*/,50,50,50,50/*50*40*/,50,50,50,-1,50,-1};
const int dlk_wtcz_sz[55]= {0,25,-1,-1,-1,-1,-1,-1,50,-1,-1,-1,-1,-1,-1,-1,-1,-1};

signed main() {
	ios::sync_with_stdio(false);
	HideCursor();
	char ch;
	cout<<"generals.io\npress SPACE to start\n"<<flush;
	while(getch()!=' ');
	cout<<endl;
	cout<<"ѡ���ͼ�����뱣֤�˳���ͬһĿ¼���йٷ��� createmap.exe �ļ���"<<endl;
	cout<<"��ϵ��1: �����ͼ��"<<endl;
	cout<<"0. �����ͼ (random_map.txt)"<<endl;
	cout<<"1. ��ȫ�� (allcity_map.txt)"<<endl;
	cout<<"2. ��ȫ���� (allswamp_map.txt)"<<endl;
	cout<<"3. ��ƽԭ (allplain_map.txt)"<<endl;
	cout<<"��ϵ��2: ������ series��"<<endl;
	cout<<"a. ������ (dlk.txt/dlk_wt.txt)"<<endl;
	cout<<"A. ������ �������ư� (dlk_wtcz.txt)"<<endl;
	cout<<"b. ������2 (dlk2.txt/dlk2_wt.txt)"<<endl;
	cout<<"c. ������3��������Ϣ (dlk3.txt/dlk3_wt.txt)"<<endl;
	cout<<"d. ������4��ɽ��֮�� (dlk4.txt/dlk4_wt.txt)"<<endl;
	cout<<"e. ������5�������Թ� (dlk5.txt)"<<endl;
	cout<<"f. ������6�����뱦�� (dlk6.txt/dlk6_wt.txt)���ݲ����ã�"<<endl;
	cout<<"g. ������7���������� (dlk7.txt/dlk7_wt.txt)"<<endl;
	cout<<"h. ������8��������Ϣ2 (dlk8.txt/dlk8_wt.txt)���ݲ����ã�"<<endl;
	cout<<"i. ������9��ŷ�޵�ͼ (dlk9.txt/dlk9_wt.txt)"<<endl;
	cout<<"I. ������9 �������ư� (dlk9_wtcz.txt)"<<endl;
	cout<<"j. ������10�����޵�ͼ (dlk10.txt/dlk10_wt.txt)"<<endl;
	cout<<"k. ������11�����ǵ�ͼ (dlk11.txt/dlk11_wt.txt)"<<endl;
	cout<<"l. ������12���Թ�֮ս (dlk12.txt)���ݲ����ã�"<<endl;
	cout<<"m. ������13��������� (dlk13.txt)"<<endl;
	cout<<"n. ������14��Ⱥ������ (dlk14.txt)"<<endl;
	cout<<"o. ������15���İ�Ϫ�� (dlk15.txt)"<<endl;
	cout<<"p. ������16�����Ⱥ (dlk16.txt)"<<endl;
	cout<<"q. ������17���ķ����� (dlk17.txt/dlk17_wt.txt)���ݲ����ã�"<<endl;
	cout<<endl;
	string mapfile;
__choosemap:
	do ch=getch(); while(!isdigit(ch)&&!isalpha(ch));
	switch(ch) {
		case '0': mapfile="random_map.txt"; getN(); break;
		case '1': mapfile="allcity_map.txt"; getN(); getCity(); break;
		case '2': mapfile="allswamp_map.txt"; getN(); break;
		case '3': mapfile="allplain_map.txt"; getN(); break;
		case 'a'...'d': case 'g': case 'i'...'k': {
			int no=ch-'a'+1;
			string nostr;
			if(no==1) nostr="";
			else nostr=to_string(ch-'a'+1);
			cout<<"ѡ���ͼ���ͣ�"<<endl;
			cout<<"0. ��ԭͼ�������� (dlk"<<nostr<<".txt)"<<endl;
			cout<<"1. ������� (dlk"<<nostr<<"_wt.txt)"<<endl;
			char tp=getch();
			while(tp!='0'&&tp!='1') tp=getch();
			N=dlk_sz[ch-'a'+1];
			if(tp=='0') mapfile="dlk"s+nostr+".txt"s;
			else mapfile="dlk"s+nostr+"_wt.txt"s;
		} break;
		case 'A': case 'I': {
			N=dlk_wtcz_sz[ch-'A'+1];
			if(ch-'A'==0) mapfile="dlk_wtcz.txt";
			else mapfile="dlk"s+to_string(ch-'A'+1)+"_wtcz.txt"s;
		} break;
		case 'e': case 'm'...'p': {
			int no=ch-'a'+1;
			string nostr;
			if(no==1) nostr="";
			else nostr=to_string(ch-'a'+1);
			N=dlk_sz[ch-'a'+1];
			mapfile="dlk"s+nostr+".txt"s;
		} break;
		default: goto __choosemap;
	}
	cout<<endl;
	cout<<"�Ƿ��ڼұ����ܱ����� 15%��"<<endl;
	cout<<"1. �� ����. ��"<<endl;
	ch=getch();
	if(ch=='1') K=1;
	cout<<endl;
	cout<<"�Ƿ������ף�"<<endl;
	cout<<"1. ��  ����. ��"<<endl;
	ch=getch();
	if(ch=='1') cheat=1;
	cout<<endl;
	system("cls");
	char createCmd[105]="createmap.exe ";
	strcat(createCmd,to_string(N).c_str());
	strcat(createCmd," ");
	strcat(createCmd,to_string(__citypower).c_str());
	system(createCmd);
	getmap(mapfile);
	print();
	int t=GetTickCount();
	cnt=0;
	while(1) {
		if(kbhit()) {
			char ch=getch();
			if(ch=='e') {
				if(!movement.empty()) movement.pop_back();
			} else if(ch=='q') movement.clear();
			else if(ch=='w') movement.push_back(0);
			else if(ch=='a') movement.push_back(1);
			else if(ch=='s') movement.push_back(2);
			else if(ch=='d') movement.push_back(3);
			else if(ch=='h') movement.push_back(4);
			else if(ch==' ') {
				ch='1';
				while(ch!=' ') ch=getch();
			}
		}
		int nt=GetTickCount();
		if(nt-t<d) continue;
		t=nt;
		++cnt;
		if(cnt>=T) {
			cnt=0;
			for(int i=1; i<=N; ++i)
				for(int j=1; j<=N; ++j)
					if(mp[i][j].type>=P+P+1) ++mp[i][j].x;
		}
		for(int i=1; i<=N; ++i)
			for(int j=1; j<=N; ++j) {
				if(mp[i][j].type<=P+P&&mp[i][j].type>=1) ++mp[i][j].x;
				else if(mp[i][j].type>P+P&&c[i][j]) {
					--mp[i][j].x;
					if(mp[i][j].x==0) mp[i][j].type=-1;
				}
			}
		while(!movement.empty()) {
			bool B=0;
			int m=movement.front();
			movement.pop_front();
			if(m==4) nowx=hx[1],nowy=hy[1];
			else {
				int nx=nowx+dx[m],ny=nowy+dy[m];
				if(nx<1||ny<1||nx>N||ny>N||mp[nx][ny].type==-2);
				else {
					int tp=mp[nowx][nowy].type,x=mp[nowx][nowy].x,nt=mp[nx][ny].type;
					int tmp=0;
					if(tp==1&&seen[1]&&K) {
						tmp=army[1]-land[1];
						tmp*=3;
						tmp/=20;
						if(army[1]>=100) {
							if(x<=tmp) tmp=x-1;
							else tmp=x-tmp;
						}
					}
					x-=tmp;
					if((tp!=1&&tp!=P+1&&tp!=P+P+1)||x<=1);
					else {
						if(nt==1||nt==P+1||nt==P+P+1) mp[nx][ny].x+=x-1;
						else if(x-1>mp[nx][ny].x) {
							mp[nx][ny].x=x-1-mp[nx][ny].x;
							if(nt==-3) mp[nx][ny].type=P+1;
							else if(nt==-1) mp[nx][ny].type=P+P+1;
							else if(nt<=P) kill(1,nt);
							else if(nt<=P+P) mp[nx][ny].type=P+1;
							else mp[nx][ny].type=P+P+1;
						} else mp[nx][ny].x-=x-1;
						mp[nowx][nowy].x=1;
						mp[nowx][nowy].x+=tmp;
						B=1;
					}
					nowx=nx;
					nowy=ny;
				}
			}
			if(B) break;
		}
		for(int i=2; i<=P; ++i) {
			int m=getmove(i);
			if(m==4) px[i]=hx[i],py[i]=hy[i];
			else {
				int nx=px[i]+dx[m],ny=py[i]+dy[m];
				if(nx<1||ny<1||nx>N||ny>N||mp[nx][ny].type==-2);
				else {
					int tp=mp[px[i]][py[i]].type,x=mp[px[i]][py[i]].x,nt=mp[nx][ny].type;
					if((tp!=i&&tp!=i+P&&tp!=i+P+P)||x<=1);
					else {
						int tmp=0;
						if(tp==i&&seen[i]) {
							tmp=army[i]-land[i];
							tmp*=3;
							tmp/=20;
							if(army[i]>=100) {
								if(x<=tmp) tmp=x-1;
								else tmp=x-tmp;
							}
						}
						x-=tmp;
						if(nt==i||nt==i+P||nt==i+P+P) mp[nx][ny].x+=x-1;
						else if(x-1>mp[nx][ny].x) {
							mp[nx][ny].x=x-1-mp[nx][ny].x;
							if(nt==-3) mp[nx][ny].type=i+P;
							else if(nt==-1) mp[nx][ny].type=i+P+P;
							else if(nt<=P) kill(i,nt);
							else if(nt<=P+P) mp[nx][ny].type=i+P;
							else mp[nx][ny].type=i+P+P;
						} else mp[nx][ny].x-=x-1;
						mp[px[i]][py[i]].x=1;
						mp[px[i]][py[i]].x+=tmp;
					}
					lx[i]=px[i];
					ly[i]=py[i];
					px[i]=nx;
					py[i]=ny;
				}
			}
			cout<<endl;
		}
		if(alive&&!cheat) print();
		else print_all();
		getseen();
	}
	return 0;
}

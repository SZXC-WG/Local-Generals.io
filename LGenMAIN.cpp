#include <bits/stdc++.h>
#include "windows.h"
#include "conio.h"
#include "LGenPrint.h"
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

struct block {int type,x;};
int cnt,cnt2,dx[4] {-1,0,1,0},dy[4] {0,-1,0,1},nowx,nowy,
    d2x[8] {-1,-1,-1,0,0,1,1,1},d2y[8] {-1,0,1,-1,1,-1,0,1},
    hx[P+1],hy[P+1],army[P+1],land[P+1],
    px[P+1],py[P+1],lx[P+1],ly[P+1],alivecnt=P;
bool vis[505][505],alive=1,seen[P+1],s[505][505],cheat,K,c[505][505],light[505][505];
block mp[505][505];
void win() {MessageBox(nullptr,"你赢了","",MB_OK);}
void lose(int x) {MessageBox(nullptr,("Player "+name[x]+"赢了").c_str(),"",MB_OK);}
void killed(int x) {MessageBox(nullptr,("Player "+name[x]+"把你杀了").c_str(),"",MB_OK);}
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
//	cout<<"|";
}
void print_all() {
	gotoxy(0,0);
//	cout<<"+";
//	for(int i=1; i<=N; ++i) cout<<"----+";
//	cout<<'\n';
	for(int i=1; i<=N; ++i) {
//		cout<<"|";
		for(int j=1; j<=N; ++j) {
			int f=0,tp=mp[i][j].type,x=mp[i][j].x;
			if(i==nowx&&j==nowy) f=1;
			if(f) SETCOLOR("black");
			switch(tp) {
				case -1:if(c[i][j]) cout<<"===="; else cout<<"    "; resetcolor(); /*cout<<"|";*/ break;
				case -2:cout<<"####"/*<<"|"*/; break;
				case -3:print(f,"white",'[',']',x); break;
				case 1:print(f,col[1],'$','$',x); break;
				case 2 ... P:print(f,col[tp],'{','}',x); break;
				case P+1 ... P+P:print(f,col[tp-P],'[',']',x); break;
				case P+P+1 ... P+P+P:print(f,col[tp-P-P],c[i][j]?'=':' ',c[i][j]?'=':' ',x); break;
			}
		}
		cout<<'\n';
//		cout<<"+";
//		for(int i=1; i<=N; ++i) cout<<"----+";
//		cout<<'\n';
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
//	cout<<"+";
//	for(int i=1; i<=N; ++i) cout<<"----+";
//	cout<<'\n';
	for(int i=1; i<=N; ++i) {
//		cout<<"|";
		for(int j=1; j<=N; ++j) {
			int f=0,tp=mp[i][j].type,x=mp[i][j].x;
			if(i==nowx&&j==nowy) f=1;
			if(f) SETCOLOR("black");
			switch(tp) {
				case -1:if(c[i][j]) cout<<"===="; else cout<<"    "; resetcolor(); /*cout<<"|";*/ break;
				case -2:if(light[i][j]||see(1,i,j)) cout<<"####"/*<<"|"*/; else cout<<"####"/*<<"|"*/; break;
				case -3:if(light[i][j]||see(1,i,j)) print(f,"white",'[',']',x); else cout<<"####"/*<<"|"*/; break;
				case 1:print(f,col[1],'$','$',x); break;
				case P+1:print(f,col[1],'[',']',x); break;
				case P+P+1:print(f,col[1],' ',' ',x); break;
				case 2 ... P:if(light[i][j]||see(1,i,j)) print(f,col[tp],'{','}',x); else cout<<"    "/*<<"|"*/; break;
				case P+2 ... P+P:if(light[i][j]||see(1,i,j)) print(f,col[tp-P],'[',']',x); else if(s[i][j]) cout<<"####"/*<<"|"*/; else cout<<"####"/*<<"|"*/; break;
				case P+P+2 ... P+P+P:if(light[i][j]||see(1,i,j)) print(f,col[tp-P-P],c[i][j]?'=':' ',c[i][j]?'=':' ',x); else cout<<"    "/*<<"|"*/; break;
			}
		}
		cout<<"\n";
//		cout<<"+"; 
//		for(int i=1; i<=N; ++i) cout<<"----+";
//		cout<<'\n';
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

/*************** map information ***************/

void getN() { cout<<"请输入地图大小："; cin>>N; }
int __citypower;
void getCity() { cout<<"请输入城池初始力量："; cin>>__citypower; }
const int dlk_sz[55]= {0,25,40,40,40,49,35,45,50/*40*50*/,50,50,50,50/*50*40*/,50,50,50,-1,50,50,50};
const int dlk_wtcz_sz[55]= {0,25,-1,-1,-1,-1,-1,-1,40,-1,-1,-1,-1,-1,-1,-1,-1,-1};

struct MapInfoS {
	int id;	string chiname; string engname; string auth; int hei; int wid; int generalcnt; int swampcnt; int citycnt; int mountaincnt; int plaincnt;
};
const int mapTOT=25;
MapInfoS maps[205] = {
	/* id , chiname , engname , auth , hei , wid , generalcnt , swampcnt , citycnt , mountaincnt , plaincnt */
	{0,"空","void","void",-2,-2,-2,-2,-2,-2,-2},
	{1,"随机地图","Random","LocalGen",-1,-1,10,-1,-1,-1,-1},
	{2,"完全塔","Full Tower/City","LocalGen",-1,-1,10,0,-1,0,0},
	{3,"完全沼泽","Full Swamp","LocalGen",-1,-1,10,-1,0,0,0},
	{4,"大平原","Plain","LocalGen",-1,-1,10,0,0,0,-1},
	{5,"地理课","Geography Class","nfls_old_salty_fish",25,25,10,102,58,170,285},
	{6,"地理课 无塔重制版","Geography Class (No General Remake)","nfls_old_salty_fish",25,25,0,136,52,172,265},
	{7,"地理课2","Geography Class 2","nfls_old_salty_fish",40,40,15,382,184,354,665},
	{8,"地理课3：川流不息","Geography Class 3: Endless Rivers","nfls_old_salty_fish",40,40,14,642,93,309,542},
	{9,"地理课4：山巅之湖","Geography Class 4: Lake Upon the Mountain","nfls_old_salty_fish",40,40,14,674,136,567,209},
	{10,"地理课5：沼泽迷宫","Geography Class 5: Swamp Labyrinth","AppOfficer",49,49,12,1085,218,1066,20},
	{11,"地理课6：中央宝藏","Geography Class 6: Middle Treasure","AppOfficer",35,35,8,396,119,504,198},
	{12,"地理课7：经典重现","Geography Class 7: Classic Recurred","nfls_old_salty_fish",45,45,25,491,165,603,741},
	{13,"地理课8：川流不息2","Geography Class 8: Endless Rivers 2","AppOfficer",40,50,15,685,177,445,678},
	{14,"地理课9：欧洲地图","Geography Class 9: Europe","nfls_old_salty_fish",50,50,19,845,136,348,1152},
	{15,"地理课9 无塔重制版","Geography Class 9: Europe (No General Remake)","nfls_old_salty_fish",40,40,0,650,92,239,619},
	{16,"地理课10：非洲地图","Geography Class 10: Africa","nfls_old_salty_fish",50,50,29,1338,164,331,638},
	{17,"地理课11：东亚地图","Geography Class 11: East Asia","AppOfficer",50,50,24,678,215,592,991},
	{18,"地理课12：迷宫之战","Geography Class 12: Labyrinth Battle","nfls_old_salty_fish",50,40,0,0,182,646,1172},
	{19,"地理课13：海盗奇兵","Geography Class 13: Pirates","nfls_old_salty_fish",50,50,0,1259,208,0,1033},
	{20,"地理课14：群岛争霸","Geography Class 14: Islands","ktq_cpp",50,50,0,1620,197,265,418},
	{21,"地理课15：幽暗溪流","Geography Class 15: Gloomy Streams","nfls_old_salty_fish",50,50,0,1038,189,998,285},
	{22,"地理课16：深海礁群","Geography Class 16: Deep Sea Reefs","chrhaa",50,50,0,2194,88,208,10},
	{23,"地理课17：四方争锋","Geography Class 17: Directions Striving","chrhaa",43,43,4,428,121,260,1036},
	{24,"地理课18：李联形势","Geography Class 18: LSZC Republic","AppOfficer & nfls_old_salty_fish",50,50,0,999,224,462,815},
	{25,"地理课19：澳大利亚","Geography Class 19: Australia","chrhaa",50,50,0,1348,188,488,476},
};

/*************** screen pages ***************/

enum PAGE {pEXIT,pMain,pCMap};

void MainPage(PAGE);
void ChooseMap(PAGE);
void MapInfo(int,PAGE);

void MainPage(PAGE pFrom=pEXIT) {
__MAINPAGE:
	system("cls");
	printText(sLeft,"Welcome to the 欢迎来到"); toNxtLine();
	printText(sLeft,R"(|                        |   ____             )"); toNxtLine();
	printText(sLeft,R"(|     _____ _____ _____  |   |     _____ _____)"); toNxtLine();
	printText(sLeft,R"(|     |   | |     |   |  |   | ___ |   | |   |)"); toNxtLine();
	printText(sLeft,R"(|     |   | |     |   |  |   |   | |___| |   |)"); toNxtLine();
	printText(sLeft,R"(|____ |___| |____ |__/|_ |_/ |___| |____ |   |)"); toNxtLine();
	toNxtLine();
	printText(sLeft,"Choose one of the options below to begin:"); toNxtLine();
	printText(sLeft,"(Arrow keys to choose; [ENTER] to confirm)"); toNxtLine();
	printText(sLeft,"选择下面的选项之一以开始："); toNxtLine();
	printText(sLeft,"（方向键选择，回车键 [ENTER] 确认）"); toNxtLine();
	toNxtLine();
	printText(sLeft,"  0 旧版     Old Version"); toNxtLine();
	printText(sLeft,"  1 选择地图 Choose Map "); toNxtLine();
	printText(sLeft,"  2 退出     Exit       ");
	char ch; int opt=1,optioncnt=2;
	for(int i=0; i<optioncnt; ++i) printText(sLeft," "),toPreLine();
	printText(sLeft," ");
	for(int i=0; i<opt; ++i) toNxtLine();
	printText(sLeft,">");
	for(int i=0; i<optioncnt-opt; ++i) toNxtLine();
	while(1) {
		ch=getch();
		if(ch==13) {
			switch(opt) {
				case 0: { return; }
				case 1: ChooseMap(pMain); goto __MAINPAGE;
				case 2: exit(0);
			}
		} else if(ch==-32) {
			ch=getch();
			switch(ch) {
				case 72: {
					if(opt>0) --opt;
					else cout<<'\a'<<flush;
					break;
				}
				case 80: {
					if(opt<optioncnt) ++opt;
					else cout<<'\a'<<flush;
					break;
				}
			}
		}
		for(int i=0; i<optioncnt; ++i) printText(sLeft," "),toPreLine();
		printText(sLeft," ");
		for(int i=0; i<opt; ++i) toNxtLine();
		printText(sLeft,">");
		for(int i=0; i<optioncnt-opt; ++i) toNxtLine();
	}
}

void ChooseMap(PAGE pFrom=pMain) {
	system("cls");
	int lpc=0; int opt=1;
__CHOOSEMAP:
	int wx,wy; getwinxy(wx,wy);
	toSpeLine(0);
	for(int i=0; i<wx-1; ++i) printText(sLeft,"|",40),toNxtLine();
	printText(sLeft,"|",40);
	int lpp=wx-3-1-2;
	toSpeLine(0);
	printText(sLeft,"  地图列表 Map Lists: (page "s+to_string(lpc+1)+"/"s+to_string((mapTOT+lpp-1)/lpp)+")     "s); toNxtLine(); 
	printText(sLeft,"  (Press [ESC] to go back to MAIN PAGE)"); toNxtLine(); toNxtLine();
	printText(sLeft,"  00: Previous Page");
	toSpeLine(wx-2);
	printText(sLeft,"  "s+to_string(lpp+1)+": Next Page    "s); 
	toSpeLine(4);
	for(int i=1; i<=lpp; ++i) cout<<setw(35)<<left,printText(sLeft,"  "s+(i<10?"0"s:""s)+to_string(i)+": "+maps[i+lpc*lpp].chiname),toNxtLine();
	char ch;
	for(int i=0; i<=lpp; ++i) printText(sLeft," "),toPreLine();
	printText(sLeft," ");
	for(int i=0; i<opt; ++i) toNxtLine();
	printText(sLeft,">");
	for(int i=0; i<=lpp-opt; ++i) toNxtLine();
	while(1) {
		if(opt!=0 && opt!=lpp+1) MapInfo(lpp*lpc+opt,pCMap);
		ch=getch();
		if(ch==13/*[ENTER]*/) {
			if(opt==0) /* 00: Previous Page */ {
				if(lpc>0) { --lpc; goto __CHOOSEMAP; }
			} else if(opt==lpp+1) /* lpp+1: Next Page */ {
				if((lpc+1)*lpp<mapTOT) { ++lpc; goto __CHOOSEMAP; }
			}
		} else if(ch==27/*[ESC]*/) {
			return;
		} else if(ch==-32/*[Arrow Keys]*/) {
			ch=getch();
			switch(ch) {
				case 72: /*[UP]*/ {
					if(opt>0) --opt;
					else cout<<'\a'<<flush;
					break;
				}
				case 80: /*[DOWN]*/ {
					if(opt<=lpp) ++opt;
					else cout<<'\a'<<flush;
					break;
				}
			}
		}
		toSpeLine(wx-2);
		for(int i=0; i<=lpp; ++i) printText(sLeft," "),toPreLine();
		printText(sLeft," ");
		for(int i=0; i<opt; ++i) toNxtLine();
		printText(sLeft,">");
		for(int i=0; i<=lpp-opt; ++i) toNxtLine();
	}
}

void MapInfo(int mapid,PAGE pFrom=pCMap) {
	/* the map information will be print aligned to left. */
	toSpeLine(2);
	printText(sLeft,maps[mapid].chiname+string(20,' '),42); toNxtLine();
	printText(sLeft,maps[mapid].engname+string(40,' '),42); toNxtLine();
	toNxtLine();
	printText(sLeft,"Author 作者"s,42); toNxtLine();
	printText(sLeft,maps[mapid].auth+string(40,' '),42); toNxtLine();
	toNxtLine();
	printText(sLeft,"Height 行数: "s+to_string(maps[mapid].hei)+string(2,' '),42); toNxtLine();
	printText(sLeft,"Width 列数: "s+to_string(maps[mapid].wid)+string(2,' '),42); toNxtLine();
	toNxtLine();
	printText(sLeft,"General Count 王塔（将军）数"s,42); toNxtLine();
	printText(sLeft,to_string(maps[mapid].generalcnt)+string(4,' '),42); toNxtLine();
	printText(sLeft,"Swamp Count 沼泽数"s,42); toNxtLine();
	printText(sLeft,to_string(maps[mapid].swampcnt)+string(4,' '),42); toNxtLine();
	printText(sLeft,"City/Tower Count 城市数"s,42); toNxtLine();
	printText(sLeft,to_string(maps[mapid].citycnt)+string(4,' '),42); toNxtLine();
	printText(sLeft,"Mountain Count 山地数"s,42); toNxtLine();
	printText(sLeft,to_string(maps[mapid].mountaincnt)+string(4,' '),42); toNxtLine();
	printText(sLeft,"Plain Count 平原数"s,42); toNxtLine();
	printText(sLeft,to_string(maps[mapid].plaincnt)+string(4,' '),42); toNxtLine();
}

/*************** main() function ***************/

HWND hwnd = GetConsoleWindow();
signed main() {
	ios::sync_with_stdio(false);
	ShowWindow(hwnd,SW_MAXIMIZE);
	HideCursor();
	printText(sLeft,"This is a text before loading is completed."); toNxtLine(); 
	printText(sLeft,"这是一个在加载前的文本。"); toNxtLine();
	printText(sLeft,"Please set your font size at this time,"); toNxtLine(); 
	printText(sLeft,"so you can get a better game feedback."); toNxtLine();
	printText(sLeft,"请适当调整您的终端字体大小，"); toNxtLine();
	printText(sLeft,"以获得更好的运行体验。"); toNxtLine();
	toNxtLine();
	printText(sLeft,"Press any key to continue. . ."); toNxtLine(); 
	printText(sLeft,"请按任意键继续. . ."); toNxtLine();
	getch();
	toNxtLine();
	MainPage();
	system("pause & cls");
	cout<<"If you see this paragraph, then you have"<<endl; 
	cout<<"successfully exited the new version."<<endl; 
	cout<<"Here you can use the old version of LocalGen."<<endl; 
	cout<<"如果您看到了这段文字，说明您已成功退出新版。"<<endl;
	cout<<"而在这里，您可以使用旧版 LocalGen。"<<endl;
	cout<<endl;
	char ch;
	cout<<"local generals.io\npress SPACE to start\n"<<flush;
	while(getch()!=' ');
	cout<<endl;
	cout<<"选择地图：（请保证此程序同一目录下有官方的 createmap.exe 文件）"<<endl;
	cout<<"【系列1: 特殊地图】"<<endl;
	cout<<"0. 随机地图 (random_map.txt)"<<endl;
	cout<<"1. 完全塔 (allcity_map.txt)"<<endl;
	cout<<"2. 完全沼泽 (allswamp_map.txt)"<<endl;
	cout<<"3. 大平原 (allplain_map.txt)"<<endl;
	cout<<"【系列2: 地理课 series】"<<endl;
	cout<<"a. 地理课 (dlk.txt/dlk_wt.txt)"<<endl;
	cout<<"A. 地理课 无塔重制版 (dlk_wtcz.txt)"<<endl;
	cout<<"b. 地理课2 (dlk2.txt/dlk2_wt.txt)"<<endl;
	cout<<"c. 地理课3：川流不息 (dlk3.txt/dlk3_wt.txt)"<<endl;
	cout<<"d. 地理课4：山巅之湖 (dlk4.txt/dlk4_wt.txt)"<<endl;
	cout<<"e. 地理课5：沼泽迷宫 (dlk5.txt)"<<endl;
	cout<<"f. 地理课6：中央宝藏 (dlk6.txt/dlk6_wt.txt)（暂不可用）"<<endl;
	cout<<"g. 地理课7：经典重现 (dlk7.txt/dlk7_wt.txt)"<<endl;
	cout<<"h. 地理课8：川流不息2 (dlk8.txt/dlk8_wt.txt)（暂不可用）"<<endl;
	cout<<"i. 地理课9：欧洲地图 (dlk9.txt/dlk9_wt.txt)"<<endl;
	cout<<"I. 地理课9 无塔重制版 (dlk9_wtcz.txt)（暂不可用）"<<endl;
	cout<<"j. 地理课10：非洲地图 (dlk10.txt/dlk10_wt.txt)"<<endl;
	cout<<"k. 地理课11：东亚地图 (dlk11.txt/dlk11_wt.txt)"<<endl;
	cout<<"l. 地理课12：迷宫之战 (dlk12.txt)（暂不可用）"<<endl;
	cout<<"m. 地理课13：海盗奇兵 (dlk13.txt)"<<endl;
	cout<<"n. 地理课14：深海礁群 (dlk14.txt)"<<endl;
	cout<<"o. 地理课15：幽暗溪流 (dlk15.txt)"<<endl;
	cout<<"p. 地理课16：群岛争霸 (dlk16.txt)（暂不可用）"<<endl;
	cout<<"q. 地理课17：四方争锋 (dlk17.txt/dlk17_wt.txt)（暂不可用）"<<endl;
	cout<<"r. 地理课18：李联形势 (dlk18.txt)"<<endl;
	cout<<"s. 地理课19：澳大利亚 (dlk19.txt)"<<endl; 
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
			cout<<"选择地图类型："<<endl;
			cout<<"0. 按原图王塔排列 (dlk"<<nostr<<".txt)"<<endl;
			cout<<"1. 随机王塔 (dlk"<<nostr<<"_wt.txt)"<<endl;
			char tp=getch();
			while(tp!='0'&&tp!='1') tp=getch();
			N=dlk_sz[ch-'a'+1];
			if(tp=='0') mapfile="dlk"s+nostr+".txt"s;
			else mapfile="dlk"s+nostr+"_wt.txt"s;
		} break;
		case 'A': /*case 'I':*/ {
			N=dlk_wtcz_sz[ch-'A'+1];
			if(ch-'A'==0) mapfile="dlk_wtcz.txt";
			else mapfile="dlk"s+to_string(ch-'A'+1)+"_wtcz.txt"s;
		} break;
		case 'e': case 'm'...'o': case 'r'...'s': {
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
	cout<<"是否在家保留总兵力的 15%？"<<endl;
	cout<<"1. 是 其它. 否"<<endl;
	ch=getch();
	if(ch=='1') K=1;
	cout<<endl;
	cout<<"是否开启作弊？"<<endl;
	cout<<"1. 是  其它. 否"<<endl;
	ch=getch();
	if(ch=='1') cheat=1;
	cout<<endl;
	system("cls");
	char createCmd[105]="createmap.exe ";
	strcat(createCmd,to_string(N).c_str());
	strcat(createCmd," ");
	strcat(createCmd,to_string(__citypower).c_str());
	system(createCmd);
	system("cls");
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


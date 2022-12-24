#include <iostream>
#include "maparr_geo.h"
#include "maparr_army.h"
#include "maparr_light.h"
using namespace std;

int m=10;
int x[20],y[20];
mt19937 mtrand(time(nullptr));

void gene_random(const char* file,int sz) {
	freopen(file,"w",stdout);
	int n=sz;
	cout << n << endl;
	for(int i=0; i<m; ++i) x[i]=mtrand()%n+1,y[i]=mtrand()%n+1;
	for(int i=1; i<=n; ++i) {
		for(int j=1; j<=n; ++j) {
			int f=1;
			for(int k=0; k<m; ++k) if(x[k]==i&&y[k]==j) { cout << 0 << ' '; f=0; }
			if(f) cout << -int(mtrand()%4+1) << ' ';
		}
		cout << endl;
	}
	for(int i=1; i<=n; ++i) {
		for(int j=1; j<=n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"%s done.\n",file);
}
void gene_allcity(const char* file,int sz,int citypower) {
	freopen(file,"w",stdout);
	int n=sz;
	cout << n << endl;
	for(int i=0; i<m; ++i) x[i]=mtrand()%n+1,y[i]=mtrand()%n+1;
	for(int i=1; i<=n; ++i) {
		for(int j=1; j<=n; ++j) {
			int f=1;
			for(int k=0; k<m; ++k) if(x[k]==i&&y[k]==j) { cout << 0 << ' '; f=0; }
			if(f) cout << -3 << ' ';
		}
		cout << endl;
	}
	for(int i=1; i<=n; ++i) {
		for(int j=1; j<=n; ++j) cout << citypower << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"%s done.\n",file);
}
void gene_allswamp(const char* file,int sz) {
	freopen(file,"w",stdout);
	int n=sz;
	cout << n << endl;
	for(int i=0; i<m; ++i) x[i]=mtrand()%n+1,y[i]=mtrand()%n+1;
	for(int i=1; i<=n; ++i) {
		for(int j=1; j<=n; ++j) {
			int f=1;
			for(int k=0; k<m; ++k) if(x[k]==i&&y[k]==j) { cout << 0 << ' '; f=0; }
			if(f) cout << -4 << ' ';
		}
		cout << endl;
	}
	for(int i=1; i<=n; ++i) {
		for(int j=1; j<=n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"%s done.\n",file);
}
void gene_allplain(const char* file,int sz) {
	freopen(file,"w",stdout);
	int n=sz;
	cout << n << endl;
	for(int i=0; i<m; ++i) x[i]=mtrand()%n+1,y[i]=mtrand()%n+1;
	for(int i=1; i<=n; ++i) {
		for(int j=1; j<=n; ++j) {
			int f=1;
			for(int k=0; k<m; ++k) if(x[k]==i&&y[k]==j) { cout << 0 << ' '; f=0; }
			if(f) cout << -1 << ' ';
		}
		cout << endl;
	}
	for(int i=1; i<=n; ++i) {
		for(int j=1; j<=n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"%s done.\n",file);
}

void gene_dlk() {
	int n=25;
	freopen("dlk.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) {
			if(dlk_mp[i][j]==-3) cout << 40 << ' ';
			else cout << 0 << ' ';
		}
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk.txt done. ");
	freopen("dlk_wt.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) if(dlk_mp[i][j]==0) dlk_mp[i][j]=-1;
	for(int i=0; i<m; ++i) {
		do x[i]=mtrand()%n,y[i]=mtrand()%n;
		while(dlk_mp[x[i]][y[i]]!=-1);
		dlk_mp[x[i]][y[i]]=0;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) {
			if(dlk_mp[i][j]==-3) cout << 40 << ' ';
			else cout << 0 << ' ';
		}
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk_wt.txt done.\n");
}
void gene_dlk_wtcz() {
	int n=25;
	freopen("dlk_wtcz.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<m; ++i) {
		do x[i]=mtrand()%n,y[i]=mtrand()%n;
		while(dlk_wtcz_mp[x[i]][y[i]]!=-1);
		dlk_wtcz_mp[x[i]][y[i]]=0;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk_wtcz_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) {
			if(dlk_wtcz_mp[i][j]==-3) cout << 40 << ' ';
			else cout << 0 << ' ';
		}
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk_wtcz.txt done.\n");
}
void gene_dlk2() {
	int n=40;
	freopen("dlk2.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) {
			switch(dlk2_mp[i][j]) {
				case -4 ... 0: cout << dlk2_mp[i][j] << ' '; break;
				case -5: cout << -3 << ' '; break;
			}
		}
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) {
			if(dlk2_mp[i][j]==-3) cout << 40 << ' ';
			else if(dlk2_mp[i][j]==-5) cout << 500 << ' ';
			else cout << 0 << ' ';
		}
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk2.txt done. ");
	freopen("dlk2_wt.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) if(dlk2_mp[i][j]==0) dlk2_mp[i][j]=-1;
	for(int i=0; i<m; ++i) {
		do x[i]=mtrand()%n,y[i]=mtrand()%n;
		while(dlk2_mp[x[i]][y[i]]!=-1);
		dlk2_mp[x[i]][y[i]]=0;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) {
			switch(dlk2_mp[i][j]) {
				case -4 ... 0: cout << dlk2_mp[i][j] << ' '; break;
				case -5: cout << -3 << ' '; break;
			}
		}
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) {
			if(dlk2_mp[i][j]==-3) cout << 40 << ' ';
			else if(dlk2_mp[i][j]==-5) cout << 500 << ' ';
			else cout << 0 << ' ';
		}
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk2_wt.txt done.\n");
}
void gene_dlk3() {
	int n=40;
	freopen("dlk3.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk3_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk3_army[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk3.txt done. ");
	freopen("dlk3_wt.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) if(dlk3_mp[i][j]==0) dlk3_mp[i][j]=-1;
	for(int i=0; i<m; ++i) {
		do x[i]=mtrand()%n,y[i]=mtrand()%n;
		while(dlk3_mp[x[i]][y[i]]!=-1);
		dlk3_mp[x[i]][y[i]]=0;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk3_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk3_army[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk3_wt.txt done.\n");
}
void gene_dlk4() {
	int n=40;
	freopen("dlk4.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk4_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk4_army[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk4_light[i][j] << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk4.txt done. ");
	freopen("dlk4_wt.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) if(dlk4_mp[i][j]==0) dlk4_mp[i][j]=-1;
	for(int i=0; i<m; ++i) {
		do x[i]=mtrand()%n,y[i]=mtrand()%n;
		while(dlk4_mp[x[i]][y[i]]!=-1);
		dlk4_mp[x[i]][y[i]]=0;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk4_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk4_army[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk4_light[i][j] << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk4_wt.txt done.\n");
}
void gene_dlk5() {
	int n=49;
	freopen("dlk5.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk5_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk5_army[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk5_light[i][j] << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk5.txt done. ");
}
void gene_dlk6() {}
void gene_dlk7() {
	int n=45;
	freopen("dlk7.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk7_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk7_army[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk7.txt done. ");
	freopen("dlk7_wt.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) if(dlk7_mp[i][j]==0) dlk7_mp[i][j]=-1;
	for(int i=0; i<m; ++i) {
		do x[i]=mtrand()%n,y[i]=mtrand()%n;
		while(dlk7_mp[x[i]][y[i]]!=-1);
		dlk7_mp[x[i]][y[i]]=0;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk7_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk7_army[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk7_wt.txt done.\n");
}
void gene_dlk8() {}
void gene_dlk9() {
	int n=50;
	freopen("dlk9.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk9_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk9_army[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk9.txt done. ");
	freopen("dlk9_wt.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) if(dlk9_mp[i][j]==0) dlk9_mp[i][j]=-1;
	for(int i=0; i<m; ++i) {
		do x[i]=mtrand()%n,y[i]=mtrand()%n;
		while(dlk9_mp[x[i]][y[i]]!=-1);
		dlk9_mp[x[i]][y[i]]=0;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk9_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk9_army[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk9_wt.txt done.\n");
}
void gene_dlk9_wtcz() {
	int n=40;
	freopen("dlk9_wtcz.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<m; ++i) {
		do x[i]=mtrand()%n,y[i]=mtrand()%n;
		while(dlk9_wtcz_mp[x[i]][y[i]]!=-1);
		dlk9_wtcz_mp[x[i]][y[i]]=0;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk9_wtcz_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk9_wtcz_army[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk9_wtcz.txt done. ");
}
void gene_dlk10() {
	int n=50;
	freopen("dlk10.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk10_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk10_army[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk10.txt done. ");
	freopen("dlk10_wt.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) if(dlk10_mp[i][j]==0) dlk10_mp[i][j]=-1;
	for(int i=0; i<m; ++i) {
		do x[i]=mtrand()%n,y[i]=mtrand()%n;
		while(dlk10_mp[x[i]][y[i]]!=-1);
		dlk10_mp[x[i]][y[i]]=0;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk10_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk10_army[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk10_wt.txt done.\n");
}
void gene_dlk11() {
	int n=50;
	freopen("dlk11.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk11_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk11_army[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk11.txt done. ");
	freopen("dlk11_wt.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) if(dlk11_mp[i][j]==0) dlk11_mp[i][j]=-1;
	for(int i=0; i<m; ++i) {
		do x[i]=mtrand()%n,y[i]=mtrand()%n;
		while(dlk11_mp[x[i]][y[i]]!=-1);
		dlk11_mp[x[i]][y[i]]=0;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk11_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk11_army[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk11_wt.txt done.\n");
}
//void gene_dlk12() {
//	int n=50;
//	freopen("dlk12.txt","w",stdout);
//	cout << n << endl;
//	for(int i=0; i<m; ++i) {
//		do x[i]=mtrand()%n,y[i]=mtrand()%n;
//		while(dlk12_mp[x[i]][y[i]]!=-1);
//		dlk12_mp[x[i]][y[i]]=0;
//	}
//	for(int i=0; i<n; ++i) {
//		for(int j=0; j<n; ++j) cout << dlk12_mp[i][j] << ' ';
//		cout << endl;
//	}
//	for(int i=0; i<n; ++i) {
//		for(int j=0; j<n; ++j) cout << dlk12_army[i][j] << ' ';
//		cout << endl;
//	}
//	for(int i=0; i<n; ++i) {
//		for(int j=0; j<n; ++j) cout << dlk12_light[i][j] << ' ';
//		cout << endl;
//	}
//	fclose(stdout);
//	fprintf(stderr,"dlk12.txt done.\n");
//}
void gene_dlk13() {
	int n=50;
	freopen("dlk13.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<m; ++i) {
		do x[i]=mtrand()%n,y[i]=mtrand()%n;
		while(dlk13_mp[x[i]][y[i]]!=-1);
		dlk13_mp[x[i]][y[i]]=0;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk13_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk13_army[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk13_light[i][j] << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk13.txt done.\n");
}
void gene_dlk14() {
	int n=50;
	freopen("dlk14.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<m; ++i) {
		do x[i]=mtrand()%n,y[i]=mtrand()%n;
		while(dlk14_mp[x[i]][y[i]]!=-1);
		dlk14_mp[x[i]][y[i]]=0;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk14_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk14_army[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << 0 << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk14.txt done.\n");
}
void gene_dlk15() {
	int n=50;
	freopen("dlk15.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<m; ++i) {
		do x[i]=mtrand()%n,y[i]=mtrand()%n;
		while(dlk15_mp[x[i]][y[i]]!=-1);
		dlk15_mp[x[i]][y[i]]=0;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk15_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk15_army[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk15_light[i][j] << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk15.txt done.\n");
}
void gene_dlk16() {
	int n=50;
	freopen("dlk16.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk16_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk16_army[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk16_light[i][j] << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk16.txt done. ");
}
void gene_dlk17() {}
void gene_dlk18() {
	int n=50;
	freopen("dlk18.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<m; ++i) {
		do x[i]=mtrand()%n,y[i]=mtrand()%n;
		while(dlk18_mp[x[i]][y[i]]!=-1);
		dlk18_mp[x[i]][y[i]]=0;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk18_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk18_army[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk18_light[i][j] << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk18.txt done.\n");
}
void gene_dlk19() {
	int n=50;
	freopen("dlk19.txt","w",stdout);
	cout << n << endl;
	for(int i=0; i<m; ++i) {
		do x[i]=mtrand()%n,y[i]=mtrand()%n;
		while(dlk19_mp[x[i]][y[i]]!=-1);
		dlk19_mp[x[i]][y[i]]=0;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk19_mp[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk19_army[i][j] << ' ';
		cout << endl;
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) cout << dlk19_light[i][j] << ' ';
		cout << endl;
	}
	fclose(stdout);
	fprintf(stderr,"dlk19.txt done.\n");
}


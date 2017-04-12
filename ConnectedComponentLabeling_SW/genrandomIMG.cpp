
/*------------------------------------- CONFIG ---------------------------------------------------------------*/
#define DEBUG
//#define LINUX

/*------------------------------------- TEMPLATE ---------------------------------------------------------------*/
#ifdef LINUX
#include <bits/stdc++.h>
#endif

#ifndef LINUX
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <bitset>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <istream>
#include <vector>
#include <list>
#include <forward_list>
#include <string>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <stack>
#include <queue>
#include <set>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <ctime>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <utility>
#include <climits>
#include <cassert>
#include <istream>
#include <random>
#include <iterator>
#include <memory>
#include <cctype>
#endif
using namespace std;

#define int long long
#define double long double
#define ll long long
#define ull unsigned long long

#define for_i(start,end,step) for(int i = start; i < (int)end; i += step) // [start, end)
#define for_id(start,end,step) for(int i = start; i > (int)end; i += step) // [start, end)
#define for_j(start,end,step) for(int j = start; j < (int)end; j += step) // [start, end)
#define for_jd(start,end,step) for(int j = start; j > (int)end; j += step) // [start, end)
#define for_(start,end,step) for(int _ = start; _ < (int)end; _ += step) // [start, end)
#define for__(start,end,step) for(int __ = start; __ < (int)end; __ += step) // [start, end)
#define for_it(A) for(auto it = A.begin(); it != A.end(); ++it)

#ifdef DEBUG
#define pr(X) { cerr << #X << " = " << (X) << endl; }
#define pr_(X) { cerr << #X << " = " << (X) << " ; "; }
#define pra(A, start, end) { cerr << #A << '[' << start << ',' << (end - 1) << "] = "; for_(start, end, 1) cerr << A[_] << ' '; cerr << endl; }
#define pra_(A, start, end) { cerr << #A << '[' << start << ',' << (end - 1) << "] = "; for_(start, end, 1) cerr << A[_] << ' '; cerr << " ; "; }
#define prai(A, start, end) { cerr << #A << '[' << start << ',' << (end - 1) << "] = "; for_(start, end, 1) cerr << '[' << _ << ']' << A[_] << ' '; cerr << endl; }
#define prai_(A, start, end) { cerr << #A << '[' << start << ',' << (end - 1) << "] = "; for_(start, end, 1) cerr << '[' << _ << ']' << A[_] << ' '; cerr << " ; "; }
#define pra2(A, start1, end1, start2, end2) {for_(start1, end1, 1) {for__(start2, end2, 1) cerr << '[' << _ << "]["  << __ << ']' << A[_][__] << ' '; cerr << endl;} }
#endif 

const int inf = 1e9 + 7;
#define sq(x) ((x) * (x))
#define PI (2 * acos((double)0))
double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }

typedef pair<int, int> pii;
typedef vector<pair<int, int>> vii;
#define fi first
#define se second
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
#define pb push_back
#define sz(a) (int)(a).size()
#define bg(a) (a).begin()
#define en(a) (a).end()
#define all(a) (a).begin(), (a).end()
#define ms(a,x) memset(a, x, sizeof(a)) //Care: Only init with 0,-1 and char[]
/*----------------------------------- PARAMETERS -----------------------------------------------------------------*/
const int MAXN = 1e6 + 1;



/*------------------------------------- FUNCTIONS ---------------------------------------------------------------*/
#define IMG_HEIGHT 512
#define IMG_WIDTH 512
vvi IMG(IMG_HEIGHT, vi(IMG_WIDTH, 0));
vii cor;

void Randstar(int numStar) {
	cor.clear();
	while (numStar--) {
		int x = rand() % IMG_HEIGHT;
		int y = rand() % IMG_WIDTH;
		cor.push_back({x,y});
	}
}

void generateStar() {
	for_i(0, sz(cor), 1) {
		if(cor[i].fi >= 0 && cor[i].se >= 0) IMG[cor[i].fi][cor[i].se] = 100;
		if (cor[i].fi - 1 >= 0 && cor[i].se >= 0) IMG[cor[i].fi - 1][cor[i].se] = 100;
		if (cor[i].fi - 2 >= 0 && cor[i].se >= 0) IMG[cor[i].fi - 2][cor[i].se] = 100;
		if (cor[i].fi + 1 >= 0 && cor[i].se >= 0) IMG[cor[i].fi + 1][cor[i].se] = 100;

		if (cor[i].fi >= 0 && cor[i].se - 1 >= 0) IMG[cor[i].fi][cor[i].se - 1] = 100;
		if (cor[i].fi >= 0 && cor[i].se + 1 >= 0) IMG[cor[i].fi][cor[i].se + 1] = 100;

		if (cor[i].fi - 1 >= 0 && cor[i].se + 1 >= 0) IMG[cor[i].fi - 1][cor[i].se + 1] = 100;
		if (cor[i].fi + 1 >= 0 && cor[i].se + 1 >= 0) IMG[cor[i].fi + 1][cor[i].se + 1] = 100;
	}
}

void outIMG() {
	for_i(0, sz(IMG), 1) {
		for_j(0, sz(IMG[0]), 1)
			cout << IMG[i][j] << ' ';
		cout << endl;
	}
}

ll solve() {
	Randstar(10);
	generateStar();
	outIMG();

	return 0;
}
/*------------------------------------- MAIN ---------------------------------------------------------------*/
int32_t main(int agrc, char *argv[]) {
#ifdef DEBUG
	freopen("..\\Debug\\Input.txt", "r", stdin);
	freopen("..\\Debug\\Output.txt", "w", stdout);
	freopen("..\\Debug\\Cerr.txt", "w", stderr);
	cerr << fixed << setprecision(6);
#endif
	ios::sync_with_stdio(false);
	cin.tie(false);
	cout << fixed << setprecision(11);
	/*----------------------------------------------------------------------------------------------------*/
	//InOut



	//Set/Clear parameters


	//solve
	solve();

	return 0;
}

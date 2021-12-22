#include <iostream>
#include <vector>

using namespace std;


struct mcomp {
	double gap;
	std::vector<int> assign;
	mcomp(double gap, std::vector<int> assign);
};

mcomp::mcomp (double gap, std::vector<int>assign) {
	this->gap = gap;
	this->assign = assign;
}

int sum (int a, int b, std::vector<int> q) {
	int r = 0;
	if (a > b) {
		return -1;
	}
	for (int i = a; i <= b; i++) {
		r += q[i];
	}
	return r;
}

double min(double a, double b) {
	if (a < b) {
		return a;
	} else {
		return b;
	}
}


int main() {

	// getting inputs
	int n;
	int t;
	int L;
	cin >> n >> t >> L;
	std::vector<int> q;
	int j;
	for (int i = 0; i < n; i++) {
		cin >> j;
		q.emplace_back(j);
	}
	// pre-compute array G
	std::vector<double> G (n*n, 0);
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			int sum_r =  sum(x, y, q);
			// this is the case when x > y
			if (sum_r == -1) {G[x*n+y] = -1;}
			else {
				double gap = L - sum_r;
				if (gap < 0) {gap = -1;}
				else if (x != y) {gap = gap/(y-x);}
				G[x*n+y] = gap;
			}
		}
	}
	std::vector<mcomp*> M(n*t, NULL);
	for (int wow = 0; wow < n*t; wow++) {
		std::vector<int> tempty;
		M[wow] = new mcomp(-1, tempty);
	}
	for (int z = 0; z < n; z++) {
		M[z*t]->gap = G[z*n+n-1];
		M[z*t]->assign.emplace_back(n-z);
	}
	for (int a = n-2; a >= 0; a--) {
		for (int b = 1; b < t; b++) {
			for (int c = a; c <= n-2; c++) {
				if ((n-a) < b+1) {;}
				else if (c == a) {
					M[a*t+b]->gap = min(G[a*n+c], M[(c+1)*t+b-1]->gap);
					M[a*t+b]->assign = M[(c+1)*t+b-1]->assign;
					M[a*t+b]->assign.emplace_back(c-a+1);
				}
				else {
					double calc = min(G[a*n+c], M[(c+1)*t+b-1]->gap);
					if (M[a*t+b]->gap < calc) {
						M[a*t+b]->gap = calc;
						M[a*t+b]->assign = M[(c+1)*t+b-1]->assign;
						M[a*t+b]->assign.emplace_back(c-a+1);
					}
				}
			}
		}
	}
	if (M[t-1]->gap < 0) {std::cout << "IMPOSSIBLE" << endl;}
	else {
		std::cout << M[t-1]->gap << endl;
		for (int result = t-1; result >=0; result--) {
			cout << M[t-1]->assign[result] << " ";
		}
		cout << endl;
	}
	for (auto &s: M) {
		delete s;
	}
}










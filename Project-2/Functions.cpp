#include "Declaration.h"
#include <cmath>

Term :: Term(){
	coef = exp = 0;
}

Term :: Term(int c, int e) {
	coef = c;
	exp = e;
}

int Term :: getCoef() const{
	return coef;
}

int Term :: getExp() const{
	return exp;
}

void Term :: setCoef(int t) {
	coef = t;
}

void Term :: setExp(int t) {
	exp = t;
}

Polynomial :: Polynomial() {
	len_of_terms = terms_default_len;
	terms = new Term[len_of_terms];
}

Polynomial :: Polynomial(int t) {
	len_of_terms = t;
	terms = new Term[len_of_terms];
}

int Polynomial :: getLength() const{
	return len_of_terms;
}

void Polynomial :: setLength(int len) {
	len_of_terms = len;
}

Term & Polynomial :: getTerm(int pos) {
	return terms[pos];
}

void Polynomial :: terms_swap(Term &a, Term &b) {
	int tmp1, tmp2;
	tmp1 = a.getCoef();
	a.setCoef(b.getCoef());
	b.setCoef(tmp1);
	tmp2 = a.getExp();
	a.setExp(b.getExp());
	b.setExp(tmp2);
}

void Polynomial :: terms_sort() {
	for (int i = 0; i < len_of_terms - 1; i++) {
		for (int j = len_of_terms - 1; j > i; j--) {
			if (getTerm(j).getExp() > getTerm(j - 1).getExp()) {
				terms_swap(getTerm(j), getTerm(j - 1));
			}
		}
	}
}

void Polynomial :: term_delete(int j) {
	getTerm(j).setCoef(0);
	getTerm(j).setExp(0);
	terms_swap(getTerm(j), getTerm(len_of_terms - 1));
	len_of_terms--;
}

void Polynomial :: terms_merge() {
	for (int i = 0; i < len_of_terms; i++) {
		for (int j = i + 1; j < len_of_terms; j++) {
			if (getTerm(j).getExp() == getTerm(i).getExp()) {
				getTerm(i).setCoef(getTerm(i).getCoef() + getTerm(j).getCoef());
				term_delete(j);
				j--;
			}
		}
	}
}

Polynomial& operator+(Polynomial &a, Polynomial &b) {
	Polynomial c(a.getLength() + b.getLength());
	Polynomial *tmp = &c;
	for (int i = 0; i < a.getLength(); i++) {
		c.getTerm(i).setCoef(a.getTerm(i).getCoef());
		c.getTerm(i).setExp(a.getTerm(i).getExp());
	}
	for (int i = a.getLength(); i < a.getLength() + b.getLength(); i++) {
		c.getTerm(i).setCoef(b.getTerm(i - a.getLength()).getCoef());
		c.getTerm(i).setExp(b.getTerm(i - a.getLength()).getExp());
	}
	c.terms_merge();
	c.terms_sort();
	return *tmp;
}

Polynomial& operator-(Polynomial &a, Polynomial &b) {
	Polynomial c(a.getLength() + b.getLength());
	Polynomial *tmp = &c;
	for (int i = 0; i < a.getLength(); i++) {
		c.getTerm(i).setCoef(a.getTerm(i).getCoef());
		c.getTerm(i).setExp(a.getTerm(i).getExp());
	}
	for (int i = a.getLength(); i < a.getLength() + b.getLength(); i++) {
		c.getTerm(i).setCoef(-(b.getTerm(i - a.getLength()).getCoef()));
		c.getTerm(i).setExp(b.getTerm(i - a.getLength()).getExp());
	}
	c.terms_merge();
	c.terms_sort();
	return *tmp;
}

Polynomial& operator*(int n, Polynomial& poly) {
	Polynomial c(poly.getLength());
	Polynomial *tmp = &c;
	for (int i = 0; i < c.getLength(); i++) {
		c.getTerm(i).setCoef(poly.getTerm(i).getCoef() * n);
		c.getTerm(i).setExp(poly.getTerm(i).getExp());
	}
	return *tmp;
}

ostream& operator<<(ostream& out, Polynomial& poly) {
	bool flag = 0;
	if (poly.getTerm(0).getCoef()) {
		cout << poly.getTerm(0).getCoef() << "x^" << poly.getTerm(0).getExp();
		flag = 1;
	}
	for (int j = 1; j < poly.getLength(); j++) {
		if (poly.getTerm(j).getCoef() > 0) {
			cout << " + " << poly.getTerm(j).getCoef() << "x^" << poly.getTerm(j).getExp();
			flag = 1;
		}
		if (poly.getTerm(j).getCoef() < 0) {
			cout << " - " << -poly.getTerm(j).getCoef() << "x^" << poly.getTerm(j).getExp();
			flag = 1;
		}
		if (poly.getTerm(j).getCoef() == 0) continue;
	}
	if (!flag) cout << 0;
	return out;
}

long long evaluate(int x, Polynomial& poly) {
	long long result = 0;
	for (int i = 0; i < poly.getLength(); i++) {
		result += poly.getTerm(i).getCoef() * pow(x, poly.getTerm(i).getExp());
	}
	return result;
}

void welcome() {
	cout << "+------------------------------------------------------------+\n"
	 	 << "|                欢迎使用大表哥多项式计算器                  |\n"
		 << "+------------------------------------------------------------+\n"
		 << "|功能如下：                                                  |\n"
		 << "|    1.新建一条多项式；                                      |\n"
		 << "|    2.输入计算式进行多项式加或减或常数乘法操作；            |\n"
		 << "|    3.求多项式代入某点的值；                                |\n"
		 << "|    4.删除一条多项式；                                      |\n"
		 << "|    5.显示所有储存多项式；                                  |\n"
		 << "|    6.返回主菜单（查看功能列表）；                          |\n"
		 << "|    0.退出系统并保存。                                      |\n"
		 << "+------------------------------------------------------------+\n";
}

void read_file(Polynomial *polys, int &tail) {
	ifstream fread;
	fread.open("Poly_store.txt");
	int polys_len;
	fread >> polys_num;
	tail = polys_num;
	int i = 0;
	while (i < polys_num) {
		fread >> polys_len;
		polys[i].setLength(polys_len);
		int j = 0;
		while (j < polys_len) {
			int tmp1, tmp2;
			fread >> tmp1 >> tmp2;
			polys[i].getTerm(j).setCoef(tmp1);
			polys[i].getTerm(j).setExp(tmp2);
			j++;
		}
		i++;
	}
}

void save_file(Polynomial *polys, int polys_num) {
	int i = 0, j;
	ofstream fsave;
	fsave.open("Poly_store.txt");
	fsave << polys_num << endl;
	while (i < polys_num) {
		j = 0;
		fsave << polys[i].getLength() << endl;
		while (j < polys[i].getLength()){
			fsave <<  polys[i].getTerm(j).getCoef() << ' ' << polys[i].getTerm(j).getExp() << endl;
			j++;
		}
		i++;
	}
	fsave.close();
}

void new_poly(Polynomial* polys, Polynomial poly) {
	polys_num++;
	polys[polys_num - 1].setLength(poly.getLength());
	for (int i = 0; i < poly.getLength(); i++) {
		polys[polys_num - 1].getTerm(i).setCoef(poly.getTerm(i).getCoef());
		polys[polys_num - 1].getTerm(i).setExp(poly.getTerm(i).getExp());
	}
}

void delete_poly(Polynomial* polys, int p) {
	for (int i = 0; i < polys[p].getLength(); i++) {
		polys[p].getTerm(i).setCoef(0);
		polys[p].getTerm(i).setExp(0);
	}
	polys[p].setLength(0);
}

bool legal_to_trans(string tmp) {
	bool flag = 1;
	int i, j, k, t;
	for (i = 0; i < tmp.size() - 4;) {
		if (tmp[i] == '(') {
			j = i + 2;
			if (!(tmp[i + 1] == '-' || (tmp[i + 1] >= '0' && tmp[i + 1] <= '9'))) {
				flag = 0;
				break;
			}
			while (tmp[j] != ',') {
				j++;
			}
			if (j > tmp.size() - 3) {
				flag = 0;
				break;
			}
			for (t = i + 2; t < j; t++) {
				if (tmp[t] < '0' || tmp[t] > '9') {
					flag = 0;
					break;
				}
			}
			if (flag == 0) break;
			k = j + 2;
			if (!(tmp[j + 1] == '-' || (tmp[j + 1] >= '0' && tmp[j + 1] <= '9'))) {
				flag = 0;
				break;
			}
			while (tmp[k] != ')') {
				k++;
			}
			if (k > tmp.size() - 1) {
				flag = 0;
				break;
			}
			for (t = j + 2; t < k; t++) {
				if (tmp[t] < '0' || tmp[t] > '9') {
					flag = 0;
					break;
				}
			}
			if (flag == 0) break;
			if (flag) {
				i = k + 1;
				continue;
			}
		} else {
			flag = 0;
			break;
		}
	}
	return flag;
}

void trans_into_poly(Polynomial *polys, int pos, string tmp) {
	int tmp1 = 0, tmp2 = 0, len = 0;
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i] == '(') len++;
	}
	polys[pos].setLength(len);
	int l1 = 1, r1, l2, r2, ex1, ex2;
	for (int i = 0; i < len; i++) {
		ex1 = 0, ex2 = 0;
		tmp1 = 0, tmp2 = 0;
		for (int j = l1 + 1; j < tmp.size(); j++) {
			if (tmp[j] == ',') {
				r1 = j;
				break;
			}
		}
		for (int k = r1 - 1; k > l1; k--) {
			tmp1 += (tmp[k] - '0') * pow(10, ex1);
			ex1++;
		}
		if (tmp[l1] == '-') tmp1 = -tmp1;
		else tmp1 += (tmp[l1] - '0') * pow(10, ex1);
		l2 = r1 + 1;
		for (int j = l2 + 1; j < tmp.size(); j++) {
			if (tmp[j] == ')') {
				r2 = j;
				break;
			}
		}
		for (int k = r2 - 1; k > l2; k--) {
			tmp2 += (tmp[k] - '0') * pow(10, ex2);
			ex2++;
		}
		if (tmp[l2] == '-') tmp2 = -tmp2;
		else tmp2 += (tmp[l2] - '0') * pow(10, ex2);
		l1 = r2 + 2;
		polys[pos].getTerm(i).setCoef(tmp1);
		polys[pos].getTerm(i).setExp(tmp2);
	}
	polys[pos].terms_merge();
	polys[pos].terms_sort();
	for (int i = 0; i < polys[pos].getLength(); i++) {
		if (polys[pos].getTerm(i).getCoef() == 0) {
			polys[pos].term_delete(i);
		}
	}
}


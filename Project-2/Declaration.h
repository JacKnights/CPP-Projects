#ifndef DECLARATION_H
#define DECLARATION_H

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

const int terms_default_len = 100;
	//单条多项式默认的项数 
const int polys_default_len = 100;
	//默认的多项式数目 
int polys_num;
	//多项式数目 

class Term {
  private:
  	int coef;  //系数 
  	int exp;  //指数 
  	
  public:
  	Term();  //默认构造函数 
	Term(int, int);  //参数为系数，指数的构造函数 
	int getCoef() const;  //获取系数 
	int getExp() const;  //获取指数 
	void setCoef(int);  //设置系数 
	void setExp(int);  //设置指数 
};

class Polynomial {
  private:
	Term *terms;  //单条多项式的单项的数组 
	int len_of_terms;  // 单条多项式所含项数 
	
  public:
  	int getLength() const;  //获取项数 
  	void setLength(int);  //设置项数 
  	Term& getTerm(int);  //获取单项 
  	Polynomial();
  	Polynomial(int);  //参数项数的构造函数 
  	void terms_swap(Term &, Term &);  //交换两项 
	void terms_sort();  //将所有单项排序 
	void terms_merge();  //整合指数相同的单项 
	void term_delete(int);  //删除单项 
};

void welcome();  //输出主界面 

void read_file(Polynomial *, int&);  //打开保存多项式的文件 

void save_file(Polynomial*, int);  //保存数据并关闭文件 

bool legal_to_trans(string);  //判断输入的多项式是否合法 

void trans_into_poly(Polynomial*, int, string);  //将合法的输入转换成多项式 

Polynomial& operator+(Polynomial&, Polynomial&);  //多项式间的加法 

Polynomial& operator-(Polynomial&, Polynomial&);  //多项式间的减法 

Polynomial& operator*(int, Polynomial&);  //多项式与常数的乘法 

ostream& operator<<(ostream&, Polynomial&);  //多项式的输出重载 

long long evaluate(int, Polynomial&);  //多项式求值 

void new_poly(Polynomial*, Polynomial);  //新建一条多项式 

void delete_poly(Polynomial*, int);  //删除一条多项式 
#endif

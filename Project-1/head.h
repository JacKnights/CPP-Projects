#include <iostream>
#include <fstream>
#include <string>
#ifndef head_h
#define head_h
using namespace std;
const int NUM_OF_OBJECTS = 1000;  //预设上限为1000
class Book {
  public:
  	int num;
 	string name;
 	bool condition;
 	int borrowed;
 	Book(string newBook = "\0", int newNum = 0);
};   //定义Book类，对象表示某册图书，成员包括书名，数量，借阅状态及借阅数量，以及构造函数 

Book :: Book(string newBook, int newNum) {
	name = newBook;
	num = newNum;
	condition = 0;
	borrowed = 0;
}   //用于初始化对象的构造函数 

Book books[NUM_OF_OBJECTS];  //最多支持保存NUM_OF_OBJECTS个books成员的信息

void read_file();  //打开文件library并将文件中的数据读到books数组成员中

void save_file();  //将books数组成员保存入文件library中 

void print_Storage();  //一次性打印所有图书信息

void close_file();  //关闭文件 

void welcome();  //输出开始界面 

void query_book(string name);  //查询指定的图书信息 

void delete_book(string name);  //清除该书信息

void add_book(string name, int num);  //增加该书项目

void return_book(string name, int num);  //归还图书，若原先无此书信息，则新增该书项目 

void borrow_book(string name, int num);  //借出图书，若超出库存则警告 

int find_book(string name);  //查询该名称的图书，有则返回该书当前位置，无则返回0 

void sort_name(); //按书名字典排序 

void sort_num_ascending();  //按图书当前库存量升序排列 

void sort_num_descending();  //按图书当前库存量降序排列 

#endif


#include"Head.h"
using namespace std;
int BOOK_TYPES; //不同的图书数量

void read_file() {  //打开文件library并将文件中的数据读到books数组成员中
	int i = 1;
	ifstream fread;
	fread.open("Library.txt");
	while (1) {
    	fread >> books[i].name >> books[i].num >> books[i].condition >> books[i].borrowed;
    	i++;
    	if(fread.eof()) {
    		BOOK_TYPES = i - 2;
  			break;
 		}
	}
}

void save_file() {  //将books数组成员保存入文件library中
	int i = 1;
	ofstream fsave;
	fsave.open("Library.txt");
	while (i <= BOOK_TYPES) {
		fsave << books[i].name << "	" << books[i].num << " " << books[i].condition  << " " << books[i].borrowed << endl;
		i++;
	}
}

void print_Storage() {  //一次性打印所有图书信息
	int i = 1;
	while (i <= BOOK_TYPES) {
		cout << "	书名:" << books[i].name << "		数量:" << books[i].num;
		if (books[i].condition) {
			cout << "	借出:" << books[i].borrowed << endl;
		} else {
			cout << endl;
		}
		i++;
	}
}

void close_file() {  //关闭文件 
	ofstream fclose;
    fclose.close();
}

void welcome() {  //输出开始界面
	cout << "------------------------------------" << endl
		 << "------欢迎使用SYSU图书管理系统------" << endl
		 << "------------------------------------" << endl
		 << "--按1归还图书，按2借阅图书，按3新增书目，按4删除书名" << endl
		 << "--按5查询指定书目，按6打印存书信息，按7按书名排序" << endl
		 << "--按8、9分别按数量升序、降序排序，按10即时保存，按0退出" << endl 
		 << "请选择服务：";
}

int find_book(string name) {  //查询该名称的图书，有则返回该书当前位置，无则返回0
	int i = 1;
	for (i = 1; i <= BOOK_TYPES; i++) {
		if (books[i].name == name) {
			return i;
		}	
	}
	if (i > BOOK_TYPES) {
		return 0;
	}	
}

void query_book(string name) {  //查询指定的图书信息
	int i = find_book(name);
	if (i) {
		cout << "	书名:" << books[i].name << "		数量:" << books[i].num;
		if (books[i].condition) {
			cout << "	借出:" << books[i].borrowed << endl;
		} else {
			cout << endl;
		}
	} else {
		cout << "	查无此书！" << endl;
	} 
}

void delete_book(string name) {  //清除该书信息 
	if (find_book(name)) {
		books[find_book(name)] = books[BOOK_TYPES];
		books[BOOK_TYPES] = Book("\0", 0);
		BOOK_TYPES--;
	} else{
		cout << "	无此书！" << endl;
	}
}

void add_book(string name, int num) {  //增加该书项目 
	BOOK_TYPES++;
	books[BOOK_TYPES] = Book(name, num);
}

void return_book(string name, int num) {  //归还图书，若原先无此书信息，则新增该书项目
	if (find_book(name)) {
		books[find_book(name)].num += num;
		if (books[find_book(name)].borrowed >= num) {
			books[find_book(name)].borrowed -= num;
		} else {
			books[find_book(name)].borrowed = 0;
		}
		if (books[find_book(name)].borrowed == 0) {
			books[find_book(name)].condition = 0;
		}
	} else {  //原先无此书信息，则新增该书项目
		add_book(name, num);
	}
}

void borrow_book(string name, int num) {  //借出图书，若超出库存则警告
	if (find_book(name) && (books[find_book(name)].num >= num)) {
		books[find_book(name)].num -= num;
		books[find_book(name)].condition = 1;
		books[find_book(name)].borrowed += num;
	} else {
		cout << "	抱歉，该书数量不足！" << endl;
	}
}

void sort_name() { //按书名字典排序
	int i, j;
	Book tmp;
	for (i = 1; i < BOOK_TYPES; i++) {
		for (j = BOOK_TYPES; j > i ; j--) {
			if (books[j].name < books[j - 1].name) {
				tmp = books[j];
				books[j] = books[j - 1];
				books[j - 1] = tmp;
			}
		}
	}
}

void sort_num_ascending() { //按图书当前库存量升序排列
	int i, j;
	Book tmp;
	for (i = 1; i < BOOK_TYPES; i++) {
		for (j = BOOK_TYPES; j > i ; j--) {
			if (books[j].num < books[j - 1].num) {
				tmp = books[j];
				books[j] = books[j - 1];
				books[j - 1] = tmp;
			}
		}
	}
}

void sort_num_descending() { //按图书当前库存量降序排列
	int i, j;
	Book tmp;
	for (i = 1; i < BOOK_TYPES; i++) {
		for (j = BOOK_TYPES; j > i ; j--) {
			if (books[j].num > books[j - 1].num) {
				tmp = books[j];
				books[j] = books[j - 1];
				books[j - 1] = tmp;
			}
		}
	}
}

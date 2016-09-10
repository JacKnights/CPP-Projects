#include"Head.h"
using namespace std;
int BOOK_TYPES; //��ͬ��ͼ������

void read_file() {  //���ļ�library�����ļ��е����ݶ���books�����Ա��
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

void save_file() {  //��books�����Ա�������ļ�library��
	int i = 1;
	ofstream fsave;
	fsave.open("Library.txt");
	while (i <= BOOK_TYPES) {
		fsave << books[i].name << "	" << books[i].num << " " << books[i].condition  << " " << books[i].borrowed << endl;
		i++;
	}
}

void print_Storage() {  //һ���Դ�ӡ����ͼ����Ϣ
	int i = 1;
	while (i <= BOOK_TYPES) {
		cout << "	����:" << books[i].name << "		����:" << books[i].num;
		if (books[i].condition) {
			cout << "	���:" << books[i].borrowed << endl;
		} else {
			cout << endl;
		}
		i++;
	}
}

void close_file() {  //�ر��ļ� 
	ofstream fclose;
    fclose.close();
}

void welcome() {  //�����ʼ����
	cout << "------------------------------------" << endl
		 << "------��ӭʹ��SYSUͼ�����ϵͳ------" << endl
		 << "------------------------------------" << endl
		 << "--��1�黹ͼ�飬��2����ͼ�飬��3������Ŀ����4ɾ������" << endl
		 << "--��5��ѯָ����Ŀ����6��ӡ������Ϣ����7����������" << endl
		 << "--��8��9�ֱ��������򡢽������򣬰�10��ʱ���棬��0�˳�" << endl 
		 << "��ѡ�����";
}

int find_book(string name) {  //��ѯ�����Ƶ�ͼ�飬���򷵻ظ��鵱ǰλ�ã����򷵻�0
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

void query_book(string name) {  //��ѯָ����ͼ����Ϣ
	int i = find_book(name);
	if (i) {
		cout << "	����:" << books[i].name << "		����:" << books[i].num;
		if (books[i].condition) {
			cout << "	���:" << books[i].borrowed << endl;
		} else {
			cout << endl;
		}
	} else {
		cout << "	���޴��飡" << endl;
	} 
}

void delete_book(string name) {  //���������Ϣ 
	if (find_book(name)) {
		books[find_book(name)] = books[BOOK_TYPES];
		books[BOOK_TYPES] = Book("\0", 0);
		BOOK_TYPES--;
	} else{
		cout << "	�޴��飡" << endl;
	}
}

void add_book(string name, int num) {  //���Ӹ�����Ŀ 
	BOOK_TYPES++;
	books[BOOK_TYPES] = Book(name, num);
}

void return_book(string name, int num) {  //�黹ͼ�飬��ԭ���޴�����Ϣ��������������Ŀ
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
	} else {  //ԭ���޴�����Ϣ��������������Ŀ
		add_book(name, num);
	}
}

void borrow_book(string name, int num) {  //���ͼ�飬����������򾯸�
	if (find_book(name) && (books[find_book(name)].num >= num)) {
		books[find_book(name)].num -= num;
		books[find_book(name)].condition = 1;
		books[find_book(name)].borrowed += num;
	} else {
		cout << "	��Ǹ�������������㣡" << endl;
	}
}

void sort_name() { //�������ֵ�����
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

void sort_num_ascending() { //��ͼ�鵱ǰ�������������
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

void sort_num_descending() { //��ͼ�鵱ǰ�������������
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

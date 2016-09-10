#include "head.h"
#include "Function.cpp"
using namespace std;
int main() {
	int service, bookNum;
	string bookName;	
	welcome();
	read_file();
	cin >> service;
	while (service) {
		switch (service) {
		  	case 1:
				cout <<"������黹��������Ŀ��";
				cin >> bookName >> bookNum;
				return_book(bookName, bookNum);
				cout << "	�ɹ��黹��" << endl;
				break;
			case 2:
				cout <<"�����������������Ŀ��";
				cin >> bookName >> bookNum;
				borrow_book(bookName, bookNum);
				cout << "	�ɹ������" << endl;
				break;
			case 3:
				cout <<"������������������Ŀ��";
				cin >> bookName >> bookNum;
				add_book(bookName, bookNum);
				cout << "	�ɹ��������飡" << endl;
				break;
			case 4:
			 	cout <<"������ɾ��������";
				cin >> bookName >> bookNum;
				delete_book(bookName);
				cout << "	�ɹ�ɾ�����飡" << endl;
				break;
			case 5:
				cout <<"�������ѯ������";
				cin >> bookName;
				query_book(bookName);
				break;
			case 6:
				print_Storage();
				cout << "	��ǰ��治ͬͼ����" << BOOK_TYPES << "��" << endl;
				break;
			case 7:
				sort_name();
				cout <<"	������ɣ�" << endl;
				break;
			case 8:
				sort_num_ascending();
				cout <<"	������ɣ�" << endl;
				break;
			case 9:
				sort_num_descending();
				cout <<"	������ɣ�" << endl;
				break;
			case 10:
				save_file();
				cout <<"	������ɣ�" << endl;
				break;
			default:
				cout << "	�޴˹��ܣ���ѡ����ȷ����" << endl; 
				break;
		}
		cout <<"�������"; 
		cin >> service;
	}
	save_file();
	close_file();
	return 0;
}

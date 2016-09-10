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
				cout <<"请输入归还书名、数目：";
				cin >> bookName >> bookNum;
				return_book(bookName, bookNum);
				cout << "	成功归还！" << endl;
				break;
			case 2:
				cout <<"请输入借阅书名、数目：";
				cin >> bookName >> bookNum;
				borrow_book(bookName, bookNum);
				cout << "	成功借出！" << endl;
				break;
			case 3:
				cout <<"请输入新增书名、数目：";
				cin >> bookName >> bookNum;
				add_book(bookName, bookNum);
				cout << "	成功新增该书！" << endl;
				break;
			case 4:
			 	cout <<"请输入删除书名：";
				cin >> bookName >> bookNum;
				delete_book(bookName);
				cout << "	成功删除该书！" << endl;
				break;
			case 5:
				cout <<"请输入查询书名：";
				cin >> bookName;
				query_book(bookName);
				break;
			case 6:
				print_Storage();
				cout << "	当前库存不同图书有" << BOOK_TYPES << "类" << endl;
				break;
			case 7:
				sort_name();
				cout <<"	排序完成！" << endl;
				break;
			case 8:
				sort_num_ascending();
				cout <<"	排序完成！" << endl;
				break;
			case 9:
				sort_num_descending();
				cout <<"	排序完成！" << endl;
				break;
			case 10:
				save_file();
				cout <<"	保存完成！" << endl;
				break;
			default:
				cout << "	无此功能，请选择正确服务！" << endl; 
				break;
		}
		cout <<"请继续："; 
		cin >> service;
	}
	save_file();
	close_file();
	return 0;
}

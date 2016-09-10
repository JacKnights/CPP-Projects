#include "Functions.cpp"
#include <cstdlib>
int main() {
	int service, tail = 0;  //tail为多项式数组的末尾的序号 
	welcome();
	Polynomial * polys;
	polys = new Polynomial[polys_default_len];
	read_file(polys, tail);
	cout << "      请选择功能：";
	cin >> service;    //输入选择使用的功能 
	while (service) {
		switch (service) {
			case 1:{
				cout << "新建一条多项式，请输入:";
				string tmp;
				cin >> tmp;
				if (legal_to_trans(tmp)) {
					trans_into_poly(polys, tail, tmp);
					cout << "输入合法，新建成功！\n";
					tail++;
					polys_num++; 
				} else {
					cout << "输入不合法，新建失败！\n";
				}
				break;
			}	
			case 2:{
				cout << "请输入计算式:";
				int a, b;
				char operation;
				cin >> a >> operation >> b;
				if (operation == '+' || operation == '-') {
					if (a >= 0 && a < polys_num && b >= 0 && b < polys_num) {
						Polynomial result(polys[a].getLength() + polys[b].getLength());
						if (operation == '+') {
							result = polys[a] + polys[b];
						}
						if (operation == '-') {
							result = polys[a] - polys[b];
						}
						cout << " (" << polys[a] << ") " << operation << " (" << polys[b] << ")" << endl;
						cout << "= " << result << endl;
						new_poly(polys, result);
					} else {
						cout << "多项式不存在！" << endl;
					}	
				} else if(operation == '*') {
					if (b >= 0 && b < polys_num) {
						Polynomial result(polys[b].getLength());
						result = a * polys[b];
						cout << a << " " << operation << " (" << polys[b] << ")" << endl;
						cout << "= " << result << endl;
						new_poly(polys, result);
					} else {
						cout << "多项式不存在！" << endl;
					}
				} else {
					cout << "未定义操作！" << endl;
				}
				break;
			}	
			case 3:{
				cout << "请选择计算的多项式：";
				int p;
				cin >> p;
				if (p >= 0 && p < polys_num) {
					cout << "未知数x = ";
					int x;
					cin >> x;
					cout << evaluate(x, polys[p]) << endl;
				} else {
					cout << "多项式不存在！" << endl;
				}
				break;
			}
			case 4:{
				cout << "请选择删除的多项式：";
				int p;
				cin >> p;
				if (p >= 0 && p < polys_num) {
					delete_poly(polys, p);
					cout << "删除成功！" << endl;
				} else {
					cout << "多项式不存在！" << endl;
				}
				break;
				break;
			} 
			case 5:{
				cout << "当前储存多项式共有如下：" << endl;
				tail = polys_num;
				for (int i = 0; i < tail; i++) {
					polys[i].terms_merge();
					polys[i].terms_sort();
					cout << "(" <<i << ") "; 
					cout << polys[i] << endl;
				}
				break;
			}
			case 6:{
				system("cls");    //清空先前使用痕迹
				welcome();    //返回主界面
				break;
			} 
			default:{
				cout << "无此功能！" << endl;  //当选择未定义功能时报错 
				break;
			}
		}
		cout << "————————————" << endl  << "      请选择功能："; 
		cin >> service;
	}
	save_file(polys, tail);  //保存并关闭文件 
	return 0;
}

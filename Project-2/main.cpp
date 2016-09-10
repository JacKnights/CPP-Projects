#include "Functions.cpp"
#include <cstdlib>
int main() {
	int service, tail = 0;  //tailΪ����ʽ�����ĩβ����� 
	welcome();
	Polynomial * polys;
	polys = new Polynomial[polys_default_len];
	read_file(polys, tail);
	cout << "      ��ѡ���ܣ�";
	cin >> service;    //����ѡ��ʹ�õĹ��� 
	while (service) {
		switch (service) {
			case 1:{
				cout << "�½�һ������ʽ��������:";
				string tmp;
				cin >> tmp;
				if (legal_to_trans(tmp)) {
					trans_into_poly(polys, tail, tmp);
					cout << "����Ϸ����½��ɹ���\n";
					tail++;
					polys_num++; 
				} else {
					cout << "���벻�Ϸ����½�ʧ�ܣ�\n";
				}
				break;
			}	
			case 2:{
				cout << "���������ʽ:";
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
						cout << "����ʽ�����ڣ�" << endl;
					}	
				} else if(operation == '*') {
					if (b >= 0 && b < polys_num) {
						Polynomial result(polys[b].getLength());
						result = a * polys[b];
						cout << a << " " << operation << " (" << polys[b] << ")" << endl;
						cout << "= " << result << endl;
						new_poly(polys, result);
					} else {
						cout << "����ʽ�����ڣ�" << endl;
					}
				} else {
					cout << "δ���������" << endl;
				}
				break;
			}	
			case 3:{
				cout << "��ѡ�����Ķ���ʽ��";
				int p;
				cin >> p;
				if (p >= 0 && p < polys_num) {
					cout << "δ֪��x = ";
					int x;
					cin >> x;
					cout << evaluate(x, polys[p]) << endl;
				} else {
					cout << "����ʽ�����ڣ�" << endl;
				}
				break;
			}
			case 4:{
				cout << "��ѡ��ɾ���Ķ���ʽ��";
				int p;
				cin >> p;
				if (p >= 0 && p < polys_num) {
					delete_poly(polys, p);
					cout << "ɾ���ɹ���" << endl;
				} else {
					cout << "����ʽ�����ڣ�" << endl;
				}
				break;
				break;
			} 
			case 5:{
				cout << "��ǰ�������ʽ�������£�" << endl;
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
				system("cls");    //�����ǰʹ�úۼ�
				welcome();    //����������
				break;
			} 
			default:{
				cout << "�޴˹��ܣ�" << endl;  //��ѡ��δ���幦��ʱ���� 
				break;
			}
		}
		cout << "������������������������" << endl  << "      ��ѡ���ܣ�"; 
		cin >> service;
	}
	save_file(polys, tail);  //���沢�ر��ļ� 
	return 0;
}

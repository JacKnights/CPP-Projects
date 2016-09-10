#include <windows.h>
#include "Function.cpp"

using namespace std;

int main() {
	
	introSystem();
	
	vector<campus_card> Ccards;
	vector<deposit_card> Dcards;
	vector<binding_card> Bcards;
	
	readCampusCard(Ccards);
	readDepositCard(Dcards);
	readBindingCard(Bcards, Ccards, Dcards);
	
	int service;
	string account;
	cout << "|��ѡ��ϵͳ���ܣ�" ;
	cin >> service;
	while (service) {
		//ϵͳ����ֱ����0�˳� 
		switch (service) {
			
			case 1:{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				cout << "|	����У԰����:" ;
				cin >> account;
				if (account[0] == 'c' && account.length() == 6 && !repeated(account, Ccards)) {
					Ccards.push_back(campus_card(account));
					Ccards[Ccards.size() - 1].create_time.setRecord();
					cout << "|		У԰������ɹ���\n";
					cout << "|	���������룺";
					string pw;
					cin >> pw;
					Ccards[Ccards.size() - 1].setPassword(pw);
					cout << "|		�������óɹ���\n";
				} else {
					cout << "|		����ʧ�ܣ�����������ѱ����\n";
				}
				break;
			}
			//�����˺ż���У԰��
			
			case 2:{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_INTENSITY);
				cout << "|	������:" ;
				cin >> account;
				if (account[0] == 'd' && account.length() == 6 && !repeated(account, Dcards)) {
					Dcards.push_back(deposit_card(account));
					cout << "|		�������ɹ���\n";
					Dcards[Dcards.size() - 1].create_time.setRecord();
					cout << "|	���������룺";
					string pw;
					cin >> pw;
					Dcards[Dcards.size() - 1].setPassword(pw);
				} else {
					cout << "|		����ʧ�ܣ�����������ѱ����\n";
				}
				break;
			}
			//�����˺ż���
			
			case 3:{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_INTENSITY);
				cout << "|	����󶨿���:" ;
				cin >> account;
				if (account[0] == 'b' && account.length() == 6 && !repeated(account, Bcards)) {
					string  Cacc, Dacc, password;
					cout << "|	����󶨵�У԰����:";
					cin >> Cacc;
					if (findCcardByAcc(Cacc, Ccards) != -1) {
						cout << "|	����У԰�����룺";
						cin >> password;
						if (password == Ccards[findCcardByAcc(Cacc, Ccards)].getPassword()) {
							Bcards.push_back(binding_card(account, Cacc, Ccards));
							cout << "|		�󶨿�����ɹ���\n";
							Bcards[Bcards.size() - 1].create_time.setRecord();
							cout << "|	���������룺";
							cin >> password;
							Bcards[Bcards.size() - 1].setPassword(password);
							cout << "|		�������óɹ���\n";
						} else {
							cout << "|		������󣬰�ʧ�ܣ�\n";
						}
					} else {
						cout << "|		�����ڴ�У԰����\n";
					}
				} else {
					cout << "|		����ʧ�ܣ�����������ѱ����\n";
				}
				break;
			}
			//���뼤��󶨿��˺Ų���ָ��У԰�� 
			
			case 4:{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				cout << "|	��¼У԰����:" ;
				cin >> account;
				if (findCcardByAcc(account, Ccards) == -1) {
					cout << "|		�޴��˺ţ�\n";
				} else {
					cout << "|	���������룺";
					string password;
					cin >> password;
					if (password != Ccards[findCcardByAcc(account, Ccards)].getPassword()) {
						cout << "|		�������\n";
					} else {
						Ccards[findCcardByAcc(account, Ccards)].useCampusCard();
					}
				}
				break;
			}
			//��¼У԰�� 
			
			case 5:{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				cout << "|	��¼�����:" ;
				cin >> account;
				if (findDcardByAcc(account, Dcards) == -1) {
					cout << "|		�޴��˺ţ�\n";
				} else {
					cout << "|	���������룺";
					string password;
					cin >> password;
					if (password != Dcards[findDcardByAcc(account, Dcards)].getPassword()) {
						cout << "|		�������\n";
					} else {
						Dcards[findDcardByAcc(account, Dcards)].useDepositCard(Ccards, Dcards);
					}
				}
				break;
			}
			//��¼��� 
			
			case 6:{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
				cout << "|	��¼�󶨿���:" ;
				cin >> account;
				if (findBcardByAcc(account, Bcards) == -1) {
					cout << "|		�޴��˺ţ�\n";
				} else {
					cout << "|	���������룺";
					string password;
					cin >> password;
					if (password != Bcards[findBcardByAcc(account, Bcards)].getPassword()) {
						cout << "|		�������\n";
					} else {
						Bcards[findBcardByAcc(account, Bcards)].useBindingCard(Bcards, Ccards, Dcards);
					}
				}
				break;
			}
			//��¼�󶨿� 
			
			default:{
				cout << "|		�޴˹��ܣ����������룡\n";
				break;
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
		cout << "+------------------------------------------------------------------\n";
		cout << "|��ѡ��ϵͳ���ܣ�" ;
		cin >> service;
	}
	
	writeCampusCard(Ccards);
	writeDepositCard(Dcards);
	writeBindingCard(Bcards);
	cout << "|ϵͳ�Ѱ�ȫ�˳���"; 
	return 0;
}

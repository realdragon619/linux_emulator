#include<Windows.h>
#include"header.h"

class System_func{
private:
	static const int GREEN=10;
	static const int WHITE=15;
public:
	static void clear_console(){
		system("cls");
	}
	static void make_green(string str){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
		cout<<str;cout<<"    ";
		make_white();
	}
	static void make_white(){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	}
};
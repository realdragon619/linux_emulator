#include"header.h"
#include"Dirclass.h"
#include<fstream>
class User{
public:
	string id;
	string pw;
};
class Login{
private:
	User user;
public:
	Login(){
		user.id="";
		user.pw="";
	}
	string get_user(){
		return user.id;
	}
	string get_pw(){
		return user.pw;
	}
	
	void program_start(){
		cout<<"*******************************************************\n";
		cout<<"2014_mju_project Linux Emulator release 1.0 (mid term)\n";
		cout<<"*******************************************************\n";
	}
	User user_login(){
		cout<<"login:";
		cin>>user.id;
		cout<<"Password:";
		cin>>user.pw;
		
		if(check_login(user)){
			return user;
		}else{
			user.id="";
			user.pw="";
			cout<<"잘못입력되었습니다\n";
			return user;
		}

	}
	bool check_login(User u){
		string login_info;
		Cmd_check file_split;
		string *split;
		bool check=false;
		ifstream ifs;
		ifs.open("login_info.txt");
		while(!ifs.eof()){			
			getline(ifs,login_info);
			split=file_split.StringSplit(login_info," ");
			if(split[0]==u.id && split[1]==u.pw){
				check=true;
				break;
			}
		}
		return check;
	}

};

class UserCmd{
private:
	User user;
	fstream ifs;
	Cmd cmd;
public:
	void init(string cmd,Dir** home, string u){
		
		if(cmd=="useradd"){
			if(u=="root"){
			Dir* point=(*home);
			user_add(&point);
			}else{
				cout<<"권한이 없습니다\n";
			}
		}
		//추후추가
		
		
	}
	void user_add(Dir** home){
		Dir* point=(*home);
		cout<<"id:";
		cin>>user.id;
		cout<<"Password:";
		cin>>user.pw;
		ifs.open("login_info.txt",ios_base::app);
		ifs<<endl<<user.id<<" "<<user.pw;
		cmd.mkdir(&point,user.id);
		cin.get();
	}
};
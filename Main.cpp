#include"header.h"
#include"Dirclass.h"
#include"DataSt.h"
#include"FileSystem.h"
#include"LoginSystem.h"
int main(){
	Login login;
	User user;
	login.program_start();
	
	while(login.get_user()=="" && login.get_pw()==""){ 
		user=login.user_login();
		
	}
	cin.get();


	Dir* home = new Dir("home",NULL,NULL);
	Dir* pt=home;
	FileSys io(pt,user.id);
	Cmd* cmd=new Cmd();
	Cmd_check* cmd_check=new Cmd_check();
	string cmd_content="";
	UserCmd user_cmd;

	
	home = io.load();
	if(user.id !="root"){
		home=cmd->cd(home,user.id,user.id);
	}

	while(true){
		cout<<"["<<user.id<<"]"<<"$";
		getline(cin, cmd_content);

		user_cmd.init(cmd_content,&pt,user.id);
		
		if(cmd_check->init(cmd_content)){
			cmd_check->exe_cmd(&home,user.id);
					
		}	

		if(cmd_content=="exit"){
			io.save();
			break;
		}
	}	
	
	return 0;
}
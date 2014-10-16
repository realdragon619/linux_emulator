#include"header.h"
#include"Dirclass.h"
#include"DataSt.h"
#include"FileSystem.h"
int main(){
	Dir* home = new Dir("home",NULL,NULL);
	Dir* pt=home;
	FileSys io(pt,"root");
	Cmd* cmd=new Cmd();
	Cmd_check* cmd_check=new Cmd_check();
	string cmd_content="";
			
	
	while(true){
		cout<<"->";
		getline(cin, cmd_content);
		if(cmd_check->init(cmd_content)){
			cmd_check->exe_cmd(&home);
					
		}	

		if(cmd_content=="exit"){
			io.save();
			break;
		}else if(cmd_content=="load"){
			home = io.load();
		}
	}
		
	
	
	
	return 0;
}
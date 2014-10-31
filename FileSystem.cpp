#include"Dirclass.h"
#include"DataSt.h"
#include"header.h"
#include<fstream>
class FileSys{
private:
	Dir* dir_copy;
	d_file* file_copy;
	ofstream ofs;
	ifstream ifs;
	string user;
	int select_num;
public:
	FileSys(Dir* dir_copy, string user){
		this->dir_copy = dir_copy;
		this->user = user;
		select_num=0;
	}
	void save(){
		ofs.open("dir_tree.txt");
		Dir* dir_node;
		d_file* file_node;
		Cmd cmd;
		dir_node=dir_copy->get_sub_dir();
		file_node=dir_copy->explore_file();
		
		
		while((dir_node->get_current_dir()!=NULL) || (file_node!=NULL) 
			|| (dir_copy->get_upper_dir()!=NULL)){		
				if(file_node!=NULL || dir_node->get_current_dir()!=NULL){
					ofs << "--"+cmd.pwd(dir_copy,"root")+"~";
				}
				while(file_node!=NULL){
					ofs << "@#" +file_node->get_name()+"/"+file_node->get_content()+"~";
					file_node=file_node->get_next();
				}
								
				while(dir_node->get_current_dir()!=NULL){
					dir_node=dir_node->get_current_dir();
					ofs << "|#"+dir_node->to_name()+"~";
				}
				node_init(&dir_node);
				if(dir_node->get_current_dir()!=NULL){//파일만 하면 오류나서 작성 
					//cout<<"count";
					dir_copy=dir_node->get_current_dir();
					dir_node=dir_copy->get_sub_dir();
					file_node=dir_copy->explore_file();
					

				}else if(dir_node->get_current_dir()==NULL && file_node==NULL){
					
					if(dir_copy->get_current_dir()==NULL){
						
						if(dir_copy->get_upper_dir()->get_current_dir()!=NULL){
							dir_copy=dir_copy->get_upper_dir()->get_current_dir();
							dir_node=dir_copy->get_sub_dir();
							file_node=dir_copy->explore_file();
							
						}else if(dir_copy->get_upper_dir()->get_current_dir()==NULL){
							dir_copy=dir_copy->get_upper_dir();
							dir_node=dir_copy->get_sub_dir();
							dir_node->set_current_dir(NULL);
							file_node=NULL;
							
						}
					}else if(dir_copy->get_current_dir()!=NULL){
						dir_copy=dir_copy->get_current_dir();
						dir_node=dir_copy->get_sub_dir();
						file_node=dir_copy->explore_file();
					}else if(dir_copy->get_current_dir()==NULL && file_node!=NULL){
						file_node=NULL;
					}
				}
			}
		
	}
	Dir* load(){
		char c;
		int count;
		ifs.open("dir_tree.txt");
		string file_content="";
		string buffer1;
		string buffer2="";
		string* split;
		Dir* point_home=dir_copy;
		string command;
		Cmd cmd;
		Cmd_check check;

		while(!ifs.eof()){
			ifs.get(c);
			buffer1=buffer2;
			buffer2=c;
			command=buffer1+buffer2;
			
			if(command=="--"){
				while(c!='~'){
					ifs.get(c);
					if(c!='~'){
						file_content+=c;
					}
				}
				dir_copy=point_home;

				split=check.StringSplit(file_content,"/");
				count=check.count_slash(file_content);
				file_content="";
				
				for(int i=1; i<count; i++){
					dir_copy = cmd.cd(dir_copy,split[i],"root");
				}
				
			}else if(command=="|#"){
				while(c!='~'){
					ifs.get(c);
					if(c!='~'){
						file_content+=c;
					}
				}
				cmd.mkdir(&dir_copy,file_content);
				file_content="";				
			
			}else if(command=="@#"){
				while(c!='~'){
					ifs.get(c);
					if(c!='~'){
						file_content+=c;
					}
				}
				split=check.StringSplit(file_content,"/");
				dir_copy->new_file(split[0],split[1]);
				file_content="";		
			}

			
			
		}
		dir_copy=point_home;
		return dir_copy;
	}
	void node_init(Dir** dir_node){
		(*dir_node)=dir_copy->get_sub_dir();
	}
};


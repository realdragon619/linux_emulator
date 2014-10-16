#include"header.h"
#include"DataSt.h"
#include"ConsoleSys.h"


enum data_type{_DIR,_FILE};
const string cmd_ref[]={"mkdir","cd","ls","pwd","rmdir","cat","cp","clear"};
#define D_MAX_ARRAY_SIZE 10


class d_file {

private:
	string name;
	string content;
	d_file* next;
	time_t current_time;

public:
	
	d_file(string name) {
		this->name = name;
		this->next = NULL;
	}
	d_file(string newName, string content) {
		this->name = newName;
		this->content = content;
		this->next = NULL;
	}

	void set_name(string name){
		this->name=name;
	}
	void set_next(d_file* next){
		this->next=next;
	}

	void set_content(string content){
		this->content=content;
	}
	string get_name(){
		return name;
	}
	string get_content(){
		return content;
	}
	d_file* get_next(){
		return next;
	}
	
};

class Dir{ 
private:
	string name;
	Dir* sub_dir;
	Dir* current_dir;
	Dir* upper_dir;
	d_file *file;
public:
	Dir(string name, Dir* upper_dir, Dir* current_dir){
		this->name=name;
		this->upper_dir=upper_dir;
		this->current_dir=current_dir;
		sub_dir=new Dir();
		file=NULL;

	}
	Dir(){
		name=".";
		upper_dir=NULL;
		current_dir=NULL;
		sub_dir=NULL;
	}
	string to_name(){
		return name;
	}
	Dir* get_sub_dir(){
		return sub_dir;
	}
	Dir* get_current_dir(){
		return current_dir;
	}
	Dir* get_upper_dir(){
		return upper_dir;
	}
	void set_sub_dir(Dir* sub_dir){
		this->sub_dir=sub_dir;
	}
	void set_current_dir(Dir* current_dir){
		this->current_dir=current_dir;
	}
	void set_upper_dir(Dir* upper_dir){
		this->upper_dir=upper_dir;
	}
	d_file* explore_file(){
		return file;
	}
	void new_file(string name, string content){
		d_file* temp;
		temp=file;
		
		if(file==NULL){
			file = new d_file(name,content);
		}else{
			while(temp->get_next()!=NULL){
				temp=temp->get_next();
			}
			temp->set_next(new d_file(name,content));
		}
	}
    void delete_file(string name){
		d_file* temp=file;
		if(file!=NULL){
			if(temp->get_name()==name){
				file->set_next(temp->get_next());
				delete temp;
			}else{
				while(temp->get_next()!=NULL){
					if(temp->get_next()->get_name()==name){
						d_file* point=temp->get_next();
						temp->set_next(temp->get_next()->get_next());
						break;
					}
					temp->set_next(temp->get_next());
				}
			}
		}
	}

};

class Cmd{
private:

public:
	void mkdir(Dir** dir, string dir_name){//dir_name은 cmd
		Dir* point=(*dir);
		Dir* sub_point=(*dir)->get_sub_dir();
		
		if(sub_point->get_current_dir()==NULL){
			Dir* new_dir= new Dir(dir_name,point,NULL);
			sub_point->set_current_dir(new_dir);
		}else if(sub_point->get_current_dir()!=NULL){
			Dir* new_dir=new Dir(dir_name,point,NULL);
			while(sub_point->get_current_dir()!=NULL){
				sub_point=sub_point->get_current_dir();	
			}
			sub_point->set_current_dir(new_dir);			
		}
	}
	string pwd(Dir* dir){
		Stack s;
		string path="";		
		if(dir->get_upper_dir()==NULL){
			path=dir->to_name();
		}else{
			while(dir->get_upper_dir()!=NULL){
				s.push(dir->to_name());
				dir=dir->get_upper_dir();
				if(dir->get_upper_dir()==NULL){
					s.push(dir->to_name());
				}
			}
			while(!s.is_empty()){
				path+=s.pop()+"/";
			}	
			
		}
		path+="\n";
		return path;
		
	}
	Dir* cd(Dir* dir, string dir_name){
		Dir* point=dir;
		Dir* sub_point=dir->get_sub_dir()->get_current_dir();
		if((dir_name=="..") && (point->get_upper_dir()!=NULL)){
			point=point->get_upper_dir();
			return point;
		}
		
		
		while(sub_point!=NULL){
			if(sub_point->to_name()==dir_name){
				return sub_point;
			}
			sub_point=sub_point->get_current_dir();
		}
		return dir;
			
	}
	void ls(Dir* dir){
		PQueue p_queue;
		Dir* sub_point=dir->get_sub_dir();
		sub_point=sub_point->get_current_dir();
		d_file* fp=dir->explore_file();
		if(sub_point!=NULL || fp!=NULL){
			while(sub_point!=NULL){
				p_queue.enqueue(sub_point->to_name(),_DIR); 
				sub_point=sub_point->get_current_dir();
			}
			while(fp!=NULL){
					p_queue.enqueue(fp->get_name(),_FILE);
					fp=fp->get_next();
				}
			while(!p_queue.is_empty()){
				if(p_queue.get_list()->type==_DIR){
					System_func::make_green(p_queue.dequeue());	//시스템 함수 콜 				
				}else if(p_queue.get_list()->type==_FILE){
					cout<<p_queue.dequeue();	cout<<"    ";
				}
			}
			cout<<endl;
		}
		
	}
	void rmdir(Dir** dir, string dir_name){
		Dir* point=(*dir);
		Dir* sub_point=(*dir)->get_sub_dir();
		Dir* temp;
		while(sub_point->get_current_dir()!=NULL){
			if(sub_point->get_current_dir()->to_name()==dir_name){
				temp=sub_point->get_current_dir();
				sub_point->set_current_dir(sub_point->get_current_dir()->get_current_dir());
				delete temp;
				break;

			}
			sub_point=sub_point->get_current_dir();
		}
		
	}
	void cat(Dir** dir, string file_name, string option="no_option"){
		Dir* point=(*dir);
		if(option==">>"){
			char c;
			string content="";
			
			while ((c = getchar()) != EOF){
				content+=c;
			}
			//Window에서 Ctrl-Z를 엔터후에 받을수있기에 줄바꿈이생기는 오류를 수정하기 위한 코드
			if(content[content.length()-1]=='\n'){
				content[content.length()-1]=NULL;
			}
			point->new_file(file_name,content);
			
		}else if(option=="no_option"){
			if(point->explore_file()!=NULL){
				d_file* fp=point->explore_file();
				while(fp!=NULL){
					if(fp->get_name()==file_name){
						cout<<fp->get_content()<<endl;
						break;
					}
					fp=fp->get_next();
				}
			}
		}
	}
	void cp(Dir** dir, string copy_file, string origin_file){
		d_file* point=(*dir)->explore_file();
		d_file* copy_point=NULL;
		string content="";
		while(point!=NULL){
			if(point->get_name()==copy_file){
				copy_point=point;
			}else if(point->get_name()==origin_file){
				content=point->get_content();
			}
			point=point->get_next();
		}
		if(copy_point!=NULL && (content!="")){
			copy_point->set_content(content);
		}
	}
	
};

class Cmd_check{
private:
	string cmd;
	string option;
	string parameter;
	string plus_parameter;
	Cmd cmd_store;
	
public:
	Cmd_check(){
				
	}

	string* StringSplit(string strTarget, string strTok)
	{
		int     nCutPos;
		int     nIndex     = 0;
		string* strResult = new string[D_MAX_ARRAY_SIZE];
 
	    while ((nCutPos = strTarget.find_first_of(strTok)) != strTarget.npos)
		{
			if (nCutPos > 0)
			{
				strResult[nIndex++] = strTarget.substr(0, nCutPos);
			}
			strTarget = strTarget.substr(nCutPos+1);
		}
 
		if(strTarget.length() > 0)
		{
			strResult[nIndex++] = strTarget.substr(0, nCutPos);
		}
 
	    return strResult;
	}
	int count_underscores(string s) {
		int count = 0;

		for (int i = 0; i < s.size(); i++){
			if (s[i] == ' ') count++;
		}
		return count;
	}
	int count_slash(string s) {
		int count = 0;

		for (int i = 0; i < s.size(); i++){
			if (s[i] == '/') count++;
		}
		return count;
	}

	bool init(string s){
		bool cmd_ok=false;
		string* split;
		int space_num;
		space_num=count_underscores(s);
		
		if(space_num==0){
			cmd=s;
		}else if(space_num==1){
			split = StringSplit(s," ");
			this->cmd=split[0];
			this->parameter=split[1];
			this->option="no_option";
		}else if(space_num==2){
			split = StringSplit(s," ");
			if(split[1]==">>" || split[1]=="<<" || split[1]=="<" || split[1]==">"){
				this->cmd=split[0];
				this->option=split[1];
				this->parameter=split[2];
			}else if(split[0]=="cp"){
				this->cmd=split[0];
				this->parameter=split[1];
				this->plus_parameter=split[2];
				this->option="no_option";
			}
		}
		for(int i=0; i<this->cmd_ref_size();i++){
			if((this->cmd)==cmd_ref[i]){
				cmd_ok=true;
				return cmd_ok;
			}
			
		}
		return cmd_ok;
	}
	
	string get_cmd(){
		return cmd;
	}
	string get_para(){
		return parameter;
	}
	int cmd_ref_size(){
		int size=0;
		while(cmd_ref[size][0]!=NULL){
			size++;
		}
		return size;
	}


	void exe_cmd(Dir** p_dir){
		Dir *temp=(*p_dir);
		if(cmd=="mkdir"){
			cmd_store.mkdir(&temp,parameter);
		}else if(cmd=="cd"){
			(*p_dir)=cmd_store.cd(temp,parameter);		
		}else if(cmd=="ls"){
			cmd_store.ls(temp);
		}else if(cmd=="pwd"){
			cout<<cmd_store.pwd(temp);
		}else if(cmd=="rmdir"){
			cmd_store.rmdir(&temp,parameter);
		}else if(cmd=="cat"){
			cmd_store.cat(&temp,parameter,option);
		}else if(cmd=="cp"){
			cmd_store.cp(&temp,parameter,plus_parameter);
		}else if(cmd=="clear"){
			System_func::clear_console();		
		}
	}
};
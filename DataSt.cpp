#include"header.h"

class list
{
public:
		string list_name;
        list* next;
		int type;
};

class Stack{
private:	
	list* head;
	list* top;
	
public:
	Stack(){
		head = NULL;
		top = NULL;
		
	}
	void push(string list_name)
	{
        list* temp=new list; 
        if(head==NULL){
			head = temp;
			top = temp;
			temp->list_name = list_name;
			temp->next = NULL;
		}else{
			top->next = temp;
			temp->list_name = list_name;
			temp->next = NULL;
			top = temp;

		}
		
    }
	string pop()
	{
		list* down_top=head;
		list* temp=new list;
		string pop_string="";
		if(head!=NULL && head!=top){
			while(!(down_top->next==top)){
				down_top=down_top->next;
			}
			pop_string=top->list_name;// Ãâ·Â		
       		down_top->next=NULL;
			temp=top;
			top=down_top;
			delete temp;
			return pop_string;
				
		}else if(head!=NULL && head==top){
			pop_string=top->list_name;
			head=NULL;
			temp=top;
			top=NULL;
			delete temp;
			return pop_string;
		}
	}
		
	bool is_empty(){
		if(head==NULL){
			return true;
		}else{
			return false;
		}
	}
};

class PQueue{
private:	
	list* head;
	list* top;
	
public:
	PQueue(){
		head = NULL;
		top = NULL;
		
	}
	void enqueue(string list_name,int type)
	{
        list* temp=new list;
		list* point;
		list* point_plus;
		
		temp->list_name = list_name;
		temp->type=type;
		temp->next = NULL;
		
        if(head==NULL){
			head = temp;
			top = temp;
		}else if(head->next==NULL){
			if(head->list_name.compare(temp->list_name)>0){
				temp->next=head;
				head=temp;
			}else{
				head->next=temp;
			}
		}else{
			point=head;
			point_plus=head->next;
			
			if(point->list_name.compare(temp->list_name)>0){
				head=temp;
				temp->next=point;
			}else if(point_plus->list_name.compare(temp->list_name)>0){
				point->next=temp;
				temp->next=point_plus;				
			}else{				
				while(point_plus->list_name.compare(temp->list_name)<0){
					point=point_plus;
					point_plus=point_plus->next;
					if(point_plus==NULL)
						break;
				}
				if(point_plus==NULL){
					point->next=temp;
				}else{
					point->next=temp;
					temp->next=point_plus;
				}
			}		

		}
				
	}
	string dequeue()
	{
		list* temp;
		string pop_string;
		
		temp=head;
		head=head->next;
		pop_string=temp->list_name;
		delete temp;
		return pop_string;

		
	}
	bool is_empty(){
		if(head==NULL){
			return true;
		}else{
			return false;
		}
	}
	list* get_list(){
		return head;
	}
};


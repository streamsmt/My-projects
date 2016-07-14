
#include<iostream>
#include<cmath>
#include<vector>
#include<string>
#include<fstream>
#include<iterator>
#include<valarray>
#include<ctime>
#include "zhjrandom.h"

using namespace std;

struct double_int {
	double_int(int a, int b) :numa(a), numb(b) {}
	int numa;
	int numb;
};

struct node_connected{
	int interaction_node_index;
	struct node_connected* next;
	node_connected& operator[](int num);
	node_connected();
	node_connected(int index);
	node_connected& node_add(node_connected add) ;
	int node_connected_size(void);
};

int node_connected::node_connected_size(void) {
	auto p=this;
	int count=1;
	while(p->next!=NULL){
		p=p->next;
		count++;
	}
	return count;
}

node_connected::node_connected(){
	interaction_node_index=0;
	next=NULL;
}

node_connected::node_connected(int index){
	interaction_node_index=index;
	next=NULL;
}

node_connected &node_connected::operator[](int num){
	auto p=this;
	for(int i=0;i<=num-1;i++)
		p=p->next;
	return *p;
}

node_connected& node_connected::node_add(node_connected add){
	auto p=this;
	while(p->next!=NULL)
		p=p->next;
	p->next=&add;
} 

node_connected* generator(node_connected *p){
	node_connected newadd;
	newadd.interaction_node_index=7;
	return p;
}

class BP_for_EA{
	private:
		vector<double_int> interaction;
		vector<struct node_connected*> node;
	public:
		BP_for_EA(istream &in,int edges_num,int nodes_num);
};
																												
BP_for_EA::BP_for_EA(istream &in,int edges_num,int nodes_num){
	int a, b;
	while (in >> a&&in >> b) {
		interaction.push_back(double_int(a, b));
	}
	cout<<"Graph has been imported successfully."<<endl;
	cout<<interaction[2].numa;
}

int main(){
	cout<<"test:";
	cout<<endl;
	node_connected test(3);
	node_connected add(5);
	test.node_add(add);
	cout<<test.next->interaction_node_index;
	cout<<test.node_connected_size()<<endl;
	cout<<((test.next)->interaction_node_index)<<endl;
	
/*	node_connected test;
	cout<<endl<<test.node_connected_size()<<"///"<<endl;
	node_connected newadd(5);
	test.node_add(newadd);
	cout<<test.next->interaction_node_index<<endl;
	node_connected newadd_2(12);
	cout<<test.next->interaction_node_index<<endl;
	cout<<test.node_connected_size()<<endl;
	cout<<test.next->interaction_node_index<<endl;
	cout<<test.next->next->interaction_node_index<<endl;*/
	
	//
	srand(time(0));
	ifstream in("data.txt");
	cout<<"Please enter the numbers of edges and nodes:";
	int edges_num=0,nodes_num=0;
	cin>>edges_num>>nodes_num;
	BP_for_EA example(in,edges_num,nodes_num);
}


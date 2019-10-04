#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<queue>
#include<vector>
using namespace std;
int find_substring(const string full, const string sub){
	if(full.size()<sub.size()) return -1;
	if(full.size()==sub.size()){ if(full==sub) return 0; return -1;}
	vector<int> alph (256, sub.size());
	int i;
	for(i=sub.size()-2; i>=0; i--){
		if(alph[(int) sub[i]]==sub.size()) alph[ (int) sub[i]]=sub.size()-i-1;
	}
	i=sub.size()-1;
	int step;
	while(i<full.size()){
		step=0;
		for(int j=sub.size()-1; j>=0; j--){
			if( sub[j] != full[i+j-sub.size() +1]){
				step=alph[(int) full[i+j-sub.size()+1]]; 
				break;
			}
		}
		if(step==0) break;
		i+=step;
	}
	if(i<full.size()) return i-sub.size()+1;
	return -1;
}

int main(){
	char buffer[30];
	buffer[0]=' ';
	vector<string> ingridients(1);//char** ingridients;
	//int ingridients.size()s=0;
	int i, key, p=0;
	//ingridients=(char **) malloc(sizeof(char *));
	
	cout<<"****************************************"<<endl
	<<"**Программа для анализа состава крема.**"<<endl
	<<"****************************************"<<endl
	<<"Вводите состав крема так, как написанно в составе со всеми пробелами и пунктуацией."<<endl
	<<"Введите ингридиетны:"<<endl;
	while(1){
		cin>>buffer;
		//cout<<buffer<<endl;
		if(buffer=="(and)" || buffer=="and") continue;
		for(i=0; i<30; ++i){
			//cout<<buffer[i]<<endl;
			if(buffer[i]=='\0'  || buffer[i]=='.'){
				//cout<<endl<<"flag"<<endl;
				break;
			}
			if(buffer[i]==','){
				ingridients.resize(ingridients.size()+1);
				continue;
			}
			if(buffer[i]>='A'&&buffer[i]<='Z'){
				ingridients[ingridients.size()-1]+=buffer[i]-'A'+'a';
			}else{
				ingridients[ingridients.size()-1]+=buffer[i];
			}
		}
		if(buffer[i]=='.') break;
		if(buffer[i-1]!=',') ingridients[ingridients.size()-1]+=' ';
	}
	//for(i=0; i< ingridients.size(); ++i) cout<< ingridients[i]<<endl;
	FILE *incs;
	//queue<int> q;
	incs=fopen("list_conservants.bin", "rb");
	int l, r;  l=r=ingridients.size(); // индексы самой левой части консервантов и правой
	//int NOI; // Number Of Ingridients of conservants
	while(1){
		int pos;
		fread(&key, sizeof(key), 1, incs);
		if(feof(incs)) break;
		fread(buffer, sizeof(char)*30, 1, incs);
		if(key>0){
			int NOGI=key;
			queue<int> q1;
			for(i=0; i<ingridients.size()-NOGI; ++i){
				if(ingridients[i]==buffer){ q1.push(i);}
			}
			for(i=0; i<NOGI-1;++i){
				fread(&key, sizeof(key), 1, incs); fread(&buffer, sizeof(char)*30, 1, incs);
				
				int size=q1.size();
				for(int j=0; j<size; ++j){
					pos=q1.front(); q1.pop();
					if(ingridients[pos+1+i]==buffer) q1.push(pos);
				}
			}
			if(!q1.empty() &&  (pos=q1.front())<=l){ 
				l=pos;
				r=pos+NOGI-1; 
				q1.pop();
			}
		}
		
	}
	fclose(incs);
//===============================================================================================================================================================
	key=1;
	p=0;
	for(i=0;i<l;++i){
		if((find_substring(ingridients[i], "glycerin"))>=0) p=i;
		if( (find_substring(ingridients[i], "oil")>=0 && !p) || find_substring(ingridients[i], "extract")>=0 || find_substring(ingridients[i], "peptide")>=0 || find_substring(ingridients[i], "hyaluronic acid")>=0){
			if(key){
				cout<<"Эти активные вещества, добавленны в достаточной дозе:"<<endl;
				key^=1;
			}else{
				cout<<","<<endl;
			}
			cout<<ingridients[i];
		}
	}
	for(i=r+1; i<ingridients.size(); i++){
		if(find_substring(ingridients[i], "hyaluronic acid")>=0){
			if(key){
				cout<<"Эти активные вещества, добавленны в достаточной дозе:";
				key^=1;
			}else{
				cout<<","<<endl;
			}
			cout<<ingridients[i];
		}
	}
		if(!key){
		cout<<"."<<endl;
	}else{
		cout<<"Здесь нет полезных веществ, добавленных в достаточной дозе."<<endl;
	}
	key=1;
	//printf("l=%d\n", l);
	if(p){
		for(i=p; i<l; i++){
			if(find_substring(ingridients[i], "oil")>=0){
				if(key){
					cout<<"Эти активные вещества, добавленны в недостаточной дозе:"<<endl;
					key^=1;
				}else{
					cout<<","<<endl;
				}
				cout<<ingridients[i];
			}
		}
	}
	for(i=r+1; i<ingridients.size(); i++){
		if(find_substring(ingridients[i], "oil")>=0 || find_substring(ingridients[i], "extract")>=0 || find_substring(ingridients[i], "peptide")>=0){
			if(key){
				cout<<"Эти активные вещества, добавленны в недостаточной дозе:"<<endl;
				key^=1;
			}else{
				cout<<","<<endl;
			}
			cout<<ingridients[i];
		}
	}
	if(!key){
		cout<<"."<<endl;
	}
}

#define __STDC_WANT_LIB_EXT1__ 1
#include<stdio.h>
#include<string.h>
#include"agets.h"
#include"tuple.h"
bool help_check(char* x){
	return ((x!=NULL)&&(*x=='y'||*x=='Y'||*x=='n'||*x=='N'));
}
char * type(void * x){
	return "char *";
}
bool func_if(const tuple * tp,void * key_word){
	if(strstr((char *)(tp->data),(char *)key_word)!=NULL){
		char * x=NULL;
		while(help_check(x)==false){
			system("cls");
			puts("Keyword:");
			printf("%s\n",(char *)(key_word));
			puts("Result:");
			printf("%s\n",(char *)(tp->data));
			puts("Remove it? [Y|N]");
			free(x);
			x=agets(stdin);
		}
		bool ret=(*x=='y'||*x=='Y');
		free(x);
		return ret;
	}else{
		return false;
	}
}
bool output(tuple *tp,void * file){
	if(*((char *)(tp->data))!='\0'){
		fprintf_s((FILE *)file,"%s\n",(char *)(tp->data));
	}else{
		/*PASS*/
	}
	return true;
}
int main(){
	FILE * file;
	tuple * _tuple=NULL;
	if(fopen_s(&file,"data.txt","r+")==0){
		while(feof(file)==0){
			_tuple=add_tuple(_tuple,new_tuple(agets(file),free,type));
		}
		fclose(file);
	}else{
		/*PASS*/
	}
	if(fopen_s(&file,"data.txt","w+")==0){
		/*PASS*/
	}else{
		puts("Open file error!");
		system("pause");
		return 1;
	}
	char * str=NULL;
	while(true){
		system("cls");
		puts("Input keyword to search:");
		str=agets(stdin);
		_tuple=remove_if_tuple(_tuple,func_if,(void *)str);
		free(str);
		do{
			system("cls");
			puts("Not find?");
			puts("Just Add the data!");
			puts("Each data is a line, ending input with empty line:");
			str=agets(stdin);
			if(*str!='\0'){
				_tuple=add_tuple(_tuple,new_tuple(str,free,type));
			}else{
				/*PASS*/
			}
		}while(*str!='\0');
		free(str);
		char * x=NULL;
		while(help_check(x)==false){
			system("cls");
			puts("Quit? [Y|N]");
			free(x);
			x=agets(stdin);
		}
		if(*x=='y'||*x=='Y'){
			foreach_tuple(_tuple,output,file);
			delete_tuple(_tuple);
			fclose(file);
			free(x);
			return 0;
		}else{
			free(x);
		}
	}
		
}
#include<stdio.h>
#include<string.h>

void input(){
	FILE* output;
	output=fopen("list_conservants.bin", "ab");
	printf("Вводите консерванты в список. Чтобы остановите ввод введите end.\n");
	char name[30];
	int kolvo;
	scanf("%c", &name[0]);
	while(1){
		scanf("%d ", &kolvo);
		gets(name);
		if(!strcmp(name,"end")) break;
		fwrite(&kolvo,sizeof(kolvo), 1, output);
		fwrite(&name, sizeof(name), 1, output);
	}
	fclose(output);
	return;
}
void print_file(){
	FILE* print;
	int number=1;
	int kolvo;
	char name[30];
	print=fopen("list_conservants.bin", "rb");
	while(1){
		fread(&kolvo, sizeof(kolvo), 1, print);
		fread(&name, sizeof(name), 1, print);
		if(feof(print)) break;
		printf("%d. %d %s\n", number++, kolvo, name);
	}
	fclose(print);
	return;
}
void del_num(){
	printf("Введите номер удаляемого консерванта: ");
	int num, i=0, kolvo;
	scanf("%d", &num);
	FILE* buffer, *input;
	char name[30];
	input=fopen("list_conservants.bin", "rb");
	buffer=fopen("buffer.bin", "wb");
	while(1){
		fread(&kolvo, sizeof(kolvo), 1, input);
		fread(&name, sizeof(name), 1, input); i++;
		if(feof(input)){
			if(i<=num){
				printf("такого номера нет.\n");
				fclose(input); fclose(buffer);
				remove("buffer.bin");
				return;
			}else{
				fclose(input); fclose(buffer);
				break;
			}
		}
		if(i!=num){
			fwrite(&kolvo, sizeof(kolvo), 1, buffer);
			fwrite(&name, sizeof(name), 1, buffer);
		}
	}
	
	input=fopen("list_conservants.bin", "wb");
	buffer=fopen("buffer.bin", "rb");
	while(1){
		fread(&kolvo, sizeof(kolvo), 1, buffer);
		fread(&name, sizeof(name), 1, buffer);
		if(feof(buffer)) break;
		fwrite(&kolvo, sizeof(kolvo), 1, input);
		fwrite(&name, sizeof(name), 1, input);
	}
	fclose(input); fclose(buffer);
	remove("buffer.bin");
	return;
}
void print_menu(){
	printf(
	"1.Распечатать меню.\n"
	"2.Добавить в список консерванты.\n"
	"3.Распечатать список консервантов\n"
	"4.Удалить консервант по номеру\n"
	"5.Вставить консревант\n"
	"0.Выход.\n"
	);
	return;
}	
void insert(){
	printf("Введите номер , которым вставить по счёту: ");
	int num, i=0, kolvo, key;
	scanf("%d", &num);
	FILE* buffer, *input;
	printf("Введите ключ и название:");
	char name[30], inpt[30];
	scanf("%d ", &key);
	gets(inpt);
	input=fopen("list_conservants.bin", "rb");
	buffer=fopen("buffer.bin", "wb");
	while(1){
		fread(&kolvo, sizeof(kolvo), 1, input);
		fread(&name, sizeof(name), 1, input); i++;
		if(feof(input)){
			if(i<=num){
				printf("такого номера нет.\n");
				fclose(input); fclose(buffer);
				remove("buffer.bin");
				return;
			}else{
				fclose(input); fclose(buffer);
				break;
			}
		}
		if(i==num){
			fwrite(&key, sizeof(key), 1, buffer);
			fwrite(&inpt, sizeof(inpt), 1, buffer);
		}
		fwrite(&kolvo, sizeof(kolvo), 1, buffer);
		fwrite(&name, sizeof(name), 1, buffer);
	}
	
	input=fopen("list_conservants.bin", "wb");
	buffer=fopen("buffer.bin", "rb");
	while(1){
		fread(&kolvo, sizeof(kolvo), 1, buffer);
		fread(&name, sizeof(name), 1, buffer);
		if(feof(buffer)) break;
		fwrite(&kolvo, sizeof(kolvo), 1, input);
		fwrite(&name, sizeof(name), 1, input);
	}
	fclose(input); fclose(buffer);
	remove("buffer.bin");
	return;
}

int main(){
	int status=1;
	while(status){
		switch(status){
			case 1 : {
				print_menu();
				break;
			}
			case 2 : { 
				input();
				break;
			}
			case 3 : {
				print_file();
				break;
			}
			case 4 : {
				del_num();
				break;
			}
			case 5 :{
				insert();
				break;
			}
		}
		printf("введите команду: ");
		scanf("%d", &status);
	}
	return 0;
}

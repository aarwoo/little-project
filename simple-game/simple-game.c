#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#define you (0)
#define me (1)
#define true (1)
#define false (0)
#define is_using (0)
#define power (1)
#define print_blood(blood_list,someone) \
printf("%3s:", #someone);\
for(int i=1;i<=(blood_list)[someone];i=i+1){\
	printf("_");\
}\
printf("\n");
#define print_card(card_list,id) \
printf("%2d:",id);\
for(int j=1;j<=(card_list)[id][power];j=j+1){\
	printf("_");\
}\
printf("\n");
#define print_all(blood_list,card_list) \
system("cls");\
print_blood(blood_list,me);\
print_blood(blood_list,you);\
printf("Card:\n");\
for(int i=0;i<=19;i=i+1){\
	if((card_list)[i][is_using]==false){\
		printf("%d\n",i);\
	}else{\
		/*Pass*/\
	}\
}
int main(){
	int blood_list[2];
	int card_list[20][2],card_choose,turn_to,is_continue=true,available_card=20;
	system("mode con cols=128 lines=32");
	system("title simple-game");
	while(is_continue==true){
		blood_list[you]=100;
		blood_list[me]=100;
		srand(time(NULL));
		for(int i=0;i<=19;i=i+1){
			card_list[i][is_using]=false;
			card_list[i][power]=rand()%20+1;
		}
		print_all(blood_list,card_list);
		turn_to=rand()%2;
		while(blood_list[you]*blood_list[me]!=0&&available_card!=0){
			switch(turn_to){
				case you:{
					do{
						printf("Please choose one:");
						scanf("%d",&card_choose);
					}while(card_choose<0||19<card_choose);
					printf("You ");
					turn_to=me;
					break;
				}
				case me:{
					do{
						card_choose=rand()%20;
					}while(card_list[card_choose][is_using]==true);
					printf("I ");
					turn_to=you;
					break;
				}
				default:{
					/*Pass*/
					break;
				}
			}
			if(card_list[card_choose][is_using]==true){
				printf("choose is unavailable:\n");
			}else{
				printf("choose is available:\n");
				card_list[card_choose][is_using]=true;
				available_card=available_card-1;
				blood_list[turn_to]=(blood_list[turn_to]>=card_list[card_choose][power])?
													  	  (blood_list[turn_to]-card_list[card_choose][power]):
													  	  (0);
			}
			print_card(card_list,card_choose);
			system("pause");
			print_all(blood_list,card_list);
		}
		if(blood_list[me]==0){
			printf("You win!T_T\n");
		}else if(blood_list[you]==0){
			printf("I win!^_^\n");
		}else{
			printf("Oh,There is no winner!\n");
		}
		printf("try again?[0:No|1:Yes]");
		scanf("%d",&is_continue);
		if(is_continue==0||is_continue==1){
			/*Pass*/
		}else{
			printf("Terminate!\n");
			return 0;
		}
	}
	return 0;
}

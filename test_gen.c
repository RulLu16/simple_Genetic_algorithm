#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


struct gen{
	int word[6];
	int fit;
};

void exchange(struct gen*, struct gen*);
int* choose(struct gen*);
void mutant(struct gen*);
int fitness(int*, struct gen*, int*);

int main(){
	int password[6];
	struct gen current_gen[6];
	struct gen next_gen[6];
	int i,j;
	int prop;
	int gen_num=0;
	int find=-1;
	int temp;
	int password_has_num[10] = { 0,0,0,0,0,0,0,0,0,0 };
	srand(time(NULL));
	printf("Enter your password (6 numbers) : ");
	
	for(i=0;i<6;i++){
		scanf("%1d",&password[i]);
		temp = password[i];
		password_has_num[temp] = 1;
	}
	
	for(i=0;i<6;i++){
		for(j=0;j<6;j++){
			prop=rand()%10;
			current_gen[i].word[j]=prop;
		}
		current_gen[i].fit=0;
	}
	
	while(1){
		find=fitness(password, current_gen,password_has_num);
		
		if(find>-1)
			break;
		
		/*for (i = 0; i < 6; i++) {
			for (j = 0; j < 6; j++)
				printf("%d", current_gen[i].word[j]);
			printf("\n");
		}*/

		exchange(current_gen, next_gen);
		gen_num++;
		//printf("%d -------------------\n", gen_num);
		
		
	}
	
		printf("Find it!! Your pass word is ");
		for(i=0;i<6;i++)
			printf("%d",current_gen[find].word[i]);
		printf("!\n");
		printf("To find out, use %d generation.\n",gen_num);
	
	return 0;
} 

int* choose(struct gen* p){
	int* choice;
	float portion[6];
	int roulette;
	int sum=0;
	int i,j;
	int flag = 0;
	
	choice=(int*)malloc(sizeof(int)*2);
	
	for(i=0;i<6;i++){
			sum=sum+p[i].fit;
	}
	for(i=0;i<6;i++){
		portion[i]=(p[i].fit * 100 / sum);
	}
	//srand(time(NULL));
	roulette=rand()%100;
	sum=0; 
	for(i=0;i<5;i++){
		sum = sum + portion[i];
		if(roulette<sum){
			flag = 1;
			choice[0]=i;
			break;
		}
	}
	if (flag == 0)
		choice[0] = 5;

	while (1) {
		roulette=rand()%100;
		flag = 0;
		sum = 0;
		for(i=0;i<5;i++){
			sum=sum + portion[i];
			if(roulette<sum){
				flag = 1;
				choice[1]=i;
				break;
			}
		}
		if (flag == 0)
			choice[1] = 5;

		if(choice[0]==choice[1])
			continue;
		else
			break;
	}
	return choice;
}   

void exchange(struct gen* p, struct gen* n){
	int* choice;
	int i,j;
	int first, second;
	int temp;


	for(i=0;i<6;i++){
		choice=choose(p);
		//printf("%d, %d\n", choice[0], choice[1]);
		first = choice[0];
		second = choice[1];
		/*for (j = 0; j < 6; j++) {
			temp   = rand() % 2;
			if (temp == 1) {
				n[i].word[j] = p[second].word[j];
			}
			else
				n[i].word[j] = p[first].word[j];
		}*/
		for(j=0;j<4;j++){
			first = choice[0];
			n[i].word[j]=p[first].word[j];
		}
		for(j=4;j<6;j++){
			second = choice[1];
			n[i].word[j]=p[second].word[j];
		}
	}

	mutant(n);

	for(i=0;i<6;i++){
		for(j=0;j<6;j++){
			p[i].word[j]=n[i].word[j];
		}
		p[i].fit=0;
	}
	
}

void mutant(struct gen* n){
	int mutant;
	int i,j;
	//srand(time(NULL));
	
	for(i=0;i<6;i++){
			for (j = 0; j < 6; j++) {
				mutant = rand() % 100;
				if (mutant == 1) {
					n[i].word[j] = rand() % 10;
				}
			}
		
	}
}

int fitness(int* p, struct gen* g,int* num){
	int i,j;
	int temp;
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 6; j++) {
			if (p[j] == g[i].word[j])
				g[i].fit = g[i].fit + 10;
		}
	}
	
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 6; j++) {
			temp = g[i].word[j];
			if (num[temp] == 1)
				g[i].fit = g[i].fit + 2;
		}
	}

	/*for (i = 0; i < 6; i++)
		printf("%d\n", g[i].fit);*/

	for(i=0;i<6;i++){
		if(g[i].fit==72){
			return i;
		}
	}
	return -1;
}

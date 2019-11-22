#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//origin_version_Not_refactoring

struct gen{
	int word[6];
	int fit;
};

void exchange(struct gen*, struct gen*);
int* choose(struct gen*);
void mutant(struct gen*);
int fitness(int*, struct gen*, int*);
void PrintResult(struct gen*, int, int);
void GivePortion(struct gen*, float*);
int GoRoulette(float*);
void ChildToParent(struct gen*, struct gen*);

int main(){
	int password[6];
	int prop;
	int gen_num=0;
	int find=-1;
	int temp,i,j;
	int password_has_num[10] = { 0,0,0,0,0,0,0,0,0,0 };
	struct gen current_gen[6];
	struct gen next_gen[6];
	srand(time(NULL));
	printf("Enter your password (6 numbers) : ");
	
	for(i=0;i<6;i++){
		scanf("%1d",&password[i]);
		temp = password[i];
		password_has_num[temp] = 1;
	} //scan password
	
	for(i=0;i<6;i++){
		for(j=0;j<6;j++){
			prop=rand()%10;
			current_gen[i].word[j]=prop;
		}
		current_gen[i].fit=0;
	}//creat random generation
	
	while(1){
		find=fitness(password, current_gen,password_has_num);
		
		if(find>-1)
			break;

		exchange(current_gen, next_gen);
		gen_num++;
		
	}

	PrintResult(current_gen,gen_num, find);
	
	return 0;
} 

int* choose(struct gen* p){
	int choice[2];
	int i,j;
	int temp;
	float portion[6];
	
	GivePortion(p,portion);
	
	choice[0]=GoRoulette(portion);
	
	while (1) {
	
		temp=GoRoulette(portion);
		
		if(choice[0]!=temp){
			choice[1]=temp;
			break;
		}
			
	}
	
	return choice;
}   

void exchange(struct gen* p, struct gen* n){
	int* parent;
	int i,j;
	int first, second;
	int temp;


	for(i=0;i<6;i++){
		parent=choose(p);
		first = parent[0];
		second = parent[1];
		/*for (j = 0; j < 6; j++) {
			temp   = rand() % 2;
			if (temp == 1) {
				n[i].word[j] = p[second].word[j];
			}
			else
				n[i].word[j] = p[first].word[j];
		}*/
		for(j=0;j<4;j++)
			n[i].word[j]=p[first].word[j];
		
		for(j=4;j<6;j++)
			n[i].word[j]=p[second].word[j];
	}

	mutant(n);

	ChildToParent(p,n);
	
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

	for(i=0;i<6;i++){
		if(g[i].fit==72){
			return i;
		}
	}
	return -1;
}

void PrintResult(struct gen* result_gen, int gen_num, int find){
	int i,j;
	
	printf("Find it!! Your pass word is ");
	for(i=0;i<6;i++)
		printf("%d",result_gen[find].word[i]);
	printf("!\n");
	printf("To find out, use %d generation.\n",gen_num);
}

void GivePortion(struct gen* p, float* portion){
	int i;
	int sum=0;
	
	for(i=0;i<6;i++){
			sum=sum+p[i].fit;
	}
	
	for(i=0;i<6;i++){
		portion[i]=(p[i].fit * 100 / sum);
	}
	
}

int GoRoulette(float* portion){
	int roulette_point, i;
	int sum=0;
	
	roulette_point=rand()%100;
	
	for(i=0;i<5;i++){
		sum = sum + portion[i];
		
		if(roulette_point<sum)
			return i;
	}
	
	return 5;
}

void ChildToParent(struct gen* p, struct gen* n){
	int i,j;
	
	for(i=0;i<6;i++){
		for(j=0;j<6;j++){
			p[i].word[j]=n[i].word[j];
		}
		p[i].fit=0;
	}
	
}

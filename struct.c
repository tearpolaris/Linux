#include <sbc.h>
#include <credential.h>
#include <struct.h>
#include <xyz.h>
#include <nadal.h>
#include <stdio.h>
#include <stdlib.h>
struct tennis {
struct student {
	char name[40];
	char code[10];
	float	score;
};

typedef struct student stden;

void input_info(stden *sample, int num);
void sort_name(stden *sample, int num);
void print_info(stden *sample, int num);

int main() {
 	int num_std;
	char temp;
	stden *pst;
        printf("Input number of student: ");
	scanf("%d", &num_std);
	//fflush(stdin);
	temp = getchar();
	pst = (stden*)malloc(num_std * sizeof(stden));
      	printf("----------------------------------\n");
	printf("Input information of students\n");
      	printf("----------------------------------\n");
	
	input_info(pst, num_std);
 	sort_name(pst, num_std);
	print_info(pst, num_std);
	//sort_name(pst);
	
	
}

void input_info (stden *sample, int num) {
	int i; 
	char tmp;
	for (i=0; i < num; i++) {
                //fflush(stdin);
 		printf("Enter name of student %d: ",i+1);
		//scanf("%[^\n]%*c", sample->name);
		scanf("%[^\n]%*c", sample->name);
 		printf("Enter his/her code: ");
		scanf("%[^\n]%*c", sample->code); 
 	        printf("Enter his/her score: ");
		scanf("%f", &(sample->score));
		tmp = getchar();
		sample++;
         }
}

void print_info(stden *sample, int num) {
	int i;
	for (i=0; i < num; i++) {
		printf("Name of student %d: %s\n", i+1, sample->name);
		printf("Code of student %s is %s\n",sample->name, sample->code);
		printf("Score of student %s is %f\n",sample->name, sample->score);
		sample++;
	}
}

void sort_name (stden *sample, int num) {
	int i,j, flag;
	stden temp;
	for (i = 0; i < num; i++) {
		flag = 0;
		for (j=0; j < num -i-1; j++) {
			//printf("j is %d and score is %f and %f\n",j,((sample+j)->score), ((sample+j+1)->score));
			if (((sample+j)->score) > ((sample + j+1)->score)) {
				temp = *(sample+j+1);
				*(sample+j+1) = *(sample + j);
				*(sample +j) = temp;
				flag = 1;
			}
		}
		if (flag == 0) {
			printf("Already is sorted\n");	
			break;
		}
	}
}
				

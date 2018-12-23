Test for hotfix branch
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 6

struct package
{
	char* id;
	int weight;
};

typedef struct package package;

struct post_office
{
	int min_weight;
	int max_weight;
	package* packages;
	int packages_count;
};

typedef struct post_office post_office;

struct town
{
	char* name;
	post_office* offices;
	int offices_count;
};

typedef struct town town;



void print_all_packages(town t) {
    printf("%s:\n",t.name);
    for (int i=0; i < t.offices_count; i++)  {
        printf("\t%d:\n", i);
        for(int j=0; j < t.offices[i].packages_count;j++)  {
            printf("\t\t%s\n", t.offices[i].packages[j].id);
        }
   }
}

void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {
    int reject = 0;
    package *temp = NULL;
    //post_office *source = source->offices[source_office_index];
    //post_office *des = target->offices[target_office_index];

    for (int j=0; j < source->offices[source_office_index].packages_count; j++) {
        if ((source->offices[source_office_index].packages[j].weight >= target->offices[target_office_index].min_weight) 
            && (source->offices[source_office_index].packages[j].weight <= target->offices[target_office_index].max_weight)) {
            target->offices[target_office_index].packages_count += 1;
            target->offices[target_office_index].packages = (package*)realloc(target->offices[target_office_index].packages, sizeof(package)*target->offices[target_office_index].packages_count);
            target->offices[target_office_index].packages[target->offices[target_office_index].packages_count-1]= source->offices[source_office_index].packages[j];  
        }
        else {
            reject++;
            temp = (package*) realloc(temp, sizeof(package)*reject);
            temp[reject-1] = source->offices[source_office_index].packages[j];
        }
        source->offices[source_office_index].packages = temp;
        source->offices[source_office_index].packages_count = reject;
    }
}            

void send_all_acceptable_packages_1(town* source, int source_office_index, town* target, int target_office_index) {
    int reject = 0;
    package *temp = NULL;
    post_office *src = source->offices + source_office_index;
    post_office *des = target->offices + target_office_index;

    for (int j=0; j < src->packages_count; j++) {
        if ((src->packages[j].weight >= des->min_weight) && (src->packages[j].weight <= des->max_weight)) {
            des->packages_count += 1;
            des->packages = (package*)realloc(des->packages, sizeof(package)*des->packages_count);
            des->packages[des->packages_count-1]= des->packages[j];  
        }
        else {
            reject++;
            temp = (package*) realloc(temp, sizeof(package)*reject);
            temp[reject-1] = src->packages[j];
        }
        src->packages = temp;
        src->packages_count = reject;
    }
}            

town town_with_most_packages(town* towns, int towns_count) {
    int total_package = 0, temp = 0;
    int pos = 0;
    for (int i=0; i < towns_count;i++) {
        for (int j=0; j < towns[i].offices_count; j++ ) {
            temp = towns[i].offices[j].packages_count + temp; 
        }      
        if (temp > total_package) {
            total_package = temp;
            pos = i;
        }
    }
    return towns[pos];
}
town* find_town(town* towns, int towns_count, char* name) {
    town* find =  NULL;
    for (int i=0; i < towns_count; i++) {
        if (strcmp(towns[i].name, name) == 0) {
            find = towns + i;
            break;
        }
    }
    return find;
}
//void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {	
//}
//
//town town_with_most_packages(town* towns, int towns_count) {
//}
//
//town* find_town(town* towns, int towns_count, char* name) {
//}

int main()
{
	int towns_count;
        printf("Nhap vao so thanh pho: ");
	scanf("%d", &towns_count);
	town* towns = malloc(sizeof(town)*towns_count);
	for (int i = 0; i < towns_count; i++) {
		towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
                printf("Nhap vao ten cua thanh pho %d: ",i+1);
		scanf("%s", towns[i].name);
                printf("Nhap vao so offices: ");
		scanf("%d", &towns[i].offices_count);
		towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
		for (int j = 0; j < towns[i].offices_count; j++) {
                        printf("Nhap vao so packages, min_weight va max_weight: ");
			scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
			towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
			for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
				towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
                                printf("Nhap vao id cua packages %d: ",k+1);
				scanf("%s", towns[i].offices[j].packages[k].id);
                                printf("Nhap vao weight cua packages %d: ",k+1);
				scanf("%d", &towns[i].offices[j].packages[k].weight);
			}
		}
	}
        print_all_packages(towns[1]);
	//int queries;
	//scanf("%d", &queries);
	char town_name[MAX_STRING_LENGTH];
	//while (queries--) {
	//	int type;
	//	scanf("%d", &type);
	//	switch (type) {
	//	case 1:
	//		scanf("%s", town_name);
	//		town* t = find_town(towns, towns_count, town_name);
	//		print_all_packages(*t);
	//		break;
	//	case 2:
	//		scanf("%s", town_name);
	//		town* source = find_town(towns, towns_count, town_name);
	//		int source_index;
	//		scanf("%d", &source_index);
	//		scanf("%s", town_name);
	//		town* target = find_town(towns, towns_count, town_name);
	//		int target_index;
	//		scanf("%d", &target_index);
	//		send_all_acceptable_packages(source, source_index, target, target_index);
	//		break;
	//	case 3:
	//		printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
	//		break;
	//	}
	//}
	return 0;
}

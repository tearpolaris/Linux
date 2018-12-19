#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct triangle
{
	int a;
	int b;
	int c;
};
typedef struct triangle triangle;

void sort_by_area(triangle* tr, int n) {
	/**
	* Sort an array a of the length n
	*/
    double S0 = 0, S1 = 0;
    double p0, p1;
    int tmp_a, tmp_b, tmp_c, max_position;
    for (int i = 0; i < n; i++) {
        //max_position = i;
        //printf("Gia tri Smax tai %d la: %lf\n", i, S0);
        for (int j = 0; j < n-i; j++) {
          p0 = ((double)tr[j].a + (double)tr[j].b + (double)tr[j].c)/2;
          S0 = sqrt(p0*(p0-tr[j].a)*(p0-tr[j].b)*(p0-tr[j].c));

          p1 = ((double)tr[j+1].a + (double)tr[j+1].b + (double)tr[j+1].c)/2; 
          S1 = sqrt(p1*(p1-tr[j+1].a)*(p1-tr[j+1].b)*(p1-tr[j+1].c));
         printf("Gia tri S1 tai %d la: %lf\n", j, S1);

          if (S0 > S1 ) {          
            tmp_a = tr[j].a;
            tmp_b = tr[j].b;
            tmp_c = tr[j].c;
            tr[j].a = tr[j+1].a;
            tr[j].b = tr[j+1].b;
            tr[j].c = tr[j+1].c;
            tr[j+1].a = tmp_a;
            tr[j+1].b = tmp_b;
            tr[j+1].c = tmp_c;
            //max_position = j;
         }
    }
  }
}

int main()
{
	int n;
        printf("Nhap vao so tam giac: ");
	scanf("%d", &n);
	triangle *tr = malloc(n * sizeof(triangle));
	for (int i = 0; i < n; i++) {
                printf("Nhap vao ba canh cua tam giac: ");
		scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
	}
	sort_by_area(tr, n);
	for (int i = 0; i < n; i++) {
		printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
	}
	return 0;
}

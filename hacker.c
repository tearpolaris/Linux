#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5
char*** kth_paragraph(char**** document, int k) {
    char*** para;
    int count = 0;
    int tmp_k;
    int exit = 0;
    tmp_k = k-1;
    for (int i = 0; ((i < strlen(***document)) && (exit == 0)); i++) {
        if (tmp_k == 0) {
            for (int i=0; strcmp(***(document+i), "\n") != 0; i++ ) {
            ***(para+i) = ****(document+i);
            }
            exit = 1;
        }
        else {
            if (strcmp(***(document+i), "\n") != 0) {
                count++;
            }
            if (count == tmp_k) {
                int k = 0;
                for (int j = i+1; (strcmp(***(document+i), "\n") != 0) || (strcmp(***(document+i), "\0") != 0); j++) {
                    ***(para+k) = ****(document+j);
                    k++;
                }
                exit = 1;
            }
        }
    }
    return para;
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) { 
    char** senten;
    char*** para;
    int count = 0;
    int tmp_k;
    int index = 0;
    int exit = 0;
    tmp_k = m-1;
    
    para = kth_paragraph(document, m);
    for (int i = 0; ((i < strlen(**para)) && (exit == 0)); i++) {
        if (tmp_k == 0) {
            for (int i=0; strcmp(**(para+i), ".") != 0; i++ ) {
            **(senten+i) = ***(para+i);
            }
            exit = 1;
        }
        else {
            if (strcmp(**(para+i), ".") != 0) {
                count++;
            }
            if (count == tmp_k) {
                int k = 0;
                for (int j = i+1; (strcmp(**(para+i), ".") != 0) || (strcmp(**(para+i), "\0") != 0); j++) {
                    **(senten+k) = ***(para+j);
                    k++;
                }
                exit = 1;
            }
        }
    }
    return senten;
}

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
    char** senten;
    char *wd;
    int count = 0;
    int tmp_k;
    int index = 0;
    int exit = 0;
    tmp_k = k-1;
    
    senten = kth_sentence_in_mth_paragraph (document,m,n);
    for (int i = 0; ((i < strlen(*senten)) && (exit == 0)); i++) {
        if (tmp_k == 0) {
            for (int i=0; strcmp(*(senten+i), " ") != 0; i++ ) {
            *(wd+i) = **(senten+i);
            }
            exit = 1;
        }
        else {
            if (strcmp(*(senten+i), " ") != 0) {
                count++;
            }
            if (count == tmp_k) {
                int k = 0;
                for (int j = i+1; (strcmp(*(senten+i), " ") != 0) || (strcmp(*(senten+i), "\0") != 0); j++) {
                    *(wd+k) = **(senten+j);
                    k++;
                }
                exit = 1;
            }
        }
    }
    return wd;
}


char**** get_document(char* text) {
    //printf ("abcxyz\n");
    char**** pt;
    //printf ("anh af\n");
    printf("Chieu dai cua chuoi: %ld", strlen (text));
    //for (int i = 0; i < strlen(text); i++) {
    //    ****(pt+i) = text[i];
    //}
    ***pt = (char*) malloc((strlen(text)+1) * (sizeof(char)));
    strcpy(***pt, text);
    return pt;
}
char* get_input_text() {	
    int paragraph_count;
    printf ("Nhap vao so doan: ");
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        printf ("Nhap vap doan thu %d:\n",i+1);
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    printf ("Nhap vao so tu cua cau can in: ");
    scanf("%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
} 

void print_paragraph(char*** paragraph) {
    int sentence_count;
    printf("Nhap vao so cau can in cua doan van: ");
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

int main() 
{
    char* text = get_input_text();
    printf ("next get_document\n");
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            printf ("Nhap vao doan van muon in ra: ");
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }     
}

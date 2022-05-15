#include <stdio.h>
#include <string.h>
#define NEDELI 4
#define DENOVI 5

// ovde strukturata RabotnaNedela
struct RabotnaNedela {
    int rabotniCasovi[DENOVI];
    int brojNedela;
};
typedef struct RabotnaNedela RN;

// ovde strukturata Rabotnik
struct Rabotnik {
    char imeRabotnik[50];
    RN rabotniNedeli[NEDELI];
};
typedef struct Rabotnik R;

// ovde funkciite
int maxNedela(R *r){
    int i, j, sumCasoviNedela=0, maxNedela=0, max=0;
    for(i=0; i<4; i++){
        sumCasoviNedela=0;
        for(j=0; j<5; j++){
            sumCasoviNedela+=r->rabotniNedeli[i].rabotniCasovi[j];
        }
        if(sumCasoviNedela>max){
            maxNedela=i+1;
            max=sumCasoviNedela;
        }
    }
    
    return maxNedela;
}

void table(R *r, int n){
    int vkNedela[4], vkCasovi=0, i, j, rbt, vkCN=0;
    printf("Rab\t1\t2\t3\t4\tVkupno\n");
    for(rbt=0; rbt<n; rbt++){
        vkCasovi=0;
        for(i=0; i<NEDELI; i++){
            vkCN=0;
            for(j=0; j<DENOVI; j++){
                vkCN+=r[rbt].rabotniNedeli[i].rabotniCasovi[j];
            }
            vkNedela[i]=vkCN;
            vkCasovi+=vkNedela[i];
        }
        printf("%s\t", r[rbt].imeRabotnik);
        for(i=0; i<4; i++){
            printf("%d\t", vkNedela[i]);
        }
        printf("%d\n", vkCasovi);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    R rabotnici[n];
    int i;
    for (i = 0; i < n; ++i) {
        scanf("%s", rabotnici[i].imeRabotnik);
        int j;
        for (j = 0; j < NEDELI; ++j) {
            int k;
            for (k = 0; k < DENOVI; ++k) {
                scanf("%d", &rabotnici[i].rabotniNedeli[j].rabotniCasovi[k]);
            }

        }
    }
    printf("TABLE\n");
    table(rabotnici, n);
    printf("MAX NEDELA NA RABOTNIK: %s\n", rabotnici[n / 2].imeRabotnik);
    printf("%d\n", maxNedela(&rabotnici[n / 2]));
    return 0;
}

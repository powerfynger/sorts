#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

int *mass_orig = NULL, *mass_q = NULL, *mass_s = NULL;

void sortt(int i){
    int k, x;
    for(int j = 1; j <= i - 1;j++){
        k = j;
        x = mass_s[j];
        while(k > 0 && x <= mass_s[k - 1]){
            mass_s[k] = mass_s[k-1];
            k--;
        }
        mass_s[k] = x;
    }    
}

void qsortt(int l, int r){
    int temp, k, j, x;
    k = l;
    j = r;
    x = mass_q[(l+r)/2];
    do{
        while(mass_q[k] < x) k++;
        while(mass_q[j] > x) j--;
        if(k <= j){
            temp = mass_q[k];
            mass_q[k] = mass_q[j];
            mass_q[j] = temp;
            k++; 
            j--;
        }
    }while (k <= j);
    if(j > l) qsortt(l, j);
    if(k < r) qsortt(k, r);
}    
//asd.txt -s -q -all
int main(int argc, char *argv[]){
    //printf("arg0:%s arg1:%s arg2:%s arg3:%s", argv[0], argv[1], argv[2], argv[3]);
    //Открытие файла
    FILE *file = fopen(argv[1], "r");
    if(file == NULL){
        printf("Не удалось найти файл для чтения \n");
        return 0;
    }
    char str[10000*4], *str2;
    int i = 0;
    //Считывание строки и заполнение массива
    fgets(str, 10000, file);
    str2 = strtok(str, " ");
    mass_orig = (int*)realloc(mass_orig, (i+1)*sizeof(int));
    mass_q = (int*)realloc(mass_q, (i+1)*sizeof(int));
    mass_s = (int*)realloc(mass_s, (i+1)*sizeof(int));
    mass_orig[i] = atoi(str2);
    mass_q[i] = atoi(str2);
    mass_s[i] = atoi(str2);
    str2 = strtok(NULL, " ");
    for(i = 1; str2 != NULL;i++){
        mass_orig = (int*)realloc(mass_orig, (i+1)*sizeof(int));
        mass_q = (int*)realloc(mass_q, (i+1)*sizeof(int));
        mass_s = (int*)realloc(mass_s, (i+1)*sizeof(int));
        mass_orig[i] = atoi(str2); 
        mass_q[i] = atoi(str2);
        mass_s[i] = atoi(str2);
        str2 = strtok(NULL, " ");
        
    }            //Алгоритм сортировки массива
    FILE *file_out = fopen(argv[3], "w");
    if(file_out == NULL){
        printf("Не удалось найти файл для записи\n");
        return 0;
    }
    // Обычная сортировка 
    if(argv[2][0] == '-' && argv[2][1] == 's'){
        sortt(i);
        for(int j = 0; j < i; j++){
            fprintf(file_out, "%d ", mass_s[j]);
        }
        return 0;
    }
    //Быстрая сортировка 
    if(argv[2][0] == '-' && argv[2][1] == 'q'){
        qsortt(0,i-1);
        for(int j = 0; j < i; j++){
            fprintf(file_out, "%d ", mass_q[j]);
            
        } 
        return 0;
    }
    
    if(argv[2][0] == '-' && argv[2][1] == 'a' && argv[2][2] == 'l' && argv[2][3] == 'l'){
        sortt(i);
        qsortt(0, i-1);
        fputs("quick sort: ", file_out);
        for(int j = 0; j < i; j++){
            fprintf(file_out, "%d ", mass_q[j]);
        }
        fputs("\nregular sort: ", file_out);
        for(int j = 0; j < i; j++){
            fprintf(file_out, "%d ", mass_s[j]);
        }
        //printf("\n%d", strcmp(mass_q, mass_s));
        return 0;
    }   
    printf("Неправильные аргументы, используйте:\n-s - медленная сортировка\n-q - быстрая сортировка\n-all - все виды сортировок\n");
    return 0;
    
}
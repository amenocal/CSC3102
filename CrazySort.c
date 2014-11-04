#include <stdio.h>

void crazySort(int items[], int numItems);

int main(void){
  
   int items[6] = {3,2,4,5,2,0};
   crazySort(items,6);
   getchar();
   return 0;
   
}

void crazySort(int items[], int numItems)
{
    int i, j, small, x;
    for (i=0;i<numItems; i++){
        for (j=i+1;j<numItems;j++){
            if (items[i] >items[j]) {
                small = items[j];items[j] = items[i];
                items[i] = small;
            }
            printf("%d, %d ", i, j);
            printf("[");
            for(x=0;x<6;x++){
                
                printf("%d", items[x]);
                //printf("%d%d",i,j);
            }
            printf("]\n");
    }
}
    
}

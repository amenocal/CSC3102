#include <stdio.h>

void AddToHeap(int itemNum, int numItems);
void MakeHeap(int numItems);
void HeapSort(int numItems);
void PrintIntArray(int nums[], int numItems);
int nums[] = {0,1,2,3,4,5,6,7,8,9};
int numItems = 10;
int main(void)
{   int i;
    HeapSort(numItems);
    PrintIntArray(nums,numItems);
    return 0;
}
void PrintIntArray(int nums[], int numItems)
{    int i;
    printf("[%d", nums[0]);
    for (i=1;i<numItems;i++)
        printf(", %d", nums[i]);
    printf("]\n");
    
}
void AddToHeap(int itemNum, int numItems)
{   int j, temp;    //j=largestchild
    int i = itemNum;
    if (2*i+1< numItems)
    {  if ((2*itemNum+2 < numItems) && 
           (nums[2*itemNum+1] <nums[2*itemNum+2]))
        j=2*i+2;
    else j=2*i+1;
        if (nums[j] > nums[i])
        {   temp = nums[j]; nums[j] = nums[i];
            nums[i] = temp;
            //printf("Parent, Child Exchange: Nums[%d] = %d, Nums[%d]=%d\n",i,nums[j],j,nums[i]);
            AddToHeap(j,numItems);
        }
    }
}
void MakeHeap(int numItems)
{   int i;
    if (1 == numItems) return;
    else 
        for (i = numItems/2-1; i >= 0; i--)
            AddToHeap(i,numItems);
}
void HeapSort(numItems)
{   int temp, i, j;
    if (1 == numItems) return;
    else {
        MakeHeap(numItems);
        for (i=numItems-1; i>=1; i--)
        {   PrintIntArray(nums, i);
            temp = nums[0]; nums[0] = nums[i]; nums[i] = temp;
            PrintIntArray(nums,i);
            AddToHeap(0,i);
        }
    }
}

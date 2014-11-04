#include <stdio.h>

int main(void)
{
    int i1,i2,i3,i4,i5,i6,i7,x;
    for (i1=1;i1<=7;i1++) {
        for(i2=1;i2<=7;i2++) {
            for(i3=1;i3<=7;i3++) {
                for(i4=1;i4<=7;i4++) {
                    for(i5=1;i5<=7;i5++) {
                        for(i6=1;i6<=7;i6++) {
                            for(i7=1;i7<=7;i7++) {
                                
    if (i7==i6 || i7==i5 || i7==i4 || i7==i3 || i7==i2 || i7==i1 ||i6==i5 || 
        i6==i4 || i6==i3 || i6==i2 || i6==i1 || i5==i4 || i5==i3 || i5==i2 || i5==i1 || i4==i3 || i4==i2 || i4==i1 ||i3==i2 || i3==i1 || i2==i1) continue;
                                
                                if (i7<i6 || i7 < i5) continue;
                                if (i6<i4) continue;
                                if (i5<i3) continue;
                                if (i3<i2 || i3<i1) continue;
                                
                                for(x=1;x<31;x++){
                                    printf("x = %d == i7: %d i6: %d i5: %d i4: %d i3: %d i2: %d i1: %d\n",x, i7,i6,i5,i4,i3,i2,i1);}
                                
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
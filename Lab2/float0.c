# include <stdio.h>
# include <string.h>

int main(){
    printf("1.0 / Float_MIN = %g\n",1.0/0x1p-149);
    printf("1.0 / 0 = %f\n",1.0/0.0);
    return 0;
}
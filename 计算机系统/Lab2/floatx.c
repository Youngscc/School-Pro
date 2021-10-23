# include <stdio.h>
# include <string.h>

int main() {
    float pos_zero = +0.0f;
    float neg_zero = -0.0f;
    float pos_max, pos_min, pos_norm_min, pos_inf, nan;
    *(int*)(&pos_max) = 0x7F7FFFFF;
    *(int*)(&pos_min) = 0x00000001;
    *(int*)(&pos_norm_min) = 0x00800000;
    *(int*)(&pos_inf) = 0x7F800000;
    *(int*)(&nan) = 0x7F800001;
    printf("pos_zero = %.9g  hex: %a\n",pos_zero,pos_zero);
    printf("neg_zero = %.9g  hex: %a\n",neg_zero,neg_zero);
    printf("pos_max = %.9g  hex: %a\n",pos_max,pos_max);
    printf("pos_min = %.9g  hex: %a\n",pos_min,pos_min);
    printf("pos_norm_min = %.9g  hex: %a\n",pos_norm_min,pos_norm_min);
    printf("pos_inf = %.9g  hex: %a\n",pos_inf,pos_inf);
    printf("NAN = %.9g  hex: %a\n",nan,nan);
    return 0;
}
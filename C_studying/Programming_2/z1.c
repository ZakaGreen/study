#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

double f1(double x){
    if (x < 0){
        return 0;
    }
    else {
        return 1;
    }
}

double f2(double x){
    if (x <= 0){
        return 0;
    }
    else {
        return x;
    }
}

double f3(double x){
    double f;
    f = 0.5 * (x + sqrt(x * x + 2));
    return f;
}

double f4(double x){
    double f;
    f = exp(-(x * x));
    return f;
}

double f5(double x){
    double f;
    f = (exp(x) - exp(-x)) / (exp(x) + exp(-x));
    return f;
}

double f6(double x){
    double f;
    f = x / (1 + exp(-0.5 * x));
    return f;
}

void table(int a, int width, double start, double end, double step, int precision){
    switch (a){
        case 1:
        printf("%*d", width, a); 
        for (double i = start; i <= end; i += step){
            printf("%*.*lf", width, precision, f1(i));
        }
        printf("\n"); return;
        case 2: 
        printf("%*d", width, a); 
        for (double i = start; i <= end; i += step){
            printf("%*.*lf", width, precision, f2(i));
        }
        printf("\n"); return;
        case 3: 
        printf("%*d", width, a); 
        for (double i = start; i <= end; i += step){
            printf("%*.*lf", width, precision, f3(i));
        }
        printf("\n"); return;
        case 4: 
        printf("%*d", width, a); 
        for (double i = start; i <= end; i += step){
            printf("%*.*lf", width, precision, f4(i));
        }
        printf("\n"); return;
        case 5: 
        printf("%*d", width, a); 
        for (double i = start; i <= end; i += step){
            printf("%*.*lf", width, precision, f5(i));
        }
        printf("\n"); return;
        case 6: 
        printf("%*d", width, a); 
        for (double i = start; i <= end; i += step){
            printf("%*.*lf", width, precision, f6(i));
        }
        printf("\n"); return;
        default: return;
    }
}

int main(void) {
    char x = 'x';
    int precision, width, a, mode = 0, flag = 0;
    double start, end, step;
    if ((scanf("%lf %lf %lf %d %d", &start, &end, &step, &precision, &width)) != 5){
        printf("E1");
        return 0;
    }

    if (start >= end){
        printf("E2");
        return 0;
    }

    if ((scanf("%d", &a)) == 1){
        mode = 1;
        if (a <= 6 && a >= 1){
            flag = 1;
            printf("%*c", width, x);
            for (double i = start; i <= end; i += step){
                printf("%*.*lf", width, precision, i);
            }
            printf("\n");
            table(a, width, start, end, step, precision);
        }
        while ((scanf("%d", &a)) == 1){
            if ((a <= 6 && a >= 1) && (flag == 0)){
                flag = 1;
                printf("%*c", width, x);
                for (double i = start; i <= end; i += step){
                    printf("%*.*lf", width, precision, i);
                }
                printf("\n");
            }
            table(a, width, start, end, step, precision);
        }
   }

    if (mode == 0){
        printf("%*c%*d%*d%*d%*d%*d%*d\n", width, x, width, 1, width, 2, width, 3, width, 4, width, 5, width, 6);
        for (double i = start; i <= end; i += step){
            printf("%*.*lf", width, precision, i);
            printf("%*.*lf", width, precision, f1(i));
            printf("%*.*lf", width, precision, f2(i));
            printf("%*.*lf", width, precision, f3(i));
            printf("%*.*lf", width, precision, f4(i));
            printf("%*.*lf", width, precision, f5(i));
            printf("%*.*lf\n", width, precision, f6(i));
        }
   }
    return 0;
}


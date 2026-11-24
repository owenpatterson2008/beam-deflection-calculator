#include <stdio.h>
#include <math.h>

void calcI(float b, float h, float* ptr_I);
void cantilever(float P, float L, float E, float* ptr_deflected, float I);
void SimplySupported(float P, float L, float E, float* ptr_deflected, float I);

int main(void){
    //variables
    int CorSS,Material;
    float E,I,P,L,b,h,deflected,limit;

    //while statement
    while(1){
        //menu
        printf("\nChoose cantilever or simply supported:\n");
        printf("Cantilever (load at free end):         1\n");
        printf("Simply supported (load in the middle): 2\n");
        printf("Enter 0 to quit\n");
        printf("----------------------------------------\n");
        scanf("%d",&CorSS);
        //check the beam choice right away
        if(CorSS==0){
            break;
        }
        if(CorSS!=1 && CorSS!=2){
            printf("Invalid option.\n");
            continue;
        }
        //Materials used
        printf("What material are you using?\n");
        printf("1 = steel\n");
        printf("2 = aluminum\n");
        printf("3 = wood\n");
        printf("------------------------------\n");
        scanf("%d",&Material);
        if(Material==1){
            E=200e9;
        }else if(Material==2){
            E=69e9;
        }else if(Material==3){
            E=11e9;
        }else{
            printf("Invalid material choice.\n");
            continue;
        }
        //Getting the load, length, width, and height
        printf("Enter the load (N), the length (m), the width (mm), and the height (mm), separated by spaces: ");
        scanf("%f %f %f %f", &P, &L, &b, &h);
        //all four values must be positive (a zero height would mean dividing by zero)
        if(P<=0 || L<=0 || b<=0 || h<=0){
            printf("All values must be greater than 0.\n");
            continue;
        }
        //converting mm to m
        b=b/1000.0;
        h=h/1000.0;
        //Calling I function
        calcI(b,h,&I);
        //Cantilever or Simply Supported
        if(CorSS==1){
            //cantilever deflection
            cantilever(P,L,E,&deflected,I);
        }else if(CorSS==2){
            //simply supported deflection
            SimplySupported(P,L,E,&deflected,I);
        }
        //print output
        printf("\nSecond moment of area I: %.3e m^4\n",I);
        printf("Deflection: %.3f mm\n",deflected);
        //safety check: deflection should not be more than L/360 (converted to mm)
        limit=L*1000.0/360.0;
        printf("Allowed deflection (L/360): %.3f mm\n",limit);
        if(deflected<=limit){
            printf("Result: OK, the beam passes the L/360 check.\n");
        }else{
            printf("Result: TOO MUCH DEFLECTION, use a stiffer material or a taller beam.\n");
        }
    }
    return 0;
}
void calcI(float b, float h, float* ptr_I){
    (*ptr_I)=b*pow(h,3)/12.0;

    return;
}
void cantilever(float P, float L, float E, float* ptr_deflected, float I){
    (*ptr_deflected)=P*pow(L,3)/(3.0*E*I);
    //in mm
    (*ptr_deflected)=(*ptr_deflected)*1000.0;

    return;
}
void SimplySupported(float P, float L, float E, float* ptr_deflected, float I){
    (*ptr_deflected)=P*pow(L,3)/(48.0*E*I);
    //in mm
    (*ptr_deflected)=(*ptr_deflected)*1000.0;

    return;
}

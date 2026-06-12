#define order 5

void polynome(float x[1024], float F[1024])
{


const float coef[order]={-3.4, 2, -1.25, 0.68, 1};
float sal;

 DataLoop: for (int i=0; i<1024; i++) {
    sal=0;

    evalLoop: for (int j=order-1; j>=0; j--){
    	sal=sal*x[i]+coef[j];
    }

    F[i]=sal;
 }
}

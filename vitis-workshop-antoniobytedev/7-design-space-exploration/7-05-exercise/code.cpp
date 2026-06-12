#define SIZE 256
 void insertion_sort(int A[SIZE], int B[SIZE]) 
 {

 L1:for(int i = 0; i < SIZE; i++) 
    {
        int item = A[i];
        L2:for(int j = SIZE-1; j >= 0; j-- ) 
        {
            int t;
            if(j > i) 
            {
                t = B[j];
            }else if(j > 0 && B[j-1] > item) {
                t = B[j-1];
            }else{
                t = item;
                if (j > 0)
                {
                item = B[j-1];
                }
            }

            B[j] = t;  
        }
    }
}



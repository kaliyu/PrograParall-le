#include <iostream>
#include <omp.h>
using namespace std;

#define TOTAL 2000000

int main(int, char *[])
{
    int pass=0;
    double start = omp_get_wtime();
    #pragma omp parallel
    {
      int id = omp_get_thread_num();
      int np = omp_get_num_threads();
      int mycur;
      for(int i=id; i<TOTAL; i+=np) {
        mycur=i;
        while (mycur>1)
          mycur=mycur%2?3*mycur+1:mycur/2;
        #pragma omp critical
        {
          pass++;
        }
        
      }
    }
    double end = omp_get_wtime();
    cout << pass << " out of " << TOTAL << "! (delta=" << TOTAL-pass << ")" << endl;
    cout << "ellapsed time: " << (end-start)*1000 << "ms" << endl; 
}
#include <iostream>
#include <omp.h>
#include <stdlib.h>
#define cimg_display 0
#define cimg_plugin "fits.h"
#include "CImg.h"
using namespace cimg_library;
using namespace std;

int main(int, char *argv[]) {
  CImg<short> astro(argv[1]);
  CImg<unsigned char> resca(astro.width(), astro.height(), 1, 1, 0);
  short amin = 32767, amax = 0;
  int i, j;
  int iterations = atoi(argv[2]);

  double start = omp_get_wtime();

  for (int k = 0; k < iterations; k++) {
    
    
      
      #pragma omp parallel{
        int id = omp_get_thread_num();
        int np = omp_get_num_threads();
        for (j = id; j < astro.height(); j+=np)
          for (i = 0; i < astro.width(); i++) {
            amin = min(amin, astro(i, j));
            amax = max(amax, astro(i, j));
          }
      }
      
      int arange = amax - amin;
      #pragma omp parallel
      {
        int id = omp_get_thread_num();
        int np = omp_get_num_threads();
        {
          for (j = id; j < astro.height(); j+=np)
            for (i = 0; i < astro.width(); i++)
              resca(i, j) = (short)(((int)astro(i, j) - amin) * 255 / arange);
        }
      }
      
  }
  double end = omp_get_wtime();
  cout << (end - start) / iterations << endl;
  resca.save_pnm("/tmp/resca.pgm");
  return 0;
}

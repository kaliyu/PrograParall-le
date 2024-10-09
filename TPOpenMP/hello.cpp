#include <iostream>
#include <omp.h>
using namespace std;


int main(int, char *[])
{
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int np = omp_get_num_threads();
        #pragma omp critical
        {
            cout << "bonjour " << id << "/" << np << endl;
        }
        #pragma omp barrier
        #pragma omp single
        {
            cout << "id : " << id << ", nous somme : " << np << endl;
            cout << "id : " << id << "fin du TP" << endl;
        }
        

        #pragma omp critical
        {
            cout << "au revoir " << id << "/" << np << endl;  
        }
        
    }
    
}
#include <cstdlib>
#include <iostream>
#include <utility>
#include <omp.h>

using namespace std;

void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void QuickSort(int* A, int q, int r) {
    if (q<r) {
        int x = A[q];
        int s = q;
        for (int i=q+1; i<r; i++) {
            if (A[i]<=x) {
                s++;
                swap(A+s,A+i);
            }
        }
        swap(A+q,A+s);
        QuickSort(A,q,s);
        QuickSort(A,s+1,r);
    }
}
void Partitionnement(int* tab, int n, int pivot, int nb_threads, int* s, int* r){
    pivot = rand() % n; 
    int pivot_value = tab[pivot]; 
    int taille_partition = n / nb_threads;
    #pragma omp parallel num_threads(nb_threads)
    {
        int id = omp_get_thread_num();
        int debut = id * taille_partition;
        int fin = (id+1) * taille_partition;
        int ss = debut;
        for (int i=debut+1; i<fin; i++) {
            if (tab[i]<=pivot) {
                swap(tab+ss,tab+i);
                ss++;
            }
            if(tab[i] <= pivot){
                s[id]++;
            }else{
                r[id]++;
            }
        }   
    }
    for (int i=0; i<n; i++)
        cout << tab[i] << " ";
    cout << endl;
}
int main(int argc, char** argv) {

    if (argc<2) {
        cout << "Mauvaise utilisation du programme :" << endl;
        cout << "./Tri [taille du tableau] " << endl;
        return 1;
    }

    int n = atoi(argv[1]);

    int* tab = new int[n];
    
    srand(time(NULL));
    for (int i=0; i<n; i++)
        tab[i] = rand()%20;
    int s[4], r[4];
    //avant partitionnement
    for (int i=0; i<n; i++)
        cout << tab[i] << " ";
    cout << endl;
    Partitionnement(tab,n,10,4,s,r);

    
    return 0;
}
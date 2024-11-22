
#include <stdio.h>
#include <immintrin.h>

int main(void)
{
    int n = 9;
    int reste = n % 4;


    float* array0 = (float*)_mm_malloc(n * sizeof(float), 16); //Initilalisation d'un tableau de float de taille n et aligné sur 16 octets.

    for(size_t i = 0 ; i < n ; ++i){   //Initialisation du tableau array0.
        array0[i] = (float)i;
    }
    
    __m128 somme = _mm_set1_ps(0.0f);
    for(size_t i = 0 ; i+4 < n ; i+=4){
        __m128 r0 = _mm_load_ps(&array0[i]);
        somme = _mm_add_ps(r0, somme);
    }


    float somme_value_reste = array0[n-reste];   //On parcourt le reste du tableau array0.
    for(size_t i = (n-reste); i < n ; ++i){
        somme_value_reste += array0[i];
    }


    float somme_array[4];
    _mm_store_ps(somme_array, somme);   //On récupère la valeur max entre les 4 éléments du vecteur max.
    for(int i = 0 ; i < 4 ; ++i){
        somme_value_reste += somme_array[i];
    }

    for(int i = 0 ; i < n ; ++i){
        printf("%f ", array0[i]);
    }
    printf("\n");

    float somme_value = somme_value_reste;
    printf("Somme value: %f\n", somme_value);

    _mm_free(array0);


    return 0;
}
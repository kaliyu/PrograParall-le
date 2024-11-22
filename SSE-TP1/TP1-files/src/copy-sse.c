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

    __m128 max = _mm_set1_ps(array0[0]); //_mm_set1_ps permet de créer un vecteur de 4 floats ayant la même valeur qui est à -infini.
    for(size_t i = 0 ; i+4 < n ; i+=4){
        __m128 r0 = _mm_load_ps(&array0[i]); // Load 4 values from the first array into a SSE register.
        r0 = _mm_max_ps(r0, max); // Modifie le vecteur r0 pour que chaque élément soit le max entre l'élément de r0 et de max.
    }


    float max_value_reste = array0[n-reste];   //On parcourt le reste du tableau array0.
    for(size_t i = (n-reste); i < n ; ++i){
        if(array0[i] > max_value_reste){
            max_value_reste = array0[i];
        }
    }


    float max_array[4];
    _mm_store_ps(max_array, max);   //On récupère la valeur max entre les 4 éléments du vecteur max.
    for(int i = 0 ; i < 4 ; ++i){
        if(max_array[i] > max_value_reste){
            max_value_reste = max_array[i];
        }
    }

    for(int i = 0 ; i < n ; ++i){
        printf("%f ", array0[i]);
    }
    printf("\n");

    float max_value = max_value_reste;
    printf("Max value: %f\n", max_value);

    _mm_free(array0);


    return 0;
}
#include <stdio.h>
#include <immintrin.h>

int main(void)
{
    int n = 9;
    int reste = n % 4;

    // Allocation mémoire alignée pour deux tableaux
    double* array0 = (double*)_mm_malloc(n * sizeof(double), 16);
    double* array1 = (double*)_mm_malloc(n * sizeof(double), 16);

    // Initialisation des tableaux array0 et array1
    for (size_t i = 0; i < n; ++i) {
        array0[i] = (double)i;
        array1[i] = (double)i;
    }

    // Initialisation du registre SSE pour la somme (sommeVecteur)
    __m128d sommeVecteur = _mm_set1_pd(0.0f);

    // Traitement par blocs de 4 éléments
    for (size_t i = 0; i <= n; i += 2) {
        __m128d r0 = _mm_load_pd(&array0[i]); // Charger 4 éléments de array0
        __m128d r1 = _mm_load_pd(&array1[i]); // Charger 4 éléments de array1
        __m128d r2 = _mm_mul_pd(r0, r1); // Multiplier les éléments correspondants
        sommeVecteur = _mm_add_pd(sommeVecteur, r2); // Ajouter à sommeVecteur
    }

    // Traitement des éléments restants (moins de 4 éléments)
    double somme_value_reste = 0.0f;
    for (size_t i = (n - reste); i < n; ++i) {
        somme_value_reste += array0[i] * array1[i]; // Multiplier et accumuler
    }

    // Stocker la somme des 4 premiers éléments dans un tableau
    double somme_array[2];
    _mm_store_pd(somme_array, sommeVecteur); // Récupérer les 4 valeurs de sommeVecteur

    // Ajouter ces valeurs au reste de la somme
    for (int i = 0; i < 2; ++i) {
        somme_value_reste += somme_array[i];
    }

    // Afficher les tableaux array0 et array1
    for (int i = 0; i < n; ++i) {
        printf("%f ", array0[i]);
    }
    printf("\n");

    for (int i = 0; i < n; ++i) {
        printf("%f ", array1[i]);
    }
    printf("\n");

    // Afficher la somme des produits
    printf("Somme des produits: %f\n", somme_value_reste);

    // Libérer la mémoire allouée
    _mm_free(array0);
    _mm_free(array1);

    return 0;
}
// -fsanitize=address,undefined

#include <stdio.h>
#include <immintrin.h>

#include <stdio.h>
#include <immintrin.h>

#include <stdio.h>
#include <immintrin.h>

int main(void)
{
    int n = 9;
    int reste = n % 4;

    // Allocation mémoire alignée pour deux tableaux
    unsigned short* array0 = (unsigned short*)_mm_malloc(n * sizeof(unsigned short), 16);
    unsigned short* array1 = (unsigned short*)_mm_malloc(n * sizeof(unsigned short), 16);

    // Initialisation des tableaux array0 et array1
    for (size_t i = 0; i < n; ++i) {
        array0[i] = (unsigned short)i;
        array1[i] = (unsigned short)i;
    }

    // Initialisation du registre SSE pour la somme (sommeVecteur)
    __m128i sommeVecteur = _mm_set1_epi16(0);  // No argument needed

    // Traitement par blocs de 4 éléments
    for (size_t i = 0; i <= n - 8; i += 8) {  // Change to ensure we process in multiples of 4
        __m128i r0 = _mm_load_si128((__m128i*)&array0[i]); // Charger 4 éléments de array0
        __m128i r1 = _mm_load_si128((__m128i*)&array1[i]); // Charger 4 éléments de array1
        __m128i r2 = _mm_add_epi16(r0, r1); // Ajouter les éléments correspondants
        sommeVecteur = _mm_add_epi16(sommeVecteur, r2); // Ajouter à sommeVecteur
    }

    // Traitement des éléments restants (moins de 4 éléments)
    unsigned short somme_value_reste = 0;
    for (size_t i = n - reste; i < n; ++i) {
        somme_value_reste += array0[i] + array1[i]; // Additionner les éléments restants
    }

    // Stocker la somme des premiers éléments dans un tableau
    unsigned short somme_array[8];  // Allocate space for the SSE register values
    _mm_store_si128((__m128i*)somme_array, sommeVecteur);  // Récupérer les valeurs de sommeVecteur

    // Ajouter ces valeurs au reste de la somme
    for (int i = 0; i < 8; ++i) {
        somme_value_reste += somme_array[i];  // Accumuler la somme
    }

    // Afficher la somme des produits
    printf("Somme des produits: %u\n", somme_value_reste);  // Change %f to %u for unsigned short

    // Libérer la mémoire allouée
    _mm_free(array0);
    _mm_free(array1);

    return 0;
}
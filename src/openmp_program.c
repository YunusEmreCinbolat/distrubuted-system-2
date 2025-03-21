#include <omp.h>
#include <stdio.h>

int main() {
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        printf("Merhaba! Ben thread %d/%d\n", id, num_threads);
    }
    return 0;
}

#include "data_structure/base.h"

int main(int argc, char *argv[]) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    dinamico(argc, argv);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    // printf("Dinamico took %f seconds to execute \n", cpu_time_used);
    return 0;
}
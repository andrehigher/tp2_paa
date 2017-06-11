#include "../data_structure/base.h"

void bruto(int argc, char *argv[]){
    FILE *fp, *fpwrite;
    Graph *graph;

    if(argc < 3){
        printf("This program needs to receive the input and output.\n");
        return;
    }

    fp = fopen(argv[1], "r");
    fpwrite = fopen(argv[2], "w");

    if(!fp) {
        printf("%s doesn't exist.\n", argv[1]);
        return;
    }
    float maxBenefit = 0;
    graph = readNodes(fp);
    readEdgesBruto(graph, fp, fpwrite, &maxBenefit);
    fclose(fp);
    fclose(fpwrite);
}

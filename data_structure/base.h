#ifndef BASE__H_
#define BASE__H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "list.h"

#define FALSE 0
#define TRUE 1

void bruto(int argc, char *argv[]);
void dinamico(int argc, char *argv[]);
void guloso(int argc, char *argv[]);
Graph* readNodes(FILE *fp);
void readEdgesBruto(Graph *graph, FILE *fp, FILE *fpwrite, float *maxBenefit);
void printCombinationAux(int arr[], int n, int r, Graph *graph, int combination[][2], float *maxBenefit, int total, FILE *fpwrite);
void combinationUtil(int arr[], int data[], int start, int end, int index, int r, Graph *graph, int combination[][2], float *maxBenefit, int total, FILE *fpwrite);

void readEdgesGuloso(Graph *graph, FILE *fp, FILE *fpwrite, float *maxBenefit);

void readEdgesDynamic(Graph *graph, FILE *fp, FILE *fpwrite, float *maxBenefit);
void printCombinationDynamic(int arr[], int n, int r, Graph *graph, int combination[][2], float *maxBenefit, int total, FILE *fpwrite);
void combinationUtilDynamic(int arr[], int data[], int start, int end, int index, int r, Graph *graph, int combination[][2], float *maxBenefit, int total, FILE *fpwrite);

#endif /*BASE_H_*/
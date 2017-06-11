#include "../data_structure/base.h"

Graph* readNodes(FILE *fp){
    int travels;
    int i;
    int travelId, passenger, driver, amount, seats;
    float distance;

    fscanf(fp, "%d", &travels);
    fscanf(fp, "%d %d %d %d %d %f", &travelId, &passenger, &driver, &amount, &seats, &distance);
    Graph *head = createGraph(travelId, passenger, driver, amount, seats, distance);
        
    for (i=1; i<travels; i++) {
        fscanf(fp, "%d %d %d %d %d %f", &travelId, &passenger, &driver, &amount, &seats, &distance);
        addNode(head, travelId, passenger, driver, amount, seats, distance);
    }
    return head;
}

void readEdges(Graph *graph, FILE *fp, FILE *fpwrite, float *maxBenefit){
    int i, sharing;
    int source, destination;
    fscanf(fp, "%d", &sharing);
    int combination[sharing][2];
    int arr[sharing];
    for (i=0; i<sharing; i++) {
        arr[i] = i;
        fscanf(fp, "%d %d", &source, &destination);
        addEdge(graph, source, destination);
        combination[i][0] = source;
        combination[i][1] = destination;
    }

    int r;
    int n = sizeof(arr)/sizeof(arr[0]);
    for(r=1;r<=sharing; r++) {
        printCombinationAux(arr, n, r, graph, combination, maxBenefit, sharing, fpwrite);
    }
    if(*maxBenefit <= 0) {
        rewind(fpwrite);
        fprintf(fpwrite, "0 0.0\n");
    }
}

void printCombinationAux(int arr[], int n, int r, Graph *graph, int combination[][2], float *maxBenefit, int total, FILE *fpwrite) {
    // A temporary array to store all combination one by one
    int data[r];
 
    // Print all combination using temprary array 'data[]'
    combinationUtil(arr, data, 0, n-1, 0, r, graph, combination, maxBenefit, total, fpwrite);
}

void combinationUtil(int arr[], int data[], int start, int end, int index, int r, Graph *graph, int combination[][2], float *maxBenefit, int total, FILE *fpwrite) {
    // Current combination is ready to be printed, print it
    if (index == r) {
        float benefit = 0;
        int totalResults = 0, results[total], finalResults[total][2], l;
        for(int j=0; j<total; j++) {
            results[j] = -1;
            finalResults[j][0] = -1;
            finalResults[j][1] = -1;
        }
        resetAvaiableSeats(graph);
        for (int j=0; j<r; j++) {
            if(checkPassengerAvailability(graph, combination[data[j]][0]) == 1 && checkDriverAvailability(graph, combination[data[j]][1]) == 1 && checkIsDriving(graph, combination[data[j]][0]) == 0 && checkAvailability(graph, combination[data[j]][0]) == 1 && checkAvailability(graph, combination[data[j]][1]) == 1 && checkSeats(graph, combination[data[j]][0], combination[data[j]][1]) == 1) {
                setTravel(graph, combination[data[j]][0], combination[data[j]][1]);
                benefit += calculateBenefit(graph, combination[data[j]][0]);
            }
        }
        if(benefit > *maxBenefit) {
            l = 0;
            totalResults = 0;
            *maxBenefit = benefit;
            resetAvaiableSeats(graph);
            for (int j=0; j<r; j++) {
                if(checkPassengerAvailability(graph, combination[data[j]][0]) == 1 && checkDriverAvailability(graph, combination[data[j]][1]) == 1 && checkIsDriving(graph, combination[data[j]][0]) == 0  && checkAvailability(graph, combination[data[j]][0]) == 1 && checkAvailability(graph, combination[data[j]][1]) == 1 && checkSeats(graph, combination[data[j]][0], combination[data[j]][1]) == 1) {
                    setTravel(graph, combination[data[j]][0], combination[data[j]][1]);
                    benefit += calculateBenefit(graph, combination[data[j]][0]);
                    finalResults[l][0] = combination[data[j]][0];
                    finalResults[l][1] = combination[data[j]][1];
                    l++;
                    if(results[combination[data[j]][1]] == -1) {
                        totalResults++;
                        results[combination[data[j]][1]] = combination[data[j]][1];
                    }
                }
            }
            rewind(fpwrite);
            fprintf(fpwrite, "%d %.1f\n", totalResults, *maxBenefit);
            for (int j=0; j<total; j++) {
                if(results[j] >= 0) {
                    fprintf(fpwrite, "%d ", results[j]);
                    for(int i=0; i<total; i++) {
                        if(finalResults[i][0]>0 && finalResults[i][1] == results[j])
                            fprintf(fpwrite, "%d ", finalResults[i][0]);
                    }
                    fprintf(fpwrite, "\n");
                }
            }
        }
        return;
    }
 
    // replace index with all possible elements. The condition
    // "end-i+1 >= r-index" makes sure that including one element
    // at index will make a combination with remaining elements
    // at remaining positions
    for (int i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, data, i+1, end, index+1, r, graph, combination, maxBenefit, total, fpwrite);
    }
}
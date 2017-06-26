#include "../data_structure/base.h"

List* createList(int from, int to, float benefit) {
    return createElement(from, to, benefit);
}

List* createElement(int from, int to, float benefit) {
    List *list = (List *) malloc(sizeof(List));
    list->From = from;
    list->To = to;
    list->Benefit = benefit;
    list->ListAdj = NULL;
    list->End = NULL;
    list->Next = NULL;
    return list;
}

ListListAdj* createTravel(int from, int to, float benefit) {
    ListListAdj *list = (ListListAdj *) malloc(sizeof(ListListAdj));
    list->From = from;
    list->To = to;
    list->Benefit = benefit;
    list->Next = NULL;
    list->Prev = NULL;
    return list;
}

void addElement(List *list, int from, int to, float benefit) {
    List *aux = list;
    List *newElement = createElement(from, to, benefit);
	while ( aux->Next != NULL ) {
		aux = aux->Next;
	}
	aux->Next = newElement;
}

void addTravel(List *list, int from, int to, float benefit, int travels, int count, int maxTravels) {
    List *aux = list;
    ListListAdj *newTravel = createTravel(from, to, benefit), *auxList;
    int countTravel = 0, howMany = maxTravels/travels, inserted = 0;
    while(aux != NULL) {
        if(countTravel >= count && inserted < howMany) {
            newTravel->Next = aux->ListAdj;
            aux->ListAdj = newTravel;
            newTravel = createTravel(from, to, benefit);
            if(aux->ListAdj->Next != NULL) {
                aux->ListAdj->Next->Prev = aux->ListAdj;
            }
            inserted++;
        }
        auxList = aux->ListAdj;
        if(auxList != NULL) {
            while(auxList->Next != NULL) {
                auxList = auxList->Next;
            }
            aux->End = auxList;
        }
        aux = aux->Next;
        countTravel++;
    }
}

void addTravelCopy(List *list, int from, int to, float benefit) {
    List *aux = list;
    ListListAdj *newTravel = createTravel(from, to, benefit);
    while(aux != NULL) {
        newTravel->Next = aux->ListAdj;
        aux->ListAdj = newTravel;
        if(aux->ListAdj->Next != NULL) {
            aux->ListAdj->Next->Prev = aux->ListAdj;
        }
        aux = aux->Next;
    }
}

void printList(List *list) {
    float benefit;
    List *aux = list;
    ListListAdj *listAux;
    while(aux != NULL) {
        benefit = aux->Benefit;
        printf("%d %d", aux->From, aux->To);
        listAux = aux->ListAdj;
        while(listAux != NULL) {
            printf("->%d %d", listAux->From, listAux->To);
            benefit += listAux->Benefit;
            listAux = listAux->Next;
        }
        printf("\n");
        // printf("->NULL\tbenefit: %f\n", benefit);
        aux = aux->Next;
    }
}

void printListReverted(List *list) {
    float benefit;
    List *aux = list;
    ListListAdj *listAux;
    while(aux != NULL) {
        benefit = aux->Benefit;
        printf("%d %d", aux->From, aux->To);
        listAux = aux->End;
        while(listAux != NULL) {
            printf("->%d %d", listAux->From, listAux->To);
            benefit += listAux->Benefit;
            listAux = listAux->Prev;
        }
        printf("\n");
        // printf("->NULL\tbenefit: %f\n", benefit);
        aux = aux->Next;
    }
}

List* copyList(List *list, int times) {
    List *aux, *aux2 = list, *newElement;
    ListListAdj *listListAux;
    if(times == 1)
        return list;
    for(int i=1;i<times;i++) {
        aux = aux2;
        while(aux != NULL) {
            newElement = createElement(aux->From, aux->To, aux->Benefit);
            listListAux = aux->ListAdj;
            while(listListAux != NULL) {
                addTravelCopy(newElement, listListAux->From, listListAux->To, listListAux->Benefit);
                listListAux = listListAux->Next;
            }
            newElement->Next = list;
            aux = aux->Next;
            list = newElement;
        }
    }
    return list;
}

int returnTravels(List *list) {
    List *aux = list;
    int count = 0;
    while(aux != NULL) {
        count++;
        aux = aux->Next;
    }
    return count;
}

void checkRestrictions(List *list, Graph *graph, int total, FILE *fpwrite) {
    List *aux = list;
    ListListAdj *listListAux;
    Graph *graphAux;
    float benefit, maxBenefit = 0;
    int travels = 0, results[total], i, count = 0, check;
    while(aux != NULL) {
        resetAvaiableSeats(graph);
        graphAux = graph;
        benefit = 0;
        if(checkPassengerAvailability(graph, aux->From) == 1 && checkDriverAvailability(graph, aux->To) == 1 && checkIsDriving(graph, aux->From) == 0 && checkAvailability(graph, aux->From) == 1 && checkAvailability(graph, aux->From) == 1 && checkSeats(graph, aux->From, aux->To) == 1) {
            setTravel(graph, aux->From, aux->To);
            benefit += calculateBenefit(graph, aux->From);
        }
        listListAux = aux->End;
        while(listListAux != NULL) {
            if(checkPassengerAvailability(graph, listListAux->From) == 1 && checkDriverAvailability(graph, listListAux->To) == 1 && checkIsDriving(graph, listListAux->From) == 0 && checkAvailability(graph, listListAux->From) == 1 && checkAvailability(graph, listListAux->To) == 1 && checkSeats(graph, listListAux->From, listListAux->To) == 1) {
                setTravel(graph, listListAux->From, listListAux->To);
                benefit += calculateBenefit(graph, listListAux->From);
            }
            listListAux = listListAux->Prev;
        }
        if(benefit > maxBenefit) {
            travels = 0;
            count = 0;
            resetAvaiableSeats(graph);
            for(i=0; i<total; i++) {
                results[i] = -1;
            }
            graphAux = graph;
            if(checkPassengerAvailability(graph, aux->From) == 1 && checkDriverAvailability(graph, aux->To) == 1 && checkIsDriving(graph, aux->From) == 0 && checkAvailability(graph, aux->From) == 1 && checkAvailability(graph, aux->From) == 1 && checkSeats(graph, aux->From, aux->To) == 1) {
                setTravel(graph, aux->From, aux->To);
                results[count] = aux->To;
                count++;
                travels++;
            }
            listListAux = aux->End;
            while(listListAux != NULL) {
                if(checkPassengerAvailability(graph, listListAux->From) == 1 && checkDriverAvailability(graph, listListAux->To) == 1 && checkIsDriving(graph, listListAux->From) == 0 && checkAvailability(graph, listListAux->From) == 1 && checkAvailability(graph, listListAux->To) == 1 && checkSeats(graph, listListAux->From, listListAux->To) == 1) {
                    setTravel(graph, listListAux->From, listListAux->To);
                    check = 0;
                    for(i=0; i<count; i++) {
                        if(results[i] == listListAux->To) {
                            check = 1;
                        }
                    }
                    if(check == 0) {
                        results[count] = listListAux->To;
                        count++;
                    }
                    travels++;
                }
                listListAux = listListAux->Prev;
            }
            maxBenefit = benefit;
            rewind(fpwrite);
            fprintf(fpwrite, "%d %.1f\n", count, maxBenefit);
            resetAvaiableSeats(graph);
            graphAux = graph;
            for(i=0;i<count;i++) {
                fprintf(fpwrite, "%d ", results[i]);
                if(results[i] == aux->To) {
                    if(checkPassengerAvailability(graph, aux->From) == 1 && checkDriverAvailability(graph, aux->To) == 1 && checkIsDriving(graph, aux->From) == 0 && checkAvailability(graph, aux->From) == 1 && checkAvailability(graph, aux->From) == 1 && checkSeats(graph, aux->From, aux->To) == 1) {
                        setTravel(graph, aux->From, aux->To);
                        fprintf(fpwrite, "%d ", aux->From);
                    }
                }
                listListAux = aux->End;
                while(listListAux != NULL) {
                    if(results[i] == listListAux->To) {
                        if(checkPassengerAvailability(graph, listListAux->From) == 1 && checkDriverAvailability(graph, listListAux->To) == 1 && checkIsDriving(graph, listListAux->From) == 0 && checkAvailability(graph, listListAux->From) == 1 && checkAvailability(graph, listListAux->To) == 1 && checkSeats(graph, listListAux->From, listListAux->To) == 1) {
                            setTravel(graph, listListAux->From, listListAux->To);
                            fprintf(fpwrite, "%d ", listListAux->From);
                        }
                    }
                    listListAux = listListAux->Prev;
                }
                fprintf(fpwrite, "\n");
            }
        }
        aux = aux->Next;
    }
    if(travels == 0) {
        fprintf(fpwrite, "0 0.0");
    }
}
#include "../data_structure/base.h"

Graph *createGraph(int travelId, int passenger, int driver, int amount, int seats, float benefit) {
    return createNode(travelId, passenger, driver, amount, seats, benefit);
}
Graph* createNode(int travelId, int passenger, int driver, int amount, int seats, float benefit) {
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    graph->TravelId = travelId;
    graph->Passenger = passenger;
    graph->Driver = driver;
    graph->Amount = amount;
    graph->Seats = seats;
    graph->Benefit = benefit;
    graph->RemainingSeats = seats - amount;
    graph->Available = 1;
    graph->isDriving = 0;
    graph->benefitIncoming = 0;
    graph->ListAdj = NULL;
    graph->Next = NULL;
    return graph;
}

void addNode(Graph *graph, int travelId, int passenger, int driver, int amount, int seats, float benefit){
    Graph *aux = graph;
    Graph *newNode = createNode(travelId, passenger, driver, amount, seats, benefit);
	while ( aux->Next != NULL ) {
		aux = aux->Next;
	}
	aux->Next = newNode;
}

int returnAmountNodes(Graph *graph) {
    int count = 1;
    Graph *aux = graph;
    while ( aux->Next != NULL ) {
        count++;
		aux = aux->Next;
	}
    return count;
}

ListAdj* createEdge(int destination) {
    ListAdj *list = (ListAdj *) malloc(sizeof(ListAdj));
    list->TravelId = destination;
    list->Next = NULL;
    return list;
}

void addEdge(Graph *graph, int source, int destination) {
    Graph *aux = graph;
    while(aux != NULL && aux->TravelId != source) {
        aux = aux->Next;
    }
    if(aux == NULL || aux->TravelId != source) {
        return;
    }
    insertEdge(aux, destination);
    updateIncomingBenefit(graph, source, destination);
}

void updateIncomingBenefit(Graph *graph, int source, int destination) {
    Graph *aux = graph;
    while(aux != NULL && aux->TravelId != destination) {
        aux = aux->Next;
    }
    if(aux == NULL || aux->TravelId != destination) {
        return;
    }
    aux->benefitIncoming += calculateBenefit(graph, source);
}

Graph* returnGraphNode(Graph *graph, float limitBenefit) {
    Graph *aux = graph;
    float maxBenefitFound = 0;
    int source = -1;
    while(aux != NULL) {
        if(aux->benefitIncoming > maxBenefitFound && aux->benefitIncoming < limitBenefit) {
            maxBenefitFound = aux->benefitIncoming;
            source = aux->TravelId;
        }
        aux = aux->Next;
    }
    if(source == -1) {
        return NULL;
    } else {
        aux = graph;
        while(aux != NULL) {
            if(aux->TravelId == source) {
                return aux;
            }
            aux = aux->Next;
        }
    }
    return NULL;
}

void insertEdge(Graph *node, int destination){
    ListAdj *newEdge = createEdge(destination);
    newEdge->Next = node->ListAdj;
    node->ListAdj = newEdge;
}

void printGraph(Graph *graph) {
    Graph *aux = graph;
    ListAdj *listAux;
    while(aux != NULL) {
        printf("%d %d %d %d %d %f %d %.1f\n", aux->TravelId, aux->Passenger, aux->Driver, aux->Amount, aux->Seats, aux->Benefit, aux->RemainingSeats, aux->benefitIncoming);
        listAux = aux->ListAdj;
        printf("Edges:");
        while(listAux != NULL) {
            printf("%d->", listAux->TravelId);
            listAux = listAux->Next;
        }
        printf("NULL\n");
        aux = aux->Next;
    }
}

float calculateBenefit(Graph *graph, int source) {
    Graph *aux = graph;
    while(aux != NULL) {
        if(source == aux->TravelId){
            return aux->Benefit;
        }
        aux = aux->Next;
    }
    return 0;
}

void setTravel(Graph *graph, int source, int destination) {
    Graph *aux = graph;
    Graph *nodeSource = NULL, *nodeDestination = NULL;
    while(aux != NULL) {
        if(source == aux->TravelId){
            nodeSource = aux;
        }
        if(destination == aux->TravelId){
            nodeDestination = aux;
        }
        aux = aux->Next;
    }

    nodeDestination->RemainingSeats = nodeDestination->RemainingSeats - nodeSource->Amount;
    nodeSource->Available = 0;
    nodeDestination->isDriving = 1;
}

void resetAvaiableSeats(Graph *graph) {
    Graph *aux = graph;
    while(aux != NULL) {
        aux->RemainingSeats = aux->Seats - aux->Amount;
        aux->Available = 1;
        aux->isDriving = 0;
        aux = aux->Next;
    }
}

int checkPassengerAvailability(Graph *graph, int source) {
    Graph *aux = graph;
    while(aux != NULL) {
        if(aux->TravelId == source) {
            return aux->Passenger;
        }
        aux = aux->Next;
    }
    return 0;
}

int checkDriverAvailability(Graph *graph, int source) {
    Graph *aux = graph;
    while(aux != NULL) {
        if(aux->TravelId == source) {
            return aux->Driver;
        }
        aux = aux->Next;
    }
    return 0;
}

int checkAvailability(Graph *graph, int source) {
    Graph *aux = graph;
    while(aux != NULL) {
        if(aux->TravelId == source) {
            return aux->Available;
        }
        aux = aux->Next;
    }
    return 0;
}

int checkIsDriving(Graph *graph, int source) {
    Graph *aux = graph;
    while(aux != NULL) {
        if(aux->TravelId == source) {
            return aux->isDriving;
        }
        aux = aux->Next;
    }
    return 0;
}

int checkSeats(Graph *graph, int source, int destination) {
    Graph *aux = graph;
    Graph *nodeSource = NULL, *nodeDestination = NULL;
        
    while(aux != NULL) {
        if(source == aux->TravelId) {
            nodeSource = aux;
        }
        if(destination == aux->TravelId){
            nodeDestination = aux;
        }
        aux = aux->Next;
    }
    if(nodeDestination->RemainingSeats >= nodeSource->Amount) {
        return 1;
    }
    return 0;
}

void printNode(Graph *graph, int source) {
    Graph *aux = graph;
    while(aux != NULL) {
        if(aux->TravelId == source) {
            printf("%d %d %d %d %d %f %d %d %d\n", aux->TravelId, aux->Passenger, aux->Driver, aux->Amount, aux->Seats, aux->Benefit, aux->RemainingSeats, aux->Available, aux->isDriving);
            return;
        }
        aux = aux->Next;
    }
}
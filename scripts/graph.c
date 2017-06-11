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
        printf("Impossible to add an edge from %d to %d\n", source, destination);
        return;
    }
    insertEdge(aux, destination);
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
        printf("%d %d %d %d %d %f %d\n", aux->TravelId, aux->Passenger, aux->Driver, aux->Amount, aux->Seats, aux->Benefit, aux->RemainingSeats);
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
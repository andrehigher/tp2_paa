#ifndef GRAPH_H_
#define GRAPH_H_

typedef struct _ListAdj {
    int TravelId;
    struct _ListAdj *Next;
}ListAdj;

typedef struct _Graph {
    int TravelId;
    int Passenger;
    int Driver;
    int Amount;
    int Seats;
    float Benefit;
    int RemainingSeats;
    int Available;
    int isDriving;
    ListAdj *ListAdj;
    struct _Graph *Next;
}Graph;

Graph* createGraph(int travelId, int passenger, int driver, int amount, int seats, float benefit);
Graph* createNode(int travelId, int passenger, int driver, int amount, int seats, float benefit);
void addNode(Graph *graph, int travelId, int passenger, int driver, int amount, int seats, float benefit);
int returnAmountNodes(Graph *graph);

ListAdj* createEdge(int destination);
void addEdge(Graph *node, int source, int destination);
void insertEdge(Graph *node, int destination);

void printGraph(Graph *graph);
float calculateBenefit(Graph *graph, int source);
void setTravel(Graph *graph, int source, int destination);
void resetAvaiableSeats(Graph *graph);
int checkPassengerAvailability(Graph *graph, int source);
int checkDriverAvailability(Graph *graph, int source);
int checkAvailability(Graph *graph, int source);
int checkSeats(Graph *graph, int source, int destination);
int checkIsDriving(Graph *graph, int source);
void printNode(Graph *graph, int source);

#endif /*GRAPH_H_*/
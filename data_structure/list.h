#ifndef LIST_H_
#define LIST_H_

typedef struct _ListListAdj {
    int From;
    int To;
    float Benefit;
    struct _ListListAdj *Next;
    struct _ListListAdj *Prev;
}ListListAdj;

typedef struct _List {
    int From;
    int To;
    float Benefit;
    ListListAdj *ListAdj;
    ListListAdj *End;
    struct _List *Next;
}List;

List* createList(int from, int to, float benefit);
List* createElement(int from, int to, float benefit);
ListListAdj* createTravel(int from, int to, float benefit);
void addTravel(List *list, int from, int to, float benefit, int travels, int count, int maxTravels);
void addTravelCopy(List *list, int from, int to, float benefit);
void addElement(List *list, int from, int to, float benefit);
void printList(List *list);
void printListReverted(List *list);
List* copyList(List *list, int times);
int returnTravels(List *list);
void checkRestrictions(List *list, Graph *graph, int total, FILE *fpwrite);

#endif /*LIST_H_*/
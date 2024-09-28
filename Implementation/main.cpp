#include "graph.hpp"

#include <iostream>

using namespace std;

#define INF 0x3f3f3f3f

int main(int argc, char const *argv[]) {
    
    //le N
    int numVerts;
    cin >> numVerts; 
    //le M
    int numEdges;
    cin >> numEdges;

    Graph graph = Graph(numVerts);

    int origVert;
    int destinVert;
    int weight;
    
    //para cada aresta seguinte 
    //da linha de entrada
    for (int i = 0; i < numEdges; i++) {
        
        //le a aresta e seu peso
        cin >> origVert;
        cin >> destinVert;
        cin >> weight;

        //se a aresta tiver peso 
        //impar ela eh ignorada
        if (weight % 2 != 0) {
            continue;
        }
        
        //decresce os numeros dos vertices para 
        //que sejam de 0 a n-1 ao inves de 1 a N
        origVert--;
        destinVert--;
        
        //Adiciona aresta lida ao grafo
        graph.addNewEdge(origVert, destinVert, weight);
        
    }

    //encontra e printa distancia minima
    //ate o vertice N partindo do vertice 1
    cout << graph.dijkstra() << endl;
    
    return 0;
}
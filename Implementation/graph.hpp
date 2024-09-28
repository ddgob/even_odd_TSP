#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

using namespace std;

#define INF 0x3f3f3f3f

class Graph {
    
    private:
        
        //numero de vertices (N) antes da 
        //adicao de vertices da particao
        //impar (N) para biparticao
        int numVerts;


        //lista de adjascencia implementada por um vetor alocado
        //dinamicamente onde cada posicao do vetor aponta para   
        //um vector de pairs da forma (vertice, distancia)

        //OBS.: esse vetor possui 2N posicoes para armazenar os N   
        //vertices da particao par e os N vertices da particao impar
        //que juntos formam o grafo bipartido
        vector<pair<int, int>>* adjList;

    public:

        //constroi grafo com o 2 * numVerts_ posicoes
        //para armazenar os vertices da particao par
        //(N) e tambem os vertice da particao impar (N)
        Graph(int numVerts_);

        //adiciona uma aresta ao grafo indo e outra voltando 
        //(pq eh n direcionado) e tambem os vertices impares
        //indo e voltando para formar o grafo bipartido

        //alem de adicionar uma nova aresta de um vertice a outro 
        //na particao par, esse metodo tb adiciona a volta pois 
        //o grafo eh nao direcionado e tambem adiciona as arestas 
        //para os correspondentes da particao impar (ida e volta)
        void addNewEdge(int origVert, int destinVert, int weight);

        //percorre grafo bipartido e encontra distancia 
        //minima do vertice 1 ate N (ou, de 0 ate N-1 se 
        //considerarmos que decrescemos os indices em 1)
        int dijkstra();

        //desaloca vector de pares
        //(vertice, distancia)
        ~Graph();
};

#endif // GRAPH_HPP
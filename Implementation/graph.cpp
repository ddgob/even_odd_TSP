#include "graph.hpp"

#include <iostream>
#include <queue>

using namespace std;


struct biggerPair {

    //operador para fazer comparacoes entre as distancias de dois
    //pares (vertice, distancia) para determinar qual tera maior
    //prioridade na fila de prioridade
    int operator() (pair<int, int> origVert, pair<int, int> destinVert) {
        
        return origVert.second > destinVert.second;

    }

};

//constroi grafo
Graph::Graph(int numVerts_) {
    
    numVerts = numVerts_;

    //lista de adjascencia implementada por um vetor alocado
    //dinamicamente onde cada posicao do vetor aponta para   
    //um vector de pairs da forma (vertice, distancia)

    //OBS.: esse vetor possui 2N posicoes para armazenar os N   
    //vertices da particao par e os N vertices da particao impar
    //que juntos formam o grafo bipartido
    adjList = new vector<pair<int, int>>[2 * numVerts_];

}

//adiciona aresta nova no grafo
void Graph::addNewEdge(int vert1, int vert2, int weight){

    //adiciona aresta do vert1 da particao  
    //par para o vert2 da particao impar 
    //OBS.: vamos chamar essa aresta de P1
    adjList[vert1].push_back({vert2 + numVerts, weight});

    //adiciona aresta do vert2 da particao  
    //impar para o vert1 da particao par
    //OBS.: essa aresta eh a volta da aresta P1
    //garantindo que o grafo seja nao direcionado
    adjList[vert2 + numVerts].push_back({vert1, weight});

    //adiciona aresta do vert2 da particao
    //par para o vert1 da particao impar
    //OBS.: vamos chamar essa aresta de P2
    adjList[vert2].push_back({vert1 + numVerts, weight});

    //adiciona aresta do vert1 da particao  
    //impar para o vert2 da particao par
    //OBS.: essa aresta eh a volta da aresta P2
    //garantindo que o grafo seja nao direcionado
    adjList[vert1 + numVerts].push_back({vert2, weight});

}

//percorre grafo bipartido e encontra distancia 
//minima do vertice 1 ate N (ou, de 0 ate N-1 se 
//considerarmos que decrescemos os indices em 1)
int Graph::dijkstra(){
    
    //vetor de distancias minimas com 2N posicoes  
    //para armazenar vertices da particao par (N)   
    //e impar(N). Todas as distancias ainda sao  
    //desconhecidas logo sao inicializadas com INF. 
    vector<int> minDist(2 * numVerts, INF);

    //fila de prioridade que armazena vertices que
    //ainda precisam ser processados com vertices de 
    //menor distancia minima tendo maior prioridade
    priority_queue<pair<int, int>, vector<pair<int, int>>, biggerPair> priorityQ;

    //Adiciona vertice 1 a fila de prioridade
    //para iniciar o algoritmo de dijkstra
    //com source sendo o vertice 1
    priorityQ.push({0, 0});

    //Atribui distancia 0 ao
    //vertice source
    minDist[0] = 0;

    //enquanto todos os vertices ainda
    //nao tiverem sido processados
    while (!priorityQ.empty()){
        
        //Pega vertice de maior prioridade
        //ou seja menor distancia minima
        int currentVertID = priorityQ.top().first;

        //retira esse vertice da
        //fila de prioridade
        priorityQ.pop();

        //Retorna a distancia minima para o 
        //destino caso ja tenha encontrado
        if (currentVertID == numVerts - 1) {
            return minDist[numVerts - 1];
        }

        //para cada vizinho do vertice atual
        for (auto neighborVert : adjList[currentVertID]) {
            
            //armazena o numero do vizinho e o peso da
            //aresta ate ele partindo do vertice atual
            int neighborVertID = neighborVert.first;
            int neighborVertWeight = neighborVert.second;
            
            //Se a distancia minima atual desse vizinho for maior 
            //que a distancia minima atual do o vertice atual + 
            //o peso da aresta do vertice atual para esse vizinho: 
            if (minDist[neighborVertID] > minDist[currentVertID] + neighborVertWeight) {
                
                //Atualize a distancia minima (relaxamento)
                minDist[neighborVertID] = minDist[currentVertID] + neighborVertWeight;

                //Adicione o vertice vizinho na fila de 
                //prioridade para que ele possa ser 
                //processado com sua nova distancia minima
                priorityQ.push({neighborVertID, minDist[neighborVertID]});

            }

        }

    }
    
    //Caso nao seja possivel chegar ate o destino 
    //por vertices arestas pares e por um numero 
    //par de arestas, o programa retorna -1
    return -1;

}

//desaloca vetor de vector 
//de pares (vertice, distancia)
Graph::~Graph(){

    delete[] adjList;
    
}
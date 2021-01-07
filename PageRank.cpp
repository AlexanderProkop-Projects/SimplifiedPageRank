#include<iostream>
#include <vector>
#include<string>
#include <unordered_map>
#include <map>
#include<sstream>
#include <iomanip>
using namespace std;

struct Vertex {
    double outdegree;
    double pageRank;
    double sum;
    string name;
    int number;
    Vertex();
    Vertex(string name);
};
//base constructor
Vertex::Vertex() {
    this->name = "";
    outdegree = 0.0;
    pageRank = 0.0;
    sum = 0.0;
}
//constructor normally used
Vertex::Vertex(string name){
    this->name = name;
    outdegree = 0.0;
    pageRank = 0.0;
    sum = 0.0;
}
class AdjacencyList {
private:
    //Think about what member variables you need to initialize
    double numVertices;
    unordered_map<string, pair<Vertex, vector<Vertex>>> list;
public:
    //Think about what helper functions you will need in the algorithm
    AdjacencyList();
    void InsertEdge(string from, string to);
    void PageRank(int n);
    ~AdjacencyList();
};
//constructor
AdjacencyList::AdjacencyList() {
    numVertices = 0.0;
}
void AdjacencyList::InsertEdge(string from, string to) {
    //creates two Vertices, from and to
    Vertex fromVertex = Vertex(from);
    Vertex toVertex = Vertex(to);

    //if the from Vertex doesnt exist, make it
    if (list.find(from) == list.end()) {
        list[from].first = fromVertex;
        list[from].first.number = numVertices;
        numVertices += 1;
    }

    //if the to Vertex doesnt exist, make it
    if (list.find(to) == list.end()) {
        list[to].first = toVertex;
        list[to].first.number = numVertices;
        numVertices += 1;
    }

    //sets from to point to to
    list[from].second.push_back(toVertex);

    //increments the outdegree of the from Vertex
    list[from].first.outdegree = list[from].first.outdegree + 1.0;
}
void AdjacencyList::PageRank(int n) {
    //make variables
    vector<double> iteration;
    auto iter = list.begin();

    //makes the iteration matrix and the initializes pagerank for all Vertexs to 1.0 / numVertices;
    for (iter; iter != list.end(); iter++) {
        iteration.push_back(1.0 / numVertices);
        iter->second.first.pageRank = 1.0 / numVertices;
    }

    //calculate
    while(n > 1) {
        //for each Vertex calculate pagerank based on the Vertexs that point to it
        for (iter = list.begin(); iter != list.end(); iter++) {
            for (int j = 0; j < iter->second.second.size(); j++) {
                double insert = (1.0 / iter->second.first.outdegree) * (iteration.at(iter->second.first.number));
                list.find(iter->second.second.at(j).name)->second.first.sum += insert;
            }
        }

        //sets iteration matrix to be up to date with current power iteration of the pagerank calculation
        for (iter = list.begin(); iter != list.end(); iter++) {
            iter->second.first.pageRank = iter->second.first.sum;
            iteration.at(iter->second.first.number) = iter->second.first.pageRank;
            iter->second.first.sum = 0.0;
        }
        n--;
    }

    //sorts the unordered map
    map<string, pair<Vertex, vector<Vertex>>> sortList(list.begin(), list.end());

    //prints
    for (auto iter2 = sortList.begin(); iter2 != sortList.end(); iter2++) {
        cout << iter2->first << " " << fixed << setprecision(2) << iter2->second.first.pageRank << endl;
    }
}
//destructor, just in case
AdjacencyList::~AdjacencyList() {

}
int main(){
    int no_of_lines, power_iterations;
    string from, to;
    AdjacencyList list;

    cin >> no_of_lines;
    cin >> power_iterations;

    for (int i = 0; i < no_of_lines; i++){
        cin >> from;
        cin >> to;

        list.InsertEdge(from, to);
    }

    list.PageRank(power_iterations);
}
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// 1) Plecak - pojemność
// 2) Wejście - zbiór elementów
// 3) Wyjście - pozdbiór elementów wejściowych (którego suma wartości jest jak największa i mniejsza od pojemności plecaka)

struct element
{   
    int weight;
    int value;
};

int capacity;
vector<element> input, output;

vector<element> load_file(string file_name){
    vector<element> result = {};
    ifstream file(file_name);
    int w, v;

    while(file >> w >> v){
        result.push_back({w,v});
    }

    return result;
}

void print_input(vector<element> input){
    cout<<"Wczytany zbiór: {";
    for (element e : input){
        cout<<"{"<<e.weight<<","<<e.value<<"},";
    }
    cout<<"}"<<endl;
}

int main(int argc, char** argv){

    capacity = stoi(argv[2]);
    input = load_file(argv[1]);

    print_input(input);

    return 0;
}
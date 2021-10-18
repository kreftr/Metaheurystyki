#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;


struct element
{   
    int weight;
    int value;
};

struct input
{
    int capacity;
    vector<element> set;
};


vector<element> output;

vector<element> load_file(string file_name){
    vector<element> result = {};
    ifstream file(file_name);
    int w, v;

    while(file >> w >> v){
        result.push_back({w,v});
    }

    return result;
}

void print(input input){
    cout<<"Wczytany zbiór: {";
    for (element e : input.set){
        cout<<"{"<<e.weight<<","<<e.value<<"},";
    }
    cout<<"}   Wczytana pojemność: "<<input.capacity<<endl;
}

int main(int argc, char** argv){

    input in;
    
    in.set = load_file(argv[1]);
    in.capacity = stoi(argv[2]);

    print(in);

    return 0;
}
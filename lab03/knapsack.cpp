#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <algorithm>

using namespace std;


struct element
{   
    int weight;
    int value;
};

struct input_data
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


void generate_random_problem_to_file(string file_name, int problem_size, int random_range){
    ofstream myfile;
    int weight, value;
    myfile.open(file_name);
    for (int i=0; i < problem_size; i++){
        weight = rand() % random_range;
        value = rand() % random_range;
        myfile << weight;
        myfile << " ";
        myfile << value;
        myfile <<"\n";
    }
    myfile.close();
}


void print_input(input_data input){
    cout<<endl<<"Wczytany zbiór: {";
    for (element e : input.set){
        cout<<"{"<<e.weight<<","<<e.value<<"},";
    }
    cout<<"}"<<endl<<"Wczytana pojemność: "<<input.capacity<<endl<<endl;
}


int goal_fuction(vector<element> solution){
    int total_value = 0;
    for (element e : solution) total_value += e.value;
    return total_value;
}


int total_weight(vector<element> solution){
    int total_weight = 0;
    for (element e : solution) total_weight += e.weight;
    return total_weight;
}


void print_solution(vector<element> solution){
    cout<<"Rozwiązanie: {";
    for (element e : solution){
        cout<<"{"<<e.weight<<","<<e.value<<"},";
    }
    cout<<"}   Całkowita waga: "<<total_weight(solution)<<"   "<<"Całkowita wartość: "<<goal_fuction(solution)<<endl<<endl;
}


void print_combinations(vector<vector<element>> combinations){
    for (vector<element> combination: combinations){
        cout<<"{"<<endl;
        for(element e : combination){
            cout<<"{"<<e.weight<<","<<e.value<<"},";
        }
        cout<<"}"<<endl;
    }
    cout<<"Liczba kombinacji: "<<combinations.size()<<endl;
}


vector<element> generate_random_domain_point(input_data input, int mode){
    vector<element> input_set = input.set;
    vector<element> solution;
    int total_weight = 0;
    int index;
    
    switch (mode){
        case 1:
            while (!input_set.empty()){
                
                index = rand() % input_set.size();

                if (input_set[index].weight + total_weight <= input.capacity){
                    
                    total_weight += input_set[index].weight;
                    solution.push_back(input_set[index]);
                    swap(input_set[index], input_set.back());
                    input_set.pop_back();
                }
                else input_set.pop_back();
            }
            break;
        case 2:
            for (element e : input_set){
                if (total_weight + e.weight <= input.capacity){
                    total_weight += e.weight;
                    solution.push_back(e);
                }
            }
            break;
        case 3:
            sort(input_set.begin(), input_set.end(), [](element a, element b){return a.weight < b.weight;});
            for (element e : input_set){
                if (total_weight + e.weight <= input.capacity){
                    total_weight += e.weight;
                    solution.push_back(e);
                }
            }
            break;
        default:
            break;
    }
    return solution;
}


void combination_rec(int offset, int elements_number, vector<element> &elements_set, vector<element> &combination, vector<vector<element>> &combinations){
    if (elements_number == 0) {
        combinations.push_back(combination);
        return;
    }

    for (int i=offset; i <= elements_set.size() - elements_number; ++i) {
        combination.push_back(elements_set[i]);
        combination_rec(i+1, elements_number-1, elements_set, combination, combinations);
        combination.pop_back();
    }
}


vector<element> next_solution(input_data problem, vector<element> solution){
    vector<element> best_found = solution;
    vector<element> combination;
    vector<vector<element>> combinations;

    for (int i = 1; i <= problem.set.size(); i++) combination_rec(0, i, problem.set, combination, combinations);

    for (vector<element> c : combinations){
        if (goal_fuction(c) > goal_fuction(best_found) && total_weight(c) <= problem.capacity) best_found = c;
    }

    //print_combinations(combinations);

    return best_found;
}


int main(int argc, char** argv){

    input_data input;
    srand(time(NULL));
    input.set = load_file(argv[1]);
    input.capacity = stoi(argv[2]);

    print_input(input);

    //generate_random_problem_to_file("problem.txt", 25, 100);

    vector<element> random_s = generate_random_domain_point(input, 1);

    print_solution(random_s);

    vector<element> next_s = next_solution(input, random_s);

    print_solution(next_s);

    return 0;
}
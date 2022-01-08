#include <iostream>
#include <vector>
#include <string>
#include "genetic_algorithm.h"

using namespace std;


int main(int argc, char** argv){

    problem p = { 100, {{12,7}, {9,13}, {14,22}, {17,18}, {4,7}, {19, 9}, {14,22}, {11,9}, {21,18}, {7,4}, {3,19}, {1,2}} };
    
    int iterations = 10;
    int avg = 10;
    int st_dev = 10;

    function<chromosome(genotype&, vector<int>&)> selection;
    function<genotype(chromosome&, chromosome&, double)> crossover;
    function<bool(genotype&, int)> termination;


    auto iteration_condition = [&](genotype &g, int i){return iterations > i;};
    auto average_fitness_condition = [&](genotype &g, int i){return round(average_fitness(g, p)) < avg;};
    auto standard_deviation_condition = [&](genotype &g, int i){return round(standard_fitness_deviation(g,p)) > st_dev;}; 

    string selection_type = argv[1];
    string crossover_type = argv[2];
    double mutation_prob = stod(argv[3]);
    double crossover_prob = stod(argv[4]);
    string termination_type = argv[5];
    int termination_val = stoi(argv[6]);

    if (selection_type == "roulette") selection = roulette_selection;
    else selection = tournament_selection;

    if (crossover_type == "one_point") crossover = one_point_crossover;
    else crossover = two_point_crossover;

    if (termination_type == "iteration") {
        iterations = termination_val;
        termination = iteration_condition;
    }
    else if (termination_type == "average"){
        avg = termination_val;
        termination = average_fitness_condition;
    }
    else {
        st_dev = termination_val;
        termination = standard_deviation_condition;
    }

    chromosome c = genetic_algorithm(30, mutation_prob, crossover_prob, fitness_function, selection, crossover, mutation, termination, p);

    cout<<"BEST: "<<fitness_function(c, p)<<endl;
    print_genotype({c}, p);

    return 0;
}
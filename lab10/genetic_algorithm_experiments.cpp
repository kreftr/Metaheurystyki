#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "genetic_algorithm.h"

using namespace std;

int main(int argc, char** argv){

    problem p = { stoi(argv[1]), load_file(argv[2])};
    
    int iterations = 50;
    int avg = 10;
    int st_dev = 10;

    function<chromosome(genotype&, vector<int>&)> selection;
    function<genotype(chromosome&, chromosome&, double)> crossover;
    function<bool(genotype&, int)> termination;

    auto iteration_condition = [&](genotype &g, int i){return iterations > i;};
    auto average_fitness_condition = [&](genotype &g, int i){return round(average_fitness(g, p)) < avg;};
    auto standard_deviation_condition = [&](genotype &g, int i){return round(standard_fitness_deviation(g,p)) > st_dev;}; 


    ofstream myfile;
    termination=iteration_condition;
    chromosome c;

    string crossover_name = "one_point";
    string selection_name = "tournament";
    crossover = one_point_crossover;
    selection = tournament_selection;

    //Open file and write columns headers
    myfile.open("genetic_algorithm_experiments.txt");
    myfile << "corssover_type,selection_type,crossover_propability,mutation_propability,population_size,best_result \n"; 


    //ONE_POINT AND TOURNAMENT

    //Population size loop
    for (int population_size=5; population_size <= 20; population_size+=5){
        
        //Mutation propablity loop
        for (double mutation_propability=0.0; mutation_propability <= 1.0; mutation_propability+=0.1){

            //Crossover propablity loop
            for (double crossover_propability=0.0; crossover_propability <= 1.0; crossover_propability+=0.1){
                c = genetic_algorithm(30, mutation_propability, crossover_propability, fitness_function, selection, crossover, mutation, termination, p);
                myfile << crossover_name << "," << selection_name << "," << crossover_propability << "," << mutation_propability << "," << population_size << "," << fitness_function(c, p) << "\n";
            }

        }

    }


    //TWO_POINT AND TOURNAMENT
    crossover_name = "two_point";
    crossover = two_point_crossover;

    for (int population_size=5; population_size <= 20; population_size+=5){
        
        //Mutation propablity loop
        for (double mutation_propability=0.0; mutation_propability <= 1.0; mutation_propability+=0.1){

            //Crossover propablity loop
            for (double crossover_propability=0.0; crossover_propability <= 1.0; crossover_propability+=0.1){
                c = genetic_algorithm(30, mutation_propability, crossover_propability, fitness_function, selection, crossover, mutation, termination, p);
                myfile << crossover_name << "," << selection_name << "," << crossover_propability << "," << mutation_propability << "," << population_size << "," << fitness_function(c, p) << "\n";
            }

        }

    }


    //ONE_POINT AND ROULETTE
    crossover_name = "one_point";
    crossover = one_point_crossover;
    selection_name = "roulette";
    selection = roulette_selection;

    for (int population_size=5; population_size <= 20; population_size+=5){
        
        //Mutation propablity loop
        for (double mutation_propability=0.0; mutation_propability <= 1.0; mutation_propability+=0.1){

            //Crossover propablity loop
            for (double crossover_propability=0.0; crossover_propability <= 1.0; crossover_propability+=0.1){
                c = genetic_algorithm(30, mutation_propability, crossover_propability, fitness_function, selection, crossover, mutation, termination, p);
                myfile << crossover_name << "," << selection_name << "," << crossover_propability << "," << mutation_propability << "," << population_size << "," << fitness_function(c, p) << "\n";
            }

        }

    }


    //TWO_POINT AND ROULETTE
    crossover_name = "two_point";
    crossover = two_point_crossover;

    for (int population_size=5; population_size <= 20; population_size+=5){
        
        //Mutation propablity loop
        for (double mutation_propability=0.0; mutation_propability <= 1.0; mutation_propability+=0.1){

            //Crossover propablity loop
            for (double crossover_propability=0.0; crossover_propability <= 1.0; crossover_propability+=0.1){
                c = genetic_algorithm(30, mutation_propability, crossover_propability, fitness_function, selection, crossover, mutation, termination, p);
                myfile << crossover_name << "," << selection_name << "," << crossover_propability << "," << mutation_propability << "," << population_size << "," << fitness_function(c, p) << "\n";
            }

        }

    }

    myfile.close();

    return 0;
}
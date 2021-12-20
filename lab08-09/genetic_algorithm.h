#include <vector>
#include <algorithm>
#include <random>
#include <functional>
#include <iostream>
#include <numeric>
#include <cmath>
#include "knapsack_problem.h"


using namespace std;

using chromosome = vector<bool>;
using genotype = vector<chromosome>;

random_device rd;
mt19937 gen(rd());


void print_genotype(genotype g, problem &problem){
    cout<<"----------------"<<endl;
    for_each(g.begin(), g.end(), [&](auto c){for_each(c.begin(), c.end(), [](auto b){cout<<b;}); cout<<" "<<fitness_function(c, problem); cout<<endl;});
    cout<<"----------------"<<endl;
}


int fitness_function(chromosome chromosome, problem &problem){
    int total_weight=0, total_value=0;
    for(int i = 0; i < chromosome.size(); i++){
        if(chromosome.at(i)){
            if(total_weight + problem.elements.at(i).weight > problem.capacity) return 0;
            else {
                total_weight += problem.elements.at(i).weight;
                total_value += problem.elements.at(i).value;
            }
        }
    }
    return total_value;
}


double average_fitness(genotype &g, problem &p){
    int sum = 0;
    for_each(g.begin(), g.end(), [&](chromosome c){sum+=fitness_function(c, p);});
    return sum/(double)g.size();
}


double standard_fitness_deviation(genotype &g, problem &p){
    int sum = 0;
    int avg = average_fitness(g, p);
    for_each(g.begin(), g.end(), [&](chromosome c){sum+=pow((fitness_function(c,p)-avg), 2);});
    return sqrt(sum/(double)g.size());
}


chromosome roulette_selection(genotype &population, vector<int> &population_fitness){
    int fitness_sum = 0;
    for_each(population_fitness.begin(), population_fitness.end(), [&](auto x){fitness_sum+=x;});
    uniform_int_distribution<int> rand_range(0,100);
    
    while (true)
    {
        int i = 0;
        for(i; i < population.size(); i++){
            int r = rand_range(gen);
            if(round(population_fitness[i]/(double)fitness_sum*100) >= r){
                return population.at(i);
            } 
        }
    }
}


chromosome tournament_selection(genotype &population, vector<int> &population_fitness){
    int tournament_size = 2;
    uniform_int_distribution<int> range(0, population.size()-1);
    vector<int> tournament;
    for(int t = 0; t < tournament_size; t++){
        tournament.push_back(range(gen));
    } 
    sort(tournament.begin(), tournament.end(), [&](auto a, auto b){return population_fitness[a] > population_fitness[b];});
    return population[tournament[0]];
}


genotype one_point_crossover(chromosome &firs_parent, chromosome &second_parent, double crossover_propability){
    uniform_real_distribution<double> rand_range(0, 1);
    if (crossover_propability >= rand_range(gen)){
        uniform_int_distribution<int> crossover_point(0, firs_parent.size());
        auto first_child = firs_parent;
        auto second_child = second_parent; 
        for(int i = crossover_point(gen); i < first_child.size(); i++) swap(first_child[i], second_child[i]);
        return {first_child, second_child};
    }
    else return {firs_parent, second_parent};
}


genotype two_point_crossover(chromosome &firs_parent, chromosome &second_parent, double crossover_propability){
    uniform_real_distribution<double> rand_range(0, 1);
    if (crossover_propability >= rand_range(gen)){
        uniform_int_distribution<int> range(0, firs_parent.size() - 1);
        int crossover_point_1 = range(gen);
        int crossover_point_2 = range(gen);
        if(crossover_point_1 > crossover_point_2) swap(crossover_point_1, crossover_point_2);
        auto first_child = firs_parent;
        auto second_child = second_parent;
        for(int i = crossover_point_1; i < crossover_point_2; i++) swap(first_child[i], second_child[i]);
        return {first_child, second_child};
    }
    else return {firs_parent, second_parent};
}


chromosome mutation(chromosome chromosome, double mutation_prop){
    uniform_real_distribution<double> rand_range(0,1);
    if(mutation_prop >= rand_range(gen)){
        uniform_int_distribution<int> allel(0, chromosome.size()-1); 
        chromosome.at(allel(gen)) = !chromosome.at(allel(gen)); 
    }
    return chromosome;
}


chromosome genetic_algorithm(int population_size, double mutation_propability, double crossover_propability, function<int(chromosome, problem&)>fitness_f, function<chromosome(genotype&, vector<int>&)>selection_f, function<genotype(chromosome&, chromosome&, double)>crossover_f, function<chromosome(chromosome, double)>mutation_f, function<bool(genotype&, int)>termination_f, problem &problem){

    genotype population;
    genotype parents;
    genotype children;
    chromosome best(problem.elements.size(), 0);
    vector<int> population_fitness;
    

    //Generate population
    for(int i = 0; i < population_size; i++){
        
        chromosome random_chromosome(problem.elements.size(), 0);
        uniform_int_distribution<> genes_to_change(0, problem.elements.size());
         
        for(int j = 0; j < genes_to_change(gen); j++) random_chromosome.at(j) = true;
        
        shuffle(begin(random_chromosome), end(random_chromosome), gen);

        population.push_back(random_chromosome);
    }
    
    int i = 0;

    while(termination_f(population, i)){
        //Clear data
        parents.clear();
        children.clear();
        population_fitness.clear();
        
        cout<<"Iteration["<<i<<"]"<<endl;
        
        //Population fitness
        for(int j = 0; j < population.size(); j++){
            population_fitness.push_back(fitness_f(population.at(j), problem));
        }

        //Select best
        if(fitness_function(population[distance(population_fitness.begin(), max_element(population_fitness.begin(), population_fitness.end()))], problem) > fitness_function(best, problem)){
            best = population[distance(population_fitness.begin(), max_element(population_fitness.begin(), population_fitness.end()))];
        }

        //Selection
        for(int k = 0; k < population.size(); k++) parents.push_back(selection_f(population, population_fitness));

        int parents_idx = 1;

        //Crossover
        while((children.size() < population.size()) && (parents_idx < population.size())){
            for (auto e : crossover_f(parents.at(parents_idx), parents.at(parents_idx - 1), crossover_propability)) children.push_back(e);
            parents_idx += 2;
        }

        //Mutation
        for(auto child : children){
            child = mutation_f(child, mutation_propability);
        }

        print_genotype(population, problem);
        cout<<"[Population fitness]:"<<accumulate(population_fitness.begin(), population_fitness.end(), 0)<<"   [Average fitness]:"<<average_fitness(population, problem)<<"   [Standard deviation]:"<<standard_fitness_deviation(population, problem)<<endl<<"----------------"<<endl;
        population = children;
        i++;
    }

    return best;
}

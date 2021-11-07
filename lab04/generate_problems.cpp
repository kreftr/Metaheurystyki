#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;


void generate_random_problem(string file_name, int problem_size, int random_range){
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


int main(int argc, char** argv){

    srand(time(NULL));

    int size = stoi(argv[1]);

    for (int i = 1; i <= size; i++){
        generate_random_problem("problem_"+to_string(i)+".txt", i*5, 50);
    }

    return 0;
}
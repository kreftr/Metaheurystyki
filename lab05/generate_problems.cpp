#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;


void generate_random_problem(string file_name, int problem_size, int random_range){
    ofstream myfile;
    int weight, value;
    myfile.open(file_name);
    for (int i=0; i < problem_size; i++){
        weight = rand() % random_range + 1;
        value = rand() % random_range + 1;
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
    int range = stoi(argv[2]);
    string file_name = argv[3];

    generate_random_problem(file_name, size, range);
    
    return 0;
}
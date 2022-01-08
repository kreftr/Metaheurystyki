#include <string>
#include <fstream>
#include <random>

using namespace std;


int main(int argc, char** argv){

    random_device rd;
    mt19937 gen(rd());

    int size = stoi(argv[1]);
    int range = stoi(argv[2]);
    string file_name = argv[3];
    ofstream myfile;
    int weight, value;

    uniform_int_distribution<int> rand_range(1, range);

    myfile.open(file_name);

    for (int i=0; i < size; i++){
        weight = rand_range(gen);
        value = rand_range(gen);
        myfile << weight;
        myfile << " ";
        myfile << value;
        myfile <<"\n";
    }
    myfile.close();


    return 0;
}
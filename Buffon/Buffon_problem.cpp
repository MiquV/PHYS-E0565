#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include <fstream>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main() {

    int seed = time(0);         //adding randomness
    srand(seed);

    double l = 1.0;             //initializing the needle length and distance between lines
	double d = 2.0;  

    int sampleCount = 0;                  //initializing starting variables
    int repetitions = 0;
    //read variables from Starting_variables.txt
    std::ifstream infile("c:/Users/miksu/projects/week_1/output/Starting_variables.txt"); //must change path for different computers
    if (infile.is_open()) {
        std::string label;
        infile >> label >> sampleCount;
        infile >> label >> repetitions;
        infile.close();
    } else {
        std::cerr << "Error: Could not open Starting_variables.txt" << std::endl;
        return 1;
    }


    int crossings = 0;
    std::vector<double> pi_estimates(repetitions); 
	
    double xDist = 0;           //initializing sample variables
    double theta = 0;
    double reach = 0;

    double mean = 0;            //initializing analysis variables
    double stddev = 0;
    double runningTime = 0;
    double FOM = 0;

    clock_t tStart = clock();                   //starting time measurement

    for (int j = 0; j < repetitions; ++j) {
        for (int i = 0; i < sampleCount; ++i) {
            xDist = ((double) rand() / (RAND_MAX)) * d / 2.0;             // Distance from center of needle to nearest line
            theta = ((double) rand() / (RAND_MAX)) * M_PI / 2.0;          // Angle of needle
            reach = (l / 2.0) * std::cos(theta);                          // How far the needle reaches on the x-axis from its center
            if (xDist <= reach) {
                ++crossings;
            }
        }
        pi_estimates[j] = (2.0 * l * sampleCount) / (d * crossings);
        crossings = 0;
    }

    runningTime = (double)(clock() - tStart)/CLOCKS_PER_SEC;        //ending time measurement after simulating

    double sum = 0;

    for (int i = 0; i < repetitions; ++i) {
        sum += pi_estimates[i];
    }
    mean = sum / repetitions;

    double sq_sum = 0;

    for (int i = 0; i < repetitions; ++i) {
        sq_sum += (pi_estimates[i] - mean) * (pi_estimates[i] - mean);
    }
    stddev = std::sqrt(sq_sum / (repetitions * (repetitions - 1)));

    FOM = 1.0 / (stddev * stddev * runningTime);

	std::cout << "Buffon's Needle Simulation" << std::endl;
    std::cout << "Trials per repetition: " << sampleCount << std::endl;
    std::cout << "Repetitions: " << repetitions << std::endl;
    std::cout << "Mean estimate of pi: " << mean << std::endl;
    std::cout << "Standard deviation: " << stddev << std::endl;
    std::cout << "Total running time (s): " << runningTime << std::endl;
    std::cout << "Figure of Merit: " << FOM << std::endl;

	return 0;
}

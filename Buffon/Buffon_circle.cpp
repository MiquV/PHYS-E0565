#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include <fstream>

main () {

    int seed = time(0);                         //adding randomness
    srand(seed);
    
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

    int hitCount = 0;
    std::vector<double> pi_estimates(repetitions); //array to store pi estimates from each repetition

    double y = 0;                               //initializing sample variables
    double x = 0;

    double mean = 0;                            //initializing analysis variables
    double stddev = 0;
    double runningTime = 0;
    double FOM = 0;

    clock_t tStart = clock();                   //starting time measurement

    for (int j = 0; j < repetitions; j++) {
        for (int i = 0; i < sampleCount; i++) {      //looping through samples
            y = ((double) rand() / (RAND_MAX));      //generating new random point
            x = ((double) rand() / (RAND_MAX));
            if ((x*x + y*y) <= 1) {                  //checking if point is within the first top right quarter of an unit circle
                hitCount++;
            }
        }
        pi_estimates[j] = 4*(double)hitCount/(double)sampleCount; //calculating estimate of pi
        hitCount = 0;
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

    std::cout << "Buffon's Circle Simulation" << std::endl;
    std::cout << "Trials per repetition: " << sampleCount << std::endl;
    std::cout << "Repetitions: " << repetitions << std::endl;
    std::cout << "Mean estimate of pi: " << mean << std::endl;
    std::cout << "Standard deviation: " << stddev << std::endl;
    std::cout << "Total running time (s): " << runningTime << std::endl;
    std::cout << "Figure of Merit: " << FOM << std::endl;

    return 0;
}

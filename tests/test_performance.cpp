#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
#include <cmath>    
#include <numeric>  
#include <iomanip>  
#include "RedBlackTree.hpp" 

using namespace std;
using namespace std::chrono;

const int NUM_ITERATIONS = 100; 

// struct for mean and sigma
struct Stats {
    double mean;
    double sigma;
};

// Compute mean and standard deviation for a vector of doubles
Stats computeStats(const vector<double>& data) {
    if (data.empty()) return {0.0, 0.0};

    // 1. mean
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    double mean = sum / data.size();

    // 2. standard deviation
    double sq_sum = 0.0;
    for (double val : data) {
        sq_sum += (val - mean) * (val - mean);
    }
    // Use sample standard deviation (divide by N-1) to get an unbiased estimate for benchmarking
    double variance = (data.size() > 1) ? sq_sum / (data.size() - 1) : 0.0;
    
    return {mean, std::sqrt(variance)};
}

struct TestResult {
    double insertTimeMs;
    double deleteTimeMs;
};

// test insert and delete for a single N, returning the times in milliseconds
TestResult runSingleTest(int n) {
    RedBlackTree tree;
    vector<int> data(n);
    for(int i = 0; i < n; i++) data[i] = i;

    // Random engine 
    std::random_device rd;
    std::mt19937 g(rd());

    // --- INSERT ---
    shuffle(data.begin(), data.end(), g);
    auto start = high_resolution_clock::now();
    for(int val : data) tree.insert(val);
    auto stop = high_resolution_clock::now();
    double insertTime = duration<double, milli>(stop - start).count();

    // --- DELETE ---
    shuffle(data.begin(), data.end(), g);
    start = high_resolution_clock::now();
    for(int val : data) tree.remove(val); 
    stop = high_resolution_clock::now();
    double deleteTime = duration<double, milli>(stop - start).count();

    return {insertTime, deleteTime};
}

int main() {
    ofstream outFile("rbt_ratio_stats.csv");
    // CSV Header
    outFile << "N,RatioInsert_Mean,RatioInsert_Sigma,RatioDelete_Mean,RatioDelete_Sigma" << endl;

    vector<int> sizes = {100, 1000, 10000, 100000}; 

    cout << scientific << setprecision(3); 
    cout << "\n=================================================================================\n";
    cout << " ANALISI STABILITA' DEL RAPPORTO (RATIO)\n";
    cout << " Ratio = Time / (N * log2(N))\n";
    cout << " Sigma basso indica alta aderenza alla complessita' teorica.\n";
    cout << "=================================================================================\n";
    
    cout << left << setw(10) << "N" 
         << setw(25) << "Ratio Ins (Mean +/- Sig)" 
         << setw(25) << "Ratio Del (Mean +/- Sig)" << endl;
    cout << "---------------------------------------------------------------------------------\n";

    for(int n : sizes) {
        vector<double> ratiosInsert;
        vector<double> ratiosDelete;
        ratiosInsert.reserve(NUM_ITERATIONS);
        ratiosDelete.reserve(NUM_ITERATIONS);

        // Compute the theoretical value once per N
        double theoretical = n * log2(n);
        if (theoretical == 0) theoretical = 1; // Protection for N=1

        // --- BLOCK AVERAGE LOOP ---
        for(int i = 0; i < NUM_ITERATIONS; ++i) {
            TestResult res = runSingleTest(n);

            // Calculate ratios and store them for THIS specific iteration
            ratiosInsert.push_back(res.insertTimeMs / theoretical);
            ratiosDelete.push_back(res.deleteTimeMs / theoretical);
        }

        // Compute stats for insert and delete ratios
        Stats statsIns = computeStats(ratiosInsert);
        Stats statsDel = computeStats(ratiosDelete);

        // Output Console
        cout << left << setw(10) << n 
             << statsIns.mean << " +/- " << statsIns.sigma << "   "
             << statsDel.mean << " +/- " << statsDel.sigma << endl;

        // Output File
        outFile << n << "," 
                << statsIns.mean << "," << statsIns.sigma << "," 
                << statsDel.mean << "," << statsDel.sigma << endl;
    }

    cout << "=================================================================================\n";
    cout << "Dati salvati in 'rbt_ratio_stats.csv'" << endl;
    outFile.close();

    return 0;
}
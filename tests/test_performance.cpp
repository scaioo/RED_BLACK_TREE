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

// --- BLOCKING CONFIGURATION ---
// Total iterations = NUM_BLOCKS * BLOCK_SIZE
// We will calculate statistics based on the averages of these blocks.
const int NUM_BLOCKS = 1000; 
const int BLOCK_SIZE = 5;  

struct TestResult {
    double insertTimeMs;
    double deleteTimeMs;
};

// Test insert and delete for a single N
TestResult runSingleTest(int dato,RedBlackTree& tree) {
    // --- INSERT ---
    auto start = high_resolution_clock::now();
    tree.insert(dato); // Insert the first element to ensure the tree is not empty
    auto stop = high_resolution_clock::now();
    double insertTime = duration<double, milli>(stop - start).count();

    // --- DELETE ---
    start = high_resolution_clock::now();
    tree.remove(dato); // Remove the first element to ensure we are deleting from a non-empty tree
    stop = high_resolution_clock::now();
    double deleteTime = duration<double, milli>(stop - start).count();

    return {insertTime, deleteTime};
}

int main() {
    ofstream outFile("rbt_ratio_stats.csv");
    outFile << "N,RatioInsert_BlockMean,RatioInsert_BlockSigma,RatioDelete_BlockMean,RatioDelete_BlockSigma" << endl;

    vector<int> sizes = {100, 1000, 10000, 100000}; 

    cout << scientific << setprecision(3); 
    cout << "\n=================================================================================\n";
    cout << " STABILITY ANALISYS' (BLOCKING AVERAGE)\n";
    cout << " Blocks: " << NUM_BLOCKS << " | Block Size: " << BLOCK_SIZE << " | Total Iter: " << NUM_BLOCKS * BLOCK_SIZE << endl;
    cout << " Statistics are computed on the AVERAGES of each block.\n";
    cout << "=================================================================================\n";
    
    cout << left << setw(10) << "N" 
         << setw(28) << "Ratio Ins (BlkMean +/- Sig)" 
         << setw(28) << "Ratio Del (BlkMean +/- Sig)" << endl;
    cout << "---------------------------------------------------------------------------------\n";
    
    RedBlackTree tree;
    int previous_size = 0;
    for(int n : sizes) {
        // Grand accumulators (Sum of Block Means)
        double grandSumIns = 0.0;
        double grandSumSqIns = 0.0;
        
        double grandSumDel = 0.0;
        double grandSumSqDel = 0.0;

        vector<int> data(n-previous_size);
        previous_size = n;
        std::iota(data.begin(), data.end(), 0);
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(data.begin(), data.end(), g);
        // insert all the elements to have the right size of the tree for the insert/delete operations
        for (int val : data) {tree.insert(val);}       
        std::shuffle(data.begin(), data.end(), g);
        // Theoretical complexity for normalization
        double theoretical =  log2(n);
        if (theoretical == 0) theoretical = 1; 

        // --- OUTER LOOP: Iterate over Blocks ---
        for(int b = 0; b < NUM_BLOCKS; ++b) {
            
            // Local accumulators for the current block
            double blockSumIns = 0.0;
            double blockSumDel = 0.0;

            // --- INNER LOOP: Fill the Block ---
            for(int k = 0; k < BLOCK_SIZE; ++k) {
                std::shuffle(data.begin(), data.end(), g);
                TestResult res = runSingleTest(data[0],tree);
                
                // Accumulate normalized ratios
                blockSumIns += (res.insertTimeMs / theoretical);
                blockSumDel += (res.deleteTimeMs / theoretical);
            }

            // 1. Compute Average for this Block
            double blockMeanIns = blockSumIns / BLOCK_SIZE;
            double blockMeanDel = blockSumDel / BLOCK_SIZE;

            // 2. Accumulate this Block Mean into Grand Stats
            grandSumIns += blockMeanIns;
            grandSumSqIns += (blockMeanIns * blockMeanIns);

            grandSumDel += blockMeanDel;
            grandSumSqDel += (blockMeanDel * blockMeanDel);
        }

        // --- FINAL STATISTICS (Across Blocks) ---
        
        // Mean of Block Means
        double finalMeanIns = grandSumIns / NUM_BLOCKS;
        double finalMeanDel = grandSumDel / NUM_BLOCKS;

        // Variance of Block Means
        double varIns = 0.0;
        double varDel = 0.0;

        if (NUM_BLOCKS > 1) {
            varIns = (grandSumSqIns - (grandSumIns * grandSumIns) / NUM_BLOCKS) / (NUM_BLOCKS - 1);
            varDel = (grandSumSqDel - (grandSumDel * grandSumDel) / NUM_BLOCKS) / (NUM_BLOCKS - 1);
        }

        // Sigma (Standard Error of the blocks)
        double sigmaIns = sqrt(max(0.0, varIns));
        double sigmaDel = sqrt(max(0.0, varDel));

        // Output Console
        cout << left << setw(10) << n 
             << finalMeanIns << " +/- " << sigmaIns << "      "
             << finalMeanDel << " +/- " << sigmaDel << endl;

        // Output File
        outFile << n << "," 
                << finalMeanIns << "," << sigmaIns << "," 
                << finalMeanDel << "," << sigmaDel << endl;
    }

    cout << "=================================================================================\n";
    cout << "Data saved in 'rbt_ratio_stats.csv'" << endl;
    outFile.close();

    return 0;
}
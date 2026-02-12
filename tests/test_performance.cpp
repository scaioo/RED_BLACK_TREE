#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
#include <cmath>    // Per log2, sqrt
#include <numeric>  // Per accumulate
#include <iomanip>  // Per formattazione
#include "RedBlackTree.hpp" 

using namespace std;
using namespace std::chrono;

const int NUM_ITERATIONS = 100; // Quante volte ripetiamo il test per ogni N

// Struttura per contenere Media e Deviazione Standard
struct Stats {
    double mean;
    double sigma;
};

// Funzione generica per calcolare Media e Sigma di un vettore di double
Stats computeStats(const vector<double>& data) {
    if (data.empty()) return {0.0, 0.0};

    // 1. Media
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    double mean = sum / data.size();

    // 2. Deviazione Standard
    double sq_sum = 0.0;
    for (double val : data) {
        sq_sum += (val - mean) * (val - mean);
    }
    // N-1 per la deviazione standard campionaria (più corretta per benchmark)
    double variance = (data.size() > 1) ? sq_sum / (data.size() - 1) : 0.0;
    
    return {mean, std::sqrt(variance)};
}

struct TestResult {
    double insertTimeMs;
    double deleteTimeMs;
};

// Esegue una singola prova (Insert + Delete)
TestResult runSingleTest(int n) {
    RedBlackTree tree;
    vector<int> data(n);
    for(int i = 0; i < n; i++) data[i] = i;

    // Random engine fresco per ogni iterazione
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
    for(int val : data) tree.remove(val); // Assumi remove() o deleteNode()
    stop = high_resolution_clock::now();
    double deleteTime = duration<double, milli>(stop - start).count();

    return {insertTime, deleteTime};
}

int main() {
    ofstream outFile("rbt_ratio_stats.csv");
    // CSV Header: Salviamo Media e Sigma dei RATIO
    outFile << "N,RatioInsert_Mean,RatioInsert_Sigma,RatioDelete_Mean,RatioDelete_Sigma" << endl;

    vector<int> sizes = {100, 1000, 10000, 100000, 1000000}; 

    cout << scientific << setprecision(3); // Notazione scientifica utile per ratio piccoli
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

        // Calcolo il valore teorico una volta sola per questo N
        double theoretical = n * log2(n);
        if (theoretical == 0) theoretical = 1; // Protezione per N=1

        // --- BLOCK AVERAGE LOOP ---
        for(int i = 0; i < NUM_ITERATIONS; ++i) {
            TestResult res = runSingleTest(n);

            // Calcolo i ratio per QUESTA specifica iterazione e li salvo
            ratiosInsert.push_back(res.insertTimeMs / theoretical);
            ratiosDelete.push_back(res.deleteTimeMs / theoretical);
        }

        // Calcolo statistiche sui vettori dei RATIO
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
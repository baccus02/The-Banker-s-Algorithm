#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Function to check if the system is in a safe state
bool isSafeState(vector<vector<int> >& allocation, vector<vector<int> >& max, vector<int>& available, vector<int>& safeSequence) {
    int numProcesses = allocation.size();
    int numResources = available.size();
    vector<int> work = available;
    vector<bool> finish(numProcesses, false);

    int count = 0;
    while (count < numProcesses) {
        bool found = false;
        for (int p = 0; p < numProcesses; ++p) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < numResources; ++j) {
                    if (max[p][j] - allocation[p][j] > work[j]) {
                        break;
                    }
                }
                if (j == numResources) {
                    for (int k = 0; k < numResources; ++k) {
                        work[k] += allocation[p][k];
                    }
                    safeSequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            return false; // No safe sequence found
        }
    }
    return true; // Safe sequence found
}

int main() {
    ifstream inputFile("input.txt");
    int numProcesses, numResources;

    // Read number of processes and resources from the file
    inputFile >> numProcesses >> numResources;

    // Initialize data structures
    vector<vector<int> > allocation(numProcesses, vector<int>(numResources));
    vector<vector<int> > max(numProcesses, vector<int>(numResources));
    vector<int> available(numResources);
    vector<int> safeSequence(numProcesses);

    // Read allocation matrix
    for (int i = 0; i < numProcesses; ++i) {
        for (int j = 0; j < numResources; ++j) {
            inputFile >> allocation[i][j];
        }
    }

    // Read maximum demand matrix
    for (int i = 0; i < numProcesses; ++i) {
        for (int j = 0; j < numResources; ++j) {
            inputFile >> max[i][j];
        }
    }

    // Read available resources
    for (int i = 0; i < numResources; ++i) {
        inputFile >> available[i];
    }

    inputFile.close();

    // Check for safe state
    if (isSafeState(allocation, max, available, safeSequence)) {
        cout << "The system is in a safe state.\nSafe sequence: ";
        for (int i = 0; i < numProcesses; ++i) {
            cout << "P" << safeSequence[i];
            if (i < numProcesses - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    } else {
        cout << "The system is not in a safe state." << endl;
    }

    return 0;
}

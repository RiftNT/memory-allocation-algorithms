#include <iostream>
#include <iomanip>
#include <vector>
#include <limits.h>

using namespace std;

struct MemoryBlock {
    int size;
    int process; // -1 if unallocated
};

const int UNALLOCATED = -1;

void getInput(vector<MemoryBlock>& memory, vector<int>& processes);
void runMemoryAllocationAlgorithms(vector<MemoryBlock>& memory, vector<int>& processes);
void printMemoryAndProcesses(const vector<MemoryBlock>& memory, const vector<int>& processes);
void printMemoryStatus(const vector<MemoryBlock>& memory);
void firstFit(vector<MemoryBlock>& memory, vector<int>& processes);
void bestFit(vector<MemoryBlock>& memory, vector<int>& processes);
void worstFit(vector<MemoryBlock>& memory, vector<int>& processes);
void nextFit(vector<MemoryBlock>& memory, vector<int>& processes);

int main() 
{
    while(true) {
        vector<MemoryBlock> memory;
        vector<int> processes;

        getInput(memory, processes);

        runMemoryAllocationAlgorithms(memory, processes);

        system("pause");
        system("cls");
    }

    return 0;
}

void getInput(vector<MemoryBlock>& memory, vector<int>& processes) 
{
    int memorySize, processCount;

    cout << "Enter the number of memory blocks: ";
    cin >> memorySize;

    memory.resize(memorySize);

    cout << "Enter the memory block sizes:" << endl;
    for(int p = 0; p < memorySize; p++) {
        cout << "Block " << p + 1 << ": ";
        cin >> memory[p].size;
        memory[p].process = UNALLOCATED;
    }

    cout << "Enter the number of processes: ";
    cin >> processCount;

    processes.resize(processCount, 0); // Initialize processes to 0

    cout << "Enter the process sizes:" << endl;
    for(int p = 0; p < processCount; p++) {
        cout << "Process " << p + 1 << ": ";
        cin >> processes[p];
    }
}

void runMemoryAllocationAlgorithms(vector<MemoryBlock>& memory, vector<int>& processes) 
{
    printMemoryAndProcesses(memory, processes);

    vector<MemoryBlock> initialMemory = memory;

    cout << "First Fit Algorithm:" << endl;
    firstFit(memory, processes);
    cout << "\nMemory Status after First Fit Algorithm:" << endl;
    printMemoryStatus(memory);
    cout << endl << "-----------------------------------" << endl;

    // Reset memory
    memory = initialMemory;

    cout << "Best Fit Algorithm:" << endl;
    bestFit(memory, processes);
    cout << "\nMemory Status after Best Fit Algorithm:" << endl;
    printMemoryStatus(memory);
    cout << endl << "-----------------------------------" << endl;

    // Reset memory
    memory = initialMemory;

    cout << "Worst Fit Algorithm:" << endl;
    worstFit(memory, processes);
    cout << "\nMemory Status after Worst Fit Algorithm:" << endl;
    printMemoryStatus(memory);
    cout << endl << "-----------------------------------" << endl;

    // Reset memory
    memory = initialMemory;

    cout << "Next Fit Algorithm:" << endl;
    nextFit(memory, processes);
    cout << "\nMemory Status after Next Fit Algorithm:" << endl;
    printMemoryStatus(memory);
    cout << endl << "-----------------------------------" << endl;
}

void printMemoryAndProcesses(const vector<MemoryBlock>& memory, const vector<int>& processes) 
{
    cout << setw(15) << "Memory Block" << setw(15) << "Processes" << endl;
    
    for(unsigned p = 0; p < max(memory.size(), processes.size()); p++) {
        cout << setw(13);
        if(p < memory.size()) {
            cout << memory[p].size << "KB";
        }

        cout << setw(13);

        if(p < processes.size()) {
            cout << processes[p] << "KB";
        }

        cout << endl;
    }
    cout << endl;
}

void printMemoryStatus(const vector<MemoryBlock>& memory) 
{
    for(unsigned p = 0; p < memory.size(); p++) {
        if(memory[p].process != UNALLOCATED) {
            cout << "[" << memory[p].process << "] ";
        } else {
            cout << "[ ] ";
        }
    }
    cout << endl;
}

// First Fit Algorithm:
// Iterate through each process and find the first memory block that can accommodate it.
// Allocate the process to the first fitting block, or indicate if allocation is not possible.
void firstFit(vector<MemoryBlock>& memory, vector<int>& processes) 
{
    for(int p : processes) {
        int firstFitIndex = -1;

        // Iterate through each memory block
        for(unsigned q = 0; q < memory.size(); ++q) {
            // Check if the block has sufficient size and is unallocated
            if(memory[q].size >= p && memory[q].process == UNALLOCATED) {
                firstFitIndex = q;
                break;
            }
        }

        // Allocate the process to the first fitting block, or indicate if allocation is not possible
        if(firstFitIndex != -1) {
            memory[firstFitIndex].process = p;
            cout << "Allocated process " << p << " in block " << firstFitIndex + 1 << endl;
        } else {
            cout << p << " cannot be allocated." << endl;
        }
    }
}

// Best Fit Algorithm:
// Iterate through each process and find the memory block with the smallest size that can accommodate it.
// Allocate the process to the best fitting block, or indicate if allocation is not possible.
void bestFit(vector<MemoryBlock>& memory, vector<int>& processes) 
{
    for(int p : processes) {
        int bestFitIndex = -1;
        int bestFitSize = INT_MAX;

        // Iterate through each memory block
        for(unsigned q = 0; q < memory.size(); q++) {
            // Check if the block has sufficient size, is unallocated, and has the smallest size
            if(memory[q].size >= p && memory[q].size < bestFitSize && memory[q].process == UNALLOCATED) {
                bestFitIndex = q;
                bestFitSize = memory[q].size;
            }
        }

        // Allocate the process to the best fitting block, or indicate if allocation is not possible
        if(bestFitIndex != -1) {
            memory[bestFitIndex].process = p; // Mark the block as used
            cout << "Allocated process " << p << " in block " << bestFitIndex + 1 << endl;
        } else {
            cout << p << " cannot be allocated." << endl;
        }
    }
}

// Worst Fit Algorithm:
// Iterate through each process and find the memory block with the largest size that can accommodate it.
// Allocate the process to the worst fitting block, or indicate if allocation is not possible.
void worstFit(vector<MemoryBlock>& memory, vector<int>& processes) 
{
    for(int p : processes) {
        int worstFitIndex = -1;
        int worstFitSize = -1;

        // Iterate through each memory block
        for(unsigned q = 0; q < memory.size(); q++) {
            // Check if the block has sufficient size, is unallocated, and has the largest size
            if(memory[q].size >= p && (worstFitIndex == -1 || memory[q].size > worstFitSize) && memory[q].process == UNALLOCATED) {
                worstFitIndex = q;
                worstFitSize = memory[q].size;
            }
        }

        // Allocate the process to the worst fitting block, or indicate if allocation is not possible
        if(worstFitIndex != -1) {
            memory[worstFitIndex].process = p; // Mark the block as used
            cout << "Allocated process " << p << " in block " << worstFitIndex + 1 << endl;
        } else {
            cout << p << " cannot be allocated." << endl;
        }
    }
}

// Next Fit Algorithm:
// Iterate through each process and find the next memory block that can accommodate it.
// Allocate the process to the next fitting block, or indicate if allocation is not possible.
void nextFit(vector<MemoryBlock>& memory, vector<int>& processes) 
{
    int lastIndex = 0;

    for(int p : processes) {
        int q = lastIndex;

        // Iterate through memory blocks in a circular manner starting from the last allocated block
        do {
            // Check if the block has sufficient size and is unallocated
            if(memory[q].size >= p && memory[q].process == UNALLOCATED) {
                memory[q].process = p; // Mark the block as used
                cout << "Allocated process " << p << " in block " << q + 1 << endl;
                lastIndex = (q + 1) % memory.size();
                break;
            }

            q = (q + 1) % memory.size();
        } while (q != lastIndex);

        // Indicate if allocation is not possible
        if(q == lastIndex) {
            cout << p << " cannot be allocated." << endl;
        }
    }
}
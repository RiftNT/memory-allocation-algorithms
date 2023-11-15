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

void getInput(vector<MemoryBlock>& memory, vector<int>& processes, vector<int>& internalFragmentation);
void runMemoryAllocationAlgorithms(vector<MemoryBlock>& memory, vector<int>& processes, vector<int>& internalFragmentation);

void printMemoryAndProcesses(const vector<MemoryBlock>& memory, const vector<int>& processes);
void printMemoryStatus(const vector<MemoryBlock>& memory);
void printMemoryTable(const vector<MemoryBlock>& memory, const vector<int>& processes, const vector<int>& internalFragmentation);
void firstFit(vector<MemoryBlock>& memory, vector<int>& processes, vector<int>& internalFragmentation);
void bestFit(vector<MemoryBlock>& memory, vector<int>& processes, vector<int>& internalFragmentation);
void worstFit(vector<MemoryBlock>& memory, vector<int>& processes, vector<int>& internalFragmentation);
void nextFit(vector<MemoryBlock>& memory, vector<int>& processes, vector<int>& internalFragmentation);

int main()
{
    while(true) {
        vector<MemoryBlock> memory;
        vector<int> processes;
        vector<int> internalFragmentation;

        getInput(memory, processes, internalFragmentation);

        runMemoryAllocationAlgorithms(memory, processes, internalFragmentation);

        system("pause");
        system("cls");
    }

    return 0;
}

void getInput(vector<MemoryBlock>& memory, vector<int>& processes, vector<int>& internalFragmentation)
{
    int memorySize, processCount;

    cout << "Enter the number of memory blocks: ";
    cin >> memorySize;

    memory.resize(memorySize);
    internalFragmentation.resize(memorySize, 0);  // Initialize internalFragmentation to 0

    cout << "Enter the memory block sizes:" << endl;
    for(int p = 0; p < memorySize; p++) {
        cout << "Block " << p + 1 << ": ";
        cin >> memory[p].size;
        memory[p].process = UNALLOCATED;
    }

    cout << "Enter the number of processes: ";
    cin >> processCount;

    processes.resize(processCount, 0);  // Initialize processes to 0

    cout << "Enter the process sizes:" << endl;
    for(int p = 0; p < processCount; p++) {
        cout << "Process " << p + 1 << ": ";
        cin >> processes[p];
    }
}


void runMemoryAllocationAlgorithms(vector<MemoryBlock>& memory, vector<int>& processes, vector<int>& internalFragmentation)
{
    vector<MemoryBlock> initialMemory = memory;

    printMemoryAndProcesses(memory, processes);

    cout << "First Fit Algorithm:" << endl;
    firstFit(memory, processes, internalFragmentation);
    cout << "\nMemory Status after First Fit Algorithm:" << endl;
    printMemoryStatus(memory);
    cout << endl << "-----------------------------------" << endl;
    printMemoryTable(memory, processes, internalFragmentation);

    // Reset memory
    memory = initialMemory;

    internalFragmentation.clear();
    internalFragmentation.resize(memory.size(), 0);

    cout << "Best Fit Algorithm:" << endl;
    bestFit(memory, processes, internalFragmentation);
    cout << "\nMemory Status after Best Fit Algorithm:" << endl;
    printMemoryStatus(memory);
    cout << endl << "-----------------------------------" << endl;
    printMemoryTable(memory, processes, internalFragmentation);

    // Reset memory
    memory = initialMemory;

    internalFragmentation.clear();
    internalFragmentation.resize(memory.size(), 0);

    cout << "Worst Fit Algorithm:" << endl;
    worstFit(memory, processes, internalFragmentation);
    cout << "\nMemory Status after Worst Fit Algorithm:" << endl;
    printMemoryStatus(memory);
    cout << endl << "-----------------------------------" << endl;
    printMemoryTable(memory, processes, internalFragmentation);

    // Reset memory
    memory = initialMemory;

    internalFragmentation.clear();
    internalFragmentation.resize(memory.size(), 0);

    cout << "Next Fit Algorithm:" << endl;
    nextFit(memory, processes, internalFragmentation);
    cout << "\nMemory Status after Next Fit Algorithm:" << endl;
    printMemoryStatus(memory);
    cout << endl << "-----------------------------------" << endl;
    printMemoryTable(memory, processes, internalFragmentation);
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
        if (memory[p].process != UNALLOCATED) {
            cout << "[" << memory[p].process << "] ";
        } else {
            cout << "[ ] ";
        }
    }
    cout << endl;
}

void printMemoryTable(const vector<MemoryBlock>& memory, const vector<int>& processes, const vector<int>& internalFragmentation)
{
    cout << setw(15) << "Memory Block" << setw(15) << "Status" << setw(30) << "Internal Fragmentation" << endl;

    for(unsigned p = 0; p < max(memory.size(), processes.size()); p++) {
        cout << setw(15);

        if(p < memory.size()) {
            cout << memory[p].size << "KB";
        }

        cout << setw(15);

        if(p < memory.size()) {
            if (p < processes.size() && memory[p].process != UNALLOCATED) {
                cout << "Allocated";
            } else {
                cout << "Unallocated";
            }
        }

        cout << setw(25);

        if(p < internalFragmentation.size()) {
            cout << internalFragmentation[p] << "KB";
        }

        cout << endl;
    }

    cout << endl;
}



void firstFit(vector<MemoryBlock>& memory, vector<int>& processes, vector<int>& internalFragmentation)
{
    for (unsigned p = 0; p < processes.size(); p++) {
        int index = -1;

        // Iterate through each memory block
        for(unsigned q = 0; q < memory.size(); q++) {
            // Check if the block has sufficient size and is unallocated
            if (memory[q].size >= processes[p] && memory[q].process == UNALLOCATED) {
                index = q;
                break;
            }
        }

        // Allocate the process to the first fitting block, or indicate if allocation is not possible
        if(index != -1) {
            memory[index].process = processes[p];
            internalFragmentation[index] = memory[index].size - processes[p];
            cout << "Allocated process " << processes[p] << " in block " << index + 1 << endl;
        } else {
            cout << processes[p] << " cannot be allocated." << endl;
        }
    }
}

void bestFit(vector<MemoryBlock>& memory, vector<int>& processes, vector<int>& internalFragmentation)
{
    for(unsigned p = 0; p < processes.size(); p++) {
        int index = -1;
        int bestFitSize = INT_MAX;

        // Iterate through each memory block
        for(unsigned q = 0; q < memory.size(); q++) {
            // Check if the block has sufficient size, is unallocated, and has the smallest size
            if (memory[q].size >= processes[p] && memory[q].size - processes[p] < bestFitSize && memory[q].process == UNALLOCATED) {
                index = p;
                bestFitSize = memory[q].size - processes[p];
            }
        }

        // Allocate the process to the best fitting block, or indicate if allocation is not possible
        if(index != -1) {
            memory[index].process = processes[p]; // Mark the block as used
            internalFragmentation[index] = memory[index].size - processes[p];
            cout << "Allocated process " << processes[p] << " in block " << index + 1 << endl;
        } else {
            cout << processes[p] << " cannot be allocated." << endl;
        }
    }
}

void worstFit(vector<MemoryBlock>& memory, vector<int>& processes, vector<int>& internalFragmentation)
{
    for(unsigned p = 0; p < processes.size(); p++) {
        int index = -1;
        int worstFitSize = -1;

        // Iterate through each memory block
        for(unsigned q = 0; q < memory.size(); q++) {
            // Check if the block has sufficient size, is unallocated, and has the largest size
            if(memory[q].size >= processes[p] && (index == -1 || memory[q].size - processes[p] > worstFitSize) && memory[q].process == UNALLOCATED) {
                index = q;
                worstFitSize = memory[q].size - processes[p];
            }
        }

        // Allocate the process to the worst fitting block, or indicate if allocation is not possible
        if(index != -1) {
            memory[index].process = processes[p]; // Mark the block as used
            internalFragmentation[index] = memory[index].size - processes[p];
            cout << "Allocated process " << processes[p] << " in block " << index + 1 << endl;
        } else {
            cout << processes[p] << " cannot be allocated." << endl;
        }
    }
}

void nextFit(vector<MemoryBlock>& memory, vector<int>& processes, vector<int>& internalFragmentation)
{
    int lastIndex = 0;

    for(unsigned p = 0; p < processes.size(); p++) {
        int q = lastIndex;

        // Iterate through memory blocks in a circular manner starting from the last allocated block
        do {
            // Check if the block has sufficient size and is unallocated
            if(memory[q].size >= processes[p] && memory[q].process == UNALLOCATED) {
                memory[q].process = processes[p]; // Mark the block as used
                internalFragmentation[q] = memory[q].size - processes[p];
                cout << "Allocated process " << processes[p] << " in block " << q + 1 << endl;
                lastIndex = (q + 1) % memory.size();
                break;
            }

            q = (q + 1) % memory.size();
        } while(q != lastIndex);

        // Indicate if allocation is not possible
        if(q == lastIndex) {
            cout << processes[p] << " cannot be allocated." << endl;
        }
    }
}

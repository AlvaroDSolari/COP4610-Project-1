#include <iostream>
#include <sstream>
#include <vector> 

void fillVector(std::string myString, std::vector<int> &myVector){
    
    std::stringstream myStream(myString); 
    int currentInteger; 
    
    while(myStream >> currentInteger){
        myVector.push_back(currentInteger); 
    }
    
}

int main() {
    
    std::string userLine = ""; 
    std::vector<int> baseLocations;
    std::vector<int> displacementSizes; 
    std::vector<int> processSizes;
    std::vector<char> processLabels;
    
    int numberOfBlocks = 0; 
    int numberOfProcesses = 0; 
    bool errorEncountered = false;
    
    std::cout << "This memory manager program allocates slots to processes using the Best Fit Dynamic Relocation" << std::endl << std::endl; 
    std::cout << "Please enter the base locations of the slots: "; 
    std::getline(std::cin, userLine); 
    fillVector(userLine, baseLocations);
    numberOfBlocks = baseLocations.size(); 
    std::cout << "Please enter the displacements for the base locations previously entered by you: ";
    std::getline(std::cin, userLine); 
    fillVector(userLine, displacementSizes); 
    
    std::cout << std::endl; 
    std::cout << "Current slot map: " << std::endl; 
    for (int theCounter = 0; theCounter < numberOfBlocks; theCounter++){
        std::cout << baseLocations[theCounter] << "\t"; 
        if (theCounter == numberOfBlocks - 1){
            std::cout << std::endl; 
        }
    }
    for (int theCounter = 0; theCounter < numberOfBlocks; theCounter++){
        std::cout << displacementSizes[theCounter] << "\t"; 
        if (theCounter == numberOfBlocks - 1){
            std::cout << std::endl << std::endl; 
        }
    }
    
    std::cout << "Please enter the list of process sizes: "; 
    std::getline(std::cin, userLine); 
    fillVector(userLine, processSizes); 
    numberOfProcesses = processSizes.size(); 
    
    for (int theCounter = 0; theCounter < numberOfProcesses; theCounter++){
        processLabels.push_back(65 + theCounter);
    }
    
    std::cout << "Processes: " << std::endl; 
    for (int theCounter = 0; theCounter < numberOfProcesses; theCounter++){
        std::cout << processLabels[theCounter] << "\t"; 
        if (theCounter == numberOfProcesses - 1){
            std::cout << std::endl; 
        }
    }
    for (int theCounter = 0; theCounter < numberOfProcesses; theCounter++){
        std::cout << processSizes[theCounter] << "\t";
        if (theCounter == numberOfProcesses - 1){
            std::cout << std::endl << std::endl; 
        }
    }

    /***********************************
     * BEGINNING OF BEST FIT ALGORITHM *
     ***********************************/ 
    for (int theCounter = 0; theCounter < numberOfProcesses; theCounter++){
        
        int bestFitIndex = -1; 
        
        std::cout << "Taking up Proccess " << processLabels[theCounter] << std::endl; 
        
        for (int anotherCounter = 0; anotherCounter < numberOfBlocks; anotherCounter++){
            
            if (processSizes[theCounter] <= displacementSizes[anotherCounter]){ /* If the processSizes is less than the displacementSizes, then the process can fit in this slot. */ 
                
                if (bestFitIndex == -1){ /* If bestFitIndex has a value of -1, then the process hasn't been allocated yet. */ 
                    bestFitIndex = anotherCounter; 
                } else if (displacementSizes[anotherCounter] < displacementSizes[bestFitIndex]){ /* If a smaller slot is found, then update the bestFitIndex to such spot. */ 
                    bestFitIndex = anotherCounter; 
                }
                
            }
        }
        
        /* If bestFitIndex is still -1, then that means that it couldn't be allocated! */ 
        if (bestFitIndex == -1){
            std::cout << "Slot assignment could not succeed. The Best Fit algorithm will now stop." << std::endl; 
            errorEncountered = true; 
        } else {
            std::cout << "Slot assignment successful. " << processLabels[theCounter] << " - Base location " << baseLocations[bestFitIndex] << "." << std::endl; 
            displacementSizes[bestFitIndex] = displacementSizes[bestFitIndex] - processSizes[theCounter]; 
            baseLocations[bestFitIndex] = baseLocations[bestFitIndex] + processSizes[theCounter]; 
        }
        
        std::cout << "Current slot map: " << std::endl; 
        for (int anotherCounter = 0; anotherCounter < numberOfBlocks; anotherCounter++){
            if (displacementSizes[anotherCounter] == 0){
                continue;
            }
            std::cout << baseLocations[anotherCounter] << "\t"; 
        }
        std::cout << std::endl; 
        for (int anotherCounter = 0; anotherCounter < numberOfBlocks; anotherCounter++){
            if (displacementSizes[anotherCounter] == 0){
                continue; 
            }
            std::cout << displacementSizes[anotherCounter] << "\t"; 
        }
        std::cout << std::endl << std::endl; 
        
        if (errorEncountered){
            break; 
        }
        
    }
    
    if (errorEncountered){
        std::cout << "Not all processes in the list could be allocated memory slots." << std::endl; 
    } else {
        std::cout << "All processes in the list were successfully allocated memory slots." << std::endl; 
    }
    
    return 0;

    
}
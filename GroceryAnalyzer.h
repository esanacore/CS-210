/*
GroceryAnalyzer.h
Author: Eric Sanacore (eric.sanacore@snhu.edu)
Date: 2024-06-17
Last Modified: 2024-06-22
Description: Header file for the GroceryAnalyzer class, which analyzes grocery item frequencies from a data file and provides various functionalities such as displaying frequencies, histograms, and saving data to a backup file.
*/


#ifndef GROCERY_ANALYZER_H // Header guard to prevent multiple inclusions of this header file
#define GROCERY_ANALYZER_H // Define the guard

#include <iostream> // For standard input/output operations
#include <string>   // For std::string type
#include <map>  // For std::map container

// Define the GroceryAnalyzer class
class GroceryAnalyzer {
private:
    // Private member variables
    std::map<std::string, int> itemFrequencies; // Stores item names and their frequencies
    std::string inputFileName;  // Name of the input data file
    std::string outputFileName; // Name of the backup output file

    // Private helper methods
    void loadFrequencies(); // Reads items from the input file and populates itemFrequencies
    void writeFrequenciesToFile();  // Writes the current itemFrequencies to the backup file

public:
	// Public constructor declaration
    // Initializes the analyzer, loads data, and creates the backup file
    GroceryAnalyzer(const std::string& inputFile, const std::string& outputFile);

    // Public methods (accessible from outside the class)
    int getItemFrequency(const std::string& item); // Returns the frequency of a specific item
    void printAllFrequencies(); // Prints all items and their frequencies
    void printHistogram();  // Prints a text-based histogram of item frequencies
    void displayMenu(); // Displays the main menu options
    void run(); // Runs the main program loop and handles user interaction
};

#endif // GROCERY_ANALYZER_H

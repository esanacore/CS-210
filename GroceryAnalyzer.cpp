/*
GroceryAnalyzer.cpp
Author: Eric Sanacore (eric.sanacore@snhu.edu)
Date: 2024-06-17
Last Modified: 2024-06-22
Description: Implementation of the GroceryAnalyzer class for analyzing grocery item frequencies from a file.
			 Includes methods for loading data, querying frequencies, printing reports, and displaying a menu interface.
			 All item lookups are case-insensitive, and the first letter of items is capitalized for display purposes.
			 Error handling is included for file operations and user input validation.
			 The program is designed to be modular and maintainable, following best practices for C++ programming.
*/


#include "GroceryAnalyzer.h" // Include the header file for the GroceryAnalyzer class
#include <fstream>  // Required for file I/O operations
#include <limits>   // Required for std::numeric_limits
#include <stdexcept>    // Required for std::runtime_error
#include <algorithm>    // Required for std::transform
#include <cctype>   // Required for ::tolower and ::toupper

// Converts a string to all lowercase characters for case-insensitive comparisons.
std::string toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return s;
}

// Converts a string to have its first letter capitalized and the rest lowercase.
std::string capitalizeFirstLetter(std::string s) {
    if (s.empty()) {
        return s;
    }
	// Convert entire string to lowercase first to handle cases like "POTATOES" -> "potatoes" or any other casing
    s = toLower(s);
	// Capitalize the first character for display purposes (e.g., "potatoes" -> "Potatoes") as sort of implicitly outlined in the requirements
    s[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(s[0])));
    return s;
}

// Loads item frequencies from the input file, converting all items to lowercase.
void GroceryAnalyzer::loadFrequencies() {
	std::ifstream inputFile(inputFileName); 

	if (!inputFile.is_open()) { // Error handling for file not found or inaccessible
        throw std::runtime_error("Error: Could not open input file: " + inputFileName);
    }

	std::string item; // Temporary variable to hold each item read from the file
	while (inputFile >> item) { // Read items one by one from the file
		itemFrequencies[toLower(item)]++; // Convert to lowercase and increment frequency count
    }
	inputFile.close();  // Close the input file after reading
}

// Writes the accumulated item frequencies to a backup file.
void GroceryAnalyzer::writeFrequenciesToFile() {
    std::ofstream outputFile(outputFileName);

	if (!outputFile.is_open()) { // Error handling for file not found or inaccessible
        std::cerr << "Error: Could not open output file for backup: " << outputFileName << std::endl;
        return;
    }

	for (const auto& pair : itemFrequencies) { // Iterate through the frequency map
		outputFile << capitalizeFirstLetter(pair.first) << " " << pair.second << std::endl; // Write each item and its frequency to the file, capitalizing the first letter for display
    }
	outputFile.close(); // Close the output file after writing
	std::cout << "Frequencies backed up to " << outputFileName << std::endl; // Confirmation message
}

// Constructor for the GroceryAnalyzer class.
GroceryAnalyzer::GroceryAnalyzer(const std::string& inputFile, const std::string& outputFile)
    : inputFileName(inputFile), outputFileName(outputFile) {
    try {
        loadFrequencies();
        writeFrequenciesToFile();
    } catch (const std::runtime_error& e) {
        throw;
    }
}

// Returns the frequency of a specific item, performing a case-insensitive search.
int GroceryAnalyzer::getItemFrequency(const std::string& item) {
    std::string searchItemLower = toLower(item);

    if (itemFrequencies.count(searchItemLower)) {
        return itemFrequencies[searchItemLower];
    }
    return 0;
}

// Prints all items and their frequencies to the console.
void GroceryAnalyzer::printAllFrequencies() {
    std::cout << "\n--- Item Frequencies ---" << std::endl;
    if (itemFrequencies.empty()) {
        std::cout << "No items found or loaded." << std::endl;
        return;
    }
    for (const auto& pair : itemFrequencies) {
        // Capitalize the first letter for display purposes (e.g., "potatoes" -> "Potatoes") as sort of implicitly outlined in the requirements
        std::cout << capitalizeFirstLetter(pair.first) << " " << pair.second << std::endl;
    }
    std::cout << "------------------------" << std::endl;
}

// Prints a text-based histogram of item frequencies.
void GroceryAnalyzer::printHistogram() {
    std::cout << "\n--- Item Frequency Histogram ---" << std::endl;
    if (itemFrequencies.empty()) {
        std::cout << "No items found or loaded to generate histogram." << std::endl;
        return;
    }
    for (const auto& pair : itemFrequencies) {
        // Capitalize the first letter for display
        std::cout << capitalizeFirstLetter(pair.first) << " ";
        for (int i = 0; i < pair.second; ++i) {
            std::cout << "*";
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------" << std::endl;
}

// Displays the main menu options to the user.
void GroceryAnalyzer::displayMenu() {
    std::cout << "\n--- Corner Grocer Menu ---" << std::endl;
    std::cout << "1. Look up item frequency" << std::endl;
    std::cout << "2. Print all item frequencies" << std::endl;
    std::cout << "3. Print histogram of item frequencies" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "Enter your choice: ";
}

// Runs the main program loop.
void GroceryAnalyzer::run() {
    int choice;
    std::string searchItem;

    do {
		displayMenu(); // Show the menu options to the user
		while (!(std::cin >> choice) || choice < 1 || choice > 4) { // Input validation for menu choice
			std::cout << "Invalid input. Please enter a number between 1 and 4: "; // Prompt user again for valid input
			std::cin.clear(); // Clear the error flag on cin
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline character from the input buffer

		switch (choice) { // Handle the user's menu choice
            case 1: // Look up item frequency
                std::cout << "Enter the item you wish to look for: ";
				std::getline(std::cin, searchItem); // Use getline to allow for multi-word items if needed in future
                { // Use a block scope for localized variable `frequency`
                    int frequency = getItemFrequency(searchItem);
					if (frequency > 0) { // Only display if item was found
                        std::cout << "Frequency of " << capitalizeFirstLetter(searchItem) << ": " << frequency << std::endl;
                    } else {
						std::cout << "'" << searchItem << "' not found in purchase records." << std::endl; // Inform user if item not found
                    }
                }
                break;
			case 2: // Print all item frequencies
                printAllFrequencies();
                break;
			case 3: // Print histogram of item frequencies
                printHistogram();
                break;
			case 4: // Exit the program
                std::cout << "Exiting program. Goodbye!" << std::endl;
                break;
			default: 
                /* This case should never be reached due to input validation above, but included for completeness as recommended in zyBooks 3.11 best practices :
                "Good practice is to always have a default case for a switch statement. A programmer may be sure all cases are covered only to be surprised that some case was missing. */
                std::cout << "An unexpected error occurred with your choice. Please try again." << std::endl;
                break;
        }
	} while (choice != 4); // Continue until user chooses to exit
}

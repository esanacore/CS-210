/*
Main.cpp
Author: Eric Sanacore (eric.sanacore@snhu.edu)
Date: 2024-06-17
Last Modified: 2024-06-22
Description: Main entry point for the Corner Grocer application. This file initializes the GroceryAnalyzer class and handles exceptions that may arise during execution.
*/


#include "GroceryAnalyzer.h" // Include the header for our GroceryAnalyzer class
#include <iostream>     // For standard input/output (std::cerr, std::endl)
#include <exception>    // For std::exception

int main() {
	// Constant file name definitions for input and output files -- makes it easy to change file names in one place if needed.
	const std::string INPUT_FILE = "CS210_Project_Three_Input_File.txt"; // Input file containing grocery data
	const std::string OUTPUT_FILE = "frequency.dat"; // Output file for frequency data backup

    try {
        // Create an instance of GroceryAnalyzer, loads data from INPUT_FILE and writes backup to OUTPUT_FILE
        GroceryAnalyzer analyzer(INPUT_FILE, OUTPUT_FILE);

        // If the analyzer is successfully initialized, run the main program loop.
        analyzer.run();
    }
    catch (const std::runtime_error& e) {
        // Catch specific runtime errors, typically related to file operations.
		std::cerr << "Application Error: " << e.what() << std::endl; // Display the error message from the exception
		std::cerr << "Please ensure the input file '" << INPUT_FILE // Display the expected input file name
			<< "' exists in the same directory as the executable." << std::endl; // Provide additional context for the error
		return 1; // Return a non-zero exit code to indicate an error (this can be customized as needed)
    }
    catch (const std::exception& e) {
        // Catch any other standard exceptions that might occur.
		std::cerr << "An unexpected standard error occurred: " << e.what() << std::endl; // Display the error message from the exception
		return 1; // Return a non-zero exit code to indicate an error (this can be customized as needed)
    }
    catch (...) {
        // Catch any other unknown or unhandled exceptions.
		std::cerr << "An unknown error occurred." << std::endl; // Generic error message for unknown exceptions
		return 1; // Return a non-zero exit code to indicate an error (this can be customized as needed)
    }

    return 0; // Return 0 to indicate successful program execution
}

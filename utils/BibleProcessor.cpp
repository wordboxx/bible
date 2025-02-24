#include "../headers/BibleProcessor.h"
#include <fstream>
#include <iostream>
#include <string>

void BibleProcessor::ScanBible(std::string bibleFilePath) {
  // --- Input stream variables
  std::ifstream bibleFile;
  std::string line;

  // Open the bible text file
  bibleFile.open(bibleFilePath);

  // If there's a problem opening the bible text file
  if (!bibleFile.is_open()) {
    std::cout << "Error: " << std::string(bibleFilePath) << " not found!";
    exit(1);
  }

  // Print out each line
  while (std::getline(bibleFile, line)) {
    std::cout << line << std::endl;
  }

  // Close the file
  bibleFile.close();
}

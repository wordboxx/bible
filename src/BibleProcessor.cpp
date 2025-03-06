// Imports
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <filesystem>
#include <functional>

// (Local)
#include "../headers/BibleProcessor.h"

// Filepaths
// TODO: fix this; these either shouldn't be in here, or they should ONLY be in here and not in main.cpp
// --- Data Directory
std::string dataDir = "data/";
// --- Processed Bible
std::string processedBibleFilepath = dataDir + "processedBible";
// --- Utility Files
std::string bibleBookNamesFilename = "bibleBookNames.txt";
std::string bibleBookNamesFilepath = dataDir + bibleBookNamesFilename;

// Methods
// --- Functional Methods
void BibleProcessor::ScanBibleFile(const std::string &bibleFilepath, std::function<void(const std::string &)> processLine)
{
	/*
	 * Takes in a bible text file and scans through every line.
	 */
	std::ifstream bibleFile;
	std::string bibleLine;

	// Open the bible text file
	bibleFile.open(bibleFilepath);
	if (!bibleFile.is_open())
	{
		std::cout << "Error: " << std::string(bibleFilepath) << " not found!" << std::endl;
		exit(1);
	}

	// Scan through every line of bible text file
	while (std::getline(bibleFile, bibleLine))
	{
		processLine(bibleLine);
	}
	// Close the file
	bibleFile.close();
}

std::string BibleProcessor::GetBookName(const std::string &bibleLine,
										const std::string &bibleBookNamesFilepath)
{
	/*
	 * Takes in a line from the bible text file and returns the book name if present.
	 */
	std::ifstream bibleBookNamesFile;
	std::string bibleBookName;

	// Open the bible book names file
	bibleBookNamesFile.open(bibleBookNamesFilepath);
	if (!bibleBookNamesFile.is_open())
	{
		std::cout << "Error: " << std::string(bibleBookNamesFilepath) << " not found!" << std::endl;
		exit(1);
	}

	// Scans through every line of bible book names file
	while (std::getline(bibleBookNamesFile, bibleBookName))
	{
		// First word of bible line
		std::string_view firstWord = bibleLine.substr(0, bibleLine.find(' '));

		// If the first word is a book name
		if (bibleBookName == firstWord)
		{
			return bibleBookName;
		}
	}

	// Close the file
	bibleBookNamesFile.close();

	return "";
}

int BibleProcessor::GetChapterNumber(const std::string &bibleLine)
{
	/*
	 * Takes in a line from the bible text file and returns the chapter number if present.
	 */

	// Get the spaces surrounding the proceeding number
	std::string::size_type firstSpacePos = bibleLine.find(' ');
	std::string::size_type secondSpacePos = bibleLine.find(' ', firstSpacePos + 1);

	// Use the spaces to isolate the chapter number
	std::string chapterNumber = bibleLine.substr(firstSpacePos + 1, secondSpacePos - firstSpacePos - 1);

	// Make double sure that what is being isolated is a number, thus a chapter number
	if (isdigit(chapterNumber[0]))
	{
		int currBibleChapter = std::stoi(chapterNumber);
		return currBibleChapter;
	}
	return -1;
}

std::pair<std::string, int> BibleProcessor::GetBookAndChapter(const std::string &bibleLine, const std::string &bibleBookNamesFilepath)
{
	std::string bookName = std::string(BibleProcessor::GetBookName(bibleLine, bibleBookNamesFilepath));
	int chapterNumber = BibleProcessor::GetChapterNumber(bibleLine);

	return std::make_pair(bookName, chapterNumber);
}

void BibleProcessor::CreateDirectory(const std::string &processedBibleFilepath,
									 const std::string &bibleLine)
{
	/*
	 * Takes in the processed Bible directory, the current book name, and the current chapter number.
	 */

	std::string bookName;
	int chapterNumber;
	std::tie(bookName, chapterNumber) = BibleProcessor::GetBookAndChapter(bibleLine, bibleBookNamesFilepath);

	// Make sure processed Bible directory exists
	if (!std::filesystem::exists(processedBibleFilepath))
	{
		std::filesystem::create_directory(processedBibleFilepath);
	}

	// Create Book directory if it doesn't exist
	std::string processedBibleBookDir = processedBibleFilepath + "/" + bookName;
	if (!std::filesystem::exists(processedBibleBookDir))
	{
		std::filesystem::create_directory(processedBibleBookDir);
	}

	// Insert text file for each chapter into Book directory if it doesn't exist
	std::string chapterFilename = bookName + "_" + std::to_string(chapterNumber) + ".txt";
	std::string processedBibleChapterFile = processedBibleBookDir + "/" + chapterFilename;
	if (!std::filesystem::exists(processedBibleChapterFile))
	{
		std::cout << processedBibleChapterFile << std::endl;
		std::ofstream chapterFile;
		chapterFile.open(processedBibleChapterFile);
		chapterFile.close();
	}
}

void BibleProcessor::ProcessLine(const std::string &bibleLine)
{
	BibleProcessor::CreateDirectory(processedBibleFilepath, bibleLine);
}
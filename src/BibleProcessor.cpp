// Imports
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <filesystem>

// (Local)
#include "../headers/BibleProcessor.h"

// Methods
// --- Functional Methods
void BibleProcessor::ScanBibleFile(const std::string &bibleFilepath)
{
	/*
	 * Takes in a bible text file and scans through every line.
	 */
	std::ifstream bibleFile;
	std::string bibleLine;
	std::string lastBook;
	int lastChapter;

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
		// TODO: Should make these functional calls or something
		// The real thing to do is to have ScanBible be able to passively return bible lines
		std::string_view currBook = BibleProcessor::GetBookName(bibleLine, "data/bibleBookNames.txt");
		if (currBook != "" && currBook != lastBook)
		{
			lastBook = currBook;
			// TODO: Do something with currBook
		}

		int currChapter = BibleProcessor::GetChapterNumber(bibleLine);
		if (currChapter != -1 && currChapter != lastChapter)
		// TODO: There might be a problem if the last book has a single chapter, since the next book will have the same chapter number
		{
			lastChapter = currChapter;
			// TODO: Do something with currChapter
		}
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

void BibleProcessor::CreateDirectory(const std::string &processedBibleFilepath,
									 const std::string &bibleBookName,
									 const int &chapterNumber)
{
	/*
	 * Takes in the processed Bible directory, the current book name, and the current chapter number.
	 */

	// Make sure processed Bible directory exists
	if (!std::filesystem::exists(processedBibleFilepath))
	{
		std::filesystem::create_directory(processedBibleFilepath);
	}

	// Create Book directory if it doesn't exist
	std::string processedBibleBookDir = processedBibleFilepath + "/" + bibleBookName;
	if (!std::filesystem::exists(processedBibleBookDir))
	{
		std::filesystem::create_directory(processedBibleBookDir);
	}

	// Insert text file for each chapter into Book directory if it doesn't exist
	std::string chapterFilename = bibleBookName + "_" + std::to_string(chapterNumber) + ".txt";
	std::string processedBibleChapterFile = processedBibleBookDir + "/" + chapterFilename;
	if (!std::filesystem::exists(processedBibleChapterFile))
	{
		std::cout << processedBibleChapterFile << std::endl;
		std::ofstream chapterFile;
		chapterFile.open(processedBibleChapterFile);
		chapterFile.close();
	}
}
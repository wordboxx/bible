// Imports
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <filesystem>

// (Local)
#include "../headers/BibleProcessor.h"

void BibleProcessor::ProcessBible(const std::string &bibleFilepath, const std::string &processedBibleFilepath)
{
	/*
	 * FUNCTION: Scans through every line of bible
	 * INPUT (String): 1) bibleFilepath to Bible text file
	 * OUTPUT (Void): Organizes bible into Book -> Chapter -> Verse in /data/processed/ directory
	 */

	// Variables for scanning through unprocessed Bible text file
	std::ifstream bibleFile;
	std::string bibleLine;

	// Open the bible text file
	bibleFile.open(bibleFilepath);

	// Exits if there's a problem opening the bible text file
	if (!bibleFile.is_open())
	{
		std::cout << "Error: " << std::string(bibleFilepath) << " not found!" << std::endl;
		exit(1);
	}

	// Scans through every line of bible text file
	while (std::getline(bibleFile, bibleLine))
	{
		// Variables for scanning through bible book names
		std::string bibleBookNamesFilepath = "data/bibleBookNames.txt";
		std::ifstream bibleBookNamesFile;
		std::string bibleBookName;

		// Open the bible book names file
		bibleBookNamesFile.open(bibleBookNamesFilepath);

		// Scans through every line of bible book names file
		while (std::getline(bibleBookNamesFile, bibleBookName))
		{
			// --- First word of bible line
			std::string_view firstWord = bibleLine.substr(0, bibleLine.find(' '));

			// --- If the first word is a book name
			if (bibleBookName == firstWord)
			{
				// --- Get the spaces surrounding the proceeding number
				std::string::size_type firstSpacePos = bibleLine.find(' ');
				std::string::size_type secondSpacePos = bibleLine.find(' ', firstSpacePos + 1);

				// --- Use the spaces to isolate the chapter number
				std::string_view chapterNumber = bibleLine.substr(firstSpacePos + 1, secondSpacePos - firstSpacePos - 1);

				// --- Make double sure that what is being isolated is a number, thus a chapter number
				if (isdigit(chapterNumber[0]))
				{
					// TODO: Make directories For each book and file for each chapter
					std::string processedBibleBookDir = processedBibleFilepath + "/" + std::string(firstWord);
					std::string processedBibleChapterFile = processedBibleBookDir + "/" + std::string(chapterNumber) + ".txt";
					if (!std::filesystem::exists(processedBibleBookDir))
					{
						std::filesystem::create_directory(processedBibleBookDir);
					} else {
						// TODO: make text files for each chapter. insert line until new chapter number is found
					}
				}
			}
		}
		bibleBookNamesFile.close();
	}

	// Close the file
	bibleFile.close();
}
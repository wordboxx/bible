#include "headers/BibleProcessor.h"

int main()
{
	// Filepath variables
	// --- Data Directory
	std::string dataDir = "data/";
	// --- Unprocessed Bible
	std::string unprocessedBibleFilename = "bibleTextNASB.txt";
	std::string unprocessedBibleFilepath = dataDir + unprocessedBibleFilename;
	// --- Processed Bible
	std::string processedBibleFilepath = dataDir + "processedBible";
	// --- Utility Files
	std::string bibleBookNamesFilename = "bibleBookNames.txt";
	std::string bibleBookNamesFilepath = dataDir + bibleBookNamesFilename;

	BibleProcessor::ScanBibleFile(unprocessedBibleFilepath);

	return 0;
}

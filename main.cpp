#include "headers/BibleProcessor.h"

int main()
{
	// Filepath variables
	// --- Data Directory
	std::string dataDir = "data/";
	// --- Unprocessed Bible
	std::string unprocessedBibleFilename = "bibleTextNASB.txt";
	std::string unprocessedBibleFilepath = dataDir + unprocessedBibleFilename;

	BibleProcessor::ScanBibleFile(unprocessedBibleFilepath, BibleProcessor::ProcessLine);

	return 0;
}

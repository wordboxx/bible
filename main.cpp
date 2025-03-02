#include "headers/BibleProcessor.h"

int main()
{
	// Filepath variables
	std::string dataDir = "data/";
	// --- Unprocessed Bible
	std::string unprocessedBibleFilename = "bibleTextNASB.txt";
	std::string unprocessedBibleFilepath = dataDir + unprocessedBibleFilename;
	// --- Processed Bible
	std::string processedBibleFilepath = dataDir + "processedBible";

	// Process the Bible
	BibleProcessor::ProcessBible(unprocessedBibleFilepath, processedBibleFilepath);

	return 0;
}

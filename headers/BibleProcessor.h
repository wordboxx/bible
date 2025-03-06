#ifndef BIBLEPROCESSOR_H
#define BIBLEPROCESSOR_H

#include <string>
#include <functional>

class BibleProcessor
{
public:
	// --- Functional Methods
	static void ScanBibleFile(const std::string &bibleFilepath);
	static std::string GetBookName(const std::string &bibleLine,
								   const std::string &bibleBookNamesFilepath);
	static int GetChapterNumber(const std::string &bibleLine);
	static void CreateDirectory(const std::string &processedBibleFilepath,
								const std::string &bibleBookName,
								const int &chapterNumber);
};

#endif

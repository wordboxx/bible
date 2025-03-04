#ifndef BIBLEPROCESSOR_H
#define BIBLEPROCESSOR_H

#include <string>

class BibleProcessor
{
public:
	static void ProcessBible(const std::string &bibleFilepath, const std::string &processedBibleFilepath);
	static std::string GetBookName(std::string &bibleLine, std::string &processedBibleFilepath);
	static int BibleProcessor::GetChapterNumber(std::string &bibleLine, std::string &processedBibleFilepath, std::string &bibleBookName);
	static void BibleProcessor::CreateDirectory(std::string &bibleBookName, std::string &chapterNumber, std::string &processedBibleFilepath);
};

#endif

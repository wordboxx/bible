#ifndef BIBLEPROCESSOR_H
#define BIBLEPROCESSOR_H

#include <string>
#include <functional>

class BibleProcessor
{
public:
	// --- Functional Methods
	static void ScanBibleFile(const std::string &bibleFilepath, std::function<void (const std::string &)> processLine);
	static void ProcessLine (const std::string &bibleLine);
	static std::string GetBookName(const std::string &bibleLine,
								   const std::string &bibleBookNamesFilepath);
	static int GetChapterNumber(const std::string &bibleLine);
	static std::pair<std::string, int> GetBookAndChapter(const std::string &bibleLine, const std::string &bibleBookNamesFilepath);
	static void CreateDirectory(const std::string &processedBibleFilepath,
								const std::string &bibleLine);
};

#endif

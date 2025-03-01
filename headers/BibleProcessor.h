#ifndef BIBLEPROCESSOR_H
#define BIBLEPROCESSOR_H

#include <string>

class BibleProcessor
{
public:
	static void ProcessBible(const std::string &bibleFilepath, const std::string &processedBibleFilepath);
};

#endif

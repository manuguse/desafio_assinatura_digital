#ifndef UTILS_H
#define UTILS_H

#include <ByteArray.h>
#include <fstream>

class Utils {
public:
    static ostringstream* createFileOStringStream(const string& filePath);

    static ByteArray getPdfByteArray(const string& pdfPath);

    static bool writeFile(const string& filePath, const string& content);

    static bool isPDF(const string& filename);
};

#endif // UTILS_H

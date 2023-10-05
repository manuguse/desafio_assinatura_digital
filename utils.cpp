#include "utils.h"

ostringstream* Utils::createFileOStringStream(const string& filePath) {
    ostringstream* oss = new ostringstream;
    ifstream file(filePath.c_str());

    (*oss) << file.rdbuf();

    return oss;
}

ByteArray Utils::getPdfByteArray(const string& pdfPath){
    ostringstream* ost = createFileOStringStream(pdfPath);
    ByteArray pdfByteArray = ByteArray(ost);
    return pdfByteArray;
}

bool Utils::writeFile(const string& filePath, const string& content) {
    ofstream file(filePath.c_str());
    if (!file) {
        return false; // Falha ao abrir o arquivo
    }
    file << content;
    return true;
}

bool Utils::isPDF(const string &filename) {
    // Verifica se a extensão do arquivo é ".pdf"
    size_t dotPosition = filename.find_last_of('.');
    if (dotPosition != string::npos) {
        string extension = filename.substr(dotPosition);
        return (extension == ".pdf" || extension == ".PDF");
    }
    return false;
}

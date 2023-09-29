// including digital signatures to pdfs

#include <iostream>
#include <fstream>
#include <poppler-document.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <vector>

using namespace std;
using namespace poppler;

int main(){
    const string path = "exemple.pdf";
    Poppler::Document* pdf = Poppler::Document::load("documento.pdf");

    RSA* rsa_private_key = nullptr;
    X509* cetificate = nullptr;



    return 0;
}

class Document{
    public:
        Document(const string& path);
        ~Document();

        void sign(const string& path, const string& signature);
        void show_signatures(const string& path);
        void add_person_to_sign(const string& path, const string& people);

    private:
        Poppler::Document* pdf;
        RSA* rsa_private_key;
        X509* certificate;
        vector<string> signatures;
        vector<string> people_to_sign;

};

Document::Document(const string& path){
    pdf = Poppler::Document::load(path);
}

void Document::add_people_to_sign
#include <iostream>
#include <fstream>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <podofo/podofo.h>

int main() {
    // Load the PDF document
    PoDoFo::PdfDocument pdf("input.pdf");

    // Load the private key
    FILE* keyFile = fopen("private_key.pem", "rb");
    RSA* rsa = PEM_read_RSAPrivateKey(keyFile, nullptr, nullptr, nullptr);
    fclose(keyFile);

    // Prepare the data for signing (you can customize this part)
    std::string dataToSign = pdf.GetObjects()[0]->ToString();

    // Compute the SHA256 hash of the data
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(dataToSign.c_str()), dataToSign.length(), hash);

    // Create a signature
    unsigned char signature[2048]; // Adjust the buffer size as needed
    unsigned int signatureLen;
    EVP_PKEY* pkey = EVP_PKEY_new();
    EVP_PKEY_set1_RSA(pkey, rsa);
    EVP_MD_CTX* mdCtx = EVP_MD_CTX_new();
    EVP_SignInit(mdCtx, EVP_sha256());
    EVP_SignUpdate(mdCtx, hash, SHA256_DIGEST_LENGTH);
    EVP_SignFinal(mdCtx, signature, &signatureLen, pkey);

    // Add the signature to the PDF (adjust the signature position)
    PoDoFo::PdfStream* stream = new PoDoFo::PdfStream("stream");
    stream->GetContents().Set(reinterpret_cast<const char*>(signature), signatureLen);

    PoDoFo::PdfReference signatureRef = pdf.CreateObject(stream);
    PoDoFo::PdfPage* page = pdf.GetPage(0); // Assuming you're signing the first page
    page->GetObject()->GetDictionary().AddKey(PoDoFo::PdfName("Signature"), signatureRef);

    // Save the modified PDF
    pdf.Write("output.pdf");

    // Clean up
    EVP_PKEY_free(pkey);
    EVP_MD_CTX_free(mdCtx);
    RSA_free(rsa);

    return 0;
}

#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>
#include "KeyPair.h"
#include <libcryptosec/certificate/CertificateBuilder.h>
#include "ByteArray.h"
#include "MessageDigest.h" 
#include "Signer.h"

class Operator {
public:
    Operator(const string& name, const KeyPair& keyPair, const Certificate& certificate);

    string getName() const;

    const KeyPair& getKeyPair() const;

    const Certificate& getCertificate() const;

    ByteArray signPDF(ByteArray pdfByteArray);

    bool verifySignature(ByteArray pdfByteArray);

    ByteArray& getSignedPDF();

private:
    string name;
    KeyPair keyPair;
    Certificate certificate;
    ByteArray signedPDF;
};

#endif // OPERATOR_H

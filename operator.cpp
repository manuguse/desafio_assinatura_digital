#include "operator.h"

Operator::Operator(const string& name, const KeyPair& keyPair, const Certificate& certificate)
    : name(name), keyPair(keyPair), certificate(certificate) {
}

string Operator::getName() const {
    return name;
}

const KeyPair& Operator::getKeyPair() const {
    return keyPair;
}

const Certificate& Operator::getCertificate() const {
    return certificate;
}

ByteArray Operator::signPDF(ByteArray pdfByteArray) {
    MessageDigest messageDigest = MessageDigest(MessageDigest::SHA256);
    ByteArray sha256data = messageDigest.doFinal(pdfByteArray);
    ByteArray signedPDF = Signer::sign(*keyPair.getPrivateKey(), sha256data, MessageDigest::SHA256);
    this->signedPDF = signedPDF;
    return signedPDF;
}

bool Operator::verifySignature(ByteArray pdfByteArray) {
    MessageDigest messageDigest = MessageDigest(MessageDigest::SHA256);
    ByteArray sha256data = messageDigest.doFinal(pdfByteArray);
    bool verify = Signer::verify(*keyPair.getPublicKey(), signedPDF, sha256data, MessageDigest::SHA256);
    return verify;
}

ByteArray& Operator::getSignedPDF() {
    return signedPDF;
}

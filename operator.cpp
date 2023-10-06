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
    // Cria um objeto MessageDigest para calcular o hash do PDF
    MessageDigest messageDigest = MessageDigest(MessageDigest::SHA256);
    ByteArray sha256data = messageDigest.doFinal(pdfByteArray);

    // Realiza a assinatura digital usando o par de chaves privadas do operador
    ByteArray signedPDF = Signer::sign(*keyPair.getPrivateKey(), sha256data, MessageDigest::SHA256);

    // Armazena a assinatura no atributo signedPDF da classe Operator
    this->signedPDF = signedPDF;

    // Retorna a assinatura
    return signedPDF;
}

bool Operator::verifySignature(ByteArray pdfByteArray) {
    // Calcula o hash SHA-256 do conteúdo do PDF
    MessageDigest messageDigest = MessageDigest(MessageDigest::SHA256);
    ByteArray sha256data = messageDigest.doFinal(pdfByteArray);

    // Verifica a assinatura digital usando a chave pública do operador
    bool verify = Signer::verify(*keyPair.getPublicKey(), signedPDF, sha256data, MessageDigest::SHA256);

    // Retorna true se a assinatura for válida, senão retorna false
    return verify;
}

ByteArray& Operator::getSignedPDF() {
    return signedPDF;
}

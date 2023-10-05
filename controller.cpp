#include "controller.h"

// Implementação do método estático runProgram
void Controller::runProgram() {
    ByteArray pdfByteArray = getPDFByteArray();
    vector<Operator> operators = createOperators();
    displayOperatorMenu(operators, pdfByteArray);
}

// Implementação do método estático getPDFByteArray
ByteArray Controller::getPDFByteArray() {
    string pdfPath = View::getPDFpath();
    ByteArray pdfByteArray = Utils::getPdfByteArray(pdfPath);
    return pdfByteArray;
}

// Implementação do método estático displayAllSignedMenu
void Controller::displayAllSignedMenu(vector<Operator>& operators, ByteArray& pdfByteArray) {
    View::displaySimpleMessage("\nTodos os operadores assinaram o documento!");
    while (true) {
        int choice = View::showAllSignedMenu();
        
        if (choice == 1) {
            int operatorIndex = View::selectOperatorFromAll("\n--- Selecione um operador para verificar a assinatura ---\n", operators);
            if (operatorIndex >= 1 && operatorIndex <= operators.size()) {
                Operator& selectedOperator = operators[operatorIndex - 1];
                bool verifySignature = selectedOperator.verifySignature(pdfByteArray);
                string text = "Assinatura do operador " + selectedOperator.getName();
                if (verifySignature) {
                    text += " validada.";
                } else {
                    text += " não validada.";
                }
                View::displaySimpleMessage(text);
            }

        } else if (choice == 2) {
            int operatorIndex = View::selectOperatorFromAll("\n--- Selecione um operador para exportar as chaves ---\n", operators);
            if (operatorIndex >= 1 && operatorIndex <= operators.size()) {
                Operator& selectedOperator = operators[operatorIndex - 1];

                string path = saveKeysFromOperator(selectedOperator);
                View::displaySimpleMessage("Chaves de " + selectedOperator.getName() + " salvo como: " + path);
            }
        }
        else if (choice == 3) {
            int operatorIndex = View::selectOperatorFromAll("\n--- Selecione um operador para exportar o certificado ---\n", operators);
            if (operatorIndex >= 1 && operatorIndex <= operators.size()) {
                Operator& selectedOperator = operators[operatorIndex - 1];

                string path = saveCertificateFromOperator(selectedOperator);
                View::displaySimpleMessage("Certificado de " + selectedOperator.getName() + " salvo como: " + path);
            }
        } else if (choice == 4) {
            int operatorIndex = View::selectOperatorFromAll("\n--- Selecione um operador para exportar a assinatura ---\n", operators);
            if (operatorIndex >= 1 && operatorIndex <= operators.size()) {
                Operator& selectedOperator = operators[operatorIndex - 1];

                string path = saveSignatureFromOperator(selectedOperator);
                View::displaySimpleMessage("Assinature de " + selectedOperator.getName() + " salvo como: " + path);
            }
        } else if (choice == 5) {
            for (int i = 0; i < operators.size(); i++) {
                Operator selectedOperator = operators[i];
                saveKeysFromOperator(selectedOperator);
                saveCertificateFromOperator(selectedOperator);
                saveSignatureFromOperator(selectedOperator);
            }
            View::displaySimpleMessage("Todos os arquivos foram salvos na pasta execução do programa.");
        } else if (choice == 6) {
            break;
        }
    }
}

// Implementação do método estático saveKeysFromOperator
string Controller::saveKeysFromOperator(Operator selectedOperator) {
    string privateKeyFilePath =  selectedOperator.getName() + " privateKey.pem";
    string publicKeyFilePath = selectedOperator.getName() + " publicKey.pem";
    KeyPair keyPair = selectedOperator.getKeyPair();
    string privateKeyContent = keyPair.getPrivateKey()->getPemEncoded();
    string publicKeyContent = keyPair.getPublicKey()->getPemEncoded();
    Utils::writeFile(privateKeyFilePath, privateKeyContent);
    Utils::writeFile(publicKeyFilePath, publicKeyContent);
    return privateKeyFilePath + " e " + publicKeyFilePath;
}

// Implementação do método estático saveCertificateFromOperator
string Controller::saveCertificateFromOperator(Operator selectedOperator) {
    string certificateFilePath =  selectedOperator.getName() + " certificate.pem";
    Certificate certificate = selectedOperator.getCertificate();
    string certificateContent = certificate.getPemEncoded();
    Utils::writeFile(certificateFilePath, certificateContent);
    return certificateFilePath;
}

// Implementação do método estático saveSignatureFromOperator
string Controller::saveSignatureFromOperator(Operator selectedOperator) {
    string signatureFilePath =  selectedOperator.getName() + " signatureHex.txt";
    ByteArray signature = selectedOperator.getSignedPDF();
    string signatureContent = signature.toHex();
    Utils::writeFile(signatureFilePath, signatureContent);
    return signatureFilePath;
}

// Implementação do método estático createOperators
vector<Operator> Controller::createOperators() {
    vector<Operator> operators;
    int numOperators = View::askNumberOfOperators();
    cin.ignore();
    for (int i = 1; i <= numOperators; i++) {
        string name = View::getOperatorNameFromUserInput(i);
        KeyPair keyPair(AsymmetricKey::RSA, 2048);
        CertificateRequest certificateRequest = CertificateRequest();
        certificateRequest.setPublicKey(*keyPair.getPublicKey());
        CertificateBuilder certificateBuilder(certificateRequest);
        certificateBuilder.setPublicKey(*keyPair.getPublicKey());

        RDNSequence rDNSequence = RDNSequence();
        rDNSequence.addEntry(RDNSequence::COMMON_NAME, name);
        certificateBuilder.setIssuer(rDNSequence);
        certificateBuilder.setSubject(rDNSequence);
        Certificate* certificate = certificateBuilder.sign(*keyPair.getPrivateKey(), MessageDigest::SHA256);

        Operator operatorInstance(name, keyPair, *certificate);
        operators.push_back(operatorInstance);
    }

    return operators;
}

// Implementação do método estático displayOperatorMenu
void Controller::displayOperatorMenu(vector<Operator>& operators, ByteArray& pdfByteArray) {
    while (true) {
        int choice = View::showMainMenu();

        if (choice == 1) {
            // Opção para verificar informações dos operadores
            for (size_t i = 0; i < operators.size(); i++) {
                View::displayOperatorInfo(i + 1, operators[i]);
            }
        } else if (choice == 2) {
            // Opção para assinar PDF por operador
            int operatorIndex = View::selectOperatorToSignPDF(operators);
            bool wasLast = false;

            if (operatorIndex == 0) {
                continue; // Voltar ao Menu Principal
            } else if (operatorIndex < 0) {
                wasLast = true;
                operatorIndex = -operatorIndex;
            }

            if (operatorIndex >= 1 && operatorIndex <= operators.size()) {
                Operator& selectedOperator = operators[operatorIndex - 1];
                ByteArray signedPDF = selectedOperator.signPDF(pdfByteArray);
                View::displaySimpleMessage("O PDF foi assinado pelo operador " + selectedOperator.getName());
            }

            if (wasLast) {
                displayAllSignedMenu(operators, pdfByteArray);
                break;
            }
        } else if (choice == 3) {
            View::displaySignedOperators(operators);
        } else if (choice == 4) {
            // Opção para sair
            break;
        }
    }
}

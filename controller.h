#include <ByteArray.h>
#include <operator.h>
#include <view.h>

class Controller {
public:
    static void runProgram();

private:
    static ByteArray getPDFByteArray();
    static void displayAllSignedMenu(vector<Operator>& operators, ByteArray& pdfByteArray);
    static string saveKeysFromOperator(Operator selectedOperator);
    static string saveCertificateFromOperator(Operator selectedOperator);
    static string saveSignatureFromOperator(Operator selectedOperator);
    static vector<Operator> createOperators();
    static void displayOperatorMenu(vector<Operator>& operators, ByteArray& pdfByteArray);
};

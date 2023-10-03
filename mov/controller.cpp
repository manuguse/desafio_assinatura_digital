#include <iostream>
#include <vector>
#include <string>

#include "view.h"
#include "operator.h"

using namespace std;

class Controller {
public:
    static vector<Operator> createOperators() {
        vector<Operator> operators;
        int numOperators = View::askNumberOfOperators();

        for (int i = 1; i <= numOperators; i++) {
            Operator operatorInstance = View::createOperatorFromUserInput(i);
            operators.push_back(operatorInstance);
        }

        return operators;
    }

    static void displayOperatorMenu(const vector<Operator>& operators) {
        while (true) {
            int choice = View::showMainMenu();

            if (choice == 1) {
                // Opção para verificar informações dos operadores
                for (size_t i = 0; i < operators.size(); i++) {
                    View::displayOperatorInfo(i + 1, operators[i]);
                }
            } else if (choice == 2) {
                // Opção para sair
                break;
            }
        }
    }

    static void runProgram() {
        // Solicite o caminho do arquivo PDF
        string pdfFilePath = View::askPDFFilePath();

        // Crie os operadores com a ajuda do controlador
        vector<Operator> operators = createOperators();

        // Execute o menu principal
        displayOperatorMenu(operators, pdfFilePath);
    }
};

int main() {
    // Inicie o programa chamando a função runProgram do Controller
    Controller::runProgram();

    return 0;
}
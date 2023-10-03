#include <iostream>
#include <vector>
#include <string>

#include "operator.h"

using namespace std;

class View {
public:
    static Operator createOperatorFromUserInput(int operatorNumber) {
        string name, organization, country;

        cout << "Digite o nome do Operator " << operatorNumber << ": ";
        cin.ignore();  // Limpa o buffer de entrada
        getline(cin, name);

        cout << "Digite a organizacao do Operator " << operatorNumber << ": ";
        getline(cin, organization);

        cout << "Digite o pais do Operator " << operatorNumber << ": ";
        getline(cin, country);

        // Cria uma instância da classe Operator com os dados informados
        Operator operatorInstance(name, organization, country);

        return operatorInstance;
    }

    static int askNumberOfOperators() {
        int numOperators;

        while (true) {
            cout << "Quantos operators você deseja criar? ";
            if (!(cin >> numOperators) || numOperators < 1) {
                cin.clear();  // Limpa o erro de entrada
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignora a entrada inválida
                cout << "Por favor, insira um número válido maior ou igual a 1." << endl;
                continue;
            }

            break;
        }

        return numOperators;
    }

    static void displayOperatorInfo(int operatorNumber, const Operator& operatorInstance) {
        cout << "Nome do Operator " << operatorNumber << ": " << operatorInstance.getName() << endl;
        cout << "Organização do Operator " << operatorNumber << ": " << operatorInstance.getOrganization() << endl;
        cout << "País do Operator " << operatorNumber << ": " << operatorInstance.getCountry() << endl;
    }

    static int showMainMenu() {
        int choice;

        cout << "\n--- Menu Principal ---\n";
        cout << "1. Verificar informações dos operadores\n";
        cout << "2. Sair\n";
        cout << "Escolha uma opção: ";

        while (true) {
            if (!(cin >> choice) || (choice != 1 && choice != 2)) {
                cin.clear();  // Limpa o erro de entrada
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignora a entrada inválida
                cout << "Por favor, escolha uma opção válida (1 ou 2): ";
                continue;
            }

            break;
        }

        return choice;
    }

    static string askPDFFilePath() {
        string pdfFilePath;
        cout << "Digite o caminho do arquivo PDF a ser assinado: ";
        cin.ignore();
        getline(cin, pdfFilePath);
        return pdfFilePath;
    }
};
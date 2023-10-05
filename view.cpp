#include "view.h"

string View::getOperatorNameFromUserInput(int operatorNumber) {
    string name;
    cout << "Digite o nome do Operator " << operatorNumber << ": ";
    getline(cin, name);
    return name;
}

int View::selectOperatorToSignPDF(vector<Operator>& operators) {
    int choice;
    cout << "\n--- Selecione um operador para assinar o PDF ---\n";
    int validChoices = 0;

    for (size_t i = 0; i < operators.size(); i++) {
        if (operators[i].getSignedPDF().size() == 0) {
            cout << i + 1 << ". " << operators[i].getName() << endl;
            validChoices++;
        }
    }

    if (validChoices == 0) {
        cout << "Nenhum operador disponível para assinar o PDF." << endl;
        return 0;
    }

    cout << "0. Voltar ao Menu Principal\n";
    cout << "Escolha uma opção: ";

    while (true) {
        if (!(cin >> choice) || (choice <= 0 || choice > operators.size()) || operators[choice - 1].getSignedPDF().size() != 0) {
            cin.clear();
            if (choice == 0) {
                return 0;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Por favor, escolha uma opção válida." << endl;
            continue;
        }

        break;
    }

    if (validChoices == 1 && choice != 0) {
        return -choice;
    } else {
        return choice;
    }
}

int View::selectOperatorFromAll(string header, vector<Operator>& operators) {
    int choice;
    cout << header;

    for (size_t i = 0; i < operators.size(); i++) {
        cout << i + 1 << ". " << operators[i].getName() << endl;
    }

    cout << "0. Voltar ao Menu Principal\n";
    cout << "Escolha uma opção: ";

    while (true) {
        if (!(cin >> choice) || (choice <= 0 || choice > operators.size())) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Por favor, escolha uma opção válida." << endl;
            continue;
        }

        break;
    }

    return choice;
}

string View::getPDFpath() {
    string userInput;
    bool isValid = false;

    while (!isValid) {
        cout << "Digite o caminho do PDF: ";
        getline(cin, userInput);

        ifstream file(userInput.c_str());
        if (!file) {
            cout << "O arquivo não existe." << endl;
        } else {
            file.close();

            if (!Utils::isPDF(userInput)) {
                cout << "O arquivo não é um arquivo PDF." << endl;
            } else {
                isValid = true;
            }
        }
    }

    return userInput;
}

int View::showMainMenu() {
    int choice;
    cout << "\n--- Menu Principal ---\n";
    cout << "1. Verificar informações dos operadores\n";
    cout << "2. Assinar PDF por operador\n";
    cout << "3. Ver operadores que já assinaram\n";
    cout << "4. Sair\n";
    cout << "Escolha uma opção: ";

    while (true) {
        if (!(cin >> choice) || (choice < 1 || choice > 4)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Por favor, escolha uma opção válida (1, 2, 3 ou 4): ";
            continue;
        }

        break;
    }

    return choice;
}

int View::showAllSignedMenu() {
    int choice;
    cout << "\n--- Menu de assinaturas ---\n";
    cout << "1. Verificar asinaturas\n";
    cout << "2. Exportar par de chaves\n";
    cout << "3. Exportar certificado\n";
    cout << "4. Exportar assinatura\n";
    cout << "5. Exportar tudo\n";
    cout << "6. Sair\n";
    cout << "Escolha uma opção: ";

    while (true) {
        if (!(cin >> choice) || (choice < 1 || choice > 6)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Por favor, escolha uma opção válida (1, 2, 3, 4, 5 ou 6): ";
            continue;
        }

        break;
    }

    return choice;
}

int View::askNumberOfOperators() {
    int numOperators;

    while (true) {
        cout << "Quantos operators você deseja criar? ";
        if (!(cin >> numOperators) || numOperators < 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Por favor, insira um número válido maior ou igual a 1." << endl;
            continue;
        }

        break;
    }

    return numOperators;
}

void View::displayOperatorInfo(int operatorNumber, const Operator& operatorInstance) {
    cout << "Nome do Operator " << operatorNumber << ": " << operatorInstance.getName() << endl;
    // Adicione qualquer outra informação relevante sobre o operador aqui
}

void View::displaySignedOperators(vector<Operator> operators) {
    cout << "\n--- Operadores que já assinaram o PDF ---\n";
    int count = 0;
    for (int i = 0; i < operators.size(); i++) {
        Operator operatorInstance = operators[i];
        if (operatorInstance.getSignedPDF().size() != 0) {
            cout << i + 1 << ". " << operatorInstance.getName() << endl;
            count++;
        }
    }

    if (count == 0) {
        cout << "Nenhum operador assinou o PDF ainda." << endl;
    }
}

void View::displaySimpleMessage(string message) {
    cout << message << endl;
}

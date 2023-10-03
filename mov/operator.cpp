#include <string>

using namespace std;

class Operator {
public:
    Operator(const string& name, const string& organization, const string& country)
        : name(name), organization(organization), country(country) {
    }

    // Getters para os atributos
    string getName() const {
        return name;
    }

    string getOrganization() const {
        return organization;
    }

    string getCountry() const {
        return country;
    }

    string getPrivateKeyPath() const {
        return privateKeyPath;
    }

    string getPublicKeyPath() const {
        return publicKeyPath;
    }

    string getCertificatePath() const {
        return certificatePath;
    }

    // Métodos set para os atributos dos caminhos dos arquivos
    void setPrivateKeyPath(const string& path) {
        privateKeyPath = path;
    }

    void setPublicKeyPath(const string& path) {
        publicKeyPath = path;
    }

    void setCertificatePath(const string& path) {
        certificatePath = path;
    }

private:
    string name;
    string organization;
    string country;
    string privateKeyPath;
    string publicKeyPath;
    string certificatePath;
};




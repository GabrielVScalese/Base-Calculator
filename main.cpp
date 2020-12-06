#include <iostream>
#include "Somadora.h"
#include "Subtradora.h"
#include "Multiplicadora.h"
#include "Divisora.h"
#include "Validadora.h"
#include <string>

using namespace std;

// Main do programa
int main() {
    inicio: cout << "==== [ Calculadora de Bases Numericas ] ====\n";

    base: cout << "\nDigite a base numerica dos valores: \n";
    int base;
    cin >> base;

    if (!Validadora::existsBase(base))
    {
        cout << "\nBase numerica invalida!\n";
        goto base;
    }

    std::cin.ignore();

    primeiroValor: cout << "\n" << "Digite o primeiro valor: \n";
    string valor1;
    getline(cin, valor1);

    if (!Validadora::existsInBase(valor1, base))
    {
        cout << "\nValor nao existe na base!\n";
        goto primeiroValor;
    }

    segundoValor: cout << "\nDigite o segundo valor: \n";
    string valor2;
    getline(cin, valor2);

    if (!Validadora::existsInBase(valor2, base))
    {
        cout << "\nValor nao existe na base!\n";
        goto segundoValor;
    }

    operacao: cout << "\nDigite a operacao: \n";
    string operacao;
    getline(cin, operacao);

    if (operacao != "+" && operacao != "-" && operacao != "*" && operacao != "/")
    {
        cout << "\nOperacao invalida!\n";
        goto operacao;
    }

    string result;
    switch (*operacao.c_str()) {
        case '+' :
        {
            if (valor1.find(',') == -1) // Nao foi possivel fazer metodo
                valor1.append(",0");

            if (valor2.find(',') == -1)
                valor2.append(",0");

            Somadora som (valor1, valor2, base);
            result = som.somarValores();
            break;
        }

        case '-':
        {
            if (valor1.find(',') == -1) // Nao foi possivel fazer metodo
                valor1.append(",0");

            if (valor2.find(',') == -1)
                valor2.append(",0");

            Subtradora sub (valor1, valor2, base);
            result = sub.subtrairValores();
            break;
        }

        case '*':
        {
            if (valor1.find(',') == -1) // Nao foi possivel fazer metodo
                valor1.append(",0");

            if (valor2.find(',') == -1)
                valor2.append(",0");

            Multiplicadora mul (valor1, valor2, base);
            result = mul.multiplicarValores();
            break;
        }

        case '/':
        {
            int numCasasDecimais;
            cout << "\nDigite o numero de casas decimais: \n";
            cin >> numCasasDecimais;

            std::cin.ignore();

            if (valor1.find(',') == -1) // Nao foi possivel fazer metodo
                valor1.append(",0");

            if (valor2.find(',') == -1)
                valor2.append(",0");

            Divisora div (valor1, valor2, base, numCasasDecimais);
            result = div.dividirValores();
            break;
        }
    }

    cout << "\nR: " + valor1 << " (base " << base  << ") " << operacao.c_str() << " " << valor2 << " (base " << base << ") = " << result << " (base " << base << ")";

    pergunta: cout << "\n\nDeseja continuar o programa? (S / N): \n";

    string resposta;
    getline(cin, resposta);

    if (resposta == "S")
    {
        system("cls");
        goto inicio;
    }
    else
        if (resposta == "N")
            return 0;
        else
        {
            cout << "\nDigite S ou N!";
            goto pergunta;
        }
}

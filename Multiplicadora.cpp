#include <string>
#include "Multiplicadora.h"
#include "Auxiliadora.h"
#include "Somadora.h"
#include "Conversor.h"

/* Implementacao da classe Multiplicadora */

using namespace std;

// Atributo que representa um vetor de valores obtidos durante uma multiplicacao
string valoresObtidos [1000];
// Atributo que representa que indica o indice atual do vetor de valores obtidos
int cont = 0;

// Construtor da classe
Multiplicadora::Multiplicadora(string valor1, string valor2, int base)
{
    Multiplicadora::valor1 = valor1;
    Multiplicadora::valor2 = valor2;
    Multiplicadora::base = base;
}

// Metodo que insere um valor no fim do vetor valoresObtidos
void inserirNoFim (string valor)
{
    valoresObtidos[cont++] = valor;
}

// Metodo que realiza uma multiplicacao entre dois digitos
string Multiplicadora::multiplicarDoisDigitos(string digito1, string digito2, string passaUm) {
    int valor1;
    int valor2;
    int adicional = 1;

    valor1 = Auxiliadora::converterDigitoEmInteiro(digito1);
    valor2 = Auxiliadora::converterDigitoEmInteiro(digito2);

    if (!passaUm.empty()) // Existe um "passaUm"
    {
        adicional = Auxiliadora::converterDigitoEmInteiro(passaUm);
        int produtoInicial = valor1 * valor2;
        return Conversor::dezParaOutra(produtoInicial + adicional, base);
    }

    return Conversor::dezParaOutra(valor1 * valor2 * adicional, base);
}

// Metodo que soma os valores obtidos durante a multiplicacao
string Multiplicadora::somarValoresObtidos()
{
    string ret = valoresObtidos[0];
    for (int i = 0; i < valoresObtidos->length() - 1; i++)
    {
        if (valoresObtidos[i + 1] == ",")
            break;

        Somadora som (ret, valoresObtidos[i + 1], base);
        ret = som.somarValores();
    }

    ret = Auxiliadora::removerZeros(Auxiliadora::inserirVirgula(ret, ret.length() -
    (Auxiliadora::getQtdDecimais(valor1) * 2))); // Retira impurezas do produto final

    return ret;
}

// Metodo que realiza a multiplicacao entre dois valores
string Multiplicadora::multiplicarValores(){
    string ret;
    string passaUm;

    Auxiliadora::prepararValores(&valor1, &valor2); // Prepara os valores para iniciar a multiplicacao
    string maiorValor = Auxiliadora::getMaiorValor(valor1, valor2);
    string menorValor = Auxiliadora::getMenorValor(valor1, valor2);

    int qtdZeros = -1; // Para saber quantos zeros descemos ao comecar cada multiplicacao de um digito
    for (int i = valor1.length() - 1; i >= 0; i--)
    {
        for (int j = valor1.length() - 1; j >= 0; j--)
        {
            if (string(1, maiorValor[j]) == "," || string(1, menorValor[i]) == "," || string(1, maiorValor[j]) == "")
                continue;

            string produtoDeDoisDigitos = multiplicarDoisDigitos(string(1, menorValor[i]),
                                                                 string(1, maiorValor[j]), passaUm);

            if (produtoDeDoisDigitos.length() > 1)
            {
                passaUm = produtoDeDoisDigitos.substr(0, produtoDeDoisDigitos.length() - 1);
                ret.insert(0, produtoDeDoisDigitos.substr(produtoDeDoisDigitos.length() - 1, 1));

                if (j == 0)
                    ret.insert(0, passaUm);
            }
            else
            {
                ret.insert(0, produtoDeDoisDigitos);
                passaUm = "";
            }
        }

        if (!ret.empty()) // Quando o digito atual e virgula, ignoramos o seu "produto"
        {
            qtdZeros++;
            ret.insert(ret.length(), qtdZeros, '0');
            inserirNoFim(ret);
        }

        ret = "";
        passaUm = "";
    }

    string resultadoFinal = somarValoresObtidos();

    valoresObtidos->erase();
    cont = 0;
    return resultadoFinal;
}



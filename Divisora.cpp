#include "Divisora.h"
#include "Auxiliadora.h"
#include "Multiplicadora.h"
#include "Subtradora.h"
#include <string>

/* Arquivo de implementacao da classe Divisora */

using namespace std;

int jaColocouVirgula = 0;

// Construtor da classe
Divisora::Divisora(string valor1, string valor2, int base, int numCasasDecimais)
{
    Divisora::valor1 = valor1;
    Divisora::valor2 = valor2;
    Divisora::base = base;

    if (numCasasDecimais <= 0)
        Divisora::numCasasDecimais = 1;
    else
        Divisora::numCasasDecimais = numCasasDecimais;
}

// Metodo que prepara os valores para comecar a divisao
void prepararValores (string *valor1, string *valor2)
{
    if (Auxiliadora::getQtdDecimais(*valor1) > Auxiliadora::getQtdDecimais(*valor2))
        *valor2 = Auxiliadora::completarParteDecimal(*valor2, Auxiliadora::getQtdDecimais(*valor1) -
        Auxiliadora::getQtdDecimais(*valor2));

    if (Auxiliadora::getQtdDecimais(*valor2) > Auxiliadora::getQtdDecimais(*valor1))
        *valor1 = Auxiliadora::completarParteDecimal(*valor1, Auxiliadora::getQtdDecimais(*valor2) -
        Auxiliadora::getQtdDecimais(*valor1));

    *valor1 = Auxiliadora::removerCaracter(',', *valor1);
    *valor2 = Auxiliadora::removerCaracter(',', *valor2);
}

// Metodo que obtem o quociente numa divisao
string Divisora::obterQuociente (string dividendo, string divisor){
    string quociente;
    string digitosPossiveis = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Digitos de todas as bases

    if (Auxiliadora::apenasZeros(dividendo))
        return "0";

    // Testa todos os produtos possiveis na base fornecida
    for (int i = 0; i < base; i++){
        Multiplicadora mul (divisor, string(1, digitosPossiveis.at(i)), base);
        string produto = Auxiliadora::removerZeros(mul.multiplicarValores());
        dividendo = Auxiliadora::removerZeros(dividendo);

        if (Auxiliadora::apenasZeros(produto))
            continue;
        else
            if (Auxiliadora::getMaiorValor(produto, dividendo) == dividendo)
                quociente = string(1, digitosPossiveis.at(i));
            else
                return quociente;
    }

    return quociente;
}

// Metodo que coloca virgula para introduzir valores decimais no resultado parcial
void Divisora::colocarVirgula(string *valor1, string *valor2, string *ret) {
    int primeiraVez = 1;

    while (Auxiliadora::getMaiorValor(*valor1, *valor2) == *valor2)
    {
        if (primeiraVez)
        {
            (*valor1).append("0");

            if (!jaColocouVirgula)
                if ((*ret).empty())
                    (*ret).append("0,");
                else
                    (*ret).append(",");

            primeiraVez = 0;
            jaColocouVirgula = 1;
        }
        else
        {
            (*valor1).append("0");
            (*ret).append("0");
        }
    }
}

// Metodo que realiza a divisao entre dois valores
string Divisora::dividirValores (){
    string ret;

    prepararValores(&valor1, &valor2);

    // Encontra um dividendo valido para iniciar a divisao
    string novoDividendo = string(1, valor1[0]);
    int i;
    for (i = 1; Auxiliadora::getMaiorValor(valor2, novoDividendo) == valor2; i++)
         novoDividendo += valor1[i];

    for (;;)
    {
        if (valor1 != valor2)
            if (Auxiliadora::getMaiorValor(valor1, valor2) == valor2)
                colocarVirgula(&valor1, &valor2, &ret);

        string quociente = obterQuociente(novoDividendo, valor2);
        ret.append(quociente);
        Multiplicadora mul (valor2, quociente, base);
        string produto = mul.multiplicarValores();
        Subtradora sub (novoDividendo, produto, base);
        string resto = sub.subtrairValores();

        if (Auxiliadora::getQtdDecimais(ret) > numCasasDecimais || Auxiliadora::apenasZeros(resto))
            break;

        if (i > valor1.length() - 1) // Nao existe mais digitos disponiveis no dividendo
        {
            novoDividendo = resto;
            if (Auxiliadora::getMaiorValor(valor2, novoDividendo) == valor2) // Novo dividendo e menor que o divisor
                Divisora::colocarVirgula(&novoDividendo, &valor2, &ret);
        }
        else
        {
            novoDividendo = resto + string(1, valor1[i]); // Pega a proximo digito do dividendo
            i++;
        }
    }

    jaColocouVirgula = 0; // Garantir que a proxima divisao comece com valores iniciais
    return Auxiliadora::removerCasasDecimais(ret, Auxiliadora::getQtdDecimais(ret) - numCasasDecimais);
}


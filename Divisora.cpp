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
        *valor1 = Auxiliadora::completarParteDecimal(*valor1, Auxiliadora::getQtdDecimais(*valor2) - Auxiliadora::getQtdDecimais(*valor1));

    *valor1 = Auxiliadora::removerCaracter(',', *valor1);
    *valor2 = Auxiliadora::removerCaracter(',', *valor2);
}

// Metodo que realiza a divisao entre dois valores (metodo secundario)
string Divisora::dividirValores (string dividendo, string divisor){
    string quociente;
    string ret; // Quociente

    // Encontra um dividendo valido para iniciar a divisao
    string novoDividendo = string(1, dividendo[0]);
    int i;
    for (i = 1; Auxiliadora::getMaiorValor(divisor, novoDividendo) == divisor; i++)
         novoDividendo += dividendo[i];

    for (;;)
    {
        quociente = obterQuociente(novoDividendo, divisor);
        ret.append(quociente);
        Multiplicadora mul (divisor, quociente, base);
        string produto = mul.multiplicarValores();
        Subtradora sub (novoDividendo, produto, base);
        string resto = sub.subtrairValores();

        // Quando o quociente ja esta pronto para ser retornado
        if (Auxiliadora::apenasZeros(resto) || Auxiliadora::getQtdDecimais(ret) > numCasasDecimais)
            break;

        if (i > dividendo.length() - 1) // Nao existe mais digitos disponiveis no dividendo
        {
            novoDividendo = resto;
            if (Auxiliadora::getMaiorValor(divisor, novoDividendo) == divisor) // Novo dividendo e menor que o divisor
                colocarVirgula(&novoDividendo, &divisor, &ret);
        }
        else
        {
            novoDividendo = resto + string(1, dividendo[i]); // Pega a proximo digito do dividendo
            i++;
        }
    }

    jaColocouVirgula = 0; // Garantir que a proxima divisao comece com valores iniciais
    return Auxiliadora::removerCasasDecimais(ret, Auxiliadora::getQtdDecimais(ret) - numCasasDecimais);
}

// Metodo que obtem o quociente numa divisao
string Divisora::obterQuociente (string dividendo, string divisor){
    string quociente;
    string digitosPossiveis = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Digitos de todas as bases

    // Testa todos os produtos possiveis na base fornecida
    for (int i = 0; i < base; i++){
        Multiplicadora mul (divisor, string(1, digitosPossiveis.at(i)), base);
        string produto = Auxiliadora::removerZeros(mul.multiplicarValores());
        dividendo = Auxiliadora::removerZeros(dividendo);

        if (Auxiliadora::apenasZeros(produto))
        {
            if (!Auxiliadora::apenasZeros(dividendo))
                quociente = string(1, digitosPossiveis.at(i));
        }
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

// Metodo que realiza divisao entre dois valores
string Divisora::dividirValores() {
    string ret;
    string digitosPossiveis = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Prepara o dividendo e o divisor para iniciar a divisao
    prepararValores(&valor1, &valor2);

    // Se o maior produto obtido a partir pelo divisor for menor que o dividendo
    Multiplicadora mul (valor2, string(1, digitosPossiveis[base - 1]), base);
    string maiorProduto = mul.multiplicarValores();
    if (Auxiliadora::getMaiorValor(maiorProduto, valor1) == valor1)
        return dividirValores(valor1, valor2);

    while (Auxiliadora::getQtdDecimais(ret) < numCasasDecimais)
    {
        if (valor1 != valor2)
            if (Auxiliadora::getMaiorValor(valor1, valor2) == valor2)
                colocarVirgula(&valor1, &valor2, &ret);

        string quociente = obterQuociente(valor1, valor2);
        ret.append(quociente);

        Multiplicadora mul (valor2, quociente, base);
        string produto = Auxiliadora::removerZeros(mul.multiplicarValores());

        Subtradora sub (valor1, produto, base);
        valor1 = Auxiliadora::removerZeros(sub.subtrairValores());

        if (Auxiliadora::apenasZeros(valor1)) // Nao ha mais resto
            return ret;
    }

    jaColocouVirgula = 0;
    return Auxiliadora::removerCasasDecimais(ret, Auxiliadora::getQtdDecimais(ret) - numCasasDecimais); // Retorna o quociente de acordo com o numero de casas desejada
}



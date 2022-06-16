#include "Funcoes.h"



istream& operator>>(istream& is, produto a)
{
	is >> a.nome;
	is >> a.preco;
	return is;
}

void linha(char ch, unsigned char tam) {
	for (char i = 0; i < tam; i++)
		cout << ch;
	cout << endl;
}

void menu() {
	cout << "Sistema de controle\n";
	linha();
	cout << "(P)edir\n"
			"(A)dicionar\n"
			"(E)xcluir\n"
			"(L)istar\n"
			"(S)air\n";
	linha();
	cout << "Opção: [_]\b\b";
}

void Adicionar(produto lista[], char* tam)
{
	produto temp{};
	cout << "Nome: ";
	cin >> temp;
	lista[*tam - 1] = temp;
	tam++;
}
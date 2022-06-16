#include "Funcoes.h"

//operadores

istream& operator>>(istream& is, produto& a)
{
	cout << "Nome: ";
	is >> a.nome;
	cout << "Preço: ";
	is >> a.preco;
	cout << "Quantidade: ";
	is >> a.quantidade;
	return is;
}

//funções de caso geral

void linha(char ch, unsigned char tam) {
	for (char i = 0; i < tam; i++)
		cout << ch;
	cout << endl;
}

produto* AumentarTamanhodeVetor(produto vetor[], char* tamanho)
{

	produto* temp = new produto[*tamanho + 2]
	{
		{"a", 1, 10},
		{"b", 2, 20},
		{"c", 3, 30},
		{"d", 4, 40},
		{"e", 5, 50},
		{"f", 6, 60},
	};
	delete[] vetor;
	return temp;
}


//menu
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



//funções do sistema

void Adicionar(produto* lista, char* tamanho)
{
	produto temp;
	cin >> temp;

	int contador = 0;
	for(contador; lista[contador].nome[0] != 0 && contador < *tamanho; contador++);

	//if(contador >= *tamanho - 1) lista = AumentarTamanhodeVetor(lista, tamanho);

	lista[contador] = temp;

}

void Listar(produto* lista, char tamanho)
{

	cout << fixed; cout.precision(2);
	for(int i = 0; i < tamanho && lista[i].nome[0] != 0; i++)
	{
		cout.width(10);
		cout << left << lista[i].nome;
		cout << " - R$";
		cout.width(5);
		cout << left << lista[i].preco;
		cout << " - ";
		cout.width(3);
		cout << right << lista[i].quantidade;
		cout << "kg";
		cout << endl;
	}

	system("Pause");
}

void Excluir(produto* lista, char* tam)
{
	int escolha;
	
	//exibir os elementos
	cout << "Qual elemento remover: \n";
	for (int i = 0; i < *tam; i++)
		cout << i+1 << ") " << lista[i].nome << endl;

	//escolhe o elemento a ser retirado
	cin >> escolha;

	//move os elementos uma posição à esquerda
	int i = escolha - 1;
	for(i; i < *tam; i++)
	lista[i] = lista[i+1];

	//ultimo elemento nulo
	lista[i-1] = {0, 0, 0};
	
}
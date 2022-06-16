#include "Funcoes.h"

//operadores

istream& operator>>(istream& is, produto& a)
{
	cout << "Nome: ";
	is >> a.nome;
	cout << "Pre�o: ";
	is >> a.preco;
	cout << "Quantidade: ";
	is >> a.quantidade;
	return is;
}

//fun��es de caso geral

void linha(char ch, unsigned char tam) {
	for (char i = 0; i < tam; i++)
		cout << ch;
	cout << endl;
}

produto* AumentarTamanhodeVetor(produto vetor[], char* tamanho)
{

	//tamanho do vetor baseado na potencia de 2
	char tamanhoNovoVetor = pow(2, log2f(*tamanho) + 1);

	//novo vetor com o tamanho crescido exponencialmente
	produto* temp = new produto[tamanhoNovoVetor];


	//copia de todos os elementos do vetor anterior
	int i = 0;
	for (i; i < *tamanho; i++) temp[i] = vetor[i];

	//preenchimento dos pr�ximos elementos com 0
	for ( i; i < tamanhoNovoVetor; i++) temp[i] = {0, 0, 0};

	//substitui��o do valor do tamanho do vetor
	*tamanho = tamanhoNovoVetor;
	return temp;
}

produto* RemoverElementodeVetor(produto vetor[], char tam, char elemento)
{
	//vetor temporario que ser� alterado
	produto* temp = new produto[tam];

	//c�pia de todos os elementos antes do elemento de remo��o
	for(int i = 0; i < elemento; i++) temp[i] = vetor[i];

	//c�pia de todos os elementos ap�s o elemento de remo��o
	for(int i = elemento; i < tam; i++) temp[i] = vetor[i+1];

	//ultimo elemento nulo
	temp[tam-1] = {0, 0, 0};


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
	cout << "Op��o: [_]\b\b";
}



//fun��es do sistema

produto* Adicionar(produto lista[], char* tam)
{
	//novo vetor que ser� alterado e conter� as altera��es
	produto* vetorTemp = new produto[*tam];


	//copia todas as informa��es do vetor anterior para o novo
	for (int i = 0; i < *tam; i++) vetorTemp[i] = lista[i];

	//contar quantos elementos est�o preenchidos
	int i = 0;
	for(i; vetorTemp[i].nome[0] != '\0' || (i + 1) == *tam; i++);

	//se o contador chegar ao tamanho do vetor, aumenta o vetor
	if (i + 1 == *tam) vetorTemp = AumentarTamanhodeVetor(vetorTemp, tam);
	//adiciona o novo elemento no vetor

	cin >> vetorTemp[i];


	return vetorTemp;
}

void Listar(produto lista[], char* tam)
{
	int contaTamanho = 0;
	for (int contador = 0; lista[contador].nome[0] != 0 || contador == *tam; contador++)
	{
		int i = 0;
		for(i; lista[contador].nome[i] != 0; i++);
		if (contaTamanho <= i) contaTamanho = i;
	}

	cout.fill(' '); cout << fixed; cout.precision(2);
	for (int contador = 0; lista[contador].nome[0] != 0 || contador == *tam; contador++)
	{
		cout.width(contaTamanho); 
		cout << left << lista[contador].nome;
		cout << " - R$";
		cout.width(5);
		cout << left << lista[contador].preco;
		cout << " - ";
		cout.width(3);
		cout << right << lista[contador].quantidade;
		cout << "kg";
		cout << endl;
	}
	system("Pause");
}

produto* Excluir(produto lista[], char* tam)
{
	//vetor com os elementos alterados
	produto* vetorTemp = new produto[*tam];


	//copia de todos os elementos alterados
	for(int i = 0; i < *tam; i++) vetorTemp[i] = lista[i];

	//display dos elementos dispon�veis
	for (int i = 0; i < *tam; i++) cout << i + 1 << ") " << vetorTemp[i].nome << endl;

	//escolha do elemento que ser� excluido
	int elementodeExclusao;	
	cout << "Escolha um elemento: ";
	cin >> elementodeExclusao;
	vetorTemp = RemoverElementodeVetor(vetorTemp, *tam, elementodeExclusao - 1);

	//display do vetor alterado
	for (int i = 0; i < *tam; i++) cout << i + 1 << ") " << vetorTemp[i].nome << endl;


	system("Pause");
	return vetorTemp;
}
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

void linha(ostream& os, char ch, unsigned char tam) {
	for (char i = 0; i < tam; i++)
		os << ch;
	os << endl;
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

void Pedir(produto* estoque, char* tamanho)
{
	//abrindo o arquivo
	char nomedoArquivo[16];
	char txt[16]{};
	ifstream fin;

	cout << "Nome do arquivo: ";
	cin >> nomedoArquivo;

	strcpy(txt, nomedoArquivo);
	strcat(txt, ".txt");

	fin.open(txt);
	while(!fin.is_open())
	{
		cout << "Arquivo não encontrado! Tente novamente...";
		system("Pause");
		system("Cls");
		cout << "Nome do arquivo: ";
		cin >> nomedoArquivo;

		strcpy(txt, nomedoArquivo);
		strcat(txt, ".txt");

		fin.open(txt);

		system("Cls");
	}



	//vetor com pedidos
	produto* pedido = new produto[8]{};



	bool falha = false;


	//entrada das informações
	produto temp;
	fin.getline(temp.nome, 16);
	fin.getline(temp.nome, 16);
	while (!fin.eof())
	{

		//recebe o nome do produto
		fin >> temp.nome;
		//formaliza o nome
		temp.nome[0] = toupper(temp.nome[0]);
		for(int i = 1; temp.nome[i] != '\0'; i++)
			temp.nome[i] = tolower(temp.nome[i]);


		//recebe a quantidade solicitada
		fin >> temp.quantidade;


		//confere onde adicionar a quantidade no vetor dinâmico
		int pos = 0;
		for(pos; strcmp(temp.nome, estoque[pos].nome); pos++);
		strcpy(pedido[pos].nome, temp.nome);
		pedido[pos].quantidade += temp.quantidade;

	}

	//confere o que está em falta
	for(int i = 0; i < *tamanho && estoque[i].quantidade > 0; i++)
		if (pedido[i].quantidade > estoque[i].quantidade)
			falha |= true;


	//processamento das informações
	
	if (falha)
	{
		for (int i = 0; i < *tamanho && pedido[i].quantidade > 0; i++)
		{
			if (pedido[i].quantidade > estoque[i].quantidade)
				cout << pedido[i].nome << ": Solicitado = " << pedido[i].quantidade << "kg / Em estoque = " << estoque[i].quantidade << "kg" << endl;
		}
	}
	else
	{
		float valordaCompra{};
		float desconto{};
		for (int i = 0; i < *tamanho && pedido[i].quantidade > 0; i++) {
			pedido[i].preco = estoque[i].preco * pedido[i].quantidade;
			valordaCompra += pedido[i].preco;
			estoque[i].quantidade -= pedido[i].quantidade;
		}

		if (valordaCompra >= 1000.0f) desconto = valordaCompra * 0.10f;


		//output do recibo
		ofstream fout;
		fout.open(strcat(nomedoArquivo, ".nfc"));
		fout.fill(' ');
		fout << "Pizzaria Mamute\n";
		linha(fout, '-', 50);
		for (int i = 0; i < 5; i++)
		{
			fout.width(10); 
			fout << left << pedido[i].nome;
			fout << pedido[i].quantidade;
			fout.width(5);
			fout << left << "kg";
			fout << "a   ";
			fout << fixed; fout.precision(2);
			fout << left << estoque[i].preco;
		
			int tamNum{};
			int temp = estoque[i].preco;
			while (temp / 10 != 0)
			{
				tamNum++;
				temp /= 10;
			}

			fout.width(8-tamNum);
			fout << left << "/kg";
			fout << "=   R$";
			fout << fixed; fout.precision(2);
			fout << pedido[i].preco;
			fout.precision(0);
			fout << endl;
		}

		linha(fout, '-', 50);


		fout.width(30); fout << right << "Compra";
		fout << "   =   R$";
		fout << fixed; fout.precision(2);
		fout << valordaCompra;
		fout << endl;

		fout.width(30); fout << right << "Desconto";
		fout << "   =   R$";
		fout << fixed; fout.precision(2);
		fout << desconto;
		fout << endl;

		fout.width(30); fout << right << "Total";
		fout << "   =   R$";
		fout << fixed; fout.precision(2); 
		fout << valordaCompra - desconto;
		fout << endl;

		fout.close();



		cout << "Recibo criado.\n";
		system("Pause");
	}
}

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
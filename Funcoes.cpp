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

void linha(char ch, unsigned char tam, ostream& os) {
	for (char i = 0; i < tam; i++)
		os << ch;
	os << endl;
}

produto* AumentarTamanhodeVetor(produto* vetor, char* tamanho)
{
	//define o novo vetor
	char novoTamanho = pow(2, log2f(*tamanho) + 1);
	produto* temp = new produto[novoTamanho]{};
	
	//copia os elementos do vetor antigo para o novo
	for (int i = 0; i <= *tamanho; i++)
		temp[i] = vetor[i];
	
	for (int j = *tamanho; j < novoTamanho; j++)
		temp[j] = {0, 0, 0};

	//aumenta a variavel do tamanho e retorna o novo vetor
	*tamanho = novoTamanho;
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

void Pedir(produto* estoque, char* tamanho)
{

	system("cls");
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
		cout << "Arquivo n�o encontrado! Tente novamente...";
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

	//entrada das informa��es
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


		//confere onde adicionar a quantidade no vetor din�mico
		int pos = 0;
		for(pos; strcmp(temp.nome, estoque[pos].nome); pos++);
		strcpy(pedido[pos].nome, temp.nome);
		pedido[pos].quantidade += temp.quantidade;

	}

	//confere o que est� em falta
	for(int i = 0; i < *tamanho && estoque[i].nome[0] != 0; i++)
		if (estoque[i].quantidade < pedido[i].quantidade)
			falha |= true;


	//processamento das informa��es
	
	if (falha)
	{
		for (int i = 0; i < *tamanho && estoque[i].nome[0] != 0; i++)
		{
			if (pedido[i].quantidade > estoque[i].quantidade)
				cout << pedido[i].nome << ": Solicitado = " << pedido[i].quantidade << "kg / Em estoque = " << estoque[i].quantidade << "kg" << endl;
		}
		system("Pause");
	}
	else
	{
		float valordaCompra{};
		float desconto{};
		for (int i = 0; i < *tamanho && estoque[i].nome[0] != 0; i++) {
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
		linha('-', 50, fout);
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

		linha( '-', 50, fout);


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

void Adicionar(produto*& lista, char* tamanho)
{
	system("cls");
	cout << "Adicionar\n";
	linha('-', 8);


	produto temp;
	cin >> temp;

	//formalizar o nome
	temp.nome[0] = toupper(temp.nome[0]);
	for(int i = 1; temp.nome[i] != 0; i++)
		temp.nome[i] = tolower(temp.nome[i]);

	//conta quantos elementos tem, e confere se j� tem algum identico
	int contador = 0;
	for (contador; (lista[contador].nome[0] != 0 && contador < *tamanho) && strcmp(temp.nome, lista[contador].nome); contador++);

	if(contador >= *tamanho) lista = AumentarTamanhodeVetor(lista, tamanho);

	strcpy(lista[contador].nome, temp.nome);
	lista[contador].preco = temp.preco;
	lista[contador].quantidade += temp.quantidade;

}

void Listar(produto* lista, char tamanho)
{
	system("cls");


	cout << "Listagem\n";
	linha('-', 8);
	
	for(int i = 0; i < tamanho && lista[i].nome[0] != 0; i++)
	{
		cout.width(10);
		cout << left << lista[i].nome;
		cout << " - R$";
		cout.width(5); cout << fixed; cout.precision(2);
		cout << left << lista[i].preco;
		cout << " - ";
		cout.width(3); cout << fixed; cout.precision(0);
		cout << right << lista[i].quantidade;
		cout << "kg";
		cout << endl;
	}

	cout << endl;
	system("Pause");
}

void Excluir(produto*& lista, char* tam)
{
	system("cls");

	int escolha;
	
	cout << "Excluir\n";
	linha('-', 8);

	//exibir os elementos
	for (int i = 0; i < *tam && lista[i].nome[0] != '\0'; i++)
		cout << i+1 << ") " << lista[i].nome << endl;
	
	cout << "N�mero do produto: ";

	//escolhe o elemento a ser retirado
	cin >> escolha;

	//move os elementos uma posi��o � esquerda
	int i = escolha - 1;
	for(i; i < *tam; i++)
	lista[i] = lista[i+1];

	//ultimo elemento nulo
	lista[i-1] = {0, 0, 0};
	
}
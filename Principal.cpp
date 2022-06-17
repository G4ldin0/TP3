#include "Funcoes.h"


int main()
{
	setlocale(LC_ALL, "portuguese");


	//leitura do arquivo de estoque
	ifstream fin;
	char TamEstoque = 2;
	produto* estoque = new produto[TamEstoque]{};
	fin.open("Estoque.bin", ios_base:: in | ios_base::binary);
	
	if(fin.is_open())
	{
		//numero de elementos no arquivo
		fin.read((char*)&TamEstoque, 1);
	
		//elementos no arquivo
	
		for(int i = 0; i < TamEstoque; i++)
		{
			for(int j = 0; j < 16; j++)
				fin.read((char*)&estoque[i].nome[j], 1);

			fin.read((char*)&estoque[i].preco, 4);
			fin.read((char*)&estoque[i].quantidade, 4);
			}
		fin.close();
	}
	else
	{
		cout << "Arquivo n�o encontrado, redirecionando para a cria��o de um novo.\n";
		system("Pause");
		Adicionar(estoque, &TamEstoque);
	}


	char EscolhaMenu{};
	while (EscolhaMenu != 'S')
	{

		//limpa tela do loop
		system("CLS");
		
		//display e navega��o do menu
		menu();
		cin >> EscolhaMenu;

		EscolhaMenu = toupper(EscolhaMenu);
		switch (EscolhaMenu)
		{
			
			case 'P':
			case 'p':
				Pedir(estoque,&TamEstoque);
			break;

			case 'A':
			case 'a':
				Adicionar(estoque, &TamEstoque);
			break;

			case 'E':
			case 'e':
				Excluir(estoque,&TamEstoque);
			break;

			case 'L':
			case 'l':
				Listar(estoque, TamEstoque);
			break;
			
			case 'S':
			case 's':
				cout << "Finalizando...\n";
			break;

			default:
				cout << endl << "Op��o inv�lida";
				system("Pause");
			break;
		}

	}
	
	//sobrescrever o arquivo bin�rio com as novas informa��es
	ofstream fout;
	fout.open("Estoque.bin", ios_base::binary | ios_base::out | ios_base::trunc);
	
	fout.write((char*)&TamEstoque, 1);

	for (int i = 0; i < TamEstoque; i++)
	{
		fout.write((char*)&estoque[i].nome, 16);
		fout.write((char*)&estoque[i].preco, 4);
		fout.write((char*)&estoque[i].quantidade, 4);
	}

	fout.close();
	delete[] estoque;
}

#include <iostream>
#include <fstream>
#include <locale.h>

using namespace std;

const char* dir_arq = "C:\\Users\\pfdsa\\OneDrive\\Área de Trabalho\\trab_base";
char nome_arq[255];

const int REGS = 100;

int codigo[REGS];
char descricao_prod[REGS][100];
int quantidade[REGS];
int preco[REGS];

int posicao = -1; 

void tratar_linha(char buffer[]) {
    posicao++;
    char* token;
    char* next_token = NULL;
    token = strtok_s(buffer, ";", &next_token);
    codigo[posicao] = atoi(token); 
    token = strtok_s(NULL, ";", &next_token);
    strcpy_s(descricao_prod[posicao], token);
    token = strtok_s(NULL, ";", &next_token);
    quantidade[posicao] = atoi(token);
    token = strtok_s(NULL, ";", &next_token);
    preco[posicao] = atoi(token);
}

void ler_arq() {
    posicao = -1;
    cout << "Nome do arquivo: ";
    cin >> nome_arq;
    char arq_entrada[255];
    strcpy_s(arq_entrada, dir_arq);
    strcat_s(arq_entrada, nome_arq);
    strcat_s(arq_entrada, ".csv");
    ifstream fin(arq_entrada);
    char linha[255];
    while (!fin.eof()) {
        if (fin >> linha) {
            tratar_linha(linha);
        }
    }
    fin.close();
}

void salvar_arq() {
    cout << "Nome do arquivo: ";
    cin >> nome_arq;
    char arq_saida[255];
    strcpy_s(arq_saida, dir_arq);
    strcat_s(arq_saida, nome_arq);
    strcat_s(arq_saida, ".csv");
    ofstream fout(arq_saida);
    for (int i = 0; i <= posicao; i++) {
        fout << codigo[i] << ";" << descricao_prod[i]
            << ";" << descricao_prod[i] << preco[i] << endl;
    }
    fout.flush();
    fout.close();
}

bool inserir() {
    if (posicao == (REGS - 1))
        return false;
    posicao++;
    cout << "Código: ";
    cin >> codigo[posicao];
    cout << "Nome: ";
    cin >> descricao_prod[posicao];
    cout << "Quantidade: ";
    cin >> quantidade[posicao];
    cout << "Preco: ";
    cin >> preco[posicao];
    return true;
}
/*-10s%-10s* , "Quantidade", "Preco"*/
void imprimir() {
    printf("%-10s%-20s%-10s%20s\n", "Codigo", "Nome", "Quantidade", "Preco");
    for (int i = 0; i <= posicao; i++)
        printf("%-10d%-20s%10d%20d\n",
            codigo[i], descricao_prod[i], quantidade[i], preco[i]);
}

int localizar(int cod_aux) {
    int pos_aux = -1;
    for (int i = 0; i <= posicao; i++) {
        if (codigo[i] == cod_aux) {
            pos_aux = i;
            break;
        }
    }
    return pos_aux;
}

void pesquisar() {
    cout << "Codigo do Produto: ";
    int cod_aux;
    cin >> cod_aux;
    int pos_vetor = localizar(cod_aux);
    if (pos_vetor == -1) {
        cout << "Nao encontrado!!!!" << endl;
    }
    else {
        printf("%-10s%-20s%-10s%20s\n", "Codigo", "Nome", "Quantidade", "Preco");
        printf("%-10d%-20s%10d%20d\n",
            codigo[pos_vetor], descricao_prod[pos_vetor], quantidade[pos_vetor], preco[pos_vetor]);
    }
}

void remover() {
    cout << "Código do Produto a ser REMOVIDO: ";
    int cod_aux;
    cin >> cod_aux;
    int pos_vetor = localizar(cod_aux);
    if (pos_vetor == -1) {
        cout << "Não encontrado!!!!" << endl;
    }
    else {
        for (int i = pos_vetor; i < posicao; i++) {
            codigo[i] = codigo[i + 1];
            strcpy_s(descricao_prod[i], descricao_prod[i + 1]);
            quantidade[i] = quantidade[i + 1];
            preco[i] = preco[i + 1];
        }
        posicao--;
    }
}

void alterar_cadastro() {

    char opc = 's';

    while (opc == 's') {

        cout << "Codigo do Produto a ser alterado: ";
        int cod_aux;
        cin >> cod_aux;
        int pos_vetor = localizar(cod_aux);



        if (pos_vetor == -1) {
            cout << "Nao encontrado!!!!" << endl;
        }
        else {
           cout << "Informe a quantidade: ";
           cin >> quantidade[pos_vetor];
            printf("Quantidade Atualizada % -10d\n",
               quantidade[pos_vetor]);
            cout << "Informe o valor: ";
            cin >> preco[pos_vetor];
            printf("Valor Atualizado % -10d\n",
                preco[pos_vetor]);
        }

        cout << "Deseja atualizar o cadastro de outro produto? [s/n]";
        cin >> opc;
    }
}

void trocar(int pos1, int pos2) {
    int cod_aux = codigo[pos1];
    char nome_aux[50];
    strcpy_s(nome_aux, descricao_prod[pos1]);
    int qtd_aux = quantidade[pos1];
    int pre_aux = preco[pos1];
    codigo[pos1] = codigo[pos2];
    strcpy_s(descricao_prod[pos1], descricao_prod[pos2]);
    quantidade[pos1] = quantidade[pos2];
    codigo[pos2] = cod_aux;
    strcpy_s(descricao_prod[pos2], nome_aux);
    preco[pos1] = preco[pos2];
    quantidade[pos2] = qtd_aux;
    strcpy_s(descricao_prod[pos2], nome_aux);
    preco[pos2] = pre_aux;
}

void ordenar_bubble_str() {
    bool ordenado;
    do {
        ordenado = true;
        for (int i = 0; i < posicao; i++) {
            if (strcmp(descricao_prod[i], descricao_prod[i + 1]) > 0) {
                trocar(i, i + 1);
                ordenado = false;
            }
        }
    } while (!ordenado);
}

void ordenar_bubble() {
    bool ordenado;
    do {
        ordenado = true;
        for (int i = 0; i < posicao; i++) {
            if (codigo[i] > codigo[i + 1]) {
                trocar(i, i + 1);
                ordenado = false;
            }
        }
    } while (!ordenado);
}

int menu() {
    cout << "1 - Ler Arquivo" << endl;
    cout << "2 - Grava Arquivo" << endl;
    cout << "3 - Inserir" << endl;
    cout << "4 - Imprimir" << endl;
    cout << "5 - Pesquisar" << endl;
    cout << "6 - Remover" << endl;
    cout << "7 - Alterar Cadastro" << endl;
    cout << "8 - Ordenar" << endl;
    cout << "0 - Sair" << endl;
    cout << "Sua opcao: ";
    int opcao;
    cin >> opcao;
    return opcao;
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    while ((opcao = menu()) != 0) {
        switch (opcao) {
        case 1:
            ler_arq(); break;
        case 2:
            salvar_arq(); break;
        case 3:
            inserir(); break;
        case 4:
            imprimir(); break;
        case 5:
            pesquisar(); break;
        case 6:
            remover(); break;
        case 7:
            alterar_cadastro(); break;
        case 8:
            ordenar_bubble(); break;

        }
        cout << endl;
    }
}



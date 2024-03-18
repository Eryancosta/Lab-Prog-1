//Cap Portes
//Al 

#include <iostream>

#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::ifstream;
using std::left;
using std::ofstream;
using std::right;
using std::setfill; // iomanip
using std::setprecision;
using std::setw; // iomanip
using std::string;
using std::vector;

// estruturas
typedef struct
{
    string cod;
    string nome;
    string cpf;
} ALUNO;

typedef struct
{
    string nome;
    string professor;
    string cod;
    string creditos;
} DISCIPLINA;

typedef struct
{
    ALUNO aluno;
    DISCIPLINA disciplina;
    float periodo;

} MATRICULA;

// variáveis globais
vector<ALUNO> alunos;
vector<DISCIPLINA> disciplinas;
vector<MATRICULA> matriculas;

void menu();
void inicializacao();
void inserir_aluno();      
void inserir_disciplina(); 
void consultar_disciplinas();
void consultar_alunos();
int validacao_cpf(string cpf);
void remover_aluno();
void remover_disciplina(); // implementar
void cadastro_em_disciplina();
void cadastro_aluno_disciplina();
void consultar_aluno_em_disciplina();
void consultar_dis_alu();
void listar_periodos();
void salvar();
void ordenacao(vector<float> &arr);
int unicidade(string cod);
void listar_periodos_al(string cod);
void listar_periodos_d(string cod);

// bloco principal
int main()
{
    int op, controle = 1;

    inicializacao();

    cout << "Aperte Enter para iniciar\n";
    while (controle)
    {

        cin.ignore();
        cout << "\n\t\tCADASTRO ESCOLAR\n";
        menu();

        cin >> op;

        switch (op)
        {
        case 1:
            cout << "\n\n\t1 - Inserir Aluno\n";
            inserir_aluno();
            break;
        case 2:
            cout << "\n\n\t2 - Inserir Disciplina\n";
            inserir_disciplina();
            break;
        case 3:
            cout << "\n\n\t3 - Remover Aluno\n";
            remover_aluno();
            break;
        case 4:
            cout << "\n\n\t4 - Remover Disciplina\n";
            remover_disciplina();
            break;

        case 5:
            cout << "\n\n\t5 - Cadastrar aluno em uma Disciplina\n";
            cadastro_aluno_disciplina();

            break;
        case 6:
            cout << "\n\n\t6 - Consultar Disciplina de um aluno\n";
            consultar_dis_alu();
            break;
        case 7:
            cout << "\n\n\t7 - Consultar alunos em uma Disciplina\n";
            consultar_aluno_em_disciplina();
            break;
        case 8:
            cout << "\t8 - Consultar Disciplinas cadastradas\n";
            consultar_disciplinas();
            break;
        case 9:
            cout << "\t9 - Consultar Alunos cadastrados\n";
            consultar_alunos();
            break;
        case 10:
            cout << "\t10 - Salvar\n";
            salvar();
            break;
        case 0:
            controle = 0;
            break;

        default:
            cout << ("\nOpcao invalida, Insira uma opcao valida");
            break;
        }
    }

    return 0;
}

// funções
void menu()
{
    cout << "\n\t\tMENU\n\n";
    cout << "\t1  - Inserir Aluno\n";
    cout << "\t2  - Inserir Disciplina\n";
    cout << "\t3  - Remover Aluno\n";
    cout << "\t4  - Remover Disciplina\n";
    cout << "\t5  - Cadastrar Aluno em um Disciplina\n";
    cout << "\t6  - Consultar Disciplina de um aluno\n";
    cout << "\t7  - Consultar alunos em uma Disciplina\n";
    cout << "\t8  - Consultar Disciplinas cadastradas\n";
    cout << "\t9  - Consultar Alunos cadastradas\n";
    cout << "\t10 - Salvar\n";
    cout << "\t0  - sair\n\n";
}

void inserir_aluno()
{
    ALUNO aluno;
    int c = 1;

    cin.ignore();
    do
    {
        cout << "\nInsira o codigo do aluno que deseja inserir (5 digitos)\n";
        getline(cin, aluno.cod);

        if (aluno.cod.length() == 5 && aluno.cod != "00000")
        {
            if (unicidade(aluno.cod))
            {
                c = 0;
            }
            else
                cout << "\nCodigo digitado ja cadastrado.\n";
            
            
        }
        else
            cout << "\n\nCODIGO INSERIDO INVALIDO\n";

    } while (c);
    c = 1;

    cout << "\nInsira o nome do aluno\n";
    getline(cin, aluno.nome);

    do // controle de cpf valido
    {
        cout << "\nInsira o CPF do Aluno, SOMENTE NUMEROS: ";
        getline(cin, aluno.cpf);

        if (validacao_cpf(aluno.cpf) || aluno.cpf == "00000000000")
            c = 0;

        else
            cout << "\n\nCPF INSERIDO INVALIDO, para sair digite 11 vezes o numero zero, ou digite o CPF novamente\n";

    } while (c);
    c = 1;

    if (aluno.cpf != "00000000000")
    {
        alunos.push_back(aluno);
        cout << "\nAluno cadastrado com sucesso.\n";
        salvar();
    }
}

int validacao_cpf(string cpf)
{
    // variaveis locais
    int i, v1 = 0, v2 = 0, soma = 0;
    vector<int> cpf_int;

    string copia;
    copia = cpf;

    for (i = 0; i < 11; i++)
    {
        cpf_int.push_back(copia[i] - 48);
    }
    for (i = 0; i < 9; i++)
    {
        soma += ((10 - i) * cpf_int[i]);
    }
    // verificação 1:
    soma = (soma * 10) % 11;
    if (soma == cpf_int[9] || (soma == 10 && cpf_int[9] == 0))
    {
        v1 = 1;
    }
    else
        return 0;

    // verificação 2:
    soma = 0;

    for (i = 0; i < 10; i++)
    {
        soma += (11 - i) * cpf_int[i];
    }
    soma = (soma * 10) % 11;

    if (soma == cpf_int[10] || (soma == 10 && cpf_int[10] == 0))
    {
        v2 = 1;
    }
    else
        return 0;

    if (v1 != 0 && v2 != 0)
        return 1;
    else

        return 0;
}

void inserir_disciplina()
{
    DISCIPLINA nova;
    int c = 1;

    cout << "\nInsira o nome da Disciplina: \n";
    cin.ignore();
    getline(cin, nova.nome);

    cout << "\nInsira o nome do professor: \n";
    getline(cin, nova.professor);

    do // controle de que sera inserido 5 caracteres no codigo
    {
        cout << "\nInsira o codigo da disciplina com 4 digitos: \n";
        getline(cin, nova.cod);
        if (nova.cod.length() == 4 && nova.cod != "0000")
        {
            if (unicidade(nova.cod))
            {
                c = 0;
                break;
            }
            else
                cout << "\nCodigo digitado ja cadastrado.\n";
        }
        else
            cout << "\n\nCODIGO INSERIDO INVALIDO\n";
    } while (c);
    cout << "\nInsira a quantidade de creditos\n";
    getline(cin, nova.creditos);

    disciplinas.push_back(nova);
    cout << "\n\nDisciplina cadastrada com sucesso";
    salvar();
}

void consultar_disciplinas()
{
    int i;

    if (disciplinas.size() == 0)
    {
        cout << "\nNao ha disciplinas cadastras\n";
    }
    else
    {
        cout << "\n\n\t\t      DISCIPLINAS";
        cout << "\n\t------------------------------------";
        for (i = 0; i <(int)  disciplinas.size(); i++)
        {
            cout << "\n\n\t----disciplina " << i + 1 << "----";
            cout << "\n\tNome: " << disciplinas[i].nome;
            cout << "\n\tCodigo: " << disciplinas[i].cod;
            cout << "\n\tProfessor: " << disciplinas[i].professor;
            cout << "\n\tCreditos: " << disciplinas[i].creditos;
        }
        cout << "\n\t------------------------------------\n";
    }
}

void consultar_alunos()
{
    int i;

    if (alunos.size() == 0)
    {
        cout << "\nNao ha alunos cadastras\n";
    }
    else
    {
        cout << "\n\n\t\t      ALUNOS";
        cout << "\n\t------------------------------------";
        for (i = 0; i <(int)  alunos.size(); i++)
        {
            cout << "\n\n\t----Aluno " << i + 1 << "----";
            cout << "\n\tNome: " << alunos[i].nome;
            cout << "\n\tCodigo: " << alunos[i].cod;
            cout << "\n\tCPF: " << alunos[i].cpf;
        }
        cout << "\n\t------------------------------------\n";
    }
}

void remover_aluno()
{
    string cod;
    int indice_remover_a = -1,indice_remover_m = -1, i, c = 1;

    do
    {
        consultar_alunos();
        cin.ignore();
        cout << "\nInsira o codigo do aluno que deseja remover: ";
        getline(cin, cod);
        for (i = 0; i <(int)  alunos.size(); i++)
        {
            if (cod == alunos[i].cod)
            {
                indice_remover_a = i;
            }
        }
        if (indice_remover_a != -1)
        {
            for (i = 0; i < (int)matriculas.size(); i++)
            {
                if (cod == matriculas[i].aluno.cod)
                {
                    indice_remover_m = i;
                    matriculas.erase(matriculas.begin() + indice_remover_m);
                }   
            } 

            cout << "\n\n\t----ALUNO REMOVIDO ----";
            cout << "\n\tNome: " << alunos[indice_remover_a].nome;
            cout << "\n\tCodigo: " << alunos[indice_remover_a].cod;
            cout << "\n\tCPF: " << alunos[indice_remover_a].cpf;
            alunos.erase(alunos.begin() + indice_remover_a);
            c = 0;
            salvar();
        }
        else
        {
            cout << "Codigo digitado nao encontrado, para re-inserir, digite 1 ou zero para voltar ao menu inicial: \n";
            cin >> c;
        }

    } while (c);
    
}

void remover_disciplina()
{
    string cod;
    int indice_remover_d = -1, indice_remover_m = -1, i, c = 1;

    do
    {
        consultar_disciplinas();
        cin.ignore();
        cout << "\nInsira o codigo da disciplina que deseja remover: ";
        getline(cin, cod);
        for (i = 0; i < (int) disciplinas.size(); i++)
        {
            if (cod == disciplinas[i].cod)
            {
                indice_remover_d = i;
            }
        }
        if (indice_remover_d != -1)
        {
            for (i = 0; i < (int)matriculas.size(); i++)
            {
                if (cod == matriculas[i].disciplina.cod)
                {
                    indice_remover_m = i;
                    matriculas.erase(matriculas.begin() + indice_remover_m);
                }   
            }  
            cout << "\n\n\t----DISCIPLINA REMOVIDA----";
            cout << "\n\tNome: " << disciplinas[indice_remover_d].nome;
            cout << "\n\tCodigo: " << disciplinas[indice_remover_d].cod;
            cout << "\n\tProfessor: " << disciplinas[indice_remover_d].professor;
            cout << "\n\tCreditos: " << disciplinas[indice_remover_d].creditos << "\n\n";
            disciplinas.erase(disciplinas.begin() + indice_remover_d);
            c = 0;
            salvar();
        }
        else
        {
            cout << "Codigo digitado nao encontrado, para re-inserir, digite 1 ou zero para voltar ao menu inicial";
            cin >> c;
        }

    } while (c);
}

void cadastro_aluno_disciplina()
{
    // ano atual
    std::time_t now = std::time(nullptr);
    std::tm *local_time = std::localtime(&now);
    int ano_atual = local_time->tm_year + 1900;

    string cod_dis, cod_al;
    MATRICULA novo;
    int c = 1, i, i_dis = -1, i_al = -1;

    // verificação se há disciplinas e alunos a serem cadastrados
    if (disciplinas.size() == 0)
    {
        printf("Nao ha disciplinas cadastradas.\n");
    }
    else if (alunos.size() == 0)
    {
        printf("Nao ha alunos cadastrados.\n");
    }
    else
    {

        // solicitação do periodo que será cadastrado
        do
        {

            
            cout << "\n\nInsira em que periodo deseja cadastrar, (Ex: 2024.1)\n\n";
            cin.ignore();
            cin >> novo.periodo;

            // verificação se o periodo é válido
            if (novo.periodo > 1900 && novo.periodo <= (float)ano_atual + 0.2)
            {
                c = 0;
            }
            else
                cout << "\nPERIODO DIGITADO INVALIDO.\n";

        } while (c);
        c = 1;

        do
        {
            cin.ignore();
            consultar_disciplinas();
            cout << "Insira o codigo da disciplina que deseja cadastrar o aluno\n";
            getline(cin, cod_dis);

            // verificação do codigo valido
            for (i = 0; i <(int)  disciplinas.size(); i++)
            {
                if (cod_dis == disciplinas[i].cod)
                {
                    i_dis = i;
                    c = 0;
                }
            }

            if (i_dis == -1)
            {
                cout << "Codigo digitado nao encontrado.\n";
            }
        } while (c);
        c = 1;

        do
        {
            cin.ignore();
            consultar_alunos();
            cout << "Insira o codigo do aluno que deseja cadastrar\n";
            getline(cin, cod_al);

            for (i = 0; i <(int)  alunos.size(); i++)
            {
                if (cod_al == alunos[i].cod)
                {
                    i_al = i;
                    c = 0;
                }
            }

            if (i_al == -1)
            {
                cout << "Codigo digitado nao encontrado.\n";
            }
        } while (c);

        if (i_al != -1 && i_dis != -1)
        {
            novo.aluno = alunos[i_al];
            novo.disciplina = disciplinas[i_dis];

            bool matricula_existe = false;

            for (i = 0; i <(int)  matriculas.size(); i++)
            {
                if (matriculas[i].aluno.cod == cod_al && matriculas[i].disciplina.cod == cod_dis && matriculas[i].periodo == novo.periodo)
                {
                    matricula_existe = true;
                    break;
                }
            }

            if (matricula_existe)
            {
                cout << "\n\nALUNO JA CADASTRO NESSA DISCIPLINA NESSE PERIODO.\n";
            }
            else
            {
                matriculas.push_back(novo);
                cout << "\n\nALUNO CADASTRADO COM SUCESSO.";
                salvar();
            }
        }
        else
            cout << "\n\nCODIGO DIGITADO ERRADO.";
    }
}

void consultar_dis_alu()
{
    // ano atual
    std::time_t now = std::time(nullptr);
    std::tm *local_time = std::localtime(&now);
    int ano_atual = local_time->tm_year + 1900;

    string cod_dis, cod_al;
    float periodo;
    int c = 1, i, i_al = -1, sem_cadastro = 0;

    // verificação se há disciplinas e alunos a serem cadastrados
    if (matriculas.size() == 0)
    {
        printf("Nao ha matriculas.\n");
    }
    else
    {
        cin.ignore();
        consultar_alunos();
        do
        {
            cout << "Insira o codigo do aluno que deseja consultar\n";
            getline(cin, cod_al);

            for (i = 0; i <(int)  alunos.size(); i++)
            {
                if (cod_al == alunos[i].cod)
                {
                    c = 0;
                    i_al = i;
                }
            }

            if (i_al == -1)
            {
                cout << "Codigo digitado nao encontrado.\n";
            }

        } while (c);
        c = 1;
        do
        {
            listar_periodos_al(cod_al);
            cin.ignore();
            cout << "\nInsira o periodo (Ex. 2022.2) que deseja consultar\n\n";
            cin >> periodo;

            if (periodo > 1900 && periodo <= (float)ano_atual + 0.2)
            {
                c = 0;
            }
            else
                cout << "\nPERIODO DIGITADO INVALIDO.\n";
        } while (c);

        cout << left << setfill('_') << setw(25) << "" << endl;
        cout << "Disciplinas de: " << alunos[i_al].nome
             << "\nPeriodo: " << fixed << setprecision(1) << periodo << endl;
        cout << left << setfill('-') << setw(25) << "" << endl;
        cout << "DISCIPLINAS\n\n";

        int contador = 1;
        for (i = 0; i <(int)  matriculas.size(); i++)
        {
            if (cod_al == matriculas[i].aluno.cod && periodo == matriculas[i].periodo)
            {
                cout << contador << ". " << matriculas[i].disciplina.nome << "\n";
                sem_cadastro++;
                contador++;
            }
        }
        cout << left << setfill('-') << setw(25) << "" << endl;

        if (sem_cadastro == 0)
        {
            cout << "\n\tSEM DISCIPLINA CADASTRADA\n";
        }
    }
}

void consultar_aluno_em_disciplina()
{
    string cod_dis;

    int c = 1, i, i_dis = -1;
    bool sem_alu = true;

    float periodo;

    // ano atual
    std::time_t now = std::time(nullptr);
    std::tm *local_time = std::localtime(&now);
    int ano_atual = local_time->tm_year + 1900;

    // verificação se há disciplinas e alunos a serem cadastrados
    if (matriculas.size() == 0)
    {
        printf("Nao ha matriculas.\n");
    }
    else
    {
        cin.ignore();
        consultar_disciplinas();
        do
        {
            cout << "Insira o codigo da disciplina que deseja consultar\n";
            getline(cin, cod_dis);

            for (i = 0; i < (int) disciplinas.size(); i++)
            {
                if (cod_dis == disciplinas[i].cod)
                {
                    c = 0;
                    i_dis = i;
                }
            }

            if (i_dis == -1)
            {
                cout << "Codigo digitado nao encontrado.\n";
            }

        } while (c);

        c = 1;

        do
        {
            listar_periodos_d(cod_dis);
            cin.ignore();
            cout << "Insira o periodo (Ex. 2022.2) que deseja consultar\n";
            cin >> periodo;

            if (periodo > 1900 && periodo <= (float)ano_atual + 0.2)
            {
                c = 0;
            }
            else
                cout << "\nPERIODO DIGITADO INVALIDO.\n";
        } while (c);

        cout << left << setfill('_') << setw(25) << "" << endl;
        cout << "Alunos de: " << disciplinas[i_dis].nome << endl;
        cout << "Periodo: " << fixed << setprecision(1) << periodo << endl;
        cout << left << setfill('-') << setw(25) << "" << endl;
        cout << "ALUNOS\n\n";

        int contador = 1;
        for (i = 0; i < (int) matriculas.size(); i++)
        {
            if (cod_dis == matriculas[i].disciplina.cod && periodo == matriculas[i].periodo)
            {
                cout << contador << "." << matriculas[i].aluno.nome << "\n";
                sem_alu = false;
                contador++;
            }
        }

        if (sem_alu)
        {
            cout << "\nDISCIPLINA SEM ALUNOS\n";
        }
    }
}

void salvar()
{
    int i;

    ofstream arquivo("Dados.txt"); // abertura de arquivo para escrita
    arquivo << "Alunos Cadastrados:\n";

    for (i = 0; i < (int) alunos.size(); i++)
    {
        arquivo << alunos[i].cod << "\n"
                << alunos[i].nome << "\n"
                << alunos[i].cpf << "\n";
    }

    arquivo << "Disciplinas Cadastradas:\n";
    for (i = 0; i <(int)  disciplinas.size(); i++)
    {

        arquivo << disciplinas[i].cod << "\n"
                << disciplinas[i].nome << "\n"
                << disciplinas[i].professor << "\n"
                << disciplinas[i].creditos << "\n";
    }

    arquivo << "Matriculas feitas:\n";
    for (i = 0; i <(int)  matriculas.size(); i++)
    {

        arquivo << matriculas[i].aluno.cod << "\n"
                << matriculas[i].aluno.nome << "\n"
                << matriculas[i].aluno.cpf << "\n";
        arquivo << matriculas[i].disciplina.cod << "\n"
                << matriculas[i].disciplina.nome << "\n"
                << matriculas[i].disciplina.professor << "\n"
                << matriculas[i].disciplina.creditos << "\n";
        arquivo << matriculas[i].periodo << "\n";
    }
    cout << "\nDados Salvos com sucesso.\n";
    arquivo.close(); // fechamento do arquivo
}

void inicializacao()
{
    ifstream arquivo("Dados.txt"); // abertura de arquivo para leitura
    ALUNO novo_al;
    DISCIPLINA novo_dis;
    MATRICULA novo_mat;

    if (!arquivo.is_open())
    {
        cout << "\nNAO FOI POSSIVEL INICIALIZAR OS DADOS\n\n";
        return;
    }

    string linha;
    while (getline(arquivo, linha)) // lendo o arquivo armazenando uma string
    {
        while (getline(arquivo, linha) && linha != "Disciplinas Cadastradas:")
        {
            novo_al.cod = linha;
            getline(arquivo, linha);
            novo_al.nome = linha;
            getline(arquivo, linha);
            novo_al.cpf = linha;

            alunos.push_back(novo_al);
        }

        while (getline(arquivo, linha) && linha != "Matriculas feitas:")
        {
            novo_dis.cod = linha;
            getline(arquivo, linha);
            novo_dis.nome = linha;
            getline(arquivo, linha);
            novo_dis.professor = linha;
            getline(arquivo, linha);
            novo_dis.creditos = linha;

            disciplinas.push_back(novo_dis);
        }

        if (arquivo.eof())
        {

            cout << "Nao ha alunos matriculados\n\n";
        }
        while (getline(arquivo, linha))
        {
            novo_mat.aluno.cod = linha;
            getline(arquivo, linha);
            novo_mat.aluno.nome = linha;
            getline(arquivo, linha);
            novo_mat.aluno.cpf = linha;
            getline(arquivo, linha);
            novo_mat.disciplina.cod = linha;
            getline(arquivo, linha);
            novo_mat.disciplina.nome = linha;
            getline(arquivo, linha);
            novo_mat.disciplina.professor = linha;
            getline(arquivo, linha);
            novo_mat.disciplina.creditos = linha;
            getline(arquivo, linha);
            novo_mat.periodo = stof(linha); // stof tranforma string e float

            matriculas.push_back(novo_mat);
        }
    }

    cout << "\nCarregamento de dados realizado com sucesso.\n";
    arquivo.close();
}

void listar_periodos()
{
    int i, j;
    vector<float> temp;
    bool n_existe = false;

    for (i = 0; i < (int) matriculas.size(); i++)
    {
        if (temp.size() == 0)
        {
            temp.push_back(matriculas[i].periodo);
        }
        else
        {
            n_existe = true;

            for (j = 0; j < (int) temp.size(); j++)
            {
                if (matriculas[i].periodo == temp[j])
                {
                    n_existe = false;
                }
            }
            if (n_existe)
            {
                temp.push_back(matriculas[i].periodo);
            }
        }
    }

    ordenacao(temp);
    cout << "\n\nPERIODOS CADASTRADOS\n";
    for (i = 0; i < (int) temp.size(); i++)
    {
        cout << "\n"
             << temp[i];
    }
    cout << "\n";
}

void ordenacao(vector<float> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                float temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int unicidade(string cod)
{
    int i;
    bool unico = true;

    if (cod.length() == 4) //verificação de unicidade de codigo de disciplina
    {
        for (i = 0; i < (int) disciplinas.size(); i++)
        {
            if (cod == disciplinas[i].cod)
            {
                unico = false;
                break;
            }
            
        }
        
    }
    else if (cod.length() == 5)//verificação de unicidade de codigo de aluno
    {
        for (i = 0; i < (int) alunos.size(); i++)
        {
            if (cod == alunos[i].cod)
            {
                unico = false;
                break;
            }   
        }
    }

    if (unico)
    {
        return 1;
    }
    else
        return 0;   
}

void listar_periodos_al(string cod)
{
    int i, j;
    vector<float> temp;
    bool n_existe = false;

    for (i = 0; i < (int) matriculas.size(); i++)
    {
        if (temp.size() == 0)
        {
            temp.push_back(matriculas[i].periodo);
        }
        else
        {
            n_existe = true;

            for (j = 0; j < (int) temp.size(); j++)
            {
                if (matriculas[i].periodo == temp[j])
                {
                    n_existe = false;
                }
            }
            if (n_existe && cod == matriculas[i].aluno.cod)
            {
                temp.push_back(matriculas[i].periodo);
            }
        }
    }

    ordenacao(temp);
    cout << "\n\nPERIODOS CADASTRADOS\n";
    for (i = 0; i < (int) temp.size(); i++)
    {
        cout << "\n"
             << temp[i];
    }
    cout << "\n";
}

void listar_periodos_d(string cod)
{
    int i, j;
    vector<float> temp;
    bool n_existe = false;

    for (i = 0; i < (int) matriculas.size(); i++)
    {
        if (temp.size() == 0)
        {
            temp.push_back(matriculas[i].periodo);
        }
        else
        {
            n_existe = true;

            for (j = 0; j < (int) temp.size(); j++)
            {
                if (matriculas[i].periodo == temp[j])
                {
                    n_existe = false;
                }
            }
            if (n_existe && cod == matriculas[i].disciplina.cod)
            {
                temp.push_back(matriculas[i].periodo);
            }
        }
    }

    ordenacao(temp);
    cout << "\n\nPERIODOS CADASTRADOS\n";
    for (i = 0; i < (int) temp.size(); i++)
    {
        cout << "\n"
             << temp[i];
    }
    cout << "\n";
}
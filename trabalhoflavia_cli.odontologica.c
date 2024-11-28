#include <stdio.h>
#include <stdlib.h>         					// sistema criado para gerenciamento de uma clinica odontologica
#include <string.h>

typedef struct {
    char nome[100];
    int idade;
    char telefone[15];   						// estrutura de identificaçao do paciente 		

typedef struct {
    Paciente pacientes[100];                              // estrutura para quantidade de cadastros da clinica
    int numPacientes;             // controle de registros dos pacientes               
    const int maximoPacientes;   // quantidade maxima de pacientes na clinica 
} Clinica;/ 
} Paciente;

void inicializarClinica(Clinica *clinica) {
    clinica->numPacientes = 0;      // começa com 0, pois nao ha pacientes cadastrados
    *(int *)&(clinica->maximoPacientes) = 100;
}

void mostrarMenu() {
    printf("\n==== CLINICA ODONTOLOGICA ====\n");
    printf("1. Cadastro\n");
    printf("2. Consulta\n");
    printf("3. Gerar Relatorio\n");                           // menu de opçoes
    printf("4. Excluir\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao: ");                                
}

void cadastrarPaciente(Clinica *clinica) {
    if (clinica->numPacientes >= clinica->maximoPacientes) {         //confere se o numero de pacintes atingiu o limite 
        printf("Limite de pacientes atingido!\n");
        return;
    }
    
    Paciente novoPaciente;
    printf("\nCadastro de Paciente:\n");
    printf("Nome: ");
    getchar(); 
    fgets(novoPaciente.nome, 100, stdin);
    novoPaciente.nome[strcspn(novoPaciente.nome, "\n")] = 0; 
    printf("Idade: ");
    scanf("%d", &novoPaciente.idade);
    
    printf("Telefone: ");
    getchar(); 
    fgets(novoPaciente.telefone, 15, stdin);
    novoPaciente.telefone[strcspn(novoPaciente.telefone, "\n")] = 0; 
    clinica->pacientes[clinica->numPacientes] = novoPaciente;
    clinica->numPacientes++;
    printf("Paciente cadastrado com sucesso!\n");
}

void consultarPaciente(Clinica *clinica) {
    char nomeConsulta[100];
    printf("\nConsulta de Paciente:\n");
    printf("Digite o nome do paciente: ");
    getchar(); // Limpa o buffer do teclado
    fgets(nomeConsulta, 100, stdin);
    nomeConsulta[strcspn(nomeConsulta, "\n")] = 0;
    
    int encontrado = 0;
    for (int i = 0; i < clinica->numPacientes; i++) {
        if (strcmp(clinica->pacientes[i].nome, nomeConsulta) == 0) {
            printf("\nPaciente encontrado:\n");
            printf("Nome: %s\n", clinica->pacientes[i].nome);
            printf("Idade: %d\n", clinica->pacientes[i].idade);
            printf("Telefone: %s\n", clinica->pacientes[i].telefone);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Paciente nao encontrado.\n");
    }
}

void gerarRelatorio(Clinica *clinica) {
    if (clinica->numPacientes == 0) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    printf("\nRelatorio de Pacientes:\n");
    for (int i = 0; i < clinica->numPacientes; i++) {
        printf("\nPaciente %d:\n", i + 1);
        printf("Nome: %s\n", clinica->pacientes[i].nome);
        printf("Idade: %d\n", clinica->pacientes[i].idade);
        printf("Telefone: %s\n", clinica->pacientes[i].telefone);
    }
}

void excluirPaciente(Clinica *clinica) {
    char nomeExcluir[100];
    printf("\nExcluir Paciente:\n");
    printf("Digite o nome do paciente para excluir: ");
    getchar(); 
    fgets(nomeExcluir, 100, stdin);
    nomeExcluir[strcspn(nomeExcluir, "\n")] = 0; 
    
    int encontrado = 0;
    for (int i = 0; i < clinica->numPacientes; i++) {
        if (strcmp(clinica->pacientes[i].nome, nomeExcluir) == 0) {
            for (int j = i; j < clinica->numPacientes - 1; j++) {
                clinica->pacientes[j] = clinica->pacientes[j + 1];
            }
            clinica->numPacientes--; 
            printf("Paciente excluido com sucesso!\n");
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Paciente nao encontrado.\n");
    }
}

int main() {
    Clinica clinica;
    inicializarClinica(&clinica); 
    int opcao;

    do {
        mostrarMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarPaciente(&clinica);
                break;
            case 2:
                consultarPaciente(&clinica);
                break;
            case 3:
                gerarRelatorio(&clinica);
                break;
            case 4:
                excluirPaciente(&clinica);
                break;
            case 5:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 5);

    return 0;
}
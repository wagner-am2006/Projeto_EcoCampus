#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50

int main() {
    FILE *arquivo_entrada = fopen("consumo_campus.txt", "r");
    if (arquivo_entrada == NULL) {
        printf("Erro ao abrir o arquivo consumo_campus.txt!\n");
        return 1;
    }

    FILE *arquivo_saida = fopen("relatorio_consumo.txt", "w");
    if (arquivo_saida == NULL) {
        printf("Erro ao criar o arquivo relatorio_consumo.txt!\n");
        fclose(arquivo_entrada);
        return 1;
    }

    char nome_local[MAX_NOME];
    float consumo, limite;

    int total_locais = 0;
    float consumo_total = 0.0;
    float maior_consumo = -1.0;
    char local_maior[MAX_NOME] = "";
    int locais_alerta = 0;

    while (fscanf(arquivo_entrada, "%s %f %f", nome_local, &consumo, &limite) == 3) {
        total_locais++;
        consumo_total += consumo;

        if (total_locais == 1 || consumo > maior_consumo) {
            maior_consumo = consumo;
            strcpy(local_maior, nome_local);
        }

        if (consumo > limite) {
            locais_alerta++;
        }
    }

    float consumo_medio = (total_locais > 0) ? (consumo_total / total_locais) : 0.0;

    printf("--- ECOCAMPUS ---\n");
    printf("Locais analisados: %d\n", total_locais);
    printf("Consumo total: %.2f litros\n", consumo_total);
    printf("Consumo medio: %.2f litros\n", consumo_medio);
    printf("Maior consumo: %s (%.2f litros)\n", local_maior, maior_consumo);
    printf("Locais em alerta: %d\n", locais_alerta);

    fprintf(arquivo_saida, "--- ECOCAMPUS ---\n");
    fprintf(arquivo_saida, "Locais analisados: %d\n", total_locais);
    fprintf(arquivo_saida, "Consumo total: %.2f litros\n", consumo_total);
    fprintf(arquivo_saida, "Consumo medio: %.2f litros\n", consumo_medio);
    fprintf(arquivo_saida, "Maior consumo: %s (%.2f litros)\n", local_maior, maior_consumo);
    fprintf(arquivo_saida, "Locais em alerta: %d\n", locais_alerta);

    fclose(arquivo_entrada);
    fclose(arquivo_saida);

    printf("\nRelatorio gerado com sucesso em 'relatorio_consumo.txt'!\n");

    return 0;
}
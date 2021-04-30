#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


/**
 * Função que verifica se os valores recebidos pelo ficheiro txt são parametros válidos para a normal execução do
 * programa.
 *
 * @param inputFile file
 * @return true se os os valores recebidos pelo ficheiro txt são parametros válidos, otherwise false.
 */
bool acceptValues(char *inputFile);

/**
 * Atualiza o sistema (data) com todos os parametros que são passados pelo ficheiro inputFile.
 *
 * @param inputFile  file
 * @param data data main
 */
void getInfo(char *inputFile, struct main_data * data);






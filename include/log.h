#ifndef SOVACCINES_LOG_H
#define SOVACCINES_LOG_H

/**
 * Devolve um apontador para o ficheiro cujo o path é dado no name.
 *
 * @param name name file
 * @return  apontador para o ficheiro cujo o path é dado no name
 */
FILE * openLogFile(char * name);

/**
 * Registar a ação (op, read, stop, help)  que o sistema fez bem como a data que foi realizada.
 *
 * @param fp file
 * @param input nome da ação
 */
void registaLog( FILE * fp, char * input);

/**
 * Fecha a leitura/escrita no ficheiro.
 *
 * @param fp file
 */
void closeLogFile(FILE * fp);


#endif //SOVACCINES_LOG_H

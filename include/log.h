

#ifndef SOVACCINES_LOG_H
#define SOVACCINES_LOG_H


FILE * openLogFile(char * name);

void registaLog( FILE * fp, char * input);

void closeLogFile(FILE * fp);


#endif //SOVACCINES_LOG_H

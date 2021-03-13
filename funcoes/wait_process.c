
/* Função que espera que um processo termine através da função waitpid. 
* Devolve o retorno do processo, se este tiver terminado normalmente.
*/
int wait_process(int process_id){
    int status;
    waitpid(process_id, &status );
    
    if(status == -1 ){
        //erro + exit
    }

    return satus;
}
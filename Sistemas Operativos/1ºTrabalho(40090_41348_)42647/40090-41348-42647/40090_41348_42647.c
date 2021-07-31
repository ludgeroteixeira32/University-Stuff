#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define QUANTUM 3
#define MAX_processos 10
#define MAX_PROGRAM_SIZE 10
#define PC_CYCLES(P) P -> programa.ciclos[P->programa.pc]  // ciclo executado no pc do programa
#define NUM_PROCESSOS 5

//programa, tem um array de ciclos (vem do input) e um program counter
typedef struct
{   
    int ciclos [MAX_PROGRAM_SIZE];
    int pc;
    
}Programa;

//estados
enum STATE
{
    NEW,
    READY,
    RUNNING,
    BLOCKED,
    EXIT,
    NONE,
    AUX,
};

//processo, contem um programa um estado e conta os ciclos que já fez
typedef struct
{   
    Programa programa;
    enum STATE state;
    int ciclosDecorridos;
}Processo;

//Queue já com o processo como type
typedef struct
{
    Processo* data[MAX_processos];
    int front;
    int size;
    int tail;
    
}Queue;

//struct que simula o sistema operativo, leva todos os processos e queues e será executado na main
typedef struct
{
    Processo* processos[MAX_processos];
    int ciclos;
    int numeroDeProcessos;
    Processo* runningProcess;
    Queue* readyQueue;
    Queue* blockedQueue;
    Queue* auxQueue;
    
}OS;


//constructor da queue
Queue* createQueue()
{
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    for(int i =0; i< MAX_processos; i++ ){

        queue ->data[i] = NULL;
    }
    queue -> front = 0;
    queue -> tail = 0;
    queue -> size = 0;
    return queue;
}

//mêtodos da queue
void enqueue(Queue* queue, Processo* processo){
    queue -> data[queue->tail] = processo;
    queue -> size++;
    queue ->tail = (queue->tail +1) % MAX_processos;
}

//"ver" o primeiro elemento da queue sem o tirar de lá
Processo* peek(Queue* queue){
    return queue -> data[queue->front];
}

//remove um elemento da queue
void dequeue(Queue* queue){
    queue -> data[queue->front] = NULL;
    queue -> size--;
    queue ->front = (queue->front + 1) % MAX_processos;

}
//constructo do processo
Processo* criarProcesso(Programa programa){
    Processo* processo = (Processo*) malloc(sizeof(Processo));
    processo -> programa = programa;
    processo -> state = NONE;
    processo -> ciclosDecorridos = 0;
    return processo;

}
//constructor do sistema operativo
OS* createOS(){
    OS* os = (OS*) malloc(sizeof(OS));
    for(int i=0; i < MAX_processos; i++){
        os -> processos[i] = NULL;
    }
    os -> numeroDeProcessos = 0;
    os -> ciclos = 0;
    os -> runningProcess = NULL;
    os -> readyQueue = createQueue();
    os -> blockedQueue = createQueue();
    os -> auxQueue = createQueue();
    return os;
}

// aqui processamos o input colocando logo os valores dados dentro do array de ciclos do programa,
// cada linha corresponde a um processo
void InputProgramas(OS* os)
{
    int programas[5][10] = {

    {0, 3, 1, 2, 2, 4, 1, 1, 1, 1 } ,
    {1, 2, 4, 2, 4, 2, 0, 0, 0, 0 } ,
    {3, 1, 6, 1, 6, 1, 6, 1, 0, 0 } ,
    {3, 6, 1, 6, 1, 6, 1, 6, 0, 0 } ,
    {5, 9, 1, 9, 0, 0, 0, 0, 0, 0 } 
    };
    for (int i =0; i<NUM_PROCESSOS; i++ ){
        Programa programa;
        programa.pc = 0;
        for(int j=0; j<MAX_PROGRAM_SIZE; j++){
            programa.ciclos[j] = programas[i][j];

        }
        // cria um processo a partir de cada linha do input,
        // cada elemento da linha corresponde ao tempo que passa em running e em blocked
        os -> processos[os -> numeroDeProcessos++] = criarProcesso(programa);
    }
}
//print do estado dos processos a cada instante
void printEstado(OS* os){
    printf("    %02d    ", os -> ciclos);
    for(int i =0; i < os->numeroDeProcessos; i++){
        Processo* processo = os-> processos[i];
        switch(processo->state){

            case NONE:
                printf("      ");
                break;

            case NEW:
                printf("NEW     ");
                break;

            case READY:
                printf("READY   ");
                break;
            
            case RUNNING:
                printf("RUN     ");
                break;
            
            case BLOCKED:
                printf("BLCK    ");
                break;

            case AUX:
                printf("AUX     ");
                break;

            case EXIT:
                if(processo->ciclosDecorridos <= 1){
                    printf("EXIT    ");
                }else{
         
                   printf("         ");
                }
                break;
       
        }       
    }
    printf("\n");
}
//corre o OS com escalonamento Round Robin
void round_robin(OS* os){
    bool correrProcesso = true;
    while(correrProcesso){

        for(int i = 0; i<os -> numeroDeProcessos; i++){
            Processo* processo = os->processos[i];
            // itera sobre os processos e caso algum ainda não tenha sido inicializado (NONE)
            // então inicia o processo no estado new(NEW) e avança o PC
            if(processo -> state == NONE && os -> ciclos == PC_CYCLES(processo)){
                processo -> state = NEW;
                processo -> programa.pc++;
            }
        }
        for(int i = 0; i < os -> numeroDeProcessos; i++){
            Processo* processo = os-> processos[i];
            // itera sobre os processos caso encontre algum no estado exit 
            if(processo->state == EXIT){
                processo->ciclosDecorridos++;
            }
        }

        //se a blockedQueue não estiver vazia
        if(os->blockedQueue->size > 0){
            Processo* processo = peek(os -> blockedQueue);  
            
            //caso o processo já tenha realizado todos os ciclos no Blocked
            //o mesmo passa para o estado "READY"
            if(processo->ciclosDecorridos == PC_CYCLES(processo)){
                dequeue(os->blockedQueue);
                enqueue(os->readyQueue, processo);
                processo->state = READY;
                processo->ciclosDecorridos =0;
                processo->programa.pc++;

            }
            else{
                processo -> ciclosDecorridos++;
            }
        }

        //Se existe um processo a "correr"
        if(os->runningProcess != NULL){

            // caso já não faltem ciclos de execução no processo (antes de passar para blocked)
            if(os->runningProcess -> ciclosDecorridos == PC_CYCLES(os->runningProcess)){

                os->runningProcess->programa.pc++;

                //caso o processo já tenha corrido todos o numero maximo de ciclos, sai para o EXIT
                if(os -> runningProcess -> programa.pc == MAX_PROGRAM_SIZE){
                    os->runningProcess->state = EXIT;
            
                //os processos quando terminam, passam do OS (estado RUNNING) para o EXIT, onde permanecem 1 instante de tempo.
                }else if(PC_CYCLES(os->runningProcess) == 0){  

                os->runningProcess->state = EXIT;        
                os->runningProcess->ciclosDecorridos = 1;
            }
            else{
                //o processo vai para o estado "BLOCKED", caso ainda não tenha terminado todos os seus ciclos
                enqueue(os->blockedQueue, os->runningProcess);
                os-> runningProcess->state = BLOCKED;
                os->runningProcess->ciclosDecorridos = 1;

            }
            //não existe nenhum processo em execuçao
            os->runningProcess = NULL;
            }
            //o processo após correr QUANTUM vezes, volta para a fila ready e passa para o estado "READY"
            else if(os->runningProcess->ciclosDecorridos % QUANTUM == 0){

                enqueue(os->readyQueue, os->runningProcess);
                os->runningProcess->state = READY;
                os->runningProcess = NULL;
            }
            else{
                os->runningProcess->ciclosDecorridos++;
            }
        }
        for(int i =0; i<os->numeroDeProcessos; i++){
            Processo* processo = os->processos[i];
            // todos processos no estado "NEW", após 1 ciclo
            // passam para "READY" e são adicionados à fila correcta
            if(processo->state == NEW && processo->ciclosDecorridos == 1){

                enqueue(os->readyQueue, processo);
                processo->state = READY;
                processo->ciclosDecorridos =0;

            }
            else if(processo->state == NEW){
                processo->ciclosDecorridos++;

            }
        }
        //por fim, atualiza o processo a correr
        // removendo o primeiro da fila READY
       if(os->readyQueue->size >0 && os->runningProcess == NULL){
            os->runningProcess = peek(os->readyQueue);
            dequeue(os->readyQueue);
            os->runningProcess->state = RUNNING;
            os->runningProcess-> ciclosDecorridos++;
        }
        os->ciclos++;
        printEstado(os);
        correrProcesso = false;
        //caso ainda existam processos por ser executados, continua o programa,
        //caso contrário nega o atributo correrProcesso para terminarmos o programa
        for( int i=0; i < os->numeroDeProcessos; i++){
            Processo* processo = os -> processos[i];
            if(processo->state != EXIT || processo-> ciclosDecorridos < 1){
                correrProcesso = true;
                break; 
            }

        }
        
    }
   
}
// corre o os com o escalonamento Virtual Round Robin
// a maior parte deste escalonamento funciona de forma semelhante ao Round Robin
// a unica diferença é que vamos preferir sempre remover da fila AUX antes da READY
void virtual_round_robin(OS* os){
    bool correrProcesso = true;
    while(correrProcesso){
        for(int i = 0; i<os -> numeroDeProcessos; i++){
            Processo* processo = os->processos[i];
            //passa os processo criados para new
            if(processo -> state == NONE && os -> ciclos == PC_CYCLES(processo)){
                processo -> state = NEW;
                processo -> programa.pc++;
            }
        }
        for(int i = 0; i< os -> numeroDeProcessos; i++){
            Processo* processo = os-> processos[i];

            if(processo->state == EXIT){
                processo->ciclosDecorridos++;
            }
        }
        if(os->blockedQueue->size > 0){
            Processo* processo = peek(os -> blockedQueue);
            // semelhante ao RR mas aqui em vez de tirarmos um processo da fila de blocked
            // para fila ready, tiramos para a fila auxiliar
            if(processo->ciclosDecorridos == PC_CYCLES(processo)){
                dequeue(os->blockedQueue);
                enqueue(os->auxQueue, processo);
                processo->state = AUX;
                processo->ciclosDecorridos = 0;
                processo->programa.pc++;

            }
            else{
                processo -> ciclosDecorridos++;
            }
        }
        if(os->runningProcess != NULL){

            if(os->runningProcess -> ciclosDecorridos == PC_CYCLES(os->runningProcess)){

                os->runningProcess->programa.pc++;

            if(os -> runningProcess -> programa.pc == MAX_PROGRAM_SIZE){
                os->runningProcess->state = EXIT;

            }else if(PC_CYCLES(os->runningProcess) == 0){

                os->runningProcess->state= EXIT;
                os->runningProcess->ciclosDecorridos = 1;
            }
            else{

                enqueue(os->blockedQueue, os->runningProcess);
                os-> runningProcess->state = BLOCKED;
                os->runningProcess->ciclosDecorridos = 1;

            }
            os->runningProcess = NULL;
            }
            else if(os->runningProcess->ciclosDecorridos % QUANTUM == 0){
                //passa processo de new para ready após executar QUANTUM vezes
                enqueue(os->readyQueue, os->runningProcess);
                os->runningProcess->state = READY;
                os->runningProcess = NULL;
            }
            else{
                os->runningProcess->ciclosDecorridos++;
            }
        }
        for(int i =0; i<os->numeroDeProcessos; i++){
            Processo* processo = os->processos[i];

            if(processo->state == NEW && processo->ciclosDecorridos == 1){
                // passa de new para ready
                enqueue(os->readyQueue, processo);
                processo->state = READY;
                processo->ciclosDecorridos =0;

            }
            else if(processo->state == NEW){
                processo->ciclosDecorridos++;

            }
        }
        //caso existam processsos na auxQueue vamos escolher o primeiro da queue
        if(os->auxQueue->size >0 && os->runningProcess == NULL){
           // dá dequeue na fila ready e mete esse programa a correr
            os->runningProcess = peek(os->auxQueue);
            dequeue(os->auxQueue);
            os->runningProcess->state = RUNNING;
            os->runningProcess-> ciclosDecorridos++;
        }
        //caso não existam processos na auxQueue optamos pela readyQueue
        else if(os->readyQueue-> size > 0 && os->runningProcess == NULL){
            os->runningProcess = peek(os->readyQueue);
            dequeue(os->readyQueue);
            os->runningProcess->state = RUNNING;
            os->runningProcess-> ciclosDecorridos++;
        }
        os->ciclos++;
        printEstado(os);
        correrProcesso = false;

        for( int i=0; i < os->numeroDeProcessos; i++){
            Processo* processo = os -> processos[i];
            if(processo->state != EXIT || processo-> ciclosDecorridos < 1){
                correrProcesso = true;
                break; 
            }

        }
        
    }
    
}

//main
int main(){

    printf("Insira o escalonamento:\n 1 - RR\n 2 - VRR\n");
    int pick;
    scanf("%d", &pick);

    OS* os = createOS();
    InputProgramas(os);

    printf("instante ");
    for(int i = 1;  i <= os->numeroDeProcessos; i++){
        printf("|proc%d  ", i);

    }
    printf("\n");

    if(pick == 1){
        round_robin(os);
    }else if(pick == 2){
        virtual_round_robin(os);
    }
    else
    {
        printf("ERRO!");
    }
    

    return 0;
}
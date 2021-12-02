//un padre genera 10 figli,i figli stampano il proprio pid e terminano.
// IL padre li attende e stampa la terminazione di  ognuno
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

int main(){
    int n=10;
    //int exit_val[n]; = status[n]
    pid_t pid,ppid;
    int status[n];
    //pid_t child_pid;
    ppid=getpid();
    
    for(int i=0;i<n;i++){
        
        if(getpid()==ppid){ //getpid prende il pid del processo in uso, se sta eseguendo il padre esegue la fork e poi va al default, se esegue il figlio (solo dopo che il padre ha eseguito la fork, perchè poi subito dopo non ha il tempo di percorrere il ciclo for in quanto fa la exit success)
        sleep(2);
            pid=fork(); //mi assicuro che la faccia solo il padre, perchè i figli effettivamente scorrono il ciclo for (teoricamente avendo messo EXIT_SUCCESS non lo scorrono, cioè quando il padre fa la fork il figlio continua ad eseguire lo stesso codice del padre -> va allo switch case 0; stampa PID ed esce!)
            
            //siccome faccio exit_success non c'è bisogno del controllo sulla fork. sarà solo il padre a passarci
        }
        
        switch(pid){
            case -1:
                perror("nn");
                exit(EXIT_FAILURE);
                break;
            case 0:
                printf("\nChild number %d, PID %d\n",i,getpid());
                //exit_val[i]=0; //exit(0); //exit() o (i) o (0)?
                //status[i]=37+i;
                exit(EXIT_SUCCESS); //mi assicuro che ogni child non percorra tutto il ciclo for , appena stampa il pid esce (e il padre ne salva il valore di terminazione)
            default:
                //padre
                //aspetta fuori dal main
                wait(&(status[i])); //quando tutti e 10 i figli finiscono, egli esce dal for1 e va al for2 (cioè prosegue il codice il padre, tutti i figli hanno finito!)
                break;
                
        } 
    }
    
    /*if(pid>0){
        printf("\nTESTT ");
        for(int i=0;i<n;i++){
            printf(" %d ",status[i]);
        }
    }*/ //non va perchè il valore d'uscita si assegna mediante wait, non come prima mediante il child
    
    for(int i=0;i<n;i++){
        if(WIFEXITED(status[i])){
            printf("\nChild number %d finished, exit code %d",i,WEXITSTATUS(status[i]));
        }else
            printf("Child exited abnormally");
    }
    
    exit(1);
    
}

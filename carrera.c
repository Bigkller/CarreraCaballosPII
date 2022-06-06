#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<ncurses.h>

#define N 4
#define CARRIL 5

typedef struct{
    int carril;
    char caballo;

}parametros_t;
void *funcionThread(parametros_t *parametro);

int contador [CARRIL]={0,0,0,0,0};
#ifdef MUTEX
pthread_mutex_t pantalla;
#endif
int main(void){
    int x=0,y=15;
    int i;
    int error[N];
    pthread_attr_t atributos[N];
    pthread_t idhilo[N];
    parametros_t in[N];

    initscr();
    curs_set(0);
    erase();
    refresh();
    srand(time(NULL));
    #ifdef MUTEX
    pthread_mutex_init(&pantalla,NULL);
    #endif

    for(i=0;i<N;i++){
        pthread_attr_setdetachstate(&atributos[i],PTHREAD_CREATE_JOINABLE);
        in[i]-carril=CARRIL+(i*2);
        in[i].caballo='h'+i;
        error[i]=pthread_create(&idhilo[i],&atributos[i],{void *}funcionThread,{void *}&in[i]);
        if(error[i] !=0){
            perror("no se pueden crear las hebras.");
            exit(-1);
        
        }
    }
    #ifdef MUTEX
    pthread_mutex_lock (&pantalla);
    #endif
    for(i=0;i<N;i++){
        mvprintw(i,0,"contador %c: %i",in[i].caballo.contador[i]);
    }
    mvprintw(N,0,"contador %c: %i","P",contador[i]);

    refresh();
    #ifdef MUTEX
    pthred_mutex_unlock(&pantalla);
    #endif
    while(1){
        #ifdef MUTEX
        pthread_mutex_lock (&pantalla);
        #endif
        move(x,y);
        printw(" ");
        refresh();
        #ifdef MUTEX
        pthread_mutex_unlock (&pantalla);
        #endif
        if(drand48[]<0,5) x++;
        if(x==20){
            x=1;
            contador[N]++;
            #ifdef MUTEX
            pthread_mutex_lock (&pantalla);
            #endif
            move(N,0);
            clrtoeol();
            move(N,0);
            printw("contador p: %i", contador[N]);
            refresh();
            #ifdef MUTEX
            pthread_mutex_unlock (&pantalla);
            #endif
        }
        #ifdef MUTEX
        pthread_mutex_lock (&pantalla);
        #endif
        mvprintw(y,x,"p");
        refresh();
        #ifdef MUTEX
		pthread_mutex_unlock(&pantalla);
        #endif

        usleep(1000000/4);						
        x++;
    }
    getch(); 										
	endwin();
}
void *funcionThread(parametros_t *parametro){
    int x=1,y=parametro->carril,pos;
    pos=y-(CARRIL+((y-CARRIL)/2));
    while(contador[pos]<=5){
    #ifdef MUTEX
    pthread_mutex_lock (&pantalla);
    #endif  
    mvprintw(y,x," ");
    refresh();
    #ifdef MUTEX
    pthread_mutex_unlock(&pantalla);
    #endif
    if(drand48()<0,5) x++;
    if(x==20){
        x=1;
        contador[pos]++;
        #ifdef MUTEX
        pthread_mutex_lock (&pantalla);
        #endif 
        move(pos,0);
        clrtoeol();
        mvprintw(pos,0,"contador%c: %i",parametro->caballo,contador[pos]);
        refresh();
        #ifdef MUTEX
        pthread_mutex_unlock(&pantalla);
        #endif
    }
    #ifdef MUTEX
    pthread_mutex_lock (&pantalla);
    #endif
    #ifdef MUTEX
	pthread_mutex_unlock(&pantalla);	
    #endif

    usleep(1000000/4);								
    x++;
    }
}

#include "ag.h"
//CUERPO DEL ALGORITMO
AG::AG()
{
    QFile log("log.txt");//ARCHIVO DE RESULTADOS
    QFile plotfile("plot.txt");//ARCHIVO PARA GRAFICAR
        if(!log.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate)){
            return;
         }
        if(!plotfile.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate)){
            return;
         }
   QTextStream cdout(&log);
   QTextStream plot(&plotfile);
    initAG();
    for(int j=0;j<GENERACIONES;j++){
        hijos.clear();
        vecino.x=x_0.x+1;
        if(vecino.x<=POSIBLES_SOLUCIONES&&vecino.x>=0){
             if(!buscarTabu(vecino.x))
                 hijos.append(vecino);
         }
        vecino.x=x_0.x-1;
        if(vecino.x<=POSIBLES_SOLUCIONES&&vecino.x>=0){
             if(!buscarTabu(vecino.x))
                 hijos.append(vecino);
        }
        bHijo=bestHijo();
        x_0.fitness=funcionObjetivo(espacioSoluciones[x_0.x]);
        if(bHijo.fitness<x_0.fitness){
            agregarTabu(bHijo.x);
            x_0=bHijo;
        }
        cdout<<"x = "<<espacioSoluciones[x_0.x]<<" fitness:"<<x_0.fitness<<endl;
        plot<<espacioSoluciones[x_0.x]<<" "<<x_0.fitness<<endl;
        actualizarTabu();
    }

}
//CALCULA A EL MEJOR DE LOS HIJOS
solucion AG::bestHijo(){
    struct solucion best;
    best=hijos.at(0);
    struct solucion aux;
    for(int j=0;j<hijos.length();j++){
        best.fitness=funcionObjetivo(espacioSoluciones[best.x]);
        aux=hijos.at(j);
        aux.fitness=funcionObjetivo(espacioSoluciones[aux.x]);
        hijos.replace(j,aux);
        if(hijos.at(j).fitness<best.fitness){
             best=hijos.at(j);
         }
    }
    return best;
}
//AGREGA UNA SOLUCION A LOS TABUES
void AG::agregarTabu(int x){
    struct tabu tab;
    tab.x=x;
    tab.t=MAX_T_TABU;
    tabus.append(tab);
}
//CALCULO DE LAS POSIBLES SOLUCIONES, LLENAMOS UN VECTOR DEPENDIENDO
//DE LOS LIMITES DE BUSQUEDA Y DE EL TAMAÑO DE NUESTRO ESPACIO DE BUSQUEDA
void AG::calcularSoluciones(){

    float f=((float)(LIM_SUP-(LIM_INF)))/POSIBLES_SOLUCIONES;
    float sol=-1;
    for(int j=0;j<POSIBLES_SOLUCIONES;j++){
        espacioSoluciones[j]=sol;
        sol=sol+f;
    }
}
//BUSCA A UNA COLUCION EN EL VECTOR DE TABUES
bool AG::buscarTabu(int ta){
    for(int j=0;j<tabus.length();j++){
        if(tabus.at(j).x==ta)
            return true;
    }
    return false;
}
//SE INICIALIZACION DE ALGORITMO, ELEGIMOS SOLUCION ALEATORIA Y UTILIZAMOS LA
//FUNCION PARA CALCULAR SOLUCIONES
void AG::initAG(){
    srand(rdtsc());
    calcularSoluciones();
    x_0.x=rand()%50;

}
//FUNCION OBJETIVO
float AG::funcionObjetivo(float x){
    float y;
    y=pow(x,4)+5*pow(x,3)+4*pow(x,2)-4*x+1;
    return y;
}
//DECREMENTA LOS TIEMPOS DE TODOS LOS TABUES Y SACA A LOS QUE ESTEN EN T=0
void AG::actualizarTabu(){
    struct tabu aux;
    for(int j=0;j<tabus.length();j++){
        aux=tabus.at(j);
        aux.t--;
        tabus.replace(j,aux);
        if(aux.t==0)
            tabus.removeAt(j);

    }
}
int AG::rdtsc()
{
   __asm__ __volatile__("rdtsc");
}

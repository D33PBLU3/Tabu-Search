#ifndef AG_H
#define AG_H
#include <QList>
#include <QTextStream>
#include <math.h>
#include <QFile>
#define POSIBLES_SOLUCIONES 50
#define MAX_VECINOS 2
#define LIM_SUP 4
#define LIM_INF -1
#define MAX_T_TABU 4
#define GENERACIONES 20

struct tabu{
    int x;
    int t;
};
struct solucion{
  int x;
  float fitness;
};
class AG
{
public:
    float espacioSoluciones[POSIBLES_SOLUCIONES];
    struct solucion x_0;
    QList<struct solucion> hijos;
    QList<struct tabu> tabus;
    struct solucion bHijo;
    struct solucion vecino;
    AG();
    bool buscarTabu(int);
    void calcularSoluciones();
    float funcionObjetivo(float);
    void actualizarTabu();
    void agregarTabu(int);
    struct solucion bestHijo();
    void initAG();
    int rdtsc();
};

#endif // AG_H

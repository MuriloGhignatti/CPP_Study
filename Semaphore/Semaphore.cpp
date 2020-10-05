#include "Semaphore.hpp"

int Semaphore::cor = 2;

void Semaphore::mudaProximaCor(){
    if (cor == 2)
        cor = 0;
    else
        cor++;
}

void Semaphore::mudaCorFixa(int novaCor){
    cor = novaCor;
}

int Semaphore::mostraCor(){
    return cor;
}
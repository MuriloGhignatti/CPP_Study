#include <iostream>
#include <string>
#include "Semaphore.hpp"

void print(int color);

int main(int argc, char const *argv[]) {


    std::cout << "Inicio do Programa" << '\n';
    print(Semaphore::mostraCor());
    
    for(int i = 0; i < 10; i++){
        Semaphore::mudaProximaCor();
        print(Semaphore::mostraCor());
    }

    Semaphore::mudaCorFixa(1);
    print(Semaphore::mostraCor());
}

void print(int color) {

    std::string message = "";

    switch (color)
    {
    case 0:
        message.append("Verde");
        break;

    case 1:
        message.append("Amarelo");
        break;

    case 2:
        message.append("Vermelho");
        break;
    
    default:
        break;
    }

    std::cout << message << '\n';
}


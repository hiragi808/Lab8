#include <iostream>
#include <fstream>
#include "i.h"
#include <string>
int main() {
    setlocale(LC_ALL, "");
    std::cout<<"Введите номер задания "<<std::endl;
    int choice;
    std::cin>>choice;
    std::cin.clear();
    switch (choice) {
            case 1: {
                t1();
                break;
            }
            case 2: {
                t2();
                break;
            }
            case 3: {
                    t3();
                    break;
            }
            default:
                std::cout << "неверный выбор!\n";
            }
        }
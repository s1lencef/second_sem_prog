#include <iostream>
#include <Windows.h>
using namespace std;
//структура очереди
struct Queue{
    int info;
    Queue *link;

};
void print(Queue *p,Queue *Top){
    p = Top;
    while(p){
        cout<< p->info<<' ';
        p = p->link;
    }
    cout<<endl;
}

void push(Queue *&Back,int x){
    Back->link = new Queue;
    Back = Back->link;
    Back->link = 0;
    Back->info = x;

}
void insert_one(Queue *&p){
    Queue *t;
    t = p->link; // сохраняем адрес отрицательного следующего элемента
    p->link = new Queue;// создаем новый элемент и заполняем его
    p->link->info = 1;
    p->link->link = t;// связываем новый элемент с остальным списком
    p = p->link->link;
}
int pop(Queue *&Top){
    Queue *p;
    int x;
    p = Top->link;
    x = Top->info;
    delete Top;
    Top = p;
    return x;
}

void first_task(Queue *&Top){
    Queue *p;
    p = Top;
    while (p->link) {
        if (p->link->info < 0) {
            insert_one(p);
        } else {
            p = p->link;
        }
    }
    // обработка первого узла
    if (Top->info < 0) {
        p = Top;
        Top = new Queue;
        Top->info = 1;
        Top->link = p;
    }
}
void second_task(Queue *&Top){
    Queue *p;
    while(Top->info < 0) {
        pop(Top);
    }
    p = Top;

    while (p->link) {

        if (p->link->info < 0) {
            pop(p->link);
        } else {
            p = p->link;
        }

    }
}
void rec_del(Queue *&Top){
    if (Top!=nullptr) {
        rec_del(Top->link);
        delete Top;
    }
    else return;
}
void third_task(Queue *&Top){
    int n,count=0;
    Queue *p;

    cout << "Введите число: ";
    cin >> n;

    p = Top;
    while (p) {
        if (p->info == n) {
            count++;
        }
        p = p->link;
    }

    cout << "Число " << n << " входит в список " << count << " раз(-а)" << endl;
}


int main() {
    setlocale(LC_ALL, "Russia");
    Queue *Top, *Back, *p = nullptr, *t;//вид очереди предполагает наличие постоянных указателей на начало и конец списка
    int x, choose;// переменная для ввода с клавиатуры

    //заполнение первого узла списка

    cout << "Введите элементы списка, для окончания введите <0>:";
    //обработка первого узла
    cin >> x;
    if (x == 0) {
        return 0;
    }
    Back = Top = new Queue;
    Back->info = x;
    Back->link = 0;
    Top->link = Back;

    // заполнение остальных узлов
    while (true) {
        cin >> x;
        if (x == 0) {
            break;
        }
        push(Back, x);
    }
    // последний элемент списка должен указывать на 0
    print(p, Top);
    while(true) {
    cout << "Укажите действие, которое надо выполнить:" << endl
         << " 1 - во все позиции списка, предшествующие узлам с отрицательной информационной частью, вставить узел = 1"
         << endl;
    cout << " 2 - удалить все отрицательные элементы" << endl << " 3 - подсичтать количество вхождений числа в список"
         << endl;
    cout << " 4 - удалить список" << endl << " 0 - завершить программу";
    cin >> choose;

    if (choose == 1) {
        //во все позиции списка, предшествующие узлам с отрицательной информационной частью, вставляется узел = 1
        first_task(Top);
        print(p, Top);
    }

    if (choose == 2) {
        // удаление всех узлов списка, содержащих в информационной части отрицательные числа
        second_task(Top);
        print(p, Top);
    }
    if (choose == 3) {
        third_task(Top);

    }

    if (choose == 4) {
        //рекурсивное удаление
        rec_del(Top);
        cout << "Список удален" << endl;
    }

    if (choose == 0) {
        break;
    }
    }

    return 0;
}

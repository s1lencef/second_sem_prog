#include <iostream>
using namespace std;

struct Cyclical{
    int value;
    Cyclical* link;
};

Cyclical* push(Cyclical* Top,Cyclical* h,int x){
    Cyclical *p =h;
    p->link = new Cyclical;
    p = p->link;
    p->value = x;
    p->link = Top;
    return p;
}
void print(Cyclical* Top){
    Cyclical *p;
    p = Top;
    do{
        cout<<p->value<<" ";
        p = p->link;
    }while(p!=Top);
    cout<<endl;
}
void del(Cyclical* Top) {

    if (Top == NULL) return;

    if (Top->link == Top) {
        delete Top;
        return;
    }

    Cyclical *tmp = Top->link;
    Top->link = Top->link->link;
    delete tmp;

    del(Top);
}

int pop(Cyclical*  &h){
    int n = h->value;
    Cyclical* p = h->link;
    h->link = p->link;
    delete p;
    return n;

}

void first_task(Cyclical*  &h,Cyclical*  &Top){
    if(h->link->value <0){
        Top = new Cyclical;
        Top->link = h->link;
        Top->value = 1;
        h->link = Top;
        h = Top->link;
    }
    do{
        if(h->link->value <0){
            h = push(h->link,h,1);
        }
        h = h->link;
    }while(h!=Top);

}

void second_task(Cyclical*  &h,Cyclical*  &Top){
    while(h->link->value <0){
        h->link = Top->link;
        delete Top;
        Top = h->link;
    }

    do {
        if (h->link->value < 0) {
            pop(h);
        } else {
            h = h->link;
        }
    } while (h->link != Top);


}
void third_task(Cyclical*  &h,Cyclical*  &Top ){
    int x,count = 0;
    cout << "Введите число: ";
    cin >> x;
    h = Top;
    do {
        if (h->value == x) {
            count++;
        }
        h = h->link;
    } while (h != Top);
    cout << "Число " << x << " встречается в последовательности " << count << " раз(-а)" << endl;
}


int main() {

    Cyclical *Top,*h;
    int x,choose,count = 0;
    setlocale(LC_ALL,"Russia");

    cout<<"Введите последовательность чисел: ";
    cin>> x;
    if (x==0){
        return 0;
    }
    h = Top = new Cyclical;
    Top->value = x;
    Top->link = Top;

    while (true){
        cin>>x;
        if(x == 0){
            break;
        }
        h = push(Top,h,x);
    }


    print(Top);
    while(true){
    cout<<"Укажите действие, которое надо выполнить:"<<endl<<" 1 - во все позиции списка, предшествующие узлам с отрицательной информационной частью, вставить узел = 1"<<endl;
    cout<<" 2 - удалить все отрицательные элементы"<<endl<<" 3 - подсичтать количество вхождений числа в список"<<endl;
    cout<<" 4 - удалить список"<<endl<<" 0 - завершить программу";
    cin>>choose;
// пункт 1
if (choose == 1) {

    first_task(h,Top);

    print(Top);
}
// пункт 2
if (choose == 2) {

    second_task(h,Top);

    print(Top);
}
//пункт 3
if (choose == 3) {
    third_task(h,Top);
}
// пункт 4
if (choose == 4) {
    del(Top);

    cout << "Все элементы удалены!" << endl;
}
if(choose == 0){
    return 0;
}
}

}

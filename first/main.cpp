#include <iostream>
using namespace std;

struct Stack{
    int value;
    Stack *link;
};
Stack* push( Stack*Top,int n){
    Stack*p;
    p = new Stack;
    p->value = n;

    if(Top == 0){
        Top = p;
        p->link = 0;
    }
    else{
        p->link = Top;
        Top = p;
    }
    return Top;
}
int pop(Stack*&Top){//передача по ссылке, чтобы изменилось значение и за пределами функции
    int n = Top->value;
    Stack*p;
    p = Top->link;
    delete Top;
    Top = p;
    return n;
}

int peek(Stack*Top){
    return Top->value;
}

int main() {
    setlocale(LC_ALL,"Russia");
    Stack *Top,*a;
    int num;

    Top = 0;

    cout<< "Введите последовательность целых чисел(для окончания введите 0) ";
    do{
        cin>>num;
        Top = push(Top,num);

    } while (num!=0);
    // вывод с использованием peek()
    a = Top;
    while(a){
        if (peek(a)>0){
            cout << peek(a) << " ";
        }
        a = a->link;
    }
    cout<<endl;
    // вывод с использованием pop()
        while(Top){
            num = pop(Top);
            if (num>0) {
                cout << num << " ";
            }
        }


    return 0;
}

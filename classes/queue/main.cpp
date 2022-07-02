#include <iostream>
using namespace std;

class Queue{
private:
    int data;
    Queue *next;
    Queue *Top= nullptr,*Back;
public:
    Queue(){
        init();
    }
    void init(){
        Back = Top = nullptr;
    }
    void push(int n){
        if (Top == nullptr){
            Top = Back = new Queue;
            Back->data = n;
            Back->next = nullptr;
            Top->next= Back;
        }
        else{
            Back->next = new Queue;
            Back = Back->next;
            Back->next = nullptr;
            Back->data = n;
        }
    }
    int pop(){
        Queue *p;
        int n;
        p = Top->next;
        n = Top->data;
        delete Top;
        Top = p;
        return n;
    }
    Queue* back(){
        return Back;
    }
    Queue *front(){
        return Top;
    }
    int size(){
        int count =0;
        Queue *p = Top;
        while (p){
            count++;
            p = p->next;
        }
        return count;
    }
    bool empty(){
        if (Top == nullptr){
            return true;
        }
        return false;
    }
};

int main() {
    int x;
    cout << "Start:";
    Queue q;
    while (true){
        cin>>x;
        if (x==0){
            break;
        }
        q.push(x);
    }

    while(!q.empty()){
        cout<< q.pop()<<endl;
    }
    return 0;
}

#include <iostream>
using namespace std;


class DQUE{

private:
    int data;
    DQUE *next;
    DQUE *prev;
    DQUE *Top;
    DQUE *Back;
    int d_size = 0;
public:
    DQUE(){
        init();
    }
    void init(){
        Top = Back = nullptr;
    }
    DQUE* at(int index){
        int count  = 0;
        DQUE * p = Top;
        while(count!= index){
            p = p->next;
            count++;
        }
        return p;
    }
    DQUE* back(){
        return Back;
    }
    DQUE* front(){
        return Top;
    }
    void clear(){
        while(Back->prev){
            Back = Back->prev;
            delete Back->next;
            Back->next = nullptr;
        }
        delete Back;
        Back = nullptr;
    }

    void delete_r(){
        Back = Back->prev;
        delete Back->next;
        Back->next = nullptr;
    }
    void delete_l(){
        Top = Top->next;
        delete Top->prev;
        Top->prev = nullptr;
    }
    void emplace_back(int item){
        DQUE *p;
        if (Back == nullptr){
            Top = Back = new DQUE;
            Back->data = item;
            Back->next = nullptr;
            Back->prev == nullptr;
        }
        else{
            Back->next = p = new DQUE;
            p->data = item;
            p->prev = Back;
            Back = p;
            Back->next = nullptr;
        }
        d_size++;
    }
    void emplace_front(int item){
        DQUE *p;
        if (Top == nullptr){
            Top = Back = new DQUE;
            Top->data = item;
            Top->next = nullptr;
            Top->prev == nullptr;
        }
        else{
            Top->prev = p = new DQUE;
            p->data = item;
            p->next = Top;
            Top = p;
            Top->prev = nullptr;
        }
        d_size ++;
    }
    void emplace(int pos, int item){
        DQUE* p = Top, *t;
        int count = 0;
        if (pos == 0){
            emplace_front(item);
        }
        else{
            while(true){
                if (count  == pos-1){
                    break;
                }
                count ++;
                p = p->next;

            }
            t = p->next;
            p->next = new DQUE;
            p->next->data = item;
            p->next->prev = p;
            p-> next->next = t;
            t->prev = p->next;
            d_size++;
        }
    }
    bool empty(){
        if (Top == nullptr){
            return true;
        }
        return false;
    }
    int size(){
        DQUE*p = Top;
        int count = 0;
        while(p){
            count++;
            p=p->next;
        }
        cout<<d_size<<endl;
        return count;

    }
    void push_back(int item){
        emplace_back(item);
    }
    void push_front(int item){
        emplace_front(item);
    }
    int pop_back(){
        DQUE *p = Back->prev;
        int n = Back->data;
        delete Back;
        Back = p;
        Back->next = nullptr;
        d_size--;
        return n;
    }
    int pop_front(){
        DQUE *p = Top->next;
        int n = Top->data;
        delete Top;
        Top = p;
        Top->prev = nullptr;
        d_size--;
        return n;
    }


    int operator[] (const int& i){
        DQUE *p = Top;
        int n =0;
        while (n!=i){
            p = p->next;
            n++;
        }
        return p->data;

    };
    
    
};


int main() {
    cout << "Starting program: " << endl;
    return 0;
}

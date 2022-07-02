#include <iostream>
using namespace std;

class Stack{
private:
    int data;
    int s_size;
    Stack* next;
    Stack* Top;
public:
    Stack(){
        init();
    }
    void init(){
        Top = nullptr;
        s_size = 0;
    }
    void push( int new_data ){
        Stack*p;
        p = new Stack;
        p->data  = new_data;
        p->next = Top;
        Top = p;
        s_size+=1;
    }
    int pop(){
        int n = Top->data;
        Stack*p;
        p = Top->next;
        delete Top;
        Top = p;
        s_size-=1;
        return n;
    }
    bool empty(){
        if (Top == nullptr){
            return true;
        }
        return false;
    }

    int size(){
        return s_size;
    }
    Stack* top(){
        return Top;
    }
    void print(){
        Stack*p=Top;
        while(p){
            cout<<p->data<<' ';
            p = p->next;
        }
    }

};


int main() {
    cout<<"Start."<<endl;
    int x;
    Stack st;
    while(true){
        cin>>x;
        if (x == 0){
            break;
        }
        st.push(x);

    }
    cout<<"\n"<<st.size()<<endl;
    cout<<"\n"<<st.top()<<endl;
    st.print();
    while (!st.empty()){
        x = st.pop();
        cout<<x<<' ';
        cout<<"\n"<<st.top()<<endl;
    }
    cout<<"\n"<<st.size();
    cout<<"\n"<<st.top()<<endl;
    return 0;
}

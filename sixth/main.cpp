#include <iostream>
using namespace std;

struct Tree{
    int info;
    Tree* left;
    Tree* right;
};

void add(Tree*&h, int n){

    if (h == nullptr){
        h = new Tree;
        h ->info = n;
        h->left = h->right = nullptr;
        cout<<"Число "<<n<<" добавлено в дерево!"<<endl;
    }
    else{
        if (h->info < n){
            add(h->left,n);
        }
        else if (h->info > n){
            add(h->right, n);
        }
        else{
            cout<<"Число "<<n<<" уже есть в дереве!"<<endl;
        }
    }
}

void search(Tree*&h,int n){

    if (h == nullptr){
        cout<<"Числа "<<n<<" нет в дереве!"<<endl;
        return;
    }
    else{
        if (h->info < n){
            search(h->left,n);
        }
        else if (h->info > n){
            search(h->right, n);
        }
        else{
            cout<<"Число "<<n<<" найдено!"<<endl;
        }
    }
}

void del(Tree*&h){
}
int main() {
    setlocale(LC_ALL, "Russian");
    Tree *Root,*p;
    int x;

    while(true){
        cin>>x;
        if (x == 0){
            break;
        }
        add(Root,x);

    }
    while(true){
        cout<<"Введите число, которое хотите найти: "<<endl;
        cin>>x;
        if (x == 0){
            break;
        }
        search(Root,x);
    }

    return 0;
}

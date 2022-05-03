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
        if (h->info > n){
            add(h->left,n);
        }
        else if (h->info < n){
            add(h->right, n);
        }
        else{
            cout<<"Число "<<n<<" уже есть в дереве!"<<endl;
        }
    }
}

void search(Tree*&h,int n){

    if (h == nullptr){
        cout<<"Числа "<<n<<" нет в дереве!\n"<<endl;
        return;
    }
    else{
        if (h->info > n){
            search(h->left,n);
        }
        else if (h->info < n){
            search(h->right, n);
        }
        else{
            cout<<"Число "<<n<<" найдено!\n"<<endl;
        }
    }
}


void show_pref(Tree *h){

    if( h != nullptr){
        cout<<h->info<<" ";
        show_pref(h->left);
        show_pref(h->right);
    }
}
void show_inf(Tree *h){

    if( h != nullptr){
        show_inf(h->left);
        cout<<h->info<<" ";
        show_inf(h->right);
    }
}

void show_postf(Tree *h){

    if( h != nullptr){
        show_postf(h->left);
        show_postf(h->right);
        cout<<h->info<<" ";
    }
}


void del(Tree*&h){
    if (h->left){
        del(h->left);
    }
    if (h->right){
        del(h->right);
    }
    delete h;
}



int main() {
    setlocale(LC_ALL, "Russian");

    Tree *Root;
    int x,choice;

    cout<<"Введите числа (для окончания введите 0): "<<endl;

    while(true){
        cin>>x;
        if (x == 0){
            break;
        }
        add(Root,x);

    }
    while(true) {
        cout<<"Выберите действие: \n1 - поиск числа в дереве\n2 - Префиксный вывод\n3 - Инфиксный вывод \n"
              "4 - Постфиксный вывод\n0 - Очистить дерево и завершить программу"<<endl;
        cin>>choice;

        switch (choice) {
            case 1:

                while (true) {
                    cout << "Введите число, которое хотите найти (для окончания введите 0): " << endl;
                    cin >> x;
                    if (x == 0) {
                        break;
                    }
                    cout <<'\n';
                    search(Root, x);
                }
                break;

            case 2:
                cout <<'\n';
                cout << "Префиксный вывод:" << endl;
                show_pref(Root);
                cout <<'\n'<< endl;
                break;

            case 3:
                cout <<'\n';
                cout << "Инфиксный вывод:" << endl;
                show_inf(Root);
                cout <<'\n'<< endl;
                break;

            case 4:
                cout <<'\n';
                cout << "Постфиксный вывод:" << endl;
                show_postf(Root);
                cout <<'\n'<< endl;
                break;

            default:
                del(Root);
                cout << "Дерево очищено!" << endl;
                return 0;
        }

    }

}
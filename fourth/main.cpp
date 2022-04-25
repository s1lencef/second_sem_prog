#include <iostream>
using namespace std;

struct City{
    string name;
    string region;
    int population;
    City* prev;
    City* next;
};

struct Region{
    string namer;
    int count_p=0;
    Region* link;
};

void print(City*Top){
    City *p;
    string s;
    p = Top;
    while(p){
    cout<<"Город: "<<p->name<<" Регион: "<<p->region<<" Население: "<<p->population<<" человек "<<endl;
    p = p->next;
        }
}
void print(Region*Top){
    Region *t;
    t = Top;
    while(t){
        cout<<"Регион: "<<t->namer<<" Население: "<<t->count_p<<" человек "<<endl;
        t = t->link;
    }
}

void push(City*&Back, int n, int num, const string& name, const string& r){
    City *p;
    if (n == 1){
        Back->name = name;
        Back->region = r;
        Back->population = num;
    }
    else{
        Back->next = p = new City;
        p->name = name;
        p->region = r;
        p->population =num;
        p->prev = Back;
        Back = p;
    }

}

void stack_push(Region *&R_top,Region *&a,const string& region){
    a = new Region;
    a->namer = region;
    a->link = R_top;
    R_top = a;
}
void read_regions(Region*&R_top, Region *&a, const string& region){
    bool flag = true;
    if (a == nullptr){
        stack_push(R_top,a,region);
    }
    else{
        a = R_top;
        while(a){
            if (a->namer == region){
                flag = false;
                break;
            }
            else{
                a = a->link;
            }
        }
        if (flag){
            stack_push(R_top,a,region);
        }
        a = R_top;
    }

}
void region_population(Region *&a,City*Top){
    City*p;
    int count_pop =0;
    while (a){
        count_pop = 0;
        p = Top;
        while(p){
            if (p->region == a->namer){
                count_pop+= p->population;
            }
            p = p->next;
        }
        a->count_p = count_pop;
        a = a->link;
    }
}

void sort(Region*Top){
    Region *a,*h;
    int n;
    string s;
    a = Top;


    while(a){
        h = Top;
        while(h){
            if (h->count_p < a->count_p){
                n = h->count_p;
                s = h->namer;
                h->count_p = a->count_p;
                h->namer = a->namer;
                a->namer = s;
                a->count_p = n;
            }
            h = h->link;
        }
        a = a->link;
    }

}

void clear(Region*&R_top){
    Region *j = R_top;
    while(j){
        j = R_top->link;
        delete R_top;
        R_top = j;
    }


}
void clear(City*&Back){
    while(Back->prev){
        Back = Back->prev;
        delete Back->next;
        Back->next = nullptr;
    }
    delete Back;
    Back = nullptr;

}
void del_r(City*&Back){

        Back = Back->prev;
        delete Back->next;
        Back->next = nullptr;


}
void del_l(City*&Top){

    Top = Top->next;
    delete Top->prev;
    Top->prev = nullptr;

}
void task2(Region*R_top, City*Top){
    Region *a;
    City* p;
    p =Top;
    a = R_top;

    while(p){
        read_regions(R_top, a, p->region);
        p = p->next;
    }

    region_population(a,Top);
    sort(R_top);
    print(R_top);
}

void task3(City*Top,City*Back){
    City *p,*h;
    string region;
    cout<<"Введите название региона, который нужно удалить: ";
    cin>>region;
    while (Top->region == region){
        del_l(Top);
    }
    p = Top;
    while (p!=Back){

        if (p->region == region){
            h = p;
            p = p->next;
            p-> prev = h->prev;
            h->prev->next = p;
            delete h;
        }
        else{
            p = p->next;
        }
    }
    if (Back->region == region){
        del_r(Back);
    }

    print(Top);

}
void task4(City*Back, Region*R_top){
    clear(Back);
    clear(R_top);
}
int main() {
    City *Top,*Back,*p,*h;
    Region *R_top, *a;
    int population, n=1, choise;

    string name, region;
    setlocale(LC_ALL, "Russian");

    Top = Back = new City;
    R_top = a = nullptr;

    Top->next = Top->prev = nullptr;

    cout<<"Начните заполнять поля для каждого города.\n"
          "Для того, чтобы перейти к следующему городу в конце введите <1>\n"
          "Чтобы закончить заполнение базы данных введите <0>"<<endl;

    for (int x = 1; x!=0; cin>>x) {

        cout << "Название города: ";
        cin >> name;

        cout << "Название региона: ";
        cin >> region;

        cout << "Численность населения города: ";
        cin >> population;

        push(Back, n, population, name, region);

        n++;
    }
    while(true){
    cout<<"Чтобы вывести список введите 1\n"
          "Чтобы вывести на экран названия регионов в порядке убывания суммарной численности городского населения введите 2\n"
          "Чтобы удалить узлы, хранящие информацию о городах указанного (с клавиатуры) региона введите 3\n"
          "Чтобы очистить список введите 4\n"
          "Чтобы завершить работу программы введите 0"<<endl;

    cin>>choise;
    if (choise == 1){
        print(Top);

    }
    if (choise == 2){
        task2(R_top,Top);
    }
    if (choise == 3){
        task3(Top,Back);
    }
    if(choise == 4){
     task4(Back,R_top);
     return 0;

    }
    if (choise == 0){
        return 0;
    }
    }



}

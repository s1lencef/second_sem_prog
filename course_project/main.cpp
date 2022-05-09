#include <iostream>
#include <locale.h>
#include <windows.h>
#include <cmath>
#include <fstream>

using namespace std;

struct Student{
    string SNP;
    int group_n;
    int marks[5];
    int grant;
    Student* next;
    Student* prev;
};

struct Group{
    int num;
    int grant_total = 0 ;
    int points_total = 0;
    double index = 0;
    Group*link;
};

bool check_number(char a){
    char numbers[10] ={'0','1','2','3','4','5','6','7','8','9'};
        for (char l:numbers){
            if(a == l){
                return true;
            }
        }
    return false;

}



void print(Student*p, string a){
    cout<<"ФИО: "<<p->SNP<<a<<"Номер группы: "<<p->group_n<<a<<"Оценки за семестр: ";
    for(int mark : p->marks){
        cout<<mark<<' ';
    }
    cout<<a<<"Размер стипендии: "<<p->grant<<endl;
    return;
}

void push(Student*&Back, int group_n, int grant, const string& name,  int ms[],int n){
    Student *p;

    if (n==1){
        Back->SNP = name;
        Back->group_n = group_n;
        Back->grant = grant;
        for (int i =0; i<5;i++){
            Back->marks[i] = ms[i];
        }
        cout<<1<<Back->SNP<<endl;
    }
    else{
        Back->next = p = new Student;
        p->SNP = name;
        p->group_n = group_n;
        p->grant = grant;
        for (int i =0; i<5;i++){
            p->marks[i] = ms[i];
        }
        p->prev = Back;
        Back = p;
        Back->next = nullptr;
        cout<<2<<Back->SNP<<endl;
    }
}
void del_student(Student*&p,Student*&Top,Student*&Back){
    if (p->next == nullptr){
        cout<<"right deleted"<<endl;
        p = p->prev;
        delete p->next;
        p->next = nullptr;
        Back = p;
        cout<<Back->SNP<<endl;
    }
    else if(p->prev == nullptr){
        cout<<"left deleted"<<endl;
        p = p->next;
        delete p->prev;
        p->prev = nullptr;
        Top = p;
        cout<<Top->SNP<<endl;

    }
    else{
        cout<<"middle deleted"<<endl;
        p->prev->next = p->next;
        p->next->prev = p->prev;
        cout<<p->prev->SNP<<endl;
        delete p;

    }



}
bool find_in_groups(int number, Group*Top){
    Group *p;
    p =Top;
    while(p){
        if (p->num == number){
            return true;
        }
        p = p->link;
    }
    return false;

}
void create_groups(int number, Group*&Top){
    Group*p;
    if (!find_in_groups(number, Top)){
        p = new Group;
        p->num = number;
        if(Top == 0){
            Top = p;
            p->link = 0;
        }
        else{
            p->link = Top;
            Top = p;
        }

    }
}
void put_group(Group *&p, Student*t){
    int mrs =0;
    for(int mark : t->marks){
        mrs+=mark;
    }
    p->grant_total+=t->grant;
    p->points_total+=mrs;
}

void fill_grouns(Group *&G_top, Student*Top){
    Group *t = G_top;
    Student *p;
    while(t){
        p = Top;
        while(p){
            if(t->num == p->group_n){
                put_group(t,p);
            }
            p = p->next;
        }
        t = t->link;
    }
}
void fill_index(Group *Top){
    Group *t = Top;
    double index;
    while(t){
        index = (double)t->grant_total/t->points_total;
        index = round(index*100)/100;
        t->index = index;
        t = t->link;
    }
}


void sort_by_index(Group*Top){
    Group *a,*h;
    int n,g,p;
    double i;

    a = Top;

    while(a){
        h = Top;
        while(h){
            if (h->index < a->index){
                n = h->num;
                g = h->grant_total;
                p = h->points_total;
                i = h->index;
                h->num = a->num;
                h->grant_total = a->grant_total;
                h->points_total = a->points_total;
                h->index = a->index;
                a->num = n;
                a->grant_total = g;
                a->points_total = p;
                a->index = i;
            }
            h = h->link;
        }
        a = a->link;
    }
}

void build_group(Group *&G_top, Student*Top){
    fill_grouns(G_top,Top);
    fill_index(G_top);
    sort_by_index(G_top);
}
void print(Group*p){
    cout<<"Номер группы: "<<p->num<<", Сумма оценок студентов: "<<p->points_total<<", Суммарный объем стипендий: "
        <<p->grant_total<<", Индекс стипендий(объем стипендий/сумма оценок): "<<p->index<<endl;
}
void id_task(Group*Top){
    double index;
    Group *h = Top;
    cout<<"Введите показатель: ";
    cin>>index;

    while(h->index > index){
        print(h);
        h = h->link;
    }
}


string make_name(){
    string name,surname,patronymic;
    cin >> surname;
    cin >> name;
    cin >> patronymic;
    surname=surname+" "+name+" "+patronymic;
    return surname;
}
void console_input(Student*&Back, int&n, Group*&Top){
    int x=1, group_n, grant;
    int ms[5];
    string full_name;

    while(true) {

        cout << "ФИО: ";
        full_name=make_name();

        cout << "Номер группы: ";
        cin >> group_n;
        create_groups(group_n, Top);
        cout << "Оценки за семестр: ";
        for (int i = 0; i<5;i++){
            cin>>ms[i];
        }
        cout<<"Размер стипендии: ";
        cin>> grant;

        push(Back, group_n, grant,full_name,ms,n);
        n++;
        cin>>x;
        if (x == 0){
            break;
        }

    }

}

void write_students(Student*Top){
    Student *p;
    string sep = ", ";
    p = Top;
    while(p){
        print(p,sep);
        p = p->next;
    }
}

void write_groups(Group *Top){
    Group *p = Top;
    while (p){
        print(p);
        p = p->link;
    }
}

void console_output(Student*Top,Group *G_top){
    write_students(Top);
    cout<<'\n';
    write_groups(G_top);
    cout<<"\n\n";
}

Student* find_student(Student*Top, const string& name, const int& group_n){
    Student*p;
    string sep;
    p = Top;
    while (p){
        cout<<p->SNP<<' '<<p->group_n;
        if ( p->SNP == name && p->group_n == group_n ){
            sep = " \n";
            cout<<"\nстудент найден!\n"<<endl;
            cout<<"ДАННЫЕ СТУДЕНТА"<<endl;
            print(p, sep);
            return p;
        }
        p = p->next;
    }
    return 0;
}
void change_student(Student*&p,Student*&Top,Student*&Back){
    string full_name;
    int group_n, grant,choice;
    while (true){
        cout<<"Что сделать с данными? \n1 - изменить данные ФИО\n2 - изменить номер группы\n3 - исправить оценки за семестр"
              "\n4 - изменить размер стипендии\n5 - удалить студента из списка\n0 - Выйти  из режима редактирования"<<endl;
        cin>>choice;
        switch(choice){
            case 1:
                cout << "Введите новые ФИО студента: " << endl;
                full_name = make_name();
                p->SNP = full_name;
                break;
            case 2:
                cout << "Введите новый номер группы студента: " << endl;
                cin >> group_n;
                p->group_n = group_n;
                break;
            case 3:
                cout << "Введите заново полный список оценок: " << endl;
                for (int i =0; i<5;i++){
                    cin>>p->marks[i] ;
                }
                break;
            case 4:
                cout << "Введите новый размер стипендии: " << endl;
                cin >> grant;
                p->grant = grant;
                break;
            case 5:
                del_student(p,Top,Back);
                cout<<"Студент удален из списка!"<<endl;
            default:
                return;
        }


    }
}

int main() {
    Group *G_top,*t;
    Student *Top,*Back,*p,*h;
    int x=1, group_n, grant,n=1, choice, old_group_n,k;
    int ms[5];
    string full_name,sep,filename;
    char a='h';
    ifstream infile;
    ofstream outfile;

    setlocale(LC_ALL, "Russian");

    Top = Back = new Student;
    Top->next = Top->prev = nullptr;
    G_top = nullptr;

    while (true){
        cout<<"Каким образом прочитать данные?\n1 - ввод через консоль\n2 - прочитать из файла"<<endl;
        cin>>choice;
        if (choice == 1){
            console_input(Back,n,G_top);
            break;
        }
        else{
            cout<<"Введите полное имя файла(путь): ";
            filename = "E:\\LETI\\1_kurs\\prog\\second_sem\\untitled1\\test.txt";
            infile.open(filename);
            if(infile.fail() ) {
                cerr << "Ошибка доступа к файлу" << endl;
                continue;}
            full_name = "";
            k=3;
            group_n = 0;
            infile.get(a);
            while(!check_number(a)){
                full_name+=a;
                infile.get(a);
            }
            cout<<'\n';
            while(check_number(a)){
                x = (int)a -48;
                cout<<a<<'-'<<x<<endl;
                group_n +=x*pow(10,k);
                k--;
                infile.get(a);
            }
            cout<<'\n';
            cout<<full_name<<' '<<group_n<<endl;




            // читает матрицы из файла и создает объекты класса


            infile.clear();
            infile.close();


            break;
        }

    }
    build_group(G_top,Top);

    cout<<'\n';
    console_output(Top,G_top);

    while (true){
        cout<<"Выберите один из пунктов меню:\n1 - вывести все данные в консоль\n2 - сохранить данные в текстовый файл"
              "\n3 - отредактировать данные о студенте\n4 - отредактировать данные о группе"
              "\n5 - Вывести в порядке возрастания номера групп, в которых соотношение «суммарный объем стипендии»"
              " / «общее количество баллов» превышает заданное значение\n0 - завершить программу"<<endl;
        cin>>choice;
        switch(choice){
            case 1:
                build_group(G_top,Top);
                console_output(Top,G_top);
                break;
            case 2:

                break;
            case 3:
                while (true){
                    cout<<"Что сделать \n1 - добавить нового студента\n2 - изменить информацию о существующем";
                    cin>>choice;
                    if (choice == 1){
                        console_input(Back,n,G_top);
                    }
                    else{
                        cout<<"Введите ФИО студента и номер его группы"<<endl;
                        full_name = make_name();
                        cin>>group_n;
                        p = find_student(Top, full_name, group_n);
                        if (p){
                            change_student(p,Top,Back);
                        }
                        else {
                            cout << "Такого студента нет в базе!\n Добавить?(1/0)";
                            cin >> choice;
                            if (choice == 1) {
                                cout<< Back->SNP<<endl;
                                console_input(Back,n,G_top);
                            }
                        }
                    }
                    cout<<"Продолжить исправления? (1/0)"<<endl;
                    cin>>choice;
                    if (choice == 0) {
                        break;
                    }
                    else{
                        continue;
                    }
                }
                break;
            case 4:
                while (true){
                    cout<<"Что сделать \n1 - добавить новyю группу\n2 - изменить информацию о существующей";
                    cin>>choice;
                    if (choice == 1){
                        cout<<n<<endl;
                        cout<<"Начните заполнять информацию о студентах новой группы"<<endl;
                        console_input(Back,n,G_top);
                        write_students(Top);
                    }

                    else{
                        cout<<"Введите номер группы, которую хотите редактировать: ";
                        cin>>old_group_n;
                        cout<<"1 - удалить группу\n2 - изменить номер  группы"<<endl;
                        cin>>choice;
                        if (choice == 1){
                            p = Top;
                            while(p){
                                while(p->group_n == old_group_n){
                                    del_student(p,Top,Back);
                                }
                                p = p->next;
                            }
                            cout<<"Группа успешно удалена из потока!"<<endl;
                        }
                        else{
                            cout<<"Введите новый номер группы:";
                            cin>>group_n;
                            p = Top;
                            while(p){
                                if(p->group_n == old_group_n){
                                    p->group_n = group_n;
                                }
                                p = p->next;
                            }
                            cout<<"Номер группы успешно изменен!"<<endl;
                        }
                        cout<<"Продолжить исправления? (1/0)"<<endl;
                        cin>>choice;
                        if (choice == 0) {
                            break;
                        }
                        else{
                            continue;
                        }

                    }

                }
                break;
            case 5:
                build_group(G_top,Top);
                id_task(G_top);
                break;
            default:
                cout<<"Program finished."<<endl;
                return 0;

        }
    }

}

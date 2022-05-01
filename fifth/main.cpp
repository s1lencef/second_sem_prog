#include <iostream>
#include <cstring>
#include <locale>

using namespace std;


struct Word{
    string info;
    Word *link;

};

Word* push( Word*Top,string n){
    Word*p;
    p = new Word;
    p->info = n;

    p->link = Top;
    Top = p;

    return Top;
}


int hash_function(string key) {
    int hashf = 0;
    for(char k :key){
        hashf = int(k) - 96;
        break;
    }

    return hashf % 26;
}


void inith(Word* (&p)[26]){
    for (int i=0; i<26; i++){
        p[i] = nullptr;
    }
}

void hpush(Word* (&p)[26],string s){
    Word *word;
    int key;
    key = hash_function(s);
    word = p[key];
    p[key] = push(word, s);

}

bool find(Word* (&p)[26],string s){
    Word *word;
    int key;
    key = hash_function(s);
    word = p[key];
    while(word){
        if (word->info == s){
            return true;
        }
        word=word->link;
    }
    return false;
}


void task(Word* (&words)[26],string s){
    while(true){
        cout<<"Введите слово, которое хотите найти(для окончания - 0)"<<endl;
        cin>>s;
        if (s == "0"){
            break;
        }
        if (find(words, s)){
            cout<<"Слово "<<s<<" найдено!\nКлюч - "<<hash_function(s)<<endl;
        }
        else{
            cout<<"Такого слова в таблице нет! "<<endl;
        }

    }
}


int main() {
    setlocale(0,"Russian");
    string s;
    Word *words[26];

    inith(words);

    cout<<"Введите последовательность слов(для окончания - 0)"<<endl;

    while (true){
        cin>>s;
        if (s == "0"){
            break;
        }
        hpush(words,s);
    }

    task(words,s);


    return 0;
}


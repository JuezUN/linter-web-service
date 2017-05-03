# include <bits/stdc++.h>
using namespace std;

int main(){
    int a;
    string name;
    while(cin>>name){
        int race = 0;
        for(int i = 0 ; i < name.length() ; i++) race += name[i]-'a'+1;
        cout << race << endl;
    }
}
#include<iostream>

using namespace std;

int main(){
    
    int A, B, C, D;
    int soma1, soma2;

    cin >> A >> B >> C >> D;
    
    soma1 = C + D;
    soma2 = D + A;

    if(B > C && D > A){
        if(soma1 > soma2){
            if(C > 0 && D > 0){
                if(A % 2 == 0)
                cout << "Valores aceitos" << endl;
            }
        }
    }
    else{
        cout << "Valores nao aceitos" << endl;
    }

    return 0;
}
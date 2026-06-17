#include<iostream>
#include<list>

using namespace std;

int main()  {
    int *vetor = NULL;
    int *p = NULL;
    int N;

    cin >> N;
    vetor = new int[N];

    p = vetor;

    for(int i = 0; i < N; i++)  {
        cin >> *p;
        p++;
    }

    p = vetor;

    for(int i = 0; i < N; i++)  {
        cout << *p << " ";
        p++;
    }


    delete []vetor;

    return 0;

}
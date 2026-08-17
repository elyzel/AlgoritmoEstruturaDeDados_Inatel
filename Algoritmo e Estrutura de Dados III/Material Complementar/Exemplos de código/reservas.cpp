#include <iostream>
#include <algorithm>
#include <stack>
#include<math.h>
using namespace std;

struct Ponto {
	int x, y;
};

Ponto p0;

void swap(Ponto &a, Ponto &b){
	Ponto aux = a;
	a = b;
	b = aux;
}

float area_triangulo(Ponto a, Ponto b, Ponto c){
	return (
		a.x * b.y - a.y * b.x +
		a.y * c.x - a.x * c.y +
		b.x * c.y - b.y * c.x
	) / 2.0;
}

int orientacao(Ponto p1, Ponto p2, Ponto p3){
	float aux = area_triangulo(p1,p2,p3);
	if(aux == 0)
		return 0;
	else if(aux < 0)
		return 1;
	else
		return 2;

}

float distancia(Ponto p1, Ponto p2){
	return sqrt((p1.y-p2.y)*(p1.y-p2.y) + (p1.x-p2.x)*(p1.x-p2.x));
}

float perimetro_vetor(Ponto pontos[], int n) {
	if (n<=2)
		return 0;
	Ponto atual, anterior, primeiro;
	float perimetro = 0;
	primeiro = atual = anterior = pontos[0];
	for (int i = 1; i < n; i++) {
		atual = pontos[i];
		perimetro += distancia(anterior, atual);
		anterior = atual;
	}
	perimetro += distancia(atual, primeiro);
	return perimetro;
}

float perimetro(stack<Ponto> pontos) {
	if (pontos.size() <= 2)
		return 0;
	Ponto atual, anterior, primeiro;
	float perimetro = 0;
	anterior = atual = primeiro = pontos.top();
	pontos.pop();
	while (!pontos.empty())
	{
		atual = pontos.top();
		perimetro += distancia(anterior, atual);
		pontos.pop();
		anterior = atual;
	}
	perimetro += distancia(atual, primeiro);
	return perimetro;
}

int compare(const void *vp1, const void *vp2)
{
   Ponto *p1 = (Ponto *)vp1;
   Ponto *p2 = (Ponto *)vp2;

   int o = orientacao(p0, *p1, *p2);
   if (o == 0)
		return (
			distancia(p0, *p2) >= distancia(p0, *p1)
		)? -1 : 1;

   return (o == 2)? -1: 1;
}

Ponto anterior_top(stack<Ponto> &S)
{
    Ponto p = S.top();
    S.pop();
    Ponto res = S.top();
    S.push(p);
    return res;
}

stack<Ponto> grahan_scan(Ponto pontos[], int n){
	int menor_y = 9999, menor_i;

	for(int i=0; i<n; i++){
		if(pontos[i].y < menor_y){
			menor_y = pontos[i].y;
			menor_i = i;
		} else if(pontos[i].y == menor_y){
			if(pontos[i].x < pontos[menor_i].x){
				menor_i = i;
			}
		}
	}
	swap(pontos[0], pontos[menor_i]);
	p0 = pontos[0];

	qsort(&pontos[1], n-1, sizeof(Ponto), compare);

	int m = 1;
	for (int i=1; i<n; i++)
	{
		while (i < n-1 && orientacao(p0, pontos[i], pontos[i+1]) == 0)
			i++;
		pontos[m] = pontos[i];
		m++;
	}

	stack<Ponto> fecho;
	if (m < 3)
		return fecho;


	fecho.push(pontos[0]);
	fecho.push(pontos[1]);
	fecho.push(pontos[2]);

	for(int i = 3; i < m; i++){

		while( fecho.size() > 1 &&
			orientacao(anterior_top(fecho), fecho.top(), pontos[i]) != 2
		){
			fecho.pop();
		}
		fecho.push(pontos[i]);
	}

	return fecho;
}

int main(){

	Ponto pontos[100];
	stack<Ponto> fecho;
	float perimetro_total = 0;
	int reservas, arvores;
	cin >> reservas;

	for (int i=0; i<reservas; i++) {
		cin >> arvores;
		for(int j=0; j<arvores; j++) {
			cin >> pontos[j].x >> pontos[j].y;
		}
		fecho = grahan_scan(pontos, arvores);
		perimetro_total += perimetro(fecho);
	}

	cout << perimetro_total << endl;

}
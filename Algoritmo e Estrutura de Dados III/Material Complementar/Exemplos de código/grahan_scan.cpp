#include <iostream>
#include <algorithm>
#include <stack>
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

float distancia_quadrada(Ponto p1, Ponto p2){
	return (p1.y-p2.y)*(p1.y-p2.y) + (p1.x-p2.x)*(p1.x-p2.x);
}

int compare(const void *vp1, const void *vp2)
{
   Ponto *p1 = (Ponto *)vp1;
   Ponto *p2 = (Ponto *)vp2;
 
   int o = orientacao(p0, *p1, *p2);
   if (o == 0)
		return (
			distancia_quadrada(p0, *p2) >= distancia_quadrada(p0, *p1)
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

void grahan_scan(Ponto pontos[], int n){
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
	
	if (m < 3)
		return;
	
	stack<Ponto> fecho;
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
	
	while (!fecho.empty())
	{
		Ponto p = fecho.top();
		cout << "(" << p.x << ", " << p.y <<")" << endl;
		fecho.pop();
	}
	
	return;
}

int main(){
	
	Ponto pontos[10];

	int n;
	cin >> n;

	for (int i=0; i<n; i++) {
		cin >> pontos[i].x >> pontos[i].y;
	}

	
	grahan_scan(pontos, n);

}
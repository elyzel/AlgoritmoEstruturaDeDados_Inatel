#include<iostream>
using namespace std;

struct ponto{
	int x, y;
};

float area_triangulo(ponto a, ponto b, ponto c){
	return (
		a.x * b.y - a.y * b.x + 
		a.y * c.x - a.x * c.y +
		b.x * c.y - b.y * c.x
	) / 2.0;
	
}

int lado(ponto a, ponto b, ponto p){
	float s = area_triangulo(a,b,p);
	if(s > 0){
		return 1;
	} else if(s < 0){
		return -1;
	} else {
		return 0;
	}
}

int main(){
	ponto a, b, c, p, q;
	cin >> a.x >> a.y;
	cin >> b.x >> b.y;
	cin >> c.x >> c.y;
	cin >> p.x >> p.y;
	cin >> q.x >> q.y;
	
	// float s = area_triangulo(a,b,c);
	// float s1 = area_triangulo(p,b,c);
	// float s2 = area_triangulo(a,p,c);
	// float s3 = area_triangulo(a,b,p);
	// 
	// float l1 = s1/s;
	// float l2 = s2/s;
	// float l3 = s3/s;
	// 
	// cout << l1 << endl << l2 << endl << l3 << endl;
	int posicao = lado(a,b,c);
	if(posicao == -1)
		cout << "C a direita" << endl;
	else if(posicao == 1)
		cout << "C a esquerda" << endl;
	else if(posicao == 0)
		cout << "C alinhado" << endl;
	
	posicao = lado(a,b,p);
	if(posicao == -1)
		cout << "P a direita" << endl;
	else if(posicao == 1)
		cout << "P a esquerda" << endl;
	else if(posicao == 0)
		cout << "P alinhado" << endl;
	
	posicao = lado(a,b,q);
	if(posicao == -1)
		cout << "Q a direita" << endl;
	else if(posicao == 1)
		cout << "Q a esquerda" << endl;
	else if(posicao == 0)
		cout << "Q alinhado" << endl;
	
}
/*
0 0
2 2
0 2
2 0
*/
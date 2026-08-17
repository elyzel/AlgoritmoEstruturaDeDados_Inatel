/*
O Papai Noel está pronto para iniciar suas viagens de entrega de presentes de Natal. A SBC (Sociedade Brasileira de Transportadores) determinou que o peso máximo de cada saco de presentes pode ser de até 50 kg, visando proteger os duendes — ajudantes do Papai Noel — de lesões nas costas ao carregar o trenó, e também evitar que o próprio Papai Noel se machuque durante as entregas.

Uma vez que todos os brinquedos estejam agrupados em pacotes, sua tarefa é ajudar criando um programa que combine o maior número possível de brinquedos dentro do limite de peso de 50 kg. Em seguida, Y-URI, o chefe dos duendes, colocará esse saco no trenó para que o Papai Noel possa seguir viagem.

Entrada
A entrada contém vários casos de teste. A primeira linha contém um inteiro N, que representa o número de casos de teste ou o número de viagens do Papai Noel. Cada viagem começa com um inteiro Pac (1 < Pac < 100), indicando a quantidade de pacotes disponíveis para aquela viagem. As Pac linhas seguintes conterão dois números inteiros, qt (1 ≤ qt < 300) e weight (1 ≤ weight ≤ 50), representando, respectivamente, a quantidade de brinquedos e o peso de cada pacote, separados por um espaço.

Saída
Para cada caso de teste, seu programa deve imprimir três linhas com as mensagens correspondentes em português, conforme mostrado abaixo, seguidas por uma linha em branco. A primeira linha deve conter a quantidade de brinquedos que Y-URI carregará no trenó. A segunda linha contém o peso total dos brinquedos. A última linha conterá a quantidade de pacotes que sobraram para uma viagem futura. No segundo caso de teste abaixo, por exemplo, 106 brinquedos foram selecionados para a viagem, agrupados em pacotes de 24, 2, 3, 4, 5 e 8 kg, totalizando 46 kg.

Para a maior quantidade de brinquedos selecionada, haverá apenas uma possibilidade de peso total ou de pacotes restantes.
*/

#include<iostream> //Biblioteca inicial
#include<algorithm> //Biblioteca com funções prontas
#include<vector> //Biblioteca para criar arrays dinâmicos

using namespace std;

int main()  {
    int N;  //Quantidade de viagens
    if(cin >> N){
        while(N--)  {
            int Pac;    //Quantidade de pacotes disponíveis
            cin >> Pac;

            vector<int> qt(Pac + 1);
            vector<int> peso(Pac + 1);

            for(int i = 1; i <= Pac; i++)   {
                cin >> qt[i] >> peso[i];
            }

            int cpdd = 50;
            //Tabela DP: dp[pacotes][peso]
            vector<vector<int>> dp(Pac + 1, vector<int>(cpdd + 1, 0));

            //Preenchimento da tabela de decisoes
            for(int i = 1; i <= Pac; i++)   {
                for(int w = 0; w <= Pac; w++)   {
                    if(peso[i] <= w)    {
                        dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - peso[i]] + qt[i]);
                    }   else    {
                        dp[i][w] = dp[i - 1][w];
                    }
                }
            }

            int brinquedos = dp[Pac][cpdd];

            //Rastreamento de volta para achar peso total e pacotes sobrantes
            int w = cpdd;
            int peso_total = 0;
            int pacotes_levados = 0;

            for(int i = Pac; i > 0; i--)    {
                if(dp[i][w] != dp[i - 1][w])    {
                    peso_total += peso[i];
                    pacotes_levados++;
                    w -= peso[i];   //Subtrai o peso do pacote escolhido
                }
            }

            int pacotes_sobrando = Pac - pacotes_levados;

            //Saída

            cout << brinquedos << " brinquedos" << endl;
            cout << "Peso: " << peso_total << " kg" << endl;
            cout << "sobra(m) " << pacotes_sobrando << " pacote(s)" << endl;

        }
    }

    return 0;
    
}

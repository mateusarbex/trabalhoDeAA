#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <vector>
#include <math.h>

using namespace std;

string vetor_type;

/** params (tamanho desejado, definir se o vetor é aleatório, definir se o vetor é invertido)
Método para criar o arquivo de texto onde será aplicado os métodos
*/
void createList(int tam, bool isRandom, bool isInverted){

    ofstream myfile;
    myfile.open("arquivo.txt");
    srand (time(NULL));

    if(isRandom){
        for(int i = 0; i < tam; i++){
            int random = rand() % tam;
            myfile << random << " ";
        }
    }
    else if(isInverted){
        for(int i = tam - 1; i >= 0; i--){
            myfile << i << " ";
        }
    }
    else{
        for(int i = 0; i < tam; i++){
            myfile << i << " ";
        }
    }
    if(isRandom){
        vetor_type = "vetor aleatorio";
    }
    else if(isInverted){
        vetor_type = "vetor invertido";
    }
    else{
        vetor_type = "vetor ordenado";
    }
    myfile.close();
}



/** params (vetor para preencher, tamanho para definir)
Função para retornar um array com uma sequência de números providenciada em um arquivo de texto
return Vetor
*/
void getArray(vector<int> &arr,unsigned int *arr_size){

    string line,escolha;
    cout << "escolha qual arquivo voce quer utilizar\n\n" << "0 - usar o mesmo arquivo\n\n\n1 - aleatorio 1000000 elementos\n2 - aleatorio 100000 elementos\n3 - aleatorio 10000 elementos\n";
    cout << "4 - ordenado 1000000 elementos\n5 - ordenado 100000 elementos\n6 - ordenado 10000 elementos\n";
    cout << "7 - invertido 1000000 elementos\n8 - invertido 100000 elementos\n9 - invertido 10000 elementos\n\n";
    cout << "10 - aleatorio escolher tamanho\n11 - ordenado escolher tamanho\n12 - invertido escolher tamanho\n\n";
    getline(cin,escolha);

    switch(stoi(escolha)){
        case 1:
            createList(1000000, true, false);
            break;
        case 2:
            createList(100000, true, false);
            break;
        case 3:
            createList(10000, true, false);
            break;
        case 4:
            createList(1000000, false, false);
            break;
        case 5:
            createList(100000, false, false);
            break;
        case 6:
            createList(10000, false, false);
            break;
        case 7:
            createList(1000000, false, true);
            break;
        case 8:
            createList(100000, false, true);
            break;
        case 9:
            createList(10000, false, true);
            break;
        case 10:
            cout<< "\nDiga o tamanho do vetor\n";
            getline(cin,escolha);
            createList(stoi(escolha), true, false);
            break;
        case 11:
            cout<< "\nDiga o tamanho do vetor\n";
            getline(cin,escolha);
            createList(stoi(escolha), false, false);
            break;
        case 12:
            cout<< "\nDiga o tamanho do vetor\n";
            getline(cin,escolha);
            createList(stoi(escolha), false, true);
            break;
        case 0:
            break;
        default:
            break;
    }

    cout << "\n";

    ifstream myfile("arquivo.txt");
    int i, j=0;
    string tempChar;

    if(myfile.is_open()){

        cout << "lendo o arquivo....\n";

        while(getline(myfile,line)){
            for(i = 0; i<=line.length(); i++){
                if(line[i]==' ' || line[i]=='\n' || i==line.length()) {
                    if(tempChar.empty()!=1){
                        j++;
                        arr.resize(j);
                        arr[j-1] = stoi(tempChar);
                        (*arr_size)++;
                    }
                tempChar = "";
                }
                else{
                    tempChar = tempChar+line[i];
                }

            }
        }
        myfile.close();
        return;
    }
    else{

        cout << "falha ao tentar acessar arquivo";

        myfile.close();
    }
    return;
}




/**params (vetor principal, index do inicio, index do topo)
Função para que particiona o vetor principal utilizando um número como pivô para ordenar os números maiores depois e o menores antes
return novo index para partição
*/
int particao(vector<int> &arr, unsigned int inicio, unsigned int topo){

    int pivo = arr[topo];
    int i, j, aux;

    i = (inicio - 1);

    //for para fazer a troca com todos os números menores que o pivô
    for(j = inicio; j <= topo - 1; j++){
        if(arr[j] < pivo){
            i++;
            aux = arr[i];
            arr[i] = arr[j];
            arr[j] = aux;
        }

    }
    aux = arr[i + 1];
    arr[i + 1] = arr[topo];
    arr[topo] = aux;

    return (i+1);

}

/** params (vetor principal, index do inicio, index do topo)
Metódo para dividir o vetor enquanto o topo é maior que o inicio
*/

void quickSort(vector<int> &vetor, int inicio, int topo){
    if(inicio < topo){
        int indexParticao = particao(vetor, inicio, topo);
        quickSort(vetor,inicio,indexParticao - 1);
        quickSort(vetor, indexParticao + 1, topo);
    }

    return;
}

/** params (vetor principal, index para o vetor esquerdo, index para merge, index para o vetor direito
Metódo para juntar os arrays que são divididos no vetor principal
*/
void juntar(vector<int> &vetor, int esquerdo,int merg, int direito){

    int i, j, k;
    int n1 = merg - esquerdo + 1;
    int n2 = direito - merg;

    int *esqArray = new int[n1];
    int *dirArray = new int[n2];

    for(i = 0; i < n1; i++){
        esqArray[i] = vetor[esquerdo + i];
    }
    for(j = 0; j < n2; j++){
        dirArray[j] = vetor[merg+1+j];
    }

    i=0;
    j=0;
    k=esquerdo;

    //Aqui se faz a comparação para verificar se um elemento de cada vetor é menor ou igual ao outro para ordenar no vetor principal
    while (i<n1 && j<n2){
        if(esqArray[i]<=dirArray[j]){
            vetor[k] = esqArray[i];
            i++;
        }
        else{
            vetor[k] = dirArray[j];
            j++;
        }
        k++;
    }

    //os números que sobraram serão jogados de volta para o vetor principal
    while(i<n1){
        vetor[k] = esqArray[i];
        i++;
        k++;
    }

     while (j < n2){
        vetor[k] = dirArray[j];
        j++;
        k++;
    }

    return;
}

/** params (vetor principal, tamanho do vetor)
Método para ordernar o vetor fazendo comparação com o termo seguinte e trocando de posição
*/
void bubblesort(vector<int> &vetor,int n){

	int x = 0, z = 0;
	long int aux = 0;

	//for para fazer comparação do valor atual e próximo onde possívelmente ocorrerá a troca
	for(x = 0; x < n; x++){
		for(z = 0; z < n - x; z++){
		 	if(vetor[z] > vetor[z+1]){
		 		aux = vetor[z];
		 		vetor[z] = vetor[z+1];
		 		vetor[z+1] = aux;
			 }
		}
	}

	return;
}

/** params (vetor principal, tamanho do vetor)
Método para ordernar o vetor levando todos números maiores que o valor na posição indicada para o lado direito
*/
void insertionSort(vector<int> &vetor,int tam){

	int x, y = 0, aux = -1;

	for(x = 1; x <= tam; x++){
		aux = vetor[x];
		y = x - 1;
        while((y >= 0) && (aux < vetor[y])){
            vetor[y + 1] = vetor[y];
            y--;
        }
	vetor[y + 1] = aux;
    }
    return;
}

/** params (vetor principal, index esquerdo, index direito)
    Método para separação em 2 do vetor principal, criando um vetor esquerdo e um vetor direito
    return null;
*/
void mergeSort(vector<int> &vetor,int iesquerdo,int idireito){
    if( iesquerdo < idireito ){

        int merg = ( iesquerdo + idireito )/2;

        mergeSort(vetor, iesquerdo, merg);
        mergeSort(vetor, merg+1, idireito);
        juntar(vetor, iesquerdo, merg, idireito);
    }
    return;
}

/** params (vetor principal, tamanho do vetor)
    Método de impressão do vetor principal
    return null;
*/
void mostrarVetor(vector<int> vetor,int n){

    int i;

    cout << "\n";

    for(i=0; i<n;i++){
        cout << vetor[i] << " ";
    }

    cout << "\n";
}
void outputArquivo(vector<int> &vetor, int n){

    ofstream logFile;
    int i;

    logFile.open("resultado.txt");
    for(i = 0; i < n; i++){
        logFile << vetor[i] << " ";
    }
    cout << "\nResultado gravado em resultado.txt!\n\n";
    return;
}

void writeLog(double time, string method, int vetor_size){
    ofstream lastSort;
    lastSort.open("sort_logs.txt", std::ios::app);
    lastSort << "Tipo de vetor: " << vetor_type;
    lastSort << "\nMetodo: "<< method;
    lastSort << "\nTempo ocorrido: " << time << "s";
    lastSort << "\nNumero de elementos: " << vetor_size;
    lastSort << "\n\n";
    lastSort.close();
    cout << "\nlog adicionado em sort_logs.txt\n\n";

}


int main(){

    while(1 > 0){

        unsigned int vetor_size = 0;
        string escolha,metodo;
        vector<int> vetor;
        double tempo_ocorrido;

        getArray(vetor,&vetor_size);

        cout << "\narray criado!\n";
        cout << "\nEscolha o metodo de ordenacao:\n\n1) Quick Sort\n2) Merge Sort\n3) Bubble Sort\n4) Insertion Sort\n\n";

        getline(cin,escolha);

        switch(stoi(escolha)){
            case 1:{
                metodo = "Quick Sort";
                cout << "[S]: Iniciando Quick Sort..." << endl << endl;
                clock_t begin = clock();
                quickSort(vetor, 0, vetor_size - 1);
                tempo_ocorrido = double(clock() - begin) / CLOCKS_PER_SEC;
                break;
            }
            case 2:{
                metodo = "Merge Sort";
                cout << "[S]: Iniciando Merge Sort..." << endl << endl;
                clock_t begin = clock();
                mergeSort(vetor, 0, vetor_size - 1);
                tempo_ocorrido = double(clock() - begin) / CLOCKS_PER_SEC;
                break;
            }
            case 3:{
                metodo = "Bubble Sort";
                cout << "[S]: Iniciando Bubble Sort..." << endl << endl;
                clock_t begin = clock();
                bubblesort(vetor, vetor_size - 1);
                tempo_ocorrido = double(clock() - begin) / CLOCKS_PER_SEC;
                break;
            }
            case 4:{
                metodo = "Insertion Sort";
                cout << "[S]: Iniciando Insertion Sort..." << endl << endl;
                clock_t begin = clock();
                insertionSort(vetor, vetor_size - 1);
                tempo_ocorrido = double(clock() - begin) / CLOCKS_PER_SEC;
                break;
            }
        }

        system("cls");

        cout<< "Deseja mostrar o resultado? Responda com '1' para sim ou '0' para nao\n\n";

        getline(cin,escolha);

        switch(stoi(escolha)){
            case 0:
                outputArquivo(vetor, vetor_size);
                cout << "\ntamanho do vetor: " << vetor_size;
                cout << "\ntempo ocorrido: " << fixed << tempo_ocorrido << " segundos\n";
                break;
            case 1:
                mostrarVetor(vetor, vetor_size);
                cout << "\ntamanho do vetor: " << vetor_size;
                cout << "\ntempo ocorrido: " << fixed << tempo_ocorrido << " segundos\n";
                break;
        }
        writeLog(tempo_ocorrido, metodo, vetor_size);
    }
    return 0;
}

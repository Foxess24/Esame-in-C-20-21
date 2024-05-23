#include <stdio.h>
#define N 10

typedef struct{
	float a;
	float b;
	float c;
	char op1;           
	char op2;
}espressione;

int caricamento_dati(FILE*,espressione[],int*);
void ricerca_operatori(espressione[],int,char[]);
float valuta_espressione(float,float,float,char,char);
void stampa_risultato(espressione[],int);

int main(){
	char operatori[4]={'+','-','*','/'};
	espressione dati[N];
	int num=0;
	int R;
	FILE* fp=NULL;
	fp = fopen("dati.txt","r");
	if(fp==NULL){
		printf("Errore apertura file.\n");
	}else{
		R=caricamento_dati(fp,dati, &num);
		if(R==1){
			return 0;
		}
		 ricerca_operatori(dati,num,operatori);
		 stampa_risultato(dati,num);
		 
	}
	fclose(fp);
	return 0;
}

int caricamento_dati(FILE* f,espressione dati[],int* n){
	int r=3;
	while(*n < N && r != EOF){
		r = fscanf(f,"%f %f %f", &dati[*n].a, &dati[*n].b, &dati[*n].c);
		if(r!=3 && r!=EOF){
		    return 1;
		}else if(r == 3){
			*n= *n+1;
		}   
	}
	return 0;
}

void ricerca_operatori(espressione dati[],int n,char operatori[]){
	int i=0;
	int A=0,B=0;
	float a;
	while(i<n){
		for(A=0;A<4;A++){	
			B=0;
			while(B<4){
				a=valuta_espressione(dati[i].a,dati[i].b,dati[i].c,operatori[A],operatori[B]);
				if(a!=0.0000){
					dati[i].op1= '?';
			        dati[i].op2= '?';
			        B++;
				}else{
				dati[i].op1= operatori[A];
				dati[i].op2= operatori[B];
				break;
				}
			}
			if(dati[i].op1!='?'&&dati[i].op2!='?'){
			break;
			}
		}
	i++;	
	}
}

float valuta_espressione(float A,float B,float C,char OP1,char OP2){
	if(OP1=='+'&& OP2=='+'){
		return A+B+C;
	}else if(OP1=='+'&& OP2=='-'){
		return A+B-C;
	}else if(OP1=='+'&& OP2=='*'){
		return A+B*C;
	}else if(OP1=='+'&& OP2=='/'){
		return A+B/C;
	}else if(OP1=='-'&& OP2=='+'){
	    return A-B+C;
	}else if(OP1=='-'&& OP2=='-'){
		return A-B-C;
	}else if(OP1=='-'&& OP2=='*'){
		return A-B*C;
	}else if(OP1=='-'&& OP2=='/'){
		return A-B/C;
	}else if(OP1=='*'&& OP2=='+'){
		return A*B+C;
	}else if(OP1=='*'&& OP2=='-'){
		return A*B-C;
	}else if(OP1=='*'&& OP2=='*'){
		return A*B*C;
	}else if(OP1=='*'&& OP2=='/'){
		return A*B/C;
	}else if(OP1=='/'&& OP2=='+'){
		return A/B+C;
	}else if(OP1=='/'&& OP2=='-'){
		return A/B-C;
	}else if(OP1=='/'&& OP2=='*'){
		return A/B*C;
	}else if(OP1=='/'&& OP2=='/'){
		return A/B/C;
	}
}

void stampa_risultato(espressione dati[], int n){
	int i;
	for(i=0;i<n;i++){
		if(dati[i].op1 != '?' && dati[i].op2 != '?'){
			printf("%f %c %f %c %f = 0\n", dati[i].a, dati[i].op1, dati[i].b, dati[i].op2, dati[i].c);
		}else{
			printf("%f, %f, %f: nessuna soluzuione\n", dati[i].a, dati[i].b, dati[i].c);
		}
    }
}







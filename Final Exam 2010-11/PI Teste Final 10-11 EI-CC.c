/**
 * @author Pirata
 * @version 2011.07
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXTEXTO 100

/* Questão 1 - Cálculo Numérico */

int somait(int a,int b)
{
	int res=0;
	if((a % 3) != 0)
	{
		while((a % 3) != 0)
			a++;
	}
	while(a <= b)
	{
		if((a % 2) != 0)
			res += a;
		a += 3;
	}
	return res;
}

int somarec(int a,int b)
{
	if(a <= b)
	{
		if((a % 3) == 0)
		{
			if((a % 2) == 0)
				return somarec((a + 3),b);
			else
				return a + somarec((a + 3),b);
		}
		else
			return somarec((a + 1),b);
	}
	else
		return 0;
}

/* Questão 2 - Arrays/Strings */
char evogal(char c)
{
	char res = 'n';
	switch(c)
	{
		case 'a' :
		case 'e' :
		case 'i' :
		case 'o' :
		case 'u' :
		case 'A' :
		case 'E' :
		case 'I' :
		case 'O' :
		case 'U' : res = 's';
	}
	return res;
}

char* pcript(char f[])
{
	int vogais = 0,lng = 0,ia = 0,ib = 0;
	char * res = NULL;
	if(f)
	{
		while(f[lng] != '\0')
		{
			if(evogal(f[lng]) == 's')
				vogais++;
			lng++;
		} 
		res = malloc((lng + (2 * vogais) + 1) * sizeof(char));
		while(ia < lng)
		{
			if(evogal(f[ia]) == 's')
			{
				res[ib] = f[ia];
				ib++;
				res[ib] = 'p';
				ib++;
			}
			res[ib] = f[ia];
			ia++;
			ib++;
		}
		res[ib] = '\0';
	}
	return res;
}

/* Questão 3 - Ordenação */

typedef struct slint
{
	int *array;
	int nelems;
} lint;

lint orderLint(lint li)
{
	if(li.nelems != 0)
	{
		char flag='s';
		int i,fim,aux;
		fim = li.nelems - 1;
		while(flag == 's')
		{
			i = 0;
			flag = 'n';
			while(i < fim)
			{
				if(li.array[i] > li.array[i+1])
				{
					aux = li.array[i];
					li.array[i] = li.array[i+1];
					li.array[i+1] = aux;
					flag = 's';
				}
				i++;
			}
		}
	}
	else
	{
		free(li.array);
		li.array = NULL;
		li.nelems = 0;
	}
	return li;
}

lint leNums(int n)
{
	lint res;
	int input,i = 0;
	int * lista = NULL;
	lista = (int*) malloc(n * sizeof(int));
	printf("Escreve os %d numeros carregando em ENTER após cada um.\n",n);
	while(i < n)
	{
		scanf("%d",&input);
		lista[i] = input;
		i++;
	}
	res.array = lista;
	res.nelems = i;
	return res;
}

void imprimeFile(lint li)
{
	FILE * fp;
	int i = 0;
	fp = fopen("output.txt","w");
	while(i < li.nelems)
	{
		fprintf(fp,"%d\n",li.array[i]);
		i++;
	}
	fclose(fp);
}

/* Função principal */
void outputFile()
{
	lint res;
	int nums;
	printf("Quantos inteiros queres que o programa leia?\n");
	scanf("%d",&nums);
	res = leNums(nums);
	res = orderLint(res);
	imprimeFile(res);
}

/* Questão 4 - Modelação de Estruturas de Dados
 * Nota: hipóteses infinitas de resposta. */

typedef struct scarta
{
	char valor;
/* {'2','3','4','5','6','7','8','9','A'(representa o 10),'D'(representa a Dama),'J'(representa o Valete),'R'(representa o Rei),'a'(representa o Ás)} - uso estes caracteres supondo que esta é a ordenação de valores do menor para o maior, podendo então o próprio caracter ser usado para comparação. */
	char naipe;
/* {'E'(espadas),'C'(copas),'P'(paus),'O'(ouros)} */
} carta;

typedef struct smao
{
	carta jogo[13]; // o máximo de cartas que pode ter é 13
	int codigo[13]; // cada posição do array de inteiros corresponde à posição do array de cartas, podendo neste 'codigo' ser os inteiros usados como codigo, podendo posteriormente dizer se a carta já foi jogada e/ou em que jogada foi jogada ou algum outro sistema que seja relevante
} mao;

typedef struct sdescarte
{
	carta pilha[4]; // as cartas jogadas
	int jogador[4]; // jogador a que corresponde cada carta
} descarte;

typedef struct svazas
{
	descarte elem;
	struct svazas *seg;
} *vazas,NODOVAZAS;

/* Questão 5 - Estruturas de Dados */

typedef struct sTarefa
{
	int dia;
	int hora;
	char *tipo;
	char *descricao;
} Tarefa;

typedef struct sLLTarefa
{
	Tarefa t;
	struct sLLTarefa *seg;
} *LLTarefa, NodoLLTarefa;

typedef struct sAgendaMensal
{
	int mes;
	LLTarefa ag[31];
} AgendaMensal;

// a)
Tarefa leTarefa()
{
	Tarefa res;
	int input;
	char texto[MAXTEXTO];
	printf("Indique o dia da tarefa: ");
	scanf("%d",&input);
	res.dia = input;
	printf("Indique a hora: ");
	scanf("%d",&input);
	res.hora = input;
	printf("Indique o tipo: ");
	fgets(texto,MAXTEXTO - 1,stdin);
	input = strlen(texto);
	if(texto[input] == '\n')
	{
		texto[input] = '\0';
		input--;
	}
	res.tipo = (char*) malloc((input+1)* sizeof(char));
	strcpy(res.tipo,texto);
	printf("Descreva a tarefa: ");
	fgets(texto,MAXTEXTO - 1,stdin);
	input = strlen(texto);
	if(texto[input] == '\n')
	{
		texto[input] = '\0';
		input--;
	}
	res.descricao = (char*) malloc((input+1) * sizeof(char));
	strcpy(res.descricao,texto);
	return res;
}

// b)
LLTarefa pushLLT(LLTarefa llt,Tarefa t)
{
	LLTarefa novo;
	novo = (LLTarefa) malloc(sizeof(NodoLLTarefa));
	novo -> t.dia = t.dia;
	novo -> t.hora = t.hora;
	novo -> t.tipo = t.tipo;
	novo -> t.descricao = t.descricao;
	novo -> seg = llt;
	return novo;
}	

AgendaMensal pushTarefa(AgendaMensal a,Tarefa t)
{
	int i;
	i = t.dia - 1;
	a.ag[i] = pushLLT(a.ag[i],t);
	return a;
}

// c)
LLTarefa sortedIn(LLTarefa llt,Tarefa t)
{
	if((!llt) || (t.hora < llt -> t.hora))
		return pushLLT(llt,t);
	else
	{
		llt -> seg = sortedIn(llt -> seg,t);
		return llt;
	}
}

AgendaMensal sortedTarefas(AgendaMensal a,Tarefa t)
{
	int i;
	i = t.dia - 1;
	a.ag[i] = sortedIn(a.ag[i],t);
	return a;
}

// d)
void printTarefa(Tarefa t)
{
	printf("\n ----- %d H - %s ----- \n\nDescrição: %s\n\n\n",t.hora,t.tipo,t.descricao);
}

void printLista(LLTarefa llt)
{
	if(llt)
	{
		printTarefa(llt -> t);
		printLista(llt -> seg);
	}
}

void listarTarefas(AgendaMensal a,int dia)
{
	printLista(a.ag[dia - 1]);
}


// TESTES

/*EX 1
 * int main()
{
	int res;
	res = somarec(1,20);
	printf("%d\n",res);
	res = somait(1,20);
	printf("%d\n",res);
	return 1;
}*/

/*EX 2
 * int main()
{
	char *st = "Está tudo bem por aqui colega?";
	char *res = NULL;
	res = pcript(st);
	printf("%s\n",res);
	return 1;
}*/

/*EX 3 */
int main()
{
	outputFile();
	return 1;
}

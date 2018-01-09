/**
 * @autor Pirata
 * @version 2011.07
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Questão 1 - Cálculo Numérico */

typedef struct sFraccao
{
	int num;
	int den;
} Fraccao;

// a)
/* Máximo divisor comum entre dois números; suposto a > b */
int mdc(int a,int b)
{
	int aux;
	while(a % b != 0)
	{
		aux = a;
		a = b;
		b = (aux % b);
	}
	return b;
}

/* Simplifica uma fracção à sua forma irredutível. */
Fraccao simplifica(Fraccao f)
{
	int div;
	if(f.num >= f.den)
		div = mdc(f.num,f.den);
	else
		div = mdc(f.den,f.num);
/* Reduz a fracção utilizando o máximo divisor comum obtido entre o numerador e o denominador. */
	f.num = f.num/div;
	f.den = f.den/div;
	return f;
}

// b)
Fraccao somafrac(Fraccao f1,Fraccao f2)
{
	Fraccao res;
	res.num = (f1.num * f2.den) + (f2.num * f1.den);
	res.den = f1.den * f2.den;
/* Depois da soma, a fracção e simplificada. */
	res = simplifica(res);
	return res;
}

/* Questão 2 - Arrays */
// a) Função que sustitui os espaços por hífens, e devolve o numero de substituições feitas.
int subesp(char *s)
{
	int i=0,count=0;
	while(s[i] != '\0')
	{
		if(s[i] == ' ')
		{
			s[i] = '-';
			count++;
		}
		i++;
	}
	return count;
}

// b) Remove caracteres que sejam iguais que estejam seguidos. 
int remCons (char *s)
{
	int i=0,desloc=0;
	while(s[i] != '\0')
	{
		s[i+1] = s[i+1+desloc]; /* Linha mais importante, o deslocamento */
		if(s[i] == s[i+1])
			desloc++;
		else
			i++;
	}
	return i; /* Para melhorar ainda poderia haver uma libertação do espaço desde o fim da reduzida até ao fim da original. */
}


/* Questão 4 - Estruturas Dinâmicas */

// AG = Indivíduo * Pai * Mãe 
//			| desconhecido
// Indivíduo = nome * BI * data-nascimento
// Pai = Mãe = AG

//a) Criar as estruturas.
typedef char * BI;

typedef struct sDate
{
	int dia;
	int mes;
	int ano;
} Date;

typedef struct sIndividuo
{
	char *nome;
	BI bi;
	Date bday;
} Individuo;

typedef struct sArvGenoa
{
	Individuo ind;
	struct sArvGenoa *mae;
	struct sArvGenoa *pai;
} *ArvGenoa,NAG;

// b) Listar todos os individuos da arvore.
void imprimeInd(Individuo tal)
{
	printf("Nome: %s - BI: %s - Data de Nascimento: %d/%d/%d .\n",tal.nome,tal.bi,tal.bday.dia,tal.bday.mes,tal.bday.ano);
}

void ListArvGenoa(ArvGenoa a)
{
	if(a)
	{
		imprimeInd(a -> ind);
		ListArvGenoa(a -> mae);
		ListArvGenoa(a -> pai);
	}
}

// c) Listaos individuos por data de nascença. 
typedef struct sIndivList
{
	Individuo indiv;
	struct sIndivList *seg;
} *IndivList,NIL;

IndivList Push(Individuo i,IndivList l)
{
	IndivList aux = (IndivList) malloc(sizeof(NIL));
	aux -> indiv = i;
	aux -> seg = l;
	return aux;
}

/* Função boleana ('s'im ou 'n'ao) que verifica se a data 'a' é anterior à data 'b'. */
char datOrd(Date a,Date b)
{
	char res;
/* Verifica o ano primeiro, depois o mês e por fim o dia. */
	if((a.ano < b.ano) || ((a.ano == b.ano) && (a.mes < b.mes)) || ((a.ano == b.ano) && (a.mes == b.mes) && (a.dia < b.dia)) || ((a.ano == b.ano) && (a.mes == b.mes) && (a.dia == b.dia)))
		res = 's';
	else
		res = 'n';
	return res;
}

/* Função de inserção do individuo na lista de individuos, (após analisar a data). */
IndivList InsOrder(Individuo i,IndivList l)
{ 
	if((!l) || (datOrd(i.bday,l -> indiv.bday) == 's'))
		l = Push(i,l);
	else
		l -> seg = InsOrder(i,l -> seg);
	return l;
}

IndivList IPNaux(ArvGenoa a,IndivList l)
{
	if(a)
	{
		l = InsOrder(a -> ind,l);
		l = IPNaux(a -> mae,l);
		l = IPNaux(a -> pai,l);
	}
	return l;
}

IndivList IndivPorNasc(ArvGenoa a)
{
	return IPNaux(a,NULL);
}

// d) 

/* Sobe tantos níveis, quantos os pedidos ('nivel'), a partir do individuo, seguindo a raiz da mãe e a raiz do pai. */
IndivList parentesco(ArvGenoa a,int nivel,IndivList l)
{
	if(a)
	{
		if(!nivel)
			l = Push(a -> ind,l);
		else
		{
			l = parentesco(a -> mae,nivel-1,l);
			l = parentesco(a -> pai,nivel-1,l);
		}
	}
	return l;
}

/* Procura o individuo com o BI igual ao pedido na árvore e aplica-lhe a função 'parentesco'. */
IndivList auxAvos(ArvGenoa a,BI b,IndivList l)
{
	if(a)
	{
		if(strcmp(b,a -> ind.bi) == 0)
			l = parentesco(a,2,l);
		else
		{
			l = auxAvos(a -> mae,b,l);
			l = auxAvos(a -> pai,b,l);
		}
	}
	return l;
}

IndivList Avos(ArvGenoa a,BI b)
{
	return auxAvos(a,b,NULL);
}

// e) Calcular as Gerações é o mesmo que calcular a altura máxima da árvore. 
int max2(int a,int b)
{
	return (a < b)?b:a; /* == if(a < b) {return b;} else {return a;}*/
}

int Geracoes(ArvGenoa a)
{
	if(!a)
		return 0;
	else
		return 1 + max2(Geracoes(a -> mae),Geracoes(a -> pai));
}

// f) Retornar os descendentes dum individuo.

/* Funçao boleana (1 ou 0) que analisa se o individuo 'i' tem o numero de BI 'b'. */
int donoBI(BI b,Individuo i)
{
	if(!strcmp(b,i.bi))
		return 1;
	else
		return 0;
}

/* Analisa se algum individuo da arvore possui o numero de BI 'b'. */
int pertenceBI(ArvGenoa a,BI b)
{
	if(!a)
		return 0;
	else
	{
		if(donoBI(b,a -> ind))
			return 1;
		else
			return ((pertenceBI(a -> mae,b)) || (pertenceBI(a -> pai,b)));
	}
}

/* Adiciona os descendentes à lista, mas apenas se as arvores do pai ou da mae, tiverem '1' como retorno da função pertenceBI.
 * Caso contrário, se apenas o individuo raiz pertencer, ele é o elemento do qual queremos saber os descendentes. */
IndivList DDaux(ArvGenoa a,BI b,IndivList l)
{
	if((pertenceBI(a,b) == 1) && ((pertenceBI(a -> pai,b)) || (pertenceBI(a -> mae,b))))
	{
		l = Push(a -> ind,l);
		l = DDaux(a -> mae,b,l);
		l = DDaux(a -> pai,b,l);
	}
	return l;
}

IndivList Descendentes(ArvGenoa a,BI b)
{
	return DDaux(a,b,NULL);
}

/*TESTE*/

int main()
{
	char s[]="111 221 31 22";
	int a;
	a = subesp(s);
	printf("%s - %d\n",s,a);
	return 1;
}

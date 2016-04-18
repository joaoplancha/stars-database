#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LIM 1000
#define LIM2 6000

char linhas[6000];

int stat,ver,ver2;


typedef struct ESTRELAS{ //estrutura que armazena os dados das estrelas
	
	char * nome;
	float massa;
	char * classe;
	char * constelacao;
	}dados;          

dados *estrelas;


//retorna o numero de linhas do ficheiro menos uma
int n_linhas()
{
  int n=0;
  char l;
  
  FILE *f;
  
  if((f=fopen("stars.dat","r"))==NULL) //abre o ficheiro se for possível
  { 
    printf("Impossivel Abrir ficheiro stars.dat\n");
    exit(1);
  }

  if (fgetc(f)==EOF)
  {printf("ficheiro vazio\n\n"); // verifica se o ficheiro esta vazio
  exit(3);
  }

  do
    {
      l = fgetc(f);
   
     if (l=='\n')
	n=n+1;
    }while (l!=EOF);
  
  fclose(f);

  return n;
}


//preenche a tabela estrelas com os dados do ficheiro
void preenche_tabela()
{

  int j=0;
  int i=0;
  
  char * c;
  char l;
  
  FILE *f;
  if((f=fopen("stars.dat","r"))==NULL) //abre o ficheiro se for possível
  { 
    printf("Impossivel Abrir ficheiro stars.dat\n");
    exit(1);
  }

  while(i<=n_linhas())
    {
      
      fgets(linhas,LIM2,f);  //poe na string linha uma linha do ficheiro
      c=strtok(linhas,";");
      estrelas[i].nome=strdup(c);
      c=strtok(NULL,";");
      sscanf(c,"%f",&estrelas[i].massa);
      c=strtok(NULL,";");
      estrelas[i].classe=strdup(c);
      c=strtok(NULL,";");
      estrelas[i].constelacao=strdup(c);
      i++;
    
    }    
 

}


//mostra a tabela no ecra
void imprime_tabela()
{
  
  int i=0;

  while (i<=n_linhas())
    { 
      
      printf("--- %s ---\n",estrelas[i].nome);
      printf("%7.2f MSol  ",estrelas[i].massa);
      printf("Class: %s  ",estrelas[i].classe);
      printf("Constelacao: %s\n\n",estrelas[i].constelacao);

      i++;
    
    }
}


//grava a tabela actual para o ficheiro
void escreve_tabela_ficheiro()
{
  
  FILE *f;
  
  int n=n_linhas();
  int i;
  
  f=fopen("stars.dat","w");
  
  for(i=0;estrelas[i].nome!=NULL;i++)
    {
      
      if(i==0)
	fprintf(f,"%s;%f;%s;%s;",estrelas[i].nome,estrelas[i].massa,estrelas[i].classe,estrelas[i].constelacao);
      
      else
	fprintf(f,"\n%s;%f;%s;%s;",estrelas[i].nome,estrelas[i].massa,estrelas[i].classe,estrelas[i].constelacao);
    
    }
  
  fclose(f);

}


//funcao que recebe os inputs (de strings) do utilizador atraves da variavel var e retorna a string sem o '\n'
char *recebe(char *var)
{
    
  fgets(var,LIM,stdin);  //recebe o input para var
  
  var[strlen(var)-1]='\0';
  
  fflush(stdin); //limpa buffer do teclado
  
  return var;
  
}


//insere uma estrela na tabela e grava a tabela no ficheiro
void insere_estrela()
{

//antes de inserir uma estrela tem que se acrescentar um espaco na tabela, por isso, ao numero de linhas inicial (que estao no ficheiro: n_linhas()+1) soma-se um e realoca-se o espaco disponivel
  estrelas=(dados*)realloc(estrelas,sizeof(dados)*(n_linhas()+2)); 
  
  preenche_tabela();
  
  char n[1000]; 	//armazena o nome
  float mf;	//armazena a massa depois de ser transformada de string para float
  char m[1000];	//armazena a massa como string
  char cl[1000];	//armazena a classe
  char co[1000];	//armazena a constelacao

  
  do
    {
      
      printf("\nNome da estrela: ");
      
      recebe(n);
            
      if (strlen(n)==0)
	printf("\n-----Invalido----- \nPara nome desconhecido introduza ?\n");
      
      else
	break;
    
    }while(strlen(n)==0);
  
  do
    {
      
      printf("\nMassa da estrela: ");
      
      recebe(m);
      
      int stat=sscanf(m,"%f",&mf);  //converte a string m para um float mf
      
      if (strcmp(m,"?")==0)         //se tiver ?, faz mf=0
	{mf=0;break;}
      
      else
	if (stat==1)
	  {sscanf(m,"%f",&mf);break;}   //se tiver numero, guarda-o em mf
      
	else
	  if(stat == 0 || stat == -1)   //se nao tiver valor numerico ou qualquer valor
	    printf("\n-----Invalido----- \nIntroduza um valor numerico. (Para massa desconhecida introduza ?)\n");
    }while(stat==0 || stat == -1);

  do
    {
      
      printf("\nClasse: ");
      
      recebe(cl);
      
      if (strlen(cl)==0)
	printf("\n-----Invalido----- \nPara classe desconhecida introduza ?\n");
      
      else
	break;
    
    }while (strlen(cl)==0);
  
  do
    {
      
      printf("\nConstelacao: ");
      
      recebe(co);
      
      if (strlen(co)==0)
	printf("\n-----Invalido----- \nPara constelacao desconhecida introduza ?\n");
      
      else
	break;
    
    }while (strlen(co)==0);
  
  estrelas[n_linhas()+1].nome=strdup(n);
  estrelas[n_linhas()+1].massa=mf;
  estrelas[n_linhas()+1].classe=strdup(cl);
  estrelas[n_linhas()+1].constelacao=strdup(co);
  
  escreve_tabela_ficheiro();

}


//altera os dados seleccionados pelo utilizador na tabela e escreve-a para o ficheiro
void corrige_dados()
{
  
  preenche_tabela();
  
  int i=0;
  int opcao,opcao2;     
  char n[1000];
  float mf;
  char m[1000];
  char cl[1000];
  char co[1000];
  
  //mostra as estrelas que existem na tabela   
  while (i<=n_linhas())
    {
      
      if (i==n_linhas())
	{
	  printf("\n%d) %s\n",i,estrelas[i].nome);
	  i=i+1;
	}
	
      else
	if (i==(n_linhas()-1))
	  {
	    printf("\n%d) %s %d) %s \n",i,estrelas[i].nome,i+1,estrelas[i+1].nome);
	    i=i+2;
	  }
	  
	else
	  if (i!=n_linhas())
	    {
	      printf("\n%d) %s %d) %s %d) %s \n",i,estrelas[i].nome,i+1,estrelas[i+1].nome,i+2,estrelas[i+2].nome);
	      i=i+3;
	    }
    }
  
  do
    {
      
      int ver = scanf("%d",&opcao);
      
      if (opcao>n_linhas() || opcao<0 || ver == 0)
	printf("OPCAO INCORRECTA!\n opcao: ");
      
      else
	break;
      
    }while (opcao>n_linhas() || opcao<0 || ver ==0);
  
  //mostra os campos da estrela seleccionada
  printf("\n--- %s ---\n",estrelas[opcao].nome);
  printf("%7.2f MSol  ",estrelas[opcao].massa);
  printf("Class: %s  ",estrelas[opcao].classe);
  printf("Constelacao: %s\n\n",estrelas[opcao].constelacao);
  
  printf("Deseja corrigir:\n");
  printf("O nome .........1\n");
  printf("A massa ........2\n");
  printf("A classe .......3\n");
  printf("A constelacao...4\n");
  
  do
    {
	    
      fflush(stdin);
      int ver2 = scanf("%d",&opcao2);
      
      getchar();
      
      if (opcao2<1 || opcao2>4 || ver2==0)
	printf("OPCAO INCORRECTA!\n opcao: ");
      
      else
	break;
    
    }while (opcao<1 || opcao2>4 || ver2==0);
  
  
  switch(opcao2)
    {
    case 1: 

        do
	  {
	    
	    printf("\nNome da estrela: ");
	    
	    recebe(n);
	    
	    if (strlen(n)==0)
	      printf("\n-----Invalido----- \nPara nome desconhecido introduza ?\n");
	    
	    else
	      break;
	    
	  }while(strlen(n)==0);
	  
	estrelas[opcao].nome=strdup(n);
	break;
	
    case 2: 
      do
  	{
		
	  printf("\nMassa da estrela: ");
	  
	  recebe(m);
	  
	  int stat=sscanf(m,"%f",&mf);  //converte a string m para um float mf
	  
	  if (strcmp(m,"?")==0)         //se tiver ?, faz mf=0
	    {mf=0;break;}
	  
  	else
	  if (stat==1)
	    {sscanf(m,"%f",&mf);break;}   //se tiver numero, guarda-o em mf
	
	  else
	    if(stat == 0 || stat == -1)   //se nao tiver valor numerico ou qualquer valor
	      printf("\n-----Invalido----- \nIntroduza um valor numerico. (Para massa desconhecida introduza ?)\n");
	  
  	}while (stat ==0 || stat == -1);
	
      estrelas[opcao].massa=mf;
      break;
      
    case 3: 
      
      do
  	{
		
	  printf("\nClasse da estrela: ");
	  
	  recebe(cl);
	  
	  if (strlen(cl)==0)
	    printf("\n-----Invalido----- \nPara classe desconhecida introduza ?\n");
	  
	  else
	    break;
  	}while (strlen(cl)==0);

      estrelas[opcao].classe=strdup(cl);
      break;
      
    case 4: 
      
      do
	{
	  printf("\nConstelacao da estrela: ");
	  recebe(co);
	  if (strlen(co)==0)
	    printf("\n-----Invalido----- \nPara constelacao desconhecida introduza ?\n");
	  else
	    break;
	}while (strlen(co)==0);

      estrelas[opcao].constelacao=strdup(co);
      break;
      
    default: printf("opcao incorrecta");          
      
    }
  
  escreve_tabela_ficheiro();       
  
}


//auxiliar para qsort comparar massas
//recebe dois apontadores do tipo void* dados pelo qsort
//retorna a comparacao entre eles
int comp_massa(const void* p1, const void* p2) 
{
  
  dados *a1 = (dados*)p1;
  dados *a2 = (dados*)p2;
  
  if (a1->massa < a2->massa) 
    return 1; //1 se massa do primeiro e menor que a do segundo
  
  if (a1->massa == a2->massa) 
    return 0; //0 se sao iguais
  
  if (a1->massa > a2->massa) 
    return -1; //-1 se a massa do primeiro e maior que a do segundo

}


//implementa o qsort para massas
void ordena_massa()
{
  /*argumentos: vector de estruturas a ordenar (estrelas)
                numero de estruturas a ordenar (n_linhas()+1(a contagem das linhas comeca em 0)
		tamanho de cada elemento (sizeof(dados))
		funcao de comparacao (comp_massa)
  devido ao tipo de funcao de comparacao, vai ordenar por ordem decrescente de massa
  */
  
  qsort(estrelas,n_linhas()+1,sizeof(dados),comp_massa);

}


//auxiliar para qsort comparar nomes
//recebe dois apontadores do tipo void* dados pelo qsort
//retorna a comparacao entre eles
static int comp_nome(const void* p1, const void* p2)
{
  
  dados *a1 = (dados*)p1;
  dados *a2 = (dados*)p2;

  return strcasecmp(a1->nome,a2->nome); //compara duas strings alfabeticamente e ignorando se as letras estao em maiusculas ou minusculas. As strings a comparar sao os campos nome.

}


//implementa qsort para nomes
void ordena_nome()
{   
  /*argumentos: vector de estruturas a ordenar (estrelas)
                numero de estruturas a ordenar (n_linhas()+1(a contagem das linhas comeca em 0)
		tamanho de cada elemento (sizeof(dados))
		funcao de comparacao (comp_nome)
  */
	
  qsort(estrelas,n_linhas()+1,sizeof(dados),comp_nome);
   
}


//auxiliar para qsort comparar constelacoes
//recebe dois apontadores do tipo void* dados pelo qsort
//retorna a comparacao entre eles
int comp_const(const void* p1, const void* p2)
{
  
  dados *a1 = (dados*)p1;
  dados *a2 = (dados*)p2;
  
  return strcasecmp(a1->constelacao,a2->constelacao);//compara duas strings alfabeticamente e ignorando se as letras estao em maiusculas ou minusculas. Ase strings a comparar sao os campos constelacao

}


//implementa qsort para constelacoes
void ordena_constelacao()
{

  /*argumentos: vector de estruturas a ordenar (estrelas)
                numero de estruturas a ordenar (n_linhas()+1(a contagem das linhas comeca em 0)
		tamanho de cada elemento (sizeof(dados))
		funcao de comparacao (comp_const)
  */
	
  qsort(estrelas,n_linhas()+1,sizeof(dados),comp_const);

}


int main()
{
	
  estrelas=(dados*)malloc(sizeof(dados)*(n_linhas()+1)); //aloca memoria necessaria para carregar todos os dados do ficheiro
  
  preenche_tabela(); //preenche a tabela na inicializacao do programa
  
  char opcao;
  
  do //ciclo que so termina se o utilizador introduzir x ou X
    {
	    
      printf("\n\nMostrar o conteudo da tabela....1\n");
      printf("Acrescentar uma estrela.........2\n");
      printf("Corrigir dados de uma estrela...3\n");
      printf("Ordenar por massa...............4\n");
      printf("Ordenar por nome................5\n");
      printf("Ordenar por constelacao.........6\n");
      printf("Sair............................x\n");
      
      opcao=getchar();
      getchar();
      
      if (opcao=='x' || opcao=='X')
	exit (2);
      else
	switch (opcao)
	  {
	  case '1': imprime_tabela(); break;
	  case '2': insere_estrela(); break;
	  case '3': corrige_dados(); break;
	  case '4': ordena_massa(); break;
	  case '5': ordena_nome(); break;
	  case '6': ordena_constelacao();break;
	  default : {printf("Opcao incorrecta");while(getchar()!='\n');};
	  }
	  
    }while(opcao!='x' || opcao!='X');
  
  return 0;
  
}

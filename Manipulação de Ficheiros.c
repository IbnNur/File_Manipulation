#include <stdio.h>
#include <stdlib.h>

int  menu(void);
void mostrardados(char nomefile[20]);
void mostrarlem(char nomefile[20]);
void mostrapordata(char nomefile[20]);
void quantidadegenero(char nomefile[20]);
void acrescentaDados(char nomefile[20]);
void acrescentaData(char nomefile[20]);
void ordenapordata(char nomefile[20]);
void eliminarRepetidos(char nomefile[20]);
void cria4ficheiros(char nomefile[20]);
void eliminardesistente(char nomefile[20]);


void main()
{

	char nomefile[20];
	int  in;

	printf("Informe o nome do arquivo que deseja processar: ");
	scanf("%s",nomefile);


	do{
			in= menu();

			switch(in)
			 {
			 	case 1: 	mostrardados(nomefile);  		 break;
			 	case 2: 	mostrarlem(nomefile);			 break;
			 	case 3: 	mostrapordata(nomefile);  		 break;
			 	case 4: 	quantidadegenero(nomefile);		 break;
			 	case 5: 	acrescentaDados(nomefile);       break;
			 	case 6: 	acrescentaData(nomefile); 		 break;
			 	case 7: 	eliminardesistente(nomefile);    break;
			 	case 8: 	ordenapordata(nomefile);         break;
			 	case 9: 	eliminarRepetidos(nomefile);     break;
			 	case 10:    cria4ficheiros(nomefile);        break;
			 	case 0:     exit(1); 
			 	default: printf("Opção Invalida!!!!!");

			 }
		}while(1);

}

void mostrardados(char nomefile[20])
{
	FILE *ptr;
	char estudante[50];


	ptr=fopen(nomefile,"r");



	while(fgets(estudante,sizeof(estudante),ptr)!=NULL)
	 {
	 	printf("%s\n",estudante);

	 }
	 fclose(ptr);
}

void mostrarlem(char nomefile[20])
{
	FILE *ptr;
	char estudante[50];
	int  cont=0,i;

	ptr=fopen(nomefile,"r");

	while(fgets(estudante,sizeof(estudante),ptr)!=NULL)
	 {
	 	for(i=0;cont!=2;i++)
	 	 {
		 	if(estudante[i]==':')
		 	 cont++;  	 
		 }

	 	if(estudante[i]=='L' && estudante[i+1]=='E' && estudante[i+2]=='M')
	 	 {
	 		printf("%s\n",estudante);
	 	 }

	 	cont=0;

	 }
	 fclose(ptr);

}

void mostrapordata(char nomefile[20])
{
	FILE *ptr;
	char estudante[50];
	char data[11];
	int  cont=0,i,j,cont2=0;

	ptr=fopen(nomefile,"r");

	printf("Deseja Imprimir estudantes matriculados/inscritos em que data (dd.mm.aaaa)? ");
	scanf(" %s",data);

	while(fgets(estudante,sizeof(estudante),ptr)!=NULL)
	 {
	 	for(i=0;cont!=3;i++)
	 	 {
		 	if(estudante[i]==':')
		 	 cont++;  	 
		 }

	 	for(j=0;j<10;i++,j++)
	 	 {
	 		if(estudante[i]==data[j])
	 			cont2++;
	 	 }

	  if(cont2==10)
	    printf("%s\n",estudante);

	  if(fgets(estudante,sizeof(estudante),ptr)==NULL)
	    printf("Nao existe algum estudante inscrito/matriculado nesta data.");

	 	cont=0;
	 	cont2=0;

	 }
	 fclose(ptr);
}

void quantidadegenero(char nomefile[20])
{
	FILE *ptr;
	char estudante[50];
	char sexo;
	int  cont=0,i;
	int  contsexo=0;

	ptr=fopen(nomefile,"r");

	printf("Deseja Imprimir estudantes de que Genero (M/F)? ");
	scanf(" %c",&sexo);

	while(fgets(estudante,sizeof(estudante),ptr)!=NULL)
	 {
	 	for(i=0;cont!=1;i++)
	 	 {
		 	if(estudante[i]==':')
		 	 cont++;  	 
		 }

	 	if(estudante[i]==sexo)
	 	 {
	 		printf("%s\n",estudante);
	 		contsexo++;
	 	 }

	 	cont=0;

	 }

	 if(sexo=='M')
	  printf("Ao todo sao %d estudantes do sexo Masculino",contsexo);
	 else
	  printf("Ao todo sao %d estudantes do sexo Feminino",contsexo);

	 fclose(ptr);
}

void acrescentaDados(char nomefile[20])
{
	FILE *ptr;
	char estudante[50];

	ptr=fopen(nomefile,"a");

	printf("digite NomeCompleto:Genero:Curso:dd.mm.aaaa (matricula)");
	scanf(" %[^\n]s",estudante);

	fprintf(ptr,"%s",estudante);

	fclose(ptr);
}

void acrescentaData(char nomefile[20])
{
	FILE *ptr;
	int i,j=0,k=0,cont=0,cont2=0,z=0;
	char estudante[80][50];
	char semdata[80][50];
	char aux[50];

	ptr=fopen(nomefile,"r");


	while(fgets(aux,sizeof(aux),ptr)!=NULL)
	 {
	 	for(i=0;cont!=3;i++)
	 	 {
		 	if(aux[i]==':')
		 	 cont++;  	 
		 }


	 	if(aux[i+1]!=' ')
	 	 {
	       fgets(estudante[k],sizeof(semdata),ptr);
	       k++;
	       z++;
	 	 }

	 	if(aux[i+1]==' ')
	 	 {
	 		fgets(semdata[j],sizeof(semdata),ptr);
	 		j++;
	 		cont2++;

	 	 }

	 	cont=0;
	 	j=0;
	 	k=0;
	 }

	  fclose(ptr);

	  j=0;
	  k=0;

	 ptr=fopen(nomefile,"w+");

	 for(k=0;k<z;k++)
	 {
	  	fprintf(ptr,"%s",estudante[k]);
	 }

	 printf("Os estudantes abaixo nao possuem data de matricula:\n");

	 for(j=0;j<cont2;j++)
	  	printf("%s",semdata[j]);	

	 fclose(ptr);

}


void eliminardesistente(char nomefile[20])
{
	struct estud
	 {
		char estudante[50]; 
	 }*save;

	FILE *ptr;
	int cont=0,cont1=0,sinal=0,i=0,find=0;
	char desistente[50];

	if((ptr = fopen(nomefile,"r"))==NULL)
	{
		printf("Erro ao abrir o ficheiro.\n");
		exit(1);
	}
	if((save=malloc(sizeof(struct estud)))==NULL)
	{
		printf("Erro ao guardar.\n");
		exit(1);
	}

	//Le todos nomes do ficheiro.
	while(fgets(save[i].estudante,sizeof(save[i].estudante),ptr)!=NULL)
	{
		if((save = realloc(save,(i+2)*sizeof(struct estud)))==NULL)
		{
			printf("Erro ao guardar.\n");
			exit(1);
		}
		i++;
	}

	//Nesta instrucao e' Eliminado o estudante desistente introduzido pelo teclado.
		printf("Digite o nome do estudante: ");
		scanf(" %[^\n]",desistente);

		rewind(ptr); // reinicializa o indicador para o inicio do ficheiro.

		//Na instrucao abaixo e feita a Comparacao com os nomes do ficheiro.
		for(cont1=0;cont1<i;cont1++)
		{	
			for(cont=0,sinal=0;save[cont1].estudante[cont]!=':' || desistente[cont]!='\0';cont++)
			{	
				if(desistente[cont]>=97) 
				  desistente[cont]-=32;
				if(save[cont1].estudante[cont]==desistente[cont])
				    sinal=1;
				else
				 {
					sinal=0;
					break;
				 }
			}

			if(sinal)
			{
				save[cont1].estudante[0]='\0';
				find=-1;
				printf("Removido!!\n");
				break;
			}

		}
		if(!sinal)
		  printf("Nome nao encontrado!\n");			

	fclose(ptr);

	cont=0;

	if(find==-1) // Se for verdadeiro e' criado um novo arquivo e armazena os dados.
	{	
		if((ptr = fopen(nomefile,"w"))==NULL)
		{
			printf("Arquivo nao pode ser aberto.\n");
			exit(1);
		}
		cont=0;	

		//Sao guardados dados em nova lista sem o nome do aluno desistente.
		while(cont<i)
		{
			if(*save[cont].estudante)
			{
				printf("%s\n",save[cont].estudante);
			}
			cont++;
		}
		fclose(ptr);
	}
	else
	{
		printf(" Nome nao encontrado.\n");		
	}
	free(save);
}

void ordenapordata(char nomefile[20])
{
	struct estud
	{
		char estudante[50];
	}*save,*aux;

	FILE *ptr;
	int cont=0,cont1=0,cont2=0,cont3=0,cont4=0,j=0,i=0;


	if((ptr = fopen(nomefile,"r"))==NULL)
	{
		printf("Erro ao abrir o ficheiro!!!\n");
		exit(1);
	}

	if(!(save = malloc(sizeof(struct estud))))
	{
		printf("Erro ao armazenamenar!!!\n");
		exit(1);
	}

	if(!(aux = malloc(sizeof(struct estud))))
	{
		printf("Erro ao armazenamenar!!!\n");
		exit(1);
	}


	while((fgets(save[i].estudante,sizeof(save[i].estudante),ptr)!=NULL))
	{
		if((save = realloc(save,(i+2)*sizeof(struct estud)))==NULL)
		{
			printf("Erro ao armazenamenar!!!\n");
			exit(1);
		}
		i++;
	}

	fclose(ptr);

	// Organiza os por data nomes.
	for(cont=0;cont<i;cont++)
	{	
		for(cont1=cont;cont1<i;cont1++)
		{	
			//Obtem o indice do inicio da data.
			for(j=0;save[cont].estudante[j];j++)
			{	if(save[cont].estudante[j] == ':')
				{
					cont3=j;
				}
			}

			for(j=0;save[cont1].estudante[j];j++)
			{	if(save[cont1].estudante[j]==':')
				{
					cont4=j;
				}
			}

			for(cont2=0;save[cont].estudante[cont3] || save[cont1].estudante[cont4];cont4++,cont3++)
			{		
				if((save[cont].estudante[cont3] > save[cont1].estudante[cont4]))
				{	
							//Organiza os nomes.
					aux[0] = save[cont];
					save[cont] = save[cont1];
					save[cont1] = aux[0];
					break;
				}
				else
				if((save[cont].estudante[cont3] < save[cont1].estudante[cont4]))
				break;
			}
		}	
	}

	//Cria novo ficheiro para os dados ja ordenados,
	if((ptr = fopen(nomefile,"w")) == NULL)
	{
		printf("Erro ao criar o arquivo.\n");
		exit(1);
	}cont=0;

	// Passa os nomes de forma ordenada para o ficheiro.

	while(cont<i)
	{
		if(*save[cont].estudante)
			if(fputs(save[cont].estudante,ptr))
		cont++;
	}
	printf("Sucesso na organizacao!!!.\n ");

	fclose(ptr);
	free(aux);
	free(save);

}



void eliminarRepetidos(char nomefile[20])
{
	FILE *ptr;
	char estudante[81][50];
	char aux[50];
	char est[20];
	int i,j,cont=0,totEst;

	ptr=fopen(nomefile,"w+");

	printf("Informe o nome com letras maiuscula do estudante que tem o nome repetido:");
	scanf("%[^\n]s",est);

	for(i=0;i<totEst;i++)
	 {
	   for(j=0;est[j]==':';)
	    {
	  	  if(aux[j]==est[j])
	  	   j++;
	  	  else
	  	   break;
	 	}
	 }


	for(i=0;i<totEst;i++)
	 {
	 	fprintf(ptr,"%s",estudante[i]);

	 }

}

void cria4ficheiros(char nomefile[20])
{	
	struct estud
	{
		char estudante[50];
	}*save,*aux;

	FILE *ptr,*ptrlei,*ptrlem,*ptrlec,*ptrleg;
	int cont=0,cont1=0,cont2=0,i=0;
	char estudante[50];


	ptr=fopen(nomefile,"r");
	ptrlei=fopen("LEI.txt","a+");
	ptrlem=fopen("LEM.txt","a+");
	ptrlec=fopen("LEC.txt","a+");
	ptrleg=fopen("LEG.txt","a+");



	while(fgets(estudante,sizeof(estudante),ptr)!=NULL)
	 {
	 	for(i=0;cont!=2;i++)
	 	 {
		 	if(estudante[i]==':')
		 	 cont++;  	 
		 }

	 	if(estudante[i]=='L' && estudante[i+1]=='E' && estudante[i+2]=='I')
	 	 {
	 		fprintf(ptrlei,"%s",estudante);
	 	 }

	 	if(estudante[i]=='L' && estudante[i+1]=='E' && estudante[i+2]=='M')
	 	 {
	 		fprintf(ptrlem,"%s",estudante);
	 	 }

	 	 if(estudante[i]=='L' && estudante[i+1]=='E' && estudante[i+2]=='C')
	 	 {
	 		fprintf(ptrlec,"%s",estudante);
	 	 }

	 	 if(estudante[i]=='L' && estudante[i+1]=='E' && estudante[i+2]=='G')
	 	 {
	 		fprintf(ptrleg,"%s",estudante);
	 	 }
	 	cont=0; 	
	 }

	fclose(ptr);
	fclose(ptrlei);
	fclose(ptrlem);
	fclose(ptrlec);
	fclose(ptrleg);

	i=0;

	//Sera feita a leitura do ficheiro ja criado LEI.txt
	if((ptrlei = fopen("LEI.txt","r"))==NULL)
	{
		printf("erro ao abrir o ficheiro!!!\n");
		exit(1);
	}

	if(!(save = malloc(sizeof(struct estud))))
	{
		printf("Erro ao armazenamenar!!!\n");
		exit(1);
	}

	if(!(aux = malloc(sizeof(struct estud))))
	{
		printf("Erro ao armazenamenar\n");
		exit(1);
	}

	//Le os nomes do ficheiro e armazena em guarde.

	while((fgets(save[i].estudante,sizeof(save[i].estudante),ptrlei)!=NULL))
	{
		if((save = realloc(save,(i+2)*sizeof(struct estud)))==NULL)
		{
			printf("Erro no armdazenamento\n");
			exit(1);
		}
		i++;
	}

	fclose(ptrlei);


	for(cont=0;cont<i;cont++)
	{
		for(cont1=cont;cont1<i;cont1++)
		{
			for(cont2=0;save[cont].estudante[cont2]!=':' || save[cont1].estudante[cont2]!=':';cont2++)
			{
				if(save[cont].estudante[cont2] > save[cont1].estudante[cont2])
				{	

					aux[0] = save[cont];
					save[cont] = save[cont1];
					save[cont1] = aux[0];
					break;
				}
				else
				if(save[cont].estudante[cont2] < save[cont1].estudante[cont2])
				break;
			}
		}	
	}


	if((ptrlei = fopen("LEI.txt","w")) == NULL)
	{
		printf("Erro ao abrir o arquivo.\n");
		exit(1);
	}
	cont=0;

	// Guarda os nomes ordenados no ficheiro.

	while(cont<i)
	{
		if(*save[cont].estudante)
			if(fputs(save[cont].estudante,ptrlei))
		cont++;
	}

	fclose(ptrlei);
	free(save);
	free(aux);


	i=0;

	//Sera feita a leitura do ficheiro ja criado LEI.txt
	if((ptrlem = fopen("LEM.txt","r"))==NULL)
	{
		printf("erro ao abrir o ficheiro!!!\n");
		exit(1);
	}

	if(!(save = malloc(sizeof(struct estud))))
	{
		printf("Erro ao armazenamenar!!!\n");
		exit(1);
	}

	if(!(aux = malloc(sizeof(struct estud))))
	{
		printf("Erro ao armazenamenar\n");
		exit(1);
	}

	//Le os nomes do ficheiro e armazena em guarde.

	while((fgets(save[i].estudante,sizeof(save[i].estudante),ptrlem)!=NULL))
	{
		if((save = realloc(save,(i+2)*sizeof(struct estud)))==NULL)
		{
			printf("Erro no armdazenamento\n");
			exit(1);
		}
		i++;
	}

	fclose(ptrlem);


	for(cont=0;cont<i;cont++)
	{
		for(cont1=cont;cont1<i;cont1++)
		{
			for(cont2=0;save[cont].estudante[cont2]!=':' || save[cont1].estudante[cont2]!=':';cont2++)
			{
				if(save[cont].estudante[cont2] > save[cont1].estudante[cont2])
				{	

					aux[0] = save[cont];
					save[cont] = save[cont1];
					save[cont1] = aux[0];
					break;
				}
				else
				if(save[cont].estudante[cont2] < save[cont1].estudante[cont2])
				break;
			}
		}	
	}


	if((ptrlem = fopen("LEM.txt","w")) == NULL)
	{
		printf("Erro ao abrir o arquivo.\n");
		exit(1);
	}
	cont=0;

	// Guarda os nomes ordenados no ficheiro.

	while(cont<i)
	{
		if(*save[cont].estudante)
			if(fputs(save[cont].estudante,ptrlem))
		cont++;
	}

	fclose(ptrlem);
	free(save);
	free(aux);


	i=0;

	//Sera feita a leitura do ficheiro ja criado LEI.txt
	if((ptrlec = fopen("LEC.txt","r"))==NULL)
	{
		printf("erro ao abrir o ficheiro!!!\n");
		exit(1);
	}

	if(!(save = malloc(sizeof(struct estud))))
	{
		printf("Erro ao armazenamenar!!!\n");
		exit(1);
	}

	if(!(aux = malloc(sizeof(struct estud))))
	{
		printf("Erro ao armazenamenar\n");
		exit(1);
	}

	//Le os nomes do ficheiro e armazena em guarde.

	while((fgets(save[i].estudante,sizeof(save[i].estudante),ptrlec)!=NULL))
	{
		if((save = realloc(save,(i+2)*sizeof(struct estud)))==NULL)
		{
			printf("Erro no armdazenamento\n");
			exit(1);
		}
		i++;
	}

	fclose(ptrlec);


	for(cont=0;cont<i;cont++)
	{
		for(cont1=cont;cont1<i;cont1++)
		{
			for(cont2=0;save[cont].estudante[cont2]!=':' || save[cont1].estudante[cont2]!=':';cont2++)
			{
				if(save[cont].estudante[cont2] > save[cont1].estudante[cont2])
				{	

					aux[0] = save[cont];
					save[cont] = save[cont1];
					save[cont1] = aux[0];
					break;
				}
				else
				if(save[cont].estudante[cont2] < save[cont1].estudante[cont2])
				break;
			}
		}	
	}


	if((ptrlec = fopen("LEC.txt","w")) == NULL)
	{
		printf("Erro ao abrir o arquivo.\n");
		exit(1);
	}
	cont=0;

	// Guarda os nomes ordenados no ficheiro.

	while(cont<i)
	{
		if(*save[cont].estudante)
			if(fputs(save[cont].estudante,ptrlec))
		cont++;
	}

	fclose(ptrlec);
	free(save);
	free(aux);

	i=0;

	//Sera feita a leitura do ficheiro ja criado LEI.txt
	if((ptrleg = fopen("LEG.txt","r"))==NULL)
	{
		printf("erro ao abrir o ficheiro!!!\n");
		exit(1);
	}

	if(!(save = malloc(sizeof(struct estud))))
	{
		printf("Erro ao armazenamenar!!!\n");
		exit(1);
	}

	if(!(aux = malloc(sizeof(struct estud))))
	{
		printf("Erro ao armazenamenar\n");
		exit(1);
	}

	//Le os nomes do ficheiro e armazena em guarde.

	while((fgets(save[i].estudante,sizeof(save[i].estudante),ptrleg)!=NULL))
	{
		if((save = realloc(save,(i+2)*sizeof(struct estud)))==NULL)
		{
			printf("Erro no armdazenamento\n");
			exit(1);
		}
		i++;
	}

	fclose(ptrleg);


	for(cont=0;cont<i;cont++)
	{
		for(cont1=cont;cont1<i;cont1++)
		{
			for(cont2=0;save[cont].estudante[cont2]!=':' || save[cont1].estudante[cont2]!=':';cont2++)
			{
				if(save[cont].estudante[cont2] > save[cont1].estudante[cont2])
				{	

					aux[0] = save[cont];
					save[cont] = save[cont1];
					save[cont1] = aux[0];
					break;
				}
				else
				if(save[cont].estudante[cont2] < save[cont1].estudante[cont2])
				break;
			}
		}	
	}


	if((ptrleg = fopen("LEG.txt","w")) == NULL)
	{
		printf("Erro ao abrir o arquivo.\n");
		exit(1);
	}
	cont=0;

	// Guarda os nomes ordenados no ficheiro.

	while(cont<i)
	{
		if(*save[cont].estudante)
			if(fputs(save[cont].estudante,ptrleg))
		cont++;
	}
	printf("Sucesso ao organizar!!!\n ");

	fclose(ptrleg);
	free(save);
	free(aux);

}

int menu(void)
{
	int in;

	printf("1- 	Leitura e apresentação dos dados:\n");
	printf("2- 	Leitura e apresentação de dados referentes a Estudantes de LEM:\n");
	printf("3- 	Leitura e apresentação de dados referentes a Estudantes inscritos/matriculados numa determinada data:\n");
	printf("4- 	Leitura e apresentação da quantidade de Estudantes de um determinado género:\n");
	printf("5- 	Acrescentar, no ficheiro, dados dos que vierem a matricular-se tardiamente:\n");
	printf("6- 	Acrescentar, no ficheiro, dados referentes a data de matrícula aos Estudantes cujo este dado não esteja presente:\n");
	printf("7- 	Eliminar, do ficheiro, dados de Estudantes desistentes:\n");
	printf("8-  Ordenar, no ficheiro, os dados de forma crescente da data de matrícula:\n");
	printf("9-  Eliminar do ficheiro, os nomes repetidos:\n");
	printf("10- Criar, quatro ficheiros diferentes, contendo os nomes (ordenados alfabeticamente) de Estudantes por curso, sem apagar o ficheiro original:\n");
	printf("0- Sair:");
	scanf("%d",&in);

	return in;	
}
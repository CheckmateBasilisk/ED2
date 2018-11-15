#include <stdlib.h>
#include <stdio.h>

void setBit(unsigned short int *value, unsigned short int bit);

int main(void)
{
	struct reg
	 {
		char c;
		int bit1, bit2;
	 };
	struct reg cod[4];
	unsigned short int number=0, contabits=0;
	char bin[17];
	int i=0,j=0,leituras=0;
	FILE *out;
    
    out = fopen("teste.bin","w+b");

	cod[0].c = 'a';cod[0].bit1 = 0;cod[0].bit2 = 0;
	cod[1].c = 'b';cod[1].bit1 = 0;cod[1].bit2 = 1;
	cod[2].c = 'c';cod[2].bit1 = 1;cod[2].bit2 = 0;
	cod[3].c = 'd';cod[3].bit1 = 1;cod[3].bit2 = 1;

	itoa(number, bin, 2);
	printf("integer = %d string = %s\n", number, bin);

	// Sequencia: a b c d a b c d a b c d (12 caracteres * 8 bits = 96 bits)
	// Codificacao: 00 01 10 11 00 01 10 11 00 01 10 11
    //              (24 bits. Entretanto, 4 bytes (2 inteiros (2 bytes cada (short))) * 8 bits = 32 bits)	
	printf("\n\n*********Montando********\n");
	
    //início cabeçalho	
	fwrite(&j,sizeof(j),1,out);//qtdade de inteiros
	fwrite(&contabits,sizeof(contabits),1,out);//qtdade de bits do ultimo byte (inteiro)
	//fim cabeçalho
	
	while(j < 24)
	 {
		if (contabits == 16) // quando preencher um inteiro (16 bits)
		  {
			 contabits=0;
			 fwrite(&number,sizeof(number),1,out);
			 itoa(number, bin, 2);
			 printf("escrevendo...integer = %d string = %s\n", number, bin);
			 number=0;
		  }
		if (cod[i].bit1 == 1)
		  setBit(&number,contabits);
		contabits++;
		if (cod[i].bit2 == 1)
		  setBit(&number,contabits);
		contabits++;
		i++;
		if (i==4)
		  i=0;
		j=j+2;
	 }
	if (contabits < 16)
		  {
			 fwrite(&number,sizeof(number),1,out);
			 itoa(number, bin, 2);
			 printf("escrevendo...integer = %d string = %s\n", number, bin);
		  }
	fseek(out,0,0);
	j=2;//2 inteiros
	
	//início arrumando cabeçalho	
	fwrite(&j,sizeof(j),1,out);
	fwrite(&contabits,sizeof(contabits),1,out);
	//fim arrumando cabeçalho	

	printf("\n\n*********Desmontando********\n");
	fseek(out,0,0);
	
	//início leitura cabeçalho
	fread(&j,sizeof(j),1,out);
	fread(&contabits,sizeof(contabits),1,out);
	//fim leitura cabeçalho	
	
	while(fread(&number,sizeof(number),1,out))
	 {
		leituras++;
		printf("valor: %d\n",number);
		itoa(number, bin, 2);
		printf("lendo...integer = %d string = %s\n", number, bin);
		printf("\nSequencia\n");
		if (leituras == j)
		  i=contabits-1;
		else i=15;
		for (;i>0;i=i-2)
		 {
			if ((bin[i] == '0') && (bin[i-1] == '0'))
			  printf("a ");
			if ((bin[i] == '0') && (bin[i-1] == '1'))
			  printf("b ");
			if ((bin[i] == '1') && (bin[i-1] == '0'))
			  printf("c ");
			if ((bin[i] == '1') && (bin[i-1] == '1'))
			  printf("d ");
		 }
		printf("\n\n");
	 }

	fclose(out);
	getchar();
	return 0;
}

void setBit(unsigned short int *value, unsigned short int bit)
{
  unsigned short int mask = 1 << bit;
  *value = *value | mask;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct				// definovanie struktury
{
	char meno[51];
	char pohlavie;
	int  rok_narodenia;
	char SPZ[8];
	int  priestupok;
	int  pokuta;
	char datum[9];
	
} ZAZNAM;

/*----------------- Pomocne funkcie -------------------------------------------------------------------------------------*/

int pocet_zaznamov(FILE *f)								// vrati pocet zaznamov v text.subore
{
  char pomo[100];
  int pocetzaz=0;
  
  f=fopen("priestupky.txt","r");
  
   if (f!=NULL)
	{
		while (fgets(pomo,sizeof(pomo),f)!=NULL)
		  pocetzaz++;
		
		pocetzaz/= 8; 				// 7 riadkov su udaje zaznamu a potom je prazdny riadok, 8.riadok je prazdny.
	    pocetzaz++;					// za poslednym zaznamom uz je koniec suboru a nie prazdny riadok 
	}
	close(f);
return pocetzaz;
}

int vytvorenie_zapis(int pocetzaznamov,ZAZNAM *pole)	// vytvvorenie pola a naplnenie ho udajmi z textoveho suboru
{
	FILE *f;
	int  i=0,k=0;
	char Meno[51],Spz[8],Datum[9],pohl,pomo[100],znak;
	int  Rok,Pokuta,Priestupok;
	int vytvorenepole;
	
	f=fopen("priestupky.txt","r");

   if (f!=NULL)
	if (pocetzaznamov>0)
	{
		while (i < pocetzaznamov)			
		{
			int j=0;						// citanie mena
			
			while((znak=fgetc(f))!= '\n') 
			 Meno[j++]=znak;
			Meno[j]='\0';	
 			if (Meno[0]!='\0')		       // ak nie som v prazdnom riadku
			{
			   fscanf(f,"%c %d %s %d %d %s",&pohl,&Rok,Spz,&Priestupok,&Pokuta,Datum);		// nacita vek  a datum	    	
	
				strcpy(pole[k].meno,Meno);													// priradenia
		     	pole[k].pohlavie=pohl;
				pole[k].rok_narodenia=Rok; 													// na predanie stringu do structu pouzivaj strcpy
		     	strcpy(pole[k].SPZ,Spz);
		     	pole[k].priestupok=Priestupok;
		     	pole[k].pokuta=Pokuta;
		     	strcpy(pole[k].datum,Datum);
				k++;
				i++;    	    
			}
	    }
		vytvorenepole=1;		// ak sa vrati 1 tak pole bolo naplnene
	}
	else
	{
	 vytvorenepole=0;			// ak sa vrati 0 tak subor z ktoreho citam je prazdny
	}
	
return vytvorenepole;	
}

void vypis(int pocetzaznamov,ZAZNAM *pole)				// vypis pola struktur
{
   int i;
   for (i=0;i<pocetzaznamov;i++)
   {
   	 printf("meno priezvisko: %s\n",pole[i].meno);
   	 printf("pohlavie: %c\n",pole[i].pohlavie);
   	 printf("rok narodenia: %d\n",pole[i].rok_narodenia);
   	 printf("SPZ: %s\n",pole[i].SPZ);
   	 printf("priestupok: %d\n",pole[i].priestupok);
   	 printf("pokuta: %d\n",pole[i].pokuta);
   	 printf("datum: %s\n",pole[i].datum);
	 putchar('\n');
   }

}

ZAZNAM novy_zaznam()									// zapis noveho zaznamu z klavesnice
{
	char Meno[51],Spz[8],Datum[9],pohl,znak;
	int  Rok,Priestupok,Pokuta,i=0;
	ZAZNAM nove;
		
	while((znak=getchar())!= '\n') 
		Meno[i++]=znak;
	Meno[i]='\0';

	scanf("%c %d %s %d %d %s",&pohl,&Rok,Spz,&Priestupok,&Pokuta,Datum);

	 strcpy(nove.meno,Meno);
	 nove.pohlavie=pohl;
	 nove.rok_narodenia=Rok;
	 strcpy(nove.SPZ,Spz);
	 nove.priestupok=Priestupok;
	 nove.pokuta=Pokuta;
	 strcpy(nove.datum,Datum);

return nove;
}

int zvacsi_pole(ZAZNAM **pole,int pocet)				// zvacsi pole pomocou realloc 
{
  int pom;
  ZAZNAM *temp;
   
  pom=++pocet;
  
  temp=(ZAZNAM *)realloc(*pole,pom*sizeof(ZAZNAM));
  
  if(temp==NULL)
   return -1;
  else
   *pole=temp;
return pom;   
}

int vloz_do_pola(ZAZNAM *pole,int pocet, ZAZNAM udaj)	// vlozi do pola novy prvok
{
	int i,pom2,pozicia;

    for (i=0;i<pocet;i++)
   {
   	pom2=strcmp(udaj.meno,pole[i].meno);	// porovnavanie mien zaznamov
    if (pom2<0)								// ak je meno zaznamu,ktory chcem vlozit do pola struktur  
     {										// lex. mensi ako meno zaznamu z pola
     	pozicia=i;
     	break;
	 }
   }
   printf("%d\n",pozicia);
 	
	if (pole!=NULL)							
	{										// vlozenie zaznamu do pola na pozadovanu poziciu
	  for(i=pocet-1;i>pozicia;i--)
		  pole[i]=pole[i-1];	
	  pole[pozicia]=udaj;
	  return 1; 
	}
	else
	 return -1; 
	 
 return 0;
}

void zadaj_datum(char *datum)					// nacita datum z klavesnice
{
  char pom[9],pomo;									// datum ma format: rrrrmmdd 
  int i;
  
  pomo=getchar();								// odfiltrovanie entra
  
  for(i=0;i<8;i++)
    pom[i]=getchar();
  pom[i]='\0';
   strcpy(datum,pom);  
}

void urci_aktmes(char *datum,char *kluc)		// berie rok a mesiac... rok a mesiac == kluc
{
	int dlzka=6,i;
	for(i=0;i<dlzka;i++)
	 kluc[i]=datum[i];
	kluc[i]='\0'; 
}
void urci_rok(char *datum,char *rok)  			// zoberie rok z datumu
{
	int dlzka=4,i;
	for (i=0;i<dlzka;i++)	
	 rok[i]=datum[i];
	rok[i]='\0'; 							// dlzka=4 lebo z datumu beriem len pozicie 0-3... teda rok
}

void urci_mesiac(char *datum, char *mesiac)    // zoberie mesiac z datumu
{
   char pom[3];
   
   mesiac[0]=datum[4];
   mesiac[1]=datum[5];
   mesiac[2]='\0';
}

void vypocitaj_odmenu(ZAZNAM *pole, int pocet_zaznamov, char *kluc)	// kluc == aktualny mesiac 
{
  double odmena=0;
  char pom[7];
  int i,hodnota;

  for(i=0;i<pocet_zaznamov;i++)
  {
    urci_aktmes(pole[i].datum,pom);				// z datumu zaznamu sa vyberie potrebna cast podla kluca 
   
   if(strcmp(pom,kluc)==0)						// zistenie ci datum zaznamu vyhovuje klucu == ci je z aktualneho roku a v aktualnom mesiaci
    {
     hodnota=pole[i].pokuta;	
	 
	 if(pole[i].priestupok==1)
      odmena+=(5.2 / 100 * hodnota);
	 else
      odmena+=(3.8 / 100 * hodnota);
	}
  }
  
 if (odmena > 0)
   printf("%.2lf\n",odmena);
}

int palindrom(char povodny[8])				// vrati 0 ak argument je palindrom	
{
	int vysledok;
	char pom[8];
	strcpy(pom,povodny);
	
	vysledok=strcmp(povodny,strrev(pom));

	return vysledok;	  				// vysledok=0... je to palindrom, inak nie je palindrom
}

void zisti_palindrom(ZAZNAM *pole,int pocetzaznamov)	// z pola vypise SPZ, kt. su palindrom
{
  int i,Vysledok;
  char Spz[9];
  char pom;
  
  for (i=0;i<pocetzaznamov;i++)
    {
   	  Vysledok=palindrom(pole[i].SPZ);
	  
	  if (Vysledok==0)
	   printf("%s %s\n",pole[i].meno,pole[i].SPZ);
	}
}

void uvolni(ZAZNAM *pole)								// uvolni pamat
{
   free(pole);
}

ZAZNAM *alokuj(int velkost)								// alokuje nove pole
{
	ZAZNAM *pol;
	
	pol=(ZAZNAM*)malloc(velkost*sizeof(ZAZNAM));
	
	return pol;
}

/*------------ Funkcie zadania ------------------------------------------------------------------------------------------*/

ZAZNAM *funkcia_o(FILE *f,int *vytvorene_pole,int *pocetzaznamov)
{
	ZAZNAM *pole;
	
	*pocetzaznamov=pocet_zaznamov(f);
	
	pole=alokuj(*pocetzaznamov);
		
	*vytvorene_pole=vytvorenie_zapis(*pocetzaznamov,pole);
	
	return pole; 
}

void funkcia_v(int pocetzaznamov,ZAZNAM *pole)
{
	vypis(pocetzaznamov,pole);
}

void funkcia_x(int pocetzaznamov,ZAZNAM *pole)
{
	char Datum[9];
	char Rok[5];
	int  i,vysledok;
	char pom[5];
	 
	zadaj_datum(Datum);
	urci_rok(Datum,Rok);
	
	for(i=0;i<pocetzaznamov;i++)
	{
		
		urci_rok(pole[i].datum,pom);
		vysledok=strcmp(Rok,pom);
		if (pole[i].priestupok==0 && vysledok==0)
		{
		 printf("meno priezvisko: %s\n" ,pole[i].meno);
		 printf("SPZ: %s\n",pole[i].SPZ);
		 printf("datum priestupku: %s\n",pole[i].datum);
		}
	}
}

void funkcia_r(int pocetzaznamov, ZAZNAM *pole)
{
	char Datum[9];
	char Aktualny_mesiac[7];
		
	zadaj_datum(Datum);
	urci_aktmes(Datum,Aktualny_mesiac);
	
	vypocitaj_odmenu(pole,pocetzaznamov,Aktualny_mesiac);

}

void funkcia_p(ZAZNAM *pole,int pocetzaznamov)
{
	zisti_palindrom(pole,pocetzaznamov);
}

int funkcia_a(ZAZNAM *pole,int pocetzaznamov, int *vytvorene_pole)
{
  int novypocet;
  ZAZNAM novy_udaj;
  
  novy_udaj=novy_zaznam();
  
  novypocet=zvacsi_pole(&pole,pocetzaznamov);
  
  vloz_do_pola(pole,novypocet,novy_udaj);

  if(vytvorene_pole==0)
   vytvorene_pole=1;
     	
  return novypocet;	
}

int funkcia_k(FILE *f,ZAZNAM *pole)
{
	close(f);
	uvolni(pole);
	return 0;
}

/*------- Hlavna funkcia ------------------------------------------------------------------------------------------------*/

int main() 
{
	FILE 	 *f;
	ZAZNAM   *udaje;
	ZAZNAM	 novy_udaj;
	int 	 vytvorene_pole=0;
	int 	 pocet_Zaznamov=0;
	char 	 akcia;	
	
	akcia=getchar();	
	while (akcia!='k')
	{
		if (akcia=='o')
		  udaje=funkcia_o(f,&vytvorene_pole,&pocet_Zaznamov);

		else if (akcia=='v' && vytvorene_pole==1)
		 vypis(pocet_Zaznamov,udaje);
		
		else if (akcia=='x' && vytvorene_pole==1)
		 funkcia_x(pocet_Zaznamov,udaje);
		
		else if (akcia=='r' && vytvorene_pole==1)
		 funkcia_r(pocet_Zaznamov,udaje);
		
		else if (akcia=='p' && vytvorene_pole==1)
		 funkcia_p(udaje,pocet_Zaznamov);
		
		else if (akcia=='a')
		 pocet_Zaznamov=funkcia_a(udaje,pocet_Zaznamov,&vytvorene_pole);
		     
		akcia=getchar();
	}
	
	if(akcia=='k' && vytvorene_pole==1)
	 funkcia_k(f,udaje);
	 	
	return 0;
}

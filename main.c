#include <stdio.h>
#include <string.h>
#define nbMax 50

typedef struct instruction{
int orig;
char mot[nbMax];
int dest;
}instruct;

typedef struct automate{
char alphabet[nbMax];
int etatInit ;
int etats[nbMax];
int etats_finaux[nbMax];
instruct instructions[nbMax];
int nb_alphabets;
int nb_instructions ;
int nb_etats;
int nb_etats_finaux;
}autom;


int isfinal(int etat,autom au)
{
int i;
for(i=0;i<au.nb_etats_finaux;i++)
{
if(au.etats_finaux[i]==etat)
return 0;
}
return -1;
}

int main()
{
autom AEFG;

/*Construction de l'automate generalise*/
printf("Nombre d'alphabets: ");
scanf("%d", &AEFG.nb_alphabets);
int i;
for ( i=0; i<AEFG.nb_alphabets; i++)
{
printf("Entrer un caractere : ");
scanf(" %c", &AEFG.alphabet[i]);
}

printf("\nAlphabets : ");
for ( i = 0; i < AEFG.nb_alphabets; i++) {
printf("%c, ", AEFG.alphabet[i]);
}

printf("\n\n");

printf("Nombre des etats: ");
scanf("%d", &AEFG.nb_etats);

for ( i=0; i<AEFG.nb_etats; i++){
AEFG.etats[i]=i;
}

printf("\nEtats : ");
for ( i = 0; i < AEFG.nb_etats; i++) {
printf("S(%d), ", AEFG.etats[i]);
}

printf("\n\n");

printf("Entrer le numero de l'etat initial: ");
scanf(" %d", &AEFG.etatInit);

printf("\n\n");

printf("Nombre des etats finaux: ");
scanf("%d" , &AEFG.nb_etats_finaux);

for ( i=0; i<AEFG.nb_etats_finaux; i++){
printf("Entrer le numero de l'etat : ");
scanf(" %d", &AEFG.etats_finaux[i]);
}

printf("\nEtats finaux : ");
for ( i = 0; i < AEFG.nb_etats_finaux; i++) {
printf("S(%d),", AEFG.etats_finaux[i]);
}

printf("\n\n");

printf("Nombre d'instructions: ");
scanf("%d", &AEFG.nb_instructions);

for ( i=0; i<AEFG.nb_instructions; i++){
printf("\nInstruction numero %d\n",i+1);
printf("Entrer le numero du premier etat : ");
scanf(" %d", &AEFG.instructions[i].orig);
printf("Entrer le mot (Veuillez noter epsilon par $): ");
scanf(" %s", &AEFG.instructions[i].mot);
printf("Entrer le numero du deuxieme etat : ");
scanf(" %d", &AEFG.instructions[i].dest);
}

printf("\nInstructions : \n");
for ( i = 0; i < AEFG.nb_instructions; i++) {
printf("{s(%d),%s,s(%d)}\n", AEFG.instructions[i].orig,AEFG.instructions[i].mot,AEFG.instructions[i].dest);
}


/*Construction de l'automate partiellement generalise*/
autom AEFPG;
AEFPG.nb_alphabets = AEFG.nb_alphabets;
for (i = 0; i < AEFPG.nb_alphabets; i++)
{
AEFPG.alphabet[i] = AEFG.alphabet[i];
}
AEFPG.nb_etats = AEFG.nb_etats;
for (i = 0; i < AEFPG.nb_etats; i++)
{
AEFPG.etats[i] = AEFG.etats[i];
}

AEFPG.nb_etats_finaux = AEFG.nb_etats_finaux;
for (i = 0; i < AEFPG.nb_etats_finaux; i++)
{
AEFPG.etats_finaux[i] = AEFG.etats_finaux[i];
}

AEFPG.nb_instructions = 0;
for (i=0; i<AEFG.nb_instructions; i++)
{
if (strlen(AEFG.instructions[i].mot)==1){
AEFPG.instructions[AEFPG.nb_instructions].orig=AEFG.instructions[i].orig;
strcpy(AEFPG.instructions[AEFPG.nb_instructions].mot,AEFG.instructions[i].mot) ;
AEFPG.instructions[AEFPG.nb_instructions].dest=AEFG.instructions[i].dest;
AEFPG.nb_instructions++;
} else {
int j;
for(j=0;j<strlen(AEFG.instructions[i].mot);j++){
instruct nouvelle;
if (j==0)
{
nouvelle.orig=AEFG.instructions[i].orig;
memcpy(nouvelle.mot, AEFG.instructions[i].mot + j, 1);
AEFPG.etats[AEFPG.nb_etats]=AEFPG.nb_etats;
nouvelle.dest=AEFPG.nb_etats;
AEFPG.nb_etats++;
AEFPG.instructions[AEFPG.nb_instructions]=nouvelle;

}else{

nouvelle.orig=AEFPG.etats[AEFPG.nb_etats-1];


if (j+1==strlen(AEFG.instructions[i].mot))
{

memcpy(nouvelle.mot, AEFG.instructions[i].mot + j, 1);
nouvelle.dest=AEFG.instructions[i].dest;
AEFPG.instructions[AEFPG.nb_instructions]=nouvelle;
} else {
memcpy(nouvelle.mot, AEFG.instructions[i].mot + j, 1);
AEFPG.etats[AEFPG.nb_etats]=AEFPG.nb_etats;
nouvelle.dest=AEFPG.nb_etats;
AEFPG.nb_etats++;
AEFPG.instructions[AEFPG.nb_instructions]=nouvelle;

}
}
AEFPG.nb_instructions++;
}
}
}

printf("\n\n");

for ( i = 0; i < AEFPG.nb_etats; i++) {
        int j;
for ( j = i + 1; j < AEFPG.nb_etats; j++) {
if (AEFPG.etats[i] == AEFPG.etats[j]) {
        int k;
for (k = j; k < AEFPG.nb_etats - 1; k++) {
AEFPG.etats[k] = AEFPG.etats[k + 1];
}
AEFPG.nb_etats--;
j--;
}
}
}


/*Construction de l'automate simple*/
autom autoS;
   autoS.nb_alphabets=0;
    autoS.nb_instructions=0 ;
    autoS.nb_etats=0;
    autoS.nb_etats_finaux=0;
   for ( i = 0; i < AEFPG.nb_alphabets; i++) {
    autoS.alphabet[i]=AEFPG.alphabet[i];
    autoS.nb_alphabets++;
    }
    for ( i = 0; i < AEFPG.nb_etats; i++) {
        autoS.etats[i] = AEFPG.etats[i];
        autoS.nb_etats++;
    }
    autoS.etatInit=AEFPG.etatInit;
    for ( i=0; i<AEFPG.nb_etats_finaux; i++){
    autoS.etats_finaux[i] = AEFPG.etats_finaux[i];
    autoS.nb_etats_finaux++;
    }
    for ( i = 0; i < AEFPG.nb_instructions; i++) {
      autoS.instructions[i].orig = AEFPG.instructions[i].orig;
      strcpy(autoS.instructions[i].mot,AEFPG.instructions[i].mot)  ;
      autoS.instructions[i].dest= AEFPG.instructions[i].dest;
      autoS.nb_instructions++;
    }
    i=0;
    int epTrouve ;
    while(i<autoS.nb_instructions)
   {
    instruct instruc1 = autoS.instructions[i];
    if(strcmp(instruc1.mot,"$")==0)
    {
        epTrouve=0;
        if(isfinal(instruc1.dest,autoS)==0)
        {
            autoS.etats_finaux[autoS.nb_etats_finaux]=instruc1.orig;
            autoS.nb_etats_finaux ++;
        }
        int j;
        for(j=0;j<autoS.nb_instructions;j++)
        {
            instruct instruc2 = autoS.instructions[j];
            if(instruc2.orig==instruc1.dest)
            {
                epTrouve=1;
                instruct instruc3;
                instruc3.orig = instruc1.orig;
                strcpy(instruc3.mot,instruc2.mot);
                instruc3.dest = instruc2.dest;
                if(strcmp(autoS.instructions[i].mot,"$")==0)
                    autoS.instructions[i] = instruc3;
                else
                {
                    autoS.instructions[autoS.nb_instructions] = instruc3;
                    autoS.nb_instructions++;
                }
            }
        }
            if(epTrouve==0)
            {
                autoS.instructions[i] = autoS.instructions[autoS.nb_instructions-1] ;
                autoS.nb_instructions--;
            }
    }
    else
    {
        i++;
    }
   }

   printf("L'automate simple equivalent:\nL'alphabet: ");
    for ( i = 0; i < autoS.nb_alphabets; i++)
    {
        printf("%c, ", autoS.alphabet[i]);
    }
printf("\nLes etats: ");
for ( i = 0; i < autoS.nb_etats; i++) {
printf("S(%d), ", autoS.etats[i]);
}

printf("\nLes etats finaux: ");
for ( i = 0; i < autoS.nb_etats_finaux; i++) {
printf("S(%d),", autoS.etats_finaux[i]);
}
printf("\nL'etat initial: S(%d)",autoS.etatInit);
printf("\nLes instructions: \n");
for ( i = 0; i < autoS.nb_instructions; i++) {
printf("{S(%d),%s,S(%d)}\n", autoS.instructions[i].orig,autoS.instructions[i].mot,autoS.instructions[i].dest);
}

return 0;
}
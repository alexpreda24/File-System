//Preda Ioan Alexandru-313CB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbore.h"
void SRD(TArb a,TArb root)
{   /*se parcurge arborele (stanga-radacina-dreapta)si se afiseaza numele
     daca are ca parinte pe root*/
    if (!a)
        return;
    SRD(a->st,root);
    if(strcmp((a->par)->nume,root->nume) == 0)printf("%s ", a->nume);
    SRD(a->dr,root);
}
int Cautaredirectorparinte(TArb a,char *x)
{
    TArb b = a;
    //se cauta directorul parinte
    while(b)
    {   
        if (strcmp(b->nume, x) == 0){
            return 1;
            }
        else if (strcmp(b->nume, x) < 0)
            b = b->dr;
        else
            b = b->st;
    }
    return 0;
}
int Cautaredirector(TArb a,char *x,TArb *gasit,TArb root)
{
    TArb b = a;
    /*se cauta directorul in root iar daca se gaseste i se retine 
    parintele*/
    while(b)
    {   
        if (strcmp(b->nume, x) == 0 && strcmp((b->par)->nume,root->nume) == 0){
          
            *gasit = b;
            return 1;
            }
        else if (strcmp(b->nume, x) < 0)
            b = b->dr;
        else
            b = b->st;
    }
    return 0;
}
int findfisier(TArb a,char *x,TArb *root,TArb a1)
{
    TArb b = a;
    /*cautam fisierul in tot arborele de fisiere,fara sa tinem
    cont de parinte*/
    while(b)
    {   
        if (strcmp(b->nume, x) == 0){
               TArb x1 = b->par;
            while(strcmp(x1->nume,"root") != 0){
                int p = Cautaredirectorparinte(a1,x1->nume);
                 if(p == 0)return 0;
                 x1 = x1->par;
            }
            *root = b->par;
            return 1;
            }
        else if (strcmp(b->nume, x) < 0)
            b = b->dr;
        else
            b = b->st;
    }
    return 0;
}
int finddirector(TArb a,char *x,TArb *root)
{
    TArb b = a;
    /*cautam directoul in tot arborele de directoare fara sa tinem
    cont de parinte*/
    while(b)
    {   
        if (strcmp(b->nume, x) == 0){
              TArb x1 = b;
            while(strcmp(x1->nume,"root") != 0){
                int p = Cautaredirectorparinte(a,x1->nume);
                 if(p == 0)return 0;
                 x1 = x1->par;
            }
            *root = b->par;
            return 1;
            }
        else if (strcmp(b->nume, x) < 0)
            b = b->dr;
        else
            b = b->st;
    }
    return 0;
}
int Inseraredirector(TArb *a, char *x, TArb a1, TArb root)
{

    TArb n, p, aux;
    p = a1;
    /*cautam in arborele de fisiere daca exista un fisier cu acest nume
    si care are ca parinte directorul root*/
    while (p)
    {
        if (strcmp((p->par)->nume,root->nume) == 0 && strcmp(x, p->nume) == 0)
        {
            printf("File %s already exists!\n", x);
            return 0;
        }
        if (strcmp(x, p->nume) < 0)
            p = p->st;
        else
            p = p->dr;
    }
    if (*a == NULL)
    {
        *a = ConstrFr(x);
        (*a)->par = root;
       
        return 1;
    }

    n = *a;
    /*cautam in arborele de directoare daca exista un director cu acest
     nume in directorul root iar daca insereaza  directorul in directorrul
     de fisiere*/
    while (n)
    {
        p = n;
        // printf("%s ",p->nume);
        if (strcmp(x, n->nume) == 0 && strcmp((n->par)->nume,root->nume) == 0)
        {
            printf("Directory %s already exists!\n", x);
            return 0;
        }
        if (strcmp(x, n->nume) <= 0)
            n = n->st;
        else
            n = n->dr;
    }
    aux = ConstrFr(x);
    aux->par = root; /*am inserat elementul x in arborele de directoare*/
   
    if (strcmp(aux->nume, p->nume) < 0)
        p->st = aux;
    else
        p->dr = aux;
  
    return 1;
}
int Inserarefisier(TArb *a, char *x, TArb a1, TArb root)
{
    //    if((*a)) printf("%s ",(*a)->nume);
  
    TArb n, p, aux;
    p = a1;
    while (p)
    {
        if (strcmp((p->par)->nume,root->nume) == 0 && strcmp(x, p->nume) == 0)
        {
            printf("Directory %s already exists!\n", x);
            return 0;
        }
        if (strcmp(x, p->nume) < 0)
            p = p->st;
        else
            p = p->dr;
    }
    if (*a == NULL)
    {
        *a = ConstrFr(x);
        (*a)->par = root;
        return 1;
    }

    n = *a;
    while (n)
    {
        p = n;
      
        if (strcmp(x, n->nume) == 0  && strcmp((n->par)->nume,root->nume) == 0)
        {
            printf("File %s already exists!\n", x);
            return 0;
        }
        if (strcmp(x, n->nume) <= 0)
            n = n->st;
        else
            n = n->dr;
    }
    aux = ConstrFr(x);
    aux->par = root; /*am inserat elementul x in arborele de directoare*/
    if (strcmp(aux->nume, p->nume) < 0)
        p->st = aux;
    else
        p->dr = aux;
 
    return 1;
}

void Stergefisier(TArb *a,char *x,TArb root){
     TArb aux, p = *a, n, k = NULL;
      
     int s = 0;
     if(strcmp((*a)->nume,x) == 0 && strcmp(((*a)->par)->nume,root->nume) == 0){
         s = 1;
         if((*a)->st == NULL && (*a)->dr == NULL)*a = NULL;
         else if((*a)->st == NULL){
             p = (*a)->dr;
             *a = NULL;
             *a = p;
         }
         else if((*a)->dr == NULL){
             p = (*a)->st;
             *a = NULL;
             *a = p;
         }
         else 
          /*daca ambii subarbori diferiti de NULL atunci
             se duce in celula cea mai din dreapta din 
             subarborele stang*/{
              {
                n = (*a)->st;
                k = p;
                while (n->dr)
                {
                    k = n;
                    n = n->dr;
                }
                strcpy((*a)->nume, n->nume);
                (*a)->par = n->par;
                if (n->st == NULL && n->dr == NULL)
                {
                    if (k)
                    {
                        if (strcmp((k->st)->nume, p->nume) == 0)
                            k->st = NULL;
                        else if (strcmp((k->dr)->nume, p->nume) == 0)
                            k->dr = NULL;
                        
                    }
                }
                else if (n->dr == NULL)
                {
                    aux = n->st;
                    aux = n->st;
                    n->st = NULL;
                    if (k)
                    {
                        if (strcmp(k->nume, aux->nume) < 0)
                            k->dr = aux;
                        else
                            k->st = aux;
                    }
                    n = aux;
                 
                }
            }
         }
     }
     p = *a;
      if (!p)
        return;
    while (p && s == 0)
    {

        if ( strcmp(p->nume, x) == 0 && strcmp((p->par)->nume,root->nume) == 0)
        {
            s = 1;
            if (p->st == NULL && p->dr == NULL)
            {
                if (k)
                {
                  if (k->st && strcmp((k->st)->nume, p->nume) == 0)
                        k->st = NULL;
                    else if(k->dr && strcmp((k->dr)->nume, p->nume) == 0)
                        k->dr = NULL;
                }
                
            }
            else if (p->st == NULL)
            {
                aux = p->dr;
                if (k)
                {
                    if (strcmp(k->nume, aux->nume) < 0)
                        k->dr = aux;
                    else
                        k->st = aux;
                }
               
            }
            else if (p->dr == NULL)
            {
                aux = p->st;
                if (k)
                {
                    if (strcmp(k->nume, aux->nume) < 0)
                        k->dr = aux;
                    else
                        k->st = aux;
                    if(!aux)k->dr = NULL;
                   
                }
              
            }
            else if (p->st && p->dr)
            /*daca ambii subarbori diferiti de NULL atunci
             se duce in celula cea mai din dreapta din 
             subarborele stang*/
           {
                n = p->st;
                k = p;
                while (n->dr)
                {
                    k = n;
                    n = n->dr;
                }
                strcpy(p->nume, n->nume);
                p->par = n->par;
                if (n->st == NULL && n->dr == NULL)
                {
                    if (k)
                    {
                        if (k->st && strcmp((k->st)->nume, p->nume) == 0)
                        k->st = NULL;
                    else if(k->dr && strcmp((k->dr)->nume, p->nume) == 0)
                            k->dr = NULL;
                        // n = NULL;
                    }
                }
                else if (n->dr == NULL)
                {
                    aux = n->st;
                    if (k)
                    {
                        if (strcmp(k->nume, aux->nume) < 0)
                            k->dr = aux;
                        else
                            k->st = aux;   
                    }
                }
            }
        }
        else if (strcmp(p->nume, x) < 0)
        {
            k = p;
            p = p->dr;
        }
        else
        {
            k = p;
            p = p->st;
        }
    }
    if (s == 0)
        printf("File %s doesn't exist!\n", x);
}
void Stergedirector(TArb *a, char *x,TArb root)
{
    TArb aux, p = *a, n,  k = NULL;
     int s = 0;
     if(strcmp((*a)->nume,x) == 0){
         s = 1;
         if((*a)->st == NULL && (*a)->dr == NULL)*a = NULL;
         else if((*a)->st == NULL){
             p = (*a)->dr;
             *a = NULL;
             *a = p;
         }
         else if((*a)->dr == NULL){
             p = (*a)->st;
             *a = NULL;
             *a = p;
         }
         else {
              {
                n = (*a)->st;
                k = p;
                while (n->dr)
                {
                    k = n;
                    n = n->dr;
                }
                strcpy((*a)->nume, n->nume);
                (*a)->par = n->par;
                if (n->st == NULL && n->dr == NULL)
                {
                    if (k)
                    {
                        if (k->st && strcmp((k->st)->nume, p->nume) == 0)
                        k->st = NULL;
                    else if(k->dr && strcmp((k->dr)->nume, p->nume) == 0)
                            k->dr = NULL;
                        
                    }
                }
                else if (n->dr == NULL)
                {
                    aux = n->st;
                    aux = n->st;
                    n->st = NULL;
                    if (k)
                    {
                        if (strcmp(k->nume, aux->nume) < 0)
                            k->dr = aux;
                        else
                            k->st = aux;
                    }
                    n = aux;
                 
                }
            }
         }
     }
     p = *a;
      if (!p)
        return;
    while (p && s == 0)
    {

        if ( strcmp(p->nume, x) == 0 && strcmp((p->par)->nume,root->nume) == 0)
        {
            s = 1;
            if (p->st == NULL && p->dr == NULL)
            {
                if (k)
                {   
                    
                    if (k->st && strcmp((k->st)->nume, p->nume) == 0)
                        k->st = NULL;
                    else if(k->dr && strcmp((k->dr)->nume, p->nume) == 0)
                        k->dr = NULL;
              
                }
                
            }
            else if (p->st == NULL)
            {
                aux = p->dr;
                if (k)
                {
                    if (strcmp(k->nume, aux->nume) < 0)
                        k->dr = aux;
                    else
                        k->st = aux;
                }
               
            }
            else if (p->dr == NULL)
            {
                aux = p->st;
                if (k)
                {
                    if (strcmp(k->nume, aux->nume) < 0)
                        k->dr = aux;
                    else
                        k->st = aux;
                    if(!aux)k->dr = NULL;
                    //    k->st = aux;
                }
              
            }
            else if (p->st && p->dr)
            {
                n = p->st;
                k = p;
                while (n->dr)
                {
                    k = n;
                    n = n->dr;
                }
                strcpy(p->nume, n->nume);
                p->par = n->par;
                if (n->st == NULL && n->dr == NULL)
                {
                    if (k)
                    {
                        if (k->st && strcmp((k->st)->nume, p->nume) == 0)
                            k->st = NULL;
                        else if (k->dr && strcmp((k->dr)->nume, p->nume) == 0)
                            k->dr = NULL;
                         n = NULL;
                    }
                }
                else if (n->dr == NULL)
                {
                    aux = n->st;
                    if (k)
                    {
                        if (strcmp(k->nume, aux->nume) < 0)
                            k->dr = aux;
                        else
                            k->st = aux;   
                    }
                }
            }
        }
        else if (strcmp(p->nume, x) < 0)
        {
            k = p;
            p = p->dr;
        }
        else
        {
            k = p;
            p = p->st;
        }
    }
    if (s == 0)
        printf("Directory %s doesn't exist!\n", x);
}
void PWD(TArb root){
    /*se ia un vector de frecventa 
    care v-a indica calea*/
    int n = 0,i = 0;
    TArb p = root;
    while(p)
    {
        n++;
        p = p->par; 
    }
    char **pwd;
    pwd = malloc(n * sizeof(char *));
    if(!pwd)return;
     p = root;
     while(p){
         int lungime = strlen(p->nume);
         pwd[i] = malloc((lungime + 1) * sizeof(char));
         if(!(pwd[i]))return;
         strcpy(pwd[i],p->nume);
         i++;
         p = p->par;
     }
     for(i = n - 1; i >= 0;i--)
     printf("/%s",pwd[i]);
     printf("\n");
     for(i = 0;i < n; i++)
     free(pwd[i]);
     free(pwd);//eliberez memoria pentru vectorul care ne arata calea
}
void PWDdir(char *x,TArb root){
    int n = 0,i = 0;
    TArb p = root;
    while(p)
    {
        n++;
        p = p->par; 
    }
    char **pwd;
    pwd = malloc(n * sizeof(char *));//vectorul care 
    if(!pwd)return;
     p = root;
     while(p){
         int lungime = strlen(p->nume);
         pwd[i] = malloc((lungime + 1) * sizeof(char));
         if(!(pwd[i]))return;
         strcpy(pwd[i],p->nume);
         i++;
         p = p->par;
     }
     for(i = n - 1; i >= 0;i--)
     printf("/%s",pwd[i]);
     printf("/%s",x);
     printf("\n");
     for(i = 0;i < n; i++)
     free(pwd[i]);
     free(pwd);//eliberez memoria pentru vectorul care ne arata calea
}
int main(int argc, char **input)
{

    size_t len = 0;
    // int i;
    
    char *line = NULL, *p = NULL;
    TArb aux = (TArb)malloc(sizeof(TNod));
    //aloc memoria pentru root pentru directoare
    if (!aux)
        return 0;
    aux->nume = malloc(sizeof(char) * 40);
    TArb dir = NULL;
    TArb fis =  NULL;
    strcpy(aux->nume, "root");
    aux->st = NULL;
    aux->dr = NULL;
    aux->par = NULL;

    while (getline(&line, &len, stdin) != -1)
    {

        p = strtok(line, " ");
        if (p[strlen(p) - 1] == '\n')
            p[strlen(p) - 1] = '\0';
        if (strcmp(p, "touch") == 0)
        { 
           
            p = strtok(NULL, " ");
            if (p[strlen(p) - 1] == '\n')
                p[strlen(p) - 1] = '\0';
            Inserarefisier(&fis, p, dir, aux);
            
         
        }
        if (strcmp(p, "mkdir") == 0)
        {
           
            p = strtok(NULL, " ");
            if (p[strlen(p) - 1] == '\n')
                p[strlen(p) - 1] = '\0';
            Inseraredirector(&dir, p, fis, aux);
        }
        if (strcmp(p, "ls") == 0)
        {
            
            TArb x = dir, y = fis;
            SRD(x,aux);
            SRD(y,aux);
            printf("\n");
          
        }
        if (strcmp(p, "rm") == 0)
        {
          
            p = strtok(NULL, " ");
            if (p[strlen(p) - 1] == '\n')
                p[strlen(p) - 1] = '\0';
             
            Stergefisier(&fis, p,aux);
           
        }
        if (strcmp(p, "rmdir") == 0)
        {
            
            p = strtok(NULL, " ");
            if (p[strlen(p) - 1] == '\n')
                p[strlen(p) - 1] = '\0';
               
            Stergedirector(&dir, p,aux);
             
        }
        if (strcmp(p, "cd") == 0)
        {
            p = strtok(NULL, " ");
             if (p[strlen(p) - 1] == '\n')
                p[strlen(p) - 1] = '\0';
            if(strcmp(p,"..") == 0 && aux->par != NULL){aux = aux->par;
          
            }
            else if(strcmp(p,"..") != 0){
              
                TArb x;
            int radacina = Cautaredirector(dir,p,&x,aux);
            if(radacina == 0 )printf("Directory not found!\n");
            else {
                 aux = x;
                 }
            }
            

        }
         if(strcmp(p,"pwd") == 0){
            PWD(aux);
         }
        if(strcmp(p,"find") == 0){
            TArb aux1 = InitA();
            p = strtok(NULL," ");
            if(strcmp(p,"-f") == 0){
                  p = strtok(NULL, " ");
             if(p[strlen(p) - 1] == '\n')p[strlen(p) - 1] = '\0';
                int nr = findfisier(fis,p,&aux1,dir);
              if(nr == 0)printf("File %s not found!\n",p);
              //nu s a gasit fisierul
              else {
                  printf("File %s found!\n",p);
                  PWD(aux1);
                  }
            }
            else {
                 p = strtok(NULL, " ");
             if (p[strlen(p) - 1] == '\n') p[strlen(p) - 1] = '\0';
            
              int nr = finddirector(dir,p,&aux1);
              if(nr == 0)printf("Directory %s not found!\n",p);
              else {
                  printf("Directory %s found!\n",p);
                  PWDdir(p,aux1);
                  
                  }
            }
              
        }
    
    }
    free(line);
    DistrArb(&dir);
    DistrArb(&fis);
  
    return 0;
}

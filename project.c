#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>
char str1[200] = {};
char str[10][40] = {};
char clipboard[50000];



void input();
void createfile(char *s);
int ifexists(const char *filename);
void insert(char *s1,char *s2,char *s3);
void cat(char *s);
void copy(char *str1,char *str2,char *str3,char *str4);
void remstr(char *str1,char *str2,char *str3,char *str4);
char *readf(char *filename);


int main() {
    input();
    char *t;
    char *t1;char *t2;char *t3;
    int i,j;
    if (strcmp(str[0], "createfile") == 0){
        t = str[2];
        createfile(t);}

    if (strcmp(str[0], "insertstr") == 0){
        insert(str[2],str[4],str[6]);}

    if (strcmp(str[0], "cat") == 0){
        t = str[2];
        cat(t);}

    if (strcmp(str[0], "copystr") == 0){
       copy(str[2],str[4],str[6],str[7]);
    }

    if (strcmp(str[0], "removestr") == 0){
        remstr(str[2],str[4],str[6],str[7]);
    }


        return 0;
    }

char *readf(char *filename){
   FILE *f;
   f = fopen(filename,"r");
   if(f == NULL)
        return NULL;
   fseek(f,0,SEEK_END);
   int h = ftell(f);
   fseek(f,0,SEEK_SET);

   char *string = malloc(sizeof(char) * (h+1));
   char c;
   int i=0;
   while((c=fgetc(f))!=EOF){
        string[i] = c;
        i++;
   }
   string[i]='\0';
   fclose(f);
   return string;}


int ifexists(const char *filename){
     struct stat buffer;
     return stat(filename, &buffer) == 0 ? 1 : 0;}


void input(){
    gets(str1);
    int n = strlen(str1);
    int c1 = 0;
    int c2 = 0;
    int c = 0;
    int e = 0;
    str[0][0] = str1[0];
    c2++;
    for (int i = 1; i < n; i++){
        if (str1[i] == 32 && c % 2 == 0){
            c1++;
            c2 = 0;}
        else if (str1[i] == '"' && str1[i - 1] != 92){
            c++;
            str[c1][c2] = str1[i];
            c2++;}
        else{
            str[c1][c2] = str1[i];
            c2++;}}}

void createfile(char *s){
    char filename[100];
    char *pt;
    char *s3;

    pt = strtok(s,"/");
    while (pt!=NULL){
        s3 = pt;
        pt = strtok(NULL,"/");
    }
    puts(s3);
    sprintf(filename, "C://root//%s", s3);
    FILE *f;
    if (ifexists(filename)==1){
    printf("File exists");}
    else{
    f = fopen(filename,"w");
    fclose(f);}}


void insert(char *s1,char *s2,char *s3){
        char *pt3;
        char *fname;
        char filename[100];
        pt3 = strtok(s1,"/");
        while (pt3!=NULL){
            fname = pt3;
            pt3 = strtok(NULL,"/");
        }

        int l,r;
        sscanf(s3,"%d:%d",&l,&r);

        sprintf(filename, "C://root//%s", fname);

        int i;
        int n = strlen(s2);
        FILE *f;
        f = fopen(filename,"w+");
        int j,k;
        for(j=0;j<l;j++){
            fputs("\n",f);
        }
        for(k=0;k<r;k++){
            fputs(" ",f);
        }
        for(i=0;i<n;i++){
            char c = s2[i];
            switch(c){
        case '\\':
            if((s2[i+1]) == '\\'){
            fputs("\\n",f);
            i+=2;
                break;}
            else if((s2[i+1]) == 'n'){
            fputs("\n",f);
            i++;}
            break;
        case '\\n':
            fputc('\n',f);
        default:
            fputc(c,f);
        }}
        fclose(f);}


void cat(char *s){
    char filename[100];
    sprintf(filename, "C://root//%s", s);
    char c;
    FILE *f;
    f = fopen(filename,"r");
    if(f==NULL)
        printf("ERROR.");
    else{
        c = fgetc(f);
        while(c!=EOF){
            printf("%c", c);
            c = fgetc(f);}}
    fclose(f);}


void copy(char *str1,char *str2,char *str3,char *str4){
    char filname[100];
    sprintf(filname, "C://root//%s",str1);
    FILE *fp;
    fp = fopen(filname, "r+");
   fseek(fp, 0, SEEK_END);
   int h = ftell(fp);
    fclose(fp);

    char s[50000];
    char filename[100];
    sprintf(filename, "C://root//%s",str1);
    FILE *f;
    f = fopen(filename, "r+");
     int l,r;
     sscanf(str2,"%d:%d",&l,&r);
    int i;
    if(f==NULL)
        printf("ERROR.");
    else{
        s[i] = fgetc(f);
        while(s[i]!=EOF){
            s[i] = fgetc(f);
            i++;}}
    for(i=0;i<h;i++){
        if(s[i] == '\n'){
            l--;}
        if(l==0) break;
    }
    int j;
    int z=0;
    int size;
    sscanf(str3,"%d:%d",&size);
    int x1 = (i+1+r);
    char temp;
    if (strcmp(str4, "-f") == 0){
        int x2 = x1 + size;
        for(j=x1;j<x2;j++){
        temp = s[j];
        s[j] = clipboard[z];
        clipboard[z] = temp;
        z++;
    }}
    if (strcmp(str4, "-b") == 0){
        int x2 = x1 - size;
        for(j=x1;j>x2;j--){
        temp = s[j];
        s[j] = clipboard[z];
        clipboard[z] = temp;
        z++;}
        strrev(clipboard);}

    }

void remstr(char *s1,char *s2,char *s3,char *s4){
    char filename[100];
    sprintf(filename, "C://root//%s",s1);
    FILE *f;
    f = fopen(filename, "r+");
     int l,r;
     int b;
     sscanf(s2,"%d:%d",&l,&r);
     l--;
     char *res = readf(filename);
     int i;
     for(i=0;res[i]!=NULL;i++){
        if(res[i]=='\n'){
            l--;
                   }
        if(l==0){
            b=i;}
     }
     int size;
     sscanf(s3,"%d",&size);
     int n;
     n = strlen(res);
     int x1 = b+2+r;

     if (strcmp(s4, "-b") == 0){
     int x2 = x1 - size;
     int d = x1-x2;
     while(d){
     for(i=x2;i<n;i++)
        res[i] = res[i+1];
        n--;
        d--;}}
    if (strcmp(s4, "-f") == 0){
     int x2 = x1 + size;
     int d = x2-x1;
     while(d){
     for(i=x1;i<n;i++)
        res[i] = res[i+1];
        n--;
        d--;}}
    int n1 = strlen(res);
    fclose(f);
    FILE *f1;
    f1 = fopen(filename, "w");
    for(i=0;i<=n;i++){
        fputc(res[i],f1);
    }
    fclose(f1);
}












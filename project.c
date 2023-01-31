#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>
char str1[200] = {};
char str[10][40] = {};
void input();
int ifexists(const char *filename);
int main() {
    input();
    char *t;
    char *t1;char *t2;char *t3;
    int i,j;
    if (strcmp(str[0], "createfile") == 0){
        //////////////
        t = str[2];
        createfile(t);}

    if (strcmp(str[0], "insertstr") == 0){
        insert(str[2],str[4],str[6]);}

    if (strcmp(str[0], "cat") == 0){
        t = str[2];
        cat(t);}

        return 0;
    }

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




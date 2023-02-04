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
#include <dirent.h>
#include <direct.h>
char str1[200] = {};
char str[20][60] = {};
char clipboard[50000];
char *qwe;


int input();
void createfile(char *s);
int ifexists(const char *filename);
void insert(char *s1,char *s2,char *s3);
void cat(char *s);
char *copy(char *str1,char *str2,char *str3,char *str4);
void remstr(char *str1,char *str2,char *str3,char *str4);
char *readf(char *filename);
void textcoimprator(char *s1,char *s2);


int main() {
    int x = input();
    char *t;
    char *t1;char *t2;char *t3;
    int i,j;
    if (strcmp(str[0], "createfile") == 0){
        createfile(str[2]);}

    if (strcmp(str[0], "insertstr") == 0){

    int n = strlen(str[4]);
        char s[100];
         int i;

   if(str[4][0]=='"'){
     for(i=0;i<100;i++){
        s[i] = str[4][i];}

    for(i=0;i<n;i++){
        s[i] = s[i+1];
    }
    strrev(s);
    for(i=0;i<n;i++){
        s[i] = s[i+1];
    }
    strrev(s);
    insert(str[2],s,str[6]);
    }
    else{
        insert(str[2],str[4],str[6]);}}

    if (strcmp(str[0], "cat") == 0){
        t = str[2];
        cat(t);}

    if (strcmp(str[0], "copystr") == 0){
       qwe = copy(str[2],str[4],str[6],str[7]);
       }

    if (strcmp(str[0], "removestr") == 0){
        remstr(str[2],str[4],str[6],str[7]);}

    if (strcmp(str[0], "cutstr") == 0){
        copy(str[2],str[4],str[6],str[7]);
        remstr(str[2],str[4],str[6],str[7]);}

    if (strcmp(str[0], "compare") == 0){
        textcoimprator(str[1],str[2]);
    }

    if (strcmp(str[0], "grep") == 0){
        if (strcmp(str[1], "–str") != 0){
            int i;
            for(i=4;i<=x;i++){
                grep(str[1],str[2],str[i]);
               if(i!=4){
               printf("\n");}}}}

    if (strcmp(str[0], "pastestr") == 0){
        puts(qwe);
        insert(str[2],qwe,str[4]);
    }

    /*if (strcmp(str[0], "tree") == 0){
    }*/





        return 0;
    }



void insert(char *s1,char *s2,char *s3){
    char filname[100];
    sprintf(filname, "C://%s",s1);
    FILE *firstfile;
    FILE *secondfile;
        firstfile = fopen(filname,"r");
        secondfile = fopen("temp.txt","w");
        int l,r;
        char c;
        sscanf(s3,"%d:%d",&l,&r);

    int i=0;
    int j=0;
    while (i != l){
        c = fgetc(firstfile);
        if(c == EOF){
            c = '\n';}
        fputc(c,secondfile);
        if(c == '\n'){
            i++;}}
    while (j != r){
        c = fgetc(firstfile);
        if(c == EOF){
            c = ' ';}
        fputc(c,secondfile);

        j++;}
        char q;
       for(i=0;s2[i]!='\0';i++){
            q = s2[i];
            switch(q){
            case '\\':
            if((s2[i+1]) == '\\' && s2[i+2] == 'n'){
            fprintf(secondfile,"\\n");
            i+=2;
                break;}
            else if((s2[i+1]) == 'n'){
            fprintf(secondfile,"\n");
            i++;
            break;}
        default:
            fputc(s2[i],secondfile);
        }}

        c = fgetc(firstfile);
        while(c != EOF){
            fputc(c,secondfile);
            c = fgetc(firstfile);
        }
        fclose(firstfile);
        fclose(secondfile);

        firstfile = fopen(filname,"w");
        secondfile = fopen("temp.txt","r");
        c = fgetc(secondfile);
        while (c != EOF){
        fputc(c,firstfile);
        c = fgetc(secondfile);}
        fclose(secondfile);
        fclose(firstfile);
}



void grep(char *s1,char *word,char *s){
    char filename[100];
    sprintf(filename, "C://%s", s);

         FILE *f;
        f = fopen(filename,"r");
         char t[300];
        char *pt3;
        char *fname;
        pt3 = strtok(s,"/");
        while (pt3!=NULL){
            fname = pt3;
            pt3 = strtok(NULL,"/");
        }



        int num =0;
        char string[2000];
        int i;
        int r=0;
        int k=0;;
                if (f == NULL){
                        printf("Error\n");
                }
                while ( fgets(string,2000, f)!=NULL){
                if(strstr(string, word)!=NULL) {
                if(strcmp(s1,"-str")==0){
                   printf("%s\t%s", fname,string);}}
                r++;
                k+=r;}
                printf("\n%d\n",k);
        fclose(f);}




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


int input(){
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
            c2++;}}
            if (strcmp(str[0], "grep") == 0){
            return c1;}
            }

void createfile(char *s){
    char t[100];
    int n = strlen(s);
    int i;
    for (i=1;i<n;i++)
    {
    t[i-1] = s[i];
    if (s[i+1] == '/'){
        char *newdir = "c:\\";
        _chdir(newdir);
        int x =  _mkdir(t);
           if(strcmp(t,"root")!=0){
            if(errno == EEXIST){
                printf("dir already exist\n");}}}}
    FILE *file;
    if (file = fopen(t, "r")){
        fclose(file);
        printf("file already exists");}
    else
        file = fopen(t,"w");
        fclose(file);
    }



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


char *copy(char *str1,char *str2,char *str3,char *str4){
    char filname[100];
    sprintf(filname, "C://%s",str1);
    FILE *fp;
    fp = fopen(filname, "r+");
   fseek(fp, 0, SEEK_END);
   int h = ftell(fp);
    fclose(fp);

    char s[50000];
    char filename[100];
    sprintf(filename, "C://%s",str1);
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



        int m = strlen(clipboard);
        char *string = malloc(sizeof(char) * m);
        int u;
        for(u=0;u<m;u++){
            string[u] = clipboard[u];
        }
        return string;

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
    free(res);
}

void textcoimprator(char *s1,char *s2){
    char data[100][1000];
    char filename1[100];
    sprintf(filename1, "C://root//%s",s1);
    char data2[100][1000];
    char filename2[100];
    sprintf(filename2, "C://root//%s",s2);
    FILE *f1;
    f1 = fopen(filename1,"r");
    if(f1==NULL){
        printf("ERROR.");
        return 1;}

    int line = 0;
    while(!feof(f1) && !ferror(f1)){
            if(fgets(data[line],1000,f1)!=NULL){
                line++;
            }}
    fclose(f1);

    FILE *f2;
    f2 = fopen(filename2,"r");
    if(f2==NULL){
        printf("ERROR.");}

    int line2 = 0;
    while(!feof(f2) && !ferror(f2)){
            if(fgets(data2[line2],1000,f2)!=NULL){
                line2++;
            }}
    fclose(f2);

    int d;
    if(line>line2){
        d = line2;}
    else if(line2>line){
        d = line;}
    else{
        d = line;}
    int a[1000];
    int i;
    int c = 0;
    int j = 0;
    for(i=0;i<d;i++){
        if(strcmp(data[i],data2[i]) != 0){
            c++;
            a[j] = i;
            j++;
        }
    }
    int k = j;
    if(c!=0){
    printf("============ #%d ============\n",c);
    for(j=0;j<k;j++){
        printf("%s",data[a[j]]);
        if(j==k-1)
            printf("\n");
        printf("%s\n",data2[a[j]]);
    }}

    if(line2>line){
        printf(">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n",line,line2-1);
        for(i=line;i<line2;i++){
            printf("%s",data2[i]);}}
    if(line2<line){
        printf(">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n",line2,line-1);
        for(i=line2;i<line;i++){
            printf("%s",data[i]);}}

}

/*void tree(){
    DIR *directory;
    struct dirent *entry;
    directory = opendir("c://root");
    if(directory == NULL){
        printf("error\n");
        return 1;
    }
    if((entry = readdir(directory))!=NULL){
     /*   if(entry->d_type == DT_REG){

        }*/
       /* printf("%s\n",entry->d_name);
        tree(1,entry->d_name);

    }
    if(closedir(directory) == -1){
        printf("error\n");
        return 1;
    }
}*/














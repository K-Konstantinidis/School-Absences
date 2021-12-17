/*************************************************************************
        Copyright © 2021 Konstantinidis Konstantinos

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*************************************************************************/
#include <stdio.h>
#include <string.h>
#include "genlib.h"
#include "simpio.h"
#include <ctype.h>

typedef struct{
    char name[31];
    int absences;
}studentT;

void readinput(FILE* infile,studentT students[100],int *pAbsences,int *pStudents);
void writeOutput(FILE* outfile,int size,studentT students[],int total);

int main(){
    studentT students[100];
    FILE *infile,*outfile;

    infile=fopen("i2f9.dat","r");
    if (infile==NULL){
        printf("Cannot open input file i2f9.dat");
        exit(1);
    }

    outfile=fopen("o2f9.dat","w");
    int absences,student;
    readinput(infile, students, &absences, &student);
    writeOutput(outfile, absences, students, student);

    fclose(infile);
    fclose(outfile);

    return 0;
}

void readinput(FILE* infile, studentT students[100], int *pAbsences, int *pStudents){
    int nscan, absences, line;
    char name[30], comments[68], termch;
    *pAbsences=0;
    *pStudents=0;
    line=0;

    while(TRUE){
        nscan=fscanf(infile,"%30[^,], %d, %68[^\n]%c",name, &absences, comments, &termch);
        if(nscan==EOF) break;
        line++;
        if(nscan!=4||termch!='\n'){
            printf("Error in line %d. Program termination\n",line);
            exit(1);
        }
        if(absences>100){
            strcpy(students[*pAbsences].name, name);
            students[*pAbsences].absences = absences;
            (*pAbsences)++;
        }
        (*pStudents)++;
    }
}

void writeOutput(FILE* outfile, int size, studentT students[], int total){
    int i;
    printf("%-30s%9s\n","FULL NAME","ABSENCES");
    fprintf(outfile,"%-30s%9s\n","FULL NAME","ABSENCES");

    for(i=1;i<=39;i++)
        fputc('-',outfile);

    fputc('\n',outfile);

    for(i=0;i<size;i++){
        printf("%-30s%9d\n",students[i].name,students[i].absences);
        fprintf(outfile,"%-30s%9d\n",students[i].name,students[i].absences);
    }
    for(i=1;i<=39;i++){
        printf("-");
        fputc('-',outfile);
    }
    printf("\n");
    fputc('\n',outfile);

    printf("%-30s%9d\n","TOTAL STUDENTS",total);
    fprintf(outfile,"%-30s%9d\n","TOTAL STUDENTS",total);

    printf("%-30s%5d\n","TOTAL STUDENTS WITH ABSENCES > 100",size);
    fprintf(outfile,"%-30s%5d\n","TOTAL STUDENTS WITH ABSENCES > 100",size);
}

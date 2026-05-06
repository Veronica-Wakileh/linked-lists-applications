#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //has useful functions for dealing with characters
#include <math.h>// power function used in radix sort
struct district{//create a node to build the district list
    int totalPopulation;//this is computed using a function called calculate District Population
    char data[51]; //define a string with maximum 50 character used to store district name //51 includes NULL charachter
    struct district* next;//pointer to the next district
    struct district* previous;//pointer to the previous district
    struct town* PtrToList;//define a pointer that will concatenate the town and district lists////51 includes NULL charachter
    };
struct town{//create a node used to build the town list
int population;//population of each town
char data[51];//define a string with maximum 50 charahters used to store town name
struct town* next;//pointer to the next town
struct town* previous;//pointer to the previous town
};

// Function prototypes
void printMenu();
struct district* makeEmpty(struct district* L);
struct town* makeEmptyTown(char x[],int pop,struct town* L);
void deleteListD(struct district* L);
void deleteListT(struct town* L);
struct district* findDistrict(char x[], struct district* L);
struct district* findLastDistrict(struct district*L);
struct town* findTown(char x[], struct town* L);
struct town* findLastTown(struct town*L);
int isEmpty(struct district* L);
int isEmptyTown(struct town*L);
int isLast(struct district* P, struct district* L);
int isLastTown(struct town* P, struct town* L);
void LoadFile(struct district* L);
void PrintInputData(struct district* L);
void PrintTheSortedInformation(struct district* L);
void insertDistrict(char x[],struct district*L);
void insertDistrictAndSort(struct district* L);
void insertTown(char x[],int pop,struct town*L);
void insertNewTown(struct district* L);
void CalculatePopulationMaxAndMin(struct district*L);
int calculateDistrictPopulation(struct town* L);
void deleteTown(struct district* L);
void deleteDistrict(struct district* L);
void printDistricts(struct district* L);
void changePopulation(struct district* L);
void saveToOutputFile(struct district* L);
int sizeOfLinkedList(struct district*L);
void SortDistricts(struct district* L);
int getMaxLengthDistrict(struct district* L);
void AddSpaces(struct district*L);
void Removespaces(struct district*L);
void SortTowns(struct district *L);
int getMaxNumber(struct town*L);
struct town* makeEmptyTownHead(struct town *L);
int NumberOfDigits(int n);

int main()
{
    int option;//the option that will be entered by the user
    struct district* head ;//define a district node called head with no data that will be pointing to districts
    head= makeEmpty(NULL); //called make empty function to create a head of a linked list  with unspecified number of strings
    do{
    printMenu(); //display application menu for the user
    scanf("%d",&option);//scan the option selected by the user
    getchar();//let gets in other function read string within incorporated spaces correctly //actually remove the null terminator placed by scanf after reading from the user
    switch(option){//do the operation based on the user choices
    case 1:LoadFile(head);break;
    case 2:PrintInputData(head);break;
    case 3:SortDistricts(head);break;
    case 4:SortTowns(head);break;
    case 5:PrintTheSortedInformation(head);break;
    case 6:insertDistrictAndSort(head);break;
    case 7:insertNewTown(head);break;
    case 8:deleteTown(head);break;
    case 9:deleteDistrict(head);break;
    case 10:CalculatePopulationMaxAndMin(head);break;
    case 11:printDistricts(head);break;
    case 12:changePopulation(head);break;
    case 13:saveToOutputFile(head);break;
    case 14: printf("exit application");exit(0);
    default:printf("try again");break;
    }}while(option!=14);//display menu to the user until they choose exit
    return 0;

}

void printMenu() // print menu to user
{
printf("Menu of my application\n");
printf("Please select an operation \n");
printf("1-load the input file(Palestinian districts and their town with population)\n");
printf("2-Print the loaded information before sorting(as in the input file format)\n");
printf("3-Sort the districts alphabetically using Radix sort\n");
printf("4-Sort the towns for each district based on population in ascending order.\n");
printf("5-Print the sorted information\n");
printf("6-Add a new district to the list of sorted districts (and sort the list)\n");
printf("7-Add a new town to a certain district\n");
printf("8-Delete a town from a specific district\n");
printf("9-Delete a complete district\n");
printf("10-Calculate the population of Palestine, the max and min town population\n");
printf("11-Print the districts and their total population\n");
printf("12-Change the population of a town\n");
printf("13-Save to output file\n");
printf("14-Exit\n");
}

struct district* makeEmpty(struct district* L){//build the head of the district list
if(L!= NULL){//if the list already have districts delete them
    deleteListD(L);
}
L=(struct district*)malloc(sizeof(struct district));//reserve a place in memory for the head of the districts linked list which will have no data and point to districts
if(L==NULL){//check if the district node was actually reserved if not we can't do operations on it
    printf("out of memory\n");
}
else {//if the reservation was successful let the next and previous pointers of the head point to null
        L->next=NULL;
        L->previous=NULL;
}
return L;//return head of the district list
}
struct town* makeEmptyTown(char x[],int pop,struct town* L){//build the head of the town list
if(L!= NULL){//if the list already have towns delete them
    deleteListT(L);
}
L=(struct town*)malloc(sizeof(struct town));//reserve a place in memory for the head of the towns linked list which will be the first town in the list
if(L==NULL){//check if the town node was actually reserved if not we can't do operations on it
    printf("out of memory\n");
}
else {//if the reservation was successful let the next and previous pointers of the head point to null and store the town name and population passed by the user
        L->next=NULL;
        L->previous=NULL;
        strcpy(L->data,x);//when dealing with strings we use string functions to do operations correctly and including string.h library //L->data =x will make L->data actually point to x rather than copying the data stored in x
        L->population=pop;
}
return L;//return head of the town list
}
struct town* makeEmptyTownHead(struct town *L){
if(L!= NULL){//if the list already have towns delete them
    deleteListT(L);
}
L=(struct town*)malloc(sizeof(struct town));//reserve a place in memory for the head of the towns linked list which will be the first town in the list
if(L==NULL){//check if the town node was actually reserved if not we can't do operations on it
    printf("out of memory\n");
}
else{//reserve a place in memory for the head of the towns linked list which will have no data and point to towns(used for sorting towns)
  L->next=NULL;
}
return L;//return head of the town list
}
void deleteListD(struct district * L){//delete district list
struct district*p;
struct district*temp;
p=L->next;//pointer to the districts in list that will be deleted
L->next=NULL;//let the next pointer of the head point to NULL
p->previous=NULL;//let the previous of the first node point to null it becomes the head of the list the will be deleted
while(p!=NULL){//this operation will continue until we delete the last district in the last
   temp=p->next;//pointer to the district that will be removed after district p
   free(p);//delete district p
   p=temp;//let p point to the next district to be deleted
   }}
void deleteListT(struct town * L){//delete town list
struct town*p;
struct town*temp;
p=L;//pointer to the towns in list that will be deleted
while(p!=NULL){//this operation will continue until we delete the last town in the list
   temp=p->next;//pointer to the town that will be removed after town p
   free(p);//delete town p
   p=temp;//let p point to the next town so we delete it
   }
   }
struct district* findDistrict(char x[],struct district *L){//return pointer to a district we are searching for
struct district*p;
p=L->next;//let p point to the first district in the list
while(p!=NULL&&strcasecmp(p->data,x)!=0){//strcasecmp() function is used for comparing strings
        p=p->next;
}
return p;//p is the district we are looking for by name
}
struct district* findLastDistrict(struct district*L){//used when inserting districts
struct district*p;
p=L->next;//let p point to the first district in the list
while(!isLast(p,L)){
    p=p->next;//here we find the last district by checking if its next pointer points to null
}
return p;
}
struct town* findTown(char x[],struct town* L){//return pointer to a town we are searching for
struct town* p;
p=L;//let p point to the first town in the list passed to the function
while(p!=NULL&&strcasecmp(p->data,x)!=0)//strcasecmp() function is used for comparing strings
    p=p->next;
return p;//return pointer to the town we looked for by name
}
struct town* findLastTown(struct town*L){//used when inserting towns
struct town *p;
p=L->next;//
while(!isLastTown(p,L)){
    p=p->next;//here we find the last town by checking if its next pointer points to null
}
return p;
}
int isEmpty(struct district*L){
return L->next==NULL; //return 1 if list is empty
}
int isEmptyTown(struct town*L){
return L==NULL; //return 1 if list is empty
}
int isLast(struct district*P,struct district*L){
return P->next==NULL;//return 1 if the district we are looking for the last one
}
int isLastTown(struct town*P,struct town*L){
return P->next==NULL;//return 1 if the town we are looking for the last one
}

void LoadFile(struct district* L){
FILE* in;//initialize pointer to the file
in = fopen("districts.txt","r"); // select the file to open, and scan it later
if(in==NULL){
    printf("Error in opening the file!\n");
    exit(0); //if file don't have data print error message and exit the function
}
char inputString[51];//define an array to store input string from file including the null charachter
char DistrictName[21],TownName[21];//define an array to store the name of distict ,population
int population;
struct district *D;
struct town* T;
struct town* TList;
while(fgets(inputString,sizeof(inputString),in)){//loop to read the file line by line
    if(strlen(inputString)>51){//if the size of a line in the file is greater than the maximum (50) exit program
        printf("Error\n");
        exit(0);
    }
    char *tok=strtok(inputString,"|");
    strcpy(DistrictName,tok);//assign district name to equal value stored in tok after splitting
    tok=strtok(NULL,"|");//
    strcpy(TownName,tok);//assign town name to equal value stored in tok after splitting
    tok=strtok(NULL,"\n");
    population=atoi(tok);//function atoi() converts strings into integers //assign population to equal value stored in tok after splitting and converting into integers
    D=findDistrict(DistrictName,L);//check if the district is already added to the linked list

    if (D == NULL) {  //if district in not found insert it
            insertDistrict(DistrictName,L);//insert district after the last added district in the list
            D=findDistrict(DistrictName,L);//return a pointer the last district added
            D->PtrToList=NULL;//let the town list for the district be initially NULL(empty)
            T=D->PtrToList;
        }

        if(T==NULL){//if the list has no town create the head of the town which will be the first town added
            T=makeEmptyTown(TownName,population,T);
            TList=T;//had to define Tlist to maintain a pointer to the first town in the list
        }
        else insertTown(TownName,population,T);//if the list already has town add town to the last town added
        D->PtrToList=TList;// updating town list for each district
    }
printf("File is loaded in success\n");
fclose(in);//close the file
}

void PrintInputData(struct district* L){
FILE* in;//initialize pointer to the file
in = fopen("districts.txt","r"); // select the file to open, and scan it later
if(in==NULL){
    printf("Error in opening the file!\n");
    exit(0); //if file don't have data print error message and exit the function
}
char inputString[51];//define an array to store input string from file including the null charachter
while(fgets(inputString,sizeof(inputString),in)){
    printf("%s\n",inputString);
}
}

int getMaxLengthDistrict(struct district* L){
struct district* p=L->next;//temp pointer to not lose head node
int max=strlen(p->data);
while(!isLast(p,L)){
    p=p->next;
    if(strlen(p->data)>max)
        max=strlen(p->data);
}
return max;
}

void SortDistricts(struct district* L){
struct district* temp;//pointer to the district in district list
struct district * PinL,*LastAdded;
struct district * NewList;//store districts after every round has only the head
char currentCharacter;//used for comparing a specific character in the radix sort
if(isEmpty(L))
    LoadFile(L);
int i,j,z,x=getMaxLengthDistrict(L),index;
AddSpaces(L);//this makes the districts of the same length making it easier to use radix sort
struct district* RadixSortArray[53];//size 63 is for spaces (0) ,numbers(1-10),upper case letters(1-26),lower case letters(27-52)
temp=L->next;
for(i=x-1;i>=0;i--){//outer loop O(the maximum district length)
//starts from the last index in the array where the district name is stored from LS character to the MS character
for(j=0;j<53;j++){
    RadixSortArray[j]=makeEmpty(NULL);
}
while(temp!=NULL){
    currentCharacter=temp->data[i];//take a specific character to compare based on it
    if(i==0){
        currentCharacter=toupper(currentCharacter);// convert char[0] to upper case easier to deal with
        temp->data[i]=currentCharacter;
    }
    else {
            currentCharacter=tolower(currentCharacter);//convert other letters to lower case better when sorting
            temp->data[i]=currentCharacter;
    }
    if(currentCharacter==' '){// index 0 is for space charachters
        index=0;
    }
    else if(currentCharacter>='A'&&currentCharacter<='Z'){//index 1-26 used to store uppercase Letters ,here we compare characters based on their ascii value
        index=currentCharacter-'A'+1;
    }
    else if(currentCharacter>='a'&&currentCharacter<='z'){//index 27-52 used to store lowercase letters ,here we compare characters based on their ascii value
        index=currentCharacter-'a'+27;
    }
    insertDistrict(temp->data,RadixSortArray[index]);
    //next of RadixSortArray[index] will be temp->data
    temp=temp->next;//update the pointer to point to the next district in the list
}

NewList=makeEmpty(NULL);
for(z=0;z<53;z++){
    temp=RadixSortArray[z]->next;
    while(temp!=NULL){
    insertDistrict(temp->data,NewList);
    LastAdded=findDistrict(temp->data,NewList);
    PinL=findDistrict(temp->data,L);
    LastAdded->PtrToList=PinL->PtrToList;
    temp=temp->next;
    }
}
temp=NewList->next;
}
deleteListD(L);
L->next=NewList->next;//// Update L to point to the new sorted list
Removespaces(L);
for(i=0;i<53;i++){
    RadixSortArray[i]->next=NULL;
}
}

void SortTowns(struct district *L){//using radix sort
if(isEmpty(L))
    LoadFile(L);
struct district * p=L->next;
struct town *P,*temp,*G;
int MaxPop,i,x,j,pop,index,divisor,z,k,MaxDigit,m=0;
struct town * RadixSortArray[10];
while(p!=NULL){
P=p->PtrToList;//P points to the first town in the town list of a district
temp=P;// temp pointer to town list
MaxPop=getMaxNumber(P);//get maximum population digit
MaxDigit=MaxPop-1;
x=pow(10,MaxDigit);
for(i=x;i>0;m++){
for(j=0;j<10;j++){
RadixSortArray[j]=makeEmptyTownHead(NULL);//let every element in the array point to a struct district future
}
while(temp!=NULL){
pop=temp->population;//assign the population of town to pop
k=NumberOfDigits(pop);
divisor=pow(10,m);
pop=pop/divisor;
index=pop;
pop=temp->population;
insertTown(temp->data,temp->population,RadixSortArray[index]);
temp=temp->next;
}
G=NULL;//define head of the town list
for(j=0;j<10;j++){
temp=RadixSortArray[j]->next;
while(temp!=NULL){
if(G==NULL){
G=makeEmptyTown(temp->data,temp->population,G);
}
else {
insertTown(temp->data,temp->population,G);
}
temp=temp->next;
}
}
i=i/10;
MaxDigit--;
temp=G;
}
for(i=0;i<10;i++){
RadixSortArray[i]->next=NULL;
}
p->PtrToList=G;
p=p->next;
}
}

int getMaxNumber(struct town*L){
struct town*temp=L;
int pop,MaxNumber=0,count;
while(temp!=NULL){
pop=temp->population;
if(pop>MaxNumber){
    MaxNumber=pop;
}
temp=temp->next;
}
count=NumberOfDigits(MaxNumber);
return count;
}

int NumberOfDigits(int n){//get number of digits for each number //used in radix sort
int count=0;
while(n>0){
    n=n/10;
    count++;
}
return count;
}

void PrintTheSortedInformation(struct district*L){
if(isEmpty(L)){
     LoadFile(L);
}
struct district*p;
struct town* temp;
SortDistricts(L) ;
SortTowns(L);
p=L->next;
while(p!=NULL){

    temp=p->PtrToList;
    p->totalPopulation=calculateDistrictPopulation(temp);
    printf("%s District, Population=%d\n",p->data,p->totalPopulation);
    while(temp!=NULL){
        printf("%s,%d\n",temp->data,temp->population);
        temp=temp->next;
    }
    p=p->next;
}
printf("\n");
}

void insertDistrict(char x[],struct district*L){
struct district *temp,*p;
temp=(struct district*)malloc(sizeof(struct district));
if(temp!=NULL){
    strcpy(temp->data,x);
    if(L->next!=NULL){
    p=findLastDistrict(L);
    }
    else p=L;
    }
    temp->next=p->next;
    temp->previous=p;
    p->next=temp;
}

void insertDistrictAndSort(struct district*L){
if(isEmpty(L)){
  LoadFile(L);
  }
struct district*p;
char district[50];
printf("please enter the name of the district to be added!\n");
gets(district);
p=findDistrict(district,L);
if(p!=NULL){
    printf("district is already in the list!\n");
}
else{
p=L;
insertDistrict(district,p);//insert district after the last district added in list p
p=findDistrict(district,L);//pointer to the district just added we need it to let pointer to town list point to null
p->PtrToList=NULL;// the district just added has no towns in the town list
SortDistricts(L);
printf("Insertion is successful!\n");
}
}

void insertTown(char x[],int pop,struct town*L){//insert town last or after position p used primarily in load but called in insert new town
struct town *temp,*p;
temp= (struct town*)malloc(sizeof(struct town));//locate a place in memory for a to be town
if(temp!=NULL){
strcpy(temp->data,x);
temp->population=pop;
if(L->next!=NULL){//the list has more than two towns we will add after the last one
   p=findLastTown(L);//find last town added to town list and add after it
}
else {//there is only one town in the list which is the head of the list we will add after it
        p=L;
}
temp->next=p->next;
temp->previous=p;
p->next=temp;
}
else printf("Out of memory\n");
}

void insertNewTown(struct district*L){
if(isEmpty(L))
    LoadFile(L);
struct district* p;//pointer to district
struct town* temp,*temp1;
char town[50],district[50];
int pop;
printf("Please Enter the district where to add the town\n");
gets(district);
p=findDistrict(district,L);
if(p==NULL){
    printf("district is not found please try again!\n");
}
else {
    printf("Please Enter the town to be added\n");
    gets(town);
    temp=p->PtrToList;//temp points to the first town in the town list
    if(temp!=NULL){
    temp1=findTown(town,temp);
    if(temp1==NULL){
        printf("please enter the population of the town!\n");
        scanf("%d",&pop);
        insertTown(town,pop,temp);
        }
    else printf("the town is already in the list!\n");
    }
    else{
        // create town list for a district
                temp=makeEmptyTown(town,pop,temp);
                p->PtrToList=temp;
    }
    printf("insertion is successful!\n");
}
}

void CalculatePopulationMaxAndMin(struct district*L){// function 11
    if(isEmpty(L)){
    LoadFile(L);}
    struct district* p=L->next;//pointer to a distrcit
    struct town* temp,*temp1,*temp2;
    int TownPopulation,sum=0,MaxPopulation=0,MinPopulation=INT_MAX;//set Max population to the smallest population value and Min population to the highest population value
    while (p!=NULL){
      sum+=  calculateDistrictPopulation(p->PtrToList);
      p=p->next;
    }
    p=L->next;
    while(p!=NULL){
    temp=p->PtrToList;
    p=p->next; //update district
    while(temp!=NULL){
    TownPopulation=temp->population;
     if(TownPopulation>  MaxPopulation){
      MaxPopulation=TownPopulation;//find max population
      temp1=temp;
     }
     if(TownPopulation< MinPopulation){
      MinPopulation=TownPopulation;//find min population
      temp2=temp;
     }
     temp=temp->next;//update town
    }
}
printf("the population of Palestine =%d\t Town %s has Max population=%d\t Town %s has Min population=%d\n",sum,temp1->data,MaxPopulation,temp2->data,MinPopulation);
}

int calculateDistrictPopulation(struct town*L){//find the total population of a district
struct town*p=L;//let L point to the first town in the town list
int sum=0;//set initial district population to equal 0
while(p!=NULL){
    sum+=p->population;//add populations together
    p=p->next;//point to next town until visiting all towns
}
return sum;// return the total population of the district
}

void deleteTown(struct district* L){
if(isEmpty(L))
    LoadFile(L);//if list is empty load file
struct district* p;
struct town* temp,*temp1,*temp2;
char town[51],district[51];
printf("Enter district Name\n");
gets(district);
p=findDistrict(district,L);
if(p!=NULL){
    printf("Enter town name\n");
    gets(town);
    temp=p->PtrToList;
    if(temp!=NULL){
    temp1=findTown(town,temp);//temp 1 points to the town we need to delete
    if(temp1!=NULL){

        if(temp1->next==NULL&&temp1->previous==NULL){//delete only town in the list
            temp=temp->next;
            p->PtrToList=temp;//update district to have no towns in the list
            free(temp1);//free memory
        }
        else if(temp1->next!=NULL&&temp1->previous==NULL){//delete first town from the list
         temp=temp->next;
         p->PtrToList=temp;
         temp->previous=NULL;
         free(temp1);//free memory
        }
        else if(temp1->next!=NULL&&temp1->previous!=NULL){//delete town in the middle
         temp2=temp1->previous;
         temp=temp1->next;
         temp2->next=temp1->next;
         temp->previous=temp1->previous;
         free(temp1);//free memory
        }
        else if(temp1->next==NULL&&temp1->previous!=NULL){//delete last town
            temp=temp1->previous;
            temp->next=temp1->next;
            free(temp1);//free memory
        }
    }

    }
    else printf("The town has no lists\n");
    }
else printf("District is not Found!\n");
}

void deleteDistrict(struct district* L){
if(isEmpty(L)){
    LoadFile(L);
}
struct town* temp;
struct district  *p,*p1,*p2;
char district[50];
printf("enter district name\n");
gets(district);
p=findDistrict(district,L);
p1=L;
if(p!=NULL){
temp=p->PtrToList;
deleteListT(temp);//deleting town list
p->PtrToList=NULL;//updating town list to point to NULL
if(p->next==NULL){//check if the district we are deleting is the last one
    p1=p->previous;
    p1->next=p->next;
    free(p);
}
else if(p->next!=NULL){
p2=p->next;
if(p1->next==p){
p1->next=p2;
p2->previous=p1;
free(p);
}
else{
p1=p->previous;
p1->next=p2;
if(p2!=NULL){
  p2->previous=p1;
}
free(p);
}
}
}
else printf("district to be deleted is not in the list!\n");
}

void printDistricts(struct district* L){
struct district* p=L;
struct town* temp;
if(isEmpty(L)){
   printf("EmptyList\n");
}
else {do{
    p=p->next;
    temp=p->PtrToList;
    p->totalPopulation=calculateDistrictPopulation(temp);
    printf("%s, Population =%d\n",p->data,p->totalPopulation);
}while(!isLast(p,L));
}
printf("\n");
}

void changePopulation(struct district*L){
if(isEmpty(L))
    LoadFile(L);//if list is empty load file
int Population;
char district[50],town[50];//initialize string that will be used to store district and town name
struct district* temp1;
struct town* temp2;
printf("Enter district name\n");
gets(district);//store district name scanned from the user//gets is better when dealing with a string with spaces within
printf("Enter town be change it's population\n");
gets(town);//store town name scanned from the user
printf("Enter new population size\n");
scanf("%d",&Population);//store population scanned from the user
getchar();
temp1=findDistrict(district,L);
if(temp1!=NULL){
    temp2=temp1->PtrToList;//temp 2 points to the town list of the district temp1
    temp2=findTown(town,temp2);//temp 2 points to the town
    if(temp2!=NULL)
        temp2->population=Population;//update town population
}
}

void saveToOutputFile(struct district *L){
 FILE* out ;//pointer to the file
 struct district* p;
 struct town* temp;
 out= fopen("sorted_districts.txt","w");//open sorted districts file for writing mode
if (out == NULL)
{
printf("Error in opening the file for writing!\n");
exit(0);
}
if(isEmpty(L)){
    LoadFile(L);
    SortDistricts(L);
}
p=L->next;//point to the first district in the linked list
while(p!=NULL){

    temp=p->PtrToList;//temp point tot the town list
    p->totalPopulation=calculateDistrictPopulation(temp);//find the total population of each district
    fprintf(out,"%s, Population=%d\n",p->data,p->totalPopulation);
    while(temp!=NULL){
        fprintf(out,"%s,%d\n",temp->data,temp->population);
        temp=temp->next;//update town to point to another town
    }
    p=p->next;//update district pointer to point to the next district
}
printf("File Saved Successfully\n");
fclose(out);//close the file
}

void AddSpaces(struct district*L){//we use this function to make the districts to be sorted of the same length
    struct district *temp=L->next;//pointer to the first district in the LL
    int MaxLength=getMaxLengthDistrict(L);//find length of the maximum district
    int LengthOfDistrict,NumOfSpacesToAdd,i;
    while(temp!=NULL){// O(NumofSpacesToAdd*n)
        LengthOfDistrict=strlen(temp->data);//find length of the district
        NumOfSpacesToAdd=MaxLength-LengthOfDistrict;
        for(i=0;i<NumOfSpacesToAdd;i++){//add spaces to district
            strcat(temp->data," ");
        }
        temp=temp->next;//let temp point to the next district
    }
}

void Removespaces(struct district*L){
struct district *temp=L->next;//pointer to the first district in the LL
int NumOfSpaces=0,LengthOfDistrict,i;
while(temp!=NULL){
       LengthOfDistrict=strlen(temp->data);//find the number of letters in each district
       for(i=0;i<LengthOfDistrict;i++){//checks every single character in the string
        if(temp->data[i]==' '){
           NumOfSpaces++;//every time finds space character increment number of spaces by 0
        }

       }
       temp->data[LengthOfDistrict-NumOfSpaces]='\0';//puts null when finds the first space
       temp=temp->next;//let temp point to the next district
       NumOfSpaces=0;//reset number of spaces when pointing to another district
    }

}

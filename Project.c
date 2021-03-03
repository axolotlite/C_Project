#include <stdio.h>
#define fork(x,y) for(int k=x;k<y;k++)
#define forj(x,y) for(int j=x;j<y;j++)
int size = 0;
int Array[100];
FILE *file;
//--Structs--
typedef struct{
	char Str[100];
	int Len;
	int Size;
}STRING;
typedef struct{
	int Day;
	int Month;
	int Year;
	int Size;
}DATE;
typedef struct{
	int ID;
	STRING Name;
	STRING Victim;
	DATE Time;
	STRING Location;
	STRING Detective;
	STRING Evidence;
	STRING Suspect;
}CASE;
CASE Zero ={0,{"Doesn't Exist",0,0},{"Doesn't Exist",0,0},{0,0,0},{"Doesn't Exist",0,0},{"Doesn't Exist",0,0},{"Doesn't Exist",0,0},{"Doesn't Exist",0,0}};
//--funcions--
int atoi(char* str){ //instead of using an entire lib to get it.
	int num=0;
	for(int i=0;str[i] != '\0' && str[i] != '\n'; i++)num = num*10 + str[i] - '0' ;
	return num; 
}
int scanInt(char* print){ //an alternative to scanf to prevent newline from glitching fgets.
	char num[10];
	printf("%s",print);
	fgets(num,10,stdin);
	int n = atoi(num);
	return n;
}

STRING getStr(char* print){
	STRING str;
	int i=0,sum=0;
	printf("%s",print);
	fgets(str.Str,100,stdin);
	for(;str.Str[i] != '\n';i++)sum += str.Str[i];
	str.Str[i] = '\0';
	str.Len = i+1;
	str.Size = sum;
	return str;
}
DATE getDate(char* print){
	DATE date;
	printf("%s",print);
	date.Day = scanInt("Day number: ");
	date.Month = scanInt("Month number: ");
	date.Year = scanInt("Year: ");
	date.Size = date.Day + date.Month + date.Year;
	return date;
}
void switchCase(CASE* data1, CASE* data2){
	CASE temp = *data1;
	*data1 = *data2;
	*data2 = temp;
}
void switchStr(STRING* from, STRING* to){
	STRING tmp = {};
	tmp = *from;
	*from = *to;
	*to = tmp;
}
void switchInt(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
//--Assignment(1)--

void fillArray(int array[]){
	fork(0,size)array[k]=scanInt("Elem: ");
}

void bubbleSort(int array[]){
	int tmp;
	fork(0,size-1)
		forj(0,size-k-1)
			if(array[j]>array[j+1])
				switchInt(&array[j],&array[j+1]);
}

int binarySearch(int array[], int num){
	int low = 0, high = size-1, mid;
	while(low <= high){
		mid = (low+high)/2;
		if(num > array[mid])low = mid+1;
		else if(num < array[mid])high = mid-1;
		else return mid;
	}
	return 0;
}
//--Assignment(2)--

void fillStrings(STRING str[]){
	fork(0,size)str[k]=getStr(">>>");
}
void sortStrings(STRING str[]){
	fork(0,size)
		forj(0,size-k)
			if(str[j].Size>str[j+1].Size)switchStr(&str[j],&str[j+1]);
}
void searchStr(STRING str[],STRING word){
	int array[100];
	fork(0,size)array[k] = str[k].Size;
	bubbleSort(array);
	int num = binarySearch(array,word.Size);
	switch(num){
		case -1:printf("String not found.\nPlease try again.");
		default:printf("String Found.");
	}
}
//--Assignment(3)--
void printCase(CASE data){
	printf("----------------\n");
	printf("ID:%d\n",data.ID);
	printf("Name:%s.\n",data.Name.Str);
	printf("Victim:%s.\n",data.Victim.Str);
	printf("Time:%d/%d/%d.\n",data.Time.Month,data.Time.Day,data.Time.Year);
	printf("Location:%s.\n",data.Location.Str);
	printf("Detective:%s.\n",data.Detective.Str);
	printf("Evidence:%s.\n",data.Evidence.Str);
	printf("Suspect:%s.\n",data.Suspect.Str);
	printf("----End case----\n");
}
void caseSort(int mode, CASE data[]){
	switch(mode){
		case 1:fork(0,size)Array[k] = data[k].ID;break;
		case 2:fork(0,size)Array[k] = data[k].Name.Size;break;
		case 3:fork(0,size)Array[k] = data[k].Victim.Size;break;
		case 4:fork(0,size)Array[k] = data[k].Time.Size;break;
		case 5:fork(0,size)Array[k] = data[k].Location.Size;break;
		case 6:fork(0,size)Array[k] = data[k].Detective.Size;break;
		case 7:fork(0,size)Array[k] = data[k].Evidence.Size;break;
		case 8:fork(0,size)Array[k] = data[k].Suspect.Size;break;
		default:printf("Invalid input.\nSorting by ID");caseSort(1,data);
	}
	fork(1,size)
		forj(0,size-k)
			if(Array[j]>Array[j+1]){
				switchInt(&Array[j],&Array[j+1]);
				switchCase(&data[j],&data[j+1]);
			}
}
int caseSearch(int mode,int size){
	switch(mode){
		case 1:return(binarySearch(Array,size)); //searches for ID
		case 4:return(binarySearch(Array,size)); //searches for date
		default:return(binarySearch(Array,size));//searches for any string
	}
}
int modCase(CASE* data){
	printCase(*data);
	switch(getStr("I)D\nN)ame\nV)ictim\nT)ime\nL)ocation\nD)etective\nE)vidence\nS)uspect\nQ)uit.\nModify: ").Str[0]){
		case 'i':
		case 'I':data->ID = scanInt("New case ID: ");modCase(data);break;
		case 'n':
		case 'N':data->Name = getStr("New name: ");modCase(data);break;
		case 'v':
		case 'V':data->Victim = getStr("New Victim: ");modCase(data);break;
		case 't':
		case 'T':data->Time = getDate("New Date:\n");modCase(data);break;
		case 'l':
		case 'L':data->Location = getStr("New Location: ");modCase(data);break;
		case 'd':
		case 'D':data->Detective = getStr("New Detective: ");modCase(data);break;
		case 'e':
		case 'E':data->Evidence = getStr("New Evidence: ");modCase(data);break;
		case 's':
		case 'S':data->Suspect = getStr("New Suspect: ");modCase(data);break;
		case 'q':
		case 'Q':return(0);
	}
}
//--Assignment(4)--
void getCase(CASE *data){
	data->ID = scanInt("Case ID: ");
	data->Name = getStr("Case Name: ");
	data->Victim = getStr("Victim Name: ");
	data->Time = getDate("Day of crime occurunce, DD/MM/YY:\n");
	data->Location = getStr("City where the crime occured: ");
	data->Detective = getStr("Detective assigned: ");
	data->Evidence = getStr("Conclusive evidence: ");
	data->Suspect = getStr("Main suspect: ");
	printCase(*data);
}
int main(){
	int flag = 1,num;
	CASE cases[100];
	STRING Name;
	printf("Opening Database...\n");
	file = fopen("Case_Database.bin","rb");
	fread(&size,sizeof(int),1,file);
	fread(&cases,sizeof(CASE),size,file);
	printf("Database loaded into RAM.\n");
	fclose(file);
	caseSort(1,cases);
	printf("---Crime Database Interface---\n");
	while(flag)switch(getStr(">>>").Str[0]){
			case 'a':
			case 'A':printf("adding a new case.\n");getCase(&cases[size++]);break;
			case 'c':
			case 'C':printf("Nobody will help you now.");break;
			case 'd':
			case 'D':
				num = caseSearch(1,scanInt("Delete(ID)>>"));
				if(num && size--)fork(num,size)switchCase(&cases[k],&cases[k+1]);
				break;
			case 'f':
			case 'F':
				num = scanInt("Available search queries:\n1)Case ID\n2)Case Name\n3)Victim Name\n4)Crime date\n5)Location\n6)Detective\n7)Evidence\n8)Suspect\nWhat are you searching for?\nFind>>");
				caseSort(Array[num-1],cases);
				switch(num){
					case 1:printCase(cases[caseSearch(num,scanInt("Number>>"))]);break;
					case 4:printCase(cases[caseSearch(num,getDate("Date>>\n").Size)]);break;
					case 6:
						Name = getStr("Detective>>:");
						fork(0,size)if(Array[k] == Name.Size)printCase(cases[k]);break;
					default:printCase(cases[caseSearch(num,getStr("String>>").Size)]);
				}
				break;
			case 'h':
			case 'H':printf( "This is the help menu.\nAvailable inputs:\n"
		"A)dd a case.\nD)elete a case.\nF)ind case.\nH)elp.\nM)odify case.\nP)rint case.\nQ)uit program.\n");break;
			case 'm':
			case 'M':
				num = scanInt("Enter ID of case you want to modify, '0' to quit: ");
				if(num)modCase(&cases[num]);
				break;
			case 'p':
			case 'P':
				num = scanInt("Enter '0' to print all IDs & Names, otherwise if you want a certain case.\nEnter ID:");
				switch(num){
					case 0:fork(1,size)printf("%d:%s\n",cases[k].ID,cases[k].Name);break;
					default:printCase(cases[caseSearch(1,num)]);
				}
				break;
			case 'q':
			case 'Q':
				if(scanInt("Write to file?\n1)Yes\n/0)No.\nwrite>> ")){
					file = fopen("Case_Database.bin","wb");
					fwrite(&size,sizeof(int),1,file);
					fwrite(&cases,sizeof(CASE),size,file);
					fclose(file);
				}
				--flag;
				printf("Exiting...\n");
				break;
			default:printf("Invalid input.\nPlease enter (h) for help.\n");
		}
}

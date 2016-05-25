#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

	

int main(int argc, char *argv[]) {
	
	int i,j;
	
	//Table Parser
	typedef char String[10];
	String tblParsing[10][5] =  {	//c     d     $   <S>  <C>
									{"s3", "s4", "e", "1", "2" }, 	//i0
									{"-", "-", "ACC", "-", "-" },	//i1
									{"s6", "s7", "-", "-", "5" },	//i2
									{"s3", "s4", "-", "-", "8" },	//i3
									{"r3", "r3", "-", "-", "-" },	//i4
									{"-", "-", "r1", "-", "-" },	//i5
									{"s6", "s7", "-", "-", "9" },	//i6
									{"-", "-", "r3", "-", "-" },	//i7
									{"r3", "r2", "-", "-", "-" },	//i8
									{"-", "-", "r2", "-", "-" }		//i9
								};
	
	int x,y;
	
	//Rule 
	static const char *r[] = {"<S>::=<C><C>","<C>::=c<C>","<C>::=d"};
	char r_temp[20]={};
	char r_head[5]={};
	char r_body[20]={};
	int rule;
	
	//Input String
	//char input_s[] = {"cdd"};
	char *input_s[] = {"cccd","Orange","Yellow","Green","Blue","Purple" };
	
	//Var Penurunan
	char p_stack[] = {""};
	char p_string[] = {""};
	char p_action[] = {""};
	
	char pc_stack[20]={};
	char pc_string[20]={};
	char pc_action[20]={};
	
	char pt_stack[20]={};
	char pt_string[20]={};
	char pt_action[20]={};
	
	//Var Temp
	char temp_string[20] ={};
	char temp_string1[1] ={};
	char temp_char;
	int temp_int;
	char temp_rule[10]={};
	
	//var bebas
	
	//Tampil Table Parser
	printf ("\nTABEL PARSER \n" );
	printf("    c   d   $ <S> <C>\n"  );
	for(i=0;i<10;++i){ 
		printf("i%d ", i);  
    	for(j=0;j<5;++j){
    		printf(" ");
			printf(tblParsing[i][j]);
			printf(" ");
		}
		printf("\n");
	}
	
	//Tampil Rule
	printf("\nRule: \n");
	printf("Rule 1 : %s\nRule 2 : %s\nRule 3 : %s\n",r[0],r[1],r[2]);
	
	//Tampil Input
	printf("\nSilahkan Input String (ex: cdd) : ");
	char input[] = {"s"};
	scanf ("%[^\n]%*c", input);
	printf("%s", input);
	//strcpy(input_s[0], name);
	
	//Tampil Input String
	printf("\nInput String: %s\n", input);
	
	//Penurunan
	printf("\nTahap-Tahap Penurunan: \n");
	
	printf("|Tahap|Stack|String|Action|\n"); //header
	
	//Proses Tahap 1
	
	strcpy(pc_stack, "0");
	strcpy(pc_string, input);
	strcat(pc_string, "$");
	
	//cek string paling kiri
	if (pc_string[0] == 'c'){
		y = 0;
	} else if (pc_string[0] == 'd'){
		y = 1;
	} else if (pc_string[0] == '$'){
		y = 2;
	} else {
		
		printf("\n\n\n-----------------\n|HASIL : DITOLAK|\n-----------------\n");
		
		goto selesai;
	}
	
	//cek stack paling kanan
	temp_int = strlen(pc_stack); //printf("bentar ini %i",temp_int);
	if (isalnum(pc_stack[temp_int-1])){
		x = pc_stack[temp_int-1]-'0'; 
	} else if ((pc_stack[temp_int-1]=='>') && (pc_stack[temp_int-2]=='C') && (pc_stack[temp_int-3]=='<')){
		y = 4;
		if (isalnum(pc_stack[temp_int-4])){
			x = pc_stack[temp_int-4]-'0';
		}
		strcat(pc_stack, tblParsing[x][y]); //printf(p_stack);  printf("|\n");
		
	}
	strcpy(pc_action, tblParsing[x][y]); //printf(tblParsing[x][y]);
	//Tampil Tahap 1
	printf("|  1  | %s | %s | %s |\n", pc_stack, pc_string, pc_action);
	
	int z=1;
	
	
	for (;;){
		z++;
		//Tahap 8 proses
		strcpy(r_temp, " ");
		strcpy(r_head, " ");
		strcpy(r_body, " ");
		
		//baca kondisi action
		if (pc_action[0]=='r'){
			//baca rule ke berapa
			if (isalnum(pc_action[1])){
				temp_int = pc_action[1]-'0'; 
				strcpy(r_temp,r[temp_int-1]);
				//printf("rule ke %i: %s \n",temp_int,r_temp);
				rule=temp_int;
				temp_int = strlen(r_temp);
				for (i=0;i<3;i++){
					temp_string[i] = r_temp[i];
					//printf(" %c ",temp_string[i]);
				}
				temp_string[i]='\0';
				strcpy(r_head, temp_string);
				strcpy(temp_string, " ");
				//printf("\n");
				for (i=6;i<temp_int;i++){
					temp_string[i-6] = r_temp[i];
					//printf(" %c ",temp_string[i-6]);
				}
				//printf("\n");
				strcpy(r_body, temp_string);
				temp_int = strlen(r_body);
				//printf("banyak isi %i yaitu %s\n",temp_int, r_body);
				
				j = strlen(pc_stack);
				//printf("banyak isi %i yaitu %s\n",j, pc_stack);
				j-=temp_int;
				if (rule == 1){
					j--;
					j--;
				} else if (rule == 2){
					j--;
					j--;
				} else {
					j--;
				}
				
				//printf("banyak isi %i yaitu %s\n",j, pc_stack);
				
				//netralisasi
				strcpy(temp_string, " ");
				strcpy(pt_stack, " ");
				
				
				//printf("_ %s\n", temp_string);
				for(i=0; i<j; i++){
					temp_string[i]=pc_stack[i];
					//printf("0 %s\n", temp_string);
				}
					
				//printf("1 %s\n", pt_stack);
				strcpy(pt_stack, temp_string);
				//printf("2 %s\n", pt_stack);
				strcat(pt_stack, r_head);
				//printf("3 %s\n", pt_stack);
				strcpy(pc_stack, " ");
				//printf("4 %s\n", pc_stack);
				
				strcpy(pc_stack, pt_stack);
				//printf("\ndebug: %s\n", pc_stack);
				
			}
			//strcpy(pc_stack, "pause");
			
		} else {
			//memindahkan string ke stack
			strcpy(temp_string1, " ");
		//	printf("stack %s\n", pc_stack);
			temp_string1[0] = pc_string[0]; 
			strcat(pc_stack, temp_string1);
			
			//printf("string %s\n", temp_string1);
			
		
			temp_int = strlen(pc_string);
			for (i=0; i<temp_int; i++){
				pc_string[i]=pc_string[i+1];
			}
		
			temp_int = strlen(pc_action);
			temp_string1[0]=pc_action[temp_int-1]; 
			strcat(pc_stack, temp_string1);
			
			//printf("\ndebug: %s\n", pc_stack);
			
		}
		
		//cek stack paling kanan
		temp_int = strlen(pc_stack); 
		if ((pc_stack[temp_int-1]=='>') && (pc_stack[temp_int-2]=='C') && (pc_stack[temp_int-3]=='<')){
			y = 4;
			if (isalnum(pc_stack[temp_int-4])){
				x = pc_stack[temp_int-4]-'0';
			}
			//printf("\ndebug: %s\n", tblParsing[x][y]);
			strcat(pc_stack, tblParsing[x][y]); 
		} else if ((pc_stack[temp_int-1]=='>') && (pc_stack[temp_int-2]=='S') && (pc_stack[temp_int-3]=='<')){
			y = 3;
			if (isalnum(pc_stack[temp_int-4])){
				x = pc_stack[temp_int-4]-'0';
			}
			strcat(pc_stack, tblParsing[x][y])	;
			
		}
		//cek string paling kiri
		if (pc_string[0] == 'c'){
			y = 0;
		} else if (pc_string[0] == 'd'){
			y = 1;
		} else if (pc_string[0] == '$'){
			y = 2;
		} else {
			printf("gk ada");
		}
		//cek stack paling kanan
		temp_int = strlen(pc_stack); 
		if (isalnum(pc_stack[temp_int-1])){
			x = pc_stack[temp_int-1]-'0'; 
		}
		strcpy(pc_action, tblParsing[x][y]); 
		//printf("\ndebug: %s\n", tblParsing[x][y]);
	
		//Tampil Tahap 1
		printf("|  %i  | %s | %s | %s |\n",z, pc_stack, pc_string, pc_action);
	
		if (pc_action[0]=='A'){
			
			printf("\n\n\n------------------\n|HASIL : DITERIMA|\n------------------\n");
			
			break;
		} else if (pc_action[0]=='-'){
			printf("\n\n\n-----------------\n|HASIL : DITOLAK|\n-----------------\n");
			break;
		}
	}
	selesai:
	
	printf("\n");
	printf("   .\n");
	printf("  / \\\n");
	printf("  | |\n");
	printf("  |.|\n");
	printf("  |.|\n");
	printf("  |:|      __\n");
	printf(",_|:|_,   /  )\n");
	printf("  (Oo    / _I_\n");
	printf("   +\\ \\  || __|\n");
	printf("      \\ \\||___|\n");
	printf("       \\ /.:.\-\\\n");
	printf("       |.:. /-----\\\n");
	printf("       |___|::oOo::|\n");
	printf("       /   |:<_T_>:|\n");
	printf("      |_____\ ::: /\n");
	printf("       | |  \ \:/\n");
	printf("       | |   | |\n");
	printf("       \\ /   | \\___\n");
	printf("       / |   \\_____\\\n");
	printf("       `-'\n");
	printf("\n\nBuild with passion by:  \nIhsan Faturohman (10113483) \nZamaludin Abdulah (10113449)\n");
	system("pause");
	return 0;
}


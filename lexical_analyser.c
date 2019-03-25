#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int format_specifiers(char *str);
int in_built_fun(char *str);
int unary(char *str,char *var,char *op);
int compound_operator(char *str);
int header_files(char *str);
int preprocessor(char *str);
int relational_operator(char *str);
int keyword(char *str);
int constant(char *str);
int operator(char *str);

int main(int argc,char *argv[])
{
	int i = 0;
	int res;
	char temp[100],ch;
	char *var =(char *) malloc(40);
	char *op = (char *)malloc(40);
	if(var == NULL)
	{
		printf("ERROR:malloc fails\n");
		return 1;
	}
	if(op == NULL)
	{
		printf("ERROR:malloc fails\n");
		return 1;
	}
	if (argc < 2)
	{
		printf("ERROR:\n");
		return 1;
	}

	FILE *fptr = fopen(argv[1],"r");

	do
	{
		i = 0;
		while((ch = fgetc(fptr)) != EOF)
		{
			if((ch != ' ') && (ch != '(') && (ch != ')') && (ch != '{') && (ch != '}') && (ch != '[') && (ch != ']') && (ch != ';') && (ch != '\n') && (ch != '"') && (ch != '\\') && (ch != '\t') && (ch != ',') && (ch != 39))
			{
				temp[i++] = ch; 
			}
			else if((ch == '"') || (ch == 39))
			{
				asm("nop");
			}
			else if((ch == '\\'))
			{
				fgetc(fptr);
			}
			else
			{
				if((ch != ' ') && (ch != '\n') && (ch != '"') && (ch != '\t'))
				{
					printf("%c : This is special character\n",ch);
					printf("\n");
				}
				break;
			}
		}
		temp[i] = '\0';

//		printf("%s\n",temp);

		if(!(keyword(temp)) && (temp[0] != '\0'))
		{
			printf("%s : is a keyword\n",temp);
			printf("\n");
		}
		else if(!(constant(temp)) && (temp[0] != '\0'))
		{
			printf("%s : is a constant\n",temp);
			printf("\n");
		}
		else if(!(compound_operator(temp)) && (temp[0] != '\0'))
		{
			printf("%s : is a compound operator\n",temp);
			printf("\n");
		}
		else if(!(operator(temp)) && (temp[0] != '\0'))
		{
			printf("%s : is a operator\n",temp);
			printf("\n");
		}
		else if(!(relational_operator(temp)) && (temp[0] != '\0'))
		{
			printf("%s : is a relational operator\n",temp);
			printf("\n");
		}
		else if(!(preprocessor(temp)) && (temp[0] != '\0'))
		{
			printf("%s : is preprocessor\n",temp);
			printf("\n");
		}
		else if(!(format_specifiers(temp)) && (temp[0] != '\0'))
		{
			printf("%s : is format specifiers\n",temp);
			printf("\n");
		}
		else if(!(header_files(temp)) && (temp[0] != '\0'))
		{
			printf("%s : is header file\n",temp);
			printf("\n");
		}
		else if(!(in_built_fun(temp)) && (temp[0] != '\0'))
		{
			printf("%s : is in built function\n",temp);
			printf("\n");
		}
		else if(!(unary(temp,var,op)) && (op[0] != ' ') && (temp[0] != '\0'))
		{
			printf("%s : unary operator\n",op);
			printf("%s : variable\n",var);
			printf("\n");
		}
		else if(temp[0] != '\0')
		{
			if(ch == '(')
			{
				printf("%s : is a function\n",temp);
			}
			else
			{
			    printf("%s : is a variable\n",temp);
			}
			printf("\n");
		}
	}while(ch != EOF);
	free(var);
	var = NULL;
	free(op);
	op = NULL;

	return 0;
}


int keyword(char *str)
{
	int res,a;
	char key[32][20] = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};

	for(int i = 0;i < 32; i++)
	{
		res = strcmp(key[i],str);
		if(res == 0)
		{
			return 0;
		}
	}
	return 1;

}

int constant(char *str)
{
	char num[10] = {'0','1','2','3','4','5','6','7','8','9'};

	for(int i = 0;i < 10; i++)
	{

		if(num[i] == str[0])
		{
			return 0;
		}
	}
	return 1;
}

int operator(char *str)
{
	char oper[11][3] = {"+","-","/","%","*","=","|","&","^","!","?"};

	for(int i = 0;i < 11; i++)
	{
		if(!(strcmp(oper[i],str)))
		{
			return 0;
		}
	}
	return 1;

}

int relational_operator(char *str)
{
	int res;
	char oper[6][4] = {"<=",">=","==","<",">","!="};

	for(int i = 0;i < 6; i++)
	{
		res = strcmp(oper[i],str);
		if(res == 0)
		{
			return 0;
		}
	}
	return 1;

}


int preprocessor(char *str)
{
	int res;
	char oper[8][15] = {"#define","#include","#if","#else","#endif","#ifdef","#ifundef","#elif"};

	for(int i = 0;i < 8; i++)
	{
		res = strcmp(oper[i],str);
		if(res == 0)
		{
			return 0;
		}
	}
	return 1;
}


int header_files(char *str)
{
	int res;
	char oper[5][15] = {"<stdio.h>","<stdlib.h>","<string.h>","<ctype.h>","<stdarg.h>"};

	for(int i = 0;i < 5; i++)
	{
		res = strcmp(oper[i],str);
		if(res == 0)
		{
			return 0;
		}
	}
	return 1;
}

int in_built_fun(char *str)
{
	int res;
	char oper[2][15] = {"printf","scanf"};

	for(int i = 0;i < 5; i++)
	{
		res = strcmp(oper[i],str);
		if(res == 0)
		{
			return 0;
		}
	}
	return 1;
}

int compound_operator(char *str)
{
	int res;
	char oper[10][4] = {"+=","-=","*=","/=","%=","|=","&=","^=",">>=","<<="};

	for(int i = 0;i < 10; i++)
	{
		res = strcmp(oper[i],str);
		if(res == 0)
		{
			return 0;
		}
	}
	return 1;
}

int unary(char *str,char *var,char *op)
{
	char opr[6] = {'+','-','!','~','*','&'};
	int i = 0,j = 0,k;
	while(*str)
	{
		if((*str >= 97) && (*str <= 122) || (*str >= 48) && (*str <= 57))
		{
			var[i++] = *str;
		}
		else
		{
			for(k = 0; k < 6; k++)
		    {
				if(*str == opr[k])
			    {
					op[j++] = *str;
				}
			}
		}
		str++;
	}
	var[i] = '\0';
	op[j] = '\0';
	if(j > 0)
	{
		return 0;
	}
	return 1;
}

int format_specifiers(char *str)
{
	int res;
	char oper[8][6] = {"%d","%c","%ld","%u","%f","%LF","%lld","%s"};

	for(int i = 0;i < 8; i++)
	{
		res = strcmp(oper[i],str);
		if(res == 0)
		{
			return 0;
		}
	}
	return 1;

}

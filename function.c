// function.c

#include"header.h"

void comment_remove( char* file)
{
FILE * fp=fopen(file,"r+");
	char ch;
	while((ch=fgetc(fp))!=EOF)
	{
		if(ch=='/')
		{
			ch=fgetc(fp);
			if(ch=='/')
			{
				fseek(fp,-2,SEEK_CUR);
				while((ch=fgetc(fp))!='\n')
				{
					fseek(fp,-1,SEEK_CUR);
					fputc(' ',fp);
				}
			}
		}
	}
	rewind(fp);
	while((ch=fgetc(fp))!=EOF)
	{
		if(ch=='/')
		{
			ch=fgetc(fp);
			if(ch=='*')
			{
				fseek(fp,-2,SEEK_CUR);
				fputc(' ',fp);
				fputc(' ',fp);
				while((ch=fgetc(fp))!='*' && (ch=fgetc(fp))!='/')
				{
					fseek(fp,-2,SEEK_CUR);
					fputc(' ',fp);
				}
				fseek(fp,-2,SEEK_CUR);
				fputc(' ',fp);
				fputc(' ',fp);
				fputc(' ',fp);
			}
		}
	}
	fclose(fp);
}

void macro_substitute(char *file)
{
    char ch, def[20] = "#define", new[50], old[50];
    int i;
    FILE *fp = fopen(file, "r+");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    while ((ch = fgetc(fp)) != EOF) {
                           
        if (ch == '#') {
            i = 1;
            while (((ch = fgetc(fp)) != ' ') && (ch != EOF)) {
                if (ch != def[i]) {
                    break;
                }
                i++;
            }

                                                
            if (def[i] == '\0') {
                fseek(fp, -8, SEEK_CUR);

                                              
                for (i = 0; i < 7; i++) {
                    fputc(' ', fp);
                }

                                                  
                while (((ch = fgetc(fp)) == ' ') && (ch != EOF));
                if (ch != ' ') {
                    i = 0;
                    fseek(fp, -1, SEEK_CUR);
                    while (((ch = fgetc(fp)) != ' ') && (ch != EOF) && (ch != '\n')) {
                        new[i++] = ch;
                        fseek(fp, -1, SEEK_CUR);
                        fputc(' ', fp);
                    }
                    new[i] = '\0';
                }

                                                  
                while (((ch = fgetc(fp)) == ' ') && (ch != EOF));
                if (ch != ' ') {
                    i = 0;
                    fseek(fp, -1, SEEK_CUR);
                    while (((ch = fgetc(fp)) != ' ') && (ch != EOF) && (ch != '\n')) {
                        old[i++] = ch;
                        fseek(fp, -1, SEEK_CUR);
                        fputc(' ', fp);
                    }
                    old[i] = '\0';
                }

                                                           
            }
        }
    }
replace_word(file,new,old);

    fclose(fp);
    return;
}

void replace_word(char *file,  char *new, char *old)
{
	char s[100];
	char *p;
	FILE * fp=fopen(file,"r");
	FILE * te=fopen("temp","w");

	while((fgets(s,sizeof(s),fp))!=NULL)
	{
		p=strstr(s,old);
		while(p!=NULL)
		{
			fwrite(s,sizeof(char),p-s,te);
			fwrite(new,sizeof(char),strlen(new),te);
			strcpy(s,p+strlen(old));
			p=strstr(s,old);
		}
		fwrite(s,sizeof(char),strlen(s),te);
	}
	remove(file);
	rename("temp",file);
	fclose(fp);
	fclose(te);

}

void header_include(char* file)
{
	int i;
	char ch;
	char inc[20]="#include",addr[50]="/usr/include/",head[20];
	FILE* fp=fopen(file,"r+");

	while((ch=fgetc(fp))!=EOF)
	{
		if(ch=='#')
		{
			fseek(fp,-1,SEEK_CUR);
			i=0;
			while((ch=fgetc(fp))!='<' && ch!=EOF)
			{
				if(ch!=inc[i])
					break;
				i++;
			}
			if(inc[i]=='\0')
			{
				fseek(fp,-9,SEEK_CUR);
				while((ch=fgetc(fp))!='<' && ch!=EOF)
				{
					fseek(fp,-1,SEEK_CUR);
					fputc(' ',fp);
				}
//#include removed
				fseek(fp,-1,SEEK_CUR);
				fputc(' ',fp);
// < removed
				i=0;
				while((ch=fgetc(fp))!='>' && ch!=EOF)
				{
				head[i]=ch;
				fseek(fp,-1,SEEK_CUR);
				fputc(' ',fp);
				i++;
				}
				head[i]='\0';
// header into string,
// header removed.
				fseek(fp,-1,SEEK_CUR);
				fputc(' ',fp);
// > removed
			}
		}
// if() of # ended

	}
// while of fp ended

	strcat(addr,head);
// path is in addr

	FILE* rp=fopen(addr,"r");
	FILE* qp=fopen("txt.txt","w");	
	while((ch=fgetc(rp))!=EOF)
	{
		fputc(ch,qp);
	}
// header file content copied into txt.txt

	fclose(rp);
	fclose(qp);
	rp=fopen(file,"r");	
	qp=fopen("txt.txt","a");	

	while((ch=fgetc(rp))!=EOF)
	{
		fputc(ch,qp);
	}
// data file content appended into txt.txt

	fclose(rp);
	fclose(qp);
	rp=fopen(file,"w");	
	qp=fopen("txt.txt","r");	
// txt.txt copied to data

	while((ch=fgetc(qp))!=EOF)
	{
		fputc(ch,rp);
	}
	fclose(rp);
	fclose(qp);

	fclose(fp);
}

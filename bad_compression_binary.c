#include <stdio.h>
#include <limits.h>


struct linkedlist{
    unsigned char repeat;
    char val;
    struct linkedlist *next;
};


struct linkedlist *addtolist(struct linkedlist *root, char c, unsigned char count)
{
    if(root == NULL)
    {
        root = (struct linkedlist*) malloc(sizeof(struct linkedlist));
        root->repeat = count;
        root->val = c;
        root->next = NULL;
    }
    else
    {
        root->next = addtolist(root->next, c, count);
    }
    return root;
}


struct linkedlist *strtolist(char *fname)
{

    long long _strlen;

    FILE *fp = fopen(fname,"rb");
    fseek(fp, 0L, SEEK_END);
    _strlen = ftell(fp);
    fseek (fp, 0, SEEK_SET);
    char *str = malloc(_strlen);
    fread(str,1,_strlen,fp);

    struct linkedlist *root = NULL;
    if (_strlen <= 1)
    {
        return NULL;
    }
    char c = *str;
    unsigned char count = 1;
    for (long long i = 1;i <_strlen;i++)
    {
        if (str[i] == c)
        {
            if (count == UCHAR_MAX)
            {
                root = addtolist(root, c, count);
                c = str[i];
                count = 0;
            }
            count++;
        }
        else
        {
            root = addtolist(root, c, count);
            c = str[i];
            count = 1;
        }
    }
    return root;
}


void print( struct linkedlist  *head) {

    struct linkedlist  *current_node = head;
   	while ( current_node != NULL) {
        for(int i = 0 ;i < current_node->repeat;i++)
        {
            putchar(current_node->val);
        }
        current_node = current_node->next;
    }
}

void save( struct linkedlist  *head,FILE *file) {
    struct linkedlist  *current_node = head;
    static int countme = 0;

   	while ( current_node != NULL)
    {
        fwrite(&current_node->repeat,sizeof(current_node->repeat),1,file);
        fwrite(&current_node->val,sizeof(current_node->val),1,file);
        countme+=2;
        current_node = current_node->next;
    }
}

void doit()
{
    FILE *output = fopen("output","wb");
    FILE *file = fopen("testmedad","rb");

    unsigned char repeat;
    char val;
    while(1){

        fread(&repeat,sizeof(repeat),1,file);
        fread(&val,sizeof(val),1,file);
        if (!feof(file))
        {
            for (int i = 0;i<repeat;i++)
            {
                fwrite(&val,1,1,output);
            }
        }else
            {
                fclose(output);
                return;
            }
    }
}

long long *inputString(FILE* fp, long long size, char *strme){
//The size is extended by savethe input with the value of the provisional
    char *str;
    int ch;
    long long len = 0;
    str = realloc(NULL, sizeof(*str)*size);//size is start size
    if(!str)return str;
    while(EOF!=(ch=fgetc(stdin)) ){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(*str)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    strme = realloc(str, sizeof(*str)*len);
    return len;
}
int main(int argc, char **argv)
{
    if (argv == 1)
        return;

    struct linkedlist *root;

    root = strtolist(argv[1]);
    FILE *file = fopen("testmedad","wb");
    save(root,file);
    fclose(file);
    doit();

}

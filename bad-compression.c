#include <stdio.h>
#include <limits.h>


char *inputString(FILE* fp, size_t size){
//The size is extended by the input with the value of the provisional
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(*str)*size);//size is start size
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(*str)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(*str)*len);
}

struct linkedlist{
    short repeat;
    char val;
    struct linkedlist *next;
};




struct linkedlist *addtolist(struct linkedlist *root, char c, short count)
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

int counter = 0;

struct linkedlist *strtotree(char *str)
{
    int _strlen = strlen(str) + 1;
    struct linkedlist *root = NULL;

    if (_strlen <= 1)
    {
        return NULL;
    }

    char c = *str;
    short count = 1;

    for (int i = 1;i < _strlen;i++)
    {
        if (str[i] == c)
        {
            if (count == SHRT_MAX)
            {
                counter++;
                root = addtolist(root, c, count);
                c = str[i];
                count = 0;
            }
            count++;
        }
        else
        {
            counter++;
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


void doit(struct linkedlist *list, FILE *file)
{
    int stat1, stat2;
    short repeat;
    char val;
    stat1 = fread(&repeat,sizeof(list->repeat),1,file);
    stat2 = fread(&val,sizeof(list->val),1,file);
    list = malloc(sizeof(struct linkedlist));


    if (stat1 == sizeof(list->repeat) || stat2 == sizeof(list->val))
    {

        for (int i = 0;i<repeat;i++)
        {
            putchar(val);
        }

        doit(list->next, file);
    }

}




int main(int argc, char **argv)
{
    struct linkedlist *root;

    char *str = "daa";

    root = strtotree(str);

    FILE *file = fopen("testmedad","wb");


    fwrite(&root->repeat,sizeof(root->repeat),1,file);
    fwrite(&root->val,sizeof(root->val),1,file);

    fwrite(&root->next->repeat,sizeof(root->repeat),1,file);
    fwrite(&root->next->val,sizeof(root->val),1,file);
    fclose(file);

    FILE *file2 = fopen("testmedad","rb");

    struct linkedlist *test = NULL;
    doit(test,file2);




}

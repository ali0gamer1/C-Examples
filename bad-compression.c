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

void save( struct linkedlist  *head,FILE *file) {

    struct linkedlist  *current_node = head;
   	while ( current_node != NULL)
    {
        fwrite(&current_node->repeat,sizeof(current_node->repeat),1,file);
        fwrite(&current_node->val,sizeof(current_node->val),1,file);

        current_node = current_node->next;
    }
}

void doit(FILE *file)
{

    short repeat;
    char val;
    fread(&repeat,sizeof(repeat),1,file);
    fread(&val,sizeof(val),1,file);


    if (!feof(file))
    {

        for (int i = 0;i<repeat;i++)
        {
            putchar(val);
        }

        doit(file);
    }


}




int main(int argc, char **argv)
{
    struct linkedlist *root;

    char *str = "aaaaaaaaaaaaaaaaffffffffffffffffffffffffffffffffffffffffffffffffffffffsdafasfasa";

    root = strtotree(str);

    FILE *file = fopen("testmedad","wb");


    save(root,file);

    fclose(file);

    FILE *file2 = fopen("testmedad","rb");

    doit(file2);




}

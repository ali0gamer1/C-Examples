#include <stdio.h>


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
    int repeat;
    char val;
    struct linkedlist *next;
};




struct linkedlist *addtolist(struct linkedlist *root, char c, int count)
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
    int count = 1;

    for (int i = 1;i < _strlen;i++)
    {
        if (str[i] == c)
        {
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



int main(int argc, char **argv)
{
    struct linkedlist *root;

    char *str = "dddddddddddddddaaa";

    root = strtotree(str);

    FILE *file = fopen("testmedad","wb");

    if (sizeof(root)*counter > strlen(str))
    {
        fwrite(str,strlen(str),1,file);

    }else
        fwrite(root,sizeof(root)*counter,1,file);

    print(root);

}

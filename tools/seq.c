#include <stdio.h>
#include <unistd.h>
/*
این خیلی ریده ماله باید اوکی بشه
یا ولش میکنم یا تمیزش میکنم
هیچی تو فانکشن نیست
کاملم نیست
*/

char isnum(char *str)
{
    while(*str != 0){

        if (!isdigit(*str++))
        {
            return 0;
        }

    }

    return 1;
}

void unescape(char *str)
{
    char *temp =(char *) malloc(strlen(str)+1);

    int i = 0, j = 0;

    if (temp == NULL)
    {
        perror("malloc rid");
        return;
    }

    while(*(str+i) != 0)
    {

        if (*(str+i) == '\\' && *((str+i)+1) == 'n')
        {
            *(temp+j) = '\n';
            j++;
            i++;
        }else
        if (*(str+i) == '\\' && *((str+i)+1) == 't')
        {
            *(temp+j) = '\t';
            j++;
            i++;
        }
        else{
            *(temp+j) = *(str+i);
            j++;
        }

        i++;

    }
    *(temp+j) = 0;

    strcpy(str,temp);


}


int main(int argc, char *argv[])
{
    int opt;
    char *format = NULL, wdth = 0, *sep ="\n";

    // put ':' in the starting of the
    // string so that program can
    //distinguish between '?' and ':'
    while((opt = getopt(argc, argv, ":s:f:w")) != -1)
    {
        switch(opt)
        {
            case 'w':
                wdth = 1;
                break;
            case 'f':
                format = strdup(optarg);
                break;
            case 's':
                sep = strdup(optarg);
                unescape(sep);
                break;
            case ':':
                printf("option needs a value\n");
                exit(1);
                break;
            case '?':
                printf("unknown option: %c\n", optopt);
                exit(1);
                break;
        }
    }

    // handle non-option integers
    int count = argc - optind;

    if (count > 3)
    {
        fprintf(stderr,"ridi dawsh man\n");
        exit(1);
    }

    if (count == 1)
    {
        int till;
        char *pad;

        if (wdth)
        {
            pad = malloc(strlen(argv[optind]) + 2 );
            sprintf(pad,"%%0%dd",strlen(argv[optind]));
        }

        till = atoi(argv[optind]);

        for(int i = 0;i<till;i++)
        {
            if (wdth)
            {
                printf(pad,i+1);
            }else
                printf("%d", i+1);

            if (i+1 < till)
            {
                printf("%s",sep);
            }

        }

    }else
    if (count == 2)
    {
        char *pad;
        int from, till;

        if (wdth)
        {
            pad = malloc(strlen(argv[optind + 1]) + 2);
            sprintf(pad,"%%0%dd",strlen(argv[optind+1]));
        }

        if (!isnum(argv[optind]) && !isnum(argv[optind + 1]))
        {
            fprintf(stderr,"ridi dawsh man\n");
            exit(1);
        }

        from = atoi(argv[optind]);
        till = atoi(argv[optind+1]);

        for(;from<=till;from++)
        {
            if (wdth)
            {
                printf(pad,from);
            }else
                printf("%d",from);

            if (from<till)
            {
                printf("%s",sep);
            }
        }
    }else
    if (count == 3)
    {
        char *pad;
        int from, till, step;


        if (wdth)
        {
            pad = malloc(strlen(argv[optind+2]) + 2);
            sprintf(pad,"%%0%dd",strlen(argv[optind+2]));
        }

        if (!isnum(argv[optind]) && !isnum(argv[optind + 1]) && !isnum(argv[optind + 2]))
        {
            fprintf(stderr,"ridi dawsh man\n");
            exit(1);
        }

        from = atoi(argv[optind]);
        step = atoi(argv[optind+1]);
        till = atoi(argv[optind+2]);

        for(;from<=till;from+=step)
        {
            if (wdth)
            {
                printf(pad,from);
            }else
                printf("%d",from);
            printf("%s",sep);
        }
    }
    puts("");
    return 0;
}

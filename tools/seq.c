#include <stdio.h>
#include <unistd.h>

/*
    TODO: implement other options, bug fix, fix potential memory problems, better handling for options' arguments
*/

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
        int till= atoi(argv[optind]);
        char *pad;

        if (wdth)
        {
            pad = malloc(strlen(argv[optind]) + 2 );
            sprintf(pad,"%%0%dd",strlen(argv[optind]));
        }


        for(int i = 0;i<till;i++)
        {
            if (wdth)
            {
                printf(pad,i+1);
            }else
                printf("%d", i+1);

            printf("%s",sep);
        }

    }else
    if (count == 2)
    {
        char *pad;

        if (wdth)
        {
            pad = malloc(strlen(argv[optind + 1]) + 2);
            sprintf(pad,"%%0%dd",strlen(argv[optind+1]));
        }

        int from = atoi(argv[optind]);
        int till = atoi(argv[optind+1]);

        for(;from<=till;from++)
        {
            if (wdth)
            {
                printf(pad,from);
            }else
                printf("%d",from);

            printf("%s",sep);
        }
    }else
    if (count == 3)
    {
        char *pad;

        if (wdth)
        {

            pad = malloc(strlen(argv[optind+2]) + 2);
            sprintf(pad,"%%0%dd",strlen(argv[optind+2]));
        }

        int from = atoi(argv[optind]);
        int step = atoi(argv[optind+1]);
        int till = atoi(argv[optind+2]);

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

    return 0;

}

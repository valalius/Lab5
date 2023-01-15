#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double x1, x2, delta, result, x;
    int N, num;
    char group_name[6], student_name[20];
    FILE * f_input, * f_output, * f_outbin, * f_inbin;

//////////////////////////////receiving data///////////////////////////////////////
    f_input = fopen("text.txt", "r");
    if (f_input==NULL)
    {
        printf("\n ERROR. CANNOT OPEN <text.txt>.");
        exit(1);
    }
    fscanf(f_input, "%lf %lf %d %lf %s ", &x1, &x2, &N, &delta, &group_name);
    fgets(&student_name, 20, f_input);
    fclose(f_input);
    printf(" Received data:");
    printf("\n x1: %.3lf\n x2 = %.3lf\n N = %d\n delta = %.3lf\n group = %s\n name = %s\n\n", x1, x2, N, delta, group_name, student_name);

    if (N==0)
    {
        N = ((x2-x1)/delta)+1;
    }
    if (delta==0)
    {
        delta=(x2-x1)/(N-1);
    }
//////////////////////////////receiving data///////////////////////////////////////

//////////////////////////////text+bin file////////////////////////////////////////
    f_output = fopen( "text_out.txt", "w" );
    f_outbin = fopen( "beans.bin", "wb" );
    if (f_output==NULL)
    {
        printf("\n ERROR. CANNOT OPEN <text_out.txt>.");
        exit(1);
    }
    if (f_outbin==NULL)
    {
        printf("\n ERROR. CANNOT OPEN <beans.bin>.");
        exit(1);
    }
    fprintf(f_output, "\n*----+---------------------+---------------------*");
    fprintf(f_output, "\n| N  |          X          |         F(X)        |");
    fprintf(f_output, "\n*----+---------------------+---------------------*");
    for(int i=1;i<=N;++i)
    {
        result = 0.5*pow((x1+250),3)-pow((x1-125),2)+500;
        fwrite( &i, sizeof(int), 1, f_outbin );
        fwrite( &x1, sizeof(double), 1, f_outbin );
        fwrite( &result, sizeof(double), 1, f_outbin );
        fprintf( f_output, "\n|%4d|%21.3lf|%21.5lf|", i, x1, result);
        fprintf( f_output,"\n*----+---------------------+---------------------*");
        x1+=delta;
    }
    fclose(f_outbin);
    fprintf(f_output, "\n\n %s %s", group_name, student_name );
    fclose(f_output);
//////////////////////////////text+bin file////////////////////////////////////////

//////////////////////////////console//////////////////////////////////////////////
    f_inbin = fopen( "beans.bin", "rb" );
    if (f_inbin==NULL)
    {
        printf("\n ERROR. CANNOT OPEN <beans.bin>.");
        exit(1);
    }
    printf("\n*----+---------------------+---------------------*");
    printf("\n| N  |          X          |         F(X)        |");
    printf("\n*----+---------------------+---------------------*");
    for (int i=1; i<=N; i++)
    {
        fread( &num, sizeof(int), 1, f_inbin );
        fread( &x, sizeof(double), 1, f_inbin );
        fread( &result, sizeof(double), 1, f_inbin );
        printf ("\n|%4d|%21.3lf|%21.5lf|", num, x, result);
        printf("\n*----+---------------------+---------------------*");
    }
    fclose(f_inbin);
//////////////////////////////console//////////////////////////////////////////////
}

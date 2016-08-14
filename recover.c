/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
    // TODO
    FILE* inptr=fopen("card.raw","r");
    if(inptr==NULL)
    {
        fclose(inptr);
        printf("can't open file");
        return 1;
    }
    ////////////////////////////////////////////////////////////////
    FILE* outptr=NULL;
    int counter=0;
    BYTE buffer[512];
    char outname[10];
    //int offset=0;
    ////////////////////////////////////////////////////////////////
    while(counter==0)
    {
    //offset+=fread(buffer,1,512,inptr);
    fread(buffer,4,1,inptr);
    if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
{
    
    sprintf(outname,"%03d.jpg",counter);

    outptr=fopen(outname,"w");
    fseek(inptr,-4,SEEK_CUR);
    fread(buffer,512,1,inptr);
    fwrite(buffer,512,1,outptr);
    ++counter;
}   
else
{
    fseek(inptr,4,SEEK_CUR);
}
    
    }
    ////////////////////////////////////////////////////
    while(!feof(inptr))
    {
        if(inptr !=NULL)
        {
            fread(buffer,512,1,inptr);
            if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
              {
                  fclose(outptr);
                  sprintf(outname,"%03d.jpg",counter);
                   outptr=fopen(outname,"w");
                   fwrite(buffer,512,1,outptr);
                   ++counter;
                  
              }
            else
            {
                fwrite(buffer,512,1,outptr);
                
            }
            
            
            
        }
        
        
    }
    fclose(inptr);
  
    
    return 0;
}

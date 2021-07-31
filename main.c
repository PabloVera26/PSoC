#include "project.h"
#include <stdio.h>//librería para la funcion sprintf
#include <stdlib.h>//libreria para algunas funciones char

uint8 personas;
uint16 sec,status0,status1;
char str[9];                // variable de impresion
uint8 contador;

int main(void)
{
    CyGlobalIntEnable;
    LCD_Start();            //Inicializacion de la LCD
    Timer_Start();
         
    personas=0;
    contador=2;
    
    LCD_Position(0,0);
    LCD_PrintString("People:");
    
    for(;;)
    {
        
        status0=A0_Read();
        status1=A1_Read();
                
        if(status0 == 0)
        {
         
            personas++;
            CyDelay(250);
                
        }
        
        if(status1 == 0)
        {
         
            personas--;
            CyDelay(250);
            
        }
            
        sprintf(str,"%d",personas);       //Conversion de variable float a char para su publicacion
        LCD_Position(0,8);
        LCD_PrintString(str);                     //Publicación del resultado en la LCD
        
    }

}
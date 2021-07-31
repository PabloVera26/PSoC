#include "project.h"
#include <stdio.h>//librería para la funcion sprintf
#include <stdlib.h>//libreria para algunas funciones char

uint8 personas; //variable del contador de personas
uint16 status0,status1; //variables para leer las entradas
char str[9];                // variable de impresion para las personas

uint sec;   //variable para contar los segundos del timer

int main(void)
{
    CyGlobalIntEnable;
    LCD_Start();            //Inicializacion de la LCD
    Timer_Start();  //inicializacion del timer
         
    personas=0; //iniciacion de la variable de personas
    
    LCD_Position(0,0);  //imprimir people en la pantalla
    LCD_PrintString("People:");
    
    for(;;)
    {
        
        status0=A0_Read();  //lectura del primer sensor
        status1=A1_Read();  //lectura del segundo sensor
        
        //condicionales para leer los sensores
        //si detectamos un 0 en la entrada sumamos 1 en el numero de personas
        
        if(status0 == 0)
        {
         
            personas++;
            CyDelay(250);
                
        }
        
        //si detectamos un 0 en la entrada restamos 1 en el numero de personas
        if(status1 == 0)
        {
         
            personas--;
            CyDelay(250);
            
        }
        
        
        //imprimir el numero de personas
        sprintf(str,"%d",personas);       //Conversion de variable float a char para su publicacion
        LCD_Position(0,8);
        LCD_PrintString(str);                     //Publicación del resultado en la LCD
        
    }

}

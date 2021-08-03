#include "project.h"
#include <stdio.h>//librería para la funcion sprintf
#include <stdlib.h>//libreria para algunas funciones char

//ADRIAN PINES- SENSOR 0 EN EL PIN 2.6
//ADRIAN PINES- SENSOR 1 EN EL PIN 2.7

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//variables adrian/contador

uint8 personas; //variable del contador de personas
uint16 status0,status1; //variables para leer las entradas
char str[9];                // variable de impresion para las personas
uint8 i;    //variable de control

personas=0; //iniciacion de la variable de personas

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//variables yayo/temperatura

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//variables yayo/co2

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
    
    CyGlobalIntEnable;
    LCD_Start();            //Inicializacion de la LCD

    //impresiones permanentes
    LCD_Position(3,0);  //imprimir people en la pantalla
    LCD_PrintString("People:");
    
    for(;;)
    {
        
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //funcion contador de personas/adrian
        
        i=1;    //iniciar el contador de control en  1
        status0=A0_Read();  //lectura del primer sensor
        status1=A1_Read();  //lectura del segundo sensor
        
        //condicionales para leer los sensores
        //si detectamos un 0 en la entrada sumamos 1 en el numero de personas
        if(status0 == 0)
        {
         
            while(i==1)
            {
                status1=A1_Read();
                
                if(status1 == 0)
                {
         
                    personas++;
                    i=0;
            
                }
                
            }
            
        }
        
        //si detectamos un 0 en la entrada restamos 1 en el numero de personas
        if(status1 == 0)
        {
         
            while(i==1)
            {
                status0=A0_Read();
                
                if(status0 == 0)
                {
         
                    personas--;
                    i=0;
            
                }
                
            }
            //hola
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        //imprimir el numero de personas
        sprintf(str,"%d",personas);       //Conversion de variable float a char para su publicacion
        LCD_Position(3,8);
        LCD_PrintString(str);                     //Publicación del resultado en la LCD
        
    }

}

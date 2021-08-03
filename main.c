#include "project.h"
#include <stdio.h>//librería para la funcion sprintf
#include <stdlib.h>//libreria para algunas funciones char

//ADRIAN PINES- SENSOR 0 EN EL PIN 2.6
//ADRIAN PINES- SENSOR 1 EN EL PIN 2.7
//YAYO PINES- SENSOR MQ135 0.0
//YAYO PINES- SENSOR LM35 0.4
//YAYO PINES- LED VERDE 0.1
//YAYO PINES- LED AMARILLO 0.2
//YAYO PINES- LED ROJO 0.3

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
int16 volts, analog2;//variable para leer adc y convertir a volts
float Temp; //Variable de temperatura
char str2[5]; //variable para imprimir temperatura en la LCD

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//variables yayo/co2
int16 analog1;//variable para leer Co2
char str3[7];//variable para imprimir en la LCD

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
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
          ////////////////////////////////////////////////// Sacar el Co2////////////////////////////////////////////////////////////////////
       Mux_FastSelect(0); // seleccionamos canal 0 del multiplexor
       ADC_StartConvert(); //empieza a leer el adc del canal 0
       ADC_IsEndConversion(ADC_WAIT_FOR_RESULT); //esperamos resultado
       analog1=ADC_GetResult16(); //recibimos resultado en 16 bits
       ADC_StopConvert(); // paramos el adc
       sprintf(str3,"%i",analog1); //convertimos la variable entera en char
       LCD_Position(0,0); //posicion donde se imprimira
       LCD_PrintString(str3); //imprimimos en LCD
       LCD_PrintString("ppm  ");  // imprimimos el texto en lcd
       
       //Condiciones para los leds bueno, moderado, peligro
       if(analog1>=0 && analog1<700){ // if para la condicion buena
        Bueno_Write(1);
        Moderado_Write(0);
        Peligro_Write(0);
    }else{
        if(analog1>=700 && analog1<1000){//if para la condicion modearada
            Moderado_Write(1);
            Bueno_Write(0);
            Peligro_Write(0);
        }else{// condicion para el peligroso
            Peligro_Write(1);
            Bueno_Write(0);
            Moderado_Write(0);
        }
    }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        ////////////////////////////////////////////////////////sacar temperatura////////////////////////////////////////////////////////////////
        Mux_FastSelect(1); //seleccionamos canal 1 del multiplexor
       ADC_StartConvert(); //empezar a convertir en el canal 2
       ADC_IsEndConversion(ADC_WAIT_FOR_RESULT); //esperamos resultado
       analog2=ADC_GetResult16(); //obtenemos resultado en 16bits
       ADC_StopConvert(); // paramos el adc
       volts=ADC_CountsTo_mVolts(analog2);// convertimos el valor leido en volts
       Temp=((volts/10)-5);// ajustamos la conversion para la temperatura con la formula
       sprintf(str2,"%.1f",Temp); //convertimos el valor float a char
       LCD_Position(1,0);// posicion para imprimir
       LCD_PrintString(str2);// imprimimos en lcs
       LCD_PrintString("C  ");// imprimimos C en LCD
        
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
    }

}

//Aaron Escaño
#include <stdio.h>
#include  <stdlib.h>

#define HORASNORMALES 44
#define MINHORAS 30
#define MAXHORAS 80
#define MINPRECIOHORAS 100
#define MAXPRECIOHORAS 550
#define MAXEMPLEADOS 20

#define CANTRANGOS 4

void imprimirTabla(int horas_Trabajadas[], int horas_Precio[],int cantTrabajadores);
float deduccion(int sueldoBruto);
float sueldoBruto(int horasTrabajadas, int precioHoras,int horasExtras[]);
int contieneRango(int horas,int numinf, int numsup);


int main(void){
    int cant_Empleados;

    int horas_Precio[MAXEMPLEADOS];
    int horas_Trabajadas[MAXEMPLEADOS];
    int rangos[CANTRANGOS];

    do{
        printf("Cantidad de trabajadores: ");
        scanf("%i",&cant_Empleados);

        if (cant_Empleados <= 0 ||cant_Empleados > MAXEMPLEADOS){
            printf("La cantidad de empleados debe estar entre 1 a %i\n",MAXEMPLEADOS);
        }
    }while (cant_Empleados <= 0 || cant_Empleados > MAXEMPLEADOS);

    for (int i = 0; i < cant_Empleados; i++){
        printf("Empleado [%i]\n",i+1);
        do{
            printf("Horas trabajadas: ");
            scanf("%i",&horas_Trabajadas[i]);

            if(horas_Trabajadas[i] < MINHORAS || horas_Trabajadas[i] > MAXHORAS){
                printf("Las horas trabajadas debe estar entre %i y %i\n",MINHORAS,MAXHORAS);
            }
        }while (horas_Trabajadas[i] < MINHORAS || horas_Trabajadas[i] > MAXHORAS);
        do{
            printf("Precio por horas: ");
            scanf("%i",&horas_Precio[i]);

            if(horas_Precio[i] < MINPRECIOHORAS || horas_Precio[i] > MAXPRECIOHORAS){
                printf("El pago por hora debe estar entre %i y %i\n",MINPRECIOHORAS,MAXPRECIOHORAS);
            }
        }while (horas_Precio[i] < MINPRECIOHORAS || horas_Precio[i] > MAXPRECIOHORAS);
    }
    imprimirTabla(horas_Trabajadas,horas_Precio,cant_Empleados);
}

/*
Función: sueldoBruto
Argumento:
   horasTrabajadas: (int), el arreglo que contiene las horas trabajadas de los empleados 
   precioHoras: (int), el arreglo que contiene el precio por hora de cada trabajador
   horasextrasPrecio: (int), el arreglo que contiene el rango de horas extras para calcular el bono por horas extra
Objetivo:
   Calcular el sueldo bruto 'sueldoBruto'
Retorno:
   (float) sueldo bruto 'sueldoBruto'
*/
float sueldoBruto(int horasTrabajadas, int precioHoras,int horasextrasPrecio[]){ 

    int horasExtras = horasTrabajadas - HORASNORMALES;
    int sueldoBruto = 0;
    if (horasTrabajadas <= HORASNORMALES){
        sueldoBruto = (horasTrabajadas * precioHoras);
        return sueldoBruto;
    }
    sueldoBruto = HORASNORMALES * precioHoras;
    
    if (horasextrasPrecio[0] > 0){
        sueldoBruto += ((precioHoras * 1.35) * horasextrasPrecio[0]);
        if (horasextrasPrecio[1] > 0){
            sueldoBruto += ((precioHoras * 1.45) * horasextrasPrecio[1]);
            if (horasextrasPrecio[2] > 0){
                sueldoBruto += ((precioHoras * 1.50) * horasextrasPrecio[2]);
                if (horasextrasPrecio[3] > 0){
                    sueldoBruto += ((precioHoras * 2) * horasextrasPrecio[3]);
                }
            }
        }
    }
    return sueldoBruto + 1;

}

/*
Función: deduccion
Argumento:
   sueldoBruto: (int), el sueldo bruto que se usara para calcular la deduccion del mismo 
Objetivo:
   Calcular la deduccion del sueldo bruto 'deduccion_final'
Retorno:
   (float) deduccion del sueldo bruto 'deduccion_final'
*/
float deduccion(int sueldoBruto){
    float deduccion_final = 0;
    if (sueldoBruto > 8000){
        deduccion_final += (contieneRango(sueldoBruto,8000,12000) * 0.10);
        if (sueldoBruto > 12000){
            deduccion_final += (contieneRango(sueldoBruto,12000,17000) * 0.15);
            if (sueldoBruto > 17000){
                deduccion_final += (contieneRango(sueldoBruto,17000,sueldoBruto) * 0.20);
            }
        }
    }
    return deduccion_final;
}

/*
Función: sueldoBruto
Argumento:
   horasTrabajadas: (int), el arreglo que contiene las horas trabajadas de los empleados para imprimirlas
   precioHoras: (int), el arreglo que contiene el precio por hora de cada trabajador para imprimirlas
   cantTrabajadores: (int), la cantidad de trabajadores para saber el numero de iteraciones
Objetivo:
   Imprimir la nomina semanal 
Retorno:
   Nada
*/
void imprimirTabla(int horas_Trabajadas[], int horas_Precio[],int cantTrabajadores){
    int rangos[CANTRANGOS];
    system("cls");
    printf("                                                     [NOMINA SEMANAL]\n");
    printf("             Horas          Precio      Horas      Sueldo    44-54    54-64    64-68    69+                   Sueldo\n");
    printf("Trabajador   Trabajadas     Por Hora    Extras      Bruto     35%c      45%c      50%c    100%c     Deduccion      Neto\n",37,37,37,37);
    for (int i = 0; i < cantTrabajadores; i++){
        rangos[0] = contieneRango(horas_Trabajadas[i],44,54);
        rangos[1] = contieneRango(horas_Trabajadas[i],54,64);
        rangos[2] = contieneRango(horas_Trabajadas[i],64,68);
        rangos[3] = contieneRango(horas_Trabajadas[i],68,horas_Trabajadas[i]);

        float sueldobruto = sueldoBruto(horas_Trabajadas[i],horas_Precio[i],rangos);
        int horasExtras = horas_Trabajadas[i] - HORASNORMALES;
        float deduccionSueldo = deduccion(sueldobruto);
        float sueldoneto  = sueldobruto - deduccionSueldo;

        if (horasExtras <= 0){
            horasExtras = 0;
        }
        printf("%2i %15i %15i %9i %14.2f %5i %8i %8i  %6i %12.2f  %13.2f\n",i+1,horas_Trabajadas[i],horas_Precio[i],horasExtras,sueldobruto,rangos[0],rangos[1],rangos[2],rangos[3],deduccionSueldo,sueldoneto);
    }
}

/*
Función: contieneRango
Argumento:
   num: (int), la cantidad que se estara verificando 
   numinf: (int), rango inferior
   numsup: (int), rango superior
Objetivo:
   Hallar la cantidad que contiene un rango en especifico 'diff'
Retorno:
   (int) cantidad contenida en el rango 'diff'
*/
int contieneRango(int num,int numinf, int numsup){
    int diff = numsup - numinf;
    if (num > numinf){
        if (num - numinf < diff){
            return num - numinf;
        }    
        return diff;        
    }
    return 0;
}
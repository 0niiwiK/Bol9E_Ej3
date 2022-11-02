#include <stdio.h>

float solicitarSaldoInicial(); //No debe ser negativo
void leer_fechas (int *dia1, int *mes1, int *dia2, int *mes2);
int comparar_fechas (int diaida,int mesida,int diavuelta,int mesvuelta); //
int dias_transcurridos (int di,int mi,int dv,int mv); //
int comprobar_fecha (int dia, int mes); //
int solicitarNovedad();
float calcularPrecio(int dias_alquilado, int esNovedad);
void leer_fechas (int *dia1, int *mes1, int *dia2, int *mes2);
void calcularYMostrar(float saldo, float precio);


int main() {
    float saldo=solicitarSaldoInicial(),precio;
    int diaAlquiler,mesAlquiler,diaDevolucion,mesDevolucion;
    int esNovedad,diasAlquilado;
    leer_fechas(&diaAlquiler,&mesAlquiler,&diaDevolucion,&mesDevolucion);
    diasAlquilado=dias_transcurridos(diaAlquiler,mesAlquiler,diaDevolucion,mesDevolucion);
    precio=calcularPrecio(diasAlquilado,solicitarNovedad());
    calcularYMostrar(saldo,precio);

    return 0;
}

int comprobar_fecha (int dia, int mes){
    int esValida=0;
    if ((mes>0&&mes<=12)&&(dia>0&&dia<=30))
        esValida=1;
    return esValida;
}

int dias_transcurridos (int di,int mi,int dv,int mv){
    // Dias transcurridos
    int dias=0;
    if (mv==mi)
        dias=dv-di;
    else
        for (int i = mv; i >= mi; i--) {
            if (i==mv)
                dias+= dv;
            else if (i==mi)
                dias+= 30-di;
            else
                dias+= 30;
        }
    return dias;
}

int comparar_fechas (int diaida,int mesida,int diavuelta,int mesvuelta){
    int esValido=1;
    if ((mesvuelta<mesida) || (mesvuelta==mesida && diavuelta<diaida))
        esValido=0;
    return esValido;
}

void leer_fechas (int *dia1, int *mes1, int *dia2, int *mes2){
    printf("\nIntroduzca la fecha de alquiler (dd mm): ");
    scanf("%d %d", dia1, mes1);
    fflush(stdin);
    while (comprobar_fecha(*dia1, *mes1) == 0){
        printf("Fecha invalida\nIntroduzca la fecha de alquiler (dd mm): ");
        scanf("%d %d", dia1, mes1);
        fflush(stdin);
    }
    printf("Introduzca la fecha de devolucion (dd mm): ");
    scanf("%d %d", dia2, mes2);
    fflush(stdin);
    while (comprobar_fecha(*dia2, *mes2) == 0){
        printf("Fecha invalida\nIntroduzca la fecha de devolucion (dd mm): ");
        scanf("%d %d", dia2, mes2);
        fflush(stdin);
    }
    while (comparar_fechas(*dia1, *mes1, *dia2, *mes2) == 0){
        printf("Error: Fecha de devolucion anterior a fecha de alquiler\nIntroduzca la fecha de devolucion (dd mm): ");
        scanf("%d %d", dia2, mes2);
        fflush(stdin);
    }
}

float solicitarSaldoInicial(){
    float saldo;
    printf("Introduce el saldo inicial: ");
    scanf("%f",&saldo);
    fflush(stdin);
    while (saldo<0){
        printf("El saldo no puede ser negativo\nIntroduce el saldo inicial: ");
        scanf("%f",&saldo);
        fflush(stdin);
    }
    return saldo;
}

float calcularPrecio(int dias_alquilado, int esNovedad){
    float precio=0;
    if (dias_alquilado<=3)
        precio=1.2;
    else
        precio=dias_alquilado*0.75;
    if (esNovedad==1)
        precio*=1.04;
    return precio;
}

int solicitarNovedad(){
    char opcion;
    int esNovedad = 0;
    printf("\nIntroduce novedad (s)i (n)o: ");
    scanf("%c", &opcion);
    fflush(stdin);
    while (opcion != 's' && opcion != 'n') {
        printf("Opcion invalida (s) o (n)\nIntroduce novedad (s)i (n)o: ");
        scanf("%c", &opcion);
        fflush(stdin);
    }
    if (opcion == 's')
        esNovedad = 1;
    return esNovedad;
}

void calcularYMostrar(float saldo, float precio){
    if (precio<=saldo)
        printf("\nPelicula devuelta | Saldo restante: %.2f euros\n",saldo-precio);
    else
        printf("\nNo se pudo devolver por falta de saldo\n");
}
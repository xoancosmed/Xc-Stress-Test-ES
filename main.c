// Xc Stress Test
// (By) Xoán Carlos Cosmed Peralejo

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define TEXTRESET   "\033[0m"
#define TEXTBLACK   "\033[30m"
#define TEXTRED     "\033[31m"
#define TEXTGREEN   "\033[32m"
#define TEXTYELLOW  "\033[33m"
#define TEXTBLUE    "\033[34m"
#define TEXTMAGENTA "\033[35m"
#define TEXTCYAN    "\033[36m"
#define TEXTWHITE   "\033[37m"
#define TEXTBOLD    "\033[1m"
#define TEXTUNDER    "\033[4m"
#define CLEARTEXT   "\033[2J\033[1;1H"

void EstresarProcesador ();
void EstresarRAM ();
void EstresarDisco ();

void EMemoriaDinamica (long int num);
void EPila (long int num);
void EMemoriaDinamicaS ();
void EPilaS ();


int main(int argc, const char * argv[]) {

    int opc;
    char opcS[25];
    int salirpreg = 0;
    int salir = 0;

    printf(CLEARTEXT);

    printf(TEXTYELLOW);
    printf("\n");
    printf("\t\t************************************\n");
    printf("\t\t************************************\n");
    printf("\t\t********** Xc Stress Test **********\n");
    printf("\t\t************************************\n");
    printf("\t\t************************************\n");
    printf("\n");

    printf(TEXTGREEN);
    printf("\nEste es el Xc Mac Stress Test versión Beta 1.03 (compatible con sistemas Unix y Linux). Esta herramienta ha sido desarrollada por Xoán Cosmed.\n");
    printf(TEXTBLUE);
    printf("\nEsta herramienta permite poner a prueba el rendimiento del equipo. En esta herramienta se hace uso de comandos como \"yes\" y funciones de C repetidas muchas veces (como \"calloc\"), por eso el uso de ésta ha de hacerse con precaución. Para ello se recomienta monitorear el sistema con una herramienta, como por ejemplo el 'Monitor del Sistema' o 'htop' En caso de cualquier mínimo problema se recomienda cancelar la prueba. ");
    printf(TEXTCYAN);
    printf("Nota: el autor de esta herramienta no se hace responsable de ningún daño producido por la misma.\n");
    printf(TEXTRED);
    printf("\nPara forzar la salida use \"Ctr + Z\", o bien la herramienta que ofrezca su sistema operativo.\n");

    printf(TEXTRESET);
    printf("\n\nPulse ENTER para continuar ");

    while (getchar() != '\n') {}
    printf(CLEARTEXT);


    do
    {

        printf("\nXc Stress Test: \n\n");
        printf("\t1) Estresar Procesador\n");
        printf("\t2) Estresar Memoria RAM\n");
        printf("\t3) Estresar Disco Duro\n");
        printf("\t0) Salir\n\n");

        do {

            printf("¿Qué desea hacer? ");

            fgets(opcS, 25, stdin);
            opc = atoi(opcS);
            if (opc == 0) { if (opcS[0] != '0' && opcS[1] != '0') { opc = -1; } }

            switch (opc)
            {
                case 1:
                    salirpreg = 1;
                    EstresarProcesador();
                    break;

                case 2:
                    salirpreg = 1;
                    EstresarRAM();
                    break;

                case 3:
                    salirpreg = 1;
                    EstresarDisco();
                    break;

                case 0:
                    salir = 1;
                    salirpreg = 1;
                    break;

                default:
                    salirpreg = 0;
                    break;
            }

        } while (salirpreg != 1);

        printf(CLEARTEXT);

    } while (salir != 1);

    return 0;
}


///// FUNCIONES DE ESTRÉS /////

void EstresarProcesador ()
{
    int num;
    char resp[25];

    int i;
    char cad[25];
    char cadN[5];

    printf("\n");

    do {

        printf("¿Cuantos procesos desea lanzar? ");

        fgets(resp, 25, stdin);
        num = atoi(resp);

    } while (num > 255 || num < 1);

    printf("\n\nUna vez iniciado el proceso de estrés pulse ENTER para finalizar dicho proceso.\n\nNotas: En caso de que al pulsar ENTER para finalizar el test, éste no se termine, pulse \"Ctr + Z\" y a continuación escriba en su terminal \"killall yes\". Se recomienda revisar el proceso a través del Monitor de Actividad.\n");
    printf("\nSi ha comprendido lo anterior pulse ENTER para comenzar.\n");

    while (getchar() != '\n') {}

    for (i = 1; i <= num; i++)
    {
        sprintf(cadN, "%i", i);

        cad[0] = '\0';
        strcat(cad, "yes ");
        strcat(cad, cadN);
        strcat(cad, " > /dev/null &");
        //strcat(cad, " &");

        system(cad);
    }

    while (getchar() != '\n') {}

    system("killall yes");

    printf("\n");
    printf("\nProceso detenido. Pulse ENTER para volver al menú principal. ");

    while (getchar() != '\n') {}

}

void EstresarRAM ()
{
    int opc;
    long int num;
    char resp[25];


    printf("\n");

    do {

        printf("¿Qué método desea usar (1 = Memoria Dinámica; 2 = Pila)? ");

        fgets(resp, 25, stdin);
        opc = atoi(resp);

    } while(opc != 1 && opc != 2);

    do {

        printf("¿Cuántos bytes x4 / ciclos deseas (-1 para que se haga hasta pulsar ENTER)? ");

        fgets(resp, 25, stdin);
        num = atoi(resp);

    } while (num < -1);


    if (num != -1)
    {
        printf("\n\nPulse ENTER para comenzar ");
    }
    else
    {
        printf("\n\nPulse ENTER para comenzar. Pulse también ENTER cuando desee finalizar (si no funciona usar \"Ctr + Z\"). Este método todavía está en desarrollo, por lo que no es recomendable (se recomienda monitorear el proceso y matarlo en caso del mínimos problema). ");
    }

    while (getchar() != '\n') {}

    if (opc == 1)
    {
        if (num != -1)
        {
            EMemoriaDinamica(num);
        }
        else
        {
            EMemoriaDinamicaS();
        }
    }
    else if (opc == 2)
    {
        if (num != -1)
        {
            EPila(num);
        }
        else
        {
            EPilaS();
        }
    }

    printf("\n\nProceso completado. Pulse ENTER para volver al menú principal. ");

    while (getchar() != '\n') {}
}

void EstresarDisco ()
{
    printf("\n");

    char resp[25];
    long int num = -2;
    long int i;
    char tmp;

    do {

        printf("¿Cuántos bytes desea escribir (-1 para hasta finalización; pulsar Ctr + Z en el caso de haber problemas)? ");

        fgets(resp, 25, stdin);
        num = atol(resp);

    } while(num < -1);

    if (num == -1) i = num + 1;
    else i = 0;

    FILE *archivo;
    archivo = fopen("rand.txt", "w+");

    fprintf(archivo, "\n");

    if (archivo == NULL)
    {
        printf("No es posible abrir el archivo.");
    }
    else
    {
        for (i = i; i != num; i++)
        {
            fprintf(archivo, "x");

            printf("+");
        }
    }

    fprintf(archivo, "\n");
    fclose(archivo);
}


///// FUNCIONES DE APOYO /////

void EMemoriaDinamica (long int num)
{
    int i;

    struct lista {

        int val;
        struct lista *sig;

    };

    typedef struct lista Lista;

    Lista *primero = NULL;
    Lista *ultimo = NULL;
    Lista *elemento;
    Lista *elementoTMP;


    for (i = 0; i < num; i++)
    {
        elemento = (Lista *)calloc(1, sizeof(Lista));

        elemento->val = rand();
        elemento->sig = NULL;

        if (primero == NULL)
        {
            primero = elemento;
            ultimo = elemento;
        }
        else
        {
            ultimo->sig = elemento;
            ultimo = elemento;
        }

        i = i + sizeof(elemento->val) + sizeof(elemento->sig);
        printf("%i\t", i);
    }

    printf("\n\nProceso completado. Pulse ENTER para liberar la memoria empleada. ");

    while (getchar() != '\n') {}

    elemento = primero;
    while (elemento != NULL)
    {
        elementoTMP = elemento->sig;
        free(elemento);
        elemento = elementoTMP;
    }
}

void EPila (long int num)
{
    if (num > 0)
    {
        EPila (num - 1);
        printf("+");
    }
}

void EMemoriaDinamicaS ()
{
    int i = 0;

    struct lista {

        int val;
        struct lista *sig;

    };

    typedef struct lista Lista;

    Lista *primero = NULL;
    Lista *ultimo = NULL;
    Lista *elemento;
    Lista *elementoTMP;

    //char Stmp[10];

ESTRERAM4EVER:


    /*fgets(Stmp, 10, stdin);
    if (Stmp[0] == '\n')
    {
        i = -1;
    }*/

    while (i != -1)
    {
        elemento = (Lista *)calloc(1, sizeof(Lista));
        elemento->val = rand();
        elemento->sig = NULL;

        if (primero == NULL)
        {
            primero = elemento;
            ultimo = elemento;
        }
        else
        {
            ultimo->sig = elemento;
            ultimo = elemento;
        }

        i = i + sizeof(elemento->val) + sizeof(elemento->sig);
        printf("%i\t", i);

        goto ESTRERAM4EVER;
    }

    printf("\n\nProceso completado. Pulse ENTER para liberar la memoria empleada. ");

    while (getchar() != '\n') {}

    elemento = primero;
    while (elemento != NULL)
    {
        elementoTMP = elemento->sig;
        free(elemento);
        elemento = elementoTMP;
    }
}

void EPilaS ()
{
    if (1 /*getchar() != '\n'*/)
    {
        EPilaS ();
        printf("+");
    }
}

// Xc Stress Test
// (By) Xoán Carlos Cosmed Peralejo

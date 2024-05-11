#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Definición de la estructura DatosMeteorologicos
struct DatosMeteorologicos
{
    int anio;
    int mes;
    int dia;
    float temperatura;
    int humedad;
    int velocidadViento;
    int presionAtmosferica;
    string condicionMeteorologica;
};

// Función para escribir los datos meteorológicos en un archivo de texto
void escribirDatosMeteorologicos(const string& nombreArchivo, DatosMeteorologicos datos[], int numDatos)
{
    // Abrir el archivo en modo escritura de texto, y posicionar el cursor al final para agregar nuevos datos
    ofstream archivo(nombreArchivo, ios::out | ios::app);

    // Verificar si el archivo se abrió correctamente
    if (!archivo)
    {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    // Escribir los datos meteorológicos al final del archivo
    for (int i = 0; i < numDatos; ++i)
    {
        archivo << datos[i].anio << " " << datos[i].mes << " " << datos[i].dia << " "
                << fixed << setprecision(1) << datos[i].temperatura << " "
                << datos[i].humedad << " " << datos[i].velocidadViento << " "
                << datos[i].presionAtmosferica << " " << datos[i].condicionMeteorologica << endl;
    }

    // Cerrar el archivo
    archivo.close();

    // Mostrar mensaje de éxito
    cout << "Datos meteorológicos escritos en el archivo de texto: " << nombreArchivo << endl;
}

// Función para solicitar y agregar un nuevo dato meteorológico
void agregarNuevoDato(DatosMeteorologicos datos[], int& numDatos)
{
    // Solicitar al usuario que ingrese los nuevos datos meteorológicos
    cout << "Ingrese la fecha (AA MM DD): ";
    cin >> datos[numDatos].anio >> datos[numDatos].mes >> datos[numDatos].dia;
    cout << "Ingrese la temperatura (C): ";
    cin >> datos[numDatos].temperatura;
    cout << "Ingrese la humedad (%): ";
    cin >> datos[numDatos].humedad;
    cout << "Ingrese la velocidad del viento (km/h): ";
    cin >> datos[numDatos].velocidadViento;
    cout << "Ingrese la presión atmosférica (hPa): ";
    cin >> datos[numDatos].presionAtmosferica;
    cout << "Ingrese la condición meteorológica: ";
    cin.ignore(); // Para consumir el salto de línea residual del último cin
    getline(cin, datos[numDatos].condicionMeteorologica);

    // Incrementar el número de datos
    numDatos++;
}

// Función para mostrar todos los datos meteorológicos almacenados
void mostrarTodosLosDatos(DatosMeteorologicos datos[], int numDatos)
{
    cout << "Todos los datos meteorológicos:" << endl;
    cout << setw(4) << "Año" << setw(4) << "Mes" << setw(4) << "Día" << setw(14) << "Temperatura" << setw(8) << "Humedad" << setw(20) << "Condición" << endl;
    for (int i = 0; i < numDatos; ++i)
    {
        cout << setw(4) << datos[i].anio << setw(4) << datos[i].mes << setw(4) << datos[i].dia
             << setw(14) << fixed << setprecision(1) << datos[i].temperatura << setw(8) << datos[i].humedad
             << setw(20) << datos[i].condicionMeteorologica << endl;
    }
}

int main()
{
    DatosMeteorologicos datos[] = {
        {2020, 1, 1, 17.9, 74, 7, 1008, "Nublado"}, 
        {2020, 1, 2, 18.7, 64, 19, 1028, "Lluvioso"},
        {2020, 1, 3, 24.7, 76, 8, 1021, "Lluvioso"},
        {2020, 1, 4, 24.6, 57, 6, 1027, "Nublado"},
        {2020, 1, 5, 27.4, 34, 20, 1019, "Soleado"},
        {2020, 1, 6, 14.3, 51, 15, 1019, "Lluvioso"},
        {2020, 1, 7, 15.5, 51, 3, 1021, "Soleado"},
        {2020, 1, 8, 12.4, 58, 7, 1003, "Nublado"},
        {2020, 1, 9, 22.1, 58, 9, 1019, "Lluvioso"},
        {2020, 1, 10, 19.5, 57, 20, 1017, "Nublado"}
    };
    int numDatos = 10; // Número total de datos meteorológicos

    int opcion;

    do
    {
        cout << "\n--- Menú ---" << endl;
        cout << "1. Agregar datos meteorológicos" << endl;
        cout << "2. Mostrar todos los datos meteorológicos" << endl;
        cout << "3. Buscar datos meteorológicos por fecha" << endl;
        cout << "4. Salir" << endl;
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1:
                agregarNuevoDato(datos, numDatos);
                escribirDatosMeteorologicos("datos.txt", datos, numDatos);
                break;
            case 2:
                mostrarTodosLosDatos(datos, numDatos);
                break;
            case 3:
                // Aquí puedes implementar la función para buscar por fecha si lo deseas
                cout << "Función de búsqueda no implementada todavía." << endl;
                break;
            case 4:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
                break;
        }
    } while (opcion != 4);

    return 0;
}





// Este codigo implemneta un menu de agregar buscar y mostrar datos meteorologicos
// Tambien utiliza un arregl donde se escribe las priemars 10 fechas de los datos meteorologicos
// y se almacena en un archivo txt 


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
    char condicionMeteorologica[20]; // Tamaño suficiente para almacenar la condición meteorológica
};

// Función para escribir los datos meteorológicos en un archivo binario
void escribirDatosMeteorologicos(const string& nombreArchivo)
{
    // Arreglo de datos meteorológicos proporcionados
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

    // Abrir el archivo en modo escritura binaria
    ofstream archivo(nombreArchivo, ios::out | ios::binary);

    // Verificar si el archivo se abrió correctamente
    if (!archivo)
    {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    // Escribir los datos meteorológicos en el archivo
    for (const auto& dato : datos)
    {
        archivo.write(reinterpret_cast<const char*>(&dato), sizeof(DatosMeteorologicos));
    }

    // Cerrar el archivo
    archivo.close();

    // Mostrar mensaje de éxito
    cout << "Datos meteorológicos escritos en el archivo binario: " << nombreArchivo << endl;
}

// Función para leer y mostrar los datos meteorológicos de una fecha específica
void mostrarDatosPorFecha(const string& nombreArchivo)
{
    int anio, mes, dia;
    cout << "Digite una fecha entre el rango 2020-01-01 hasta 2020-01-10 (en el formato AA MM DD): ";
    cin >> anio >> mes >> dia;

    ifstream archivoLectura(nombreArchivo, ios::binary);
    if (!archivoLectura)
    {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return;
    }

    DatosMeteorologicos datoLeido;
    bool encontrado = false;

    // Leer y buscar los datos correspondientes a la fecha ingresada
    while (archivoLectura.read(reinterpret_cast<char*>(&datoLeido), sizeof(DatosMeteorologicos)))
    {
        if (datoLeido.anio == anio && datoLeido.mes == mes && datoLeido.dia == dia)
        {
            encontrado = true;
            cout << "Datos meteorológicos para la fecha " << anio << "-" << mes << "-" << dia << ":" << endl;
            cout << "Temperatura (C): " << datoLeido.temperatura << endl;
            cout << "Humedad (%): " << datoLeido.humedad << endl;
            cout << "Velocidad del Viento (km/h): " << datoLeido.velocidadViento << endl;
            cout << "Presión Atmosférica (hPa): " << datoLeido.presionAtmosferica << endl;
            cout << "Condición Meteorológica: " << datoLeido.condicionMeteorologica << endl;
            break;
        }
    }

    if (!encontrado)
    {
        cout << "No se encontraron datos para la fecha ingresada." << endl;
    }

    archivoLectura.close();
}

// Función para mostrar todos los datos meteorológicos almacenados en el archivo
void mostrarTodosLosDatos(const string& nombreArchivo)
{
    ifstream archivoLectura(nombreArchivo, ios::binary);
    if (!archivoLectura)
    {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return;
    }

    DatosMeteorologicos datoLeido;

    cout << "Todos los datos meteorológicos:" << endl;
    cout << setw(4) << "Año" << setw(4) << "Mes" << setw(4) << "Día" << setw(10) << "Temperatura" << setw(8) << "Humedad" << setw(20) << "Condición" << endl;
    while (archivoLectura.read(reinterpret_cast<char*>(&datoLeido), sizeof(DatosMeteorologicos)))
    {
        cout << setw(4) << datoLeido.anio << setw(4) << datoLeido.mes << setw(4) << datoLeido.dia << setw(10) << datoLeido.temperatura << setw(8) << datoLeido.humedad << setw(20) << datoLeido.condicionMeteorologica << endl;
    }

    archivoLectura.close();
}

int main()
{
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
                escribirDatosMeteorologicos("datos.bin");
                break;
            case 2:
                mostrarTodosLosDatos("datos.bin");
                break;
            case 3:
                mostrarDatosPorFecha("datos.bin");
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

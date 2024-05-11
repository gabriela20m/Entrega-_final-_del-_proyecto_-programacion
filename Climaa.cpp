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

int main()
{
    escribirDatosMeteorologicos("datos.bin");
    mostrarDatosPorFecha("datos.bin");
    return 0;
}



// Solo con una funcion que es que digite la fecha
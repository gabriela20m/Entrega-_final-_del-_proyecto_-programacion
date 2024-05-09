#include <iostream>
#include <fstream>
#include <string>
// Sin el arreglo de los datos 
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

// Función para agregar datos meteorológicos al archivo binario
void agregarDatosMeteorologicos(const string& nombreArchivo)
{
    // Pedir al usuario que ingrese los nuevos datos meteorológicos
    DatosMeteorologicos nuevoDato;
    cout << "Ingrese la fecha (en el formato AAAA MM DD): ";
    cin >> nuevoDato.anio >> nuevoDato.mes >> nuevoDato.dia;
    cout << "Ingrese la temperatura (C): ";
    cin >> nuevoDato.temperatura;
    cout << "Ingrese la humedad (%): ";
    cin >> nuevoDato.humedad;
    cout << "Ingrese la velocidad del viento (km/h): ";
    cin >> nuevoDato.velocidadViento;
    cout << "Ingrese la presión atmosférica (hPa): ";
    cin >> nuevoDato.presionAtmosferica;
    cout << "Ingrese la condición meteorológica: ";
    cin.ignore(); // Limpiar el buffer del teclado
    getline(cin, nuevoDato.condicionMeteorologica);

    // Abrir el archivo en modo escritura binaria (en modo append para agregar al final)
    ofstream archivo(nombreArchivo, ios::out | ios::binary | ios::app);

    // Verificar si el archivo se abrió correctamente
    if (!archivo)
    {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    // Escribir el nuevo dato meteorológico en el archivo
    archivo.write(reinterpret_cast<const char*>(&nuevoDato), sizeof(DatosMeteorologicos));

    // Cerrar el archivo
    archivo.close();

    // Mostrar mensaje de éxito
    cout << "Datos meteorológicos agregados correctamente." << endl;
}

// Función para mostrar todos los datos meteorológicos almacenados en el archivo binario
void mostrarTodosLosDatos(const string& nombreArchivo)
{
    ifstream archivoLectura(nombreArchivo, ios::binary);
    if (!archivoLectura)
    {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return;
    }

    DatosMeteorologicos datoLeido;

    // Leer y mostrar todos los datos meteorológicos almacenados en el archivo
    cout << "Todos los datos meteorológicos almacenados:" << endl;
    while (archivoLectura.read(reinterpret_cast<char*>(&datoLeido), sizeof(DatosMeteorologicos)))
    {
        cout << "Fecha: " << datoLeido.anio << "-" << datoLeido.mes << "-" << datoLeido.dia << endl;
        cout << "Temperatura (C): " << datoLeido.temperatura << endl;
        cout << "Humedad (%): " << datoLeido.humedad << endl;
        cout << "Velocidad del Viento (km/h): " << datoLeido.velocidadViento << endl;
        cout << "Presión Atmosférica (hPa): " << datoLeido.presionAtmosferica << endl;
        cout << "Condición Meteorológica: " << datoLeido.condicionMeteorologica << endl;
        cout << endl;
    }

    archivoLectura.close();
}

// Función para buscar y mostrar los datos meteorológicos de una fecha específica
void mostrarDatosPorFecha(const string& nombreArchivo)
{
    int anio, mes, dia;
    cout << "Digite alguna entre el rango 2020-01-01 hasta 2020-01-10 (en el formato AA MM DD): ";
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
    int opcion;
    const string nombreArchivo = "datos.bin";

    do
    {
        // Mostrar el menú
        cout << "\n--- Menú ---" << endl;
        cout << "1. Agregar datos meteorologicos" << endl;
        cout << "2. Mostrar todos los datos meteorologicos" << endl;
        cout << "3. Buscar datos meteorologicos por fecha" << endl;
        cout << "4. Salir" << endl;
        cout << "Opción: ";
        cin >> opcion;

        // Realizar la opción seleccionada
        switch (opcion)
        {
            case 1:
                agregarDatosMeteorologicos(nombreArchivo);
                break;
            case 2:
                mostrarTodosLosDatos(nombreArchivo);
                break;
            case 3:
                mostrarDatosPorFecha(nombreArchivo);
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

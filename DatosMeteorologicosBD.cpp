#include <iostream>
#include <fstream>
#include <string>
//Datos meteorologicos (temperatura y condicion meteorologica)
using namespace std;

// Definición de la estructura para los datos meteorológicos
struct Tiempo {
    int dia;
    int mes;
    int anio;
    float temperatura;
    string condicionMeteorologica;
};

// Función para mostrar el menú y obtener la opción del usuario
int menu() {
    int x = 0;

    // Mostrar las opciones del menú
    cout << "1. Agregar datos meteorologicos" << endl;
    cout << "2. Mostrar todos los datos meteorologicos" << endl;
    cout << "3. Buscar datos meteorologicos por fecha" << endl;
    cout << "4. Salir" << endl;
    cout << "Opción: ";

    // Leer la opción del usuario
    cin >> x;

    return x;
}

// Función para obtener una estructura de datos meteorológicos de la entrada del usuario
Tiempo obtenerDatosMeteorologicos() {
    Tiempo datos; //variable para obtener datos y guardarlos

    // Solicitar y leer la fecha, temperatura y condición meteorológica del usuario
    cout << "Fecha (DD/MM/AAAA): ";
    char slash;
    cin >> datos.dia >> slash >> datos.mes >> slash >> datos.anio;
    cout << "Temperatura: ";
    cin >> datos.temperatura;
    cout << "Condición Meteorológica: ";
    cin.ignore();
    getline(cin, datos.condicionMeteorologica);

    return datos;
}

// Función para agregar datos meteorológicos al archivo binario
void agregarDatosMeteorologicos(const string& fileName) {
    // Abrir el archivo en modo binario para añadir datos al final
    ofstream openArchivo(fileName, ios::binary | ios::app);

    // Verificar si el archivo se abrió correctamente
    if (!openArchivo) {
        cout << "Error al abrir el archivo de salida." << endl;
        return;
    }

    // Obtener los datos meteorológicos del usuario
    Tiempo datos = obtenerDatosMeteorologicos();

    // Escribir los datos en el archivo
    openArchivo.write(reinterpret_cast<char*>(&datos), sizeof(Tiempo));

    // Cerrar el archivo
    openArchivo.close();
}

// Función para mostrar todos los datos meteorológicos del archivo binario
void mostrarTodosLosDatosMeteorologicos(const string& fileName) {
    // Abrir el archivo en modo binario para lectura
    ifstream openFile(fileName, ios::binary);

    // Verificar si el archivo se abrió correctamente
    if (!openFile) {
        cout << "Error al abrir el archivo de entrada." << endl;
        return;
    }

    // Crear una variable para almacenar los datos meteorológicos leídos
    Tiempo datos;

    // Leer y mostrar todos los datos meteorológicos del archivo
    while (openFile.read(reinterpret_cast<char*>(&datos), sizeof(Tiempo))) {
        cout << "Fecha: " << datos.dia << "/" << datos.mes << "/" << datos.anio << ", ";
        cout << "Temperatura: " << datos.temperatura << ", ";
        cout << "Condición Meteorológica: " << datos.condicionMeteorologica << endl;
    }

    // Cerrar el archivo
    openFile.close();
}

// Función para buscar datos meteorológicos por fecha en el archivo binario
void buscarDatosMeteorologicosPorFecha(int dia, int mes, int anio, const string& fileName) {
    // Abrir el archivo en modo binario para lectura
    ifstream openFile(fileName, ios::binary);

    // Verificar si el archivo se abrió correctamente
    if (!openFile) {
        cout << "Error al abrir el archivo de entrada." << endl;
        return;
    }

    // Crear una variable para almacenar los datos meteorológicos leídos
    Tiempo datos;

    // Variable para indicar si se encontró la fecha buscada
    bool encontrado = false;

    // Leer cada registro y comparar la fecha con la proporcionada por el usuario
    while (openFile.read(reinterpret_cast<char*>(&datos), sizeof(Tiempo))) {
        if (datos.dia == dia && datos.mes == mes && datos.anio == anio) {
            encontrado = true;
            cout << "Fecha: " << datos.dia << "/" << datos.mes << "/" << datos.anio << ", ";
            cout << "Temperatura: " << datos.temperatura << ", ";
            cout << "Condición Meteorológica: " << datos.condicionMeteorologica << endl;
        }
    }

    // Cerrar el archivo
    openFile.close();

    // Mostrar un mensaje si no se encontraron datos para la fecha proporcionada
    if (!encontrado) {
        cout << "No se encontraron datos meteorológicos para la fecha proporcionada." << endl;
    }
}

int main() {
    string fileName = "datos_meteorologicos.bin";
    int opcion;

    // Bucle principal del programa
    do {
        // Mostrar el menú y obtener la opción del usuario
        opcion = menu();

        // Realizar la acción correspondiente según la opción del usuario
        switch (opcion) {
            case 1:
                agregarDatosMeteorologicos(fileName);
                break;
            case 2:
                mostrarTodosLosDatosMeteorologicos(fileName);
                break;
            case 3:
                {
                    int dia, mes, anio;
                    cout << "Ingrese la fecha (DD/MM/AAAA): ";
                    char slash;
                    cin >> dia >> slash >> mes >> slash >> anio;
                    buscarDatosMeteorologicosPorFecha(dia, mes, anio, fileName);
                }
                break;
            case 4:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida. Por favor, ingrese una opción válida." << endl;
        }
    } while (opcion != 4);

    return 0;
}

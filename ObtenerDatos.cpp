#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Definición de la estructura DatosMeteorologicos
struct DatosMeteorologicos {
    int anio;
    int mes;
    int dia;
    float temperatura;
    int humedad;
    int velocidadViento;
    int presionAtmosferica;
    string condicionMeteorologica;
};

// Constante para definir el tamaño máximo del arreglo
const int MAX_DATOS = 900;

// Función para leer los datos meteorológicos desde un archivo
int leerDatosMeteorologicos(const string& nombreArchivo, DatosMeteorologicos datos[], int& numDatos) {
    ifstream archivo(nombreArchivo);

    // Verificar si el archivo se abrió correctamente
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    // Ignorar la primera línea (encabezado)
    string encabezado;
    getline(archivo, encabezado);

    // Leer los datos del archivo y almacenarlos en el arreglo
    string linea;
    while (numDatos < MAX_DATOS && getline(archivo, linea)) {
        istringstream iss(linea);
        string fecha;

        // Leer la fecha y los datos meteorológicos
        if (!(iss >> fecha >> datos[numDatos].temperatura >> datos[numDatos].humedad
                >> datos[numDatos].velocidadViento >> datos[numDatos].presionAtmosferica)) {
            cerr << "Error al leer los datos en la línea " << numDatos + 2 << endl;
            continue; // Saltar esta línea si hay un error de lectura
        }

        // Procesar la fecha
        size_t pos1 = fecha.find('-');
        size_t pos2 = fecha.rfind('-');
        if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2) {
            datos[numDatos].anio = stoi(fecha.substr(0, pos1));
            datos[numDatos].mes = stoi(fecha.substr(pos1 + 1, pos2 - pos1 - 1));
            datos[numDatos].dia = stoi(fecha.substr(pos2 + 1));
        } else {
            cerr << "Error al procesar la fecha en la línea " << numDatos + 2 << endl;
            continue; // Saltar esta línea si hay un error de formato de fecha
        }

        // Leer la condición meteorológica (resto de la línea)
        getline(iss, datos[numDatos].condicionMeteorologica);
        if (!datos[numDatos].condicionMeteorologica.empty() && datos[numDatos].condicionMeteorologica[0] == ' ') {
            datos[numDatos].condicionMeteorologica = datos[numDatos].condicionMeteorologica.substr(1); // Quitar el espacio inicial
        }

        numDatos++;
    }

    archivo.close();
    return 0;
}

// Función para imprimir los datos meteorológicos
void imprimirDatosMeteorologicos(const DatosMeteorologicos datos[], int numDatos) {
    for (int i = 0; i < numDatos; ++i) {
        cout << "Año: " << datos[i].anio << ", Mes: " << datos[i].mes << ", Día: " << datos[i].dia
             << ", Temperatura: " << datos[i].temperatura << ", Humedad: " << datos[i].humedad
             << ", Velocidad del viento: " << datos[i].velocidadViento << ", Presión atmosférica: "
             << datos[i].presionAtmosferica << ", Condición meteorológica: " << datos[i].condicionMeteorologica << endl;
    }
}

int main() {
    string nombreArchivo = "datos_meteorologicos.txt";
    DatosMeteorologicos datos[MAX_DATOS];
    int numDatos = 0;

    // Leer los datos meteorológicos desde el archivo
    int resultado = leerDatosMeteorologicos(nombreArchivo, datos, numDatos);
    if (resultado != 0) {
        return resultado;
    }

    // Imprimir los datos meteorológicos
    imprimirDatosMeteorologicos(datos, numDatos);

    return 0;
}

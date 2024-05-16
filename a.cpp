#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Definici�n de la estructura DatosMeteorologicos
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

// Constante para definir el tama�o m�ximo del arreglo
const int MAX_DATOS = 900;

// Funci�n para leer los datos meteorol�gicos desde un archivo
int leerDatosMeteorologicos(const string& nombreArchivo, DatosMeteorologicos datos[], int& numDatos) {
    ifstream archivo(nombreArchivo);

    // Verificar si el archivo se abri� correctamente
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    // Ignorar la primera l�nea (encabezado)
    string encabezado;
    getline(archivo, encabezado);

    // Leer los datos del archivo y almacenarlos en el arreglo
    string linea;
    while (numDatos < MAX_DATOS && getline(archivo, linea)) {
        istringstream iss(linea);
        string fecha;

        // Leer la fecha y los datos meteorol�gicos
        if (!(iss >> fecha >> datos[numDatos].temperatura >> datos[numDatos].humedad
                >> datos[numDatos].velocidadViento >> datos[numDatos].presionAtmosferica)) {
            cerr << "Error al leer los datos en la l�nea " << numDatos + 2 << endl;
            continue; // Saltar esta l�nea si hay un error de lectura
        }

        // Procesar la fecha
        size_t pos1 = fecha.find('-');
        size_t pos2 = fecha.rfind('-');
        if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2) {
            datos[numDatos].anio = stoi(fecha.substr(0, pos1));
            datos[numDatos].mes = stoi(fecha.substr(pos1 + 1, pos2 - pos1 - 1));
            datos[numDatos].dia = stoi(fecha.substr(pos2 + 1));
        } else {
            cerr << "Error al procesar la fecha en la l�nea " << numDatos + 2 << endl;
            continue; // Saltar esta l�nea si hay un error de formato de fecha
        }

        // Leer la condici�n meteorol�gica (resto de la l�nea)
        getline(iss, datos[numDatos].condicionMeteorologica);
        if (!datos[numDatos].condicionMeteorologica.empty() && datos[numDatos].condicionMeteorologica[0] == ' ') {
            datos[numDatos].condicionMeteorologica = datos[numDatos].condicionMeteorologica.substr(1); // Quitar el espacio inicial
        }

        numDatos++;
    }

    archivo.close();
    return 0;
}

// Funci�n para imprimir los datos meteorol�gicos
void imprimirDatosMeteorologicos(const DatosMeteorologicos datos[], int numDatos) {
    for (int i = 0; i < numDatos; ++i) {
        cout << "A�o: " << datos[i].anio << ", Mes: " << datos[i].mes << ", D�a: " << datos[i].dia
             << ", Temperatura: " << datos[i].temperatura << ", Humedad: " << datos[i].humedad
             << ", Velocidad del viento: " << datos[i].velocidadViento << ", Presi�n atmosf�rica: "
             << datos[i].presionAtmosferica << ", Condici�n meteorol�gica: " << datos[i].condicionMeteorologica << endl;
    }
}

int main() {
    string nombreArchivo = "datos_meteorologicos.txt";
    DatosMeteorologicos datos[MAX_DATOS];
    int numDatos = 0;

    // Leer los datos meteorol�gicos desde el archivo
    int resultado = leerDatosMeteorologicos(nombreArchivo, datos, numDatos);
    if (resultado != 0) {
        return resultado;
    }

    // Imprimir los datos meteorol�gicos
    imprimirDatosMeteorologicos(datos, numDatos);

    return 0;
}


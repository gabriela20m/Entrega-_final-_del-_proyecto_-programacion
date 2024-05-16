#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const int MAX_DATOS = 1000;

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

// Función para leer los datos meteorológicos desde un archivo
int leerDatosMeteorologicos(const string &nombreArchivo, DatosMeteorologicos datos[], int &numDatos) {
    ifstream archivo(nombreArchivo);

    // Verificar si el archivo se abrió correctamente
    if (!archivo) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
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
        if (!(iss >> fecha >> datos[numDatos].temperatura >>
            datos[numDatos].humedad >> datos[numDatos].velocidadViento >>
            datos[numDatos].presionAtmosferica)) {
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
        if (!datos[numDatos].condicionMeteorologica.empty() &&
            datos[numDatos].condicionMeteorologica[0] == ' ') {
            datos[numDatos].condicionMeteorologica =
                datos[numDatos].condicionMeteorologica.substr(1); // Quitar el espacio inicial
        }

        numDatos++;
    }

    archivo.close();
    return 0;
}

// Función para imprimir los datos meteorológicos
void imprimirDatosMeteorologicos(const DatosMeteorologicos datos[], int numDatos) {
    for (int i = 0; i < numDatos; ++i) {
        cout << "Año: " << datos[i].anio << ", Mes: " << datos[i].mes
            << ", Día: " << datos[i].dia
            << ", Temperatura: " << datos[i].temperatura
            << ", Humedad: " << datos[i].humedad
            << ", Velocidad del viento: " << datos[i].velocidadViento
            << ", Presión atmosférica: " << datos[i].presionAtmosferica
            << ", Condición meteorológica: " << datos[i].condicionMeteorologica
            << endl;
    }
}

// Función para encontrar los rangos de fechas
void encontrarRangos(int &anio1, int &mes1, int &dia1, int &anio2, int &mes2, int &dia2) {
    cout << "Digite la primera fecha (en el formato AAAA MM DD): ";
    cin >> anio1 >> mes1 >> dia1;

    cout << "Digite la segunda fecha (en el formato AAAA MM DD): ";
    cin >> anio2 >> mes2 >> dia2;
}

// Función para encontrar temperatura máxima y mínima en un rango de fechas
void encontrarMaximaMinimaTemperatura(const DatosMeteorologicos datos[], int numDatos) {
    int anio1, mes1, dia1;
    int anio2, mes2, dia2;
    encontrarRangos(anio1, mes1, dia1, anio2, mes2, dia2);

    // Variables para almacenar las temperaturas máxima y mínima
    float temperaturaMaxima = -999; // Inicializado con un valor muy bajo
    float temperaturaMinima = 999; // Inicializado con un valor muy alto
    bool encontrado = false;

    // Buscar las temperaturas máxima y mínima en el rango de fechas
    for (int i = 0; i < numDatos; ++i) {
        if (datos[i].anio >= anio1 && datos[i].mes >= mes1 &&
            datos[i].dia >= dia1 && datos[i].anio <= anio2 &&
            datos[i].mes <= mes2 && datos[i].dia <= dia2) {
            if (datos[i].temperatura > temperaturaMaxima)
                temperaturaMaxima = datos[i].temperatura;
            if (datos[i].temperatura < temperaturaMinima)
                temperaturaMinima = datos[i].temperatura;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron datos para el rango de fechas ingresado." << endl;
        return;
    }

    cout << "Temperatura máxima en el rango de fechas: " << temperaturaMaxima << " C" << endl;
    cout << "Temperatura mínima en el rango de fechas: " << temperaturaMinima << " C" << endl;
}

// Función para calcular el promedio de temperatura para un mes específico
void calcularPromedioTemperaturaPorMes(const DatosMeteorologicos datos[], int numDatos) {
    int mes, anio;
    cout << "Ingrese el número de mes y año para calcular el promedio de temperatura (en el formato MM AAAA): ";
    cin >> mes >> anio;

    float totalTemperaturas = 0;
    int cantidadDias = 0;
    bool encontrado = false;

    // Calcular el promedio de temperaturas para el mes y año especificados
    for (int i = 0; i < numDatos; ++i) {
        if (datos[i].mes == mes && datos[i].anio == anio) {
            totalTemperaturas += datos[i].temperatura;
            cantidadDias++;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No hay datos para el mes y año especificados." << endl;
        return;
    }

    float promedio = totalTemperaturas / cantidadDias;
    cout << "El promedio de temperatura para el mes " << mes << "/" << anio << " es: " << fixed
        << setprecision(2) << promedio << " C" << endl;
}

// Función para calcular el mayor promedio de humedad en relación a una
// condición meteorológica
void calcularMayorPromedioHumedad(const DatosMeteorologicos datos[], int numDatos) {
    string condicion;
    int mes, anio;
    cout << "Ingrese mes y año para evaluar: ";
    cin >> mes >> anio;
    cout << "Ingrese la condición meteorológica para calcular el promedio de humedad: ";
    cin >> condicion;

    int totalHumedad = 0;
    int cantidadMediciones = 0;
    bool encontrado = false;
    float mayorPromedio = -1.0; // Inicializar con un valor muy bajo

    // Calcular el mayor promedio de humedad para la condición meteorológica
    // especificada en el mes y año especificados
    for (int i = 0; i < numDatos; ++i) {
        if (datos[i].mes == mes && datos[i].anio == anio &&
            datos[i].condicionMeteorologica == condicion) {
            totalHumedad += datos[i].humedad;
            cantidadMediciones++;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No hay datos para la condición meteorológica y fecha especificados." << endl;
        return;
    }

    float promedio = totalHumedad / cantidadMediciones;
    if (promedio > mayorPromedio)
        mayorPromedio = promedio;

    cout << "El mayor promedio de humedad para la condición " << condicion
        << " en el mes " << mes << "/" << anio << " es: " << fixed << setprecision(2) << mayorPromedio << " %" << endl;
}

// Función para calcular el menor promedio de humedad en relación a una
// condición meteorológica
void calcularMenorPromedioHumedad(const string& nombreArchivo)
{
    // Solicitar la condición meteorológica, el mes y el año al usuario
    string condicion;
    int mes, anio;

    cout << "Digite la condición meteorológica: ";
    cin >> condicion;

    cout << "Digite el mes y el año (en el formato MM AAAA): ";
    cin >> mes >> anio;

    // Abrir el archivo para lectura
    ifstream archivoLectura(nombreArchivo);
    if (!archivoLectura)
    {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return;
    }

    // Declarar variables para el cálculo del promedio y el contador
    DatosMeteorologicos datoLeido;
    int contador = 0;
    float sumaHumedad = 0;
    float menorPromedio = 100.0; // Inicializamos con un valor alto

    // Leer el archivo línea por línea
    while (archivoLectura >> datoLeido.anio >> datoLeido.mes >> datoLeido.dia
                          >> datoLeido.temperatura >> datoLeido.humedad >> datoLeido.velocidadViento
                          >> datoLeido.presionAtmosferica >> datoLeido.condicionMeteorologica)
    {
        // Verificar si los datos corresponden al mes y año especificados
        if (datoLeido.mes == mes && datoLeido.anio == anio)
        {
            // Verificar si la condición meteorológica es la especificada por el usuario
            if (datoLeido.condicionMeteorologica == condicion)
            {
                // Sumar la humedad y aumentar el contador
                sumaHumedad += datoLeido.humedad;
                contador++;
            }
        }
    }

    // Cerrar el archivo después de leer todos los datos
    archivoLectura.close();

    // Comprobar si se encontraron datos de humedad para la condición y el período de tiempo especificados
    if (contador == 0)
    {
        cout << "No hay datos de humedad para la condición meteorológica ingresada en el mes y año especificados." << endl;
    }
    else
    {
        // Calcular el promedio de humedad
        float promedio = sumaHumedad / contador;

        // Comprobar si el promedio es menor que el menor promedio encontrado hasta ahora
        if (promedio < menorPromedio)
        {
            // Actualizar el menor promedio si es menor que el actual
            menorPromedio = promedio;
        }

        // Mostrar el menor promedio de humedad encontrado
        cout << "El menor promedio de humedad para la condición meteorológica " << condicion << " en el mes " << mes << "/" << anio << " es: " << menorPromedio << "%" << endl;
    }
}

// Función para mostrar datos meteorológicos en un rango de fechas
void mostrarDatosMeteorologicosPorRango(const DatosMeteorologicos datos[], int numDatos) {
    int anio1, mes1, dia1;
    int anio2, mes2, dia2;
    encontrarRangos(anio1, mes1, dia1, anio2, mes2, dia2);

    bool encontrado = false;

    // Mostrar los datos en el rango de fechas
    cout << "Datos meteorológicos en el rango de fechas:" << endl;
    cout << "Fecha        Temperatura (C)  Humedad (%)  Vel. Viento (km/h)  "
        << "Presión Atmosférica (Pa)  Condición Meteorológica"
        << endl;
    for (int i = 0; i < numDatos; ++i) {
        if (datos[i].anio >= anio1 && datos[i].anio <= anio2 &&
            datos[i].mes >= mes1 && datos[i].mes <= mes2 && datos[i].dia >= dia1 &&
            datos[i].dia <= dia2) {
            cout << setw(4) << datos[i].anio << "-" << setw(2) << datos[i].mes << "-"
                << setw(2) << datos[i].dia << "    ";
            cout << setw(14) << fixed << datos[i].temperatura << "   ";
            cout << setw(10) << fixed << datos[i].humedad << "   ";
            cout << setw(18) << fixed << datos[i].velocidadViento << "   ";
            cout << setw(23) << fixed << datos[i].presionAtmosferica << "   ";
            cout << datos[i].condicionMeteorologica << endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron datos para el rango de fechas ingresado." << endl;
    }
}

// Función principal para ejecutar el programa
int main() {
    DatosMeteorologicos datos[MAX_DATOS];
    int numDatos = 0;

    // Leer los datos meteorológicos del archivo
    if (leerDatosMeteorologicos("datos_meteorologicos.txt", datos, numDatos) != 0) {
        return 1; // Salir del programa si hay un error al leer el archivo
    }

    int opcion;
    do {
        // Menú de opciones
        cout << "\nMenú:\n";
        cout << "1. Mostrar datos meteorológicos en un rango de fechas\n";
        cout << "2. Encontrar temperatura máxima y mínima en un rango de fechas\n";
        cout << "3. Calcular promedio de temperatura por mes\n";
        cout << "4. Calcular mayor promedio de humedad por condición meteorológica\n";
        cout << "5. Calcular menor promedio de humedad por condición meteorológica\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarDatosMeteorologicosPorRango(datos, numDatos);
                break;
            case 2:
                encontrarMaximaMinimaTemperatura(datos, numDatos);
                break;
            case 3:
                calcularPromedioTemperaturaPorMes(datos, numDatos);
                break;
            case 4:
                calcularMayorPromedioHumedad(datos, numDatos);
                break;
            case 5:
                calcularMenorPromedioHumedad("datos_meteorologicos.txt");
                break;
            case 0:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida. Inténtelo de nuevo." << endl;
        }
    } while (opcion != 0);

    return 0;
}

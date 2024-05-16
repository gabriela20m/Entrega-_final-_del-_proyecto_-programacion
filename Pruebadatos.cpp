#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

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


void encontarRangos(const DatosMeteorologicos datos[], int numDatos){
int anio1, mes1, dia1;
int anio2, mes2, dia2;
    
    cout << "Digite la primera fecha (en el formato AAAA MM DD): ";
    cin >> anio1 >> mes1 >> dia1;

    cout << "Digite la segunda fecha (en el formato AAAA MM DD): ";
    cin >> anio2 >> mes2 >> dia2;

    for (int i = 0; i < numDatos; ++i) {
        if (datos[i].anio >= anio1 && datos[i].mes >= mes1 && datos[i].dia >= dia1 &&
            datos[i].anio <= anio2 && datos[i].mes <= mes2 && datos[i].dia <= dia2){
                cout << "Año: " << datos[i].anio << ", Mes: " << datos[i].mes << ", Día: " << datos[i].dia
             << ", Temperatura: " << datos[i].temperatura << ", Humedad: " << datos[i].humedad
             << ", Velocidad del viento: " << datos[i].velocidadViento << ", Presión atmosférica: "
             << datos[i].presionAtmosferica << ", Condición meteorológica: " << datos[i].condicionMeteorologica << endl;
            }

}

// Función para encontrar la temperatura máxima y mínima en un rango de fechas
void encontrarMaximaMinimaTemperatura(DatosMeteorologicos datos[], int numDatos) {
    int anio1, mes1, dia1;
    int anio2, mes2, dia2;
    
    cout << "Digite la primera fecha (en el formato AAAA MM DD): ";
    cin >> anio1 >> mes1 >> dia1;

    cout << "Digite la segunda fecha (en el formato AAAA MM DD): ";
    cin >> anio2 >> mes2 >> dia2;

    bool encontrado = false;
    float temperaturaMaxima = -9999.0; // Inicializar con un valor muy bajo
    float temperaturaMinima = 9999.0; // Inicializar con un valor muy alto

    // Buscar las temperaturas máxima y mínima en el rango de fechas
    for (int i = 0; i < numDatos; ++i) {
        if (datos[i].anio >= anio1 && datos[i].mes >= mes1 && datos[i].dia >= dia1 &&
            datos[i].anio <= anio2 && datos[i].mes <= mes2 && datos[i].dia <= dia2) {
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
void calcularPromedioTemperaturaPorMes(DatosMeteorologicos datos[], int numDatos) {
    int mes;
    cout << "Ingrese el número de mes para calcular el promedio de temperatura: ";
    cin >> mes;

    int totalTemperaturas = 0;
    int cantidadDias = 0;
    bool encontrado = false;

    // Calcular el promedio de temperaturas para el mes especificado
    for (int i = 0; i < numDatos; ++i) {
        if (datos[i].mes == mes) {
            totalTemperaturas += datos[i].temperatura;
            cantidadDias++;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No hay datos para el mes especificado." << endl;
        return;
    }

    float promedio = static_cast<float>(totalTemperaturas) / cantidadDias;
    cout << "El promedio de temperatura para el mes " << mes << " es: " << fixed << setprecision(2) << promedio << " C" << endl;
}

// Función para calcular el mayor promedio de humedad en relación a una condición meteorológica
void calcularMayorPromedioHumedad(DatosMeteorologicos datos[], int numDatos) {
    string condicion;
    cout << "Ingrese la condición meteorológica para calcular el promedio de humedad: ";
    cin >> condicion;

    int totalHumedad = 0;
    int cantidadMediciones = 0;
    bool encontrado = false;
    float mayorPromedio = -1.0; // Inicializar con un valor muy bajo

    // Calcular el mayor promedio de humedad para la condición meteorológica especificada
    for (int i = 0; i < numDatos; ++i) {
        if (datos[i].condicionMeteorologica == condicion) {
            totalHumedad += datos[i].humedad;
            cantidadMediciones++;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No hay datos para la condición meteorológica especificada." << endl;
        return;
    }

    float promedio = static_cast<float>(totalHumedad) / cantidadMediciones;
    if (promedio > mayorPromedio)
        mayorPromedio = promedio;

    cout << "El mayor promedio de humedad para la condición " << condicion << " es: " << fixed << setprecision(2) << mayorPromedio << " %" << endl;
}

// Función para calcular el menor promedio de humedad en relación a una condición meteorológica
void calcularMenorPromedioHumedad(DatosMeteorologicos datos[], int numDatos) {
    string condicion;
    cout << "Ingrese la condición meteorológica para calcular el promedio de humedad: ";
    cin >> condicion;

    int totalHumedad = 0;
    int cantidadMediciones = 0;
    bool encontrado = false;
    float menorPromedio = 999.0; // Inicializar con un valor muy alto

    // Calcular el menor promedio de humedad para la condición meteorológica especificada
    for (int i = 0; i < numDatos; ++i) {
        if (datos[i].condicionMeteorologica == condicion) {
            totalHumedad += datos[i].humedad;
            cantidadMediciones++;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No hay datos para la condición meteorológica especificada." << endl;
        return;
    }

    float promedio = static_cast<float>(totalHumedad) / cantidadMediciones;
    if (promedio < menorPromedio)
        menorPromedio = promedio;

    cout << "El menor promedio de humedad para la condición " << condicion << " es: " << fixed << setprecision(2) << menorPromedio << " %" << endl;
}

// Función para mostrar datos meteorológicos en un rango de fechas
void mostrarDatosMeteorologicosPorRango(DatosMeteorologicos datos[], int numDatos) {
    int anio1, mes1, dia1;
    int anio2, mes2, dia2;
    
    cout << "Digite la primera fecha (en el formato AAAA MM DD): ";
    cin >> anio1 >> mes1 >> dia1;

    cout << "Digite la segunda fecha (en el formato AAAA MM DD): ";
    cin >> anio2 >> mes2 >> dia2;

    bool encontrado = false;

    // Mostrar los datos en el rango de fechas
    cout << "Datos meteorológicos en el rango de fechas:" << endl;
    cout << "Fecha        Temperatura (C)  Humedad (%)  Vel. Viento (km/h)  Presión Atmosférica (Pa)  Condición Meteorológica" << endl;
    for (int i = 0; i < numDatos; ++i) {
        if (datos[i].anio >= anio1 && datos[i].anio <= anio2 &&
            datos[i].mes >= mes1 && datos[i].mes <= mes2 &&
            datos[i].dia >= dia1 && datos[i].dia <= dia2) {
            cout << setw(4) << datos[i].anio << "-" << setw(2) << datos[i].mes << "-" << setw(2) << datos[i].dia << "    ";
            cout << setw(14) << fixed << datos[i].temperatura << "   ";
            cout << setw(10) << fixed << datos[i].humedad << "   ";
            cout << setw(18) << fixed << datos[i].velocidadViento << "   ";
            cout << setw(25) << fixed << datos[i].presionAtmosferica << "   ";
            cout << datos[i].condicionMeteorologica << endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron datos para el rango de fechas ingresado." << endl;
    }
}

// Función para agregar nuevos datos meteorológicos al archivo
void agregarDatosMeteorologicos(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::app);

    // Verificar si el archivo se abrió correctamente
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    DatosMeteorologicos nuevoDato;

    cout << "Ingrese la fecha (en el formato AAAA MM DD): ";
    cin >> nuevoDato.anio >> nuevoDato.mes >> nuevoDato.dia;

    cout << "Ingrese la temperatura: ";
    cin >> nuevoDato.temperatura;

    cout << "Ingrese la humedad: ";
    cin >> nuevoDato.humedad;

    cout << "Ingrese la velocidad del viento: ";
    cin >> nuevoDato.velocidadViento;

    cout << "Ingrese la presión atmosférica: ";
    cin >> nuevoDato.presionAtmosferica;

    cout << "Ingrese la condición meteorológica: ";
    cin.ignore(); // Limpiar el buffer del teclado antes de leer la cadena
    getline(cin, nuevoDato.condicionMeteorologica);

    // Escribir los nuevos datos en el archivo
    archivo << nuevoDato.anio << "-" << nuevoDato.mes << "-" << nuevoDato.dia << " "
            << nuevoDato.temperatura << " " << nuevoDato.humedad << " "
            << nuevoDato.velocidadViento << " " << nuevoDato.presionAtmosferica << " " << nuevoDato.condicionMeteorologica << endl;

    // Cerrar el archivo
    archivo.close();

    // Mostrar mensaje de éxito
    cout << "Nuevos datos meteorológicos agregados al archivo." << endl;
}

int main() {
    string nombreArchivo = "datos_meteorologicos.txt";
    DatosMeteorologicos datos[MAX_DATOS];
    int numDatos = 0;

    // Leer los datos meteorológicos del archivo
    if (leerDatosMeteorologicos(nombreArchivo, datos, numDatos) != 0) {
        cerr << "No se pudieron leer los datos meteorológicos del archivo." << endl;
        return 1;
    }

    int opcion;
    while (true) {
        // Menú
        cout << "\n--- Menú ---" << endl;
        cout << "1. Encontrar temperatura máxima y mínima en un rango de fechas" << endl;
        cout << "2. Calcular promedio de temperatura para un mes específico" << endl;
        cout << "3. Calcular el mayor promedio de humedad en relación a una condición meteorológica" << endl;
        cout << "4. Calcular el menor promedio de humedad en relación a una condición meteorológica" << endl;
        cout << "5. Mostrar datos meteorológicos en un rango de fechas" << endl;
        cout << "6. Agregar nuevos datos meteorológicos" << endl;
        cout << "7. Salir" << endl;
        cout << "Ingrese su opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                encontarRangos( datos, numDatos)
                break;
            case 2:
                calcularPromedioTemperaturaPorMes(datos, numDatos);
                break;
            case 3:
                calcularMayorPromedioHumedad(datos, numDatos);
                break;
            case 4:
                calcularMenorPromedioHumedad(datos, numDatos);
                break;
            case 5:
                mostrarDatosMeteorologicosPorRango(datos, numDatos);
                break;
            case 6:
                agregarDatosMeteorologicos(nombreArchivo);
                break;
            case 7:
                cout << "Saliendo..." << endl;
                return 0; // Salir del programa
            default:
                cout << "Opción no válida. Por favor, ingrese un número entre 1 y 7." << endl;
        }
    }

    return 0;
}

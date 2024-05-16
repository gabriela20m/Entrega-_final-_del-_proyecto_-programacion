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

// Definición de las variables globales para almacenar las fechas encontradas
int anio1, mes1, dia1;
int anio2, mes2, dia2;

// Función para leer los datos meteorológicos desde un archivo
int leerDatosMeteorologicos(const string &nombreArchivo,
                            DatosMeteorologicos datos[], int &numDatos) {
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
          datos[numDatos].condicionMeteorologica.substr(
              1); // Quitar el espacio inicial
    }

    numDatos++;
  }

  archivo.close();
  return 0;
}

// Función para agregar datos meteorológicos desde el teclado
void agregarDatosMeteorologicos(DatosMeteorologicos datos[], int &numDatos) {
  if (numDatos == MAX_DATOS) {
    cerr << "No se pueden agregar más datos. El límite ha sido alcanzado."
         << endl;
    return;
  }

  cout << "Ingrese los datos meteorológicos (Formato: AAAA-MM-DD Temp Humedad Velocidad Presión Condición):" << endl;
  cout << "Ejemplo: 2023-05-16 25.6 70 5 1013 Soleado" << endl;

  string fecha;
  cin >> fecha >> datos[numDatos].temperatura >> datos[numDatos].humedad >>
      datos[numDatos].velocidadViento >> datos[numDatos].presionAtmosferica;

  // Procesar la fecha
  size_t pos1 = fecha.find('-');
  size_t pos2 = fecha.rfind('-');
  if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2) {
    datos[numDatos].anio = stoi(fecha.substr(0, pos1));
    datos[numDatos].mes = stoi(fecha.substr(pos1 + 1, pos2 - pos1 - 1));
    datos[numDatos].dia = stoi(fecha.substr(pos2 + 1));
  } else {
    cerr << "Error al procesar la fecha." << endl;
    return;
  }

  // Leer la condición meteorológica
  cin.ignore(); // Ignorar el salto de línea
  cout << "Ingrese la condición meteorológica: ";
  getline(cin, datos[numDatos].condicionMeteorologica);

  // Incrementar el número de datos
  numDatos++;
}

// Función para imprimir los datos meteorológicos
void imprimirDatosMeteorologicos(const DatosMeteorologicos datos[],
                                 int numDatos) {
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
void encontrarRangos(int &anio1, int &mes1, int &dia1, int &anio2, int &mes2,
                     int &dia2) {
  cout << "Digite la primera fecha (en el formato AAAA MM DD): ";
  cin >> anio1 >> mes1 >> dia1;

  cout << "Digite la segunda fecha (en el formato AAAA MM DD): ";
  cin >> anio2 >> mes2 >> dia2;
}

// Función para encontrar temperatura máxima y mínima en un rango de fechas
void encontrarMaximaMinimaTemperatura(const DatosMeteorologicos datos[],
                                      int numDatos) {

  encontrarRangos(anio1, mes1, dia1, anio2, mes2, dia2);

  float tempMax = -9999.0;
  float tempMin = 9999.0;
  bool encontrada = false;

  for (int i = 0; i < numDatos; ++i) {
    if (datos[i].anio >= anio1 && datos[i].anio <= anio2 &&
        datos[i].mes >= mes1 && datos[i].mes <= mes2 &&
        datos[i].dia >= dia1 && datos[i].dia <= dia2) {
      if (datos[i].temperatura > tempMax) {
        tempMax = datos[i].temperatura;
      }
      if (datos[i].temperatura < tempMin) {
        tempMin = datos[i].temperatura;
      }
      encontrada = true;
    }
  }

  if (encontrada) {
    cout << "La temperatura máxima en el rango de fechas especificado es: "
         << tempMax << " grados Celsius." << endl;
    cout << "La temperatura mínima en el rango de fechas especificado es: "
         << tempMin << " grados Celsius." << endl;
  } else {
    cout << "No hay datos para el rango de fechas especificado." << endl;
  }
}

// Función para calcular el promedio de la temperatura en un mes especificado
void calcularPromedioTemperaturaMes(const DatosMeteorologicos datos[], int numDatos) {
  int mes, anio;
  cout << "Ingrese el mes y año (Formato MM AAAA): ";
  cin >> mes >> anio;

  float totalTemperatura = 0.0;
  int cantidadMediciones = 0;
  bool encontrada = false;

  for (int i = 0; i < numDatos; ++i) {
    if (datos[i].mes == mes && datos[i].anio == anio) {
      totalTemperatura += datos[i].temperatura;
      cantidadMediciones++;
      encontrada = true;
    }
  }

  if (encontrada) {
    float promedio = totalTemperatura / cantidadMediciones;
    cout << "El promedio de la temperatura en el mes " << mes << "/" << anio
         << " es: " << fixed << setprecision(2) << promedio << " grados Celsius."
         << endl;
  } else {
    cout << "No hay datos para el mes y año especificados." << endl;
  }
}

// Función para calcular el mayor promedio de humedad para una condición
// meteorológica específica
void calcularMayorPromedioHumedad(const DatosMeteorologicos datos[],
                                  int numDatos) {
  string condicion;
  cout << "Ingrese la condición meteorológica: ";
  cin >> condicion;

  int mes, anio;
  cout << "Ingrese el mes y año (Formato MM AAAA): ";
  cin >> mes >> anio;

  int totalHumedad = 0;
  int cantidadMediciones = 0;
  bool encontrado = false;
  float mayorPromedio = -1.0; // Inicializar con un valor muy bajo

  for (int i = 0; i < numDatos; ++i) {
    if (datos[i].condicionMeteorologica == condicion && datos[i].mes == mes &&
        datos[i].anio == anio) {
      totalHumedad += datos[i].humedad;
      cantidadMediciones++;
      encontrado = true;
    }
  }

  if (!encontrado) {
    cout << "No hay datos para la condición meteorológica, mes y año "
            "especificados."
         << endl;
    return;
  }

  float promedio = static_cast<float>(totalHumedad) / cantidadMediciones;
  if (promedio > mayorPromedio)
    mayorPromedio = promedio;

  cout << "El mayor promedio de humedad para la condición " << condicion
       << " en el mes " << mes << "/" << anio << " es: " << fixed
       << setprecision(2) << mayorPromedio << " %" << endl;
}

// Función para calcular el menor promedio de humedad para una condición
// meteorológica específica
void calcularMenorPromedioHumedad(const DatosMeteorologicos datos[],
                                  int numDatos) {
  string condicion;
  cout << "Ingrese la condición meteorológica: ";
  cin >> condicion;

  int mes, anio;
  cout << "Ingrese el mes y año (Formato MM AAAA): ";
  cin >> mes >> anio;

  int totalHumedad = 0;
  int cantidadMediciones = 0;
  bool encontrado = false;
  float menorPromedio = 9999.0; // Inicializar con un valor muy alto

  for (int i = 0; i < numDatos; ++i) {
    if (datos[i].condicionMeteorologica == condicion && datos[i].mes == mes &&
        datos[i].anio == anio) {
      totalHumedad += datos[i].humedad;
      cantidadMediciones++;
      encontrado = true;
    }
  }

  if (!encontrado) {
    cout << "No hay datos para la condición meteorológica, mes y año "
            "especificados."
         << endl;
    return;
  }

  float promedio = static_cast<float>(totalHumedad) / cantidadMediciones;
  if (promedio < menorPromedio)
    menorPromedio = promedio;

  cout << "El menor promedio de humedad para la condición " << condicion
       << " en el mes " << mes << "/" << anio << " es: " << fixed
       << setprecision(2) << menorPromedio << " %" << endl;
}

// Función para mostrar datos meteorológicos por rango de fechas
void mostrarDatosMeteorologicosPorRango(const DatosMeteorologicos datos[],
                                        int numDatos) {
  encontrarRangos(anio1, mes1, dia1, anio2, mes2, dia2);

  bool encontrada = false;

  cout << "Datos meteorológicos en el rango de fechas especificado:" << endl;
  for (int i = 0; i < numDatos; ++i) {
    if (datos[i].anio >= anio1 && datos[i].anio <= anio2 &&
        datos[i].mes >= mes1 && datos[i].mes <= mes2 &&
        datos[i].dia >= dia1 && datos[i].dia <= dia2) {
      cout << "Año: " << datos[i].anio << ", Mes: " << datos[i].mes
           << ", Día: " << datos[i].dia
           << ", Temperatura: " << datos[i].temperatura
           << ", Humedad: " << datos[i].humedad
           << ", Velocidad del viento: " << datos[i].velocidadViento
           << ", Presión atmosférica: " << datos[i].presionAtmosferica
           << ", Condición meteorológica: " << datos[i].condicionMeteorologica
           << endl;
      encontrada = true;
    }
  }

  if (!encontrada) {
    cout << "No hay datos para el rango de fechas especificado." << endl;
  }
}

int main() {
    DatosMeteorologicos datos[MAX_DATOS];
    int numDatos = 0;

    string nombreArchivo = "datos_meteorologicos.txt";

    if (leerDatosMeteorologicos(nombreArchivo, datos, numDatos) != 0) {
        return 1;
    }

    int opcion;
    do {
        // Menú de opciones
        cout << "Menú:" << endl;
        cout << "1. Mostrar datos meteorológicos" << endl;
        cout << "2. Encontrar temperatura máxima y mínima en un rango de fechas" << endl;
        cout << "3. Calcular promedio de temperatura en un mes especificado" << endl;
        cout << "4. Calcular mayor promedio de humedad con relacion a una condicion meteorologica" << endl;
        cout << "5. Calcular menor promedio de humedad con relacion a una condicion meteorologica" << endl;
        cout << "6. Mostrar datos meteorológicos por rango de fechas" << endl;
        cout << "7. Agregar datos meteorológicos" << endl;
        cout << "8. Salir" << endl;
        cout << "Ingrese su opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                imprimirDatosMeteorologicos(datos, numDatos);
                break;
            case 2:
                encontrarMaximaMinimaTemperatura(datos, numDatos);
                break;
            case 3:
                calcularPromedioTemperaturaMes(datos, numDatos);
                break;
            case 4:
                calcularMayorPromedioHumedad(datos, numDatos);
                break;
            case 5:
                calcularMenorPromedioHumedad(datos, numDatos);
                break;
            case 6:
                mostrarDatosMeteorologicosPorRango(datos, numDatos);
                break;
            case 7:
                agregarDatosMeteorologicos(datos, numDatos);
                break;
            case 8:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción no válida. Inténtelo de nuevo." << endl;
                break;
        }

    } while (opcion != 8);

    return 0;
}



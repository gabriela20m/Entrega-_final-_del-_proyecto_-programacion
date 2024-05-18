#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const int MAX_DATOS = 1000;

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

int leerDatosMeteorologicos(const string &nombreArchivo, DatosMeteorologicos datos[], int &numDatos,
                            int &anioMin, int &mesMin, int &diaMin,
                            int &anioMax, int &mesMax, int &diaMax) {
    ifstream archivo(nombreArchivo);

    if (!archivo) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return 1;
    }

    string encabezado;
    getline(archivo, encabezado);

    anioMin = 9999;
    mesMin = 12;
    diaMin = 31;
    anioMax = 0;
    mesMax = 1;
    diaMax = 1;

    string linea;
    while (numDatos < MAX_DATOS && getline(archivo, linea)) {
        istringstream iss(linea);
        string fecha;

        if (!(iss >> fecha >> datos[numDatos].temperatura >>
              datos[numDatos].humedad >> datos[numDatos].velocidadViento >>
              datos[numDatos].presionAtmosferica)) {
            cerr << "Error al leer los datos en la línea " << numDatos + 2 << endl;
            continue;
        }

        size_t pos1 = fecha.find('-');
        size_t pos2 = fecha.rfind('-');
        if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2) {
            datos[numDatos].anio = stoi(fecha.substr(0, pos1));
            datos[numDatos].mes = stoi(fecha.substr(pos1 + 1, pos2 - pos1 - 1));
            datos[numDatos].dia = stoi(fecha.substr(pos2 + 1));

            if (datos[numDatos].anio < anioMin ||
                (datos[numDatos].anio == anioMin && datos[numDatos].mes < mesMin) ||
                (datos[numDatos].anio == anioMin && datos[numDatos].mes == mesMin && datos[numDatos].dia < diaMin)) {
                anioMin = datos[numDatos].anio;
                mesMin = datos[numDatos].mes;
                diaMin = datos[numDatos].dia;
            }
            if (datos[numDatos].anio > anioMax ||
                (datos[numDatos].anio == anioMax && datos[numDatos].mes > mesMax) ||
                (datos[numDatos].anio == anioMax && datos[numDatos].mes == mesMax && datos[numDatos].dia > diaMax)) {
                anioMax = datos[numDatos].anio;
                mesMax = datos[numDatos].mes;
                diaMax = datos[numDatos].dia;
            }
        } else {
            cerr << "Error al procesar la fecha en la línea " << numDatos + 2 << endl;
            continue;
        }

        getline(iss, datos[numDatos].condicionMeteorologica);
        if (!datos[numDatos].condicionMeteorologica.empty() &&
            datos[numDatos].condicionMeteorologica[0] == ' ') {
            datos[numDatos].condicionMeteorologica = datos[numDatos].condicionMeteorologica.substr(1);
        }

        numDatos++;
    }

    archivo.close();
    return 0;
}

bool fechaValida(int anio, int mes, int dia, int anioMin, int mesMin, int diaMin, int anioMax, int mesMax, int diaMax) {
    if (anio < anioMin || anio > anioMax) return false;
    if (anio == anioMin && (mes < mesMin || (mes == mesMin && dia < diaMin))) return false;
    if (anio == anioMax && (mes > mesMax || (mes == mesMax && dia > diaMax))) return false;
    return true;
}

void encontrarRangos(int &anio1, int &mes1, int &dia1, int &anio2, int &mes2, int &dia2,
                     int anioMin, int mesMin, int diaMin, int anioMax, int mesMax, int diaMax) {
    bool fechasValidas = false;

    while (!fechasValidas) {
        cout << "Digite la primera fecha (en el formato AAAA MM DD): ";
        cin >> anio1 >> mes1 >> dia1;

        cout << "Digite la segunda fecha (en el formato AAAA MM DD): ";
        cin >> anio2 >> mes2 >> dia2;

        if (fechaValida(anio1, mes1, dia1, anioMin, mesMin, diaMin, anioMax, mesMax, diaMax) &&
            fechaValida(anio2, mes2, dia2, anioMin, mesMin, diaMin, anioMax, mesMax, diaMax) &&
            (anio1 < anio2 || (anio1 == anio2 && (mes1 < mes2 || (mes1 == mes2 && dia1 <= dia2))))) {
            fechasValidas = true;
        } else {
            cout << "Las fechas ingresadas están fuera del rango de datos disponibles (" 
                 << anioMin << "-" << mesMin << "-" << diaMin << " a " 
                 << anioMax << "-" << mesMax << "-" << diaMax << "). Por favor, ingrese nuevamente.\n";
        }
    }
}

bool fechaEnRango(int anio, int mes, int dia, int anioInicio, int mesInicio, int diaInicio, int anioFin, int mesFin, int diaFin) {
    if (anio < anioInicio || anio > anioFin) return false;
    if (anio == anioInicio && (mes < mesInicio || (mes == mesInicio && dia < diaInicio))) return false;
    if (anio == anioFin && (mes > mesFin || (mes == mesFin && dia > diaFin))) return false;
    return true;
}

void imprimirDatosMeteorologicos(const DatosMeteorologicos datos[], int numDatos) {
    cout << left << setw(10) << "Fecha" << setw(15) << "Temperatura" << setw(10) << "Humedad"
         << setw(15) << "Vel. Viento" << setw(20) << "Presión Atmosférica" << "Condición Meteorológica" << endl;
    for (int i = 0; i < numDatos; ++i) {
        cout << datos[i].anio << "-" << setw(2) << setfill('0') << datos[i].mes << "-" << setw(2) << setfill('0') << datos[i].dia << setfill(' ')
             << setw(15) << datos[i].temperatura << setw(10) << datos[i].humedad
             << setw(15) << datos[i].velocidadViento << setw(20) << datos[i].presionAtmosferica
             << datos[i].condicionMeteorologica << endl;
    }
}

void encontrarMaximaTemperatura(const DatosMeteorologicos datos[], int numDatos, int anioMin, int mesMin, int diaMin, int anioMax, int mesMax, int diaMax) {
    int anio1, mes1, dia1;
    int anio2, mes2, dia2;

    encontrarRangos(anio1, mes1, dia1, anio2, mes2, dia2, anioMin, mesMin, diaMin, anioMax, mesMax, diaMax);

    float tempMax = -9999.0;
    bool encontrada = false;

    for (int i = 0; i < numDatos; ++i) {
        if (fechaEnRango(datos[i].anio, datos[i].mes, datos[i].dia, anio1, mes1, dia1, anio2, mes2, dia2)) {
            if (datos[i].temperatura > tempMax) {
                tempMax = datos[i].temperatura;
                encontrada = true;
            }
        }
    }

    if (encontrada) {
        cout << "La temperatura máxima en el rango de fechas especificado es: " << tempMax << " C°." << endl;
    } else {
        cout << "No hay datos para el rango de fechas especificado." << endl;
    }
}

void encontrarMinimaTemperatura(const DatosMeteorologicos datos[], int numDatos, int anioMin, int mesMin, int diaMin, int anioMax, int mesMax, int diaMax) {
    int anio1, mes1, dia1;
    int anio2, mes2, dia2;

    encontrarRangos(anio1, mes1, dia1, anio2, mes2, dia2, anioMin, mesMin, diaMin, anioMax, mesMax, diaMax);

    float tempMin = 9999.0;
    bool encontrada = false;

    for (int i = 0; i < numDatos; ++i) {
        if (fechaEnRango(datos[i].anio, datos[i].mes, datos[i].dia, anio1, mes1, dia1, anio2, mes2, dia2)) {
            if (datos[i].temperatura < tempMin) {
                tempMin = datos[i].temperatura;
                encontrada = true;
            }
        }
    }

    if (encontrada) {
        cout << "La temperatura mínima en el rango de fechas especificado es: " << tempMin << " C°." << endl;
    } else {
        cout << "No hay datos para el rango de fechas especificado." << endl;
    }
}

void calcularPromedioTemperaturaMes(const DatosMeteorologicos datos[], int numDatos) {
    int mes, anio;
    cout << "Ingrese el mes y año (Formato MM AAAA): ";
    cin >> mes >> anio;

    float totalTemperatura = 0;
    int cantidadMediciones = 0;

    for (int i = 0; i < numDatos; ++i) {
        if (datos[i].anio == anio && datos[i].mes == mes) {
            totalTemperatura += datos[i].temperatura;
            cantidadMediciones++;
        }
    }

    if (cantidadMediciones > 0) {
        float promedioTemperatura = totalTemperatura / cantidadMediciones;
        cout << "El promedio de temperatura para " << mes << "/" << anio << " es: " << fixed << setprecision(2) << promedioTemperatura << " C°." << endl;
    } else {
        cout << "No hay datos disponibles para el mes y año especificados." << endl;
    }
}


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


void calcularMenorPromedioHumedad(const DatosMeteorologicos datos[], int numDatos) {
  string condicion;
  cout << "Ingrese la condición meteorológica: ";
  cin >> condicion;

  int mes, anio;
  cout << "Ingrese el mes y año (Formato MM AAAA) Ejemplo : ";
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

void mostrarDatosMeteorologicosPorRango(const DatosMeteorologicos datos[], int numDatos, int anioMin, int mesMin, int diaMin, int anioMax, int mesMax, int diaMax) {
    int anio1, mes1, dia1;
    int anio2, mes2, dia2;

    encontrarRangos(anio1, mes1, dia1, anio2, mes2, dia2, anioMin, mesMin, diaMin, anioMax, mesMax, diaMax);

    cout << left << setw(10) << "Fecha" << setw(15) << "Temperatura" << setw(10) << "Humedad"
         << setw(15) << "Vel. Viento" << setw(20) << "Presión Atmosférica" << "Condición Meteorológica" << endl;

    for (int i = 0; i < numDatos; ++i) {
        if (fechaEnRango(datos[i].anio, datos[i].mes, datos[i].dia, anio1, mes1, dia1, anio2, mes2, dia2)) {
            cout << datos[i].anio << "-" << setw(2) << setfill('0') << datos[i].mes << "-" << setw(2) << setfill('0') << datos[i].dia << setfill(' ')
                 << setw(15) << datos[i].temperatura << setw(10) << datos[i].humedad
                 << setw(15) << datos[i].velocidadViento << setw(20) << datos[i].presionAtmosferica
                 << datos[i].condicionMeteorologica << endl;
        }
    }
}

void agregarDatosMeteorologicos(DatosMeteorologicos datos[], int &numDatos, int anioMin, int mesMin, int diaMin, int anioMax, int mesMax, int diaMax) {
    if (numDatos >= MAX_DATOS) {
        cout << "No se pueden agregar más datos, se ha alcanzado el máximo permitido." << endl;
        return;
    }

    DatosMeteorologicos nuevoDato;

    cout << "Ingrese la fecha (AAAA MM DD): ";
    cin >> nuevoDato.anio >> nuevoDato.mes >> nuevoDato.dia;

    if (!fechaValida(nuevoDato.anio, nuevoDato.mes, nuevoDato.dia, anioMin, mesMin, diaMin, anioMax, mesMax, diaMax)) {
        cout << "Fecha fuera del rango permitido." << endl;
        return;
    }

    cout << "Ingrese la temperatura: ";
    cin >> nuevoDato.temperatura;
    cout << "Ingrese la humedad: ";
    cin >> nuevoDato.humedad;
    cout << "Ingrese la velocidad del viento: ";
    cin >> nuevoDato.velocidadViento;
    cout << "Ingrese la presión atmosférica: ";
    cin >> nuevoDato.presionAtmosferica;
    cout << "Ingrese la condición meteorológica: ";
    cin.ignore();
    getline(cin, nuevoDato.condicionMeteorologica);

    datos[numDatos] = nuevoDato;
    numDatos++;

    cout << "Datos meteorológicos agregados exitosamente." << endl;
}

bool continuarPrograma() {
  char respuesta;
  while (true) {
    cout << "¿Desea seguir operando? (s/n): ";
    cin >> respuesta;
    respuesta = tolower(respuesta); // Convertir a minúscula para hacer la
                                    // comparación y evitar errores

    if (respuesta == 's') {
      return true;
    } else if (respuesta == 'n') {
      return false;
      break;
    } else {
      cout << "Respuesta no válida. Por favor, responda 's' para sí o 'n' para "
              "no."
           << endl;
    }
  }
}


int main() {
    string nombreArchivo;
    DatosMeteorologicos datos[MAX_DATOS];
    int numDatos = 0;
    int anioMin, mesMin, diaMin, anioMax, mesMax, diaMax;

    cout << "datos.meteorologicos.txt: ";
    getline(cin, nombreArchivo);

    if (leerDatosMeteorologicos(nombreArchivo, datos, numDatos, anioMin, mesMin, diaMin, anioMax, mesMax, diaMax) != 0) {
        return 1;
    }

    int opcion;
    do {
    cout << "|---------------------------------------------------------------------------|"<< endl;
    cout << " ------------------------MENU DATOS METEOROLOGICOS----------------------------" << endl;
    cout << "|---------------------------------------------------------------------------|" << endl;
          
    cout << "1. Mostrar datos meteorológicos" << endl;
    cout << "________________________________________________________________________________"<< endl;
    cout << "2. Encontrar temperatura máxima en un rango de fechas"<< endl;
    cout << "________________________________________________________________________________"<< endl;
    cout << "3. Encontrar temperatura mínima en un rango de fechas"<< endl;
    cout << "________________________________________________________________________________"<< endl;
    cout << "4. Calcular promedio de temperatura en un mes especificado"<< endl;
    cout << "________________________________________________________________________________"<< endl;
    cout << "5. Calcular mayor promedio de humedad con relacion a una condicion meteorologica"<< endl;
    cout << "________________________________________________________________________________"<< endl;
    cout << "5. Calcular menor promedio de humedad con relacion a una condicion meteorologica"<< endl;
    cout << "________________________________________________________________________________"<< endl;
    cout << "6. Mostrar datos meteorológicos por rango de fechas" << endl;
    cout << "________________________________________________________________________________"<< endl;
    cout << "7. Agregar datos meteorológicos" << endl;
    cout << "________________________________________________________________________________"<< endl;
    cout << "8. Salir" << endl;
    cout << "________________________________________________________________________________"<< endl;
    cout << "Ingrese su opción: ";
    cin >> opcion;

 switch (opcion) {
    case 1:
      imprimirDatosMeteorologicos(datos, numDatos);

      break;
    case 2:
      encontrarMaximaTemperatura(datos, numDatos, anioMin, mesMin, diaMin, anioMax, mesMax, diaMax);

       break;
    case 3:
        encontrarMinimaTemperatura(datos, numDatos, anioMin, mesMin, diaMin, anioMax, mesMax, diaMax);

      break;
    case 4:
      calcularPromedioTemperaturaMes(datos, numDatos);

      break;
    case 5:
      calcularMayorPromedioHumedad(datos, numDatos);

      break;
    case 6:
      calcularMenorPromedioHumedad(datos, numDatos);

      break;
    case 7:
      mostrarDatosMeteorologicosPorRango(datos, numDatos, anioMin, mesMin, diaMin, anioMax, mesMax, diaMax);

      break;
    case 8:
      agregarDatosMeteorologicos(datos, numDatos, anioMin, mesMin, diaMin, anioMax, mesMax, diaMax);

      break;
    case 9:
      cout << "Saliendo..." << endl;
      break;
    default:
      cout << "Opción no válida. Inténtelo de nuevo." << endl;
      break;
    }
    if (!continuarPrograma()) {
      cout << "Gracias por usar el programa. ¡Hasta luego!" << endl;
      return 1; // Sale inmediatamente de la función menu
    }

  } while (opcion != 8);

  return 0;
}












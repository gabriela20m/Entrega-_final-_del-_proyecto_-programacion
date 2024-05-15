#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

const int MAX_DATOS = 1000;

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

// Función para escribir los datos meteorológicos en un archivo de texto
void escribirDatosMeteorologicos(const string& nombreArchivo, const DatosMeteorologicos datos[], int numDatos)
{
    ofstream archivo(nombreArchivo);

    // Verificar si el archivo se abrió correctamente
    if (!archivo)
    {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    // Escribir los datos meteorológicos en el archivo
    for (int i = 0; i < numDatos; ++i)
    {
        archivo << datos[i].anio << " " << datos[i].mes << " " << datos[i].dia << " "
                << datos[i].temperatura << " " << datos[i].humedad << " "
                << datos[i].velocidadViento << " " << datos[i].presionAtmosferica << " " << datos[i].condicionMeteorologica << endl;
    }

    // Cerrar el archivo
    archivo.close();

    // Mostrar mensaje de éxito
    cout << "Datos meteorológicos escritos en el archivo de texto: " << nombreArchivo << endl;
}

// Función para encontrar la temperatura máxima y mínima en un rango de fechas
void encontrarMaximaMinimaTemperatura(const string& nombreArchivo)
{
    int anio1, mes1, dia1;
    int anio2, mes2, dia2;
    
    cout << "Digite la primera fecha (en el formato AAAA MM DD): ";
    cin >> anio1 >> mes1 >> dia1;

    cout << "Digite la segunda fecha (en el formato AAAA MM DD): ";
    cin >> anio2 >> mes2 >> dia2;

    ifstream archivoLectura(nombreArchivo);
    if (!archivoLectura)
    {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return;
    }

    DatosMeteorologicos datoLeido;
    bool encontrado = false;

    float temperaturaMaxima = -9999.0; // Inicializar con un valor muy bajo
    float temperaturaMinima = 9999.0; // Inicializar con un valor muy alto

    // Leer y encontrar las temperaturas máxima y mínima en el rango de fechas
    while (archivoLectura >> datoLeido.anio >> datoLeido.mes >> datoLeido.dia
                          >> datoLeido.temperatura >> datoLeido.humedad >> datoLeido.velocidadViento
                          >> datoLeido.presionAtmosferica >> datoLeido.condicionMeteorologica)
    {
        if ((datoLeido.anio > anio1 || (datoLeido.anio == anio1 && datoLeido.mes > mes1) ||
             (datoLeido.anio == anio1 && datoLeido.mes == mes1 && datoLeido.dia >= dia1)) &&
            (datoLeido.anio < anio2 || (datoLeido.anio == anio2 && datoLeido.mes < mes2) ||
             (datoLeido.anio == anio2 && datoLeido.mes == mes2 && datoLeido.dia <= dia2)))
        {
            encontrado = true;

            if (datoLeido.temperatura > temperaturaMaxima)
                temperaturaMaxima = datoLeido.temperatura;

            if (datoLeido.temperatura < temperaturaMinima)
                temperaturaMinima = datoLeido.temperatura;
        }
    }

    archivoLectura.close();

    if (!encontrado)
    {
        cout << "No se encontraron datos para el rango de fechas ingresado." << endl;
        return;
    }

    cout << "Temperatura máxima en el rango de fechas: " << temperaturaMaxima << " C" << endl;
    cout << "Temperatura mínima en el rango de fechas: " << temperaturaMinima << " C" << endl;
}

// Función para mostrar los datos meteorológicos en un rango de fechas
void mostrarDatosPorRango(const string& nombreArchivo)
{
    int anio1, mes1, dia1;
    int anio2, mes2, dia2;

    cout << "Digite la primera fecha (en el formato AAAA MM DD): ";
    cin >> anio1 >> mes1 >> dia1;

    cout << "Digite la segunda fecha (en el formato AAAA MM DD): ";
    cin >> anio2 >> mes2 >> dia2;

    ifstream archivoLectura(nombreArchivo);
    if (!archivoLectura)
    {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return;
    }

    DatosMeteorologicos datoLeido;
    bool encontrado = false;

    cout << "Datos meteorológicos para el rango de fechas " << anio1 << "-" << mes1 << "-" << dia1
         << " hasta " << anio2 << "-" << mes2 << "-" << dia2 << ":" << endl;

    // Leer y mostrar los datos correspondientes al rango de fechas ingresado
    while (archivoLectura >> datoLeido.anio >> datoLeido.mes >> datoLeido.dia
                          >> datoLeido.temperatura >> datoLeido.humedad >> datoLeido.velocidadViento
                          >> datoLeido.presionAtmosferica >> datoLeido.condicionMeteorologica)
    {  
        if ((datoLeido.anio > anio1 || (datoLeido.anio == anio1 && datoLeido.mes > mes1) ||
             (datoLeido.anio == anio1 && datoLeido.mes == mes1 && datoLeido.dia >= dia1)) &&
            (datoLeido.anio < anio2 || (datoLeido.anio == anio2 && datoLeido.mes < mes2) ||
             (datoLeido.anio == anio2 && datoLeido.mes == mes2 && datoLeido.dia <= dia2)))
        {
            encontrado = true;
            cout << "Fecha: " << datoLeido.anio << "-" << datoLeido.mes << "-" << datoLeido.dia << endl;
            cout << "Temperatura (C): " << datoLeido.temperatura << endl;
            cout << "Humedad (%): " << datoLeido.humedad << endl;
            cout << "Velocidad del Viento (km/h): " << datoLeido.velocidadViento << endl;
            cout << "Presión Atmosférica (hPa): " << datoLeido.presionAtmosferica << endl;
            cout << "Condición Meteorológica: " << datoLeido.condicionMeteorologica << endl;
            cout << "--------------------------" << endl;
        }
    }

    archivoLectura.close();

    if (!encontrado)
    {
        cout << "No se encontraron datos para el rango de fechas ingresado." << endl;
        return;
    }
}

// Función para agregar nuevos datos meteorológicos al archivo de texto
void agregarDatosMeteorologicos(const string& nombreArchivo)
{
    DatosMeteorologicos nuevoDato;                  

    cout << "Digite la fecha (en el formato AAAA MM DD): ";
    cin >> nuevoDato.anio >> nuevoDato.mes >> nuevoDato.dia;

    cout << "Digite la temperatura (C): ";
    cin >> nuevoDato.temperatura;

    cout << "Digite la humedad (%): ";
    cin >> nuevoDato.humedad;

    cout << "Digite la velocidad del viento (km/h): ";
    cin >> nuevoDato.velocidadViento;

    cout << "Digite la presión atmosférica (hPa): ";
    cin >> nuevoDato.presionAtmosferica;

    cout << "Digite la condición meteorológica: ";
    cin >> nuevoDato.condicionMeteorologica;

    ofstream archivo(nombreArchivo, ios::app);

    if (!archivo)
    {
        cerr << "Error al abrir el archivo para escritura." << endl;
        return;
    }

    archivo << nuevoDato.anio << " " << nuevoDato.mes << " " << nuevoDato.dia << " "
            << nuevoDato.temperatura << " " << nuevoDato.humedad << " "
            << nuevoDato.velocidadViento << " " << nuevoDato.presionAtmosferica << " " << nuevoDato.condicionMeteorologica << endl;

    archivo.close();
    cout << "Datos meteorológicos agregados correctamente." << endl;
}

// Función para calcular el promedio de temperatura para un mes específico
void calcularPromedioTemperaturaPorMes(const string& nombreArchivo)
{
    int mes;
    cout << "Ingrese el número de mes para calcular el promedio de temperatura: ";
    cin >> mes;

    ifstream archivo(nombreArchivo);
    if (!archivo)
    {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return;
    }

    int totalTemperaturas = 0;
    int cantidadDias = 0;
    float temperatura;
    bool encontrado = false;

    // Leer y encontrar las temperaturas correspondientes al mes especificado
    while (archivo >> temperatura)
    {
        int anio, mes, dia;
        archivo >> anio >> mes >> dia; // Leer la fecha pero no almacenarla en ninguna variable
        if (mes == mes)
        {
            totalTemperaturas += temperatura;
            cantidadDias++;
            encontrado = true;
        }
    }

    archivo.close();

    if (!encontrado)
    {
        cout << "No hay datos para el mes especificado." << endl;
        return;
    }

    float promedio = totalTemperaturas / static_cast<float>(cantidadDias);
    cout << "El promedio de temperatura para el mes " << mes << " es: " << fixed << setprecision(2) << promedio << " C" << endl;
}

// Función para calcular el promedio de humedad para una condición meteorológica específica
void calcularPromedioHumedadPorCondicion(const string& nombreArchivo)
{
    string condicion;
    cout << "Ingrese la condición meteorológica para calcular el promedio de humedad: ";
    cin >> condicion;

    ifstream archivo(nombreArchivo);
    if (!archivo)
    {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return;
    }

    int totalHumedad = 0;
    int cantidadMediciones = 0;
    int humedad;
    string condicionLeida;
    bool encontrado = false;

    // Leer y encontrar las humedades correspondientes a la condición meteorológica especificada
    while (archivo >> humedad)
    {
        int anio, mes, dia;
        archivo >> anio >> mes >> dia; // Leer la fecha pero no almacenarla en ninguna variable
        getline(archivo, condicionLeida); // Leer la condición meteorológica
        if (condicionLeida == condicion)
        {
            totalHumedad += humedad;
            cantidadMediciones++;
            encontrado = true;
        }
    }

    archivo.close();

    if (!encontrado)
    {
        cout << "No hay datos para la condición meteorológica especificada." << endl;
        return;
    }

    float promedio = totalHumedad / static_cast<float>(cantidadMediciones);
    cout << "El promedio de humedad para la condición " << condicion << " es: " << fixed << setprecision(2) << promedio << " %" << endl;
}

// Función para calcular el mayor promedio de humedad en relación a una condición meteorológica
void calcularMayorPromedioHumedad(const string& nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    if (!archivo)
    {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return;
    }

    string condicion;
    string mejorCondicion;
    float mejorPromedio = -1; // Inicializar con un valor muy bajo

    // Leer y encontrar la condición meteorológica con el mayor promedio de humedad
    while (archivo >> condicion)
    {
        int humedad, anio, mes, dia;
        archivo >> humedad >> anio >> mes >> dia; // Leer la humedad y la fecha pero no almacenarlas
        float totalHumedad = 0;
        int cantidadMediciones = 0;
        string condicionLeida;
        while (getline(archivo, condicionLeida))
        {
            if (condicionLeida == condicion)
            {
                totalHumedad += humedad;
                cantidadMediciones++;
            }
        }
        float promedio = totalHumedad / cantidadMediciones;
        if (promedio > mejorPromedio)
        {
            mejorPromedio = promedio;
            mejorCondicion = condicion;
        }
    }

    archivo.close();

    if (mejorPromedio == -1)
    {
        cout << "No hay datos para calcular el promedio de humedad." << endl;
    }
    else
    {
        cout << "La condición meteorológica con el mayor promedio de humedad es: " << mejorCondicion
             << " con un promedio de " << fixed << setprecision(2) << mejorPromedio << " %" << endl;
    }
}

// Función para calcular el menor promedio de humedad en relación a una condición meteorológica
void calcularMenorPromedioHumedad(const string& nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    if (!archivo)
    {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return;
    }

    string condicion;
    string peorCondicion;
    float peorPromedio = 101; // Inicializar con un valor muy alto

    // Leer y encontrar la condición meteorológica con el menor promedio de humedad
    while (archivo >> condicion)
    {
        int humedad, anio, mes, dia;
        archivo >> humedad >> anio >> mes >> dia; // Leer la humedad y la fecha pero no almacenarlas
        float totalHumedad = 0;
        int cantidadMediciones = 0;
        string condicionLeida;
        while (getline(archivo, condicionLeida))
        {
            if (condicionLeida == condicion)
            {
                totalHumedad += humedad;
                cantidadMediciones++;
            }
        }
        float promedio = totalHumedad / cantidadMediciones;
        if (promedio < peorPromedio)
        {
            peorPromedio = promedio;
            peorCondicion = condicion;
        }
    }

    archivo.close();

    if (peorPromedio == 101)
    {
        cout << "No hay datos para calcular el promedio de humedad." << endl;
    }
    else
    {
        cout << "La condición meteorológica con el menor promedio de humedad es: " << peorCondicion
             << " con un promedio de " << fixed << setprecision(2) << peorPromedio << " %" << endl;
    }
}

int main()
{
    string nombreArchivo = "datos_metorologicos.txt";
    DatosMeteorologicos datos[MAX_DATOS];
    int numDatos = 0;

    // Leer los datos meteorológicos desde el archivo
    if (leerDatosMeteorologicos(nombreArchivo, datos, numDatos) != 0)
    {
        return 1;
    }

    int opcion;
    do
    {
        cout << "\nMenú:" << endl;
        cout << "1. Mostrar datos meteorológicos" << endl;
        cout << "2. Agregar nuevos datos meteorológicos" << endl;
        cout << "3. Calcular promedio de temperatura para un mes" << endl;
        cout << "4. Calcular promedio de humedad para una condición meteorológica" << endl;
        cout << "5. Encontrar temperatura máxima y mínima en un rango de fechas" << endl;
        cout << "6. Mostrar datos meteorológicos por un rango de fechas" << endl;
        cout << "7. Calcular el mayor promedio de humedad en relación a una condición meteorológica" << endl;
        cout << "8. Calcular el menor promedio de humedad en relación a una condición meteorológica" << endl;
        cout << "9. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            // Lógica para mostrar datos meteorológicos
            imprimirDatosMeteorologicos(datos, numDatos);
            break;
        case 2:
            // Lógica para agregar nuevos datos meteorológicos
            agregarDatosMeteorologicos(nombreArchivo);
            break;
        case 3:
            // Lógica para calcular promedio de temperatura para un mes
            calcularPromedioTemperaturaPorMes(nombreArchivo);
            break;
        case 4:
            // Lógica para calcular promedio de humedad para una condición meteorológica
            calcularPromedioHumedadPorCondicion(nombreArchivo);
            break;
        case 5:
            // Lógica para encontrar temperatura máxima y mínima en un rango de fechas
            encontrarMaximaMinimaTemperatura(nombreArchivo);
            break;
        case 6:
            // Lógica para mostrar datos meteorológicos por un rango de fechas
            mostrarDatosPorRango(nombreArchivo);
            break;
        case 7:
            // Lógica para calcular el mayor promedio de humedad en relación a una condición meteorológica
            calcularMayorPromedioHumedad(nombreArchivo);
            break;
        case 8:
            // Lógica para calcular el menor promedio de humedad en relación a una condición meteorológica
            calcularMenorPromedioHumedad(nombreArchivo);
            break;
        case 9:
            // Salir
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opción no válida. Por favor, seleccione una opción del menú." << endl;
            break;
        }
    } while (opcion != 9);

    return 0;
}



//Progrma del codi
// El prpmedio de temperatura y de humedad con una condicion meteorologica 
// Funcional con los condicionales por ahora solo hasta el 4 :)
        
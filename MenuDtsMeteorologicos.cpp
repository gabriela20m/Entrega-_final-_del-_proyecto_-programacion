#include <iostream>
#include <fstream>
#include <string>

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

// Función para escribir los datos meteorológicos en un archivo de texto
void escribirDatosMeteorologicos(const string& nombreArchivo)
{
    ofstream archivo(nombreArchivo);

    // Verificar si el archivo se abrió correctamente
    if (!archivo)
    {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

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

    // Escribir los datos meteorológicos en el archivo
    for (const auto& dato : datos)
    {
        archivo << dato.anio << " " << dato.mes << " " << dato.dia << " "
                << dato.temperatura << " " << dato.humedad << " "
                << dato.velocidadViento << " " << dato.presionAtmosferica << " " << dato.condicionMeteorologica << endl;
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
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    archivo << nuevoDato.anio << " " << nuevoDato.mes << " " << nuevoDato.dia << " "
            << nuevoDato.temperatura << " " << nuevoDato.humedad << " "
            << nuevoDato.velocidadViento << " " << nuevoDato.presionAtmosferica << " "
            << nuevoDato.condicionMeteorologica << endl;

    archivo.close();

    cout << "Datos meteorológicos agregados correctamente." << endl;
}

// Función para calcular el promedio de temperatura durante un mes determinado
void calcularPromedioTemperatura(const string& nombreArchivo)
{                                                                  //aqui e calcula el promedio de temperatura teniendo todas las temperauras
    int anio, mes;                                                  //y los dias que es el contador se divide y se saca el promedio
                                                                
    cout << "Digite el año y el mes (en el formato AAAA MM): ";
    cin >> anio >> mes;

    ifstream archivoLectura(nombreArchivo);
    if (!archivoLectura)
    {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return;
    }

    DatosMeteorologicos datoLeido;
    int contador = 0;
    float sumaTemperatura = 0;

    while (archivoLectura >> datoLeido.anio >> datoLeido.mes >> datoLeido.dia
                          >> datoLeido.temperatura >> datoLeido.humedad >> datoLeido.velocidadViento
                          >> datoLeido.presionAtmosferica >> datoLeido.condicionMeteorologica)
    {
        if (datoLeido.anio == anio && datoLeido.mes == mes)
        {
            sumaTemperatura += datoLeido.temperatura;
            contador++;
        }
    }

    archivoLectura.close();

    if (contador == 0)
    {
        cout << "No hay datos de temperatura para el mes y año ingresados." << endl;
    }
    else
    {
        float promedio = sumaTemperatura / contador;
        cout << "El promedio de temperatura para " << mes << "/" << anio << " es: " << promedio << " C" << endl;
    }
}

// Función para calcular el promedio de humedad en relación con una condición meteorológica dada
void calcularPromedioHumedad(const string& nombreArchivo)
{
    string condicion;                                 // Aqui se calcula el promedio de humedad teniendo encuenta el total de humedad
                                                    // y el contador que son los dias por dodne recorre ese contador
    cout << "Digite la condición meteorológica: ";
    cin >> condicion;

    ifstream archivoLectura(nombreArchivo);
    if (!archivoLectura)
    {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return;
    }

    DatosMeteorologicos datoLeido;
    int contador = 0;
    float sumaHumedad = 0;

    while (archivoLectura >> datoLeido.anio >> datoLeido.mes >> datoLeido.dia
                          >> datoLeido.temperatura >> datoLeido.humedad >> datoLeido.velocidadViento
                          >> datoLeido.presionAtmosferica >> datoLeido.condicionMeteorologica)
    {
        if (datoLeido.condicionMeteorologica == condicion)
        {
            sumaHumedad += datoLeido.humedad;
            contador++;
        }
    }

    archivoLectura.close();

    if (contador == 0)
    {
        cout << "No hay datos de humedad para la condición meteorológica ingresada." << endl;
    }
    else
    {
        float promedio = sumaHumedad / contador;
        cout << "El promedio de humedad para la condición meteorológica " << condicion << " es: " << promedio << "%" << endl;
    }
}

int main()
{
    const string nombreArchivo = "datos_meteorologicos.txt";

    // Escribir los datos meteorológicos en un archivo si no existe
    escribirDatosMeteorologicos(nombreArchivo);

    // Opción del menú
    int opcion;

    do
    {
        // Menú principal}
        cout <<  "-------:3 Menu datos meteorologicos :)-------" << endl;
        cout << "1. Mostrar datos por rango de fechas" << endl;
        cout << "2. Agregar nuevo dato meteorológico" << endl;
        cout << "3. Ver máxima y mínima temperatura en un rango específico" << endl;
        cout << "4. Calcular promedio de temperatura durante un mes determinado" << endl;
        cout << "5. Calcular promedio de humedad en relación con una condición meteorológica dada" << endl;
        cout << "6. Salir" << endl;

        // Selección de opción
        cout << "Seleccione una opción: ";
        cin >> opcion;

        // Ejecutar la opción seleccionada
        switch (opcion)
        {
            case 1:
                mostrarDatosPorRango(nombreArchivo); // llama a la funcio para bsucar datos de un rango de fecha
                break;
            case 2:
                agregarDatosMeteorologicos(nombreArchivo); // Llama a la funcion para agregar nuevos datos en la base de dats
                break;
            case 3:
                encontrarMaximaMinimaTemperatura(nombreArchivo); // LLama a la funcio par hallar la Max y min de temperatura
                break;
            case 4:
                calcularPromedioTemperatura(nombreArchivo); // Llma a la funcion para hallar el promedio de temperatura
                break;
            case 5:
                calcularPromedioHumedad(nombreArchivo); // Llama a la funcion para hallar el promedio de humedad
                break;
            case 6:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida. Inténtelo de nuevo." << endl;
                break;
        }
    } while (opcion != 6);

    return 0;
}


//Codigo del menu de los datos meteriologicos dodeen calcula la maxima minima temperatura 
// El prpmedio de temperatura y de humedad con una condicion meteorologica 
// Funcional con los condicionales por ahora solo hasta el 4 :)
        
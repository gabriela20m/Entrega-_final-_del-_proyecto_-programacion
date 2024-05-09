#include <iostream>   // Inclusión de la biblioteca estándar para entrada/salida
#include <fstream>    // Inclusión de la biblioteca estándar para operaciones de archivo
#include <iomanip>    // Inclusión de la biblioteca estándar para manipulación de formato de salida
#include <cstdlib>    // Inclusión de la biblioteca estándar para funciones de utilidad
#include <cstring>    // Inclusión de la biblioteca estándar para operaciones de cadena de caracteres
// Info de personas pero ahora con mas opciones en el menu
using namespace std;

// Definicion de la estructura persona
struct Persona
{
    char nombre[45];        // Nombre de la persona
    char apellido[30];      // Apellido de la persona
    char apellido2[30];     // Segundo apellido de la persona
    long cedula;            // Cédula de la persona
};

// Función para mostrar el menú y obtener la opción del usuario
int menu()
{
    int x = 0; // Almacenar la opcion del usuario

    cout << "1. Agregar" << endl;   // Mostrar opción para agregar
    cout << "2. Listar" << endl;     // Mostrar opción para listar
    cout << "3. Buscar" << endl;     // Mostrar opción para buscar
    cout << "4. Eliminar" << endl;   // Mostrar opción para eliminar
    cout << "5. Modificar" << endl;  // Mostrar opción para modificar
    cout << "6. Salir" << endl;      // Mostrar opción para salir
    cout << "Opción: ";              // Pedir al usuario que ingrese una opción
    cin >> x;                        // Leer la opción ingresada por el usuario

    return x;                        // Devolver la opción ingresada por el usuario
}

// Función para obtener un valor long de la entrada del usuario
long getLong(string mjs)
{
    long m;
    cout << mjs << ": ";   // Mostrar el mensaje pasado como argumento
    cin >> m;              // Leer el valor long ingresado por el usuario
    return m;              // Devolver el valor long ingresado por el usuario
}

// Función para obtener una cadena de texto de la entrada del usuario
string getString(string mjs)
{
    string m;
    cout << mjs << ": ";   // Mostrar el mensaje pasado como argumento
    cin.ignore();          // Ignorar el carácter de nueva línea del búfer de entrada
    getline(cin, m);       // Leer la cadena de texto ingresada por el usuario
    return m;              // Devolver la cadena de texto ingresada por el usuario
}

// Función para agregar un registro de Persona
void agregarRegistro()
{
    Persona p;                                             // Crear una nueva Persona
    cin.ignore();                                          // Ignorar el carácter de nueva línea del búfer de entrada
    strcpy(p.nombre, getString("Ingresar Nombre").c_str());    // Obtener y copiar el nombre ingresado por el usuario
    strcpy(p.apellido, getString("Ingresar Apellido1").c_str());  // Obtener y copiar el primer apellido ingresado por el usuario
    strcpy(p.apellido2, getString("Ingresar Apellido2").c_str()); // Obtener y copiar el segundo apellido ingresado por el usuario
    p.cedula = getLong("Número de cédula");               // Obtener y asignar la cédula ingresada por el usuario

    fstream e("Archivos.bin", ios::in | ios::out | ios::binary);  // Abrir el archivo en modo lectura y escritura binaria

    // Si el archivo no existe, se crea
    if (!e)
    {
        e.open("Archivos.bin", ios::out | ios::binary);
        e.close();
        e.open("Archivos.bin", ios::in | ios::out | ios::binary);
    }

    // Obtener el tamaño del archivo y el número de registros
    e.seekg(0, ios::end);
    int fileSize = e.tellg();
    int numRecords = fileSize / sizeof(Persona);

    // Verificar si el registro ya existe
    bool exists = false;
    for (int i = 0; i < numRecords; ++i)
    {
        Persona aux;
        e.seekg(0 * sizeof(Persona));
        e.read(reinterpret_cast<char*>(&aux), sizeof(Persona));
        if (aux.cedula == p.cedula)
        {
            exists = true;
            break;
        }
    }

    // Si el registro no existe, se agrega al final del archivo
    if (exists)
    {
        cout << "Registro ya existe" << endl;              // Mostrar mensaje de que el registro ya existe
    }
    else
    {
        e.seekp(0, ios::end);
        e.write(reinterpret_cast<char*>(&p), sizeof(Persona));  // Escribir la nueva Persona en el archivo
        cout << "Registro agregado correctamente" << endl;  // Mostrar mensaje de que el registro se agregó correctamente
    }

    e.close();  // Cerrar el archivo
}

// Función para listar todos los registros
void listarRegistros()
{
    fstream e("Archivos.bin", ios::in | ios::binary);  // Abrir el archivo en modo lectura binaria

    if (!e)
    {
        cout << "El archivo no existe o no se puede abrir." << endl;  // Mostrar mensaje de error si no se pudo abrir el archivo
        return;
    }

    // Obtener el tamaño del archivo y el número de registros
    e.seekg(0, ios::end);
    int fileSize = e.tellg();
    int numRecords = fileSize / sizeof(Persona);

    if (numRecords == 0)
    {
        cout << "No hay registros para mostrar." << endl;  // Mostrar mensaje si no hay registros en el archivo
        e.close();  // Cerrar el archivo
        return;
    }

    // Imprimir los registros almacenados en el archivo
    e.seekg(0, ios::beg);
    cout << setw(15) << "Nombre" << setw(15) << "Apellido1" << setw(15) << "Apellido2" << setw(15) << "Cédula" << endl;
    cout << "-----------------------------------------------" << endl;

    for (int i = 0; i < numRecords; ++i)
    {
        Persona p;
        e.read(reinterpret_cast<char*>(&p), sizeof(Persona));
        cout << setw(15) << p.nombre << setw(15) << p.apellido << setw(15) << p.apellido2 << setw(15) << p.cedula << endl;
    }

    e.close();  // Cerrar el archivo
}

// Función para buscar un registro por cédula
void buscarRegistro()
{
    long ced = getLong("Ingrese la cédula a buscar");  // Obtener la cédula ingresada por el usuario
    fstream e("Archivos.bin", ios::in | ios::binary);  // Abrir el archivo en modo lectura binaria

    if (!e)
    {
        cout << "El archivo no existe o no se puede abrir." << endl;  // Mostrar mensaje de error si no se pudo abrir el archivo
        return;
    }

    // Obtener el tamaño del archivo y el número de registros
    e.seekg(0, ios::end);
    int fileSize = e.tellg();
    int numRecords = fileSize / sizeof(Persona);

    if (numRecords == 0)
    {
        cout << "No hay registros para buscar." << endl;  // Mostrar mensaje si no hay registros en el archivo
        e.close();  // Cerrar el archivo
        return;
    }

    // Buscar el registro por cédula
    bool found = false;
    for (int i = 0; i < numRecords; ++i)
    {
        Persona p;
        e.seekg(0* sizeof(Persona));
        e.read(reinterpret_cast<char*>(&p), sizeof(Persona));
        if (p.cedula == ced)
        {
            found = true;
            cout << "Registro encontrado:" << endl;  // Mostrar mensaje de que se encontró el registro
            cout << "Nombre: " << p.nombre << endl;  // Mostrar el nombre del registro
            cout << "Apellido1: " << p.apellido << endl;  // Mostrar el apellido del registro
            cout << "Apellido2: " << p.apellido2 << endl;  // Mostrar el segundo apellido del registro
            cout << "Cédula: " << p.cedula << endl;  // Mostrar la cédula del registro
            break;
        }
    }

    if (!found)
    {
        cout << "Registro no encontrado." << endl;  // Mostrar mensaje si no se encontró el registro
    }

    e.close();  // Cerrar el archivo
}

// Función principal
int main()
{
    int x = 0;
    do
    {
        x = menu();  // Mostrar el menú y obtener la opción del usuario
        switch (x)  // Evaluar la opción del usuario
        {
        case 1:
            agregarRegistro();  // Agregar un nuevo registro de Persona
            break;
        case 2:
            listarRegistros();  // Listar todos los registros
            break;
        case 3:
            buscarRegistro();  // Buscar un registro por cédula
            break;
        default:
            break;
        }
    } while (x != 6);  // Repetir hasta que el usuario elija salir

    return 0;  // Devolver 0 para indicar que el programa se ejecutó correctamente
}

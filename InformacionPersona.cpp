#include <iostream>   // Inclusión de la biblioteca estándar para entrada/salida
#include <fstream>    // Inclusión de la biblioteca estándar para operaciones de archivo
#include <iomanip>    // Inclusión de la biblioteca estándar para manipulación de formato de salida
#include <cstdlib>    // Inclusión de la biblioteca estándar para funciones de utilidad
#include <cstring>    // Inclusión de la biblioteca estándar para operaciones de cadena de caracteres
// Informacion persona J
using namespace std;  

// Definición de la estructura Persona
struct Persona
{
    char nombre[45] = "";    // Nombre de la persona
    char apellido[30] = "";  // Apellido de la persona
    char apellido2[30] = ""; // Segundo apellido de la persona
    long cedula;              // Cédula de la persona
};

// Función para mostrar el menú y obtener la opción del usuario
int menu()
{
    int x = 0; //almacenar la opción seleccionada por el usuario en el menú

    cout << "1.Agregar" << endl;   // Mostrar opción para agregar
    cout << "2.Lista" << endl;     // Mostrar opción para listar
    cout << "3.Buscar" << endl;    // Mostrar opción para buscar
    cout << "4.Eliminar" << endl;  // Mostrar opción para eliminar
    cout << "5.Modificar" << endl; // Mostrar opción para modificar
    cout << "6.Salir" << endl;     // Mostrar opción para salir
    cout << "Opcion: ";            // Pedir al usuario que ingrese una opción
    cin >> x;                      // Leer la opción ingresada por el usuario

    return x;  // Devolver la opción ingresada por el usuario
}

// Función para obtener un valor long de la entrada del usuario
long getLong(string mjs)
{
    long m;
    cout << mjs << endl;  // Mostrar el mensaje pasado como argumento
    cin >> m;             // Leer el valor long ingresado por el usuario
    return m;             // Devolver el valor long ingresado por el usuario
}

// Función para obtener una cadena de texto de la entrada del usuario
string getString(string mjs)
{
    string m;
    cout << mjs << endl;   // Mostrar el mensaje pasado como argumento
    cin.ignore();          // Ignorar el carácter de nueva línea del búfer de entrada
    getline(cin, m);      // Leer la cadena de texto ingresada por el usuario
    return m;             // Devolver la cadena de texto ingresada por el usuario
}

// Función para obtener una Persona del archivo
Persona getPersona(long ced)
{
    fstream e("Archivos.bin", ios::in | ios::binary);  // Abrir el archivo en modo lectura binaria
    Persona aux;                                       // Variable auxiliar para almacenar la Persona leída
    if(e.is_open())                                    // Verificar si el archivo se abrió correctamente
    {
        e.seekg((ced - 1) * sizeof(Persona));         // Desplazarse al registro de la Persona en la posición ced
        e.read((char*)&aux, sizeof(Persona));         // Leer la Persona desde el archivo
        e.close();                                    // Cerrar el archivo
    }
    return aux;                                        // Devolver la Persona leída
}

// Función para agregar un registro de Persona
void agregarRegistro()
{
    Persona p;                                             // Crear una nueva Persona
    cin.ignore();                                          // Ignorar el carácter de nueva línea del búfer de entrada
    strcpy(p.nombre, getString("Ingresar Nombre: ").c_str());    // Obtener y copiar el nombre ingresado por el usuario
    strcpy(p.apellido, getString("Ingresar Apellido1: ").c_str());  // Obtener y copiar el primer apellido ingresado por el usuario
    strcpy(p.apellido2, getString("Ingresar Apellido2: ").c_str()); // Obtener y copiar el segundo apellido ingresado por el usuario
    p.cedula = getLong("Numero de cedula: ");               // Obtener y asignar la cédula ingresada por el usuario

    Persona aux = getPersona(p.cedula);                    // Obtener la Persona con la cédula ingresada
    if(aux.cedula != 0)                                    // Verificar si la Persona ya existe en el archivo
    {
        cout << "Registro ya existe" << endl;              // Mostrar mensaje de que el registro ya existe
    }
    else
    {
        fstream e("Archivos.bin", ios::out | ios::app | ios::binary);  // Abrir el archivo en modo escritura binaria
        if(e.is_open())                                             // Verificar si el archivo se abrió correctamente
        {
            e.write((char*)&p, sizeof(Persona));                   // Escribir la nueva Persona en el archivo
            e.close();                                             // Cerrar el archivo
            cout << "Registro agregado correctamente" << endl;     // Mostrar mensaje de que el registro se agregó correctamente
        }
        else
        {
            cout << "Error al abrir el archivo" << endl;            // Mostrar mensaje de error si no se pudo abrir el archivo
        }
    }
}

// Función principal
int main()
{
    int x = 0;                            // Variable para almacenar la opción del menú
    do
    {
        x = menu();                       // Mostrar el menú y obtener la opción del usuario
        switch (x)                        // Evaluar la opción del usuario
        {
            case 1:
                agregarRegistro();        // Agregar un nuevo registro de Persona
                break;
            default:
                break;
        }
    } while (x != 6);                     // Repetir hasta que el usuario elija salir

    return 0;                            // Devolver 0 para indicar que el programa se ejecutó correctamente
}
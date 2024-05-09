#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string> 

using namespace std;

// Definición de la estructura Persona
struct Persona
{
    string usuario;       // Nombre de usuario (asumido como correo electrónico)
    string contrasena;    // Contraseña
};

// Función para mostrar el menú y obtener la opción del usuario
int menu()
{
    int x = 0;

    cout << "1. Iniciar sesión" << endl;           // Mostrar opción para iniciar sesión
    cout << "2. Registrar usuario" << endl;        // Mostrar opción para registrar un nuevo usuario
    cout << "3. Ver usuarios registrados" << endl; // Mostrar opción para ver usuarios registrados
    cout << "4. Salir" << endl;                     // Mostrar opción para salir
    cout << "Opción: ";                             // Pedir al usuario que ingrese una opción
    cin >> x;                                       // Leer la opción ingresada por el usuario

    return x;                                       // Devolver la opción ingresada por el usuario
}

// Función para registrar un nuevo usuario
void registrarUsuario()
{
    Persona p;                                             // Crear una nueva Persona
    cout << "Ingrese el nombre de usuario: ";
    cin >> p.usuario;                                      // Obtener y copiar el nombre de usuario ingresado por el usuario
    cout << "Ingrese la contraseña: ";
    cin >> p.contrasena;                                   // Obtener y copiar la contraseña ingresada por el usuario

    ofstream e("Usuarios.bin", ios::out | ios::binary | ios::app);  // Abrir el archivo en modo escritura binaria

    // Verificar si el archivo se abrió correctamente
    if (!e)
    {
        cout << "Error al abrir el archivo." << endl;  // Mostrar mensaje de error si no se pudo abrir el archivo
        return;
    }

    // Escribir el nuevo usuario en el archivo con un delimitador entre usuario y contraseña
    e << p.usuario << " " << p.contrasena << endl;
    
    // Cerrar el archivo
    e.close();

    // Mensaje de usuario registrado correctamente
    cout << "Usuario registrado correctamente." << endl;
}

// Función para mostrar los usuarios registrados
void verUsuariosRegistrados()
{
    ifstream e("Usuarios.bin");     // Abrir el archivo en modo lectura

    // Verificar si el archivo se abrió correctamente
    if (!e)
    {
        cout << "Error al abrir el archivo." << endl;  // Mostrar mensaje de error si no se pudo abrir el archivo
        return;
    }

    // Leer y mostrar todos los usuarios registrados
    cout << "Usuarios registrados:" << endl; 
    string usuario, contrasena;
    while (e >> usuario >> contrasena) // Leer los usuarios almacenados en el archivo
    {
        cout << "Usuario: " << usuario << endl;
    }

    // Cerrar el archivo
    e.close();
}

// Función para iniciar sesión
void iniciarSesion()
{
    string usuarioIngresado;                             // Almacenar el nombre de usuario ingresado por el usuario
    string contrasenaIngresada;                          // Almacenar la contraseña ingresada por el usuario
    cout << "Ingrese el nombre de usuario: ";
    cin >> usuarioIngresado;                             // Obtener y copiar el nombre de usuario ingresado por el usuario
    cout << "Ingrese la contraseña: ";
    cin >> contrasenaIngresada;                          // Obtener y copiar la contraseña ingresada por el usuario

    ifstream e("Usuarios.bin");   // Abrir el archivo en modo lectura

    // Verificar si el archivo se abrió correctamente
    if (!e)
    {
        cout << "Error al abrir el archivo." << endl;  // Mostrar mensaje de error si no se pudo abrir el archivo
        return;
    }

    // Buscar el usuario en el archivo
    bool found = false;
    string usuario, contrasena;
    while (e >> usuario >> contrasena)
    {
        if (usuario == usuarioIngresado && contrasena == contrasenaIngresada)
        {
            found = true;
            break;
        }
    }

    // Mostrar el resultado de la búsqueda
    if (found)
    {
        cout << "Inicio de sesión exitoso." << endl;  // Mostrar mensaje de inicio de sesión exitoso
    }
    else
    {
        cout << "Usuario o contraseña incorrectos." << endl;  // Mostrar mensaje de usuario o contraseña incorrectos
        return;  // Salir si las credenciales son incorrectas
    }

    // Cerrar el archivo
    e.close();

    // Mostrar opción para ver el correo
    cout << "¿Desea ver su correo? (S/N): ";
    char opcion;
    cin >> opcion;
    if (opcion == 'S' || opcion == 's')
    {
        cout << "Correo: " << usuarioIngresado << endl;
    }
}

// Función principal
int main()
{
    int x = 0;
    do
    {
        x = menu();  // Mostrar el menú y obtener la opción del usuario
        switch (x)   // Evaluar la opción del usuario
        {
            case 1:
                iniciarSesion();         // Iniciar sesión
                break;
            case 2:
                registrarUsuario();     // Registrar un nuevo usuario
                break;
            case 3:
                verUsuariosRegistrados(); // Ver usuarios registrados
                break;
            default:
                break;
        }
    } while (x != 4);  // Repetir hasta que el usuario elija salir

    return 0;  // Devolver 0 para indicar que el programa se ejecutó correctamente
}

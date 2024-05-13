#include <iostream>
#include <fstream>
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
    int opcion = 0;

    cout << "\n--- Menú ---" << endl;
    cout << "1. Iniciar sesión" << endl;           // Mostrar opción para iniciar sesión
    cout << "2. Registrar usuario" << endl;        // Mostrar opción para registrar un nuevo usuario
    cout << "3. Ver usuarios registrados" << endl; // Mostrar opción para ver usuarios registrados
    cout << "4. Salir" << endl;                     // Mostrar opción para salir
    cout << "Opción: ";                             // Pedir al usuario que ingrese una opción
    cin >> opcion;                                       // Leer la opción ingresada por el usuario

    return opcion;                                       // Devolver la opción ingresada por el usuario
}

// Función para registrar un nuevo usuario
void registrarUsuario()
{
    Persona nuevoUsuario;                                             // Crear una nueva Persona
    cout << "Ingrese el nombre de usuario: ";
    cin >> nuevoUsuario.usuario;                                      // Obtener y copiar el nombre de usuario ingresado por el usuario
    cout << "Ingrese la contraseña: ";
    cin >> nuevoUsuario.contrasena;                                   // Obtener y copiar la contraseña ingresada por el usuario

    ofstream archivoUsuarios("usuarios.txt", ios::app);  // Abrir el archivo en modo escritura

    // Verificar si el archivo se abrió correctamente
    if (!archivoUsuarios)
    {
        cout << "Error al abrir el archivo." << endl;  // Mostrar mensaje de error si no se pudo abrir el archivo
        return;
    }

    // Escribir el nuevo usuario en el archivo 
    archivoUsuarios << nuevoUsuario.usuario << " " << nuevoUsuario.contrasena << endl;
    
    // Cerrar el archivo
    archivoUsuarios.close();

    // Mensaje de usuario registrado correctamente
    cout << "Usuario registrado correctamente." << endl;
}

// Función para mostrar los usuarios registrados
void verUsuariosRegistrados()
{
    ifstream archivoUsuarios("usuarios.txt");     // Abrir el archivo en modo lectura 

    // Verificar si el archivo se abrió correctamente
    if (!archivoUsuarios)
    {
        cout << "Error al abrir el archivo." << endl;  // Mostrar mensaje de error si no se pudo abrir el archivo
        return;
    }

    // Leer y mostrar todos los usuarios registrados
    cout << "Usuarios registrados:" << endl; 
    string usuarioLeido;
    while (archivoUsuarios >> usuarioLeido) // Leer los usuarios almacenados en el archivo
    {
        cout << "Usuario: " << usuarioLeido << endl;
    }

    // Cerrar el archivo
    archivoUsuarios.close();
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

    ifstream archivoUsuarios("usuarios.txt");   // Abrir el archivo en modo lectura

    // Verificar si el archivo se abrió correctamente
    if (!archivoUsuarios)
    {
        cout << "Error al abrir el archivo." << endl;  // Mostrar mensaje de error si no se pudo abrir el archivo
        return;
    }

    // Buscar el usuario en el archivo
    bool encontrado = false;
    string usuario;
    string contrasena;
    while (archivoUsuarios >> usuario >> contrasena)
    {
        // Comparamos usuario y contraseña
        if (usuario == usuarioIngresado && contrasena == contrasenaIngresada)
        {
            encontrado = true;
            break;
        }
    }

    // Mostrar el resultado de la búsqueda
    if (encontrado)
    {
        cout << "Inicio de sesión exitoso." << endl;  // Mostrar mensaje de inicio de sesión exitoso

        // Preguntar si desea ver su correo
        char opcion;
        cout << "¿Desea ver su correo? (S/N): ";
        cin >> opcion;
        if (opcion == 'S' || opcion == 's')
        {
            cout << "Correo: " << usuarioIngresado << endl;
        }
    }
    else
    {
        cout << "Usuario o contraseña incorrectos." << endl;  // Mostrar mensaje de usuario o contraseña incorrectos
    }

    // Cerrar el archivo
    archivoUsuarios.close();
}

// Función principal
int main()
{
    int opcionSeleccionada = 0;
    do
    {
        opcionSeleccionada = menu();  // Mostrar el menú y obtener la opción del usuario
        switch (opcionSeleccionada)   // Evaluar la opción del usuario
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
    } while (opcionSeleccionada != 4);  // Repetir hasta que el usuario elija salir
    
    return 0;
}

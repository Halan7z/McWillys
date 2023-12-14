#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <wchar.h>
#include <vector>
#include <ctime>
#include <wchar.h>
#include <map>
#include <string>
#include <windows.h>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <sys/stat.h>
#include <limits>


//Limpiar pantalla
#ifdef _WIN32
#define CLEAR "cls"
#elif defined(unix)||defined(__unix__)||defined(__unix)||defined(__APPLE__)||defined(__MACH__)
#define CLEAR "clear"
#else
#error "SO no soportado para limpiar pantalla"
#endif

using namespace std;


const char *archivo = "inventario.txt";

// ------------------------------------------------------------
struct informacionCajero
{
    string nombre, numerocarnet;
};

struct Orden {
    vector<string> productos;
    vector<int> preciosEnConjunto;
    double total = 0;
    string nombreCliente;
    string carnetONit;
    string fechaVenta;

};
// ------------------------------------------------------------

// ------------------------------------------------------------
struct Ingrediente {
    string nombre;
    int stock;
};



// ------------------------------------------------------------

class menu
{
private:
    string nombre;
    string domicilio;
    string celular;
    string fechaContratacion;
    string codigoEmpleado;

    vector<Orden> cargarOrdenes();
    void mostrarOrden(const Orden& orden);


public:
    void menuPrincipal();
    void contratarEmpleado();
    void despedirEmpleado();
    void buscarEmpleado();
    void desplegarMenu();
    void gestionarOfertas();
    void administrarclientes();

    void verVentasPorMes();
    void verVentasDeCliente();
    void verTodasLasVentas();

    void mostrarMenuMcWillys(informacionCajero& info);
    void mostrarMenuHamburguesas(Orden& orden, informacionCajero& info);
    void mostrarMenuDesayunos(Orden& orden, informacionCajero& info);
    void mostrarMenuExtras(Orden& orden, informacionCajero& info);
    void mostrarMenuPostres(Orden& orden, informacionCajero& info);

    void obtenerYMostrarHoraActual();
    bool validacionTrabajador(informacionCajero& info);
    void venderOfertas(Orden& orden);

    void generarFactura(const Orden& orden, informacionCajero& info);
    void guardarOrdenMes(const Orden& orden);
    void guardarOrden(const Orden& orden);
};

void inicializarInventario(const char *archivo, const std::vector<std::string> &ingredientes);
void actualizarStock(const char *archivo, const std::string &ingrediente, int cantidad);
void aumentarStock(const char *archivo, const std::string &ingrediente, int cantidad, int );
void restarStock(const char *archivo, const std::string &ingrediente, int cantidad);
void mostrarInventario(const char *archivo);
void administrarStockIngredientes();


void pausa();
void error();
void comprobarArchivo();
void esperarSegundo();


void esperarSegundo() {
    clock_t inicio = clock();
    while (static_cast<double>(clock() - inicio) / CLOCKS_PER_SEC < 1.0) {}
}


int main()
{
    setlocale(LC_ALL, "");
    system ("color f0");
    menu inicio;
    comprobarArchivo();
    inicio.menuPrincipal();
    return 0;
}


void menu::menuPrincipal()
{

    string contrasenaGerente = "willyporsiempre2";
    string contrasenaTrabajador = "1985";
    string contrasenaUsuarioNormal = "contrasena";
    int opcion;
    bool ejecucionTerminada = false; // Variable para controlar la finalización
    bool mostrarMensajeAutodestruccion = false; // Variable para mostrar el mensaje de autodestrucción

    // Imprimir un mensaje de bienvenida y la hamburguesa con caracteres ASCII
    /* cout << "Inicializando el sistema." << endl;
            for (int i = 3; i > 0; i--) {
                cout << "." << " ";
                esperarSegundo();
            }
    system ("cls"); */

    cout << "\t¡BIENVENIDO A MC WILLY'S!\n" << endl;

    cout << "                           |\\ /| /|_/|" << endl;
    cout << "                           |\\||-|\\||-/|/|" << endl;
    cout << "                            \\|\\|//||///" << endl;
    cout << "          _..----.._       |\\/\\||//||||" << endl;
    cout << "        .'     o    '.     |||\\\\|/\\\\ ||_" << endl;
    cout << "       /   o       o  \\    | './\\_/.' |" << endl;
    cout << "      |o        o     o|   |          |" << endl;
    cout << "      /'-.._o     __.-'\\   |          |" << endl;
    cout << "      \\      `````     /   |          |" << endl;
    cout << "      |``--........--'|    '.______.'" << endl;
    cout << "       \\              /" << endl;
    cout << "        `'----------'`" << endl;

    cout << "\n  ";
    system("pause");

    /* cout << "\n  Presione cualquier tecla para continuar. " ;
    cin.ignore(); // Esperar a que el usuario presione una tecla */

    system ("cls");

    do {
        int intentos = 3;
        bool accesoPermitido = false;

        cout << "----- MENÚ PRINCIPAL -----" << endl;
        cout << "1. Opción para Gerente" << endl;
        cout << "2. Opción para Trabajador" << endl;
        cout << "3. Opción para Usuario Normal" << endl;
        cout << "4. Salir" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        while (cin.fail()) {
            cin.clear();  // Limpiar el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descartar la entrada inválida
            cout << "Entrada inválida. Ingrese un número: ";
            cin >> opcion;
        }

        switch (opcion) {
            case 1: {
                system("cls");
                string inputContrasena;
                do {

                    cout << "Por favor, ingresa la contraseña para Gerente: ";
                    cin >> inputContrasena;
                    if (inputContrasena == contrasenaGerente) {
                        system("cls");

                        cout << "Has seleccionado la opción para Gerente.\n" << endl;
                        system("pause");
                        system("cls");


                        accesoPermitido = true;
                        bool ejecucionTerminada = false;
                        while (!ejecucionTerminada) {


                            int opcion;
                            cout << "----- MENU PARA GERENTE -----" << endl;
                            cout << "1. Contratar empleado" << endl;
                            cout << "2. Despedir empleado" << endl;
                            cout << "3. Buscar empleado" << endl;
                            cout << "4. Administrar Stock de Ingredientes" << endl; // Nueva opción
                            cout << "5. Administrar Ofertas y Promociones" << endl; // Nueva opción
                            cout << "6. Administrar clientes" << endl; // Nueva opción
                            cout << "7. Salir" << endl;
                            cout << "Ingresa la opción: ";
                            cin >> opcion;

                            while (cin.fail()) {
                                cin.clear();  // Limpiar el estado de error
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descartar la entrada inválida
                                cout << "Entrada inválida. Ingrese una opción valida: ";
                                cin >> opcion;
                            }


                            switch(opcion) {
                                case 1:
                                    system("cls");
                                    contratarEmpleado();
                                    break;
                                case 2:
                                    system("cls");
                                    despedirEmpleado();
                                    break;
                                case 3:
                                    system("cls");
                                    buscarEmpleado();
                                    break;
                                case 4:
                                    system("cls");
                                    desplegarMenu();
                                    break;
                                case 5:
                                    system("cls");
                                    gestionarOfertas();
                                    break;
                                case 6:
                                    system("cls");
                                    administrarclientes();
                                    break;
                                case 7:
                                    ejecucionTerminada = true;
                                    system("cls");
                                    break;
                                default:
                                    system("cls");
                                    cout << "Opción no válida. Por favor ingresa una opción válida.\n" << endl;

                                    /*for (int i = 1; i > 0; i--) {
                                        esperarSegundo();
                                    } */

                                    break;
                                }
                            }
                            break;
                        }

                        else {

                            cout << "Contraseña incorrecta. Intentos restantes: " << --intentos << endl;
                            cout << endl;
                            if (intentos == 0) {

                                mostrarMensajeAutodestruccion = true;
                                ejecucionTerminada = true; // Finalizar la ejecución
                            }
                        }
                    } while (intentos > 0);
                    break;

            }
            case 2: {
                system("cls");
                string inputContrasena;
                do {

                    cout << "Por favor, ingresa la contraseña para Trabajador: ";
                    cin >> inputContrasena;
                    if (inputContrasena == contrasenaTrabajador) {
                        system("cls");
                        cout << "Has seleccionado la opción para Trabajador.\n" << endl;

                        system("pause");
                        informacionCajero info;

                        if(validacionTrabajador(info))
                        {
                            accesoPermitido = true;

                            // Submenú para Trabajador
                            while (accesoPermitido) {
                                int opcionTrabajador;
                                system("cls");
                                cout << "Menu para Trabajador:" << endl;

                                cout << "1. Vender" << endl;

                                cout << "4. Salir" << endl;
                                cout << "Ingresa la opción: ";
                                cin >> opcionTrabajador;

                                switch(opcionTrabajador) {
                                    case 1:
                                        mostrarMenuMcWillys(info);
                                        break;

                                    case 4:
                                        accesoPermitido = false; // Salir del submenu
                                        system("cls");
                                        break;
                                    default:
                                        cout << "Opción no válida. Por favor ingresa una opción válida." << endl;
                                        break;
                                }
                            }
                        }
                        break;
                    } else {
                        cout << "Contraseña incorrecta. Intentos restantes: " << --intentos << endl;
                        cout << endl;
                        if (intentos == 0) {

                            mostrarMensajeAutodestruccion = true;
                            ejecucionTerminada = true; // Finalizar la ejecución
                        }
                    }
                } while (intentos > 0);
                break;
            }
            case 3: {
                system("cls");
                string inputContrasena;
                do {
                    cout << "Por favor, ingresa la contraseña para Usuario Normal: ";
                    cin >> inputContrasena;
                    if (inputContrasena == contrasenaUsuarioNormal) {
                        cout << "Has seleccionado la opción para Usuario Normal." << endl;
                        accesoPermitido = true;
                        ejecucionTerminada = true; // Finalizar la ejecución
                        break;
                    } else {
                        cout << "Contraseña incorrecta. Intentos restantes: " << --intentos << endl;
                        cout << endl;
                        if (intentos == 0) {

                            mostrarMensajeAutodestruccion = true;
                            ejecucionTerminada = true; // Finalizar la ejecución
                        }
                    }
                } while (intentos > 0);
                break;
            }
            case 4:
                cout << "Saliendo del programa. ¡Hasta luego!" << endl;
                accesoPermitido = true;
                ejecucionTerminada = true; // Finalizar la ejecución
                break;
            default:
                system("cls");
                cout << "Opción no válida. Por favor, elige una opción válida.\n" << endl;
                break;
        }

        if (!accesoPermitido && mostrarMensajeAutodestruccion) {
            cout << "Mensaje de autodestrucción activado. Saliendo en:" << endl;
            for (int i = 3; i > 0; i--) {
                cout << i << " ";
                esperarSegundo();
            }
        }
    } while (!ejecucionTerminada);
}


void menu::contratarEmpleado() {
    ofstream escritura;
    ifstream verificador;
    string auxCodigo;
    bool coincidencia = false;
    string codigoEmpleado, nombre, domicilio, celular, fechaContratacion;

    escritura.open("empleados.txt", ios::app);  // Cambiado a "empleados.txt" para guardar información de empleados
    verificador.open("empleados.txt", ios::in); // Cambiado a "empleados.txt" para verificar empleados existentes

    if (escritura.is_open()) {
        cout << "\t\t\t\t***Contratar una persona***\t\t\t\t\n\n";
        fflush(stdin);
        cout << "Ingresa el numero de carnet del empleado: ";
        getline(cin, auxCodigo);

        // Verificar que la longitud del código sea de 8 caracteres y que sean todos dígitos
        while (auxCodigo.length() != 8 || !all_of(auxCodigo.begin(), auxCodigo.end(), ::isdigit)) {
            cout << "Carnet de empleado no válido, debe tener 8 digitos. Inténtalo nuevamente: ";
            getline(cin, auxCodigo);
        }

        do {
            verificador.seekg(0);
            getline(verificador, codigoEmpleado); // Cambiado a "codigoEmpleado" para empleados

            while (!verificador.eof()) {
                getline(verificador, nombre);
                getline(verificador, domicilio);
                getline(verificador, celular);
                getline(verificador, fechaContratacion); // Cambiado a "fechaContratacion"

                if (codigoEmpleado == auxCodigo) // Cambiado a "codigoEmpleado"
                {
                    coincidencia = true;
                    cout << "\n\nYa existe un empleado con ese numero de carnet!\n\n";
                    cout << "El empleado con ese numero de carnet es: " << nombre << "\n\n";
                    cout << "Ingresa un numero de carnet válido!: ";
                    getline(cin, auxCodigo);

                    // Verificar que la longitud del código sea de 8 caracteres y que sean todos dígitos
                    while (auxCodigo.length() != 8 || !all_of(auxCodigo.begin(), auxCodigo.end(), ::isdigit)) {
                        cout << "Código de empleado no válido, debe ser una cadena de 8 números. Inténtalo nuevamente: ";
                        getline(cin, auxCodigo);
                    }

                    break;
                }

                getline(verificador, codigoEmpleado); // Cambiado a "codigoEmpleado" para empleados
            }

            if (verificador.eof() && auxCodigo != codigoEmpleado) // Cambiado a "codigoEmpleado" para empleados
                coincidencia = false;

        } while (coincidencia == true);

        system(CLEAR);
        codigoEmpleado = auxCodigo; // Cambiado a "codigoEmpleado" para empleados
        cout << "\t\t\t\t***Contratar una persona***\t\t\t\t\n\n";
        cout << "Ingresa el numero de carnet del empleado: ";
        cout << codigoEmpleado;
        cout << "\n\n\n";

        // Verificar que el nombre no sea solo un carácter en blanco
        do {
            fflush(stdin);
            cout << "Ingresa el nombre del empleado: ";
            getline(cin, nombre);
        } while (nombre.empty() || all_of(nombre.begin(), nombre.end(), ::isspace));

        system("cls");
        cout << "\t\t\t\t***Contratar una persona***\t\t\t\t\n\n";
        cout << "Ingresa el numero de carnet del empleado: ";
        cout << codigoEmpleado;
        cout << "\n\n\n";
        cout << "Ingresa el nombre del empleado: ";
        cout << nombre << endl;

        cout << "\n\n";

        // Verificar que el domicilio no sea solo un carácter en blanco
        do {
            fflush(stdin);
            cout << "Ingresa el domicilio del empleado: ";
            getline(cin, domicilio);
        } while (domicilio.empty() || all_of(domicilio.begin(), domicilio.end(), ::isspace));

        system("cls");
        cout << "\t\t\t\t***Contratar una persona***\t\t\t\t\n\n";
        cout << "Ingresa el numero de carnet del empleado: ";
        cout << codigoEmpleado;
        cout << "\n\n\n";
        cout << "Ingresa el nombre del empleado: ";
        cout << nombre << endl;
        cout << "\n\n";
        cout << "Ingresa el domicilio del empleado: ";
        cout << domicilio << endl;
        cout << "\n\n";

        // Verificar que el número de teléfono no sea solo un carácter en blanco
        do {
            fflush(stdin);
            cout << "Ingresa el número de telefono del empleado (8 dígitos): ";
            getline(cin, celular);

            // Verificar que el número de teléfono no esté vacío y que tenga 8 dígitos
            if (celular.empty() || celular.length() != 8 || !all_of(celular.begin(), celular.end(), ::isdigit)) {
                cout << "Número de teléfono no válido. Debe contener 8 dígitos. Inténtalo nuevamente.\n";
            }

        } while (celular.empty() || celular.length() != 8 || !all_of(celular.begin(), celular.end(), ::isdigit));

        system("cls");
        cout << "\t\t\t\t***Contratar una persona***\t\t\t\t\n\n";
        cout << "Ingresa el numero de carnet del empleado: ";
        cout << codigoEmpleado;
        cout << "\n\n\n";
        cout << "Ingresa el nombre del empleado: ";
        cout << nombre << endl;
        cout << "\n\n";
        cout << "Ingresa el domicilio del empleado: ";
        cout << domicilio << endl;
        cout << "\n\n";
        cout << "Ingresa el número de telefono del empleado (8 dígitos): ";
        cout << celular << endl;
        cout << "\n\n";

        // Verificar que la fecha de contratación no sea solo un carácter en blanco
        do {
            fflush(stdin);
            cout << "Ingresa la fecha de contratación del empleado: ";
            getline(cin, fechaContratacion);
        } while (fechaContratacion.empty() || all_of(fechaContratacion.begin(), fechaContratacion.end(), ::isspace));

        system("cls");
        cout << "\t\t\t\t***Contratar una persona***\t\t\t\t\n\n";
        cout << "Ingresa el numero de carnet del empleado: ";
        cout << codigoEmpleado;
        cout << "\n\n\n";
        cout << "Ingresa el nombre del empleado: ";
        cout << nombre << endl;
        cout << "\n\n";
        cout << "Ingresa el domicilio del empleado: ";
        cout << domicilio << endl;
        cout << "\n\n";
        cout << "Ingresa el número de telefono del empleado (8 dígitos): ";
        cout << celular << endl;
        cout << "\n\n";
        cout << "Ingresa la fecha de contratación del empleado: ";
        cout << fechaContratacion;
        cout << "\n\n";

        escritura << codigoEmpleado << endl << nombre << endl << domicilio << endl << celular
                  << endl << fechaContratacion << endl; // Cambiado a "fechaContratacion"

        cout << "\nEl registro se ha completado correctamente.\n\n";
    } else {
        error();
    }

    escritura.close();
    verificador.close();
    pausa();
}

void menu::despedirEmpleado()
{
    ifstream lectura;
    ofstream auxiliar;
    bool encontrado=false;
    string auxCodigo;
    string respuesta;
    lectura.open("empleados.txt",ios::in); // Cambiado a "empleados.txt" para despedir empleados
    if(lectura.is_open())
    {
        cout<<"\t\t\t\t***Despedir un empleado***\t\t\t\t\n\n";
        auxiliar.open("auxiliar.txt",ios::out);
        fflush(stdin);
        getline(lectura,codigoEmpleado); // Cambiado a "codigoEmpleado" para empleados
        if(lectura.eof())
        {
            cout<<"No hay ningun empleado registrado"; // Cambiado a "empleado" para empleados
        }
        else
        {
            lectura.seekg(0);
            cout<<"Ingresa el numero de carnet del empleado que deseas despedir: "; // Cambiado a "empleado" para empleados
            getline(cin,auxCodigo);
            getline(lectura,codigoEmpleado); // Cambiado a "codigoEmpleado" para empleados
            while(!lectura.eof())
            {
                getline(lectura,nombre);
                getline(lectura,domicilio);
                getline(lectura,celular);
                getline(lectura,fechaContratacion); // Cambiado a "fechaContratacion"

                if(auxCodigo==codigoEmpleado) // Cambiado a "codigoEmpleado" para empleados
                {
                    encontrado=true;
                    cout<<"\n\nRegistro Encontrado\n\n";
                    cout<<"Código: "<<codigoEmpleado<<endl; // Cambiado a "codigoEmpleado" para empleados
                    cout<<"Nombre: "<<nombre<<endl;
                    cout<<"Domicilio: "<<domicilio<<endl;
                    cout<<"Celular: "<<celular<<endl;
                    cout<<"Fecha de contratación: "<<fechaContratacion<<endl; // Cambiado a "fechaContratacion"
                    cout<<"\n\n";
                    cout<<"¿Realmente deseas despedir a: "<<nombre<<" (s/n)?: ";
                    getline(cin,respuesta);
                    if(respuesta=="s"||respuesta=="S"||respuesta=="si"||respuesta=="SI"||
                            respuesta=="Si"||respuesta=="sI")
                    {
                        cout<<"\n\nEl empleado ha sido despedido correctamente\n\n";
                    }

                    else
                    {

                        cout<<"\n\nEmpleado conservado\n\n";
                        auxiliar<<codigoEmpleado<<endl<<nombre<<endl<<domicilio<<endl<<celular
                                <<endl<<fechaContratacion<<endl; // Cambiado a "fechaContratacion"

                    }

                }
                else
                {
                    auxiliar<<codigoEmpleado<<endl<<nombre<<endl<<domicilio<<endl<<celular
                            <<endl<<fechaContratacion<<endl; // Cambiado a "fechaContratacion"
                }
                getline(lectura,codigoEmpleado); // Cambiado a "codigoEmpleado" para empleados
            }
            if(encontrado==false)
            {
                cout<<"\n\nNo se encontró el código: "<<auxCodigo<<"\n\n";
            }
        }
        lectura.close();
        auxiliar.close();
        remove("empleados.txt"); // Cambiado a "empleados.txt" para despedir empleados
        rename("auxiliar.txt","empleados.txt"); // Cambiado a "empleados.txt" para despedir empleados

    }
    else
    {
        error();
    }
    pausa();
}

void pausa()
{
    cout<<"\n\nPresiona Enter para continuar...";
    fflush(stdin);
    cin.get();
    system(CLEAR);
}


void error()
{
    cout<<" No se pudo abrir el archivo de registros asegurese que el archivo se";
    cout<<" encuentre en la misma ubicaci\242n \n que el programa o  que el archivo de texto se ";
    cout<<"llame: clientes.txt, si el archivo tiene otro nombre \n ren\242mbrelo al ya mencionado.";
    cout<<"\n\n";
    cout<<" Este error tambien puede ser porque es la primera vez que usa el programa y ";
    cout<<"no se ha hecho ningun registro.";
    cout<<"\n Si este es el caso le invito a seleccionar la opcion de dar de alta un cliente y ";
    cout<<"dar de alta al primer cliente \n para asi dejar de ver este error. :)";
}

void comprobarArchivo()
{
    ifstream archivo;
    archivo.open("ordenes.txt",ios::in);
    if(!archivo.is_open())
    {
        cout<<"No se pudo abrir el archivo de registros o aun no se ha registrado ningun cliente!";
        cout<<"\n\n";
        cout<<"Para crear el archivo de registros selecciona la opcion de dar de alta un cliente.";
        cout<<"\n";
        pausa();
        system(CLEAR);
    }
}

void menu::buscarEmpleado() {
    ifstream lectura;
    lectura.open("empleados.txt", ios::in); // Cambiado a "empleados.txt" para buscar empleados
    int encontrados = 0;
    string buscarCodigo;

    cout << "\t\t\t\t***Buscar Empleado***\t\t\t\t\n\n" << endl << endl;

    if (lectura.is_open()) {
        cout << "Ingresa el numero de carnet del empleado: "; // Cambiado a "empleado" para buscar empleados
        fflush(stdin);
        getline(cin, buscarCodigo);
        cout << endl;

        getline(lectura, codigoEmpleado); // Cambiado a "codigoEmpleado" para empleados

        while (!lectura.eof()) {
            getline(lectura, nombre);
            getline(lectura, domicilio);
            getline(lectura, celular);
            getline(lectura, fechaContratacion); // Cambiado a "fechaContratacion"

            if (codigoEmpleado == buscarCodigo) // Cambiado a "codigoEmpleado" para empleados
            {
                cout << "Carnet: " << codigoEmpleado << endl; // Cambiado a "codigoEmpleado" para empleados
                cout << "Nombre: " << nombre << endl;
                cout << "Domicilio: " << domicilio << endl;
                cout << "Celular: " << celular << endl;
                cout << "Fecha de contratación: " << fechaContratacion << endl; // Cambiado a "fechaContratacion"
                cout << "\n\n";
                encontrados++;
                break; // Si se encuentra el empleado, no es necesario seguir buscando
            }

            getline(lectura, codigoEmpleado); // Cambiado a "codigoEmpleado" para empleados
        }

        if (encontrados) {
            cout << "Se encontró 1 registro con el numero de carnet buscado" << endl;
        } else {
            cout << "No se encontró ningún registro con el numero de carnet buscado" << endl;
        }
    } else {
        cout << endl << "No se pudo abrir el archivo!";
    }

    lectura.close();
    pausa();
}


// --------------------------------------------------
// Menu para administrar el stock
void menu::desplegarMenu() {
    bool ejecucionTerminada = false;

    while (!ejecucionTerminada) {
        int opcion;
        cout << "Menu:" << endl;
        cout << "1. Mostrar inventario actual" << endl;
        cout << "2. Agregar stock" << endl;
        cout << "3. Volver al menu para Gerente" << endl;
        cout << "Ingresa la opción: ";
        cin >> opcion;

        while (cin.fail()) {
            system("cls");
            cout << "Menu:" << endl;
            cout << "1. Mostrar inventario actual" << endl;
            cout << "2. Agregar stock" << endl;
            cout << "3. Volver al menu para Gerente" << endl;

            cin.clear();  // Limpiar el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descartar la entrada inválida
            cout << "\nEntrada inválida. Ingrese un opción valida: ";
            cin >> opcion;
        }

        switch(opcion) {
            case 1:
                system("cls");
                administrarStockIngredientes();
                break;
            case 2:

            {
                system("cls");

                vector<string> ingredientes = {
                    "Pollo", "Carne de res", "Carne vegetariana", "Carne especial", "Carne silpancho", "Salchicha",
                    "Tortilla", "Pan hot dog", "Wafles", "Galletas",
                    "Queso", "Queso suizo", "Queso gouda",
                    "Mayonesa", "Mostaza", "Ketchup", "Salsa BBQ", "Salsa especial", "Salsa programación",
                    "Salsa tenorio", "Salsa picante", "Salsa de vino tinto",
                    "Vegetales", "Tocino", "Pepinillos", "Jalapeños", "Champiñones",
                    "Papas", "Soda", "Café", "Helado", "Palza cakes", "Sandwich de helado", "Cupcakes", "Palza pie"
                };




                string ingrediente;
                int cantidad;

                cout << "Seleccione un ingrediente para aumentar el stock:" << endl;
                for (int i = 0; i < ingredientes.size(); ++i) {
                    cout << i + 1 << ". " << ingredientes[i] << endl;
                }

                int seleccion;
                cout << "Ingresa el número correspondiente al ingrediente: ";
                cin >> seleccion;

                if (seleccion >= 1 && seleccion <= ingredientes.size()) {
                    ingrediente = ingredientes[seleccion - 1];

                    cout << "Ingrese la cantidad deseada: ";
                    cin >> cantidad;

                    if (cantidad > 0) {
                        aumentarStock(archivo, ingrediente, cantidad, seleccion);
                    } else {
                        cout << "La cantidad debe ser mayor que cero." << endl;
                    }
                } else {
                    cout << "Selección no válida." << endl;
                }
            }


                break;

            case 3:
                ejecucionTerminada = true;
                system("cls");
                break;
            default:
                system("cls");
                cout << "Opción no válida. Por favor ingresa una opción válida.\n" << endl;

                break;
        }
    }
}

// Función para inicializar el inventario con un valor de 1000 para cada ingrediente
void inicializarInventario(const char *archivo, const vector<string> &ingredientes) {
    ofstream file(archivo);

    if (file.is_open()) {
        for (const string &ingrediente : ingredientes) {
            file << ingrediente << ": 1000\n";
        }
        file.close();
        cout << "Inventario creado exitosamente." << endl;
    } else {
        cerr << "Error al abrir el archivo." << endl;
    }
}

// Función para actualizar el stock de un ingrediente
void actualizarStock(const char *archivo, const string &ingrediente, int cantidad) {
    ifstream readFile(archivo);
    ofstream tempFile("temp.txt");

    if (!readFile.is_open() || !tempFile.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    string line;
    while (getline(readFile, line)) {
        stringstream ss(line);
        string token;
        getline(ss, token, ':'); // Obtener el nombre del ingrediente

        if (token == ingrediente) {
            ss >> token; // Obtener la cantidad actual
            int stock = stoi(token) + cantidad; // Actualizar la cantidad

            // Verificar si el stock llega a cero
            if (stock <= 0) {
                cout << "¡Alerta! Ya no queda stock de " << ingrediente << "." << endl;
                stock = 0; // Asegurarse de que el stock no sea negativo
            }

            tempFile << ingrediente << ": " << stock << endl;
        } else {
            tempFile << line << endl;
        }
    }

    readFile.close();
    tempFile.close();

    remove(archivo);
    rename("temp.txt", archivo);

}

// Función para aumentar stock de un ingrediente
void aumentarStock(const char *archivo, const string &ingrediente, int cantidad, int seleccion) {

    vector<double> preciosCompraIngredientes = {
        1, 2, 2.5, 3, 1.5, 2, 1, 1, 2, 1,
        2, 2, 2.5, 1, 1, 1, 1, 2, 2, 3,
        2, 3, 2, 1.5, 1.5, 1, 1, 2, 3, 3,
        4, 4, 3, 3, 5
    };

    actualizarStock(archivo, ingrediente, cantidad);
    cout << "Stock de " << ingrediente << " actualizado exitosamente." << endl;
    cout << endl;

    int total = preciosCompraIngredientes[seleccion-1] * cantidad;

    cout << "Total a pagar por el stock añadido: " << total << " Bs.\n" << endl;
    system("pause");
    system("cls");
}



// Función para restar stock de un ingrediente
void restarStock(const char *archivo, const string &ingrediente, int cantidad) {
    actualizarStock(archivo, ingrediente, -cantidad);

}

// Función para mostrar el inventario
void mostrarInventario(const char *archivo) {
    ifstream readFile(archivo);
    string line;

    cout << left << setw(28) << "Producto" << "Unidades" << endl;
    cout << setfill('-') << setw(40) << "" << setfill(' ') << endl;

    while (getline(readFile, line)) {
        string producto;
        int cantidad;

        // Supongamos que cada línea tiene un formato "producto: cantidad"
        istringstream iss(line);
        getline(iss, producto, ':');
        iss >> cantidad;

        cout << "- " << left << setw(20) << producto << right << setw(10) << cantidad << " unidades" << endl;
    }

    cout << endl;
    system("pause");
    system("cls");
}

void administrarStockIngredientes() {
    // Lista de ingredientes

    vector<string> ingredientes = {
        "Pollo", "Carne de res", "Carne vegetariana", "Carne especial", "Carne silpancho", "Salchicha",
        "Tortilla", "Pan hot dog", "Wafles", "Galletas",
        "Queso", "Queso suizo", "Queso gouda",
        "Mayonesa", "Mostaza", "Ketchup", "Salsa BBQ", "Salsa especial", "Salsa programación",
        "Salsa tenorio", "Salsa picante", "Salsa de vino tinto",
        "Vegetales", "Tocino", "Pepinillos", "Jalapeños", "Champiñones",
        "Papas", "Soda", "Café", "Helado", "Palza cakes", "Sandwich de helado", "Cupcakes", "Palza pie"
    };


    // Nombre del archivo
    const char* archivo = "inventario.txt";

    // Verificar si el archivo ya existe
    ifstream file(archivo);

    if (file.good()) {
        file.close();

    } else {
        // Si el archivo no existe, inicializar el inventario
        cout << "El archivo " << archivo << " no existe. Creando el inventario..." << endl;
        inicializarInventario(archivo, ingredientes);
    }

    // Leer el inventario actual
    mostrarInventario(archivo);

}
// ---------------------------------

string archivoPromociones = "promociones.txt";

void menu::gestionarOfertas() {
    vector<string> listaNombres;
    vector<string> listaDescripciones;
    vector<double> listaPrecios;

    ifstream archivo(archivoPromociones);
    if (archivo.is_open()) {
        string nombre, descripcion;
        double precio;
        while (getline(archivo, nombre) && getline(archivo, descripcion) && archivo >> precio) {
            archivo.ignore();
            listaNombres.push_back(nombre);
            listaDescripciones.push_back(descripcion);
            listaPrecios.push_back(precio);
        }
        archivo.close();
    }

    int opcion;
    do {
        cout << "Menú:" << endl;
        cout << "1. Agregar oferta" << endl;
        cout << "2. Eliminar oferta" << endl;
        cout << "3. Mostrar ofertas" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        while (cin.fail()) {
            cin.clear();  // Limpiar el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descartar la entrada inválida
            cout << "Entrada inválida. Ingrese un número: ";
            cin >> opcion;
        }


        switch (opcion) {
            case 1: {
                system("cls");
                cout << "\t\t ----- AGREGAR OFERTA ----- \t\t\n\n" << endl;
                string nombre, descripcion;
                double precio;
                cin.ignore(); // Limpiar el buffer antes de leer el nombre
                cout << "Ingrese el nombre de la oferta: ";
                getline(cin, nombre);
                cout << "Ingrese la descripción de la oferta: ";
                getline(cin, descripcion);
                cout << "Ingrese el precio de la oferta: ";
                cin >> precio;

                listaNombres.push_back(nombre);
                listaDescripciones.push_back(descripcion);
                listaPrecios.push_back(precio);

                ofstream archivoAgregar(archivoPromociones, ios::app);
                if (archivoAgregar.is_open()) {
                    archivoAgregar << nombre << endl << descripcion << endl << precio << endl;
                    archivoAgregar.close();
                }
                cout << "Oferta agregada: " << nombre << endl;
                cout << endl;
                system("pause");
                system("cls");
                break;
            }
            case 2: {
                system("cls");
                cout << "\t\t ----- ELIMINAR OFERTA ----- \t\t\n\n" << endl;

                string nombreEliminar;
                cin.ignore(); // Limpiar el buffer antes de leer el nombre
                cout << "Ingrese el nombre de la oferta a eliminar: ";
                getline(cin, nombreEliminar);

                auto it = find(listaNombres.begin(), listaNombres.end(), nombreEliminar);
                if (it != listaNombres.end()) {
                    int index = distance(listaNombres.begin(), it);
                    listaNombres.erase(listaNombres.begin() + index);
                    listaDescripciones.erase(listaDescripciones.begin() + index);
                    listaPrecios.erase(listaPrecios.begin() + index);

                    ofstream archivoEliminar(archivoPromociones);
                    if (archivoEliminar.is_open()) {
                        for (size_t i = 0; i < listaNombres.size(); ++i) {
                            archivoEliminar << listaNombres[i] << endl << listaDescripciones[i] << endl << listaPrecios[i] << endl;
                        }
                        archivoEliminar.close();
                    }
                    cout << "Oferta eliminada: " << nombreEliminar << endl;
                    cout << endl;
                    system("pause");
                    system("cls");
                } else {
                    cout << "La oferta " << nombreEliminar << " no fue encontrada." << endl;
                    cout << endl;
                    system("pause");
                    system("cls");
                }
                break;
            }
            case 3: {
                system("cls");
                if (listaNombres.empty()) {
                    cout << "No hay ofertas disponibles." << endl;
                } else {
                    cout << "OFERTAS DISPONIBLES:" << endl;
                    cout << endl;
                    for (size_t i = 0; i < listaNombres.size(); ++i) {
                        cout << "Nombre: " << listaNombres[i] << endl;
                        cout << "Descripción: " << listaDescripciones[i] << endl;
                        cout << "Precio: $" << listaPrecios[i] << endl;
                        cout << "------------------------" << endl;
                    }
                }
                system("pause");
                system("cls");
                break;
            }
            case 4:
                cout << "Saliendo del programa." << endl;
                system("pause");
                system("cls");
                break;
            default:
                system("cls");
                cout << "Opción no válida. Intente nuevamente." << endl;
                cout << endl;
                break;
        }
    } while (opcion != 4);
}

// ---------------------------------

void menu::administrarclientes(){
    int opcion;

    do {

        cout << "---- ADMINISTRAR CLIENTES ----" << endl;
        cout << "1. Ver ventas por mes" << endl;
        cout << "2. Ver ventas de un cliente" << endl;
        cout << "3. Ver todas las ventas" << endl;
        cout << "4. Salir" << endl;
        cout << "------------------------------" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                verVentasPorMes();
                break;
            case 2:
                verVentasDeCliente();
                break;
            case 3:
                verTodasLasVentas();
                break;
            case 4:
                cout << "Saliendo del menú de administración de clientes." << endl;
                system("cls");
                break;

            default:
                cout << "Opción no válida. Inténtalo de nuevo." << endl;
        }
    } while (opcion != 4);
}

void menu::verVentasPorMes() {

    system("cls");
    cout << "Ingrese el mes y año en formato MM_YYYY (por ejemplo, 02_2023): ";
    string mesYAnio;
    cin.ignore();
    getline(cin,mesYAnio);

    ifstream archivo((mesYAnio + "/ordenes_del_mes.txt").c_str());

    system("cls");

    cout << "Ordenes del: " << mesYAnio << "\n\n";

    if (archivo.is_open()) {
        string line;

        while (getline(archivo, line)) {
            cout << line << endl;
        }

        archivo.close();
    } else {
        cout << "\tError al abrir el archivo de órdenes del mes." << endl;
    }

    cout << endl;
    system("pause");
    system("cls");
}

void menu::verVentasDeCliente() {
    string numeroCarnet;
    cout << "Ingrese el numero de carnet: ";
    cin >> numeroCarnet;

    ifstream archivo("ordenes.txt");

    system("cls");
    cout << "ORDENES DEL CLIENTE CON CI: " << numeroCarnet;
    cout << "\n\n";

    if (archivo.is_open()) {
        string linea;

        while (getline(archivo, linea)) {
            // Buscar la línea que contiene el número de carnet
            size_t pos = linea.find("Carnet o NIT: " + numeroCarnet);

            if (pos != string::npos) {
                // Si se encuentra, imprimir la orden
                cout << linea << endl;

                // Imprimir las líneas siguientes hasta encontrar el separador
                while (getline(archivo, linea) && linea != "-------------------------------------") {
                    cout << linea << endl;
                }
                cout << "-------------------------------------" << endl;
            }
        }

        archivo.close();
    } else {
        cout << "Error al abrir el archivo de órdenes." << endl;
    }

    system("pause");
    system("cls");
}

void menu::verTodasLasVentas() {
    ifstream archivo("ordenes.txt");

    system("cls");

    cout << "----- TODAS LAS ORDENES ----- " << "\n\n";

    if (archivo.is_open()) {
        string line;

        while (getline(archivo, line)) {
            cout << line << endl;
        }

        archivo.close();
    } else {
        cout << "\tError al abrir el archivo de órdenes del mes." << endl;
    }

    cout << endl;
    system("pause");
    system("cls");
}

// --------------------------------------------------

bool menu::validacionTrabajador(informacionCajero& info) {
    ifstream lectura;
    lectura.open("empleados.txt", ios::in);

    string buscarCarnet;
    system("cls");
    cout << "\t\t\t\t***Validación de Trabajador***\t\t\t\t\n" << endl << endl;

    if (lectura.is_open()) {
        cout << "Ingrese el numero de carnet del trabajador: ";
        fflush(stdin);
        getline(cin, buscarCarnet);

        while (!lectura.eof()) {
            getline(lectura, codigoEmpleado);
            getline(lectura, nombre);
            getline(lectura, domicilio);
            getline(lectura, celular);
            getline(lectura, fechaContratacion);

            if (codigoEmpleado == buscarCarnet) {
                cout << "NOMBRE DEL EMPLEADO: " << nombre << endl;
                lectura.close();
                cout << endl;
                system("pause");

                info.nombre = nombre;
                info.numerocarnet = codigoEmpleado;

                return true;  // Se encontró al empleado
            }

            else if(buscarCarnet == "")
            {
                cout << "nCARNET INEXISTENTE" << endl;
                cout << endl;
                system("pause");
                system("cls");
                return false;
            }


            // Leer el próximo código de empleado
            // getline(lectura, codigoEmpleado);
        }

        cout << "\nNo se encontró ningun empleado con el numero de carnet: " << buscarCarnet;
    } else {
        cout << "No se pudo abrir el archivo de empleados." << endl;
    }

    lectura.close();
    pausa();  // Supongo que pausa() es una función que realiza alguna pausa en el programa
    return false;  // No se encontró al empleado
}

void menu::mostrarMenuMcWillys(informacionCajero& info) {
    int opcion;
    Orden orden;

    do {
        system("cls");
        cout << "---- Menú de McWilly's ----" << endl;
        cout << "1. Hamburguesas" << endl;
        cout << "2. Desayunos" << endl;
        cout << "3. Extras" << endl;
        cout << "4. Postres" << endl;
        cout << "5. Promociones" << endl;
        cout << "6. Terminar Orden y Generar Factura" << endl;
        cout << "------------------------------" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                system("cls");
                mostrarMenuHamburguesas(orden, info);
                break;
            case 2:
                system("cls");
                mostrarMenuDesayunos(orden, info);
                break;
            case 3:
                system("cls");
                mostrarMenuExtras(orden, info);
                break;
            case 4:
                system("cls");
                mostrarMenuPostres(orden, info);
                break;
            case 5:
                system("cls");
                venderOfertas(orden);
                break;
            case 6:
                system("cls");
                cout << "Terminando orden y generando factura..." << endl;
                cout << "Ingrese el nombre del cliente: ";
                cin.ignore();
                getline(cin, orden.nombreCliente);
                cout << "Ingrese el carnet o NIT del cliente: ";
                getline(cin, orden.carnetONit);
                cout << "Ingrese la fecha: ";
                getline(cin, orden.fechaVenta);

                generarFactura(orden, info);
                guardarOrdenMes(orden);
                guardarOrden(orden);
                break;
            default:
                cout << "Opción no válida. Por favor, elige una opción válida." << endl;
                break;
        }
    } while (opcion != 6);
}

vector<string> descripciones = {
    "Un wrap de pollo con un toque especial de McWilly’s, relleno de sabiduría informática y salsa secreta de programación.\n",
    "Una hamburguesa con un montón de tocino y pollo branch con una mezcla secreta de código, servida con una salsa BBQ de McWilly’s.\n",
    "Una hamburguesa con doble procesador de carne, chips de datos crujientes y una salsa algoritmo especial.\n",
    "Una hamburguesa especial con 'bytes' extra de sabor y una salsa de 'bits' única.\n",
    "Una hamburguesa con carne de res, salsa de depuración y una capa extra de 'bugs' crujientes para los amantes de la caza de errores.\n",
    "Una hamburguesa gourmet con carne de res de alta calidad, queso suizo y una salsa de programación maestra creada por Willy Tenorio.\n",
    "Una hamburguesa con carne de pollo a la parrilla, tocino y una mezcla secreta de 'bits' y 'bytes' que solo encontrarás en McWilly's.\n",
    "Una delicia llena de ingredientes frescos y creativos que dejaran satisfecho tu paladar y tu mente.\n",
    "Una hamburguesa picante con carne de ternera, jalapeños y una capa de seguridad informática que protegerá tu paladar de cualquier amenaza.\n",
    "Una hamburguesa con capas de carne, pollo y tocino, junto con una variedad de ingredientes para satisfacer todas tus necesidades de programación.\n",
    "Una hamburguesa hecha por willy tenorio con los máximos secretos culinarios de la abuelita tenorio.\n",
    "Una variacion de la tenorio con doble carne y doble amor.\n",
    "Una mini tenorio con java fries y una deliciosa Palza Pie, todo esto acompañado de un juguete SUPER WILLY\n",
    "Una hamburguesa hecha con ingredientes de una deliciosa sopita con su especialidad “la coronel” una salsa extrapicante insuperable.\n",
    "Esta hamburguesa combina creatividad y programación en cada capa. El pan multicolor representa la diversidad de ideas, la carne es una mezcla innovadora, el queso aporta lógica, y la lechuga añade diversión con humor. Los tomates ilustran conceptos, la cebolla optimiza, la mostaza es atrevida pero planificada, y el ketchup representa la variedad de lenguajes de programación. Los pepinillos aportan soluciones ingeniosas.\n",
    "Una hamburguesa de carne premium, bacon ahumado, queso gouda derretido, champiñones en salsa de vino tinto, cebolla caramelizada y vegetales frescos. La fusión perfecta de la pasión de Alan por los autos y la elegancia de Lamborghini.\n",
};

vector<double>precios = {
    25,
    30,
    30,
    25,
    30,
    35,
    35,
    30,
    35,
    40,
    50,
    65,
    35,
    25,
    69,
    77,
};

vector<string> Hamburguesas = {
    "Tenorio's Chicken Code Wrap.",
    "Git Burger.",
    "McCodeBurger.",
    "Willy's Byte Burger.",
    "La 'Bug Buster' Burger.",
    "La 'Code Master' Burger.",
    "La 'Bit Byte' Burger.",
    "'Willy's Veggie Code Delight.",
    "La 'Cybersecurity' Burger.",
    "La 'Full Stack' Burger.",
    "LA TENORIO.",
    "LA TENORIO DOBLE.",
    "LA WILLY FELIZ.",
    "LA CHRIS BURGUER.",
    "LA ROMANA BURGUER.",
    "Alan's Lamborghini Dream Burger.",
    };

void menu::mostrarMenuHamburguesas(Orden& orden, informacionCajero& info) {
    cout << "---- Menú de Hamburguesas ----" << endl;
    cout << "1. Tenorio's Chicken Code Wrap - 25Bs" << endl;
    cout << "2. Git Burger - 30Bs" << endl;
    cout << "3. McCodeBurger - 30Bs" << endl;
    cout << "4. Willy's Byte Burger - 25Bs" << endl;
    cout << "5. La 'Bug Buster' Burger - 30Bs" << endl;
    cout << "6. La 'Code Master' Burger - 35Bs" << endl;
    cout << "7. La 'Bit Byte' Burger - 35Bs" << endl;
    cout << "8. 'Willy's Veggie Code Delight' - 30Bs" << endl;
    cout << "9. La 'Cybersecurity' Burger - 35Bs" << endl;
    cout << "10. La 'Full Stack' Burger - 40Bs" << endl;
    cout << "11. LA TENORIO - 50Bs" << endl;
    cout << "12. LA TENORIO DOBLE - 65Bs" << endl;
    cout << "13. LA WILLY FELIZ - 35Bs" << endl;
    cout << "14. LA CHRIS BURGUER - 25Bs" << endl;
    cout << "15. LA ROMANA BURGUER - 69Bs" << endl;
    cout << "16. Alan's Lamborghini Dream Burger - 77Bs" << endl;
    cout << "17. Volver al Menú Principal" << endl;
    cout << "------------------------------" << endl;

    int seleccion;
    cout << "Selecciona una hamburguesa para ver la descripción: ";
    cin >> seleccion;

    if (seleccion >= 1 && seleccion <= descripciones.size())
    {
        cout << endl;
        cout << "DESCRIPCIÓN: " << descripciones[seleccion - 1] << endl;

        int cantidad;
        vector<int> cantidades(descripciones.size(), 0);

        // Validar que la cantidad sea mayor que cero

        cantidades[seleccion - 1] += cantidad;  // Almacenar la cantidad seleccionada



        int opcion;
        cout << "1. Volver al Menú Principal" << endl;
        cout << "2. Añadir artículo en el pedido." << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1:
                system("cls");
                mostrarMenuMcWillys(info);
                break;
            case 2:

                cout << endl;
                cout << "Ingrese la cantidad deseada: ";
                cin >> cantidad;

                if (cantidad > 0)
                {
                    orden.productos.push_back(Hamburguesas[seleccion - 1] + " x" + to_string(cantidad));
                    orden.preciosEnConjunto.push_back(precios[seleccion - 1] * cantidad);
                    orden.total += precios[seleccion - 1] * cantidad;
                    cout << endl;
                    cout << "¡Producto agregado a la orden!\n" << endl;
                    system("pause");
                }
                else {
                    cout << "La cantidad debe ser mayor que cero." << endl;
                }

                switch(seleccion)
                {
                    case 1:
                        restarStock(archivo, "pollo", 0.5*cantidad);
                        restarStock(archivo, "vegetales", 1*cantidad);
                        restarStock(archivo, "queso", 1*cantidad);
                        restarStock(archivo, "salsas y extras", 1*cantidad);
                        break;
                    case 2:
                        restarStock(archivo, "carne", 1*cantidad);
                        restarStock(archivo, "pan", 1*cantidad);
                        restarStock(archivo, "pollo", 1*cantidad);
                        restarStock(archivo, "vegetales", 1*cantidad);
                        restarStock(archivo, "queso", 1*cantidad);
                        restarStock(archivo, "salsas y extras", 1*cantidad);
                        break;
                    case 3:
                        restarStock(archivo, "carne", 2*cantidad);
                        restarStock(archivo, "pan", 1*cantidad);
                        restarStock(archivo, "vegetales", 1*cantidad);
                        restarStock(archivo, "queso", 2*cantidad);
                        restarStock(archivo, "salsas y extras", 1*cantidad);
                        break;
                    case 4:
                        restarStock(archivo, "carne", 1*cantidad);
                        restarStock(archivo, "pan", 1*cantidad);
                        restarStock(archivo, "vegetales", 1*cantidad);
                        restarStock(archivo, "queso", 1*cantidad);
                        restarStock(archivo, "salsas y extras", 1*cantidad);
                        break;
                    case 5:
                        restarStock(archivo, "carne", 1*cantidad);
                        restarStock(archivo, "pan", 1*cantidad);
                        restarStock(archivo, "vegetales", 1*cantidad);
                        restarStock(archivo, "queso", 1*cantidad);
                        restarStock(archivo, "salsas y extras", 2*cantidad);
                        break;
                    case 6:
                        restarStock(archivo, "carne", 2*cantidad);
                        restarStock(archivo, "pan", 1*cantidad);
                        restarStock(archivo, "vegetales", 1*cantidad);
                        restarStock(archivo, "queso", 2*cantidad);
                        restarStock(archivo, "salsas y extras", 2*cantidad);
                        break;
                    case 7:
                        restarStock(archivo, "pollo", 1*cantidad);
                        restarStock(archivo, "pan", 1*cantidad);
                        restarStock(archivo, "vegetales", 1*cantidad);
                        restarStock(archivo, "queso", 1*cantidad);
                        restarStock(archivo, "salsas y extras", 2*cantidad);
                        break;
                    case 8:
                        restarStock(archivo, "carne", 1*cantidad);
                        restarStock(archivo, "pan", 1*cantidad);
                        restarStock(archivo, "vegetales", 2*cantidad);
                        restarStock(archivo, "queso", 1*cantidad);
                        break;
                    case 9:
                        restarStock(archivo, "carne", 2*cantidad);
                        restarStock(archivo, "pan", 1*cantidad);
                        restarStock(archivo, "queso", 1*cantidad);
                        restarStock(archivo, "salsas y extras", 1*cantidad);
                        break;
                    case 10:
                        restarStock(archivo, "carne", 1*cantidad);
                        restarStock(archivo, "pollo", 1*cantidad);
                        restarStock(archivo, "pan", 1*cantidad);
                        restarStock(archivo, "queso", 2*cantidad);
                        restarStock(archivo, "salsas y extras", 2*cantidad);
                        break;
                    case 11:
                        restarStock(archivo, "carne", 1*cantidad);
                        restarStock(archivo, "pan", 1*cantidad);
                        restarStock(archivo, "queso", 1*cantidad);
                        restarStock(archivo, "salsas y extras", 2*cantidad);
                        break;
                    case 12:
                        restarStock(archivo, "carne", 2*cantidad);
                        restarStock(archivo, "pan", 1*cantidad);
                        restarStock(archivo, "queso", 2*cantidad);
                        restarStock(archivo, "salsas y extras", 3*cantidad);
                        break;
                    case 13:
                        restarStock(archivo, "carne", 1*cantidad);
                        restarStock(archivo, "pan", 1*cantidad);
                        restarStock(archivo, "queso", 1*cantidad);
                        restarStock(archivo, "masa reposteria", 1*cantidad);
                        restarStock(archivo, "extras", 1*cantidad);
                        break;
                    case 14:
                        restarStock(archivo, "carne", 1*cantidad);
                        restarStock(archivo, "pan", 1*cantidad);
                        restarStock(archivo, "queso", 1*cantidad);
                        restarStock(archivo, "salsas y extras", 1*cantidad);
                        break;
                    case 15:
                        restarStock(archivo, "carne", 2*cantidad);
                        restarStock(archivo, "pan", 1*cantidad);
                        restarStock(archivo, "queso", 1*cantidad);
                        restarStock(archivo, "vegetales", 2*cantidad);
                        restarStock(archivo, "salsas y extras", 2*cantidad);
                        break;
                    case 16:
                        restarStock(archivo, "carne", 2*cantidad);
                        restarStock(archivo, "pan", 1*cantidad);
                        restarStock(archivo, "queso", 2*cantidad);
                        restarStock(archivo, "vegetales", 2*cantidad);
                        restarStock(archivo, "salsas y extras", 2*cantidad);
                        break;
                }
                break;
            default:
                cout << "Opción no válida." << endl;
                break;
        }
    } else {
        cout << "Selección no válida." << endl;
    }
}

vector<string> descripciones2 = {
    "Unos Palza cakes llenos de codigo limpio con un toque de chocolate willy.\n",
    "Unos wafles realizados con cariño por Willy.\n",
    "Una willy hot hecha con pan Palza y una enorme Willy salchicha.\n",
};

vector<double>precios2 = {
    15,
    15,
    10,
};

vector<string> desayunos = {
    "Los Palza cakes.",
    "Los WWWafles.",
    "La hot.",
    };

void menu::mostrarMenuDesayunos(Orden& orden, informacionCajero& info) {
    cout << "---- Menú de Desayunos ----" << endl;
    cout << "1. Los Palza cakes - 15Bs" << endl;
    cout << "2. Los WWWafles - 15Bs" << endl;
    cout << "3. La Hot - 10Bs" << endl;
    cout << "4. Volver al Menú Principal" << endl;
    cout << "------------------------------" << endl;

    int seleccion;
    cout << "Selecciona un desayuno para ver la descripción: ";
    cin >> seleccion;

    if (seleccion >= 1 && seleccion <= descripciones2.size()) {
        cout << endl;
        cout << "DESCRIPCIÓN: " << descripciones2[seleccion - 1] << endl;

        int cantidad;
        vector<int> cantidades2(descripciones2.size(), 0);
        cantidades2[seleccion - 1] += cantidad;



        int opcion;
        cout << "1. Volver al Menú Principal" << endl;
        cout << "2. Añadir artículo en el pedido." << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarMenuMcWillys(info);
                break;
            case 2:

                cout << endl;
                cout << "Ingrese la cantidad deseada: ";
                cin >> cantidad;

                if (cantidad > 0)
                {
                    orden.productos.push_back(desayunos[seleccion - 1] + " x" + to_string(cantidad));
                    orden.preciosEnConjunto.push_back(precios2[seleccion - 1] * cantidad);
                    orden.total += (precios2[seleccion - 1]*cantidad);
                    cout << endl;
                    cout << "¡Producto agregado a la orden!" << endl;
                    cout << endl;
                    system("pause");
                }
                else
                {
                    cout << "La cantidad debe ser mayor que cero." << endl;
                }

                switch(seleccion)
                {
                    case 1:
                    {
                       restarStock(archivo, "masa reposteria", 0.5*cantidad);
                       restarStock(archivo, "extras", 0.5*cantidad);
                    }
                    case 2:
                    {
                       restarStock(archivo, "masa reposteria", 0.5*cantidad);
                       restarStock(archivo, "extras", 0.5*cantidad);
                    }
                    case 3:
                    {
                       restarStock(archivo, "masa reposteria", 0.5*cantidad);
                       restarStock(archivo, "extras", 0.5*cantidad);
                    }

                }

                break;
            default:
                cout << "Opción no válida." << endl;
                break;
        }
    } else {
        cout << "Selección no válida." << endl;
    }
}

vector<string> descripciones3 = {
    "Trozos de pollo empanizados con el lenguaje de programación Python, servidos con una salsa de syntax.\n",
    "Una bebida refrescante con consultas SQL burbujeante.\n",
    "Un café latte con un toque de magia JavaBean, la especialidad de Willy Tenorio.\n",
    "Un postre épico que te hace sentir como un ingeniero de software infinito, con capas de conocimiento ilimitado.\n",
    "Papas fritas doradas y crujientes con un toque de café Java para esa energía extra.\n",
};

vector<double>precios3 = {
    25,
    10,
    15,
    20,
    20,
};

vector<string> extras = {
        "Python Nuggets",
        "SQL Soda",
        "JavaBean Latte",
        "Ingeniero Infinito Sundae",
        "Java Fries",
    };


void menu::mostrarMenuExtras(Orden& orden, informacionCajero& info) {
    cout << "---- Menú de Extras ----" << endl;
    cout << "1. Python Nuggets - 25Bs" << endl;
    cout << "2. SQL Soda - 10Bs" << endl;
    cout << "3. JavaBean Latte - 15Bs" << endl;
    cout << "4. Ingeniero Infinito Sundae - 20Bs" << endl;
    cout << "5. Java Fries - 20Bs" << endl;
    cout << "6. Volver al Menú Principal" << endl;
    cout << "------------------------------" << endl;

    int seleccion;
    cout << "Selecciona un extra para ver la descripción: ";
    cin >> seleccion;

    if (seleccion >= 1 && seleccion <= descripciones3.size())
    {
        cout << endl;
        cout << "DESCRIPCIÓN: " << descripciones3[seleccion - 1] << endl;

        int cantidad;
        vector<int> cantidades3(descripciones3.size(), 0);

        cantidades3[seleccion - 1] += cantidad;  // Almacenar la cantidad seleccionada

        int opcion;
        cout << "1. Volver al Menú Principal" << endl;
        cout << "2. Añadir articulo en el pedido" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarMenuMcWillys(info);
                break;
            case 2:

                cout << endl;
                cout << "Ingrese la cantidad deseada: ";
                cin >> cantidad;
                cout << endl;

                if (cantidad > 0)
                {
                    orden.productos.push_back(extras[seleccion - 1] + " x" + to_string(cantidad));
                    orden.preciosEnConjunto.push_back(precios3[seleccion - 1] * cantidad);
                    orden.total += (precios3[seleccion - 1]*cantidad);
                    cout << "¡Producto agregado a la orden!" << endl;
                    cout << endl;
                    system("pause");
                }

                else {
                    cout << "La cantidad debe ser mayor que cero." << endl;
                }

                switch(seleccion)
                {
                    case 1:
                    {
                       restarStock(archivo, "pollo", 0.5*cantidad);
                       restarStock(archivo, "salsas y extras", 1*cantidad);
                    }
                    case 2:
                    {
                       restarStock(archivo, "soda", 0.5*cantidad);
                    }
                    case 3:
                    {
                       restarStock(archivo, "cafe", 0.25*cantidad);
                    }
                    case 4:
                    {
                       restarStock(archivo, "helado", 0.25*cantidad);
                    }
                    case 5:
                    {
                       restarStock(archivo, "papas", 0.5*cantidad);
                       restarStock(archivo, "salsas y extras", 1*cantidad);
                    }

                }

                break;
            default:
                cout << "Opción no válida." << endl;
                break;
        }
    } else {
        cout << "Selección no válida." << endl;
    }
}

vector<string> descripciones4 = {
    "Galletas recién horneadas con chips de chocolate y trozos de código incrustados para los amantes de la programación dulce.\n",
    "Dos galletas de HTML rellenas de helado de tu elección, una experiencia fresca y sabrosa.\n",
    "Helado con chispas de datos crujientes y una selección de coberturas para personalizar tu postre.\n",
    "Cupcakes de vainilla con un toque de Git Commit, decorados con mensajes de confirmación de código.\n",
    "Paletas heladas con sabores de frutas frescas y forma de serpiente en honor a Python.\n",
    "Un Pie de la familia Palza hecha principalmente de mango.\n",
};

vector<double>precios4 = {
    5,
    8,
    10,
    15,
    5,
    10,
};

vector<string> postres = {
        "Code Crunch Cookies",
        "HTML Ice Cream Sandwich",
        "Data Byte Delight",
        "Git Commit Cupcake",
        "Python Popsicles",
        "Palza Pie"
    };

void menu::mostrarMenuPostres(Orden& orden, informacionCajero& info) {
    cout << "---- Menú de Postres ----" << endl;
    cout << "1. Code Crunch Cookies - 5Bs" << endl;
    cout << "2. HTML Ice Cream Sandwich - 8Bs" << endl;
    cout << "3. Data Byte Delight - 10Bs" << endl;
    cout << "4. Git Commit Cupcake - 15Bs" << endl;
    cout << "5. Python Popsicles - 5Bs" << endl;
    cout << "6. Palza Pie - 10Bs" << endl;
    cout << "7. Volver al Menú Principal" << endl;
    cout << "------------------------------" << endl;

    int seleccion;
    cout << "Selecciona un postre para ver la descripción: ";
    cin >> seleccion;

    if (seleccion >= 1 && seleccion <= descripciones4.size()) {
        cout << endl;
        cout << "DESCRIPCIÓN: " << descripciones4[seleccion - 1] << endl;


        int cantidad;
        vector<int> cantidades4(descripciones4.size(), 0);
        cantidades4[seleccion - 1] += cantidad;

        int opcion;
        cout << "1. Volver al Menú Principal" << endl;
        cout << "2. Añadir artículo en el pedido." << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        cout << endl;

        switch (opcion) {
            case 1:
                mostrarMenuMcWillys(info);
                break;
            case 2:

                cout << "Ingrese la cantidad deseada: ";
                cin >> cantidad;
                cout << endl;

                if (cantidad > 0) {
                    orden.productos.push_back(postres[seleccion - 1] + " x" + to_string(cantidad));
                    orden.preciosEnConjunto.push_back(precios4[seleccion - 1] * cantidad);
                    orden.total += (precios4[seleccion - 1])*cantidad;
                    cout << "¡Producto agregado a la orden!" << endl;
                    cout << endl;
                    system("pause");
                } else {
                    cout << "La cantidad debe ser mayor que cero." << endl;
                }

                switch(seleccion)
                {
                    case 1:
                    {
                       restarStock(archivo, "masa reposteria", 0.5*cantidad);
                       restarStock(archivo, "extras", 0.5*cantidad);
                    }
                    case 2:
                    {
                       restarStock(archivo, "helado", 0.5*cantidad);
                       restarStock(archivo, "masa reposteria", 0.5*cantidad);
                    }
                    case 3:
                    {
                       restarStock(archivo, "helado", 0.5*cantidad);
                       restarStock(archivo, "extras", 0.5*cantidad);
                    }
                    case 4:
                    {
                       restarStock(archivo, "masa reposteria", 0.50*cantidad);
                       restarStock(archivo, "extras", 0.50*cantidad);
                    }
                    case 5:
                    {
                       restarStock(archivo, "helado", 0.25*cantidad);
                    }
                    case 6:
                    {
                       restarStock(archivo, "masa reposteria", 0.5*cantidad);
                       restarStock(archivo, "extras", 0.5*cantidad);
                    }

                }

                break;
            default:
                cout << "Opción no válida." << endl;
                break;
        }
    } else {
        cout << "Selección no válida." << endl;
    }
}

// --------------------------------------------------

void menu::venderOfertas(Orden& orden)
{
    vector<string> listaNombres;
    vector<string> listaDescripciones;
    vector<double> listaPrecios;

    const string archivoPromociones = "promociones.txt";
    ifstream archivo(archivoPromociones);
    if (archivo.is_open()) {
        string nombre, descripcion;
        double precio;
        while (getline(archivo, nombre) && getline(archivo, descripcion) && archivo >> precio) {
            archivo.ignore();
            listaNombres.push_back(nombre);
            listaDescripciones.push_back(descripcion);
            listaPrecios.push_back(precio);
        }
        archivo.close();
    }

    int opcion;
    do {
        cout << "Menú:" << endl;
        cout << "1. Mostrar ofertas disponibles" << endl;
        cout << "2. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        system ("cls");

        switch (opcion) {
            case 1: {
                if (listaNombres.empty()) {
                    cout << "No hay ofertas disponibles." << endl;
                } else {
                    cout << "Ofertas disponibles:" << endl;
                    for (size_t i = 0; i < listaNombres.size(); ++i) {
                        cout << i + 1 << ". Nombre: " << listaNombres[i] << endl;
                        cout << "   Descripción: " << listaDescripciones[i] << endl;
                        cout << "   Precio: $" << listaPrecios[i] << endl;
                        cout << "------------------------" << endl;
                    }

                    int opcionOferta;
                    cout << "Seleccione una oferta (1-" << listaNombres.size() << "): ";
                    cin >> opcionOferta;

                    if (opcionOferta >= 1 && opcionOferta <= listaNombres.size()) {
                        int cantidad;
                        cout << "Ingrese la cantidad: ";
                        cin >> cantidad;

                        if (cantidad > 0) {

                            int idOferta = opcionOferta - 1;
                            string nombre = listaNombres[idOferta];
                            double totalPagar = listaPrecios[idOferta] * cantidad;

                            orden.productos.push_back("Promoción: " + nombre + " x" + to_string(cantidad));
                            orden.preciosEnConjunto.push_back(totalPagar);
                            orden.total += totalPagar;
                            cout << endl;
                            cout << "¡Producto agregado a la orden!" << endl;
                            cout << endl;

                            // cout << "Total a pagar: $" << totalPagar << endl;

                        } else {
                            cout << "La cantidad debe ser mayor que cero." << endl;
                        }
                    } else {
                        cout << "Opción no válida." << endl;
                    }
                }
                system("pause");
                system("cls");
                break;
            }
            case 2:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción no válida. Intente nuevamente." << endl;
                break;
        }
    } while (opcion != 2);
}

// --------------------------------------------------

/* void menu::generarFactura(const Orden& orden) {
    system("cls");
    cout << "\t\t\t\tFACTURA GENERADA\t\t\t\t\n" << endl;
    cout << "Cliente: " << orden.nombreCliente << endl;
    cout << "Carnet o NIT: " << orden.carnetONit << endl;
    cout << "Fecha de venta: " << orden.fechaVenta << endl;
    cout << endl;
    cout << "Productos:" << endl;

    for (const string& producto : orden.productos) {
        cout << "\t- " << producto << endl;
    }

    cout << endl;
    cout << "Total a pagar: " << orden.total << " Bs" << endl;
} */


void menu::obtenerYMostrarHoraActual() {
    // Obtener la hora actual
    time_t tiempoActual = time(0);
    tm* tiempoLocal = localtime(&tiempoActual);

    // Imprimir la hora actual
    cout << tiempoLocal->tm_hour << ":" << tiempoLocal->tm_min << ":" << tiempoLocal->tm_sec;

}


void menu::generarFactura(const Orden& orden, informacionCajero& info) {
    system("cls");

    // Configurar la salida para imprimir dos decimales en los precios
    cout << fixed << setprecision(2);
    cout << "\t\t\t\tFACTURA GENERADA\t\t\t\t\n" << endl;
    cout << "Restaurantes Ciudad de La Paz" << endl;
    cout << "Green tower, Edificio Horizonte, Av .Ballivián 1063, La Paz" << endl;
    cout << "Factura Nº: " << endl;
    cout << "Cajero: " << info.nombre << endl;
    cout << "Codigo cajero: " << info.numerocarnet << endl;
    cout << "Fecha de venta: " << orden.fechaVenta << endl;
    cout << "Hora: ";
    obtenerYMostrarHoraActual();
    cout << endl;
    cout << "Cliente: " << orden.nombreCliente << endl;
    cout << "Carnet o NIT: " << orden.carnetONit << endl;
    cout << endl;

    cout << "Detalle de la orden:" << endl;

    for (size_t i = 0; i < orden.productos.size(); ++i) {
        cout << "\t- " << orden.productos[i] << "\t" << orden.preciosEnConjunto[i] << endl;
    }

    cout << endl;
    // cout << "Subtotal: " << orden.subtotal << " Bs" << endl;
    // cout << "Impuestos (" << (orden.impuestosPorcentaje * 100) << "%): " << orden.impuestos << " Bs" << endl;
    // cout << "Descuento: " << orden.descuento << " Bs" << endl;
    cout << "Total a pagar: " << orden.total << " Bs" << endl;

    // Puedes agregar más detalles según sea necesario

    cout << "\n¡Gracias por su compra!\n" << endl;
    cout << "Si requiere factura solicitela en este retaurante o para su mayor comodidad y rapidez obtengala en www.facturacionmcwills.com.bo" << endl;
}


void menu::guardarOrdenMes(const Orden& orden) {
    // Obtener el mes y año de la orden
    tm timeinfo = {};
    istringstream ss(orden.fechaVenta);
    ss >> get_time(&timeinfo, "%d/%m/%Y");

    if (ss.fail()) {
        cout << "Error al obtener la fecha de la orden." << endl;
        return;
    }

    ostringstream mesYAnio;
    mesYAnio << put_time(&timeinfo, "%m_%Y");

    string rutaCarpeta = mesYAnio.str();

    struct stat info;
    if (stat(rutaCarpeta.c_str(), &info) != 0) {
        // La carpeta no existe, crearla
        if (system(("mkdir " + rutaCarpeta).c_str()) != 0) {
            cerr << "Error al crear la carpeta del mes." << endl;
            return;
        }
    }


    // Crear la carpeta del mes si no existe



    // Crear un nombre de archivo único para la orden
    string nombreArchivo = rutaCarpeta + "/orden_";

    // Encontrar el número de archivo único
    int numeroArchivo = 1;
    while (ifstream(nombreArchivo + to_string(numeroArchivo) + ".txt")) {
        numeroArchivo++;
    }

    nombreArchivo += to_string(numeroArchivo);

    // Guardar la orden en el archivo individual
    ofstream archivo(nombreArchivo + ".txt", ios::app);

    if (archivo.is_open()) {
        archivo << "Cliente: " << orden.nombreCliente << ", Carnet o NIT: " << orden.carnetONit << ", Fecha de venta: " << orden.fechaVenta << endl;
        archivo << "Productos:" << endl;

        for (const string& producto : orden.productos) {
            archivo << "- " << producto << endl;
        }

        archivo << "Total a pagar: " << orden.total << " Bs" << endl;
        archivo << "-------------------------------------" << endl;

        archivo.close();
    } else {
        cout << "Error al abrir el archivo de órdenes individuales." << endl;
        return;
    }

    // Guardar la orden en el archivo del mes
    string archivoMes = rutaCarpeta + "/ordenes_del_mes.txt";
    ofstream archivoMesStream(archivoMes, ios::app);

    if (archivoMesStream.is_open()) {
        archivoMesStream << "Cliente: " << orden.nombreCliente << ", Carnet o NIT: " << orden.carnetONit << ", Fecha de venta: " << orden.fechaVenta << endl;
        archivoMesStream << "Productos:" << endl;

        for (const string& producto : orden.productos) {
            archivoMesStream << "- " << producto << endl;
        }

        archivoMesStream << "Total a pagar: " << orden.total << " Bs" << endl;
        archivoMesStream << "-------------------------------------" << endl;

        archivoMesStream.close();
    } else {
        cout << "Error al abrir el archivo de órdenes del mes." << endl;
    }
}


void menu::guardarOrden(const Orden& orden) {
    ofstream archivo("ordenes.txt", ios::app);  // Abre el archivo en modo de apendizaje

    if (archivo.is_open()) {
        archivo << "Cliente: " << orden.nombreCliente << ", Carnet o NIT: " << orden.carnetONit << ", Fecha de venta: " << orden.fechaVenta << endl;
        archivo << "Productos:" << endl;

        for (const string& producto : orden.productos) {
            archivo << "- " << producto << endl;
        }

        archivo << "Total a pagar: " << orden.total << " Bs" << endl;
        archivo << "-------------------------------------" << endl;

        archivo.close();

        cout << "\nOrden guardada correctamente.\n" << endl;

        system ("pause");
    } else {
        cout << "Error al abrir el archivo de órdenes." << endl;
    }
}
// --------------------------------------------------

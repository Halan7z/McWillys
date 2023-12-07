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
struct Orden {
    vector<string> productos;
    double total;
    string nombreCliente;
    string carnetONit;
};
// ------------------------------------------------------------


// ------------------------------------------------------------
struct Ingrediente {
    string nombre;
    int stock;
};
//-------------------------------------------------------------


// Funci�n para inicializar el inventario con un valor de 1000 para cada ingrediente
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

// Funci�n para actualizar el stock de un ingrediente
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
                cout << "�Alerta! Ya no queda stock de " << ingrediente << "." << endl;
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

    cout << "Stock de " << ingrediente << " actualizado exitosamente." << endl;
}

// Funci�n para aumentar stock de un ingrediente
void aumentarStock(const char *archivo, const string &ingrediente, int cantidad) {


    actualizarStock(archivo, ingrediente, cantidad);
    cout << endl;
    system("pause");
    system("cls");
}

// Funci�n para restar stock de un ingrediente
void restarStock(const char *archivo, const string &ingrediente, int cantidad) {
    actualizarStock(archivo, ingrediente, -cantidad);

}

// Funci�n para mostrar el inventario
void mostrarInventario(const char *archivo) {
    ifstream readFile(archivo);
    string line;

    cout << "Inventario actual:" << endl;
    while (getline(readFile, line)) {
        cout << line << endl;
    }

    cout << endl;
    system("pause");
    system("cls");
}

void administrarStockIngredientes() {
    // Lista de ingredientes
    vector<string> ingredientes = {
        "carnes", "pan", "vegetales", "queso", "salsas y extras",
        "pollo", "soda", "cafe", "helado", "papas", "masa reposteria", "extras"
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

void desplegarMenu() {
    bool ejecucionTerminada = false;

    while (!ejecucionTerminada) {
        int opcion;
        cout << "Menu:" << endl;
        cout << "1. Mostrar inventario actual" << endl;
        cout << "2. Agregar stock" << endl;
        cout << "3. Volver al menu para Gerente" << endl;
        cout << "Ingresa la opci�n: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                system("cls");
                administrarStockIngredientes();
                break;
            case 2:

            {
                system("cls");
                vector<string> ingredientes = {
                    "carnes", "pan", "vegetales", "queso", "salsas y extras",
                    "pollo", "soda", "cafe", "helado", "papas", "masa reposteria", "extras"
                };

                string ingrediente;
                int cantidad;

                cout << "Seleccione un ingrediente para aumentar el stock:" << endl;
                for (int i = 0; i < ingredientes.size(); ++i) {
                    cout << i + 1 << ". " << ingredientes[i] << endl;
                }

                int seleccion;
                cout << "Ingresa el n�mero correspondiente al ingrediente: ";
                cin >> seleccion;

                if (seleccion >= 1 && seleccion <= ingredientes.size()) {
                    ingrediente = ingredientes[seleccion - 1];

                    cout << "Ingrese la cantidad deseada: ";
                    cin >> cantidad;

                    if (cantidad > 0) {
                        aumentarStock(archivo, ingrediente, cantidad);
                    } else {
                        cout << "La cantidad debe ser mayor que cero." << endl;
                    }
                } else {
                    cout << "Selecci�n no v�lida." << endl;
                }
            }


                break;

            case 3:
                ejecucionTerminada = true;
                system("cls");
                break;
            default:
                cout << "Opci�n no v�lida. Por favor ingresa una opci�n v�lida." << endl;
                break;
        }
    }
}

// ------------------------------------------------------------

class menu
{
private:
    string nombre;
    string domicilio;
    string celular;
    string fechaContratacion;
    string codigoEmpleado;

public:
    void contratarEmpleado();
    void despedirEmpleado();
    void menuPrincipal();
    void buscarEmpleado();
    void gestionarOfertas();

    void mostrarMenuMcWillys();
    void mostrarMenuHamburguesas(Orden& orden);
    void mostrarMenuDesayunos(Orden& orden);
    void mostrarMenuExtras(Orden& orden);
    void mostrarMenuPostres(Orden& orden);
    void agregarArticulo();
    void venderOfertas();

    void venderArticulo(Orden& orden);
    void generarFactura(const Orden& orden);
    void guardarOrden(const Orden& orden);
};

void pausa();
void error();
void comprobarArchivo();
void esperarSegundo();


void esperarSegundo() {
    clock_t inicio = clock();
    while (static_cast<double>(clock() - inicio) / CLOCKS_PER_SEC < 1.0) {}
}

void menu::menuPrincipal()
{
    setlocale(LC_ALL, "");
    string contrasenaGerente = "willyporsiempre2";
    string contrasenaTrabajador = "1985";
    string contrasenaUsuarioNormal = "contrasena";
    int opcion;
    bool ejecucionTerminada = false; // Variable para controlar la finalizaci�n
    bool mostrarMensajeAutodestruccion = false; // Variable para mostrar el mensaje de autodestrucci�n

    // Imprimir un mensaje de bienvenida y la hamburguesa con caracteres ASCII
    cout << "�Bienvenidos a Mc Willy's!" << endl;
    cout << "Presione cualquier tecla para continuar" << endl;
    cout << endl;
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

    cin.ignore(); // Esperar a que el usuario presione una tecla

    do {
        int intentos = 3;
        bool accesoPermitido = false;

        cout << "Men� Principal" << endl;
        cout << "1. Opci�n para Gerente" << endl;
        cout << "2. Opci�n para Trabajador" << endl;
        cout << "3. Opci�n para Usuario Normal" << endl;
        cout << "4. Salir" << endl;
        cout << "Selecciona una opci�n: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                system("cls");
                string inputContrasena;
                do {

                    cout << "Por favor, ingresa la contrase�a para Gerente: ";
                    cin >> inputContrasena;
                    if (inputContrasena == contrasenaGerente) {
                        system("cls");

                        cout << "Has seleccionado la opci�n para Gerente.\n" << endl;
                        system("pause");
                        system("cls");

                        accesoPermitido = true;
                        bool ejecucionTerminada = false;
                        while (!ejecucionTerminada) {
                                int opcion;
                                cout << "Menu para Gerente:" << endl;
                                cout << "1. Contratar empleado" << endl;
                                cout << "2. Despedir empleado" << endl;
                                cout << "3. Buscar empleado" << endl;
                                cout << "4. Administrar Stock de Ingredientes" << endl; // Nueva opci�n
                                cout << "5. Administrar Ofertas y Promociones" << endl; // Nueva opci�n
                                cout << "6. Salir" << endl;
                                cout << "Ingresa la opci�n: ";
                                cin >> opcion;

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
                                    ejecucionTerminada = true;
                                    system("cls");
                                    break;
                                default:
                                    cout << "Opci�n no v�lida. Por favor ingresa una opci�n v�lida." << endl;
                                    break;
                                }
                            }
                            break;
                        }

                        else {

                            cout << "Contrase�a incorrecta. Intentos restantes: " << --intentos << endl;
                            cout << endl;
                            if (intentos == 0) {

                                mostrarMensajeAutodestruccion = true;
                                ejecucionTerminada = true; // Finalizar la ejecuci�n
                            }
                        }
                    } while (intentos > 0);
                    break;

            }
            case 2: {
                system("cls");
                string inputContrasena;
                do {

                    cout << "Por favor, ingresa la contrase�a para Trabajador: ";
                    cin >> inputContrasena;
                    if (inputContrasena == contrasenaTrabajador) {
                        system("cls");
                        cout << "Has seleccionado la opci�n para Trabajador.\n" << endl;

                        system("pause");
                        system("cls");

                        accesoPermitido = true;

                        // Submen� para Trabajador
                        while (accesoPermitido) {
                            int opcionTrabajador;
                            system("cls");
                            cout << "Menu para Trabajador:" << endl;

                            cout << "1. Vender" << endl;

                            cout << "4. Salir" << endl;
                            cout << "Ingresa la opci�n: ";
                            cin >> opcionTrabajador;

                            switch(opcionTrabajador) {
                                case 1:
                                    mostrarMenuMcWillys();
                                    break;

                                case 4:
                                    accesoPermitido = false; // Salir del submenu
                                    break;
                                default:
                                    cout << "Opci�n no v�lida. Por favor ingresa una opci�n v�lida." << endl;
                                    break;
                            }
                        }
                        break;
                    } else {
                        cout << "Contrase�a incorrecta. Intentos restantes: " << --intentos << endl;
                        cout << endl;
                        if (intentos == 0) {

                            mostrarMensajeAutodestruccion = true;
                            ejecucionTerminada = true; // Finalizar la ejecuci�n
                        }
                    }
                } while (intentos > 0);
                break;
            }
            case 3: {
                system("cls");
                string inputContrasena;
                do {
                    cout << "Por favor, ingresa la contrase�a para Usuario Normal: ";
                    cin >> inputContrasena;
                    if (inputContrasena == contrasenaUsuarioNormal) {
                        cout << "Has seleccionado la opci�n para Usuario Normal." << endl;
                        accesoPermitido = true;
                        ejecucionTerminada = true; // Finalizar la ejecuci�n
                        break;
                    } else {
                        cout << "Contrase�a incorrecta. Intentos restantes: " << --intentos << endl;
                        cout << endl;
                        if (intentos == 0) {

                            mostrarMensajeAutodestruccion = true;
                            ejecucionTerminada = true; // Finalizar la ejecuci�n
                        }
                    }
                } while (intentos > 0);
                break;
            }
            case 4:
                cout << "Saliendo del programa. �Hasta luego!" << endl;
                accesoPermitido = true;
                ejecucionTerminada = true; // Finalizar la ejecuci�n
                break;
            default:
                cout << "Opci�n no v�lida. Por favor, elige una opci�n v�lida." << endl;
                break;
        }

        if (!accesoPermitido && mostrarMensajeAutodestruccion) {
            cout << "Mensaje de autodestrucci�n activado. Saliendo en:" << endl;
            for (int i = 3; i > 0; i--) {
                cout << i << " ";
                esperarSegundo();
            }
        }
    } while (!ejecucionTerminada);
}


void menu::contratarEmpleado()
{
    ofstream escritura;
    ifstream verificador;
    string auxCodigo;
    bool coincidencia=false;
    escritura.open("empleados.txt",ios::app); // Cambiado a "empleados.txt" para guardar informaci�n de empleados
    verificador.open("empleados.txt",ios::in); // Cambiado a "empleados.txt" para verificar empleados existentes
    if(escritura.is_open())
    {
        cout<<"\t\t\t\t***Contratar una persona***\t\t\t\t\n\n";
        fflush(stdin);
        cout<<"Ingresa el c�digo del empleado: ";
        getline(cin,auxCodigo);
        if(auxCodigo=="")
            do
            {
                cout<<"C�digo de empleado no v�lido!, int�ntalo nuevamente: ";
                getline(cin,auxCodigo);
            }
            while(auxCodigo=="");
        do
        {
            verificador.seekg(0);
            getline(verificador,codigoEmpleado); // Cambiado a "codigoEmpleado" para empleados
            while(!verificador.eof())
            {
                getline(verificador,nombre);
                getline(verificador,domicilio);
                getline(verificador,celular);
                getline(verificador,fechaContratacion); // Cambiado a "fechaContratacion"

                if(codigoEmpleado==auxCodigo) // Cambiado a "codigoEmpleado"
                {
                    coincidencia=true;
                    cout<<"\n\nYa existe un empleado con ese c�digo!\n\n";
                    cout<<"El empleado con ese c�digo es: "<<nombre<<"\n\n"; // Cambiado a "empleado" para empleados
                    cout<<"Ingresa un c�digo v�lido!: ";
                    getline(cin,auxCodigo);
                    if(auxCodigo=="")
                        do
                        {
                            cout<<"\nC�digo de empleado no v�lido!, int�ntalo nuevamente: ";
                            getline(cin,auxCodigo);
                        }
                        while(auxCodigo=="");

                    break;
                }

                getline(verificador,codigoEmpleado); // Cambiado a "codigoEmpleado" para empleados
            }

            if(verificador.eof()&&auxCodigo!=codigoEmpleado) // Cambiado a "codigoEmpleado" para empleados
                coincidencia=false;

        }
        while(coincidencia==true);
        system(CLEAR);
        codigoEmpleado=auxCodigo; // Cambiado a "codigoEmpleado" para empleados
        cout<<"\t\t\t\t***Contratar una persona***\t\t\t\t\n\n";
        cout<<"Ingresa el c�digo del empleado: ";
        cout<<codigoEmpleado;
        cout<<"\n\n";
        fflush(stdin);
        cout<<"Ingresa el nombre del empleado: ";
        getline(cin,nombre);
        cout<<"\n\n";
        fflush(stdin);
        cout<<"Ingresa el domicilio del empleado: ";
        getline(cin,domicilio);
        cout<<"\n\n";
        fflush(stdin);
        cout<<"Ingresa el n�mero de telefono del empleado: ";
        getline(cin,celular);
        cout<<"\n\n";
        fflush(stdin);
        cout<<"Ingresa la fecha de contrataci�n del empleado: ";
        getline(cin,fechaContratacion); // Cambiado a "fechaContratacion"
        cout<<"\n\n";

        escritura<<codigoEmpleado<<endl<<nombre<<endl<<domicilio<<endl<<celular
                 <<endl<<fechaContratacion<<endl; // Cambiado a "fechaContratacion"

        cout<<"El registro se ha completado correctamente.\n\n";
    }

    else
    {
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
            cout<<"Ingresa el c�digo del empleado que deseas despedir: "; // Cambiado a "empleado" para empleados
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
                    cout<<"C�digo: "<<codigoEmpleado<<endl; // Cambiado a "codigoEmpleado" para empleados
                    cout<<"Nombre: "<<nombre<<endl;
                    cout<<"Domicilio: "<<domicilio<<endl;
                    cout<<"Celular: "<<celular<<endl;
                    cout<<"Fecha de contrataci�n: "<<fechaContratacion<<endl; // Cambiado a "fechaContratacion"
                    cout<<"\n\n";
                    cout<<"�Realmente deseas despedir a: "<<nombre<<" (s/n)?: ";
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
                cout<<"\n\nNo se encontr� el c�digo: "<<auxCodigo<<"\n\n";
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

int main()
{
    system ("color f0");
    menu inicio;
    comprobarArchivo();
    inicio.menuPrincipal();
    return 0;
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
    archivo.open("clientes.txt",ios::in);
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

void menu::buscarEmpleado()
{
    ifstream lectura;
    lectura.open("empleados.txt",ios::in); // Cambiado a "empleados.txt" para buscar empleados
    int encontrados;
    string buscarNombre;

    cout<<"\t\t\t\t***Buscar Empleado***\t\t\t\t\n\n"<<endl<<endl;
    if(lectura.is_open())
    {
        cout<<"Ingresa el nombre del empleado: "; // Cambiado a "empleado" para buscar empleados
        fflush(stdin);
        getline(cin,buscarNombre);
        encontrados=0;
        cout<<endl;

        getline(lectura,codigoEmpleado); // Cambiado a "codigoEmpleado" para empleados
        while(!lectura.eof())
        {
            getline(lectura,nombre);
            getline(lectura,domicilio);
            getline(lectura,celular);
            getline(lectura,fechaContratacion); // Cambiado a "fechaContratacion"

            if(nombre.find(buscarNombre)!=string::npos)
            {
                cout<<"C�digo: "<<codigoEmpleado<<endl; // Cambiado a "codigoEmpleado" para empleados
                cout<<"Nombre: "<<nombre<<endl;
                cout<<"Domicilio: "<<domicilio<<endl;
                cout<<"Celular: "<<celular<<endl;
                cout<<"Fecha de contrataci�n: "<<fechaContratacion<<endl; // Cambiado a "fechaContratacion"
                cout<<"\n\n";
                encontrados++;
            }

            getline(lectura,codigoEmpleado); // Cambiado a "codigoEmpleado" para empleados
        }
        if (encontrados)
        {
            cout<<"Se encontr� "<<encontrados<<" registro(s) con la palabra buscada"<<endl;
        }
        else
        {
            cout<<"No se encontr� ning�n registro con la palabra buscada"<<endl;
        }
    }
    else
    {
        cout<<endl<<"No se pudo abrir el archivo!";
    }
    lectura.close();
    pausa();
}

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

        switch (opcion) {
            case 1: {
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
                break;
            }
            case 2: {
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
                } else {
                    cout << "La oferta " << nombreEliminar << " no fue encontrada." << endl;
                }
                break;
            }
            case 3: {
                if (listaNombres.empty()) {
                    cout << "No hay ofertas disponibles." << endl;
                } else {
                    cout << "Ofertas disponibles:" << endl;
                    for (size_t i = 0; i < listaNombres.size(); ++i) {
                        cout << "Nombre: " << listaNombres[i] << endl;
                        cout << "Descripción: " << listaDescripciones[i] << endl;
                        cout << "Precio: $" << listaPrecios[i] << endl;
                        cout << "------------------------" << endl;
                    }
                }
                break;
            }
            case 4:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción no válida. Intente nuevamente." << endl;
                break;
        }
    } while (opcion != 4);
}
// --------------------------------------------------

void menu::generarFactura(const Orden& orden) {
    system("cls");
    cout << "\t\t\t\tFACTURA GENERADA\t\t\t\t\n" << endl;
    cout << "Cliente: " << orden.nombreCliente << endl;
    cout << "Carnet o NIT: " << orden.carnetONit << endl;
    cout << "Productos:" << endl;

    for (const string& producto : orden.productos) {
        cout << "- " << producto << endl;
    }

    cout << "Total a pagar: " << orden.total << " Bs" << endl;
}

void menu::guardarOrden(const Orden& orden) {
    ofstream archivo("ordenes.txt", ios::app);  // Abre el archivo en modo de apendizaje

    if (archivo.is_open()) {
        archivo << "Cliente: " << orden.nombreCliente << ", Carnet o NIT: " << orden.carnetONit << endl;
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
        cout << "Error al abrir el archivo de �rdenes." << endl;
    }
}
// --------------------------------------------------

void menu::mostrarMenuMcWillys() {
    int opcion;
    Orden orden;

    do {
        system("cls");
        cout << "---- Men� de McWilly's ----" << endl;
        cout << "1. Hamburguesas" << endl;
        cout << "2. Desayunos" << endl;
        cout << "3. Extras" << endl;
        cout << "4. Postres" << endl;
        cout << "5. PROMOCIONES" << endl;
        cout << "6. Terminar Orden y Generar Factura" << endl;
        cout << "------------------------------" << endl;
        cout << "Selecciona una opci�n: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                system("cls");
                mostrarMenuHamburguesas(orden);
                break;
            case 2:
                system("cls");
                mostrarMenuDesayunos(orden);
                break;
            case 3:
                system("cls");
                mostrarMenuExtras(orden);
                break;
            case 4:
                system("cls");
                mostrarMenuPostres(orden);
                break;
            case 5:
                system("cls");
                venderOfertas();
                break;
            case 6:
                system("cls");
                cout << "Terminando orden y generando factura..." << endl;
                cout << "Ingrese el nombre del cliente: ";
                cin >> orden.nombreCliente;
                cout << "Ingrese el carnet o NIT del cliente: ";
                cin >> orden.carnetONit;
                generarFactura(orden);
                guardarOrden(orden);
                break;
            default:
                cout << "Opci�n no v�lida. Por favor, elige una opci�n v�lida." << endl;
                break;
        }
    } while (opcion != 5);
}

vector<string> descripciones = {
    "Un wrap de pollo con un toque especial de McWilly�s relleno de sabidur�a inform�tica y salsa secreta de programaci�n.\n",
    "Una hamburguesa con un mont�n de tocino y pollo branch con una mezcla secreta de c�digo, servida con una salsa BBQ de McWilly�s.\n",
    "Una hamburguesa con doble procesador de carne, chips de datos crujientes y una salsa algoritmo especial.\n",
    "Una hamburguesa especial con 'bytes' extra de sabor y una salsa de 'bits' �nica.\n",
    "Una hamburguesa con carne de res, salsa de depuraci�n y una capa extra de 'bugs' crujientes para los amantes de la caza de errores.\n",
    "Una hamburguesa gourmet con carne de res de alta calidad, queso suizo y una salsa de programaci�n maestra creada por Willy Tenorio.\n",
    "Una hamburguesa con carne de pollo a la parrilla, tocino y una mezcla secreta de 'bits' y 'bytes' que solo encontrar�s en el McWyllis.\n",
    "Es una delicia llena de ingredientes frescos y creativos que satisfar�n tu paladar y tu mente.\n",
    "Una hamburguesa picante con carne de ternera, jalape�os y una capa de seguridad inform�tica que proteger� tu paladar de cualquier amenaza.\n",
    "Una hamburguesa con capas de carne, pollo y tocino, junto con una variedad de ingredientes para satisfacer todas tus necesidades de programaci�n.\n",
    "Una hamburguesa hecha por willy tenorio con los m�ximos secretos culinarias de la abuelita tenorio como: \n",
    "Una variacion de la tenorio con doble carne y doble amor.\n",
    "Una mini tenorio con java fries y una deliciosa Palza Pie, todo esto acompa�ado de un juguete SUPER WILLY\n",
    "Una hamburguesa hecha con ingredientes de una deliciosa sopita con su especialidad �la coronel� una salsa extrapicante insuperable.\n",
    "Esta hamburguesa combina creatividad y programaci�n en cada capa. El pan multicolor representa la diversidad de ideas, la carne es una mezcla innovadora, el queso aporta l�gica, y la lechuga a�ade diversi�n con humor. Los tomates ilustran conceptos, la cebolla optimiza, la mostaza es atrevida pero planificada, y el ketchup representa la variedad de lenguajes de programaci�n. Los pepinillos aportan soluciones ingeniosas.\n",
    "Una hamburguesa de carne premium, bacon ahumado, queso gouda derretido, champi�ones en salsa de vino tinto, cebolla caramelizada y vegetales frescos. La fusi�n perfecta de la pasi�n de Alan por los autos y la elegancia de Lamborghini.\n",
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

void menu::mostrarMenuHamburguesas(Orden& orden) {
    cout << "---- Men� de Hamburguesas ----" << endl;
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
    cout << "17. Volver al Men� Principal" << endl;
    cout << "------------------------------" << endl;

    int seleccion;
    cout << "Selecciona una hamburguesa para ver la descripci�n: ";
    cin >> seleccion;

    if (seleccion >= 1 && seleccion <= descripciones.size())
    {
        cout << endl;
        cout << "DESCRIPCI�N: " << descripciones[seleccion - 1] << endl;

        int cantidad;
        vector<int> cantidades(descripciones.size(), 0);

        // Validar que la cantidad sea mayor que cero

        cantidades[seleccion - 1] += cantidad;  // Almacenar la cantidad seleccionada



        int opcion;
        cout << "1. Volver al Men� Principal" << endl;
        cout << "2. A�adir art�culo en el pedido." << endl;
        cout << "Selecciona una opci�n: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1:
                system("cls");
                mostrarMenuMcWillys();
                break;
            case 2:

                cout << endl;
                cout << "Ingrese la cantidad deseada: ";
                cin >> cantidad;

                if (cantidad > 0)
                {
                    orden.productos.push_back(descripciones[seleccion - 1] + " x" + to_string(cantidad));
                    orden.total += precios[seleccion - 1] * cantidad;
                    cout << endl;
                    cout << "�Producto agregado a la orden!\n" << endl;
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
                cout << "Opci�n no v�lida." << endl;
                break;
        }
    } else {
        cout << "Selecci�n no v�lida." << endl;
    }
}

vector<string> descripciones2 = {
    "Unos Plaza cakes llenos de codigo limpio con un toque de chocolate willy.\n",
    "Una cari�osa masa hecha por willy con mantenorio.\n",
    "Una willy hot hecha con pan Palza y una enorme Willy salchicha.\n",
};

vector<double>precios2 = {
    15,
    15,
    10,
};

void menu::mostrarMenuDesayunos(Orden& orden) {
    cout << "---- Men� de Desayunos ----" << endl;
    cout << "1. Los Palza cakes - 15Bs" << endl;
    cout << "2. Los WWafles - 15Bs" << endl;
    cout << "3. La Hot - 10Bs" << endl;
    cout << "4. Volver al Men� Principal" << endl;
    cout << "------------------------------" << endl;

    int seleccion;
    cout << "Selecciona un desayuno para ver la descripci�n: ";
    cin >> seleccion;

    if (seleccion >= 1 && seleccion <= descripciones2.size()) {
        cout << endl;
        cout << "DESCRIPCI�N: " << descripciones2[seleccion - 1] << endl;

        int cantidad;
        vector<int> cantidades2(descripciones2.size(), 0);
        cantidades2[seleccion - 1] += cantidad;



        int opcion;
        cout << "1. Volver al Men� Principal" << endl;
        cout << "2. A�adir art�culo en el pedido." << endl;
        cout << "Selecciona una opci�n: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarMenuMcWillys();
                break;
            case 2:

                cout << endl;
                cout << "Ingrese la cantidad deseada: ";
                cin >> cantidad;

                if (cantidad > 0)
                {
                    orden.productos.push_back(descripciones2[seleccion - 1] + " x" + to_string(cantidad));
                    orden.total += (precios2[seleccion - 1]*cantidad);
                    cout << endl;
                    cout << "�Producto agregado a la orden!" << endl;
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
                cout << "Opci�n no v�lida." << endl;
                break;
        }
    } else {
        cout << "Selecci�n no v�lida." << endl;
    }
}

vector<string> descripciones3 = {
    "Trozos de pollo empanizados con el lenguaje de programaci�n Python, servidos con una salsa de syntax.\n",
    "Una bebida refrescante con consultas SQL burbujeante.\n",
    "Un caf� latte con un toque de magia JavaBean, la especialidad de Willy Tenorio.\n",
    "Un postre �pico que te hace sentir como un ingeniero de software infinito, con capas de conocimiento ilimitado.\n",
    "Papas fritas doradas y crujientes con un toque de caf� Java para esa energ�a extra.\n",
};

vector<double>precios3 = {
    25,
    10,
    15,
    20,
    20,
};

void menu::mostrarMenuExtras(Orden& orden) {
    cout << "---- Men� de Extras ----" << endl;
    cout << "1. Python Nuggets - 25Bs" << endl;
    cout << "2. SQL Soda - 10Bs" << endl;
    cout << "3. JavaBean Latte - 15Bs" << endl;
    cout << "4. Ingeniero Infinito Sundae - 20Bs" << endl;
    cout << "5. Java Fries - 20Bs" << endl;
    cout << "6. Volver al Men� Principal" << endl;
    cout << "------------------------------" << endl;

    int seleccion;
    cout << "Selecciona un extra para ver la descripci�n: ";
    cin >> seleccion;

    if (seleccion >= 1 && seleccion <= descripciones3.size())
    {
        cout << endl;
        cout << "DESCRIPCI�N: " << descripciones3[seleccion - 1] << endl;

        int cantidad;
        vector<int> cantidades3(descripciones3.size(), 0);

        cantidades3[seleccion - 1] += cantidad;  // Almacenar la cantidad seleccionada

        int opcion;
        cout << "1. Volver al Men� Principal" << endl;
        cout << "2. A�adir articulo en el pedido" << endl;
        cout << "Selecciona una opci�n: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarMenuMcWillys();
                break;
            case 2:

                cout << endl;
                cout << "Ingrese la cantidad deseada: ";
                cin >> cantidad;
                cout << endl;

                if (cantidad > 0)
                {
                    orden.productos.push_back(descripciones3[seleccion - 1] + " x" + to_string(cantidad));
                    orden.total += (precios3[seleccion - 1]*cantidad);
                    cout << "�Producto agregado a la orden!" << endl;
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
                cout << "Opci�n no v�lida." << endl;
                break;
        }
    } else {
        cout << "Selecci�n no v�lida." << endl;
    }
}

vector<string> descripciones4 = {
    "Galletas reci�n horneadas con chips de chocolate y trozos de c�digo incrustados para los amantes de la programaci�n dulce.\n",
    "Dos galletas de HTML5 rellenas de helado de tu elecci�n, una experiencia fresca y sabrosa.\n",
    "Helado con chispas de datos crujientes y una selecci�n de coberturas para personalizar tu postre.\n",
    "Cupcakes de vainilla con un toque de Git Commit, decorados con mensajes de confirmaci�n de c�digo.\n",
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

void menu::mostrarMenuPostres(Orden& orden) {
    cout << "---- Men� de Postres ----" << endl;
    cout << "1. Code Crunch Cookies - 5Bs" << endl;
    cout << "2. HTML5 Ice Cream Sandwich - 8Bs" << endl;
    cout << "3. Data Byte Delight - 10Bs" << endl;
    cout << "4. Git Commit Cupcake - 15Bs" << endl;
    cout << "5. Python Popsicles - 5Bs" << endl;
    cout << "6. Palza Pie - 10Bs" << endl;
    cout << "7. Volver al Men� Principal" << endl;
    cout << "------------------------------" << endl;

    int seleccion;
    cout << "Selecciona un postre para ver la descripci�n: ";
    cin >> seleccion;

    if (seleccion >= 1 && seleccion <= descripciones4.size()) {
        cout << endl;
        cout << "DESCRIPCI�N: " << descripciones4[seleccion - 1] << endl;


        int cantidad;
        vector<int> cantidades4(descripciones4.size(), 0);
        cantidades4[seleccion - 1] += cantidad;

        int opcion;
        cout << "1. Volver al Men� Principal" << endl;
        cout << "2. A�adir art�culo en el pedido." << endl;
        cout << "Selecciona una opci�n: ";
        cin >> opcion;

        cout << endl;

        switch (opcion) {
            case 1:
                mostrarMenuMcWillys();
                break;
            case 2:

                cout << "Ingrese la cantidad deseada: ";
                cin >> cantidad;
                cout << endl;

                if (cantidad > 0) {
                    orden.productos.push_back(descripciones4[seleccion - 1] + " x" + to_string(cantidad));
                    orden.total += (precios4[seleccion - 1])*cantidad;
                    cout << "�Producto agregado a la orden!" << endl;
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
                cout << "Opci�n no v�lida." << endl;
                break;
        }
    } else {
        cout << "Selecci�n no v�lida." << endl;
    }
}

void menu::venderOfertas() {
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
        cout << "1. Mostrar ofertas disponibles" << endl;
        cout << "2. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                if (listaNombres.empty()) {
                    cout << "No hay ofertas disponibles." << endl;
                } else {
                    cout << "Ofertas disponibles:" << endl;
                    for (size_t i = 0; i < listaNombres.size(); ++i) {
                        cout << "Nombre: " << listaNombres[i] << endl;
                        cout << "Descripción: " << listaDescripciones[i] << endl;
                        cout << "Precio: $" << listaPrecios[i] << endl;
                        cout << "------------------------" << endl;
                    }

                    int opcionOferta;
                    cout << "Seleccione una opción:" << endl;
                    cout << "1. Agregar a la orden de venta" << endl;
                    cout << "2. Volver" << endl;
                    cout << "Opción: ";
                    cin >> opcionOferta;

                    if (opcionOferta == 1) {
                        int cantidad;
                        cout << "Ingrese la cantidad: ";
                        cin >> cantidad;

                        if (cantidad > 0) {
                            int idOferta = opcionOferta - 1;
                            double totalPagar = listaPrecios[idOferta] * cantidad;
                            cout << "Total a pagar: $" << totalPagar << endl;
                        } else {
                            cout << "La cantidad debe ser mayor que cero." << endl;
                        }
                    } else if (opcionOferta == 2) {
                        continue; // Volver al menú principal
                    } else {
                        cout << "Opción no válida." << endl;
                    }
                }
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

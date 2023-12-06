#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <wchar.h>
#include <vector>

//Limpiar pantalla
#ifdef _WIN32
#define CLEAR "cls"
#elif defined(unix)||defined(__unix__)||defined(__unix)||defined(__APPLE__)||defined(__MACH__)
#define CLEAR "clear"
#else
#error "SO no soportado para limpiar pantalla"
#endif

using namespace std;


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

    void mostrarMenuMcWillys();
    void mostrarMenuHamburguesas();
    void mostrarMenuDesayunos();
    void mostrarMenuExtras();
    void mostrarMenuPostres();
    void venderArticulo();
    void agregarArticulo();
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
    bool ejecucionTerminada = false; // Variable para controlar la finalización
    bool mostrarMensajeAutodestruccion = false; // Variable para mostrar el mensaje de autodestrucción

    // Imprimir un mensaje de bienvenida y la hamburguesa con caracteres ASCII
    cout << "¡Bienvenidos a Mc Willy's!" << endl;
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

        cout << "Menú Principal" << endl;
        cout << "1. Opción para Gerente" << endl;
        cout << "2. Opción para Trabajador" << endl;
        cout << "3. Opción para Usuario Normal" << endl;
        cout << "4. Salir" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                string inputContrasena;
                do {
                    cout << "Por favor, ingresa la contraseña para Gerente: ";
                    cin >> inputContrasena;
                    if (inputContrasena == contrasenaGerente) {
                        cout << "Has seleccionado la opción para Gerente." << endl;
                        accesoPermitido = true;
                        bool ejecucionTerminada = false;
                        while (!ejecucionTerminada) {
                            int opcion;
                            cout << "\nMenu para Gerente:" << endl;
                            cout << "1. Contratar empleado" << endl;
                            cout << "2. Despedir empleado" << endl;
                            cout << "3. Buscar empleado" << endl;
                            cout << "4. Salir" << endl;
                            cout << "Ingresa la opción: ";
                            cin >> opcion;

                            switch(opcion) {
                                case 1:
                                    contratarEmpleado();
                                    break;
                                case 2:
                                    despedirEmpleado();
                                    break;
                                case 3:
                                    buscarEmpleado();
                                    break;
                                case 4:
                                    ejecucionTerminada = true;
                                    break;
                                default:
                                    cout << "Opción no válida. Por favor ingresa una opción válida." << endl;
                                    break;
                                }
                            }
                            break;
                        } else {
                            cout << "Contraseña incorrecta. Intentos restantes: " << --intentos << endl;
                            if (intentos == 0) {
                                mostrarMensajeAutodestruccion = true;
                                ejecucionTerminada = true; // Finalizar la ejecución
                            }
                        }
                    } while (intentos > 0);
                    break;

            }
            case 2: {
                string inputContrasena;
                do {
                    cout << "Por favor, ingresa la contraseña para Trabajador: ";
                    cin >> inputContrasena;
                    if (inputContrasena == contrasenaTrabajador) {
                        cout << "Has seleccionado la opción para Trabajador." << endl;
                        accesoPermitido = true;

                        // Submenú para Trabajador
                        while (accesoPermitido) {
                            int opcionTrabajador;
                            cout << "\nMenu para Trabajador:" << endl;
                            cout << "1. Menu" << endl;
                            cout << "2. Vender" << endl;
                            cout << "3. Factura" << endl;
                            cout << "4. Salir" << endl;
                            cout << "Ingresa la opción: ";
                            cin >> opcionTrabajador;

                            switch(opcionTrabajador) {
                                case 1:
                                    mostrarMenuMcWillys();
                                    break;
                                case 2:
                                    venderArticulo();
                                    break;
                                case 3:
                                    // Factura
                                    break;
                                case 4:
                                    accesoPermitido = false; // Salir del submenu
                                    break;
                                default:
                                    cout << "Opción no válida. Por favor ingresa una opción válida." << endl;
                                    break;
                            }
                        }
                        break;
                    } else {
                        cout << "Contraseña incorrecta. Intentos restantes: " << --intentos << endl;
                        if (intentos == 0) {
                            mostrarMensajeAutodestruccion = true;
                            ejecucionTerminada = true; // Finalizar la ejecución
                        }
                    }
                } while (intentos > 0);
                break;
            }
            case 3: {
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
                cout << "Opción no válida. Por favor, elige una opción válida." << endl;
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


void menu::contratarEmpleado()
{
    ofstream escritura;
    ifstream verificador;
    string auxCodigo;
    bool coincidencia=false;
    escritura.open("empleados.txt",ios::app); // Cambiado a "empleados.txt" para guardar información de empleados
    verificador.open("empleados.txt",ios::in); // Cambiado a "empleados.txt" para verificar empleados existentes
    if(escritura.is_open())
    {
        cout<<"\t\t\t\t***Contratar una persona***\t\t\t\t\n\n";
        fflush(stdin);
        cout<<"Ingresa el código del empleado: ";
        getline(cin,auxCodigo);
        if(auxCodigo=="")
            do
            {
                cout<<"Código de empleado no válido!, inténtalo nuevamente: ";
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
                    cout<<"\n\nYa existe un empleado con ese código!\n\n";
                    cout<<"El empleado con ese código es: "<<nombre<<"\n\n"; // Cambiado a "empleado" para empleados
                    cout<<"Ingresa un código válido!: ";
                    getline(cin,auxCodigo);
                    if(auxCodigo=="")
                        do
                        {
                            cout<<"\nCódigo de empleado no válido!, inténtalo nuevamente: ";
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
        cout<<"Ingresa el código del empleado: ";
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
        cout<<"Ingresa el número de telefono del empleado: ";
        getline(cin,celular);
        cout<<"\n\n";
        fflush(stdin);
        cout<<"Ingresa la fecha de contratación del empleado: ";
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
            cout<<"Ingresa el código del empleado que deseas despedir: "; // Cambiado a "empleado" para empleados
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

    cout<<"***Buscar Empleado***"<<endl<<endl;
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
                cout<<"Código: "<<codigoEmpleado<<endl; // Cambiado a "codigoEmpleado" para empleados
                cout<<"Nombre: "<<nombre<<endl;
                cout<<"Domicilio: "<<domicilio<<endl;
                cout<<"Celular: "<<celular<<endl;
                cout<<"Fecha de contratación: "<<fechaContratacion<<endl; // Cambiado a "fechaContratacion"
                cout<<"\n\n";
                encontrados++;
            }

            getline(lectura,codigoEmpleado); // Cambiado a "codigoEmpleado" para empleados
        }
        if (encontrados)
        {
            cout<<"Se encontró "<<encontrados<<" registro(s) con la palabra buscada"<<endl;
        }
        else
        {
            cout<<"No se encontró ningún registro con la palabra buscada"<<endl;
        }
    }
    else
    {
        cout<<endl<<"No se pudo abrir el archivo!";
    }
    lectura.close();
    pausa();
}

void menu::mostrarMenuMcWillys() {
    int opcion;
    do {
        cout << "---- Menú de McWilly's ----" << endl;
        cout << "1. Hamburguesas" << endl;
        cout << "2. Desayunos" << endl;
        cout << "3. Extras" << endl;
        cout << "4. Postres" << endl;
        cout << "5. Salir" << endl;
        cout << "------------------------------" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                mostrarMenuHamburguesas();
                break;
            case 2:
                mostrarMenuDesayunos();
                break;
            case 3:
                mostrarMenuExtras();
                break;
            case 4:
                mostrarMenuPostres();
                break;
            case 5:
                cout << "Saliendo del menú de McWilly's. ¡Hasta luego!" << endl;
                break;
            default:
                cout << "Opción no válida. Por favor, elige una opción válida." << endl;
                break;
        }
    } while(opcion != 4);
}

vector<string> descripciones = {
    "Un wrap de pollo con un toque especial de McWilly’s relleno de sabiduría informática y salsa secreta de programación.\n",
    "Una hamburguesa con un montón de tocino y pollo branch con una mezcla secreta de código, servida con una salsa BBQ de McWilly’s.\n",
    "Una hamburguesa con doble procesador de carne, chips de datos crujientes y una salsa algoritmo especial.\n",
    "Una hamburguesa especial con 'bytes' extra de sabor y una salsa de 'bits' única.\n",
    "Una hamburguesa con carne de res, salsa de depuración y una capa extra de 'bugs' crujientes para los amantes de la caza de errores.\n",
    "Una hamburguesa gourmet con carne de res de alta calidad, queso suizo y una salsa de programación maestra creada por Willy Tenorio.\n",
    "Una hamburguesa con carne de pollo a la parrilla, tocino y una mezcla secreta de 'bits' y 'bytes' que solo encontrarás en el McWyllis.\n",
    "Es una delicia llena de ingredientes frescos y creativos que satisfarán tu paladar y tu mente.\n",
    "Una hamburguesa picante con carne de ternera, jalapeños y una capa de seguridad informática que protegerá tu paladar de cualquier amenaza.\n",
    "Una hamburguesa con capas de carne, pollo y tocino, junto con una variedad de ingredientes para satisfacer todas tus necesidades de programación.\n",
    "Una hamburguesa hecha por willy tenorio con los máximos secretos culinarias de la abuelita tenorio como: \n",
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

void menu::mostrarMenuHamburguesas() {
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

    if (seleccion >= 1 && seleccion <= descripciones.size()) {
        cout << "Descripción: " << descripciones[seleccion - 1] << endl;

        int opcion;
        cout << "1. Volver al Menú Principal" << endl;
        cout << "2. Ir a Vender este artículo" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                mostrarMenuMcWillys();
                break;
            case 2:
                venderArticulo();
                //cout << "¡Vendiendo artículo seleccionado!" << endl;
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
    "Unos Plaza cakes llenos de codigo limpio con un toque de chocolate willy.\n",
    "Una cariñosa masa hecha por willy con mantenorio.\n",
    "Una willy hot hecha con pan Palza y una enorme Willy salchicha.\n",
};

vector<double>precios2 = {
    15,
    15,
    10,
};

void menu::mostrarMenuDesayunos() {
    cout << "---- Menú de Desayunos ----" << endl;
    cout << "1. Los Palza cakes - 15Bs" << endl;
    cout << "2. Los WWafles - 15Bs" << endl;
    cout << "3. La Hot - 10Bs" << endl;
    cout << "4. Volver al Menú Principal" << endl;
    cout << "------------------------------" << endl;

    int seleccion;
    cout << "Selecciona un desayuno para ver la descripción: ";
    cin >> seleccion;

    if (seleccion >= 1 && seleccion <= descripciones2.size()) {
        cout << "Descripción: " << descripciones2[seleccion - 1] << endl;

        int opcion;
        cout << "1. Volver al Menú Principal" << endl;
        cout << "2. Ir a Vender este artículo" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarMenuMcWillys();
                break;
            case 2:
                venderArticulo();
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

void menu::mostrarMenuExtras() {
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

    if (seleccion >= 1 && seleccion <= descripciones3.size()) {
        cout << "Descripción: " << descripciones3[seleccion - 1] << endl;

        int opcion;
        cout << "1. Volver al Menú Principal" << endl;
        cout << "2. Ir a Vender este artículo" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarMenuMcWillys();
                break;
            case 2:
                venderArticulo();
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
    "Dos galletas de HTML5 rellenas de helado de tu elección, una experiencia fresca y sabrosa.\n",
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

void menu::mostrarMenuPostres() {
    cout << "---- Menú de Postres ----" << endl;
    cout << "1. Code Crunch Cookies - 5Bs" << endl;
    cout << "2. HTML5 Ice Cream Sandwich - 8Bs" << endl;
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
        cout << "Descripción: " << descripciones4[seleccion - 1] << endl;

        int opcion;
        cout << "1. Volver al Menú Principal" << endl;
        cout << "2. Ir a Vender este artículo" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarMenuMcWillys();
                break;
            case 2:
                venderArticulo();
                break;
            default:
                cout << "Opción no válida." << endl;
                break;
        }
    } else {
        cout << "Selección no válida." << endl;
    }
}

void menu::venderArticulo() {
    int categoria;
    int seleccion;
    int cantidad;
    /*cout << "Ingrese la cantidad a vender: ";
    cin >> cantidad;

    totalRecaudado += precios[seleccion - 1] * cantidad;
    cantidadVendida += cantidad;

    cout << cantidad << " artículo(s) vendido(s)." << endl;
    cout << "Cantidad total vendida: " << cantidadVendida << endl;
    cout << "Total recaudado: $" << totalRecaudado << endl;*/

    int opcion;
    cout << "1. Buscar articulo en el menu" << endl;
    cout << "2. Agregar otro artículo" << endl;
    cout << "Selecciona una opción: ";
    cin >> opcion;

    switch (opcion) {
        case 1:
            mostrarMenuMcWillys();
            break;
        case 2:
            agregarArticulo();
            break;
        default:
            cout << "Opción no válida." << endl;
            break;
    }
}

void menu::agregarArticulo() {
    int categoria;
    int seleccion;
    int totalArticulos = 0;
    double totalPagar = 0.0;
    int cantidadVendida = 0;
    int totalRecaudado = 0;

    while (true) {
        venderArticulo();

         while (true) {
        venderArticulo();

        int opcion;
        cout << "1. Agregar otro artículo de este tipo" << endl;
        cout << "2. Terminar y mostrar total a pagar" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                break; // Continuar agregando más artículos del mismo tipo
            case 2:
                totalArticulos += cantidadVendida;
                totalPagar += totalRecaudado;
                cout << "Total de artículos: " << totalArticulos << endl;
                cout << "Total a pagar: $" << totalPagar << endl;
                agregarArticulo(); // Llamar nuevamente a agregarArticulo()
                return;
            default:
                cout << "Opción no válida." << endl;
                break;
            }
        }
    }
}




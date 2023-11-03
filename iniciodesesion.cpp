#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <wchar.h>

using namespace std;

// Función para esperar aproximadamente 1 segundo
void esperarSegundo() {
    clock_t inicio = clock();
    while (static_cast<double>(clock() - inicio) / CLOCKS_PER_SEC < 1.0) {}
}

int main() {
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
    cout << "                             |\\ /| /|_/|" << endl;
    cout << "                             |\\||-|\\||-/|/|" << endl;
    cout << "                              \\|\\|//||///" << endl;
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
            case 2: {
                string inputContrasena;
                do {
                    cout << "Por favor, ingresa la contraseña para Trabajador: ";
                    cin >> inputContrasena;
                    if (inputContrasena == contrasenaTrabajador) {
                        cout << "Has seleccionado la opción para Trabajador." << endl;
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

    return 0;
}

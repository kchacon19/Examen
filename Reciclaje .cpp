
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

struct Usuario {
    string nombre;
    map<string, double> materialesReciclados; 
    int puntos;
};

map<string, double> materiales; 
vector<Usuario> usuarios;


void inicializarMateriales() {
    materiales["metal"] = 15.0;
    materiales["carton"] = 5.0;
    materiales["plastico"] = 10.0;
}

void registrarMaterial() {
    string material;
    double puntosPorKg;

    cout << "Ingrese el nombre del material reciclable (metal, carton, plastico): ";
    cin >> material;

  
    if (material != "metal" && material != "carton" && material != "plastico") {
        cout << "Material no válido.\n";
        return;
    }

   
    if (material == "metal") {
        puntosPorKg = 15.0;
    } else if (material == "carton") {
        puntosPorKg = 5.0;
    } else if (material == "plastico") {
        puntosPorKg = 10.0;
    }

    materiales[material] = puntosPorKg;
    cout << "Material registrado exitosamente.\n";
}

void registrarReciclaje() {
    string nombreUsuario, material;
    double cantidad;

    cout << "Ingrese el nombre del usuario: ";
    cin >> nombreUsuario;

    cout << "Ingrese el material reciclado (metal, carton, plastico): ";
    cin >> material;

    
    if (material != "metal" && material != "carton" && material != "plastico") {
        cout << "Material no registrado. Por favor, registre el material primero.\n";
        return;
    }

    cout << "Ingrese la cantidad de " << material << " reciclado (en kg): ";
    cin >> cantidad;

    
    bool usuarioEncontrado = false;
    for (auto &usuario : usuarios) {
        if (usuario.nombre == nombreUsuario) {
           
            double puntosGanados = cantidad * materiales[material];
            
           
            usuario.puntos += puntosGanados;

            
            usuario.materialesReciclados[material] += cantidad;

            usuarioEncontrado = true;
            break;
        }
    }

    
    if (!usuarioEncontrado) {
        Usuario nuevoUsuario;
        nuevoUsuario.nombre = nombreUsuario;
        nuevoUsuario.materialesReciclados[material] = cantidad;
        nuevoUsuario.puntos = cantidad * materiales[material];
        usuarios.push_back(nuevoUsuario);
    }

    cout << "Reciclaje registrado exitosamente.\n";
}

void mostrarEstadisticas() {
    for (const auto &usuario : usuarios) {
        cout << "Usuario: " << usuario.nombre << endl;
        cout << "Materiales reciclados:\n";
        for (const auto &material : usuario.materialesReciclados) {
            cout << " - " << material.first << ": " << material.second << " kg" << endl;
        }
        cout << "Puntos totales: " << usuario.puntos << "\n\n";
    }
}

void canjearPuntos() {
    string nombreUsuario;
    int puntosCanjeados;
    cout << "Ingrese el nombre del usuario: ";
    cin >> nombreUsuario;
    cout << "Ingrese la cantidad de puntos a canjear: ";
    cin >> puntosCanjeados;

    for (auto &usuario : usuarios) {
        if (usuario.nombre == nombreUsuario) {
            if (usuario.puntos >= puntosCanjeados) {
                usuario.puntos -= puntosCanjeados;
                cout << "Puntos canjeados exitosamente. Puntos restantes: " << usuario.puntos << "\n";
            } else {
                cout << "Puntos insuficientes. Puntos disponibles: " << usuario.puntos << "\n";
            }
            return;
        }
    }
    cout << "Usuario no encontrado.\n";
}

int main() {
   
    inicializarMateriales();

    int opcion;
    do {
        cout << "Sistema de Gestión de Reciclaje\n";
        cout << "1. Registrar Material Reciclable\n";
        cout << "2. Registrar Reciclaje\n";
        cout << "3. Mostrar Estadísticas de Reciclaje\n";
        cout << "4. Canjear Puntos por Recompensas\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarMaterial();
                break;
            case 2:
                registrarReciclaje();
                break;
            case 3:
                mostrarEstadisticas();
                break;
            case 4:
                canjearPuntos();
                break;
            case 5:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opción no válida. Por favor, intente de nuevo.\n";
        }
    } while (opcion != 5);

    return 0;
}

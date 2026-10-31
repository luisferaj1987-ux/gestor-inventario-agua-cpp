#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// --- ESTRUCTURAS ---
struct Venta {
    string cliente;
    int cantidadBotellones;
    double totalUSD;
    double totalVES;
    string estadoPago; // "Pagado" o "Deudor"
};

// --- PROCEDIMIENTOS Y FUNCIONES ---

// Procedimiento para mostrar el encabezado y estado actual (Usa condicionales)
void mostrarInventario(int stockActual, double precioUnitario, double tasaCambio) {
    cout << "\n==========================================" << endl;
    cout << "     ESTACION DE RECARGA DE AGUA          " << endl;
    cout << "==========================================" << endl;
    cout << " Botellones en stock: " << stockActual << endl;
    cout << " Precio unitario:     $" << precioUnitario << " USD" << endl;
    cout << " Tasa BCV actual:     Bs. " << tasaCambio << endl;
    
    // Condicional para alerta de stock bajo
    if (stockActual < 10) {
        cout << " [!] ALERTA: Stock bajo. ¡Recargar tanque!" << endl;
    }
    cout << "==========================================" << endl;
}

// Función para calcular el pago total en bolívares
double calcularTotalVES(int cantidad, double precioUSD, double tasa) {
    return cantidad * precioUSD * tasa;
}

// Procedimiento para registrar una nueva venta (Usa condicionales y arreglos/vectores)
void registrarVenta(int &stockActual, double precioUnitario, double tasaCambio, vector<Venta> &registroVentas) {
    string nombreCliente;
    int cantidad;
    int opcionPago;
    
    cout << "\n--- NUEVA RECARGA ---" << endl;
    cout << "Nombre del cliente: ";
    cin >> nombreCliente;
    cout << "Cantidad de botellones: ";
    cin >> cantidad;

    // Condicional para validar el stock disponible
    if (cantidad <= 0) {
        cout << " [X] Error: La cantidad debe ser mayor a cero." << endl;
        return;
    }

    if (cantidad <= stockActual) {
        double totalUSD = cantidad * precioUnitario;
        double totalVES = calcularTotalVES(cantidad, precioUnitario, tasaCambio);
        
        cout << "Total a pagar: $" << fixed << setprecision(2) << totalUSD << " USD (Bs. " << totalVES << ")" << endl;
        
        // Ciclo repetitivo para asegurar una opcion de pago valida
        do {
            cout << "Metodo de pago / Estado:\n";
            cout << "1. Pagado de contado\n";
            cout << "2. Fiado (Deudor)\n";
            cout << "Seleccione una opcion: ";
            cin >> opcionPago;
            
            if (opcionPago != 1 && opcionPago != 2) {
                cout << " [X] Opcion invalida. Intente de nuevo.\n";
            }
        } while (opcionPago != 1 && opcionPago != 2);

        string estado = (opcionPago == 1) ? "Pagado" : "Deudor";

        // Actualizar inventario (Arreglo/Vector)
        stockActual -= cantidad;
        
        // Agregar a la estructura de vector
        registroVentas.push_back({nombreCliente, cantidad, totalUSD, totalVES, estado});
        
        cout << " [OK] Transaccion registrada exitosamente como: " << estado << endl;
    } else {
        cout << " [X] Error: No hay suficiente stock disponible (Quedan " << stockActual << ")." << endl;
    }
}

// Procedimiento para mostrar el historial de ventas y filtrar deudores (Usa ciclos repetitivos y condicionales)
void mostrarHistorial(const vector<Venta> &registroVentas) {
    cout << "\n--- HISTORIAL GENERAL DE VENTAS ---" << endl;
    
    // Condicional por si el vector esta vacio
    if (registroVentas.empty()) {
        cout << " No hay ventas registradas aun." << endl;
        return;
    }

    double totalIngresosUSD = 0;
    
    // Ciclo repetitivo (for) para recorrer el arreglo de estructuras
    for (size_t i = 0; i < registroVentas.size(); i++) {
        cout << i + 1 << ". Cliente: " << registroVentas[i].cliente 
             << " | Botellones: " << registroVentas[i].cantidadBotellones 
             << " | Total: $" << registroVentas[i].totalUSD 
             << " | Estado: " << registroVentas[i].estadoPago << endl;
             
        // Condicional para sumar solo los que ya pagaron al ingreso real
        if (registroVentas[i].estadoPago == "Pagado") {
            totalIngresosUSD += registroVentas[i].totalUSD;
        }
    }
    
    cout << "------------------------------------------" << endl;
    cout << " Ingresos totales acumulados (Cobrados): $" << totalIngresosUSD << " USD" << endl;
}

// Procedimiento para mostrar un reporte exclusivo de deudores
void mostrarDeudores(const vector<Venta> &registroVentas) {
    cout << "\n--- LISTA DE CLIENTES DEUDORES (FIADOS) ---" << endl;
    bool hayDeudores = false;

    // Ciclo para recorrer el arreglo buscando deudores
    for (size_t i = 0; i < registroVentas.size(); i++) {
        if (registroVentas[i].estadoPago == "Deudor") {
            cout << "- Cliente: " << registroVentas[i].cliente 
                 << " | Debe: $" << registroVentas[i].totalUSD 
                 << " (Bs. " << registroVentas[i].totalVES << ")" << endl;
            hayDeudores = true;
        }
    }

    if (!hayDeudores) {
        cout << " ¡Excelente! No hay clientes con deudas pendientes." << endl;
    }
}

// --- FUNCION PRINCIPAL ---
int main() {
    int stockBotellones = 40;       // Inventario inicial
    double precioBotellon = 1.50;   // Precio en USD
    double tasaBCV = 36.50;         // Tasa de cambio de referencia
    vector<Venta> registroVentas;   // Arreglo dinamico de estructuras
    int opcionPrincipal;

    // Ciclo principal del sistema (do-while)
    do {
        cout << "\n========== MENU PRINCIPAL ==========" << endl;
        cout << "1. Ver inventario y estado" << endl;
        cout << "2. Registrar nueva recarga (Venta/Fiado)" << endl;
        cout << "3. Ver historial de ventas" << endl;
        cout << "4. Ver reporte de deudores" << endl;
        cout << "5. Salir del sistema" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcionPrincipal;

        // Estructura de control condicional (switch)
        switch(opcionPrincipal) {
            case 1:
                mostrarInventario(stockBotellones, precioBotellon, tasaBCV);
                break;
            case 2:
                registrarVenta(stockBotellones, precioBotellon, tasaBCV, registroVentas);
                break;
            case 3:
                mostrarHistorial(registroVentas);
                break;
            case 4:
                mostrarDeudores(registroVentas);
                break;
            case 5:
                cout << "\n Saliendo del sistema. ¡Mucho exito con tu emprendimiento de agua!" << endl;
                break;
            default:
                cout << " [X] Opcion invalida. Intente de nuevo." << endl;
        }

    } while (opcionPrincipal != 5); // Condición para mantener el programa abierto

    return 0;
}

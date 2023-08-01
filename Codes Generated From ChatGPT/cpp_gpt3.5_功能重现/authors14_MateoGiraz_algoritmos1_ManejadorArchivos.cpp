#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>

class ManejadorArchivos {
public:
    ManejadorArchivos(const std::string& rutaL, const std::string& rutaC, const std::string& rutaS)
        : rutaL_(rutaL), rutaC_(rutaC), rutaS_(rutaS) {}

    void compararArchivos() {
        std::vector<std::string> contenidoL = leerArchivo(rutaL_);
        std::vector<std::string> contenidoC = leerArchivo(rutaC_);

        std::vector<std::string> resultado;
        int totalCorrecto = 0, totalIncorrecto = 0, totalNoImplementado = 0;

        for (size_t i = 0; i < contenidoL.size(); ++i) {
            if (contenidoL[i] == contenidoC[i]) {
                resultado.push_back("Correcto");
                ++totalCorrecto;
            } else if (contenidoL[i] == "No implementado") {
                resultado.push_back("No implementado");
                ++totalNoImplementado;
            } else {
                resultado.push_back("Incorrecto");
                ++totalIncorrecto;
            }
        }

        std::ofstream salida(rutaS_);
        if (salida.is_open()) {
            for (size_t i = 0; i < resultado.size(); ++i) {
                salida << "Test " << (i + 1) << ": " << resultado[i] << std::endl;
                if (resultado[i] == "Incorrecto") {
                    salida << "   Esperado: " << contenidoC[i] << std::endl;
                    salida << "   Obtenido: " << contenidoL[i] << std::endl;
                }
            }
            salida << "Resumen:" << std::endl;
            salida << "   Correcto: " << totalCorrecto << std::endl;
            salida << "   Incorrecto: " << totalIncorrecto << std::endl;
            salida << "   No implementado: " << totalNoImplementado << std::endl;
            salida.close();
        } else {
            std::cerr << "Error al abrir el archivo de salida." << std::endl;
        }
    }

private:
    std::string rutaL_;
    std::string rutaC_;
    std::string rutaS_;

    std::vector<std::string> leerArchivo(const std::string& ruta) {
        std::vector<std::string> contenido;
        std::ifstream archivo(ruta);
        if (archivo.is_open()) {
            std::string linea;
            while (std::getline(archivo, linea)) {
                contenido.push_back(linea);
            }
            archivo.close();
        } else {
            std::cerr << "Error al abrir el archivo: " << ruta << std::endl;
        }
        return contenido;
    }
};

int main() {
    std::string rutaL = "estudiante.txt";
    std::string rutaC = "correcto.txt";
    std::string rutaS = "resultado.txt";

    ManejadorArchivos manejador(rutaL, rutaC, rutaS);
    manejador.compararArchivos();

    return 0;
}

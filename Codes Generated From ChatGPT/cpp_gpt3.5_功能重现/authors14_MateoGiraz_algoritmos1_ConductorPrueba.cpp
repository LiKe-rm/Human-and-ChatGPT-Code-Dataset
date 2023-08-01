#include <iostream>
#include <string>
#include <filesystem>
#include "ConductorPrueba.h"
#include "ManejadorImpresionPrueba.h"
#include "ManejadorSalidaPrueba.h"

class ConductorPrueba {
private:
    int nroPrueba;
    bool firstTime;
    ManejadorImpresionPrueba manejadorImpresion;
    ManejadorSalidaPrueba manejadorSalida;

public:
    ConductorPrueba() : nroPrueba(0), firstTime(true) {}

    ~ConductorPrueba() {}

    void correrPrueba(bool paraParseo = false) {
        manejadorSalida = ManejadorSalidaPrueba::getInstancia();
        std::filesystem::create_directories("Prueba");

        correrPruebaConcreta();

        manejadorSalida->setSalida(&std::cout);
    }

void correrPrueba(bool paraParseo = false) {
    manejadorSalida = ManejadorSalidaPrueba::getInstancia();
    
    try {
        std::filesystem::create_directories("Prueba");

        // 重定向输出到文件
        std::ofstream outputFile;
        if (paraParseo) {
            outputFile.open("Prueba/salida.txt");
            manejadorSalida->setSalida(&outputFile);
        } else {
            manejadorSalida->setSalida(&std::cout);
        }

        // 运行具体的测试
        correrPruebaConcreta();

        // 关闭文件
        if (paraParseo) {
            outputFile.close();
        }
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
    }

    // 将输出设置为屏幕输出
    manejadorSalida->setSalida(&std::cout);
}


    void ver(bool condition, const std::string &message) {
        manejadorImpresion.ver(condition, message, nroPrueba);
    }

    void ver2(bool condition, const std::string &message) {
        manejadorImpresion.ver2(condition, message, nroPrueba);
    }

    void ver3(const std::string &message, int puntos) {
        manejadorImpresion.ver3(message, puntos, nroPrueba);
    }

    void comenzarNuevaPrueba() {
        nroPrueba = 0;
    }

    EstadisticaPrueba &getEstadisticaGlobal() {
        return manejadorImpresion.getEstadisticaGlobal();
    }

    ManejadorImpresionPrueba &getManejadorImpresion() {
        return manejadorImpresion;
    }

    ManejadorSalidaPrueba &getManejadorSalida() {
        return manejadorSalida;
    }

protected:
    virtual void correrPruebaConcreta() = 0;
};

// Aquí puedes implementar otras clases como ManejadorImpresionPrueba, ManejadorSalidaPrueba, EstadisticaPrueba, etc.

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;
using namespace System;

// Estados para saber exactamente dónde dibujar a las personas
enum EstadoPersona { EN_TIERRA, EN_NAVE, EN_LUNA };

struct Persona {
    int x, y;
    EstadoPersona estado;
    ConsoleColor color;
};

// ================= FUNCIONES DE DIBUJO ASCII =================
void DibujarTierra() {
    Console::ForegroundColor = ConsoleColor::DarkBlue;
    Console::SetCursorPosition(2, 7);  cout << "       _____       ";
    Console::SetCursorPosition(2, 8);  cout << "    .-'.  ':'-.    ";
    Console::SetCursorPosition(2, 9);  cout << "  .''::: .:    '.  ";
    Console::SetCursorPosition(2, 10); cout << " /   :::::'      \\ ";
    Console::SetCursorPosition(2, 11); cout << ";.    ':' `       ;";
    Console::SetCursorPosition(2, 12); cout << "|       '..       |";
    Console::SetCursorPosition(2, 13); cout << "; '       ::::.   ;";
    Console::SetCursorPosition(2, 14); cout << " \\       '::::   / ";
    Console::SetCursorPosition(2, 15); cout << "  '.      :::  .'  ";
    Console::SetCursorPosition(2, 16); cout << "    '-.___'_.-'    ";
}

void DibujarLuna() {
    Console::ForegroundColor = ConsoleColor::Gray;
    // Luna alejada (X = 85) para un recorrido más largo
    Console::SetCursorPosition(85, 6);  cout << "         ___---___      ";
    Console::SetCursorPosition(85, 7);  cout << "      .--          --.    ";
    Console::SetCursorPosition(85, 8);  cout << "    ./   ()      .-. \\.  ";
    Console::SetCursorPosition(85, 9);  cout << "   /   o    .   (   )  \\";
    Console::SetCursorPosition(85, 10); cout << "  / .           '-'     \\";
    Console::SetCursorPosition(85, 11); cout << " | ()    .  O         .   |";
    Console::SetCursorPosition(85, 12); cout << "|                          |";
    Console::SetCursorPosition(85, 13); cout << "|    o           ()        |";
    Console::SetCursorPosition(85, 14); cout << "|        .--.          O   |";
    Console::SetCursorPosition(85, 15); cout << " | .    |    |            |";
    Console::SetCursorPosition(85, 16); cout << "  \\    `.__.'    o   .  /  ";
    Console::SetCursorPosition(85, 17); cout << "   \\                   /   ";
    Console::SetCursorPosition(85, 18); cout << "    `\\  o    ()      /'    ";
    Console::SetCursorPosition(85, 19); cout << "      `--___   ___--'      ";
    Console::SetCursorPosition(85, 20); cout << "            ---            ";
}

void DibujarPersona(int x, int y, ConsoleColor color) {
    Console::ForegroundColor = color;
    Console::SetCursorPosition(x, y);     cout << " O ";
    Console::SetCursorPosition(x, y + 1); cout << "/|\\";
    Console::SetCursorPosition(x, y + 2); cout << "/ \\";
}

void BorrarPersona(int x, int y) {
    Console::SetCursorPosition(x, y);     cout << "   ";
    Console::SetCursorPosition(x, y + 1); cout << "   ";
    Console::SetCursorPosition(x, y + 2); cout << "   ";
}

void DibujarNave(int x, int y, ConsoleColor color) {
    Console::ForegroundColor = color;
    Console::SetCursorPosition(x, y);     cout << " /\\ ";
    Console::SetCursorPosition(x, y + 1); cout << "|##|";
    Console::SetCursorPosition(x, y + 2); cout << "/__\\";
}

void BorrarNave(int x, int y) {
    Console::SetCursorPosition(x, y);     cout << "    ";
    Console::SetCursorPosition(x, y + 1); cout << "    ";
    Console::SetCursorPosition(x, y + 2); cout << "    ";
}

void DibujarMeteorito(int x, int y) {
    Console::ForegroundColor = ConsoleColor::Red;
    Console::SetCursorPosition(x, y);     cout << "   /\\   ";
    Console::SetCursorPosition(x, y + 1); cout << "|\\/  \\/|";
    Console::SetCursorPosition(x, y + 2); cout << "| ____ |";
    Console::ForegroundColor = ConsoleColor::White;
    Console::SetCursorPosition(x, y + 3); cout << "/      \\";
    Console::SetCursorPosition(x, y + 4); cout << "|      |";
    Console::SetCursorPosition(x, y + 5); cout << "\\______/";
}

void BorrarMeteorito(int x, int y) {
    Console::SetCursorPosition(x, y);     cout << "        ";
    Console::SetCursorPosition(x, y + 1); cout << "        ";
    Console::SetCursorPosition(x, y + 2); cout << "        ";
    Console::SetCursorPosition(x, y + 3); cout << "        ";
    Console::SetCursorPosition(x, y + 4); cout << "        ";
    Console::SetCursorPosition(x, y + 5); cout << "        ";
}

// ================= PANTALLAS DEL SISTEMA =================

void Presentacion() {
    Console::Clear();
    Console::ForegroundColor = ConsoleColor::Cyan;
    Console::SetCursorPosition(30, 5); cout << "=======================================";
    Console::SetCursorPosition(30, 6); cout << "        FLY ME TO THE MOON             ";
    Console::SetCursorPosition(30, 7); cout << "          Mision Artemis II            ";
    Console::SetCursorPosition(30, 8); cout << "=======================================";
    Console::ForegroundColor = ConsoleColor::White;
    Console::SetCursorPosition(30, 11); cout << "Instrucciones:";
    Console::SetCursorPosition(30, 12); cout << "- Rescata a las 12 personas cerca a la Tierra.";
    Console::SetCursorPosition(30, 13); cout << "- Muevete con las flechas direccionales.";
    Console::SetCursorPosition(30, 14); cout << "- Tu nave Orion solo puede llevar 2 a la vez.";
    Console::SetCursorPosition(30, 15); cout << "- Evita los meteoritos, si chocas pierdes 1 vida.";
    Console::SetCursorPosition(30, 18); cout << "Presiona cualquier tecla para comenzar el rescate...";
    char pausa = _getch();
}

void Creditos() {
    Console::Clear();
    Console::ForegroundColor = ConsoleColor::Yellow;
    Console::SetCursorPosition(35, 10); cout << "Desarrollado por el Equipo Experto UPC";
    Console::SetCursorPosition(35, 12); cout << "Gracias por jugar Mision Artemis II";
    Sleep(3000);
}

// ================= LÓGICA PRINCIPAL DEL JUEGO =================

void EjecutarRescate() {
    int naveX = 20, naveY = 10;
    int vidas = 3;
    int velocidadNave = rand() % 2 + 1;
    ConsoleColor colorNave = ConsoleColor::Magenta;

    int personasEnTierra = 12;
    int pasajerosNave = 0;
    int rescatadosLuna = 0;

    int tiempoRestante = rand() % 41 + 80;
    int ciclosFrames = 0;

    int met1X = 50, met1Y = 2;
    int met2X = 65, met2Y = -10; // Cae con retraso

    Persona personas[12];
    ConsoleColor paleta[5] = { ConsoleColor::Green, ConsoleColor::Cyan, ConsoleColor::Yellow, ConsoleColor::Red, ConsoleColor::White };

    // Generar personas esparcidas sobre/alrededor de la Tierra
    for (int i = 0; i < 12; i++) {
        personas[i].x = rand() % 20 + 15; // Sobre la Tierra
        personas[i].y = rand() % 16 + 6;
        personas[i].estado = EN_TIERRA;
        personas[i].color = paleta[rand() % 5];
    }

    Console::Clear();

    while (vidas > 0 && rescatadosLuna < 12 && tiempoRestante > 0) {

        // 1. DIBUJAR ENTORNO Y PERSONAS
        DibujarTierra();
        DibujarLuna();

        for (int i = 0; i < 12; i++) {
            if (personas[i].estado == EN_TIERRA || personas[i].estado == EN_LUNA) {
                DibujarPersona(personas[i].x, personas[i].y, personas[i].color);
            }
        }

        // 2. PANEL DE CONTROL (HUD)
        Console::ForegroundColor = ConsoleColor::Yellow;
        Console::SetCursorPosition(2, 1);
        cout << "[ NAVE: ORION ]  [ VELOCIDAD: " << velocidadNave << " ]  [ VIDAS: " << vidas << " ]  [ TIEMPO: " << tiempoRestante << "s ]   ";
        Console::SetCursorPosition(2, 2);
        cout << "TIERRA: " << personasEnTierra << "   |   PASAJEROS: " << pasajerosNave << "/2   |   LUNA (RESCATADOS): " << rescatadosLuna << "/12   ";

        // 3. MOVER Y DIBUJAR METEORITOS
        if (met1Y >= 2) BorrarMeteorito(met1X, met1Y);
        if (met2Y >= 2) BorrarMeteorito(met2X, met2Y);

        met1Y++; if (met1Y > 28) { met1Y = 2; met1X = rand() % 20 + 45; }
        met2Y++; if (met2Y > 28) { met2Y = 2; met2X = rand() % 20 + 55; }

        if (met1Y >= 2) DibujarMeteorito(met1X, met1Y);
        if (met2Y >= 2) DibujarMeteorito(met2X, met2Y);

        // 4. CONTROL DE LA NAVE CON TECLADO
        BorrarNave(naveX, naveY);
        if (_kbhit()) {
            char tecla = _getch();
            if (tecla == -32) { tecla = _getch(); }

            if (tecla == 72 && naveY > 4) naveY -= velocidadNave; // Arriba
            if (tecla == 80 && naveY < 28) naveY += velocidadNave; // Abajo
            if (tecla == 75 && naveX > 2) naveX -= velocidadNave; // Izquierda 
            if (tecla == 77 && naveX < 110) naveX += velocidadNave; // Derecha (ampliado por la Luna)
        }
        DibujarNave(naveX, naveY, colorNave);

        // 5. LÓGICA DE COLISIONES Y RESCATES

        // Colisión con Meteoritos (Ajustado al nuevo tamaño 8x6 del meteorito)
        if ((abs(naveX - met1X) <= 6 && abs(naveY - met1Y) <= 4) ||
            (abs(naveX - met2X) <= 6 && abs(naveY - met2Y) <= 4)) {
            vidas--;
            BorrarNave(naveX, naveY);
            naveX = 40; naveY = 15; // Retorna al centro

            // Si choca, las personas en la nave se pierden en el espacio (vuelven a la Tierra)
            for (int i = 0; i < 12; i++) {
                if (personas[i].estado == EN_NAVE) {
                    personas[i].estado = EN_TIERRA;
                    personasEnTierra++;
                }
            }
            pasajerosNave = 0;

            Console::SetCursorPosition(45, 15);
            Console::ForegroundColor = ConsoleColor::Red;
            cout << "¡IMPACTO! Pierdes 1 vida.";
            Sleep(1000);
            Console::SetCursorPosition(45, 15); cout << "                         ";
        }

        // Zona de Carga (Recolectar personas de cuerpo completo)
        for (int i = 0; i < 12; i++) {
            if (personas[i].estado == EN_TIERRA && pasajerosNave < 2) {
                // Distancia de colisión ajustada al tamaño del cuerpo
                if (abs(naveX - personas[i].x) <= 3 && abs(naveY - personas[i].y) <= 3) {
                    personas[i].estado = EN_NAVE;
                    BorrarPersona(personas[i].x, personas[i].y);
                    pasajerosNave++;
                    personasEnTierra--;
                }
            }
        }

        // Zona de Descarga (Superficie de la Luna)
        if (naveX >= 80 && pasajerosNave > 0) {
            for (int i = 0; i < 12; i++) {
                if (personas[i].estado == EN_NAVE) {
                    personas[i].estado = EN_LUNA;
                    // Posicionamos a las personas ordenadas sobre la Luna
                    personas[i].x = 88 + (rescatadosLuna % 4) * 4;
                    personas[i].y = 8 + (rescatadosLuna / 4) * 4;
                    rescatadosLuna++;
                }
            }
            pasajerosNave = 0;
        }

        // 6. CONTROL DEL TIEMPO
        Sleep(50);
        ciclosFrames++;
        if (ciclosFrames == 20) {
            tiempoRestante--;
            ciclosFrames = 0;
        }
    }

    // ================= VENTANAS DE FINALIZACIÓN =================
    Console::Clear();
    Console::SetCursorPosition(35, 12);
    if (rescatadosLuna == 12) {
        Console::ForegroundColor = ConsoleColor::Green;
        cout << "¡GANASTE! Has rescatado a todas las personas a tiempo.";
    }
    else if (vidas == 0) {
        Console::ForegroundColor = ConsoleColor::Red;
        cout << "GAME OVER. La nave Orion fue destruida.";
    }
    else if (tiempoRestante <= 0) {
        Console::ForegroundColor = ConsoleColor::DarkYellow;
        cout << "TIEMPO AGOTADO. No lograste el rescate a tiempo.";
    }
    Sleep(3000);
}

int main() {
    srand((unsigned int)time(0));
    Console::CursorVisible = false;
    char jugarDeNuevo;

    Presentacion();

    do {
        EjecutarRescate();

        Console::Clear();
        Console::ForegroundColor = ConsoleColor::White;
        Console::SetCursorPosition(35, 10);
        cout << "¿Deseas jugar un nuevo rescate? (S/N): ";
        cin >> jugarDeNuevo;
        jugarDeNuevo = toupper(jugarDeNuevo);

    } while (jugarDeNuevo == 'S');

    Creditos();
    return 0;
}
#include <iostream>
#include <random>
#include <limits> 
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <queue>
#include <list>
#include <chrono>  // Para chrono::seconds
#include <thread>  // Para this_thread::sleep_for
#include <stack>

using namespace std;
#define ANSI_RGB(R, G, B) "\033[38;2;" << R << ";" << G << ";" << B << "m"
int ID_IMPLEMENTOS = 0;
int ID_PERSONAJES = 0;
int MIN = 1000000;


// Colores estándar
#define RESET       "\033[0m"
#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
#define ORANGE_RGB  "\033[38;2;255;165;0m"
#define GRAY        "\033[90m"
#define LIGHT_BROWN "\33[38;2;208;156;95m"

// Colores brillantes
#define BRIGHT_BLACK    "\033[90m"
#define BRIGHT_RED      "\033[91m"
#define BRIGHT_GREEN    "\033[92m"
#define BRIGHT_YELLOW   "\033[93m"
#define BRIGHT_BLUE     "\033[94m"
#define BRIGHT_MAGENTA  "\033[95m"
#define BRIGHT_CYAN     "\033[96m"
#define BRIGHT_WHITE    "\033[97m"
vector<string> colores_bright = {BRIGHT_BLUE, BRIGHT_RED, BRIGHT_GREEN, BRIGHT_YELLOW, BRIGHT_MAGENTA, BRIGHT_CYAN, ORANGE_RGB, LIGHT_BROWN};
// Fondos estándar (Backgrounds)
#define BG_BLACK    "\033[40m"
#define BG_RED      "\033[41m"
#define BG_GREEN    "\033[42m"
#define BG_YELLOW   "\033[43m"
#define BG_BLUE     "\033[44m"
#define BG_MAGENTA  "\033[45m"
#define BG_CYAN     "\033[46m"
#define BG_WHITE    "\033[47m"

// Estilos de texto
#define BOLD        "\033[1m"      // Texto en negrita
#define DIM         "\033[2m"      // Texto tenue (no soportado en todos los terminales)
#define ITALIC      "\033[3m"      // Texto en cursiva
#define UNDERLINE   "\033[4m"      // Subrayado
#define BLINK       "\033[5m"      // Parpadeo (poco soportado)
#define REVERSE     "\033[7m"      // Invertir colores (foreground/background)
#define HIDDEN      "\033[8m"      // Texto oculto
#define STRIKE      "\033[9m"      // Texto tachado

// Combinaciones predefinidas
#define WARNING     (BOLD YELLOW)
#define ERROR       (BOLD RED)
#define SUCCESS     (BOLD GREEN)
#define INFO        (BOLD CYAN)
#define DEBUG       (BOLD BRIGHT_BLACK)
#define HIGHLIGHT   (BOLD BRIGHT_WHITE BG_BLUE)

void salaMovimiento() 
{
    int cont = 1;
    cout << "Moviendo a la siguiente sala... \n";
    while (cont <= 5)
    {
        this_thread::sleep_for(chrono::milliseconds(300));
        cout << "-->\t";
        cont++;
    }
    cout << "\n ha llegado a la sala... \n";
}

void mensajeInicial()
{
    cout << RED << ITALIC << "Lidera a Borin y su valiente grupo a través de los túneles ancestrales, " << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Evadiendo a los orcos y buscando la esquiva Puerta del Destino. " << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Cada paso es una batalla, cada decisión cuenta. " << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "¿Podrás guiarlos hacia la libertad antes de que Gnashrak los alcance? " << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "La esperanza de los enanos vive en tu coraje " << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout <<"¡El destino de la Ciudadela de Bronce está en tus manos! "  << RESET << endl;
    this_thread::sleep_for(chrono::seconds(2));
}

// Funcion validar y obtener un entero
int ObtenerEntero(string texto) 
{
    int numero;
    do 
    {
        cout << texto;
        cin >> numero;
        if (cin.fail() || numero < 0) {
            cout << "Entrada inválida. Ingrese un número válido.\n";
            cin.clear(); // Evitar errores
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        } else {
            return numero; // Devuelve el numero si está bien ingresado
        }
        // Ensure a return value in case the loop exits unexpectedly
    } while (cin.fail() == false || numero < 0);
    cin.clear();
    return 0; // No hace falta, pero me suelta error si no lo pongo
}

// Funcion validar y obtener texto
string ObtenerTexto(string mensaje) 
{
    cin.clear(); // Limpia flags de error
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta el buffer
    string entrada;
    while (true) {
        cout << mensaje;
        getline(cin, entrada);
        
        // Verificar si la entrada está vacía o solo contiene espacios
        if (entrada.empty() || entrada.find_first_not_of(' ') == string::npos) 
        {
            cout << "Error: No se permiten entradas vacias. Intente de nuevo.\n";
        } 
        else 
        {
            // Si la entrada es válida, salir del bucle
            break;
        }
        // Limpiar el buffer de entrada en caso de error previo
        cin.clear();
    }
    return entrada;
}

int numeroAleatorio(int min, int max) 
{
    static std::random_device rd;  // Semilla
    static std::mt19937 gen(rd()); // Motor Mersenne Twister
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

// Declarar estructura de implementos
class Implemento // Para cada heroe
{
    public: 
    string nombre;
    string tipo;
    string cambio;
    int ID;
    int requisito;                                      
    int valor;
    int uso;
    Implemento* siguiente = nullptr;
    Implemento* anterior = nullptr;

    Implemento(string n = "", string t = "", string c = "", int r = 0, int v = 0, int u = 0, int id = 0)
    {
        nombre = n;
        tipo = t;
        cambio = c;
        uso = u;
        requisito = r;
        valor = v;
        ID = id;
        siguiente = nullptr;
        anterior = nullptr;
    };
};
// "El ID ingresado no coincide con ningún heroe."
// Lista de implementos (mochila para cada heroe)
class Lista_Implementos
{
    public:
    Implemento* cabeza = nullptr;
    int cantidad = 0;
    int registros = 0;
    Lista_Implementos() : cabeza(nullptr), cantidad(0) {}
    ~Lista_Implementos()
    {
        Implemento* actual = cabeza;
        while(actual != nullptr)
        {
            Implemento* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }
    void agregarImplemento(string nomb, string tip, string cam, int req, int val, int us )
    {
        Implemento* nuevo = new Implemento(nomb, tip, cam, req, val, us, ID_IMPLEMENTOS + 1);
        if (cabeza == nullptr)
        {
            cabeza = nuevo;
        }
        else
        {
            Implemento* actual = cabeza;
            while (actual->siguiente != nullptr)
            {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
            nuevo->anterior = actual;
        }
        cantidad++;
        ID_IMPLEMENTOS++;
    }

    void nuevoImplemento()
    {
        string nombre, tipo, cambio; int uso, requisito, valor; 
        nombre = ObtenerTexto("Ingrese el nombre del implemento: ");
        cout<< "Ingrese el tipo del implemento \n" 
            << "1. Arma\n" 
            << "2. Defensa \n" 
            << "3. Consumible \n" 
            << "4. Herramienta \n";
        int opcion = ObtenerEntero("Opcion: ");
        switch (opcion)
        {
            case 1:  
                tipo = "Arma";
                cambio = "Ataque";
                break;
            case 2: 
                tipo = "Escudo";
                cambio = "Defensa"; 
                break;
            case 3: 
                tipo = "Consumible";
                cambio = "Vida"; 
                break;
            default: 
                cout << "Numero ingresado invalido. Intente de nuevo\n\n";
        }
        requisito = ObtenerEntero("Ingrese el requisito del implemento: ");
        valor = ObtenerEntero("Ingrese el valor (daño/cura/protección) a cambiar del implemento: ");
        uso = ObtenerEntero("Ingrese la cantidad de usos del implemento: ");
        agregarImplemento(nombre, tipo, cambio, uso, requisito, valor);
    }

    void mostrarImplementos()
    {
        if (cantidad == 0)
        {
            cout << "No hay implementos en la lista \n";
        }
        else
        {
            Implemento* actual = cabeza;
            while (actual != nullptr)
            {
                cout<< "- ID: " << actual->ID << ","
                    << " Nombre: <" << actual->nombre << ">,"
                    << " Cambio: +" << actual->valor << " en " << actual->cambio << ","
                    << " Fortaleza requerida: " << actual->requisito << ","
                    << " Usos: " << actual->uso << endl;
                actual = actual->siguiente;
            }
        }
    }

    void eliminarImplemento()
    {
        mostrarImplementos();
        int numero = ObtenerEntero("Ingrese 0 para no eliminar ningún implemento \nIngrese el ID del implemento a eliminar: ") ;
        if (cantidad == 0) 
        {
            cout << "No hay implementos en la lista.\n";
        }
        else
        {
            Implemento* actual = cabeza;
            Implemento* eliminar;
            while (actual != nullptr) 
            {
                if (numero == cabeza->ID)
                {
                    eliminar = cabeza;
                    cabeza = cabeza->siguiente;
                    actual->siguiente->anterior = nullptr;
                    cout << "<"<< eliminar->nombre << "> eliminado correctamente.\n";
                    delete eliminar;
                    cantidad--;
                    return;
                }
                else if (actual->ID == numero)
                {
                    eliminar = actual;
                    actual->anterior->siguiente = actual->siguiente;
                    if (actual->siguiente != nullptr)
                    {
                        actual->siguiente->anterior = actual->anterior;
                    }
                    cout << "<"<< eliminar->nombre << "> eliminado correctamente.\n\n";
                    delete eliminar;
                    cantidad--;
                    return;
                }
                actual = actual->siguiente;
            }
            if (numero != 0)
            {
                cout << "El implemento no fue encontrado en la lista \n";
            }
            else
            {
                cout << "No se eliminó ningún implemento\n";
            }
        }
    }

    void implementosPredeterminados()
    {   //Implemento
        agregarImplemento("Espada de Andúril", "Arma", "Ataque", 120, 200, 50);
        agregarImplemento("Arco de Galadriel", "Arma", "Ataque", 80, 150, 100);
        agregarImplemento("Hacha de Guerra Enana", "Arma", "Ataque", 150, 180, 30);
        agregarImplemento("Báculo de Gandalf", "Arma", "Ataque", 90, 100, 20);
        agregarImplemento("Anillo Único", "Defensa", "Escudo", 200, 500, 1);
        agregarImplemento("Daga Élfica", "Arma", "Ataque", 70, 120, 200);
        agregarImplemento("Escudo de Minas Tirith", "Defensa", "Escudo", 110, 150, 80);
        agregarImplemento("Poción de Curación", "Consumible", "Salud", 30, 75, 3);
        agregarImplemento("Red de Captura", "Defensa", "Defensa", 40, 25, 5);
        agregarImplemento("Cetro de Saruman", "Arma", "Ataque", 100, 300, 10);
        agregarImplemento("Armadura de Mithril", "Defensa", "Escudo", 140, 250, 150);
        agregarImplemento("Cuerno de Gondor", "Defensa", "Escudo", 60, 50, 2);
    }

    void editarImplemento()
    {
        int numero = ObtenerEntero("Ingrese 0 para no editar \nIngrese el ID del implemento a editar: ");
        Implemento* actual = cabeza;
        while (actual != nullptr) 
        {
            if (actual->ID == numero) 
            {
                actual->nombre = ObtenerTexto("Ingrese el nombre del nuevo implemento: ");
                actual->uso = ObtenerEntero("Ingrese la cantidad de usos nuevo implemento: ");
                actual->valor = ObtenerEntero("Ingrese el valor del nuevo implemento: ");
                actual->requisito = ObtenerEntero("Ingrese la fortaleza requerida del nuevo implemento: ");
                cout << "\nEl implemento <" << actual->nombre << "> ha sido actualizado. \n\n";
                return;
            }
            actual = actual->siguiente;
        }
        if (numero != 0)
        {
            cout << "El implemento no fue encontrado. \n";
        }
        else if (numero == 0)
        {
            cout << "Ningún implemento fue editado. \n";
        }
        
    }

    Implemento returnImplemento()
    {
        mostrarImplementos();
        int numero = ObtenerEntero("\nIngrese 0 si no quiere agregar ningún implemento\nIngrese el ID del implemento que quiera agregar: ");
        Implemento* actual = cabeza;
        while (actual != nullptr) 
        {
            if (actual->ID == numero) 
            {
                Implemento nuevo = *actual;
                nuevo.siguiente = nullptr;
                nuevo.anterior= nullptr;
                if (actual == cabeza) 
                {
                    cabeza = actual->siguiente;
                    if (cabeza != nullptr)
                    {
                        cabeza->anterior = nullptr;
                    }
                } 
                else 
                {
                    actual->anterior->siguiente = actual->siguiente;
                    if (actual->siguiente != nullptr)
                    {
                        actual->siguiente->anterior = actual->anterior;
                    }
                }
                delete actual;
                return nuevo;
            }
            actual = actual->siguiente;
        }
        if (numero != 0)
        {
            cout << "El implemento no fue encontrado \n\n";
        }
        else
        {
            cout << "No se agregó ningún implemento \n\n";
        }
        return Implemento("","",0,0,0);
    }

    // Funcion eliminar un implemento cuando sus usos llegan a 0
    void ultimoUso(int numero)
    {
        if (cantidad == 0) 
        {
            cout << "No hay implementos en la mochila.\n";
        }
        else
        {
            Implemento* actual = cabeza;
            Implemento* eliminar;
            while (actual != nullptr) 
            {
                if (numero == cabeza->ID)
                {
                    eliminar = cabeza;
                    cabeza = cabeza->siguiente;
                    cout << YELLOW << "<"<< eliminar->nombre << "> ha llegado a 0 usos\n" << RESET;
                    delete eliminar;
                    cantidad--;
                    return;
                }
                else if (actual->ID == numero)
                {
                    eliminar = actual->siguiente;
                    actual->anterior->siguiente = actual->siguiente;
                    if (actual->siguiente != nullptr)
                    {
                        actual->siguiente->anterior = actual->anterior;
                    }
                    cout << "<"<< eliminar->nombre << "> ha llegado a 0 usos.\n\n";
                    delete eliminar;
                    cantidad--;
                    return;
                }
                actual = actual->siguiente;
            }
            if (numero != 0)
            {
                cout << "El implemento no fue encontrado en la lista \n";
            }
            else
            {
                cout << "No se eliminó ningún implemento\n";
            }
        }
    }
};

Lista_Implementos lista_implementos;

/// Declarar estructura de Especie (ya sea heroe u orco) 
class Especie {
    public:
    string nombre;
    string tipo;
    int id;
    int fortaleza; // Heroes
    int fort_base; // Heroes
    int dano; // Orcos
    int vida_base;
    int vida;
    int velocidad;
    int defensa;
    Especie *siguiente = nullptr;
    Especie *anterior = nullptr;
    Lista_Implementos mochila;
    Especie(string nmb, string tip, int fort, int vid,  int vel, int id_) // Constructor-Heroe
    { 
        nombre = nmb;
        tipo = tip;
        vida = vid;
        vida_base = vid;
        fortaleza = fort;
        fort_base = fort;
        velocidad = vel;
        id = id_;
        defensa = 0;
        dano = 0;
    };
    
    Especie(string n, string tip, int vid, int vel, int da) // Constructor-Orcos
    { 
        nombre = n;
        tipo = tip;
        vida = vid;
        vida_base = vid;
        velocidad = vel;
        dano = da;
        fortaleza = 0;
    };
};

// Lista para heroes disponibles y equipo
class Lista_Heroes
{
    public:
        Especie* cabeza;
        int cantidad;
        int cant_vivos;
        Lista_Heroes() : cabeza(nullptr), cantidad(0) {}
    
        ~Lista_Heroes() //Destructor
        { 
            Especie* actual = cabeza;
            while (actual != nullptr) 
            {
                Especie* temp = actual;
                actual = actual->siguiente;
                delete temp;
            }
        }

        void agregarHeroe(string name, string tip, int fort, int vid, int vel) 
        {
            Especie* nuevo = new Especie(name, tip, fort, vid, vel, ID_PERSONAJES+1);
            if (cabeza == nullptr)
            {
                cabeza = nuevo;
            }
            else
            {
                Especie* actual = cabeza;
                while (actual->siguiente != nullptr)
                {
                    actual = actual->siguiente;
                }
                actual->siguiente = nuevo;
                nuevo->anterior = actual;   
            }
            cantidad++;
            ID_PERSONAJES++;
        }

        // CRUD con heroes
        void agregarNuevo_Heroe()
        {
            string nombre, tipo;
            int vida, fortaleza, velocidad;
            nombre = ObtenerTexto("Ingrese el nombre del nuevo heroe: ");
            fortaleza = ObtenerEntero("Ingrese la fortaleza del heroe: ");
            vida = ObtenerEntero("Ingrese la vida del heroe: ");
            velocidad = ObtenerEntero("Ingrese la velocidad del heroe: ");
            tipo = ObtenerTexto("Ingrese la especie del heroe: ");
            agregarHeroe(nombre, tipo, vida, fortaleza, velocidad);
            cout << "Heroe llamado <" << nombre << "> del tipo " << tipo << " fue creado con exito.\n\n";
        }
        
        void mostrarEspecies() 
        {
            if (cantidad == 0) 
            {
                cout << "\nNo hay heroes en la lista.\n";
            }
            else
            {
                Especie* actual = cabeza;
                cout << "\nLista de heroes (cantidad: " << cantidad << ")";
                while (actual != nullptr) 
                {
                    cout << "\nID: " << actual->id << ", ";
                    cout << "Nombre: <" << actual->nombre << ">, ";
                    cout << "Tipo: " << actual->tipo << ", ";
                    cout << "Fortaleza: " << actual->fortaleza << ", ";
                    cout << "Vida: " << actual->vida << ", ";
                    cout << "Velocidad: " << actual->velocidad << " ";
                    cout << "Defensa: " << actual->defensa << " ";
                    actual = actual->siguiente;
                }
                cout << endl << endl;
            }
        }

        void eliminarEspecie()
        {   
            mostrarEspecies();
            int numero;
            numero = ObtenerEntero("Ingrese 0 para no eliminar ninguno. \nIngrese el ID del heroe a eliminar: ");
            if (cantidad == 0) 
            {
                cout << "No hay heroes en la lista.\n";
            }
            else
            {
                Especie* actual = cabeza;
                Especie* eliminar;
                while (actual != nullptr) 
                {
                    if (numero == cabeza->id)
                    {
                        eliminar = cabeza;
                        cabeza = cabeza->siguiente;
                        actual->siguiente->anterior = nullptr;
                        cout << "<"<< eliminar->nombre << "> eliminado correctamente.\n";
                        delete eliminar;
                        return;
                    }
                    else if (actual->id == numero)
                    {
                        eliminar = actual;
                        actual->anterior->siguiente = actual->siguiente;
                        if (actual->siguiente != nullptr)
                        {
                            actual->siguiente->anterior = actual->anterior;
                        }
                        cout << "<"<< eliminar->nombre << "> eliminado correctamente.\n\n";
                        delete eliminar;
                        return;
                    }
                    actual = actual->siguiente;
                }
                if (numero != 0)
                {
                    cout << "\nNo se encontró al héroe con el ID indicado.\n";
                }
                else
                {
                    cout << "No se eliminó ninguna especie.\n";
                }
                
            }
        }

        void EditarHeroe()
        {
            mostrarEspecies();
            int numero;
            numero = ObtenerEntero("Ingrese 0 para no editar ninguno. \nIngrese el ID del heroe a editar: ");
            Especie* actual = cabeza;
            while (actual != nullptr) 
            {
                if (actual->id == numero) 
                {

                    actual->nombre = ObtenerTexto("Ingrese el nombre del heroe: ");
                    actual->fortaleza = ObtenerEntero("Ingrese la fortaleza del heroe: ");
                    actual->fort_base = actual->fortaleza;
                    actual->vida = ObtenerEntero("Ingrese la vida del heroe: ");
                    actual->vida_base = actual->vida;
                    actual->velocidad = ObtenerEntero("Ingrese la velocidad del heroe: ");
                    actual->tipo = ObtenerTexto("Ingrese el tipo de especie del heroe: ");
                    cout << "\nEl heroe <" << actual->nombre << "> ha sido actualizado. \n\n";
                    return;
                }
                actual = actual->siguiente;
            }
            if (numero != 0)
            {
                cout << "\nNo se encontró al héroe con el ID indicado.\n";
            }
            else
            {
                cout << "No se editó ninguna especie.\n";
            }
        }

        // En caso de no elegir por archivos:
        void heroesPredeterminados()
        {
            agregarHeroe("Aragorn", "Humano", 120, 70, 60);
            agregarHeroe("Legolas", "Elfo", 80, 65, 90);
            agregarHeroe("Gimli", "Enano", 150, 100, 40);
            agregarHeroe("Boromir", "Humano", 120, 70, 60);
            agregarHeroe("Gandalf", "Mago", 95, 55, 50);
            agregarHeroe("Titania", "Elfo", 80, 65, 90);
        }


        // Agregar una especie de la lista de heroes disponibles a la lista del equipo:
        // Busca la especie en la lista de heroes disponibles
        Especie RetornarEspecie(int id_agg)
        {
            Especie* actual = cabeza;
            while (actual != nullptr) 
            {
                if (actual->id == id_agg) 
                {
                    Especie nuevo = *actual;
                    nuevo.siguiente = nullptr;
                    nuevo.anterior = nullptr;
                    cout << "El heroe <" << nuevo.nombre << "> ha sido agregado al equipo\n";
                    if (actual == cabeza) 
                    {
                        cabeza = actual->siguiente;
                        if (cabeza != nullptr)
                        {
                            cabeza->anterior = nullptr;
                        }
                    } 
                    else 
                    {
                        actual->anterior->siguiente = actual->siguiente;
                        if (actual->siguiente != nullptr)
                            actual->siguiente->anterior = actual->anterior;
                    }
                    delete actual;
                    return nuevo;
                }
                actual = actual->siguiente;
            }
            // Si no se encontró el héroe, retornar un Especie por defecto
            if (id_agg != 0)
            {
                cout << "\nNo se encontró al héroe con el ID indicado.\n";
            }
            else
            {   
                cout << "No se agregó ninguna especie.\n";
            }
            return Especie("", "", 0, 0, 0, 0);
        }

        // El heroe encontrado se ingresa en esta funcion y es enlazado a la lista
        void agregarHeroe(Especie nuevo_heroe) 
        {
            if (nuevo_heroe.id != 0)
            {
                string nombre = nuevo_heroe.nombre; string tipo = nuevo_heroe.tipo; int vida = nuevo_heroe.vida; 
                int fortaleza = nuevo_heroe.fortaleza; int velocidad = nuevo_heroe.velocidad; int id = nuevo_heroe.id;
                Especie* nuevo = new Especie(nombre, tipo, fortaleza, vida, velocidad, id);
                if (cabeza == nullptr)
                {
                    cabeza = nuevo;
                }
                else
                {
                    Especie* actual = cabeza;
                    while (actual->siguiente != nullptr)
                    {
                        actual = actual->siguiente;
                    }
                    actual->siguiente = nuevo;
                    nuevo->anterior = actual;
                }
                cantidad++;
                ID_PERSONAJES++;
            }
        }

        void mostrarMochilas()
        {
            Especie* actual = cabeza;
            
            while (actual != nullptr) 
            {
                cout << "\nMochila de <" << actual->nombre << "> ";
                cout << "(ID: " << actual->id << ", Fortaleza = " << actual->fortaleza <<"): \n";
                cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n";
                if (actual->mochila.cantidad == 0)
                {
                    cout << " Empty\n";
                    
                }
                else
                {
                    actual->mochila.mostrarImplementos();
                }
                cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n";
                actual = actual->siguiente;
            }
            cout << endl << endl;
        }

        void agregar_a_Mochila(Implemento nuevo_implemento)
        {
            int numero = 1;
            while (numero != 0)
            {
                mostrarMochilas();
                numero = ObtenerEntero("Ingrese 0 para no agregarlo a ninguno \n¿A cuál heroe quiere agregarle implemento (Ingrese el ID)?: ");
                Especie* actual = cabeza;
                while (actual != nullptr) 
                {
                    if (numero == actual->id)
                    {
                        if (actual->mochila.cantidad == 5)
                        {
                            cout << "\nLa mochila de este heroe está llena.\n";
                            lista_implementos.agregarImplemento(nuevo_implemento.nombre, nuevo_implemento.tipo, 
                            nuevo_implemento.cambio, nuevo_implemento.requisito, nuevo_implemento.valor, nuevo_implemento.uso);
                            return;
                        }
                        else if (actual->fortaleza < nuevo_implemento.requisito)
                        {
                            cout << "\nEl heroe no tiene la fortaleza (" << actual->fortaleza << ") necesaria para llevar el implemento (" << nuevo_implemento.requisito <<"). \n";
                            lista_implementos.agregarImplemento(nuevo_implemento.nombre, nuevo_implemento.tipo, 
                            nuevo_implemento.cambio, nuevo_implemento.requisito, nuevo_implemento.valor, nuevo_implemento.uso);
                            return;
                        }
                        else
                        {
                            string nombre = nuevo_implemento.nombre; string tipo = nuevo_implemento.tipo; string cambio = nuevo_implemento.cambio;
                            int uso = nuevo_implemento.uso; int requisito = nuevo_implemento.requisito; int valor = nuevo_implemento.valor;
                            actual->mochila.agregarImplemento(nombre, tipo, cambio, uso, requisito, valor);
                            cout << "\nEl implemento " << nombre << " fue agregado a la mochila de <" << actual->nombre << ">\n";
                            if (tipo == "Defensa")
                            {
                                actual->defensa = valor;
                            }
                            return;
                        }
                    }
                    actual = actual->siguiente;
                }
                if (numero != 0)
                {
                    cout << "El ID ingresado no coincide con ningún heroe.";
                }
                else
                {
                    cout << "No se agregó el implemento a ninguna mochila.";
                }
            }
        }
        
        void agregar_a_Mochila_conid(Implemento nuevo_implemento, int numero)
        {
            while (numero != 0)
            {
                Especie* actual = cabeza;
                while (actual != nullptr) 
                {
                    if (numero == actual->id)
                    {
                        if (actual->mochila.cantidad == 5)
                        {
                            cout << "\nLa mochila de este heroe está llena.\n";
                            return;
                        }
                        if (actual->fortaleza < nuevo_implemento.requisito)
                        {
                            cout << "\nEl heroe no tiene la fortaleza (" << actual->fortaleza << ") necesaria para llevar el implemento (" << nuevo_implemento.requisito <<"). \n";
                        }
                        string nombre = nuevo_implemento.nombre; string tipo = nuevo_implemento.tipo; string cambio = nuevo_implemento.cambio;
                        int uso = nuevo_implemento.uso; int requisito = nuevo_implemento.requisito; int valor = nuevo_implemento.valor;
                        actual->mochila.agregarImplemento(nombre, tipo, cambio, requisito, valor, uso);
                        cout << "\nEl implemento " << nombre << " fue agregado a la mochila de <" << actual->nombre << ">\n";
                        if (tipo == "Defensa")
                        {
                            actual->defensa = valor;
                        }
                        return;
                    }
                    actual = actual->siguiente;
                }
                if (numero != 0)
                {
                    cout << "El ID ingresado no coincide con ningún heroe.";
                    return;
                }
                else
                {
                    cout << "No se agregó el implemento a ninguna mochila.";
                    return;
                }
            }
        }

        void eliminarImplemento_conID(int numero)
        {
            
        }
    
        int suma_Mochilas()
        {
            int suma = 0;
            Especie* actual = cabeza;
            while (actual != nullptr) 
            {
                suma += actual->mochila.cantidad;
                actual = actual->siguiente;
            }
            cout << endl << endl;
            return suma;
        }
        
        int heroes_conVida()
        {
            int contador = 0;
            Especie* actual = cabeza;
            while (actual == nullptr)
            {
                if (actual->vida > 0)
                {
                    contador++;
                }
                actual->siguiente;
            }
            return contador;
        }
};

// Se crean las listas enlazadas
Lista_Heroes lista_heroes;
Lista_Heroes lista_equipo;


// Menu para heroes y equipo
void MenuHeroes()
{
    int opcion;
    do 
    {  
        cout << "╔════════════════════════════╗\n";
        cout << "║        MENÚ HEROES         ║\n";
        cout << "╠════════════════════════════╣\n";
        cout << "║ 1. Equipo                  ║\n";
        cout << "║ 2. Especies                ║\n";
        cout << "║ 3. Implementos             ║\n";
        cout << "║ 4. Salir                   ║\n";
        cout << "╚════════════════════════════╝\n";
        opcion = ObtenerEntero("Opcion: ");
        switch (opcion)
        {
            case 1:
                int opcion_equipo;
                do 
                {
                    cout << "╔══════════════════════════════════════════╗\n";
                    cout << "║     ¿Qué desea hacer con el equipo?      ║\n";
                    cout << "╠══════════════════════════════════════════╣\n";
                    cout << "║ 1. Observar equipo                       ║\n";
                    cout << "║ 2. Agregar                               ║\n";
                    cout << "║ 3. Eliminar                              ║\n";
                    cout << "║ 4. Editar                                ║\n";
                    cout << "║ 5. Mochilas                              ║\n";
                    cout << "║ 6. Regresar                              ║\n";
                    cout << "╚══════════════════════════════════════════╝\n";
                    opcion_equipo = ObtenerEntero("Opcion: ");
                    switch (opcion_equipo)
                    {
                    case 1:
                        lista_equipo.mostrarEspecies();
                        break;
                    case 2:
                        if (lista_equipo.cantidad == 4)
                        {
                            cout << "El equipo ya tiene 4 integrantes. No se pueden agregar más.\n";
                            break;
                        }
                        int id_agregar;
                        lista_heroes.mostrarEspecies();
                        id_agregar = ObtenerEntero("Ingrese 0 para no agregar ninguno. \nID del heroe a agregar: ");
                        if (id_agregar != 0)
                        {
                            lista_equipo.agregarHeroe(lista_heroes.RetornarEspecie(id_agregar));
                            lista_heroes.cantidad--;
                            break;
                        }
                        break;
                    case 3:
                        lista_equipo.eliminarEspecie();
                        break;
                    case 4: 
                        lista_equipo.EditarHeroe();
                        break;
                    case 5:
                        if (lista_equipo.cantidad == 0)
                        {
                            cout << "No hay heroes en el equipo a quienes ver su mochila \n";
                            break;
                        }
                        int opcion_mochila;
                        do 
                        {
                            cout << "╔══════════════════════════════════════════╗\n";
                            cout << "║    ¿Que desea hacer con las mochilas?    ║\n";
                            cout << "╠══════════════════════════════════════════╣\n";
                            cout << "║ 1. Observar mochilas                     ║\n";
                            cout << "║ 2. Agregar implemento                    ║\n";
                            cout << "║ 3. Agregar poder mágico                  ║\n";
                            cout << "║ 4. Eliminar implemento                   ║\n";
                            cout << "║ 5. Editar implemento                     ║\n";
                            cout << "║ 6. Regresar                              ║\n";
                            cout << "╚══════════════════════════════════════════╝\n";
                            opcion_mochila = ObtenerEntero("Opcion: ");
                            switch (opcion_mochila)
                            {
                                case 1:
                                    lista_equipo.mostrarMochilas();
                                    break;
                                case 2:
                                    lista_equipo.agregar_a_Mochila(lista_implementos.returnImplemento());
                                    break;
                                case 3:
                                    int opcion_poder_magico;
                                    do
                                    {
                                        cout << "╔══════════════════════════════════════════╗\n";
                                        cout << "║          Elija un poder mágico           ║\n";
                                        cout << "╠══════════════════════════════════════════╣\n";
                                        cout << "║ 1. Poder Magico de Enanos                ║\n";
                                        cout << "║ 2. Poder Magico Translador de Salas      ║\n";
                                        cout << "║ 3. Poder Magico contra los orcos         ║\n";
                                        cout << "║ 4. Duplicador de ataque de implemento    ║\n";
                                        cout << "║ 5. Regresar                              ║\n";
                                        cout << "╚══════════════════════════════════════════╝\n";
                                        opcion_poder_magico = ObtenerEntero("Opcion: ");
                                        cout << "Escoja un heroe: \n";
                                        lista_equipo.mostrarMochilas();
                                        int id;
                                        switch(opcion_poder_magico)
                                        {
                                            case 1:
                                                cout << "Poder Mágico que permite a todos los enanos recuperar su salud y\n";
                                                cout << "hacer que aumente su salud en 100 y su fortaleza en 1000 \n";
                                                id = ObtenerEntero("ID: ");
                                                lista_equipo.agregar_a_Mochila_conid(Implemento("Poder Magico de Enanos", "Poder mágico", "---", 1, 1, 1), id);
                                                break;
                                            case 2:
                                                cout << "Poder Mágico que traslada a todos los orcos del combate \n";
                                                cout << "a otra sala indicada por el usuario\n";
                                                id = ObtenerEntero("ID: ");
                                                lista_equipo.agregar_a_Mochila_conid(Implemento("Poder Magico Translador de Salas", "Poder mágico", "---", 1, 1, 1), id);
                                                break;
                                            case 3:
                                                cout << "Poder MÁgigo que hace que todos los orcos de una sala tengan 1 de salud\n";
                                                id = ObtenerEntero("ID: ");
                                                lista_equipo.agregar_a_Mochila_conid(Implemento("Poder Magico contra los orcos", "Poder mágico", "---", 1, 1, 1), id);
                                                //
                                                break;
                                            case 4:
                                                cout << "Poder MÁgico que hace que todo ataque de un implemento se duplique\n";
                                                cout << "y la fortaleza para usarlo se reduzca a 0\n";
                                                id = ObtenerEntero("ID: ");
                                                lista_equipo.agregar_a_Mochila_conid(Implemento("Duplicador de ataque de implemento", "Poder mágico", "---", 1, 1, 1), id);
                                                break;
                                            case 5:
                                                cout << "Regresando...\n";
                                                break;
                                            default:
                                                cout << "Numero ingresado invalido. Intente de nuevo \n\n";
                                        }
                                    } while (opcion_poder_magico != 5);
                                    break;
                                case 4: {
                                    cout << "¿A cuál heroe quiere eliminarle un implemento de su mochila?\n";
                                    lista_equipo.mostrarMochilas();
                                    int id_elim;
                                    Especie* actual = lista_equipo.cabeza;
                                    id_elim = ObtenerEntero("ID: ");
                                    while (actual != nullptr)
                                    {
                                        if (actual->id == id_elim)
                                        {
                                            actual->mochila.eliminarImplemento();
                                            break;
                                        }
                                        actual = actual->siguiente;
                                    }
                                    cout << "No se editó ningún implemento \n";
                                    break;
                                    }
                                case 5:{
                                    cout << "¿A cuál heroe quiere editarle un implemento de su mochila?\n";
                                    lista_equipo.mostrarMochilas();
                                    int id_elim;
                                    id_elim = ObtenerEntero("ID: ");
                                    Especie* actual = lista_equipo.cabeza;
                                    while (actual != nullptr)
                                    {
                                        if (actual->id == id_elim)
                                        {
                                            actual->mochila.editarImplemento();
                                            break;
                                        }
                                        actual = actual->siguiente;
                                    }
                                    cout << "No se editó ningún implemento \n";
                                    break;
                                    }
                                case 6:
                                    cout << "Regresando... \n";
                                    break;
                                default:
                                    cout << "Numero ingresado invalido. Intente de nuevo \n\n";
                            }
                        } while (opcion_mochila != 6);
                        break;
                    case 6:
                        cout << "Regresando...\n\n";
                        break;
                    default:
                        cout << "Numero ingresado invalido. Intente de nuevo \n\n";
                    }
                } while (opcion_equipo != 6);
                break;
        
            case 2:
                int opcion_especies;
                do
                {
                    cout << "╔══════════════════════════════════════════╗\n";
                    cout << "║    ¿Que desea hacer con las especies?    ║\n";
                    cout << "╠══════════════════════════════════════════╣\n";
                    cout << "║ 1. Observar                              ║\n";
                    cout << "║ 2. Crear                                 ║\n";
                    cout << "║ 3. Eliminar                              ║\n";
                    cout << "║ 4. Editar                                ║\n";
                    cout << "║ 5. Regresar                              ║\n";
                    cout << "╚══════════════════════════════════════════╝\n";
                    opcion_especies = ObtenerEntero("Opcion: ");
                    switch (opcion_especies)
                    {
                        case 1:
                            lista_heroes.mostrarEspecies();
                            break;
                        case 2:
                            lista_heroes.agregarNuevo_Heroe();
                            break;
                        case 3:
                            lista_heroes.eliminarEspecie();
                            break;
                        case 4:
                            lista_heroes.EditarHeroe();
                            break;
                        case 5:
                            cout << "Regresando...\n\n";
                            break;
                        default:
                            cout << "Numero ingresado invalido. Intente de nuevo\n\n";
                    }
                } while (opcion_especies != 5);
                break;

            case 3:
                int opcion_implementos;
                do
                {
                    cout << "╔══════════════════════════════════════════╗\n";
                    cout << "║  ¿Que desea hacer con los implementos?   ║\n";
                    cout << "╠══════════════════════════════════════════╣\n";
                    cout << "║ 1. Observar                              ║\n";
                    cout << "║ 2. Crear                                 ║\n";
                    cout << "║ 3. Eliminar                              ║\n";
                    cout << "║ 4. Editar                                ║\n";
                    cout << "║ 5. Regresar                              ║\n";
                    cout << "╚══════════════════════════════════════════╝\n";
                    opcion_implementos = ObtenerEntero("Opcion: ");
                    switch (opcion_implementos)
                    {
                        case 1:
                            cout << "Lista de implementos (cantidad: " << lista_implementos.cantidad << ")\n";
                            lista_implementos.mostrarImplementos();
                            break;
                        case 2:
                            lista_implementos.nuevoImplemento();
                            break;
                        case 3:
                            lista_implementos.eliminarImplemento();
                            break;
                        case 4:
                            lista_implementos.editarImplemento();
                            break;
                        case 5:
                            cout << "Regresando...\n\n";
                            break;
                        default:
                            cout << "Numero ingresado invalido. Intente de nuevo\n\n";
                    }
                } while (opcion_implementos != 5);
                break;

            case 4:
                cout << "Regresando al menu... \n\n";
                break;
                
            default:
                cout << "Numero ingresado invalido. Intente de nuevo\n\n";
        }
    } while (opcion != 4);
}

// Lista de orcos disponibles y horda en sala
class Lista_Orcos
{
    public:
    Especie* cabeza = nullptr;
    int cantidad = 0;
    ~Lista_Orcos()
    {
        Especie* actual = cabeza;
        while(actual != nullptr)
        {
            Especie* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
        cabeza = nullptr;
    }

    // CRUD DE ORCOS

    void agregarOrco(string n, string tip, int vid, int vel, int dano)
    {
        Especie* nuevo = new Especie(n, tip, vid, vel, dano);
        nuevo->id = ID_PERSONAJES+1;
        if(cabeza == nullptr)
        {
            cabeza = nuevo;
        }
        else
        {
            Especie* actual = cabeza;
            while(actual->siguiente != nullptr)
            {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
            nuevo->anterior = actual;
        }
        cantidad++;
        ID_PERSONAJES++;
    } 

    void agregarNuevo_Orco()
    {
        string nombre, tipo;
        int vida, fortaleza, velocidad, dano;
        nombre = ObtenerTexto("Ingrese el nombre del nuevo orco: ");
        vida = ObtenerEntero("Ingrese la vida del orco: ");
        velocidad = ObtenerEntero("Ingrese la velocidad del orco: ");
        dano = ObtenerEntero("Ingrese el daño del orco: ");
        tipo = ObtenerTexto("Ingrese la especie del orco: ");
        agregarOrco(nombre, tipo, vida, velocidad, dano);
        cout << "Orco llamado <" << nombre << "> del tipo "<< tipo << " fue creado con exito";
        cout << endl;
    }

    void mostrarOrcos() 
    {
        if (cantidad == 0) 
        {
            cout << "\nNo hay orcos en la lista.\n";
        }
        else
        {
            Especie* actual = cabeza;
            cout << "\nLista de orcos (cantidad: " << cantidad << ")";
            int i = 1;
            while (actual != nullptr) 
            {
                cout << "\nID: " << actual->id << ", ";
                cout << "Nombre: <" << actual->nombre << ">, ";
                cout << "Tipo: " << actual->tipo << ", ";
                cout << "Daño: " << actual->dano << ", ";
                cout << "Vida: " << actual->vida << ", ";
                cout << "Velocidad: " << actual->velocidad;
                actual = actual->siguiente;
                i++;
            }
            cout << "\n\n";
        }
    }

    void EliminarOrco()
    {
        mostrarOrcos();
        int numero;
        numero = ObtenerEntero("Ingrese 0 para no eliminar ninguno. \nIngrese el ID del orco a eliminar: ");
        if (cantidad == 0) 
        {
            cout << "No hay orcos en la lista.\n";
        }
        else
        {
            Especie* actual = cabeza;
            Especie* eliminar;
            while (actual != nullptr) 
            {
                if (numero == cabeza->id)
                {
                    eliminar = cabeza;
                    cabeza = cabeza->siguiente;
                    actual->siguiente->anterior = nullptr;
                    cout << "<"<< eliminar->nombre << "> eliminado correctamente.\n";
                    delete eliminar;
                    return;
                }
                else if (actual->id == numero)
                {
                    eliminar = actual;
                    actual->anterior->siguiente = actual->siguiente;
                    if (actual->siguiente != nullptr)
                    {
                        actual->siguiente->anterior = actual->anterior;
                    }
                    cout << "<"<< eliminar->nombre << "> eliminado correctamente.\n\n";
                    delete eliminar;
                    return;
                }
                actual = actual->siguiente;
            }
            if (numero != 0)
            {
                cout << "\nNo se encontró al orco con el ID indicado.\n";
            }
            else
            {
                cout << "No se eliminó ninguna especie.\n";
            }
            
        }
    }
    
    void EditarOrco()
    {
        mostrarOrcos();
        int numero;
        numero = ObtenerEntero("Ingrese 0 para no editar ninguno. \nIngrese el ID del orco a editar: ");
        Especie* actual = cabeza;
        while (actual != nullptr) 
        {
            if (actual->id == numero) 
            {
                actual->nombre = ObtenerTexto("Ingrese el nombre del orco");
                actual->dano = ObtenerEntero("Ingrese la dano del orco: ");
                actual->vida = ObtenerEntero("Ingrese la vida del orco: ");
                actual->velocidad = ObtenerEntero("Ingrese la velocidad del orco: ");
                actual->tipo = ObtenerTexto("Ingrese el tipo de especie del orco: ");
                cout << "\nEl orco <" << actual->nombre << "> ha sido actualizado. \n\n";
                return;
            }
            actual = actual->siguiente;
        }
        if (numero != 0)
        {
            cout << "\nNo se encontró al orco con el ID indicado.\n";
        }
        else
        {
            cout << "No se editó ninguna especie.\n";
        }
    }
    
    void agregarOrco(Especie nuevo_orco)
    {
        if (nuevo_orco.id != 0)
        {
            string nombre = nuevo_orco.nombre; string tipo = nuevo_orco.tipo; int vida = nuevo_orco.vida; 
            int dano = nuevo_orco.dano; int velocidad = nuevo_orco.velocidad;
            Especie* nuevo = new Especie(nombre, tipo, dano, vida, velocidad);
            nuevo->id = nuevo_orco.id;
            if(cabeza == nullptr)
            {
                cabeza = nuevo;
            }
            else
            {
                Especie* actual = cabeza;
                while(actual->siguiente != nullptr)
                {
                    actual = actual->siguiente;
                }
                actual->siguiente = nuevo;
                nuevo->anterior = actual;
            }
            cantidad++;
            ID_PERSONAJES++;
        }
    } 
    
    void orcosPredeterminados()
    {
        agregarOrco("Grishnakh", "Orco",          100, 100, 100 );
        agregarOrco("Uglúk",     "Araña Gigante", 150, 110, 120 );
        agregarOrco("Drácula",   "Ladrón",        150, 110, 120 );
        agregarOrco("Fenrin",    "Gólem",         180, 150, 40  );
        agregarOrco("Nazgul",    "Dragón",        220, 80 , 50  );
        agregarOrco("Boss",      "Orco",          320, 220 ,400 );
    }

    void orcosPrueba()
    {
        agregarOrco("Grishnakh", "Orco",          100, 100, 100 );
        agregarOrco("Uglúk",     "Araña Gigante", 150, 110, 120 );
    }

    void MuereOrco(int numero)
    {
        if (cantidad == 0) 
        {
            cout << "No hay orcos en la lista.\n";
        }
        else
        {
            Especie* actual = cabeza;
            Especie* eliminar;
            while (actual != nullptr) 
            {
                if (numero == cabeza->id)
                {
                    eliminar = cabeza;
                    cabeza = cabeza->siguiente;
                    actual->siguiente->anterior = nullptr;
                    cout << RED << "<"<< eliminar->nombre << "> ha muerto. \n" << RESET;
                    delete eliminar;
                    return;
                }
                else if (actual->id == numero)
                {
                    eliminar = actual;
                    actual->anterior->siguiente = actual->siguiente;
                    if (actual->siguiente != nullptr)
                    {
                        actual->siguiente->anterior = actual->anterior;
                    }
                    cout << RED << "<"<< eliminar->nombre << "> ha muerto.\n\n" << RESET;
                    delete eliminar;
                    return;
                }
                actual = actual->siguiente;
            }
            if (numero != 0)
            {
                cout << "\nNo se encontró al orco con el ID indicado.\n";
            }
            else
            {
                cout << "No se eliminó ninguna especie.\n";
            }
        }
    }

    Especie RetornarOrco(int id_agg)
    {
        Especie* actual = cabeza;
        while (actual != nullptr) 
        {
            if (actual->id == id_agg) 
            {
                Especie nuevo = *actual;
                nuevo.siguiente = nullptr;
                nuevo.anterior = nullptr;
                //cout << "El orco <" << nuevo.nombre << "> ha sido agregado a la sala\n";
                return nuevo;
            }
            actual = actual->siguiente;
        }
        // Si no se encontró el héroe, retornar un Especie por defecto
        if (id_agg != 0)
        {
            cout << "\nNo se encontró al héroe con el ID indicado.\n";
        }
        else
        {   
            cout << "No se agregó ninguna especie.\n";
        }
        return Especie("", "", 0, 0, 0, 0);
    }
};

// Se crea la lista enlazada
Lista_Orcos lista_orcos;

// Menu para orcos
void MenuOrcos()
{
    cout << endl;
    int opcion_especies;
    do
    {
        cout << "╔══════════════════════════════════════════╗\n";
        cout << "║     ¿Que desea hacer con los orcos?      ║\n";
        cout << "╠══════════════════════════════════════════╣\n";
        cout << "║ 1. Observar                              ║\n";
        cout << "║ 2. Agregar                               ║\n";
        cout << "║ 3. Eliminar                              ║\n";
        cout << "║ 4. Editar                                ║\n";
        cout << "║ 5. Regresar                              ║\n";
        cout << "╚══════════════════════════════════════════╝\n";
        opcion_especies = ObtenerEntero("Opcion: ");
        switch (opcion_especies)
        {
            case 1:
                lista_orcos.mostrarOrcos();
                break;
            case 2:
                lista_orcos.agregarNuevo_Orco();
                break;
            case 3:
                lista_orcos.EliminarOrco();
                break;
            case 4:
                lista_orcos.EditarOrco();
                break;
            case 5:
                cout << "Regresando...";
                break;
            default:
                cout << "Numero ingresado invalido. Intente de nuevo\n";
        }
    } while (opcion_especies != 5);
}
void MenuMapas();
void cargarEspecies(); //Definida antes para usarla abajo
//// Función de menú principal ////

class Sala
{
    public:
        int id;
        string nombre;
        bool HayPuerta;
        Lista_Orcos horda; // Agregado para que cada sala tenga una lista de orcos

        Sala(int _id, const string& _nombre) : id(_id), nombre(_nombre), HayPuerta(false) {}
        Sala() : id(0), nombre(""), HayPuerta(false) {}
};

class Arista
{
    public:
        int sala_destino;
        int distancia;
};
int orcos_restantes(Lista_Orcos &horda);

class Grafo
{
    private:
        unordered_map< int, list< Sala > > salas;
        unordered_map< int, list< Arista > > adj;
        bool dirigido;
    public:

        Grafo(bool esdirigido = 0) : dirigido(esdirigido) {}
        
        bool HaySalas()
        {
            if(salas.empty())
            {
                return false;
            }
            return true;
        }

        list<Arista>* RetornarAdyacencias(int ID)
        {
            return &adj[ID];
        }
        
        list<Sala>* RetornarSala(int ID)
        {
            return &salas[ID];
        }

        int ContarSalas()
        {
            int cont = 0;
            for(auto i : salas)
            {
                if(i.second.front().id)
                {
                    cont++;
                }
            }
            return cont;
        }

        void SeleccionarSalaPuerta()
        {
            if(salas.empty())
            {
                return;
            }
            int numero_salas = ContarSalas();
            vector <int> ids;
            for(auto i : salas)
            {
                ids.push_back(i.second.front().id);
                int id_aleatorio = numeroAleatorio(0, ids.size() - 1);
                salas[ids[id_aleatorio]].front().HayPuerta = true;
            }
        }

        void ImprimirSalas()
        {
            if(salas.empty())
            {
                cout << "No hay salas existentes." << endl;
                cout << endl;
                return;
            }
            for(auto i : salas)
            {
                int id = i.first;
                cout << "Sala ID: " << id << endl;
                cout << "Nombre: " << i.second.front().nombre << endl;
                cout << "<<<<<<<<<Conexiones>>>>>>>>> " << endl;
                if(adj[id].empty())
                {
                    cout << "No hay conexiones.\n\n";
                }
                else
                {
                    for(Arista& arista : adj[id])
                    {
                        cout << "Sala destino: " << arista.sala_destino;
                        cout << " Distancia: " << arista.distancia;
                        cout << endl;
                    }
                    cout << endl;
                }
            }
        }

        void AgregarSala(int id, string nombre)
        {
            while(salas.find(id) != salas.end())
            {
                cout << "Ya existe una sala con ese id. Intente nuevamente.\n";
                return;
                //id = ObtenerEntero("Ingrese el ID de la sala a agregar (0 para terminar): ");
                //nombre = ObtenerTexto("Ingrese el nombre de la sala a agregar: ");
            }
            salas[id].push_back(Sala(id, nombre));
            cout << endl;
        }

        void ConectarSala(int id)
        {
            if(salas.empty())
            {
                cout << "No hay salas existentes. No se puede conectar.\n\n";
                return;
            }
            if(salas.find(id) == salas.end())
            {
                cout << "Sala ID: " << id << " no existe. No se puede conectar.\n\n";
                return;
            }
            int destino, distancia;
            cout << "Conectando sala ID: " << id << endl;
            if (adj.find(id) == adj.end()) {
                adj[id] = list<Arista>();
            }
            while (true) 
            {
                destino = ObtenerEntero("Ingrese ID de la sala destino (0 para terminar): ");
                if (salas.find(destino) == salas.end() && destino != 0) {
                    cout << "Sala destino no existe. Intente de nuevo." << endl;
                    destino = ObtenerEntero("Ingrese ID de la sala destino (0 para terminar): ");
                }
                if (destino == 0) break; // Terminar entrada
                distancia = ObtenerEntero("Ingrese la distancia a la sala destino: ");
                if (distancia <= 0) {
                    cout << "La distancia debe ser un número positivo. Intente de nuevo." << endl;
                    continue;
                }
                AgregarArista(id, destino, distancia);
                break;
            }
            cout << "Conexiones para la sala ID: " << id << " han sido agregadas.\n\n";
        }

        void AgregarArista(int origen, int destino, int distancia)
        {
            adj[origen].push_back({destino, distancia});
            if(dirigido)
            {
                adj[destino].push_back({origen, distancia});
            }
        }

        void EliminarSala()
        {
            if(salas.empty())
            {
                cout << "No hay salas existentes.\n\n";
                return;
            }

            int id;
            ImprimirSalas();
            id = ObtenerEntero("Ingresa ID de la sala a eliminar: ");
            if(salas.find(id) != salas.end())
            {
                // Eliminar conexiones asociadas a la sala
                for(auto& i : adj)
                {
                    i.second.remove_if([id](const Arista& arista)
                    {
                        return arista.sala_destino == id;
                    });
                }
                salas.erase(id);
                adj.erase(id);
                cout << "Sala ID: " << id << " eliminada exitosamente.\n";
            }
            else
            {
                cout << "Sala ID: " << id << " no encontrada.\n";
            }
        }

        void MostrarSalas()
        {
            cout << endl;
            cout << "Salas: \n";
            for(auto i : salas)
            {
                cout << "ID Sala: " << i.second.front().id << endl;
                cout << "Nombre: " << i.second.front().nombre << endl;
            }
            cout << endl;
        }
        void EditarSala()
        {
            if(salas.empty())
            {
                cout << "No hay salas existentes.\n\n";
                return;
            }

            cout << endl;
            int id;
            string nuevo_nombre;
            cout<< "Que desea editar de la sala?\n"
                << "1. ID \n"
                << "2. Nombre \n"
                << "3. Conexiones \n"
                << "4. Todo \n"
                << "5. Regresar\n";
            int opcion = ObtenerEntero("Ingrese una opcion: ");
            switch(opcion)
            {
                case 1:
                    MostrarSalas();
                    id = ObtenerEntero("Ingrese el ID de la sala a editar: ");
                    if(salas.find(id) != salas.end())
                    {
                        int nuevo_id = ObtenerEntero("Ingrese el nuevo ID de la sala: ");
                        while(salas.find(nuevo_id) != salas.end())
                        {
                            cout << "Ya existe una sala con ese ID. Intente nuevamente.\n";
                            nuevo_id = ObtenerEntero("Ingrese el nuevo ID de la sala: ");
                        }
                        salas[nuevo_id] = salas[id];
                        salas[nuevo_id].front().id = nuevo_id;
                        salas.erase(id);
                        cout << "ID de la sala actualizado exitosamente.\n\n";
                    }
                    else
                    {
                        cout << "Sala ID: " << id << " no encontrada.\n";
                    }
                    break;
                case 2:
                    MostrarSalas();
                    id = ObtenerEntero("Ingrese el ID de la sala a editar: ");
                    if(salas.find(id) != salas.end())
                    {
                        nuevo_nombre = ObtenerTexto("Ingrese el nuevo nombre de la sala: ");
                        salas[id].front().nombre = nuevo_nombre;
                        cout << "Nombre de la sala actualizado exitosamente.\n";
                    }
                    else
                    {
                        cout << "Sala ID: " << id << " no encontrada.\n";
                    }
                    break;
                case 3:
                    ConectarSala(id);
                    break;
                case 4:
                    cout << endl;
                    ImprimirSalas();
                    id = ObtenerEntero("Ingrese el ID de la sala a editar: ");
                    if(salas.find(id) != salas.end())
                    {
                        nuevo_nombre = ObtenerTexto("Ingrese el nuevo nombre de la sala: ");
                        salas[id].front().nombre = nuevo_nombre;
                        ConectarSala(id);
                        cout << "Sala actualizada exitosamente.\n";
                    }
                    else
                    {
                        cout << "Sala ID: " << id << " no encontrada.\n";
                    }
                    break;
                case 5:
                    cout << "Regresando al menu de mapas...\n\n";
                    return;
                default:
                    cout << "Opción inválida. Intente nuevamente.\n";
                    return;   
            } while(opcion != 5);
            cout << endl;
        }

        void BFS(int nodo)
        {
            unordered_map<int, bool> visitados;
            queue<int> visita;
            visitados[nodo] = true;
            visita.push(nodo);

            while(!visita.empty())
            {
                int actual = visita.front();
                visita.pop();

                cout << "ID de la Sala: " << actual << endl;
                cout << "Nombre: " << salas[actual].front().nombre << endl;
                cout << "Conexiones: " << endl;
                for(const auto& arista : adj[actual])
                {
                    cout << "Sala Destino: " << arista.sala_destino << " Distancia: " << arista.distancia << endl;
                    if (!visitados[arista.sala_destino])
                    {
                        visita.push(arista.sala_destino);
                        visitados[arista.sala_destino] = true;
                    }
                }
                cout << endl;
            }
        }

        void cargarDesdeArchivo(const string& nombre_archivo)
        {
            int cont = 0;
            ifstream archivo(nombre_archivo);
            if (!archivo.is_open()) 
            {
                cout << "No se pudo abrir el archivo: " << nombre_archivo << endl;
                return;
            }

            salas.clear();
            adj.clear();

            string linea;
            int num_salas = 0;
            // Leer número de salas (primera línea no vacía)
            while (getline(archivo, linea)) 
            {
                if (!linea.empty() && linea.find_first_not_of(" \t\r\n") != string::npos) 
                {
                    try {
                        num_salas = stoi(linea);
                    } catch (...) {
                        cout << "Error al leer el número de salas: " << linea << endl;
                        archivo.close();
                        return;
                    }
                    break;
                }
            }

            for (int sala_idx = 0; sala_idx < num_salas; sala_idx++) {
                // Buscar delimitador de sala "---"
                bool found = false;
                while (getline(archivo, linea)) 
                {
                    if (linea.find("---") == 0) {
                        found = true;
                        break;
                    }
                }
                if (!found) break; // No hay más bloques de sala

                // Leer ID (saltando líneas vacías)
                do {
                    if (!getline(archivo, linea)) { sala_idx = num_salas; break; }
                } while (linea.empty() || linea.find_first_not_of(" \t\r\n") == string::npos);
                if (archivo.eof()) break;
                int id = -1;
                try {
                    id = stoi(linea);
                } catch (...) {
                    cout << "ID de sala inválido: '" << linea << "'" << endl;
                    continue;
                }

                // Leer nombre (saltando líneas vacías)
                do {
                    if (!getline(archivo, linea)) { sala_idx = num_salas; break; }
                } while (linea.empty() || linea.find_first_not_of(" \t\r\n") == string::npos);
                if (archivo.eof()) break;
                string nombre = linea;

                // Leer delimitador de conexiones "--" (saltando líneas vacías)
                do {
                    if (!getline(archivo, linea)) { sala_idx = num_salas; break; }
                } while (linea.empty() || linea.find_first_not_of(" \t\r\n") == string::npos);
                if (archivo.eof()) break;
                if (linea.find("--") != 0) {
                    cout << "Formato inválido, se esperaba '--' después del nombre de la sala (ID: " << id << ")\n";
                    continue;
                }

                // Leer conexiones (puede estar vacía)
                string conexiones_linea;
                if (!getline(archivo, conexiones_linea)) break;
                // Formato: 2:5|3:7|4:10|5:3
                vector<Arista> conexiones;
                if (!conexiones_linea.empty() && conexiones_linea.find_first_not_of(" \t\r\n") != string::npos) {
                    stringstream ss(conexiones_linea);
                    string token;
                    while (getline(ss, token, '|')) {
                        size_t pos = token.find(':');
                        if (pos != string::npos) {
                            try {
                                int destino = stoi(token.substr(0, pos));
                                int distancia = stoi(token.substr(pos + 1));
                                conexiones.push_back({destino, distancia});
                            } catch (...) {
                                cout << "Advertencia: conexión inválida '" << token << "' en sala " << id << endl;
                            }
                        }
                    }
                }

                // Agregar sala y conexiones
                AgregarSala(id, nombre);
                cont++;
                for (const auto& arista : conexiones) 
                {
                    AgregarArista(id, arista.sala_destino, arista.distancia);
                }
            }
            archivo.close();
            cout << "Archivo cargado correctamente.\n\n";
            cout << "Se han cargado " << cont << " salas.\n\n";
        }

        void Dijkstra(int nodo)
        {
            queue<int> salas_no_visitadas;
            vector<int> distancias;
            // Marcar al primer nodo
            salas_no_visitadas.push(nodo);
            distancias.push_back(MIN);
            for(auto i : salas)
            {
                if(i.second.front().id != nodo)
                {
                    salas_no_visitadas.push(i.second.front().id);
                }
            }
            
            while(!salas_no_visitadas.empty())
            {
                for(auto& par : adj[salas_no_visitadas.front()])
                {
                    cout << par.sala_destino << ", ";
                    salas_no_visitadas.pop();
                }
            }
        }

        int RetornarSalaLejana(int sala)
        {
            // Encuentra la sala más lejana usando BFS (o Dijkstra si implementado)
            unordered_map<int, int> distancias;
            unordered_map<int, bool> visitados;
            queue<pair<int, int>> cola;
            cola.push({sala, 0});
            distancias[sala] = 0;
            visitados[sala] = true;
            int max_dist = 0;
            int sala_lejana = sala;
            while (!cola.empty()) {
                int actual = cola.front().first;
                int distancia_actual = cola.front().second;
                cola.pop();
                if (distancia_actual > max_dist) {
                    max_dist = distancia_actual;
                    sala_lejana = actual;
                }
                for (const auto& arista : adj[actual]) {
                    int vecino = arista.sala_destino;
                    if (!visitados[vecino]) {
                        visitados[vecino] = true;
                        distancias[vecino] = distancia_actual + arista.distancia;
                        cola.push({vecino, distancias[vecino]});
                    }
                }
            }
            return sala_lejana;
        }

        void MostrarAdyacencias(int id)
        {
            list<Sala> *sala;
            for(auto i : adj[id])
            {
                sala = RetornarSala(i.sala_destino);
                cout << "ID: "<< sala->front().id << "\t|\t Sala: " << sala->front().nombre << "   " << "\t|\tDistancia: " << i.distancia << " \t|Orcos: ";
                if (sala->front().horda.cabeza == nullptr)
                {
                    cout << " No\n";
                }
                else
                {
                    cout << " Si (" << orcos_restantes(sala->front().horda) << ") \n";
                }
            }
        }

        int MoveraAdyacencia(int id)
        {
            int distancia;
            int id_sala_a_mover = ObtenerEntero("Ingrese el id de la sala destino: ");
            for(auto i : adj[id])
            {
                if(id_sala_a_mover == i.sala_destino)
                {
                    return i.sala_destino;
                }
            }
            return -1;
        }

        int RetornarDistanciaAdyacencia(int id1, int id2)
        {
            for(auto i : adj[id1])
            {
                if(i.sala_destino == id2)
                {
                    return i.distancia;
                }
            }
            return 0;   
        }

        int RetornarMenorDistancia(int id1, int id2)
        {
            int sala_actual = id1;
            int sala_destino = id2;
            int sum = 0;
            unordered_map <int, bool> visitados;
            unordered_map <int, int> dist_max;
            queue <pair <int, int> > cola;

            for(auto i : salas)
            {
                dist_max[i.first] = INT_MAX;
            }

            cola.push({sala_actual, 0});
            dist_max[sala_actual] = 0;
            while(!cola.empty())
            {
                int actual = cola.front().first;
                int distancia_actual = cola.front().second;
                if(visitados[actual]) continue;
                visitados[actual] = true;
                cola.pop();
                for(auto i : adj[actual])
                {
                    int vecino = i.sala_destino;
                    int nueva_distancia = distancia_actual + i.distancia;
                    if(nueva_distancia < dist_max[vecino])
                    {
                        dist_max[vecino] = nueva_distancia;
                        cola.push({i.sala_destino, nueva_distancia});
                    }
                }
            }
            for(auto i : dist_max)
            {
                if(i.first == sala_destino)
                {
                    return i.second;
                }
            }
            return -1; 
        }

        void BFSOrcos(int nodo)
        {
            unordered_map<int, bool> visiteradorados;
            queue<int> cola;
            visiteradorados[nodo] = true;
            cola.push(nodo);
            int orcos_a_repartir = 20;
            
            while(!cola.empty() && orcos_a_repartir > 0)
            {
                int actual = cola.front();
                int orcos_en_sala = 5;
                cola.pop();
                
                for(auto& adyacente : adj[actual])
                {
                    if(visiteradorados[adyacente.sala_destino]) continue;
                    
                    list<Sala>* adyacente_orcos = &salas[adyacente.sala_destino];
                    if(!adyacente_orcos || adyacente_orcos->empty()) continue;
                    
                    Sala& sala_destino = adyacente_orcos->front();
                    
                    if(sala_destino.horda.cantidad >= 5) continue;
                    
                    for(int i = 0; i < orcos_en_sala; ++i)
                    {
                        Especie temp = lista_orcos.RetornarOrco(numeroAleatorio(7,11));
                        Especie* nuevo = new Especie(temp);
                        
                        if(sala_destino.horda.cabeza == nullptr)
                        {
                            sala_destino.horda.cabeza = nuevo;
                        }
                        else
                        {
                            Especie* actual = sala_destino.horda.cabeza;
                            while(actual->siguiente != nullptr)
                            {
                                actual = actual->siguiente;
                            }
                            actual->siguiente = nuevo;
                            nuevo->anterior = actual;
                        }
                        sala_destino.horda.cantidad++;
                    }
                    orcos_a_repartir -= orcos_en_sala;
                    visiteradorados[adyacente.sala_destino] = true;
                    cola.push(adyacente.sala_destino);
                    
                    if(orcos_a_repartir <= 0) break;
                }
            }
        }
};

Grafo mapa;

void MenuMapas()
{
    int opcion;
    do
    {
        cout << "╔══════════════════════════════════════════╗\n";
        cout << "║                Menu Mapas                ║\n";
        cout << "╠══════════════════════════════════════════╣\n";
        cout << "║ 1. Ver salas                             ║\n";
        cout << "║ 2. Agregar sala                          ║\n";
        cout << "║ 3. Eliminar sala                         ║\n";
        cout << "║ 4. Editar sala                           ║\n";
        cout << "║ 5. Cargar desde archivo                  ║\n";
        cout << "║ 6. Regresar                              ║\n";
        cout << "╚══════════════════════════════════════════╝\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        int id;
        string nombre_sala;
        string nombre_archivo;
        switch (opcion)
        {
            case 1:
                mapa.ImprimirSalas();
                break;
            case 2:
                cout << "Ingresa ID: " ; cin >> id;
                cout << "Ingresa nombre de la sala: " ; cin >> nombre_sala;                
                mapa.AgregarSala(id, nombre_sala); // Agregar sala
                mapa.ConectarSala(id);             // Conectar sala
                break;
            case 3:
                mapa.EliminarSala();
                break;
            case 4:
                mapa.EditarSala();
                break;
            case 5:
                {
                    cout << "Ingrese el nombre del archivo: ";
                    cin >> nombre_archivo;
                    mapa.cargarDesdeArchivo(nombre_archivo);
                }
                break;
            case 6:
                cout << "Regresando al menu principal...\n";
                break;
            default:
                cout << "Numero ingresado invalido. Intente de nuevo\n\n";
        }
    } while (opcion != 6);
}

////// Archivos /////////

struct Especies
{
    int id;
    string tipo;
    int fortaleza; 
    int dano;
    int salud;
    int rapidez;
    Especies* siguiente = nullptr;
};

class EspeciesPredeterminadas
{
    public:
        Especies* cabeza;
        EspeciesPredeterminadas() : cabeza(nullptr) {}
        ~EspeciesPredeterminadas() //Destructor
        { 
            Especies* actual = cabeza;
            while (actual != nullptr) 
            {
                Especies* temp = actual;
                actual = actual->siguiente;
                delete temp;
            }
        }

        void agregarHeroe(int id, string tip, int fort, int dan, int vid, int vel) 
        {
            Especies* nuevo = new Especies();
            nuevo->id = id;
            nuevo->tipo = tip;
            nuevo->fortaleza = fort;
            nuevo->dano = dan;
            nuevo->salud = vid;
            nuevo->rapidez = vel;
            nuevo->siguiente = nullptr;
            if (cabeza == nullptr)
            {
                cabeza = nuevo;
            }
            else
            {
                Especies* actual = cabeza;
                while (actual->siguiente != nullptr)
                {
                    actual = actual->siguiente;
                }
                actual->siguiente = nuevo; 
            }
        }

        void mostrar()
        {
            if (cabeza == nullptr){cout << "Lista vacía\n"; return;}
            Especies* actual = cabeza;
            while (actual != nullptr)
            {
                cout << "#ID: " << actual->id;
                cout << ", tipo: " << actual->tipo;
                cout << ", fortaleza: " << actual->fortaleza;
                cout << ", daño: " << actual->dano;
                cout << ", salud: " << actual->salud;
                cout << ", rapidez: " << actual->rapidez << endl;                
                actual = actual->siguiente; 
            }
        }

        Especie buscarEspecie(string tip, string nomb, int id)
        {
            Especies* nuevo = new Especies();
            if (cabeza == nullptr)
            {
                cout << "No hay heroes en la lista\n";
                return Especie("", "", 0, 0, 0, 0);
            }
            else
            {
                Especies* actual = cabeza;
                while (actual->siguiente != nullptr)
                {
                    if (actual->tipo == tip)
                    {
                        if (actual->fortaleza != 0)
                        {
                            Especie nuevo = Especie(nomb, tip, actual->fortaleza, actual->salud, actual->rapidez, id);
                            return nuevo;
                        }
                        else
                        {
                            Especie nuevo = Especie(nomb, tip, actual->dano, actual->salud, actual->rapidez);
                            nuevo.id = actual->id;
                            return nuevo;
                        }
                    }
                    actual = actual->siguiente;
                }
                return Especie("", "", 0, 0, 0, 0);
            }
        }
};
EspeciesPredeterminadas lista;

void cargarEspecies()
{
    int id, fort, dan, sal, rap, cantidad;
    string tipo, linea, nomb;
    ifstream archivo("C:\\Users\\yisut\\OneDrive\\Escritorio\\Dev-UCAB\\Estructura de datos UCAB\\Proyecto\\especie.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo especie.txt\n";
        return;
    }

    if (!getline(archivo, linea)) return;
    cantidad = stoi(linea);

    for (int contador = 1; contador <= cantidad; contador++)
    {
        do {
            if (!getline(archivo, linea)) return;
        } while (linea == "---");

        id = stoi(linea);

        if (!getline(archivo, tipo)) break;

        if (!getline(archivo, linea)) break;
        if (linea == "-")
        {
            fort = 0;
        }
        else
        {
            fort = stoi(linea);
        }

        if (!getline(archivo, linea)) break;
        if (linea == "-")
        {
            dan = 0;
        }
        else{
            dan = stoi(linea);
        }
        
        if (!getline(archivo, linea)) break;
        sal = stoi(linea);

        if (!getline(archivo, linea)) break;
        rap = stoi(linea);

        lista.agregarHeroe(id, tipo, fort, dan, sal, rap);
        
    }
    
    string linea2;
    ifstream archivo2("C:\\Users\\yisut\\OneDrive\\Escritorio\\Dev-UCAB\\Estructura de datos UCAB\\Proyecto\\Personajes.txt");

    if (!archivo2.is_open()) {
        cout << "No se pudo abrir el archivo Personajes.txt\n";
        return;
    }

    if (!getline(archivo2, linea2)) return;
    cantidad = stoi(linea2);

    for (int contador = 1; contador <= cantidad; contador++)
    {
        do {
            if (!getline(archivo2, linea2)) return;
        } while (linea2 == "---");

        id = stoi(linea2);

        if (!getline(archivo2, tipo)) break;

        if (!getline(archivo2, nomb)) break;
        
        Especie nuevo = lista.buscarEspecie(tipo, nomb, id);
        if (nuevo.fortaleza != 0)
        {
            lista_heroes.agregarHeroe(nuevo);
        }
        else
        {
            lista_orcos.agregarOrco(nuevo);
        }
    }

    int req, val, uso;
    string linea3, cambio;

    ifstream archivo3("C:\\Users\\yisut\\OneDrive\\Escritorio\\Dev-UCAB\\Estructura de datos UCAB\\Proyecto\\implemento.txt");
    if (!archivo3.is_open()) {
        cout << "No se pudo abrir el archivo especie.txt\n";
        return;
    }

    if (!getline(archivo3, linea3)) return;
    cantidad = stoi(linea3);
    cout << cantidad << endl;
    for (int contador = 1; contador <= cantidad; contador++)
    {
        do {
            if (!getline(archivo3, linea3)) return;
        } while (linea3 == "---");

        id = stoi(linea3);

        if (!getline(archivo3, nomb)) break;

        if (!getline(archivo3, tipo)) break;

        if (tipo == "Arma")
        {
            cambio = "Ataque";
        }
        else if (tipo == "Escudo")
        {
            cambio = "Defensa"; 
        }
        else if (tipo == "Consumible")
        {
            cambio = "Vida"; 
        }

        if (!getline(archivo3, linea3)) break;
        req = stoi(linea3);

        if (!getline(archivo3, linea3)) break;
        val = stoi(linea3);
        if (!getline(archivo3, linea3)) break;
        uso = stoi(linea3);

        lista_implementos.agregarImplemento(nomb, tipo, cambio, uso, req, val);
        
    }
}

void menuPrincipal()
{
    cout << "\n---------------------------------" << endl;
    cout << "--> ¡Bienvenido a Khazad-Dum! <--" << endl;
    cout << "---------------------------------" << endl << endl;

    cout << "Desea usar los datos predeterminados (1) o cargar archivos(2)?\n";
    cout << "Nota: Asegúrese de tener los archivos en el mismo directorio del programa o la ruta exacta de cada uno\n";
    int opcion = ObtenerEntero("Opción: ");
    while (opcion != 1 && opcion != 2)
    {
        cout << "Número ingresado incorrecto, ingrese una opción válida (1 o 2)\n";
        int opcion = ObtenerEntero("Opción: ");
    }
    if (opcion == 1)
    {
        lista_heroes.heroesPredeterminados(); 
        lista_orcos.orcosPredeterminados();
        lista_heroes.agregarHeroe("Arwen", "Elfo", 80, 65, 90); 
        lista_implementos.implementosPredeterminados();
    }
    else
    {
        cargarEspecies();
    }
    mapa.cargarDesdeArchivo("C:\\Users\\yisut\\OneDrive\\Escritorio\\Dev-UCAB\\Estructura de datos UCAB\\Proyecto\\salas.txt");
    int opcion_main;
    do 
    {
        cout << LIGHT_BROWN;
        cout << "\n╔════════════════════════════╗\n";
        cout <<   "║        MENÚ PRINCIPAL      ║\n";
        cout <<   "╠════════════════════════════╣\n";
        cout <<   "║ 1. Iniciar Juego           ║\n";
        cout <<   "║ 2. Editar Heroes           ║\n";
        cout <<   "║ 3. Editar Orcos            ║\n";
        cout <<   "║ 4. Editar Mapa y Salas     ║\n";
        cout <<   "╚════════════════════════════╝\n";
        cout << RESET; 
        opcion_main = ObtenerEntero("Opcion: ");
        switch(opcion_main)
        {
            case 1:
                if (lista_equipo.cantidad != 4)
                {
                    cout << "No puede iniciar el juego. El equipo debe tener 4 heroes";
                    opcion_main = 5;
                    break;
                }
                else if (lista_equipo.suma_Mochilas() < lista_equipo.cantidad*5)
                {
                    cout<< "Parece que uno de sus heroes no tiene implementos en su mochila.\n" 
                        << "Está seguro de iniciar? (Si = 1 | No = 0)\n";
                    int opcion_inicio;
                    do
                    {
                        opcion_inicio = ObtenerEntero("Opcion: ");
                        if (opcion_inicio != 1 && opcion_inicio != 0)
                        {
                            cout << "Numero ingresado invalido. Intente de nuevo\n\n";
                        }
                    } while (opcion_inicio != 1 && opcion_inicio != 0);
                    if (opcion_inicio == 1)
                    {
                        break;
                    }
                    else 
                    {
                        opcion_main = 5;
                        break;
                    }
                }
                else
                {
                    cout << "Iniciando...\n\n";
                    break;
                }
            case 2:
                MenuHeroes();
                break;
            case 3:
                MenuOrcos();
                break;
            case 4:
                MenuMapas();
                break;
            case 5:
                break; //Volver al menu
            default:
                cout << "Numero ingresado invalido. Intente de nuevo\n\n";
        }
    } while (opcion_main != 1);
}


/////// Interfa de combate /////////////////
int atacar_heroe(Especie *heroe, Lista_Orcos &Orcos)
{
    int implemento;
    Implemento* actual_i = heroe->mochila.cabeza;
    cout << "\nIngrese el id del arma a utilizar. \nFortaleza actual: " << heroe->fortaleza << " \n\n";
    while (actual_i != nullptr)
    {
        if (actual_i->tipo == "Arma")
        {
            cout << "- ID: " << actual_i->ID << " " << actual_i->nombre << " (ataque: " << actual_i->valor << " | usos: " << actual_i->uso << " | fortaleza: " << actual_i->requisito << ") \n";
        }
        actual_i = actual_i->siguiente;
    }
    cout << "Ingrese 0 para no luchar (recuperar 10 por ciento de la fortaleza actual)\n";
    implemento = ObtenerEntero("\nOpción: ");
    if (implemento == 0)
    {
        cout << "El heroe ha descansado por esta ronda\n";
        heroe->fortaleza += heroe->fort_base/10;
        if (heroe->fortaleza > heroe->fort_base)
        {
            heroe->fortaleza -= heroe->fort_base - heroe->fortaleza;
        }
        return 1;
    }
    actual_i = heroe->mochila.cabeza;
    Implemento* arma = nullptr;
    while (actual_i != nullptr)
    {
        if (actual_i->ID == implemento)
        {
            arma = actual_i;
            break;
        }
        actual_i = actual_i->siguiente;
    }
    if (arma == nullptr)
    {
        cout << "El id ingresado no coincide con ninguna arma. Intente de nuevo. \n";
        return 0;
    }
    if (arma->uso == 0)
    {
        cout << "El arma llegó al límite de usos \n";
        return 0;
    }
    if (heroe->fortaleza < arma->requisito)
    {
        cout << "El heroe no cuenta con la fortaleza(" << heroe->fortaleza <<") necesaria para usar el arma("<< arma->requisito <<")\n";
        return 0;
    }
    int objetivo;
    cout << "\nIngrese el id del orco que quiera atacar:\n";
    Especie* actual_o = Orcos.cabeza;
    while (actual_o != nullptr)
    {
        cout << "- ID: " << actual_o->id << " " << actual_o->nombre << " (salud: " << actual_o->vida << ")  \n";
        actual_o = actual_o->siguiente;
    }
    objetivo = ObtenerEntero("\nObjetivo: ");
    actual_o = Orcos.cabeza;
    while (actual_o != nullptr)
    {
        if (actual_o->id == objetivo)
        {
            cout << endl << heroe->nombre << " ha atacado a " << actual_o->nombre << endl;
            cout << "La vida de <"<< actual_o->nombre <<"> ha sido reducida de " << actual_o->vida << " a ";
            actual_o->vida -= (arma->valor/4);
            if (actual_o->vida < 0)
            {
                actual_o->vida -= actual_o->vida;
            }
            cout << actual_o->vida << endl;
            arma->uso--;
            heroe->fortaleza -= heroe->fort_base/10;
            if (actual_o->vida == 0)
            {
                if (Orcos.cantidad > 1)
                {
                    Orcos.MuereOrco(actual_o->id);
                }
                Orcos.cantidad--;
            }
            if (arma->uso == 1)
            {
                cout << RED "¡Al arma <" << actual_i->nombre << "> le queda un uso! \n" RESET ;
                return 1;
            }
            else if (arma->uso == 0)
            {
                heroe->mochila.ultimoUso(actual_i->ID);
                return 1;
            }
            else
            {
                cout << "Al arma <" << actual_i->nombre << "> le quedan " << actual_i->uso << " usos\n" ;
                return 1;
            }
        }
        actual_o = actual_o->siguiente;
    }
    cout << "El id ingresado no coincide con ningún orco. Intente de nuevo. \n";
    return 0;
}
// 2DA OPCIÓN: Usar o ver implementos de la mochila
int Mochila_de(Especie *heroe, Lista_Orcos &horda)
{
    Implemento* actual = heroe->mochila.cabeza;
    int opcion;
    int i = 1;
    while (actual != nullptr)
    {
        if (actual->tipo != "Arma" && actual->tipo != "Defensa")
        {
            cout << "#" << i << " " << actual->nombre << " (usos: "<< actual->uso << " | valor: " << actual->valor << ") \n";
            i++;
        }
        actual = actual->siguiente; 
    } 
    cout << "#" << i << " Regresar\n";
    int j = 1;
    opcion = ObtenerEntero("\nIngrese opcion:");
    if (opcion == i)
    {
        cout << "Regresando... \n";
        return 0;
    }
    else
    {
        actual = heroe->mochila.cabeza;
        while (actual != nullptr)
        {
            if (opcion == j)
            {
                if (actual->tipo == "Consumible")
                {
                    Especie* actual2 = lista_equipo.cabeza;
                    cout << "\n¿A cual heroe quiere curar?\n";
                    while (actual2 != nullptr)
                    {
                        cout << "ID: "<< actual2->id << " <"<< actual2->nombre << "> (salud: " << actual2->vida << ")\n";
                        actual2 = actual2->siguiente;
                    }
                    cout << endl;
                    int opcion2 = ObtenerEntero("ID: ");
                    actual2 = lista_equipo.cabeza;
                    while (actual2 != nullptr)
                    {
                        if (opcion2 == actual2->id)
                        {
                            if (actual2->vida == actual2->vida_base)
                            {
                                cout << "\nEste heroe ya tiene la vida máxima\n\n";
                                return 0;
                            }
                            else if (actual2->vida == 0)
                            {
                                cout << "\nEste heroe está muerto, no se puede curar\n\n";
                                return 0;
                            }
                            else 
                            {
                                actual2->vida += actual->valor;
                                if (actual2->vida > actual2->vida_base)
                                {
                                    actual2->vida -= (actual2->vida-actual2->vida_base);
                                }
                                cout << "\nLa salud de <" << actual2->nombre << "> ha aumentado a " << actual2->vida << " (+" << actual->valor << ") \n\n";
                                actual->uso --;
                                if(actual->uso == 0)
                                {
                                    actual2->mochila.ultimoUso(actual->ID);
                                }
                                return 1;
                            }
                            
                        }
                        actual2 = actual2->siguiente;
                    }
                    cout << "\nEl ID ingresado no está en la lista\n\n";
                }
                else if (actual->tipo == "Poder magico")
                {
                    if (actual->nombre == "Poder Magico de Enanos")
                    {
                        Especie* &actual = lista_equipo.cabeza;
                        while (actual != nullptr)
                        {
                            if (actual->tipo == "Enano")
                            {
                                actual->vida += 100;
                                actual->vida_base += 100;
                                actual->fort_base += 1000;
                                actual->fortaleza += 1000;
                                cout << "La salud del enano <" << actual->nombre << "> ha aumentado +100\n";
                                cout << "La fortaleza del enano <" << actual->nombre << "> ha aumentado +1000\n";
                            }
                            actual = actual->siguiente;
                        }
                        return 1;
                    }
                    else if (actual->nombre == "Poder Magico Translador de Salas")
                    {
                        list<Sala>* sala_aleat = mapa.RetornarSala(numeroAleatorio(1,60));
                        Especie *actual = sala_aleat->front().horda.cabeza;
                        if (sala_aleat->front().horda.cabeza == nullptr)
                        {
                            sala_aleat->front().horda.cabeza = horda.cabeza;
                        }
                        else
                        {
                            while (actual->siguiente != nullptr)
                            {
                                actual = actual->siguiente;
                            }
                            actual->siguiente = horda.cabeza;

                        }
                        cout << "Todos los orcos se han movido a la sala: " << sala_aleat->front().nombre << endl;
                        return 2;
                    }
                    else if (actual->nombre == "Poder Magico contra los orcos")
                    {
                        Especie *actual = horda.cabeza;
                        while (actual != nullptr)
                        {
                            actual->vida = 1;
                            actual = actual->siguiente;
                        }
                        return 1;
                    }
                    else if (actual->nombre == "Duplicador de ataque de implemento")
                    {
                        Implemento* &actual_i2 = heroe->mochila.cabeza;
                        while (actual_i2 != nullptr)
                        {
                            if (actual_i2->tipo == "Arma")
                            {
                                actual_i2->valor *= 2;
                                actual_i2->requisito = 0;
                                cout << "El ataque de todas las armas del heroe <" << heroe->nombre << "> se ha duplicado \ny sus fortalezas necesarias se han reducido a 0\n";
                            }
                            actual_i2 = actual_i2->siguiente;
                        }
                        return 1;
                    }
                }
            }
            if (actual->tipo != "Arma" && actual->tipo != "Defensa")
            {
                j++;
            }
            actual = actual->siguiente; 
        }
        cout << "\nNúmero ingresado incorrecto\n\n";
        return 0;
    }
    return 0; 
}

// Funcion para que los enemigos ataquen a los heroes en su turno
void atacar_orcos(Lista_Heroes &heroes, Lista_Orcos &orcos)
{
    Especie* orco_actual = orcos.cabeza;
    int atq_suma = 0;
    while (orco_actual != nullptr)
    {
        atq_suma += orco_actual->dano;
        orco_actual = orco_actual->siguiente;
    }
    Especie* heroe_actual = heroes.cabeza;
    Especie* heroe_mdebil = heroes.cabeza;
    while (heroe_actual != nullptr)
    {
        if (heroe_actual->vida < heroe_mdebil->vida && heroe_mdebil->vida == 0)
        {
            heroe_mdebil = heroe_actual;
        }
        heroe_actual = heroe_actual->siguiente;
    }
    if (heroe_mdebil->defensa == 0)
    {
        cout << "La vida de " << heroe_mdebil->nombre << " ha sido reducida de " << heroe_mdebil->vida << " a ";
        heroe_mdebil->vida -= atq_suma/4;
        if (heroe_mdebil->vida < 0)
        {
            heroe_mdebil->vida -= heroe_mdebil->vida;
        }
        cout << heroe_mdebil->vida << endl;
        if (heroe_mdebil->vida == 0) {cout << RED "¡Parece que " << heroe_mdebil->nombre << " ha muerto!\n" RESET ;} 
    }
    else
    {
        cout << "La defensa de " << heroe_mdebil->nombre << " ha sido reducida de " << heroe_mdebil->defensa << " a ";
        heroe_mdebil->defensa -= atq_suma/4;
        if (heroe_mdebil->defensa < 0)
        {
            heroe_mdebil->defensa -= heroe_mdebil->defensa;
        }
        cout << heroe_mdebil->defensa << endl;
        if (heroe_mdebil->defensa == 0) {cout << YELLOW "El escudo de " << heroe_mdebil->nombre << " se ha roto\n" RESET ;} 
    } 
}
// solo para verificar si queda combate
int suma_heroes(Lista_Heroes &equipo)
{
    int suma_h = 0; Especie* heroe_actual = equipo.cabeza;
    while (heroe_actual != nullptr)
    {
        suma_h += heroe_actual->vida;
        heroe_actual = heroe_actual->siguiente;
        
    }
    return suma_h;
}

int heroes_restantes(Lista_Heroes &equipo)
{
    int cont = 0; Especie* heroe_actual = equipo.cabeza;
    while (heroe_actual != nullptr)
    {
        if (heroe_actual->vida > 0)
        {
            cont++;
        }
        heroe_actual = heroe_actual->siguiente;
    }
    return cont;
}

int suma_orcos(Lista_Orcos &horda)
{
    int suma_o = 0; Especie* orco_actual = horda.cabeza;
    while (orco_actual != nullptr)
    {
        suma_o += orco_actual->vida;
        orco_actual = orco_actual->siguiente;
    }
    return suma_o;
}

int orcos_restantes(Lista_Orcos &horda)
{
    int cont = 0; Especie* orco_actual = horda.cabeza;
    if (horda.cabeza == nullptr)
    {
        return 0;
    }
    if (horda.cabeza->siguiente == nullptr)
    {
        cont++;
        return cont;
    }
    else
    {
        while (orco_actual->siguiente != nullptr)
        {
            cont++;
            orco_actual = orco_actual->siguiente;
        }
    }
    return cont;
}

int menor_velocidad_h();
int menor_velocidad_o(Lista_Orcos &horca);
// Como parámetros, entrarían el equipo y la horda de enemigos en la sala actual
int interfazBatalla(Lista_Heroes &equipo, Lista_Orcos &horda)
{
    Especie* heroe_actual;
    while (suma_heroes(equipo) != 0 && orcos_restantes(horda) != 0)
    {
        cout << "Suma heroes: " << suma_heroes(equipo) << endl;
        cout << "Suma orcos: " << suma_orcos(horda) << endl;
        cout << BRIGHT_CYAN "\nTurno del usuario\n" RESET;
        heroe_actual = lista_equipo.cabeza;
        while (heroe_actual != nullptr)
        {
            int opcion;
            int objetivo = 0;
            do
            {
                if (heroe_actual->vida != 0)
                {
                    cout<< BRIGHT_CYAN "\nHeroes restantes: " << heroes_restantes(equipo); cout << RED << " \t\t\t\t | Orcos restantes: " << horda.cantidad << endl;
                    Especie* orco_actual = horda.cabeza;
                    Especie* equipo_actual = equipo.cabeza;
                    while (equipo_actual != nullptr || orco_actual != nullptr)
                    {
                        if (equipo_actual != nullptr)
                        {
                            if (equipo_actual->vida > 0)
                            {
                                cout << BRIGHT_CYAN << equipo_actual->nombre << " (salud: " << equipo_actual->vida << " | escudo: " << equipo_actual->defensa <<")" << RED;
                                equipo_actual = equipo_actual->siguiente;
                            }
                            else
                            {
                                cout << GRAY << equipo_actual->nombre << " (salud: " << equipo_actual->vida << " | escudo: " << equipo_actual->defensa <<")" << RED;
                                equipo_actual = equipo_actual->siguiente;
                            }
                        }
                        else
                        {
                            cout << BRIGHT_CYAN " \t\t\t\t " RED;
                        }
                        if (orco_actual != nullptr)
                        {
                            cout << " \t\t - " << orco_actual->nombre << " (salud: " << orco_actual->vida << " | daño: " << orco_actual->dano <<")  \n" << RESET;
                            orco_actual = orco_actual->siguiente;
                        }
                        else 
                        {
                            cout << "\n" RESET;
                        }
                    }

                    cout<< LIGHT_BROWN "\n\t¿Qué desea hacer con <"<< heroe_actual->nombre << ">? \n";
                    cout<< BRIGHT_RED  "\t\t   _________________  \t\t" YELLOW  "   _________________   \n";
                    cout<< BRIGHT_RED  "\t\t  /________________/| \t\t" YELLOW  "  /________________/|  \n";
                    cout<< BRIGHT_RED  "\t\t |   1. Actuar     || \t\t" YELLOW  " | 2. Ver mochila  ||  \n";
                    cout<< BRIGHT_RED  "\t\t |_________________|/ \t\t" YELLOW  " |_________________|/  \n";
                    cout<<             "                                                                \n";
                    cout<< ORANGE_RGB  "\t\t   _________________  \t\t" MAGENTA "   _________________   \n";
                    cout<< ORANGE_RGB  "\t\t  /________________/| \t\t" MAGENTA "  /________________/|  \n";
                    cout<< ORANGE_RGB  "\t\t | 3. Informacion  || \t\t" MAGENTA " |     4.Huir      ||  \n";
                    cout<< ORANGE_RGB  "\t\t |_________________|/ \t\t" MAGENTA " |_________________|/  \n\n" << RESET;
                    opcion = ObtenerEntero("Opcion: ");
                    switch (opcion)
                    {
                        case 1: {
                            if (atacar_heroe(heroe_actual, horda) == 0)
                            {
                                break;
                            }
                            else
                            {
                                heroe_actual = heroe_actual->siguiente;
                                opcion = 5;
                                break;
                            }
                        }
                        case 2: {
                            if (heroe_actual->mochila.cantidad == 0)
                            {
                                cout << "Este heroe no tiene implementos en su mochila\n";
                                break;
                            }
                            int ocasion = Mochila_de(heroe_actual, horda);
                            if (ocasion == 1)
                            {
                                heroe_actual = heroe_actual->siguiente;
                                opcion = 5;
                                break;
                            }
                            else if (ocasion == 2)
                            {
                                return 1;
                            }
                            else
                            {
                                break;
                            }
                        }
                        case 3:
                            cout << "\nID: "      << heroe_actual->id <<       "\n";
                            cout << "Nombre: <"   << heroe_actual->nombre <<  ">\n";
                            cout << "Tipo: "      << heroe_actual->tipo <<     "\n";
                            cout << "Fortaleza: " << heroe_actual->fortaleza << " (fortaleza base: " << heroe_actual->fort_base <<") \n";
                            cout << "Vida: "      << heroe_actual->vida << " (vida base: " << heroe_actual->vida_base <<") \n";
                            cout << "Velocidad: " << heroe_actual->velocidad <<"\n";
                            cout << "Defensa: "   << heroe_actual->defensa <<  "\n";
                            break;
                        case 4:
                            if (orcos_restantes(horda) > heroes_restantes(equipo)*3)
                            {
                                cout << "La cantidad de orcos triplica la cantidad de heroes en tu equipo, puedes escapar...\n";
                                horda.~Lista_Orcos();
                                return 1;
                            }
                            else 
                            {
                                if (menor_velocidad_h() < menor_velocidad_o(horda))
                                {
                                    cout << "El heroe más lento no tiene la velocidad suficiente para huir\n";
                                    opcion = 5;
                                }
                                else
                                {
                                    cout << "Has escapado con éxito\n";
                                    return 1;
                                }
                            }
                            
                            break;
                        case 5:
                            break;
                        default:
                            cout << "\nNúmero ingresado incorrecto. Intente de nuevo\n\n";
                    }
                }
                else
                {
                    heroe_actual = heroe_actual->siguiente;
                    opcion = 5;
                }
            } while (opcion != 5);
            if (suma_orcos(horda) == 0)
            {
                cout << "Tu equipo ha ganado!! \n";
                return 1;
            }
        }
        cout << RED "\nTurno de los Orcos\n" RESET;
        atacar_orcos(equipo, horda);
        if (suma_heroes(equipo) <= 0)
        {
            cout << "Tu equipo ha perdido!!\n";
            return 0;
        }
    }
    cout << "Suma heroes: " << suma_heroes(equipo) << endl;
    cout << "Suma orcos: " << orcos_restantes(horda) << endl;
    return 0;
}

// Ignoren esto
void prueba()
{
    lista_equipo.agregarHeroe("Aragorn", "Hombre", 160, 120, 140);
    lista_equipo.agregarHeroe("Legolas", "Elfo",   130, 130, 110);
    lista_equipo.agregarHeroe("Gimli",   "Enano",  155, 200, 180);
    lista_equipo.agregarHeroe("Gandalf", "Mago",   120, 330, 150);
    lista_equipo.mostrarEspecies();
    // Poder Magico de Enanos // Poder Magico Translador de Salas // Duplicador de ataque de implemento // Poder Magico contra los orcos
    lista_equipo.agregar_a_Mochila_conid(Implemento("Gotas sagradas", "Pocion", "Vida", 1, 10, 50),13);
    lista_equipo.agregar_a_Mochila_conid(Implemento("Poder Magico de Enanos ", "Poder magico", "Magico", 12, 20, 50),13);
    lista_equipo.agregar_a_Mochila_conid(Implemento("Escudo", "Defensa", "Defensa", 15, 20, 150),13);
    lista_equipo.agregar_a_Mochila_conid(Implemento("Daga", "Arma", "Ataque", 12, 250, 250),13);
    lista_equipo.agregar_a_Mochila_conid(Implemento("Martillo", "Arma", "Ataque", 12, 250, 150),13);

    lista_equipo.agregar_a_Mochila_conid(Implemento("Gotas sagradas", "Pocion", "Vida", 1, 10, 50),14);
    lista_equipo.agregar_a_Mochila_conid(Implemento("Pocima", "Pocion", "Vida", 12, 20, 50),14);
    lista_equipo.agregar_a_Mochila_conid(Implemento("Escudo", "Defensa", "Defensa", 15, 20, 150),14);
    lista_equipo.agregar_a_Mochila_conid(Implemento("Daga", "Arma", "Ataque", 12, 250, 20),14);
    lista_equipo.agregar_a_Mochila_conid(Implemento("Martillo", "Arma", "Ataque", 12, 250, 20),14);

    lista_equipo.agregar_a_Mochila_conid(Implemento("Gotas sagradas", "Pocion", "Vida", 1, 10, 50),15);
    lista_equipo.agregar_a_Mochila_conid(Implemento("Pocima", "Pocion", "Vida", 12, 20, 50),15);
    lista_equipo.agregar_a_Mochila_conid(Implemento("Escudo", "Defensa", "Defensa", 15, 20, 150),15);
    lista_equipo.agregar_a_Mochila_conid(Implemento("Daga", "Arma", "Ataque", 12, 250, 250),15);
    lista_equipo.agregar_a_Mochila_conid(Implemento("Martillo", "Arma", "Ataque", 12, 250, 150),15);

    lista_equipo.agregar_a_Mochila_conid(Implemento("Escudo", "Defensa", "Defensa", 15, 20, 150),16);
    lista_equipo.agregar_a_Mochila_conid(Implemento("Daga", "Arma", "Ataque", 12, 250, 250),16);
    lista_equipo.agregar_a_Mochila_conid(Implemento("Martillo", "Arma", "Ataque", 12, 250, 150),16);
}

class Registro 
{
    public: 
    string sala;
    int ID;
    int orcos_derrotados;
    Registro* siguiente = nullptr;

    Registro(string sal, int orc = 0, int id = 0)
    {
        sala = sal;
        orcos_derrotados = orc;
        ID = id;
        siguiente = nullptr;
    };
};

class Misiones
{
    public:
    Registro* cabeza = nullptr;
    int cantidad = 0;
    Misiones() : cabeza(nullptr), cantidad(0) {}

    ~Misiones()
    {
        Registro* actual = cabeza;
        while(actual != nullptr)
        {
            Registro* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }

    void agregarRegistro(string sala, int orcos_derrotados)
    {
        Registro* nuevo = new Registro(sala, orcos_derrotados, cantidad + 1);
        if (cabeza == nullptr)
        {
            cabeza = nuevo;
        }
        else
        {
            Registro* actual = cabeza;
            while (actual->siguiente != nullptr)
            {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
        cantidad++;
    }

    void mostrarRegistros()
    {
        Registro* actual = cabeza;
        
        if (cabeza == nullptr)
        {
            cout << "\nNo hay registros de movimientos\n";
        }
        else
        {
            while (actual != nullptr)
            {
                cout << "\n________________________________________\n";
                cout << "Movimiento número: " << actual->ID << endl;
                cout << "Sala visitada: "<< actual->sala << endl;
                cout << "Orcos derrotados: " << actual->orcos_derrotados << endl;
                actual = actual->siguiente;
            }
        }
    }
};

Misiones lista_registros;

// (moved up above MenuMapas)
void menuMovimientos()
{
    cout << LIGHT_BROWN;
    cout << "\n╔════════════════════════════╗\n";
    cout << "║        MOVIMIENTOS         ║\n";
    cout << "╠════════════════════════════╣\n";
    cout << "║ 1. Mover a Otra Sala       ║\n";
    cout << "║ 2. Luchar con Orcos        ║\n";
    cout << "║ 3. Ver Mapa                ║\n";
    cout << "║ 4. Ver equipo              ║\n";
    cout << "║ 5. Ver mochilas            ║\n";
    cout << "║ 6. Registros               ║\n";
    cout << "╚════════════════════════════╝\n";
    cout << RESET;
}

int menor_velocidad_h()
{
    Especie* actual = lista_equipo.cabeza;
    int menor_vel = actual->velocidad;
    while (actual != nullptr)
    {
        if (actual->velocidad < menor_vel)
        {
            menor_vel = actual->velocidad;
        }
        actual = actual->siguiente;
    }
    return menor_vel;
}

int menor_velocidad_o(Lista_Orcos &horda)
{
    Especie* actual = horda.cabeza;
    int menor_vel = actual->velocidad;
    while (actual != nullptr)
    {
        if (actual->velocidad < menor_vel)
        {
            menor_vel = actual->velocidad;
        }
        actual = actual->siguiente;
    }
    return menor_vel;
}

int espacio_enMochilas()
{
    Especie* actual = lista_equipo.cabeza;
    Implemento* actuali = nullptr;
    int cont = 0;
    while (actual != nullptr) 
    {
        if (actual->mochila.cantidad == 0)
        {
            cont += 5;
        }
        else
        {
            actuali = actual->mochila.cabeza;
            while (actuali != nullptr)
            {
                cont++;
                actuali = actuali->siguiente;
            }
        }
        actual = actual->siguiente;
    }
    cout << endl << endl;
    return cont;
}


int juego()
{
    //mensajeInicial();
    list<Sala>* sala_actual = mapa.RetornarSala(1);
    list<Sala>* sala_maslejana = mapa.RetornarSala(mapa.RetornarSalaLejana(1));
    Especie temp = lista_orcos.RetornarOrco(numeroAleatorio(7, 11));
    sala_maslejana->front().horda.agregarOrco(temp);
    sala_maslejana->front().horda.mostrarOrcos();
    list<Sala>* sala_conpuerta = mapa.RetornarSala(numeroAleatorio(10,59));
    
    sala_conpuerta->front().HayPuerta = true;
    int contador_puerta = 0;
    cout << RED "\nLa Puerta del Destino se encuentra en la sala: ID " << sala_conpuerta->front().id << " <" << sala_conpuerta->front().nombre << "> \n" RESET ;
    while (suma_heroes(lista_equipo) > 0)
    {
        if (sala_conpuerta->front().id == sala_actual->front().id)
        {
            sala_actual->front().horda.agregarOrco(lista_orcos.RetornarOrco(12));
            cout << GREEN << "Estás en la sala con la Puerta del Destino \n" << RESET;
            cout << RED << "El BOSS ha aparecido, derrótalo para ganar! \n" << RESET;
        }
        cout << colores_bright[numeroAleatorio(0,7)] << endl;
        cout << "|══════════════════════════════════|\n";
        cout << "\t   SALA ACTUAL                    \n";
        cout << "|══════════════════════════════════|\n";
        cout << " \t" << sala_actual->front().nombre                                   <<" \n";
        cout << " \tOrcos en la sala: " << orcos_restantes(sala_actual->front().horda) <<" \n";
        cout << " \tHeroes restantes: " << heroes_restantes(lista_equipo)              <<" \n";
        cout << "<══════════════════════════════════>\n";
        cout << RESET;
        int orcos_cant = orcos_restantes(sala_actual->front().horda);
        int opcion; 
        int cont_turnos = 0;
        do
        {
            menuMovimientos();
            opcion = ObtenerEntero("Opción: ");
            cout << endl;
            switch (opcion)
            {
            case 1:
                if(sala_actual->front().horda.cabeza == nullptr)
                {
                    mapa.MostrarAdyacencias(sala_actual->front().id);
                    int id_saladest = mapa.MoveraAdyacencia(sala_actual->front().id);
                    while (id_saladest == -1)
                    {
                        cout << "\nIngrese un id válido.\n";
                        mapa.MostrarAdyacencias(sala_actual->front().id);
                        id_saladest = mapa.MoveraAdyacencia(sala_actual->front().id);
                    }
                    list<Sala> *sala_destino = mapa.RetornarSala(id_saladest);
    //Para probar:  //cout << "Sala destino: " << sala_destino->front().nombre << endl;
    //Para probar:  //cout << "Distancia total: " << mapa.RetornarDistanciaAdyacencia(sala_actual->front().id, sala_destino->front().id) << endl;
    //Para probar:  //cout << "Heroe de menor velocidad: " << menor_velocidad_h() << endl;
                    int distancia = mapa.RetornarDistanciaAdyacencia(sala_actual->front().id, sala_destino->front().id);
                    int recorrido = 0;
                    while (recorrido < distancia)
                    {
                        recorrido += menor_velocidad_h()/10;
                        cont_turnos++;  
                    } 
                    if (cont_turnos == 0)
                    {
                        cont_turnos++;
                    }
                    cout << "Turnos necesarios: " << cont_turnos << endl;
                    contador_puerta += cont_turnos;
                    if (contador_puerta >= 10)
                    {
                        sala_conpuerta->front().HayPuerta = false;
                        cout << RED << "!La Puerta del Destino se ha trasladado a una sala aleatoria!\n";
                        sala_conpuerta = mapa.RetornarSala(numeroAleatorio(10, 60));
                        cout << "La Puerta del Destino se encuentra en la sala: " << sala_conpuerta->front().id << " <" << sala_conpuerta->front().nombre << "> \n" RESET ;
                        sala_conpuerta->front().HayPuerta = true;
                        contador_puerta = 0;
                    } 
                    int cont = 0;
                    while (cont <= cont_turnos)
                    {
                        mapa.BFSOrcos(sala_maslejana->front().id);
                        cont++;
                    } 
                    cont = 0;
                    while (cont <= 3)
                    {
                        list<Sala> *salax = mapa.RetornarSala(numeroAleatorio(1,60));
                        int cantid = 0;
                        while (cantid <= 5)
                        {
                            salax->front().horda.agregarOrco(lista_orcos.RetornarOrco(numeroAleatorio(7,11)));
                            cantid++;
                        }
                        cont++;
                    }
                    //sala_maslejana->front().horda.mostrarOrcos(); 
                    lista_registros.agregarRegistro(sala_actual->front().nombre, orcos_cant);
                    sala_actual = mapa.RetornarSala(sala_destino->front().id);
                    salaMovimiento();
                    opcion = 7;
                    break;
                }
                else 
                {
                    cout << "Hay orcos en la sala, no puedes salir \n";
                    break;
                }
            case 2:
                if(sala_actual->front().horda.cabeza == nullptr)
                {
                    cout << "No hay orcos en la sala actual y puede avanzar de sala \n";
                    break;
                }
                else if (interfazBatalla(lista_equipo, sala_actual->front().horda) == 1)
                {
                    if (sala_actual->front().id == sala_conpuerta->front().id)
                    {
                        cout << GREEN << ITALIC << "¡Puedes entrar a la Puerta del destino!\n";
                        cout << "Has ganado el juego, FELICITACIONES!" << RESET;
                        return 1;
                        break;
                    }
                    else
                    {
                        cout << "Puedes avanzar a la siguiente sala. \n";
                        sala_actual->front().horda.cabeza = nullptr;
                        break;
                    }
                }
                else
                {
                    cout << "El juego ha terminado\n";
                    return 0;
                }
                
            case 3: 
                cout << CYAN "\nActualmente se encuentra en la sala: ID " << sala_actual->front().id << " <" << sala_actual->front().nombre << "> " RESET ;
                cout << "\n<<< Adyacencias a la Sala Actual >>>\n";
                mapa.MostrarAdyacencias(sala_actual->front().id);
                cout << RED "\nLa Puerta del Destino se encuentra en la sala: ID " << sala_conpuerta->front().id << " <" << sala_conpuerta->front().nombre << "> \n" RESET ;
                cout << "<<< Adyacencias a la Puerta del Destino >>>\n";
                mapa.MostrarAdyacencias(sala_conpuerta->front().id);
                int opcion_sala;
                cout << "\n¿Desea ver las adyacencias de otra sala? \n";
                do 
                {
                    opcion_sala = ObtenerEntero("\nID de la sala (Ingrese 0 para salir): ");
                    if (opcion_sala != 0)
                    {
                        cout << "Adyacencias a la sala de ID: " << opcion_sala <<  endl;
                        mapa.MostrarAdyacencias(opcion_sala);
                    }
                }
                while(opcion_sala != 0);
                break;
            case 4:
                lista_equipo.mostrarEspecies();
                break;
            case 5:
                lista_equipo.mostrarMochilas();
                break;
            case 6:
                lista_registros.mostrarRegistros();
                break;
            case 7:
                break;
            default:
                cout << "Opción ingresada inválida. Ingrese un número correcto\n";
            }
        } while (opcion != 7);
    }
    if (suma_heroes(lista_equipo) == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int main()
{
    menuPrincipal();
    mensajeInicial();
    juego();
    return 1;
} 
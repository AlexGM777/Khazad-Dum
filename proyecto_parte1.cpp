#include <iostream>
#include <random>
#include <limits> 
using namespace std;

// Funcion validar un entero
int ObtenerEntero() 
{
    int numero;
    do 
    {
        cin >> numero;
        if (cin.fail()) {
            cout << "Entrada inválida. Ingrese un número válido.\n";
            cin.clear(); // Evitar errores
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        } else {
            return numero; // Devuelve el numero si está bien ingresado
        }
    } while (cin.fail() == false);
    return 0; // No hace falta, pero me suelta error si no lo pongo
}

// Funcion validar texto
string ObtenerTexto() 
{
    string cadena;
    do 
    {
        cin >> cadena;
        if (cin.fail()) {
            cout << "Entrada inválida. Ingrese un texto válido.\n";
            cin.clear(); // Evitar errores
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        } else {
            return cadena; // Devuelve el numero si está bien ingresado
        }
    } while (cin.fail() == false);
    return cadena; // Es redundante, pero me suelta error si no lo pongo
}

// PARTE DE LOS HEROES
class Implemento // Para cada heroe
{
    public: 
    string nombre;
    string tipo;
    int uso;
    int requisito;
    int valor;

    Implemento(string n = "", string t = "", int u = 0, int r = 0, int v = 0)
    {
        nombre = n;
        tipo = t;
        uso = u;
        requisito = r;
        valor = v;
    };
};

class Especie {
    public:
    string nombre;
    int vida;
    int fortaleza;
    int velocidad;
    Implemento mochila[5];
    Especie *siguiente = nullptr;

    Especie(string n, int v, int f, int vel) // Constructor-Heroe
    { 
        nombre = n;
        vida = v;
        fortaleza = f;
        velocidad = vel;
        for (int i = 0; i < 5; i++) {
            mochila[i] = Implemento("Vacio", "", 0, 0, 0);
        }
    };
    Especie(string n, int v, int f, int vel, bool esOrco) // Constructor-Orcos
    { 
        nombre = n;
        vida = v;
        fortaleza = f;
        velocidad = vel;
        if (!esOrco) 
        {
            for (int i = 0; i < 5; i++) 
            {
                mochila[i] = Implemento("Vacio", "", 0, 0, 0);
            }
        }
    };
};
class ListaOrcos
{
    private:
        Especie* cabeza = nullptr;
    public:
    int cantidad = 0;
    ~ListaOrcos()
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
    void agregarOrco(string n, int v, int f, int vel, Implemento moc[5] = NULL)
    {
        Especie* nuevo = new Especie(n, v, f, vel, NULL);
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
        }
        cantidad++;
        cout << "Especie <" << n <<"> agregada con exito\n\n";
    }
    void EliminarOrco(string nombre_eliminar)
    {
        if (cabeza == nullptr) {
            cout << "La lista está vacía. No hay orcos para eliminar.\n";
            return;
        }
        if (cabeza->nombre == nombre_eliminar)
        {
            Especie* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            cantidad--;
            cout << "Orco <" << nombre_eliminar << "> eliminado correctamente.\n";
            return;
        }
        Especie* actual = cabeza;
        Especie* anterior = nullptr;
        while (actual != nullptr && actual->nombre != nombre_eliminar)
        {
            anterior = actual;
            actual = actual->siguiente;
        }
        if (actual == nullptr) 
        {
            cout << "El orco <" << nombre_eliminar << "> no se encontró en la lista.\n";
            return;
        }
        anterior->siguiente = actual->siguiente;
        delete actual;
        cantidad--;
        cout << "Orco <" << nombre_eliminar << "> eliminado correctamente.\n";
    }
    void mostrarOrcos() 
    {
        if (cantidad == 0) 
        {
            cout << "\nNo hay orcos en la lista.\n";
        }
        else
        {
            cout << "\nLista de orcos (" << cantidad << "):";
            Especie* actual = cabeza;
            int i = 1;
            while (actual != nullptr) 
            {
                cout << "\nOrco #" << i << ' ';
                cout << "Nombre: <" << actual->nombre << ">, ";
                cout << "Vida: " << actual->vida << ", ";
                cout << "Fortaleza: " << actual->fortaleza << ", ";
                cout << "Velocidad: " << actual->velocidad;
                actual = actual->siguiente;
                i++;
            }
            cout << endl;
        }
    }
};
class ListaHeroes
    {
    private:
        Especie* cabeza;
        
    public:
    int cantidad; // cantidad de heroes en el equipo
        ListaHeroes() : cabeza(nullptr), cantidad(0) {}

        ~ListaHeroes() //Destructor
        { 
            Especie* actual = cabeza;
            while (actual != nullptr) 
            {
                Especie* temp = actual;
                actual = actual->siguiente;
                delete temp;
            }
        }

        void anadirImplementos(Especie* nuevo_)
        {
            ////////// ARMAS ///////////
            int i = 0;
            cout<< "\nElija un arma para su heroe de fortaleza: " << nuevo_->fortaleza << endl 
                << "1. Dardo (Fortaleza mayor a 50, Daño: 100) \n"
                << "2. Baston de Gandalf (Fortaleza mayor a 100, Daño: 150) \n"
                << "3. Espada de Aragorn (Fortaleza mayor a 200, Daño: 200) \n\n";
            int opcion_armas;
            do 
            {
                cout << "Elija un arma: ";
                opcion_armas = ObtenerEntero();
                switch (opcion_armas)
                {
                    case 1:
                        nuevo_->mochila[i] = Implemento("Dardo", "Arma", 20, 50, 100);
                        i++;
                        break;
                    case 2:
                        nuevo_->mochila[i] = Implemento("Baston de Gandalf", "Arma", 20, 100, 150);
                        i++;
                        break;
                    case 3:
                        nuevo_->mochila[i] = Implemento("Arma 3", "Arma", 20, 200, 200);
                        i++;
                        break;
                    default:
                        cout << "Opcion inválida\n";
                } 
            } while(opcion_armas > 3 || opcion_armas < 1);
            
            ////////// BOTAS ///////////
            cout<< "\nElija unas botas para su heroe\n"
            << "1. Patas de Liebre de la Marca (30% más de velocidad, 30% menos de daño) \n"
            << "2. Patas de Huargo (15% más de velocidad, 15% menos de daño) \n"
            << "3. Botas de Enano (20% más de velocidad, 20% menos de daño) \n\n";
            
            int opcion_botas;
            do
            {
                cout << "Elija un par: ";
                opcion_botas = ObtenerEntero();
                switch (opcion_botas)
                {
                    case 1:
                        nuevo_->mochila[i] = Implemento("Patas de Liebre de la Marca", "Botas", 20, 30, 0);
                        i++;
                        break;
                    case 2:
                        nuevo_->mochila[i] = Implemento("Patas de Huargo", "Botas", 20, 15, 0);
                        i++;
                        break;
                    case 3:
                        nuevo_->mochila[i] = Implemento("Botas de Enano ", "Botas", 20, 20, 0);
                        i++;
                        break;
                    default:
                        cout << "Opcion inválida\n";
                }
            } while (opcion_botas < 1 || opcion_botas > 3);
            
            cout << endl;
            
            /////// ACCESORIOS ////////

            cout<< "Elija un accesorio para su heroe: " << endl
                << "1. Manto de Dragon (20% más de vida, 20% menos de velocidad) \n"
                << "2. Brazalete de Elfo (15% más de vida, 15% menos de velocidad) \n"
                << "3. Pipa de Gandalf (10% más de vida, 10% menos de velocidad) \n\n";
            int opcion_accesorios;
            do 
            {
                cout << "Elija un accesorio: ";
                opcion_accesorios = ObtenerEntero();
                switch (opcion_accesorios)
                {
                case 1:
                    nuevo_->mochila[i] = Implemento("Manto de Dragon", "Accesorio", 20, 50, 100);
                    i++;
                    break;
                case 2:
                    nuevo_->mochila[i] = Implemento("Brazalete de Elfo", "Accesorio", 20, 100, 150);
                    i++;
                    break;
                case 3:
                    nuevo_->mochila[i] = Implemento("Pipa de Gandalf", "Accesorio", 20, 200, 200);
                    i++;
                    break;
                default:
                    cout << "\nOpcion inválida\n";
                }
            } while(opcion_accesorios > 3 || opcion_accesorios < 1);
        
            cout << endl;
        }
        void agregarHeroe(string name, int vid, int fort, int vel) 
        {
            Especie* nuevo = new Especie(name, vid, fort, vel);
            anadirImplementos(nuevo);
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
            }
            cantidad++;
            cout << "Especie <" << name <<"> agregada con exito\n\n";
        }

        void agregarLider()
        {
            string nombre;
            cout << "Indique el nombre de el lider de sus heroes: ";
            nombre = ObtenerTexto();
            Especie* lider = new Especie(nombre, 200, 200, 200); 
            if (cabeza == nullptr) // Si cabeza no apunta a nadie (Inicio)
            {
                
                cabeza = lider;
                cantidad++;
                cout<< "\nSu lider <" << cabeza->nombre << "> tiene 200 puntos en cada característica\n";
                anadirImplementos(cabeza);
            }
            else
            {
                Especie* auxiliar = cabeza;
                cabeza = lider;
                lider->siguiente = auxiliar;
                cout << "<" <<nombre <<"> ha sido agregado con exito\n\n";
                cantidad++;
            }
            
        }
        void mostrarHeroes() 
        {
            if (cantidad == 0) 
            {
                cout << "\nNo hay heroes en la lista.\n";
            }
            else
            {
                cout << "\nLista de heroes (" << cantidad << "):";
                Especie* actual = cabeza;
                int i = 1;
                while (actual != nullptr) 
                {
                    cout << "\nHeroe #" << i << ' ';
                    cout << "Nombre: <" << actual->nombre << ">, ";
                    cout << "Vida: " << actual->vida << ", ";
                    cout << "Fortaleza: " << actual->fortaleza << ", ";
                    cout << "Velocidad: " << actual->velocidad;
                    actual = actual->siguiente;
                    i++;
                }
                cout << endl;
            }
        }

        void eliminarHeroe(int numero)
        {
            if (cantidad == 0) 
            {
                cout << "\nNo hay heroes en la lista.\n";
            }
            else
            {
                Especie* actual = cabeza;
                Especie* eliminar;
                int i = 1;
                while (actual != nullptr) 
                {
                    if (numero == 1)
                    {
                        eliminar = cabeza;
                        cabeza = cabeza->siguiente;
                        cout << "\n<"<< eliminar->nombre << "> eliminado correctamente.\n";
                        delete eliminar;
                        cantidad--;
                        break;
                    }
                    else if (i == numero-1)
                    {
                        eliminar = actual->siguiente;
                        actual->siguiente = eliminar->siguiente;
                        cout << "\n<"<< eliminar->nombre << "> eliminado correctamente.\n";
                        delete eliminar;
                        cantidad--;
                        break;
                    }
                    actual = actual->siguiente;
                    i++;
                }
            }
        }

        void mostrarImplementos()
        {
            if (cantidad == 0) 
            {
                cout << "\nNo hay heroes en la lista.\n";
            }
            else
            {
                Especie* actual = cabeza;
                int i = 1;
                while (actual != nullptr) 
                {
                    cout << "\nHeroe #" << i << ' ';
                    cout << "Nombre: " << actual->nombre << "\n ";
                    cout << "Lista de implementos: \n";
                    for (int j = 0; j < 5; j++)
                    {
                        if (actual->mochila[j].uso != 0)
                        {
                            cout << "#" << " " << actual->mochila[j].nombre << endl;
                        }
                    }
                actual = actual->siguiente;
                i++;
                }
            }
        }

        void eliminarImplemento()
        {
            mostrarImplementos();
            int numero;
            cout << "\nIngrese el número del heroe a editar: ";
            numero = ObtenerEntero();
            Especie* actual = cabeza;
            int j = 1;
            cout << "\nEditando al heroe >" << actual->nombre << "<... \n\n";
            while(actual != nullptr)
            {
                if (j == numero)
                {
                    for(int i = 0 ; i < 5 ; i++)
                    {
                        
                        actual->mochila[i] = Implemento("","",0,0,0);
                    }
                    anadirImplementos(actual);
                }
                j++;
                actual = actual->siguiente;
            }
        }
    };

ListaHeroes lista_heroes;
void agregarHeroes()
{
    int opcion_h;
    do 
    {
        cout << "\nQué tipo de heroe quiere agregar?\n\n" 
        << "1. Elfo      (Vida: 140, Fortaleza: 210, Velocidad: 150 )\n"
        << "2. Hombre    (Vida: 170, Fortaleza: 160, Velocidad: 170 )\n" 
        << "3. Enano     (Vida: 150, Fortaleza: 110, Velocidad: 240 )\n" 
        << "4. Mago      (Vida: 110, Fortaleza: 240, Velocidad: 170 )\n" 
        << "5. Ente      (Vida: 250, Fortaleza: 90,  Velocidad: 160 )\n"
        << "6. Beornings (Vida: 130, Fortaleza: 300, Velocidad: 70  )\n"
        << "7. Hobbit    (Vida: 280, Fortaleza: 70,  Velocidad: 150 )\n" 
        << "8. Druedain  (Vida: 190, Fortaleza: 200, Velocidad: 110 )\n"
        << "9. Ver equipo de heroes\n"
        << "10. Retroceder\n\n";
        cout << "Elija un heroe: ";

        opcion_h = ObtenerEntero();
        switch (opcion_h) 
        {
        case 1: 
            lista_heroes.agregarHeroe("Elfo", 140, 210, 150);
            break;
        
        case 2: 
            lista_heroes.agregarHeroe("Hombre", 170, 160, 170); 
            break;
        
        case 3:
            lista_heroes.agregarHeroe("Enano", 150, 110, 240);
            break;
        
        case 4: 
            lista_heroes.agregarHeroe("Mago", 110, 240, 170);
            break;
        
        case 5: 
            lista_heroes.agregarHeroe("Ente", 250, 90, 160);
            break;
        
        case 6: 
            lista_heroes.agregarHeroe("Beornings", 130, 300, 70);
            break;
        
        case 7: 
            lista_heroes.agregarHeroe("Hobbit", 280, 70, 150);
            break;
        case 8:
            lista_heroes.agregarHeroe("Druedain", 190, 200, 110);
            break;
        case 9:
            lista_heroes.mostrarHeroes();
            break;
        case 10:
            cout << "Volviendo al menu..." << endl;
            break;
        default: 
            cout << "Opción inválida. Intente de nuevo.\n";    
        }
    } while (opcion_h != 10 && lista_heroes.cantidad < 4);
}

ListaOrcos lista_orcos;

void agregarOrcos()
{
    int opcion_o;
    string nombre;
    cout << "\nIngrese nombre del orco: ";
    cin >> nombre;
    cout << "\n¿Qué tipo de orco es <" << nombre << ">?\n"
    << "1. Orco comun (Vida: 130, Daño: 130, Velocidad: 130)\n"
    << "2. Uruk-hai   (Vida: 150, Daño: 110, Velocidad: 160)\n"
    << "3. Trasgos    (Vida: 180, Daño: 150,  Velocidad: 70)\n"
    << "4. Semi-orco  (Vida: 220, Daño: 80, Velocidad: 100)\n"
    << "5. Snaga      (Vida: 90, Daño: 190, Velocidad: 120)\n";
    cout << "Elija un tipo de orco: " << endl;
    opcion_o = ObtenerEntero();
    switch (opcion_o) 
    {
    case 1: 
        lista_orcos.agregarOrco(nombre, 130, 130, 130);
        break;   
    case 2: 
        lista_orcos.agregarOrco(nombre, 150, 110, 160); 
        break;
    case 3:
        lista_orcos.agregarOrco(nombre, 180, 150, 70); 
        break;
    case 4: 
        lista_orcos.agregarOrco(nombre, 220, 80, 100); 
        break;
    case 5:
        lista_orcos.agregarOrco(nombre, 90, 190, 120);
        break;
    case 6:
        cout << "Regresando al menu...\n\n";
        break;
    default: 
        cout << "Opción inválida. Intente de nuevo.\n";    
    } 
}

void MenuOrcos()
{
    int opcion_menu_orcos;
    do
    {
        cout<< "Menu Orco\n"
            << "\n¿Qué desea hacer ahora?\n\n"
            << "1. Agregar orco\n"
            << "2. Eliminar un orco\n"
            << "3. Mostrar lista de orcos\n"
            << "4. Salir\n\n";
        cout << "Ingrese una opción: ";
        opcion_menu_orcos = ObtenerEntero();
        switch (opcion_menu_orcos)
        {
            case 1:
                agregarOrcos();
                int opcion_orco;
                do 
                {
                    cout<< "Desea agregar otro orco? \n"
                        << "1. Si\n"
                        << "2. No\n"
                        << "Ingrese una opcion: ";
                    opcion_orco = ObtenerEntero();
                    cout << endl;
                    switch (opcion_orco)
                    {
                        case 1: 
                            agregarOrcos();
                            break;

                        case 2:
                            cout << "Regresando al menu... \n\n";
                            break;
                        default:
                            cout << "Opcion invalida. Intente de nuevo";
                    } 
                } while (opcion_orco != 2);
                break;
            case 2:
                {
                    string nombre_orco;
                    cout << "Ingrese el nombre del orco que desea eliminar: ";
                    cin >> nombre_orco;
                    lista_orcos.EliminarOrco(nombre_orco);
                }
                break;
            case 3:
                lista_orcos.mostrarOrcos();
                break;
            case 4:
                cout << "Saliendo del programa...\n";
                break;
        default:
            cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion_menu_orcos != 4);
}

//////// MAPAS ///////////
struct mapa {
    string ubicacion;
    mapa *siguiente;
};

void menu();
void insertarubicacion(mapa *&, string);
void mostrarmapa(mapa *);
void buscarubicacion(mapa *&, string);
void borrarubicacion(mapa *&, string);
void borrarmapa(mapa *&, string &); 
mapa *lista_salas = NULL;

void menuMapa() {
    int opc;
    string ubicacion; 
    do {   
        cout << "\nMenu del mapa\n";
        cout << "1. Agregar una ubicacion al mapa\n";
        cout << "2. Mostrar mapa\n";
        cout << "3. Buscar una ubicacion\n";
        cout << "4. Eliminar una ubicacion del mapa\n";
        cout << "5. Borrar mapa\n";
        cout << "6. Salir \n\n";
        cout << "Escoge una opcion: ";
        opc = ObtenerEntero();
        switch (opc) 
        {
            case 1:
                cout << "Digite un texto: ";
                cin >> ubicacion;
                insertarubicacion(lista_salas, ubicacion);
                break;
            case 2:
                mostrarmapa(lista_salas);
                break;
            case 3:
                cout << endl;
                cout << "Que ubicacion quiere buscar? ";
                cin >> ubicacion;
                buscarubicacion(lista_salas, ubicacion);
                break;
            case 4:
                cout << "Que ubicacion quiere eliminar? ";
                cin >> ubicacion;
                borrarubicacion(lista_salas, ubicacion);
                break;
            case 5:
                while (lista_salas != NULL) { // mientras la lista no se vacie por completo
                    borrarmapa(lista_salas,ubicacion);
                    cout << ubicacion << " -> ";
                }
                cout << "Mapa vacio.\n";
                break;
            case 6:
                cout << "Saliendo del programa...";
                break;
        }
    } while (opc != 6);
    borrarmapa(lista_salas, ubicacion); // Por si acaso
}

void insertarubicacion(mapa *&lista_salas, string u) {
    mapa *nuevo = new mapa();
    nuevo->ubicacion = u;
    mapa *aux1 = lista_salas;
    mapa *aux2;

    while ((aux1 != NULL) && (aux1->ubicacion < u)) {
        aux2 = aux1;
        aux1 = aux1->siguiente;   
    }
    if (lista_salas == aux1) {
        lista_salas = nuevo;
        nuevo->siguiente = aux1;
    } else {
        aux2->siguiente = nuevo;
    }

    nuevo->siguiente = aux1;
    cout << "\nUbicacion: " << u << " agregada a la lista\n";
    cout << endl;
}

void mostrarmapa(mapa *lista_salas) {
    mapa *actual = lista_salas;
    
    while (actual != NULL) {
        cout << actual->ubicacion << " --> ";
        actual = actual->siguiente;
    }
    cout << endl;
}
void buscarubicacion(mapa *&lista_salas, string u) {
    bool band = false;
    mapa *actual = lista_salas;
    while ((actual != NULL) && (actual->ubicacion != u)) {
        actual = actual->siguiente;
    }
    if (actual != NULL) {
        band = true;
    }
    if (band) {
        cout << u << " ha sido encontrado en la lista\n";
    } else {
        cout << u << " no ha sido encontrado\n";
    }
    cout << endl;
}

void borrarubicacion(mapa *&lista_salas, string u) {
    if (lista_salas != NULL) {
        mapa *aux_borrar;
        mapa *anterior = NULL;
        aux_borrar = lista_salas;

        // Buscar el elemento en la lista
        while (aux_borrar != NULL && aux_borrar->ubicacion != u) {
            anterior = aux_borrar;
            aux_borrar = aux_borrar->siguiente;
        }
        
        if (aux_borrar == NULL) { // elemento no encontrado
            cout <<  u << "\" no existe en la lista.\n";
        } else if (anterior == NULL) { // elemento encontrado y es el primer nodo
            lista_salas = lista_salas->siguiente;
            delete aux_borrar;
            cout <<  u << " se ha eliminado con exito\n";
        } else { // está en la lista pero no es el primer nodo
            anterior->siguiente = aux_borrar->siguiente;
            delete aux_borrar;         
            cout <<  u << "\" se ha eliminado con exito\n";
        }
    } else {
        cout << "El mapa esta vacio.\n";
    }
    cout << endl;
}

void borrarmapa(mapa* &lista_salas, string &u) {
    if (lista_salas != NULL) {
        mapa *aux = lista_salas;
        u = aux->ubicacion; // guardamos la ubicacion en el auxiliar
        lista_salas = aux->siguiente;
        delete aux;
        cout << u << "\" ha sido eliminado de la lista.\n";
    }
    cout << endl;
}

int main()
{
    cout << "\n---------------------------------" << endl;
    cout << "--> ¡Bienvenido a Khazad-Dum! <--" << endl;
    cout << "---------------------------------" << endl << endl;

    // Menu agregar heroes
    int opcion;
    do 
    {
        cout<< "Que desea hacer?\n\n" 
        << "1. Elegir heroes\n"
        << "2. Salir\n\n" 
        << "Ingrese una opcion: " ;
        opcion = ObtenerEntero();
        switch (opcion) 
        {
            case 1: // Elige heroes restantes
                lista_heroes.agregarLider();
                agregarHeroes();
                break;
            case 2:
                cout << "Saliendo del programa\n\n";
                return 0;
            default:
                cout << "Opción inválida. Intente de nuevo.\n\n";
        }
    } while (opcion != 2 && lista_heroes.cantidad < 4);
    cout << endl;

    // Menu editar heroes
    cout << "\n# Los implementos aun no cambian las estadisticas de los heroes #\n";
    int opcion2;
    do {
        cout << endl;
        cout<< "Desea editar su equipo?\n\n"
            << "1. No, avanzar\n"
            << "2. Editar heroes\n\n"
            << "Ingrese una opcion: " ;
        opcion2 = ObtenerEntero();
        switch (opcion2)
        {
        case 1:
            cout << endl;
            break;
        case 2:
            int camb_opc;
            do 
            {
                cout<< "\n¿Que quiere cambiar? \n\n"
                << "1. Lista de heroes \n"
                << "2. Implementos de un heroe \n"
                << "3. Listo \n\n"
                << "Ingrese una opcion: " ;
                camb_opc = ObtenerEntero();
                switch (camb_opc)
                {
                    case 1: // Elimina y agrega a un heroe determinado 
                        lista_heroes.mostrarHeroes();
                        cout<< "\nElige el numero del heroe que desea eliminar" 
                            << "(Si no quiere eliminar a ninguno, ingrese 5): ";
                        int num;
                        cin >> num;
                        if (num == 5)
                        {
                            break;
                        }
                        else if (num == 1)
                        {
                            lista_heroes.eliminarHeroe(num);
                            lista_heroes.agregarLider();
                            break;
                        }
                        else
                        {
                            lista_heroes.eliminarHeroe(num);
                            agregarHeroes();
                            break;
                        }

                    case 2: // Elimina y reagrega implementos a un heroe determinado 
                        lista_heroes.eliminarImplemento();
                        break;

                    case 3:
                        cout << "Regresando...\n";
                        break;

                    default:
                        cout << "Opción inválida. Intente de nuevo.\n\n";
                    }
            } while(camb_opc != 3);
            break;
        default:
            cout << "Opción inválida. Intente de nuevo.\n\n\n";
            break;
        }
        
    } while (opcion2 != 1);

    menuMapa();

    cout << endl;

    MenuOrcos();
    
    return 0;
}
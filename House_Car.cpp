#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Dimensiones de la ventana
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

// Estructura para la casa
struct Casa {
    int x; // Origen en x
    int y; // Origen en y
    int altura;
    int ancho;
    float color[3]; // Color RGB
};

// Estructura para el carro
struct Carro {
    int x; // Origen en x
    int y; // Origen en y
    int largo;
    int alto;
    float color[3]; // Color RGB
};

// Función para dibujar un cuadrado
void drawSquare(int x, int y, int width, int height, const float color[3]) {
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + width, y);
    glVertex2i(x + width, y + height);
    glVertex2i(x, y + height);
    glEnd();
}

// Función para dibujar una casa
void crearCasa(const Casa &C) {
    drawSquare(C.x, C.y, C.ancho, C.altura, C.color);

    // Dibuja el techo de la casa
    float techoColor[3] = {C.color[0] * 0.8f, C.color[1] * 0.8f, C.color[2] * 0.8f}; // Un poco más oscuro
    glColor3f(techoColor[0], techoColor[1], techoColor[2]);
    glBegin(GL_TRIANGLES);
    glVertex2i(C.x, C.y + C.altura);
    glVertex2i(C.x + C.ancho / 2, C.y + C.altura + C.altura / 2);
    glVertex2i(C.x + C.ancho, C.y + C.altura);
    glEnd();
}

// Función para dibujar un carro
void crearCarro(const Carro &C) {
    drawSquare(C.x, C.y, C.largo, C.alto, C.color);

    // Dibuja las ruedas del carro en gris oscuro
    float wheelColor[3] = {0.3f, 0.3f, 0.3f}; // Gris oscuro
    drawSquare(C.x + C.largo / 4, C.y - C.alto / 4, C.alto / 2, C.alto / 2, wheelColor);
    drawSquare(C.x + (3 * C.largo) / 4 - C.alto / 2, C.y - C.alto / 4, C.alto / 2, C.alto / 2, wheelColor);

    // Dibuja las ventanas del carro en azul claro
    float windowColor[3] = {0.6f, 0.8f, 1.0f}; // Azul claro
    drawSquare(C.x + C.largo / 6, C.y + C.alto, C.largo / 4, C.alto / 2, windowColor);
    drawSquare(C.x + (C.largo / 2) - (C.largo / 12), C.y + C.alto, C.largo / 4, C.alto / 2, windowColor);
}

// Función para inicializar OpenGL
void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WIDTH, 0.0, HEIGHT, -1.0, 1.0);
}

// Función de renderizado
void render() {
    glClear(GL_COLOR_BUFFER_BIT);

    Casa casa = {100, 100, 100, 200, {0.5f, 0.3f, 0.1f}}; // Color marrón
    crearCasa(casa);

    Carro carro = {400, 100, 200, 50, {0.0f, 0.0f, 1.0f}}; // Color azul
    crearCarro(carro);

    glfwSwapBuffers(glfwGetCurrentContext());
}

int main() {
    // Inicializar GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Crear una ventana
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Casa y Carro", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Inicializar GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    initGL();

    // Bucle de renderizado
    while (!glfwWindowShouldClose(window)) {
        render();
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

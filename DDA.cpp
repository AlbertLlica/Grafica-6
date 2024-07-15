#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

// Dimensiones de la ventana
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

// Función para dibujar un píxel
void putPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Función para dibujar una línea usando el algoritmo DDA
void drawLineDDA(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xIncrement = dx / (float) steps;
    float yIncrement = dy / (float) steps;

    float x = x0;
    float y = y0;

    for (int i = 0; i <= steps; i++) {
        putPixel(round(x), round(y));
        x += xIncrement;
        y += yIncrement;
    }
}

// Función para inicializar OpenGL
void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WIDTH, 0.0, HEIGHT,-1,1);
}

// Función de renderizado
void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawLineDDA(100, 100, 700, 500);
    glfwSwapBuffers(glfwGetCurrentContext());
}

int main() {
    // Inicializar GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Crear una ventana
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "DDA Line Drawing", NULL, NULL);
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

//PF_1

/*

 gcc PF_1.c -o PF1 -lfreeglut -lopengl32 -lglu32
 Paso 1: inventar le personaje
 basado en la lamparita de pixar, dibujar una laptop que salte sobre la palabra ingeniería 
 letra por letra, tan cual, pero antes presentarse como la herramienta de trabajo mas necesiaria de un info JAJAJ
 ahora, despues de eso pues que haga los saltos se colocque en la íltima (I)
 aunque no se si tenga mucho sentio, o donde colocarla

 debo dibujarla con extremidades y articulaciones para que no se vea muy tieso todo


 u otra ocpion, que la computadora explique el sistema solar, asi aprovecho ese código como el escenario, y solo deberá moverse en el 

 */
#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265

//colores en un solo lado 
//si quiero cambiar algo directamente se cambai aqui
float COL_FONDO[] = {0.96, 0.96, 0.96};
float COL_MARCO[] = {0.12, 0.12, 0.12};
float COL_PANTALLA[] = {0.45, 0.84, 0.98};
float COL_TECLADO[] = {0.17, 0.22, 0.26};
float COL_BRAZO[] = {0.23, 0.28, 0.31};
float COL_MEJILLA[] = {1.0, 0.64, 0.74};

//uso de variables que se pueden modificar para las animaciones 
float ang_hombro_izq = -135.0;
float ang_codo_izq = 20.0;
float ang_hombro_der = -45.0;
float ang_codo_der = -20.0;

void dibujarCirculo(float cx, float cy, float r, int segmentos) 
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segmentos; i++) 
    {
        float theta = 2.0 * PI * i / segmentos;
        glVertex2f(cx + r * cos(theta), cy + r * sin(theta));
    }
    glEnd();
}

void dibujarRectangulo(float x, float y, float w, float h) 
{
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

void dibujarRectanguloRedondeado(float x, float y, float w, float h, float radio)
 {
    int segmentos = 20;
    glBegin(GL_POLYGON);
    
    float cx[4] = {x + radio, x + w - radio, x + w - radio, x + radio};
    float cy[4] = {y + radio, y + radio, y + h - radio, y + h - radio};
    float angulo_inicio[4] = {180.0, 270.0, 0.0, 90.0};
    
    for (int esquina = 0; esquina < 4; esquina++) {
        for (int i = 0; i <= segmentos; i++) {
            float angulo = (angulo_inicio[esquina] + i * 90.0 / segmentos) * PI / 180.0;
            glVertex2f(cx[esquina] + cos(angulo) * radio, 
                      cy[esquina] + sin(angulo) * radio);
        }
    }
    glEnd();
}

//funcionesmodulares

void dibujarPantalla() 
{
    // Borde
    glColor3fv(COL_MARCO);
    dibujarRectanguloRedondeado(-2.0, 0.6, 4.0, 2.4, 0.1);
    // Interior
    glColor3f(0.07, 0.07, 0.07);
    dibujarRectangulo(-1.85, 0.75, 3.7, 2.2);
    // Pantalla 
    glColor3fv(COL_PANTALLA);
    dibujarRectangulo(-1.7, 0.85, 3.4, 1.95);
}

void dibujarCara() 
{
    float ojo_y = 2.25;
    float ojo_x = 0.65;
    
    // Ojos
    glColor3f(1.0, 1.0, 1.0);
    dibujarCirculo(-ojo_x, ojo_y, 0.25, 24);
    dibujarCirculo(ojo_x, ojo_y, 0.25, 24);
    // Pupilas
    glColor3f(0.08, 0.08, 0.1);
    dibujarCirculo(-ojo_x, ojo_y - 0.02, 0.12, 24);
    dibujarCirculo(ojo_x, ojo_y - 0.02, 0.12, 24);
    // Brillo
    glColor3f(1.0, 1.0, 1.0);
    dibujarCirculo(-ojo_x + 0.07, ojo_y + 0.10, 0.05, 12);
    dibujarCirculo(ojo_x + 0.07, ojo_y + 0.10, 0.05, 12);
    // cachetes
    glColor3fv(COL_MEJILLA);
    dibujarCirculo(-1.05, ojo_y - 0.08, 0.14, 20);
    dibujarCirculo(1.05, ojo_y - 0.08, 0.14, 20);
    // Boca
    glColor3f(0.12, 0.16, 0.2);
    glLineWidth(3.0);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 20; i++) 
    {
        float t = (float)i / 20.0;
        float x = -0.35 + t * 0.7;
        float y = 1.75 - 0.12 * sin(t * PI);
        glVertex2f(x, y);
    }
    glEnd();
    glLineWidth(1.0);
}

//se podrá agregar textura depsues?
void dibujarTeclado() 
{
    float x = -2.15, y = -0.05;
    float w = 4.3, h = 0.75;
    
    glColor3fv(COL_TECLADO);
    dibujarRectanguloRedondeado(x, y, w, h, 0.08);
    
    glColor3f(0.24, 0.29, 0.32);
    float ix = x + 0.15, iy = y + 0.06;
    float iw = w - 0.3, ih = h - 0.12;
    dibujarRectangulo(ix, iy, iw, ih);
    
    // lineas que separan las teclas dando la visión del teclado
    glColor3f(0.2, 0.25, 0.28);
    glLineWidth(1.0);
    for (int c = 0; c <= 13; c++) 
    {
        float vx = ix + c * (iw / 13.0);
        glBegin(GL_LINES);
        glVertex2f(vx, iy);
        glVertex2f(vx, iy + ih);
        glEnd();
    }
    for (int r = 0; r <= 4; r++) {
        float vy = iy + r * (ih / 4.0);
        glBegin(GL_LINES);
        glVertex2f(ix, vy);
        glVertex2f(ix + iw, vy);
        glEnd();
    }
}

void dibujarBrazo(int lado) 
{
    float ox = (lado == -1) ? -1.95 : 1.95;
    float oy = 0.28;
    float ang_h = (lado == -1) ? ang_hombro_izq : ang_hombro_der;
    float ang_c = (lado == -1) ? ang_codo_izq : ang_codo_der;
    
    glPushMatrix();
    glTranslatef(ox, oy, 0.0);
    glRotatef(ang_h, 0.0, 0.0, 1.0);
    // Brazo superior
    glColor3fv(COL_BRAZO);
    dibujarRectangulo(0.0, -0.06, 0.72, 0.12);
    // Codo
    glColor3f(0.2, 0.25, 0.28);
    dibujarCirculo(0.72, 0.0, 0.12, 24);
    glColor3f(0.39, 0.45, 0.48);
    dibujarCirculo(0.72, 0.0, 0.06, 16);
    glTranslatef(0.72, 0.0, 0.0);
    glRotatef(ang_c, 0.0, 0.0, 1.0);
    // segunda parte del brazo
    glColor3fv(COL_BRAZO);
    dibujarRectangulo(0.0, -0.06, 0.68, 0.12);
    // Mano
    glColor3f(0.2, 0.25, 0.28);
    dibujarCirculo(0.82, 0.0, 0.20, 28);
    
    glPopMatrix();
}

void dibujarPierna(float px)
 {
    glColor3fv(COL_BRAZO);
    dibujarRectangulo(px - 0.05, -0.1, 0.1, -0.85);
    
    glColor3f(0.2, 0.25, 0.28);
    dibujarCirculo(px, -0.95, 0.13, 20);
    glColor3f(0.42, 0.48, 0.5);
    dibujarCirculo(px, -0.95, 0.06, 16);
    
    glColor3fv(COL_BRAZO);
    dibujarRectangulo(px - 0.05, -0.95, 0.1, -0.45);
    
    glColor3f(0.15, 0.18, 0.22);
    dibujarRectangulo(px - 0.35, -1.58, 0.7, 0.25);
}

void dibujarCuerpo() 
{
    glColor3fv(COL_MARCO);
    dibujarRectanguloRedondeado(-2.35, -0.15, 4.7, 1.05, 0.12);
    
    glColor3fv(COL_TECLADO);
    dibujarRectangulo(-2.2, -0.05, 4.4, 0.9);
    
    glColor3f(0.27, 0.31, 0.34);
    dibujarRectangulo(-2.2, -0.2, 4.4, 0.12);
}

//iniciar display
void display(void) 
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    dibujarCuerpo();
    dibujarPantalla();
    dibujarCara();
    dibujarTeclado();
    dibujarBrazo(-1);
    dibujarBrazo(1);
    dibujarPierna(-0.9);
    dibujarPierna(0.9);
    
    // Hombros
    glColor3f(0.2, 0.25, 0.28);
    dibujarCirculo(-1.05, 0.32, 0.12, 24);
    dibujarCirculo(1.05, 0.32, 0.12, 24);
    // Borde
    glColor3f(0.07, 0.07, 0.07);
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-2.25, -0.15);
    glVertex2f(2.25, -0.15);
    glVertex2f(2.25, 0.9);
    glVertex2f(-2.25, 0.9);
    glEnd();
    glLineWidth(1.0);
    
    glFlush();
}

void init(void)
 {
    glClearColor(COL_FONDO[0], COL_FONDO[1], COL_FONDO[2], 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-4.0, 4.0, -2.5, 3.5);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(960, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("MI PERSONAJE");
    
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
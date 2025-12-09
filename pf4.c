// gcc sistema_solar_laptop.c -o solar -lfreeglut -lopengl32 -lglu32
#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265
#define NUM_ASTEROIDES 200

// ============================================================
// VARIABLES DEL SISTEMA SOLAR COMPLETO
// ============================================================
float sun_ambient[] = {0.0, 0.2, 0.0, 1.0};
float sun_diffuse_specular[] = {1.0, 0.9, 0.5, 1.0};
float sun_pos[] = {0.0, 0.0, 0.0, 1.0};
float spot_dir[] = {0.0, 0.0, -1.0};
float spot_cutoff = 360.0;
float spot_exponent = 0.1;
float mat_ambient_diffuse[] = {1.0, 1.0, 1.0, 1.0};
float mat_specular[] = {0.0, 0.0, 0.0, 1.0};
float mat_emission[] = {0.0, 0.0, 1.0, 1.0};
float mat_shininess = 0.1;
float focus_emission[] = {0.8, 0.8, 0.8, 1.0};

float zoom = -18.0;
float inc = 80.0;
float seconds_per_day = 0.5;

// Tamaños planetas
float sol_tamanio = 0.6;
float mercurio_tamanio = 0.08;
float venus_tamanio = 0.15;
float tierra_tamanio = 0.16;
float marte_tamanio = 0.12;
float jupiter_tamanio = 0.45;
float saturno_tamanio = 0.38;
float urano_tamanio = 0.25;
float neptuno_tamanio = 0.24;

// Distancias orbitales
float mercurio_dist_orbita = 1.2;
float venus_dist_orbita = 1.8;
float tierra_dist_orbita = 2.5;
float marte_dist_orbita = 3.2;
float jupiter_dist_orbita = 5.5;
float saturno_dist_orbita = 7.0;
float urano_dist_orbita = 8.5;
float neptuno_dist_orbita = 10.0;

// Periodos orbitales
float mercurio_periodo_orbital = 88.0;
float venus_periodo_orbital = 225.0;
float tierra_periodo_orbital = 365.0;
float marte_periodo_orbital = 687.0;
float jupiter_periodo_orbital = 4333.0;
float saturno_periodo_orbital = 10759.0;
float urano_periodo_orbital = 30687.0;
float neptuno_periodo_orbital = 60190.0;

// Periodos de rotación
float mercurio_periodo_rotacion = 1407.6;
float venus_periodo_rotacion = 5832.5;
float tierra_periodo_rotacion = 24.0;
float marte_periodo_rotacion = 24.6;
float jupiter_periodo_rotacion = 9.9;
float saturno_periodo_rotacion = 10.7;
float urano_periodo_rotacion = 17.2;
float neptuno_periodo_rotacion = 16.1;

// Lunas
float luna_tamanio = 0.05;
float luna_dist_orbita = 0.25;
float luna_periodo_orbital = 27.3;

float fobos_tamanio = 0.02;
float fobos_dist_orbita = 0.18;
float fobos_periodo_orbital = 0.32;
float deimos_tamanio = 0.015;
float deimos_dist_orbita = 0.25;
float deimos_periodo_orbital = 1.26;

float io_tamanio = 0.055;
float io_dist_orbita = 0.65;
float io_periodo_orbital = 1.77;
float europa_tamanio = 0.05;
float europa_dist_orbita = 0.82;
float europa_periodo_orbital = 3.55;
float ganimedes_tamanio = 0.065;
float ganimedes_dist_orbita = 1.0;
float ganimedes_periodo_orbital = 7.15;
float calisto_tamanio = 0.06;
float calisto_dist_orbita = 1.3;
float calisto_periodo_orbital = 16.69;

float titan_tamanio = 0.065;
float titan_dist_orbita = 1.0;
float titan_periodo_orbital = 15.95;
float rea_tamanio = 0.035;
float rea_dist_orbita = 0.7;
float rea_periodo_orbital = 4.52;

float titania_tamanio = 0.04;
float titania_dist_orbita = 0.6;
float titania_periodo_orbital = 8.71;
float oberon_tamanio = 0.038;
float oberon_dist_orbita = 0.75;
float oberon_periodo_orbital = 13.46;

float triton_tamanio = 0.045;
float triton_dist_orbita = 0.5;
float triton_periodo_orbital = 5.88;

float saturno_anillo_radio_interno = 0.5;
float saturno_anillo_radio_externo = 0.8;

float cinturon_radio_interno = 3.8;
float cinturon_radio_externo = 4.8;

typedef struct {
    float angulo;
    float radio;
    float tamanio;
    float velocidad;
} Asteroide;
Asteroide asteroides[NUM_ASTEROIDES];

// ============================================================
// VARIABLES DE LA LAPTOP (HUD)
// ============================================================
float laptop_pos_x = 0.85;
float laptop_pos_y = 0.80;
float laptop_escala = 0.04;

float ang_hombro_izq = -135.0;
float ang_codo_izq = 20.0;
float ang_hombro_der = -45.0;
float ang_codo_der = -20.0;

float COL_MARCO[] = {0.12, 0.12, 0.12};
float COL_PANTALLA[] = {0.45, 0.84, 0.98};
float COL_TECLADO[] = {0.17, 0.22, 0.26};
float COL_BRAZO[] = {0.23, 0.28, 0.31};
float COL_MEJILLA[] = {1.0, 0.64, 0.74};

// ============================================================
// DECLARACIONES DE FUNCIONES
// ============================================================
void dibujarLaptop3D(void);
void DibujarOrbita(float radio, int segmentos);
void DibujarAnilloSaturno(float radio_interno, float radio_externo, float ang_rot);
void DibujarLunaGenerica(float tamanio, float dist_orbita, float periodo_orbital, 
                         float dias_simulados, float r, float g, float b);
void DibujarLuna(float dias_simulados);
void DibujarSol(void);
void DibujarMercurio(float dias_simulados);
void DibujarVenus(float dias_simulados);
void DibujarTierra(float dias_simulados);
void DibujarMarte(float dias_simulados);
void DibujarJupiter(float dias_simulados);
void DibujarSaturno(float dias_simulados);
void DibujarUrano(float dias_simulados);
void DibujarNeptuno(float dias_simulados);
void DibujarCinturonAsteroides(float dias_simulados);
void cubo3D(float w, float h, float d);
void cilindro3D(float radio, float altura, int segs);

// ============================================================
// FUNCIONES DEL SISTEMA SOLAR
// ============================================================
void DibujarOrbita(float radio, int segmentos) {
    glDisable(GL_LIGHTING);
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < segmentos; i++) {
        float angulo = 2.0 * M_PI * i / segmentos;
        float x = radio * cos(angulo);
        float z = radio * sin(angulo);
        glVertex3f(x, 0.0, z);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void DibujarAnilloSaturno(float radio_interno, float radio_externo, float ang_rot) {
    glPushMatrix();
        glRotatef(ang_rot, 0.0, 1.0, 0.0);
        glRotatef(25.0, 1.0, 0.0, 0.0);
        
        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.8, 0.7, 0.5, 0.6);
        
        int segmentos = 100;
        glBegin(GL_QUAD_STRIP);
        for(int i = 0; i <= segmentos; i++) {
            float angulo = 2.0 * M_PI * i / segmentos;
            float x_interno = radio_interno * cos(angulo);
            float z_interno = radio_interno * sin(angulo);
            float x_externo = radio_externo * cos(angulo);
            float z_externo = radio_externo * sin(angulo);
            
            glVertex3f(x_interno, 0.0, z_interno);
            glVertex3f(x_externo, 0.0, z_externo);
        }
        glEnd();
        
        glDisable(GL_BLEND);
        glEnable(GL_LIGHTING);
    glPopMatrix();
}

void DibujarLunaGenerica(float tamanio, float dist_orbita, float periodo_orbital, 
                         float dias_simulados, float r, float g, float b) {
    float ang_tras = fmod(360.0 * (dias_simulados / periodo_orbital), 360.0);
    
    glPushMatrix();
        glRotatef(ang_tras, 0.0, 1.0, 0.0);
        glTranslatef(dist_orbita, 0.0, 0.0);
        glRotatef(ang_tras, 0.0, 1.0, 0.0);
        
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(r, g, b);
        glutSolidSphere(tamanio, 15, 12);
        glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
}

void DibujarLuna(float dias_simulados) {
    float luna_ang_tras = fmod(360.0 * (dias_simulados / luna_periodo_orbital), 360.0);
    
    glPushMatrix();
        glRotatef(luna_ang_tras, 0.0, 1.0, 0.0);
        glTranslatef(luna_dist_orbita, 0.0, 0.0);
        glRotatef(luna_ang_tras, 0.0, 1.0, 0.0);
        
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(0.7, 0.7, 0.7);
        glutSolidSphere(luna_tamanio, 20, 15);
        glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
}

void DibujarSol(void) {
    glPushMatrix();
        glLightfv(GL_LIGHT0, GL_POSITION, sun_pos);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_dir);
        glTranslatef(sun_pos[0], sun_pos[1], sun_pos[2]);
        
        glColorMaterial(GL_FRONT, GL_EMISSION);
        glEnable(GL_COLOR_MATERIAL);
        glColor4fv(focus_emission);
        glColor3f(1.0, 0.0, 0.0);
        glutSolidSphere(sol_tamanio, 30, 20);
        glColor4fv(mat_emission);
        glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
}

void DibujarMercurio(float dias_simulados) {
    glPushMatrix();
        float ang_tras = fmod(360.0 * (dias_simulados / mercurio_periodo_orbital), 360.0);
        float ang_rot = fmod(360.0 * (dias_simulados / (mercurio_periodo_rotacion / 24.0)), 360.0);
        
        glRotatef(ang_tras, 0.0, 1.0, 0.0);
        glTranslatef(mercurio_dist_orbita, 0.0, 0.0);
        glRotatef(ang_rot, 0.0, 1.0, 0.0);
        
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(0.5, 0.5, 0.5);
        glutSolidSphere(mercurio_tamanio, 20, 15);
        glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
}

void DibujarVenus(float dias_simulados) {
    glPushMatrix();
        float ang_tras = fmod(360.0 * (dias_simulados / venus_periodo_orbital), 360.0);
        float ang_rot = fmod(360.0 * (dias_simulados / (venus_periodo_rotacion / 24.0)), 360.0);
        
        glRotatef(ang_tras, 0.0, 1.0, 0.0);
        glTranslatef(venus_dist_orbita, 0.0, 0.0);
        glRotatef(ang_rot, 0.0, 1.0, 0.0);
        
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(0.9, 0.7, 0.3);
        glutSolidSphere(venus_tamanio, 25, 20);
        glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
}

void DibujarTierra(float dias_simulados) {
    glPushMatrix();
        float ang_tras = fmod(360.0 * (dias_simulados / tierra_periodo_orbital), 360.0);
        float ang_rot = fmod(360.0 * (dias_simulados / (tierra_periodo_rotacion / 24.0)), 360.0);
        
        glRotatef(ang_tras, 0.0, 1.0, 0.0);
        glTranslatef(tierra_dist_orbita, 0.0, 0.0);
        
        glPushMatrix();
            glRotatef(ang_rot, 0.0, 1.0, 0.0);
            glEnable(GL_COLOR_MATERIAL);
            glColor3f(0.0, 0.3, 0.8);
            glutSolidSphere(tierra_tamanio, 30, 20);
            glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();
        
        DibujarLuna(dias_simulados);
    glPopMatrix();
}

void DibujarMarte(float dias_simulados) {
    glPushMatrix();
        float ang_tras = fmod(360.0 * (dias_simulados / marte_periodo_orbital), 360.0);
        float ang_rot = fmod(360.0 * (dias_simulados / (marte_periodo_rotacion / 24.0)), 360.0);
        
        glRotatef(ang_tras, 0.0, 1.0, 0.0);
        glTranslatef(marte_dist_orbita, 0.0, 0.0);
        
        glPushMatrix();
            glRotatef(ang_rot, 0.0, 1.0, 0.0);
            glEnable(GL_COLOR_MATERIAL);
            glColor3f(0.8, 0.3, 0.1);
            glutSolidSphere(marte_tamanio, 25, 20);
            glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();
        
        DibujarLunaGenerica(fobos_tamanio, fobos_dist_orbita, fobos_periodo_orbital, 
                           dias_simulados, 0.6, 0.6, 0.5);
        DibujarLunaGenerica(deimos_tamanio, deimos_dist_orbita, deimos_periodo_orbital, 
                           dias_simulados, 0.65, 0.65, 0.55);
    glPopMatrix();
}

void DibujarJupiter(float dias_simulados) {
    glPushMatrix();
        float ang_tras = fmod(360.0 * (dias_simulados / jupiter_periodo_orbital), 360.0);
        float ang_rot = fmod(360.0 * (dias_simulados / (jupiter_periodo_rotacion / 24.0)), 360.0);
        
        glRotatef(ang_tras, 0.0, 1.0, 0.0);
        glTranslatef(jupiter_dist_orbita, 0.0, 0.0);
        
        glPushMatrix();
            glRotatef(ang_rot, 0.0, 1.0, 0.0);
            glEnable(GL_COLOR_MATERIAL);
            glColor3f(0.8, 0.6, 0.4);
            glutSolidSphere(jupiter_tamanio, 35, 25);
            glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();
        
        DibujarLunaGenerica(io_tamanio, io_dist_orbita, io_periodo_orbital, 
                           dias_simulados, 0.9, 0.8, 0.3);
        DibujarLunaGenerica(europa_tamanio, europa_dist_orbita, europa_periodo_orbital, 
                           dias_simulados, 0.8, 0.8, 0.7);
        DibujarLunaGenerica(ganimedes_tamanio, ganimedes_dist_orbita, ganimedes_periodo_orbital, 
                           dias_simulados, 0.6, 0.6, 0.5);
        DibujarLunaGenerica(calisto_tamanio, calisto_dist_orbita, calisto_periodo_orbital, 
                           dias_simulados, 0.5, 0.4, 0.4);
    glPopMatrix();
}

void DibujarSaturno(float dias_simulados) {
    glPushMatrix();
        float ang_tras = fmod(360.0 * (dias_simulados / saturno_periodo_orbital), 360.0);
        float ang_rot = fmod(360.0 * (dias_simulados / (saturno_periodo_rotacion / 24.0)), 360.0);
        
        glRotatef(ang_tras, 0.0, 1.0, 0.0);
        glTranslatef(saturno_dist_orbita, 0.0, 0.0);
        
        glPushMatrix();
            glRotatef(ang_rot, 0.0, 1.0, 0.0);
            glEnable(GL_COLOR_MATERIAL);
            glColor3f(0.9, 0.8, 0.5);
            glutSolidSphere(saturno_tamanio, 35, 25);
            glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();
        
        DibujarAnilloSaturno(saturno_anillo_radio_interno, saturno_anillo_radio_externo, ang_rot);
        
        DibujarLunaGenerica(titan_tamanio, titan_dist_orbita, titan_periodo_orbital, 
                           dias_simulados, 0.8, 0.7, 0.5);
        DibujarLunaGenerica(rea_tamanio, rea_dist_orbita, rea_periodo_orbital, 
                           dias_simulados, 0.7, 0.7, 0.7);
    glPopMatrix();
}

void DibujarUrano(float dias_simulados) {
    glPushMatrix();
        float ang_tras = fmod(360.0 * (dias_simulados / urano_periodo_orbital), 360.0);
        float ang_rot = fmod(360.0 * (dias_simulados / (urano_periodo_rotacion / 24.0)), 360.0);
        
        glRotatef(ang_tras, 0.0, 1.0, 0.0);
        glTranslatef(urano_dist_orbita, 0.0, 0.0);
        
        glPushMatrix();
            glRotatef(ang_rot, 0.0, 1.0, 0.0);
            glEnable(GL_COLOR_MATERIAL);
            glColor3f(0.5, 0.8, 0.9);
            glutSolidSphere(urano_tamanio, 30, 22);
            glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();
        
        DibujarLunaGenerica(titania_tamanio, titania_dist_orbita, titania_periodo_orbital, 
                           dias_simulados, 0.75, 0.75, 0.7);
        DibujarLunaGenerica(oberon_tamanio, oberon_dist_orbita, oberon_periodo_orbital, 
                           dias_simulados, 0.7, 0.7, 0.65);
    glPopMatrix();
}

void DibujarNeptuno(float dias_simulados) {
    glPushMatrix();
        float ang_tras = fmod(360.0 * (dias_simulados / neptuno_periodo_orbital), 360.0);
        float ang_rot = fmod(360.0 * (dias_simulados / (neptuno_periodo_rotacion / 24.0)), 360.0);
        
        glRotatef(ang_tras, 0.0, 1.0, 0.0);
        glTranslatef(neptuno_dist_orbita, 0.0, 0.0);
        
        glPushMatrix();
            glRotatef(ang_rot, 0.0, 1.0, 0.0);
            glEnable(GL_COLOR_MATERIAL);
            glColor3f(0.2, 0.3, 0.8);
            glutSolidSphere(neptuno_tamanio, 30, 22);
            glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();
        
        DibujarLunaGenerica(triton_tamanio, triton_dist_orbita, triton_periodo_orbital, 
                           dias_simulados, 0.8, 0.75, 0.7);
    glPopMatrix();
}

void DibujarCinturonAsteroides(float dias_simulados) {
    glPushMatrix();
    for(int i = 0; i < NUM_ASTEROIDES; i++) {
        float periodo_asteroide = 1500.0 + (asteroides[i].velocidad * 500.0);
        float angulo_actual = fmod(asteroides[i].angulo + 
                                  (360.0 * dias_simulados / periodo_asteroide), 360.0);
        
        glPushMatrix();
            glRotatef(angulo_actual, 0.0, 1.0, 0.0);
            glTranslatef(asteroides[i].radio, 0.0, 0.0);
            
            glEnable(GL_COLOR_MATERIAL);
            glColor3f(0.5, 0.4, 0.3);
            glutSolidSphere(asteroides[i].tamanio, 6, 6);
            glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();
    }
    glPopMatrix();
}

// ============================================================
// FUNCIONES PARA DIBUJAR LA LAPTOP 3D (HUD)
// ============================================================
void cubo3D(float w, float h, float d) {
    glBegin(GL_QUADS);
    float x = w/2, y = h/2, z = d/2;
    glVertex3f(-x,-y,z); glVertex3f(x,-y,z); glVertex3f(x,y,z); glVertex3f(-x,y,z);
    glVertex3f(-x,-y,-z); glVertex3f(-x,y,-z); glVertex3f(x,y,-z); glVertex3f(x,-y,-z);
    glVertex3f(-x,y,-z); glVertex3f(-x,y,z); glVertex3f(x,y,z); glVertex3f(x,y,-z);
    glVertex3f(-x,-y,-z); glVertex3f(x,-y,-z); glVertex3f(x,-y,z); glVertex3f(-x,-y,z);
    glVertex3f(x,-y,-z); glVertex3f(x,y,-z); glVertex3f(x,y,z); glVertex3f(x,-y,z);
    glVertex3f(-x,-y,-z); glVertex3f(-x,-y,z); glVertex3f(-x,y,z); glVertex3f(-x,y,-z);
    glEnd();
}

void cilindro3D(float radio, float altura, int segs) {
    glBegin(GL_QUAD_STRIP);
    for(int i = 0; i <= segs; i++) {
        float ang = 2.0 * PI * i / segs;
        float x = radio * cos(ang);
        float z = radio * sin(ang);
        glVertex3f(x, 0, z);
        glVertex3f(x, altura, z);
    }
    glEnd();
}

void dibujarLaptop3D(void) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    glPushMatrix();
        glTranslatef(laptop_pos_x, laptop_pos_y, 0.0);
        glScalef(laptop_escala, laptop_escala, laptop_escala);
        
        glColor3fv(COL_MARCO);
        cubo3D(4.3, 0.3, 2.3);
        
        glColor3fv(COL_TECLADO);
        glPushMatrix();
            glTranslatef(0.0, 0.18, 0.0);
            cubo3D(4.0, 0.08, 2.1);
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0.0, 1.5, -0.95);
            glRotatef(-12.0, 1.0, 0.0, 0.0);
            
            glColor3fv(COL_MARCO);
            cubo3D(4.0, 2.6, 0.18);
            
            glColor3fv(COL_PANTALLA);
            glPushMatrix();
                glTranslatef(0.0, 0.0, 0.11);
                cubo3D(3.7, 2.3, 0.05);
            glPopMatrix();
            
            glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
                glTranslatef(-0.6, 0.3, 0.14);
                glutSolidSphere(0.24, 16, 16);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.6, 0.3, 0.14);
                glutSolidSphere(0.24, 16, 16);
            glPopMatrix();
            
            glColor3f(0.08, 0.08, 0.1);
            glPushMatrix();
                glTranslatef(-0.6, 0.28, 0.17);
                glutSolidSphere(0.11, 16, 16);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.6, 0.28, 0.17);
                glutSolidSphere(0.11, 16, 16);
            glPopMatrix();
            
            glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
                glTranslatef(-0.53, 0.35, 0.19);
                glutSolidSphere(0.05, 12, 12);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.67, 0.35, 0.19);
                glutSolidSphere(0.05, 12, 12);
            glPopMatrix();
            
            glColor3fv(COL_MEJILLA);
            glPushMatrix();
                glTranslatef(-1.0, 0.22, 0.14);
                glutSolidSphere(0.13, 16, 16);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(1.0, 0.22, 0.14);
                glutSolidSphere(0.13, 16, 16);
            glPopMatrix();
            
            glColor3f(0.12, 0.16, 0.2);
            for(int i = 0; i <= 10; i++) {
                float t = (float)i / 10.0;
                float x = -0.35 + t * 0.7;
                float y = -0.28 - 0.12 * sin(t * PI);
                glPushMatrix();
                    glTranslatef(x, y, 0.15);
                    glutSolidSphere(0.035, 8, 8);
                glPopMatrix();
            }
        glPopMatrix();
        
        glColor3fv(COL_BRAZO);
        glPushMatrix();
            glTranslatef(-2.0, 0.28, 0.0);
            glRotatef(ang_hombro_izq, 0.0, 0.0, 1.0);
            glutSolidSphere(0.12, 12, 12);
            glPushMatrix();
                glTranslatef(0.36, 0.0, 0.0);
                glRotatef(90, 0, 1, 0);
                cilindro3D(0.07, 0.72, 12);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.72, 0.0, 0.0);
                glRotatef(ang_codo_izq, 0.0, 0.0, 1.0);
                glColor3f(0.2, 0.25, 0.28);
                glutSolidSphere(0.10, 12, 12);
                glColor3fv(COL_BRAZO);
                glPushMatrix();
                    glTranslatef(0.34, 0.0, 0.0);
                    glRotatef(90, 0, 1, 0);
                    cilindro3D(0.06, 0.68, 12);
                glPopMatrix();
                glPushMatrix();
                    glTranslatef(0.82, 0.0, 0.0);
                    glColor3f(0.2, 0.23, 0.26);
                    glutSolidSphere(0.18, 12, 12);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        
        glColor3fv(COL_BRAZO);
        glPushMatrix();
            glTranslatef(2.0, 0.28, 0.0);
            glRotatef(ang_hombro_der, 0.0, 0.0, 1.0);
            glutSolidSphere(0.12, 12, 12);
            glPushMatrix();
                glTranslatef(0.36, 0.0, 0.0);
                glRotatef(90, 0, 1, 0);
                cilindro3D(0.07, 0.72, 12);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.72, 0.0, 0.0);
                glRotatef(ang_codo_der, 0.0, 0.0, 1.0);
                glColor3f(0.2, 0.25, 0.28);
                glutSolidSphere(0.10, 12, 12);
                glColor3fv(COL_BRAZO);
                glPushMatrix();
                    glTranslatef(0.34, 0.0, 0.0);
                    glRotatef(90, 0, 1, 0);
                    cilindro3D(0.06, 0.68, 12);
                glPopMatrix();
                glPushMatrix();
                    glTranslatef(0.82, 0.0, 0.0);
                    glColor3f(0.2, 0.23, 0.26);
                    glutSolidSphere(0.18, 12, 12);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        
        glColor3fv(COL_BRAZO);
        glPushMatrix();
            glTranslatef(-0.85, -0.15, 0.0);
            glRotatef(90, 1, 0, 0);
            cilindro3D(0.08, 1.1, 12);
            glTranslatef(0.0, 0.0, 1.1);
            glColor3f(0.18, 0.21, 0.24);
            glutSolidSphere(0.13, 12, 12);
        glPopMatrix();
        
        glColor3fv(COL_BRAZO);
        glPushMatrix();
            glTranslatef(0.85, -0.15, 0.0);
            glRotatef(90, 1, 0, 0);
            cilindro3D(0.08, 1.1, 12);
            glTranslatef(0.0, 0.0, 1.1);
            glColor3f(0.18, 0.21, 0.24);
            glutSolidSphere(0.13, 12, 12);
        glPopMatrix();
        
    glPopMatrix();
    
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    
        int ms = glutGet(GLUT_ELAPSED_TIME);
        float dias_simulados = (float)ms / 1000.0 / seconds_per_day;
        
        DibujarSol();
        DibujarOrbita(mercurio_dist_orbita, 100);
        DibujarOrbita(venus_dist_orbita, 100);
        DibujarOrbita(tierra_dist_orbita, 100);
        DibujarOrbita(marte_dist_orbita, 100);
        DibujarOrbita(jupiter_dist_orbita, 120);
        DibujarOrbita(saturno_dist_orbita, 120);
        DibujarOrbita(urano_dist_orbita, 120);
        DibujarOrbita(neptuno_dist_orbita, 120);
        
        DibujarMercurio(dias_simulados);
        DibujarVenus(dias_simulados);
        DibujarTierra(dias_simulados);
        DibujarMarte(dias_simulados);
        DibujarCinturonAsteroides(dias_simulados);
        DibujarJupiter(dias_simulados);
        DibujarSaturno(dias_simulados);
        DibujarUrano(dias_simulados);
        DibujarNeptuno(dias_simulados);
        
    glPopMatrix();
    
    dibujarLaptop3D();
    
    glFlush();
    glutSwapBuffers();
}

void redibujo(void) {
    glutPostRedisplay();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / (float)h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, aspect, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, zoom);
    glRotatef(inc, 1.0, 0.0, 0.0);
}

void iniciogl() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, sun_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_diffuse_specular);
    glLightfv(GL_LIGHT0, GL_SPECULAR, sun_diffuse_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, sun_pos);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
    glEnable(GL_LIGHT0);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
    
    float ancho_cinturon = cinturon_radio_externo - cinturon_radio_interno;
    for(int i = 0; i < NUM_ASTEROIDES; i++) {
        asteroides[i].angulo = (360.0 * i) / NUM_ASTEROIDES;
        float factor = (i % 10) / 10.0;
        asteroides[i].radio = cinturon_radio_interno + (factor * ancho_cinturon);
        asteroides[i].tamanio = 0.01 + (i % 5) * 0.006;
        asteroides[i].velocidad = 0.5 + (i % 8) * 0.2;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(30, 30);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Sistema Solar Completo con Laptop Presentadora");
    iniciogl();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(redibujo);
    glutMainLoop();
    return 0;
};
#include "Coordinador.h"
#include "freeglut.h"

Coordinador c; //Todo el codigo esta gestionado por el coordinador

//los callback, funciones que seran llamadas automaticamente por la glut
//cuando sucedan eventos
//NO HACE FALTA LLAMARLAS EXPLICITAMENTE
void OnDraw(void); //esta funcion sera llamada para dibujar
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	
void OnSpecialKeyboardDown(int key, int x, int y); //cuando se pulse una tecla	
void Mouse(int, int, int, int);
void Motion(int x, int y);

int main(int argc,char* argv[])
{
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(900, 700);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("TheyCMeRollin");

	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);	
	glMatrixMode(GL_PROJECTION);
	gluPerspective( 40.0, 900.0f/700.0f, 0.1, 100);

	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutTimerFunc(25,OnTimer,0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);
	glutSpecialFunc(OnSpecialKeyboardDown);

	c.inicializa();
		
	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();	

	return 0;   
}

void OnDraw(void)
{
	//Borrado de la pantalla	
   	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	c.dibuja();

	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	//poner aqui el código de teclado
	c.teclas(key);

	glutPostRedisplay();
}
void OnSpecialKeyboardDown(int key, int x, int y)
{
	c.teclasespeciales(key);
}
void Mouse(int button, int state, int x, int y)
{
	c.mouse(button, x, y, state);
}

void Motion(int x, int y)
{
	c.motion(x, y);

	glutPostRedisplay();
}

void OnTimer(int value)
{
	//poner aqui el código de animacion
	c.mueve();

	//no borrar estas lineas
	glutTimerFunc(25, OnTimer, 0);
	glutPostRedisplay();
}
#include<GL/glut.h>
#include<math.h>
//#include<GL/RGBPixMap.h>


#define PI 3.1415927


//int framenumber = 0;
//jim
GLint startrot = 0;
GLint startwalk1 = 0;
GLint startwalk2 = 0;
GLint startarm = 0;
GLint navigate = 0;

//radar
GLfloat anim = 0.0;
//speedometer
GLfloat spd = -40.0;
//rudder
GLfloat rud = 0.0;
//movement of officer jim
GLfloat jimX = 0.0;
GLfloat jimY = 0.0;
GLfloat jimZ = 0.0;
GLfloat elrx = 0.0;
GLfloat ellx = 0.0;
GLfloat ellz = 0.0;
GLfloat elrz = 0.0;
GLfloat jimrot = 0.0;

//controls
GLfloat navi = 0.0;
GLfloat lever1 = 0.0;
GLfloat lever2 = 0.0;
GLfloat lever3= 0.0;
GLfloat lever4 = 0.0;

//move scene
GLfloat sceX = 0.0;
GLfloat sceY = 0.0;
GLfloat sceZ = 0.0;

//move camera
GLfloat camX = 0.0;
GLfloat camY = 0.0;
GLfloat camZ = 0.0;

//colormaterial
GLfloat amb1[] = { 0.0,0.0,0.0 };//black
GLfloat amb2[] = { 0.082,0.28,0.2 };//dark green screen
GLfloat amb3[] = { 1.0,0.2,0.0 };//red
GLfloat amb4[] = { 1.0, 1.0, 0.0,1 };//yellow
GLfloat amb5[] = { 1.0, 1.0, 0.78,1 };//back wall
GLfloat amb6[] = { 0.21, 0.27, 0.31,1 };
GLfloat amb7[] = { 1.0, 0.5, 0.0,1 };
GLfloat amb8[] = { 0.0, 0.41, 0.58,1 };//sea blue
GLfloat amb9[] = { 0.5, 0.5, 0.5,1 };
GLfloat amb10[] = { 0.4, 0.4, 0.4,1 };
GLfloat amb11[] = { 0.3, 0.3, 0.3,1 };
GLfloat amb12[] = { 1.0, 1.0, 1.0,1 };//white
GLfloat amb13[] = { 0.0, 1.0, 0.0,1 };//green
GLfloat amb14[] = { 0.0, 0.0, 0.4,1 };//navy blue
GLfloat amb15[] = { 0.99, 0.89, 0.83,1 };//cream
GLfloat amb16[]= { 0.0, 1.0, 0.0,0 };//green transparent

GLfloat diff1[] = { 0.0,0.0,0.0 };//black
GLfloat diff2[] = { 0.082,0.28,0.2 };//dark green screen
GLfloat diff3[]= { 1.0,0.2,0.0 };//red
GLfloat diff4[] = { 1.0, 1.0, 0.0,1 };//yellow
GLfloat diff5[] = { 1.0, 1.0, 0.78,1 };// back wall
GLfloat diff6[] = { 0.21, 0.27, 0.31,1 }; //panel grey
GLfloat diff7[] = { 1.0, 0.5, 0.0,1 }; //wooden brown
GLfloat diff8[] = { 0.0, 0.41, 0.58,1 }; //sea blue
GLfloat diff9[] = { 0.5, 0.5, 0.5,1 };//grey
GLfloat diff10[] = { 0.3, 0.3, 0.3,1 };//dark grey
GLfloat diff11[] = { 0.1, 0.1, 0.1,1 };//darker grey
GLfloat diff12[] = { 1.0, 1.0, 1.0,1 };//white
GLfloat diff13[] = { 0.0, 1.0, 0.0,1 };//green
GLfloat diff14[] = { 0.0, 0.0, 0.4,1 };//navy blue
GLfloat diff15[] = { 0.99, 0.89, 0.83,1 };//cream
GLfloat diff16[] = { 0.0, 1.0, 0.0,0 };//green transparent


GLfloat spec8[] = { 1,1,1,1 };

GLfloat shin3[] = { 10 };
GLfloat shin5[] = { 50 };
GLfloat shin8[] = { 0 };

void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	//glDisable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glOrtho(-400, 400, -200, 200, 0.0, 400);
}

void material(GLfloat amb[], GLfloat diff[], GLfloat spec[], GLfloat shin[]) {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);
}

void drawDisk(double radius) {
	int d;
	glBegin(GL_POLYGON);
	for (d = 0; d < 32; d++) {
		double angle = 2 * PI / 32 * d;
		glVertex3d(radius * cos(angle), radius * sin(angle),0.0);
	}
	glEnd();

}

void drawCircle(double radius) {
	int d;
	glLineWidth(1);
	glBegin(GL_LINE_LOOP);
	for (d = 0; d < 32; d++) {
		double angle = 2 * PI / 32 * d;
		glVertex3d(radius * cos(angle), radius * sin(angle), 0.0);
	}
	glEnd();

}



void drawcylinder(GLfloat radius,GLfloat height) {
	GLfloat x=0.0;
	GLfloat y=0.0;
	GLfloat angle = 0.0;
	GLfloat angle_stepsize = 0.1;

	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		glVertex3f(x, y, 0.0);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glVertex3f(radius, 0.0, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glEnd();
}

void wheel() {
	glColor3f(1.0, 0.5, 0.0);
	glutSolidTorus(1, 10, 50, 50);
	drawcylinder(2, 1);
	//spokes
	glPushMatrix();
	glRotated(90, 1.0, 0.0, 0.0);
	drawcylinder(1, 12);
	glPopMatrix();

	glPushMatrix();
	glRotated(-90, 1.0, 0.0, 0.0);
	drawcylinder(1, 12);
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 0.0, 1.0, 0.0);
	drawcylinder(1, 12);
	glPopMatrix();

	glPushMatrix();
	glRotated(-90, 0.0, 1.0, 0.0);
	drawcylinder(1, 12);
	glPopMatrix();

	glPushMatrix();
	glRotated(-90, 0.0, 1.0, 0.0);
	glRotated(45, 0.0, 0.0, 1.0);
	drawcylinder(1, 12);
	glPopMatrix();

	
}

void steeringWheel() {
	glColor3f(1.0, 0.5, 0.0);
	
	glPushMatrix();
	glTranslatef(0.0, 10.0, 0.0);
	glRotated(-navi,0.0,0.0,1.0);
	wheel();
	glPopMatrix();

	//back hold
	glPushMatrix();
	glTranslated(0.0, 10.0, -10.0);
	drawcylinder(2, 10);
	glPopMatrix();

	//stand
	glPushMatrix();
	glTranslated(0.0,-40.0,-10.0);
	glRotated(-90, 1.0, 0.0, 0.0);
	glutSolidCone(5.0, 50, 50, 50);
	glPopMatrix();
	
	
}

void drawpuller() {
	material(amb10, diff10, spec8, shin5);
	glPushMatrix();
	glTranslated(2.5,0.0,0.0);
	glRotated(-90, 1.0, 0.0, 0.0);
	drawcylinder(0.5, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.5, 0.0, 0.0);
	glRotated(-90, 1.0, 0.0, 0.0);
	drawcylinder(0.5, 10);
	glPopMatrix();
	
	glPushMatrix();
	material(amb3, diff3, spec8, shin5);
	glRotated(90, 0.0, 1.0, 0.0);
	glTranslated(0.0,10.0,-1.5);
	drawcylinder(1, 5);
	glPopMatrix();
}

void drawlever() {
	glPushMatrix();
	material(amb1, diff1, spec8, shin8);
	//glColor3f(0.5, 0.5, 0.5);
	glRotated(90, 0.0, 1.0, 0.0);
	drawcylinder(3, 2);
	glPopMatrix();

	glPushMatrix();
	material(amb11, diff11, spec8, shin8);
	//glColor3f(0.4, 0.4, 0.4);
	glRotated(90, 0.0, 1.0, 0.0);
	drawcylinder(5, 2);
	glPopMatrix();

	glPushMatrix();
	material(amb9, diff9, spec8, shin8);
	//glColor3f(0.3, 0.3, 0.3);
	glRotated(90, 0.0, 1.0, 0.0);
	drawcylinder(6, 2);
	glPopMatrix();
	
	glPushMatrix();
	
	drawpuller();
	glPopMatrix();
}

void drawscreen() {
	material(amb1,diff1,spec8,shin5);
	glBegin(GL_QUADS);
	//front
	glVertex3f(5, 3, 0);
	glVertex3f(-5, 3, 0);
	glVertex3f(-5, -3, 0);
	glVertex3f(5, -3, 0);
	//back
	glVertex3f(5, 3, -3);
	glVertex3f(-5, 3, -3);
	glVertex3f(-5, -3, -3);
	glVertex3f(5, -3, -3);
	//right
	glVertex3f(5, 3, 0);
	glVertex3f(5, 3, -3);
	glVertex3f(5, -3, -3);
	glVertex3f(5, -3, 0);
	//left
	glVertex3f(-5, 3, 0);
	glVertex3f(-5, 3, -3);
	glVertex3f(-5, -3, -3);
	glVertex3f(-5, -3, 0);
	//bottom
	glVertex3f(5, -3, 0);
	glVertex3f(5, -3, -3);
	glVertex3f(-5, -3, -3);
	glVertex3f(-5, -3, 0);
	//top
	glVertex3f(5, 3, 0);
	glVertex3f(5, 3, -3);
	glVertex3f(-5, 3, -3);
	glVertex3f(-5, 3, 0);
	glEnd();

	glPushMatrix();
	material(amb2,diff2,spec8,shin3);
	glTranslated(0.0,0.0,0.01);
	glBegin(GL_POLYGON);
	glVertex2f(4.8, 2.8);
	glVertex2f(-4.8, 2.8);
	glVertex2f(-4.8, -2.8);
	glVertex2f(4.8, -2.8);
	glEnd();
	glPopMatrix();

}

void bargraph() {	
	material(amb12, diff12, spec8, shin8);
	
	int line;
	int step = 3;
	glLineWidth(0.5);
	glBegin(GL_LINES);
	for (line = -8; line <= 7; line += step) {
		glVertex3i(10,line,0);
		glVertex3i(-10,line,0);
	}
	glEnd();
	material(amb8,diff8,spec8,shin8);
	glLineWidth(10);
	glBegin(GL_LINES);
	glVertex3i(-8, -8, 0);
	glVertex3i(-8, 6, 0);

	glVertex3i(8, -8, 0);
	glVertex3i(8, 4, 0);

	glVertex3i(-4, -8, 0);
	glVertex3i(-4, 5, 0);

	glVertex3i(4, -8, 0);
	glVertex3i(4, 0, 0);

	glVertex3i(0, -8, 0);
	glVertex3i(0, 3, 0);
	glEnd();
	
}

void linegraph() {
	material(amb12, diff12, spec8, shin8);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex3i(-7,-1,0);
	glVertex3i(-6,5,0);

	glVertex3i(-6, 5, 0);
	glVertex3i(-4,-5,0);

	glVertex3i(-4, -5, 0);
	glVertex3i(-2,2,0);

	glVertex3i(-2, 2, 0);
	glVertex3i(0,-2,0);

	glVertex3i(7, -2, 0);
	glVertex3i(6, 5, 0);

	glVertex3i(6, 5, 0);
	glVertex3i(4, -7, 0);

	glVertex3i(4, -7, 0);
	glVertex3i(2, 6, 0);

	glVertex3i(2, 6, 0);
	glVertex3i(0, -2, 0);

	glVertex3i(7, -2, 0);
	glVertex3i(9, 0, 0);

	glVertex3i(-7, -1, 0);
	glVertex3i(-9, 0, 0);
	glEnd();
}

void map() {
	material(amb13, diff13, spec8, shin8);
	glTranslatef(3,-3,0);
	drawCircle(5);
	drawCircle(3);
	drawDisk(0.5);
	glTranslatef(0,6,0);
	drawCircle(3);
	drawCircle(5);
	drawDisk(0.5);
	glTranslatef(-7,0,0);
	drawCircle(3);
	drawCircle(5);
	drawDisk(0.5);
	glTranslatef(4,-5,0);
	drawCircle(3);
	drawCircle(5);
	drawDisk(0.5);
}

void radar() {
	material(amb13, diff13, spec8, shin8);
	glRotatef(-15, 0.0, 1.0, 0.0);
	
	drawCircle(12);
	drawCircle(11);
	drawCircle(10);
	drawCircle(9);
	drawCircle(8);
	drawCircle(7);
	drawCircle(6);
	drawCircle(5);
	drawCircle(4);
	drawCircle(3);
	drawCircle(2);
	drawCircle(1);
	glPushMatrix();
	material(amb3, diff3, spec8, shin8);
	glTranslatef(5,5,0);
	drawDisk(0.7);
	glPopMatrix();
	glPushMatrix();
	glRotatef(anim, 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	material(amb13, diff13, spec8, shin8);
	glVertex3f(-2,13,0);
	material(amb2, diff2, spec8, shin8);
	glVertex3f(2.5,13,0);
	material(amb2, diff2, spec8, shin8);
	glVertex3f(0.3, 0, 0);
	material(amb13, diff13, spec8, shin8);
	glVertex3f(0,0,0);
	glEnd();
	glPopMatrix();

}

void drawbuttonboard() {
	glPushMatrix();
	material(amb1, diff1, spec8, shin8);
	glBegin(GL_POLYGON);
	glVertex3d(-10, 6,0.0);
	glVertex3d(10, 6,0.0);
	glVertex3d(10, -6,0.0);
	glVertex3d(-10, -6,0.0);
	glEnd();
	glPopMatrix();
	material(amb3, diff3, spec8, shin3);
	glPushMatrix();
	glTranslatef(3,-2,0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, -2, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(7, -2, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-7, -2, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, -4, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, -4, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(7, -4, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-7, -4, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	material(amb8, diff8, spec8, shin8);
	glPushMatrix();
	glTranslatef(3, 4, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, 4, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(7, 4, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-7, 4, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, 2, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, 2, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(7, 2, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-7, 2, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	
}

void drawboard() {
	glPushMatrix();
	material(amb1, diff1, spec8, shin8);
	glBegin(GL_POLYGON);
	glVertex2d(-10, 6);
	glVertex2d(10, 6);
	glVertex2d(10, -6);
	glVertex2d(-10, -6);
	glEnd();
	glPopMatrix();
	material(amb4, diff4, spec8, shin3);
	glPushMatrix();
	glTranslatef(3, -2, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(7, -2, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(7, -4, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, -4, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	material(amb13, diff13, spec8, shin3);
	glPushMatrix();
	glTranslatef(3, 4, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(7, 4, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, 2, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(7, 2, 0.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
}

void speedometer() {
	material(amb12,amb12,spec8,shin5);
	drawcylinder(5, 1);
	glPushMatrix();
	material(amb1, diff1, spec8, shin5);
	int i; 
	glLineWidth(3);
	glBegin(GL_LINES);
	for (i = 0; i <=12 ; i += 1) {
		glVertex3f(5*sin(i*2*PI/12),5*cos(i*2*PI/12), 1.1);
		glVertex3f(0.0,0.0, 1.1);
	}
	glEnd();
	glPopMatrix();
	glPushMatrix();
	material(amb12, amb12, spec8, shin5);
	glTranslated(0.0, 0.0, 1.25);
	drawDisk(4);
	glPopMatrix();

	glPushMatrix();
	material(amb3, diff3, spec8, shin3);
	glRotatef(spd, 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-1, -1, 1.26);
	glVertex3f(1, -1, 1.26);
	glVertex3f(0, 5, 1.26);
	glEnd();
	glPopMatrix();

}

void rudder() {
	material(amb12, amb12, spec8, shin5);
	drawcylinder(5, 1);
	glPushMatrix();
	material(amb1, diff1, spec8, shin5);
	int i; 
	glLineWidth(3);
	glBegin(GL_LINES);
	for (i = 2; i <= 10; i += 1) {
		glVertex3f(5 * sin(i * 2 * PI / 12), 5 * cos(i * 2 * PI / 12), 1.1);
		glVertex3f(0.0, 0.0, 1.1);
	}
	glEnd();
	glPopMatrix();
	glPushMatrix();
	material(amb12, amb12, spec8, shin5);
	glTranslated(0.0, 0.0, 1.25);
	drawDisk(4);
	glPopMatrix();

	glPushMatrix();
	material(amb3, diff3, spec8, shin3);
	glRotatef(180 + rud, 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-1, -1, 1.26);
	glVertex3f(1, -1, 1.26);
	glVertex3f(0, 5, 1.26);
	glEnd();
	glPopMatrix();
}

void windanemo() {
	material(amb12, amb12, spec8, shin5);
	drawcylinder(5, 1);
	glPushMatrix();
	material(amb1, diff1, spec8, shin5);
	int i;
	glLineWidth(3);
	glBegin(GL_LINES);
	for (i = 0; i <= 12; i += 1) {
		glVertex3f(5 * sin(i * 2 * PI / 4), 5 * cos(i * 2 * PI / 4), 1.1);
		glVertex3f(0.0, 0.0, 1.1);
	}
	glEnd();
	glPopMatrix();
	glPushMatrix();
	material(amb12, amb12, spec8, shin5);
	glTranslated(0.0, 0.0, 1.25);
	drawDisk(4);
	glPopMatrix();

	glPushMatrix();
	material(amb3, diff3, spec8, shin3);
	glRotatef(-90, 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-1, -1, 1.26);
	glVertex3f(1, -1, 1.26);
	glVertex3f(0, 5, 1.26);
	glEnd();
	glPopMatrix();
}

void drawarm() {
	material(amb14, diff14, spec8, shin8);
	//left elbow                                
	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	drawcylinder(2.5, 20);
	glPopMatrix();
	

	//hands
	material(amb15, diff15, spec8, shin8);
	glPushMatrix();
	glTranslatef(0.0, -20, 0.0);
	glutSolidSphere(2.5, 20, 20);
	glPopMatrix();

	material(amb4, diff4, spec8, shin8);
	glPushMatrix();
	glTranslatef(0.0, -18, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glutSolidTorus(1,1.9, 20, 20);
	glPopMatrix();

	
	glPushMatrix();
	glTranslatef(0.0, -18, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glutSolidTorus(1,1.9, 20, 20);
	glPopMatrix();


}

void officer() {
	//head
	glPushMatrix();
	material(amb15, diff10, spec8, shin8);
	glScalef(0.85, 1.1, 1.0);
	glutSolidSphere(7.5, 20, 20);
	glPopMatrix();
	//eyes and mouth
	glPushMatrix();
	material(amb1, diff1, spec8, shin8);
	glTranslatef(-2.2,1.6,6.0);
	glutSolidSphere(1, 10, 10);
	glPopMatrix();
	glPushMatrix();
	material(amb1, diff1, spec8, shin8);
	glTranslatef(2.2, 1.6, 6.0);
	glutSolidSphere(1, 10, 10);
	glPopMatrix();
	glPushMatrix();
	material(amb12, diff12, spec8, shin8);
	//glTranslatef(0.0, -1.6, 6.8);
	glBegin(GL_POLYGON);
	glVertex3f(-1.2,-1.6,7.3);
	glVertex3f(1.2,-1.6,7.3);
	glVertex3f(0,-2.2,7.3);
	glEnd();
	glPopMatrix();
	//hat lining
	glPushMatrix();
	material(amb1, diff1, spec8, shin8);
	glTranslated(0.0, 5.0, 0.0);
	glRotated(90, 1.0, 0.0, 0.0);
	glutSolidTorus(1.00, 6, 20, 20);
	glPopMatrix();
	//hat
	glPushMatrix();
	material(amb12, diff12, spec8, shin8);
	glTranslated(0.0, 9.0, 0.0);
	glRotated(90, 1.0, 0.0, 0.0);
	glutSolidCone(8, 20, 20, 20);
	glPopMatrix();
	//neck
	glPushMatrix();
	material(amb12, diff12, spec8, shin8);
	glTranslated(0.0, -7.0, 0.0);
	glRotated(90, 1.0, 0.0, 0.0);
	drawcylinder(3.5, 3.5);
	glPopMatrix();
	//torso
	glPushMatrix();
	material(amb14, diff14, spec8, shin8);
	glTranslated(0.0, -28.0, 0);
	glBegin(GL_QUADS);
	//top
	glVertex3f(-11, 18, -5);
	glVertex3f(-11, 18, 5);
	glVertex3f(11, 18, 5);
	glVertex3f(11, 18, -5);
	//bottom
	glVertex3f(-10, -18, -5);
	glVertex3f(-10, -18, 5);
	glVertex3f(10, -18, 5);
	glVertex3f(10, -18, -5);
	//right
	glVertex3f(11, 18, -5);
	glVertex3f(11, 18, 5);
	glVertex3f(10, -18, 5);
	glVertex3f(10, -18, -5);
	//left
	glVertex3f(-11, 18, -5);
	glVertex3f(-11, 18, 5);
	glVertex3f(-10, -18, 5);
	glVertex3f(-10, -18, -5);
	//front
	glVertex3f(11, 18, 5);
	glVertex3f(-11, 18, 5);
	glVertex3f(-10, -18, 5);
	glVertex3f(10, -18, 5);
	//back
	glVertex3f(11, 18, -5);
	glVertex3f(-11, 18, -5);
	glVertex3f(-10, -18, -5);
	glVertex3f(10, -18, -5);
	glEnd();
	glPopMatrix();
	//buttons
	material(amb4, diff4, spec8, shin5);
	glPushMatrix();
	glTranslatef(-5, -25, 5.1);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5, -30, 5.1);
	glutSolidSphere(1,20,20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5, -35, 5.1);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(5, -25, 5.1);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(5, -30, 5.1);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(5, -35, 5.1);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	//legs
	glPushMatrix();
	material(amb14, diff14, spec8, shin8);
	glPushMatrix();
	glTranslatef(5, -40, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	
	drawcylinder(4.8, 50);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5, -40, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	
	drawcylinder(4.8, 50);
	glPopMatrix();
	glPopMatrix();
	//arms
	material(amb14, diff14, spec8, shin8);	
	glPushMatrix();
	//left upper arm
	glTranslatef(13.5, -11, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	drawcylinder(2.5, 20);
	glPopMatrix();
	
	//right upper arm
	glPushMatrix();
	glTranslatef(-13.5, -11, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	drawcylinder(2.5, 20);
	glPopMatrix();
	//left elbow
	glPushMatrix();
	glTranslatef(13.5, -31, 0.0);
	glRotatef(ellx, 1.0, 0.0, 0.0);
	glRotatef(ellz, 0.0, 0.0, 1.0);
	drawarm();
	glPopMatrix();
	//right elbow
	glPushMatrix();
	glTranslatef(-13.5, -31, 0.0);
	glRotatef(elrx, 1.0, 0.0, 0.0);
	glRotatef(elrz, 0.0, 0.0, 1.0);
	drawarm();
	glPopMatrix();
	
	//shoes
	material(amb1, diff1, spec8, shin3);
	glPushMatrix();
	glTranslatef(-5.2, -90, 0);
	glutSolidSphere(5.2,20,20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(5.2, -90, 0);
	glutSolidSphere(5.2,20,20);
	glPopMatrix();

}

void water() {
	glColor3f(0.0, 0.5, 1.0);
	glBegin(GL_QUADS);
	//top
	glVertex3f(-200, 15, -115);
	glVertex3f(-200, 15, -105);
	glVertex3f(200, 15, -105);
	glVertex3f(200, 15, -115);
	//bottom
	glVertex3f(-200, -70, -115);
	glVertex3f(-200, -70, -105);
	glVertex3f(200, -70, -105);
	glVertex3f(200, -70, -115);
	//left
	glVertex3f(-200, 15, -115);
	glVertex3f(-200, 15, -105);
	glVertex3f(-200, -70, -105);
	glVertex3f(-200, -70, -115);
	//right
	glVertex3f(200, 15, -115);
	glVertex3f(200, 15, -105);
	glVertex3f(200, -70, -105);
	glVertex3f(200, -70, -115);
	//front
	glVertex3f(-200, 15, -105);
	glVertex3f(200, 15, -105);
	glVertex3f(200, -70, -105);
	glVertex3f(-200, -70, -105);
	//back
	glVertex3f(-200, 15, -115);
	glVertex3f(200, 15, -115);
	glVertex3f(200, -70, -115);
	glVertex3f(-200, -70, -115);
	glEnd();
}

void panel() {
	//glColor3f(0.5, 0.5, 0.5);
	//left block
	glBegin(GL_QUADS);
	//left
	glVertex3f(-130,-20,-90);
	glVertex3f(-130, -20, -30);
	glVertex3f(-130, -70, -30);
	glVertex3f(-130, -70, -90);
	//front
	glVertex3f(-130, -20, -30);
	glVertex3f(-130, -70, -30);
	glVertex3f(-100, -70, -50);
	glVertex3f(-100, -20, -50);
	//right
	glVertex3f(-100, -20, -50);
	glVertex3f(-100, -70, -50);
	glVertex3f(-100, -70, -60);
	glVertex3f(-100, -20, -60);
	//back
	glVertex3f(-100, -20, -60);
	glVertex3f(-100, -70, -60);
	glVertex3f(-130, -70, -90);
	glVertex3f(-130, -20, -90);
	//top
	glVertex3f(-130, -20, -30);
	glVertex3f(-130, -20, -90);
	glVertex3f(-100, -20, -60);
	glVertex3f(-100, -20, -50);

	//bottom
	glVertex3f(-130, -70, -30);
	glVertex3f(-130, -70, -90);
	glVertex3f(-100, -70, -60);
	glVertex3f(-100, -70, -50);
	glEnd();

	//right block
	glBegin(GL_QUADS);
	glVertex3f(130, -20, -90);
	glVertex3f(130, -20, -30);
	glVertex3f(130, -70, -30);
	glVertex3f(130, -70, -90);

	glVertex3f(130, -20, -30);
	glVertex3f(130, -70, -30);
	glVertex3f(100, -70, -50);
	glVertex3f(100, -20, -50);

	glVertex3f(100, -20, -50);
	glVertex3f(100, -70, -50);
	glVertex3f(100, -70, -60);
	glVertex3f(100, -20, -60);

	glVertex3f(100, -20, -60);
	glVertex3f(100, -70, -60);
	glVertex3f(130, -70, -90);
	glVertex3f(130, -20, -90);

	//top
	glVertex3f(130, -20, -30);
	glVertex3f(130, -20, -90);
	glVertex3f(100, -20, -60);
	glVertex3f(100, -20, -50);

	//bottom
	glVertex3f(130, -70, -30);
	glVertex3f(130, -70, -90);
	glVertex3f(100, -70, -60);
	glVertex3f(100, -70, -50);
	glEnd();

	//middle block
	
	glBegin(GL_LINES);
	glVertex3f(-100,-19,-59.99);
	glVertex3f(100,-19,-59.99);
	glEnd();

	glBegin(GL_QUADS);
	//top
	glVertex3f(-130, -20, -90);
	glVertex3f(130, -20, -90);
	glVertex3f(100, -20, -60);
	glVertex3f(-100, -20, -60);

	//bottom
	glVertex3f(-130, -70, -90);
	glVertex3f(130, -70, -90);
	glVertex3f(100, -70, -60);
	glVertex3f(-100, -70, -60);

	//left
	glVertex3f(-130, -20, -90);
	glVertex3f(-100, -20, -60);
	glVertex3f(-100, -70, -60);
	glVertex3f(-130, -70, -90);

	//right
	glVertex3f(130, -20, -90);
	glVertex3f(130, -70, -90);
	glVertex3f(100, -70, -60);
	glVertex3f(100, -20, -60);

	//front
	glVertex3f(-100, -20, -60);
	glVertex3f(100, -20, -60);
	glVertex3f(100, -70, -60);
	glVertex3f(-100, -70, -60);

	//back
	glVertex3f(-130, -20, -90);
	glVertex3f(130, -20, -90);
	glVertex3f(130, -70, -90);
	glVertex3f(-130, -70, -90);
	glEnd();

	//triangle
	glBegin(GL_QUADS);
	//left
	glVertex3f(-70, -10, -90);
	glVertex3f(-70, -20, -80);
	glVertex3f(-70, -20, -90);
	//right
	glVertex3f(70, -10, -90);
	glVertex3f(70, -20, -80);
	glVertex3f(70, -20, -90);
	//top
	glVertex3f(-70, -10, -90);
	glVertex3f(-70, -20, -80);
	glVertex3f(70, -20, -80);
	glVertex3f(70, -10, -90);
	//bottom
	glVertex3f(-70, -20, -90);
	glVertex3f(-70, -20, -80);
	glVertex3f(70, -20, -80);
	glVertex3f(70, -20, -90);
	//back
	glVertex3f(-70, -10, -90);
	glVertex3f(-70, -20, -90);
	glVertex3f(70, -20, -90);
	glVertex3f(70, -10, -90);
	glEnd();
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	
	GLfloat white[] = { 0.1,0.1,0.1,1.0 };
	GLfloat lightposition0[] = { 125.0,69.0,-85.0,1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE,white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glLightfv(GL_LIGHT0, GL_POSITION, lightposition0);
	
	GLfloat white2[] = { 0.2,0.2,0.2,1.0 };
	GLfloat lightposition1[] = { -125.0,69.0,-85.0,1.0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white2);
	glLightfv(GL_LIGHT1, GL_POSITION, lightposition1);
	
	glEnable(GL_LIGHT2);
	GLfloat sunwhite[] = { 1.0,1.0,1.0,1.0 };
	GLfloat lightposition2[] = { 0.0,100.0,-110.0,1.0 };
	glLightfv(GL_LIGHT2, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT2, GL_SPECULAR, white);
	glLightfv(GL_LIGHT2, GL_POSITION, lightposition2);

	gluLookAt(camX, camY, camZ, camX, camY, camZ - 200, 0.0, 1.0, 0.0);
	
	glRotatef(sceY,1.0,0.0,0.0);
	glRotatef(sceX, 0.0, 1.0, 0.0);
	glRotatef(sceZ, 0.0, 0.0, 1.0);

	//drawaxes();
	//glColor3f(1, 1, 0);
	

	//back wall
	glPushMatrix();
	material(amb5, diff5, spec8, shin5);

	glColor3f(0.0f,0.0f,0.54f);
	//glTranslatef(0,-70,0);
	
	//low wall
	glBegin(GL_QUADS);
	//left
	glVertex3f(-140, -10, -100);
	glVertex3f(-140, -10, -90);
	glVertex3f(-140, -80, -90);
	glVertex3f(-140, -80, -100);

	//right
	glVertex3f(140, -10, -100);
	glVertex3f(140, -10, -90);
	glVertex3f(140, -80, -90);
	glVertex3f(140, -80, -100);

	//top
	glVertex3f(-140, -10, -100);
	glVertex3f(-140, -10, -90);
	glVertex3f(140, -10, -90);
	glVertex3f(140, -10, -100);

	//bottom
	glVertex3f(-140, -80, -100);
	glVertex3f(-140, -80, -90);
	glVertex3f(140, -80, -90);
	glVertex3f(140, -80, -100);

	//inner face
	glVertex3f(-140, -10, -90);
	glVertex3f(-140, -80, -90);
	glVertex3f(140, -80, -90);
	glVertex3f(140, -10, -90);

	//outer face
	glVertex3f(-140, -10, -100);
	glVertex3f(-140, -80, -100);
	glVertex3f(140, -80, -100);
	glVertex3f(140, -10, -100);
	glEnd();

	//upper wall
	glBegin(GL_QUADS);

	//left
	glVertex3f(-140, 80, -100);
	glVertex3f(-140, 80, -90);
	glVertex3f(-140, 60, -90);
	glVertex3f(-140, 60, -100);

	//right
	glVertex3f(140, 60, -100);
	glVertex3f(140, 60, -90);
	glVertex3f(140, 80, -90);
	glVertex3f(140, 80, -100);

	//top
	glVertex3f(-140, 80, -100);
	glVertex3f(-140, 80, -90);
	glVertex3f(140, 80, -90);
	glVertex3f(140, 80, -100);

	//bottom
	glVertex3f(-140, 60, -100);
	glVertex3f(-140, 60, -90);
	glVertex3f(140, 60, -90);
	glVertex3f(140, 60, -100);

	//inner face
	glVertex3f(-140, 80, -90);
	glVertex3f(-140, 60, -90);
	glVertex3f(140, 60, -90);
	glVertex3f(140, 80, -90);

	//outer face
	glVertex3f(-140, 80, -100);
	glVertex3f(-140, 60, -100);
	glVertex3f(140, 60, -100);
	glVertex3f(140, 80, -100);
	glEnd();

	//lining left
	glBegin(GL_QUADS);

	//left
	glVertex3f(-140, -10, -100);
	glVertex3f(-140, -10, -90);
	glVertex3f(-140, 60, -90);
	glVertex3f(-140, 60, -100);

	//right
	glVertex3f(-125, -10, -100);
	glVertex3f(-125, -10, -90);
	glVertex3f(-115, 60, -90);
	glVertex3f(-115, 60, -100);

	//top
	glVertex3f(-140, 60, -100);
	glVertex3f(-140, 60, -90);
	glVertex3f(-115, 60, -90);
	glVertex3f(-115, 60, -100);

	//bottom
	glVertex3f(-140, -10, -100);
	glVertex3f(-140, -10, -90);
	glVertex3f(-125, -10, -90);
	glVertex3f(-125, -10, -100);

	//front face
	glVertex3f(-140, 60, -90);
	glVertex3f(-140, -10, -90);
	glVertex3f(-125, -10, -90);
	glVertex3f(-115, 60, -90);

	//back face
	glVertex3f(-140, 60, -100);
	glVertex3f(-140, -10, -100);
	glVertex3f(-125, -10, -100);
	glVertex3f(-115, 60, -100);
	glEnd();

	//lining right
	glBegin(GL_QUADS);

	//right
	glVertex3f(140, -10, -100);
	glVertex3f(140, -10, -90);
	glVertex3f(140, 60, -90);
	glVertex3f(140, 60, -100);

	//left
	glVertex3f(125, -10, -100);
	glVertex3f(125, -10, -90);
	glVertex3f(115, 60, -90);
	glVertex3f(115, 60, -100);

	//top
	glVertex3f(140, 60, -100);
	glVertex3f(140, 60, -90);
	glVertex3f(115, 60, -90);
	glVertex3f(115, 60, -100);

	//bottom
	glVertex3f(140, -10, -100);
	glVertex3f(140, -10, -90);
	glVertex3f(125, -10, -90);
	glVertex3f(125, -10, -100);

	//front face
	glVertex3f(140, 60, -90);
	glVertex3f(140, -10, -90);
	glVertex3f(125, -10, -90);
	glVertex3f(115, 60, -90);

	//back face
	glVertex3f(140, 60, -100);
	glVertex3f(140, -10, -100);
	glVertex3f(125, -10, -100);
	glVertex3f(115, 60, -100);
	glEnd();

	//middle strip left
	glBegin(GL_QUADS);

	//left
	glVertex3f(-59, -10, -100);
	glVertex3f(-59, -10, -90);
	glVertex3f(-54, 60, -90);
	glVertex3f(-54, 60, -100);

	//right
	glVertex3f(-49, -10, -100);
	glVertex3f(-49, -10, -90);
	glVertex3f(-44, 60, -90);
	glVertex3f(-44, 60, -100);

	//top
	glVertex3f(-54, 60, -100);
	glVertex3f(-54, 60, -90);
	glVertex3f(-44, 60, -90);
	glVertex3f(-44, 60, -100);

	//bottom
	glVertex3f(-59, -10, -100);
	glVertex3f(-59, -10, -90);
	glVertex3f(-49, -10, -90);
	glVertex3f(-49, -10, -100);

	//front face
	glVertex3f(-54, 60, -90);
	glVertex3f(-59, -10, -90);
	glVertex3f(-49, -10, -90);
	glVertex3f(-44, 60, -90);

	//back face
	glVertex3f(-54, 60, -100);
	glVertex3f(-59, -10, -100);
	glVertex3f(-49, -10, -100);
	glVertex3f(-44, 60, -100);
	glEnd();

	//middle strip right
	glBegin(GL_QUADS);
	//right
	glVertex3f(59, -10, -100);
	glVertex3f(59, -10, -90);
	glVertex3f(54, 60, -90);
	glVertex3f(54, 60, -100);

	//left
	glVertex3f(49, -10, -100);
	glVertex3f(49, -10, -90);
	glVertex3f(44, 60, -90);
	glVertex3f(44, 60, -100);

	//top
	glVertex3f(54, 60, -100);
	glVertex3f(54, 60, -90);
	glVertex3f(44, 60, -90);
	glVertex3f(44, 60, -100);

	//bottom
	glVertex3f(59, -10, -100);
	glVertex3f(59, -10, -90);
	glVertex3f(49, -10, -90);
	glVertex3f(49, -10, -100);

	//front face
	glVertex3f(54, 60, -90);
	glVertex3f(59, -10, -90);
	glVertex3f(49, -10, -90);
	glVertex3f(44, 60, -90);

	//back face
	glVertex3f(54, 60, -100);
	glVertex3f(59, -10, -100);
	glVertex3f(49, -10, -100);
	glVertex3f(44, 60, -100);
	glEnd();

	glPopMatrix();
	//walls
	glPushMatrix();
	
	material(amb9, diff9, spec8, shin3);
	
	glPushMatrix();
	glColor3f(1.0f, 0.70f, 0.75f);
	//glTranslatef(0, -70, 0);
	//left wall
	glBegin(GL_QUADS);
	glVertex3f(-140, 70, -20);
	glVertex3f(-130, -70, -20);
	glVertex3f(-130, -70, -20);
	glVertex3f(-140, -70, -20);

	glVertex3f(-140, 70, -90);
	glVertex3f(-130, -70, -90);
	glVertex3f(-130, -70, -90);
	glVertex3f(-140, -70, -90);

	//top
	glVertex3f(-140, 70, -90);
	glVertex3f(-130, 70, -90);
	glVertex3f(-130, 70, -20);
	glVertex3f(-140, 70, -20);

	//bottom
	glVertex3f(-140, -70, -90);
	glVertex3f(-130, -70, -90);
	glVertex3f(-130, -70, -20);
	glVertex3f(-140, -70, -20);

	//inner face
	glVertex3f(-130, -70, -20);
	glVertex3f(-130, -70, -90);
	glVertex3f(-130, 70, -90);
	glVertex3f(-130, 70, -20);

	//outer face
	glVertex3f(-140, -70, -20);
	glVertex3f(-140, -70, -90);
	glVertex3f(-140, 70, -90);
	glVertex3f(-140, 70, -20);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 0.70f, 0.75f);
	//glTranslatef(0, -70, 0);
	//right wall
	glBegin(GL_QUADS);
	glVertex3f(140, 70, -20);
	glVertex3f(130, -70, -20);
	glVertex3f(130, -70, -20);
	glVertex3f(140, -70, -20);

	glVertex3f(140, 70, -90);
	glVertex3f(130, -70, -90);
	glVertex3f(130, -70, -90);
	glVertex3f(140, -70, -90);

	//top
	glVertex3f(140, 70, -90);
	glVertex3f(130, 70, -90);
	glVertex3f(130, 70, -20);
	glVertex3f(140, 70, -20);

	//bottom
	glVertex3f(140, -70, -90);
	glVertex3f(130, -70, -90);
	glVertex3f(130, -70, -20);
	glVertex3f(140, -70, -20);

	//inner face
	glVertex3f(130, -70, -20);
	glVertex3f(130, -70, -90);
	glVertex3f(130, 70, -90);
	glVertex3f(130, 70, -20);

	//outer face
	glVertex3f(140, -70, -20);
	glVertex3f(140, -70, -90);
	glVertex3f(140, 70, -90);
	glVertex3f(140, 70, -20);
	glEnd();
	glPopMatrix();
	glPopMatrix();

	//ceiling and floor
	glPushMatrix();
	
	material(amb7, diff7, spec8, shin3);

	
	glPushMatrix();
	glColor3f(0.78f, 0.63f, 0.78f);
	//glTranslatef(0, -70, 0);
	//floor
	glBegin(GL_QUADS);
	glVertex3f(-140, -70, -20);
	glVertex3f(-140, -80, -20);
	glVertex3f(140, -80, -20);
	glVertex3f(140, -70, -20);

	glVertex3f(140, -70, -90);
	glVertex3f(140, -80, -90);
	glVertex3f(140, -80, -20);
	glVertex3f(140, -70, -20);

	glVertex3f(140, -70, -90);
	glVertex3f(140, -80, -90);
	glVertex3f(-140, -80, -90);
	glVertex3f(-140, -70, -90);

	glVertex3f(-140, -70, -90);
	glVertex3f(-140, -80, -90);
	glVertex3f(-140, -80, -20);
	glVertex3f(-140, -70, -20);

	//top face
	glVertex3f(-140, -70, -20);
	glVertex3f(-140, -70, -90);
	glVertex3f(140, -70, -90);
	glVertex3f(140, -70, -20);

	//bottom face
	glVertex3f(-140, -80, -20);
	glVertex3f(-140, -80, -90);
	glVertex3f(140, -80, -90);
	glVertex3f(140, -80, -20);
	glEnd();
	glPopMatrix();

	
	glPushMatrix();
	glColor3f(0.78f, 0.63f, 0.78f);
	//glTranslatef(0, -70, 0);
	//ceiling
	glBegin(GL_QUADS);
	glVertex3f(-140, 70, -20);
	glVertex3f(-140, 80, -20);
	glVertex3f(140, 80, -20);
	glVertex3f(140, 70, -20);

	glVertex3f(140, 70, -90);
	glVertex3f(140, 80, -90);
	glVertex3f(140, 80, -20);
	glVertex3f(140, 70, -20);

	glVertex3f(140, 70, -90);
	glVertex3f(140, 80, -90);
	glVertex3f(-140,80, -90);
	glVertex3f(-140, 70, -90);

	glVertex3f(-140, 70, -90);
	glVertex3f(-140, 80, -90);
	glVertex3f(-140, 80, -20);
	glVertex3f(-140, 70, -20);

	//top face
	glVertex3f(-140, 70, -20);
	glVertex3f(-140, 70, -90);
	glVertex3f(140, 70, -90);
	glVertex3f(140, 70, -20);

	//bottom face
	glVertex3f(-140, 80, -20);
	glVertex3f(-140, 80, -90);
	glVertex3f(140, 80, -90);
	glVertex3f(140, 80, -20);
	glEnd();
	glPopMatrix();
	glPopMatrix();

	//lines on ceiling and floor
	glPushMatrix();
	material(amb1, diff1, spec8, shin8);
	GLfloat step = 10;
	GLint line;
	glLineWidth(1);
	glBegin(GL_LINES);
	for (line = -130; line <= 130; line += step) {
		glVertex3f(line, -69.5, -20);
		glVertex3f(line, -69.5, -90);

		glVertex3f(line, 69.5, -20);
		glVertex3f(line, 69.5, -90);
	}
	glEnd();
	glPopMatrix();


	

	//panels
	glPushMatrix();
	material(amb6, diff6, spec8, shin8);		
	panel();
	glPopMatrix();

	//navigation
	glPushMatrix();
	material(amb7, diff7, spec8, shin8);
	glTranslatef(0.0, -20.0, -45.0);
	glScaled(1.3, 1.3, 1.3);
	steeringWheel();
	glPopMatrix();

	//water
	glPushMatrix();
	material(amb8, diff8, spec8, shin8);
	glRotated(navi / 10, 0.0, 0.0, 1.0);
	water();
	glPopMatrix();

	//levers
	glPushMatrix();
	glTranslated(-55,-20,-70);
	glRotatef(lever1, 1.0, 0.0, 0.0);
	drawlever();
	glPopMatrix();

	/*glPushMatrix();
	glTranslated(-45, -20, -70);
	glRotatef(lever2, 1.0, 0.0, 0.0);
	drawlever();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-35, -20, -70);
	glRotated(180, 0.0, 1.0, 0.0);
	glRotatef(lever3, 1.0, 0.0, 0.0);
	drawlever();
	glPopMatrix();
	*/
	glPushMatrix();
	glTranslated(35, -20, -70);
	glRotated(180, 0.0, 1.0, 0.0);
	glRotatef(lever4, 1.0, 0.0, 0.0);
	drawlever();
	glPopMatrix();

	//screens
	glPushMatrix();
	glTranslated(-88.0,-5.0,-80);
	glRotated(15,0.0,1.0,0.0);
	glScaled(3,5,0.5);
	drawscreen();
	glPopMatrix();

	glPushMatrix();
	glTranslated(88.0, -5.0, -80); 
	glRotated(-15, 0.0, 1.0, 0.0);
	glScaled(3, 5, 0.5);
	drawscreen();
	glPopMatrix();
	//map
	glPushMatrix();
	glTranslatef(-115.0, -5.0, -64.9);
	glRotatef(225, 0.0, 1.0, 0.0);
	glScaled(1.5, 1.5, 0);
	map();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-115.0, -5.0, -65);
	glRotated(45, 0.0, 1.0, 0.0);
	glScaled(3, 5, 0.5);
	drawscreen();
	glPopMatrix();
	//bar
	glPushMatrix();
	glTranslatef(-88.0, -5.0, -79.9);
	glRotatef(15, 0.0, 1.0, 0.0);
	glScaled(1.5,1.5,0);
	bargraph();
	glPopMatrix();

	glPushMatrix(); 
	glTranslated(115.0, -5.0, -65);
	glRotated(-45, 0.0, 1.0, 0.0);
	glScaled(3, 5, 0.5);
	drawscreen();
	glPopMatrix();
	//line
	glPushMatrix();
	glTranslatef(115.0, -5.0, -64.9);
	glRotatef(-45, 0.0, 1.0, 0.0);
	glScaled(1.5, 1.5, 0);
	linegraph();
	glPopMatrix();
	
	//radar
	glPushMatrix();
	glTranslatef(88.0, -5.0, -79.9);
	radar();
	glPopMatrix();

	glPushMatrix();
	material(amb1, diff1, spec8, shin8);
	glTranslated(0.0, -19.9, -70.0);
	glRotated(90, 1.0, 0.0, 0.0);
	glScaled(2, 1.5, 1.0);
	drawbuttonboard();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-44.0, -19.9, -70.0);
	glRotated(90, 1.0, 0.0, 0.0);
	glScaled(2, 1.5, 1.0);
	drawboard();
	glPopMatrix();

	glPushMatrix();
	glTranslated(44.0, -19.9, -70.0);
	glRotated(90, 1.0, 0.0, 0.0);
	glScaled(2, 1.5, 1.0);
	drawboard();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, -15, -85);
	glRotated(-45, 1.0, 0.0, 0.0);
	speedometer();
	glPopMatrix();

	
	glPushMatrix();
	glTranslated(-40.0, -15, -85);
	glRotated(-45, 1.0, 0.0, 0.0);
	rudder();
	glPopMatrix();

	glPushMatrix();
	glTranslated(40.0, -15, -85);
	glRotated(-45, 1.0, 0.0, 0.0);
	windanemo();
	glPopMatrix();

	glPushMatrix();
	glTranslated(jimX-80, 25, jimZ-50);
	glRotatef(jimrot, 0.0, 1.0, 0.0);
	officer();
	glPopMatrix();

	

	glPopMatrix();
	

	glutSwapBuffers();

}


/*void speed(int x) {
	if (spd >= (-41))
		spd -= 1;
	else if (spd <= (-60))
		spd += 1;
	else
		spd -= 1;
	glutPostRedisplay();
	glutTimerFunc(40, speed, 0);
}*/

//radar timer func
void radartime(int v) {
	if (anim == 360.0)
		anim = 0.0;
	else
		anim += 2;
	glutPostRedisplay();
	glutTimerFunc(30, radartime, 1);
}

void timer(int p) {
	if (startrot==1) {
		if (jimrot == 180.0)
			jimrot += 0;
		else {
			jimrot += 1.0;
		}
		glutPostRedisplay();
		glutTimerFunc(30.0, timer, 1);
	}
	else {
		glutTimerFunc(30.0, timer, 1);
	}
}

void timer1(int q) {
	if (startwalk1 == 1) {
		if (jimZ == 25.0)
			jimZ += 0;
		else {
			jimZ += 1.0;
		}
		glutPostRedisplay();
		glutTimerFunc(30.0, timer1, 1);
	}
	else {
		glutTimerFunc(30.0, timer1, 1);
	}
}

void timer2(int r) {
	if (startwalk2 == 1) {
		if (jimX == 80.0)
			jimX += 0;
		else {
			jimX += 1.0;
		}
		glutPostRedisplay();
		glutTimerFunc(30.0, timer2, 1);
	}
	else {
		glutTimerFunc(30.0, timer2, 1);
	}
}
void timer3(int s) {
	if (startarm == 1) {
		if ((elrx == -90.0) && (ellx == -90.0))
			(elrx += 0.0) && (ellx += 0.0);
		else {
			(elrx -= 1.0) && (ellx -= 1.0);;
		}
		glutPostRedisplay();
		glutTimerFunc(30.0, timer3, 1);
	}
	else {
		glutTimerFunc(30.0, timer3, 1);
	}
}


void timer4(int t) {
	if (navigate == 1) {
		if (navi == -90 )
			(navi -= 0.0);
		else {
			(navi -= 1.0);
		}
		glutPostRedisplay();
		glutTimerFunc(30.0, timer4, 1);
	}
	else {
		glutTimerFunc(30.0, timer4, 1);
	}
}

void keyboardspecial(int key,int x, int y) {
	if (key == GLUT_KEY_RIGHT)
		camX += 1;
	if (key == GLUT_KEY_LEFT)
		camX -= 1;
	if (key == GLUT_KEY_UP)
		camY += 1;
	if (key == GLUT_KEY_DOWN)
		camY -= 1;
	if (key == GLUT_KEY_PAGE_UP)
		camZ += 1;
	if (key == GLUT_KEY_PAGE_DOWN)
		camZ -= 1;

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	if (key == '1')
		glEnable(GL_LIGHT0);
	if (key == '!')
		glDisable(GL_LIGHT0);
	if (key == '2')
		glEnable(GL_LIGHT1);
	if (key == '@')
		glDisable(GL_LIGHT1);
	if (key == '[')
		sceY -= 1;
	if (key == ']')
		sceY += 1;
	if (key == ',')
		sceX -= 1;
	if (key == '.')
		sceX += 1;
	if (key == 'o')
		(navi -= 1) && (rud -= 1);
	if (key == 'p')
		(navi += 1) && (rud += 1);
	if (key == 'q')
		lever1 -= 45;
	if (key == 'w')
		lever1 += 45;
	if (key == 'u')
		lever4 -= 45;
	if (key == 'i')
		lever4 += 45;
	if (key == 'a')
		jimX -= 1;
	if (key == 's')
		jimX += 1;
	if (key == 'd')
		jimZ -= 1;
	if (key == 'f')
		jimZ += 1;
	if (key == 'c')
		ellx -= 3;
	if (key == 'v')
		ellx += 3;
	if (key == 'z')
		elrx -= 3;
	if (key == 'x')
		elrx += 3;
	if (key == 'g')
		ellz -= 3;
	if (key == 'h')
		ellz += 3;
	if (key == 'n')
		elrz -= 3;
	if (key == 'm')
		elrz += 3;
	if (key == 'b')
		jimrot += 2;
	if (key == 'j')
		jimrot -= 2;
	if (key == '5')
		startrot = 1;
	if (key == '6')
		startrot = 0;
	if (key == 'e')
		startwalk1 = 1;
	if (key == 'r')
		startwalk1 = 0;
	if (key == 't')
		startwalk2 = 1;
	if (key == 'y')
		startwalk2 = 0;
	if (key == '7')
		startarm = 1;
	if (key == '8')
		startarm = 0;
	if (key == '9')
		navigate = 1;
	if (key == '0')
		navigate = 0;

	glutPostRedisplay();
}

void reshape(GLsizei w,GLsizei h) {
	glViewport(0, 0, w, h);
	GLfloat aspectratio = h == 0 ? w / 1 : 
		(GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(110.0, aspectratio, 1.0, 200.0);


}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(150, 150);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Ship Control Room");
	//pix[0].readBMPFile("radar.bmp");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutTimerFunc(200, speed, 0);
	glutTimerFunc(200, radartime, 1);
	glutTimerFunc(200, timer, 1);
	glutTimerFunc(200, timer1, 1);
	glutTimerFunc(200, timer2, 1);
	glutTimerFunc(200, timer3, 1);
	glutTimerFunc(200, timer4, 1);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardspecial);
	init();
	glutMainLoop();
	return 0;
}
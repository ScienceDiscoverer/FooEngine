#include <mymath.h>
#include <shapes.h>

vector2 acceleration(0.0, 0.08);
rectangle bat1(0.5, 3, -x_goal+0.5, 0); // x_goal defined in <shapes.h>
rectangle bat2(0.5, 3, x_goal-0.5, 0);
rectangle walltop(x_goal*2, 1, 0, 5.3);
rectangle wallbot(x_goal*2, 1, 0, -5.3);

shape *boxes[] = {&bat1, &bat2, &walltop, &wallbot};
shape *walls[] = {&walltop, &wallbot};

circle ball(0.25);

void keyDown(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 27: exit(0); break; // ESC - quit game
		
		case 'w': bat1.setSpeed(acceleration); break; // add speed
		case 's': bat1.setSpeed(-acceleration); break;
		
		case 'i': bat2.setSpeed(acceleration); break; // add speed
		case 'k': bat2.setSpeed(-acceleration); break;
		
		case 'r':
			ball.setPos(0, 0);
			ball.setNewBallSpd();
			ball.score[0] = ball.score[1] = 0;
		break;
		
		case 'v': show_vectors = show_vectors ? false : true; // vectors display switcher
	}
}

void keyUp(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'w': bat1.setSpeed(vector2()); break; // set speed to 0
		case 's': bat1.setSpeed(vector2()); break;
		
		case 'i': bat2.setSpeed(vector2()); break; // set speed to 0
		case 'k': bat2.setSpeed(vector2());
	}
}

void renderWorld()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity(); // reset transformations
	
	ball.pongScore(); // enable score mechanics
	
	// enable physics simulation
	bat1.enablePhysics(walls, 2);
	bat2.enablePhysics(walls, 2);
	ball.enablePhysics(boxes, 4);
	
	ball.renderMe(); // render ball
	for(int i = 0; i < 4; ++i) // render all boxes
		boxes[i]->renderMe();
	
	glutSwapBuffers();
}

void reSize(int w, int h) // prevent distortions when window is resized
{
	if(h == 0) h = 1; // prevent division by 0
	
	float ratio = (float)w / h;
	float s = 10.7; // camera scale (zoom)
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
		
	if(ratio < 1)
		gluOrtho2D(-s*ratio, s*ratio, -s, s); // scale projection to match window ratio
	else if(ratio > 1)
		gluOrtho2D(-s, s, -s/ratio, s/ratio); // scale projection to match window ratio
	else
		gluOrtho2D(-s, s, -s, s); // set default 2D orthographic projection if ratio is 1.0
	
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[])
{
	// initialise glut and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(130, 130);
	glutInitWindowSize(960, 540);
	glutCreateWindow("FooEngine");
	glEnable(GL_DEPTH_TEST);
	
	// register callbacks for OS event loop
	glutDisplayFunc(renderWorld);
	glutReshapeFunc(reSize);
	glutIdleFunc(renderWorld);
	glutIgnoreKeyRepeat(1); // ignore standard OS key repeats
	
	// user controls callbacks
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	
	glutMainLoop();
	
	return 0;
}

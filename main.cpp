#include "main.H"

int main(int argc, char *argv[]) {
	int win;
	
	glutInit(&argc, argv);		/* initialize GLUT system */
	
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(WINWIDTH, WINHEIGHT);		/* width=400pixels height=500pixels */
	win = glutCreateWindow("Galaxian - TP1 CG");	/* create window */
	
	/* from this point on the current window is win */
	  
	glClearColor(0.0,0.0,0.0,0.0);	/* set background to black */
	gluOrtho2D(0,400,0,500);		/* how object is mapped to window */
	glutKeyboardFunc(keyCB);		/* set window's key callback */

	myship.setPosy(50.0);
	myship.wp.setSpeed(10);
	myship.wp.setColor(0.2,1,1);

	//glutDisplayFunc(displayAll);
		
	glutMouseFunc(mouseCB);
	glutDisplayFunc(mainScreen);
	glutMainLoop();			    /* start processing events... */

    /* execution never reaches this point */

  return 0;
}

#include<windows.h>
#include <GL/glut.h>
#include <math.h>
#include <bits/stdc++.h>

#define PI 3.1416

using namespace std;
///Global Variable
float boundary = 150; /// Scene boundary
float border = 100;   /// Game boundary

///Agent Parameters
float RAgent = 6.0;
float CAgentX = -15, CAgentY = 0;
///
float RAgent1 = 6.0;
float CAgent1X = 15, CAgent1Y = 0;

float agentSpeed = 5;
bool isAgentDestroyed = false;
bool isAgent1Destroyed = false;


///Enemy Parameters
float REnemy = 4.0;
float REnemy1 = 4.0;
float CEnemyX = -border, CEnemyY = 0.0;
float CEnemy1X = border, CEnemy1Y = 0.0;
int state = 1;
int state1 = 1;
float enemySpeed = 0.1;

//Score count
int scoreCount=0;

//Shape making
void circle(float radius_x, float radius_y)
{
	int i=0;
	float angle = 0.0;

	glBegin(GL_POLYGON);

		for(i = 0; i < 100; i++)
		{
			angle = 2 * PI * i / 100;
			glVertex2f (cos(angle) * radius_x, sin(angle) * radius_y);
			//glVertex2f (cos(angle) * radius_x+5, sin(angle) * radius_y);
		}

	glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINE_STRIP);
        glVertex2f(-border, border);
        glVertex2f(border, border);
        glVertex2f(border, -border);
        glVertex2f(-border, -border);
        glVertex2f(-border, border);
    glEnd();

	if(!isAgentDestroyed)
    {
        glPushMatrix();             //Green Circle
        glTranslatef(CAgentX, CAgentY,0);
        glColor3f(0.0, 1.0, 0.0);
        circle(RAgent,RAgent);
        glPopMatrix();
    }
    if(!isAgent1Destroyed)
    {
        glPushMatrix();
        glTranslatef(CAgent1X, CAgent1Y,0);
        glColor3f(0.0, 0.0, 1.0);
        circle(RAgent1,RAgent1);
        glPopMatrix();
    }

    glPushMatrix();             //Red circle (Static)
	glTranslatef(CEnemyX, CEnemyY,0);
    glColor3f(1.0, 0.0, 0.0);
	circle(REnemy,REnemy);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(CEnemy1X, CEnemy1Y,0);
    glColor3f(1.0, 0.0, 0.0);
	circle(REnemy1,REnemy1);
	glPopMatrix();

	glFlush();
}

void animate()
{
    //Stopping conditions
    if(isAgentDestroyed && isAgent1Destroyed){
        return;
    }
    scoreCount++;

    ///Enemy Movement
    if(state == 1)
    {
        CEnemyX += enemySpeed;
        CEnemyY -= enemySpeed;
        if(CEnemyX>0 && CEnemyY<-border)
        {
            state = 2;
        }
    }
    else if(state == 2)
    {
        CEnemyX += 0;
        CEnemyY += enemySpeed;
        if(CEnemyY>border)
        {
            state = 3;
        }
    }
    else if(state == 3)
    {
        CEnemyX += enemySpeed;
        CEnemyY -= 2*enemySpeed;
        if(CEnemyX>0 && CEnemyY<-border)
        {
            state = 4;
        }
    }
    else if(state == 4)
    {
        CEnemyX -= 2*enemySpeed;
        CEnemyY += enemySpeed;
        if(CEnemyX<-border && CEnemyY>0)
        {
            state = 1;
        }
    }
    ///Enemy1 Movement
    if(state1==1)
    {
        CEnemy1X -= enemySpeed;
        CEnemy1Y += enemySpeed;
        if(CEnemy1X<0 && CEnemy1Y>border)
        {
            state1 = 2;
        }
    }
    else if(state1==2)
    {
        CEnemy1X -= enemySpeed;
        CEnemy1Y -= 2*enemySpeed;
        if(CEnemy1X<0 && CEnemy1Y<-border)
        {
            state1 = 3;
        }
    }
    else if(state1==3)
    {
        CEnemy1X += enemySpeed;
        CEnemy1Y += enemySpeed;
        if(CEnemy1X>=0 && CEnemy1Y>=0)
        {
            state1 = 4;
        }
    }
    else if(state1==4)
    {
        CEnemy1X += enemySpeed;
        CEnemy1Y = 0;
        if(CEnemy1X>border)
        {
            state1 = 1;
        }
    }

    ///Attack Logic
    float distance = sqrt((CAgentX-CEnemyX)*(CAgentX-CEnemyX) + (CAgentY-CEnemyY)*(CAgentY-CEnemyY));
    if(distance <= RAgent+REnemy)
    {
        isAgentDestroyed = true;
    }
    float distance1 = sqrt((CAgentX-CEnemy1X)*(CAgentX-CEnemy1X) + (CAgentY-CEnemy1Y)*(CAgentY-CEnemy1Y));
    if(distance1 <= RAgent+REnemy1)
    {
        isAgentDestroyed = true;
    }
    float distance2 = sqrt((CAgent1X-CEnemyX)*(CAgent1X-CEnemyX) + (CAgent1Y-CEnemyY)*(CAgent1Y-CEnemyY));
    if(distance2 <= RAgent1+REnemy)
    {
        isAgent1Destroyed = true;
    }
    float distance3 = sqrt((CAgent1X-CEnemy1X)*(CAgent1X-CEnemy1X) + (CAgent1Y-CEnemy1Y)*(CAgent1Y-CEnemy1Y));
    if(distance3 <= RAgent1+REnemy1)
    {
        isAgent1Destroyed = true;
    }

    glutPostRedisplay();

    cout << "Score : " << scoreCount <<endl;

    }


void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glOrtho(-boundary, boundary, -boundary, boundary, -boundary, boundary);
}


void spe_key(int key, int x, int y)
{

	switch (key) {

		case GLUT_KEY_LEFT:
                CAgentX -= agentSpeed;

                if(CAgentX<0 && -CAgentX>border-RAgent)
                {
                    isAgentDestroyed = true;
                }
				glutPostRedisplay();
				break;

		case GLUT_KEY_RIGHT:
                CAgentX += agentSpeed;

                if(CAgentX>0 && CAgentX>border-RAgent)
                {
                    isAgentDestroyed = true;
                }
				glutPostRedisplay();
				break;

        case GLUT_KEY_DOWN:
                CAgentY -= agentSpeed;
                if(CAgentY<0 && -CAgentY>border - RAgent)
                {
                    isAgentDestroyed = true;
                }
				glutPostRedisplay();
				break;

		case GLUT_KEY_UP:
                CAgentY += agentSpeed;
                if(CAgentY>0 && CAgentY>border-RAgent)
                {
                    isAgentDestroyed = true;
                }
				glutPostRedisplay();
				break;
	  default:
			break;
	}
}

void keyboard_action(unsigned char key, int x, int y)
{
    if(key == 'l')
    {
        CAgent1X -= agentSpeed;

        if(CAgent1X<0 && -CAgent1X>border-RAgent1)
        {
            isAgentDestroyed = true;
        }
        glutPostRedisplay();

    }
    else if(key == 'r')
    {
        CAgent1X += agentSpeed;

        if(CAgent1X>0 && CAgent1X>border-RAgent1)
        {
            isAgentDestroyed = true;
        }
        glutPostRedisplay();
    }
    else if(key == 'd')
    {
        CAgent1Y -= agentSpeed;

        if(CAgent1Y<0 && -CAgent1Y>border-RAgent1)
        {
            isAgentDestroyed = true;
        }
        glutPostRedisplay();
    }
    else if(key == 'u')
    {
        CAgent1Y += agentSpeed;

        if(CAgent1Y>0 && CAgent1Y>border-RAgent1)
        {
            isAgentDestroyed = true;
        }
        glutPostRedisplay();
    }
}

void mouse_action(int button,int state,int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        glutPostRedisplay();
    }
    else if(button == GLUT_RIGHT_BUTTON)
    {
        glutPostRedisplay();
    }
    else if(button == GLUT_MIDDLE_BUTTON)
    {
        glutPostRedisplay();
    }
}


int main()
{
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Circle");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(animate);
	glutSpecialFunc(spe_key);
	glutKeyboardFunc(keyboard_action);
	glutMouseFunc(mouse_action);
	glutMainLoop();
	return 0;
}

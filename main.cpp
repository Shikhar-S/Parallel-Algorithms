

#include <iostream>
#include "bezier1.h"
#include "primitive.h"
#include <iostream>
#include <algorithm>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "graphics.h"
using namespace std;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
vector<point> curve;
vector<point> control;
int wind_w=1200,wind_h=780;
bool flag_shift;
int i;
void key(unsigned char key,int x,int y){
    if(key==32){
        cout<<"Pressed"<<endl;
        double a[(int)curve.size()+1];
        double b[(int)curve.size()+1];
        int count=0;
        for(vector<point>::iterator it=curve.begin();it!=curve.end();it++)
        {
            
            a[count] = it->x;
            b[count] = it->y;
            printf("%lf %lf\n",a[count],b[count]);
            count+=1;
        }
        func(a,b,count);
    }
    
}
void init() {
    
    //intializing the display window
    
    glutInitWindowPosition(-1,-1);
    glutInitWindowSize(wind_w ,wind_h);			//The resolution of the output Window
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutCreateWindow("Bezier Curve");
    glClearColor(1.0,1.0,1.0,1.0f); 			//the screen is cleared and the screen is made opaque
    glColor3f(1.0,1.0,1.0);
    glViewport(0, 0, wind_w, wind_h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, wind_w,wind_h,0, 0, 1);
}
void disp()
{
    glPointSize(4);
    glClearColor(1.0f,1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);			//choose red color
    //glFrontFace(GL_CW);
    if(control.size()!=0)
    {
        curve.clear();
        for(double t=0;t<=1;t+=0.1)
        {
            point ans=bezier(control, t);
            curve.push_back((ans));
        }
    }
    glBegin(GL_LINE_STRIP);
    for(vector<point>::iterator it=curve.begin();it!=curve.end();it++)
    {
        
        glVertex2f((GLfloat)it->x,(GLfloat) it->y);
        
        //cout<<it->x<<" "<<it->y<<endl;
    }
    glEnd();
    glBegin(GL_POINTS);
    for(vector<point>::iterator it=control.begin();it!=control.end();it++)
    {
        glVertex2f((GLfloat)it->x, (GLfloat)it->y);
    }
    glEnd();

    
   // glVertex2f(0.2f, -0.5f);
    
    glutSwapBuffers();
    //glFlush();
}
bool found(point x)
{
    for(vector<point>::iterator it=control.begin();it!=control.end();it++)
        if(*it==x)
            return true;
    return false;
}
void mouse(int button,int state,int x,int y)
{
    int mod=glutGetModifiers();
    //cout<<mod<<endl;
    if(mod==GLUT_ACTIVE_SHIFT)
    {
        if(flag_shift)
        {
            i=-1;
            flag_shift=false;
        }
        cout<<"Returning\n";
        return;
    }
    
    if(button==GLUT_LEFT_BUTTON)
    {
        if(found(point((double)x, (double)y)))
        {
            return;
        }
        control.push_back(point((double)x, (double)y));
        cout<<control.size()<<"<---Size after adding one pt\n";
    }
    else if(button==GLUT_RIGHT_BUTTON)
    {
        cout<<"Deleted\n";
        for(vector<point>::iterator it=control.begin();it!=control.end();it++)
        {
            if((*it)==point(double(x),double(y)))
            {
                control.erase(it);
                break;
            }
        }
        //cout<<control.size()<<"<---Size after deleting one pt\n";
    }
    glutPostRedisplay();
}
void drag(int x,int y)
{
    
    int n=control.size();
    if(!flag_shift)
    {
        flag_shift=true;
        for(i=0;i<n;i++)
        {
            if((control[i])==point(double(x),double(y)))
            {
                break;
            }
        }
    }
    
    if(i!=(n+1) && flag_shift)
    {
        //cout<<"Changing point\n";
        control[i]=point(double(x),double(y));
        cout<<control.size()<<"<---Size\n";
        glutPostRedisplay();
    }
    else{
        cout<<"No Point Selected\n";
    }
}
int main(int argc,char **argv) {
    flag_shift=false;
    i=-1;
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(disp);
    glutMouseFunc(mouse);
    glutMotionFunc(drag);
    glutKeyboardFunc(key);
    glutMainLoop();
    //cout<<ans.x<<" "<<ans.y<<endl;
}
#pragma GCC diagnostic pop

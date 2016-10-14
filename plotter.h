#include<bits/stdc++.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<string>

using namespace std;


class Plot{
	
	public:	static void init() { 			 	//intializing the display window
	  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	  glutInitWindowPosition(0,0);
	  glutInitWindowSize(1300, 700);			//The resolution of the output Window
	  glutCreateWindow("My Line");		
	  glClearColor(1.0,1.0,1.0,1.0f); 			//the screen is cleared and the screen is made opaque
	  glColor3f(1.0,1.0,1.0);
	  gluOrtho2D(xmin-1000,xmax+1000,ymin-1000,ymax+1000);	// The coordinates of the window (xmin,xmax,ymin,ymax)
	  
	}
	static void setPixel(GLint x,GLint y)			//plotting the coordinates
	{
		glBegin(GL_POINTS);				//Function to plot vertices
		glVertex2i(x,y);
		glEnd();
	}

	static void plotpixel()					//function to plot all coordinates
	{
		glClearColor(1.0f,1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);  
		glColor3f(1.0f, 0.0f, 0.0f);			//choose red color
		FILE* fp=fopen("pixels.txt","r");		//file where all the coordinates are stored
		if(fp==NULL)
		{
			cout << "Invalid file" << endl;
			return;
		}
		char c,nextc=getc(fp);
		string s;
		int flag=0,x,y;
		while(nextc!=EOF)
		{
			c=nextc;
			if(c==' ' || c=='\0' || c=='\n')	
			{
				if(s.length()!=0)
				{
					if(flag==0)
					{
						x=atoi(s.c_str());	//The string in the file is converted into an integer 
						flag=1;
					}
					else
					{
						y=atoi(s.c_str());
						flag=0;
						setPixel(x,ymax-y);	// the y-coordinate is subtracted to get the root on the top and the leaves at the bottom of the screen 
					}
					s="";
				}
				nextc=fgetc(fp);
				continue;
			}
			s.append(1,c);
			nextc=fgetc(fp);
		}
		glFlush();						// Forces execution of OpenGl commands in finite time
	}
};

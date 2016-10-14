#include<stdio.h>
#include<stdlib.h>

struct point{
	int x,y;
	point(int a,int b): x(a),y(b){

	}
};


class primitives{
        // Sub Routine For Midpoint Circle Drawing Algorithm
	public: static void drawCircle(point center,int radius){
			int a=center.x,b=center.y;
			int x=0;
			int y=radius;
			int d = 1 - radius;			//The decision variable		
			//Second order derivatives are used
			int deltaE = 3;				
			int deltaSE = -2*radius + 5;
			//The eight point symmetry of a circle is used to plot eight points in all the eight octants
				fprintf(fp,"%d %d\n",a+x,b+y);
		 		fprintf(fp,"%d %d\n",a+-x,b+y);
				fprintf(fp,"%d %d\n",a+x,b+-y);
				fprintf(fp,"%d %d\n",a+-x,b+-y);
				fprintf(fp,"%d %d\n",a+y,b+x);
				fprintf(fp,"%d %d\n",a+-y,b+x);
				fprintf(fp,"%d %d\n",a+y,b+-x);
				fprintf(fp,"%d %d\n",a+-y,b+-x);
			while(y>x){
		 		if(d<0){				//East pixel is chosen
					d+=deltaE;
					deltaE+=2;
					deltaSE+=2;
				}
				else{					//South East Pixel is chosen and y is decremented
					d+= deltaSE;
					deltaE+=2;
					deltaSE+=4;
					y--;
				}
				x++;
				fprintf(fp,"%d %d\n",a+x,b+y);
		 		fprintf(fp,"%d %d\n",a+-x,b+y);
				fprintf(fp,"%d %d\n",a+x,b+-y);
				fprintf(fp,"%d %d\n",a+-x,b+-y);
				fprintf(fp,"%d %d\n",a+y,b+x);
				fprintf(fp,"%d %d\n",a+-y,b+x);
				fprintf(fp,"%d %d\n",a+y,b+-x);
				fprintf(fp,"%d %d\n",a+-y,b+-x);
			}
	}
	// Sub Routines For Bresenham's Line Drawing Algorithm
	
	//SubRoutine to move a point from any of the eight octants to the zeroth octant
	public:  static   point toOctantZero(int octant,point a)
			{
				int x=a.x,y=a.y;
				switch(octant)  
				{
					case 0: return point(x, y);
				    case 1: return point(y, x);
				    case 2: return point(y, -x);
				    case 3: return point(-x, y);
				    case 4: return point(-x, -y);
				    case 5: return point(-y, -x);
				    case 6: return point(-y, x);
				    case 7: return point(x, -y);
				}
			     return point(0,0); //to silence warnings
			}
		//Method to move any point from the zeroth octant to any of the eight octants
		static	point fromOctantZero(int octant,point a)
			{
				int x=a.x,y=a.y;
				switch(octant) 
				{
					case 0: return point(x, y);
				    case 1: return point(y, x);
				    case 2: return point(-y, x);
				    case 3: return point(-x, y);
				    case 4: return point(-x, -y);
				    case 5: return point(-y, -x);
				    case 6: return point(y, -x);
				    case 7: return point(x, -y);
				} 
			     return point(0,0); //to silence warnings
			}
		//Method to find out the octant of a given line
		static	int getOctant(point a,point b)
			{
				//find octant here
				if(b.x-a.x==0)
					return 1;
				double slope=(b.y-a.y)/((b.x-a.x)*1.0);
				if(slope>=0 && slope<=1)
					return (a.x<b.x)?0:4; //0 or 4
				else if(slope>1)
					return (a.x<b.x)?1:5; //1 or 5
				else if(slope<0 && slope>=-1)
					return (a.x>b.x)?3:7; // 3 or 7
				else if(slope<-1)
					return (a.x>b.x)?2:6;// 2 or 6
				return -1;
			}
		//Bresenham's LIne Drawing Algorithm 
		static	void drawLine(point a,point b)
			{
				int octant=getOctant(a,b);
				if(octant==-1)
				{
					cout<<"ERROR\n";
					return;
				}
				a=toOctantZero(octant,a);
				b=toOctantZero(octant,b);
				int dx=b.x-a.x,dy=b.y-a.y;
				int D=2*dy-dx;						// The decision variable to find out the next point
				int y=a.y;
				for(int x=a.x;x<=b.x;x++)
				{
					point pixel=(fromOctantZero(octant,point(x,y)));
					fprintf(fp,"%d %d\n",pixel.x,pixel.y);
					if(D>=0)
					{
						y+=1;
						D-=dx;
					}
					D+=dy;
				}
			}


};














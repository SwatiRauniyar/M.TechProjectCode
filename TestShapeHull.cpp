// standard includes
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <utility>
#include <vector>

#include "ShapeHull2D.h"

using namespace shapehull;

using namespace std;



#define NENDS 2           /* number of end "points" to draw */

GLdouble width, height;   /* window width and height */
int wd;                   /* GLUT window handle */
int ends1[NENDS][2];       /* array of 2D points */
int minx=999,miny=999,maxx=-999,maxy=-999;

vector<pair<double, double> > pointVec;
vector<pair<int,int> > *boundary;
vector <int>v;
vector<pair<int, int>> v1;

void init(void)
{
    width  = 1280.0;                 /* initial window width and height, */
    height = 800.0;                  /* within which we draw. */
    ends1[0][0] = (int)(0.25*width);  /* (0,0) is the lower left corner */
    ends1[0][1] = (int)(0.75*height);
    ends1[1][0] = (int)(0.75*width);
    ends1[1][1] = (int)(0.25*height);
    
    return;
}
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    int i,triangleAmount = 20;
    GLfloat twicePi = 2.0f * 3.14159265;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    //  glColor3f(1,0,0);
    for(i = 0; i <= triangleAmount;i++)
        glVertex2f(x + (radius * cos(i *  twicePi / triangleAmount)),y + (radius * sin(i * twicePi / triangleAmount)));
    glEnd();
}


void pointset(void)
{  // My modification 1
  // (*boundary) contain index of boundary vertices in pointVec 
/*  int n= (*boundary).size();
  
  for(int i=0; i<n; i++)
  {   v.push_back((*boundary)[i].first);
      v.push_back((*boundary)[i].second);
   }
n= v.size();
cout<<"Vector v size before sorting & removing duplicates " <<n<<endl;

// unique & sorted elements in Vector v
//sort( v.begin(), v.end() );
//v.erase( unique( v.begin(), v.end() ), v.end() );



    for(int i=0; i<n; i++)
{   // std::cout<<"i "<<i<<" n "<<n<<std::endl;
   for(int j=i+1; j<n; j++)
   {  // std::cout<<"j "<<j<<std::endl;
       if(v.at(i)== v.at(j))
         {  v.erase(v.begin()+j);
            //std::cout<<"Vector size after erase "<<k.size()<<std::endl;
            n--;
            j--;
         }
   }
} 

n= v.size();
cout<<"Vector v size after removing duplicate " <<n<<endl;
cout<<"Contour Simplification- removing collinear points by calculating area of triangle formed by 3 consecutive co-ordinates." <<endl;
 for(int i=0; i<n;)
   {   int x1= pointVec[v.at(i)].first;
       int y1= pointVec[v.at(i)].second;
       int x2= pointVec[v.at((i+1)%n)].first;
       int y2= pointVec[v.at((i+1)%n)].second;
       int x3= pointVec[v.at((i+2)%n)].first;
       int y3= pointVec[v.at((i+2)%n)].second;
       cout<<"Area of ("<<x1<<", "<<y1<<"), ("<<x2<<", "<<y2<<"), ("<<x3<<", "<<y3<<") = "<<fabs(((x2-x1)*(y3-y1)- (x3- x1)*(y2-y1)))<<endl;
       if(fabs(((x2-x1)*(y3-y1)- (x3- x1)*(y2-y1)))==0)
           {  v.erase(v.begin()+i+1);
              n--;
              continue;
           } 
      i++; 
 }   
cout<<"No. of co-ordinates after removing collinear points in boundary: "<<v.size()<<endl;

 glPointSize(6.0);
    glColor3f(0.0, 0.0, 0.0);
    for(int i=0;i<v.size();i++)
        drawFilledCircle(pointVec[v.at(i)].first,pointVec[v.at(i)].second,3.0);
    glColor3f(1.0, 0.2, 0.2);
    glLineWidth(3.0);
    glEnable( GL_LINE_SMOOTH );
    glEnable( GL_POLYGON_SMOOTH );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
    glColor3f(0.18, 0.69, 0.25);
    
cout<<"Only those Vertex co-ordinates from input which are used for boundary drawing:"<<endl;

        for(int i=0;i<v.size();i++)
           { glBegin(GL_LINES);
            // pointVec contains input vertices
           std::cout<<pointVec[v.at(i)].first<<" "<<pointVec[v.at(i)].second<<endl;
           std::cout<<pointVec[v.at((i+1)%v.size())].first<<" "<<pointVec[v.at((i+1)%v.size())].second<<endl;
            glVertex2f(pointVec[v.at(i)].first,pointVec[v.at(i)].second);
            glVertex2f(pointVec[v.at((i+1)%v.size())].first,pointVec[v.at((i+1)%v.size())].second);
            glEnd();
            
        
    }  */
// My modification 2

for(auto & val : *boundary)
    {
      std::pair<int, int> indices=val;
      v1.push_back(make_pair(indices.first, indices.second));
     }

int n= v1.size();
cout<<"Contour Simplification- removing collinear points by calculating area of triangle formed by 3 consecutive co-ordinates." <<endl;
 int i=0;
 label: for( ; i<n;)
   {   int x1= pointVec[v1[i].first].first;
       int y1= pointVec[v1[i].first].second;
       int x2= pointVec[v1[i].second].first;
       int y2= pointVec[v1[i].second].second;
       int x3=0, y3=0, j=0;
       for( ; j<n; j++)
        {  if(v1[i].second==v1[j].first)
            { x3= pointVec[v1[j].second].first;
              y3= pointVec[v1[j].second].second;
              break;
            }
         }
       cout<<"Area of ("<<x1<<", "<<y1<<"), ("<<x2<<", "<<y2<<"), ("<<x3<<", "<<y3<<") = "<<fabs(((x2-x1)*(y3-y1)- (x3- x1)*(y2-y1)))<<endl;
       if(fabs(((x2-x1)*(y3-y1)- (x3- x1)*(y2-y1)))==0)
           {  v1[i].second= v1[j].second;
              v1.erase(v1.begin()+j);
              n--;
              goto label;
           } 
       i++; 
 }   

    glPointSize(6.0);
    glColor3f(0.0, 0.0, 0.0);
    for(int i=0;i<v1.size();i++)
       { drawFilledCircle(pointVec[v1[i].first].first,pointVec[v1[i].first].second,3.0);
         drawFilledCircle(pointVec[v1[i].second].first,pointVec[v1[i].second].second,3.0);
        }
    glColor3f(1.0, 0.2, 0.2);
    glLineWidth(3.0);
    glEnable( GL_LINE_SMOOTH );
    glEnable( GL_POLYGON_SMOOTH );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
    glColor3f(0.18, 0.69, 0.25);
    
//cout<<"Only those Vertex co-ordinates from input which are used for boundary drawing:"<<endl;

        for(int i=0;i<v1.size();i++)
           { glBegin(GL_LINES);
            // pointVec contains input vertices
        //   std::cout<<pointVec[v.at(i)].first<<" "<<pointVec[v.at(i)].second<<endl;
         //  std::cout<<pointVec[v.at((i+1)%v.size())].first<<" "<<pointVec[v.at((i+1)%v.size())].second<<endl;
            glVertex2f(pointVec[v1[i].first].first,pointVec[v1[i].first].second);
            glVertex2f(pointVec[v1[i].second].first,pointVec[v1[i].second].second);
            glEnd();
            
        
    }
// Original algorithm

 /*   glPointSize(6.0);
    glColor3f(0.0, 0.0, 0.0);
    for(int i=0;i<pointVec.size();i++)
        drawFilledCircle(pointVec[i].first,pointVec[i].second,3.0);
    glColor3f(1.0, 0.2, 0.2);
    glLineWidth(3.0);
    glEnable( GL_LINE_SMOOTH );
    glEnable( GL_POLYGON_SMOOTH );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
    glColor3f(0.18, 0.69, 0.25);
    
    
for(auto & val : *boundary)
    {
    std::pair<int, int> indices=val;
        
            glBegin(GL_LINES);
            glVertex2f(pointVec[indices.first].first,pointVec[indices.first].second);
            glVertex2f(pointVec[indices.second].first,pointVec[indices.second].second);
            glEnd();
            
        
    }  */
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    pointset();
    glFlush();
    return;
}

/* Called when window is resized,
 also when window is first created,
 before the first call to display(). */
void reshape(int w, int h)
{
    /* save new screen dimensions */
    width = (GLdouble) w;
    height = (GLdouble) h;
    
    /* tell OpenGL to use the whole window for drawing */
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    
    /* do an orthographic parallel projection with the coordinate
     system set to first quadrant, limited by screen/window size */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(minx-20.0,maxx+20.0,miny-20.0,maxy+20.0, -1.f, 1.f);
    return;
}

void kbd(unsigned char key, int x, int y)
{
    switch((char)key) {
        case 'q':
        case 27:    /* ESC */
            glutDestroyWindow(wd);
            exit(0);
        default:
            break;
    }
    
    return;
}

void loadPointSet(string name)
	{
		pointVec.clear();
		ifstream file(name.data());

		if (file)
		{
			while (!file.eof())
			{
				float x, y;
				file >> x >> y;
	if(x>maxx)
            maxx=x;
        if(x<minx)
            minx=x;
        if(y>maxy)
            maxy=y;
        if(y<miny)
	miny=y;

// Storing input file points in pointVec in form of pair of x and y coordinate
				if (!file.eof())
					pointVec.push_back(pair<double, double>(x, y));
			}
		cout<<"No. of input co-ordinates: "<<pointVec.size()<<endl;
		}
		else
		{
			cerr << "ERROR: input file " << name << " could not be read." << endl;
			exit(2);
		}

		file.close();

		if (pointVec.size() < 3)
		{
			cerr << "ERROR: input file " << name << " contains less than 3 points." << endl;
			exit(3);
		}
	}

int main(int argc, char **argv)
{
	string filename;
		
	if(argc>=2){
		filename=string(argv[1]);				
	}
	else{
		std::cout<< "Usage" << argv[0] << " filename" << std::endl;
		return 0;
	}
	
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(250, 250);
    wd = glutCreateWindow("Shapehull 2D");
	
	
    loadPointSet(filename);	
    ShapeHull2D shapeHullIstance(pointVec);
    boundary=shapeHullIstance.extractBoundary();
	
	
    glutReshapeFunc(reshape);
    glutKeyboardFunc(kbd);
    glutDisplayFunc(display);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3.0);
    glutMainLoop();
    exit(0);
    return 0;
}

// FBO Example
//
// A demonstration of using an FBO in your own programs.
// Uses GLee for extension setup
// Note: This isn't meant to indicate good programming style, just act as an example
//

#include <glut/glut.h>
#include <cstdlib>
#include <cstdio>


GLuint fbo;					// Our handle to the FBO
GLuint depthBuffer;			// Our handle to the depth render buffer
GLuint img;					// Our handle to a texture
GLuint f, v, p;


const int width = 640;		// The hight of the texture we'll be rendering to
const int height = 480;		// The width of the texture we'll be rendering to

// Used for drawing the 3D cube with our rendered texture on it

void init(GLvoid)     
{
	
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.2f, 0.5f);
	glClearDepth(1.0f);					
	glEnable(GL_DEPTH_TEST);			
	glDepthFunc(GL_LEQUAL);				
	glViewport(0,0,width,height);
	
	// Setup our FBO
	glGenFramebuffersEXT(1, &fbo);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
	
	// Create the render buffer for depth	
	glGenRenderbuffersEXT(1, &depthBuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depthBuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, width, height);
	
	// Now setup a texture to render to
	glGenTextures(1, &img);
	glBindTexture(GL_TEXTURE_2D, img);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	//  The following 3 lines enable mipmap filtering and generate the mipmap data so rendering works
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//	glGenerateMipmapEXT(GL_TEXTURE_2D);
	
	// And attach it to the FBO so we can render to it
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, img, 0);
	
	// Attach the depth render buffer to the FBO as it's depth attachment
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depthBuffer);
	
	
	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
		exit(1);
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);	// Unbind the FBO for now
}

void ShutDown(GLvoid)
{
	glDeleteFramebuffersEXT(1, &fbo);
	glDeleteRenderbuffersEXT(1, &depthBuffer);
	glDeleteTextures(1,&img);
}

void reshape(int w,int h)			
{
	glViewport( 0, 0, w, h );
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();					
	if ( h==0 )							
		gluPerspective(80,(float)w,1.0,5000.0);
	else
		gluPerspective(80,(float)w/(float)h,1.0,5000.0);
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();					
}

void keyboard(unsigned char key,int x,int y)  
{
	switch(key)
	{
		case 27:				// When Escape Is Pressed...
			ShutDown();
			exit(0);			// Exit The Program
			break;				
		default:				
			break;
	}
}

void idle(void)
{
	glutPostRedisplay();
}

void display(void)   
{
	// First we bind the FBO so we can render to it
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
	
	// Save the view port and set it to the size of the texture
	glPushAttrib(GL_VIEWPORT_BIT);
	glViewport(0,0,width,height);
	
	// Then render as normal
	// Today's scene is a wonderful multi-coloured spinning cube ;)
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();
	
	glTranslatef(0.0f,0.0f,-0);
	
	
	glPushMatrix();
	
	glOrtho (0, width, height, 0, 0, 1);
	
	
	glColor3f(1,0,0);
	
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(326,214,0);
	glVertex3f(332, 133, 0);
	glVertex3f(369, 112, 0);
	glVertex3f(430, 90, 0);
	glVertex3f(485, 132,0);
	glVertex3f(466, 207,0);
	glVertex3f(460, 250,0);
	glVertex3f(395, 311,0);
	glVertex3f(340, 344,0);
	glVertex3f(256, 282,0);
	glVertex3f(171, 185,0);
	glVertex3f(152, 122,0);
	glVertex3f(247, 82,0);
	glVertex3f(307, 103,0);
	glVertex3f(332, 133, 0);
	glEnd();
	glFlush();
	
	
	glPopMatrix();
	
	
	// Restore old view port and set rendering back to default frame buffer
	glPopAttrib();
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	
	glClearColor(0.0f, 0.0f, 0.2f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();
	// Now bind the texture to use it
	glBindTexture(GL_TEXTURE_2D, img);
	//	If you enabled the mipmap filtering on setup earlier then you'll need to uncomment the line
	//	below so OpenGL can generate all the mipmap data for the new main image each frame
	//	glGenerateMipmapEXT(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	
	glTranslatef(0.0f,0.0f,0);
	
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	
	glOrtho (0, width, height, 0, 0, 1);
	
	
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f( 0.0f, 0.0f, 1.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 0, 0,  0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( width, 0,  0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( width,  height,  0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 0,  height,  0);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	
	
	glutSwapBuffers ( );
	// Swap The Buffers To Not Be Left With A Clear Screen
}
//Function from: http://www.evl.uic.edu/aej/594/code/ogl.cpp
//Read in a textfile (GLSL program)
// we need to pass it as a string to the GLSL driver
char *textFileRead(char *fn) 
{
	FILE *fp;
	char *content = NULL;
	
	int count=0;
	
	if (fn != NULL) {
		
		fp = fopen(fn,"rt");
		
		if (fp != NULL) {
			
			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);
			
			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
			
		}
	}
	
	return content;
}

void printLog(GLuint obj)
{
	int infologLength = 0;
	int maxLength;
	
	if(glIsShader(obj))
		glGetShaderiv(obj,GL_INFO_LOG_LENGTH,&maxLength);
	else
		glGetProgramiv(obj,GL_INFO_LOG_LENGTH,&maxLength);
	
	char * infoLog = new char[maxLength];
	
	if (glIsShader(obj))
		glGetShaderInfoLog(obj, maxLength, &infologLength, infoLog);
	else
		glGetProgramInfoLog(obj, maxLength, &infologLength, infoLog);
	
	if (infologLength > 0)
		printf("%s\n",infoLog);
	else
		printf("errir\n");
	
	delete [] infoLog;
	
}




void setShaders() {
	
	char *vs,*fs;
	
	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);	
	
	vs = textFileRead("./tiney.vert");
	fs = textFileRead("./tiney.frag");
	
	const char * vv = vs;
	const char * ff = fs;
	
	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);
	
	printf("x\n");
	free(vs);free(fs);
	
	printf("y\n");
	glCompileShader(v);
	printLog(v);
	
	
	glCompileShader(f);
	printLog(f);
	
	p = glCreateProgram();
	
	glAttachShader(p,v);
	glAttachShader(p,f);
	
	printf("z\n");
	glLinkProgram(p);
	printLog(p);
	glUseProgram(p);
}
int main(int argc, char* argv[])
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE );		// Display Mode
	glutInitWindowSize(width,height);
	glutCreateWindow( "" );
	
	
	init();
	setShaders();
	
	// Setup the various call back functions GLUT requires
	glutDisplayFunc     ( display );  
	glutReshapeFunc     ( reshape );
	glutKeyboardFunc    ( keyboard );
	glutIdleFunc		( idle );
	glutMainLoop        ( );			// Run the main GLUT loop for rendering
	
	return 0;
}


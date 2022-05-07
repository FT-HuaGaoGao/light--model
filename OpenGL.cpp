# include<GL/glut.h>
#include<stdio.h>

int ambient = 0;
int diffuse = 0;
int specular = 0;

void init(void) 
{
    //光照参数初始化全位于此处
    GLfloat mat_specular[] = { 1.0,1.0,1.0,1.0 }; //镜面反射参数
    GLfloat mat_shininess[] = { 100.0 }; //高光指数
   

    GLfloat light_1[] = { 2.0,0.0,0.0,0.0 }; //设置光源颜色
    GLfloat light_2[] = { 0.0,0.0,1.0,0.0 }; //设置光源颜色
    GLfloat light_position1[] = { 5.0,5.0,5.0,1.0 }; //点光源位置
    GLfloat light_position2[] = { -5.0,-5.0,5.0,1.0 }; //点光源位置


    glClearColor(0.0, 0.0, 0.0, 0.0); //背景色
    glShadeModel(GL_SMOOTH); //多变形填充模式

//材质属性：如何反射光线（材料环境、散射、镜面颜色、光泽度）
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //使用镜面材质颜色
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess); //使用光泽度


//第一个光源
    glLightfv(GL_LIGHT0, GL_POSITION, light_position1); //定义光源的位置

//第二个光源
    glLightfv(GL_LIGHT1, GL_POSITION, light_position2); //定义光源的位置

    if (ambient == 1)
    {
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_1); //定义散射光
        glLightfv(GL_LIGHT1, GL_AMBIENT, light_2); //定义散射光
    }

    if (diffuse==1)
    {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_1); //定义散射光
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light_2); //定义散射光
    }
    if (specular==1)
    {
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_1); //定义镜面光
        glLightfv(GL_LIGHT1, GL_SPECULAR, light_2); //定义镜面光
    }

    glEnable(GL_LIGHTING); //打开光源
    glEnable(GL_LIGHT0); //启动 0 号光源    
    glEnable(GL_LIGHT1); //启动 1 号光源
    glEnable(GL_DEPTH_TEST); //打开深度测试  
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glNewList(1, GL_COMPILE);
    glColor3f(0.0, 0.0, 1.0);
    init();
	glutSolidTeapot(0.5);
	glEndList();
	glCallList(1);
   
    glFlush();
    glutSwapBuffers();
}
void mykeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        ambient = 1;
        diffuse = 0;
        specular = 0;
        printf("泛光模型\n");
        break;
    case '2':
        ambient = 1;
        diffuse = 1;
        specular = 0;
        printf("漫反射模型\n");
        break;
    case '3':
        ambient = 1;
        diffuse = 1;
        specular = 1;
        printf("镜面反射模型\n");
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(400, 400);
	glutCreateWindow("光照模型");
    
    glutKeyboardFunc(mykeyboard);
    
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}
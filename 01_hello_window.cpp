#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

//注册一个回调函数，在每次窗口大小被调整的时候被调用
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/*
这里我们检查用户是否按下了返回键(Esc)
如果没有按下，glfwGetKey将会返回GLFW_RELEASE。如果用户的确按下了返回键，
我们将通过glfwSetwindowShouldClose使用把WindowShouldClose属性设置为 true的方法关闭GLFW。
下一次while循环的条件检测将会失败，程序将会关闭
*/
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	//初始化GLFW
	glfwInit();
	//设置GLFW的主要版本号(Major)和次要版本号(Minor)都为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//设置GLFW使用核心模式(Core-profile),意味着我们只能使用OpenGL的一个子集，不再需要向后兼容特性
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建窗口对象
	GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "未能成功创建窗口" << endl;
		glfwTerminate(); //释放所有资源为GLFW的下一次初始化设置做准备
		return -1;
	}

	//将窗口的上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(window);

	//初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "未能成功初始化GLAD" << endl;
		return -1;
	}

	//设置视口
	glViewport(0, 0, 800, 600);	//前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度

	//注册窗口变化监听
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	//设置渲染循环(Render Loop)
	while (!glfwWindowShouldClose(window)) //glfwWindowShouldClose函数在每次循环的开始前检查一次GLFW是否被要求退出，如果是的话该函数返回true然后渲染循环便结束了，之后为我们就可以关闭应用程序了
	{
		//输入
		processInput(window);

		//渲染指令
		//...
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //glClearColor来设置清空屏幕所用的颜色
		glClear(GL_COLOR_BUFFER_BIT); //glClear函数来清空屏幕的颜色缓冲

		//检查并调用事件，交换缓冲
		glfwPollEvents(); //glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数
		glfwSwapBuffers(window); //glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上
	}

	//释放所有资源为GLFW的下一次初始化设置做准备
	glfwTerminate();

	return 0;
}
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

//ע��һ���ص���������ÿ�δ��ڴ�С��������ʱ�򱻵���
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/*
�������Ǽ���û��Ƿ����˷��ؼ�(Esc)
���û�а��£�glfwGetKey���᷵��GLFW_RELEASE������û���ȷ�����˷��ؼ���
���ǽ�ͨ��glfwSetwindowShouldCloseʹ�ð�WindowShouldClose��������Ϊ true�ķ����ر�GLFW��
��һ��whileѭ����������⽫��ʧ�ܣ����򽫻�ر�
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
	//��ʼ��GLFW
	glfwInit();
	//����GLFW����Ҫ�汾��(Major)�ʹ�Ҫ�汾��(Minor)��Ϊ3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//����GLFWʹ�ú���ģʽ(Core-profile),��ζ������ֻ��ʹ��OpenGL��һ���Ӽ���������Ҫ����������
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//�������ڶ���
	GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "δ�ܳɹ���������" << endl;
		glfwTerminate(); //�ͷ�������ԴΪGLFW����һ�γ�ʼ��������׼��
		return -1;
	}

	//�����ڵ�����������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);

	//��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "δ�ܳɹ���ʼ��GLAD" << endl;
		return -1;
	}

	//�����ӿ�
	glViewport(0, 0, 800, 600);	//ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶�

	//ע�ᴰ�ڱ仯����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	//������Ⱦѭ��(Render Loop)
	while (!glfwWindowShouldClose(window)) //glfwWindowShouldClose������ÿ��ѭ���Ŀ�ʼǰ���һ��GLFW�Ƿ�Ҫ���˳�������ǵĻ��ú�������trueȻ����Ⱦѭ��������ˣ�֮��Ϊ���ǾͿ��Թر�Ӧ�ó�����
	{
		//����
		processInput(window);

		//��Ⱦָ��
		//...
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //glClearColor�����������Ļ���õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT); //glClear�����������Ļ����ɫ����

		//��鲢�����¼�����������
		glfwPollEvents(); //glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����
		glfwSwapBuffers(window); //glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ��
	}

	//�ͷ�������ԴΪGLFW����һ�γ�ʼ��������׼��
	glfwTerminate();

	return 0;
}
#include "PhysicsDebugRenderer.h"
#include "Game.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Camera.h"


#include "GL\glew.h"

PhysicsDebugRenderer::PhysicsDebugRenderer()
{
	
}


PhysicsDebugRenderer::~PhysicsDebugRenderer()
{

}

void PhysicsDebugRenderer::drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor)
{

	//glm::dvec3 offset = Game::GetSceneManager().GetActiveScene()->GetActiveCamera().GetPosition();

	//glBegin(GL_LINES);
	//glColor3f(
	//	static_cast<float>(fromColor.getX()),
	//	static_cast<float>(fromColor.getY()),
	//	static_cast<float>(fromColor.getZ()));
	//
	//glVertex3d(
	//	static_cast<float>(from.getX() - offset.x),
	//	static_cast<float>(from.getY() - offset.y),
	//	static_cast<float>(from.getZ() - offset.z));
	//
	//glColor3f(
	//	static_cast<float>(toColor.getX()),
	//	static_cast<float>(toColor.getY()),
	//	static_cast<float>(toColor.getZ()));
	//
	//glVertex3d(
	//	static_cast<float>(to.getX() - offset.x),
	//	static_cast<float>(to.getY() - offset.y),
	//	static_cast<float>(to.getZ() - offset.z));
	//glEnd();

	//glPopMatrix();

	glBegin(GL_LINES);
	glColor3f(
		static_cast<float>(fromColor.getX()),
		static_cast<float>(fromColor.getY()),
		static_cast<float>(fromColor.getZ()));

	glVertex3d(
		static_cast<float>(from.getX()),
		static_cast<float>(from.getY()),
		static_cast<float>(from.getZ()));

	glColor3f(
		static_cast<float>(toColor.getX()),
		static_cast<float>(toColor.getY()),
		static_cast<float>(toColor.getZ()));

	glVertex3d(
		static_cast<float>(to.getX()),
		static_cast<float>(to.getY()),
		static_cast<float>(to.getZ()));
	glEnd();

}

void PhysicsDebugRenderer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	drawLine(from, to, color, color);
}

void PhysicsDebugRenderer::drawSphere(const btVector3& p, btScalar radius, const btVector3& color)
{

	glm::dvec3 offset = Game::GetSceneManager().GetActiveScene()->GetActiveCamera().GetPosition();

	glColor4f(static_cast<float>(color.getX()), static_cast<float>(color.getY()), static_cast<float>(color.getZ()), btScalar(1.0f));
	glPushMatrix();
	glTranslatef(static_cast<float>(p.getX() - offset.x), static_cast<float>(p.getY() - offset.y), static_cast<float>(p.getZ() - offset.z));

	int lats = 5;
	int longs = 5;

	int i, j;
	for (i = 0; i <= lats; i++) {
		float lat0 = SIMD_PI * (-float(0.5) + (float)(i - 1) / lats);
		float z0 = radius*sin(lat0);
		float zr0 = radius*cos(lat0);

		float lat1 = SIMD_PI * (-float(0.5) + (float)i / lats);
		float z1 = radius*sin(lat1);
		float zr1 = radius*cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= longs; j++) {
			float lng = 2 * SIMD_PI * (float)(j - 1) / longs;
			float x = cos(lng);
			float y = sin(lng);

			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(x * zr0, y * zr0, z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(x * zr1, y * zr1, z1);
		}
		glEnd();
	}

	glPopMatrix();
}



void PhysicsDebugRenderer::drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha)
{
	glm::dvec3 offset = Game::GetSceneManager().GetActiveScene()->GetActiveCamera().GetPosition();
	//	if (m_debugMode > 0)
	{
		const btVector3	n = btCross(b - a, c - a).normalized();
		glBegin(GL_TRIANGLES);
		glColor4f(static_cast<float>(color.getX()), static_cast<float>(color.getY()), static_cast<float>(color.getZ()), alpha);

		glNormal3d(static_cast<float>(n.getX()), static_cast<float>(n.getY()), static_cast<float>(n.getZ()));

		glVertex3d(static_cast<float>(a.getX() - offset.x), static_cast<float>(a.getY() - offset.y), static_cast<float>(a.getZ() - offset.z));
		glVertex3d(static_cast<float>(b.getX() - offset.x), static_cast<float>(b.getY() - offset.y), static_cast<float>(b.getZ() - offset.z));
		glVertex3d(static_cast<float>(c.getX() - offset.x), static_cast<float>(c.getY() - offset.y), static_cast<float>(c.getZ() - offset.z));
		glEnd();
	}
}

void PhysicsDebugRenderer::setDebugMode(int debugMode)
{
	m_debugMode = debugMode;

}

void PhysicsDebugRenderer::draw3dText(const btVector3& location, const char* textString)
{
	//glRasterPos3f(static_cast<float>(location.x()), static_cast<float>(location.y()), static_cast<float>(location.z()));
}

void PhysicsDebugRenderer::reportErrorWarning(const char* warningString)
{
	//printf("%s\n", warningString);
}

void PhysicsDebugRenderer::drawContactPoint(const btVector3& pointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
	{
		//btVector3 to = pointOnB + normalOnB * 1;//distance;
		//const btVector3&from = pointOnB;
		//glColor4f(static_cast<float>(color.getX()), static_cast<float>(color.getY()), static_cast<float>(color.getZ()), 1.f);
		//glBegin(GL_LINES);
		//glVertex3d(static_cast<float>(from.getX()), static_cast<float>(from.getY()), static_cast<float>(from.getZ()));
		//glVertex3d(static_cast<float>(to.getX()), static_cast<float>(to.getY()), static_cast<float>(to.getZ()));
		//glEnd();
	}
}
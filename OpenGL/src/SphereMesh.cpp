#include "SphereMesh.h"
#include <glm/gtc/constants.hpp>

#include <iostream>
#include <iterator>
#include <algorithm>


SphereMesh::SphereMesh(GLuint rings, GLuint sectors, GLfloat radius)
	:Shape(rings), m_radius(radius), m_sectors(sectors)
{}

SphereMesh::~SphereMesh()
{}

void SphereMesh::generate()
{

	for (unsigned int ring = 0; ring < m_size; ++ring)
	{
		
		GLfloat lontitiude = map(static_cast<GLfloat>(ring), 0.0f, static_cast<GLfloat>(m_size) + 1, -glm::pi<GLfloat>(), glm::pi<GLfloat>());
		for (unsigned int point = 0; point < m_sectors; ++point)
		{
			GLfloat latituide = map(static_cast<GLfloat>(point), 0.0f, static_cast<GLfloat>(m_sectors) + 1, 0.0f, 2.0f * glm::pi<GLfloat>());
			GLfloat x = m_radius * glm::sin(lontitiude) * glm::cos(latituide);
			GLfloat y = m_radius * glm::sin(lontitiude) * glm::sin(latituide);
			GLfloat z = m_radius * glm::cos(lontitiude);

			GLfloat texcordx = map(static_cast<GLfloat>(point), 0.0f, static_cast<GLfloat>(m_size), 0.0f, 1.0f);
			GLfloat texcordy = map(static_cast<GLfloat>(ring), 0.0f, static_cast<GLfloat>(m_size), 0.0f, 1.0f);

			m_texcords.emplace_back(glm::vec2(texcordx, texcordy));
			m_vertecies.emplace_back(glm::vec3(x, y, z));
		}
	}
	
	for (unsigned int ring = 0; ring < m_vertecies.size() - m_size - 1; ++ring)
	{
		if (ring == 0)
		{
			m_indicies.emplace_back(0);
			m_indicies.emplace_back(1);
			m_indicies.emplace_back(m_size);

			m_indicies.emplace_back(1);
			m_indicies.emplace_back(m_size);
			m_indicies.emplace_back(m_size + 1);
		}
		for (unsigned int i = 0; i < 6; ++i)
		{
			m_indicies.emplace_back(m_indicies[i] + ring);
		}
	}

}

GLfloat SphereMesh::map(GLfloat value, GLfloat low1, GLfloat max1, GLfloat low2, GLfloat max2)
{
	return low2 + (max2 - low2) * ((value - low1) / (max1 - low1));
}

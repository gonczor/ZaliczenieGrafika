#include "SolidSphere.h"
#include <glm/gtc/constants.hpp>

#include <iostream>
#include <iterator>
#include <algorithm>


SolidSphere::SolidSphere(GLuint size, GLfloat radius)
	:Shape(size), m_radius(radius)
{
}


SolidSphere::~SolidSphere()
{}

void SolidSphere::generate()
{
	for (unsigned int ring = 0; ring < m_size; ++ring)
	{
		
		GLfloat lontitiude = map(static_cast<GLfloat>(ring), 0.0f, static_cast<GLfloat>(m_size) - 1, glm::pi<GLfloat>(), -glm::pi<GLfloat>());
		for (unsigned int point = 0; point < m_size; ++point)
		{
			GLfloat latituide = map(static_cast<GLfloat>(point), 0.0f, static_cast<GLfloat>(m_size) - 1, glm::half_pi<GLfloat>(), -glm::half_pi<GLfloat>());
			GLfloat x = m_radius * glm::sin(lontitiude) * glm::cos(latituide);
			GLfloat y = m_radius * glm::sin(lontitiude) * glm::sin(latituide);
			GLfloat z = m_radius * glm::cos(lontitiude);

			m_vertecies.emplace_back(glm::vec3(x, y, z));
		}
	}
	
	for (unsigned int ring = 0; ring < (m_size * m_size) - m_size - 1; ++ring)
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
	std::cout << m_vertecies.size() << std::endl;
	std::cout << m_indicies.size() << std::endl;
}

GLfloat SolidSphere::map(GLfloat value, GLfloat low1, GLfloat max1, GLfloat low2, GLfloat max2)
{
	return low2 + (max2 - low2) * ((value - low1) / (max1 - low1));
}

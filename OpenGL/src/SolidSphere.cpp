#include "SolidSphere.h"
#include <glm/gtc/constants.hpp>

#include <iostream>
#include <iterator>
#include <algorithm>


SolidSphere::SolidSphere(GLuint size, GLfloat radius)
	:Shape(size), m_radius(radius)
{}


SolidSphere::~SolidSphere()
{}

void SolidSphere::generate()
{
	for (unsigned int ring = 0; ring < m_size; ++ring)
	{
		GLfloat lontitiude = map(static_cast<GLfloat>(ring), 0.0f, static_cast<GLfloat>(m_rings), glm::pi<GLfloat>(), -glm::pi<GLfloat>());
		for (unsigned int point = 0; point < m_size; ++point)
		{
			GLfloat latituide = map(static_cast<GLfloat>(point), 0.0f, static_cast<GLfloat>(m_rings), glm::half_pi<GLfloat>(), -glm::half_pi<GLfloat>());
			GLfloat x = m_radius * glm::sin(lontitiude) * glm::cos(latituide);
			GLfloat y = m_radius * glm::sin(lontitiude) * glm::sin(latituide);
			GLfloat z = m_radius * glm::cos(lontitiude);

			m_vertecies.emplace_back(glm::vec3(x, y, z));
		}
	}
	
	for (unsigned int ring = 0; ring < (m_size * m_size) - m_size; ++ring)
	{
		m_indicies.push_back(ring);
		m_indicies.push_back(ring + 1);
		m_indicies.push_back(ring + m_size);
	}

	//std::copy(m_vertecies.begin(),
	//	m_vertecies.end(),
	//	std::ostream_iterator<glm::vec3>(std::cout, " "));

	std::copy(m_indicies.begin(), 
		m_indicies.end(), 
		std::ostream_iterator<GLushort>(std::cout, " "));
}

GLfloat SolidSphere::map(GLfloat value, GLfloat low1, GLfloat max1, GLfloat low2, GLfloat max2)
{
	return low2 + (max2 - low2) * ((value - low1) / (max1 - low1));
}

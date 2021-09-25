#include "DrawPhysics.hh"

const float RATIO {30.0f};

DrawPhysics::DrawPhysics(sf::RenderWindow*& window) : window(window){}

sf::Color DrawPhysics::B2SFColor(const b2Color &color, int alpha = 255)
{
	sf::Color result((sf::Uint8)(color.r*255), (sf::Uint8)(color.g*255), (sf::Uint8)(color.b*255), (sf::Uint8) alpha);
	return result;
}

void DrawPhysics::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape polygon(vertexCount);
	sf::Vector2f center;
	for(int i = 0; i < vertexCount; i++)
	{
		//polygon.setPoint(i, SFMLDraw::B2VecToSFVec(vertices[i]));
		sf::Vector2f transformedVec = DrawPhysics::B2VecToSFVec(vertices[i]);
		polygon.setPoint(i, sf::Vector2f(std::floor(transformedVec.x), std::floor(transformedVec.y))); // flooring the coords to fix distorted lines on flat surfaces
	}																								   // they still show up though.. but less frequently
	polygon.setOutlineThickness(-1.f);
	polygon.setFillColor(sf::Color::Transparent);
	polygon.setOutlineColor(DrawPhysics::GLColorToSFML(color));

	window->draw(polygon);
}

void DrawPhysics::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape polygon(vertexCount);
	for(int i = 0; i < vertexCount; i++)
	{
		//polygon.setPoint(i, SFMLDraw::B2VecToSFVec(vertices[i]));
		sf::Vector2f transformedVec = DrawPhysics::B2VecToSFVec(vertices[i]);
		polygon.setPoint(i, sf::Vector2f(std::floor(transformedVec.x), std::floor(transformedVec.y))); // flooring the coords to fix distorted lines on flat surfaces
	}																								   // they still show up though.. but less frequently
	polygon.setOutlineThickness(-1.f);
	polygon.setFillColor(DrawPhysics::GLColorToSFML(color, 60));
	//polygon.setFillColor(sf::Color::Transparent);
	polygon.setOutlineColor(DrawPhysics::GLColorToSFML(color));

	window->draw(polygon);
}
void DrawPhysics::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
	sf::CircleShape circle(radius * sfdd::SCALE);
	circle.setOrigin(radius * sfdd::SCALE, radius * sfdd::SCALE);
	circle.setPosition(DrawPhysics::B2VecToSFVec(center));
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(-1.f);
	circle.setOutlineColor(DrawPhysics::GLColorToSFML(color));

	window->draw(circle);
}
void DrawPhysics::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
	sf::CircleShape circle(radius * sfdd::SCALE);
	circle.setOrigin(radius * sfdd::SCALE, radius * sfdd::SCALE);
	circle.setPosition(DrawPhysics::B2VecToSFVec(center));
	circle.setFillColor(DrawPhysics::GLColorToSFML(color, 60));
	circle.setOutlineThickness(1.f);
	circle.setOutlineColor(DrawPhysics::GLColorToSFML(color));

	b2Vec2 endPoint = center + radius * axis;
	sf::Vertex line[2] =
	{
		sf::Vertex(DrawPhysics::B2VecToSFVec(center), DrawPhysics::GLColorToSFML(color)),
		sf::Vertex(DrawPhysics::B2VecToSFVec(endPoint), DrawPhysics::GLColorToSFML(color)),
	};

	window->draw(circle);
	window->draw(line, 2, sf::Lines);
}
void DrawPhysics::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	sf::Vertex line[] =
	{
		sf::Vertex(DrawPhysics::B2VecToSFVec(p1), DrawPhysics::GLColorToSFML(color)),
		sf::Vertex(DrawPhysics::B2VecToSFVec(p2), DrawPhysics::GLColorToSFML(color))
	};

	window->draw(line, 2, sf::Lines);
}
void DrawPhysics::DrawTransform(const b2Transform& xf)
{
	float lineLength = 0.4;

	//b2Vec2 xAxis(b2Vec2(xf.p.x + (lineLength * xf.q.c), xf.p.y + (lineLength * xf.q.s)));
	b2Vec2 xAxis = xf.p + lineLength * xf.q.GetXAxis();
	sf::Vertex redLine[] =
	{
		sf::Vertex(DrawPhysics::B2VecToSFVec(xf.p), sf::Color::Red),
		sf::Vertex(DrawPhysics::B2VecToSFVec(xAxis), sf::Color::Red)
	};

	// You might notice that the ordinate(Y axis) points downward unlike the one in Box2D testbed
	// That's because the ordinate in SFML coordinate system points downward while the OpenGL(testbed) points upward
	/*b2Vec2 yAxis(b2Vec2(xf.p.x + (lineLength * -xf.q.s), xf.p.y + (lineLength * xf.q.c)));*/
	b2Vec2 yAxis = xf.p + lineLength * xf.q.GetYAxis();
	sf::Vertex greenLine[] =
	{
		sf::Vertex(DrawPhysics::B2VecToSFVec(xf.p), sf::Color::Green),
		sf::Vertex(DrawPhysics::B2VecToSFVec(yAxis), sf::Color::Green)
	};

	window->draw(redLine, 2, sf::Lines);
}

void DrawPhysics::DrawPoint (const b2Vec2 &p, float size, const b2Color &color)
{

}

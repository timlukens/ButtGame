#include <Box2D/Box2D.h>
#include <stdio.h>

int main() {
	b2Vec2 gravity(0.f,-10.f);
	b2World world(gravity);
	
	b2BodyDef groundBodyDef; 
	groundBodyDef.position.Set(0.0f, -10.0f);
	
	b2Body* groundBody = world.CreateBody(&groundBodyDef); 
	groundBox.SetAsBox(50.0f, 10.0f); 

	groundBody->CreateFixture(&groundBox, 0.0f);
	
	
	
	
	
	
	
	
	b2BodyDef bodyDef; 
	bodyDef.type = b2_dynamicBody; 
	bodyDef.position.Set(0.0f, 4.0f); 
	b2Body* body = world.CreateBody(&bodyDef);
	
	b2PolygonShape dynamicBox; 
	dynamicBox.SetAsBox(1.0f, 1.0f);
	
	b2FixtureDef fixtureDef; 
	fixtureDef.shape = &dynamicBox; 
	fixtureDef.density = 1.0f; 
	fixtureDef.friction = 0.3f; 

	body->CreateFixture(&fixtureDef); 
	int32 velocityIterations = 6; 
	int32 positionIterations = 2; 

	for (int32 i = 0; i < 200; ++i) 
	{ 
		world.Step(timeStep, velocityIterations, positionIterations); 
		b2Vec2 position = body->GetPosition(); 
		float32 angle = body->GetAngle(); 
		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle); 
	} 
	
	return 0;
}
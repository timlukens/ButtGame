//
//  GenericView.cpp
//  ButtGame
//
//  Created by tim on 3/17/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "GenericView.h"
#include "Game.h"
#include <allegro5/allegro_primitives.h>

#include "Debug.h"

GenericView::GenericView() {
	backgroundColor_ = al_map_rgb(255, 0, 0);
	
	x_ = 0;
	y_ = 0;
	width_ = 0;
	height_ = 0;

    activeView_ = true;
	clipsToBounds_ = false;
}

GenericView::~GenericView() {
    DBMSG("GenericView::~GenericView");
}

GenericView::GenericView(int x, int y, int width, int height, bool isDynamic) {
	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;
	
	backgroundColor_ = al_map_rgb(255, 0, 0);

    activeView_ = true;
	clipsToBounds_ = false;
	isDynamic_ = isDynamic;
	
	body_ = nullptr;
	
	this->setBodyDefinition();
}

void GenericView::setBodyDefinition() {
	//setup body and add to world
	b2BodyDef bodyDef;
	bodyDef.linearDamping = kDefaultLinearDampening;
	
	//we have to define the position in meters, but also in screen coords, so we want to translate from the superview
	int shiftedX = x_;
	int shiftedY = y_;
	this->translateCoordsToScreen(shiftedX, shiftedY);
	
	bodyDef.position.Set(kMetersFromPixels(shiftedX), kMetersFromPixels(shiftedY));
	if(isDynamic_) bodyDef.type = b2_dynamicBody;
	
	if(body_) Game::instance()->getWorld()->DestroyBody(body_);
	body_ = Game::instance()->getWorld()->CreateBody(&bodyDef);
	
	//define shape
	b2EdgeShape boxShape;
	
	//define fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	
//	fixtureDef.density = 1.f;
//	fixtureDef.friction = 0.3f;
//	fixtureDef.restitution = 0.0f;
	
	float x1 = kMetersFromPixels(0);
	float y1 = kMetersFromPixels(0);
	float x2 = kMetersFromPixels((width_));
	float y2 = kMetersFromPixels((height_));
	
	boxShape.Set(b2Vec2(x1,y1), b2Vec2(x2,y1));
	body_->CreateFixture(&fixtureDef);
	
	boxShape.Set(b2Vec2(x1,y1), b2Vec2(x1,y2));
	body_->CreateFixture(&fixtureDef);
	
	boxShape.Set(b2Vec2(x1,y2), b2Vec2(x2,y2));
	body_->CreateFixture(&fixtureDef);
	
	boxShape.Set(b2Vec2(x2,y2), b2Vec2(x2,y1));
	body_->CreateFixture(&fixtureDef);
}


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//TODO
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Have to translate x_ and y_ back to it's relative position to the superview AFTER we grab the position from the world_
//Box2D now handles the actual position of the object on the screen, but not it's relative position. We need to keep track
//of that ourselves.
void GenericView::drawInView(GenericView* aView) {
	//local variables for real world position as given by the body_
	int x(0), y(0);
	
	if(body_) {
		b2Vec2 position = body_->GetPosition();
		x = kPixelsFromMeters(position.x);
		y = kPixelsFromMeters(position.y);
//		x_ = x;
//		y_ = y;
		
		for (b2Fixture* f = body_->GetFixtureList(); f; f = f->GetNext()) {
			b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
			b2Vec2 v1 = shape->m_vertex1;
			b2Vec2 v2 = shape->m_vertex2;
			int x1 = kPixelsFromMeters(v1.x) + x;
			int y1 = kPixelsFromMeters(v1.y) + y;
			int x2 = kPixelsFromMeters(v2.x) + x;
			int y2 = kPixelsFromMeters(v2.y) + y;
			
//			this->translateCoordsToScreen(x1, y1);
//			this->translateCoordsToScreen(x2, y2);
			
			al_draw_line(x1, y1, x2, y2, backgroundColor_, 5);
		}
	}
//	
//	else {
//		this->translateCoordsToScreen(x, y);
//		
//		//draw this
//		al_draw_rectangle(x, y, x+width_, y+height_, backgroundColor_, 5);
//	}
	
	this->drawSubViews();
}

void GenericView::translateCoordsToView(int& x, int& y, GenericView* aView) {
	GenericView* view = this->superView_.get();
	GenericView* lastView = nullptr;
	
	while(view && aView != lastView) {
		//translate to coordinate system of the view we're drawing in
		if(aView) {
			x += view->x_;
			y += view->y_;
			
			//check bounds of view we're translating into
			//but only if we clip to bounds
			if(clipsToBounds_ && view == superView_.get()) {
				if(x < view->x_) {
					x = view->x_;
					if(view != this) x_ = x - view->x_;
				}
				if(x + width_ > view->x_ + view->width_) {
					x = view->x_ + view->width_ - width_;
					if(view != this) x_ = x - view->x_;
				}
				
				if(y < view->y_){
					y = view->y_;
					if(view != this) y_ = y - view->y_;
				}
				if(y + height_ > view->y_ + view->height_) {
					y = view->y_ + view->height_ - height_;
					if(view != this) y_ = y - view->y_;
				}
			}
		}
		lastView = view;
		view = view->getSuperView().get();
	}
}

void GenericView::translateCoordsToScreen(int&x, int& y) {
	GenericView* view = superView_.get();
	
	while(view) {
		//translate to coordinate system of the view we're drawing in
		if(view) {
			x += view->x_;
			y += view->y_;
			
			//check bounds of view we're translating into
			//but only if we clip to bounds
			if(clipsToBounds_ && view == superView_.get()) {
				if(x < view->x_) {
					x = view->x_;
					if(view != this) x_ = x - view->x_;
				}
				if(x + width_ > view->x_ + view->width_) {
					x = view->x_ + view->width_ - width_;
					if(view != this) x_ = x - view->x_;
				}
				
				if(y < view->y_){
					y = view->y_;
					if(view != this) y_ = y - view->y_;
				}
				if(y + height_ > view->y_ + view->height_) {
					y = view->y_ + view->height_ - height_;
					if(view != this) y_ = y - view->y_;
				}
			}
		}
		view = view->getSuperView().get();
	}
}

void GenericView::drawSubViews() {
    //draw subViews
    vector<shared_ptr<GenericView> >::iterator subView = subViews_.begin();
    while(subView != subViews_.end()) {
        if(*subView) {
            if((*subView)->isActive()) {
                (*subView)->drawInView(this);
                ++subView;
            }
            else {
                subView = subViews_.erase(subView);
            }
        }
        else {
            subView = subViews_.erase(subView);
        }

    }
}

void GenericView::addSubview(shared_ptr<GenericView> aView, shared_ptr<GenericView> pView) {
    subViews_.push_back(aView);
    aView->setSuperView(pView);
}

void GenericView::setSuperView(shared_ptr<GenericView> aView) {
    superView_ = aView;
}

shared_ptr<GenericView> GenericView::getSuperView() {
    return superView_;
}

void GenericView::removeFromSuperView() {
    if(superView_) {
        return superView_->removeView(this);
    }
}

void GenericView::removeView(GenericView* aView) {
    vector<shared_ptr<GenericView> >::iterator subView = subViews_.begin();
    while(subView != subViews_.end()) {
        if((*subView)) {
            if((*subView).get() == aView) {
                subView = subViews_.erase(subView);
            }
            ++subView;
        }
        else {
            subView = subViews_.erase(subView);
        }
    }
}

void GenericView::setBackgroundColor(ALLEGRO_COLOR color) {
	backgroundColor_ = color;
}

void GenericView::destroyView() {
    activeView_ = false;
}

bool GenericView::isActive() {
    return activeView_;
}

bool GenericView::isInView(shared_ptr<GenericView> aView) {
//	Game* game = Game::instance();
	
	int x = x_, y = y_;
	int otherX = aView->x_, otherY = aView->y_;
	
	this->translateCoordsToScreen(x, y);
	aView->translateCoordsToScreen(otherX, otherY);
	
//	this->translateCoordsToView(x, y, game->getBounds().get());
//	aView->translateCoordsToView(otherX, otherY, game->getBounds().get());
	
	if(y + height_ < otherY || y > otherY + aView->height_ || x > otherX + aView->width_ || x + width_ < otherX) return false;
	return true;
}

void GenericView::setClipsToBounds(bool clips) {
	clipsToBounds_ = clips;
}

b2Body* GenericView::getBody() {
	return body_;
}











//This is how box2d debug draw does their drawing of shapes
//
//

//void b2World::DrawShape(b2Fixture* fixture, const b2Transform& xf, const b2Color& color)
//{
//	switch (fixture->GetType())
//	{
//        case b2Shape::e_circle:
//		{
//			b2CircleShape* circle = (b2CircleShape*)fixture->GetShape();
//			
//			b2Vec2 center = b2Mul(xf, circle->m_p);
//			float32 radius = circle->m_radius;
//			b2Vec2 axis = b2Mul(xf.q, b2Vec2(1.0f, 0.0f));
//			
//			g_debugDraw->DrawSolidCircle(center, radius, axis, color);
//		}
//			break;
//			
//        case b2Shape::e_edge:
//		{
//			b2EdgeShape* edge = (b2EdgeShape*)fixture->GetShape();
//			b2Vec2 v1 = b2Mul(xf, edge->m_vertex1);
//			b2Vec2 v2 = b2Mul(xf, edge->m_vertex2);
//			g_debugDraw->DrawSegment(v1, v2, color);
//		}
//			break;
//			
//        case b2Shape::e_chain:
//		{
//			b2ChainShape* chain = (b2ChainShape*)fixture->GetShape();
//			int32 count = chain->m_count;
//			const b2Vec2* vertices = chain->m_vertices;
//			
//			b2Vec2 v1 = b2Mul(xf, vertices[0]);
//			for (int32 i = 1; i < count; ++i)
//			{
//				b2Vec2 v2 = b2Mul(xf, vertices[i]);
//				g_debugDraw->DrawSegment(v1, v2, color);
//				g_debugDraw->DrawCircle(v1, 0.05f, color);
//				v1 = v2;
//			}
//		}
//			break;
//			
//        case b2Shape::e_polygon:
//		{
//			b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
//			int32 vertexCount = poly->m_count;
//			b2Assert(vertexCount <= b2_maxPolygonVertices);
//			b2Vec2 vertices[b2_maxPolygonVertices];
//			
//			for (int32 i = 0; i < vertexCount; ++i)
//			{
//				vertices[i] = b2Mul(xf, poly->m_vertices[i]);
//			}
//			
//			g_debugDraw->DrawSolidPolygon(vertices, vertexCount, color);
//		}
//			break;
//            
//		default:
//			break;
//	}
//}
//
//void b2World::DrawJoint(b2Joint* joint)
//{
//	b2Body* bodyA = joint->GetBodyA();
//	b2Body* bodyB = joint->GetBodyB();
//	const b2Transform& xf1 = bodyA->GetTransform();
//	const b2Transform& xf2 = bodyB->GetTransform();
//	b2Vec2 x1 = xf1.p;
//	b2Vec2 x2 = xf2.p;
//	b2Vec2 p1 = joint->GetAnchorA();
//	b2Vec2 p2 = joint->GetAnchorB();
//	
//	b2Color color(0.5f, 0.8f, 0.8f);
//	
//	switch (joint->GetType())
//	{
//        case e_distanceJoint:
//			g_debugDraw->DrawSegment(p1, p2, color);
//			break;
//			
//        case e_pulleyJoint:
//		{
//			b2PulleyJoint* pulley = (b2PulleyJoint*)joint;
//			b2Vec2 s1 = pulley->GetGroundAnchorA();
//			b2Vec2 s2 = pulley->GetGroundAnchorB();
//			g_debugDraw->DrawSegment(s1, p1, color);
//			g_debugDraw->DrawSegment(s2, p2, color);
//			g_debugDraw->DrawSegment(s1, s2, color);
//		}
//			break;
//			
//        case e_mouseJoint:
//			// don't draw this
//			break;
//			
//        default:
//			g_debugDraw->DrawSegment(x1, p1, color);
//			g_debugDraw->DrawSegment(p1, p2, color);
//			g_debugDraw->DrawSegment(x2, p2, color);
//	}
//}

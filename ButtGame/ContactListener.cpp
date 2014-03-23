//
//  ContactListener.cpp
//  ButtGame
//
//  Created by tim on 3/23/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "ContactListener.h"

//ContactListener::ContactListener() : contacts_() { }
//
//ContactListener::~ContactListener() { }
//
//void ContactListener::BeginContact(b2Contact* contact) {
//    // We need to copy out the data because the b2Contact passed in
//    // is reused.
//    ContactStruct aContact = { contact->GetFixtureA(), contact->GetFixtureB() };
//    contacts_.push_back(aContact);
//}
//
//void ContactListener::EndContact(b2Contact* contact) {
//    ContactStruct aContact = { contact->GetFixtureA(), contact->GetFixtureB() };
//    std::vector<ContactStruct>::iterator pos;
//    pos = std::find(contacts_.begin(), contacts_.end(), aContact);
//    if (pos != contacts_.end()) {
//        contacts_.erase(pos);
//    }
//}
//
//void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) { }
//
//void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) { }

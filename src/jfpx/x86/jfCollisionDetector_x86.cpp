/**
jfpx - A cross platform physics engine using CUDA    
Copyright (C) 2010 Jonathan Frawley

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
#include "jfCollisionDetector_x86.h"


unsigned jfCollisionDetector_x86::sphereAndHalfSpace(const jfCollisionSphere& sphere,
														const jfCollisionPlane& plane,
														jfCollisionData* data
														) const
{
    // Cache the sphere position
    jfVector3_x86 position;
	sphere.getAxisVector(3, &position);

    // Find the distance from the plane
	jfVector3_x86 planeDirection;
	plane.getDirection(&planeDirection);
    jfReal sphereDistance = planeDirection.dotProduct(position) - sphere.getRadius() - plane.getOffset();

    if (sphereDistance >= 0)
	{
		return 0;
	}

    // Create the contact - it has a normal in the plane direction.
    jfContact_x86 contact;
    jfVector3_x86 contactPoint;
	jfVector3_x86 planeDirectionMult;

    contact.setContactNormal(planeDirection);
    contact.setPenetration(-sphereDistance);
	planeDirection.multiply(sphereDistance + sphere.getRadius(), &planeDirectionMult);
	position.subtract(planeDirectionMult, &contactPoint);
    contact.setContactPoint(contactPoint);
    contact.setBodyData(sphere.getBody(), NULL, data->getFriction(), data->getRestitution());

    data->addContact(contact);
    return 1;
}

unsigned jfCollisionDetector_x86::sphereAndTruePlane(const jfCollisionSphere& sphere,
														const jfCollisionPlane& plane,
														jfCollisionData* data) const
{
    // Cache the sphere position
    jfVector3_x86 position;
	sphere.getAxisVector(3, &position);

    // Find the distance from the plane
	jfVector3_x86 planeDirection;
	plane.getDirection(&planeDirection);
    jfReal centreDistance = planeDirection.dotProduct(position) - plane.getOffset();

    // Check if we're within radius
    if ((centreDistance*centreDistance) > (sphere.getRadius()*sphere.getRadius()))
    {
        return 0;
    }

    // Check which side of the plane we're on
    jfReal penetration = -centreDistance;
    if (centreDistance < 0)
    {
        planeDirection *= -1;
        penetration = -penetration;
    }
    penetration += sphere.getRadius();

    // Create the contact - it has a normal in the plane direction.
    jfContact_x86 contact;
    jfVector3_x86 contactPoint;
    jfVector3_x86 centreDistanceMult;
    contact.setContactNormal(planeDirection);
    contact.setPenetration(penetration);
	planeDirection.multiply(centreDistance, &centreDistanceMult);
	position.subtract(centreDistanceMult, &contactPoint);
    contact.setContactPoint(contactPoint);
	contact.setBodyData(sphere.getBody(), NULL, data->getFriction(), data->getRestitution());
    data->addContact(contact);
    return 1;
}

unsigned jfCollisionDetector_x86::sphereAndSphere(const jfCollisionSphere& one,
														const jfCollisionSphere& two,
														jfCollisionData* data) const
{
    jfVector3_x86 positionOne;
    jfVector3_x86 positionTwo;
    jfVector3_x86 midline;

    // Cache the sphere positions
	one.getAxisVector(3, &positionOne);
   	two.getAxisVector(3, &positionTwo);

    // Find the vector between the objects
    positionOne.subtract(positionTwo, &midline);
    jfReal size = midline.magnitude();

    // See if it is large enough.
    if ((size <= 0.0f) || (size >= (one.getRadius()+two.getRadius())))
    {
        return 0;
    }

    // We manually create the normal, because we have the
    // size to hand.
    jfVector3_x86 normal;
   	midline.multiply((((jfReal)1.0)/size), &normal);

    jfContact_x86 contact;
    contact.setContactNormal(normal);
	jfVector3_x86 contactPoint;
	jfVector3_x86 midlineHalved;
	midline.multiply((jfReal)0.5, &midlineHalved);
	positionOne.add(midlineHalved, &contactPoint);
    contact.setContactPoint(contactPoint);
    contact.setPenetration(one.getRadius()+two.getRadius() - size);
    contact.setBodyData(one.getBody(), two.getBody(), data->getFriction(), data->getRestitution());

    data->addContact(contact);
    return 1;
}

unsigned jfCollisionDetector_x86::sphereAndSphereBatch(vector<jfBall*>& spheres,
                                                            jfCollisionData* collisionData) const
{
    vector<jfBall*>::iterator sphere = spheres.begin();
    vector<jfBall*>::iterator otherSphere;
    unsigned contactCount = 0;
    sphere = spheres.begin();
    for(sphere = spheres.begin(); sphere != spheres.end() ; ++sphere)
    {
        for(otherSphere = (sphere+1) ; otherSphere != spheres.end() ; ++otherSphere)
        {
            contactCount += sphereAndSphere((*(*sphere)), (*(*otherSphere)), collisionData);
        }
    }
    return contactCount;
}

unsigned jfCollisionDetector_x86::boxAndHalfSpace(const jfCollisionBox& box,
													const jfCollisionPlane& plane,
													jfCollisionData* data
													) const
{
        /*
	// Make sure we have contacts
    if (! data->hasMoreContacts())
	{
		return 0;
	}
*/
	jfIntersectionTester_x86 intersectionTester;

    // Check for intersection
    if (! intersectionTester.boxAndHalfSpace(box, plane))
    {
        return 0;
    }

    // We have an intersection, so find the intersection points. We can make
    // do with only checking vertices. If the box is resting on a plane
    // or on an edge, it will be reported as four or two contact points.

    // Go through each combination of + and - for each half-size
/*    static jfReal mults[8][3] = {{1,1,1},
                                    {-1,1,1},
                                    {1,-1,1},
                                    {-1,-1,1},
                                    {1,1,-1},
                                    {-1,1,-1},
                                    {1,-1,-1},
                                    {-1,-1,-1}};
                                    */
    static jfReal mults[8][3] = { {-1,-1,-1},
                                    {-1,-1,1},
                                    {-1,1,-1},
                                    {-1,1,1},
                                    {1,-1,-1},
                                    {1,-1,1},
                                    {1,1,-1},
                                    {1,1,1} };

    jfMatrix4_x86 boxTransformMatrix;
    jfVector3_x86 boxHalfSize;
    jfVector3_x86 planeDirection;

    //For efficiency cache these values
    box.getHalfSize(&boxHalfSize);
    plane.getDirection(&planeDirection);
    box.getTransformMatrix(&boxTransformMatrix);

    unsigned contactsUsed = 0;
    for (unsigned i = 0; i < 8; i++) {
		// Calculate the position of each vertex
        jfVector3_x86 vertexPos(mults[i][0],
                                mults[i][1],
                                mults[i][2]);

        vertexPos.componentProductUpdate(boxHalfSize);
		boxTransformMatrix.transform(vertexPos, &vertexPos);

        // Calculate the distance from the plane
        jfReal vertexDistance = vertexPos.dotProduct(planeDirection);

        // Compare this to the plane's distance
        if (vertexDistance <= (plane.getOffset() + data->getTolerance()))
        {
            jfContact_x86 contact;
            // Create the contact data.
            // The contact point is halfway between the vertex and the
            // plane - we multiply the direction by half the separation
            // distance and add the vertex location.
            jfVector3_x86 contactPoint = planeDirection;
			contactPoint *= (vertexDistance-plane.getOffset());
			contactPoint += vertexPos;
            contact.setContactPoint(contactPoint);
            contact.setContactNormal(planeDirection);
            contact.setPenetration(plane.getOffset() - vertexDistance);
            cout<<"vertexDistance is : "<<vertexDistance<<endl;
            // Write the appropriate data
            contact.setBodyData(box.getBody(), NULL, data->getFriction(), data->getRestitution());

            // Move onto the next contact
			data->addContact(contact);
            contactsUsed++;
/*
            if (! data->hasMoreContacts())
			{
				return contactsUsed;
			}*/
		}
    }
    return contactsUsed;
}

jfReal jfCollisionDetector_x86::penetrationOnAxis(
		const jfCollisionBox& one,
		const jfCollisionBox& two,
		jfVector3& axis,
		const jfVector3& toCentre
		) const
{
    jfIntersectionTester_x86 intersectionTester;
    // Project the half-size of one onto axis
    jfReal oneProject = intersectionTester.transformToAxis(one, axis);
    jfReal twoProject = intersectionTester.transformToAxis(two, axis);

    // Project this onto the axis
    jfReal distance = jfRealAbs(toCentre.dotProduct(axis));

    // Return the overlap (i.e. positive indicates
    // overlap, negative indicates separation).
    return (oneProject + twoProject - distance);
}

bool jfCollisionDetector_x86::tryAxis(
    const jfCollisionBox& one,
    const jfCollisionBox& two,
    jfVector3& axis,
    const jfVector3& toCentre,
    unsigned index,
    // These values may be updated
    jfReal& smallestPenetration,
    unsigned& smallestCase
    ) const
{
    // Make sure we have a normalized axis, and don't check almost parallel axes
    if (axis.squareMagnitude() < 0.0001)
	{
		return true;
	}
    axis.normalize();

    jfReal penetration = penetrationOnAxis(one, two, axis, toCentre);

    if (penetration < 0)
	{
		return false;
	}
    if (penetration < smallestPenetration)
	{
        smallestPenetration = penetration;
        smallestCase = index;
    }
    return true;
}

void jfCollisionDetector_x86::fillPointFaceBoxBox(
    const jfCollisionBox& one,
    const jfCollisionBox& two,
    const jfVector3& toCentre,
    jfCollisionData* data,
    unsigned best,
    jfReal pen
    ) const
{
    // This method is called when we know that a vertex from
    // box two is in contact with box one.
    //jfContact* contact = data->contacts;

    // We know which axis the collision is on (i.e. best),
    // but we need to work out which of the two faces on
    // this axis.
    jfVector3_x86 normal;
    jfVector3_x86 twoAxis;
   	one.getAxisVector(best, &normal);
    if (normal.dotProduct(toCentre) > 0)
    {
        normal *= -1.0f;
    }

    // Work out which vertex of box two we're colliding with.
    // Using toCentre doesn't work!
    jfVector3_x86 vertex;
   	two.getHalfSize(&vertex);
	two.getAxisVector(0, &twoAxis);
    if (twoAxis.dotProduct(normal) < 0)
	{
		vertex.setX(-vertex.getX());
	}
	two.getAxisVector(1, &twoAxis);
    if (twoAxis.dotProduct(normal) < 0)
	{
		vertex.setY(-vertex.getY());
	}
	two.getAxisVector(2, &twoAxis);
    if (twoAxis.dotProduct(normal) < 0)
	{
		vertex.setZ(-vertex.getZ());
	}

    // Create the contact data
	jfContact_x86 contact;
    contact.setContactNormal(normal);
    contact.setPenetration(pen);
	jfVector3_x86 contactPoint;
	jfMatrix4_x86 twoTransform;
	two.getTransformMatrix(&twoTransform);
	twoTransform.multiply(vertex, &contactPoint);
    contact.setContactPoint(contactPoint);
    contact.setBodyData(one.getBody(), two.getBody(), data->getFriction(), data->getRestitution());
	data->addContact(contact);
}

void jfCollisionDetector_x86::contactPoint(
		const jfVector3& pOne,
		const jfVector3& dOne,
		jfReal oneSize,
		const jfVector3& pTwo,
		const jfVector3& dTwo,
		jfReal twoSize,
		// If this is true, and the contact point is outside
		// the edge (in the case of an edge-face contact) then
		// we use one's midpoint, otherwise we use two's.
		bool useOne,
		jfVector3* result) const
{
	//TODO:Opportunity for CUDA?
    jfVector3_x86 toSt, cOne, cTwo;
    jfReal dpStaOne, dpStaTwo, dpOneTwo, smOne, smTwo;
    jfReal denom, mua, mub;

    smOne = dOne.squareMagnitude();
    smTwo = dTwo.squareMagnitude();
    dpOneTwo = dTwo.dotProduct(dOne);

    pOne.subtract(pTwo, &toSt);
    dpStaOne = dOne.dotProduct(toSt);
    dpStaTwo = dTwo.dotProduct(toSt);

    denom = (smOne * smTwo) - (dpOneTwo * dpOneTwo);

    // Zero denominator indicates parrallel lines
    if (jfRealAbs(denom) < 0.0001f) {
		if(useOne)
		{
			(*result) = pOne;
			return;
		}
		else
		{
            (*result) = pTwo;
			return;
		}
    }

    mua = ((dpOneTwo * dpStaTwo) - (smTwo * dpStaOne)) / denom;
    mub = ((smOne * dpStaTwo) - (dpOneTwo * dpStaOne)) / denom;

    // If either of the edges has the nearest point out
    // of bounds, then the edges aren't crossed, we have
    // an edge-face contact. Our point is on the edge, which
    // we know from the useOne parameter.
    if ((mua > oneSize) ||
        (mua < -oneSize) ||
        (mub > twoSize) ||
        (mub < -twoSize))
    {
		if(useOne)
		{
			(*result) = pOne;
			return;
		}
		else
		{
            (*result) = pTwo;
			return;
		}
    }
    else
    {
        //cOne = pOne + dOne * mua;
        dOne.multiply(mua, &cOne);
        cOne += pOne;
        //cTwo = pTwo + dTwo * mub;
        dTwo.multiply(mub, &cTwo);
        cTwo += pTwo;

        cOne *= 0.5;
        cTwo *= 0.5;

        cOne.add(cTwo, result);
    }
}

// This preprocessor definition is only used as a convenience
// in the boxAndBox contact generation method.
#define CHECK_OVERLAP(axis, index) \
    if (!tryAxis(one, two, (axis), toCentre, (index), pen, best)) return 0;

unsigned jfCollisionDetector_x86::boxAndBox(const jfCollisionBox& one,
												const jfCollisionBox& two,
												jfCollisionData* data
												) const
{
	//TODO:Ideal candidate for CUDA
	jfIntersectionTester_x86 intersectionTester;

    // Check for intersection
    if (! intersectionTester.boxAndBox(one, two))
    {
        return 0;
    }

	jfVector3_x86 oneAxis0, oneAxis1, oneAxis2, oneAxis3;
    jfVector3_x86 twoAxis0, twoAxis1, twoAxis2, twoAxis3;
	jfVector3_x86 toCentre;

	//Find vector between the two centres
	one.getAxisVector(3, &oneAxis3);
	two.getAxisVector(3, &twoAxis3);
	twoAxis3.subtract(oneAxis3, &toCentre);

	//Assume no contact at start
	jfReal pen = JF_REAL_MAX;
	unsigned best = 0xffffff;

	// Now we check each axes, returning if it gives us
    // a separating axis, and keeping track of the axis with
    // the smallest penetration otherwise.
	one.getAxisVector(0, &oneAxis0);
    CHECK_OVERLAP(oneAxis0, 0);
	one.getAxisVector(1, &oneAxis1);
    CHECK_OVERLAP(oneAxis1, 1);
	one.getAxisVector(2, &oneAxis2);
    CHECK_OVERLAP(oneAxis2, 2);

	two.getAxisVector(0,&twoAxis0);
    CHECK_OVERLAP(twoAxis0, 3);
	two.getAxisVector(1,&twoAxis1);
    CHECK_OVERLAP(twoAxis1, 4);
	two.getAxisVector(2,&twoAxis2);
    CHECK_OVERLAP(twoAxis2, 5);

    // Store the best axis-major, in case we run into almost
    // parallel edge collisions later
    unsigned bestSingleAxis = best;

	jfVector3_x86 crossProduct;
	oneAxis0.crossProduct(twoAxis0, &crossProduct);
    CHECK_OVERLAP(crossProduct, 6);
	oneAxis0.crossProduct(twoAxis1, &crossProduct);
    CHECK_OVERLAP(crossProduct, 7);
	oneAxis0.crossProduct(twoAxis2, &crossProduct);
    CHECK_OVERLAP(crossProduct, 8);
	oneAxis1.crossProduct(twoAxis0, &crossProduct);
    CHECK_OVERLAP(crossProduct, 9);
	oneAxis1.crossProduct(twoAxis1, &crossProduct);
    CHECK_OVERLAP(crossProduct, 10);
	oneAxis1.crossProduct(twoAxis2, &crossProduct);
    CHECK_OVERLAP(crossProduct, 11);
	oneAxis2.crossProduct(twoAxis0, &crossProduct);
    CHECK_OVERLAP(crossProduct, 12);
	oneAxis2.crossProduct(twoAxis1, &crossProduct);
    CHECK_OVERLAP(crossProduct, 13);
	oneAxis2.crossProduct(twoAxis2, &crossProduct);
    CHECK_OVERLAP(crossProduct, 14);

    // Make sure we've got a result.
    assert(best != 0xffffff);

    // We now know there's a collision, and we know which
    // of the axes gave the smallest penetration. We now
    // can deal with it in different ways depending on
    // the case.
    if (best < 3)
    {
        // We've got a vertex of box two on a face of box one.
        fillPointFaceBoxBox(one, two, toCentre, data, best, pen);
    ///    data->addContacts(1);
        return 1;
    }
    else if (best < 6)
    {
        // We've got a vertex of box one on a face of box two.
        // We use the same algorithm as above, but swap around
        // one and two (and therefore also the vector between their
        // centres).
        toCentre *= -1;
        fillPointFaceBoxBox(two, one, toCentre, data, (best-3), pen);
       /// data->addContacts(1);
        return 1;
    }
    else
    {
        // We've got an edge-edge contact. Find out which axes
        best -= 6;
        unsigned oneAxisIndex = best / 3;
        unsigned twoAxisIndex = best % 3;
        jfVector3_x86 oneAxis;
		one.getAxisVector(oneAxisIndex, &oneAxis);
        jfVector3_x86 twoAxis;
	   	two.getAxisVector(twoAxisIndex, &twoAxis);
        jfVector3_x86 axis;
		oneAxis.crossProduct(twoAxis, &axis);
        axis.normalize();

        // The axis should point from box one to box two.
        if (axis.dotProduct(toCentre) > 0)
		{
			axis *= -1.0f;
		}

        // We have the axes, but not the edges: each axis has 4 edges parallel
        // to it, we need to find which of the 4 for each object. We do
        // that by finding the point in the centre of the edge. We know
        // its component in the direction of the box's collision axis is zero
        // (its a mid-point) and we determine which of the extremes in each
        // of the other axes is closest.
        jfVector3_x86 ptOnOneEdge;
	   	one.getHalfSize(&ptOnOneEdge);
        jfVector3_x86 ptOnTwoEdge;
		two.getHalfSize(&ptOnTwoEdge);
        for (unsigned i = 0; i < 3; i++)
        {
			jfVector3_x86 oneAxisCurrent;
			jfVector3_x86 twoAxisCurrent;

			one.getAxisVector(i, &oneAxisCurrent);
			two.getAxisVector(i, &twoAxisCurrent);
            if (i == oneAxisIndex)
			{
				ptOnOneEdge.setElem(i,0);
			}
            else if (oneAxisCurrent.dotProduct(axis) > 0)
			{
				ptOnOneEdge.setElem(i, -ptOnOneEdge.getElem(i));
			}

            if (i == twoAxisIndex)
			{
				ptOnTwoEdge.setElem(i, 0);
			}
            else if (twoAxisCurrent.dotProduct(axis) < 0)
			{
				ptOnTwoEdge.setElem(i, -ptOnTwoEdge.getElem(i));
			}
        }

        // Move them into world coordinates (they are already oriented
        // correctly, since they have been derived from the axes).
		jfMatrix4_x86 oneTransform, twoTransform;

		one.getTransformMatrix(&oneTransform);
		oneTransform.multiply(ptOnOneEdge, &ptOnOneEdge);
		two.getTransformMatrix(&twoTransform);
		twoTransform.multiply(ptOnTwoEdge, &ptOnTwoEdge);

        // So we have a point and a direction for the colliding edges.
        // We need to find out point of closest approach of the two
        // line-segments.
        jfVector3_x86 vertex;
        jfVector3_x86 oneHalfSize, twoHalfSize;

		one.getHalfSize(&oneHalfSize);
		two.getHalfSize(&twoHalfSize);
		contactPoint(
            ptOnOneEdge,
			oneAxis,
			oneHalfSize.getElem(oneAxisIndex),
            ptOnTwoEdge,
			twoAxis,
			twoHalfSize.getElem(twoAxisIndex),
            (bestSingleAxis > 2),
			&vertex
            );

        // We can fill the contact.
        //jfContact* contact = data->contacts;
        jfContact_x86 contact;

        contact.setPenetration(pen);
        contact.setContactNormal(axis);
        contact.setContactPoint(vertex);
        contact.setBodyData(one.getBody(),
								two.getBody(),
								data->getFriction(),
								data->getRestitution());
        data->addContact(contact);
        return 1;
    }
    return 0;
}
#undef CHECK_OVERLAP

unsigned jfCollisionDetector_x86::boxAndBoxBatch(vector<jfBox*>& boxes,
                                                    jfCollisionData* collisionData) const
{
    unsigned contactCount = 0;
    vector<jfBox*>::iterator box, otherBox;

    for(box = boxes.begin() ; box != boxes.end(); ++box)
    {
        for(otherBox = (box+1) ; otherBox != boxes.end() ; ++otherBox)
        {
            contactCount += boxAndBox((*(*box)), (*(*otherBox)), collisionData);
        }
    }
    return contactCount;
}

unsigned jfCollisionDetector_x86::boxAndPoint(const jfCollisionBox& box,
												const jfVector3& point,
												jfCollisionData* data
												) const
{
	// Transform the point into box coordinates
	jfMatrix4_x86 boxTransform;
    jfVector3_x86 relPt;
    jfVector3_x86 normal;
    jfVector3_x86 boxHalfSize;
    jfVector3_x86 boxAxis;

	box.getTransformMatrix(&boxTransform);
	boxTransform.transformInverse(point, &relPt);
	box.getHalfSize(&boxHalfSize);
    // Check each axis, looking for the axis on which the
    // penetration is least deep.
    jfReal min_depth = boxHalfSize.getX() - jfRealAbs(relPt.getX());
    if (min_depth < 0)
	{
		return 0;
	}
	box.getAxisVector(0, &boxAxis);
	int multiplier = 1;
	if(relPt.getX() < 0)
	{
		multiplier = -1;
	}
	boxAxis.multiply(multiplier, &normal);

    jfReal depth = boxHalfSize.getY() - jfRealAbs(relPt.getY());
    if (depth < 0)
	{
		return 0;
	}
    else if (depth < min_depth)
    {
        min_depth = depth;
		box.getAxisVector(1, &boxAxis);
		multiplier = 1;
		//@opt put multiply in if statement
		if(relPt.getY() < 0)
		{
			multiplier = -1;
		}
		boxAxis.multiply(multiplier, &normal);
    }

    depth = boxHalfSize.getZ() - jfRealAbs(relPt.getZ());
    if (depth < 0)
	{
		return 0;
	}
    else if (depth < min_depth)
    {
        min_depth = depth;
		box.getAxisVector(2, &boxAxis);
		multiplier = 1;
		//@opt put multiply in if statement
		if(relPt.getZ() < 0)
		{
			multiplier = -1;
		}
		boxAxis.multiply(multiplier, &normal);
    }

    // Compile the contact
    jfContact_x86 contact;
    contact.setContactNormal(normal);
    contact.setContactPoint(point);
    contact.setPenetration(min_depth);

    // Note that we don't know what rigid body the point
    // belongs to, so we just use NULL. Where this is called
    // this value can be left, or filled in.
    contact.setBodyData(box.getBody(), NULL,
        data->getFriction(), data->getRestitution());

    data->addContact(contact);
    return 1;
}

unsigned jfCollisionDetector_x86::boxAndSphere(const jfCollisionBox& box,
												const jfCollisionSphere& sphere,
												jfCollisionData* data
												) const
{
	// Transform the centre of the sphere into box coordinates
	jfMatrix4_x86 boxTransformMatrix;
    jfVector3_x86 relCentre;
    jfVector3_x86 centre;
    jfVector3_x86 boxHalfSize;

    sphere.getAxisVector(3, &centre);

//    cout<<"Printing centre"<<centre<< endl;

	box.getTransformMatrix(&boxTransformMatrix);

	//cout <<"Printing boxTransformMatrix" << boxTransformMatrix << endl;

	boxTransformMatrix.transformInverse(centre, &relCentre);

	box.getHalfSize(&boxHalfSize);

    cout<<"boxTransformMatrix is :"<<boxTransformMatrix<<endl;
    cout<<"boxHalfSize is :"<<boxHalfSize<<endl;
    cout<<"sphere.getRadius() :"<<sphere.getRadius()<<endl;
    jfVector3_x86 sphereCentre, boxPos;
    box.getBody()->getPos(&boxPos);
    sphere.getBody()->getPos(&sphereCentre);
    cout<<"Printing boxPos"<<boxPos<<endl;
    cout<<"Printing centre"<<sphereCentre<<endl;
    cout<<"Printing relCentre"<<relCentre<<endl;

    // Early out check to see if we can exclude the contact
	// Principle of Seperating Axis
	// @ref Millington p.283
    if (((jfRealAbs(relCentre.getX()) - sphere.getRadius()) > boxHalfSize.getX()) ||
			((jfRealAbs(relCentre.getY()) - sphere.getRadius()) > boxHalfSize.getY()) ||
			((jfRealAbs(relCentre.getZ()) - sphere.getRadius()) > boxHalfSize.getZ()))
    {
        cout<<"DEBUG: Early out"<<endl;
        return 0;
    }

    jfVector3_x86 closestPt(0,0,0);
    jfReal dist;

    // Clamp each coordinate to the box.
    dist = relCentre.getX();
    if (dist > boxHalfSize.getX())
	{
		dist = boxHalfSize.getX();
	}
	if (dist < -boxHalfSize.getX())
	{
		dist = -boxHalfSize.getX();
	}
    closestPt.setX(dist);

    dist = relCentre.getY();
    if (dist > boxHalfSize.getY())
	{
		dist = boxHalfSize.getY();
	}
    if (dist < -boxHalfSize.getY())
	{
		dist = -boxHalfSize.getY();
	}
    closestPt.setY(dist);

    dist = relCentre.getZ();
    if (dist > boxHalfSize.getZ())
	{
		dist = boxHalfSize.getZ();
	}
	if (dist < -boxHalfSize.getZ())
	{
		dist = -boxHalfSize.getZ();
	}
    closestPt.setZ(dist);

    cout <<"closestPt is :"<<closestPt<<endl;

    // Check we're in contact
    jfVector3_x86 closestPtMinusRelCentre;
    closestPt.subtract(relCentre, &closestPtMinusRelCentre);
    dist = closestPtMinusRelCentre.squareMagnitude();
    if (dist > (sphere.getRadius() * sphere.getRadius()))
	{
		return 0;
	}

    //cout <<"Sphere radius : "<<sphere.getRadius()<<endl;
    //cout <<"dist : "<<dist<<endl;

    // Compile the contact
    jfVector3_x86 closestPtWorld;
    jfContact_x86 contact;
    jfVector3_x86 contactNormal;

	boxTransformMatrix.transform(closestPt, &closestPtWorld);
    cout <<"closestPtWorld is :"<<closestPtWorld<<endl;
	closestPtWorld.subtract(centre, &contactNormal);
	contactNormal.normalize();
    contact.setContactNormal(contactNormal);
    contact.setContactPoint(closestPtWorld);
    contact.setPenetration(sphere.getRadius() - jfRealSqrt(dist));
    contact.setBodyData(box.getBody(), sphere.getBody(), data->getFriction(), data->getRestitution());

    data->addContact(contact);
    return 1;
}

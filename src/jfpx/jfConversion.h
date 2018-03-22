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
#ifndef JFCONVERSION_H
#define JFCONVERSION_H

//TODO:Unit test This
jfVector3* localToWorldCoords(jfVector3& localCoord, jfMatrix4& transformMatrix)
{
    //Millington p.181
    return (transformMatrix * localCoord);
}

//TODO:Unit test This
/**
 * Conversion from world to local coordinates
 */
jfVector3* worldToLocalCoords(jfVector3& worldCoord, jfMatrix4& transformMatrix)
{
    //Millington p.181
    jfMatrix4* inverseTransformMatrix = transformMatrix->getInverse();
    return ((*inverseTransformMatrix) * worldCoord);
}

//TODO:Unit test This
jfVector3* localToWorldDirn(jfVector3& localCoord, Matrix4& transformMatrix)
{
    return transformMatrix.transformDirection(localCoord);
}

//TODO:Unit test This
jfVector3* worldCoordToLocalDirn(jfVector3& worldCoord, Matrix4& transformMatrix)
{
    return transformMatrix.transformInverseDirection(worldCoord);
}

#endif //JFCONVERSION_H

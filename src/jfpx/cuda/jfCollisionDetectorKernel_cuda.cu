
#include <jfpx/cuda/jfVector3_cuda.h>
#include <jfpx/cuda/jfContact_cuda.h>
#include <jfpx/cuda/jfCollisionSphere_cuda.h>
#include <jfpx/cuda/jfCudaConstants.h>


#include <cuda.h>
#include <cuda_runtime.h>

#include <stdio.h>

__device__ float3
multiply(float3 a, float b)
{
    float3 result;
    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;
    return result;
}

/**
  * Device function run on GPU which tests
  * whether two spheres are colliding and 
  * if so, generates a contact.
  */
__device__ void
sphereSphereCollision(float3* contactNormal,
                      float4* contactPointPenetration,
                      int* valid,
                      float4 currentSphere,
                      float4 otherSphere
                      )
{
    float3 midline;
    midline.x = currentSphere.x-otherSphere.x;
    midline.y = currentSphere.y-otherSphere.y;
    midline.z = currentSphere.z-otherSphere.z;
    float size = sqrt((midline.x*midline.x) + (midline.y*midline.y) + (midline.z*midline.z));
    float radiiSum = currentSphere.w+otherSphere.w;

    //Don't want us to take it if we have inaccuracy.
    float tolerance = 0.0001;
    if((size > (0.0f+tolerance)) && (size < radiiSum))
    {
        (*valid) = 1;
    }
    else
    {
        (*valid) = 0;
    }

	//Set contact normal
	float invSize = 1.0f/size;
	contactNormal->x = midline.x * invSize;
	contactNormal->y = midline.y * invSize;
	contactNormal->z = midline.z * invSize;

    //Set contact point
    contactPointPenetration->x = (currentSphere.x + (midline.x*0.5));
    contactPointPenetration->y = (currentSphere.y + (midline.y*0.5));
    contactPointPenetration->z = (currentSphere.z + (midline.z*0.5));

    //Set penetration of contact
    contactPointPenetration->w = (radiiSum - size);
}

/**
  * Called at the beginning of checking all of the spheres as this is the only case when the 
  * number of spheres tested is not uniform.
  */
__device__ void
tileSphereSphereCalculationStart(float3* currentContactNormal,
									float4* currentContactPointPenetration,
									int* valid,
									float4 currentSphere,
									float4 sharedSpheres[BLOCK_SIZE],
									unsigned amount)
{
    int i;

    for (i=0; i < amount; i++)
    {
		sphereSphereCollision(&(currentContactNormal[i]),
				&(currentContactPointPenetration[i]),
				&(valid[i]),
				currentSphere,
				sharedSpheres[threadIdx.x+1+i]);
    }
    return;
}

/**
  * Perform collision detection between a tile of spheres
  * in shared memory.
  */
__device__ void
tileSphereSphereCalculation(float3* currentContactNormal,
                            float4* currentContactPointPenetration,
                            int* valid,
                            float4 currentSphere,
                            float4 sharedSpheres[BLOCK_SIZE])
{
    int i;
    for (i=0; i < blockDim.x; i++)
    {
		sphereSphereCollision(&(currentContactNormal[i]),
				&(currentContactPointPenetration[i]),
				&(valid[i]),
				currentSphere,
				sharedSpheres[i]);
    }
    return;
}

/** 
 * Computes the row index in the triangular array.
 * Each row gets shorter and shorter by one each time.
 */
__device__
unsigned computeContactRowIndex(unsigned n_Spheres, unsigned sphere_row)
{
    unsigned rowLength=(n_Spheres-1);
    unsigned resultRow=0;
    for(unsigned i=0;i<sphere_row;i++)
    {
        resultRow+=rowLength;
        --rowLength;
    }
    return resultRow;
}

/**
 * Computes the number of columns in the row of the
 * triangular contacts array
 */
__device__
unsigned computeContactNumCols(unsigned sphere_row)
{
    return ((N_SPHERES-1)-sphere_row);
}

/**
 * Kernel which checks exhaustively for collisions 
 * between the spheres passed in.
 */
__global__ void
calculateContacts(float4* devContactNormal,
                  float4* devContactPointPenetration,
                  int4* devContactValidBodies,
                  float4* devSphere,
				  unsigned numSpheres)
{
    //Define shared memory inside a block
    //Spheres represented by 3 floats for position and 4th for radius
	__shared__ float4 sharedSpheres[BLOCK_SIZE];

    float4* globalSpheres = (float4*) devSphere;

    float4 mySphere;
    int i;
    int tile;
    int gtid = blockIdx.x * blockDim.x + threadIdx.x;

    //Make float3 as we want to conserve registers
    //We will only use as much as we need.
    //Set all to maximum possible size
    float3 currentContactNormal[N_SPHERES-1];
    float4 currentContactPointPenetration[N_SPHERES-1];
    int currentContactValid[N_SPHERES-1];

    unsigned rowIndex = computeContactRowIndex(N_SPHERES, gtid);
	unsigned numCols = computeContactNumCols(gtid);

    //Make float4 as we want to coalesce memory accesses
    float4* globalContactNormal = (float4*) &(devContactNormal[rowIndex]);
    float4* globalContactPointPenetration = (float4*) &(devContactPointPenetration[rowIndex]);
    int4* globalContactValidBodies = (int4*) &(devContactValidBodies[rowIndex]);

    //Get current sphere to test all others against
    mySphere = globalSpheres[gtid];

	i = 0;
	
	unsigned amountContactsFirstBlock = (numCols % BLOCK_SIZE);
	tile = blockIdx.x;
    int idx = tile * blockDim.x + threadIdx.x;
    //Collaboratively load sharedSpheres
    sharedSpheres[threadIdx.x] = globalSpheres[idx];
    __syncthreads();
	//Do the first loop, as it is slightly different, not dealing with square blocks, triangular ones instead
	tileSphereSphereCalculationStart(&(currentContactNormal[i]),
								&(currentContactPointPenetration[i]),
								&(currentContactValid[i]),
								mySphere,
								sharedSpheres,
								amountContactsFirstBlock); //don't skip too far ahead, triangular array first
	__syncthreads();

    //Start at our blockID, this ensures we don't check ones
    //that have been done by other blocks
	for (i = amountContactsFirstBlock, tile = (blockIdx.x+1); i < numCols; i += BLOCK_SIZE, tile++)
    {
        idx = tile * blockDim.x + threadIdx.x;
        //Collaboratively load sharedSpheres
        sharedSpheres[threadIdx.x] = globalSpheres[idx];
        __syncthreads();

        tileSphereSphereCalculation(&(currentContactNormal[i]),
                                    &(currentContactPointPenetration[i]),
                                    &(currentContactValid[i]),
                                    mySphere,
                                    sharedSpheres);
		__syncthreads();
    }

    // Save the result in global memory for the collision response step.
    for (i=0;i < numCols;i++)
    {
        //Coalesce memory accesses with float4s instead.
		globalContactNormal[i].x = currentContactNormal[i].x;
		globalContactNormal[i].y = currentContactNormal[i].y;
		globalContactNormal[i].z = currentContactNormal[i].z;
		globalContactNormal[i].w = 0;
        globalContactPointPenetration[i] = currentContactPointPenetration[i];
        globalContactValidBodies[i].x = currentContactValid[i];
		globalContactValidBodies[i].y = gtid; //Set body1 index
		globalContactValidBodies[i].z = (i+gtid+1); //Set body2 index
    }
}

__host__ void
copySpheresToFloat4s(float4* sphereFloat4s,
						jfCollisionSphereStruct* sphereStructs,
						unsigned sphereSize)
{
	for(unsigned i = 0; i < sphereSize ; i++)
	{
		sphereFloat4s[i].x = sphereStructs[i].m_Centre.m_X;
		sphereFloat4s[i].y = sphereStructs[i].m_Centre.m_Y;
		sphereFloat4s[i].z = sphereStructs[i].m_Centre.m_Z;
		sphereFloat4s[i].w = sphereStructs[i].m_Radius; //Use w value as radius.
	}
}

__host__ void
generateContacts(jfContactStruct contactStructs[N_CONTACTS],
					float4 contactNormal[N_CONTACTS],
					float4 contactPointPenetration[N_CONTACTS],
					int4 contactValid[N_CONTACTS],
					unsigned numberContacts)
{
	for(unsigned i = 0; i < numberContacts ; i++)
	{
		if(contactValid[i].x)
		{
			contactStructs[i].m_ContactNormal.m_X = contactNormal[i].x;
			contactStructs[i].m_ContactNormal.m_Y = contactNormal[i].y;
			contactStructs[i].m_ContactNormal.m_Z = contactNormal[i].z;
			contactStructs[i].m_ContactPoint.m_X = contactPointPenetration[i].x;
			contactStructs[i].m_ContactPoint.m_Y = contactPointPenetration[i].y;
			contactStructs[i].m_ContactPoint.m_Z = contactPointPenetration[i].z;
			contactStructs[i].m_Penetration = contactPointPenetration[i].w;
			contactStructs[i].m_Valid = contactValid[i].x;
			contactStructs[i].m_Body1Idx = contactValid[i].y;
			contactStructs[i].m_Body2Idx = contactValid[i].z;
		}
	}
}

/**
 * Wrapper function invoked by "jfCollisionDetector_cuda"
 * class in sphereAndSphereBatch method.
 */
extern "C" void
sphereSphereCollisionTiled(jfCollisionSphereStruct* sphereStructs,
                                jfContactStruct* contactStructs)
{
    float4 contactNormal[N_CONTACTS];
    float4 contactPointPenetration[N_CONTACTS]; //Holds point and penetration
    int4 contactValidBodies[N_CONTACTS]; //Holds validity and body pointers
	float4 sphere[N_SPHERES];

	//Copy spheres over to local float4s
	copySpheresToFloat4s(sphere, sphereStructs, N_SPHERES);

    //Alloc mem on device
    float4* d_ContactNormal;
    cudaMalloc((void**)&d_ContactNormal, N_CONTACTS*sizeof(float4));

    float4* d_ContactPointPenetration;
    cudaMalloc((void**)&d_ContactPointPenetration, N_CONTACTS*sizeof(float4));

    int4* d_ContactValidBodies;
    cudaMalloc((void**)&d_ContactValidBodies, N_CONTACTS*sizeof(int4));

    float4* d_Sphere;
    unsigned sizeSphere = sizeof(float4) * N_SPHERES;
    cudaMalloc((void**)&d_Sphere, sizeSphere);
    cudaMemcpy(d_Sphere, &sphere, sizeSphere, cudaMemcpyHostToDevice);

    //Configure Kernel
    dim3 threads(BLOCK_SIZE, 1);
    dim3 grid((N_SPHERES / BLOCK_SIZE),1);

	//Call Kernel
    calculateContacts<<< grid, threads >>>(d_ContactNormal,
                                            d_ContactPointPenetration,
                                            d_ContactValidBodies,
                                            d_Sphere,
                                            N_SPHERES);
    //Get results from device
    cudaMemcpy(&contactNormal,
                d_ContactNormal,
                N_CONTACTS*sizeof(float4),
                cudaMemcpyDeviceToHost);

    cudaMemcpy(&contactPointPenetration,
                d_ContactPointPenetration,
                N_CONTACTS*sizeof(float4),
                cudaMemcpyDeviceToHost);

    cudaMemcpy(&contactValidBodies,
                d_ContactValidBodies,
                N_CONTACTS*sizeof(int4),
                cudaMemcpyDeviceToHost);

    //Free memory
    cudaFree(d_Sphere);
    cudaFree(d_ContactNormal);
    cudaFree(d_ContactPointPenetration);
    cudaFree(d_ContactValidBodies);

	//Fill in contact objects with contacts generated by kernel call.
	generateContacts(contactStructs, contactNormal, contactPointPenetration, contactValidBodies, N_CONTACTS);
}

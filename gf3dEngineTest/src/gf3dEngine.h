#ifndef _GF3DENGINE_H
#define _GF3DENGINE_H

/*#ifdef __cplusplus
extern "C"
{
#endif
*/

#include "gfTypes.h"
#include "gfBitmap.h"
#include <math.h>


typedef struct _vec2_t
{
	float	x;
	float	y;
	float	w;

}vec2_t;


typedef struct _vec3_t
{
	float	x;
	float	y;
	float	z;
	float	w;

}vec3_t;

typedef struct _triangle_t
{

	vec3_t		p[3];		//vertices points [3]
	vec2_t		t[3];		//texture points [3]

	tgfBitmap	*texture;

}triangle_t;

typedef struct _matrix4x4_t
{
	float m[4][4];

}matrix4_4_t;


typedef struct _tgfMesh
{
	uint32_t	numTriangles;
	uint32_t	maxTriangles;
	uint32_t	getTriangleIndex;
	triangle_t	*tri;


}tgfMesh;


typedef struct tgfScene
{
	tgfBitmap 	*frameBuffer;
	tgfBitmap	*zBuffer;

	matrix4_4_t	projectionMatrix;
	vec3_t		vCamera;
	vec3_t		vLookDir;

	tgfMesh		mesh;

	tgfMesh		meshRaster;

}tgfScene;



#define degToRad( angleInDegrees ) ( (angleInDegrees) * M_PI / 180.0 )
#define radToDeg( angleInRadians ) ( (angleInRadians) * 180.0 / M_PI )

uint32_t gf3dVectorClear( vec3_t * out );
uint32_t gf3dVectorCopy( vec3_t * out, vec3_t *v );
uint32_t gf3dVectorAdd( vec3_t *out, vec3_t *v1, vec3_t *v2 );
uint32_t gf3dVectorSub( vec3_t *out, vec3_t *v1, vec3_t *v2 );
uint32_t gf3dVectorMul( vec3_t *out, vec3_t *v1, float k );
uint32_t gf3dVectorDiv( vec3_t *out, vec3_t *v1, float k );
uint32_t gf3dVectorDotProduct( float *out, vec3_t *v1, vec3_t *v2 );
uint32_t gf3dVectorLength( float *out, vec3_t *v );
uint32_t gf3dVectorNormalise( vec3_t *out, vec3_t *v );
uint32_t gf3dVectorCrossProduct( vec3_t *out, vec3_t *v1, vec3_t *v2 );
uint32_t gf3dVectorIntersectPlane( vec3_t *out, vec3_t *plane_p, vec3_t *plane_n, vec3_t *lineStart, vec3_t *lineEnd, float *t );

uint32_t gf3dVector2Clear( vec2_t * out );
uint32_t gf3dVector2Copy( vec2_t * out, vec2_t *v );

uint32_t gf3dMatrixClear( matrix4_4_t *out );
uint32_t gf3dMatrixCopy( matrix4_4_t *out, matrix4_4_t *m );
uint32_t gf3dMatrixMultiplyVector( vec3_t *out, matrix4_4_t *m, vec3_t *i );
uint32_t gf3dMatrixMakeIdentity( matrix4_4_t *out );
uint32_t gf3dMatrixMakeRotationX( matrix4_4_t *out, float fAngleRad );
uint32_t gf3dMatrixMakeRotationY( matrix4_4_t *out, float fAngleRad );
uint32_t gf3dMatrixMakeRotationZ( matrix4_4_t *out, float fAngleRad );
uint32_t gf3dMatrixMakeTranslation( matrix4_4_t *out, float x, float y, float z );
uint32_t gf3dMatrixMakeProjection( matrix4_4_t *out, float fFovDegrees, float fAspectRatio, float fNear, float fFar );
uint32_t gf3dMatrixMultiplyMatrix( matrix4_4_t *out, matrix4_4_t *m1, matrix4_4_t *m2 );

uint32_t gf3dTriangleCopy( triangle_t *out, triangle_t *tri );

uint32_t gf3dMeshNew( tgfMesh *out );
uint32_t gf3dMeshAllocate( tgfMesh *mesh, uint32_t maxNumTriangles );
uint32_t gf3dMeshClear( tgfMesh *mesh );
uint32_t gf3dMeshAdd( tgfMesh *mesh, triangle_t *tri );
uint32_t gf3dMeshGetStart( tgfMesh *mesh );
triangle_t * gf3dMeshGetNext( tgfMesh *mesh );
uint32_t gf3dMeshLoadOBJ( tgfMesh *outMesh, char *fileName, float scaleFactor, tgfBitmap *texture );


/*#ifdef __cplusplus
}
#endif
*/

#endif

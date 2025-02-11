
#include "gf3dEngine.h"

#include "bsp.h"
#include "osAlloc.h"
#include "osFile.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

uint32_t gf3dVectorClear( vec3_t * out )
{
	out->x	= 0.0f;
	out->y	= 0.0f;
	out->z	= 0.0f;
	out->w	= 1.0f;

	return 0;
}

uint32_t gf3dVectorCopy( vec3_t * out, vec3_t *v )
{
	out->x	= v->x;
	out->y	= v->y;
	out->z	= v->z;
	out->w	= v->w;

	return 0;
}

uint32_t gf3dVectorAdd( vec3_t *out, vec3_t *v1, vec3_t *v2 )
{
	out->x = v1->x + v2->x;
	out->y = v1->y + v2->y;
	out->z = v1->z + v2->z;

	return 0;
}

uint32_t gf3dVectorSub( vec3_t *out, vec3_t *v1, vec3_t *v2 )
{
	out->x = v1->x - v2->x;
	out->y = v1->y - v2->y;
	out->z = v1->z - v2->z;

	return 0;
}

uint32_t gf3dVectorMul( vec3_t *out, vec3_t *v1, float k )
{
	out->x = v1->x * k;
	out->y = v1->y * k;
	out->z = v1->z * k;

	return 0;
}

uint32_t gf3dVectorDiv( vec3_t *out, vec3_t *v1, float k )
{
	out->x = v1->x / k;
	out->y = v1->y / k;
	out->z = v1->z / k;

	return 0;
}

uint32_t gf3dVectorDotProduct( float *out, vec3_t *v1, vec3_t *v2 )
{
	*out = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;

	return 0;
}

uint32_t gf3dVectorLength( float *out, vec3_t *v )
{
	float dp;

	gf3dVectorDotProduct( &dp, v, v );

	*out = sqrtf( dp );

	return 0;
}

uint32_t gf3dVectorNormalise( vec3_t *out, vec3_t *v )
{
	float l;

	gf3dVectorLength( &l, v );

	out->x = v->x / l;
	out->y = v->y / l;
	out->z = v->z / l;

	return 0;
}

uint32_t gf3dVectorCrossProduct( vec3_t *out, vec3_t *v1, vec3_t *v2 )
{
	out->x = v1->y * v2->z - v1->z * v2->y;
	out->y = v1->z * v2->x - v1->x * v2->z;
	out->z = v1->x * v2->y - v1->y * v2->x;

	return 0;
}

uint32_t gf3dVectorIntersectPlane( vec3_t *out, vec3_t *plane_p, vec3_t *plane_n, vec3_t *lineStart, vec3_t *lineEnd, float *t )
{
	vec3_t 	plane_n_norm;
	float	plane_d;
	float	ad;
	float	bd;

	vec3_t	lineStartToEnd    = { .x = 0.0f, .y = 0.0f, .z = 0.0f, .w = 1.0f };
	vec3_t   lineToIntersect   = { .x = 0.0f, .y = 0.0f, .z = 0.0f, .w = 1.0f };

	gf3dVectorNormalise( &plane_n_norm, plane_n );

	gf3dVectorDotProduct( &plane_d, &plane_n_norm, plane_p );
	plane_d *= -1;

	gf3dVectorDotProduct( &ad, lineStart, &plane_n_norm );
	gf3dVectorDotProduct( &bd, lineEnd, &plane_n_norm );

	*t = ( -plane_d - ad) / ( bd - ad );

	gf3dVectorSub( &lineStartToEnd, lineEnd, lineStart );
	gf3dVectorMul( &lineToIntersect, &lineStartToEnd, *t );

	gf3dVectorAdd( out, lineStart, &lineToIntersect );

	return 0;
}


uint32_t gf3dVector2Clear( vec2_t * out )
{
   out->x   = 0.0f;
   out->y   = 0.0f;
   out->w   = 1.0f;

   return 0;
}

uint32_t gf3dVector2Copy( vec2_t * out, vec2_t *v )
{
   out->x   = v->x;
   out->y   = v->y;
   out->w   = v->w;

   return 0;
}

uint32_t gf3dMatrixClear( matrix4_4_t *out )
{
	uint32_t x;
	uint32_t y;

	for( y = 0; y < 4; y++ )
	{
		for( x = 0; x < 4; x++ )
		{
			out->m[x][y] = 0;
		}
	}

	return 0;
}

uint32_t gf3dMatrixCopy( matrix4_4_t *out, matrix4_4_t *m )
{
	uint32_t x;
	uint32_t y;

	for( y = 0; y < 4; y++ )
	{
		for( x = 0; x < 4; x++ )
		{
			out->m[x][y] = m->m[x][y];
		}
	}

	return 0;
}


uint32_t gf3dMatrixMultiplyVector( vec3_t *out, matrix4_4_t *m, vec3_t *i )
{
	out->x = i->x * m->m[0][0] + i->y * m->m[1][0] + i->z * m->m[2][0] + i->w * m->m[3][0];
	out->y = i->x * m->m[0][1] + i->y * m->m[1][1] + i->z * m->m[2][1] + i->w * m->m[3][1];
	out->z = i->x * m->m[0][2] + i->y * m->m[1][2] + i->z * m->m[2][2] + i->w * m->m[3][2];
	out->w = i->x * m->m[0][3] + i->y * m->m[1][3] + i->z * m->m[2][3] + i->w * m->m[3][3];

	return 0;
}

uint32_t gf3dMatrixMakeIdentity( matrix4_4_t *out )
{
	out->m[0][0] = 1.0f;
	out->m[1][1] = 1.0f;
	out->m[2][2] = 1.0f;
	out->m[3][3] = 1.0f;

	return 0;
}

uint32_t gf3dMatrixMakeRotationX( matrix4_4_t *out, float fAngleRad )
{

   out->m[0][0] = 1.0f;
	out->m[1][1] = cosf( fAngleRad );
	out->m[1][2] = sinf( fAngleRad );
	out->m[2][1] = -sinf( fAngleRad );
	out->m[2][2] = cosf( fAngleRad );
	out->m[3][3] = 1.0f;

	return 0;
}

uint32_t gf3dMatrixMakeRotationY( matrix4_4_t *out, float fAngleRad )
{

   out->m[0][0] = cosf( fAngleRad );
	out->m[0][2] = sinf( fAngleRad );
	out->m[2][0] = -sinf( fAngleRad );
	out->m[1][1] = 1.0f;
	out->m[2][2] = cosf( fAngleRad );
	out->m[3][3] = 1.0f;

	return 0;
}

uint32_t gf3dMatrixMakeRotationZ( matrix4_4_t *out, float fAngleRad )
{
	out->m[0][0] = cosf( fAngleRad );
	out->m[0][1] = sinf( fAngleRad );
	out->m[1][0] = -sinf( fAngleRad );
	out->m[1][1] = cosf( fAngleRad );
	out->m[2][2] = 1.0f;
	out->m[3][3] = 1.0f;

	return 0;
}

uint32_t gf3dMatrixMakeTranslation( matrix4_4_t *out, float x, float y, float z )
{
	out->m[0][0] = 1.0f;
	out->m[1][1] = 1.0f;
	out->m[2][2] = 1.0f;
	out->m[3][3] = 1.0f;
	out->m[3][0] = x;
	out->m[3][1] = y;
	out->m[3][2] = z;

	return 0;
}

uint32_t gf3dMatrixMakeProjection( matrix4_4_t *out, float fFovDegrees, float fAspectRatio, float fNear, float fFar )
{
	float fFovRad;

	fFovRad = 1.0f / tanf( fFovDegrees * 0.5f / 180.0f * 3.14159f );

	out->m[0][0] = fAspectRatio * fFovRad;
	out->m[1][1] = fFovRad;
	out->m[2][2] = fFar / (fFar - fNear);
	out->m[3][2] = (-fFar * fNear) / (fFar - fNear);
	out->m[2][3] = 1.0f;
	out->m[3][3] = 0.0f;

	return 0;
}


uint32_t gf3dMatrixMultiplyMatrix( matrix4_4_t *out, matrix4_4_t *m1, matrix4_4_t *m2 )
{
	uint32_t y;
	uint32_t x;

	for( y = 0; y < 4; y++ )
	{
		for( x = 0; x < 4; x++ )
		{
			out->m[x][y] = m1->m[x][0] * m2->m[0][y] + m1->m[x][1] * m2->m[1][y] + m1->m[x][2] * m2->m[2][y] + m1->m[x][3] * m2->m[3][y];
		}
	}

	return 0;
}

uint32_t gf3dMatrixQuickInverse( matrix4_4_t *out, matrix4_4_t *m ) // Only for Rotation/Translation Matrices
{
	out->m[0][0] = m->m[0][0]; out->m[0][1] = m->m[1][0]; out->m[0][2] = m->m[2][0]; out->m[0][3] = 0.0f;
	out->m[1][0] = m->m[0][1]; out->m[1][1] = m->m[1][1]; out->m[1][2] = m->m[2][1]; out->m[1][3] = 0.0f;
	out->m[2][0] = m->m[0][2]; out->m[2][1] = m->m[1][2]; out->m[2][2] = m->m[2][2]; out->m[2][3] = 0.0f;
	out->m[3][0] = -( m->m[3][0] * out->m[0][0] + m->m[3][1] * out->m[1][0] + m->m[3][2] * out->m[2][0] );
	out->m[3][1] = -( m->m[3][0] * out->m[0][1] + m->m[3][1] * out->m[1][1] + m->m[3][2] * out->m[2][1] );
	out->m[3][2] = -( m->m[3][0] * out->m[0][2] + m->m[3][1] * out->m[1][2] + m->m[3][2] * out->m[2][2] );
	out->m[3][3] = 1.0f;

	return 0;
}


uint32_t gf3dTriangleCopy( triangle_t *out, triangle_t *tri )
{
	uint32_t	i;

	out->texture = tri->texture;
	for( i = 0; i < 3; i++ )
	{
		out->p[i].x = tri->p[i].x;
		out->p[i].y	= tri->p[i].y;
		out->p[i].z = tri->p[i].z;
		out->p[i].w = tri->p[i].w;

		out->t[i].x = tri->p[i].x;
		out->t[i].y = tri->p[i].y;
		out->t[i].w = tri->p[i].w;
	}

	return 0;
}

uint32_t gf3dMeshNew( tgfMesh *out )
{

	out->numTriangles		= 0;
	out->getTriangleIndex	= 0;
	out->maxTriangles		= 0;
	out->tri				= NULL;

	return 0;
}

uint32_t gf3dMeshAllocate( tgfMesh *mesh, uint32_t maxNumTriangles )
{
	mesh->numTriangles		= 0;
	mesh->getTriangleIndex	= 0;
	mesh->maxTriangles		= maxNumTriangles;

	if( mesh->tri )
	{
		osFree( mesh->tri );
	}

	mesh->tri	= ( triangle_t *)osAlloc( sizeof( triangle_t ) * maxNumTriangles, OS_ALLOC_MEMF_CHIP );

	if( mesh->tri )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

uint32_t gf3dMeshClear( tgfMesh *mesh )
{
	mesh->numTriangles 		= 0;
	mesh->getTriangleIndex	= 0;

	return 0;
}

uint32_t gf3dMeshAdd( tgfMesh *mesh, triangle_t *tri )
{
	if( mesh->numTriangles < mesh->maxTriangles )
	{
		gf3dTriangleCopy( &mesh->tri[ mesh->numTriangles++ ], tri );

		return 0;
	}
	else
	{
		return 1;
	}
}

uint32_t gf3dMeshGetStart( tgfMesh *mesh )
{
	mesh->getTriangleIndex = 0;

	return 0;
}

triangle_t * gf3dMeshGetNext( tgfMesh *mesh )
{
	if( mesh->getTriangleIndex < mesh->numTriangles )
	{
		return &mesh->tri[ mesh->getTriangleIndex++ ];
	}
	else
	{
	   return NULL;
	}
}

uint32_t gf3dMeshLoadOBJ( tgfMesh *outMesh, char *fileName, float scaleFactor, tgfBitmap *texture )
{
	tosFile		in;
	char  		lineBuf[256];
   uint16_t    lineIdx;
	uint32_t    lineLen;

	uint32_t    objNumTriPoints;
	uint32_t    objNumTriangles;
	uint32_t   	objNumTexturePoints;

   float       x;
   float       y;
   float       z;

   uint32_t    p1;
   uint32_t    p2;
   uint32_t    p3;
   uint32_t    t1;
   uint32_t    t2;
   uint32_t    t3;

	//local point buffers

	//triangle vertices
	vec3_t      *objTriPoints;
   uint32_t    triPointIdx;
   vec3_t      triPoint = { .x = 0, .y = 0, .z = 0, .w = 1 };

	//texture coordinates
	vec2_t      *objTexturePoints;
   uint32_t    texturePointIdx;
   vec2_t      texturePoint = { .x = 0, .y = 0, .w = 1 };

   objNumTriPoints      = 0;
   objNumTriangles      = 0;
   objNumTexturePoints  = 0;

   objTriPoints         = NULL;
   objTexturePoints     = NULL;

   triPointIdx          = 0;
   texturePointIdx      = 0;

   triangle_t           tri;

   if( osFOpen( &in, fileName, OS_FILE_READ ) )
   {
      return 1;
   }

   while( !osFGetS( &in, (uint8_t*)lineBuf, sizeof( lineBuf ) ) )
   {

      lineLen = strlen( lineBuf );

      if( lineLen > 2 )
      {
         if( ( lineBuf[0] == 'v' ) && ( lineBuf[1] == ' ' ) )
         {
            objNumTriPoints++;
         }

         if( ( lineBuf[0] == 'v' ) && ( lineBuf[1] == 't' ) && ( lineBuf[2] == ' ' ) )
         {
            objNumTexturePoints++;
         }

         if( ( lineBuf[0] == 'f' ) && ( lineBuf[1] == ' ' ) )
         {
            objNumTriangles++;
         }
      }
   }
   osFClose( &in );

   if( objNumTriPoints == 0 )
   {
      return 1;
   }

   if( objNumTriangles == 0 )
   {
      return 1;
   }

   //allocate point buffers

   objTriPoints = ( vec3_t * )osAlloc( sizeof( vec3_t ) * objNumTriPoints, OS_ALLOC_MEMF_CHIP );

   if( objTexturePoints )
   {
      objTexturePoints = ( vec2_t * )osAlloc( sizeof( vec2_t ) * objNumTexturePoints, OS_ALLOC_MEMF_CHIP );

   }

   //init mesh
   if( gf3dMeshNew( outMesh ) )
   {
      return 1;
   }

   //allocate mesh triangle buffer
   if( gf3dMeshAllocate( outMesh, objNumTriangles ) )
   {
      //free point buffers

      if( objTriPoints )
      {
         osFree( objTriPoints );
         objTriPoints   = NULL;
      }

      if( objTexturePoints )
      {
         osFree( objTexturePoints );
         objTexturePoints = NULL;
      }

      return 1;
   }

   if( osFOpen( &in, fileName, OS_FILE_READ ) )
   {
      //free point buffers

      if( objTriPoints )
      {
         osFree( objTriPoints );
         objTriPoints   = NULL;
      }

      if( objTexturePoints )
      {
         osFree( objTexturePoints );
         objTexturePoints = NULL;
      }

      return 1;
   }

   while( !osFGetS( &in, (uint8_t*)lineBuf, sizeof( lineBuf ) ) )
   {

      lineLen = strlen( lineBuf );

      if( lineLen > 2 )
      {
         if( ( lineBuf[0] == 'v' ) && ( lineBuf[1] == ' ' ) )
         {

             lineIdx = 2;
             x = atof( &lineBuf[lineIdx] );

             //find space
             while( lineIdx < lineLen )
             {
               if( lineBuf[ lineIdx++ ] == ' ' )
               {
                  break;
               }
             }

             y = atof( &lineBuf[lineIdx] );
             //find space
             while( lineIdx < lineLen )
             {
               if( lineBuf[ lineIdx++ ] == ' ' )
               {
                  break;
               }
             }
             z = atof( &lineBuf[lineIdx] );

             triPoint.x = x * scaleFactor;
             triPoint.y = y * scaleFactor;
             triPoint.z = z * scaleFactor;
             triPoint.w = 1;

             //add triangle vertex ( point 3d )

             gf3dVectorCopy( &objTriPoints[ triPointIdx++ ], &triPoint );

         }

         if( ( lineBuf[0] == 'v' ) && ( lineBuf[1] == 't' ) && ( lineBuf[2] == ' ' )  )
         {

             lineIdx = 3;
             x = atof( &lineBuf[lineIdx] );

             //find space
             while( lineIdx < lineLen )
             {
               if( lineBuf[ lineIdx++ ] == ' ' )
               {
                  break;
               }
             }

             y = atof( &lineBuf[lineIdx] );
             //find space
             while( lineIdx < lineLen )
             {
               if( lineBuf[ lineIdx++ ] == ' ' )
               {
                  break;
               }
             }

             //add texture coordinate

             texturePoint.x = x;
             texturePoint.y = y;
             texturePoint.w = 1;

             gf3dVector2Copy( &objTexturePoints[ texturePointIdx++ ], &texturePoint );

         }


         if( ( lineBuf[0] == 'f' ) && ( lineBuf[1] == ' ' ) )
         {
             lineIdx = 2;
             p1 = atoi( &lineBuf[lineIdx] );

             if( objNumTexturePoints > 0 )
             {
               //find '/'
               while( lineIdx < lineLen )
               {
                  if( lineBuf[ lineIdx++ ] == '/' )
                  {
                     break;
                  }
               }
               t1 = atoi( &lineBuf[lineIdx] );
             }

             //find space
             while( lineIdx < lineLen )
             {
               if( lineBuf[ lineIdx++ ] == ' ' )
               {
                  break;
               }
             }

             p2 = atoi( &lineBuf[lineIdx] );

             if( objNumTexturePoints > 0 )
             {
               //find '/'
               while( lineIdx < lineLen )
               {
                  if( lineBuf[ lineIdx++ ] == '/' )
                  {
                     break;
                  }
               }
               t2 = atoi( &lineBuf[lineIdx] );
             }

             //find space
             while( lineIdx < lineLen )
             {
               if( lineBuf[ lineIdx++ ] == ' ' )
               {
                  break;
               }
             }

             p3 = atoi( &lineBuf[lineIdx] );

             if( objNumTexturePoints > 0 )
             {
               //find '/'
               while( lineIdx < lineLen )
               {
                  if( lineBuf[ lineIdx++ ] == '/' )
                  {
                     break;
                  }
               }

               t3 = atoi( &lineBuf[lineIdx] );
             }

             //points
             gf3dVectorCopy( &tri.p[0], &objTriPoints[ p1 - 1 ] );
             gf3dVectorCopy( &tri.p[1], &objTriPoints[ p2 - 1 ] );
             gf3dVectorCopy( &tri.p[2], &objTriPoints[ p3 - 1 ] );


             if( texture != NULL )
             {
               if( objNumTexturePoints > 0 )
               {
                  //texture coords are present in file
                  gf3dVector2Copy( &tri.t[0], &objTexturePoints[ t1 - 1 ] );
                  gf3dVector2Copy( &tri.t[1], &objTexturePoints[ t2 - 1 ] );
                  gf3dVector2Copy( &tri.t[2], &objTexturePoints[ t3 - 1 ] );

               }
               else
               {
                  //random texture coords
                  tri.t[0].x  = (float)( ( randomNumber() & 255 ) / 255.0f );
                  tri.t[0].y  = (float)( ( randomNumber() & 255 ) / 255.0f );
                  tri.t[0].w  = 1.0f;

                  tri.t[1].x  = (float)( ( randomNumber() & 255 ) / 255.0f );
                  tri.t[1].y  = (float)( ( randomNumber() & 255 ) / 255.0f );
                  tri.t[1].w  = 1.0f;

                  tri.t[2].x  = (float)( ( randomNumber() & 255 ) / 255.0f );
                  tri.t[2].y  = (float)( ( randomNumber() & 255 ) / 255.0f );
                  tri.t[2].w  = 1.0f;


               }
               tri.texture = texture;

             }
             else
             {
                tri.texture = NULL;
             }

             //add triangle to mesh
             gf3dMeshAdd( outMesh, &tri );

         }
      }
   }
   osFClose( &in );


   //free point buffers

   if( objTriPoints )
   {
      osFree( objTriPoints );
      objTriPoints   = NULL;
   }

   if( objTexturePoints )
   {
      osFree( objTexturePoints );
      objTexturePoints = NULL;
   }

	return 0;
}

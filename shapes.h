#ifndef SHAPES_H
#define SHAPES_H
#include <gl/freeglut.h>
#include <vector.h>

extern float const x_goal; // x position of goal, counting from origin (0.0)
extern bool show_vectors; // render/not render simulational vectors

class shape
{
	protected:
		
		vector2 pos; // position of the shape's center (point)
		vector2 speed; // speed vector
		unsigned int np; // number of shape's points (vertices)
		vector2 *verts; // pointer to an array of shape's vertices
		
		void applySpeedVec(vector2 spd); // translate object's points and position by applying given vector
		bool detectCollision(shape *obst[], int n); // detect collision with array of obstacles (other shapes)
		void drawVector(vector2 const &base_p, vector2 const &vec, // display vector
						float v_scale, float r = 0, float g = 1, float b = 0);
	
	public:
		
		shape(unsigned int num_p = 0); // num_p - number of points in a shape
		~shape();
		virtual void renderMe() = 0; // display shape interface
		
		unsigned int pnum(); // get number of points in a shape
		vector2 const* getPoints(); // get pointer to const array of shape's vertices
		vector2 getSpeed(); // get shape's speed vector
		
		void setSpeed(vector2 acc); // set object's speed i.e. add/substruct acceleration
		void setPos(float x, float y); //set object's position
		void enablePhysics(shape *ob[], int obn); //enable shape in phisics simulation
};

class rectangle : public shape
{
	public:
		
		rectangle(float w = 2, float h = 3, float x = 0, float y = 0); // construct rectangle (width, height, position)
		
		vector2 getTop(); // extract top-left vertice
		vector2 getBot(); // extract bottom-right vertice
		
		void renderMe();
};

class circle : public shape
{	
	vector2 new_start_spd; // "random" speed at ball relocation, instead of pseudo-RNG
	
	public:
		
		short unsigned int score[2]; // score of pong match
		circle(float r = 2, float x = 0, float y = 0); // construct circle (radius, position)
		
		void pongScore(); // display score and reset ball position
		void setNewBallSpd(); // reset ball speed
		void renderMe();
};

#endif  /* SHAPES_H */

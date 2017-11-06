#include <shapes.h>
#include <mymath.h>

#define BOUNCE_C 0.05 // coefficient of "bounceiness" for ball/walls/bats material

using namespace math;

const vector2 vec0; // zero vector/point
float const x_goal = 10; // external var, x absolute position of goal, counting from origin (0.0)
bool show_vectors = false; // external variable, do not show vectors by default

shape::shape(unsigned int num_p) : speed(vec0), np(num_p)
{
	verts = new vector2[np]; // allocate heap memory for np number of vertices
}

shape::~shape() { delete verts; } // clear memory allocated for shape's vertices

void shape::applySpeedVec(vector2 spd)
{
	pos += spd;
	
	for(int i = 0; i < np; ++i)
		verts[i] += spd;
}

bool shape::detectCollision(shape *obst[], int n) // this only detects collision with (non-tilted) rectangles
{												 // to check collision with any shape need more complex algorithm
	unsigned int o_i = 0; // index of the obstacle that is beeing checked
	for( ; o_i < n; ++o_i) // check collision for every obstacle
	{
		vector2 const *obst_p = obst[o_i]->getPoints(); // obstacle points
		vector2 s_trans_min; // smallest obstacle cliping reset translation
		for(int i = 0; i < np; ++i) // for every point of this object
		{
			vector2 f_pos = verts[i] + speed; // Future position of a point
			vector2 hitvec; // vector of obst. side that was hit by object
			bool on_edge = verts[i].x == obst_p[2].x || verts[i].x == obst_p[0].x || // ceck if object is on edge
				 verts[i].y == obst_p[0].y || verts[i].y == obst_p[2].y ? true : false; // of obstacle
			
			if(on_edge)
			{				
				vector2 p_pos = verts[i] + (-speed); // past position of a point
				//Find side vector of object/obstacle collision
				if(p_pos.x < obst_p[2].x)
				{
					if(p_pos.x > obst_p[0].x)
					{
						if(p_pos.y < obst_p[0].y)
						{
							hitvec = obst_p[3] - obst_p[2]; // vector from one bottom right point to bot left
						}
						else
							hitvec = obst_p[1] - obst_p[0]; // top-left --> top-right vector
					}
					else
						hitvec = obst_p[0] - obst_p[3]; //  bot-left --> top-left vector
				}
				else
					hitvec = obst_p[2] - obst_p[1]; // top-right --> bot-right vector
				
				vector2 ortho_hit_v = hitvec.ortho(); // vector perpendicular to obstacle side
				vector2 unit_obst_f = ortho_hit_v.normalize(); // unit vector of obstacle's force (speed) that counter object's speed
				float obst_force_mag = np == 4 ? speed.mag() : speed.mag() + BOUNCE_C; // obstacle force magnitude
				vector2 obst_force = unit_obst_f * obst_force_mag; // final obstacle force speed of object + bounce coefficient
					
				if(show_vectors) drawVector(pos, obst_force, 12, 0, 1, 1); // draw obstacle return force vector
				
				speed += obst_force; // calculate bounce vector by adding vector of object's speed and counter force of obstacle
				if(obst[o_i]->getSpeed() != 0)
					speed += obst[o_i]->getSpeed(); // add speed from bat, if bat is moving
				
				applySpeedVec(speed); // translate points
				return true; // collision happened, return 1
			}
			
			if(!on_edge && f_pos.x < obst_p[2].x && f_pos.x > obst_p[0].x)
			{
				if(f_pos.y < obst_p[0].y && f_pos.y > obst_p[2].y)
				{
					vector2 q; // base point of hitvect (basepoint of obst. side)
					if(verts[i].x <= obst_p[2].x)
					{
						if(verts[i].x >= obst_p[0].x)
						{
							if(verts[i].y <= obst_p[0].y)
							{
								hitvec = obst_p[3] - obst_p[2]; // vector from one bottom right point to bot left
								q = obst_p[2];
							}
							else
							{
								hitvec = obst_p[1] - obst_p[0]; // top-left --> top-right vector
								q = obst_p[0];
							}
						}
						else
						{
							hitvec = obst_p[0] - obst_p[3]; //  bot-left --> top-left vector
							q = obst_p[3];
						}
					}
					else
					{
						hitvec = obst_p[2] - obst_p[1]; // top-right --> bot-right vector
						q = obst_p[1];
					}
					
					if(show_vectors) drawVector(q, hitvec, 1, 1, 0, 0); // draw obstacle hit side vector
					
					/* get crossing point between 2 line segments to not let object clip inside of obstacle:
					q - base of obstacle line; s - vector from q to end of obstacle line;
					p - point of object that is outside of obstacle; r - vector from p to objects future position (speed);
					u and t - scalars; crossing point will be at: p + tr = q + us; */
					
					vector2 q_delta_p = q - verts[i];
					float vectors_cross = speed.cross2D(hitvec);
					float u = q_delta_p.cross2D(speed) / vectors_cross;
					vector2 intersection_point = q + (hitvec * u);
					vector2 short_trans = intersection_point - verts[i]; // vector to translate object before it hits obstacle
					
					// find smallest translation, i.e. from a point that is closest to obstacle
					if(s_trans_min == vec0)
						s_trans_min = short_trans;
					else if(short_trans.mag() < s_trans_min.mag())
						s_trans_min = short_trans;
				}
			}
		}
		if(s_trans_min != vec0)
		{
			applySpeedVec(s_trans_min); // translate points
			return true; // collision happened, return 1
		}
	}
	return false; // no collision found, return 0
}

void shape::drawVector(vector2 const &base_p, vector2 const &vec,
						float v_scale, float r, float g, float b)
{
	vector2 spd_head = (base_p + (vec * v_scale));
	vector2 arrow_head = (-vec * v_scale) * 0.25;
	if(arrow_head.mag() > 1) arrow_head = arrow_head * 0.15;
	else if(arrow_head.mag() > 0.5) arrow_head = arrow_head * 0.55;
	vector2 arrow_h_L;
	arrow_h_L.x = arrow_head.x * cos_d(30) - arrow_head.y * sin_d(30);
	arrow_h_L.y = arrow_head.x * sin_d(30) + arrow_head.y * cos_d(30);
	vector2 arrow_h_R;
	arrow_h_R.x = arrow_head.x * cos_d(330) - arrow_head.y * sin_d(330);
	arrow_h_R.y = arrow_head.x * sin_d(330) + arrow_head.y * cos_d(330);
	arrow_h_L += spd_head;
	arrow_h_R += spd_head;
	glBegin(GL_LINES);
	glColor3f(r, g, b);
	glVertex3f(base_p.x, base_p.y, 0.01);
	glVertex3f(spd_head.x, spd_head.y, 0.01);
	glVertex3f(arrow_h_L.x, arrow_h_L.y, 0.01);
	glVertex3f(spd_head.x, spd_head.y, 0.01);
	glVertex3f(arrow_h_R.x, arrow_h_R.y, 0.01);
	glVertex3f(spd_head.x, spd_head.y, 0.01);
	glEnd();
}

unsigned int shape::pnum() { return np; }

vector2 const* shape::getPoints() { return verts; }

vector2 shape::getSpeed() { return speed; }

void shape::setSpeed(vector2 acc)
{
	speed = acc;
}

void shape::setPos(float x, float y)
{
	vector2 translate = vector2(x, y) - pos;
	applySpeedVec(translate);
}

void shape::enablePhysics(shape *ob[], int obn)
{
	if(!detectCollision(ob, obn)) // if collision is not detected
		if(speed != vec0) applySpeedVec(speed); // and if speed non-0, translate points
}

rectangle::rectangle(float w, float h, float x, float y) : shape(4) // call shape constructor i.e. create 4-point rectangle
{
	vector2 pos_o(x, y); // original position
	pos = pos_o;
	float hw = w/2, hh = h/2; // half width, half height
	verts[0] = pos + vector2(-hw, hh); // translate original position to top left corner
	verts[1] = pos + vector2(hw, hh); // translate original position to top right corner
	verts[2] = pos + vector2(hw, -hh); // translate original position to bottom right corner
	verts[3] = pos + vector2(-hw, -hh); // translate original position to bottom left corner
}

vector2 rectangle::getTop()
{
	return verts[0];
}

vector2 rectangle::getBot()
{
	return verts[2];
}

void rectangle::renderMe()
{
	glColor3f(0.92, 0.92, 0.95); // light grey
	glBegin(GL_QUADS);
		for(int i = 0; i < np; ++i)
			glVertex2f(verts[i].x, verts[i].y);
	glEnd();
	
	if(show_vectors) drawVector(pos, speed, 12); // display box speed vectors
}

circle::circle(float r, float x, float y) : shape(32) // call shape constructor i.e. create 32-point circle
{
	speed = vector2(0.07, 0.07); // set default speed
	new_start_spd = speed;
	score[0] = score[1] = 0;
	float dang = 360.f / np; // delta-angle between points - full circle/number of points
	float ang = 0.0;
	
	for(int i = 0; i < np; ++i) // calculate each point of a circle
	{
		vector2 tmp;
		tmp.x = r * cos_d(ang);
		tmp.y = r * sin_d(ang);
		verts[i] = tmp;
		ang += dang;
	}
}

void circle::pongScore()
{
	if(score[0] != 0 || score[1] != 0) //print score
	{
		char p1_score, p2_score;
		switch(score[0]) // don't want to include <string> or <iostream> for this!
		{
			case 0: p1_score = '0'; break;
			case 1: p1_score = '1'; break;
			case 2: p1_score = '2'; break;
			case 3: p1_score = '3'; break;
			case 4: p1_score = '4'; break;
			case 5: p1_score = '5';
		}
		switch(score[1])
		{
			case 0: p2_score = '0'; break;
			case 1: p2_score = '1'; break;
			case 2: p2_score = '2'; break;
			case 3: p2_score = '3'; break;
			case 4: p2_score = '4'; break;
			case 5: p2_score = '5';
		}
		
		glColor3f(0.22, 0.22, 0.25);
		glPushMatrix();
		glTranslatef(-x_goal/2-0.5, -1.8, -0.01);
		glScalef(0.03, 0.03, 0);
		glLineWidth(9);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, p1_score);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(x_goal/2-0.5, -1.8, -0.01);
		glScalef(0.03, 0.03, 0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, p2_score);
		glPopMatrix();
	}
	glLineWidth(3);
	if(score[0] == 5)
	{
		glPushMatrix();
		glTranslatef(-5.5, -4, -0.01);
		glScalef(0.006, 0.006, 0);
		unsigned char const str[] = "P1 wins! Press R to restart";
		glutStrokeString(GLUT_STROKE_ROMAN, str);
		glPopMatrix();
	}
	else if(score[1] == 5)
	{
		glPushMatrix();
		glTranslatef(-5.5, -4, -0.01);
		glScalef(0.006, 0.006, 0);
		unsigned char const str[] = "P2 wins! Press R to restart";
		glutStrokeString(GLUT_STROKE_ROMAN, str);
		glPopMatrix();
	}
	else
	{
		if(pos.x < -x_goal-1)
		{
			++score[1];
			if(score[1] != 5)
			{
				setPos(0, 0);
				setNewBallSpd();
			}
		}
		else if(pos.x > x_goal+1)
		{
			++score[0];
			if(score[0] != 5)
			{
				setPos(0, 0);
				setNewBallSpd();
			}
		}
	}
	glLineWidth(1);
}

void circle::setNewBallSpd()
{
	vector2 new_spd;
	new_spd.x = new_start_spd.x * cos_d(90) - new_start_spd.y * sin_d(90);
	new_spd.y = new_start_spd.x * sin_d(90) + new_start_spd.y * cos_d(90);
	speed = new_spd;
	new_start_spd = new_spd; // add a little increce in initial speed after each respawn
}

void circle::renderMe()
{
	float speed_mag = speed.mag();
	if(speed_mag <= BOUNCE_C) // ball color change
		glColor3f(0.92, 0.92, 0.95);
	else
	{
		float green = 0.92 - speed_mag * 3;
		float blue = 0.95 - speed_mag * 6;
		glColor3f(0.92, green, blue);
	}
	glBegin(GL_POLYGON);
		for(int i = 0; i < np; ++i)
			glVertex2f(verts[i].x, verts[i].y);
	glEnd();
	
	if(show_vectors) drawVector(pos, speed, 12); // display balls speed vectors
}



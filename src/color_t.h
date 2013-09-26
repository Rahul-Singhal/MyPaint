#ifndef COLOR_T
#define COLOR_T
class color_t{
	private:
	float r_comp;
	float g_comp;
	float b_comp;
	public:
	color_t();
	color_t(float r, float g, float b);
	float getR() const;
	float getG() const;
	float getB() const;
	color_t & operator= (const color_t & c) ;
	bool operator== (const color_t & c) ;
	
};
#endif

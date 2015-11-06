#ifndef _cs1571_as3_City_h
#define _cs1571_as3_City_h

class City {

		protected:
				double x,y;
				int number;
		public:
				City();
				City(double ex, double why, int num);
				~City();

				void display();

				double getx();
				double gety();
				int id();
};		

#endif
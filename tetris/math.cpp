#include <iostream>

int main(){
	double x, y, tx, ty;
	for (int i=0; i<16; ++i){
		tx=(i%4)-1.5;
		ty=(int)((i-tx)/4)-1.5;
		// std::cout<<ty<<std::endl;
		// std::cout<<tx<<" "<<ty<<std::endl;
		x = -ty+1.5; y=tx+1.5;
		printf("%d:%f, %f, %d\n",i, x,y,int(4*y+x));
		// printf("%ld, %ld\n", x,y);
	}
	return 0;
}

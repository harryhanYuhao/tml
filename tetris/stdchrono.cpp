#include<iostream>
#include<chrono>

int main(){
	auto now = std::chrono::system_clock::now();
	auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
	auto epoch = now_ms.time_since_epoch();
	auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
	long duration = value.count();
	std::cout<<duration<<std::endl;
	
	int a = 0;
	while(a < 100000000){
		++a;
	}

	now = std::chrono::system_clock::now();
	now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
	epoch = now_ms.time_since_epoch();
	value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
	duration = value.count();

	std::cout<<duration<<std::endl;
}

#ifndef PERFORMANCE_H_INCLUDED
#define PERFORMANCE_H_INCLUDED


#include <chrono>
#include <iostream>

#define NOW std::chrono::system_clock::now()

#define START_MEASUREMENT(name)                                     \
do{                                                                 \
const char* _description_ = name;                                   \
std::chrono::time_point<std::chrono::system_clock> _start_ = NOW;

#define END_MEASUREMENT()                                                \
std::chrono::duration<double> _elapsed_ = NOW - _start_;                 \
std::cout << _description_ << " : "  <<  _elapsed_.count()<< std::endl;  \
}while(0);


#endif // PERFORMANCE_H_INCLUDED

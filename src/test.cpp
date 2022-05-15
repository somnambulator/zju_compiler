
#include <iostream>
// #include <string>
#include <vector>
#include <memory>

// using namespace std;

class A{
    int i=0;
public:
    virtual void print()=0;
};

class B : public A{
    int j=1;
public:
    void print() override;
};

void B::print(){
    std::cout<<j<<std::endl;
}

int main()
{
    float a = 1.234561423;
    printf("%lf\n", a);
    return 0;
}
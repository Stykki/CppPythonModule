#include <iostream>

using namespace std;
class ASDF
{

    public:
        ASDF();
        void aha();
};

ASDF::ASDF()
{
    cout << "created" << endl;
}
void ASDF::aha()
{
    cout << "aha" << endl;
}

int main(){
    ASDF** test = new ASDF*[20];
    ASDF* &ARR = *test;
    ARR[0].aha();
    return 0;
}


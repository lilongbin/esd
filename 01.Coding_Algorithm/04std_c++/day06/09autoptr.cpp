#include <iostream>
#include <memory>
using namespace std;

class Test {
public:
    Test(string s) {
       str = s;
       cout<<"Test creat\n";
    }
    ~Test() {
        cout<<"Test delete:"<<str<<endl;
    }
    string& getStr() {
        return str;
    }
    void setStr(string s) {
        str = s;
    }
    void print() {
        cout<<str<<endl;
    }
private:
    string str;
};
 
int main() {
    auto_ptr<Test> ptest(new Test("123"));
    ptest->setStr("hello ");
    ptest->print();
    ptest.get()->print();
    ptest->getStr() += "world !";
    (*ptest).print();
    ptest.reset(new Test("123"));
    ptest->print();
    return 0;
}


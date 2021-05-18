#include <iostream>
#include <sstream>
#include <cstdint>
#include <cassert>

class Class
{
private:
    
public:
    // ...
    int32_t *data_ , num;
    Class(size_t num_columns = 0)
    {
        
        data_ = new int32_t [num_columns];
        data_[0] = num_columns;
        num = num_columns;
        std::cout << "Constr " << this->data_[0] << "\n";
    }
    Class(const Class &obj)
    {
        data_ = obj.data_;
        std::cout << "Constr Copy " << this->data_[0] << "\n";
    }
    ~Class()
    {
        std::cout << "num = " << num << " Destr!!\n";
        delete[] data_;
    }
    Class &operator=(const Class obj)
    {
        if (this == &obj) return *this;
        delete[] data_;
        int32_t *tmp = new int32_t[obj.num];
        num = obj.num;
        std::copy(obj.data_, obj.data_ + obj.num, data_);
        return *this;
    }
};

int main()
{
    Class *c, d, *a;
    a = new Class[5];
    c = new Class(4);
    a[0] = Class(6);
    a[1] = Class(7);
    //(*c).data_[0] = 1;
    std::cout << a[0].data_[0] << " 10 \n";
    std::cout << a[1].data_[0] << " 10 \n";
    d = Class(6);
    //a[2] = Class(d);
    //Class f(d);
    std::cout << d.num << " num \n";
    std::cout << d.data_[0] << " 11 \n";
}
#include <iostream>
#include <sstream>
#include <cstdint>
#include <cassert>

class Matrix
{
    class ProxyRow
    {
    private:
    public:
        // ...
        int32_t *data_, num;
        ProxyRow(size_t num_columns)
        {
            data_ = new int32_t[num_columns];
            this->num = num_columns;
        }
        ProxyRow()
        {
            data_ = new int32_t[1];
        }
        int32_t &operator[](size_t j)
        {
            return data_[j];
        }
        ProxyRow &operator=(const ProxyRow obj)
        {
            if (this == &obj)
                return *this;
            delete[] data_;
            int32_t *tmp = new int32_t[obj.num];
            num = obj.num;
            std::copy(obj.data_, obj.data_ + obj.num, data_);
            return *this;
        }
        ProxyRow(const ProxyRow &obj)
        {
            std::cout << "COPY PROXY\n";
            num = obj.num;
            data_ = new int32_t[num];
            std::copy(obj.data_, obj.data_ + num, data_);
        }
        ~ProxyRow()
        {
            delete[] data_;
        }
    };

public:
    // ...
    Matrix(size_t num_rows, size_t num_col)
    {
        this->num_rows = num_rows;
        this->num_columns = num_col;
        rows_ = new ProxyRow[num_rows];
        for (int i = 0; i < num_rows; i++)
        {
            rows_[i] = ProxyRow(i + 1);
        }
    }
    Matrix(Matrix &obj)
    {
        std::cout << "COPY\n";
        num_rows = obj.num_rows;
        num_columns = obj.num_columns;
        rows_ = new ProxyRow[num_rows];
        std::copy(obj.rows_, obj.rows_ + num_rows, rows_);
    }
    ProxyRow &operator[](size_t i)
    {
        return rows_[i];
    }
    Matrix operator+(Matrix m)
    {
        if (num_columns == m.getColumns() && num_rows == m.getRows())
        {
            Matrix ans(num_rows, num_columns);
            for (int i = 0; i < num_rows; i++)
            {
                for (int j = 0; j < num_columns; j++)
                {
                    ans[i][j] = rows_[i][j] + m[i][j];
                }
            }
            return ans;
        }
        return m;
    }
    friend std::ostream &operator<<(std::ostream &out, Matrix m)
    {
        for (int i = 0; i < m.getRows(); i++)
        {
            for (int j = 0; j < m.getColumns(); j++)
            {
                out << m[i][j] << " ";
            }
            out << "\n";
        }
        return out;
    }
    size_t getColumns()
    {
        return num_columns;
    }
    size_t getRows()
    {
        return num_rows;
    }
    ~Matrix()
    {
        
        if (rows_ != nullptr)
        {
            std::cout << "Destr!!\n";
            delete[] rows_;
        }
            
    }

private:
    ProxyRow *rows_;
    size_t num_rows, num_columns;
};

int main()
{
    /*Matrix m(3, 2);
    m[2][0] = 6;
    m[1][0] = 3;
    //printf("%d", m[0][0]);
    std::cout << "HEllo " << m[0][1] << " " << m[2][0] << "\n";*/

    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);

    assert(m.getRows() == 5);
    assert(m.getColumns() == 3);
    std::cout << "HEllo " << m.getRows() << " " << m.getColumns() << "\n";
    m[1][4] = 5; // строка 1, колонка 2
    double x = m[4][1];
    std::cout << "HEllo \n";
    //m *= 3; // умножение на число
    Matrix m1(rows, cols);

    Matrix m2(rows, cols);
    m[1].data_[0] = 3;
    m[2].data_[0] = 2;
    std::cout << m[1][0] << " 10 \n";
    std::cout << m[2][0] << " 11 \n";
    //std::cout << m << " HEllo \n";

    for (size_t i = 0; i < m.getRows(); i++)
    {
        for (size_t j = 0; j < m.getColumns(); j++)
        {
            m1[i][j] = 1;
            m[i][j] = i + j;
            if (i == 1)
            {
            }
            //m[i][j] = 0;
            std::cout << m[i][j] << " ";
        }
        std::cout << "\n";
    }
    m2 = m1 + m;
    std::cout << "HEllo \n";
    std::cout << m << std::endl;
    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;
}
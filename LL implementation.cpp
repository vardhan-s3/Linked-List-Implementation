#include <iostream>
struct Node
{
    int row, col, val;
    Node *next;
};
class Matrix
{
private:
    int rows, cols;
    Node **rows_head;

public:
    Matrix(int rows, int cols)
    {
        this->rows = rows;
        this->cols = cols;
        rows_head = new Node *[rows];
        for (int i = 0; i < rows; i++)
        {
            rows_head[i] = nullptr;
        }
    }
    void insert(int row, int col, int val)
    {
        if (row >= rows || col >= cols)
        {
            std::cerr << "Invalid row or column index." << std::endl;
            return;
        }
        Node *new_node = new Node;
        new_node->row = row;
        new_node->col = col;
        new_node->val = val;
        new_node->next = nullptr;
        if (rows_head[row] == nullptr)
        {
            rows_head[row] = new_node;
        }
        else
        {
            Node *curr = rows_head[row];
            Node *prev = nullptr;
            while (curr != nullptr && curr->col < col)
            {
                prev = curr;
                curr = curr->next;
            }
            if (curr != nullptr && curr->col == col)
            {
                curr->val = val;
                delete new_node;
            }
            else
            {
                if (prev == nullptr)
                {
                    new_node->next = rows_head[row];
                    rows_head[row] = new_node;
                }
                else
                {
                    prev->next = new_node;
                    new_node->next = curr;
                }
            }
        }
    }

    // Print the matrix
    void print()
    {
        for (int i = 0; i < rows; i++)
        {
            Node *curr = rows_head[i];
            int j = 0;
            while (curr != nullptr && j < cols)
            {
                if (curr->col == j)
                {
                    std::cout << curr->val << " ";
                    curr = curr->next;
                }
                else
                {
                    std::cout << "0 ";
                }
                j++;
            }
            while (j < cols)
            {
                std::cout << "0 ";
                j++;
            }
            std::cout << std::endl;
        }
    }

    ~Matrix()
    {
        for (int i = 0; i < rows; i++)
        {
            Node *curr = rows_head[i];
            while (curr != nullptr)
            {
                Node *temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        delete[] rows_head;
    }
};

// Test the implementation
int main()
{
    Matrix mat(3, 3);
    mat.insert(0, 0, 1);
    mat.insert(0, 2, 2);
    mat.insert(1, 1, 3);
    mat.insert(2, 0, 4);
    mat.insert(2, 2, 5);
    mat.print();
    return 0;
}

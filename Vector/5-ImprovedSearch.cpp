#include <iostream>
#include <cassert>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Vector {
private:
	int *arr { nullptr };
	int size { 0 };			// user size
	int capacity { };		// actual size

	void expand_capacity() {
		// Double the actual array size
		cout << "Expanding Capacity!!!\n";
		capacity *= 2;
		cout << "Expand capacity to "
				<< capacity << "\n";
		int *arr2 = new int[capacity] { };
		for (int i = 0; i < size; ++i)
			arr2[i] = arr[i];	// copy data

		swap(arr, arr2);
		delete[] arr2;
		cout << "Capacity Expanded!!!\n";
	}

    void shift_left(int start_idx) {
        for(int i {start_idx}; i < size-1; i++)
            arr[i] = arr[i+1];
        
        return ;
    }

public:
	Vector(int size) :
			size(size) {
		if (size < 0)
			size = 1;
		capacity = size + 10;
		// The actual size array will
		// be bigger than needed
		arr = new int[capacity] { };
	}

	~Vector() {
		delete[] arr;
		arr = nullptr;
	}

	int get_size() {
		return size;
	}

	int get(int idx) {
		assert(0 <= idx && idx < size);
		return arr[idx];
	}

	void set(int idx, int val) {
		assert(0 <= idx && idx < size);
		arr[idx] = val;
	}

	void print() {
		for (int i = 0; i < size; ++i)
			cout << arr[i] << " ";
		cout << "\n";
	}

	int find(int value) {
		for (int i = 0; i < size; ++i)
			if (arr[i] == value)
				return i;
		return -1;	// -1 for NOT found
	}

	int get_front() {
		return arr[0];
	}

	int get_back() {
		return arr[size - 1];
	}

	void push_back(int value) {
		// we can't add any more
		if (size == capacity)
			expand_capacity();
		arr[size++] = value;
	}
	void insert(int idx, int value) {
		assert(0 <= idx && idx < size);

		// we can't add any more
		if (size == capacity)
			expand_capacity();

		// Shift all the data to right first

		for(int p = size-1; p >= idx; --p)
			arr[p+1] = arr[p];

		arr[idx] = value;
		++size;

		// Common mistake to iterate from begin to end
		// the whole array right array will be arr[idx]
		//for (int p = idx; p < size; ++p)
	}

    // ======================================================
    // Right Rotation
    int pop_back() {
        return arr[--size];
    }

    void right_rotate() {
        int value = pop_back();
        insert(0, value);
        return;
    }

    // Left Rotation

    void left_rotation() {
        int front = get_front();

        //shift left
        shift_left(0);

        arr[size-1] = front;
        return ;
    }

    // Right Rotation with Steps
    void right_rotate( int times) {
        stack<int> s;

        for (int i {0}; i < times; i++)
            s.push(pop_back());
        
        // Shift Right
        for (int i {size + times - 1};  i >= (size - 1); i--) {
            arr[i] = arr[i - times];
        }

        for(int i {0}; i < times; i++) {
            arr[i] = s.top(), s.pop();
        }

        size += times;

        return ;
    }

    // Delete Position
    int pop(int idx) {
        int value = arr[idx];
        shift_left(idx);
        --size;
        return value;
    }

    // Improved Search
    int find_transposition(int value) {
        int pos = find(value);
        if (pos <= 0)
            return pos;
        
        swap(arr[pos], arr[pos-1]);
        return pos-1;
    }

};

int main() {
    Vector v (6);

    for (int i {0}; i < 6; i++) {
        v.set(i, i);
    }
    cout << v.get_size() << "\n";
    v.print();

    cout << v.find_transposition(3) << "\n";
    v.print();

    cout << v.find_transposition(3) << "\n";
    v.print();

    cout << v.find_transposition(3) << "\n";
    v.print();

    cout << v.find_transposition(3) << "\n";
    v.print();


    cout << v.get_size() << "\n";
    

	return 0;
}
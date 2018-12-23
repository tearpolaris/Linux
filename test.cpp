#include <iostream>
namespace test1 {
    void print() {
        std::cout << "This is the first print\n";
    }
}
namespace test2 {
	void print() {
		std::cout << "This is the second print\n";
    }
}

template <typename T>
T increase(T para) {
    return (++para);
}

template <typename T>
void printArray(T* para, int n) {
    for (int i=0; i < n; i++) {
        std::cout << para[i] << " ";
    }
    std::cout << "\n";
}
    
int main() {
        int i;
        int arr[4] = {1,2,3,4};
        double brr[5] = {1.1, 1.2, 1.3, 1.4, 1.5};
        //double k,l;
	//test1::print();
	//test2::print();   
       // std::cout << "Input first integer: "
       // std::cin >> i;
//        std::cout << "Input second integer: ";
//        std::cin >> k;
//        j = increase(i);
//        l = increase(k);
//        std::cout << j << std::endl;
//        std::cout << l << std::endl;
	printArray(arr,4);
	printArray(brr,5);
	return 0;
} 

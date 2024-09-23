//编写test case,测试各种函数和类方法
#include"type.h"
#include "zm.h"
#include <algorithm>
#ifndef T
#define T double
#endif

#ifndef Dim
#define Dim 2
#endif

//test case1:测试read_points,读取2维uniform数据
void test_case_1(){
    points_t<T,Dim> raw_data;
    const std::string test_path="../../datasets/uniform_0";//note,最终的相对路径是相对于执行文件来说的
    read_points(raw_data,test_path);
    //输出头5个数据
    std::cout<<"data:[";
    for(int i=0;i<5;i++){
        std::cout<<"[";
        for(int j=0;j<Dim-1;j++)
            std::cout<<raw_data[i][j]<<",";
        std::cout<<raw_data[i][Dim-1]<<"],";
    }
    std::cout<<"]\n";
};

//test_case_2,测试模板化的z_order实现
void test_case_2(){
    const size_t bits = 64; // Number of bits to process

    int xs[2] = {3, 5}; 
    uint64_t z_value = compute_Z_value(xs, Dim,bits);

    // Output __uint128_t value (you can write a function to print it)
    std::cout << "Z-value: " << (unsigned long long)(z_value >> 64) << (unsigned long long)z_value << std::endl;
};
//return mapped_keys count
int write_mapped_keys(std::string fn){
    ZM<T,Dim> zm;
    points_t<T,Dim> raw_data;
    const std::string test_path="../../datasets/uniform_0";//note,最终的相对路径是相对于执行文件来说的
    read_points(raw_data,test_path);
    std::vector<uint64_t> mapped_keys;
    zm.mapping(raw_data,mapped_keys);

    for(int i=0;i<5;i++)
        std::cout<<mapped_keys[i]<<std::endl;

    //write mapped_keys to file
    std::ofstream out(fn,std::ios::out|std::ios::binary);
    size_t count=mapped_keys.size();
    std::cout<<"mapped keys num="<<count<<std::endl;
    for(int i=0;i<count;i++)
        out.write((char*)&mapped_keys[i],sizeof(uint64_t));
    out.close();

    return count;
}
int main(){
    std::cout<<"Begin to Test ZM Disk...\n";
    
    // //test_case_1:
    // std::cout<<"read_points test:\n";
    // test_case_1();
    
    // std::cout<<"test compute_z_value:\n ";
    // test_case_2();
    std::string fn="../lipp/mapped_keys";
    int count=write_mapped_keys(fn);

    // std::ifstream fin(fn, std::ios::binary);
    // uint64_t *keys = new uint64_t[count];
    // fin.read((char*)(keys), sizeof(uint64_t)*count);
    // fin.close();
    // std::sort(keys, keys+count);
    // printf("keys head: \n");
    // for(int i=0;i<5;i++)
    //     std::cout<<keys[i]<<std::endl;
    return 0;
}
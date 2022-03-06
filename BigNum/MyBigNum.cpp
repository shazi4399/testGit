//
//  MyBigNum.cpp
//  testGit
//
//  Created by zhanghao on 2022/3/6.
//


#include  <iostream>
#include <string>
#include <deque>
#include <functional>
#include <iterator>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

class MyBigNum{
private:
    deque<int> v; //用 deque 容器表示大整数
public:
    MyBigNum() {}
    MyBigNum(string strNum){        //通过字符串建立大整数
        copy(strNum.begin(), strNum.end(),back_inserter(v));
        transform(v.begin(), v.end(), v.begin(), bind2nd(minus<int>(),'0'));
    }

    deque<int>::iterator begin(){   //头迭代指针
        return v.begin();
    }
    deque<int>::iterator end(){  //尾迭代指针
        return v.end();
    }
    int size(){                             //容器大小
        return v.size();
    }
    back_insert_iterator<deque<int>> Back_Inserter(){
        return back_inserter(v);
    }
    void push_front(int n){           //前插入元素
        v.push_front(n);
    }

    void push_back(int n ){
        v.push_back(n);
    }

    void adjust(){              // 调整使得容器每位整型元素值 都小于 10；
        int nSize = v.size();
        for(int i = nSize-1; i >=1; i-- ){
            int value = v[i];
            if(value < 10)
                continue;
            v[i] = value%10;
            v[i - 1] += value/10;
        }

        int value = v[0];               //处理最高位
        if(value >= 10){
            v[0] = value % 10;
            value = value / 10;
            while(value > 0){
                v.push_front(value%10);
                value /= 10;
            }
        }
        nSize = v.size();
    }
    MyBigNum Add(MyBigNum & m){
        MyBigNum result;
        int n =size() - m.size();
        if(n >= 0){                 //若大于等于加数位数
            transform(begin()+n, end(), m.begin(), Back_Inserter(),plus<int>());
            for(int i = n -1; i >= 0; i-- ){
                result.push_front(*(begin()+i));
            }
        }else{                      //若小于加数位数
            transform(begin(), end(), m.begin() - n, result.Back_Inserter(),plus<int>());
            for(int i = -n-1;i>=0;i--){
                result.push_front(*(m.begin()+i));
            }

        }
        result.adjust();        //结果调整
        return result;
    }

    MyBigNum Multiply(MyBigNum & m){
        MyBigNum result("0");
        MyBigNum mid;
        for(int i = 0; i < m.size(); ++i){
            mid = *this;
            for(int j = 0; j < i;j++){
                mid.push_back(0);
            }
            transform(mid.begin(), mid.end(), mid.begin(), bind2nd(multiplies<int>(), *(m.begin() + i)));
            result = mid.Add(result);
        }
        return result;
    }
};

int main(){
    cout<<"teset"<<endl;
    MyBigNum m1("123456789");
    MyBigNum m2("999999999");
    MyBigNum result = m1.Add(m2);
    cout<<"123456789+99999999 = ";
    copy(result.begin(),result.end(),ostream_iterator<int>(cout));
    cout<<endl;

    MyBigNum m3("999");
    MyBigNum m4("99999");
    MyBigNum m5 = m3.Multiply(m4);
    cout<<"999 * 99999 = ";
    copy(m5.begin(),m5.end(),ostream_iterator<int>(cout));
    cout<<endl;
    return 0;
}


#include <iostream>
#include "01list.cpp"
using namespace std;
//泛型算法函数（抽象函数）
template<typename T,typename IT>
IT find(IT begin,IT end,T const& key){
	IT it;
	for(it = begin;it != end;++it){
		if(*it == key){
			break;
		}
	}
	return it;
}
//快速排序
template<typename IT>
void sort(IT begin,IT end){
	IT pivot = begin;
	IT last = end;
	--last;//前--比后--的效率高
	for(IT i =begin,j = last;i != j;){
		for(;!(i == pivot || *pivot < *i);++i){	}
		if(i != pivot){
			swap(*i,*pivot);
			pivot = i;
		}
		for(;!(j == pivot || *j < *pivot);--j);
		if(j != pivot){
			swap(*j,*pivot);
			pivot = j;
		}
	}
	IT it = begin;
	++it;
	if(pivot != begin && pivot != it){
		sort(begin,pivot);
	}
	it = pivot;
	++it;
	if(it != end && it != last){
			sort(it,end);
	}
}
template<typename IT,typename CMP>
void sort(IT begin,IT end,CMP cmp){
	IT pivot = begin;
	IT last = end;
	--last;//前--比后--的效率高
	for(IT i =begin,j = last;i != j;){
		for(;!(i == pivot || cmp(*pivot,*i));++i){	}
		if(i != pivot){
			swap(*i,*pivot);
			pivot = i;
		}
		for(;!(j == pivot ||cmp(*j,*pivot));--j);
		if(j != pivot){
			swap(*j,*pivot);
			pivot = j;
		}
	}
	IT it = begin;
	++it;
	if(pivot != begin && pivot != it){
		sort(begin,pivot,cmp);
	}
	it = pivot;
	++it;
	if(it != end && it != last){
			sort(it,end,cmp);
	}
}
class CmpInt{
	public:
	bool operator()(int lhs,int rhs)const{
		return lhs > rhs;
	}
};
int main(void){
	int arr[] = {12,34,23,17,33,49,25};
	int *pn = find(arr,arr+7,34);
	if(pn == arr+7){
		cout << "没找到" << endl;
	}else{
		cout << "找到了:" << *pn <<endl;
	}

	List<int> lst;
	lst.push_back(29);
	lst.push_back(18);
	lst.push_back(42);
	lst.push_back(33);
	lst.push_back(27);
	lst.push_back(64);
	lst.push_back(55);
	List<int>::Iterator it = find(lst.begin(),lst.end(),27);
	if(it == lst.end()){
		cout << "没找到" << endl;
	}else{
		cout << "找到了："<< *it << endl;
	}
	sort(arr,arr+7);
	for(size_t i = 0;i < 7;++i){
		cout << arr[i] << ' '  ;
	}
	cout << endl;
	return 0;
}

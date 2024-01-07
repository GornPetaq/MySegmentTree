#include <bits/stdc++.h>


using namespace std;

template <class T, class AssotiativeOperation>
class SegmentTree {
    public:
vector <T> data;
AssotiativeOperation op;
size_t len;
SegmentTree(vector<T> *input, AssotiativeOperation __op){
    len = input->size();
    op = __op;
    data = vector <T>(input->size()*2-1); // 0->1,2; 1-> 3,4; 2->5,6; i->2i+1,2i+2; (i-1)/2<-i
    copy(input->begin(),input->end(),data.begin()+(input->size()-1));
    for (int i = input->size()-2;i>=0;i--) data[i] = op(data.at(2*i+1),data.at(2*i+2));
}

T accumulateSegment(size_t L, size_t R){ //[L....R) //If L == R this returns new T, so you better check this, can be undefined
    assert((L<=R && R <= len));
    L += len;
    R += len;
    if (R-L == 1) return data[L-1];
    if (R-L == 2) return op(data[L-1],data[L]);
    if (R==L) return *(new T);
    T leftSummand = data[L-1];
    T rightSummand = data[R-2];
    L++;
    R--;
    while (L!=R){
        if (R & 1) {rightSummand = op(data[R-2],rightSummand); cout<<R-2<<" "; R--;}
        if (L & 1) {leftSummand = op(leftSummand,data[L-1]); cout<<L-1<<" "; L++;}
        L/=2;
        R/=2;
    }
    return op(leftSummand,rightSummand);
}

void set(size_t pos,T value){
pos += len;
data[pos - 1] = value;
pos/=2;
while (pos){
data[pos-1] = op(data[2*pos -1],data[2*pos]);
pos/=2;
}
}


};

int addx(int a,int b){return a+b;}

int main (){

vector<int> a(9,3);
auto z = new SegmentTree(&a,addx); //[](int a,int b){return a*b;}
z->set(0,1);
copy(z->data.begin(),z->data.end(),ostream_iterator<int>(cout," "));
cout<<endl;
cout<<z->accumulateSegment(0,9);
//transform_inclusive_scan(a.begin(),)
}
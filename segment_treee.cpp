#include<bits/stdc++.h>
using namespace std;

template<class t>
class SegmentTree{
public:
	SegmentTree(vector<t> data,t dumy,t (*combine)(t obj1,t obj2));
	t query(int l,int r);
	void update(vector<t> &data,t val,int ind);
	void updatehelper(vector<t> &data,int st,int end,int ind,t val,int node);
private:
	t* tree;
	void build(vector<t> data);
	t queryhelper(int l,int r,int st,int end,int node);
	int sizeofsegmenttree;
	int sizeofarray;
	t dummy;
	void buildhelper(vector<t> data,int st,int end,int node);
	t (*combine)(t obj1,t obj2);
};
template<class t>
void SegmentTree<t>:: buildhelper(vector<t> data,int st,int end,int node){
	if(st>end)
		return ;
	if(st==end){
		tree[node]=data[st];
		return ;
	}
	int mid=(st+end)>>1;
	buildhelper(data,st,mid,2*node+1);
	buildhelper(data,mid+1,end,2*node+2);
	tree[node]=combine(tree[2*node+1],tree[2*node+2]);
}
template<class t>
void SegmentTree<t>::build(vector<t> data){
	int st=0;
	int end=sizeofarray-1;
	tree=new t[sizeofsegmenttree];
	buildhelper(data,st,end,0);
}
template<class t>
SegmentTree<t>::SegmentTree(vector<t> data,t dumy,t (*combine)(t obj1,t obj2)){
	dummy=dumy;
	this->combine=combine;
	sizeofarray=data.size();
	sizeofsegmenttree=sizeofarray*4+1;
	build(data);
}
template<class t>
t SegmentTree<t>::queryhelper(int l,int r,int st,int end,int node){
	if(st>end || l>end || r<st)
		return dummy;
	if(st>=l && end<=r)
		return tree[node];
	int mid=(st+end)>>1;
	t ll=queryhelper(l,r,st,mid,2*node+1);
	t rr=queryhelper(l,r,mid+1,end,2*node+2);
	return combine(ll,rr);
}
template<class t>
t SegmentTree<t>::query(int l,int r){
	int st=0;
	int end=sizeofarray-1;
	return queryhelper(l,r,st,end,0);
}
template<class t>
void SegmentTree<t>::updatehelper(vector<t> &data,int st,int end,int index, t val,int node){
	if(st==end){
		tree[node]=val;
		data[index]=val;
	}
	else{
		int mid=(st+end)>>1;
		if(index<=mid && index>=st)
			updatehelper(data,st,mid,index,val,2*node+1);
		else
			updatehelper(data,mid+1,end,index,val,2*node+2);
		tree[node]=combine(tree[2*node+1],tree[2*node+2]);
	}
}
template<class t>
void SegmentTree<t>::update(vector<t> &data,t val,int index){
	updatehelper(data,0,data.size()-1,index,val,0);
}

template<class t>
void print(vector<t> ar){
	for(int i=0;i<ar.size();i++){
		cout<<ar[i]<<" ";
	}
	cout<<endl;
}
template<class t>
t minn(t a,t b){
	return min(a,b);
}
int main(){
	// write your code here
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int n;
	cin>>n;
	vector<float> ar(n);
	for(int i=0;i<n;i++)
		cin>>ar[i];
	SegmentTree<float> myseg(ar,INT_MAX,minn);
	int q;
	cin>>q;
	while(q--){
		int l,r;
		cin>>l>>r;
		cout<<myseg.query(l,r)<<endl;
	}
}
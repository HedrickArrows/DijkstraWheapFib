#include <cstdio>
#include <algorithm>
using namespace std;

#define sIntMin 0x80000000
#define sIntMax 0x7FFFFFFF
#define YES true
#define NO false
#define startVec 10

#define maxPat 0x70000000

#define heapMax 100000
#define log2heapMax 50

template <typename T>
class vec{
public:
	T* tor;
	unsigned int size;
	unsigned int elems;

	vec() : tor(new T[startVec]), size(startVec), elems(0){}

	
	vec(int a) : tor(new T[a]), size(a), elems(0){}

	~vec(){ delete[] tor; }
	
	void add(const T &t){
		if (size == elems) { resize(size * 2); }
		tor[elems] = t;
		elems++;
	}

	void resize(unsigned int n){
		if (n > size){
			T* new_a = new T[n];
			for (unsigned int i = 0; i < elems; i++){
				new_a[i] = tor[i];
			}
			delete[] tor;
			tor = new_a;
			size = n;
		}
	}

	void pop(const T &t){
		int a = 0;
		for (a; a < elems; a++){
			if (tor[a] == t) break;
		}
		for (a; a < elems - 1; a++){
			tor[a] = tor[a + 1];
		}
		elems--;
	}

};


class FibonacciHeap{
public:
	struct node{
		int key;
		node* parent;
		node* child;
		node* left;
		node* right;
		unsigned int degree;
		bool mark;

		int index;

		bool in;
		vec<node*> neighbors;
		vec<int> distances;
		node* previous;
		int k2;
		node* prev2;
		
		
	};
	node* rootlist;
	node* min;
	node* A[log2heapMax];
	int n;

	FibonacciHeap(){
		n = 0;
		min = NULL;
		rootlist = new node;
		rootlist->right = rootlist->left = rootlist;
		rootlist->child = rootlist->parent = NULL;
	}

	~FibonacciHeap(){
		rootlist->right = rootlist->left = rootlist;
		min = NULL;
		n = 0;
		for (int i = 0; i < log2heapMax; i++){
			A[i] = NULL;
		}
		
	}

	static node* newNode(int key){
		node* Node = new node;
		Node->parent = NULL;
		Node->left = Node->right = Node;
		Node->key = key;
		Node->degree = 0;
		Node->mark = false;
		Node->child = new node;
		Node->child->parent = Node;
		Node->child->left = Node->child->right = Node->child;

		Node->previous = NULL;
		return Node;
	}

	bool cmp(int a, int b){ return a < b; }

	int Minimum(){ return min->key; }

	void Insert(node* list, node* x){
		x->right = list->right;
		list->right->left = x;
		list->right = x;
		x->left = list;
	}

	void Remove(node* x){
		x->left->right = x->right;
		x->right->left = x->left;
	}

	void InsertToRoots(node* x){
		Insert(rootlist, x);
		if (!min || cmp(x->key, min->key)){ min = x; }
		n++;
	}

	void Link(node* x, node* y){

		Remove(y);
		Insert(x->child, y);
		y->parent = x;
		x->degree++;
		y->mark = false;
	}

	void Consolidate(){
		int d;
		node* x, *y, *w, *tmp, *next;
		for (int i = 0; i<log2heapMax; i++) A[i] = NULL;
		for (w = rootlist->right; w != rootlist; w = next)
		{
			next = w->right;
			x = w;
			d = x->degree;
			if (d = sIntMax) d = 0;
			while (A[d])
			{
				y = A[d];

				if (cmp(y->key, x->key) || (y->key == x->key && y->index < x->index)){
					tmp = x;
					x = y;
					y = tmp;
				}
				Link(x, y);
				A[d] = NULL;
				d++;
			}
			A[d] = x;
		}
		min = NULL;
		for (w = rootlist->right; w != rootlist; w = w->right) Remove(w);
		for (int i = 0; i<log2heapMax; i++) if (A[i])
		{
			Insert(rootlist, A[i]);
			if (!min || cmp(A[i]->key, min->key) || (min->key == A[i]->key && A[i]->index < min->index)) min = A[i];
		}

	}

	node* ExtractMin(){
		node* z = min, *next, *w;

		if (z)
		{

			for (w = z->child->right; w != z->child; w = next)
			{
				next = w->right;
				w->parent = NULL;
				Remove(w);
				Insert(rootlist, w);
			}
			Remove(z);
			if (z->right == rootlist && z->left == rootlist) min = NULL;
			else
			{
				min = (z->left != rootlist) ? z->left : z->right;
				Consolidate();
			}
			n--;
		}
		return z;
	}

	void DecreaseKey(node* x, int k){
		if (cmp(k, x->key)){
			x->key = k;
			node* y = x->parent;
			if (y && cmp(x->key, y->key)){
				Cut(x, y);
				CascadingCut(y);
			}
			if (cmp(x->key, min->key) || (min->key == x->key && x->index < min->index)){ min = x; }
		}
	}

	void Cut(node* x, node* y){
		Remove(x);
		y->degree--;
		x->parent = NULL;
		Insert(rootlist, x);
		x->mark = false;
	}

	void CascadingCut(node* y){
		node* z = y->parent;
		if (z){
			if (!y->mark){ y->mark = true; }
			else{
				Cut(y, z);
				CascadingCut(z);
			}
		}
	}

	void Delete(node* x){
		DecreaseKey(x, sIntMin);
		ExtractMin();
	}

	void IncreaseKey(node* x, int k){
		if (cmp(x->key, k)){
			Delete(x);
			x->key = k;
			InsertToRoots(x);
		}
	}


};



bool isQfilled(FibonacciHeap::node* Q, int size){
	for (int i = 0; i < size; i++){
		if (!(Q[i].in)){ return YES; }
	}
	return NO;
}


int dijkstra(FibonacciHeap::node* nodes, int x){
	FibonacciHeap* heap = new FibonacciHeap;

	for (int i = 0; i < x; i++){
		(nodes[i]).key = (nodes[i]).k2 =  maxPat;
		if (i == 0){ (nodes[i]).key = 0; }
		nodes[i].in = NO;
		
		(*heap).InsertToRoots(&nodes[i]);
	}
	
	FibonacciHeap::node* mn, *tmp;
	vec<FibonacciHeap::node*>* nei; vec<int>* dst;
	int help, aaa;
	while (isQfilled(nodes,x)){

		mn = (*heap).min;

		mn->in = YES;
		nei = &mn->neighbors;
		dst = &mn->distances;
		help = nei->elems;

		for (int re = 0; re < help; re++){
			tmp = nei->tor[re];
				aaa = mn->key + dst->tor[re];
				if (aaa < tmp->key){
					tmp->k2 = tmp->key;
					tmp->prev2 = tmp->previous;
					heap->DecreaseKey(tmp, aaa);
					tmp->previous = mn;
				}
				else if (aaa < tmp->k2){
					tmp->k2 = aaa;
					tmp->prev2 = mn;
				}
				if (mn->k2 + dst->tor[re] < tmp->k2){
					tmp->k2 = mn->k2 + dst->tor[re];
					tmp->prev2 = mn;
				}
		}
		(*heap).ExtractMin();
	}
	delete heap;
	
	return nodes[x-1].key;
}

int main(){
	int n, m, v, u, w, e[2], f;
	scanf("%d %d", &n, &m);
	FibonacciHeap::node* nodes = new FibonacciHeap::node[n], *temp;
	for (int q = 0; q < n; q++){
		temp = FibonacciHeap::newNode(0);
		nodes[q] = *temp;
		(nodes[q]).index = q;
	}
	for (int o = 0; o < m; o++){
		scanf("%d %d %d", &v, &u, &w);
		nodes[v].neighbors.add(&nodes[u]);
		nodes[v].distances.add(w);

		nodes[u].neighbors.add(&nodes[v]);
		nodes[u].distances.add(w);
		
	}
	dijkstra(nodes, n);
	e[0] = nodes[n - 1].key; e[1] = nodes[n - 1].k2;

	if (e[0] >= maxPat || e[1] >= maxPat)
		printf("#");
	else
	printf("%d %d", e[0], e[1]);

	return 0;
}
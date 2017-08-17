#ifndef LIST_H_
#define LIST_H_

typedef int Rank;  //��
#define ListNodePosi(T) ListNode<T> *  //�б�ڵ�λ��

template <typename T>
struct ListNode  //�б�ڵ�ģ���ࣨ��˫��������ʽʵ�֣�
{
// ��Ա
	T data;  //��ֵ
	ListNodePosi(T) pred;  //ǰ��
	ListNodePosi(T) succ;  //���

// ���캯��
	ListNode() {}  //���header��trailer�Ĺ���
	ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr)
		: data(e), pred(p), succ(s) {}  //Ĭ�Ϲ�����

// �����ӿ�
	ListNodePosi(T) insertAsPred(T const& e);  //������ǰ�ڵ�֮ǰ�����½ڵ�
	ListNodePosi(T) insertAsSucc(T const& e);  //���浱ǰ�ڵ�֮������½ڵ�
};


template <typename T>
class List  //�б�ģ����
{
private:
	int _size;  //��ģ
	ListNodePosi(T) header;  //ͷ�ڱ�
	ListNodePosi(T) trailer;  //β�ڱ�

protected:
	void init();  //�б���ʱ�ĳ�ʼ��

	int clear();  //������нڵ�

	void copyNodes(ListNodePosi(T) p, int n);  //�����б�����λ��p���n��

	void merge(ListNodePosi(T) p, int n, List<T>& L, ListNodePosi(T) q, int m);  //�鲢

	void mergeSort(ListNodePosi(T) p, int n);  //�Դ�p��ʼ������n���ڵ�鲢����

	void selectionSort(ListNodePosi(T) p, int n);  //�Դ�p��ʼ������n���ڵ�ѡ������

	void insertionSort(ListNodePosi(T) p, int n);  //�Դ�p��ʼ������n���ڵ��������

public:
	// ���캯��
	List() //Ĭ�Ϲ��캯��
	{
		init();
	}

	List(List<T> const& L)  //���帴���б�L
	{
		copyNodes(L.first(), L.size());
	}

	List(List<T> const& L, Rank r, int n);  //�����б�L���Ե�r�����n��

	List(ListNodePosi(T) p, int n)  //�����б�����λ��p���n��
	{
		copyNodes(p, n);
	}

	// ��������
	~List();  //�ͷţ�����ͷ��β�ڱ����ڵģ����нڵ�

// ֻ�����ʽӿ�
	Rank size() const  //��ģ
	{
		return _size;
	}

	bool empty() const  //�п�
	{
		return _size <= 0;
	}

	T& operator[] (Rank r) const;  //�����[]���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ�

	ListNodePosi(T) first() const  //�׽ڵ�λ��
	{
		return header->succ;
	}

	ListNodePosi(T) last() const  //ĩ�ڵ�λ��
	{
		return trailer->pred;
	}

	bool valid(ListNodePosi(T) p)  //�ж�λ��p�Ƿ����Ϸ�
	{
		return p && (trailer != p) && (header != p);
	}  //��ͷ��β�ڵ��ͬ��nullptr

	int disordered() const;  //�ж��б��Ƿ�������

	ListNodePosi(T) find(T const& e) const  //�����б����
	{
		return find(e, _size, trailer);
	}

	ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const;  //�����������

	ListNodePosi(T) search(T const& e) const  //�����б����
	{
		return search(e, _size, trailer);
	}
	ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const;  //�����������

	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);  //��p����n-1�������ѡ�������

	ListNodePosi(T) selectMax()
	{
		return selectMax(header->succ, _size);
	}  //���������

// ��д���ʽӿ�
	ListNodePosi(T) insertAsFirst(T const& e);  //��e�����׽ڵ����

	ListNodePosi(T) insertAsLast(T const& e);  //��e����ĩ�ڵ����

	ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e);  //��e����p�ĺ�̲��루After��

	ListNodePosi(T) insertB(ListNodePosi(T) p, T const& e);  //��e����p��ǰ�����루Before��

	T remove(ListNodePosi(T) p);  //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�

	void merge(List<T>& L)   //ȫ�б�鲢
	{
		merge(header->succ, size(), L, L.header->succ, L.size());
	}

	void sort(ListNodePosi(T) p, int n);  //�б���������

	void sort()   //�б���������
	{
		sort(first(), _size);
	}

	int deduplicate();  //����ȥ��

	int uniquify();  //����ȥ��

	void reverse();  //ǰ����

	// ����
	void traverse(void(*visit) (T&));  //����������ʵʩvisit����������ָ�룬ֻ����ֲ����޸ģ�

	template <typename VST>  //������
	void traverse(VST& visit);  //����������ʵʩvisit�������������󣬿�ȫ�����޸ģ�

};  //List





// �ڵ�ģ��ṹʵ��
template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e)  //��e������ǰ�ڵ�֮ǰ�����ڵ�ǰ�ڵ������б������ڱ�ͷ�ڵ�header��
{
	ListNodePosi(T) x = new ListNode(e, pred, this);  //�����½ڵ�
	pred->succ = x;
	pred = x;  //������������
	return x;  //�����½ڵ��λ��
}


template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e)  //��e���浱ǰ�ڵ�֮������ڵ�ǰ�ڵ������б������ڱ�β�ڵ�trailer��
{
	ListNodePosi(T) x = new ListNode(e, this, succ);  //�����½ڵ�
	succ->pred = x;
	succ = x;  //������������
	return x;  //�����½ڵ��λ��
}




// �б�ģ����ʵ��
template <typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n)  //�б��ڲ������������б�����λ��p���n��
{  //p�Ϸ�����������n-1�����̽ڵ�
	init();  //����ͷ��β�ڱ��ڵ㲢����ʼ��
	while (n--)
	{
		insertAsLast(p->data);  //������p��n��������Ϊĩ�ڵ����
		p = p->succ;
	}
}


template<typename T>
void List<T>::merge(ListNodePosi(T) p, int n, List<T>& L, ListNodePosi(T) q, int m)  //�������б�[q,q+m)����[p,p+n),�õ�[p,p+n+m)
{
	while (m > 0)  
	{
		if (p->data > q->data)
		{
			q = q->succ;
			insertB(p, L.remove(q->pred));
			m--;
		}
		else
		{
			if (n > 1)
			{
				p = p->succ;
				n--;
			}
			else
			{
				while (m--)
				{   
					q = q->succ;
					insertA(p, L.remove(q->pred));
					p = p->succ;				
				}
			}
		}
	}
}


template<typename T>
void List<T>::mergeSort(ListNodePosi(T) p, int n)
{
	ListNodePosi(T) q = p;
	for (int m = 0; m < n / 2; m++)
		q = q->succ;
	mergeSort(p, n / 2);
	mergeSort(q, n - n / 2);
	merge(p, n / 2, *this, q, n - n / 2);
}


template <typename T>
void List<T>::init()  //�б��ʼ�����ڴ����б����ʱͳһ����
{
	header = new ListNode<T>;  //����ͷ�ڱ��ڵ�
	trailer = new ListNode<T>;  //����β�ڱ��ڵ�
	header->succ = trailer; header->pred = nullptr;
	trailer->pred = header; trailer->succ = nullptr;
	_size = 0;  //��¼��ģ
}


template <typename T>
List<T>::List(List<T> const& L, Rank r, int n)
{
	ListNodePosi(T) p = L.first();  //���׽ڵ����
	while (0 < r--)
		p = p->succ;
	copyNodes(p, n);
}


template <typename T>
List<T>::~List()
{
	clear();
	delete header;
	delete trailer;
}


template <typename T>
T& List<T>::operator[] (Rank r) const  //�����±����������ͨ����ֱ�ӷ����б�ڵ㣨���Ӷ�O(n)��
{
	ListNodePosi(T) p = first();  //���׽ڵ����
	while (0 < r--)
		p = p->succ;  //˳����r���ڵ㼴��
	return p->data;  //Ŀ��ڵ㣬������������Ԫ��
}


template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const& e)  //e�����׽ڵ����
{
	_size++;
	return header->insertAsSucc(e);
}


template <typename T>
ListNodePosi(T) List<T>::insertAsLast(T const& e)  //e����ĩ�ڵ����
{
	_size++;
	return trailer->insertAsPred(e);
}


template <typename T>
ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p, T const& e)  //e����p�ĺ�̲��루After��
{
	_size++;
	return p->insertAsSucc(e);
}


template <typename T>
ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p, T const& e)  //e����p��ǰ�����루Before��
{
	_size++;
	return p->insertAsPred(e);
}


template <typename T>
T List<T>::remove(ListNodePosi(T) p)  //ɾ���Ϸ��ڵ�p����������ֵ�����Ӷ� O(1)
{
	T e = p->data;  //���ݴ�ɾ���ڵ����ֵ���ٶ�T���Ϳ�ֱ�Ӹ�ֵ��
	p->pred->succ = p->succ;  //���
	p->succ->pred = p->pred;  //ǰ��
	delete p;  //�ͷŽڵ�
	_size--;  //���¹�ģ
	return e;  //���ر��ݵ���ֵ
}


template<typename T>
void List<T>::sort(ListNodePosi(T) p, int n)
{
	mergeSort(p, n);
}


template <typename T>  //����б�
int List<T>::clear()
{
	int oldSize = _size;
	while (0 < _size)
		remove(header->succ); //����ɾ���׽ڵ㣬ֱ���б���
	return oldSize;
}



template <typename T>
int List<T>::deduplicate()  //�޳������б��е��ظ��ڵ�
{
	if (_size < 2)
		return 0;  //ƽ���б���Ȼ���ظ�
	int oldSize = _size;  //��¼ԭ��ģ
	ListNodePosi(T) p = header;  //p���׽ڵ㿪ʼ
	Rank r = 0;
	while ((p = p->succ) != trailer)  //����ֱ��ĩ�ڵ�
	{
		ListNodePosi(T) q = find(p->data, r, p);  //��p��r�����棩ǰ���в�����ͬ��
		q ? remove(q) : r++;  //�����ڣ���ɾ��֮�������ȼ�һ
	}
	//assert: ѭ�������е�����ʱ�̣�p������ǰ��������ͬ
	return oldSize - _size;  //�б��ģ�仯��������ɾ��Ԫ������
}


template <typename T>
int List<T>::uniquify()              //�޳������б��е��ظ��ڵ�
{
	if (_size < 2)
		return 0;                    //ƽ���б���Ȼ���ظ�
	int oldSize = _size;             //��¼ԭ��ģ
	ListNodePosi(T) p = first();
	ListNodePosi(T) q;               //pΪ��������㣬qΪ����
	while (trailer != (q = p->succ)) //����������ڵĽڵ��(p, q)
	{
		if (p->data != q->data)
			p = q;                   //�����죬��ת����һ����
		else
			remove(q);               //����ɾ������
	}
	return oldSize - _size;          //�б��ģ�仯��������ɾ��Ԫ������
}


template <typename T>
void List<T>::reverse()
{ //ǰ����
	if (_size < 2) return; //ƽ�����
	for (ListNodePosi(T) p = header; p; p = p->pred) //��ǰ�������
		swap(p->pred, p->succ); //�������ڵ�mǰ�������ָ��
	swap(header, trailer); //ͷ��β�ڵ㻥��
}


template <typename T>
int List<T>::disordered() const
{
	int n = 0;
	ListNodePosi(T) p = header;
	while (p != trailer)
		if (p > p->succ)
		{
			n++;
			p = p->succ;
		}
	return n;
}


//�������б��ڽڵ�p��������trailer����n�����棩ǰ���У��ҵ�����e�������
template<typename T>
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const
{
	while (0 < n--)  //��0 <= n <= rank(p) < _size������p�������n��ǰ����������������ȶԣ�ֱ�����л�ΧԽ��
	{
		p = p->pred;
		if (e == p->data) return p;
	}
	return nullptr;  //pԽ����߽���ζ�������ڲ���e������ʧ�ܣ����ؿ�ָ��
}


template <typename T> //�������б��ڽڵ�p��������trailer����n�����棩ǰ���У��ҵ�������e�������
ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const
{
	// assert: 0 <= n <= rank(p) < _size
	do
	{
		p = p->pred; n--;  //��������

	} while ((-1 < n) && (e < p->data)); //����Ƚϣ�ֱ�����л�Խ��
	return p; //���ز�����ֹ��λ��
} //ʧ��ʱ������������߽��ǰ����������header��


template<typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n)
{
	ListNodePosi(T) max = p;
	while (--n)  //ִ��n-1��
	{
		p = p->succ;
		if (p->data > max->data)
			max->p;
	}
	return max;
}


template <typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n)   //�б��ѡ�������㷨������ʼ��λ��p��n��Ԫ������
{
	//valid(p) && rank(p) + n <= size
	ListNodePosi(T) head = p->pred;
	ListNodePosi(T) tail = p;
	for (int i = 0; i < n; i++)
		tail = tail->succ;                               //����������Ϊ(head, tail)
	while (1 < n)                                        //�����ٻ�ʣ�����ڵ�֮ǰ���ڴ�����������
	{
		ListNodePosi(T) max = selectMax(head->succ, n);  //�ҳ�[head->succ, head->succ + n)������ߣ�����ʱ�������ȣ�
		insertB(tail, remove(max));                      //����������������ĩβ����Ϊ���������µ���Ԫ�أ�
		tail = tail->pred;
		n--;
	}
}


template <typename T> //�б�Ĳ��������㷨������ʼ��λ��p��n��Ԫ������
void List<T>::insertionSort(ListNodePosi(T) p, int n)
{ //valid(p) && rank(p) + n <= size
	for (int r = 0; r < n; r++)
	{ //��һΪ���ڵ�
		insertA(search(p->data, r, p), p->data); //�����ʵ���λ�ò�����
		p = p->succ;
		remove(p->pred); //ת����һ�ڵ�
	}
}


template <typename T> void List<T>::traverse(void(*visit) (T&)) //��������ָ����Ʊ���
{
	for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ) visit(p->data);
}

template <typename T> template <typename VST> //Ԫ�����͡�������
void List<T>::traverse(VST& visit) //��������������Ʊ���
{
	for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ) visit(p->data);
}
#endif  

#include "List.h"


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


//template<typename T>
//void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m)  //�������б�[q,q+m)����[p,p+n),�õ�[p,p+n+m)
//{
//	while (m > 0)  
//	{
//		if (p->data > q->data)
//		{
//			q = q->succ;
//			insertB(p, L.remove(q->pred));
//			m--;
//		}
//		else
//		{
//			if (n > 1)
//			{
//				p = p->succ;
//				n--;
//			}
//			else
//			{
//				while (m--)
//				{
//					insertA(p, q);
//					p = p->succ;
//					q = q->succ;
//				}
//			}
//		}
//	}
//
//}
//
//template<typename T>
//void List<T>::mergeSort(ListNodePosi(T)& p, int n)
//{
//	ListNodePosi(T) q = p;
//	for (int m = 0; m < n / 2; m++)
//		q = q->succ;
//	mergeSort(p, n / 2);
//	mergeSort(q, n - n / 2);
//	merge(p, n / 2, this, q, n - n / 2);
//}



template <typename T> //�б�Ĺ鲢�����㷨������ʼ��λ��p��n��Ԫ������
void List<T>::mergeSort(ListNodePosi(T) & p, int n) { //valid(p) && rank(p) + n <= size
	if (n < 2) return; //��������Χ���㹻С����ֱ�ӷ��أ�����...
	int m = n >> 1; //���е�Ϊ��
	ListNodePosi(T) q = p; for (int i = 0; i < m; i++) q = q->succ; //�����б�
	mergeSort(p, m); mergeSort(q, n - m); //��ǰ�������б�ֱ�����
	merge(p, m, *this, q, n - m); //�鲢

} //ע�⣺�����p��Ȼָ��鲢������ģ��£����


template <typename T> //�����б�Ĺ鲢����ǰ�б�����p���n��Ԫ�أ����б�L����q���m��Ԫ�ع鲢
void List<T>::merge(ListNodePosi(T) & p, int n, List<T>& L, ListNodePosi(T) q, int m) {
	// assert:  this.valid(p) && rank(p) + n <= size && this.sorted(p, n)
		//          L.valid(q) && rank(q) + m <= L._size && L.sorted(q, m)
		// ע�⣺�ڹ鲢����֮��ĳ��ϣ��п��� this == L && rank(p) + n = rank(q)
	ListNodePosi(T) pp = p->pred; //����ǰ����������header�����Ա㷵��ǰ ...
	while (0 < m) //��q��δ�Ƴ�����֮ǰ
		if ((0 < n) && (p->data <= q->data)) //��p������������v(p) <= v(q)����
		{
			if (q == (p = p->succ)) break; n--;
		} //p����ϲ����б����滻Ϊ��ֱ�Ӻ��
		else //��p�ѳ����ҽ��v(q) < v(p)����
		{
			insertB(p, L.remove((q = q->succ)->pred)); m--;
		} //��qת����p֮ǰ
	p = pp->succ; //ȷ���鲢������ģ��£����

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
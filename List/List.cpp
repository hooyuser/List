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


template <typename T>  //�������б��ڽڵ�p��������trailer����n�����棩ǰ���У��ҵ�����e�������
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const
{
	while (0 < n--)  //��0 <= n <= rank(p) < _size������p�������n��ǰ����������������ȶԣ�ֱ�����л�ΧԽ��
	{
		p = p->pred;
		if (e == p->data) return p;
	}
	return nullptr;  //pԽ����߽���ζ�������ڲ���e������ʧ�ܣ����ؿ�ָ��
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
T List<T>::remove(ListNodePosi(T) p)  //ɾ���Ϸ��ڵ�p����������ֵ
{
	T e = p->data;  //���ݴ�ɾ���ڵ����ֵ���ٶ�T���Ϳ�ֱ�Ӹ�ֵ��
	p->pred->succ = p->succ;  //���
	p->succ->pred = p->pred;  //ǰ��
	delete p;  //�ͷŽڵ�
	_size--;  //���¹�ģ
	return e;  //���ر��ݵ���ֵ
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
	ListNodePosi(T) p = header;
	Rank r = 0;  //p���׽ڵ㿪ʼ
	while (trailer != (p = p->succ))  //����ֱ��ĩ�ڵ�
	{
		ListNodePosi(T) q = find(p->data, r, p);  //��p��r�����棩ǰ���в�����ͬ��
		q ? remove(q) : r++;  //����ȷ���ڣ���ɾ��֮�������ȼ�һ
	}  //assert: ѭ�������е�����ʱ�̣�p������ǰ��������ͬ
	return oldSize - _size;  //�б��ģ�仯��������ɾ��Ԫ������
}


template <typename T>
int List<T>::uniquify()  //�޳������б��е��ظ��ڵ�
{
	if (_size < 2) return 0;  //ƽ���б���Ȼ���ظ�
	int oldSize = _size;  //��¼ԭ��ģ
	ListNodePosi(T) p = first();
	ListNodePosi(T) q;  //pΪ��������㣬qΪ����
	while (trailer != (q = p->succ)) //����������ڵĽڵ��(p, q)
	{
		if (p->data != q->data)
			p = q;  //�����죬��ת����һ����
		else remove(q);  //������ͬ����ɾ������
	}
	return oldSize - _size;  //�б��ģ�仯��������ɾ��Ԫ������

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


template <typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n) //�б��ѡ�������㷨������ʼ��λ��p��n��Ԫ������
{ //valid(p) && rank(p) + n <= size
	ListNodePosi(T) head = p->pred;
	ListNodePosi(T) tail = p;
	for (int i = 0; i < n; i++)
		tail = tail->succ; //����������Ϊ(head, tail)
	while (1 < n)
	{ //�����ٻ�ʣ�����ڵ�֮ǰ���ڴ�����������
		ListNodePosi(T) max = selectMax(head->succ, n); //�ҳ�����ߣ�����ʱ�������ȣ�
		insertB(tail, remove(max)); //����������������ĩβ����Ϊ���������µ���Ԫ�أ�
		tail = tail->pred; n--;
	}
}


template <typename T>
void List<T>::traverse(void(*visit) (T&))  //��������ָ����Ʊ���
{
	for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
		visit(p->data);
}


template <typename T>  //Ԫ������
template <typename VST>  //������
void List<T>::traverse(VST& visit)  //��������������Ʊ���
{
	for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
		visit(p->data);
}
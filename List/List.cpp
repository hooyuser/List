#include "List.h"

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e) //��e������ǰ�ڵ�֮ǰ�����ڵ�ǰ�ڵ������б������ڱ�ͷ�ڵ�header��
{
	ListNodePosi(T) x = new ListNode(e, pred, this); //�����½ڵ�
	pred->succ = x;
	pred = x; //������������
	return x; //�����½ڵ��λ��
}


template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e) //��e���浱ǰ�ڵ�֮������ڵ�ǰ�ڵ������б������ڱ�β�ڵ�trailer��
{
	ListNodePosi(T) x = new ListNode(e, this, succ); //�����½ڵ�
	succ->pred = x;
	succ = x; //������������
	return x; //�����½ڵ��λ��
}


template <typename T>
void List<T>::init() //�б��ʼ�����ڴ����б����ʱͳһ����
{
	header = new ListNode<T>; //����ͷ�ڱ��ڵ�
	trailer = new ListNode<T>; //����β�ڱ��ڵ�
	header->succ = trailer; header->pred = nullptr;
	trailer->pred = header; trailer->succ = nullptr;
	_size = 0; //��¼��ģ
}


template <typename T>
T& List<T>::operator[] (Rank r) const //�����±����������ͨ����ֱ�ӷ����б�ڵ㣨���Ӷ�O(n)��
{
	ListNodePosi(T) p = first(); //���׽ڵ����
	while (0 < r--)
		p = p->succ; //˳����r���ڵ㼴��
	return p->data; //Ŀ��ڵ㣬������������Ԫ��
}

template <typename T> //�������б��ڽڵ�p��������trailer����n�����棩ǰ���У��ҵ�����e�������
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const
{
	while (0 < n--) //��0 <= n <= rank(p) < _size������p�������n��ǰ����������������ȶԣ�ֱ�����л�ΧԽ��
	{
		p = p->pred;
		if (e == p->data) return p; 
	}	 
	return nullptr; //pԽ����߽���ζ�������ڲ���e������ʧ�ܣ����ؿ�ָ��
} 
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

	void copyNodes(ListNodePosi(T), int);  //�����б�����λ��p���n��

	void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);  //�鲢

	void mergeSort(ListNodePosi(T)&, int);  //�Դ�p��ʼ������n���ڵ�鲢����

	void selectionSort(ListNodePosi(T), int);  //�Դ�p��ʼ������n���ڵ�ѡ������

	void insertionSort(ListNodePosi(T), int);  //�Դ�p��ʼ������n���ڵ��������

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
	}  //��ͷ��β�ڵ��ͬ��NULL

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

	ListNodePosi(T) selectMax() { return selectMax(header->succ, _size); }  //���������

// ��д���ʽӿ�
	ListNodePosi(T) insertAsFirst(T const& e);  //��e�����׽ڵ����

	ListNodePosi(T) insertAsLast(T const& e);  //��e����ĩ�ڵ����

	ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e);  //��e����p�ĺ�̲��루After��

	ListNodePosi(T) insertB(ListNodePosi(T) p, T const& e);  //��e����p��ǰ�����루Before��

	T remove(ListNodePosi(T) p);  //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�

	void merge(List<T>& L) { merge(first(), size, L, L.first(), L._size); }  //ȫ�б�鲢

	void sort(ListNodePosi(T) p, int n);  //�б���������

	void sort() { sort(first(), _size); }  //�б���������

	int deduplicate();  //����ȥ��

	int uniquify();  //����ȥ��

	void reverse();  //ǰ���ã�ϰ�⣩

// ����
	void traverse(void(*) (T&));  //����������ʵʩvisit����������ָ�룬ֻ����ֲ����޸ģ�

	template <typename VST>  //������

	void traverse(VST&);  //����������ʵʩvisit�������������󣬿�ȫ�����޸ģ�

};  //List

#endif  

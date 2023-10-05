#include <iostream>
#include <vector>
#include <random>

class MyCircularQueue {
    private:

	std::vector<int> m_v;
	unsigned int m_head, m_tail, m_size, m_capacity;
	
    public:

	MyCircularQueue(unsigned int k): m_capacity{ k }, m_head{}, m_tail{}, m_size{}
	{
	    m_v.reserve(k);
	}

	bool enQueue(int value) {
	    if(m_size < m_capacity)
	    {
		if(m_size)
		{
		    m_tail = (m_tail + 1) % m_capacity;
		    m_v[m_tail] = value;
		}
		else
		{
		    m_v[m_tail] = value;
		}
		++m_size;
		return true;
	    }
	    else
	    {
		return false;
	    }
	}

	bool deQueue() {
	    if(m_size > 0)
	    {
		if(m_head != m_tail)
		    m_head = (m_head + 1) % m_capacity;
		--m_size;
		return true;
	    }
	    else
	    {
		return false;
	    }
	}

	int Front() const {
	    return (m_size > 0)? m_v[m_head]: -1;
	}

	int Rear() const {
	    return (m_size > 0)? m_v[m_tail]: -1;
	}

	bool isEmpty() const {
	    return !m_size;
	}

	bool isFull() const {
	    return (m_size == m_capacity);
	}

	void print() const
	{
	    if(m_size)
	    {
		auto i{ m_head };
		while(1)
		{
		    std::cout << m_v[i] << ' ';
		    if(i == m_tail)
			break;
		    i = (i + 1) % m_capacity;
		}
	    }
	    std::cout << '\n';
	}
};

int main()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,1);

    MyCircularQueue q{ 5 };

    for(int i{}; i < 100; ++i)
    {
	if(dist6(rng))
	{
	    std::cout << "Enque " << i << ": ";
	    q.enQueue(i);
	    q.print();
	}
	else
	{
	    std::cout << "Deque: ";
	    q.deQueue();
	    q.print();
	}
    }
}


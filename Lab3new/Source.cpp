#include "Header.h"

struct City {
private:
	int count_of_citizens;
	string name;

public:
	City(const int c = 0, const string n = "") :count_of_citizens(c), name(n) {}
	City(const City& c)
	{
		this->count_of_citizens = c.count_of_citizens;
		this->name = c.name;
	}
	friend bool operator==(const City& lhs, const City& rhs)
	{
		return (lhs.name == rhs.name);
	}
	friend bool operator!=(const City& lhs, const City& rhs)
	{
		return !operator==(lhs, rhs);
	}
	friend std::ostream& operator<<(std::ostream& out, City& c)
	{
		cout << c.name;
		return out;
	}
};

struct Road {
private:
	bool federal;
	bool toll;
	int length;
public:
	Road(bool f = false, bool t = false, int l = 0) : federal(f), toll(t), length(l) {}
	int getLength() {
		return this->length;
	}
	operator double()
	{
		return length;
	}
	Road operator=(const int& v)
	{
		this->federal = false;
		this->toll = false;
		this->length = v;
		return *this;
	}
	Road(const Road& v)
	{
		this->federal = v.federal;
		this->toll = v.toll;
		this->length = v.length;
	}
	friend Road operator+(const Road& lhs, const Road& rhs)
	{
		return Road(lhs.federal || rhs.federal, lhs.toll || rhs.toll, lhs.length + rhs.length);

	}
	friend std::ostream& operator<<(std::ostream& out, Road& r)
	{
		cout << r.length << " (is toll: " << r.toll << ", is federal: " << r.federal << ")";
		return out;
	}
};


int main()
{
	Graph<City, Road> g;
	City Samara(1000000, "Samara"), Togliatti(700000, "Togliatti"), Zhigulevsk(40000, "Zhigulevsk"), Syzran(100000, "Syzran"), Kurumoch(700, "Kurumoch"), Moscow(10000000, "Moscow");
	Road SaTo(true, false, 70), ToZh(true, false, -15), ToSy(true, false, 100),
		ToKu(true, false, 30), KuSa(false, true, 30), ZhSy(true, false, 80),
		SaMo(true, false, 1000), ToMo(true, false, 900), SyMo(true, false, 800);
	g.addVertex(Samara);
	g.addVertex(Togliatti);
	g.addVertex(Zhigulevsk);
	g.addVertex(Syzran);
	g.addVertex(Kurumoch);
	g.addVertex(Moscow);
	g.addEdge(Samara, Togliatti, SaTo);
	g.addEdge(Togliatti, Zhigulevsk, ToZh);
	g.addEdge(Togliatti, Syzran, ToSy);
	g.addEdge(Togliatti, Kurumoch, ToKu);
	g.addEdge(Kurumoch, Samara, KuSa);
	g.addEdge(Togliatti, Samara, SaTo);
	g.addEdge(Zhigulevsk, Syzran, ZhSy);
	g.addEdge(Samara, Moscow, SaMo);
	g.addEdge(Togliatti, Moscow, ToMo);
	//g.addEdge(Syzran, Moscow, SyMo);
	//g.print();
	g.deep_search();
	g.dijkstra(Samara, Togliatti);
	return 0;
}
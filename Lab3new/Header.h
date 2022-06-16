#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <float.h>

using namespace std;

template<typename TVertex, typename TEdge>
class Graph
{
private:
	struct for_deep {
		int color = 0;
		TVertex prev;
		int t_open = 0;
		int t_close = 0;
	};
	struct destination {
		int id;
		TVertex des;
		TEdge edge;
	};
	struct Vertex {
		int id;
		TVertex source;
		vector<destination> dest;
		for_deep inf;
	};
	vector<Vertex> table;
public:
	int ret_index(TVertex f_ver)
	{
		for (int i = 0; i < table.size(); i++)
		{
			if (table[i].source == f_ver) return table[i].id;
		}
		return -1;
	}

	void addVertex(TVertex tmp_source)
	{
		Vertex struct_to_add;
		struct_to_add.id = table.size();
		struct_to_add.source = tmp_source;
		table.push_back(struct_to_add);
	}

	void addEdge(TVertex source, TVertex des, TEdge ed)
	{
		if (ed.getLength() > 0) {
			int tmp_id = ret_index(source);
			int temp_id = ret_index(des);
			destination temp;
			temp.des = des;
			temp.edge = ed;
			temp.id = temp_id;
			table[tmp_id].dest.push_back(temp);
		}
	}

	void delVertex(TVertex sourc)
	{
		int ind = ret_index(sourc);
		for (int i = 0; i < ind; i++)
		{
			for (int j = 0; j < table[i].dest.size(); j++)
			{
				if (table[i].dest[j].des == sourc)
				{
					for (int k = j; k < table[i].dest.size() - 1; k++)
					{
						table[i].dest[k].des = table[i].dest[k + 1].des;
					}
					table[i].dest.pop_back();
				}
			}
		}
		for (int i = ind + 1; i < table.size(); i++)
		{
			for (int j = 0; j < table[i].dest.size(); j++)
			{
				if (table[i].dest[j].des == sourc)
				{
					for (int k = j; k < table[i].dest.size() - 1; k++)
					{
						table[i].dest[k].des = table[i].dest[k + 1].des;
					}
					table[i].dest.pop_back();
				}
			}
		}
		for (int i = ind; i < table.size() - 1; i++)
		{
			table[i] = table[i + 1];
			table[i].id--;
		}
		table.pop_back();
	}

	void delEdge(TVertex source, TVertex des)
	{
		int ind_s = ret_index(source);
		int ind_d = ret_index(des);
		for (int i = 0; i < table[ind_s].dest.size(); i++)
		{
			if (table[ind_s].dest[i].id == ind_d)
			{
				for (int j = i; j < table[ind_s].dest.size() - 1; j++)
				{
					table[ind_s].dest[i] = table[ind_s].dest[i + 1];
					table[ind_s].dest[i].id--;
				}
				table[ind_s].dest.pop_back();
			}
		}
	}

	void print()
	{
		for (unsigned i = 0; i < table.size(); i++)
		{
			cout << "From ";
			cout << table.at(i).source;
			cout << " to ";
			for (unsigned j = 0; j < table.at(i).dest.size(); j++)
			{
				cout << table.at(i).dest.at(j).des;
				cout << " by ";
				cout << table.at(i).dest.at(j).edge;
				if (j != table.at(i).dest.size() - 1)
				{
					cout << ", ";
				}
			}
			cout << endl;
		}
	}

	void deep_search()
	{
		int t = 0;
		deep(table[0], t);
		for (int i = 0; i < table.size(); i++)
		{
			if (table[i].inf.color == 0)
			{
				deep(table[i], t);
			}
		}
	}
	void deep(Vertex s, int& t)
	{
		table[s.id].inf.color = 1;
		table[s.id].inf.t_open = t;
		t++;
		for (int j = 0; j < table[s.id].dest.size(); j++)
		{
			if (table[table[s.id].dest[j].id].inf.color == 0)
			{
				table[table[s.id].dest[j].id].inf.prev = table[s.id].source;
				deep(table[table[s.id].dest[j].id], t);
			}
		}
		table[s.id].inf.color = 2;
		table[s.id].inf.t_close = t;
		cout << table[s.id].source << endl;
		t++;
	}

	struct DVertex {
		TVertex prev;
		TVertex cur;
		TEdge d;
		DVertex() : d(999999) {}
		DVertex operator=(const DVertex& c)
		{
			this->prev = c.prev;
			this->cur = c.cur;
			this->d = c.d;
			return *this;
		}
		bool operator()(const DVertex& lhs, const DVertex& rhs)
		{
			return(lhs.d < rhs.d);
		}
		operator double()
		{
			return this->d;
		}
	};


};
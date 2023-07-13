#include <bits/stdc++.h>
using namespace std;
map<string, map<string, int>> vtces;

void addVertex(string vname)
{
	vtces[vname];
}

void addEdge(string vname1, string vname2, int value)
{

	if (vtces[vname1].find(vname2) != vtces[vname1].end())
	{
		return;
	}

	vtces[vname1][vname2] = value;
	vtces[vname2][vname1] = value;
}

void create_metro()
{
	addVertex("Ghatkopar");
	addVertex("Jagruti Nagar");
	addVertex("Asalpha (Subhash Nagar)");
	addVertex("Saki Naka");
	addVertex("Marol Naka");
	addVertex("Airport Road");
	addVertex("Chakala (J.B.Nagar)");
	addVertex("Western Express Highway");
	addVertex("Andheri");
	addVertex("Azad Nagar");
	addVertex("D.N. Nagar");
	addVertex("Versova");
	addVertex("Thane");
	addVertex("Powai");
	addVertex("Goregaon");
	addVertex("Kalyan");
	addVertex("Malad");
	addVertex("Bhayandar");
	addVertex("Kandivali");
	addVertex("Kurla");

	addEdge("Ghatkopar", "Jagruti Nagar", 8);
	addEdge("Jagruti Nagar", "Asalpha (Subhash Nagar)", 10);
	addEdge("Asalpha (Subhash Nagar)", "Marol Naka", 8);
	addEdge("Asalpha (Subhash Nagar)", "Saki Naka", 6);
	addEdge("Saki Naka", "Airport Road", 9);
	addEdge("Airport Road", "Chakala (J.B.Nagar)", 7);
	addEdge("Chakala (J.B.Nagar)", "Western Express Highway", 6);
	addEdge("Andheri", "Azad Nagar", 15);
	addEdge("Azad Nagar", "Powai", 6);
	addEdge("Powai", "Saki Naka", 7);
	addEdge("Saki Naka", "Thane", 1);
	addEdge("Thane", "Versova", 2);
	addEdge("Versova", "D.N. Nagar", 5);
	addEdge("Thane", "Goregaon", 2);
	addEdge("Goregaon", "Kalyan", 7);
	addEdge("Kalyan", "Malad", 8);
	addEdge("Airport Road", "Bhayandar", 2);
	addEdge("Kurla", "Bhayandar", 2);
	addEdge("Kurla", "Kandivali", 3);
}

void display_Stations()
{
	cout << "\n***********************************************************************\n"
		 << endl;
	vector<string> keys;

	for (auto it = vtces.begin(); it != vtces.end(); it++)
	{
		keys.push_back(it->first);
	}

	for (int i = 0; i < keys.size(); i++)
	{
		cout << i + 1 << "." << keys[i] << endl;
	}

	cout << "\n***********************************************************************\n"
		 << endl;
}

void display_Map()
{
	cout << "\t Delhi Metro Map" << endl;
	cout << "\t------------------" << endl;
	cout << "----------------------------------------------------\n"
		 << endl;

	for (auto it : vtces)
	{
		cout << it.first << "=>" << endl;
		for (auto itt : it.second)
		{
			cout << '\t' << itt.first << '\t';
			if (itt.first.length() < 16)
				cout << '\t';
			if (itt.first.length() < 8)
				cout << '\t';
			cout << itt.second << endl;
		}

		cout << endl;
	}

	cout << "\t------------------" << endl;
	cout << "---------------------------------------------------\n"
		 << endl;
}

vector<string> no_Of_Station(string src, string des)
{
	priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

	map<string, int> dist;
	map<string, string> track;

	for (auto it : vtces)
	{
		track[it.first] = it.first;
	}
	for (auto it : vtces)
		dist[it.first] = 1e9;

	dist[src] = 0;
	pq.push({0, src});

	while (!pq.empty())
	{
		int dis = pq.top().first;
		string node = pq.top().second;
		pq.pop();

		for (auto it : vtces[node])
		{
			int edgeWeight = it.second;
			string adjNode = it.first;
			if (dis + edgeWeight < dist[adjNode])
			{
				dist[adjNode] = dis + edgeWeight;
				pq.push({dist[adjNode], adjNode});
				track[adjNode] = node;
			}
		}
	}

	vector<string> path;
	string node = des;
	while (track[node] != node)
	{
		path.push_back(node);
		node = track[node];
	}

	reverse(path.begin(), path.end());

	return path;
}

bool containsVertex(string st, vector<string> keys)
{
	for (string a : keys)
	{
		if (a == st)
			return true;
	}
	return false;
}

bool containsEdge(string vname1, string vname2)
{
	if (vtces[vname1].find(vname2) == vtces[vname1].end())
	{
		return false;
	}

	return true;
}

bool hasPath(string vname1, string vname2, map<string, bool> processed)
{
	if (containsEdge(vname1, vname2))
	{
		return true;
	}

	processed[vname1] = true;

	for (auto it : vtces[vname1])
	{
		if (processed.find(it.first) == processed.end())
		{
			if (hasPath(it.first, vname2, processed))
			{
				return true;
			}
		}
	}

	return false;
}

int dijkstra(string src, string des, bool nan)
{
	priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
	// vector<int> dist(V);
	map<string, int> dist;
	for (auto it : vtces)
		dist[it.first] = 1e9;

	dist[src] = 0;
	pq.push({0, src});

	while (!pq.empty())
	{
		int dis = pq.top().first;
		string node = pq.top().second;
		pq.pop();

		for (auto it : vtces[node])
		{
			int edgeWeight = it.second;
			string adjNode = it.first;
			if (dis + edgeWeight < dist[adjNode])
			{
				dist[adjNode] = dis + edgeWeight;
				pq.push({dist[adjNode], adjNode});
			}
		}
	}

	for (auto it : dist)
	{
		if (it.first == des)
		{
			return it.second;
		}
	}
}

int main()
{

	cout << "\n\t\t\t****WELCOME TO THE METRO APP*****" << endl;

	create_metro();

	while (true)
	{
		cout << "\t\t\t\t~~LIST OF ACTIONS~~\n\n"
			 << endl;
		cout << "1. LIST ALL THE STATIONS IN THE MAP" << endl;
		cout << "2. SHOW THE METRO MAP" << endl;
		cout << "3. GET SHORTEST DISTANCE FROM A 'SOURCE' STATION TO 'DESTINATION' STATION" << endl;
		cout << "4. GET SHORTEST TIME TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION" << endl;
		cout << "5. EXIT THE MENU" << endl;
		cout << "\nENTER YOUR CHOICE FROM THE ABOVE LIST (1 to 5) : ";

		int choice;
		cin >> choice;

		cout << "\n***********************************************************\n";

		if (choice == 5)
		{
			cout << "\n*********THE END********";
			break;
		}

		switch (choice)
		{
		case 1:
		{
			display_Stations();
			break;
		}
		case 2:
		{
			display_Map();
			break;
		}

		case 3:
		{

			display_Stations();
			string st1, st2;

			cout << "ENTER THE SOURCE STATION: " << endl;
			getline(cin >> ws, st1);

			cout << "ENTER THE DESTINATION STATION: " << endl;
			getline(cin >> ws, st2);

			map<string, bool> processed;

			vector<string> keys;
			for (auto it = vtces.begin(); it != vtces.end(); it++)
			{
				keys.push_back(it->first);
			}

			if (!containsVertex(st1, keys) || !containsVertex(st2, keys) || !hasPath(st1, st2, processed))
				cout << "THE INPUTS ARE INVALID" << endl;
			else
				cout << "SHORTEST DISTANCE FROM " << st1 << " TO " << st2 << " IS " << dijkstra(st1, st2, false) << "KM\n"
					 << endl;

			vector<string> path = no_Of_Station(st1, st2);
			string ans = st1 + " " + "=>" + " ";
			for (int i = 0; i < path.size(); i++)
			{
				if (i == path.size() - 1)
					ans = ans + path[i];
				else
					ans = ans + path[i] + " " + "=>" + " ";
			}
			cout << "SHORTEST PATH FROM" << st1 << "TO" << st2 << "IS" << " " << ans << endl;
			cout << "NO. OF STATIONS ON THE WAY ARE" << " " << path.size() - 1;
			break;
		}

		case 4:
		{

			display_Stations();
			string st1, st2;

			cout << "ENTER THE SOURCE STATION: " << endl;
			getline(cin >> ws, st1);

			cout << "ENTER THE DESTINATION STATION: " << endl;
			getline(cin >> ws, st2);

			map<string, bool> processed1;

			double val = (dijkstra(st1, st2, true) / 45.0) * 60;
			cout << "SHORTEST TIME FROM " << st1 << " TO" << st2 << "IS " << " " << val << " MINUTES\n\n"
				 << endl;
			vector<string> path = no_Of_Station(st1, st2);
			string ans = st1 + " " + "=>" + " ";
			for (int i = 0; i < path.size(); i++)
			{
				if (i == path.size() - 1)
					ans = ans + path[i];
				else
					ans = ans + path[i] + " " + "=>" + " ";
			}
			cout << "SHORTEST PATH FROM" << st1 << "TO" << st2 << "IS" << ans << endl;
			cout << "NO. OF STATIONS ON THE WAY ARE" << " " << path.size() - 1;
			break;
		}
		break;
		default: // If switch expression does not match with any case,
			// default statements are executed by the program.
			// No break is needed in the default case
			cout << "Please enter a valid option! " << endl;
			cout << "The options you can choose are from 1 to 4. " << endl;
		}
	}
}
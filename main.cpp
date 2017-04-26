#include <iostream>
#include <vector>
#include <algorithm>

#define FAIL "Insuficiente"

class Buildable {
public:
    unsigned int cost;
    bool built = false;

    Buildable(unsigned int c) : cost(c) {}
};

class City : public Buildable {
public:
    unsigned int id;
    bool reachable = false;

    City(unsigned int i) : Buildable(0), id(i) {}
};

class Road : public Buildable {
public:
    City *city1, *city2;
    bool virt = false;

    void build() {
      city1->built = true;
      city2->built = true;
    }

    Road(City *c1, City *c2, unsigned int c) : Road(c1, c2, c, false) {};

    Road(City *c1, City *c2, unsigned int c, bool v) : Buildable(c), city1(c1), city2(c2), virt(v) {};
};

using namespace std;

int main(int argc, char const *argv[]) {
  unsigned int N, A, E; /* Cities, Airports, Edges/Paths */
  unsigned int a, b, c;
  vector<City *> cities;
  vector<Road *> roads;

  /* INPUTING */

  cin >> N;
  for (unsigned int i = 0; i <= N; i++) {
    cities.push_back(new City(i));
  }
  City *sky = cities.at(0);

  cin >> A;
  cout << "Reading " << A << " Airports" << endl;
  for (unsigned int i = 0; i < A; i++) {
    cin >> a >> c;
    City *city = cities.at(a);
    city->cost = c;
    city->reachable = true;

    roads.push_back(new Road(city, sky, c, true));
  }

  cin >> E;
  cout << "Reading " << E << " Streets" << endl;
  for (unsigned int i = 0; i < E; i++) {
    cin >> a >> b >> c;
    roads.push_back(new Road(cities.at(a), cities.at(b), c));
  }

  /* ALGORITHMING */

  cout << "ALGORITHMING... !!!" << endl;

  sort(roads.begin(), roads.end(), [](Road *r1, Road *r2) {
      return (r1->cost == r2->cost) ? (!r1->virt) : r1->cost < r2->cost;
  });

  vector<Road *> mst;
  for (auto road : roads) { // fills in MST (or forest)
    if (!(road->city1->built && road->city2->built)) {
      road->build();
      mst.push_back(road);
    }
  }

  unsigned int cost = 0, nAir = 0, nRoads = 0;
  for (auto m : mst) {
    cost += m->cost;
    if (m->virt) nAir++;
    else nRoads++;
  }

  cout << cost << endl;
  cout << nAir << " " << nRoads << endl;

  return 0;
}

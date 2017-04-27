#include <iostream>
#include <vector>
#include <algorithm>

class City {
public:
    int id;
    bool built = false;

    City(int i) : id(i) {}
};

class Road {
public:
    City *city1, *city2;
    int cost;
    bool virt = false;

    void build() {
      city1->built = true;
      city2->built = true;
    }

    Road(City *c1, City *c2, int c) : Road(c1, c2, c, false) {};

    Road(City *c1, City *c2, int c, bool v) : city1(c1), city2(c2), cost(c), virt(v) {};
};

using namespace std;

int main(int argc, char const *argv[]) {
  int N, A, E; /* Cities, Airports, Edges/Paths */
  int a, b, c;
  vector<City *> cities;
  vector<Road *> roads;

  /* INPUTING */

  cin >> N;
  for (int i = 0; i <= N; i++) {
    cities.push_back(new City(i));
  }
  City *sky = cities.at(0);

  cin >> A;
  //cout << "Reading " << A << " Airports" << endl;
  for (int i = 0; i < A; i++) {
    cin >> a >> c;
    roads.push_back(new Road(cities.at(a), sky, c, true));
  }

  cin >> E;
  //cout << "Reading " << E << " Streets" << endl;
  for (int i = 0; i < E; i++) {
    cin >> a >> b >> c;
    roads.push_back(new Road(cities.at(a), cities.at(b), c));
  }

  /* ALGORITHMING */

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

  for (auto city : cities) {
    if (!city->built){
      cout << "Insuficiente" << endl;
      return 1;
    }
  }

  int cost = 0, nAir = 0, nRoads = 0;
  for (auto m : mst) {
    cost += m->cost;
    if (m->virt) nAir++;
    else nRoads++;
  }

  cout << cost << endl;
  cout << nAir << " " << nRoads << endl;

  return 0;
}

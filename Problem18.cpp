#include <iostream>
#include <queue>
#include <vector>

bool resuelveCaso() {
	int N, k;
	std::cin >> N >> k;
	if (N == 0 && k == 0) return false;
	std::vector<int> v(N);
	for (int& x : v) std::cin >> x;
	std::deque<std::pair<int, int>> q;
	q.push_back({ v[0], k });
	for (int i = 1; i < k; i++) {
		if (q.front().second == i) q.pop_front();
		while (!q.empty() && v[i] > q.back().first) q.pop_back();
		q.push_back({ v[i], i + k });
	}
	printf("%d", q.front());
	for (int i = k; i < N; i++) {
		if (q.front().second == i) q.pop_front();
		while (!q.empty() && v[i] > q.back().first) q.pop_back();
		q.push_back({ v[i], i + k });
		printf(" %d", q.front());
	}
	printf("\n");
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}